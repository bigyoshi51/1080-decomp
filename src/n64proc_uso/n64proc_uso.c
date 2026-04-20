#include "common.h"

extern int gl_func_00000000();

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000000);

extern char D_00000000;
#ifdef NON_MATCHING
/* 74.9 %: dispatcher loop on arg1 against D_00000000+0x40. Goto-flattened
 * control flow matches target's forward-branch dispatch. Target s-reg
 * assignment: s0=cur, s1=flag, s2=ONE(=1), s3=base, s4=base10, s5=arg0.
 * IDO's global allocator doesn't reach the same priority order regardless
 * of declaration order. Tried: (a) original order (base/base10/flag/cur/r/ONE)
 * = 75 %, (b) reorder to flag/ONE/base/base10/cur/r = 74.9 %. Register-
 * forcing via `register T x asm("$sN")` is GCC-only and rejected by IDO
 * (feedback_ido_no_gcc_register_asm.md). Remaining structural gap is the
 * 6 s-register allocno ordering; permuter may find it. Next pass: try
 * bumping flag's ref count (multiple checks) or boosting base's uses to
 * move them up in priority. */
void n64proc_uso_func_00000014(int arg0, int arg1) {
    int flag = 0;
    int ONE = 1;
    char *base = &D_00000000;
    char *base10 = &D_00000000 + 0x10;
    int *cur;
    int r;

loop:
    if (arg1 == 0) goto do0;
    if (arg1 == ONE) goto do1;
    goto tail;

do0:
    gl_func_00000000(base, 1, 0, 0);
    flag = 1;
    r = gl_func_00000000(0);
    gl_func_00000000(arg0, 1, r);
    goto tail;

do1:
    cur = (int*)gl_func_00000000(base, 1, 0);
    flag = 1;
    gl_func_00000000(base10, cur);
    if (*(int*)((char*)cur + 0x14) != 0) {
        *(int*)((char*)cur + 0x4) = 1;
    }
    *(int*)((char*)cur + 0x14) = (int)base;

tail:
    arg1 = *(int*)((char*)base + 0x40);
    if (flag == 0) goto loop;
}
#else
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000014);
#endif

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000100);

void n64proc_uso_func_00000230(char *a0) {
    gl_func_00000000(a0 + 0x58, 6);
    gl_func_00000000(a0 + 0x70, 3);
}

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000268);

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000364);
#pragma GLOBAL_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso/n64proc_uso_func_00000364_pad.s")

