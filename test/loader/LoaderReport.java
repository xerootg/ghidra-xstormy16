// Writes what SigmaFirmwareLoader produced for the current program to <outdir>/<name>.txt,
// one fact per line, for check.py.
//@category Test
import java.io.File;
import java.io.PrintWriter;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.framework.options.Options;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Program;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.mem.MemoryBlockSourceInfo;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;

public class LoaderReport extends GhidraScript {
	@Override
	public void run() throws Exception {
		File out = new File(getScriptArgs()[0], currentProgram.getName() + ".txt");
		try (PrintWriter w = new PrintWriter(out)) {
			w.println("FORMAT " + currentProgram.getExecutableFormat());
			w.println("LANG " + currentProgram.getLanguageID());
			Options info = currentProgram.getOptions(Program.PROGRAM_INFO);
			for (String key : info.getOptionNames()) {
				if (key.startsWith("Sigma")) {
					w.println("INFO " + key + "=" + info.getObject(key, null));
				}
			}
			for (MemoryBlock b : currentProgram.getMemory().getBlocks()) {
				String map = "";
				for (MemoryBlockSourceInfo s : b.getSourceInfos()) {
					if (s.getMappedRange().isPresent()) {
						map = " map=" + s.getMappedRange().get().getMinAddress();
					}
				}
				w.println("BLOCK " + b.getName() + " " + b.getStart() + " " + b.getEnd() +
					" init=" + b.isInitialized() + " vol=" + b.isVolatile() + " x=" + b.isExecute() + map);
			}
			for (Symbol s : currentProgram.getSymbolTable().getAllSymbols(false)) {
				if (s.getSource() == SourceType.IMPORTED) {
					w.println("SYM " + s.getName() + " " + s.getAddress());
				}
			}
			AddressIterator entries = currentProgram.getSymbolTable().getExternalEntryPointIterator();
			while (entries.hasNext()) {
				w.println("ENTRY " + entries.next());
			}
			for (Address from : currentProgram.getReferenceManager().getReferenceSourceIterator(
				currentProgram.getMinAddress(), true)) {
				for (Reference r : currentProgram.getReferenceManager().getReferencesFrom(from)) {
					if (r.isMemoryReference()) {
						w.println("REF " + from + " " + r.getToAddress() + " " + r.getReferenceType());
					}
				}
			}
			// Decompile the lens far-access test function, if there is one.
			Symbol handler = getSymbol("RESET_handler", null);
			Function f = handler == null ? null : getFunctionAt(handler.getAddress());
			if (f != null && currentProgram.getLanguageID().toString().startsWith("Xstormy16")) {
				DecompInterface d = new DecompInterface();
				d.openProgram(currentProgram);
				DecompileResults r = d.decompileFunction(f, 60, monitor);
				String c = r.decompileCompleted() ? r.getDecompiledFunction().getC() : "FAILED " + r.getErrorMessage();
				for (String line : c.split("\n")) {
					w.println("C " + line);
				}
				d.dispose();
			}
		}
	}
}
