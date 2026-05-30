#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

/* Contiguous -O0 run at the start of the mgrproc_uso Yay0 block (0x0..0xF8).
 * Carved into a dedicated -O0 sub-unit (region 0); its truncated .text is
 * concatenated with the -O2 main object before crunch64 compression. See the
 * mgrproc_uso_block1_yay0 rule in the Makefile. The -O0 emit (vs the -O2
 * accessor template's 15 insns) shows: sw-ra-before-sw-a0, unfilled jal delay,
 * pointer-indirect reload, and a trailing dead `b +1; nop`. */

/* int-reader (0x4C / 19 insns) */
void mgrproc_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

/* Quad4-reader (0x64 / 25 insns) */
void mgrproc_uso_func_0000004C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

/* refcount-increment wrapper (0x48 / 18 insns). The `register` pointer lands in
 * callee-saved s0 — the target's pointer base — under -O0. */
void mgrproc_uso_func_000000B0(int *a0) {
    register int *p = a0;
    p[1]++;
    gl_func_00000000(a0);
}

/* refcount-decrement wrapper (0x48 / 18 insns), exact sibling of _000000B0
 * (decrement of [0] vs increment of [1]). The `register` pointer lands in
 * callee-saved s0 — the target's pointer base — under -O0. Moved here from
 * mgrproc_uso_head.c (region extended 0xF8->0x140) so it builds at -O0. */
void mgrproc_uso_func_000000F8(int *a0) {
    register int *p = a0;
    p[0]--;
    gl_func_00000000(a0);
}
