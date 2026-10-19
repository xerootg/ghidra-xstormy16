#!/usr/bin/env python3
"""Write a byte stream that exercises every possible first instruction word.

Each 16-bit opcode word 0x0000-0xffff is followed by one of several second words, so
4-byte forms see a mix of displacements, immediates and register fields. A linear sweep
over the stream also decodes many of those second words as instructions of their own.
"""
import struct
import sys

SECOND = [0x0000, 0x1234, 0xffff, 0x8001, 0x7ffe, 0x0fff, 0xf000, 0x5a5a, 0xa5a5, 0x0800]

out = bytearray()
for w0 in range(0x10000):
    out += struct.pack("<HH", w0, SECOND[w0 % len(SECOND)])
open(sys.argv[1], "wb").write(out)
