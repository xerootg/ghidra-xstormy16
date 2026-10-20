package xstormy16

import ghidra.app.services.AbstractAnalyzer
import ghidra.app.services.AnalysisPriority
import ghidra.app.services.AnalyzerType
import ghidra.app.util.importer.MessageLog
import ghidra.program.model.address.Address
import ghidra.program.model.address.AddressSetView
import ghidra.program.model.listing.Program
import ghidra.program.model.mem.MemoryBlock
import ghidra.program.model.mem.MemoryBlockType
import ghidra.util.task.TaskMonitor

/**
 * Moves references that land in a byte-mapped view onto the memory the view maps.
 *
 * In a Sigma lens program, far (movf) accesses address RAM and the SFRs through the
 * FAR_RAM/FAR_SFR views in the code space, so their references would otherwise collect on
 * code-space addresses that no near access or user label ever shares. Pointing them at the
 * ram addresses puts every access to a variable under one set of xrefs. The decompiler still
 * names far accesses by their code-space address.
 */
class FarViewReferenceAnalyzer : AbstractAnalyzer(NAME, DESCRIPTION, AnalyzerType.INSTRUCTION_ANALYZER) {

    init {
        // After constant propagation and operand analysis have made their references.
        setPriority(AnalysisPriority.REFERENCE_ANALYSIS.after())
        setDefaultEnablement(true)
        setSupportsOneTimeAnalysis()
    }

    override fun canAnalyze(program: Program): Boolean =
        program.language.processor.toString() == "Xstormy16" && views(program).isNotEmpty()

    override fun added(program: Program, set: AddressSetView, monitor: TaskMonitor, log: MessageLog): Boolean {
        val views = views(program)
        val refs = program.referenceManager
        for (from in refs.getReferenceSourceIterator(set, true)) {
            monitor.checkCancelled()
            for (ref in refs.getReferencesFrom(from)) {
                if (!ref.isMemoryReference) continue
                val to = mapped(views, ref.toAddress) ?: continue
                refs.delete(ref)
                refs.addMemoryReference(from, to, ref.referenceType, ref.source, ref.operandIndex)
            }
        }
        return true
    }

    /** Byte-mapped blocks in the code space whose target is in another space (FAR_RAM, FAR_SFR). */
    private fun views(program: Program): List<Pair<MemoryBlock, Address>> {
        val code = program.addressFactory.defaultAddressSpace
        return program.memory.blocks.mapNotNull { block ->
            if (block.type != MemoryBlockType.BYTE_MAPPED || block.start.addressSpace != code) return@mapNotNull null
            val target = block.sourceInfos.firstOrNull()?.mappedRange?.orElse(null)?.minAddress
            if (target == null || target.addressSpace == code) null else block to target
        }
    }

    private fun mapped(views: List<Pair<MemoryBlock, Address>>, address: Address): Address? {
        val (block, target) = views.firstOrNull { it.first.contains(address) } ?: return null
        return target.add(address.subtract(block.start))
    }

    private companion object {
        const val NAME = "Xstormy16 Far View References"
        const val DESCRIPTION = "Moves references into byte-mapped code-space views (the far view of RAM and " +
            "SFRs in Sigma lens programs) onto the ram addresses they map, so near and far accesses share xrefs."
    }
}
