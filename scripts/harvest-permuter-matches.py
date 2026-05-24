#!/usr/bin/env python3
"""Harvest score-0 permuter matches into the repo as REAL matches (no patch).

For each nonmatchings/<func>/output-0-*/source.c:
  1. extract the matched function definition,
  2. replace that function's body inside its src `#ifdef NON_MATCHING` block,
  3. rebuild the .c.o and VERIFY byte-exact vs the .s (raw-diff=0) — the honesty gate,
  4. on success print READY (caller refreshes report / logs episode / commits).

Verify-only by default; does NOT git-commit (caller decides). Prints one line per
candidate: READY <fn> | FAIL <fn> <reason>.
"""
import re, sys, glob, os, subprocess, struct

def extract_func(src_text, fn):
    """Return (start_idx, end_idx, text) of the function definition in src_text,
    matching the col-0 signature line to the matching col-0 '}'."""
    L = src_text.split('\n')
    for i, l in enumerate(L):
        if re.match(rf'^[A-Za-z_][\w \*]*\b{re.escape(fn)}\s*\(', l) and not l.lstrip().startswith(('//','*','/*')):
            depth=0; seen=False
            for k in range(i, len(L)):
                depth += L[k].count('{') - L[k].count('}')
                if '{' in L[k]: seen=True
                if seen and depth==0:
                    return i, k, '\n'.join(L[i:k+1])
    return None

def src_file_for(fn):
    for p in glob.glob('src/**/*.c', recursive=True):
        if extract_func(open(p).read(), fn):
            return p
    return None

def asm_words(fn):
    g = glob.glob(f'asm/nonmatchings/**/{fn}.s', recursive=True)
    if not g: return None
    return [w.lower() for w in re.findall(r'\.word 0x([0-9A-F]{8})', open(g[0]).read())]

def built_words(obj, fn):
    d = subprocess.run(['mips-linux-gnu-objdump','-d',obj],capture_output=True,text=True).stdout
    m = re.search(rf'<{fn}>:\n((?:\s+[0-9a-f]+:\s+[0-9a-f]{{8}}.*\n)+)', d)
    if not m: return None
    return [w for w,_ in re.findall(r':\s+([0-9a-f]{8})\s+(.*)', m.group(1))]

def norm(w): return '0c000000' if w[:2]=='0c' else w

def harvest_one(fn):
    outs = sorted(glob.glob(f'nonmatchings/{fn}/output-0-*/source.c'))
    if not outs:
        return None
    cand = extract_func(open(outs[0]).read(), fn)
    if not cand:
        return f'FAIL {fn} no-func-in-output'
    new_body = cand[2]
    p = src_file_for(fn)
    if not p:
        return f'FAIL {fn} no-src-file'
    txt = open(p).read()
    span = extract_func(txt, fn)
    if not span:
        return f'FAIL {fn} no-func-in-src'
    s,e,_ = span
    L = txt.split('\n')
    L[s:e+1] = new_body.split('\n')
    open(p,'w').write('\n'.join(L))
    # rebuild + verify
    obj = 'build/non_matching/' + p + '.o'
    subprocess.run(['rm','-f',obj])
    r = subprocess.run(['make','RUN_CC_CHECK=0',obj],capture_output=True,text=True)
    bw = built_words(obj, fn); tw = asm_words(fn)
    if not bw or not tw:
        return f'FAIL {fn} build-or-asm-missing'
    nd = sum(1 for i in range(min(len(bw),len(tw))) if norm(bw[i])!=norm(tw[i])) + abs(len(bw)-len(tw))
    if nd==0:
        return f'READY {fn} {p}'
    # revert on failure
    subprocess.run(['git','checkout','--',p])
    return f'FAIL {fn} verify-diff={nd}'

if __name__ == '__main__':
    fns = sys.argv[1:] or [os.path.basename(os.path.dirname(os.path.dirname(d)))
                           for d in glob.glob('nonmatchings/*/output-0-*/')]
    for fn in sorted(set(fns)):
        res = harvest_one(fn)
        if res: print(res)
