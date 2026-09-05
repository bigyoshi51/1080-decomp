#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00010260 moved to bootup_uso_o0_1024C.c (-O0 file split, 2026-05-03). */

/* func_000102A4 moved to bootup_uso_o0_1024C.c 2026-07-10 — it was an -O0
 * island (register params, unfolded div.s by 2.0f, mtc1 load-delay nops);
 * byte-exact there. The 2-word "func_000102E8" (jr ra; nop) that used to head
 * this unit was 102A4's dead -O0 `$exit` pair, absorbed into o0_1024C.c
 * 2026-09-05 (TRUNCATE_TEXT here 0x28 -> 0x20). tail2 now starts at
 * func_000102F0 (0x102F0). */

void func_000102F0(char *a0, int a1) {
    *(float*)(a0 + 0x70) = (float)a1;
}

void func_00010308(void) {
}

