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
 * -O2 always does here. Genuine register-pick + const-fold cap; permuter-only. */
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
