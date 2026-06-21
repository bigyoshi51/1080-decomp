"""twinlib.py — shared helpers for masked-twin work."""
import os, re, subprocess, struct, glob, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OBJDUMP = "mips-linux-gnu-objdump"
OBJCOPY = "mips-linux-gnu-objcopy"

def text_funcs(opath):
    """ {name: (addr,size) } for global F .text symbols, excluding .NON_MATCHING """
    try:
        syms = subprocess.check_output([OBJDUMP, '-t', opath], stderr=subprocess.DEVNULL).decode()
    except Exception:
        return {}
    d = {}
    for l in syms.splitlines():
        m = re.match(r'([0-9a-f]+)\s+\S+\s+F\s+\.text\s+([0-9a-f]+)\s+(\S+)$', l)
        if m and not m.group(3).endswith('.NON_MATCHING'):
            d[m.group(3)] = (int(m.group(1), 16), int(m.group(2), 16))
    return d

def text_bytes(opath):
    tf = tempfile.NamedTemporaryFile(suffix='.bin', delete=False); tf.close()
    subprocess.run([OBJCOPY, '-O', 'binary', '--only-section=.text', opath, tf.name],
                   stderr=subprocess.DEVNULL)
    data = open(tf.name, 'rb').read(); os.unlink(tf.name)
    return data

def reloc_offsets(opath):
    """ {offset: (type, symbol)} for .text relocs """
    try:
        out = subprocess.check_output([OBJDUMP, '-r', opath], stderr=subprocess.DEVNULL).decode()
    except Exception:
        return {}
    d = {}
    cur = None
    for l in out.splitlines():
        if l.startswith('RELOCATION RECORDS FOR'):
            cur = '.text' in l
            continue
        if cur:
            m = re.match(r'([0-9a-f]+)\s+(\S+)\s+(\S+)', l)
            if m:
                d[int(m.group(1), 16)] = (m.group(2), m.group(3))
    return d

def funcs_words(opath):
    """ {name: [words]} """
    fs = text_funcs(opath)
    if not fs: return {}
    data = text_bytes(opath)
    out = {}
    for nm, (a, sz) in fs.items():
        chunk = data[a:a+sz]
        if len(chunk) < sz: continue
        out[nm] = list(struct.unpack('>%dI' % (sz // 4), chunk[:sz // 4 * 4]))
    return out

def reloc_masked_words(opath, name):
    """Return (words, reloc_at_index_set) for one function: words with reloc'd
    instruction immediates zeroed, plus the relative reloc index set + symbols."""
    fs = text_funcs(opath)
    if name not in fs: return None
    a, sz = fs[name]
    data = text_bytes(opath)
    chunk = data[a:a+sz]
    words = list(struct.unpack('>%dI' % (sz // 4), chunk[:sz // 4 * 4]))
    relocs = reloc_offsets(opath)
    rel = {}   # rel_index -> (type, sym)
    masked = list(words)
    for off, (typ, sym) in relocs.items():
        if a <= off < a + sz:
            idx = (off - a) // 4
            rel[idx] = (typ, sym)
            # mask immediate (low 16) for HI16/LO16/loads; target for J/JAL(26)
            if typ == 'R_MIPS_26':
                masked[idx] = words[idx] & 0xFC000000
            else:
                masked[idx] = words[idx] & 0xFFFF0000
    return words, masked, rel
