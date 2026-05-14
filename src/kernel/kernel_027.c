#include "common.h"

extern s32 func_80005120(void*);

/* osVirtualToPhysical */
u32 func_80004730(void* vaddr) {
    if ((u32)vaddr >= 0x80000000U && (u32)vaddr < 0xA0000000U) {
        return (u32)vaddr & 0x1FFFFFFF;
    }
    if ((u32)vaddr >= 0xA0000000U && (u32)vaddr < 0xC0000000U) {
        return (u32)vaddr & 0x1FFFFFFF;
    }
    return func_80005120(vaddr);
}

/* func_800047B0: 22-insn unaligned-big-endian-u32 load from byte array.
 * Merged 2026-05-14 from 47B0 (13-insn prologue) + 47E4 (9-insn tail)
 * splat fragments — was 2 separate symbols joined as a single function.
 * Alt-entry at 47E4 (some callers jal there directly with pre-set
 * $t2/$t5 — preserved via undefined_syms_auto.txt entry).
 *
 * 2026-05-14 C-body decomp blocked: `volatile u32 acc` + cast chain
 * produces 21-insn form (4 bytes short) — IDO -O2 elides the redundant
 * `andi $t, $t, 0xFF` post-lbu that target keeps (lbu already zero-
 * extends). 19 byte diffs + 4-byte size shortfall. Cap class:
 * narrow-arg-cast-vs-bitmask (per docs/IDO_CODEGEN.md). NM-wrap-only
 * for now; merge unblocks future decomp passes. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800047B0);
