#include "common.h"

extern int gl_func_00000000();

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000000);

extern char D_00000000;

#ifdef NON_MATCHING
/* 33.7% promoted (2026-04-20). Semantic logic is correct:
 *  - Dispatch loop on arg1
 *  - arg1==0: call gl_func_00000000(base, 1, 0, 0); then gl_func_00000000(0)→r; then
 *             gl_func_00000000(arg0, 1, r). Set flag=1.
 *  - arg1==1: cur = gl_func_00000000(0, 1, 0). set flag=1. gl_func_00000000(base10, cur).
 *             Branch-likely pattern: if cur[0x14] != 0 then cur[0x04]=1; always cur[0x14]=base.
 *             Asm uses `beql t6, zero, merge; sw s3, 0x14(s0)` (delay-slot store ON taken) +
 *             `sw s2, 0x04(s0)` (fall-through) + `sw s3, 0x14(s0)` (at merge). Net effect:
 *             always store base to 0x14; additionally store 1 to 0x04 when prev value was nonzero.
 *  - else (fallthrough): no body, just loop-tail.
 *  - arg1 = base[0x40]. Loop until flag != 0.
 *
 * Structural diffs keeping it at 33%:
 *  1) Target uses $s0-$s5 for: base ($s3), base10 ($s4), arg0-save ($s5), flag ($s1),
 *     cur ($s0), one=1 ($s2). My build likely uses $t-registers and reloads.
 *     Need register hints or live-range extension to get IDO to pick $s regs.
 *  2) Target dispatches via `beq $a1, $zero, do0; or $a0, $s3, $zero (delay)`; `beq $a1,
 *     $s2, do1; or $a0, $zero, $zero (delay)`; `b loop_tail; or $a0, $zero, $zero`.
 *     The delay slots carry the a0-setup for the branches. My current if/else-if chain
 *     won't produce this layout — need a different control-flow shape (maybe a switch
 *     or explicit goto's with pre-computed a0 values).
 *  3) Second gl_func_00000000 call in arg1==0 path has a0 = base (from earlier delay
 *     slot `or a0, s3, zero` at 0x54). My current C may pass different args.
 *
 * Next pass: rework dispatch with explicit gotos to pre-position args in delay slots,
 * and force `register int *cur asm("")` style hints to pin the $s-regs. */
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

