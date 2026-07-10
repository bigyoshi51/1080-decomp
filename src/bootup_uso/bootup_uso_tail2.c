#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00010260 moved to bootup_uso_o0_1024C.c (-O0 file split, 2026-05-03). */

/* func_000102A4 moved to bootup_uso_o0_1024C.c 2026-07-10 — it was an -O0
 * island (register params, unfolded div.s by 2.0f, mtc1 load-delay nops);
 * byte-exact there. tail2 now starts at func_000102E8 (0x102E8). */

void func_000102E8(void) {
}

void func_000102F0(char *a0, int a1) {
    *(float*)(a0 + 0x70) = (float)a1;
}

void func_00010308(void) {
}

