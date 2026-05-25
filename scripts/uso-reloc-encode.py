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

STATUS: the encoder + the section round-trip are VALIDATED (15543/15543 entries on
bootup.uso byte-identical). The remaining pieces of the full fado-equivalent (a
focused-session refactor, NOT yet done) are:
  1. Build C with REAL symbols (the recovered call graph) instead of the collapsed
     gl_func_00000000/D_00000000 placeholders.
  2. Extract the compiler's ELF relocs (offset, symbol, type) per module.
  3. Map symbol-name -> Kyoto symIdx. NOTE: bootup_uso.symnames.json has 1672
     symIdx but only 1611 distinct names (61 collisions) -> name->symIdx is NOT 1:1;
     the C side must carry the symIdx (e.g. usosym_<N>), not rely on the name.
  4. encode() the section (this module) and splice it at the module's TextReloc
     location, REPLACING the current Makefile jal-baking approach (Makefile ~L108).
  5. Verify the rebuilt module is byte-identical to the ROM (code + reloc section).
This is a build-approach change (bake-jals -> generate-reloc-section), high blast
radius; do it on a branch, one module, verify, then scale.
"""
import argparse, struct, sys

SEC = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 13}
ELF_TYPE_TO_KIND = {4: 1, 6: 2, 5: 3}  # R_MIPS_26->1, LO16->2, HI16->3


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
