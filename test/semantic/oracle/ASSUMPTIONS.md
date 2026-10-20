# Oracle assumptions

Both oracles execute CGEN semantics generated from the xstormy16 `.cpu` description:
O1 (`sid`) is the generated code shipped in the SID 2018-06-01 snapshot, O2 (`cgen26`)
is regenerated from binutils 2.45 `cpu/xstormy16.cpu` by CGEN at 360079d. What the
generated code does not define comes from the hand-written hooks listed here. Anything a
hook decides is an assumption: where the slaspec makes the same choice, a passing case
only shows that the two agree, not that either is right.

| | Assumption | O1 source | O2 source |
|---|---|---|---|
| H1 | `parity(v)` is 1 when the 16-bit value has an odd number of set bits (PT = odd parity). | SID's own hook, verbatim (`sid-shim/sid-hooks.inc`) | popcount (`o2-cgen26.c`) |
| H2 | Writes to general registers keep the low 16 bits (`h_gr_set_handler`). | SID's own hook, verbatim | same masking |
| H3 | Memory is one flat little-endian byte bus with 32-bit addresses: near, far, code and stack accesses all reach the same bytes, and nothing wraps at 0xffff. | shared `xs16-bus.h` | shared |
| H4 | C undefined behaviour is not left to the host (see below). | shared `ub-guards.h` | shared |
| H5 | The decoder tries the 32-bit form first and falls back to the 16-bit form when that is invalid or its semantics report a 2-byte length. | SID's generated decoder | `o2-cgen26.c` |

## H3: the flat bus

Unwritten bytes read `xs16_memhash(mseed, addr)` (`xs16-case.h`), and the instruction
words sit at `pc..pc+3`. The SUT implements the same function (`sut/.../CaseIo.java`),
maps `ram:A` and `code:A` both to bus address `A`, and does not mirror or wrap anything.
So the harness models CGEN's memory, not the LC88 memory map or the loader's byte-mapped
blocks; those need a program-backed lane (not part of this tier set). Where CGEN's 32-bit
address sum leaves the 16-bit near space the cases differ by construction; they are
tagged `ADDR_EDGE` and adjudicated (ORC-2, OPEN-2).

## H4: undefined behaviour

`ub-guards.h` replaces CGEN's shift, rotate and divide ops after `cgen-ops.h`:

- Shifts by 32 or more (after C's promotion of HI operands to int) return 0 and set
  `XS16_UB_SHIFT`; the case is tagged `ORACLE_UB`. In practice this is `bn`/`bp Rd,Rs`
  with `Rs >= 32`, which CGEN passes to `(sll 1 Rs)` unmasked.
- Rotates follow gdb's `sim/common/cgen-utils.c`: a count of 0 returns the value
  unchanged (SID's macro form would shift by 32). Counts of 32 or more are flagged.
- Division by zero and `INT_MIN / -1` return 0 and set a flag; the driver turns the case
  into `REF_UNDEFINED`, so only the SUT's behaviour is recorded (it must not throw).
- Every oracle is also built with `-fsanitize=undefined`; a UBSan report or any output
  difference between the `ref` and `ubsan` builds fails the smoke run.

The shift counts used by S2 include 16, 17, 31, 32, 0x8000 and 0xffff for rrc, rlc, shl,
shr, asr, bn, bp, set1 and clr1. Both oracles mask the rotate count to 4 bits inside
`set-psw-rrotate17`/`set-psw-rotate17`, so `rrc Rd,Rs` with `Rs >= 16` agrees with the
slaspec's `n & 0xf`.

## What is compared

CTI attributes come from O1 (O2's generated code does not distinguish conditional from
unconditional branches and reports `*`). The oracles must agree field by field on every
case before the SUT is consulted; any `ORACLE_DISAGREE` fails the run.
