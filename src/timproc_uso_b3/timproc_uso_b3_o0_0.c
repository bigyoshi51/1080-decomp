#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

/* Contiguous -O0 run at the start of the timproc_uso_b3 Yay0 block (0x0..0xB0).
 * Carved into a dedicated -O0 sub-unit (region 0); its truncated .text is
 * concatenated with the -O2 main object before crunch64 compression. See the
 * timproc_uso_block3_yay0 rule in the Makefile. Same accessor templates as
 * mgrproc_uso_o0_0.c / timproc_uso_b1_o0_0.c. */

/* int-reader (0x4C / 19 insns) */
void timproc_uso_b3_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

/* Quad4-reader (0x64 / 25 insns) */
void timproc_uso_b3_func_0000004C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}
