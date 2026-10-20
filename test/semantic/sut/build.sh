#!/bin/bash
# Compiles the SUT runner against the Ghidra installation at GHIDRA_INSTALL_DIR.
#   build.sh [<outdir>]   -> <outdir>/semval.jar (default: build/)
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
out=${1:-$here/build}
: "${GHIDRA_INSTALL_DIR:?GHIDRA_INSTALL_DIR is not set}"
cp=$(find "$GHIDRA_INSTALL_DIR/Ghidra/Framework" "$GHIDRA_INSTALL_DIR/Ghidra/Features/Base" \
	-path '*/lib/*.jar' ! -name '*-src.zip' | sort | tr '\n' ':')
rm -rf "$out/classes"
mkdir -p "$out/classes"
javac -nowarn --release 21 -cp "$cp" -d "$out/classes" $(find "$here/src" -name '*.java')
jar --create --file "$out/semval.jar" -C "$out/classes" .
