// Decompiler golden checks over the test/decomp fixtures. Each check inspects the
// decompiler's HighFunction p-code (not its C text) for one fixture function, and the
// result is compared with expectations.json: "pass" checks must pass, "xfail" checks are
// tied to an open finding and must still fail, so a fix shows up as an unexpected pass
// until the expectation is updated.
// Usage (headless): -postScript DecompCheck.java <symbols-file> <expectations.json> <results-file>
//@category Xstormy16

import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;
import java.util.function.Predicate;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import ghidra.app.cmd.function.CallDepthChangeInfo;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSpace;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.pcode.*;
import ghidra.program.model.symbol.Reference;

public class DecompCheck extends GhidraScript {
	private static final Set<String> FLAGS = Set.of("Z8", "Z16", "CY", "HC", "OV", "PT", "S");
	private static final Set<Integer> COMPARES = Set.of(PcodeOp.INT_EQUAL, PcodeOp.INT_NOTEQUAL,
		PcodeOp.INT_LESS, PcodeOp.INT_LESSEQUAL, PcodeOp.INT_SLESS, PcodeOp.INT_SLESSEQUAL);
	/** Conditions that are a plain relation between the two operands. */
	private static final Set<String> RELATIONAL =
		Set.of("ge", "nc", "lt", "c", "gt", "hi", "le", "ls", "nz", "z");
	private static final String[] CONDITIONS =
		{ "ge", "nc", "lt", "c", "gt", "hi", "le", "ls", "pl", "nv", "mi", "v", "nzb", "nz", "zb", "z" };

	private final Map<String, Address> symbols = new LinkedHashMap<>();
	private final Map<String, HighFunction> highs = new HashMap<>();
	private final Map<String, String> warnings = new HashMap<>();
	private final Map<String, String[]> results = new LinkedHashMap<>();
	private DecompInterface decompiler;

	@Override
	protected void run() throws Exception {
		String[] args = getScriptArgs();
		for (String line : Files.readAllLines(Path.of(args[0]))) {
			String[] f = line.trim().split("\\s+");
			if (f.length == 2) {
				symbols.put(f[0], toAddr(Long.parseLong(f[1], 16)));
			}
		}
		decompiler = new DecompInterface();
		decompiler.openProgram(currentProgram);
		try {
			runChecks();
		}
		finally {
			decompiler.dispose();
		}
		report(JsonParser.parseString(Files.readString(Path.of(args[1]))).getAsJsonObject(), args[2]);
	}

	private void runChecks() {
		// 1. Rx resolves to a register once a flag-setting instruction has named it.
		check("rx-known", "t_rx_known", hf -> {
			String bad = registerSpaceAccess(hf) + rxiInput(hf);
			PcodeOp def = storedAt(hf, 0x40).stream().map(v -> through(v).getDef()).findFirst().orElse(null);
			if (def == null || def.getOpcode() != PcodeOp.INT_OR) {
				bad += " stored value is " + describe(def);
			}
			return bad;
		});
		// Rx before anything sets it names a register chosen by the caller's PSW. Expected:
		// that dependency stays visible as an RXI input instead of a guessed register.
		check("rx-entry-visible", "t_rx_entry", hf -> rxiInput(hf).isEmpty() ? "no RXI input" : "");
		// No other fixture leaves Rx unresolved or reads a flag the function did not set.
		checkAll("rx-resolved-everywhere", n -> !n.equals("t_rx_entry"), hf -> registerSpaceAccess(hf) + rxiInput(hf));
		checkAll("no-flag-inputs", n -> true, this::flagInputs);

		// 2. Compare-and-branch folds into one comparison of the original operands.
		for (String cc : CONDITIONS) {
			for (String form : new String[] { "rr", "ri", "rx" }) {
				check("cc-" + form + "-" + cc, "t_cc_" + form + "_" + cc,
					hf -> foldedCondition(hf, RELATIONAL.contains(cc), Set.of("r2", "r3")));
			}
		}
		for (String fn : new String[] { "t_bit_lmem", "t_bit_hmem", "t_bit_reg_imm", "t_bit_reg_reg" }) {
			check(fn.substring(2).replace('_', '-'), fn, this::bitTest);
		}

		// 3. 32-bit signed compare (sub, sbc, blt) and add (add, adc) become 4-byte operations.
		check("wide-slt", "t_wide_slt", hf -> {
			PcodeOp root = conditionRoot(hf);
			if (root == null) {
				return "no single CBRANCH";
			}
			boolean ok = (root.getOpcode() == PcodeOp.INT_SLESS || root.getOpcode() == PcodeOp.INT_SLESSEQUAL) &&
				root.getInput(0).getSize() == 4;
			return ok ? "" : "condition is " + tree(root.getOutput(), 4);
		});
		// Short of that, the sbc's overflow must combine its two partial borrows exclusively
		// (an overflow in both steps cancels), not with an OR.
		check("wide-slt-ov", "t_wide_slt", hf -> {
			PcodeOp root = conditionRoot(hf);
			String shape = root == null ? "" : tree(root.getOutput(), 6);
			boolean ok = root != null && (root.getOpcode() == PcodeOp.INT_SLESS ||
				shape.matches(".*(INT_NOTEQUAL|BOOL_XOR|INT_XOR)\\(INT_SBORROW\\(.*INT_SBORROW.*"));
			return ok ? "" : "condition is " + shape;
		});
		// The adc consumes the add's carry directly: CARRY(lo, lo) with no flag left over.
		check("wide-add", "t_wide_add", hf -> {
			StringJoiner shapes = new StringJoiner(", ");
			boolean ok = true;
			for (Varnode v : storedAt(hf, 0x42)) {
				String shape = tree(through(v), 5);
				ok &= shape.contains("INT_CARRY(in:r2,in:r4)") && !hasFlag(shape);
				shapes.add(shape);
			}
			return ok && shapes.length() > 0 ? "" : "high word is " + shapes;
		});

		// 4. Calls and returns: a pushed argument comes back from the pop after a call.
		check("call-frame", "t_call_frame", hf -> {
			String bad = callsTo(hf, "t_call_leaf") ? "" : "no CALL to t_call_leaf;";
			return bad + tracesToInput(hf, 0x40, "r2") + stackWarnings("t_call_frame");
		});
		check("call-depth-balanced", "t_call_frame", hf -> depthAtReturns("t_call_frame"));

		// 5. icall pushes 6 bytes and the target returns with iret.
		check("icall-frame", "t_icall_frame", hf -> tracesToInput(hf, 0x40, "r2") + stackWarnings("t_icall_frame"));
		check("icall-depth-balanced", "t_icall_frame", hf -> depthAtReturns("t_icall_frame"));
		// An interrupt handler takes nothing and returns nothing, whatever prototype the
		// loader or analysis gives it.
		check("iret-handler-signature", "t_iret_handler", hf -> {
			FunctionPrototype proto = hf.getFunctionPrototype();
			String bad = proto.getNumParams() == 0 ? "" : proto.getNumParams() + " params;";
			return bad + (returnsValue(hf) ? " returns a value" : "");
		});

		// 6. GCC ABI with the default prototype: arguments in r2.., result in r2, r8/r9
		// clobbered by calls, r10-r13 preserved, r13 frame pointer.
		check("abi-callee-r2", "t_abi_add2", hf -> {
			FunctionPrototype proto = hf.getFunctionPrototype();
			String bad = "";
			if (proto.getNumParams() != 2 || !isRegister(proto.getParam(0).getStorage().getFirstVarnode(), "r2") ||
				!isRegister(proto.getParam(1).getStorage().getFirstVarnode(), "r3")) {
				bad += " params " + params(proto) + ";";
			}
			return bad + (returnsValue(hf) ? "" : " no return value");
		});
		check("abi-caller-r2", "t_abi_caller", hf -> {
			String bad = "";
			for (Iterator<PcodeOpAST> it = hf.getPcodeOps(); it.hasNext();) {
				PcodeOp op = it.next();
				if (op.getOpcode() == PcodeOp.CALL && (op.getNumInputs() != 3 || !isConst(op.getInput(1), 5) ||
					!isConst(op.getInput(2), 7))) {
					bad += " call args " + (op.getNumInputs() - 1) + ";";
				}
			}
			List<Varnode> stored = storedAt(hf, 0x40);
			if (stored.isEmpty()) {
				bad += " nothing stored;";
			}
			for (Varnode v : stored) {
				Varnode src = through(v);
				if (src.getDef() == null || src.getDef().getOpcode() != PcodeOp.CALL) {
					bad += " stored value from " + describe(src.getDef()) + ";";
				}
			}
			for (Iterator<HighSymbol> it = hf.getLocalSymbolMap().getSymbols(); it.hasNext();) {
				String name = it.next().getName();
				if (name.startsWith("extraout_")) {
					bad += " " + name;
				}
			}
			return bad;
		});
		check("abi-r8-clobbered", "t_abi_keep8", hf -> storedAt(hf, 0x40).isEmpty() ? "nothing stored"
			: tracesToInput(hf, 0x40, "r2").isEmpty() ? "r8 propagated across the call" : "");
		check("abi-r10-preserved", "t_abi_keep10", hf -> tracesToInput(hf, 0x40, "r2"));
		check("abi-frame-r13", "t_abi_frame", hf -> tracesToInput(hf, 0x40, "r2") + stackWarnings("t_abi_frame"));

		// 7. SFRs are volatile through either view, and far accesses land on ram symbols.
		check("far-sfr-volatile", "t_far_sfr_twice", hf -> readsOf(hf, 0x7f10) >= 2 ? "" : "reads merged");
		check("near-sfr-volatile", "t_near_sfr_twice", hf -> readsOf(hf, 0x7f10) >= 2 ? "" : "reads merged");
		check("far-sfr-xref", "t_far_sfr_twice", hf -> refsTo("t_far_sfr_twice", ram(0x7f10)));
		check("near-sfr-xref", "t_near_sfr_twice", hf -> refsTo("t_near_sfr_twice", ram(0x7f10)));
		// A near read above 0x8000 lands on the flash word through the near view, with a reference.
		check("near-flash-read", "t_near_flash", hf -> {
			Address near = ram(symbols.get("d_flash_word").getOffset());
			List<Varnode> stored = storedAt(hf, 0x40);
			for (Varnode v : stored) {
				Varnode src = through(v);
				if (!isConst(src, 0x1234) && !src.getAddress().equals(near)) {
					return "stores " + describe(stored);
				}
			}
			return stored.isEmpty() ? "nothing stored" : refsTo("t_near_flash", near);
		});

		// 8. br Rd into a jmpf table is recovered as a switch.
		check("jumptable-br", "t_jt_switch", hf -> {
			JumpTable[] tables = hf.getJumpTables();
			if (tables == null || tables.length != 1) {
				return (tables == null ? 0 : tables.length) + " jump tables";
			}
			int cases = tables[0].getCases().length;
			return cases >= 4 ? "" : cases + " cases";
		});

		// System instructions: a software reset does not return; halt resumes.
		check("flow-reset-noreturn", "t_flow_reset", hf -> {
			Instruction insn = firstWithMnemonic("t_flow_reset", "reset");
			return insn == null ? "no reset" : insn.getFallThrough() == null ? "" : "flow " + insn.getFlowType();
		});
		check("flow-halt-resumes", "t_flow_halt", hf -> {
			Instruction insn = firstWithMnemonic("t_flow_halt", "halt");
			return insn == null ? "no halt" : insn.getFallThrough() != null ? "" : "flow " + insn.getFlowType();
		});
	}

	// --- checks over p-code ---

	private interface Check {
		String run(HighFunction hf) throws Exception;
	}

	/** Records the result of one check; an empty string from the check means it passed. */
	private void check(String id, String fn, Check c) {
		String detail;
		try {
			HighFunction hf = high(fn);
			detail = hf == null ? "decompile failed: " + warnings.get(fn) : c.run(hf).trim();
		}
		catch (Exception e) {
			detail = "error: " + e;
		}
		results.put(id, new String[] { detail.isEmpty() ? "PASS" : "FAIL", detail });
	}

	private void checkAll(String id, Predicate<String> which, Check c) {
		StringBuilder bad = new StringBuilder();
		for (String fn : symbols.keySet()) {
			if (!fn.startsWith("t_") || !which.test(fn)) {
				continue;
			}
			check(id, fn, c);
			if (!results.get(id)[1].isEmpty()) {
				bad.append(fn).append(": ").append(results.get(id)[1]).append("; ");
			}
		}
		results.put(id, new String[] { bad.length() == 0 ? "PASS" : "FAIL", bad.toString().trim() });
	}

	private HighFunction high(String fn) {
		if (!highs.containsKey(fn)) {
			Function f = getFunctionAt(symbols.get(fn));
			HighFunction hf = null;
			if (f == null) {
				warnings.put(fn, "no function");
			}
			else {
				DecompileResults res = decompiler.decompileFunction(f, 60, monitor);
				hf = res.getHighFunction();
				String c = res.getDecompiledFunction() == null ? "" : res.getDecompiledFunction().getC();
				StringBuilder w = new StringBuilder(res.getErrorMessage());
				for (String line : c.split("\n")) {
					if (line.contains("WARNING")) {
						w.append(line.trim()).append(' ');
					}
				}
				warnings.put(fn, w.toString());
			}
			highs.put(fn, hf);
		}
		return highs.get(fn);
	}

	private String stackWarnings(String fn) {
		String w = warnings.getOrDefault(fn, "").toLowerCase();
		return w.contains("stack") ? " stack warning: " + warnings.get(fn) : "";
	}

	/** The condition of the function's only CBRANCH, with BOOL_NEGATE stripped. */
	private PcodeOp conditionRoot(HighFunction hf) {
		PcodeOp branch = null;
		for (Iterator<PcodeOpAST> it = hf.getPcodeOps(); it.hasNext();) {
			PcodeOp op = it.next();
			if (op.getOpcode() == PcodeOp.CBRANCH) {
				if (branch != null) {
					return null;
				}
				branch = op;
			}
		}
		if (branch == null) {
			return null;
		}
		PcodeOp root = branch.getInput(1).getDef();
		while (root != null && (root.getOpcode() == PcodeOp.BOOL_NEGATE || root.getOpcode() == PcodeOp.COPY)) {
			root = root.getInput(0).getDef();
		}
		return root;
	}

	/**
	 * Relational conditions must be a single comparison whose operands are the original
	 * values (inputs or constants). The others (sign, overflow, byte zero) may compute on
	 * the operands first, but no flag may survive.
	 */
	private String foldedCondition(HighFunction hf, boolean strict, Set<String> inputs) {
		PcodeOp root = conditionRoot(hf);
		if (root == null) {
			return "no single CBRANCH";
		}
		String shape = tree(root.getOutput(), 5);
		if (!COMPARES.contains(root.getOpcode()) && root.getOpcode() != PcodeOp.INT_SBORROW) {
			return "condition is " + shape;
		}
		if (strict) {
			for (Varnode in : root.getInputs()) {
				Varnode v = through(in);
				if (!v.isConstant() && !(v.isInput() && inputs.stream().anyMatch(r -> isRegister(v, r)))) {
					return "condition is " + shape;
				}
			}
		}
		if (hasFlag(shape) || countOps(root.getOutput(), 6) > 4) {
			return "condition is " + shape;
		}
		return "";
	}

	private String bitTest(HighFunction hf) {
		PcodeOp root = conditionRoot(hf);
		if (root == null) {
			return "no single CBRANCH";
		}
		String shape = tree(root.getOutput(), 5);
		boolean ok = (root.getOpcode() == PcodeOp.INT_EQUAL || root.getOpcode() == PcodeOp.INT_NOTEQUAL) &&
			shape.contains("INT_AND") && !hasFlag(shape);
		return ok ? "" : "condition is " + shape;
	}

	/** A rendered tree still mentions a flag register. */
	private boolean hasFlag(String shape) {
		return shape.matches(".*\\b(" + String.join("|", FLAGS) + ")\\b.*");
	}

	private String registerSpaceAccess(HighFunction hf) {
		for (Iterator<PcodeOpAST> it = hf.getPcodeOps(); it.hasNext();) {
			PcodeOp op = it.next();
			if ((op.getOpcode() == PcodeOp.LOAD || op.getOpcode() == PcodeOp.STORE) &&
				space(op.getInput(0)).isRegisterSpace()) {
				return " register-space " + op.getMnemonic() + ";";
			}
		}
		return "";
	}

	private String rxiInput(HighFunction hf) {
		return inputs(hf, Set.of("RXI"));
	}

	private String flagInputs(HighFunction hf) {
		return inputs(hf, FLAGS);
	}

	private String inputs(HighFunction hf, Set<String> names) {
		StringBuilder found = new StringBuilder();
		for (Iterator<PcodeOpAST> it = hf.getPcodeOps(); it.hasNext();) {
			for (Varnode v : it.next().getInputs()) {
				Register r = register(v);
				if (v.isInput() && r != null && names.contains(r.getName()) && found.indexOf(r.getName()) < 0) {
					found.append(" input ").append(r.getName()).append(';');
				}
			}
		}
		return found.toString();
	}

	/** Values written to lmem/ram at a constant address, directly or through a STORE. */
	private List<Varnode> storedAt(HighFunction hf, long offset) {
		List<Varnode> out = new ArrayList<>();
		for (Iterator<PcodeOpAST> it = hf.getPcodeOps(); it.hasNext();) {
			PcodeOp op = it.next();
			Varnode o = op.getOutput();
			if (o != null && o.getAddress().isMemoryAddress() && o.getOffset() == offset &&
				o.getAddress().getAddressSpace().getName().equals("ram") && op.getOpcode() != PcodeOp.INDIRECT) {
				out.add(o);
			}
			if (op.getOpcode() == PcodeOp.STORE && space(op.getInput(0)).getName().equals("ram") &&
				isConst(through(op.getInput(1)), offset)) {
				out.add(op.getInput(2));
			}
		}
		return out;
	}

	/** Every value stored at {@code offset} is the function's incoming {@code reg}. */
	private String tracesToInput(HighFunction hf, long offset, String reg) {
		List<Varnode> stored = storedAt(hf, offset);
		if (stored.isEmpty()) {
			return " nothing stored at 0x" + Long.toHexString(offset) + ";";
		}
		for (Varnode v : stored) {
			Varnode src = through(v);
			if (!(src.isInput() && isRegister(src, reg))) {
				return " stored value is " + tree(src, 3) + ";";
			}
		}
		return "";
	}

	/** Separate reads of one address: varnodes at it, plus LOADs from a constant pointer to it. */
	private int readsOf(HighFunction hf, long offset) {
		Set<Varnode> reads = new HashSet<>();
		int loads = 0;
		for (Iterator<PcodeOpAST> it = hf.getPcodeOps(); it.hasNext();) {
			PcodeOp op = it.next();
			if (op.getOpcode() == PcodeOp.LOAD && isConst(through(op.getInput(1)), offset)) {
				loads++;
			}
			for (Varnode v : op.getInputs()) {
				if (v.getAddress().isMemoryAddress() && v.getOffset() == offset) {
					reads.add(v);
				}
			}
		}
		return reads.size() + loads;
	}

	private boolean callsTo(HighFunction hf, String fn) {
		for (Iterator<PcodeOpAST> it = hf.getPcodeOps(); it.hasNext();) {
			PcodeOp op = it.next();
			if (op.getOpcode() == PcodeOp.CALL && op.getInput(0).getAddress().equals(symbols.get(fn))) {
				return true;
			}
		}
		return false;
	}

	private boolean returnsValue(HighFunction hf) {
		for (Iterator<PcodeOpAST> it = hf.getPcodeOps(); it.hasNext();) {
			PcodeOp op = it.next();
			if (op.getOpcode() == PcodeOp.RETURN && op.getNumInputs() > 1) {
				return true;
			}
		}
		return false;
	}

	// --- checks over the listing ---

	/** Stack analysis must see the same depth at every return as at entry. */
	private String depthAtReturns(String fn) throws Exception {
		Function f = getFunctionAt(symbols.get(fn));
		CallDepthChangeInfo info = new CallDepthChangeInfo(f, monitor);
		StringBuilder bad = new StringBuilder();
		for (Instruction insn : currentProgram.getListing().getInstructions(f.getBody(), true)) {
			if (insn.getFlowType().isTerminal()) {
				int depth = info.getDepth(insn.getAddress());
				if (depth != 0) {
					bad.append(" depth ").append(depth).append(" at ").append(insn.getMnemonicString()).append(';');
				}
			}
		}
		return bad.toString();
	}

	private Address ram(long offset) {
		return currentProgram.getAddressFactory().getAddressSpace("ram").getAddress(offset);
	}

	private String refsTo(String fn, Address target) {
		Function f = getFunctionAt(symbols.get(fn));
		for (Reference r : currentProgram.getReferenceManager().getReferencesTo(target)) {
			if (f.getBody().contains(r.getFromAddress())) {
				return "";
			}
		}
		StringBuilder seen = new StringBuilder();
		for (Instruction insn : currentProgram.getListing().getInstructions(f.getBody(), true)) {
			for (Reference r : insn.getReferencesFrom()) {
				seen.append(' ').append(r.getToAddress());
			}
		}
		return "no reference to " + target + "; refs from function:" + seen;
	}

	private Instruction firstWithMnemonic(String fn, String mnemonic) {
		Address a = symbols.get(fn);
		for (int i = 0; i < 8; i++) {
			Instruction insn = getInstructionAt(a);
			if (insn == null) {
				return null;
			}
			if (insn.getMnemonicString().equals(mnemonic)) {
				return insn;
			}
			a = insn.getMaxAddress().next();
		}
		return null;
	}

	// --- varnode helpers ---

	/**
	 * Follows copies, casts and INDIRECTs back to where a value was produced. A constant the
	 * decompiler typed as a pointer (PTRSUB(0,c)) counts as the constant c.
	 */
	private Varnode through(Varnode v) {
		for (int i = 0; i < 16 && v.getDef() != null; i++) {
			PcodeOp d = v.getDef();
			if (d.getOpcode() == PcodeOp.COPY || d.getOpcode() == PcodeOp.CAST || d.getOpcode() == PcodeOp.INDIRECT) {
				v = d.getInput(0);
			}
			else if (d.getOpcode() == PcodeOp.PTRSUB && isConst(d.getInput(0), 0) && d.getInput(1).isConstant()) {
				v = d.getInput(1);
			}
			else {
				break;
			}
		}
		return v;
	}

	private AddressSpace space(Varnode spaceId) {
		return currentProgram.getAddressFactory().getAddressSpace((int) spaceId.getOffset());
	}

	private Register register(Varnode v) {
		return v.isRegister() ? currentProgram.getLanguage().getRegister(v.getAddress(), v.getSize()) : null;
	}

	private boolean isRegister(Varnode v, String name) {
		Register r = v == null ? null : register(v);
		return r != null && r.getName().equals(name);
	}

	private boolean isConst(Varnode v, long value) {
		return v != null && v.isConstant() && v.getOffset() == value;
	}

	private int countOps(Varnode v, int depth) {
		PcodeOp d = v.getDef();
		if (d == null || depth == 0) {
			return 0;
		}
		int n = 1;
		for (Varnode in : d.getInputs()) {
			n += countOps(in, depth - 1);
		}
		return n;
	}

	/** A compact rendering of the expression tree that defines {@code v}. */
	private String tree(Varnode v, int depth) {
		if (v.isConstant()) {
			return "#0x" + Long.toHexString(v.getOffset());
		}
		Register r = register(v);
		String name = r != null ? r.getName() : v.getAddress().toString();
		PcodeOp d = v.getDef();
		if (d == null || depth == 0) {
			return v.isInput() ? "in:" + name : name;
		}
		StringBuilder s = new StringBuilder(d.getMnemonic()).append('(');
		for (int i = 0; i < d.getNumInputs(); i++) {
			s.append(i == 0 ? "" : ",").append(tree(d.getInput(i), depth - 1));
		}
		return s.append(')').toString();
	}

	private String describe(Object o) {
		if (o instanceof PcodeOp op) {
			return tree(op.getOutput() != null ? op.getOutput() : op.getInput(0), 3);
		}
		if (o instanceof Varnode v) {
			return tree(v, 3);
		}
		if (o instanceof List<?> l) {
			StringJoiner j = new StringJoiner(", ", "[", "]");
			l.forEach(x -> j.add(describe(x)));
			return j.toString();
		}
		return String.valueOf(o);
	}

	private String params(FunctionPrototype proto) {
		StringJoiner j = new StringJoiner(",", "(", ")");
		for (int i = 0; i < proto.getNumParams(); i++) {
			Varnode v = proto.getParam(i).getStorage().getFirstVarnode();
			Register r = v == null ? null : register(v);
			j.add(r != null ? r.getName() : String.valueOf(v));
		}
		return j.toString();
	}

	// --- expectations ---

	private void report(JsonObject expectations, String out) throws Exception {
		int unexpected = 0;
		try (PrintWriter w = new PrintWriter(out)) {
			for (Map.Entry<String, String[]> e : results.entrySet()) {
				String id = e.getKey();
				boolean passed = e.getValue()[0].equals("PASS");
				JsonObject exp = expectations.has(id) ? expectations.getAsJsonObject(id) : null;
				String verdict;
				if (exp == null) {
					verdict = "UNLISTED";
				}
				else if (exp.get("expect").getAsString().equals("xfail")) {
					verdict = passed ? "XPASS" : "XFAIL";
				}
				else {
					verdict = passed ? "PASS" : "FAIL";
				}
				String finding = exp != null && exp.has("finding") ? " [" + exp.get("finding").getAsString() + "]" : "";
				boolean ok = verdict.equals("PASS") || verdict.equals("XFAIL");
				unexpected += ok ? 0 : 1;
				w.printf("%-8s %s%s%s%n", verdict, id, finding,
					e.getValue()[1].isEmpty() ? "" : ": " + e.getValue()[1]);
			}
			for (String id : expectations.keySet()) {
				if (!id.startsWith("_") && !results.containsKey(id)) {
					w.printf("%-8s %s%n", "MISSING", id);
					unexpected++;
				}
			}
			w.printf("RESULT %s (%d checks, %d unexpected)%n", unexpected == 0 ? "ok" : "FAILED", results.size(),
				unexpected);
		}
	}
}
