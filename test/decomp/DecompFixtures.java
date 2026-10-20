// Pre-analysis step for the decompiler golden checks: labels the fixture symbols from the
// linker's symbol list and creates a function at each "t_" one, so auto-analysis treats
// them like functions found in real firmware. Names the loader already gave are kept.
// Usage (headless): -preScript DecompFixtures.java <symbols-file>
// The symbols file holds "<name> <hex address>" lines (from xstormy16-elf-nm).
//@category Xstormy16

import java.nio.file.Files;
import java.nio.file.Path;

import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SourceType;

public class DecompFixtures extends GhidraScript {
	@Override
	protected void run() throws Exception {
		for (String line : Files.readAllLines(Path.of(getScriptArgs()[0]))) {
			String[] f = line.trim().split("\\s+");
			if (f.length != 2) {
				continue;
			}
			Address addr = toAddr(Long.parseLong(f[1], 16));
			currentProgram.getSymbolTable().createLabel(addr, f[0], SourceType.USER_DEFINED);
			if (!f[0].startsWith("t_")) {
				continue;
			}
			new DisassembleCommand(addr, null, true).applyTo(currentProgram, monitor);
			if (getFunctionAt(addr) == null) {
				createFunction(addr, null);
			}
		}
	}
}
