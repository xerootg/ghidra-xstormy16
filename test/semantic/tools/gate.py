#!/usr/bin/env python3
"""Semantic smoke gate: checks a runner report (buckets.json) against the adjudications,
the expected bucket list and the golden vectors' xfail markers.

  gate.py <buckets.json> [--update | --no-expected]
    --update       rewrite expected-buckets.json from this run instead of comparing
    --no-expected  skip the expected-bucket comparison (runs with a seed other than ci-smoke)

Fails on: an unadjudicated bucket; a bucket that is new or has vanished compared with
expected-buckets.json; a stale FIXED-PENDING adjudication (its fix has landed); a golden
vector that passes while marked xfail or fails without one; a reset self-test
difference; a SLEIGH constructor no case reached. Writes report.md next to buckets.json.
"""
import json
import os
import re
import sys

import yaml

HERE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def load_golden():
    """tag -> (xfail id or None, finding or None) from golden/*.vec"""
    out = {}
    gdir = os.path.join(HERE, "golden")
    for name in sorted(os.listdir(gdir)):
        if not name.endswith(".vec"):
            continue
        for line in open(os.path.join(gdir, name)):
            line = line.split("#", 1)[0].strip()
            if not line:
                continue
            tag = "S0:" + line.split()[0]
            kv = dict(t.split("=", 1) for t in line.replace(";", " ").split()[1:] if "=" in t)
            out[tag] = (kv.get("xfail"), kv.get("finding"))
    return out


def adjudicate(key, adj):
    insn, _ctor, fields, tags = key.split("|")
    for a in adj:
        if all(re.search(a.get(k) or "", v) for k, v in (("insn", insn), ("fields", fields), ("tags", tags))):
            return a["id"]
    return None


def main():
    report_path = sys.argv[1]
    update = "--update" in sys.argv[2:]
    compare = not update and "--no-expected" not in sys.argv[2:]
    rep = json.load(open(report_path))
    adj = yaml.safe_load(open(os.path.join(HERE, "adjudications.yaml")))
    exp_path = os.path.join(HERE, "expected-buckets.json")
    stats, buckets = rep["stats"], rep["buckets"]
    errors = []

    verdict = {k: adjudicate(k, adj) for k in buckets}
    for k, v in verdict.items():
        if v is None:
            errors.append(f"UNADJUDICATED bucket {k} ({buckets[k]['count']} cases, e.g. {buckets[k]['exemplars'][0]})")
    for a in adj:
        if a["kind"] == "FIXED-PENDING" and a["id"] not in verdict.values():
            errors.append(f"STALE adjudication {a['id']} ({a.get('finding')}): no bucket left, remove it with the fix")

    current = {k: {"adjudication": verdict[k], "count": buckets[k]["count"]} for k in sorted(buckets)}
    if update:
        with open(exp_path, "w") as f:
            json.dump({"buckets": current}, f, indent=1, sort_keys=True)
            f.write("\n")
        print(f"wrote {exp_path} ({len(current)} buckets)")
    elif compare:
        expected = json.load(open(exp_path))["buckets"]
        for k in sorted(set(current) - set(expected)):
            errors.append(f"NEW bucket {k} ({current[k]['count']} cases, e.g. {buckets[k]['exemplars'][0]})")
        for k in sorted(set(expected) - set(current)):
            errors.append(f"VANISHED bucket {k} (adjudication {expected[k]['adjudication']})")

    for tag, (xfail, finding) in sorted(load_golden().items()):
        got = rep["golden"].get(tag)
        if got is None:
            errors.append(f"GOLDEN {tag} was not run")
        elif xfail and got == "pass":
            errors.append(f"GOLDEN {tag} passes but is marked xfail={xfail} ({finding}): remove the xfail")
        elif xfail and verdict.get(got) != xfail:
            errors.append(f"GOLDEN {tag} fails in {got}, not under its xfail {xfail}")
        elif not xfail and got != "pass":
            errors.append(f"GOLDEN {tag} fails: {got}")

    diffs = stats["selftest_rerun_diffs"] + stats["selftest_fresh_diffs"]
    if diffs:
        errors.append(f"RESET self-test: {diffs} cases gave a different result on re-run: {rep['selftest_diffs'][:5]}")
    if stats["ctors_unhit"]:
        errors.append(f"COVERAGE: SLEIGH constructors never reached (slaspec lines): {stats['ctors_unhit']}")

    write_report(os.path.join(os.path.dirname(report_path), "report.md"), rep, verdict, adj, errors)
    for e in errors:
        print("gate:", e)
    print(f"gate: {stats['cases']} cases, {stats['mismatch']} mismatching in {len(buckets)} buckets, "
          f"{len(errors)} problems")
    sys.exit(1 if errors and not update else 0)


def write_report(path, rep, verdict, adj, errors):
    stats, buckets = rep["stats"], rep["buckets"]
    kinds = {a["id"]: a for a in adj}
    per = {}
    for k, b in buckets.items():
        per.setdefault(verdict[k], []).append((b["count"], k))
    lines = ["# xstormy16 semantic smoke", "",
             f"{stats['cases']} cases, {stats['pass']} pass, {stats['mismatch']} mismatching in "
             f"{len(buckets)} buckets. Reset self-test: {stats['selftest_reruns']} re-runs, "
             f"{stats['selftest_fresh']} fresh-emulator runs, "
             f"{stats['selftest_rerun_diffs'] + stats['selftest_fresh_diffs']} differences. "
             f"{stats['ctors']} SLEIGH constructors, {len(stats['ctors_unhit'])} never reached.", ""]
    if errors:
        lines += ["## Gate problems", ""] + [f"- {e}" for e in errors] + [""]
    lines += ["## By adjudication", "", "| id | kind | finding | buckets | cases |", "|---|---|---|---|---|"]
    for aid, items in sorted(per.items(), key=lambda x: -sum(c for c, _ in x[1])):
        a = kinds.get(aid, {})
        lines.append(f"| {aid} | {a.get('kind', '-')} | {a.get('finding', '')} | {len(items)} | "
                     f"{sum(c for c, _ in items)} |")
    lines += ["", "## Top buckets", "", "| cases | bucket | slaspec | adjudication | example |",
              "|---|---|---|---|---|"]
    top = sorted(buckets.items(), key=lambda kv: -kv[1]["count"])[:10]
    for k, b in top:
        lines.append(f"| {b['count']} | `{k}` | {b['ctor_src']} | {verdict[k]} | `{b['exemplars'][0]}` |")
    with open(path, "w") as f:
        f.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
