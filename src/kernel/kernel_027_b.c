#include "common.h"

extern s32 func_80005120(void*);

/* split from kernel_027.c - 2026-06-10 kernel ROM-order relayout */


/* [RESOLVED 2026-07-10 — cap cracked via |= compound-assign; see the exact
 * body below. Historical characterization retained:]
 * func_800047B0: 22-insn unaligned-big-endian-u32 load from byte array.
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
 * other structure). Register-name-only cap.
 *
 * 2026-05-15 (agent-b, source-3) — exhaustive characterization:
 *   - 19/22 instructions differ, ALL pure register-field changes (same
 *     opcode/structure/immediates; accumulator EXP t8→t2→t6→t0 vs C $a1).
 *   - Variant: 4 distinct plain locals + volatile sink — accumulator DOES
 *     thread fresh regs (matches EXP!) but distinct locals over-spill
 *     (frame -0x18, double stores per step). Worse, not better.
 *   - Variant: 4 distinct `register` locals — also over-spills under -O1
 *     (frame -0x18, sink slot). Worse. Confirms the register-pin tradeoff
 *     is fundamental to IDO -O1 here, not a missing C idiom.
 *   - Permuter ACTUALLY RUN (import OK via PERMUTER=1; 150s, -j4, random):
 *     NO match, NO improvement saved. Random mode does not crack it; would
 *     need targeted PERM_GENERAL on the |-operand order + a longer run.
 *   - INSN_PATCH is NOT a valid promotion here: patching 19 register-field
 *     bytes to expected would be the documented tautology trap (bytes not
 *     produced by the C). The DEFAULT build is already byte-exact via
 *     INCLUDE_ASM, so the ROM is correct and NO episode is possible/needed
 *     — the fuzzy<100 is purely the reference-wrap scoring artifact.
 * Verdict: genuine IDO -O1 register-allocation cap. Leave as 92.73%
 * reference wrap; INCLUDE_ASM keeps ROM byte-exact. Do NOT re-grind C
 * variants or INSN_PATCH; only a targeted long permuter run could help. */
/* Unaligned big-endian u32 load (byte-pack). CRACKED EXACT 22/22
 * 2026-07-10: the "register-name-only cap" falls to the plain-local +
 * COMPOUND-ASSIGNMENT form. `v |= expr;` builds the OR tree acc-first
 * (rs=accumulator, rt=new bits), and a single plain (non-register,
 * non-volatile) local at -O1 gets exactly one home slot (sp+4) with a
 * store after each step while the accumulator threads through fresh
 * temps ($t8 -> $t2 -> $t6 -> $t0). The old 92.73% floor came from
 * `acc = acc | expr` (canonicalizes rs=new / rt=acc) and from
 * register/volatile-sink hybrids (pin the accumulator). No donor needed:
 * this file is already -O1. */
u32 func_800047B0(u8 *a0) {
    u32 v;
    v = (a0[0] & 0xFF) << 24;
    v |= (a0[1] & 0xFF) << 16;
    v |= (a0[2] & 0xFF) << 8;
    v |= a0[3] & 0xFF;
    return v;
}
