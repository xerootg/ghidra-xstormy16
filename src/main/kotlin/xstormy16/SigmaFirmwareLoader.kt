package xstormy16

import java.io.ByteArrayInputStream
import java.math.BigInteger

import ghidra.app.util.MemoryBlockUtils
import ghidra.app.util.bin.ByteProvider
import ghidra.app.util.importer.MessageLog
import ghidra.app.util.opinion.AbstractProgramWrapperLoader
import ghidra.app.util.opinion.LoadSpec
import ghidra.app.util.opinion.Loader
import ghidra.program.model.address.Address
import ghidra.program.model.data.PointerDataType
import ghidra.program.model.lang.LanguageCompilerSpecPair
import ghidra.program.model.listing.Program
import ghidra.program.model.symbol.SourceType
import ghidra.program.model.util.CodeUnitInsertionException

/**
 * Loads the firmware images that SIGMA Optimization Pro downloads for Sigma lenses and the
 * USB Dock UD-01: un-inverts them, picks the right processor, maps flash at its real
 * address and labels the reset/interrupt vectors.
 */
class SigmaFirmwareLoader : AbstractProgramWrapperLoader() {

    override fun getName(): String = "Sigma lens / USB dock firmware"

    override fun findSupportedLoadSpecs(provider: ByteProvider): Collection<LoadSpec> {
        val image = SigmaImage.identify(provider) ?: return emptyList()
        val pair = LanguageCompilerSpecPair(image.kind.languageId, image.kind.compilerSpecId)
        return listOf(LoadSpec(this, 0, pair, true))
    }

    override fun load(program: Program, settings: Loader.ImporterSettings) {
        val image = SigmaImage.identify(settings.provider())
            ?: throw java.io.IOException("Not a Sigma firmware image")
        val log = settings.log()
        when (image.kind) {
            SigmaImage.Kind.LENS -> loadLens(program, image, log)
            SigmaImage.Kind.DOCK -> loadDock(program, image, log)
        }
        val info = program.getOptions(Program.PROGRAM_INFO)
        info.setString("Sigma Image Type", image.kind.description)
        info.setBoolean("Sigma Image Inverted", image.inverted)
        image.chip?.let { info.setString("Sigma Chip", it) }
        image.product?.let { info.setString("Sigma Product", it) }
    }

    private fun loadLens(program: Program, image: SigmaImage, log: MessageLog) {
        val bytes = image.bytes
        val flashEnd = minOf(bytes.size, SigmaImage.LENS_FLASH_END)

        // Near accesses, the stack and the SFRs live in the 16-bit "ram" space; code and far
        // (movf) accesses use the 24-bit "code" space. On the chip the two overlap, which the
        // byte-mapped blocks reproduce: near 0x8000-0xffff reads flash, far 0x0000-0x7fff is RAM.
        val ram = program.addressFactory.getAddressSpace("ram")
        uninitialized(program, "RAM", ram.getAddress(0x0000), 0x7f00, "Internal RAM and low memory", log)
        uninitialized(program, "SFR", ram.getAddress(0x7f00), 0x100, "Special function registers", log,
            volatile = true)
        initialized(program, "FLASH", addr(program, SigmaImage.LENS_FLASH_BASE.toLong()), bytes,
            SigmaImage.LENS_FLASH_BASE, flashEnd - SigmaImage.LENS_FLASH_BASE, "Program flash", log, execute = true)
        program.memory.createByteMappedBlock("NEAR_FLASH", ram.getAddress(0x8000),
            addr(program, 0x8000), 0x8000, false).apply {
            comment = "Near view of the first 32 KiB of flash"
            isWrite = false
        }
        program.memory.createByteMappedBlock("FAR_RAM", addr(program, 0), ram.getAddress(0), 0x8000, false).apply {
            comment = "Far (movf) view of RAM and SFRs"
        }

        // The update header ("CHIPINFORMATION", chip name, region table) sits just below
        // flash, overlapping the SFR window, so it goes in an overlay.
        initialized(program, "image_header", ram.getAddress(0x7f00), bytes, 0x7f00, 0x100,
            "Sigma update-file header (not on the chip)", log, overlay = true)
        if (bytes.size > flashEnd && bytes.copyOfRange(flashEnd, bytes.size).any { it != 0xff.toByte() }) {
            initialized(program, "IMAGE_TAIL", addr(program, flashEnd.toLong()), bytes, flashEnd,
                bytes.size - flashEnd, "Image data beyond the 128 KiB flash", log)
        }

        // Vector table: a run of 4-byte "jmpf" instructions starting at the flash base.
        var count = 0
        while (count < 64) {
            val at = SigmaImage.LENS_FLASH_BASE + 4 * count
            if (bytes[at + 1] != 0x02.toByte() || bytes[at + 3] != 0.toByte()) break
            count++
        }
        val symbols = program.symbolTable
        for (n in 0 until count) {
            val at = SigmaImage.LENS_FLASH_BASE + 4 * n
            val vector = addr(program, at.toLong())
            // jmpf: low 8 address bits in the first byte, high 16 in the second word
            val target = bytes.u8(at) or (bytes.u8(at + 2) shl 8) or (bytes.u8(at + 3) shl 16)
            val name = if (n == 0) "RESET" else "VECTOR_%02d".format(n)
            symbols.createLabel(vector, name, SourceType.IMPORTED)
            symbols.addExternalEntryPoint(vector)
            if (target in SigmaImage.LENS_FLASH_BASE until flashEnd) {
                val handler = addr(program, target)
                symbols.createLabel(handler, "${name}_handler", SourceType.IMPORTED)
                symbols.addExternalEntryPoint(handler)
            }
        }
    }

    private fun loadDock(program: Program, image: SigmaImage, log: MessageLog) {
        val bytes = image.bytes
        var used = bytes.size
        while (used > 0 && bytes[used - 1] == 0xff.toByte()) used--
        used = (used + 0xfff) and 0xfff.inv()

        initialized(program, "FLASH", addr(program, 0), bytes, 0, used, "Program flash", log, execute = true)
        uninitialized(program, "SRAM", addr(program, 0x2000_0000), 0x10000, "On-chip SRAM", log)
        uninitialized(program, "PERIPHERALS", addr(program, 0x4000_0000), 0x10_0000, "Peripheral registers", log, volatile = true)
        uninitialized(program, "SCS", addr(program, 0xE000_E000), 0x1000, "System control space", log, volatile = true)

        // Thumb everywhere: Cortex-M has no ARM state.
        val tmode = program.programContext.getRegister("TMode")
        program.programContext.setValue(tmode, addr(program, 0), addr(program, used - 1L), BigInteger.ONE)

        val names = listOf("initial_sp", "Reset", "NMI", "HardFault", "MemManage", "BusFault", "UsageFault",
            null, null, null, null, "SVCall", "DebugMonitor", null, "PendSV", "SysTick")
        val symbols = program.symbolTable
        val listing = program.listing
        // Past the 16 system entries, the table ends at the first word that is neither zero
        // nor a Thumb pointer into flash.
        for (n in 0 until 256) {
            val value = bytes.u32(4 * n)
            val isHandler = n > 0 && (value and 1L) == 1L && value < used
            if (n >= names.size && value != 0L && !isHandler) break
            val name = if (n < names.size) names[n] else "IRQ%d".format(n - names.size)
            val slot = addr(program, 4L * n)
            if (name != null) {
                symbols.createLabel(slot, "vector_$name", SourceType.IMPORTED)
            }
            try {
                listing.createData(slot, PointerDataType.dataType)
            } catch (e: CodeUnitInsertionException) {
                log.appendMsg("Could not mark vector $n: ${e.message}")
            }
            if (isHandler && name != null) {
                val handler = addr(program, value and 1L.inv())
                symbols.createLabel(handler, "${name}_Handler", SourceType.IMPORTED)
                symbols.addExternalEntryPoint(handler)
            }
        }
    }

    private fun addr(program: Program, offset: Long): Address =
        program.addressFactory.defaultAddressSpace.getAddress(offset)

    private fun initialized(
        program: Program, name: String, start: Address, bytes: ByteArray, from: Int, length: Int,
        comment: String, log: MessageLog, execute: Boolean = false, overlay: Boolean = false,
    ) {
        if (length <= 0) return
        MemoryBlockUtils.createInitializedBlock(
            program, overlay, name, start,
            ByteArrayInputStream(bytes, from, length), length.toLong(),
            comment, "Sigma firmware", true, !execute, execute, log, ghidra.util.task.TaskMonitor.DUMMY,
        )
    }

    private fun uninitialized(
        program: Program, name: String, start: Address, length: Int, comment: String, log: MessageLog,
        volatile: Boolean = false,
    ) {
        val block = MemoryBlockUtils.createUninitializedBlock(
            program, false, name, start, length.toLong(),
            comment, "Sigma firmware", true, true, false, log,
        )
        block?.isVolatile = volatile
    }
}
