#!/usr/bin/env python3
"""find-byte-identical-clones.py — scan all USOs for byte-identical functions
that appear in 2+ segments. Highlights mass-mirror opportunities where
already-wrapped functions in one USO can be directly mirrored to identical
unmatched siblings in other USOs.

Per `feedback_uso_byte_identical_clones_beyond_accessors.md` — 1080's USOs
share constructor/utility functions byte-identical because they all link
the same internal libgdl. A wrap that works in eddproc_uso applies
verbatim to h2hproc_uso, arcproc_uso, etc.

Usage:
    python3 scripts/find-byte-identical-clones.py [--min-size 0x40] [--max-size 0x100]

Output: groups of 2+ byte-identical functions, annotated with each member's
state (plain INCLUDE_ASM = unmatched, wrapped = NM partial, matched = exact
C body). Look for groups where 1+ is wrapped/matched and 1+ is plain — those
are immediate mass-mirror candidates.
"""
import os, hashlib, sys, argparse

USO_SEGMENTS = [
    'arcproc_uso', 'boarder1_uso', 'boarder2_uso', 'boarder3_uso',
    'boarder4_uso', 'boarder5_uso', 'eddproc_uso', 'gui_uso',
    'h2hproc_uso', 'n64proc_uso', 'titproc_uso',
    'timproc_uso_b1', 'timproc_uso_b3', 'timproc_uso_b5',
]


def get_state(seg, nm):
    """Classify function as 'plain' (INCLUDE_ASM only), 'wrapped' (in
    #ifdef NON_MATCHING), or 'matched' (clean C body, no INCLUDE_ASM).
    """
    seg_dir = f'src/{seg}'
    if not os.path.isdir(seg_dir):
        return 'unknown'
    for cf in os.listdir(seg_dir):
        if not cf.endswith('.c'):
            continue
        try:
            src = open(f'{seg_dir}/{cf}').read()
        except OSError:
            continue
        in_nm = False
        for line in src.split('\n'):
            s = line.strip()
            if s.startswith('#ifdef NON_MATCHING'):
                in_nm = True
            elif s.startswith('#endif'):
                in_nm = False
            if 'INCLUDE_ASM(' in line and nm in line:
                return 'wrapped' if in_nm else 'plain'
        # Check for clean C body (no INCLUDE_ASM at all)
        if any(f'{ret} {nm}(' in src for ret in
               ('void', 'int', 'float', 'char', 'void *', 'int *')):
            return 'matched'
    return 'unknown'


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--min-size', type=lambda x: int(x, 0), default=0x40,
                    help='minimum function size in bytes (default 0x40)')
    ap.add_argument('--max-size', type=lambda x: int(x, 0), default=0x100,
                    help='maximum function size in bytes (default 0x100)')
    args = ap.parse_args()

    sigs = {}
    for seg in USO_SEGMENTS:
        asm_dir = f'asm/nonmatchings/{seg}/{seg}'
        if not os.path.isdir(asm_dir):
            continue
        for f in os.listdir(asm_dir):
            if not f.endswith('.s'):
                continue
            with open(f'{asm_dir}/{f}') as fd:
                content = fd.read()
            first = content.split('\n')[0]
            if 'nonmatching' not in first:
                continue
            sz = first.split()[-1]
            sz_int = int(sz, 16)
            if sz_int < args.min_size or sz_int > args.max_size:
                continue
            words = []
            for line in content.split('\n'):
                if '.word' in line:
                    w = line.split('.word')[1].strip()
                    words.append(w)
            if not words:
                continue
            sig = ','.join(words)
            h = hashlib.md5(sig.encode()).hexdigest()[:10]
            sigs.setdefault(h, []).append((seg, f[:-2], sz))

    interesting = 0
    for h, grp in sigs.items():
        if len(grp) < 2:
            continue
        states = [(seg, nm, sz, get_state(seg, nm)) for seg, nm, sz in grp]
        ss = [s[3] for s in states]
        if 'plain' not in ss:
            continue  # nothing to mirror to
        # Show groups with mass-mirror potential: at least 1 wrapped/matched + 1 plain
        any_done = any(s in ('wrapped', 'matched') for s in ss)
        plains = sum(1 for s in ss if s == 'plain')
        if any_done or plains >= 3:
            interesting += 1
            print(f'sig={h} size={grp[0][2]} count={len(grp)}')
            for seg, nm, sz, st in states:
                print(f'  {seg:18s} {nm:42s} [{st}]')
            print()

    if interesting == 0:
        print('No mass-mirror clone groups found in size range '
              f'[{args.min_size:#x}, {args.max_size:#x}].',
              file=sys.stderr)


if __name__ == '__main__':
    main()
