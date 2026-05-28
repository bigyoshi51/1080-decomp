#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;

/* Int-reader compiled at -O0 (0x4C / 19 insns) — the -O2 template is 15 insns.
 * Carved into its own -O0 sub-unit (region 0 of the Yay0 block); concatenated
 * with the -O2 main object before crunch64 compression. See the
 * mgrproc_uso_block1_yay0 rule in the Makefile. */
void mgrproc_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
