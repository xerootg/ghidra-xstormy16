package xs16.semval;

/**
 * Maps CGEN architectural state onto the SLEIGH registers and back.
 *
 * CGEN h_gr[0..13] and h_gr[15] are r0..r13 and sp. h_gr[14] is the PSW; SLEIGH keeps its
 * flag bits in byte registers and the Rx index in RXI, apart from the psw register:
 *   bit 0 Z8, 1 Z16, 2 CY, 3 HC, 4 OV, 5 PT, 6 S; bits 7-11 psw-hi; bits 12-15 RXI.
 * Only psw-hi lives in the psw register; its flag and Rx bits are stale except right after
 * an instruction that reads or writes r14, which packs them first. Seeding therefore writes
 * the psw register with those bits inverted (STALE), so an explicit r14 read that skips the
 * packing shows up as a mismatch. Readback packs the flags and RXI with psw-hi.
 */
final class StateMap {
	static final int PSW_HI = 0x0f80;
	static final int STALE = 0xf07f;

	/** The PSW fields compared bit by bit, in the order of PSW_BITS. */
	static final String[] PSW_FIELDS = { "Z8", "Z16", "CY", "HC", "OV", "PT", "S" };

	private StateMap() {
	}

	static void seed(Sut sut, int[] r) {
		for (int i = 0; i < 16; i++) {
			sut.setReg(sut.gr[i], i == 14 ? r[i] ^ STALE : r[i]);
		}
		int p = r[14];
		for (int i = 0; i < 7; i++) {
			sut.setReg(sut.flag[i], (p >> i) & 1);
		}
		sut.setReg(sut.rxi, (p >> 12) & 0xf);
	}

	/** The PSW Ghidra's state stands for: (psw & 0x0F80) | flags | RXI << 12. */
	static int pack(Sut.Result s) {
		int v = s.r[14] & PSW_HI;
		for (int i = 0; i < 7; i++) {
			v |= (s.flags[i] & 1) << i;
		}
		return v | (s.rxi & 0xf) << 12;
	}
}
