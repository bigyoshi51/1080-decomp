#include "common.h"

/* -O0 run at 0x50: Quad4 reader accessor template. See
 * feedback_uso_accessor_o0_variant.md. */

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

void arcproc_uso_func_00000050(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

/* -O0 ref-count/check-full at 0xB4 (moved from arcproc_uso_tail1.c).
 * Was 82.3 % cap when compiled at -O2; this file's -O0 override should
 * make the IDO load order (a0[1] before a0[2], spill+reload at every use,
 * trailing `b +1; nop`) match. */
#ifdef NON_MATCHING
/* Moved into this -O0 file 2026-05-02 (was at 82.3 % cap in -O2 tail1).
 * In -O0 mode: block-local `register int *p` on the increment branch
 * matches target's frame size (-0x28), s0 save at 0x18, and reload to s0
 * in the second half. Remaining ~26-byte diff: target loads `a0[1]`
 * BEFORE `a0[2]` for the `+1==` comparison; IDO -O0 evaluates the rhs-load
 * first regardless of source order, AND emits an extra `b +3; nop` near
 * the increment-branch return path. Tried `next = a0[1]+1; if (next ==
 * a0[2])` to force load order -- adds spill+reload (worse). Estimated cap
 * in -O0: ~85-90 %. */
int arcproc_uso_func_000000B4(int *a0, int a1) {
    gl_func_00000000(a0, a1);
    if (a0[1] + 1 == a0[2]) {
        return 1;
    }
    {
        register int *p = a0;
        p[1] += 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000000B4);
#endif
