#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00010260 moved to bootup_uso_o0_1024C.c (-O0 file split, 2026-05-03). */

#ifdef NON_MATCHING
/* ~33% NM. 17-insn FPU formula:
 *   a0->0x70 = (float)a1 - (float)(a0->0x78_int) * (a0->0x74_float) / 2.0f;
 *
 * Two structural caps per feedback_ido_div_2_mul_fold_and_mtc1_load_delay_nops.md:
 *   1. IDO -O2 strength-reduces `/2.0f` -> `*0.5f` (lui 0x3F000000 + mul.s).
 *      Target uses div.s with lui 0x40000000 (= 2.0f) — wrong shape.
 *   2. Target has post-mtc1 nops (load-delay slots from -mips1 ISA), my
 *      -mips2 build schedules across them — different size.
 * Combined: ~50% cap per memo. Currently 33%. Defer. */
void func_000102A4(char *a0, int a1) {
    *(float*)(a0 + 0x70) = (float)a1 - (float)(*(int*)(a0 + 0x78)) * (*(float*)(a0 + 0x74)) / 2.0f;
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

