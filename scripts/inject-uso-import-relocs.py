#!/usr/bin/env python3
"""Phase-1 prototype of the USO reloc-symbolization migration (expected/ side).

Injects R_MIPS_26 / R_MIPS_HI16 / R_MIPS_LO16 relocations + UND symbols into
expected/ .o files for USO reloc sites that are still RELOC-BLIND (raw baked
words, no ELF reloc). Metadata-only ELF surgery: .text bytes are NEVER touched,
so this cannot change the ROM (expected/ is measurement-only anyway).

Background: the .s-level symbolization (uso-reloc-symbolize.py, already applied
to bootup_uso) covered module-INTERNAL reloc sites (D_/RO_/func_ targets, baked
nonzero imm -> %hi/%lo reloc form). The residual blind class is the ~4.6k
IMPORT sites (cross-module targets, e.g. kernel/game_libs): the USO ships them
imm==0 (resolved at load via the Sym table), the .s kept them as literal
`lui $rt, (0x0 >> 16)` / `jal 0`, so expected/.o has NO reloc there while the
C build side emits a reloc (to a blank D_00000000-family extern). This script
adds the missing expected-side reloc from the module's own TextReloc table.

Safety rules:
  - only sites whose in-place addend bits are ZERO are injected (pure metadata;
    nonzero-imm sites would need byte edits to be reloc-form -> out of scope).
  - only functions in --funcs allowlist (default: none = dry run listing).
  - sites already covered by an ELF reloc are skipped.

MEASURED RESULT (2026-08-23, phase-1 prototype, bootup_uso, 526 sites in the
86 sub-100 fns): NET-NEGATIVE — 15 fns moved, ALL down (-0.01..-0.21pp), zero
up; exact count and matched_code exactly unchanged. Identical deltas whether
the injected symbol names are the truthful import_<addr> or the base-side
blank D_00000000 — so the penalty is not reloc-name mismatch; objdiff 3.7
ALREADY gives full credit to the blind literal-0-vs-reloc-to-blank pairing,
and the tiny loss is a second-order fuzzy-alignment effect of making the
target instruction reloc-bearing. Conclusion: the C234/55A0/6808 "reloc-blind
cap" residuals are structural (regalloc/schedule), NOT reloc rendering; do NOT
apply this to expected/. Kept as the mechanism record + for any future objdiff
version whose reloc handling changes. See docs/MATCHING_WORKFLOW.md
("USO expected-side reloc injection is score-negative").

Usage:
  inject-uso-import-relocs.py --module 0xD9FE28 \
      --symnames scripts/emu-symdump/bootup_uso.symnames.json \
      --objs 'expected/src/bootup_uso/*.o' \
      [--funcs func_000055A0,func_0000C234,...] [--apply]
"""
import argparse, fnmatch, glob, json, re, struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
rfb = __import__("replace-function-body")
Elf = rfb.Elf

R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16 = 4, 5, 6
KIND2RTYPE = {1: R_MIPS_26, 2: R_MIPS_LO16, 3: R_MIPS_HI16}
SEC = {0:'Info',1:'Sym',2:'TextReloc',3:'DataReloc',4:'RoDataReloc',5:'Text',
       6:'Data',7:'RoData',8:'Bss',9:'EntrySym',10:'EOF',11:'End'}
FUNC_RE = re.compile(r'^func_([0-9A-Fa-f]{8})$')


def u32(d, o):
    return struct.unpack_from('>I', d, o)[0]


def walk_dir(d, mod):
    if u32(d, mod) != 0x12345678:
        return None
    o = mod + 0xC
    secs = {}
    for _ in range(64):
        typ, size = u32(d, o + 4), u32(d, o + 8)
        if typ in (10, 11) or typ not in SEC:
            break
        secs.setdefault(typ, (o + 12, size))
        o += 12 + (0 if typ == 8 else ((size + 3) & ~3))
    return secs


def build_relocmap(d, tr, trs):
    m = {}
    o = tr
    while o + 12 <= tr + trs:
        f1 = u32(d, o + 4)
        off = u32(d, o + 8)
        m[off] = (f1 >> 4, f1 & 7)
        o += 12
    return m


def inplace_addend(word, kind):
    if kind == 1:
        return (word & 0x3FFFFFF) << 2
    return word & 0xFFFF  # hi/lo 16-bit field


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--module', type=lambda x: int(x, 0), required=True)
    ap.add_argument('--rom', default='baserom.z64')
    ap.add_argument('--symnames', required=True)
    ap.add_argument('--objs', required=True, help='glob of expected .o files')
    ap.add_argument('--funcs', default='',
                    help='comma-separated allowlist of function symbols to touch')
    ap.add_argument('--apply', action='store_true')
    a = ap.parse_args()

    rom = open(a.rom, 'rb').read()
    secs = walk_dir(rom, a.module)
    if not secs or 2 not in secs:
        sys.exit(f'no TextReloc at module {a.module:#x}')
    relmap = build_relocmap(rom, *secs[2])
    symnames = json.load(open(a.symnames))
    allow = set(f for f in a.funcs.split(',') if f)

    grand = 0
    for path in sorted(glob.glob(a.objs)):
        elf = Elf(Path(path).read_bytes())
        try:
            text_idx = elf.find_section('.text')
            symtab_idx = elf.find_section('.symtab')
        except Exception:
            continue
        strtab_idx = elf.sections[symtab_idx][6]
        text_sec = elf.sections[text_idx]
        text_off_abs, text_size = text_sec[4], text_sec[5]
        text = bytes(elf.data[text_off_abs:text_off_abs + text_size])

        # defined func symbols named by module offset
        funcs = []  # (mod_off, st_value, size, name)
        for _, f in elf.iter_symtab(symtab_idx):
            name = elf.strtab_string(strtab_idx, f[0])
            m = FUNC_RE.match(name)
            if m and f[5] == text_idx and f[2] > 0:
                funcs.append((int(m.group(1), 16), f[1], f[2], name))
        if not funcs:
            continue

        # existing reloc offsets
        existing = set()
        if elf.has_section('.rel.text'):
            rel_idx = elf.find_section('.rel.text')
            rs = elf.sections[rel_idx]
            for o in range(rs[4], rs[4] + rs[5], rs[9]):
                existing.add(u32(elf.data, o))

        new_entries = []
        per_fn = {}
        for mod_off, (symidx, kind) in relmap.items():
            if kind not in KIND2RTYPE:
                continue
            for fo, sv, fsz, fname in funcs:
                if fo <= mod_off < fo + fsz:
                    break
            else:
                continue
            if allow and fname not in allow:
                continue
            toff = sv + (mod_off - fo)
            if toff in existing or toff + 4 > text_size:
                continue
            word = u32(text, toff)
            if inplace_addend(word, kind) != 0:
                continue  # would need byte edits; out of scope
            sname = symnames.get(str(symidx), f'usosym_{symidx}')
            symi = elf.find_or_add_global_undef_symbol(sname)
            new_entries.append((toff, (symi << 8) | KIND2RTYPE[kind]))
            per_fn[fname] = per_fn.get(fname, 0) + 1

        if not new_entries:
            continue
        new_entries.sort()
        if a.apply:
            elf.append_text_relocs(new_entries)
            elf.realign_sections()
            Path(path).write_bytes(bytes(elf.data))
        grand += len(new_entries)
        print(f'{path}: {"APPLIED" if a.apply else "DRY"} {len(new_entries)} relocs '
              f'in {len(per_fn)} fns')
        for k in sorted(per_fn):
            print(f'    {k}: {per_fn[k]}')
    print(f'total: {grand} relocs')


if __name__ == '__main__':
    main()
