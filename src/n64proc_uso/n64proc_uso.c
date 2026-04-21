#include "common.h"

extern int gl_func_00000000();

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000000);

extern char D_00000000;

#ifdef NON_MATCHING
/* Promoted to $s-reg allocation via `register` hints (2026-04-20).
 * Logic confirmed correct; structure matches target's do-while shape.
 *
 * Register allocation NOW (all 6 in $s-regs, just with different numbers):
 *   target:  s0=cur, s1=flag, s2=one, s3=base,  s4=base10, s5=arg0-save
 *   ours:    s0=cur, s1=flag, s2=base, s3=one, s4=arg0-save, s5=base10
 * Locally swapping $s-numbers blocks byte match. Per
 * feedback_ido_sreg_order_not_decl_driven.md: reordering decls is a no-op —
 * IDO's allocator is weight-driven (refs × live-length). Target `one` beats
 * `base` for $s2 despite our analysis giving base more "essential" uses.
 *
 * Remaining structural diff: the loop-tail reload `arg1 = base[0x40]` emits
 * as fresh lui+lo (bytes 0xB4-0xBC) instead of reusing the $s-reg holding
 * base. This is IDO's scheduler folding the load into the beq delay slot
 * rematerialization path. No straightforward C rewrite reproduces it.
 *
 * Next passes: (1) permuter to hit the $s-reg renumber, (2) eliminate `one`
 * local and use literal 1s to change weight distribution. */
void n64proc_uso_func_00000014(int arg0, int arg1) {
    register char *base = &D_00000000;
    register char *base10 = &D_00000000 + 0x10;
    register int *cur;
    register int flag = 0;
    register int one = 1;
    int r;

    do {
        if (arg1 == 0) {
            gl_func_00000000(base, one, 0, 0);
            flag = one;
            r = gl_func_00000000(0);
            gl_func_00000000(arg0, one, r);
        } else if (arg1 == one) {
            cur = (int*)gl_func_00000000(0, one, 0);
            flag = one;
            gl_func_00000000(base10, cur);
            if (*(int*)((char*)cur + 0x14) != 0) {
                *(int*)((char*)cur + 0x4) = one;
            }
            *(int*)((char*)cur + 0x14) = (int)base;
        }
        arg1 = *(int*)((char*)base + 0x40);
    } while (flag == 0);
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

