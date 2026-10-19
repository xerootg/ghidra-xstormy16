#!/bin/bash
# Differential test: Ghidra (this module) vs GNU objdump over every opcode word.
# Needs GHIDRA_INSTALL_DIR and an xstormy16-elf-objdump on PATH (or OBJDUMP=...).
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
python3 "$here/gen_corpus.py" "$work/corpus.bin"
"${OBJDUMP:-xstormy16-elf-objdump}" -z -D -b binary -m xstormy16 "$work/corpus.bin" > "$work/objdump.txt"
mkdir "$work/proj"
"$GHIDRA_INSTALL_DIR/support/analyzeHeadless" "$work/proj" t -import "$work/corpus.bin" \
	-loader BinaryLoader -processor Xstormy16:LE:32:default -noanalysis \
	-scriptPath "$here/../ghidra_scripts" -postScript DumpLinearSweep.java "$work/ghidra.txt" \
	> "$work/headless.log" 2>&1 || { tail -40 "$work/headless.log"; exit 1; }
python3 "$here/compare.py" "$work/ghidra.txt" "$work/objdump.txt"
