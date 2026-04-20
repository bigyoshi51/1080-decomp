#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010260);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000102A4);

void func_000102E8(void) {
}

#ifdef NON_MATCHING
/* Unmatchable from C at -O2: target has `cvt.s.w f6, f4; swc1 f6, 0x70(a0);
 * jr ra; nop` (unfilled delay slot, 6 insns) but IDO -O2 schedules the swc1
 * into the delay slot producing `cvt.s.w f6, f4; jr ra; swc1 f6, 0x70(a0)`
 * (5 insns). Different size/layout. See feedback_ido_unfilled_store_return.md
 * — same pattern, swc1 variant. */
void func_000102F0(char *a0, int a1) {
    *(float*)(a0 + 0x70) = (float)a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000102F0);
#endif

void func_00010308(void) {
}

