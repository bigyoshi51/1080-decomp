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
 * (1) TRIED 2026-04-21 (parallel agent): permuter random-mode, 3 minutes,
 * ~12k iterations. Best score 1030 — per the skill's score-band rubric,
 * "1000+ means structural issues remain." Best output just hoisted
 * `base+0x40` into a `new_var` local, didn't flip any $s-reg assignments.
 * Confirms the register-renumber is not reachable from random C-level
 * variation; target was likely compiled under a slightly different IDO
 * version/flag, or with manual `register T x asm("$N")` which IDO rejects.
 *
 * (3) TRIED 2026-04-21: removing the `register` keyword from all locals
 * (base, base10, cur, flag, one) regressed from ~95% to 33%. `register`
 * is ESSENTIAL for keeping these 6 pseudos in $s-regs vs stack-spilled.
 * The 33% cap matches IDO's default -O2 allocation where most of these
 * stay in stack slots. Don't remove the keyword.
 *
 * (4) TRIED 2026-04-21: `base10 = base + 0x10` (derive from base instead
 * of `&D_0 + 0x10`) — regressed to 33%. base+0x10 forces computation at
 * runtime instead of IDO's compile-time `addiu s4, s4, 0x10` pattern.
 *
 * (5) TRIED 2026-04-21: extra `one = 1;` statement inside if branch to
 * boost ref count — no change in match %.
 *
 * (6) TRIED 2026-04-21: decl reorder `cur, flag, one, base, base10`
 * (matching target's $s0..$s5 order) — IDENTICAL allocation output.
 * Confirms decl-source-order is decoupled from pseudo-number ordering
 * in IDO's RTL build (first-encountered-pseudo tiebreaker doesn't
 * correspond to C decl order). This rules out syntactic ordering as a
 * knob for the s2/s3 tiebreak between `one` and `base`.
 *
 * No remaining path reachable from C without inline-asm. NM-only. */
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
 * UPDATE 2026-04-21: the "lui+mtc1 not reproducible" claim was WRONG.
 * With this NM body (`buf[0] = buf[1] = buf[2] = buf[3] = 1.0f`), IDO
 * emits `lui $at, 0x3F80; mtc1 $at, $f0` BEFORE `addiu sp` — matching
 * target's pre-prologue pattern. The actual blockers are:
 *   1. Stack frame size: target 0x48, mine 0x38 (fixed w/ `char pad[16]`
 *      brings frame to 0x48 but shifts other offsets).
 *   2. Branch structure: target uses goto-style dispatch
 *        `beq v0,0,tag0; beq v0,1,tag1; b epi; tag0: ... b epi; tag1: ... b epi; epi`
 *      My natural `if (key==0) ... else if (key==1) ...` emits 2 branches
 *      but with different fall-through and no explicit `b epi` between arms.
 *   3. Spill pattern: target saves a3 (= a0) to 0x48(sp) before each jal;
 *      mine puts the save at 0x1C(sp) with 0x38 frame.
 * Try: rewrite with explicit `goto`s to k0_tag/k1_tag/end_tag + `char pad[16]`.
 * Multi-variant grind still required; keep NM until promoted to exact. */
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

