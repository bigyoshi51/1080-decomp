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
                                             [--exclude NAME,NAME,...] [--runs]

--runs (2026-09-05, agent-g, after cases 13/14): the DISPATCHER-STUB-RUN
flavour the pairwise scan misses.  A head symbol H ends in a `jr tN`
jumptable dispatch, or carries an `li at,K; beq/bne` compare chain, or
branches into the run; it is followed by a RUN of >=2 ADJACENT 1-3 word
symbols each ending in `jr ra` (`jr ra; li v0,K` case arms, `jr ra; nop`
shared epilogue), every one "matched" as `return K;` / `{}` WITH a fake-exact
episode (2E290: seven arms; 560E4: ten arms + epilogue).  The pairwise scan
only reports H -> first stub (and only when H branches onto it, which a `jr
tN` head never does).  --runs walks the address ladder (all .s + all C fn
defs in src/<seg>/) and prints every such run with the head's flavour,
episode count, and outside references (jal / other-.s reloc / src refs /
undefined_syms_auto.txt); the head + whole run is ONE function.  Runs of
`jr ra; sw a0,0(sp)` (-O1 arg-homing empty callbacks after a jr-tN head, e.g.
game_libs 7324.., 76C8.., 38B6C..) are separate functions and are filtered:
a case arm never homes an argument.  First two --runs hits, both the same
`addiu t6,aN,-1; sltiu at,t6,8; beqz; jr t6` + 3-4 return arms + an unfilled
`X; jr ra; nop` default that had been carved into a -O2 -g3 TRUNCATE_TEXT
unit: game_libs 343F4 (landed, case 15) and timproc_uso_b5 87A0 (open).
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


C_DEF = re.compile(r'^\s*(?:static\s+)?(?:void|int|s32|u32|s16|u16|s8|u8|f32|float|char|short|long|unsigned(?:\s+\w+)?|\w+\s*\*+|\w+)\s+\**(\w*func_[0-9A-Fa-f]{4,8})\s*\(')
C_STUB = re.compile(r'^\s*(?:void|int|s32|u32)\s+(\w+)\(void\)\s*\{\s*(?:return\s+(-?(?:0x[0-9A-Fa-f]+|\d+))\s*;)?\s*\}')


def c_defs(seg):
    """Every C-defined fn with a name-derivable address in src/<seg>/ ->
    {addr: (name, file:line, stub_return_or_None_or_'void')}"""
    out = {}
    for cf in glob.glob(f'src/{seg}/*.c'):
        for ln, line in enumerate(open(cf), 1):
            m = C_DEF.match(line)
            if not m or line.lstrip().startswith(('extern', 'INCLUDE_ASM')):
                continue
            a = name_addr(m.group(1))
            if a is None:
                continue
            st = C_STUB.match(line)
            stub = None
            if st:
                stub = 'void' if st.group(2) is None else int(st.group(2), 0)
            out[a] = (m.group(1), f'{cf}:{ln}', stub)
    return out


def is_jr_tn(w):
    return (w >> 26) == 0 and (w & 0x3f) == 8 and ((w >> 21) & 31) != 31


def li_at_compare_count(words):
    """count `addiu at,zero,K` immediately followed by beq/bne rs,at"""
    n = 0
    for i in range(len(words) - 1):
        w, nx = words[i], words[i + 1]
        if (w >> 16) == 0x2401 and ((nx >> 26) in (4, 5, 0x14, 0x15)) and ((nx >> 16) & 31) == 1:
            n += 1
    return n


def outside_refs(name, own_path):
    """(other .s files naming it, undefined_syms_auto.txt line, src ref count)"""
    r = subprocess.run(['grep', '-rlw', name, 'asm/'], capture_output=True, text=True)
    others = [f for f in r.stdout.split() if f and os.path.abspath(f) != os.path.abspath(own_path or '')]
    u = 0
    if os.path.exists('undefined_syms_auto.txt'):
        u = sum(1 for l in open('undefined_syms_auto.txt') if re.search(r'\b' + re.escape(name) + r'\b', l))
    nref, _ = src_refs(name)
    return others, u, nref


def runs_mode(filt, max_stub, excl):
    hits = []
    for segdir in sorted(glob.glob('asm/nonmatchings/*/')):
        seg = segdir.rstrip('/').split('/')[-1]
        if filt and filt not in seg:
            continue
        files = glob.glob(segdir + '*/*.s') + glob.glob(segdir + '*.s')
        funcs = [p for p in (parse(sf) for sf in files if '_pad' not in sf and 'tail_data' not in sf) if p]
        pads = [p for p in (parse(sf) for sf in files if '_pad' in sf or 'tail_data' in sf) if p]
        defs = c_defs(seg)
        # address ladder: .s symbols win (they carry words); C-only defs fill the rest
        ladder = {}
        for f in funcs:
            ladder[f['start']] = dict(name=f['name'], start=f['start'], size=f['size'], words=f['words'],
                                      path=f['path'], c=None)
        for f in pads:
            ladder.setdefault(f['start'], dict(name=f['name'], start=f['start'], size=f['size'], words=f['words'],
                                               path=f['path'], c=None, pad=True))
        for a, (nm, where, stub) in defs.items():
            if a in ladder:
                ladder[a]['c'] = (where, stub)
            else:
                ladder[a] = dict(name=nm, start=a, size=None, words=None, path=None, c=(where, stub))
        syms = [ladder[a] for a in sorted(ladder)]
        for i, sy in enumerate(syms):
            if sy['size'] is None:  # C-only: size = gap to the next symbol
                sy['size'] = (syms[i + 1]['start'] - sy['start']) if i + 1 < len(syms) else 0x1000
        jals = set()
        for f in funcs:
            jals |= jaltargets(f['start'], f['words'])

        def is_stub(sy):
            if sy.get('pad'):
                return False
            if sy['size'] > max_stub * 4 or sy['size'] <= 0:
                return False
            if sy['words'] is not None:
                # a store to $sp (arg homing `sw a0,0(sp)`) is a FUNCTION ENTRY, never a case arm
                if any(((w >> 26) in (0x2B, 0x29, 0x28)) and ((w >> 21) & 31) == 29 for w in sy['words']):
                    return False
                return JR_RA in sy['words']
            return sy['c'] is not None and sy['c'][1] is not None  # C one-liner stub

        i = 0
        while i < len(syms):
            if not is_stub(syms[i]):
                i += 1
                continue
            j = i
            while j + 1 < len(syms) and is_stub(syms[j + 1]) and syms[j + 1]['start'] == syms[j]['start'] + syms[j]['size']:
                j += 1
            run = syms[i:j + 1]
            i = j + 1
            if len(run) < 2:
                continue
            k = syms.index(run[0]) - 1
            if k < 0:
                continue
            H = syms[k]
            if H['words'] is None or H['start'] + H['size'] != run[0]['start']:
                continue
            rs, re_ = run[0]['start'], run[-1]['start'] + run[-1]['size']
            flav = []
            if any(is_jr_tn(w) for w in H['words']):
                flav.append('jr-tN')
            nli = li_at_compare_count(H['words'])
            if nli >= 2:
                flav.append(f'li-at-cmp x{nli}')
            bt = [t for t in btargets(H['start'], H['words']) if rs <= t < re_]
            if bt:
                flav.append(f'branch->run+{",".join(str(t - rs) for t in sorted(set(bt)))}')
            if not flav:
                continue
            if H['name'] in excl or any(s['name'] in excl for s in run):
                continue
            notes = []
            for s in run:
                eps = os.path.exists(f'episodes/{s["name"]}.json')
                jl = any(s['start'] <= t < s['start'] + s['size'] for t in jals)
                others, u, nref = outside_refs(s['name'], s['path'])
                kind = 'C' if s['c'] and s['words'] is None else ('C+.s' if s['c'] else '.s')
                dis = '; '.join(disasm_word(w) for w in s['words']) if s['words'] else \
                    ('{}' if s['c'][1] == 'void' else f'return {s["c"][1]}')
                flag = ''
                if jl:
                    flag += ' JAL!'
                if others:
                    flag += f' ASMREF:{",".join(os.path.basename(o) for o in others[:3])}'
                if u:
                    flag += ' UNDEF_SYMS!'
                notes.append(f'      {s["name"]} {s["size"] // 4}w [{dis}] {kind}{" EP" if eps else ""} srcrefs={nref}{flag}')
            neps = sum(1 for s in run if os.path.exists(f'episodes/{s["name"]}.json'))
            hits.append((seg, H, run, flav, neps, notes, rs, re_))
    print(f'{len(hits)} dispatcher-stub-RUN candidates (head H + >=2 adjacent 1-{max_stub}w jr-ra symbols)')
    for seg, H, run, flav, neps, notes, rs, re_ in hits:
        hk = 'C+.s' if H['c'] else '.s'
        print(f'  {seg:14s} HEAD {H["name"]} ({len(H["words"])}w, {hk}, {"; ".join(flav)}) + run of {len(run)} '
              f'[{rs:#x}..{re_:#x}] merged={(re_ - H["start"]) // 4}w fake-episodes={neps}')
        for n in notes:
            print(n)


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
    if '--runs' in args:
        return runs_mode(filt, max_stub, excl)
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
