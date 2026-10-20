#!/usr/bin/env python3
"""Checks the LoaderReport.java output for the images gen_images.py writes.
Usage: check.py REPORTDIR HEADLESS_LOG
"""
import os
import re
import sys

failures = []


def expect(cond, image, what):
    if not cond:
        failures.append(f'{image}: {what}')


def load(outdir, image):
    path = os.path.join(outdir, image + '.txt')
    if not os.path.exists(path):
        return None
    r = {'info': {}, 'blocks': {}, 'syms': {}, 'entries': set(), 'refs': [], 'c': []}
    for line in open(path):
        kind, _, rest = line.rstrip('\n').partition(' ')
        if kind == 'INFO':
            k, _, v = rest.partition('=')
            r['info'][k] = v
        elif kind == 'BLOCK':
            name, start, end, *attrs = rest.split()
            r['blocks'][name] = dict(a.split('=', 1) for a in attrs) | {'start': start, 'end': end}
        elif kind == 'SYM':
            name, at = rest.split()
            r['syms'][name] = at
        elif kind == 'ENTRY':
            r['entries'].add(rest)
        elif kind == 'REF':
            r['refs'].append(tuple(rest.split()))
        elif kind == 'C':
            r['c'].append(rest)
        else:
            r[kind] = rest
    return r


def block(r, image, name, start, end, **attrs):
    b = r['blocks'].get(name)
    expect(b is not None, image, f'no block {name}')
    if b is None:
        return
    expect((b['start'], b['end']) == (start, end), image, f'{name} spans {b["start"]}-{b["end"]}, want {start}-{end}')
    for k, v in attrs.items():
        expect(b.get(k) == v, image, f'{name} {k}={b.get(k)}, want {v}')


def vectors(r, image, handlers):
    """handlers: the expected vector-table handler addresses, in order."""
    got = sorted(n for n in r['syms'] if re.fullmatch(r'RESET|VECTOR_\d\d', n))
    want = sorted(['RESET'] + ['VECTOR_%02d' % n for n in range(1, len(handlers))])
    expect(got == want, image, f'vector labels {len(got)}, want {len(want)}')
    for n, target in enumerate(handlers):
        name = 'RESET' if n == 0 else 'VECTOR_%02d' % n
        at = 'code:%08x' % target
        expect(r['syms'].get(name + '_handler') == at, image, f'{name}_handler at {r["syms"].get(name + "_handler")}, want {at}')
        expect(at in r['entries'], image, f'{at} is not an entry point')


def lens_common(r, image, inverted, flash_end):
    expect(r.get('LANG') == 'Xstormy16:LE:32:default', image, 'wrong language')
    expect(r['info'].get('Sigma Image Inverted') == str(inverted).lower(), image, 'wrong polarity')
    expect(r['info'].get('Sigma Chip') == 'TESTCHIP', image, 'chip name')
    block(r, image, 'FLASH', 'code:00008000', 'code:%08x' % (flash_end - 1), init='true', x='true')
    block(r, image, 'NEAR_FLASH', 'ram:8000', 'ram:%04x' % (min(flash_end, 0x10000) - 1), map='code:00008000')
    block(r, image, 'RAM', 'ram:0000', 'ram:7eff', vol='false')
    block(r, image, 'SFR', 'ram:7f00', 'ram:7fff', vol='true')
    block(r, image, 'FAR_RAM', 'code:00000000', 'code:00007eff', vol='false', map='ram:0000')
    block(r, image, 'FAR_SFR', 'code:00007f00', 'code:00007fff', vol='true', map='ram:7f00')
    block(r, image, 'image_header', 'image_header::7f00', 'image_header::7fff', init='true')


def check_lens_full_inv(r, image):
    lens_common(r, image, True, 0x28000)
    expect(r['info'].get('Sigma Product') == '50mm F1.4 DG TEST | Test 000', image, 'product name')
    vectors(r, image, [0x8100, 0x12344, 0x8200, 0x27ffe])
    # Far reads of an SFR and of RAM are referenced in ram, like near ones.
    refs = {(f, t) for f, t, _ in r['refs']}
    for frm, to in [('8108', 'ram:7f10'), ('810a', 'ram:7f10'), ('8112', 'ram:0200'), ('811a', 'ram:7f10')]:
        expect(('code:0000' + frm, to) in refs, image, f'no reference code:{frm} -> {to}')
    stray = [t for _, t, _ in r['refs'] if t.startswith('code:0000') and int(t[5:], 16) < 0x8000]
    expect(not stray, image, f'references left in the far view: {stray}')
    # FAR_SFR is volatile: the two far reads of 0x7f10 stay two reads.
    far_reads = [l for l in r['c'] if re.search(r'code_0+7f10', l)]
    expect(len(far_reads) == 2, image, f'{len(far_reads)} far SFR reads in the decompiled test function, want 2')


def check_lens_raw_tail(r, image):
    lens_common(r, image, False, 0x28000)
    block(r, image, 'IMAGE_TAIL', 'code:00028000', 'code:000287ff', init='true')
    vectors(r, image, [0x8100, 0x8200])  # vector 2 jumps outside flash and ends the table


def check_lens_many_vectors(r, image):
    lens_common(r, image, True, 0xa000)
    vectors(r, image, [0x9800] * 64)


def check_lens_8004(r, image):
    lens_common(r, image, True, 0x8004)
    vectors(r, image, [0x8000])


def check_lens_8007(r, image):
    lens_common(r, image, True, 0x8007)
    vectors(r, image, [0x8000])  # the second jmpf is cut off by the end of the file


def dock_common(r, image, inverted, flash_end, irqs, slots=None):
    """irqs: IRQ handler addresses; slots: number of IRQ vector slots (default len(irqs))."""
    slots = len(irqs) if slots is None else slots
    expect(r.get('LANG') == 'ARM:LE:32:Cortex', image, 'wrong language')
    expect(r['info'].get('Sigma Image Inverted') == str(inverted).lower(), image, 'wrong polarity')
    block(r, image, 'FLASH', '00000000', '%08x' % (flash_end - 1), init='true', x='true')
    block(r, image, 'PERIPHERALS', '40000000', '400fffff', vol='true')
    for name, at in [('Reset', 0x400), ('NMI', 0x402), ('HardFault', 0x404), ('SVCall', 0x406),
                     ('PendSV', 0x408), ('SysTick', 0x40a)] + [('IRQ%d' % n, a) for n, a in enumerate(irqs)]:
        expect(r['syms'].get(name + '_Handler') == '%08x' % at, image, f'{name}_Handler at {r["syms"].get(name + "_Handler")}')
    got = sorted(n for n in r['syms'] if n.startswith('vector_IRQ'))
    expect(got == sorted('vector_IRQ%d' % n for n in range(slots)), image, f'IRQ vectors {got}')
    # Vector slots reference the handler itself, not handler+1 (the Thumb bit).
    for frm, to, _ in r['refs']:
        if int(frm, 16) < 0x40 + 4 * slots and int(to, 16) < 0x20000000:
            expect(int(to, 16) % 2 == 0, image, f'vector {frm} references odd address {to}')


def check_dock_odd_inv(r, image):
    dock_common(r, image, True, 0x11a01, [0x500, 0x502])


def check_dock_raw_trim(r, image):
    dock_common(r, image, False, 0x5000, [0x500], slots=2)  # IRQ1 is an empty (zero) slot


NOT_CLAIMED = ['lens_8000.bin', 'lens_8002.bin', 'random_64k.bin']


def main(outdir, log):
    # analyzeHeadless logs "IMPORTING: <file>" and then "Using Loader: <name>" for each import.
    used = {}
    current = None
    for line in open(log):
        m = re.search(r'IMPORTING: file://\S*/([^/?\s]+)', line)
        if m:
            current = m.group(1)
        elif 'Using Loader:' in line and current:
            used[current] = line.split('Using Loader:')[1].split('(')[0].strip()
    for image in NOT_CLAIMED:
        expect(load(outdir, image) is None and 'Sigma' not in used.get(image, ''), image, 'claimed by the Sigma loader')
    for name, fn in globals().items():
        if name.startswith('check_'):
            image = name[len('check_'):] + '.bin'
            r = load(outdir, image)
            expect(r is not None, image, 'not imported')
            if r is not None:
                expect(r.get('FORMAT') == 'Sigma lens / USB dock firmware', image, 'not loaded by the Sigma loader')
                fn(r, image)
    for f in failures:
        print('FAIL', f)
    checked = len(NOT_CLAIMED) + sum(1 for n in globals() if n.startswith('check_'))
    print(f'{checked} images, {len(failures)} failures')
    sys.exit(1 if failures else 0)


if __name__ == '__main__':
    main(*sys.argv[1:3])
