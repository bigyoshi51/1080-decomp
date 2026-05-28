#include "common.h"

/* bootup_uso 0xFBCC — split off bootup_uso_tail1.c (which builds -O2) into
 * this -O0 sub-file on 2026-05-28 so the function compiles byte-exact.
 *
 * func_0000FBCC: single-block bit-clear, 23 insns / 0x5C. Constant-folded
 * `set = 0` flag makes the `if (set)` branch dead; at -O0 IDO keeps both
 * arms + the dead `b .+1; nop` BB marker, reproducing the target exactly.
 * -O0 emit is 24 insns (0x60); the trailing nop past 0x5C is clipped by
 * TRUNCATE_TEXT := 0x5C. (At -O2 the dead branch folds away — hence the
 * file split.) */

void func_0000FBCC(int *a0) {
    register int *p1, *p2;
    register int set;
    register int *t;
    p1 = (int*)((char*)a0[0x48/4] + 0x18);
    p2 = p1;
    set = 0;
    if (set) { t = p2; *t = *t | 8; }
    else     { t = p2; *t = *t & ~8; }
}
