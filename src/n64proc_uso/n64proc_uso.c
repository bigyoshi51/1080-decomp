#include "common.h"

extern int gl_func_00000000();

/* USO entry-0: leading `beq zero,zero,+0x6F00` trampoline (loader-patched
 * at runtime) followed by an empty void body. The 4-byte trampoline is
 * injected post-cc via PREFIX_BYTES (Makefile + scripts/inject-prefix-bytes.py).
 * The body is just jr ra + nop (8 bytes); after injection the function
 * symbol covers the full 12 bytes target wants. */
void n64proc_uso_func_00000000(void) {
}

void n64proc_uso_func_0000000C(void) {
}

extern char D_00000000;

#ifdef NON_MATCHING
/* (12) TRIED 2026-05-04: INSN_PATCH eligibility check — built emits 67 insns
 * vs expected 59 (+8 insn delta from per-iteration `lui v1,0; lw v1,0x40(v1)`
 * fresh-lui+lo reload at loop_tail vs target's single `lw a1, 0x40(s3)`
 * indexed-via-$s form). Size mismatch blocks INSN_PATCH per
 * feedback_insn_patch_size_diff_blocked.md. Would need a recipe that GROWS
 * st_size + shifts symbols/relocs (not currently available). Stays at 74.49 %.
 *
 * Promoted to $s-reg allocation via `register` hints (2026-04-20).
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
 * (10) TRIED 2026-05-02 (later session): split decl-init from inline-
 * init (`register int one; ... one = 1;`). No change — confirms IDO's
 * allocator priority is purely refs/live-length-based, decl-init vs
 * later-init doesn't shift it. The s2/s3 swap is structurally fixed
 * given current IDO flag set; no C-level lever remaining.
 *
 * (11) TRIED 2026-05-02: goto-chain dispatch (per
 * feedback_ido_dispatch_goto_chain_beats_switch_and_ifelse.md, applied
 * to func_00000268 with 85→93 % gain). MASSIVE jump: 33.37 % → 74.49 %.
 * The goto-chain replaces if/else-if with explicit `if (==X) goto bodyN`
 * which lets IDO emit the target's 3-way beq dispatch with shared-arg
 * delay-slot setup (target shape `beq a1,zero,body0; or a0,base; beq
 * a1,one,body1; or a0,zero; beq zero,zero,end; lw a1,0x40(s3)`).
 *
 * Remaining 25 % is two structural diffs:
 *   (a) Same s2/s3 (one/base) and s4/s5 (base10/arg0-save) renumber as
 *       before — register allocation issue from variants (3)-(7), no
 *       reachable C-level lever per existing memos.
 *   (b) Loop-tail reload `arg1 = base[0x40]` — target uses indexed
 *       load `lw a1, 64(s3)` via base reg directly. IDO instead emits
 *       fresh `lui v1, %hi(D); lw v1, 0x40(v1)` because both ends are
 *       compile-time-constant addresses. Even though base is `register`-
 *       declared, IDO prefers a fresh constant-address load over the
 *       indexed-via-$s form. No C-level workaround found.
 *
 * (9) TRIED 2026-05-02: eliminate `flag` entirely; restructure as
 * `while (arg1 != 0 && arg1 != one) { arg1 = base->0x40; }` — REGRESSED to
 * 18.5 %. The structural change pushes IDO too far from target's do-while-
 * with-dispatch shape. The do-while + flag pattern IS load-bearing for the
 * register allocator's priority calc.
 *
 * Now at 74.49 % (variant 11). Remaining structural — see (11) note.
 *
 * (12) TRIED 2026-05-03: `register int *base = (int*)&D_00000000` + indexed
 * `arg1 = base[0x10]` — same 74.49 %, IDO still constant-folds the indexed
 * load through a fresh lui+lw rather than reusing the $s-reg holding base.
 *
 * (13) TRIED 2026-05-03: `arg1 = *(volatile int*)((char*)base + 0x40)` —
 * REGRESSED slightly to 74.24 %. Volatile defeats CSE on the load address
 * but introduces an extra $t-reg shuffle before the lw.
 *
 * (14) TRIED 2026-05-03: `register int *baseAt40 = (int*)(base + 0x40)` as
 * a separate $s-reg holding the precomputed pointer — same 74.49 %, IDO
 * either constant-folds baseAt40 (since base is constant) OR allocates it
 * to its own $s-reg without changing the loop_tail load shape.
 *
 * (15) TRIED 2026-05-03: `if ((int)base == 0) flag = 0;` no-op use of base
 * inserted at body1 tail to keep base live to loop_tail — REGRESSED to
 * 66.97 %. Adds a beq branch that throws off the dispatch arrangement.
 *
 * (16) CONFIRMED 2026-05-03: `__asm__ volatile(...)` inline asm REJECTED
 * by IDO cfe with "Syntax Error" — IDO does not parse the GCC inline-asm
 * extension at any form. Cannot use inline asm to force the loop_tail
 * load shape. Documented in feedback_ido_no_asm_barrier.md (existing) +
 * feedback_ido_constant_address_load_fold_inevitable.md (new this session).
 *
 * 16 variants total. Cap is structural per IDO -O2 constant-fold pass on
 * fixed-extern-derived pointer addresses. NM-only — accept.
 *
 * (17) 2026-05-04 RE-EVALUATED post-INSN_PATCH-infra: now that
 * scripts/patch-insn-bytes.py is wired, checked if the 74.49% fuzzy cap
 * could be patched to 100%. NO. Word-diff against expected/.o (NM build):
 * 57 of 59 instructions differ — fuzzy_match_percent overestimates
 * exactness; the actual byte-level shape diverges fundamentally from
 * insn 0x18 onward (different basic-block-fill, different jal call
 * order, even epilogue is partially shifted). INSN_PATCH is for ≤10
 * specific words, NOT structural rewrites. Confirmed cap holds.
 *
 * Other agents (b, c, e) checked: same C body, no INSN_PATCH attempt —
 * they hit the same wall. Genuine structural cap from IDO -O2 + the
 * 6-local register-allocation interaction that can't be flipped from C.
 *
 * (18) TRIED 2026-05-05: link-time-0 proxy extern hack to defeat
 * IDO -O2's constant-fold of base[0x40] back to fresh lui+lw. Approach:
 *   extern char D_n64proc_zero;  // mapped to 0x0 in undefined_syms_auto
 *   register char *base = &D_00000000 + (int)&D_n64proc_zero;
 *   register char *base10 = &D_00000000 + 0x10 + (int)&D_n64proc_zero;
 * Standalone .s confirms the structural fix WORKS: all 3 loop_tail
 * loads now emit as `lw a1, 0x40(s_base)` indexed-via-$s form — closes
 * the 8-insn delta to 5-insn (recovers 3 of 5 caps in residual diff (b)).
 * BUT: the proxy machinery (2 luis + 1 addu = 3 insns at function start)
 * shifts register allocation: base lands in $s1 instead of $s3, base10
 * in $s2 instead of $s4, etc. Net regression: 74.49 % -> 58.68 %.
 * Indexed-load gain (~5 insns) was outweighed by 6-way $s-reg renumber
 * (which scores far more diffs in objdiff).
 *
 * The proxy approach is the correct mechanism for the loop_tail load
 * but cannot be applied without paying a register-renumber penalty —
 * the proxy's addu introduces a new pseudo-source for $s1, perturbing
 * the priority queue. Variant 18 is therefore a documented dead-end:
 * the indexed-load fix CANNOT be combined with target's $s-numbering
 * via this proxy formulation. Stays at 74.49 %.
 *
 * (19) TRIED 2026-05-05: Proxy on `base` ONLY (not also `base10`) —
 * apply variant 18's link-time-0 trick to just the one local that needs
 * the indexed-load preservation, hoping the reduced perturbation (3 extra
 * insns vs 5) leaves enough register-allocation latitude for target's
 * $s-numbering. Result: 74.49 % → 69.02 %. Smaller regression than
 * variant 18 (which went to 58.68 %), but still net negative. Confirms
 * the proxy mechanism inherently disturbs the priority queue regardless
 * of which subset of locals it's applied to. The 5-pp loss from variant
 * 19 vs the 16-pp loss from variant 18 quantifies the per-proxy-extern
 * cost: each one introduces ~5pp of regression. CAP HOLDS at 74.49 %.
 *
 * (20) TRIED 2026-05-05: file-split to apply -O3 OPT_FLAGS instead of
 * default -O2. Hypothesis: maybe -O3's stronger optimization changes
 * the loop_tail load codegen or the register allocation. Sandbox-tested
 * standalone .c with `cc -O3`. Result: byte-IDENTICAL output to -O2 (67
 * insns, same 5-pp delta vs target). IDO -O3 differs from -O2 mostly in
 * inter-module opt (per cc's own warning: "-O3 ... use -j instead to get
 * inter-module"), which doesn't apply to a single-function compile. So
 * the file-split-with-OPT_FLAGS technique that worked for func_80008030
 * (-O1→-O2) doesn't help here — we're already at the ceiling for this
 * codegen problem within IDO's single-file optimization.
 *
 * (21) TRIED 2026-05-05 RE-RETEST: variant 7's `flag = 1;` literal
 * (instead of `flag = one;`) was tested AT 33% (pre-goto-chain). With
 * variant 11's goto-chain dispatch in place (current 75.02% baseline),
 * retested to see if the literal vs $s-reg-via-`one` distinction
 * matters for the post-dispatch flag store. Result: build/.o BYTES ARE
 * IDENTICAL between the two C forms (cmp = 0). Reason: `register int
 * one = 1;` IS a compile-time constant; IDO's constant-fold pass
 * propagates it through `flag = one;` and emits the same literal
 * `addiu s1, zero, 1` regardless of which C form is used. The
 * `register` keyword does NOT prevent constant folding when the
 * register's value is a known immediate. Variant doesn't help; the
 * current shape is what IDO produces in both cases.
 *
 * Score drift: doc previously said 74.49%; current build is 75.02%
 * (+0.5pp from upstream parallel-agent activity reshuffling expected/.o
 * baselines). Cap behavior unchanged. */
void n64proc_uso_func_00000014(int arg0, int arg1) {
    register char *base = &D_00000000;
    register char *base10 = &D_00000000 + 0x10;
    register int *cur;
    register int flag = 0;
    register int one = 1;
    int r;

loop_top:
    if (arg1 == 0) goto body0;
    if (arg1 == one) goto body1;
    goto loop_tail;
body0:
    gl_func_00000000(base, one, 0, 0);
    flag = one;
    r = gl_func_00000000(0);
    gl_func_00000000(arg0, one, r);
    goto loop_tail;
body1:
    cur = (int*)gl_func_00000000(0, one, 0);
    flag = one;
    gl_func_00000000(base10, cur);
    if (*(int*)((char*)cur + 0x14) != 0) {
        *(int*)((char*)cur + 0x4) = one;
    }
    *(int*)((char*)cur + 0x14) = (int)base;
loop_tail:
    arg1 = *(int*)((char*)base + 0x40);
    if (flag == 0) goto loop_top;
}
#else
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000014);
#endif

#ifdef NON_MATCHING
/* n64proc_uso_func_00000100: 76-insn TRIPLE-alloc-or-passthrough constructor.
 * 0x130 size, target frame 0x28; build frame 0x30 (1 extra spill slot).
 *
 * Logic: cascade of `x = prev; if (x == 0) { x = alloc(N); if (!x) goto end; }`
 *   p = a0; if (!p) { p = alloc(0x88); if (!p) goto end; }
 *   q = p;  if (!q) { q = alloc(0x50); if (!q) goto end; }   // dead arm
 *   r = q;  if (!r) { r = alloc(0x2C); if (!r) goto end; }   // dead arm
 *   helper(r, &D + 0xB0);
 *   r[0x28] = &D;
 *   q[0x28] = &D;
 *   p[0x28] = &D + 0x18;
 *   p[0xC]  = &D + 0xB8;
 *   helper(p);
 *   p[0x50] = 0; p[0x3C] = 0x64; p[0x54] = 0xFF;
 *   z = *(int*)(&D + 0x190);
 *   helper(p + 0x10, z);
 *   if (z[0x14] != 0) z[1] = 1;
 *   z[0x14] = p;
 *   helper(*(int*)(&D + 0x190));   // fresh load
 *   helper(0xA3);
 *   p[0x48] = 0; p[0x30] = 0; p[0x2C] = 0;
 *   end: return p;
 *
 * 2026-05-05 BIG PROMOTION: 73.33% -> 88.04% (+14.71pp) via THREE fixes:
 *
 *   FIX 1 (+4.64pp): Triple alloc-cascade. Previous wrap had only 2 cascade
 *   steps (`p = a0; q = alloc(0x50); r = q`). Target has 3: each step is
 *   `x = prev; if (!x) { x = alloc(N); if (!x) goto end; }`. The 2nd and 3rd
 *   bnez tests are dead-arm guards but IDO emits them. See
 *   feedback_alloc_or_passthrough_cascade_includes_dead_arms.md.
 *
 *   FIX 2 (+3.30pp): Defeat IDO -O2 CSE on &D base. Target emits 4 fresh
 *   `lui+addiu` pairs for the &D-derived stores (r[0x28]=&D, q[0x28]=&D,
 *   p[0x28]=&D+0x18, p[0xC]=&D+0xB8); inline `&D_00000000` form CSEs the
 *   base into v1. Recipe per feedback_unique_extern_with_offset_cast_breaks_cse.md:
 *   declare 5 unique externs (D_n64_100_a..e) all mapped to 0x0 in
 *   undefined_syms_auto.txt, write each access as `(char*)&D_n64_100_X + N`.
 *   IDO sees them as different symbols → no CSE.
 *
 *   FIX 3 (+6.78pp): Missing args on the post-conditional helper call. Target
 *   prepares `li a1, 2; move a2, zero` BEFORE the beqzl-and-store, then uses
 *   them in the jal at 0xFC. The C had `gl_func(*(int*)(&D + 0x190))` (1 arg);
 *   should be `gl_func(*(int*)(&D + 0x190), 2, 0)` (3 args).
 *
 * Remaining 12% diff (verified 2026-05-05 via objdump):
 *   1. Frame size: 0x30 (build) vs 0x28 (target) — build has 5 spill slots,
 *      target has 4. Build can't share q-spill slot with z-spill (live ranges
 *      overlap in build's allocation, not in target's).
 *   2. Register choice for q/r passthroughs: target uses a3 for q + a0 for r;
 *      build uses v1 for q + a2 for r. Cascades through ~15 insns of register-
 *      rename diff. `register` hint on q/r had no effect (88.04% identical).
 *   3. Spill ordering at first jal helper(r, &D+0xB0) — target's spill of a3
 *      to sp+0x24 in BD slot vs build's spill of a2 to sp+0x24 BEFORE jal.
 *
 * All three remaining caps are IDO regalloc-priority choices not reachable
 * from C-source modifications. */
extern int gl_func_00000000();
void *n64proc_uso_func_00000100(void *a0) {
    void *p;
    void *q;
    void *r;
    int *z;

    p = a0;
    if (p == 0) {
        p = (void*)gl_func_00000000(0x88);
        if (p == 0) goto end;
    }
    q = p;
    if (q == 0) {
        q = (void*)gl_func_00000000(0x50);
        if (q == 0) goto end;
    }
    r = q;
    if (r == 0) {
        r = (void*)gl_func_00000000(0x2C);
        if (r == 0) goto end;
    }
    {
        extern char D_n64_100_a, D_n64_100_b, D_n64_100_c, D_n64_100_d, D_n64_100_e;
        gl_func_00000000(r, (char*)&D_n64_100_a + 0xB0);
        *(int*)((char*)r + 0x28) = (int)&D_n64_100_b;
        *(int*)((char*)q + 0x28) = (int)&D_n64_100_c;
        *(int*)((char*)p + 0x28) = (int)((char*)&D_n64_100_d + 0x18);
        *(int*)((char*)p + 0xC)  = (int)((char*)&D_n64_100_e + 0xB8);
    }
    gl_func_00000000(p);

    *(int*)((char*)p + 0x50) = 0;
    *(int*)((char*)p + 0x3C) = 0x64;
    *(int*)((char*)p + 0x54) = 0xFF;
    {
        extern char D_n64_100_f;
        z = *(int**)((char*)&D_n64_100_f + 0x190);
    }
    gl_func_00000000((char*)p + 0x10, z);

    if (z[0x14 / 4] != 0) z[1] = 1;
    z[0x14 / 4] = (int)p;
    {
        extern char D_n64_100_f;
        gl_func_00000000(*(int*)((char*)&D_n64_100_f + 0x190), 2, 0);
    }
    gl_func_00000000(0xA3);
    *(int*)((char*)p + 0x48) = 0;
    *(int*)((char*)p + 0x30) = 0;
    *(int*)((char*)p + 0x2C) = 0;
end:
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000100);
#endif

void n64proc_uso_func_00000230(char *a0) {
    gl_func_00000000(a0 + 0x58, 6);
    gl_func_00000000(a0 + 0x70, 3);
}

#ifdef NON_MATCHING
/* (e) TRIED 2026-05-04: INSN_PATCH eligibility check — built 60 insns vs
 * expected 61 (+1 insn delta), and 52 of 60 insns differ due to register
 * cascade. The +1 delta comes from the second dispatch: built picks
 * `bnel v0,at,end` with `lw ra,20(sp)` epilogue-prep in delay slot;
 * expected picks `beql v0,at,c1` with `lw t5,84(a3)` c1-body-preload in
 * delay slot. Same branch target, opposite polarity. The body-preload
 * cascades through register choices (expected uses t6/t5/t8 throughout
 * c1 body where built uses v0/t9/etc). INSN_PATCH can't repair: size
 * differs AND each subsequent insn has different opcode bits (not just
 * register renames at fixed offsets). Stays at 93.57%.
 *
 * State machine on a0->0x50:
 *   case 0: decrement a0->0x3C; if dropped below 16, decay a0->0x54 by 16
 *           (clamp >= 0); when a0->0x3C hits 0, transition to mode 1
 *           (a0->0x50 = 1) and reset a0->0x3C = 100.
 *   case 1: ramp a0->0x54 by 8 (clamp <= 255); decrement a0->0x3C; on 0,
 *           OR if (a0->0x3C < 0x55 AND gl_func(&D, 0x40100) != 0), set
 *           D[0x40] = 1 and call gl_func(a0, 0, 0).
 *
 * 2026-05-02: applied goto-chain dispatch per
 * feedback_ido_dispatch_goto_chain_beats_switch_and_ifelse.md.
 * Match jumped from 85.25% (if-else-if form) to 93.57%.
 *
 * Remaining 6.4% diff (verified 2026-05-02 via objdump -M no-aliases):
 *   1. First dispatch beql preload IS reached: mine `beql v0,zero,c0_body`
 *      + delay-slot `lw v0, 60(a3)` matches target's beql + lw t6, 60(a3)
 *      shape; only the destination register differs ($v0 vs $t6).
 *   2. Second dispatch IDO picks bnel-skip-to-end (with `lw ra` epilogue
 *      restore in delay slot) where target picks beql-jump-to-c1-body
 *      (with `lw t5, 0x54(a3)` body-preload). Both arms have valid
 *      delay-slot fillers so IDO chooses based on internal heuristic
 *      (likely "early-return is hotter than body").
 *   3. The body-register cascade: target uses fresh $t6/$t7/$t9/$t3/$t4/
 *      $t0/$t2/$t5/$t8 throughout each body. Mine reuses $v0 because the
 *      dispatch loaded into $v0 (single-use of `t = a0[0x3C/4] - 1` as one
 *      expression collapses both load + subtract into $v0).
 *
 * 2026-05-02: tried 4 more variants. None promote.
 *   (a) Split `t = a0[0x3C/4] - 1` into `int load = ...; int decr = load - 1;`
 *       — IDO picked $v1+$v0 (not $t6+$t7) for the named locals; promoted
 *       a couple constants to $t-regs but lost the $t-reg promotion for
 *       the body's primary load. Net: regressed body register choice.
 *   (b) Replace `goto end` with `return` — byte-identical output. Same
 *       early-return optimization either way.
 *   (c) Reorder bodies (c1 before c0 in source) — case-1 body becomes the
 *       fall-through after dispatch chain, but second dispatch STILL emits
 *       bnel-skip-to-end. The body-block placement doesn't influence the
 *       branch-likely arm choice.
 *   (d) Clean if-else-if (no goto): `if (v==0){...} else if (v==1){...}`
 *       — fully regressed; IDO loses the beql + body-preload pattern
 *       entirely, emits plain `bne v0,zero,+X`. Goto-chain is strictly
 *       better for this shape.
 *
 * Per feedback_ido_sparse_switch_beql_preload_unreachable.md (and the
 * 4 attempts above), no further C-level lever flips IDO's bnel/beql
 * choice on the second dispatch. Stays at 93.57 %.
 *
 * 2026-05-03 re-measure: 93.34 % (slight drift from parallel-agent commits
 * affecting siblings; nothing structural).
 *
 * 2026-05-04: re-measure 93.57 % (back to original). Two more variants
 * tried, both no-op:
 *   (e) `register int t` qualifier on the body's working local — no
 *       effect on body cascade $t-reg picks. IDO already promotes `t`
 *       past stack; the `register` hint is redundant. % unchanged.
 *   (f) Inline dispatch reads `if (a0[0x50/4] == 0) goto c0;` (no named
 *       `v` local) — IDO still picks the same bnel-skip-to-end at the
 *       second dispatch. The named-vs-inline distinction (per
 *       feedback_ido_inline_deref_v0.md / feedback_ido_v0_reuse_via_locals.md)
 *       affects $v0/$t-reg destination, not the dispatch arm choice.
 *       % unchanged at 93.57 %.
 *
 * Six C-form variants tried total ((a)-(f)). Cap stands at 93.57 %.
 *
 * 2026-05-04 (NEW): four more variants tried, all 52/61 word diffs (no
 * promotion). Cap reconfirmed:
 *   (g) Goto-form for c1 inner (`if (t == 0) goto fire;` + early-out
 *       gotos for the && short-circuit condition) instead of compound
 *       `||`/`&&` form — same diff count.
 *   (m) Unique externs (D_n64proc_268_a / _b at 0x0) for the &D loads
 *       to break possible CSE — no effect; the bottleneck isn't &D-CSE
 *       (only 2 sites total; CSE wasn't happening to begin with).
 *   (n) Inline dispatch (no `v` local; `if (a0[0x50/4]==0) goto c0;`
 *       repeated) — per memo `feedback_ido_inline_deref_v0.md` should
 *       affect $v0/$t-reg destination but didn't here. Same 52 diffs.
 *   (o) `char pad[4]` to grow stack frame — IDO optimized it away
 *       (unused). Frame stays at 0x18.
 *
 * Total: 10 variants tried ((a)-(f) + (g)/(m)/(n)/(o)). Cap holds at
 * 93.57 %. The first-instruction divergence at 0x18 is `lw $t6` (target)
 * vs `lw $v0` (build) — IDO's allocator reuses the dispatch register
 * for the body's first load, where target uses a fresh $t-reg. No
 * C-level lever found to force the fresh-$t allocation. */
void n64proc_uso_func_00000268(int *a0) {
    int v;
    int t;

    v = a0[0x50/4];
    if (v == 0) goto c0;
    if (v == 1) goto c1;
    goto end;
c0:
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
    goto end;
c1:
    t = a0[0x54/4] + 8;
    a0[0x54/4] = t;
    if (t >= 0x100) a0[0x54/4] = 0xFF;
    t = a0[0x3C/4] - 1;
    a0[0x3C/4] = t;
    if (t == 0 || (t < 0x55 && gl_func_00000000(&D_00000000, 0x40100) != 0)) {
        *(int*)((char*)&D_00000000 + 0x40) = 1;
        gl_func_00000000(a0, 0, 0);
    }
end:
    ;
}
#else
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000268);
#endif

#ifdef NON_MATCHING
/* (NEW 2026-05-04) INSN_PATCH eligibility check: built 50 insns vs expected
 * 51 (+1 delta) + 21 differing insns. Size mismatch blocks INSN_PATCH per
 * feedback_insn_patch_size_diff_blocked.md. The IDO k0/k1 block-reorder is
 * a structural shift, not a per-offset rename. Wrap doc's "~98% via unique
 * externs (mechanical)" path remains the only forward move. Stays at 95.51%.
 *
 * Dual-branch sub-struct dispatcher (51 insns, 0xCC after prologue-stolen fix).
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
 * target's pre-prologue pattern.
 *
 * UPDATE 2026-05-03: re-measured at 95.51 % (was 94.86 %); small drift from
 * unrelated source changes. Re-measure 2026-05-03 (later): 94.86 % again
 * (drifted back). Tried `char *spill_a0 = a0 + 0x58;` named-local variant
 * inside both k0/k1 blocks to force a0 spill location — REGRESSED to
 * 95.27 %. The named local pulls computation forward into a slot that
 * conflicts with IDO's natural a0 reuse, breaking 1 byte but unlocking 0.
 *
 * UPDATE 2026-05-02: applied the suggested fix (explicit `goto k0/k1/end`
 * + split pad layout). Match jumped 79.7 % → 94.86 %.
 *   - `char pad1[4]` BEFORE buf[4] + `char pad2[12]` AFTER all locals
 *     gives frame=0x48 with buf at sp+0x34 (matches target). Pad before
 *     buf shifts buf 4 bytes UP (consumes 4 bytes of top-of-frame), and
 *     pad2[12] keeps total padding at 16 bytes (16-byte alignment-rounded
 *     to 0x10 frame growth from 0x38 → 0x48).
 *   - Goto-style emits `beq v0,zero,k0; beq v0,at,k1; b epi` exactly
 *     as target wants for the dispatch.
 *
 * Remaining 4 mismatches (all structural, IDO basic-block reorder):
 *   1. IDO swaps k0/k1 BLOCK ORDER in emit: emits k1 body at 0x39C and k0
 *      body at 0x3D8. Target wants k0 first (0x3A4) then k1 (0x3E0).
 *      Inverts second branch from `beq v0,at,k1` to `bne v0,at,end`
 *      because k1 becomes fall-through after the bne. Source order has
 *      k0 body FIRST in C source — IDO reorders blocks anyway, likely
 *      because the `else` arm of the second test is a single fall-through
 *      whereas k1 body is "longer".
 *   2. Spill of a0 across third jal at sp+0x1c (mine) vs sp+0x18 (target).
 *      4 bytes off — `pad2[8]` collapses frame to 0x40, regressing other
 *      offsets. Spill location depends on where IDO finds free local slot;
 *      can't directly control without changing local layout.
 *   3-4. Two `jal gl_func_00000000` and two `lui/addiu D_00000000` symbol
 *      reloc diffs — same usoplaceholder issue affecting many wrapped
 *      functions; would need per-call extern aliases per
 *      feedback_usoplaceholder_unique_extern.md.
 *
 * No further C-level structural variation will flip IDO's k0/k1 block
 * reorder — that's reorg.c-equivalent post-RTL behavior. Marginal gains
 * may come from per-call unique externs (mechanical), bringing it to ~98 %.
 * Keep NM. */
void n64proc_uso_func_0000035C(char *a0) {
    char pad1[4];
    float buf[4];
    int key;
    int val;
    char pad2[12];
    buf[0] = 1.0f;
    buf[1] = 1.0f;
    buf[2] = 1.0f;
    buf[3] = 1.0f;
    key = *(int*)(a0 + 0x50);
    if (key == 0) goto k0;
    if (key == 1) goto k1;
    goto end;
k0:
    val = *(int*)(a0 + 0x54);
    gl_func_00000000(&D_00000000, val, buf);
    gl_func_00000000(a0 + 0x58);
    gl_func_00000000(a0 + 0x58, 0xA0, 0x78, 3);
    goto end;
k1:
    val = *(int*)(a0 + 0x54);
    gl_func_00000000(&D_00000000, val, buf);
    gl_func_00000000(a0 + 0x70);
    gl_func_00000000(a0 + 0x70, 0xA0, 0x78, 3);
end:
    ;
}
#else
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_0000035C);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso/n64proc_uso_func_0000035C_pad.s")

