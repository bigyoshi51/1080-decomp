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

/* 5-function bundle (splat can't separate); INCLUDE_ASM keeps all 5 matching. */
#ifdef NON_MATCHING
void mgrproc_uso_func_000000F8(int *a0) {
    a0[0]--;
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000000F8);
#endif

/* leaf-branch-past-end CAP (bne offset is linker-set, branches past fn end). */
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

/* leaf-branch-past-end CAP (same as _00000140). */
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
