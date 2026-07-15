#include "common.h"

/* func_80008030: SP idle-check (HALT|BROKE bits clear?). Compiled at -O2,
 * not the surrounding kernel_031.c's -O1 default. Split here to apply
 * file-level OPT_FLAGS := -O2.
 *
 * NATURAL CEILING: 82.78% NM. Register-pick cap class (target uses $t0
 * throughout + direct $v0; build emits $t6/$t7 + $v1 then `or v0,v1,zero`).
 * Same insn count (9), 5 word-diffs at NON-reloc offsets — all
 * register-allocation choices IDO -O2 won't reproduce from this C shape.
 *
 * The historical INSN_PATCH bridge (including the clever lui/lw
 * register-field patch that preserved the R_MIPS_HI16/LO16 relocs by
 * writing zero-immediate) was REMOVED 2026-05-23 as match-faking
 * (per feedback_no_instruction_forcing_matches_policy). Permuter-class
 * fix or focused-session split-shape grind would be the path forward.
 *
 * 2026-06-04 opt-level + variant grind (standalone IDO, don't re-run): the
 * target is `or v0,zero,zero / ... / ori v0,v0,1` with $t0 temp + $v0 result,
 * 9 insns frameless. -O1 REGRESSES (adds an -0x8 frame + stack-homes v:
 * `sw zero,4(sp); li t8,1; sw t8,4(sp); lw v0,4(sp)`, 12 insns). -O2 is
 * closest but const-folds `0|1`→`li v1,1` and routes through $v1
 * (`move v1,zero; li v1,1; move v0,v1`). Four -O2 variants all fail to
 * produce the target's unfolded `ori v0,v0,1`+$t0+$v0: named `u32 status`
 * local (pushes the read into $v0 but keeps v1/move), ternary
 * `?1:0` (emits a doubled jr + li v0 delay), and the `if(1){}` BB-boundary
 * lever in the if-body (NO change — the if already supplies the BB). The
 * unfolded OR requires IDO to not propagate v=0 into the if-body BB, which
 * -O2 always does here. Genuine register-pick + const-fold cap; permuter-only.
 *
 * 2026-07-15 (agent-h) coloring-lever-wave re-verify — cap CONFIRMED, sharpened:
 *  - Same-name destructive reuse (`stat = D; stat &= 3;`) DOES reproduce the
 *    single-register load/mask chain (lui/lw/andi all one reg) — but colors it
 *    $v0 (return-web pick), never $t0, and v then takes $v1 + li fold + tail move.
 *  - The 0|1 fold is VN-robust: unpassed-K&R-param opaque source with v&=0 /
 *    v-=v / v^=v all fold to `li 1`; dead-if(stat), register hint, bitfield
 *    insert (goes to memory), u32/order permutations — all fold. The ONLY
 *    unfolded `ori x,x,1` obtained is from a VOLATILE zero source (costs
 *    frame+sw+lw) or -O1/-O0 `register` v (costs frame + a0 color + tail move).
 *  - Flag matrix: -O2 -g2/-g homes v (12 insns); -O2 -g3 bnezl form; -O1/-O0
 *    frame +8; IDO 5.3 -O1/-O2 same t6-first ring. NO IDO config yields a
 *    t0-FIRST temp ring on this shape.
 *  - The trio {t0-first ring, unfolded const OR, unfilled bnez delay in a
 *    9-insn frameless leaf} matches no IDO output family we can produce;
 *    plausibly HAND-WRITTEN ASM in the original (SP idle-check boot helper).
 *    If so, no C will ever land it — candidate for a GLOBAL_ASM/hand-asm
 *    disposition rather than further C grinding. */
extern u32 D_A4040010;  /* SP_STATUS_REG */

#ifdef NON_MATCHING
s32 func_80008030(void) {
    s32 v = 0;
    if ((D_A4040010 & 3) == 0) v |= 1;
    return v;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008030);
#endif
