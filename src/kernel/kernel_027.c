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
 * splat fragments. Alt-entry at 47E4 preserved via undefined_syms_auto.txt.
 *
 * C-body retest 2026-05-14 with `& 0xFF` mask (per IDO_CODEGEN narrow-
 * arg-cast recipe): andi-after-lbu emit is correct, but volatile u32 is
 * overdoing stack roundtrips (built is 12 bytes LARGER than target).
 * Target has a curious pattern: accumulator in register chain
 * (t8 → t2 → t6 → t0) AND speculative sw to sp+4 after each OR, but
 * NO lw reload — return value comes from register, not stack. No std
 * C form (volatile, 1-elem-array, plain local) produces this register-
 * chain + speculative-store hybrid. NM-wrap-only. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800047B0);
