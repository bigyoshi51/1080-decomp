#!/usr/bin/env python3
"""De-INSN_PATCH a set of functions: re-wrap their unwrapped C bodies as
#ifdef NON_MATCHING / #else INCLUDE_ASM / #endif (so the default build uses the
asm = correct ROM bytes, and the C is preserved as documentation), and strip the
function's INSN_PATCH / NON_MATCHING_INSN_PATCH / INSN_RELOC_PATCH lines from the
Makefile.

Usage: dewrap-insn-patch.py <fn1> <fn2> ...   (or - to read fns from stdin)

Honors the 2026-05 decision: instruction-byte patching is removed; these
functions revert to honest NON_MATCHING. Idempotent-ish: skips already-wrapped.
"""
import re, sys, glob, os

def asm_incpath(fn):
    m = glob.glob(f'asm/nonmatchings/**/{fn}.s', recursive=True)
    if not m:
        return None
    return os.path.dirname(m[0])  # e.g. asm/nonmatchings/kernel  or asm/nonmatchings/game_libs/game_libs

def find_def_span(L, fn):
    """Return (start, end) line indices [start, end] inclusive covering the C
    definition of fn (ANSI or K&R), or None. end is the col-0 '}' line."""
    for i, l in enumerate(L):
        # definition line: starts at col0, contains fn( , not a call/decl/comment
        if re.match(rf'^[A-Za-z_][\w \*]*\b{re.escape(fn)}\s*\(', l) and ';' not in l.split(')')[-1][:2] and not l.lstrip().startswith(('//','*','/*')):
            # walk to the opening brace, then to matching col-0 '}'
            j = i
            # ensure this is a definition (a '{' appears before the next col-0 '}' / ';' def)
            # find body end: next line that is exactly '}'
            k = i
            depth = 0
            seen_brace = False
            while k < len(L):
                depth += L[k].count('{') - L[k].count('}')
                if '{' in L[k]:
                    seen_brace = True
                if seen_brace and depth == 0:
                    return (i, k)
                k += 1
            return None
    return None

def wrap_file(path, fns):
    """Wrap unwrapped C defs as NON_MATCHING. Return set of HANDLED fns
    (newly-wrapped OR already-wrapped) — only these are safe to strip from the
    Makefile."""
    txt = open(path).read()
    L = txt.split('\n')
    handled = set()
    spans = []
    for fn in fns:
        if re.search(rf'#else\s*\n\s*INCLUDE_ASM\("[^"]+",\s*{re.escape(fn)}\)', txt):
            handled.add(fn)  # already NM-wrapped, default build = INCLUDE_ASM
            continue
        sp = find_def_span(L, fn)
        if not sp:
            print(f'  WARN no def span for {fn} in {path}', file=sys.stderr)
            continue
        inc = asm_incpath(fn)
        if not inc:
            print(f'  WARN no asm for {fn}', file=sys.stderr)
            continue
        spans.append((sp[0], sp[1], fn, inc))
    spans.sort(reverse=True)
    for s, e, fn, inc in spans:
        block = ['#ifdef NON_MATCHING'] + L[s:e+1] + ['#else', f'INCLUDE_ASM("{inc}", {fn});', '#endif']
        L[s:e+1] = block
        handled.add(fn)
    if spans:
        open(path, 'w').write('\n'.join(L))
    return handled

def strip_makefile(fns):
    mk = open('Makefile').read()
    out = []
    fnset = set(fns)
    raw = mk.split('\n')
    i = 0
    removed = 0
    while i < len(raw):
        l = raw[i]
        # gather full logical line (continuations)
        full = l
        cont = [i]
        while full.rstrip().endswith('\\'):
            i += 1
            full = full[:-1] + raw[i]
            cont.append(i)
        is_patch = re.search(r':\s*(NON_MATCHING_)?(INSN_PATCH|INSN_RELOC_PATCH)\s*[:+]?=', full)
        if is_patch:
            # remove only the fn= entries for our fns; if all removed, drop the line
            patched = re.findall(r'\b([A-Za-z_]\w*)=0x', full)
            keep = [p for p in patched if p not in fnset]
            if not keep:
                removed += 1
                i += 1
                continue
            else:
                # rebuild line keeping only non-target specs (rare; usually 1 fn/line)
                # split header and specs
                m = re.match(r'(.*?:\s*(?:NON_MATCHING_)?(?:INSN_PATCH|INSN_RELOC_PATCH)\s*[:+]?=)(.*)', full, re.DOTALL)
                hdr, body = m.group(1), m.group(2)
                specs = re.findall(r'[A-Za-z_]\w*=(?:0x[0-9A-Fa-f]+:0x[0-9A-Fa-f]+,?)+|[A-Za-z_]\w*=(?:0x[0-9A-Fa-f]+,?)+', body)
                kept = [sp for sp in specs if sp.split('=')[0] not in fnset]
                if kept:
                    out.append(hdr + ' ' + ' '.join(kept))
                else:
                    removed += 1
                i += 1
                continue
        out.append(full)
        i += 1
    open('Makefile', 'w').write('\n'.join(out))
    return removed

if __name__ == '__main__':
    args = sys.argv[1:]
    if args == ['-']:
        fns = [x.strip() for x in sys.stdin if x.strip()]
    else:
        fns = args
    # group fns by the file that actually DEFINES them (not merely mentions them
    # in a comment/cross-ref). Prefer a file where find_def_span succeeds; else a
    # file with a standalone INCLUDE_ASM(fn).
    byfile = {}
    srcfiles = glob.glob('src/**/*.c', recursive=True)
    fileidx = {p: open(p).read().split('\n') for p in srcfiles}
    for fn in fns:
        target = None
        for p, L in fileidx.items():
            if find_def_span(L, fn):
                target = p
                break
        if target is None:
            for p, L in fileidx.items():
                if any(re.search(rf'INCLUDE_ASM\("[^"]+",\s*{re.escape(fn)}\)', x) for x in L):
                    target = p
                    break
        if target is None:
            print(f'  WARN cannot locate definition file for {fn}', file=sys.stderr)
            continue
        byfile.setdefault(target, []).append(fn)
    handled = set()
    for p, fl in byfile.items():
        handled |= wrap_file(p, fl)
    rtot = strip_makefile(handled)   # only strip Makefile for funcs we actually handled
    unhandled = [f for f in fns if f not in handled]
    print(f'handled {len(handled)} funcs, removed {rtot} Makefile patch lines')
    if unhandled:
        print(f'UNHANDLED ({len(unhandled)}) — left intact for manual review:')
        for f in unhandled:
            print('  ', f)
