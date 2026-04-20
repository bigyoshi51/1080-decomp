#include "common.h"

extern int gl_func_00000000();

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000000);

extern char D_00000000;

#ifdef NON_MATCHING
/* 74.9 %: dispatcher loop on arg1 against D_00000000+0x40. Goto-based flow
 * (75 %) beats do-while/if-elif (33 %). Target compiles the dispatch as
 * 3 forward-only branches (beq+delay, beq+delay, b+delay-reload) — mine
 * inflates to 6 branches (bne+delay, b+delay, bne+delay, b+delay, b+delay)
 * because IDO doesn't short-circuit if-goto chains the way target was.
 * Likely only permuter can bridge the gap. Variants tried (2026-04-20):
 * (a) decl order flag/ONE/base/base10 = 74.9 %, (b) literal 1 instead of
 * ONE var = 33 %, (c) do-while+if-elif = 33 %. Keep goto version. */
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

