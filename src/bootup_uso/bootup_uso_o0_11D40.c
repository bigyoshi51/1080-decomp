#include "common.h"

/* -O0 sub-file split out of bootup_uso_tail3a.c so this single function
 * builds at -O0 (matching its target shape) while neighbours stay -O2 -g3.
 * Same recipe as the existing bootup_uso_o0_F1F0.c / o0_F390.c cluster.
 *
 * Body verified byte-for-byte at -O0 (see kept-in-comment trace at
 * tail3a.c's 2026-05-06 RE-DIAGNOSED #2 entry, archived below). */
int func_00011D40(int *a0, int a1) {
    if (*(int*)((char*)a0 + 0x120) < a1) return 0;
    return *(int*)((char*)a0 + a1 * 4 + 0xDC);
}
