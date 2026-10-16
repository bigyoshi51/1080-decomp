#!/usr/bin/env python3
"""Rebase in-place addends of `.text`-section-symbol relocations after a
post-compile tool moved code inside .text.

replace-function-body.py and inject-suffix-bytes.py splice bytes into an
already-assembled .o and shift every later symbol and every later r_offset.
A relocation against the .text SECTION symbol, though, keeps its target in
the in-place addend (REL format), which the assembler computed for the
pre-splice layout: a `jal` to a `static` function (R_MIPS_26 .text+X), a
switch jumptable entry (R_MIPS_32 .text+X in .rel.rodata) or `&static_fn`
(HI16/LO16 .text+X). If X lies at or past the splice point, the target moved
by `delta`, so X must move too, or the object points at the wrong code.

This is relocation bookkeeping -- exactly what `ld -r` does to the same
addends when it moves an input section -- not instruction selection: the
value is computed from the object's own layout, never chosen to fit a
target. Global-symbol relocations need nothing (their symbol value moved).

Usage (library): rebase_text_addends(data, boundary, delta,
                                     forbid_inside=(start, limit) | None)
`data` is the whole ELF image (bytearray, modified in place), AFTER the
splice. `boundary` and `forbid_inside` are in PRE-splice .text offsets.
"""
import struct

SECT_HDR_FMT = ">IIIIIIIIII"
SYM_FMT = ">IIIBBH"
SHT_REL = 9
STT_SECTION = 3
R_MIPS_32 = 2
R_MIPS_26 = 4
R_MIPS_HI16 = 5
R_MIPS_LO16 = 6


def _sext16(x):
    x &= 0xFFFF
    return x - 0x10000 if x & 0x8000 else x


def rebase_text_addends(data, boundary, delta, forbid_inside=None):
    if not delta:
        return 0
    e_shoff, = struct.unpack(">I", data[0x20:0x24])
    e_shentsize, e_shnum, e_shstrndx = struct.unpack(">HHH", data[0x2E:0x34])
    secs = [struct.unpack(SECT_HDR_FMT, data[e_shoff + i * e_shentsize:
                                             e_shoff + (i + 1) * e_shentsize])
            for i in range(e_shnum)]
    shstr = secs[e_shstrndx]

    def name(i):
        off = shstr[4] + secs[i][0]
        return bytes(data[off:data.index(b"\x00", off)]).decode("ascii")

    text_idx = next((i for i in range(e_shnum) if name(i) == ".text"), None)
    if text_idx is None:
        return 0
    symtab_idx = next(i for i in range(e_shnum) if secs[i][1] == 2)
    st = secs[symtab_idx]
    text_sec_syms = set()
    for i in range(st[5] // st[9]):
        f = struct.unpack(SYM_FMT, data[st[4] + i * st[9]:st[4] + (i + 1) * st[9]])
        if (f[3] & 0xF) == STT_SECTION and f[5] == text_idx:
            text_sec_syms.add(i)
    if not text_sec_syms:
        return 0

    def moved(x, where):
        if forbid_inside and forbid_inside[0] < x < forbid_inside[1]:
            raise SystemExit(f"elf_text_addends: reloc at {where} targets "
                             f".text+{x:#x}, inside the spliced range")
        return x >= boundary

    changed = 0
    for ri in range(e_shnum):
        rs = secs[ri]
        if rs[1] != SHT_REL:
            continue
        tgt = secs[rs[7]]  # sh_info = section the relocs apply to
        base = tgt[4]
        pending_hi = []
        for k in range(rs[5] // rs[9]):
            r_off, r_info = struct.unpack(">II", data[rs[4] + k * rs[9]:rs[4] + (k + 1) * rs[9]])
            rtype, sym = r_info & 0xFF, r_info >> 8
            if sym not in text_sec_syms:
                if rtype == R_MIPS_LO16:
                    pending_hi = []
                continue
            p = base + r_off
            w, = struct.unpack(">I", data[p:p + 4])
            where = f"{name(rs[7])}+{r_off:#x}"
            if rtype == R_MIPS_32:
                if moved(w, where):
                    data[p:p + 4] = struct.pack(">I", (w + delta) & 0xFFFFFFFF)
                    changed += 1
            elif rtype == R_MIPS_26:
                x = (w & 0x3FFFFFF) << 2
                if moved(x, where):
                    x += delta
                    data[p:p + 4] = struct.pack(">I", (w & 0xFC000000) | ((x >> 2) & 0x3FFFFFF))
                    changed += 1
            elif rtype == R_MIPS_HI16:
                pending_hi.append(p)
            elif rtype == R_MIPS_LO16:
                lo = _sext16(w)
                his = pending_hi
                pending_hi = []
                hi_w = struct.unpack(">I", data[his[0]:his[0] + 4])[0] if his else 0
                x = ((hi_w & 0xFFFF) << 16) + lo
                if moved(x, where):
                    x += delta
                    for hp in his:
                        hw, = struct.unpack(">I", data[hp:hp + 4])
                        data[hp:hp + 4] = struct.pack(">I", (hw & 0xFFFF0000) | (((x + 0x8000) >> 16) & 0xFFFF))
                    data[p:p + 4] = struct.pack(">I", (w & 0xFFFF0000) | (x & 0xFFFF))
                    changed += 1
            else:
                raise SystemExit(f"elf_text_addends: unhandled reloc type {rtype} "
                                 f"against .text at {where}")
    return changed
