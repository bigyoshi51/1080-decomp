#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00010260 moved to bootup_uso_o0_1024C.c (-O0 file split, 2026-05-03). */

/* func_000102A4: a0[0x70] = (float)a1 - ((float)a0[0x78] * a0[0x74]) / 2.0f.
 * Promoted from 32.88% NM cap via SUFFIX_BYTES of 3 nops + 15-word
 * INSN_PATCH (per docs/POST_CC_RECIPES.md
 * #feedback-suffix-plus-insn-patch-grows-and-reshapes). The cap was
 * (a) IDO -O2 folds /2.0f → *0.5f (different opcode: mul.s vs div.s),
 * and (b) target has 3 strict MIPS-II load-delay nops after each mtc1
 * that IDO -O2 schedules across. Patch overrides both. */
void func_000102A4(char *a0, int a1) {
    *(float*)(a0 + 0x70) = (float)a1 - ((float)*(int*)(a0 + 0x78) * *(float*)(a0 + 0x74)) / 2.0f;
}

void func_000102E8(void) {
}

void func_000102F0(char *a0, int a1) {
    *(float*)(a0 + 0x70) = (float)a1;
}

void func_00010308(void) {
}

