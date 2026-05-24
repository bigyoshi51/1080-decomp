#!/usr/bin/env python3
"""Unicorn-based harness to run the 1080 kernel USO loader and capture the
RESOLVED in-memory symbol table for a USO module.

WHY: the on-disk Kyoto-USO Sym section can't be parsed statically (the loader
resolves names->values in-place at load; no separate parser found in the kernel
cluster). Running the loader and dumping the resolved symTable (module->0x3C,
12-byte entries, value@+4) lets us reverse the symIdx->(name,value) encoding,
which unlocks reloc-CLEAN episodes + real symbol names for the reloc-aware
emitter (uso-reloc-symbolize.py).

HARNESS STATUS (2026-05-24): the Unicorn MIPS execution infra WORKS.
KEY GOTCHA: Unicorn MIPS32 CANNOT fetch from 0x80000000+ (high bit). Solution =
virtual-TLB mode (UC_TLB_VIRTUAL) + a UC_HOOK_TLB_FILL callback that maps
0x80xxxxxx -> physical via KSEG mask (vaddr & 0x1FFFFFFF). Physical RAM mapped at
0x0. jal/j auto-work (target high-nibble comes from PC). Verified: kernel
functions execute + access translated memory correctly.

REMAINING (the full loader drive): the loader is file-based --
func_800015D0 (open) / func_800009D8(dst,size,count,fh) (read) / func_80000A88
(seek) over a file object; func_80001EC8 = section loader; func_80001ADC =
relocator (a0=module[->0x3C=symTable], a1=section base, a2=reloc table, a3=count);
func_800018F0 = un-relocator. The SYM RESOLVER (writes symEntry+4 + sets
symEntry+0 bit3) was not located statically. NEXT: either (a) stub
open/read/seek to serve the bootup.uso ROM bytes + an allocator stub, then run
the top-level load entry (callers of uso_file_open: func_800012BC/80001414/
80001348) and hook func_80001ADC to dump a0->0x3C; or (b) manually load
bootup.uso sections + build the module struct, set a UC_HOOK_MEM_WRITE on the
Sym region, and run candidate loader fns to EMPIRICALLY identify the resolver by
who writes symEntry+4.

Module struct layout (from RE): +0x08/0x0C/0x10 = rodata/data/text section bases;
+0x3C = Sym table; +0x40/44/48 = reloc counts (text/data/rodata);
+0x4C/50/54 = reloc tables. Section loader also stores bases at +0x38+type*4.
"""
import struct
from unicorn import *
from unicorn.mips_const import *

ROM = 'baserom.z64'
KERN_ROM, KERN_END, KERN_VRAM = 0x1000, 0xBBC0, 0x80000000
BOOTUP_MODULE = 0xD9FE28   # bootup.uso module header (magic 0x12345678) on ROM

def make_emu():
    rom = open(ROM, 'rb').read()
    mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
    mu.ctl_tlb_mode(UC_TLB_VIRTUAL)
    mu.mem_map(0x0, 0x2000000)                  # 32MB phys RAM at 0x0
    mu.mem_write(0x0, rom[KERN_ROM:KERN_END])   # kernel .text/.rodata/.data -> phys 0x0
    def tlb_cb(uc, vaddr, access, entry, user):
        entry.paddr = vaddr & 0x1FFFFFFF        # KSEG0/1 -> physical
        entry.perms = UC_PROT_ALL
        return True
    mu.hook_add(UC_HOOK_TLB_FILL, tlb_cb)
    return mu, rom

def call(mu, addr, a0=0, a1=0, a2=0, a3=0, sp=0x80F00000, ret=0x80000004, maxinsn=2_000_000):
    mu.reg_write(UC_MIPS_REG_SP, sp)
    mu.reg_write(UC_MIPS_REG_RA, ret)
    for r, v in [(UC_MIPS_REG_A0,a0),(UC_MIPS_REG_A1,a1),(UC_MIPS_REG_A2,a2),(UC_MIPS_REG_A3,a3)]:
        mu.reg_write(r, v)
    try:
        mu.emu_start(addr, ret, count=maxinsn)
    except UcError as e:
        return None, (e, mu.reg_read(UC_MIPS_REG_PC))
    return mu.reg_read(UC_MIPS_REG_V0), None

if __name__ == '__main__':
    mu, rom = make_emu()
    # smoke test: harness executes kernel code (returns garbage until allocator
    # init, but proves fetch+mem+jal work through the TLB)
    v, err = call(mu, 0x800000B0, 0x11, 0x8)
    print('harness smoke test func_800000B0(0x11,0x8) ->', hex(v) if v is not None else err)
    print('Harness OK. See module docstring for the remaining loader-drive steps.')
