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
 * (2) TRIED 2026-04-20: eliminating `one` local and using literal 1s made
 * the diff worse (regressed to 5+ register-renumber mismatches vs the
 * current 4). `one` as a named local IS needed to keep its $s-reg
 * allocation. Allocator's refs-weight gives `one` to $s3, target gives
 * it to $s2 — decl-order is a no-op per sreg_order_not_decl_driven memo.
 *
 * Remaining path: (1) permuter-only. */
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
/* Dual-branch sub-struct dispatcher (51 insns, 0xCC after prologue-stolen fix).
 * Prior "MYSTERY" (swc1 $f0 without preceding mtc1) resolved 2026-04-20:
 * splat had mis-attributed the function's base-pointer prologue
 * `lui $at, 0x3F80; mtc1 $at, $f0` to the predecessor (func_00000268)'s
 * trailing bytes. Reverse-merged so this function now starts at 0x35C
 * with $f0 = 1.0f initialized up-front, then stored to buf[4] at sp+0x34.
 * See feedback_splat_prologue_stolen_by_predecessor.md.
 *
 * The pre-prologue `lui+mtc1` pattern is not reproducible from standard C
 * — IDO emits the mtc1 AFTER the addiu sp, not before. Keep NM. */
void n64proc_uso_func_0000035C(char *a0) {
    float buf[4];
    int key;
    int val;
    buf[0] = 1.0f;
    buf[1] = 1.0f;
    buf[2] = 1.0f;
    buf[3] = 1.0f;
    key = *(int*)(a0 + 0x50);
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
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_0000035C);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso/n64proc_uso_func_0000035C_pad.s")

