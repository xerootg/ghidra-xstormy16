# Semantic validation

Differential test of the SLEIGH semantics: each case is one instruction from a seeded
state, executed by two reference models generated from CGEN's `xstormy16.cpu` and by
Ghidra's `PcodeEmulator` running this module, and compared field by field.

```
driver gen ──> cases ──> oracle O1 (sid)    ┐ must agree (oracle_agree.py)
                     ├─> oracle O2 (cgen26) ┘
                     └─> sut/XsSemRunner ──> buckets.json ──> tools/gate.py ──> report.md
```

Run it with `test/semantic/run-smoke.sh` after `./gradlew buildExtension`
(GHIDRA_INSTALL_DIR must be set; about 40 s on 8 cores). The extension and runner it
installs go into a Ghidra settings directory under `build/` unless `XDG_CONFIG_HOME` is set;
it refuses to use `~/.config/ghidra` unless `XS16_USER_SETTINGS=1`.

## Pieces

| Path | What |
|---|---|
| `oracle/fetch-sid.sh` | fetches the pinned SID snapshot; O1 is its generated xstormy16 code |
| `oracle/sid-shim/` | replaces SID's framework so the generated code compiles; SID's own hooks verbatim |
| `oracle/cgen26/regen.sh` | regenerates O2 into `cgen26/gen/` (committed; CI checks it is unchanged) |
| `oracle/driver.cxx` | `gen`, `golden`, `run`, `check` modes; UB/divide pre-filter |
| `oracle/ASSUMPTIONS.md` | what the hand-written hooks decide (H1-H5) |
| `sut/` | `XsSemRunner` (Ghidra launchable): emulator per thread, `StateMap`, `Compare` |
| `golden/*.vec` | S0: hand-checked vectors; `findings.vec` has one per confirmed semantic finding |
| `adjudications.yaml` | what every mismatch bucket is; `expected-buckets.json` is the bucket list the gate expects |
| `NOTICE` | third-party code |

## Tiers

| Tier | Cases | Content |
|---|---|---|
| S0 | 18 | golden vectors; the finding vectors carry `xfail=<adjudication>` while their fix is pending |
| S1 | 262,144 | every first word × 4 seeded states: registers from a boundary set or random, psw random (so RXI hits 14 and 15), sp near 0/0xffff, w1 from a structured imm16 set, pc random or a boundary (0x7ffe, 0xfffe, 0x10000, 0x27ffe, 0xfffffe, ...) |
| S2 | 49,456 | macro-lite: add/adc/sub/sbc, cmp via b cc (all 16 conditions), rrc/rlc/shr/shl/asr, bn/bp/set1/clr1 with counts including 16, 17, 31, 32, 0x8000, 0xffff, mul and the four divides over nibble/byte boundary values |

Every case is a pure function of (seed, tier, index). The CI seed is `ci-smoke`; any
other seed skips the expected-bucket comparison but still requires every bucket to be
adjudicated.

The larger X1–X4 tiers (opcode × 256 states, macro sweeps, alias classes, sequences) are
not implemented. `driver gen <tier> <seed> [<shard> <nshards>]` already regenerates any
shard of a tier, so a run can be split across machines once they exist.

## Comparison

Registers r0-r13 and sp; the PSW per bit (Z8, Z16, CY, HC, OV, PT, S, RXI and psw bits
7-11); the raw psw register when r14 is involved (tag `PSW_ALIAS`); the next pc on 24
bits plus bits 31:24 apart; written bytes as an address→value map; SUT reads outside
the oracle's read set; userop events; Ghidra's FlowType against CGEN's CTI attribute.
Each flag byte must be 0 or 1. The SUT's psw register is seeded with its flag and Rx bits
inverted: the slaspec keeps only PSW[11:7] there and packs the rest in before an explicit r14
read, so a read that skips the packing shows up as a mismatch. A bucket key is `INSN|slaspec constructor lines|fields|tags`,
the constructor lines being the root and every subtable constructor of the decoded
instruction (for example `MOVFGRIPREDECGR|262>202|PT,Z16,Z8|`).

The runner re-runs 1% of the cases later on the same emulator, each right after a decoy
case (a nop at the same pc with inverted registers), and 0.1% on a fresh emulator; any
difference fails the gate. The first golden run showed why: Ghidra's instruction decoder
keeps the last decoded block across counter overrides, so a case at the same pc as the
previous one executed the previous instruction. `Sut` disables that cache.

## Current state

With the current slaspec the smoke run has 11,066 mismatching cases in 49 buckets, all
adjudicated, and no confirmed semantic finding or OPEN question is left. The finding
vectors of the fixed ones pass and stay as regression checks: adc-ov-carry and
sbc-ov-borrow (ov-carry-in-or), movf-predec-alias (movf-predec-store-flag-order),
mov-psw-r1 and set1-psw-cy (psw-reg-not-synced-with-flags), callr-sp-target (the former
OPEN-1, decided for CGEN's order). OPEN-2 (stack wrap) became KNOWN-2 and UND-1 (divide by
zero) was decided without a change; their entries say why.

When a fix lands its buckets vanish: the gate then reports the stale FIXED-PENDING entry,
the vanished buckets and the golden vector that now passes, and all three have to be
updated in the same change (`run-smoke.sh --update-expected` rewrites the bucket list).

## Throughput

Single-step, one instruction per case, measured with `semval.sh bench` on S1 (262,144
cases) on an Intel Core Ultra 7 165H laptop, Ghidra 12.1.2, OpenJDK 21:

| | vectors/s |
|---|---|
| SUT, 1 thread | 23,500-26,000 (about 40 µs per case) |
| SUT, 4 threads | 50,100 total, 12,800 per thread |
| SUT, 8 threads | 50,200 total |
| SUT `run` (with comparison and self-test), 1 thread | 19,000 |
| oracle O1 / O2, 1 core | 395,000 / 379,000 |

Four separate one-thread JVMs reach the same 12,000 per process as four threads in one
JVM, so the drop is the laptop (shared turbo budget and memory), not a lock in the
runner. Server cores need their own measurement before sizing X2-X5. The X5 exhaustive
adc/sbc sweep (1.7e10 steps) was gated on 1e5 steps/s per core; at 25,000 it is about
190 core-hours.
