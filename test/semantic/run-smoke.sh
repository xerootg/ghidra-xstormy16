#!/bin/bash
# Semantic smoke run: builds both oracles, checks them against the golden vectors and
# each other, runs tiers S0-S2 through Ghidra's emulator and applies the gate.
#
#   run-smoke.sh [--seed S] [--threads N] [--work DIR] [--update-expected]
#
# Needs GHIDRA_INSTALL_DIR, a built extension zip in dist/ (./gradlew buildExtension),
# g++, java and python3 with PyYAML. The extension and the runner are installed into a
# Ghidra settings directory under the work directory (XDG_CONFIG_HOME/XDG_CACHE_HOME
# default to <work>/xdg and <work>/xdgcache), never into your own unless asked for.
# With a seed other than ci-smoke the expected-bucket comparison is skipped.
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/../.." && pwd)
seed=ci-smoke
threads=$(nproc)
work=$here/build
gate_opt=
while [ $# -gt 0 ]; do
	case $1 in
	--seed) seed=$2; shift 2 ;;
	--threads) threads=$2; shift 2 ;;
	--work) work=$2; shift 2 ;;
	--update-expected) gate_opt=--update; shift ;;
	*) echo "unknown option $1" >&2; exit 2 ;;
	esac
done
[ "$seed" = ci-smoke ] || gate_opt=${gate_opt:---no-expected}
: "${GHIDRA_INSTALL_DIR:?GHIDRA_INSTALL_DIR is not set}"
mkdir -p "$work"
step() { printf '\n== %s\n' "$*"; }

step "oracles"
make -s -C "$here/oracle" B="$work/oracle" -j"$threads"
O=$work/oracle
for o in sid-ref sid-ubsan cgen26-ref cgen26-ubsan; do
	"$O/$o" check "$here"/golden/*.vec
done

step "cases (seed $seed)"
"$O/sid-ref" golden "$here"/golden/*.vec > "$work/cases.txt"
"$O/sid-ref" gen S1 "$seed" >> "$work/cases.txt"
"$O/sid-ref" gen S2 "$seed" >> "$work/cases.txt"
wc -l < "$work/cases.txt"

step "oracle runs: ref vs UBSan, O1 vs O2"
for o in sid-ref sid-ubsan cgen26-ref cgen26-ubsan; do
	"$O/$o" run < "$work/cases.txt" > "$work/$o.res" 2> "$work/$o.err" &
done
wait
for o in sid cgen26; do
	if [ -s "$work/$o-ubsan.err" ]; then
		echo "ORACLE_UB: UBSan reported in $o:" >&2
		head "$work/$o-ubsan.err" >&2
		exit 1
	fi
	cmp "$work/$o-ref.res" "$work/$o-ubsan.res" || { echo "ORACLE_UB: $o ref and UBSan builds differ" >&2; exit 1; }
done
python3 "$here/tools/oracle_agree.py" "$work/sid-ref.res" "$work/cgen26-ref.res"

step "SUT"
"$here/sut/build.sh" "$work/sut"
export XDG_CONFIG_HOME=${XDG_CONFIG_HOME:-$work/xdg} XDG_CACHE_HOME=${XDG_CACHE_HOME:-$work/xdgcache}
settings=$("$here/sut/settings-dir.sh")
zip=$(ls "$root"/dist/*.zip | head -1)
rm -rf "$settings/Extensions/xstormy16"
mkdir -p "$settings/Extensions"
unzip -q "$zip" -d "$settings/Extensions"
SEMVAL_JAR=$work/sut/semval.jar "$here/sut/semval.sh" run --cases "$work/cases.txt" \
	--oracle "$work/sid-ref.res" --out "$work/report" --threads "$threads" 2>&1 | grep -v '^INFO '

step "gate"
python3 "$here/tools/gate.py" "$work/report/buckets.json" $gate_opt
