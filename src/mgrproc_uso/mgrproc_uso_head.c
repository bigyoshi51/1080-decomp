#include "common.h"

/* [0xF8, 0x19C) of the mgrproc_uso Yay0 block (region 1, -O2): the func_000000F8
 * bundle + the small leaves between the two -O0 runs. Carved out so the -O0 run
 * at [0x19C, 0xAE0) can be its own -O0 sub-unit (mgrproc_uso_o0_19C.c). The
 * empty stubs func_00000168/_00000194 (`void f(){}` = jr ra; nop) are -g3-
 * invariant. This .o is built -O2 -g3 (see Makefile): -g3 disables the reorg
 * delay-slot filler so the return-0 leaves func_0000015C/_00000188 emit their
 * UNFILLED `move v0,zero; jr ra; nop` target form; the empty stubs and the
 * INCLUDE_ASM funcs are unaffected. See the mgrproc_uso_block1_yay0 rule. */

extern int gl_func_00000000();

/* branch-into-adjacent-return-0-leaf CAP. The bne (.word 15CF0004) offset is
 * SELF-RELATIVE / link-independent (NOT "linker-set") — it branches +4 past
 * this fn's end into func_0000015C, the `move v0,0; jr ra` return-0 leaf below
 * (no jal/data xref). The target shape (regular bne, NOP delay, two separate
 * jr-ra blocks) needs the return-0 to be a SEPARATE adjacent fn the guard
 * branches into; the cross-fn branch blocks the optimizer. C can't reproduce:
 * merging `if(eq)return 1;return 0;` -> preset-default (move v0,0;bne;li v0,1,
 * 9 insns); `goto ret0` -> branch-LIKELY (bnel+ret0 in delay, 9 insns). Both
 * collapse the two blocks. INCLUDE_ASM is the faithful path. Verified
 * 2026-05-30; see docs/IDO_CODEGEN.md#branch-into-adjacent-return-leaf-cap.
 * 2026-06-10: the 75264 boundary-dissolves-cap precedent does NOT apply
 * here -- tested the MERGED [0x140..0x168) function (if/return, goto,
 * if/else, named temps) at 7.1 -O1/-O2 x -g3: IDO always collapses to
 * 9 insns (preset-default or bnel), never the 10-insn two-block form.
 * The cap stands; the pair really is two source functions. */
#ifdef NON_MATCHING
int mgrproc_uso_func_00000140(int *a0) {
    if (a0[1] == a0[2]) {
        return 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000140);
#endif

/* return-0 leaf, size 0xC (`move v0,zero; jr ra; nop`, UNFILLED jr-delay) —
 * matched via the file-wide -O2 -g3 build (see Makefile). */
int mgrproc_uso_func_0000015C(void) {
    return 0;
}

void mgrproc_uso_func_00000168(void) {
}

/* branch-into-adjacent-return-0-leaf CAP (same as _00000140); its bnez
 * (.word 15C00004) branches +4 into func_00000188, the return-0 leaf below. */
#ifdef NON_MATCHING
int mgrproc_uso_func_00000170(int *a0) {
    if (a0[0] == 0) {
        return 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000170);
#endif

/* return-0 leaf, size 0xC (UNFILLED jr-delay) — matched via -O2 -g3. */
int mgrproc_uso_func_00000188(void) {
    return 0;
}

void mgrproc_uso_func_00000194(void) {}
