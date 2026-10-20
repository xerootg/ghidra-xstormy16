// Aggregate metrics over a real lens image, for tracking decompiler quality and for the
// ABI evidence behind prototype changes. Run it on an image imported with the Sigma loader
// and full analysis (see run.sh). It writes counts only: no addresses, bytes, names,
// instructions or hashes of anything in the image, so the output may be committed.
// Usage (headless): -postScript LensMetrics.java <output.json>
//@category Xstormy16

import java.io.PrintWriter;
import java.util.*;

import com.google.gson.GsonBuilder;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.AddressSpace;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.*;
import ghidra.program.model.symbol.Symbol;

public class LensMetrics extends GhidraScript {
	private static final Set<String> FLAGS = Set.of("Z8", "Z16", "CY", "HC", "OV", "PT", "S");
	private static final Set<Integer> COMPARES = Set.of(PcodeOp.INT_EQUAL, PcodeOp.INT_NOTEQUAL,
		PcodeOp.INT_LESS, PcodeOp.INT_LESSEQUAL, PcodeOp.INT_SLESS, PcodeOp.INT_SLESSEQUAL, PcodeOp.INT_SBORROW);
	private static final Set<Integer> BOOLEANS = Set.of(PcodeOp.BOOL_AND, PcodeOp.BOOL_OR, PcodeOp.BOOL_XOR,
		PcodeOp.BOOL_NEGATE, PcodeOp.INT_CARRY, PcodeOp.INT_SCARRY);
	/** How far the call-site and return scans look, in instructions. */
	private static final int WINDOW = 8;

	@Override
	protected void run() throws Exception {
		Map<String, Object> out = new LinkedHashMap<>();
		out.put("image", imageMetrics());
		out.put("abi", abiMetrics());
		out.put("decompiler_default", decompilerMetrics());
		// The same functions under the GCC convention, for comparison (not saved).
		for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
			f.setCallingConvention("__gcc");
		}
		out.put("decompiler_gcc", decompilerMetrics());
		try (PrintWriter w = new PrintWriter(getScriptArgs()[0])) {
			w.println(new GsonBuilder().setPrettyPrinting().create().toJson(out));
		}
	}

	private Map<String, Object> imageMetrics() {
		Map<String, Object> m = new LinkedHashMap<>();
		m.put("functions", currentProgram.getFunctionManager().getFunctionCount());
		int vectors = 0;
		int handlers = 0;
		for (Symbol s : currentProgram.getSymbolTable().getAllSymbols(false)) {
			String n = s.getName();
			if (n.equals("RESET") || n.matches("VECTOR_\\d\\d")) {
				vectors++;
			}
			if (n.matches("(RESET|VECTOR_\\d\\d)_handler")) {
				handlers++;
			}
		}
		m.put("vectors_found", vectors);
		m.put("vector_handlers", handlers);
		int errors = 0;
		int badInsn = 0;
		for (Iterator<Bookmark> it = currentProgram.getBookmarkManager().getBookmarksIterator(BookmarkType.ERROR); it
				.hasNext();) {
			errors++;
			String c = it.next().getComment();
			if (c != null && c.contains("Unable to resolve constructor")) {
				badInsn++;
			}
		}
		m.put("error_bookmarks", errors);
		m.put("bad_instruction_bookmarks", badInsn);
		int iretFns = 0;
		int icalls = 0;
		for (Instruction insn : currentProgram.getListing().getInstructions(true)) {
			if (insn.getMnemonicString().startsWith("icall")) {
				icalls++;
			}
		}
		for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
			if (endsWith(f, "iret")) {
				iretFns++;
			}
		}
		m.put("functions_ending_iret", iretFns);
		m.put("icall_instructions", icalls);
		return m;
	}

	/**
	 * Convention evidence from the listing alone, independent of any prototype: which
	 * registers carry arguments and results, and which ones prologues save.
	 */
	private Map<String, Object> abiMetrics() {
		int[] argRead = new int[8];
		int[] retWrite = new int[8];
		int[] prologuePush = new int[16];
		int[] epiloguePop = new int[16];
		int[] isrPush = new int[16];
		int[] setBeforeCall = new int[8];
		int[] readAfterCall = new int[8];
		int retFns = 0;
		int calls = 0;
		Listing listing = currentProgram.getListing();
		for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
			boolean isr = endsWith(f, "iret");
			// Registers pushed by the run of pushes at entry.
			Instruction insn = listing.getInstructionAt(f.getEntryPoint());
			boolean[] pushed = new boolean[16];
			while (insn != null && insn.getMnemonicString().equals("push")) {
				int r = regIndex(insn.getRegister(0));
				if (r >= 0) {
					pushed[r] = true;
				}
				insn = next(insn);
			}
			for (int r = 0; r < 16; r++) {
				if (pushed[r]) {
					(isr ? isrPush : prologuePush)[r]++;
				}
			}
			// r0-r7 read before being written, along the fall-through path from entry.
			boolean[] written = new boolean[16];
			boolean[] read = new boolean[8];
			insn = listing.getInstructionAt(f.getEntryPoint());
			for (int i = 0; i < 32 && insn != null && !isr; i++) {
				if (!insn.getMnemonicString().equals("push")) {
					for (int r : regsRead(insn)) {
						if (r < 8 && !written[r]) {
							read[r] = true;
						}
					}
				}
				if (insn.getFlowType().isCall() || insn.getFlowType().isJump() || insn.getFlowType().isTerminal()) {
					break;
				}
				for (int r : regsWritten(insn)) {
					written[r] = true;
				}
				insn = next(insn);
			}
			for (int r = 0; r < 8; r++) {
				argRead[r] += read[r] ? 1 : 0;
			}
			// Registers written (other than by pop) shortly before a ret, and popped before any return.
			boolean[] wroteAtRet = new boolean[8];
			boolean[] popped = new boolean[16];
			boolean hasRet = false;
			for (Instruction r : listing.getInstructions(f.getBody(), true)) {
				String m = r.getMnemonicString();
				if (!m.equals("ret") && !m.equals("iret")) {
					continue;
				}
				hasRet |= m.equals("ret");
				Instruction p = r.getPrevious();
				for (int i = 0; i < WINDOW && p != null && f.getBody().contains(p.getAddress()); i++) {
					if (p.getFlowType().isCall() || p.getFlowType().isJump() || p.getFlowType().isTerminal()) {
						break;
					}
					if (p.getMnemonicString().equals("pop")) {
						int reg = regIndex(p.getRegister(0));
						if (reg >= 0) {
							popped[reg] = true;
						}
					}
					else if (m.equals("ret")) {
						for (int reg : regsWritten(p)) {
							if (reg < 8) {
								wroteAtRet[reg] = true;
							}
						}
					}
					p = p.getPrevious();
				}
			}
			if (hasRet) {
				retFns++;
				for (int r = 0; r < 8; r++) {
					retWrite[r] += wroteAtRet[r] ? 1 : 0;
				}
			}
			if (!isr) {
				for (int r = 0; r < 16; r++) {
					epiloguePop[r] += popped[r] ? 1 : 0;
				}
			}
		}
		// Call sites: registers set just before a call, and read just after it.
		for (Instruction c : listing.getInstructions(true)) {
			String m = c.getMnemonicString();
			if (!c.getFlowType().isCall() || m.startsWith("icall")) {
				continue;
			}
			calls++;
			boolean[] set = new boolean[8];
			Instruction p = c.getPrevious();
			for (int i = 0; i < WINDOW && p != null; i++) {
				if (p.getFlowType().isCall() || p.getFlowType().isJump() || p.getFlowType().isTerminal() ||
					isBranchTarget(p.getMaxAddress().next())) {
					break;
				}
				for (int r : regsWritten(p)) {
					if (r < 8) {
						set[r] = true;
					}
				}
				p = p.getPrevious();
			}
			boolean[] written = new boolean[8];
			boolean[] read = new boolean[8];
			Instruction n = next(c);
			for (int i = 0; i < WINDOW && n != null; i++) {
				for (int r : regsRead(n)) {
					if (r < 8 && !written[r]) {
						read[r] = true;
					}
				}
				if (n.getFlowType().isCall() || n.getFlowType().isJump() || n.getFlowType().isTerminal()) {
					break;
				}
				for (int r : regsWritten(n)) {
					if (r < 8) {
						written[r] = true;
					}
				}
				n = next(n);
			}
			for (int r = 0; r < 8; r++) {
				setBeforeCall[r] += set[r] ? 1 : 0;
				readAfterCall[r] += read[r] ? 1 : 0;
			}
		}
		Map<String, Object> m = new LinkedHashMap<>();
		m.put("functions_with_ret", retFns);
		m.put("ret_tail_writes_rN", named(retWrite));
		m.put("entry_reads_rN_before_write", named(argRead));
		m.put("prologue_pushes_rN", named(prologuePush));
		m.put("epilogue_pops_rN", named(epiloguePop));
		m.put("iret_handler_prologue_pushes_rN", named(isrPush));
		m.put("call_sites", calls);
		m.put("call_sites_set_rN_before", named(setBeforeCall));
		m.put("call_sites_read_rN_after", named(readAfterCall));
		return m;
	}

	private Map<String, Object> decompilerMetrics() {
		int ok = 0;
		int failed = 0;
		int extraout = 0;
		int unaff = 0;
		int inRegs = 0;
		int stackWarnings = 0;
		int warnings = 0;
		int baddata = 0;
		int flagInputs = 0;
		int rxiInputs = 0;
		int registerSpaceAccess = 0;
		int cbranches = 0;
		int folded = 0;
		int returnsValue = 0;
		int params = 0;
		Map<String, Integer> roots = new TreeMap<>();
		DecompInterface decompiler = new DecompInterface();
		decompiler.openProgram(currentProgram);
		try {
			for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
				DecompileResults res = decompiler.decompileFunction(f, 60, monitor);
				HighFunction hf = res.getHighFunction();
				if (hf == null) {
					failed++;
					continue;
				}
				ok++;
				String c = res.getDecompiledFunction() == null ? "" : res.getDecompiledFunction().getC();
				for (String line : c.split("\n")) {
					if (line.contains("WARNING")) {
						warnings++;
						stackWarnings += line.toLowerCase().contains("stack") ? 1 : 0;
					}
					baddata += line.contains("halt_baddata") ? 1 : 0;
				}
				for (Iterator<HighSymbol> it = hf.getLocalSymbolMap().getSymbols(); it.hasNext();) {
					String n = it.next().getName();
					extraout += n.startsWith("extraout_") ? 1 : 0;
					unaff += n.startsWith("unaff_") ? 1 : 0;
					inRegs += n.startsWith("in_") ? 1 : 0;
				}
				params += hf.getFunctionPrototype().getNumParams();
				Set<String> inputsSeen = new HashSet<>();
				boolean retVal = false;
				for (Iterator<PcodeOpAST> it = hf.getPcodeOps(); it.hasNext();) {
					PcodeOp op = it.next();
					int code = op.getOpcode();
					if ((code == PcodeOp.LOAD || code == PcodeOp.STORE) && space(op.getInput(0)).isRegisterSpace()) {
						registerSpaceAccess++;
					}
					if (code == PcodeOp.RETURN && op.getNumInputs() > 1) {
						retVal = true;
					}
					if (code == PcodeOp.CBRANCH) {
						PcodeOp root = conditionRoot(op.getInput(1));
						cbranches++;
						folded += isFolded(root) ? 1 : 0;
						roots.merge(root == null ? "none" : root.getMnemonic(), 1, Integer::sum);
					}
					for (Varnode v : op.getInputs()) {
						Register r = register(v);
						if (v.isInput() && r != null && inputsSeen.add(r.getName())) {
							flagInputs += FLAGS.contains(r.getName()) ? 1 : 0;
							rxiInputs += r.getName().equals("RXI") ? 1 : 0;
						}
					}
				}
				returnsValue += retVal ? 1 : 0;
			}
		}
		finally {
			decompiler.dispose();
		}
		Map<String, Object> m = new LinkedHashMap<>();
		m.put("decompiled", ok);
		m.put("decompile_failures", failed);
		m.put("warnings", warnings);
		m.put("stack_warnings", stackWarnings);
		m.put("halt_baddata", baddata);
		m.put("extraout_vars", extraout);
		m.put("unaff_vars", unaff);
		m.put("in_vars", inRegs);
		m.put("params_total", params);
		m.put("functions_returning_value", returnsValue);
		m.put("flag_input_varnodes", flagInputs);
		m.put("rxi_input_varnodes", rxiInputs);
		m.put("register_space_accesses", registerSpaceAccess);
		m.put("cbranches", cbranches);
		m.put("cbranches_folded", folded);
		m.put("cbranch_condition_roots", roots);
		return m;
	}

	/** The branch condition with BOOL_NEGATE and copies stripped. */
	private PcodeOp conditionRoot(Varnode cond) {
		PcodeOp root = cond.getDef();
		while (root != null && (root.getOpcode() == PcodeOp.BOOL_NEGATE || root.getOpcode() == PcodeOp.COPY)) {
			root = root.getInput(0).getDef();
		}
		return root;
	}

	/**
	 * The condition is one comparison of values, not a combination of flag-like booleans
	 * (such as S == OV or CY || Z16 left unfolded).
	 */
	private boolean isFolded(PcodeOp root) {
		if (root == null || !COMPARES.contains(root.getOpcode())) {
			return false;
		}
		for (Varnode in : root.getInputs()) {
			PcodeOp d = in.getDef();
			while (d != null && (d.getOpcode() == PcodeOp.COPY || d.getOpcode() == PcodeOp.CAST)) {
				d = d.getInput(0).getDef();
			}
			if (d != null && (BOOLEANS.contains(d.getOpcode()) || COMPARES.contains(d.getOpcode()))) {
				return false;
			}
		}
		return true;
	}

	// --- listing helpers ---

	private boolean endsWith(Function f, String mnemonic) {
		for (Instruction insn : currentProgram.getListing().getInstructions(f.getBody(), true)) {
			if (insn.getMnemonicString().equals(mnemonic)) {
				return true;
			}
		}
		return false;
	}

	private Instruction next(Instruction insn) {
		return insn.getFallThrough() == null ? null : currentProgram.getListing().getInstructionAt(insn.getFallThrough());
	}

	private boolean isBranchTarget(ghidra.program.model.address.Address a) {
		return currentProgram.getReferenceManager().hasReferencesTo(a);
	}

	/** r0-r15 an instruction's p-code reads, ignoring reads after it writes the register. */
	private Set<Integer> regsRead(Instruction insn) {
		Set<Integer> read = new TreeSet<>();
		Set<Integer> written = new HashSet<>();
		for (PcodeOp op : insn.getPcode()) {
			for (Varnode v : op.getInputs()) {
				int r = regIndex(register(v));
				if (r >= 0 && !written.contains(r)) {
					read.add(r);
				}
			}
			int w = op.getOutput() == null ? -1 : regIndex(register(op.getOutput()));
			if (w >= 0) {
				written.add(w);
			}
		}
		return read;
	}

	private Set<Integer> regsWritten(Instruction insn) {
		Set<Integer> written = new TreeSet<>();
		for (PcodeOp op : insn.getPcode()) {
			int w = op.getOutput() == null ? -1 : regIndex(register(op.getOutput()));
			if (w >= 0) {
				written.add(w);
			}
		}
		return written;
	}

	private int regIndex(Register r) {
		if (r == null || !r.getName().matches("r\\d+")) {
			return -1;
		}
		return Integer.parseInt(r.getName().substring(1));
	}

	private Register register(Varnode v) {
		return v != null && v.isRegister() ? currentProgram.getLanguage().getRegister(v.getAddress(), v.getSize()) : null;
	}

	private AddressSpace space(Varnode spaceId) {
		return currentProgram.getAddressFactory().getAddressSpace((int) spaceId.getOffset());
	}

	private Map<String, Integer> named(int[] counts) {
		Map<String, Integer> m = new LinkedHashMap<>();
		for (int r = 0; r < counts.length; r++) {
			m.put("r" + r, counts[r]);
		}
		return m;
	}
}
