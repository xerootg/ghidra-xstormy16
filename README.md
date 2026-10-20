# ghidra-xstormy16

A Ghidra processor module for the **Xstormy16** core (Sanyo, now onsemi, LC88 series
microcontrollers), plus a loader for the firmware images that SIGMA Optimization Pro
downloads for Sigma lenses and the USB Dock UD-01.

- Disassembly matches GNU objdump instruction for instruction. CI checks this with a
  differential test: every one of the 65,536 possible opcode words, each paired with a
  varied second word, is decoded by both tools and the results must agree, branch targets
  included. A real lens firmware (124,175 instructions) also matches with no differences.
- P-code semantics support the decompiler: flag computations fold back into ordinary
  comparisons, calls and returns are tracked through the upward-growing stack, and
  special-function-register accesses show up as plain memory reads and writes.
- The Kotlin loader recognises Sigma `EC5_*.bin` (lens, Xstormy16) and `EE2_*.bin`
  (USB dock, ARM Cortex-M) images, both as downloaded and as raw dumps.
  - It undoes the update-file obfuscation: every byte is inverted.
  - It maps flash, RAM and SFRs at their real addresses.
  - It labels the reset and interrupt vectors.

## Install

### Arch Linux

**From [xerootg's package feed](https://xerootg.github.io/)**, built against `ghidra-noprompt`.
It is published in the feed's `[ghidra]` repo, next to `ghidra-noprompt`:

```sh
sudo pacman -S ghidra-ext-xstormy16
```

This installs into `/opt/ghidra-noprompt/Ghidra/Extensions/xstormy16`. The package depends
on exactly the Ghidra release it was built against. The feed builds it in the same run as
each new `ghidra-noprompt` and publishes both together, so `pacman -Syu` upgrades them as a
pair. If the extension does not build against a new Ghidra, the feed holds that Ghidra
back instead of publishing it alone.

**With Arch's own `ghidra` package**, build `packaging/arch/PKGBUILD` (`ghidra-xstormy16`)
with makepkg. It installs into `/opt/ghidra/Ghidra/Extensions/xstormy16`. Instead of pinning
a Ghidra version, it ships a pacman hook. The hook recompiles the SLEIGH spec and updates
the extension version whenever `ghidra` is upgraded, because otherwise Ghidra refuses to
load the extension. It conflicts with `ghidra-noprompt`, which installs elsewhere: switching
to the feed's Ghidra removes this package, and `ghidra-ext-xstormy16` replaces it.

### Anywhere else

1. Download the zip that matches your Ghidra version from the
   [releases](https://github.com/xerootg/ghidra-xstormy16/releases).
2. In Ghidra, open **File → Install Extensions**, click **+**, and select the zip.
3. Restart Ghidra.

## Use

Import a Sigma firmware file and Ghidra picks the **Sigma lens / USB dock firmware**
loader on its own. For any other Xstormy16 binary, import it as *Raw Binary* with the
language `Xstormy16:LE:32:default`.

### Lens images

On disk, file offset equals flash address. The program uses two address spaces:

| space | range | contents |
|---|---|---|
| `code` | `0x008000`–`0x027fff` | 128 KiB program flash; the vector table (a run of `jmpf`) starts at `0x8000` |
| `code` | `0x000000`–`0x007eff` | byte-mapped view of RAM (what far `movf` accesses see) |
| `code` | `0x007f00`–`0x007fff` | byte-mapped view of the SFRs (volatile) |
| `ram` | `0x0000`–`0x7eff` | RAM and low memory |
| `ram` | `0x7f00`–`0x7fff` | special function registers (volatile) |
| `ram` | `0x8000`–`0xffff` | byte-mapped view of the first 32 KiB of flash (what near accesses see) |

The update file also carries a header at `0x7fb8`. It holds a `CHIPINFORMATION` block
naming the chip (for example `LC88F58B0`), and it sits on top of the SFR window. The loader
keeps it in an `image_header` overlay and also records the chip and product names under
**Program Information**.

The *Xstormy16 Far View References* analyzer moves the references of far accesses from the
`code` view onto the `ram` addresses, so near and far accesses to a variable share its xrefs.
The decompiler still names far accesses by their `code` address.

### USB dock images

The dock image is ordinary Cortex-M firmware. It loads as `ARM:LE:32:Cortex` with flash at
`0x0` and SRAM at `0x20000000`. The vector table is typed as pointers and its handlers are
named.

## Modelling notes and limitations

- **Flags:** the condition flags (`Z8 Z16 CY HC OV PT S`) are kept in separate registers so
  the decompiler can follow them. Instructions that read or write `r14` (the PSW) directly,
  including `push`/`pop`, `iret` and the `icall` frame, pack the flags and `Rx` into it before
  the read and unpack them after the write, so the two views stay in step.
- **`Rx`:** this is the register named by PSW bits 15:12, which is the destination of the
  most recent flag-setting instruction. It is tracked in `RXI`. The decompiler resolves it
  wherever the preceding instruction is known.
- **Calling conventions:** see [below](#calling-conventions).
- **Unknown LC88 opcodes:** LC88 parts appear to have a few opcodes that are not in the
  binutils description. For example, `0x0007` is used in a trap stub. They decode as
  invalid instructions.
- **Deliberate differences from the CGEN model:** the semantic tests in
  [`test/semantic`](test/semantic/README.md) compare every instruction with two models built
  from the binutils CGEN description. The remaining differences are intentional and are
  listed in [`adjudications.yaml`](test/semantic/adjudications.yaml):
  - byte loads from low and high memory zero-extend, where CGEN sign-extends (GCC relies on
    `mov.b` zero-extending);
  - near addresses wrap at 16 bits, including stack accesses that cross `0xffff`;
  - `reset` branches to the reset vector, where CGEN treats it as a no-op;
  - division by zero is left undefined, and Ghidra's emulator stops on it.

## Calling conventions

The compiler spec has two prototypes:

- `__gcc` (the default) is the GCC xstormy16 ABI. Arguments go in `r2`–`r7` and the result
  in `r2` (`r2:r3` for 32-bit values, low word in `r2`). `r0`–`r9` may be clobbered by a call,
  `r10`–`r13` are preserved, and `r13` is the frame pointer. Sigma lens firmware follows it:
  across the 262 functions of one lens image, 68 read `r2` on entry against 3 that read
  `r0`, 59 returns leave a value in `r2` against 6 in `r0`, and the registers pushed in
  prologues are `r10`–`r13` (`r8` in one function, `r9` in none). These are aggregate counts
  from [`test/decomp/lens-metrics.json`](test/decomp/lens-metrics.json). GCC can keep a value
  in `r8`/`r9` across a call it knows leaves them alone; the decompiler shows those as
  `extraout_r8`.
- `__interrupt` is for interrupt handlers and the targets of `icall`, `icallf` and `icallr`.
  These push the PSW as well as the return address (6 bytes rather than 4) and return with
  `iret`. The handler takes no arguments, returns nothing and preserves every register.

The *Xstormy16 Interrupt Prototypes* analyzer applies `__interrupt` to every function that
returns only through `iret`. A direct `icallf` then picks it up from its target. An `icall`
or `icallr` whose target is unknown gets a call-site override instead, because the
decompiler cannot tell from the call itself that it pushed 6 bytes. Without either, the
caller's stack is off by 2 after the call.

Stack arguments are not modelled, because Ghidra's decompiler cannot take negative stack
parameter offsets on a stack that grows upwards.

### Upgrading from 1.0.x

Version 1.0.x made `__sanyo` (arguments from `r0`, result in `r0`, `r8`/`r9` preserved) the
default. That convention does not match the lens firmware and is gone. When you reopen
an existing project:

- Functions left at the default convention (shown as `unknown`, which is what
  auto-analysis assigns) switch to `__gcc` on their own.
- Functions explicitly set to `__sanyo` decompile as `__gcc`, with an *Unknown calling
  convention* warning. Their parameter and return types are kept and move to the `__gcc`
  registers; only signatures with custom storage stay where they were. To clear the warning,
  run this in the Python interpreter (PyGhidra):

  ```python
  for f in currentProgram.getFunctionManager().getFunctions(True):
      if f.getCallingConventionName() == "__sanyo":
          f.setCallingConvention("__gcc")
  ```

- Interrupt handlers are not retagged automatically. Run **Analysis → One Shot → Xstormy16
  Interrupt Prototypes** once.

## Build

You need JDK 21 and a Ghidra installation:

```sh
GHIDRA_INSTALL_DIR=/opt/ghidra ./gradlew buildExtension   # -> dist/ghidra_<ver>_..._xstormy16.zip
```

The differential test also needs `xstormy16-elf-objdump`. To get it, build binutils with
`--target=xstormy16-elf`.

```sh
OBJDUMP=xstormy16-elf-objdump GHIDRA_INSTALL_DIR=/opt/ghidra test/run_diff.sh
```

Install the built extension first; `test/run_diff.sh` runs headless Ghidra, which loads
user extensions from `~/.config/ghidra/<version>/Extensions`.

The loader test generates synthetic lens and dock images, imports them headless with the
extension zip from `dist/` (installed into a throwaway Ghidra settings directory) and checks
the memory map, vectors, polarity and references:

```sh
GHIDRA_INSTALL_DIR=/opt/ghidra test/loader/run_loader_test.sh
```

## License

GPL-3.0-or-later. The SLEIGH specification is derived from the CGEN CPU description in
GNU binutils (`cpu/xstormy16.cpu`), which is under GPL-3.0-or-later.
