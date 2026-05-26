#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00010260 moved to bootup_uso_o0_1024C.c (-O0 file split, 2026-05-03). */

/* func_000102A4: a0[0x70] = (float)a1 - ((float)a0[0x78] * a0[0x74]) / 2.0f.
 * NATURAL CEILING: 32.88% NM cap with two documented structural diffs:
 *   (a) IDO -O2 folds /2.0f → *0.5f (mul.s vs target's div.s);
 *   (b) target has 3 strict MIPS-II load-delay nops after each mtc1
 *       that IDO -O2 schedules across.
 * The historical SUFFIX_BYTES (3 nops) + 15-word INSN_PATCH promotion was
 * REMOVED 2026-05-23 as match-faking. The div-fold piece could be fixed
 * with a function-scope named-divisor (see docs/IDO_CODEGEN div-fold
 * entry — would lift to ~50%); the load-delay nop schedule is a -g/-O0
 * cap class (see feedback_unfilled_delay_int_reader_needs_o0_split). */
#ifdef NON_MATCHING
void func_000102A4(char *a0, int a1) {
    *(float*)(a0 + 0x70) = (float)a1 - ((float)*(int*)(a0 + 0x78) * *(float*)(a0 + 0x74)) / 2.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000102A4);
#endif

void func_000102E8(void) {
}

void func_000102F0(char *a0, int a1) {
    *(float*)(a0 + 0x70) = (float)a1;
}

void func_00010308(void) {
}

