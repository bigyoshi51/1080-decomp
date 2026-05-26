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
 * fix or focused-session split-shape grind would be the path forward. */
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
