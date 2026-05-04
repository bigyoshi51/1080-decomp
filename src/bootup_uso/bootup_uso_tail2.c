#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00010260 moved to bootup_uso_o0_1024C.c (-O0 file split, 2026-05-03). */

#ifdef NON_MATCHING
/* 32.88% NM. Logic: a0[0x70] = (float)a1 - ((float)a0[0x78] * a0[0x74]) / 2.0f.
 *
 * Two structural caps that block 100%:
 *  (a) IDO -O2 folds `/2.0f` into `*0.5f` (mul-by-reciprocal) — replaces
 *      div.s + lui 0x40000000 with mul.s + lui 0x3F000000. Logically
 *      equivalent but different opcode; can't be flipped from C.
 *  (b) Function shrinks 12 bytes (16 vs 19 insns): expected has 3 nop
 *      load-delay slots after each mtc1 (mtc1 t6,f4 / nop / cvt.s.w
 *      f6,f4). Our IDO -O2 -mips2 schedules across the load delays
 *      since the operations are independent. Likely original was
 *      compiled at -mips1 or with a flag that forced strict MIPS-II
 *      load-delay nops.
 *
 * Since size differs, INSN_PATCH alone can't promote per
 * feedback_insn_patch_size_diff_blocked.md.
 *
 * Promotion path: per-file -mips1 override OR an `inject-insn-at.py`
 * sibling that grows function size + shifts symbols/relocs. Deferred. */
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

