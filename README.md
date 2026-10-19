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

The package is published in [xerootg's package feed](https://xerootg.github.io/):

```sh
sudo pacman -S ghidra-xstormy16
```

The package installs into `/opt/ghidra/Ghidra/Extensions/xstormy16`. A pacman hook
recompiles the SLEIGH spec and updates the extension version whenever `ghidra` or
`ghidra-noprompt` is upgraded. Without that, Ghidra would refuse to load the extension
after an upgrade.

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
| `code` | `0x000000`–`0x007fff` | byte-mapped view of `ram` (what far `movf` accesses see) |
| `ram` | `0x0000`–`0x7eff` | RAM and low memory |
| `ram` | `0x7f00`–`0x7fff` | special function registers (volatile) |
| `ram` | `0x8000`–`0xffff` | byte-mapped view of the first 32 KiB of flash (what near accesses see) |

The update file also carries a header at `0x7fb8`. It holds a `CHIPINFORMATION` block
naming the chip (for example `LC88F58B0`), and it sits on top of the SFR window. The loader
keeps it in an `image_header` overlay and also records the chip and product names under
**Program Information**.

### USB dock images

The dock image is ordinary Cortex-M firmware. It loads as `ARM:LE:32:Cortex` with flash at
`0x0` and SRAM at `0x20000000`. The vector table is typed as pointers and its handlers are
named.

## Modelling notes and limitations

- **Flags:** the condition flags (`Z8 Z16 CY HC OV PT S`) are kept in separate registers so
  the decompiler can follow them. A few instructions read or write `r14` (the PSW)
  directly; those do not see the separate flags.
- **`Rx`:** this is the register named by PSW bits 15:12, which is the destination of the
  most recent flag-setting instruction. It is tracked in `RXI`. The decompiler resolves it
  wherever the preceding instruction is known.
- **Calling conventions:** the default convention, `__sanyo`, comes from Sanyo-compiled
  lens firmware: the first argument and the result are in `r0`, then `r1`–`r3`. A `__gcc`
  convention covers the GCC ABI (`r2`–`r7`, result in `r2`). Stack arguments are not
  modelled, because Ghidra's decompiler cannot take negative stack parameter offsets on a
  stack that grows upwards.
- **Unknown LC88 opcodes:** LC88 parts appear to have a few opcodes that are not in the
  binutils description. For example, `0x0007` is used in a trap stub. They decode as
  invalid instructions.

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

## License

GPL-3.0-or-later. The SLEIGH specification is derived from the CGEN CPU description in
GNU binutils (`cpu/xstormy16.cpu`), which is under GPL-3.0-or-later.
