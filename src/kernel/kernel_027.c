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
 * 2026-05-15: found the C form (92.73%, was comment-only before). The
 * "register-chain + speculative-store hybrid" reproduces with:
 *   - a SEPARATE `volatile u32 sb` sink (NOT a volatile accumulator —
 *     that over-spills); `sb = acc` after each OR emits the lone
 *     sw,4(sp) per step with no reload.
 *   - `register u32 acc` keeps the accumulator out of the stack (plain
 *     local spills it to sp+0, +4 extra stores → 81.6%; register → 92.7%).
 *   - explicit `(a0[N] & 0xFF)` masks emit the andi-after-lbu (without
 *     the mask: 58%; with: 81.6%).
 * Remaining ~7%: target threads the accumulator through a FRESH register
 * each step (t8→t2→t6→t0); `register` pins it to one ($a1 chain). Using
 * distinct per-step temps to get fresh regs regresses to 80.2% (loses
 * other structure). Register-name-only cap — permuter/INSN_PATCH class.
 * Default build is INCLUDE_ASM (byte-exact); wrap is for reference. */
#ifdef NON_MATCHING
/* Unaligned big-endian u32 load. Register-chain accumulator with a
 * speculative volatile-sink store to sp+4 after every OR step (target
 * never reloads it; return value is the register). */
u32 func_800047B0(u8 *a0) {
    volatile u32 sb;
    register u32 acc;
    acc = (a0[0] & 0xFF) << 24;   sb = acc;
    acc |= (a0[1] & 0xFF) << 16;  sb = acc;
    acc |= (a0[2] & 0xFF) << 8;   sb = acc;
    acc |= (a0[3] & 0xFF);        sb = acc;
    return acc;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800047B0);
#endif
