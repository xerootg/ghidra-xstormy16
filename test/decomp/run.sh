#!/bin/bash
# Decompiler golden checks: assembles the fixtures into a synthetic lens image, imports it
# with the Sigma loader and full auto-analysis, then runs DecompCheck against
# expectations.json. Needs GHIDRA_INSTALL_DIR, the extension installed as a user
# extension, and xstormy16-elf-{as,ld,objcopy,nm} on PATH (or BINUTILS=<prefix>/bin/xstormy16-elf-).
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
bu=${BINUTILS:-xstormy16-elf-}
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
for s in "$here"/*.S; do
	"${bu}as" -o "$work/$(basename "$s" .S).o" "$s"
done
"${bu}ld" -T "$here/linker.ld" -o "$work/fixtures.elf" "$work"/*.o
"${bu}objcopy" -O binary "$work/fixtures.elf" "$work/fixtures.bin"
"${bu}nm" "$work/fixtures.elf" | awk '$3 ~ /^[td]_/ { print $3, $1 }' > "$work/symbols.txt"
mkdir "$work/proj"
"$GHIDRA_INSTALL_DIR/support/analyzeHeadless" "$work/proj" t -import "$work/fixtures.bin" \
	-loader SigmaFirmwareLoader -scriptPath "$here" \
	-preScript DecompFixtures.java "$work/symbols.txt" \
	-postScript DecompCheck.java "$work/symbols.txt" "$here/expectations.json" "$work/results.txt" \
	> "$work/headless.log" 2>&1 || { tail -40 "$work/headless.log"; exit 1; }
[ -s "$work/results.txt" ] || { grep -iE 'error|exception' "$work/headless.log" | head -40; exit 1; }
cat "$work/results.txt"
grep -q '^RESULT ok' "$work/results.txt"
