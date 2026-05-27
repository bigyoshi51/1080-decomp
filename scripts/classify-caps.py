#!/usr/bin/env python3
"""Classify NM-wrap caps by their dominant diff pattern.

For each unmatched function, compares non_matching/.o vs expected/.o byte-by-byte,
classifies the diff pattern, and groups candidates by cap class. This tells us
WHERE to focus tooling investment.

Cap classes detected:
  REG_RENAME    - same opcode, different register field (Reg-rename, common)
  SCHED_SWAP    - same insns reordered (Schedule)
  FP_OPERAND    - FP operand swap (commutative add/mul fs/ft)
  IMMEDIATE     - same opcode, different immediate field (Const)
  BRANCH_TYPE   - beq vs beql vs bne vs bnel
  EXTRA_INSN    - built has extra/missing instructions (size mismatch)
  SPILL_OFFSET  - sw/lw to different sp offset
  MIXED         - multiple cap classes
  RELOC         - jal target / lui-addiu reloc placeholder diff only (often false-positive)

Usage:
  classify-caps.py [--fuzzy-min FM] [--fuzzy-max FX] [--size-max SZ] [--limit N]
"""
import argparse, json, os, re, struct, subprocess, sys
from collections import defaultdict, Counter
from pathlib import Path

REPO = Path(__file__).parent.parent.resolve()


def get_bytes(obj_path, sym):
    if not os.path.exists(obj_path): return None
    try:
        out = subprocess.check_output(['mips-linux-gnu-objdump', '-t', obj_path], text=True)
    except: return None
    for line in out.split('\n'):
        if sym in line and '.text' in line:
            parts = line.split()
            try:
                addr = int(parts[0], 16)
                size = int(parts[-2], 16)
                raw = subprocess.check_output([
                    'mips-linux-gnu-objcopy', '-O', 'binary', '-j', '.text',
                    obj_path, '/dev/stdout'])
                return raw[addr:addr+size]
            except:
                return None
    return None


def decode_insn(w):
    """Rough instruction class identification."""
    opc = (w >> 26) & 0x3F
    if opc == 0:  # SPECIAL
        funct = w & 0x3F
        return ('R', funct)
    if opc == 0x4: return ('BEQ', 0)
    if opc == 0x5: return ('BNE', 0)
    if opc == 0x14: return ('BEQL', 0)
    if opc == 0x15: return ('BNEL', 0)
    if opc == 0x11: return ('COP1', (w >> 21) & 0x1F)  # FP
    if opc in (0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26): return ('LOAD', opc)
    if opc in (0x28, 0x29, 0x2A, 0x2B, 0x2E, 0x2F): return ('STORE', opc)
    if opc in (0x31, 0x35): return ('LWC1', 0)
    if opc in (0x39, 0x3D): return ('SWC1', 0)
    if opc == 0xC: return ('ANDI', 0)
    if opc == 0xD: return ('ORI', 0)
    if opc == 0xF: return ('LUI', 0)
    return ('OTHER', opc)


def diff_class(built, expected):
    """Classify the differences between built and expected bytes."""
    if not built or not expected: return ('NOEXP', 0)
    if len(built) != len(expected):
        return ('EXTRA_INSN', abs(len(built) - len(expected)) // 4)
    classes = Counter()
    n_diffs = 0
    for i in range(0, len(built), 4):
        bw = struct.unpack('>I', built[i:i+4])[0]
        ew = struct.unpack('>I', expected[i:i+4])[0]
        if bw == ew: continue
        n_diffs += 1
        bd = decode_insn(bw)
        ed = decode_insn(ew)
        # Reloc-only: jal with different target
        if (bw >> 26) == 3 and (ew >> 26) == 3:
            classes['RELOC'] += 1
            continue
        # Same opcode + funct, different operands -> register rename or operand swap
        if bd == ed:
            opc = (bw >> 26) & 0x3F
            if opc == 0:
                # R-type: check if same operation, diff regs
                funct = bw & 0x3F
                if funct in (0x21, 0x25, 0x24, 0x26):  # addu, or, and, xor
                    classes['REG_RENAME'] += 1
                else:
                    classes['REG_RENAME'] += 1
            elif opc == 0x11:  # COP1
                fmt = (bw >> 21) & 0x1F
                if fmt == 0x10:  # .s
                    func = bw & 0x3F
                    if func in (0, 1, 2, 3):  # add/sub/mul/div
                        classes['FP_OPERAND'] += 1
                    else:
                        classes['REG_RENAME'] += 1
                else:
                    classes['REG_RENAME'] += 1
            elif opc in (0x20, 0x23, 0x24, 0x25, 0x28, 0x2B, 0x31, 0x39):
                # Load/store: check if offset differs
                b_off = bw & 0xFFFF
                e_off = ew & 0xFFFF
                b_rt = (bw >> 16) & 0x1F
                e_rt = (ew >> 16) & 0x1F
                if b_off != e_off and b_rt == e_rt:
                    classes['SPILL_OFFSET'] += 1
                else:
                    classes['REG_RENAME'] += 1
            elif opc in (0xC, 0xD, 0xE, 0x8, 0x9):  # immediate ops
                b_imm = bw & 0xFFFF
                e_imm = ew & 0xFFFF
                if b_imm != e_imm:
                    classes['IMMEDIATE'] += 1
                else:
                    classes['REG_RENAME'] += 1
            elif opc == 0xF:  # LUI
                classes['IMMEDIATE'] += 1
            else:
                classes['OTHER'] += 1
        else:
            # Different opcode/funct
            if (bd[0] in ('BEQ','BNE','BEQL','BNEL')) and (ed[0] in ('BEQ','BNE','BEQL','BNEL')):
                classes['BRANCH_TYPE'] += 1
            else:
                classes['OTHER'] += 1
    if n_diffs == 0: return ('MATCH', 0)
    # Strip RELOC if it's the only diff (likely false positive)
    if classes['RELOC'] == n_diffs:
        return ('RELOC', n_diffs)
    real_diffs = n_diffs - classes['RELOC']
    classes.pop('RELOC', None)
    if not classes: return ('RELOC', n_diffs)
    if len(classes) == 1:
        return (list(classes.keys())[0], real_diffs)
    return ('MIXED', real_diffs)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--fuzzy-min', type=float, default=80.0)
    ap.add_argument('--fuzzy-max', type=float, default=100.0)
    ap.add_argument('--size-max', type=int, default=400)
    ap.add_argument('--limit', type=int, default=80)
    args = ap.parse_args()

    print('Generating fresh report...', file=sys.stderr)
    subprocess.run(['objdiff-cli', 'report', 'generate', '-o', '/tmp/classify-rep.json'],
                   capture_output=True, cwd=REPO)
    r = json.load(open('/tmp/classify-rep.json'))

    by_class = defaultdict(list)
    for u in r['units']:
        unit_name = u['name']
        for fn in u.get('functions', []):
            fm = fn.get('fuzzy_match_percent', 100)
            sz = int(fn['size'])
            if fm == 100.0 or 'fuzzy_match_percent' not in fn: continue
            if not (args.fuzzy_min <= fm < args.fuzzy_max): continue
            if sz > args.size_max: continue
            name = fn['name']
            nm_obj = str(REPO / 'build/non_matching' / f'{unit_name}.c.o')
            ex_obj = str(REPO / 'expected' / f'{unit_name}.c.o')
            nm = get_bytes(nm_obj, name)
            ex = get_bytes(ex_obj, name)
            cls, d = diff_class(nm, ex)
            by_class[cls].append((fm, sz, name, unit_name, d))

    total = sum(len(v) for v in by_class.values())
    print(f'\nClassification (fuzzy={args.fuzzy_min}-{args.fuzzy_max}%, size<={args.size_max}, total={total}):\n')
    for cls in sorted(by_class, key=lambda c: -len(by_class[c])):
        items = by_class[cls]
        print(f'=== {cls}: {len(items)} candidates ===')
        for fm, sz, name, unit, d in sorted(items, key=lambda x: (-x[0], x[1]))[:10]:
            print(f'  {fm:6.2f}  size={sz:3}  diffs={d:3}  {unit:42}  {name}')
        if len(items) > 10:
            print(f'  ... +{len(items)-10} more')


if __name__ == '__main__':
    main()
