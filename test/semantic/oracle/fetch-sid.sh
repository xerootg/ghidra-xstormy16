#!/bin/bash
# Fetches the pinned SID snapshot and extracts what oracle O1 compiles: the CGEN-generated
# xstormy16 semantics and decoder, SID's cgen-ops.h/cgen-types.h, the instruction field
# macros (extract.inc, cut from cgen-engine.h), COPYING.SID and the xstormy16 .cgs tests.
# Nothing from the snapshot is committed; it is GPLv2-or-later (see ../NOTICE).
#   fetch-sid.sh <outdir>      SID_TARBALL=<file> uses a local copy instead of downloading
set -euo pipefail
out=${1:?usage: fetch-sid.sh <outdir>}
URL=https://sourceware.org/pub/sid/snapshots/sid-20180601.tar.bz2
SHA512=c6565c2e36841af350f7e5dd542ab08a19e0c036ac810b5db7dde3134a9fe6ce47a3d3ba9c5f47def85629911759b6e511e51cbdf18668aae8497a6c18482450
cache=${XS16_CACHE:-$HOME/.cache/xs16-semval}
tarball=${SID_TARBALL:-$cache/sid-20180601.tar.bz2}
if [ ! -f "$tarball" ]; then
	mkdir -p "$cache"
	curl -sSfL -o "$tarball.part" "$URL"
	mv "$tarball.part" "$tarball"
fi
echo "$SHA512  $tarball" | sha512sum -c --quiet

cpu=src/sid/component/cgen-cpu
mkdir -p "$out"
tar -xjf "$tarball" -C "$out" --strip-components=1 \
	"$cpu/cgen-ops.h" "$cpu/cgen-types.h" "$cpu/cgen-engine.h" "$cpu/xstormy16" \
	src/sid/COPYING.SID src/sid/component/testsuite/sidcomp.cgen-cpu.xstormy16
gen=$out/gen
mkdir -p "$gen"
for f in cgen-ops.h cgen-types.h; do cp "$out/sid/component/cgen-cpu/$f" "$gen/"; done
x=$out/sid/component/cgen-cpu/xstormy16
for f in xstormy16-sem.cxx xstormy16-decode.cxx xstormy16-decode.h xstormy16-cpu.h \
	xstormy16-desc.h xstormy16-defs.h; do
	cp "$x/$f" "$gen/"
done
: > "$gen/config.h"
mkdir -p "$gen/cgen" && : > "$gen/cgen/bitset.h"
# The EXTRACT_{MSB0,LSB0}_{SINT,UINT} field macros from cgen-engine.h.
awk '/^#define EXTRACT_(MSB0|LSB0)_(SINT|UINT)\(/ { p = 1 } p { print } p && !/\\$/ { p = 0 }' \
	"$out/sid/component/cgen-cpu/cgen-engine.h" > "$gen/extract.inc"
[ "$(grep -c '^#define' "$gen/extract.inc")" = 4 ] || { echo "extract.inc: unexpected cgen-engine.h" >&2; exit 1; }
