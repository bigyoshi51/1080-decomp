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

#ifdef NON_MATCHING
/* Dual-branch sub-struct dispatcher (49 insns, 0xC4).
 * Logic: switch on a0[0x50]:
 *   key == 0: operate on sub-struct at a0+0x58
 *   key == 1: operate on sub-struct at a0+0x70
 *   default:  no-op (epilogue)
 * Each branch does 3 gl_func calls with a pre-zeroed 4-float out-buffer
 * at sp+0x34..0x40 passed as the 3rd arg of the first call.
 *
 * MYSTERY: target has `swc1 $f0, 0x34..0x40(sp)` x4 at entry WITHOUT
 * a preceding `mtc1 $0, $f0` — meaning $f0 is inherited uninitialized
 * from caller, yet the 4 stores still happen. Any C that explicitly
 * zeros the buffer will emit the extra mtc1. Likely unreachable without
 * caller-coordinated $f0=0.0f or a specific IDO idiom I don't know yet.
 * Keep NM — compiled path remains INCLUDE_ASM. */
void n64proc_uso_func_00000364(char *a0) {
    float buf[4];  /* sp+0x34..0x40 — out-buffer for first gl_func call */
    int key = *(int*)(a0 + 0x50);
    int val;

    if (key == 0) {
        val = *(int*)(a0 + 0x54);
        gl_func_00000000(&D_00000000, val, buf);
        gl_func_00000000(a0 + 0x58);
        gl_func_00000000(a0 + 0x58, 0xA0, 0x78, 3);
    } else if (key == 1) {
        val = *(int*)(a0 + 0x54);
        gl_func_00000000(&D_00000000, val, buf);
        gl_func_00000000(a0 + 0x70);
        gl_func_00000000(a0 + 0x70, 0xA0, 0x78, 3);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000364);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso/n64proc_uso_func_00000364_pad.s")

