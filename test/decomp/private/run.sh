#!/bin/bash
# Private lane: imports a real lens image with the Sigma loader and full analysis and
# writes LensMetrics' aggregate counts, then ratchets them against the committed
# test/decomp/lens-metrics.json. The image itself is never copied or committed.
# Usage: run.sh <EC5_*.bin> [output.json]   (needs GHIDRA_INSTALL_DIR and the extension installed)
# The new counts replace the baseline only when the ratchet passes; UPDATE_BASELINE=1 accepts
# a regression on purpose. An explicit output.json elsewhere is always written.
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
image=$(realpath "$1")
committed=$here/../lens-metrics.json
out=${2:-$committed}
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
baseline="$work/baseline.json"
[ -f "$committed" ] && cp "$committed" "$baseline"
mkdir "$work/proj"
"$GHIDRA_INSTALL_DIR/support/analyzeHeadless" "$work/proj" lens -import "$image" \
	-loader SigmaFirmwareLoader -scriptPath "$here" -postScript LensMetrics.java "$work/metrics.json" \
	> "$work/headless.log" 2>&1 || { echo "analyzeHeadless failed" >&2; exit 1; }
[ -s "$work/metrics.json" ] || { echo "LensMetrics wrote nothing" >&2; exit 1; }
status=0
[ -f "$baseline" ] && { python3 "$here/ratchet.py" "$baseline" "$work/metrics.json" || status=$?; }
if [ "$status" -eq 0 ] || [ "${UPDATE_BASELINE:-0}" = 1 ] || [ "$(realpath -m "$out")" != "$(realpath -m "$committed")" ]; then
	cp "$work/metrics.json" "$out"
	[ "${UPDATE_BASELINE:-0}" = 1 ] && status=0
else
	echo "ratchet failed; $out left unchanged (UPDATE_BASELINE=1 to accept)" >&2
fi
exit "$status"
