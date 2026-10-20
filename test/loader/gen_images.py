#!/usr/bin/env python3
"""Writes synthetic Sigma-style firmware images for the loader test.

Everything here is made up: the header carries only the tags the loader looks for
(SigmaImage.kt), and the code is a few hand-encoded instructions.
Usage: gen_images.py OUTDIR
"""
import os
import random
import struct
import sys

FLASH_BASE = 0x8000
FLASH_END = 0x28000
LENS_HEADER = 0x7fc0


def invert(data):
    return bytes(b ^ 0xff for b in data)


# --- Xstormy16 encodings (checked against xstormy16-elf-as) ---
def jmpf(target):
    return bytes([target & 0xff, 0x02, (target >> 8) & 0xff, (target >> 16) & 0xff])


def mov_imm(rd, imm):          # mov Rd,#imm16
    return bytes([0x30 | rd, 0x31]) + struct.pack('<H', imm)


def movf_w_load(rd, rs):       # movf.w Rd,(Rs)
    return bytes([rs << 4 | rd, 0x75])


def mov_w_load(rd, rs):        # mov.w Rd,(Rs)
    return bytes([rs << 4 | rd, 0x71])


def add(rd, rs):               # add Rd,Rs
    return bytes([rs << 4 | rd, 0x49])


RET = bytes([0x03, 0x00])

# Reads one SFR twice through the far view, a RAM word through the far view, and the same
# SFR twice through the near view. r8 is the far-address high word.
FAR_TEST = b''.join([
    mov_imm(8, 0), mov_imm(6, 0x7f10), movf_w_load(2, 6), movf_w_load(3, 6), add(2, 3),
    mov_imm(6, 0x0200), movf_w_load(4, 6), add(2, 4),
    mov_imm(6, 0x7f10), mov_w_load(3, 6), mov_w_load(4, 6), add(2, 3), add(2, 4), RET,
])


def lens(size, vectors, code=(), tail=None):
    """A lens image in true form: erased flash is 0xFF."""
    img = bytearray(b'\xff' * size)
    hdr = b'CHIPINFORMATION\0TESTCHIP\0'
    img[LENS_HEADER:LENS_HEADER + len(hdr)] = hdr
    for n, entry in enumerate(vectors):
        at = FLASH_BASE + 4 * n
        img[at:at + len(entry)] = entry[:size - at]
    for at, blob in code:
        img[at:at + len(blob)] = blob
    if tail is not None:
        img[FLASH_END:FLASH_END + len(tail)] = tail
    if size > 0x9100:
        product = b'50mm F1.4 DG TEST | Test 000\0'
        img[0x9000:0x9000 + len(product)] = product
    return bytes(img)


# --- Thumb encodings ---
THUMB_LOOP = bytes([0xfe, 0xe7])   # b .
THUMB_BX_LR = bytes([0x70, 0x47])  # bx lr


def dock(size, vectors, code=(), fill_end=None):
    """A dock image in true form. Data runs to fill_end (default: the whole file)."""
    img = bytearray(b'\xff' * size)
    end = size if fill_end is None else fill_end
    for at in range(0x400, end - 1, 2):
        img[at:at + 2] = THUMB_BX_LR
    for n, v in enumerate(vectors):
        img[4 * n:4 * n + 4] = struct.pack('<I', v)
    for at, blob in code:
        img[at:at + len(blob)] = blob
    tag = b'SIGMA USB-DOCK\0'
    img[0x300:0x300 + len(tag)] = tag
    if fill_end is None:
        img[size - 1] = 0x5a  # a non-0xFF last byte so nothing is trimmed
    return bytes(img)


def main(out):
    os.makedirs(out, exist_ok=True)

    def write(name, data):
        with open(os.path.join(out, name), 'wb') as f:
            f.write(data)

    # Full-size lens, as downloaded (inverted). Vector 1 jumps above 64 KiB.
    write('lens_full_inv.bin', invert(lens(FLASH_END,
        [jmpf(0x8100), jmpf(0x12344), jmpf(0x8200), jmpf(0x27ffe)],
        code=[(0x8100, FAR_TEST), (0x12344, RET), (0x8200, RET), (0x27ffe, RET)])))
    # Raw dump (not inverted) with data past the 128 KiB flash; the table ends at a jmpf
    # whose target is outside flash.
    write('lens_raw_tail.bin', lens(FLASH_END + 0x800,
        [jmpf(0x8100), jmpf(0x8200), jmpf(0x30000), jmpf(0x8200)],
        code=[(0x8100, RET), (0x8200, RET)], tail=b'TAILDATA'))
    # More than 64 consecutive jmpf: the loader stops at 64.
    write('lens_many_vectors.bin', invert(lens(0xa000, [jmpf(0x9800)] * 80, code=[(0x9800, RET)])))
    # Too small to hold a reset vector: not claimed.
    write('lens_8000.bin', invert(lens(0x8000, [])))
    write('lens_8002.bin', invert(lens(0x8002, [jmpf(0x8000)])))
    # Just one vector, plus a truncated second one.
    write('lens_8004.bin', invert(lens(0x8004, [jmpf(0x8000)])))
    write('lens_8007.bin', invert(lens(0x8007, [jmpf(0x8000), jmpf(0x8000)])))

    sys_vectors = [0x20002000, 0x401, 0x403, 0x405, 0, 0, 0, 0, 0, 0, 0, 0x407, 0, 0, 0x409, 0x40b]
    handlers = [(0x400, THUMB_LOOP)]
    # Odd length, not a multiple of 4 KiB. IRQ0-1 are handlers; IRQ2 points past EOF but
    # inside the 4 KiB page that the length rounds up to, so it ends the table.
    size = 0x11a01
    write('dock_odd_inv.bin', invert(dock(size, sys_vectors + [0x501, 0x503, 0x11c01, 0x601], handlers)))
    # Raw dump with erased flash after 0x4f10: the block is trimmed to 0x5000.
    write('dock_raw_trim.bin', dock(0x10000, sys_vectors + [0x501, 0], handlers, fill_end=0x4f10))

    # 64 KiB of noise is not a Sigma image in either polarity.
    write('random_64k.bin', random.Random(0x5167).randbytes(0x10000))


if __name__ == '__main__':
    main(sys.argv[1])
