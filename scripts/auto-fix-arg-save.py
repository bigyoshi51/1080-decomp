#!/usr/bin/env python3
"""Auto-apply unused-arg-save lever to candidates flagged by analyze-extra-insn.

For each MISSING/UNUSED_ARG_SAVE or MISSING/OTHER candidate where the diff is a
single missing `sw aN, OFF(sp)`, try adding `(void)aN;` at function start or
removing existing `(void)aN;` (per the doc's "(void) prevents the spill" rule).

Usage:
  auto-fix-arg-save.py [--apply] [--funcs F1,F2,...]
"""
import argparse, json, os, re, struct, subprocess, sys, tempfile
from pathlib import Path

REPO = Path(__file__).parent.parent.resolve()
IDO = REPO.parent.parent / 'tools/ido-static-recomp/build/7.1/out/cc'
CFLAGS = ['-O2', '-G', '0', '-mips2', '-32', '-non_shared', '-Xcpluscomm', '-Wab,-r4300_mul']
INCLUDES = ['-I', str(REPO/'include'), '-I', str(REPO/'src')]


def get_disasm_insns(obj_path, sym):
    if not os.path.exists(obj_path): return None
    try:
        out = subprocess.check_output(['mips-linux-gnu-objdump', '-d', '-M', 'no-aliases',
                                       obj_path], text=True)
    except: return None
    m = re.search(rf'<{re.escape(sym)}>:\s*\n', out)
    if not m: return None
    body = out[m.end():]
    end = re.search(r'\n\s*\.\.\.|\n[0-9a-f]+\s+<', body)
    if end: body = body[:end.start()]
    insns = []
    for line in body.split('\n'):
        m = re.match(r'\s+([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)', line)
        if m:
            insns.append((int(m.group(1), 16), m.group(2), m.group(3).strip()))
    return insns


def find_single_arg_save_diff(built, expected):
    """Return (kind, arg_reg, offset) if the diff is a single missing/extra `sw aN, off(sp)`."""
    if not built or not expected: return None
    if abs(len(built) - len(expected)) != 1: return None
    # Walk both, find first divergence
    n = min(len(built), len(expected))
    i = 0
    while i < n and built[i][1] == expected[i][1]:
        i += 1
    if i >= n: return None
    longer = expected if len(expected) > len(built) else built
    extra = longer[i][2]
    # Check shift: does built[i] == expected[i+1] (or vice versa)?
    if len(expected) > len(built):
        if i+1 >= len(expected) or built[i][1] != expected[i+1][1]:
            return None
        kind = 'MISSING'
    else:
        if i+1 >= len(built) or expected[i][1] != built[i+1][1]:
            return None
        kind = 'EXTRA'
    # Parse `sw aN, OFF(sp)` from the extra insn
    m = re.match(r'sw\s+(a[0-3])[,\s]+(\d+)\(sp\)', extra)
    if not m: return None
    return (kind, m.group(1), int(m.group(2)))


def get_func_source(src_path, fname):
    """Return (text, start, end, sig_line_idx) for the function definition."""
    if not os.path.exists(src_path): return None
    text = open(src_path).read()
    lines = text.split('\n')
    for i, line in enumerate(lines):
        if re.match(rf'^[A-Za-z_][\w \*]*\b{re.escape(fname)}\s*\(', line):
            # Find matching closing brace
            depth = 0
            seen = False
            for k in range(i, len(lines)):
                depth += lines[k].count('{') - lines[k].count('}')
                if '{' in lines[k]: seen = True
                if seen and depth == 0:
                    return text, i, k, i
    return None


def has_void_cast(fn_text, arg):
    return re.search(rf'\(void\)\s*{re.escape(arg)}\s*;', fn_text) is not None


def try_add_void_cast(src_path, fname, arg):
    """Add `(void)arg;` at function start. Return new full file text or None."""
    info = get_func_source(src_path, fname)
    if not info: return None
    text, i, k, sig = info
    lines = text.split('\n')
    # Find opening brace line
    brace_line = None
    for j in range(i, k+1):
        if '{' in lines[j]:
            brace_line = j
            break
    if brace_line is None: return None
    # Insert (void)arg; right after the opening brace
    new_line = f'    (void){arg};'
    if has_void_cast('\n'.join(lines[i:k+1]), arg):
        return None  # already has it
    new_lines = lines[:brace_line+1] + [new_line] + lines[brace_line+1:]
    return '\n'.join(new_lines)


def try_remove_void_cast(src_path, fname, arg):
    """Remove existing `(void)arg;` from function body."""
    info = get_func_source(src_path, fname)
    if not info: return None
    text, i, k, sig = info
    lines = text.split('\n')
    if not has_void_cast('\n'.join(lines[i:k+1]), arg):
        return None
    new_lines = []
    pat = re.compile(rf'\(void\)\s*{re.escape(arg)}\s*;')
    for j, line in enumerate(lines):
        if i <= j <= k and pat.search(line):
            stripped = pat.sub('', line).strip()
            if not stripped:
                continue
            new_lines.append(pat.sub('', line))
        else:
            new_lines.append(line)
    return '\n'.join(new_lines)


def rebuild_and_compare(unit_path, fname):
    """Rebuild the non_matching .o, compare against expected. Return diff count."""
    src_path = str(REPO / f'{unit_path}.c')
    # touch + make
    subprocess.run(['touch', src_path])
    r = subprocess.run(['make', 'RUN_CC_CHECK=0', f'build/non_matching/{unit_path}.c.o'],
                      cwd=REPO, capture_output=True, timeout=120)
    if r.returncode != 0:
        return None
    nm_obj = str(REPO / f'build/non_matching/{unit_path}.c.o')
    ex_obj = str(REPO / f'expected/{unit_path}.c.o')
    nm = get_bytes_for(nm_obj, fname)
    ex = get_bytes_for(ex_obj, fname)
    if not nm or not ex: return None
    if nm == ex: return 0
    if len(nm) != len(ex): return -1
    diffs = sum(1 for i in range(0, len(nm), 4)
                if struct.unpack('>I', nm[i:i+4])[0] != struct.unpack('>I', ex[i:i+4])[0])
    return diffs


def get_bytes_for(obj_path, sym):
    if not os.path.exists(obj_path): return None
    try:
        out = subprocess.check_output(['mips-linux-gnu-objdump', '-t', obj_path], text=True)
    except: return None
    for line in out.split('\n'):
        if sym in line and '.text' in line:
            parts = line.split()
            addr = int(parts[0], 16)
            size = int(parts[-2], 16)
            raw = subprocess.check_output(['mips-linux-gnu-objcopy', '-O', 'binary',
                                          '-j', '.text', obj_path, '/dev/stdout'])
            return raw[addr:addr+size]
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--apply', action='store_true', help='actually write the change')
    ap.add_argument('--funcs', type=str, default='')
    args = ap.parse_args()

    subprocess.run(['objdiff-cli', 'report', 'generate', '-o', '/tmp/auto-rep.json'],
                   capture_output=True, cwd=REPO)
    r = json.load(open('/tmp/auto-rep.json'))

    explicit = set(args.funcs.split(',')) if args.funcs else set()

    print('Scanning EXTRA/MISSING single-insn-arg-save candidates...')
    for u in r['units']:
        unit = u['name']
        for fn in u.get('functions', []):
            fm = fn.get('fuzzy_match_percent', 100)
            sz = int(fn['size'])
            if fm == 100.0 or 'fuzzy_match_percent' not in fn: continue
            if explicit and fn['name'] not in explicit: continue
            if not explicit and not (85 <= fm < 100): continue
            if not explicit and sz > 250: continue
            name = fn['name']
            nm_obj = str(REPO / 'build/non_matching' / f'{unit}.c.o')
            ex_obj = str(REPO / 'expected' / f'{unit}.c.o')
            built = get_disasm_insns(nm_obj, name)
            expected = get_disasm_insns(ex_obj, name)
            diff = find_single_arg_save_diff(built, expected)
            if not diff: continue
            kind, arg, off = diff
            src_path = str(REPO / f'{unit}.c')
            if kind == 'MISSING':
                # Add (void)arg
                new_text = try_add_void_cast(src_path, name, arg)
                action = f'add (void){arg};'
            else:
                # Remove (void)arg
                new_text = try_remove_void_cast(src_path, name, arg)
                action = f'remove (void){arg};'
            if not new_text:
                print(f'  {name}: {kind} {arg} -- no source change possible')
                continue
            # Try the fix
            backup = open(src_path).read()
            open(src_path, 'w').write(new_text)
            d = rebuild_and_compare(unit, name)
            if d == 0:
                print(f'  ✓ MATCHED {name}: {action}')
                if args.apply:
                    print(f'    -> kept change in {src_path}')
                else:
                    open(src_path, 'w').write(backup)
                    print(f'    -> reverted (use --apply to keep)')
            else:
                open(src_path, 'w').write(backup)
                print(f'  ✗ {name}: {action} -> diffs={d}')


if __name__ == '__main__':
    main()
