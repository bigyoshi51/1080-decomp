#include "common.h"

extern s32 func_800077DC(s32);
extern s32 func_800096B0(s32);
extern s32 D_8000A41C;

/* split from kernel_039.c - 2026-06-10 kernel ROM-order relayout */


/* __osGetActiveQueue */
s32 func_80009830(void) {
    return D_8000A41C;
}
