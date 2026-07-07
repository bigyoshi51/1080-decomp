#!/usr/bin/env python3
"""Replace one function body in a MIPS ELF .o with bytes from a donor .o.

This is for compressed USO blocks that are extracted from a single .o, where
ordinary file-splitting would put an -O0 function in the wrong text stream.
The destination object still compiles the C body, then this script swaps just
that function's bytes with a verified donor body and shifts later symbols and
relocations if the size changes.
"""
import argparse
import struct
from pathlib import Path

ELF_HDR_FMT = ">16sHHIIIIIHHHHHH"
SECT_HDR_FMT = ">IIIIIIIIII"
SYM_FMT = ">IIIBBH"
REL_FMT = ">II"


class Elf:
    def __init__(self, data: bytes):
        self.data = bytearray(data)
        self._parse_header()
        self._parse_sections()

    def _parse_header(self):
        h = struct.unpack(ELF_HDR_FMT, self.data[:struct.calcsize(ELF_HDR_FMT)])
        (self.e_ident, self.e_type, self.e_machine, self.e_version,
         self.e_entry, self.e_phoff, self.e_shoff, self.e_flags,
         self.e_ehsize, self.e_phentsize, self.e_phnum,
         self.e_shentsize, self.e_shnum, self.e_shstrndx) = h
        if self.e_ident[:4] != b"\x7fELF" or self.e_ident[4] != 1 or self.e_ident[5] != 2:
            raise ValueError("expected big-endian ELF32")

    def _parse_sections(self):
        self.sections = []
        for i in range(self.e_shnum):
            off = self.e_shoff + i * self.e_shentsize
            self.sections.append(list(struct.unpack(SECT_HDR_FMT, self.data[off:off + self.e_shentsize])))
        shstr = self.sections[self.e_shstrndx]
        self.shstrtab = bytes(self.data[shstr[4]:shstr[4] + shstr[5]])

    def section_name(self, idx):
        name_off = self.sections[idx][0]
        end = self.shstrtab.index(b"\x00", name_off)
        return self.shstrtab[name_off:end].decode("ascii")

    def find_section(self, name):
        for i in range(self.e_shnum):
            if self.section_name(i) == name:
                return i
        raise KeyError(name)

    def has_section(self, name):
        try:
            self.find_section(name)
            return True
        except KeyError:
            return False

    def write_section_header(self, idx):
        off = self.e_shoff + idx * self.e_shentsize
        self.data[off:off + self.e_shentsize] = struct.pack(SECT_HDR_FMT, *self.sections[idx])

    def write_elf_header(self):
        self.data[:struct.calcsize(ELF_HDR_FMT)] = struct.pack(
            ELF_HDR_FMT,
            self.e_ident, self.e_type, self.e_machine, self.e_version,
            self.e_entry, self.e_phoff, self.e_shoff, self.e_flags,
            self.e_ehsize, self.e_phentsize, self.e_phnum,
            self.e_shentsize, self.e_shnum, self.e_shstrndx)

    def iter_symtab(self, symtab_idx):
        sec = self.sections[symtab_idx]
        off, size, ent = sec[4], sec[5], sec[9]
        for i in range(size // ent):
            entry_off = off + i * ent
            yield i, list(struct.unpack(SYM_FMT, self.data[entry_off:entry_off + ent]))

    def write_sym(self, symtab_idx, sym_idx, fields):
        sec = self.sections[symtab_idx]
        off = sec[4] + sym_idx * sec[9]
        self.data[off:off + sec[9]] = struct.pack(SYM_FMT, *fields)

    def strtab_string(self, strtab_idx, name_off):
        sec = self.sections[strtab_idx]
        off = sec[4] + name_off
        end = self.data.index(b"\x00", off)
        return bytes(self.data[off:end]).decode("ascii")

    def find_symbol(self, name):
        symtab_idx = self.find_section(".symtab")
        strtab_idx = self.sections[symtab_idx][6]
        text_idx = self.find_section(".text")
        for sym_idx, fields in self.iter_symtab(symtab_idx):
            if fields[5] == text_idx and self.strtab_string(strtab_idx, fields[0]) == name:
                return sym_idx, fields, symtab_idx
        raise KeyError(f"symbol {name} not found")

    def text_bytes_for(self, name):
        _, fields, _ = self.find_symbol(name)
        text = self.sections[self.find_section(".text")]
        start = text[4] + fields[1]
        return bytes(self.data[start:start + fields[2]])

    def replace_text_range(self, old_start, old_size, payload):
        text_idx = self.find_section(".text")
        text = self.sections[text_idx]
        absolute = text[4] + old_start
        old_end = absolute + old_size
        self.data[absolute:old_end] = payload
        delta = len(payload) - old_size
        text[5] += delta
        if delta:
            for i, sec in enumerate(self.sections):
                if i != text_idx and sec[4] >= old_end:
                    sec[4] += delta
            if self.e_shoff >= old_end:
                self.e_shoff += delta
        for i in range(self.e_shnum):
            self.write_section_header(i)
        self.write_elf_header()
        return delta

    def fix_symbols(self, func_name, old_start, old_size, new_size, delta):
        symtab_idx = self.find_section(".symtab")
        text_idx = self.find_section(".text")
        old_limit = old_start + old_size
        for sym_idx, fields in self.iter_symtab(symtab_idx):
            if fields[5] != text_idx:
                continue
            name = self.strtab_string(self.sections[symtab_idx][6], fields[0])
            if name == func_name:
                fields[2] = new_size
                self.write_sym(symtab_idx, sym_idx, fields)
            elif delta and fields[1] >= old_limit:
                fields[1] += delta
                self.write_sym(symtab_idx, sym_idx, fields)
            elif old_start < fields[1] < old_limit:
                raise RuntimeError(f"{name} lies inside replaced body")

    def fix_relocations(self, old_start, old_size, delta):
        if not self.has_section(".rel.text"):
            return
        rel_idx = self.find_section(".rel.text")
        sec = self.sections[rel_idx]
        off, size, ent = sec[4], sec[5], sec[9]
        old_limit = old_start + old_size
        kept = bytearray()
        dropped = 0
        for i in range(size // ent):
            entry_off = off + i * ent
            r_off, r_info = struct.unpack(REL_FMT, self.data[entry_off:entry_off + ent])
            if old_start <= r_off < old_limit:
                dropped += 1
                continue
            if delta and r_off >= old_limit:
                r_off += delta
            kept += struct.pack(REL_FMT, r_off, r_info)
        # Always write back `kept` when offsets may have changed. If nothing was
        # dropped the length is unchanged (in-place overwrite of shifted r_off
        # values); the earlier code only wrote back when dropped>0, which silently
        # discarded the +delta shift for reloc-free donor bodies (dropped==0) and
        # left downstream relocs pointing at the pre-shift byte positions.
        if dropped or delta:
            self.data[off:off + len(kept)] = kept
        if dropped:
            del self.data[off + len(kept):off + size]
            shrink = dropped * ent
            sec[5] -= shrink
            for i, other in enumerate(self.sections):
                if i != rel_idx and other[4] > off:
                    other[4] -= shrink
            if self.e_shoff > off:
                self.e_shoff -= shrink
        self.write_section_header(rel_idx)
        for i in range(self.e_shnum):
            self.write_section_header(i)
        self.write_elf_header()

    # ---- section-growth + symbol-import helpers (for import_donor_relocs) ----
    def _grow_section(self, sec_idx, extra_bytes):
        """Insert extra_bytes of 0 at the end of section sec_idx. Shift later
        sections + e_shoff. Returns the byte offset within self.data where the
        new (zeroed) range starts (i.e. old end of the section)."""
        sec = self.sections[sec_idx]
        old_end = sec[4] + sec[5]
        self.data[old_end:old_end] = b"\x00" * extra_bytes
        sec[5] += extra_bytes
        for i, other in enumerate(self.sections):
            if i != sec_idx and other[4] >= old_end:
                other[4] += extra_bytes
        if self.e_shoff >= old_end:
            self.e_shoff += extra_bytes
        for i in range(self.e_shnum):
            self.write_section_header(i)
        self.write_elf_header()
        return old_end

    def realign_sections(self):
        """Final pass: ensure every section's sh_offset is a multiple of its
        sh_addralign by inserting zero padding before it (shifting that section
        and all later ones, plus e_shoff). Size-changing splices grow .text by
        a non-16-multiple, which `replace_text_range` propagates as a flat
        offset shift — leaving later sections (e.g. align-16 .data/.rodata) at
        non-aligned offsets. objdump tolerates this but objdiff's stricter
        `object`-crate parser rejects the whole object, aborting `report
        generate`. This pass restores alignment; it is idempotent (no-op on
        already-aligned objects), invisible to the linker (inter-section gaps
        are ignored), and never touches section *content* (.text bytes are
        unchanged, so matched-ness is preserved). See
        docs/MATCHING_WORKFLOW.md#feedback-replace-func-body-o0-donor."""
        # Process in ascending file-offset order so each insertion's +pad is
        # already reflected in later sections' offsets when we reach them.
        for i in sorted(range(self.e_shnum), key=lambda j: self.sections[j][4]):
            sec = self.sections[i]
            sh_type, sh_off, align = sec[1], sec[4], sec[8]
            if sh_type in (0, 8) or align <= 1:  # SHT_NULL / SHT_NOBITS / no align
                continue
            rem = sh_off % align
            if rem == 0:
                continue
            pad = align - rem
            self.data[sh_off:sh_off] = b"\x00" * pad
            for other in self.sections:
                if other[4] >= sh_off:
                    other[4] += pad
            if self.e_shoff >= sh_off:
                self.e_shoff += pad
        for i in range(self.e_shnum):
            self.write_section_header(i)
        self.write_elf_header()

    def _strtab_find(self, strtab_idx, name):
        """Search strtab for an exact (NUL-terminated) match. Returns offset
        or None if not present."""
        sec = self.sections[strtab_idx]
        blob = bytes(self.data[sec[4]:sec[4] + sec[5]])
        needle = name.encode("ascii") + b"\x00"
        idx = blob.find(needle)
        if idx < 0:
            return None
        # Must be NUL-preceded (or at index 0) to be a real start, not a tail match
        if idx > 0 and blob[idx - 1] != 0:
            return None
        return idx

    def _strtab_add(self, strtab_idx, name):
        """Return offset of name in strtab; append if missing."""
        existing = self._strtab_find(strtab_idx, name)
        if existing is not None:
            return existing
        encoded = name.encode("ascii") + b"\x00"
        sec = self.sections[strtab_idx]
        new_off = sec[5]  # current end (relative to section start)
        start_abs = self._grow_section(strtab_idx, len(encoded))
        self.data[start_abs:start_abs + len(encoded)] = encoded
        return new_off

    def find_or_add_global_undef_symbol(self, name):
        """Return the symbol-table index of a GLOBAL UND symbol with this name.
        If absent, append a new entry (and matching strtab string)."""
        symtab_idx = self.find_section(".symtab")
        strtab_idx = self.sections[symtab_idx][6]
        for sym_idx, fields in self.iter_symtab(symtab_idx):
            if self.strtab_string(strtab_idx, fields[0]) == name:
                return sym_idx
        # Append new symbol: STB_GLOBAL=1, STT_NOTYPE=0 -> st_info=(1<<4)|0=0x10;
        # st_other=0, st_shndx=SHN_UNDEF=0, st_value=0, st_size=0.
        name_off = self._strtab_add(strtab_idx, name)
        symtab = self.sections[symtab_idx]
        ent = symtab[9]
        new_idx = symtab[5] // ent
        new_abs = self._grow_section(symtab_idx, ent)
        struct.pack_into(SYM_FMT, self.data, new_abs, name_off, 0, 0, 0x10, 0, 0)
        return new_idx

    def append_text_relocs(self, new_entries):
        """Append (r_off, r_info) entries to .rel.text, creating it if needed.
        Used for import_donor_relocs."""
        if not new_entries:
            return
        if not self.has_section(".rel.text"):
            raise RuntimeError(".rel.text section missing — cannot append relocs")
        rel_idx = self.find_section(".rel.text")
        ent = self.sections[rel_idx][9]
        bytes_per_entry = struct.calcsize(REL_FMT)
        if ent != bytes_per_entry:
            raise RuntimeError(f".rel.text ent_size {ent} != {bytes_per_entry}")
        start_abs = self._grow_section(rel_idx, ent * len(new_entries))
        for i, (r_off, r_info) in enumerate(new_entries):
            struct.pack_into(REL_FMT, self.data, start_abs + i * ent, r_off, r_info)

    def import_donor_relocs(self, donor, donor_func_start, donor_func_size, dest_func_start):
        """Read donor's .rel.text relocs that fall within the donor function's
        byte range, remap their symbol indices to dest's symbol table (adding
        missing symbols), remap their offsets to the destination function, and
        append them to dest's .rel.text. Companion to fix_relocations which
        drops the dest's own relocs in the replaced range — this re-adds the
        ones from the donor compile so linker resolution still works (without
        this, externs the donor referenced silently zero out the field bytes)."""
        if not donor.has_section(".rel.text"):
            return 0
        d_rel_idx = donor.find_section(".rel.text")
        d_sec = donor.sections[d_rel_idx]
        d_off, d_size, d_ent = d_sec[4], d_sec[5], d_sec[9]
        d_symtab_idx = donor.find_section(".symtab")
        d_strtab_idx = donor.sections[d_symtab_idx][6]
        donor_limit = donor_func_start + donor_func_size
        new_entries = []
        for i in range(d_size // d_ent):
            entry_off = d_off + i * d_ent
            r_off, r_info = struct.unpack(REL_FMT, donor.data[entry_off:entry_off + d_ent])
            if not (donor_func_start <= r_off < donor_limit):
                continue
            r_type = r_info & 0xFF
            d_sym_idx = r_info >> 8
            d_sym = list(donor.iter_symtab(d_symtab_idx))[d_sym_idx][1]
            sym_name = donor.strtab_string(d_strtab_idx, d_sym[0])
            dest_sym_idx = self.find_or_add_global_undef_symbol(sym_name)
            dest_r_off = (r_off - donor_func_start) + dest_func_start
            dest_r_info = (dest_sym_idx << 8) | r_type
            new_entries.append((dest_r_off, dest_r_info))
        self.append_text_relocs(new_entries)
        return len(new_entries)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dest")
    ap.add_argument("func")
    ap.add_argument("donor")
    args = ap.parse_args()

    dest_path = Path(args.dest)
    dest = Elf(dest_path.read_bytes())
    donor = Elf(Path(args.donor).read_bytes())
    payload = donor.text_bytes_for(args.func)
    _, fields, _ = dest.find_symbol(args.func)
    old_start, old_size = fields[1], fields[2]

    old_payload = dest.text_bytes_for(args.func)
    if old_payload == payload:
        print(f"replace-body-skip: {args.func} already matches donor")
        return

    # Find donor function range for reloc import (before replace_text_range, so
    # we can still query donor cleanly).
    _, donor_fields, _ = donor.find_symbol(args.func)
    donor_func_start, donor_func_size = donor_fields[1], donor_fields[2]

    delta = dest.replace_text_range(old_start, old_size, payload)
    dest.fix_symbols(args.func, old_start, old_size, len(payload), delta)
    dest.fix_relocations(old_start, old_size, delta)
    imported = dest.import_donor_relocs(donor, donor_func_start, donor_func_size, old_start)
    dest.realign_sections()
    dest_path.write_bytes(dest.data)
    suffix = f" + imported {imported} donor reloc(s)" if imported else ""
    print(f"replace-body: {args.func} {old_size:#x}->{len(payload):#x} in {dest_path}{suffix}")


if __name__ == "__main__":
    main()
