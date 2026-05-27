#!/usr/bin/env python3
"""Automated lever-sweep: try documented levers on NM-wrap candidates, find matches.

Strategy:
  1. Enumerate NM-wrap functions with fuzzy_match < 100 (from report.json)
  2. For each, extract the C body
  3. Generate variants by applying documented levers
  4. Compile each variant via IDO toolchain
  5. Compare against expected/.o for byte-equality
  6. Report best variant and diff count

Usage:
  lever-sweep.py [--fuzzy-min FM] [--size-max SZ] [--limit N] [--funcs F1,F2,...]
  lever-sweep.py --funcs gl_func_00037FAC,gl_func_00066514

Output: per-function lines with best lever and diff count.
"""
import argparse, glob, json, os, re, subprocess, sys, tempfile
from pathlib import Path

REPO = Path(__file__).parent.parent.resolve()
IDO = REPO.parent.parent / 'tools/ido-static-recomp/build/7.1/out/cc'
CFLAGS = ['-O2', '-G', '0', '-mips2', '-32', '-non_shared', '-Xcpluscomm', '-Wab,-r4300_mul']
INCLUDES = ['-I', str(REPO/'include'), '-I', str(REPO/'src')]


def find_nm_block(src_text, fname):
    """Find the function definition inside a #ifdef NON_MATCHING ... #endif block.
    Returns (block_start, block_end, fn_start, fn_end, sig_line_text)."""
    # Find all #ifdef NON_MATCHING ... #endif blocks
    lines = src_text.split('\n')
    block_start = None
    for i, line in enumerate(lines):
        if line.strip() == '#ifdef NON_MATCHING':
            block_start = i
        elif line.strip() == '#endif' and block_start is not None:
            block_text = '\n'.join(lines[block_start:i+1])
            if re.search(rf'\b{re.escape(fname)}\s*\(', block_text):
                # Find the actual function definition
                for j in range(block_start, i):
                    if re.match(rf'^[A-Za-z_][\w \*]*\b{re.escape(fname)}\s*\(', lines[j]):
                        # Find matching closing brace
                        depth = 0
                        seen = False
                        for k in range(j, i):
                            depth += lines[k].count('{') - lines[k].count('}')
                            if '{' in lines[k]:
                                seen = True
                            if seen and depth == 0:
                                return (block_start, i, j, k, lines[j])
            block_start = None
    return None


def get_expected_bytes(unit_path, sym):
    """unit_path like 'src/game_libs/game_libs_post' -> read expected/<unit>.c.o."""
    obj = REPO / 'expected' / f'{unit_path}.c.o'
    if not obj.exists():
        return None
    try:
        out = subprocess.check_output(['mips-linux-gnu-objdump', '-t', str(obj)], text=True)
    except:
        return None
    for line in out.split('\n'):
        if sym in line and '.text' in line:
            parts = line.split()
            try:
                addr = int(parts[0], 16)
                size = int(parts[-2], 16)
                raw = subprocess.check_output([
                    'mips-linux-gnu-objcopy', '-O', 'binary', '-j', '.text',
                    str(obj), '/dev/stdout'])
                return raw[addr:addr+size]
            except:
                return None
    return None


def compile_test(c_src, fname):
    """Compile c_src to .o and extract fname's bytes. Returns (bytes, error_str)."""
    if not c_src.endswith('\n'):
        c_src += '\n'
    with tempfile.NamedTemporaryFile(mode='w', suffix='.c', delete=False) as f:
        f.write(c_src)
        cpath = f.name
    opath = cpath.replace('.c', '.o')
    try:
        r = subprocess.run([str(IDO), '-c'] + CFLAGS + INCLUDES +
                          ['-DNON_MATCHING', '-o', opath, cpath],
                          capture_output=True, text=True, timeout=30)
        # IDO emits warnings on stderr but returns 0 if compile succeeds.
        # Check the .o was actually produced.
        if not os.path.exists(opath) or os.path.getsize(opath) == 0:
            return None, r.stderr[:200]
        out = subprocess.check_output(['mips-linux-gnu-objdump', '-t', opath], text=True)
        for line in out.split('\n'):
            if fname in line and '.text' in line:
                parts = line.split()
                addr = int(parts[0], 16)
                size = int(parts[-2], 16)
                raw = subprocess.check_output([
                    'mips-linux-gnu-objcopy', '-O', 'binary', '-j', '.text',
                    opath, '/dev/stdout'])
                return raw[addr:addr+size], None
        return None, 'symbol not found'
    finally:
        for p in (cpath, opath):
            if os.path.exists(p): os.unlink(p)


def count_diffs(b1, b2):
    if not b1 or not b2: return 999
    if len(b1) != len(b2): return 999
    import struct
    return sum(1 for i in range(0, len(b1), 4)
               if struct.unpack('>I', b1[i:i+4])[0]
                  != struct.unpack('>I', b2[i:i+4])[0])


def apply_lever_drop_fresh_local(fn_body):
    """Lever: 'T <name> = a0;' as first stmt -> reuse a0 throughout."""
    m = re.search(r'^([\w \*]*\b\w+_func_\w+|\b\w+)\s*\(([^)]*)\)\s*\{(.*)\}\s*$',
                  fn_body, re.DOTALL)
    if not m: return None
    sig = m.group(0)
    # find "T name = a0;" pattern
    inner = m.group(3)
    var_m = re.search(r'^\s*(?:int|void|char|float|register\s+\w+)\s*\*?\s*(\w+)\s*=\s*a0\s*;',
                      inner, re.MULTILINE)
    if not var_m: return None
    var = var_m.group(1)
    if var == 'a0': return None
    # Remove the declaration, replace usages of var with a0
    new_inner = inner.replace(var_m.group(0), '', 1)
    # Replace var as a standalone identifier (word boundary)
    new_inner = re.sub(rf'\b{re.escape(var)}\b', 'a0', new_inner)
    return fn_body[:m.start(3)] + new_inner + fn_body[m.end(3):]


def apply_lever_drop_extra_param(fn_body):
    """Lever: '(int a0, int a1, ...)' with 'a1 = a0;' first stmt -> drop a1 param."""
    m = re.search(r'(\w+_func_\w+|\w+)\s*\(([^)]*)\)\s*\{(.*?)^\}', fn_body, re.DOTALL | re.MULTILINE)
    if not m: return None
    name = m.group(1)
    params = m.group(2)
    body = m.group(3)
    # check first stmt is "aN = a0;"
    first = re.search(r'\s*(\w+)\s*=\s*a0\s*;', body)
    if not first: return None
    extra = first.group(1)
    if not re.match(r'a[1-3]$', extra): return None
    # Drop the extra param from params list
    param_list = [p.strip() for p in params.split(',')]
    new_params = [p for p in param_list if not re.search(rf'\b{re.escape(extra)}\s*$', p)]
    if len(new_params) == len(param_list): return None
    # Remove the assignment + replace extra with a0
    new_body = body.replace(first.group(0), '', 1)
    new_body = re.sub(rf'\b{re.escape(extra)}\b', 'a0', new_body)
    full = fn_body[:m.start(2)] + ', '.join(new_params) + ')' + ' {' + new_body + '}'
    # Reconstruct (rough)
    sig_end = fn_body.find('{', m.start())
    new_sig = re.sub(rf'\(\s*{re.escape(params)}\s*\)', '(' + ', '.join(new_params) + ')',
                     fn_body[:sig_end])
    return new_sig + ' {' + new_body + '}'


def apply_lever_strip_register_kw(fn_body):
    """Remove 'register ' qualifiers from local decls."""
    new = re.sub(r'\bregister\s+', '', fn_body)
    if new == fn_body: return None
    return new


def apply_lever_add_register_kw(fn_body):
    """Add 'register' to the first non-register local in the function body."""
    m = re.search(r'\{[^\n]*\n(\s*)(int|char|void|float|s32|s16|u32|u16)\s+(\*?\s*\w+\s*;)',
                  fn_body)
    if not m: return None
    ws, typ, rest = m.groups()
    new = fn_body[:m.start()] + m.group(0).replace(f'{ws}{typ} {rest}', f'{ws}register {typ} {rest}', 1)
    if new == fn_body: return None
    return new


def apply_lever_swap_first_two_decls(fn_body):
    """Swap the order of first two local declarations."""
    m = re.search(r'(\{[^\n]*\n)((?:\s*(?:int|char|void|float|s\d+|u\d+)\s*\*?\s*\w+(?:\s*=\s*[^;]*)?\s*;\s*\n){2})',
                  fn_body)
    if not m: return None
    decls = re.findall(r'(\s*(?:int|char|void|float|s\d+|u\d+)\s*\*?\s*\w+(?:\s*=\s*[^;]*)?\s*;\s*\n)',
                       m.group(2))
    if len(decls) < 2: return None
    new_decls = decls[1] + decls[0] + ''.join(decls[2:])
    new = fn_body[:m.start(2)] + new_decls + fn_body[m.end(2):]
    if new == fn_body: return None
    return new


def apply_lever_volatile_arg(fn_body):
    """Add volatile read of first arg at function start."""
    # Find first param name
    m = re.match(r'.*?\(([^)]*?)\)\s*\{', fn_body, re.DOTALL)
    if not m: return None
    params = m.group(1).strip().split(',')
    if not params or '*' not in params[0] or not params[0].strip(): return None
    # Skip if already has volatile
    if 'volatile' in fn_body[m.end():m.end()+200]: return None
    body_start = m.end()
    # Get first identifier as param name
    pm = re.search(r'\*?\s*(\w+)\s*$', params[0])
    if not pm: return None
    pname = pm.group(1)
    inject = f'\n    (void)*(volatile char *){pname};\n'
    return fn_body[:body_start] + inject + fn_body[body_start:]


LEVERS = [
    ('drop_fresh_local', apply_lever_drop_fresh_local),
    ('drop_extra_param', apply_lever_drop_extra_param),
    ('strip_register_kw', apply_lever_strip_register_kw),
    ('add_register_kw', apply_lever_add_register_kw),
    ('swap_first_two_decls', apply_lever_swap_first_two_decls),
]


def sweep_function(fname, fuzzy_pct, unit_path):
    """Try each lever on the function, report results."""
    # Find source file
    src_file = None
    src_text = None
    for p in glob.glob(str(REPO/'src/**/*.c'), recursive=True):
        text = open(p).read()
        if find_nm_block(text, fname):
            src_file = p
            src_text = text
            break
    if not src_file:
        return f'NOFILE {fname}'

    # Extract NM block
    block = find_nm_block(src_text, fname)
    if not block:
        return f'NOBLOCK {fname}'
    bs, be, fs, fe, sig_line = block
    fn_body = '\n'.join(src_text.split('\n')[fs:fe+1])

    # Get expected bytes
    expected = get_expected_bytes(unit_path, fname)
    if not expected:
        return f'NOEXP {fname}'

    # Extract extern decls / typedefs immediately preceding the NM block
    lines = src_text.split('\n')
    preamble = []
    # Walk backward from block start, collect extern/typedef/typedef-struct lines
    for j in range(bs-1, max(0, bs-30), -1):
        l = lines[j].strip()
        if l.startswith(('extern ', 'typedef ', 'struct ', '/*', ' *', '*/')) or l == '':
            preamble.insert(0, lines[j])
        elif l.startswith('}') and 'struct' in '\n'.join(preamble[:3] if preamble else ['']):
            preamble.insert(0, lines[j])
        else:
            break
    headers = '\n'.join(preamble)
    # Strip preprocessor directives that won't work standalone
    headers = re.sub(r'#include.*', '', headers)
    headers = re.sub(r'INCLUDE_ASM\([^)]*\);', '', headers)
    # Add minimal stubs
    stub = '''
typedef int s32; typedef unsigned int u32; typedef short s16; typedef unsigned short u16;
typedef char s8; typedef unsigned char u8; typedef float f32; typedef double f64;
#ifndef NULL
#define NULL ((void*)0)
#endif
extern char D_00000000;
extern int gl_func_00000000();
'''

    # Baseline: compile current body
    test_c = stub + headers + '\n' + fn_body
    base_bytes, err = compile_test(test_c, fname)
    if err:
        return f'NOCOMPILE {fname}: {err[:80]}'
    base_diffs = count_diffs(base_bytes, expected)

    # Try each lever
    results = [('baseline', base_diffs)]
    for lname, lfn in LEVERS:
        variant = lfn(fn_body)
        if variant is None or variant == fn_body:
            continue
        test_c = stub + headers + '\n' + variant
        var_bytes, err = compile_test(test_c, fname)
        if err: continue
        d = count_diffs(var_bytes, expected)
        results.append((lname, d))

    best = min(results, key=lambda x: x[1])
    return f'  {fname:42}  base={base_diffs:3}  best={best[0]:20}={best[1]:3}  fuzzy={fuzzy_pct:.1f}'


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--fuzzy-min', type=float, default=80.0)
    ap.add_argument('--fuzzy-max', type=float, default=100.0)
    ap.add_argument('--size-max', type=int, default=300)
    ap.add_argument('--limit', type=int, default=20)
    ap.add_argument('--funcs', type=str, default='')
    args = ap.parse_args()

    # Generate fresh report
    print('Generating fresh report...', file=sys.stderr)
    subprocess.run(['objdiff-cli', 'report', 'generate', '-o', '/tmp/sweep-report.json'],
                   capture_output=True, cwd=REPO)
    r = json.load(open('/tmp/sweep-report.json'))

    targets = []
    explicit = set(args.funcs.split(',')) if args.funcs else set()
    for u in r['units']:
        for fn in u.get('functions', []):
            name = fn['name']
            fm = fn.get('fuzzy_match_percent', 100)
            sz = int(fn['size'])
            if explicit:
                if name in explicit: targets.append((fm, sz, name, u['name']))
            else:
                if args.fuzzy_min <= fm < args.fuzzy_max and sz <= args.size_max:
                    targets.append((fm, sz, name, u['name']))

    targets.sort(key=lambda x: (-x[0], x[1]))
    if not explicit:
        targets = targets[:args.limit]

    print(f'Testing {len(targets)} candidates...', file=sys.stderr)
    for fm, sz, name, unit in targets:
        try:
            print(sweep_function(name, fm, unit))
        except Exception as e:
            print(f'  ERROR {name}: {e}')


if __name__ == '__main__':
    main()
