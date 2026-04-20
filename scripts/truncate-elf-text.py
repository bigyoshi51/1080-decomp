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

    for i in range(e_shnum):
        base = e_shoff + i * e_shentsize
        sh_name_off = struct.unpack('>I', data[base:base + 4])[0]
        name_bytes = data[shstr_off + sh_name_off:]
        name = name_bytes[:name_bytes.find(b'\x00')].decode()
        if name == '.text':
            sh_size = struct.unpack('>I', data[base + 0x14:base + 0x18])[0]
            sh_addralign = struct.unpack('>I', data[base + 0x20:base + 0x24])[0]
            changed = False
            if sh_size > target_size:
                data[base + 0x14:base + 0x18] = struct.pack('>I', target_size)
                print(f"{path}: truncated .text from 0x{sh_size:x} to 0x{target_size:x}")
                changed = True
            elif sh_size < target_size:
                sys.exit(f"{path}: .text is already smaller (0x{sh_size:x} < 0x{target_size:x})")
            # Reduce alignment to 4 so the linker doesn't pad to 16-aligned
            if sh_addralign > 4:
                data[base + 0x20:base + 0x24] = struct.pack('>I', 4)
                print(f"{path}: reduced .text alignment from {sh_addralign} to 4")
                changed = True
            if not changed:
                return
            break
    else:
        sys.exit(f"{path}: no .text section found")

    with open(path, 'wb') as f:
        f.write(bytes(data))


if __name__ == '__main__':
    truncate_elf_text(sys.argv[1], int(sys.argv[2], 16))
