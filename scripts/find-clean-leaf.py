#!/usr/bin/env python3
"""Surface unwrapped functions that are NOT one of the known IDO/USO caps —
i.e. the clean per-tick decomp candidates. Run after `objdiff-cli report
generate -o /tmp/rp.json`.

Usage:
    scripts/find-clean-leaf.py [--max-fuzzy 5] [--min 80] [--max 240]
                               [--seg game_libs] [--limit 10]

For each candidate (fuzzy < max-fuzzy, size in [min,max]) it reads the raw
`.word` from asm/nonmatchings/**/<fn>.s, objdumps a 0-based blob, and rejects
the cap classes this project has hit repeatedly (2026-06 session):
  fp       — any cop1/lwc1/swc1 (FP scheduling / caller-set-float)
  64       — ld/sd/ddiv/dmult/dsra... (libgcc 64-bit runtime)
  cp0      — mfc0/mtc0/cache/tlb/eret (kernel/exception, m2c can't parse)
  mmio     — lui 0xA4xx/0xBF.. (hardware register I/O)
  leadnop  — leading nop (splat boundary misattribution)
  interfn  — a branch target past the function end (inter-fn shared tail)
  cs       — a t/v register READ before written, or mflo w/o mult (caller-set)
  call     — has jal (reloc-blind USO call; only flagged when --no-call)

NOTE: only works for raw-.word USO segments (game_libs, *_uso). Kernel `.s`
is mnemonic disasm (no .word) -> use `uv run m2c <.s>` directly there.
Survivors still hit -O2 *quirk* near-miss ceilings (branch-likely redundant
pointer-copy ~36-61%, DSE redundant store ~93%, multi-use-multu — see
docs/IDO_CODEGEN.md) but are the right place to spend a tick; the
inline-to-frameless and explicit-shift levers reliably get them to 60-93%.
"""
import json, re, struct, subprocess, glob, sys, argparse


def decode(n):
    fs = glob.glob('asm/nonmatchings/**/%s.s' % n, recursive=True)
    if not fs:
        return None
    ws = [int(m, 16) for m in re.findall(r'\.word 0x([0-9A-Fa-f]{8})', open(fs[0]).read())]
    if not ws:
        return None  # mnemonic .s (kernel) — not handled here
    fp = sum(1 for w in ws if (w >> 26) in (0x11, 0x31, 0x35, 0x39, 0x3d, 0x32, 0x36, 0x3a, 0x3e))
    open('/tmp/_fcl.bin', 'wb').write(b''.join(struct.pack('>I', w) for w in ws))
    out = subprocess.run(['mips-linux-gnu-objdump', '-D', '-b', 'binary', '-m', 'mips:4000',
                          '-EB', '-M', 'no-aliases', '/tmp/_fcl.bin'], capture_output=True, text=True).stdout
    ins = [re.sub(r'^\s+[0-9a-f]+:\s+[0-9a-f]{8}\s+', '', l).strip()
           for l in out.splitlines() if re.match(r'\s+[0-9a-f]+:', l)]
    return ins, len(ws) * 4, fp


def cap(ins, size, fp, allow_call):
    if fp > 0:
        return 'fp'
    txt = ' '.join(ins)
    if re.search(r'\b(ld|sd|dadd|dsub|ddiv|dmult|dsll|dsra|dsrl|dmtc|dmfc)\w*\b', txt):
        return '64'
    if re.search(r'\b(mfc0|mtc0|cache|tlb|eret)\b', txt):
        return 'cp0'
    if re.search(r'lui\s+\w+,0x(a4|a3|a5|bf)', txt):
        return 'mmio'
    if not allow_call and re.search(r'\bjal\b', txt):
        return 'call'
    if ins and ins[0] in ('nop', 'sll zero,zero,0x0'):
        return 'leadnop'
    BR = ('b', 'beq', 'bne', 'beql', 'bnel', 'blez', 'bgtz', 'bltz', 'bgez', 'beqz', 'bnez')
    for l in ins:
        m = re.search(r'\b0x([0-9a-f]+)$', l)
        if m and l.split()[0] in BR and int(m.group(1), 16) >= size:
            return 'interfn'
    written = set()
    ARG = {'a0', 'a1', 'a2', 'a3', 'sp', 'zero', 'ra'}
    RD = ('lw', 'lh', 'lhu', 'lb', 'lbu', 'lwl', 'lwr')
    ALU = ('addu', 'subu', 'addiu', 'or', 'and', 'sll', 'sllv', 'slt', 'sltu',
           'multu', 'mult', 'move', 'xor', 'nor', 'sra', 'srl', 'srlv', 'srav')
    for l in ins[:30]:
        parts = re.split(r'[\s,]+', l)
        if not parts:
            continue
        op = parts[0]
        regs = [x for x in parts[1:] if re.match(r'^(v[01]|t\d|s\d|a[0-3]|at)$', x)]
        if op in ('mflo', 'mfhi'):
            return 'mf'
        if op in RD and len(regs) >= 2 and (regs[1].startswith('t') or regs[1] in ('v0', 'v1')) \
                and regs[1] not in written and regs[1] not in ARG:
            return 'cs'
        if op in ALU and len(regs) >= 2:
            for sr in regs[1:]:
                if (sr.startswith('t') or sr in ('v0', 'v1')) and sr not in written and sr not in ARG:
                    return 'cs'
        if regs and op not in ('sw', 'sh', 'sb', 'swl', 'swr', 'beq', 'bne', 'j', 'jr', 'jal', 'b', 'nop'):
            written.add(regs[0])
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--max-fuzzy', type=float, default=5)
    ap.add_argument('--min', type=int, default=80)
    ap.add_argument('--max', type=int, default=240)
    ap.add_argument('--seg', default='')
    ap.add_argument('--limit', type=int, default=10)
    ap.add_argument('--allow-call', action='store_true')
    ap.add_argument('--report', default='/tmp/rp.json')
    a = ap.parse_args()
    r = json.load(open(a.report))
    cands = []
    for u in r.get('units', []):
        for f in u.get('functions', []) or []:
            p = f.get('fuzzy_match_percent', 0)
            try:
                s = int(f.get('size', 0))
            except Exception:
                s = 0
            n = f['name']
            if isinstance(p, (int, float)) and p < a.max_fuzzy and a.min <= s <= a.max and (not a.seg or a.seg in n):
                cands.append((s, n, round(p, 1)))
    cands.sort()
    srcs = glob.glob('src/**/*.c', recursive=True)
    shown = 0
    for s, n, p in cands:
        if shown >= a.limit:
            break
        d = decode(n)
        if not d:
            continue
        ins, size, fp = d
        c = cap(ins, size, fp, a.allow_call)
        if c is None:
            occ = sum(open(fp2).read().count(n) for fp2 in srcs)
            print('%-30s sz=%-4d fuzzy=%-5s occ=%d' % (n, s, p, occ))
            shown += 1
    if shown == 0:
        print('(no clean candidates in range — vein may be exhausted; widen --min/--max/--seg)')


if __name__ == '__main__':
    main()
