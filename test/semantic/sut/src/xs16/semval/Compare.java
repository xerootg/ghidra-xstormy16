package xs16.semval;

import java.util.*;

import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.FlowType;

/**
 * Compares one SUT result with the oracle's and names the mismatching fields and tags.
 * A case's bucket key is (cgen insn, SLEIGH constructor lines, sorted fields, sorted tags).
 * Under PSW_ALIAS the PSW sub-fields are folded into one "PSW*" field: which flag bits
 * differ there depends on the random state, not on the defect.
 */
final class Compare {
	static final Set<String> PSW_PARTS =
		Set.of("Z8", "Z16", "CY", "HC", "OV", "PT", "S", "RXI", "PSWHI", "psw_raw");

	/** Register and flag fields; under ADDR_EDGE they follow from the address and fold into "VAL*". */
	static final Set<String> VALUE_PARTS = new HashSet<>(PSW_PARTS);
	static {
		VALUE_PARTS.addAll(List.of(Sut.GR));
	}

	/** Mismatched field name -> "oracle/sut" values, sorted by field. */
	final TreeMap<String, String> fields = new TreeMap<>();
	final TreeSet<String> tags = new TreeSet<>();
	String ctor = "-";

	boolean pass() {
		return fields.isEmpty();
	}

	String bucketKey(String insn) {
		TreeSet<String> f = new TreeSet<>();
		boolean alias = tags.contains("PSW_ALIAS"), edge = tags.contains("ADDR_EDGE");
		for (String k : fields.keySet()) {
			f.add(edge && VALUE_PARTS.contains(k) ? "VAL*" : alias && PSW_PARTS.contains(k) ? "PSW*" : k);
		}
		return insn + "|" + ctor + "|" + String.join(",", f) + "|" + String.join(",", tags);
	}

	String detail() {
		StringBuilder sb = new StringBuilder();
		fields.forEach((k, v) -> sb.append(sb.length() > 0 ? " " : "").append(k).append('=').append(v));
		return sb.toString();
	}

	private void diff(String f, long oracle, long sut) {
		if (oracle != sut) {
			fields.put(f, Long.toHexString(oracle) + "/" + Long.toHexString(sut));
		}
	}

	static Compare of(CaseIo.Case c, CaseIo.OracleResult o, Sut.Result s) {
		Compare d = new Compare();
		d.ctor = Sut.ctorChain(s.insn);
		boolean sutOk = s.status.equals("OK");
		switch (o.status) {
			case "INVALID":
				if (!s.status.equals("INVALID")) {
					d.fields.put("decode", "invalid/" + s.status);
				}
				return d;
			case "UNDEF":
				// No reference value; the SUT only has to complete without throwing.
				d.tags.add("REF_UNDEFINED");
				if (!sutOk) {
					d.fields.put("sut_exc", s.status + " " + s.error);
				}
				return d;
			default:
				break;
		}
		if (s.status.equals("INVALID")) {
			d.fields.put("decode", "ok/invalid");
			return d;
		}
		if (!sutOk) {
			d.fields.put("sut_exc", s.status + " " + s.error);
			if (String.valueOf(s.error).contains("exceeds address space")) {
				d.tags.add("ADDR_EDGE");
			}
			return d;
		}
		if (o.ub != 0) {
			d.tags.add("ORACLE_UB");
		}
		Instruction insn = s.insn;
		int preRxi = (c.r[14] >> 12) & 0xf;
		boolean usesRx = insn != null && insn.toString().contains("Rx");
		boolean pswOperand = false, spOperand = false;
		if (insn != null) {
			for (int i = 0; i < insn.getNumOperands(); i++) {
				for (Object x : insn.getOpObjects(i)) {
					if (x instanceof Register r) {
						pswOperand |= r.getName().equals("psw");
						spOperand |= r.getName().equals("sp");
					}
				}
			}
		}
		boolean strict = pswOperand || (usesRx && preRxi == 14) || o.insn.equals("IRET") ||
			o.insn.startsWith("ICALL");
		if (strict) {
			d.tags.add("PSW_ALIAS");
		}
		if (spOperand || (usesRx && preRxi == 15)) {
			d.tags.add("SP_ALIAS");
		}

		for (int i = 0; i < 16; i++) {
			if (i != 14) {
				d.diff(Sut.GR[i], o.r[i], s.r[i]);
			}
		}
		int op = o.r[14];
		for (int i = 0; i < 7; i++) {
			if (s.flags[i] > 1) {
				d.fields.put("flagbyte_" + StateMap.PSW_FIELDS[i], Integer.toHexString(s.flags[i]));
			}
			d.diff(StateMap.PSW_FIELDS[i], (op >> i) & 1, s.flags[i] & 1);
		}
		d.diff("RXI", (op >> 12) & 0xf, s.rxi);
		d.diff("PSWHI", op & StateMap.PSW_HI, s.r[14] & StateMap.PSW_HI);
		if (strict) {
			d.diff("psw_raw", op, s.r[14]);
		}
		d.diff("npc", o.npc & 0xffffff, s.npc & 0xffffff);
		d.diff("npc_hi", o.npc >>> 24, s.npc >>> 24 & 0xff);

		if (!o.writes.keySet().equals(s.writes.keySet())) {
			d.fields.put("mem_addr", keys(o.writes) + "/" + keys(s.writes));
		}
		else if (!o.writes.equals(s.writes)) {
			d.fields.put("mem_val", o.writes + "/" + s.writes);
		}
		for (long a : s.reads) {
			if (!o.reads.contains(a)) {
				d.fields.put("read_extra", Long.toHexString(a));
				break;
			}
		}
		if (!o.events.equals(s.events)) {
			d.fields.put("events", o.events + "/" + s.events);
		}
		String flow = flowCheck(o, insn);
		if (flow != null) {
			d.fields.put("flow", flow);
		}
		boolean edge = s.ramWrap;
		if (s.ramTouched) {
			for (long a : o.reads) {
				edge |= a > 0xffff;
			}
			for (long a : o.writes.keySet()) {
				edge |= a > 0xffff;
			}
		}
		if (edge) {
			d.tags.add("ADDR_EDGE");
		}
		return d;
	}

	private static String keys(Map<Long, Integer> m) {
		StringBuilder sb = new StringBuilder();
		for (long a : m.keySet()) {
			sb.append(sb.length() > 0 ? "," : "").append(Long.toHexString(a));
		}
		return "[" + sb + "]";
	}

	/** Ghidra's FlowType against CGEN's CTI attribute (O1) and the dni name. */
	private static String flowCheck(CaseIo.OracleResult o, Instruction insn) {
		if (insn == null) {
			return null;
		}
		FlowType ft = insn.getFlowType();
		boolean ok;
		String want;
		if (o.insn.startsWith("CALL") || o.insn.startsWith("ICALL")) {
			want = "call";
			ok = ft.isCall();
		}
		else if (o.insn.equals("RET") || o.insn.equals("IRET")) {
			want = "terminal";
			ok = ft.isTerminal();
		}
		else if (o.cti == 'C') {
			want = "cond-jump";
			ok = ft.isJump() && ft.isConditional();
		}
		else if (o.cti == 'U' || o.cti == '*') {
			want = "jump";
			ok = ft.isJump();
		}
		else {
			want = "fallthrough";
			ok = !ft.isJump() && !ft.isCall() && !ft.isTerminal() && ft.hasFallthrough();
		}
		return ok ? null : want + "/" + ft;
	}
}
