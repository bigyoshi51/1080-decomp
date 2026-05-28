#!/usr/bin/env python3
"""Find splat MIS-SPLIT functions: one real function that splat's jr-ra
heuristic cut into multiple .s pieces because of an internal early-return
`jr ra`. A later branch (beq/bne/beql/bnel/...) jumps OVER that early return
into the rest of the body, so the pieces look like separate functions — and
each often gets independently mislabeled as a cap ("leaf-branch-past-end" for
the head, "caller-set-$vN" / coincidental empty `void f(void){}` for the tail,
because the tail reads a register the head set). They are ONE function: merge
the .s pieces and decompile as a unit. See docs/MATCHING_WORKFLOW.md
#feedback-adjacent-branchpastend-callerset-cap-pair-is-misplit and
#feedback-branch-past-end-unshared-epilogue-merge.

A "closed" group = a run of address-adjacent pieces where (a) the successor
pieces have NO prologue (don't start with `addiu sp,sp,-N`), (b) every branch
in the accumulated group stays within [group_start, group_end), and (c) no
function OUTSIDE the group branches into a successor piece (single-caller —
otherwise it's a genuine shared-tail / -O1 tail-merge cap, NOT a mis-split).
Such groups merge cleanly and usually match at -O2.

CAVEATS:
  - Yay0 segments (mgrproc/timproc*/game_uso/...) are compiled -g3 (unfilled
    delay slots). Even a correct merge there won't byte-match at plain -O2, and
    the per-file -g3 split is blocked by the Yay0 one-block-per-.o pipeline.
    Mine NON-Yay0 segments first (game_libs, gui_uso non-char-mapper, kernel).
  - gui_uso 0x00..~0xCC is the documented char-mapper fallthrough chain
    (reference_1080_chained_char_mapper_fallthrough) — NM-only, skip.

MERGE RECIPE (verified game_libs_func_0002A8C4, 00009A2C):
  1. Append successor pieces' `.word` lines into the head .s before `endlabel`;
     set the head `nonmatching` size to the merged total; `rm` successor .s.
  2. Replace head + successor INCLUDE_ASM/stub lines in src/ with ONE C fn.
  3. make build/src/<unit>.c.o; diff fn bytes vs the merged .s words.
  4. refresh expected/.o, log episode, land.

Usage: python3 scripts/find-misplit-pairs.py [segment_substr] [--max-insn N]
"""
import re, glob, sys

BRANCH_OPS = {4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17, 1}  # beq/bne/blez/bgtz/*l/regimm


def parse(sf):
    t = open(sf).read()
    h = re.search(r'nonmatching\s+(\S+),\s*0x([0-9A-Fa-f]+)', t)
    rows = re.findall(r'/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s*\*/', t)
    if not h or not rows:
        return None
    return dict(name=h.group(1), size=int(h.group(2), 16),
                start=int(rows[0][0], 16), words=[int(w, 16) for _, w in rows])


def btargets(start, words):
    out = []
    for i, w in enumerate(words):
        if ((w >> 26) & 0x3f) in BRANCH_OPS:
            off = w & 0xffff
            if off & 0x8000:
                off -= 0x10000
            out.append(start + (i + 1 + off) * 4)
    return out


def has_prologue(f):
    w0 = f['words'][0]
    return (w0 >> 16) == 0x27bd and (w0 & 0x8000)


def main():
    filt = next((a for a in sys.argv[1:] if not a.startswith('--')), '')
    max_insn = 9999
    if '--max-insn' in sys.argv:
        max_insn = int(sys.argv[sys.argv.index('--max-insn') + 1])
    results = []
    for d in sorted(glob.glob('asm/nonmatchings/*/*/')):
        seg = d.split('/')[-3]
        if filt and filt not in seg:
            continue
        funcs = [p for p in (parse(sf) for sf in glob.glob(d + '*.s') if '_pad' not in sf) if p]
        funcs.sort(key=lambda x: x['start'])
        by_start = {f['start']: f for f in funcs}
        tcount = {}
        for f in funcs:
            for t in set(btargets(f['start'], f['words'])):
                tcount.setdefault(t, set()).add(f['start'])
        visited = set()
        for f in funcs:
            if f['start'] in visited:
                continue
            members = [f]
            end = f['start'] + f['size']
            ok = True
            while True:
                allt = set()
                for m in members:
                    allt |= set(btargets(m['start'], m['words']))
                if not [t for t in allt if t >= end]:
                    break
                nxt = by_start.get(end)
                if not nxt or has_prologue(nxt):
                    ok = False
                    break
                ext = set()
                for t in range(end, end + nxt['size'], 4):
                    ext |= tcount.get(t, set())
                if ext - {m['start'] for m in members}:
                    ok = False  # an outside fn branches in -> shared tail cap
                    break
                members.append(nxt)
                end += nxt['size']
                if len(members) > 8:
                    ok = False
                    break
            if ok and len(members) > 1:
                for m in members:
                    visited.add(m['start'])
                allt = set()
                for m in members:
                    allt |= set(btargets(m['start'], m['words']))
                if any(t < members[0]['start'] for t in allt):
                    continue  # head is itself a tail of an earlier fn
                total = end - members[0]['start']
                if total // 4 <= max_insn:
                    results.append((total, len(members), seg, members[0]['name'],
                                    [m['name'] for m in members[1:]]))
    results.sort()
    print(f'{len(results)} CLOSED mis-split groups'
          + (f' (<= {max_insn} insn)' if max_insn < 9999 else ''))
    for tot, n, seg, head, tail in results:
        print(f'  0x{tot:03x} ({tot // 4:2d}) {n}pc  {seg:14s} {head}  +{tail}')


if __name__ == '__main__':
    main()
