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
 * (7) TRIED 2026-04-21: `flag = 1;` (literal) instead of `flag = one;`
 * at both sites — to reduce `one`'s ref count so the allocator might
 * demote it past `base` in the $s-reg priority queue. No change:
 * both the original `flag = one` body AND the `flag = 1` body now
 * compile to 33% match, not the ~95% that the earlier (1)-(6) notes
 * claim. Verified via objdump -M no-aliases of build/.o with
 * `CPPFLAGS=-DNON_MATCHING`: current output has TWO $s-reg swaps
 * vs target, not just one — (s2/s3: base/one) AND (s4/s5: base10/
 * arg0-save). The historical "register keyword promotes to ~95%"
 * claim no longer reproduces; the 6-local $s-reg allocation is no
 * longer happening even with `register` everywhere. Something in
 * IDO/asm-processor/flags changed since (1)-(6) were measured.
 * Target 7th attempt is correct in logic but can't flip either swap.
 *
 * (8) TRIED 2026-05-02: `while (1) { ... if (flag != 0) break; }` form
 * (no do-while). Marginal: 33.07 % -> 33.69 %. Different loop-back
 * branch encoding accounts for the small gain (1 extra insn aligned).
 * Adopted because it's strictly better and same logic. The 6-local
 * $s-reg allocation is still mis-numbered.
 *
 * (9) TRIED 2026-05-02: eliminate `flag` entirely; restructure as
 * `while (arg1 != 0 && arg1 != one) { arg1 = base->0x40; } if (arg1==0)
 * branch1 else branch2; arg1 = base->0x40;` — REGRESSED to 18.5 %. The
 * structural change pushes IDO too far from target's do-while-with-
 * dispatch shape. The do-while + flag pattern IS load-bearing for the
 * register allocator's priority calc.
 *
 * No remaining path reachable from C without inline-asm. NM-only. */
void n64proc_uso_func_00000014(int arg0, int arg1) {
    register char *base = &D_00000000;
    register char *base10 = &D_00000000 + 0x10;
    register int *cur;
    register int flag = 0;
    register int one = 1;
    int r;

    while (1) {
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
        if (flag != 0) break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000014);
#endif

INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000100);

void n64proc_uso_func_00000230(char *a0) {
    gl_func_00000000(a0 + 0x58, 6);
    gl_func_00000000(a0 + 0x70, 3);
}

#ifdef NON_MATCHING
/* State machine on a0->0x50:
 *   case 0: decrement a0->0x3C; if dropped below 16, decay a0->0x54 by 16
 *           (clamp >= 0); when a0->0x3C hits 0, transition to mode 1
 *           (a0->0x50 = 1) and reset a0->0x3C = 100.
 *   case 1: ramp a0->0x54 by 8 (clamp <= 255); decrement a0->0x3C; on 0,
 *           OR if (a0->0x3C < 0x55 AND gl_func(&D, 0x40100) != 0), set
 *           D[0x40] = 1 and call gl_func(a0, 0, 0).
 *
 * Cap: NM body emits std bne if-else (59 insns); target uses 3-arm beql
 * dispatch with delay-slot pre-loads + a dead `lw t6` at offset 0x294
 * (61 insns). Switch is rejected (1080 discards .rodata jumptables per
 * feedback_ido_switch_rodata_jumptable.md), so beql dispatch is unreachable
 * from C. Logic confirmed equivalent. */
void n64proc_uso_func_00000268(int *a0) {
    int v;
    int t;

    v = a0[0x50/4];
    if (v == 0) {
        t = a0[0x3C/4] - 1;
        a0[0x3C/4] = t;
        if (t < 0x10) {
            t = a0[0x54/4] - 0x10;
            a0[0x54/4] = t;
            if (t < 0) a0[0x54/4] = 0;
            if (a0[0x3C/4] == 0) {
                a0[0x50/4] = 1;
                a0[0x3C/4] = 0x64;
            }
        }
    } else if (v == 1) {
        t = a0[0x54/4] + 8;
        a0[0x54/4] = t;
        if (t >= 0x100) a0[0x54/4] = 0xFF;
        t = a0[0x3C/4] - 1;
        a0[0x3C/4] = t;
        if (t == 0 || (t < 0x55 && gl_func_00000000(&D_00000000, 0x40100) != 0)) {
            *(int*)((char*)&D_00000000 + 0x40) = 1;
            gl_func_00000000(a0, 0, 0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000268);
#endif

#ifdef NON_MATCHING
/* Dual-branch sub-struct dispatcher (51 insns, 0xCC after prologue-stolen fix).
 * Prior "MYSTERY" (swc1 $f0 without preceding mtc1) resolved 2026-04-20:
 * splat had mis-attributed the function's base-pointer prologue
 * `lui $at, 0x3F80; mtc1 $at, $f0` to the predecessor (func_00000268)'s
 * trailing bytes. Reverse-merged so this function now starts at 0x35C
 * with $f0 = 1.0f initialized up-front, then stored to buf[4] at sp+0x34.
 * See feedback_splat_prologue_stolen_by_predecessor.md.
 *
 * UPDATE 2026-05-02: 80.3 % -> 99.88 % via `switch (key) { case 0: ... case 1: ... }`
 * + `char pad[16]`. The switch produces the target's 3-branch dispatch
 * `beq v0,0,k0; beq v0,1,k1; b end` (vs the if-else's inverted `bne` form);
 * `char pad[16]` brings frame to 0x48 with caller-arg-slot a3 spill at
 * sp+0x48. ALL the structural diffs are gone — only buf offset remains.
 *
 * Remaining 0.12 % cap: `float buf[4]` lands at sp+0x28 in mine vs sp+0x34
 * in target. Diff is 12 bytes / 1-instruction-class pattern (3 places: 4
 * swc1 init stores + 2 `addiu a2, sp, OFFSET` to pass buf to gl_func).
 *
 * Tried (2026-05-02): pad[20], pad[24], pad[28], int pad[N], buf-decl-first,
 * pad-decl-first w/ split pad before+after buf, int buf[4] cast-to-float —
 * none of these placed buf at exactly sp+0x34 with frame=0x48. IDO's local
 * allocator picks 8-byte-aligned slots for `float[4]` (sp+0x28 or sp+0x38),
 * never sp+0x34 (which is 4-aligned but not 8-aligned). Target probably had
 * a non-aligned reason — maybe an earlier-decl variable that's now optimized
 * away but reserved its slot. Unreproducible from C w/o asm tricks. */
void n64proc_uso_func_0000035C(char *a0) {
    char pad[16];
    float buf[4];
    int key;
    int val;
    buf[0] = 1.0f;
    buf[1] = 1.0f;
    buf[2] = 1.0f;
    buf[3] = 1.0f;
    key = *(int*)(a0 + 0x50);
    switch (key) {
    case 0:
        val = *(int*)(a0 + 0x54);
        gl_func_00000000(&D_00000000, val, buf);
        gl_func_00000000(a0 + 0x58);
        gl_func_00000000(a0 + 0x58, 0xA0, 0x78, 3);
        break;
    case 1:
        val = *(int*)(a0 + 0x54);
        gl_func_00000000(&D_00000000, val, buf);
        gl_func_00000000(a0 + 0x70);
        gl_func_00000000(a0 + 0x70, 0xA0, 0x78, 3);
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_0000035C);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso/n64proc_uso_func_0000035C_pad.s")

