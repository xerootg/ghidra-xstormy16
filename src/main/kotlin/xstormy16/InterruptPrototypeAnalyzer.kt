package xstormy16

import ghidra.app.services.AbstractAnalyzer
import ghidra.app.services.AnalysisPriority
import ghidra.app.services.AnalyzerType
import ghidra.app.util.importer.MessageLog
import ghidra.program.model.address.Address
import ghidra.program.model.address.AddressSetView
import ghidra.program.model.data.FunctionDefinitionDataType
import ghidra.program.model.data.VoidDataType
import ghidra.program.model.listing.Function
import ghidra.program.model.listing.Program
import ghidra.program.model.pcode.HighFunctionDBUtil
import ghidra.program.model.symbol.SourceType
import ghidra.program.model.symbol.SymbolType
import ghidra.util.task.TaskMonitor

/**
 * Gives interrupt-style routines the `__interrupt` prototype.
 *
 * Hardware interrupts and icall/icallf/icallr push 6 bytes (return address and PSW) and the
 * handler returns with iret, while ordinary calls push 4. The decompiler takes that stack
 * adjustment from the callee's prototype, so:
 *  - a function that returns only through iret gets `__interrupt`, which fixes its own body
 *    and every direct icallf/icall that reaches it;
 *  - an icall whose target is not a known function gets a call-site override with
 *    `__interrupt`, so the caller's stack stays balanced after it.
 */
class InterruptPrototypeAnalyzer : AbstractAnalyzer(NAME, DESCRIPTION, AnalyzerType.FUNCTION_ANALYZER) {

    init {
        // Before the stack and decompiler-based analyzers, which depend on the prototype.
        setPriority(AnalysisPriority.FUNCTION_ANALYSIS.before())
        setDefaultEnablement(true)
        setSupportsOneTimeAnalysis()
    }

    override fun canAnalyze(program: Program): Boolean =
        program.language.processor.toString() == "Xstormy16" &&
            program.compilerSpec.getCallingConvention(INTERRUPT) != null

    override fun added(program: Program, set: AddressSetView, monitor: TaskMonitor, log: MessageLog): Boolean {
        val functions = program.functionManager
        val listing = program.listing
        for (function in functions.getFunctions(set, true)) {
            monitor.checkCancelled()
            if (function.isThunk || function.isExternal) continue
            var iret = false
            var ret = false
            for (instruction in listing.getInstructions(function.body, true)) {
                when (instruction.mnemonicString.lowercase()) {
                    "iret" -> iret = true
                    "ret" -> ret = true
                    "icall", "icallr", "icallf" -> {
                        val callees = instruction.flows.mapNotNull { functions.getFunctionAt(it) }
                        if (callees.isEmpty()) overrideCallSite(function, instruction.address, log)
                    }
                }
            }
            if (iret && !ret && function.callingConventionName != INTERRUPT &&
                function.signatureSource != SourceType.USER_DEFINED) {
                function.setCallingConvention(INTERRUPT)
            }
        }
        return true
    }

    private fun overrideCallSite(function: Function, at: Address, log: MessageLog) {
        val existing = function.program.symbolTable.getSymbols(at)
            .any { it.symbolType == SymbolType.LABEL && HighFunctionDBUtil.readOverride(it) != null }
        if (existing) return
        try {
            val signature = FunctionDefinitionDataType("icall_target", function.program.dataTypeManager).apply {
                returnType = VoidDataType.dataType
                setCallingConvention(INTERRUPT)
            }
            HighFunctionDBUtil.writeOverride(function, at, signature)
        } catch (e: Exception) {
            log.appendMsg("Could not mark the icall at $at as an interrupt call: ${e.message}")
        }
    }

    companion object {
        const val NAME = "Xstormy16 Interrupt Prototypes"
        const val DESCRIPTION = "Applies the __interrupt prototype (6-byte frame, returns with iret) " +
            "to functions that return through iret and to icall sites with unknown targets."
        const val INTERRUPT = "__interrupt"
    }
}
