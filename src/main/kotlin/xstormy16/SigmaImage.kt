package xstormy16

import ghidra.app.util.bin.ByteProvider

/**
 * A Sigma firmware image as served to SIGMA Optimization Pro (`EC5_*.bin` for lenses,
 * `EE2_*.bin` for the USB dock).
 *
 * The update files are flash images in which every byte is inverted (XOR 0xFF), so erased
 * flash reads as 0x00. File offset equals flash address. Raw dumps taken straight off the
 * chip are accepted as well; [inverted] records which form the file was in.
 */
class SigmaImage private constructor(
    val kind: Kind,
    /** Image contents in true (non-inverted) form, indexed by flash address. */
    val bytes: ByteArray,
    val inverted: Boolean,
    /** Chip name from the lens header, e.g. "LC88F58B0"; null for the dock. */
    val chip: String?,
    /** Product string found in the image, e.g. "35mm F1.4 DG HSM | Art 012". */
    val product: String?,
) {
    enum class Kind(val languageId: String, val compilerSpecId: String, val description: String) {
        LENS("Xstormy16:LE:32:default", "default", "Sigma lens firmware (Xstormy16)"),
        DOCK("ARM:LE:32:Cortex", "default", "Sigma USB dock firmware (ARM Cortex-M)"),
    }

    companion object {
        /** Lens images carry a header just below the flash base: "CHIPINFORMATION\0<chip>\0". */
        const val LENS_HEADER = 0x7fc0
        const val LENS_FLASH_BASE = 0x8000
        const val LENS_FLASH_END = 0x28000

        private const val MAX_SIZE = 0x100000
        private val CHIP_TAG = "CHIPINFORMATION".toByteArray(Charsets.US_ASCII)
        private val DOCK_TAG = "SIGMA USB-DOCK".toByteArray(Charsets.US_ASCII)

        fun identify(provider: ByteProvider): SigmaImage? {
            val length = provider.length()
            if (length < LENS_FLASH_BASE || length > MAX_SIZE) {
                return null
            }
            val raw = provider.readBytes(0, length)
            for (inverted in listOf(true, false)) {
                val bytes = if (inverted) ByteArray(raw.size) { (raw[it].toInt() xor 0xff).toByte() } else raw
                identifyLens(bytes, inverted)?.let { return it }
                identifyDock(bytes, inverted)?.let { return it }
            }
            return null
        }

        private fun identifyLens(bytes: ByteArray, inverted: Boolean): SigmaImage? {
            if (!bytes.regionMatches(LENS_HEADER, CHIP_TAG)) {
                return null
            }
            val chip = bytes.cString(LENS_HEADER + CHIP_TAG.size + 1)
            return SigmaImage(Kind.LENS, bytes, inverted, chip, findProduct(bytes))
        }

        private fun identifyDock(bytes: ByteArray, inverted: Boolean): SigmaImage? {
            val sp = bytes.u32(0)
            val reset = bytes.u32(4)
            val plausible = sp in 0x2000_0000L..0x2010_0000L && (reset and 1L) == 1L && reset < bytes.size
            if (!plausible || bytes.indexOf(DOCK_TAG) < 0) {
                return null
            }
            return SigmaImage(Kind.DOCK, bytes, inverted, null, "SIGMA USB-DOCK")
        }

        /** Lens images embed their marketing name, e.g. "35mm F1.4 DG HSM | Art 012". */
        private fun findProduct(bytes: ByteArray): String? {
            val text = String(bytes, Charsets.ISO_8859_1)
            return Regex("""\d+(?:-\d+)?mm F\d+(?:\.\d+)?(?:-\d+(?:\.\d+)?)? [ -~]{3,60}""").find(text)?.value?.trim()
        }
    }
}

internal fun ByteArray.u8(offset: Int): Long = this[offset].toLong() and 0xff

internal fun ByteArray.u32(offset: Int): Long =
    (0 until 4).fold(0L) { acc, i -> acc or ((this[offset + i].toLong() and 0xff) shl (8 * i)) }

internal fun ByteArray.regionMatches(offset: Int, needle: ByteArray): Boolean =
    offset + needle.size <= size && needle.indices.all { this[offset + it] == needle[it] }

internal fun ByteArray.indexOf(needle: ByteArray): Int =
    (0..size - needle.size).firstOrNull { regionMatches(it, needle) } ?: -1

internal fun ByteArray.cString(offset: Int): String {
    var end = offset
    while (end < size && this[end] != 0.toByte()) end++
    return String(this, offset, end - offset, Charsets.US_ASCII)
}
