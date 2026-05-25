#!/usr/bin/env python3
"""Kyoto-USO reloc-section ENCODER (the generate side of a fado-equivalent).

Background: OoT/MM/Yoshi match overlay functions by compiling C with REAL symbols
and running `fado`, which GENERATES the Zelda64 `.ovl` reloc section from the
compiler's ELF relocs; the full overlay (placeholder code + generated reloc
section) then matches the ROM byte-exact. 1080 uses a CUSTOM Kyoto USO format
(not Zelda64), so `fado`/spimdisasm don't apply. This module is the encoder half
of a Kyoto-format equivalent.

Kyoto TextReloc on-disk format (cracked + validated, see
project_1080_uso_spimdisasm_migration_todo): the module (magic 0x12345678) holds
inline sections [flag,type,size,data...]; the TextReloc section (type 2) is an
array of 12-byte big-endian entries:
    field0 = flag word (0x1; entry0 ORs in the 0x08000000 start-marker -> 0x08000001)
    field1 = (symIdx << 4) | kind     kind: 1=R_MIPS_26 (jal/j), 2=LO16, 3=HI16
    field2 = byte offset into the code (relative to code base = textdata+4)

ELF reloc type -> Kyoto kind (for the future build-side generator):
    R_MIPS_26 (4) -> 1 ; R_MIPS_LO16 (6) -> 2 ; R_MIPS_HI16 (5) -> 3

STATUS: the GENERATE-SIDE of the fado-equivalent is VALIDATED END-TO-END.
  - encode() + section round-trip: 15543/15543 bootup.uso entries byte-identical.
  - extract_elf_relocs() + the full pipeline: symbolize a .s with usosym_<N>
    (uso-reloc-symbolize.py, no --symnames) -> assemble (GNU as + asm-prelude,
    .set noreorder/noat, strip the `nonmatching`/`endlabel` splat lines) ->
    extract_elf_relocs(.o, func_base) -> (symIdx, kind, module_offset) reproduces
    the ROM's Kyoto entries EXACTLY (validated on bootup func_00000008:
    (73,HI16,0x14),(73,LO16,0x18),(74,R26,0x20) == ROM). So given the symbolized
    .s the generator regenerates the ROM reloc section.
The remaining pieces (the BUILD INTEGRATION = a focused-session, high-blast-radius
refactor, NOT done) are:
  A. For a whole module: run the above per .s, collect entries, sort by
     module_offset, encode() -> the module's full TextReloc section.
  B. Wire into the build: make C/.s use usosym_<N> (the recovered call graph),
     emit the generated reloc section, and REPLACE the Makefile jal-baking (~L108)
     -> the rebuilt module (code + generated relocs) is byte-identical to ROM.
  C. Real names: map usosym_<N> -> bootup_uso.symnames.json for episode display
     (game_libs uses the +0x1466C shim into bootup's reloc/sym space).
Do B on a branch, one module, verify the full build green + per-fn byte-exact, then
scale. NOTE objdiff CANNOT validate USO targets (it's fooled by jal-0 de-collision)
-- validate against the ROM reloc section + the reloc table, never objdiff.
"""
import argparse, struct, sys

SEC = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 13}
ELF_TYPE_TO_KIND = {4: 1, 6: 2, 5: 3}  # ELF type NUMBER -> kind (R_MIPS_26=4,LO16=6,HI16=5)
ELF_NAME_TO_KIND = {'R_MIPS_26': 1, 'R_MIPS_LO16': 2, 'R_MIPS_HI16': 3}  # objdump name -> kind


def u32(d, o):
    return struct.unpack_from('>I', d, o)[0]


def walk_dir(d, mod):
    """Return {type: (data_off, size)} for the module at offset `mod`."""
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


def encode(entries):
    """entries: list of (symIdx, kind, offset) in ROM order -> Kyoto section bytes.

    Entry 0 gets the 0x08000000 start-marker bit ORed into its flag word."""
    out = bytearray()
    for i, (symidx, kind, off) in enumerate(entries):
        flag = 0x1 | (0x08000000 if i == 0 else 0)
        out += struct.pack('>III', flag, (symidx << 4) | kind, off)
    return bytes(out)


ELF_RE = __import__('re').compile(r'([0-9a-f]+)\s+(R_MIPS_\w+)\s+(\S+)')


def extract_elf_relocs(objpath, func_base, objdump='mips-linux-gnu-objdump'):
    """Read R_MIPS relocs from an assembled .o (built from a usosym-symbolized .s)
    and return Kyoto entries (symIdx, kind, module_offset) for it.

    The .s must use `usosym_<N>` symbol names (uso-reloc-symbolize.py default, no
    --symnames) so symIdx is unambiguous (N == symIdx; real NAMES collide -- 61 of
    1672 -- so the name can't be the key). `func_base` is the function's module-
    relative byte offset (e.g. 0x8 for bootup func_00000008); module_offset =
    func_base + elf_reloc_offset. VALIDATED end-to-end on bootup func_00000008:
    symbolize -> as -> this -> (73,3,0x14),(73,2,0x18),(74,1,0x20) == ROM exactly."""
    import re as _re
    import subprocess
    out = subprocess.run([objdump, '-r', objpath], capture_output=True, text=True).stdout
    entries = []
    for line in out.splitlines():
        m = ELF_RE.match(line)
        if not m:
            continue
        off, typ, sym = int(m.group(1), 16), m.group(2), m.group(3)
        kind = ELF_NAME_TO_KIND.get(typ)
        if kind is None or not sym.startswith('usosym_'):
            continue
        entries.append((int(sym.split('_')[1]), kind, func_base + off))
    return entries


def decode(d, data, size):
    """Inverse of encode(): -> list of (symIdx, kind, offset)."""
    out = []
    o = data
    while o + 12 <= data + size:
        f1, f2 = u32(d, o + 4), u32(d, o + 8)
        out.append((f1 >> 4, f1 & 7, f2))
        o += 12
    return out


def selftest(rom, mod):
    d = open(rom, 'rb').read()
    secs = walk_dir(d, mod)
    if not secs or 2 not in secs:
        sys.exit(f'no TextReloc section at module {mod:#x}')
    data, size = secs[2]
    orig = d[data:data + size]
    entries = decode(d, data, size)
    rt = encode(entries)
    ok = rt == orig
    print(f'TextReloc @ {data:#x} size {size:#x} ({len(entries)} entries)')
    print(f'round-trip: {"BYTE-IDENTICAL (encoder valid)" if ok else "MISMATCH"}')
    return 0 if ok else 1


if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument('--selftest', action='store_true',
                    help='round-trip a ROM module TextReloc section (decode->encode==orig)')
    ap.add_argument('--rom', default='baserom.z64')
    ap.add_argument('--module', type=lambda x: int(x, 0), default=0xD9FE28,
                    help='ROM offset of the USO module (magic 0x12345678); bootup.uso=0xD9FE28')
    a = ap.parse_args()
    if a.selftest:
        sys.exit(selftest(a.rom, a.module))
    ap.print_help()
