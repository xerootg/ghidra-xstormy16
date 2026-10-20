#!/bin/bash
# Loader test: imports synthetic Sigma images with SigmaFirmwareLoader in analyzeHeadless and
# checks the resulting programs. Needs GHIDRA_INSTALL_DIR and a built extension zip in dist/
# (or EXT_ZIP=...). Ghidra user state goes to a throwaway directory, so the extension is
# installed only for this run.
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
zip=${EXT_ZIP:-$(ls -t "$here"/../../dist/*.zip | head -1)}
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT

props="$GHIDRA_INSTALL_DIR/Ghidra/application.properties"
ver=$(sed -n 's/^application.version=//p' "$props")
rel=$(sed -n 's/^application.release.name=//p' "$props")
# With XDG_CONFIG_HOME set, Ghidra keeps its settings in $XDG_CONFIG_HOME/<user>-ghidra.
export XDG_CONFIG_HOME="$work/config" XDG_CACHE_HOME="$work/cache"
ext="$XDG_CONFIG_HOME/$(id -un)-ghidra/ghidra_${ver}_${rel}/Extensions"
mkdir -p "$ext"
unzip -q "$zip" -d "$ext"

python3 "$here/gen_images.py" "$work/img"
mkdir "$work/proj" "$work/out"
# Images the Sigma loader rejects fail to import (no other loader takes them without a
# language), so a nonzero exit here is expected; check.py decides.
"$GHIDRA_INSTALL_DIR/support/analyzeHeadless" "$work/proj" t -import "$work/img" -recursive \
	-scriptPath "$here" -postScript LoaderReport.java "$work/out" > "$work/headless.log" 2>&1 || true
grep -A5 "Exception" "$work/headless.log" || true
python3 "$here/check.py" "$work/out" "$work/headless.log"
