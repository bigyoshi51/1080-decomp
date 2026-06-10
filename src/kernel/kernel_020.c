#include "common.h"

extern s32 rmonbrk_bss_0000;
extern s32 D_8001FEF4;
extern s32 D_8001FEF0;
extern void func_800031F0(void*, s32);
extern void func_80005350(void*, s32);






/* func_80007FC8: 8-insn infinite-loop stub (likely __osPanic/__halt-class).
 * Target: `b self; nop; nop; nop; nop; nop; jr ra; nop`.
 *
 * IDO -O2 can't emit the 6-leading-nop layout from any C body (`while(1){}`
 * produces 10 insns). Previously matched via `void f(void){}` + PREFIX_BYTES
 * (6-insn instruction-appending prefix). PREFIX_BYTES REMOVED 2026-05-27
 * (cleanup of policy violation, was missed by 2026-05-23 sweep) per
 * feedback_no_instruction_forcing_matches_policy — was instruction-appending
 * match-faking, not USO-header data. Function stays NM (INCLUDE_ASM build
 * path); honest unmatched. */
#ifdef NON_MATCHING
void func_80007FC8(void) {}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80007FC8);
#endif
