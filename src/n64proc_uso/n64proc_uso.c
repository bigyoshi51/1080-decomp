#include "common.h"

extern int gl_func_00000000();

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000000);

extern char D_00000000;

#ifdef NON_MATCHING
/* Dispatcher loop on arg1. Two previous semantic bug: do1's first call
 * passed `base` as a0 but target has `a0 = 0` from the dispatch delay
 * slot. Fixed. New structure: plain if-else instead of goto chain, which
 * lets IDO emit the dispatch as `bne skip; <delay=setup>` rather than
 * the goto-expanded `bne skip; b TARGET` pair — closer to target's 3
 * forward branches. Still not exact (~?% TBD): target uses `beq` direct
 * to labels (`beq $a1, $zero, do0`), mine uses `bne skip-forward` which
 * is semantically identical but emits different bytes. */
void n64proc_uso_func_00000014(int arg0, int arg1) {
    int flag;
    char *base = &D_00000000;
    char *base10 = &D_00000000 + 0x10;
    int *cur;
    int r;

    flag = 0;
loop:
    if (arg1 == 0) {
        gl_func_00000000(base, 1, 0, 0);
        flag = 1;
        r = gl_func_00000000(0);
        gl_func_00000000(arg0, 1, r);
    } else if (arg1 == 1) {
        cur = (int*)gl_func_00000000(0, 1, 0);
        flag = 1;
        gl_func_00000000(base10, cur);
        if (*(int*)((char*)cur + 0x14) != 0) {
            *(int*)((char*)cur + 0x4) = 1;
        }
        *(int*)((char*)cur + 0x14) = (int)base;
    }
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

