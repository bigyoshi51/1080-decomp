#!/usr/bin/env python3
"""Kyoto USO 'is this orphan a real entry?' oracle: walk a module's sections from its INNER
header (magic 0x12345678; the FILE wrapper's magic is 0x28 earlier and names the .uso), dump
the Sym exports and every TextReloc/DataReloc/RoDataReloc reference to the given text offsets.

Layout (verified 2026-09-05 on h2hproc/timproc/trkproc/bootup): module header = [magic, 8,
size, flag]; then sections [type, size, flag] + data (types 1=Sym 2=TextReloc 3=DataReloc
4=RoDataReloc 5=Text 6=Data 7=RoData 9=EntrySym 11=end). flag 0x1001xxxx = Yay0-compressed
section (crunch64 decompress; the next header follows the compressed bytes and may be
byte-misaligned); bootup's Text carries flag 0x2000xxxx. Sym entry = [tag, value, hash]
(tag 0x0052xxxx = text; value 0 = import). Reloc entry = [(symIdx<<4)|kind, offset, flag],
kind 1=R_MIPS_26 2=LO16 3=HI16 4=word.
Offsets: uncompressed module whose splat segment starts at the section FLAG word (h2hproc,
arcproc): splat = section + 4. Yay0 code blocks (timproc b1 = timproc.uso @0x5AF114, b3 =
trkproc.uso @0x5B3DE2): splat == section offset. game_libs = bootup.uso's Text (inner
header 0xD9FE28, Text data 0xDD0A6C): section offset = ROM - 0xDD0A6C.
Verdict rule: orphan exported (or referenced) and successor not = hoisted head -> merge.
Usage: uso-sym-oracle.py <rom> <inner_header_rom_off> <sec_off> [<sec_off> ...]
"""
import struct, sys
import crunch64
rom = open(sys.argv[1], 'rb').read()
mod = int(sys.argv[2], 0)
want = [int(x, 0) for x in sys.argv[3:]]
u32 = lambda o: struct.unpack_from('>I', rom, o)[0]
assert u32(mod) == 0x12345678, hex(u32(mod))
TYPES = {1:'Sym',2:'TextReloc',3:'DataReloc',4:'RoDataReloc',5:'Text',6:'Data',7:'RoData',9:'EntrySym',11:'End'}
o = mod + 16; secs = {}
while o < len(rom) - 12:
    found = False
    for k in range(4):
        t = u32(o + k); fl = u32(o + k + 8)
        if t in TYPES and (fl >> 16) in (0x1000, 0x1001, 0x0800, 0x2000, 0x2001):
            o += k; found = True; break
    if not found: break
    t = u32(o); size = u32(o + 4); flag = u32(o + 8); d0 = o + 12
    if flag & 0x10000:
        data = crunch64.yay0.decompress(rom[d0:d0 + size + 0x40000])
        nxt = d0 + len(crunch64.yay0.compress(data))
    else:
        data = rom[d0:d0 + size]; nxt = d0 + size
    print(f'sec {TYPES[t]:12s} hdr@0x{o:X} data@0x{d0:X} usize=0x{len(data):X} flag=0x{flag:X}')
    secs.setdefault(TYPES[t], data)
    o = nxt
    if t in (9, 11) and 'Sym' in secs: break
sym = secs['Sym']; syms = [struct.unpack_from('>III', sym, i * 12) for i in range(len(sym) // 12)]
print('text exports:', sorted(hex(v) for tag, v, h in syms if v and (tag >> 16) & 0xFF == 0x52))
for w in want:
    print(f'0x{w:X}: export sym idx {[i for i, (t, v, h) in enumerate(syms) if v == w and (t >> 16) & 0xFF == 0x52]}')
    for name in ('TextReloc', 'DataReloc', 'RoDataReloc'):
        d = secs.get(name, b'')
        for i in range(len(d) // 12):
            f1, off, f0 = struct.unpack_from('>III', d, i * 12); si = f1 >> 4; kind = f1 & 0xF
            if si < len(syms) and syms[si][1] == w and (syms[si][0] >> 16) & 0xFF == 0x52:
                print(f'   REF {name} @0x{off:X} kind={kind} -> sym{si}')
            if name == 'TextReloc' and w <= off < w + 8:
                print(f'   reloc-at 0x{off:X} sym{si} kind={kind} (symval 0x{syms[si][1]:X})')
