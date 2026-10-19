#!/usr/bin/env python3
"""Compare a Ghidra linear sweep (DumpLinearSweep.java) with GNU objdump -D output.

Both sides are normalised to the same textual form; the script prints the first
mismatches, a per-mnemonic summary, and exits non-zero if anything differs.
"""
import collections
import re
import sys

HEX = re.compile(r"0x0*([0-9a-f]+)")


def norm(text):
    t = text.strip().lower()
    t = re.sub(r"\s+", " ", t)
    t = re.sub(r"\bpsw\b", "r14", t)
    t = re.sub(r"\bsp\b", "r15", t)
    t = HEX.sub(lambda m: "0x" + m.group(1), t)
    # Displacements: objdump prints them in signed decimal, Ghidra in hex.
    t = re.sub(r",(-?)(0x[0-9a-f]+|\d+)\)",lambda m: ",%s%d)" % (m.group(1), int(m.group(2), 0)), t)
    t = t.replace(", ", ",")
    return t


def load_objdump(path):
    insns = {}
    for line in open(path):
        m = re.match(r"\s*([0-9a-f]+):\t(?:[0-9a-f]{2} )+\s*\t(.*)$", line)
        if not m:
            continue
        text = m.group(2)
        if text == "*unknown*" or text.startswith(".word") or text.startswith(".byte") or text == "--unused--":
            text = "(bad)" if text != "--unused--" else "syscall"
        insns[int(m.group(1), 16)] = norm(text)
    return insns


def load_ghidra(path):
    insns = {}
    for line in open(path):
        addr, text = line.rstrip("\n").split("\t", 1)
        insns[int(addr, 16)] = norm(text)
    return insns


def main():
    ghidra = load_ghidra(sys.argv[1])
    objdump = load_objdump(sys.argv[2])
    shown = 0
    bad = collections.Counter()
    for addr in sorted(set(ghidra) | set(objdump)):
        g, o = ghidra.get(addr), objdump.get(addr)
        if g == o:
            continue
        key = (o or "<none>").split(" ")[0]
        bad[key] += 1
        if shown < 40:
            print(f"{addr:06x}  objdump: {o!s:40} ghidra: {g}")
            shown += 1
    total = len(objdump)
    print(f"\n{sum(bad.values())} mismatches out of {total} objdump instructions")
    for k, v in bad.most_common(30):
        print(f"  {v:6} {k}")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
