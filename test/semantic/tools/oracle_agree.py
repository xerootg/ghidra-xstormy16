#!/usr/bin/env python3
"""N-version check of the two oracles: compares two result files line by line.

O2 (cgen26) cannot tell conditional from unconditional CTIs and reports '*' for both, so
the cti column is compared as CTI / not CTI. Prints a summary per (insn, field) and exits
1 if anything disagrees (an ORACLE_DISAGREE is a harness or generator bug)."""
import collections
import sys

FIELDS = ["status", "insn", "cti", "taken", "npc"] + [f"r{i}" for i in range(16)] + ["ub", "W", "R", "EV"]


def rows(path):
    with open(path) as f:
        for line in f:
            t = line.split()
            yield t[0], dict(zip(FIELDS, t[1:]))


def main():
    a, b = sys.argv[1], sys.argv[2]
    diffs = collections.Counter()
    examples = {}
    n = 0
    for (ta, ra), (tb, rb) in zip(rows(a), rows(b)):
        if ta != tb:
            sys.exit(f"case streams differ: {ta} vs {tb}")
        n += 1
        for f in FIELDS:
            va, vb = ra.get(f), rb.get(f)
            if f == "cti":
                va, vb = va != "-", vb != "-"
            if va != vb:
                key = (ra["insn"], f)
                diffs[key] += 1
                examples.setdefault(key, f"{ta}: {ra.get(f)} vs {rb.get(f)}")
    for (insn, f), c in sorted(diffs.items()):
        print(f"ORACLE_DISAGREE {insn} {f}: {c}  e.g. {examples[(insn, f)]}")
    print(f"oracle agreement: {n} cases, {sum(diffs.values())} field disagreements ({a} vs {b})")
    sys.exit(1 if diffs else 0)


if __name__ == "__main__":
    main()
