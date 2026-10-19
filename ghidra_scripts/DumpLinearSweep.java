// Linear-sweep disassembly of the whole program, one "address<TAB>text" line per
// instruction, for diffing against GNU objdump. Undecodable words print as "(bad)" and,
// like objdump's CGEN disassembler, skip 4 bytes so both sweeps stay in step.
// Usage (headless): -postScript DumpLinearSweep.java <output-file>
//@category Xstormy16

import java.io.PrintWriter;

import ghidra.app.script.GhidraScript;
import ghidra.app.util.PseudoDisassembler;
import ghidra.program.model.address.Address;
import ghidra.program.model.lang.InsufficientBytesException;
import ghidra.program.model.lang.UnknownInstructionException;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.mem.MemoryBlock;

public class DumpLinearSweep extends GhidraScript {
	@Override
	protected void run() throws Exception {
		PseudoDisassembler dis = new PseudoDisassembler(currentProgram);
		try (PrintWriter out = new PrintWriter(getScriptArgs()[0])) {
			for (MemoryBlock block : currentProgram.getMemory().getBlocks()) {
				if (!block.isInitialized()) {
					continue;
				}
				Address addr = block.getStart();
				Address end = block.getEnd();
				while (addr.compareTo(end) <= 0) {
					int len;
					String text;
					try {
						Instruction insn = dis.disassemble(addr);
						if (insn == null) {
							text = "(bad)";
							len = 4;
						}
						else {
							text = insn.toString();
							len = insn.getLength();
						}
					}
					catch (InsufficientBytesException | UnknownInstructionException e) {
						text = "(bad)";
						len = 4;
					}
					out.printf("%x\t%s%n", addr.getOffset(), text);
					if (end.subtract(addr) < len) {
						break;
					}
					addr = addr.add(len);
				}
			}
		}
	}
}
