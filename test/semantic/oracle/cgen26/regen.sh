#!/bin/bash
# Regenerates the second oracle (O2) from binutils' xstormy16.cpu with upstream CGEN.
# Both inputs are pinned, so the output in gen/ is reproducible; CI reruns this and fails
# on any diff. Needs guile (3.0), git and curl.
#   CGEN_DIR=<checkout>  reuse an existing cgen clone (it is checked out at the pin)
#   CPU_DIR=<dir>        take xstormy16.cpu and simplify.inc from here instead of the
#                        binutils release tarball (BINUTILS_TARBALL=<file> for a local copy)
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
CGEN_COMMIT=360079deda913ae36d1c9c985aa505bf0fd49af0
CPU_SHA256=2679d6a510cc5f442cb737b3479fa602c1080c5ee1073973b7a453ddeb12b07a
INC_SHA256=9bfb778067e4b00627cecd7111c6c491f50865b4d3e50c1cff1e9e35cd3da8dc
BINUTILS=binutils-2.45
BINUTILS_SHA256=c50c0e7f9cb188980e2cc97e4537626b1672441815587f1eab69d2a1bfbef5d2
cache=${XS16_CACHE:-$HOME/.cache/xs16-semval}
mkdir -p "$cache"

cgen=${CGEN_DIR:-$cache/cgen}
if [ ! -d "$cgen/.git" ]; then
	git clone -q https://sourceware.org/git/cgen.git "$cgen"
fi
if ! git -C "$cgen" cat-file -e "$CGEN_COMMIT^{commit}" 2>/dev/null; then
	git -C "$cgen" fetch -q origin
fi
git -C "$cgen" -c advice.detachedHead=false checkout -q "$CGEN_COMMIT"

cpu=${CPU_DIR:-$cache/cpu-$BINUTILS}
if [ ! -f "$cpu/xstormy16.cpu" ] || [ ! -f "$cpu/simplify.inc" ]; then
	tarball=${BINUTILS_TARBALL:-$cache/$BINUTILS.tar.xz}
	if [ ! -f "$tarball" ]; then
		curl -sSfL -o "$tarball.part" "https://ftpmirror.gnu.org/gnu/binutils/$BINUTILS.tar.xz" ||
			curl -sSfL -o "$tarball.part" "https://ftp.gnu.org/gnu/binutils/$BINUTILS.tar.xz"
		mv "$tarball.part" "$tarball"
	fi
	echo "$BINUTILS_SHA256  $tarball" | sha256sum -c --quiet
	mkdir -p "$cpu"
	tar -xJf "$tarball" -C "$cpu" --strip-components=2 "$BINUTILS/cpu/xstormy16.cpu" "$BINUTILS/cpu/simplify.inc"
fi
echo "$CPU_SHA256  $cpu/xstormy16.cpu" | sha256sum -c --quiet
echo "$INC_SHA256  $cpu/simplify.inc" | sha256sum -c --quiet

work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
(cd "$cgen" && guile -l guile.scm -s cgen-sim.scm -s . -f "" -m xstormy16 \
	-a "$cpu/xstormy16.cpu" -i xstormy16 \
	-C "$work/cpu.h" -U "$work/cpu.c" -T "$work/dec.h" -D "$work/dec.c" -S "$work/sem.c" > "$work/log" 2>&1) \
	|| { cat "$work/log"; exit 1; }

# Substitute the placeholders the way gdb's sim/common/cgen.sh does for a cpu family.
for f in cpu.h cpu.c dec.h dec.c sem.c; do
	sed -e 's/@ARCH@/XSTORMY16/g' -e 's/@arch@/xstormy16/g' \
	    -e 's/@CPU@/XSTORMY16/g' -e 's/@cpu@/xstormy16/g' \
	    -e 's/@PREFIX@/XSTORMY16/g' -e 's/@prefix@/xstormy16/g' "$work/$f" > "$here/gen/$f"
done
echo "regenerated $here/gen (cgen $CGEN_COMMIT, $BINUTILS xstormy16.cpu)"
