package xs16.semval;

import java.util.*;

import ghidra.app.plugin.processors.sleigh.*;
import ghidra.pcode.emu.*;
import ghidra.pcode.exec.*;
import ghidra.pcode.exec.PcodeArithmetic.Purpose;
import ghidra.pcode.exec.PcodeExecutorStatePiece.Reason;
import ghidra.program.model.address.*;
import ghidra.program.model.lang.*;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.pcode.PcodeOp;

/**
 * The system under test: Ghidra's PcodeEmulator running this module's SLEIGH, one
 * instruction per case. One instance per thread; the emulator is reused and reset
 * between cases (dropInstruction plus clearing the shared and thread state).
 *
 * Memory is the flat CGEN bus: ram:A and code:A both read CaseIo.flatByte(A) until the
 * case writes them. Register-space stores (the Rx access) are not memory and are not logged.
 */
final class Sut {
	static final String[] GR = { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9",
		"r10", "r11", "r12", "r13", "psw", "sp" };
	static final String[] FLAGS = { "Z8", "Z16", "CY", "HC", "OV", "PT", "S" };

	/** What one instruction did, as seen through Ghidra. */
	static final class Result {
		String status = "OK";          // OK, INVALID or EXC:<exception class>
		String error;
		long npc;
		int[] r = new int[16];          // raw registers; r[14] is the raw psw register
		int[] flags = new int[7];       // the flag bytes, as stored (should be 0 or 1)
		int rxi;
		TreeMap<Long, Integer> writes = new TreeMap<>();
		Set<Long> reads = new TreeSet<>();
		boolean ramTouched, ramWrap;
		List<String> events = new ArrayList<>();
		Instruction insn;

		/** Everything that must be identical when the same case is run twice. */
		String signature() {
			return status + " " + Long.toHexString(npc) + " " + Arrays.toString(r) + " " +
				Arrays.toString(flags) + " " + rxi + " " + writes + " " + reads + " " + events;
		}
	}

	final Language lang;
	final AddressSpace code, ram;
	final Register[] gr = new Register[16];
	final Register[] flag = new Register[7];
	final Register rxi;
	private final PcodeEmulator emu;
	private final PcodeThread<byte[]> th;
	private final PcodeArithmetic<byte[]> ar;
	private CaseIo.Case cur;
	private Result res;

	Sut(Language lang) {
		this.lang = lang;
		code = lang.getAddressFactory().getAddressSpace("code");
		ram = lang.getAddressFactory().getAddressSpace("ram");
		for (int i = 0; i < 16; i++) {
			gr[i] = lang.getRegister(GR[i]);
		}
		for (int i = 0; i < 7; i++) {
			flag[i] = lang.getRegister(FLAGS[i]);
		}
		rxi = lang.getRegister("RXI");
		emu = new Emulator(lang, new Callbacks());
		th = emu.newThread();
		ar = emu.getArithmetic();
	}

	/**
	 * A PcodeEmulator whose decoder never reuses the last decoded block: the decoder keeps
	 * it across counter overrides, so a new case at the same pc would otherwise execute the
	 * previous case's instruction.
	 */
	private static final class Emulator extends PcodeEmulator {
		Emulator(Language lang, PcodeEmulationCallbacks<byte[]> cb) {
			super(lang, cb);
		}

		@Override
		protected BytesPcodeThread createThread(String name) {
			return new BytesPcodeThread(name, this) {
				@Override
				protected SleighInstructionDecoder createInstructionDecoder(
						PcodeExecutorState<byte[]> sharedState) {
					return new SleighInstructionDecoder(getLanguage(), sharedState) {
						@Override
						protected boolean useCachedInstruction(Address address, RegisterValue ctx) {
							return false;
						}
					};
				}
			};
		}
	}

	private boolean isMemory(AddressSpace s) {
		return s == code || s == ram;
	}

	private final class Callbacks implements PcodeEmulationCallbacks<byte[]> {
		@Override
		public void beforeExecuteInstruction(PcodeThread<byte[]> t, Instruction instruction,
				PcodeProgram program) {
			res.insn = instruction;
		}

		@Override
		public void beforeLoad(PcodeThread<byte[]> t, PcodeOp op, AddressSpace space, byte[] off,
				int size) {
			if (!isMemory(space)) {
				return;
			}
			long a = ar.toLong(off, Purpose.LOAD);
			for (int i = 0; i < size; i++) {
				res.reads.add(flat(space, a + i));
			}
			note(space, a, size);
		}

		@Override
		public void beforeStore(PcodeThread<byte[]> t, PcodeOp op, AddressSpace space, byte[] off,
				int size, byte[] val) {
			if (!isMemory(space)) {
				return;
			}
			long a = ar.toLong(off, Purpose.STORE);
			long v = ar.toLong(val, Purpose.INSPECT);
			for (int i = 0; i < size; i++) {
				res.writes.put(flat(space, a + i), (int) (v >>> (8 * i)) & 0xff);
			}
			note(space, a, size);
		}

		@Override
		public boolean handleMissingUserop(PcodeThread<byte[]> t, PcodeOp op, PcodeFrame frame,
				String opName, PcodeUseropLibrary<byte[]> library) {
			res.events.add(opName);
			return true;
		}

		@Override
		public <A, U> AddressSetView readUninitialized(PcodeThread<byte[]> t,
				PcodeExecutorStatePiece<A, U> piece, AddressSetView set, Reason reason) {
			if (set.isEmpty() || !isMemory(set.getMinAddress().getAddressSpace())) {
				return set;
			}
			@SuppressWarnings("unchecked")
			PcodeExecutorStatePiece<byte[], byte[]> p = (PcodeExecutorStatePiece<byte[], byte[]>) piece;
			for (AddressRange rg : set) {
				for (Address a = rg.getMinAddress();; a = a.next()) {
					p.setVar(a, 1, false, new byte[] { (byte) CaseIo.flatByte(cur, a.getOffset()) });
					if (a.equals(rg.getMaxAddress())) {
						break;
					}
				}
			}
			return new AddressSet();
		}
	}

	/** ram is 16-bit, so an access running past 0xffff wraps inside Ghidra's space. */
	private long flat(AddressSpace space, long a) {
		return space == ram ? a & 0xffff : a & 0xffffffffL;
	}

	private void note(AddressSpace space, long a, int size) {
		if (space == ram) {
			res.ramTouched = true;
			if (a + size - 1 > 0xffff) {
				res.ramWrap = true;
			}
		}
	}

	private long get(Register r) {
		return ar.toLong(th.getState().getVar(r, Reason.INSPECT), Purpose.INSPECT);
	}

	private void set(Register r, long v) {
		th.getState().setVar(r, ar.fromConst(v, r.getMinimumByteSize()));
	}

	/** Runs one case from a clean state. */
	Result run(CaseIo.Case c) {
		cur = c;
		res = new Result();
		try {
			th.dropInstruction();
		}
		catch (Exception e) {
			// nothing was decoded
		}
		emu.getSharedState().clear();
		th.getState().clear();
		byte[] ib = { (byte) c.w0, (byte) (c.w0 >> 8), (byte) c.w1, (byte) (c.w1 >> 8) };
		emu.getSharedState().setVar(code, ar.fromConst(c.pc, 4), 4, true, ib);
		th.overrideContextWithDefault();
		th.overrideCounter(code.getAddress(c.pc));
		StateMap.seed(this, c.r);
		try {
			th.stepInstruction();
		}
		catch (DecodePcodeExecutionException e) {
			res.status = "INVALID";
		}
		catch (Exception e) {
			res.status = "EXC:" + e.getClass().getSimpleName();
			res.error = String.valueOf(e.getMessage()).replace('\n', ' ');
		}
		res.npc = th.getCounter().getOffset();
		for (int i = 0; i < 16; i++) {
			res.r[i] = (int) get(gr[i]) & 0xffff;
		}
		for (int i = 0; i < 7; i++) {
			res.flags[i] = (int) get(flag[i]) & 0xff;
		}
		res.rxi = (int) get(rxi) & 0xff;
		return res;
	}

	void setReg(Register r, long v) {
		set(r, v);
	}

	/**
	 * The SLEIGH constructors that built the instruction, root first, as source line
	 * numbers ("351" or "262>202"), plus the file they came from.
	 */
	static String ctorChain(Instruction insn) {
		if (insn == null || !(insn.getPrototype() instanceof SleighInstructionPrototype p)) {
			return "-";
		}
		StringBuilder sb = new StringBuilder();
		walk(p.getRootState(), sb);
		return sb.toString();
	}

	private static void walk(ConstructState s, StringBuilder sb) {
		if (s == null) {
			return;
		}
		Constructor ct = s.getConstructor();
		if (ct != null) {
			if (sb.length() > 0) {
				sb.append('>');
			}
			sb.append(ct.getLineno());
		}
		for (int i = 0; i < s.getNumSubStates(); i++) {
			walk(s.getSubState(i), sb);
		}
	}

	static String ctorFile(Instruction insn) {
		if (insn != null && insn.getPrototype() instanceof SleighInstructionPrototype p &&
			p.getRootState().getConstructor() != null) {
			return p.getRootState().getConstructor().getSourceFile();
		}
		return "-";
	}
}
