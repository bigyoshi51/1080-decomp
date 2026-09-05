#!/usr/bin/env python3
"""Find "matched empty fn" / tiny-leaf STUBS that are really the preceding
function's own block (mis-split at an internal `jr ra`).

Generalises scripts/find-beql-dup-misplits.py (agent-c, branch-likely
dup-first-insn only) to ANY branch: the six 2026-09-05 cases share one root --
a 1-3 word symbol B (`jr ra; nop`, `move v0,zero; jr ra; nop`, `li v0,N; jr
ra; nop`, ...) that immediately follows A in the ROM, and A's last/any branch
(`bne/beq/beql/bnel/bnez/beqz/bgez/...`) lands ON B or on B+4.  B is then
  * an -O2 return-0 / return-1 exit block reached by a plain bne with the
    preset-default `move v0,zero` in the delay slot (timproc_b5 1CF0+1D14),
  * an -O0 else arm + ugen's dead fall-off `jr ra; nop` (mgrproc 140/170),
  * the trailing null block of the beql dup-first-insn idiom (game_uso 7A98).
Several such B were "matched" as `void f(void){}` WITH episodes -- fake exacts.

B may still be an INCLUDE_ASM .s, or already a matched C stub (`void f(void)
{}` / `{ return 0; }`) whose .s is gone; both are found (the C-stub address is
derived from the name).  Rejects B that any OTHER function branches into (a
genuine shared tail), that is `jal`-ed by name-visible code, or that is
referenced from C as a call / pointer (grep count > its own def+decl).

See docs/MATCHING_WORKFLOW.md
  #feedback-beql-next-symbol-plus-4-is-mis-split-branch-likely-block
  #o0-predicate-misplit-merge-recipe
and docs/IDO_CODEGEN.md #o0-two-block-predicate-not-adjacent-leaf-cap.

Usage: python3 scripts/find-stub-misplits.py [segment_substr] [--max-stub-words N]
                                             [--exclude NAME,NAME,...]
"""
import glob
import os
import re
import subprocess
import sys

BRANCH_OPS = {4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17, 1}  # beq/bne/blez/bgtz/*l/regimm
JR_RA = 0x03E00008
ROWRE = re.compile(r'/\*\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s*\*/')
BAREWORD = re.compile(r'^\s*\.word\s+0x([0-9A-Fa-f]{8})', re.M)
NAMEHEX = re.compile(r'(?:func_|D_)([0-9A-Fa-f]{8})$')


def name_addr(name):
    m = NAMEHEX.search(name)
    if not m:
        return None
    v = int(m.group(1), 16)
    return v & 0x7FFFFFFF if v >= 0x80000000 else v


def parse(sf):
    t = open(sf).read()
    h = re.search(r'nonmatching\s+(\S+),\s*0x([0-9A-Fa-f]+)', t)
    if not h:
        return None
    name, size = h.group(1), int(h.group(2), 16)
    rows = ROWRE.findall(t)
    if rows:
        start = int(rows[0][1], 16)
        if start >= 0x80000000:
            start &= 0x7FFFFFFF
        words = [int(w, 16) for _, _, w in rows]
    else:
        words = [int(w, 16) for w in BAREWORD.findall(t)]
        start = name_addr(name)
        if start is None or not words:
            return None
    return dict(name=name, size=size, start=start, words=words, path=sf)


def btargets(start, words):
    out = []
    for i, w in enumerate(words):
        if ((w >> 26) & 0x3f) in BRANCH_OPS:
            off = w & 0xffff
            if off & 0x8000:
                off -= 0x10000
            out.append(start + (i + 1 + off) * 4)
    return out


def jaltargets(start, words):
    out = set()
    for w in words:
        if (w >> 26) == 3 and (w & 0x3ffffff):
            out.add(((start & 0xF0000000) | ((w & 0x3ffffff) << 2)) & 0x7FFFFFFF)
    return out


def disasm_word(w):
    op = w >> 26
    if w == 0:
        return 'nop'
    if w == JR_RA:
        return 'jr ra'
    if w == 0x00001025:
        return 'move v0,zero'
    if op == 9 and ((w >> 21) & 31) == 0:
        return f'li ${(w >> 16) & 31},{w & 0xffff:#x}'
    return f'{w:08x}'


def c_stubs(seg):
    """Matched C stubs (void f(void){} / {return 0;}) in src/<seg>/ -> {addr: (name, nwords, file:line)}"""
    out = {}
    pat = re.compile(r'^\s*(?:void|int|s32|u32)\s+(\w+)\(void\)\s*\{\s*(return\s+0\s*;)?\s*\}')
    for cf in glob.glob(f'src/{seg}/*.c'):
        for ln, line in enumerate(open(cf), 1):
            m = pat.match(line)
            if m:
                a = name_addr(m.group(1))
                if a is not None:
                    out[a] = (m.group(1), 3 if m.group(2) else 2, f'{cf}:{ln}')
    return out


def src_refs(name):
    r = subprocess.run(['grep', '-rlw', name, 'src/'], capture_output=True, text=True)
    files = [f for f in r.stdout.split() if f]
    n = 0
    for f in files:
        n += sum(1 for l in open(f) if re.search(r'\b' + re.escape(name) + r'\b', l))
    return n, files


def main():
    args = sys.argv[1:]
    flagvals = {args[i + 1] for i, a in enumerate(args[:-1]) if a in ('--max-stub-words', '--exclude')}
    filt = next((a for a in args if not a.startswith('--') and a not in flagvals), '')
    max_stub = 3
    excl = set()
    if '--max-stub-words' in args:
        max_stub = int(args[args.index('--max-stub-words') + 1])
    if '--exclude' in args:
        excl = set(args[args.index('--exclude') + 1].split(','))
    hits = []
    for segdir in sorted(glob.glob('asm/nonmatchings/*/')):
        seg = segdir.rstrip('/').split('/')[-1]
        if filt and filt not in seg:
            continue
        files = glob.glob(segdir + '*/*.s') + glob.glob(segdir + '*.s')
        funcs = [p for p in (parse(sf) for sf in files if '_pad' not in sf and 'tail_data' not in sf) if p]
        funcs.sort(key=lambda x: x['start'])
        by_start = {f['start']: f for f in funcs}
        stubs = c_stubs(seg)
        tcount, jals = {}, set()
        for f in funcs:
            for t in set(btargets(f['start'], f['words'])):
                tcount.setdefault(t, set()).add(f['start'])
            jals |= jaltargets(f['start'], f['words'])
        for A in funcs:
            end = A['start'] + A['size']
            targ = [t for t in set(btargets(A['start'], A['words'])) if t >= end]
            if not targ:
                continue
            B = by_start.get(end)
            if B is not None:
                bname, bwords, bwhere = B['name'], B['words'], B['path']
                if end in stubs:  # .s kept but the C already "matched" it as a stub (has an episode?)
                    bwhere = stubs[end][2]
            elif end in stubs:
                bname, nw, bwhere = stubs[end]
                bwords = [JR_RA, 0] if nw == 2 else [0x00001025, JR_RA, 0]
            else:
                continue
            if len(bwords) > max_stub or JR_RA not in bwords:
                continue
            if bname in excl or A['name'] in excl:
                continue
            bend = end + len(bwords) * 4
            if not any(end <= t < bend for t in targ):
                continue
            outsiders = set()
            for t in range(end, bend, 4):
                outsiders |= tcount.get(t, set()) - {A['start']}
            if outsiders:
                continue
            if any(end <= j < bend for j in jals):
                continue
            nref, reffiles = src_refs(bname)
            hits.append((seg, A, bname, bwords, bwhere, sorted(t - end for t in targ if end <= t < bend),
                         nref, reffiles, B is None))
    print(f'{len(hits)} stub mis-split candidates (A -> adjacent stub B, A branches onto B/B+4, no other refs)')
    for seg, A, bname, bwords, bwhere, offs, nref, reffiles, matched in hits:
        kind = 'MATCHED-C-STUB(no .s)' if matched else ('MATCHED-C-STUB' if '.c:' in bwhere else 'INCLUDE_ASM')
        dis = '; '.join(disasm_word(w) for w in bwords)
        print(f'  {seg:14s} {A["name"]} ({len(A["words"])}w) -> {bname} [{dis}] '
              f'target=B+{",".join(str(o) for o in offs)} {kind} srcrefs={nref} ({os.path.basename(bwhere)})')


if __name__ == '__main__':
    main()
