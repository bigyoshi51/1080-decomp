#include "common.h"

extern int gl_func_00000000();

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000000);

/*
 * n64proc_uso_func_00000014: dispatcher loop on arg1 against D_00000000+0x40.
 * Decoded 2026-04-20 at 75 % match (under NM wrap threshold). See
 * notes/n64proc_uso_func_00000014.md for the partial C + analysis.
 *
 * void f(int arg0, int arg1) {
 *   char *base = &D_00000000;
 *   char *base10 = &D_00000000 + 0x10;
 *   int flag = 0, *cur, r, ONE = 1;
 * loop:
 *   if (arg1 == 0) goto do0;
 *   if (arg1 == ONE) goto do1;
 *   goto tail;
 * do0:  gl_func_00000000(base, 1, 0, 0); flag = 1;
 *       r = gl_func_00000000(0);
 *       gl_func_00000000(arg0, 1, r);
 *       goto tail;
 * do1:  cur = (int*)gl_func_00000000(base, 1, 0); flag = 1;
 *       gl_func_00000000(base10, cur);
 *       if (*(int*)((char*)cur + 0x14) != 0)
 *           *(int*)((char*)cur + 0x4) = 1;
 *       *(int*)((char*)cur + 0x14) = (int)base;
 * tail: arg1 = *(int*)((char*)base + 0x40);
 *       if (flag == 0) goto loop;
 * }
 *
 * Remaining gap: register allocation (target s3/s4/s5/s2 = base/base10/
 * arg0/one, ours swapped) and one extra reload of base+0x40. Revisit
 * with register-forcing or the -O1 override.
 */
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000014);

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000100);

void n64proc_uso_func_00000230(char *a0) {
    gl_func_00000000(a0 + 0x58, 6);
    gl_func_00000000(a0 + 0x70, 3);
}

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000268);

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000364);
#pragma GLOBAL_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso/n64proc_uso_func_00000364_pad.s")

