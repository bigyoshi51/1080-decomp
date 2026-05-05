#!/usr/bin/env python3
"""Truncate a MIPS ELF .o file's .text section to a specific size.

Removes trailing zero-padding that the IDO compiler adds for 16-byte alignment,
and also reduces the section's sh_addralign to 4 so the linker places the
next .o right after this one's logical end rather than at the next 16-aligned
address.

Used when splitting a single .c file into multiple .o files that need to land
at non-16-aligned boundaries in the linker output.

Usage: truncate-elf-text.py <elf_file> <new_text_size_hex>

The file is modified in place.
"""
import sys, struct


def truncate_elf_text(path, target_size):
    with open(path, 'rb') as f:
        data = bytearray(f.read())

    assert data[0:4] == b'\x7fELF', f"{path} is not an ELF file"
    assert data[5] == 2, f"{path} is not big-endian"

    e_shoff = struct.unpack('>I', data[0x20:0x24])[0]
    e_shentsize = struct.unpack('>H', data[0x2E:0x30])[0]
    e_shnum = struct.unpack('>H', data[0x30:0x32])[0]
    e_shstrndx = struct.unpack('>H', data[0x32:0x34])[0]

    shstr_off = struct.unpack(
        '>I',
        data[e_shoff + e_shstrndx * e_shentsize + 0x10:
             e_shoff + e_shstrndx * e_shentsize + 0x14],
    )[0]

    text_idx = None
    symtab_off = symtab_size = symtab_entsize = strtab_idx = None
    for i in range(e_shnum):
        base = e_shoff + i * e_shentsize
        sh_name_off = struct.unpack('>I', data[base:base + 4])[0]
        name_bytes = data[shstr_off + sh_name_off:]
        name = name_bytes[:name_bytes.find(b'\x00')].decode()
        sh_type = struct.unpack('>I', data[base + 4:base + 8])[0]
        if name == '.text':
            text_idx = i
            sh_size = struct.unpack('>I', data[base + 0x14:base + 0x18])[0]
            sh_addralign = struct.unpack('>I', data[base + 0x20:base + 0x24])[0]
            changed = False
            if sh_size > target_size:
                data[base + 0x14:base + 0x18] = struct.pack('>I', target_size)
                print(f"{path}: truncated .text from 0x{sh_size:x} to 0x{target_size:x}")
                changed = True
            elif sh_size < target_size:
                # INCLUDE_ASM build path: the asm-emit produces a function at
                # exactly the asm length, which can be < target_size when the
                # C-emit version was bigger and TRUNCATE_TEXT was set to clip
                # it. Nothing to truncate; leave the .text alone. The symbol
                # walk below will still tighten any over-long symbols if any
                # exist, but typically there are none in this case.
                print(f"{path}: .text is already smaller (0x{sh_size:x} < "
                      f"0x{target_size:x}); INCLUDE_ASM build path, no-op")
            if sh_addralign > 4:
                data[base + 0x20:base + 0x24] = struct.pack('>I', 4)
                print(f"{path}: reduced .text alignment from {sh_addralign} to 4")
                changed = True
        if sh_type == 2:  # SHT_SYMTAB
            symtab_off = struct.unpack('>I', data[base + 0x10:base + 0x14])[0]
            symtab_size = struct.unpack('>I', data[base + 0x14:base + 0x18])[0]
            symtab_entsize = struct.unpack('>I', data[base + 0x24:base + 0x28])[0]
            strtab_idx = struct.unpack('>I', data[base + 0x18:base + 0x1C])[0]

    if text_idx is None:
        sys.exit(f"{path}: no .text section found")

    # Shrink any symbol in .text whose end > target_size — otherwise objdiff
    # rejects the .o with "Symbol data out of bounds".
    if symtab_off is not None:
        strtab_sh = e_shoff + strtab_idx * e_shentsize
        strtab_off = struct.unpack('>I', data[strtab_sh + 0x10:strtab_sh + 0x14])[0]
        n_syms = symtab_size // symtab_entsize
        for i in range(n_syms):
            s = symtab_off + i * symtab_entsize
            st_name = struct.unpack('>I', data[s:s + 4])[0]
            st_value = struct.unpack('>I', data[s + 4:s + 8])[0]
            st_size = struct.unpack('>I', data[s + 8:s + 12])[0]
            st_shndx = struct.unpack('>H', data[s + 0xE:s + 0x10])[0]
            if st_shndx == text_idx and st_value + st_size > target_size:
                new_size = max(0, target_size - st_value)
                name_end = data.index(b'\0', strtab_off + st_name)
                name = data[strtab_off + st_name:name_end].decode() or '<no-name>'
                struct.pack_into('>I', data, s + 8, new_size)
                print(f"{path}: shrunk symbol '{name}' @ 0x{st_value:x} from 0x{st_size:x} to 0x{new_size:x}")

    with open(path, 'wb') as f:
        f.write(bytes(data))


if __name__ == '__main__':
    truncate_elf_text(sys.argv[1], int(sys.argv[2], 16))
