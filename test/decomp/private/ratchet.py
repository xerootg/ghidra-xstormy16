#!/usr/bin/env python3
"""Fails when a lens metric moved the wrong way compared with the committed baseline.

Usage: ratchet.py <baseline.json> <new.json>
Only the metrics listed here are ratcheted; the rest (ABI evidence, totals) are informational.
"""
import json
import sys

LOWER = {
    "image": ["error_bookmarks", "bad_instruction_bookmarks"],
    "decompiler_default": ["decompile_failures", "warnings", "stack_warnings", "halt_baddata",
                           "extraout_vars", "unaff_vars", "flag_input_varnodes",
                           "rxi_input_varnodes", "register_space_accesses"],
}
HIGHER = {
    "image": ["functions", "vectors_found", "vector_handlers"],
    "decompiler_default": ["decompiled", "cbranches_folded"],
}

old, new = (json.load(open(p)) for p in sys.argv[1:3])
worse = []
for rules, better in ((LOWER, lambda a, b: b <= a), (HIGHER, lambda a, b: b >= a)):
    for section, keys in rules.items():
        for key in keys:
            a, b = old.get(section, {}).get(key), new.get(section, {}).get(key)
            if a is None or b is None:
                continue
            mark = "" if better(a, b) else "  WORSE"
            if a != b or mark:
                print(f"{section}.{key}: {a} -> {b}{mark}")
            if mark:
                worse.append(key)
sys.exit(1 if worse else 0)
