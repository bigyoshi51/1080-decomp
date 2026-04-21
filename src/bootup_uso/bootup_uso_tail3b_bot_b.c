#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

#ifdef NON_MATCHING
/* Unmatchable at -O2: target has `sw zero,0x168(a0); sw zero,0x16C(a0);
 * jr ra; nop` (4 insns, unfilled delay slot) but IDO -O2 schedules the
 * 2nd sw into the delay slot producing `sw zero,0x168(a0); jr ra; sw
 * zero,0x16C(a0)` (3 insns). Size mismatch prevents byte match. Same
 * class as func_00010A9C / func_00012090 — see
 * feedback_ido_unfilled_store_return.md. Wrap documents: field_168 and
 * field_16C = 0 (2-word sentinel clear). */
void func_00012BF8(int *a0) {
    *(int*)((char*)a0 + 0x168) = 0;
    *(int*)((char*)a0 + 0x16C) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012BF8);
#endif

void func_00012C08(void) {
}


