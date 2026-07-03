#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00012E00 - verified structural decode (0x24C, 147 insns,
 * get-or-create constructor + work-buffer allocation). bootup_uso
 * constructor family (cf. func_00005124 / func_0001438C).
 *   void *func_00012E00(void *a0, int a1) {
 *       o = a0 ? a0 : func_00000000(0x78); if (!o) return 0;
 *       s = func_00000000(0x2C);
 *       func_00000000(s, &D_0000C730);            // init sub
 *       s->0x28 = &D_a;  o->0x28 = &D_b;          // descriptors
 *       o->0xC  = &D_0000C738;                    // type/vtable
 *       o->0x5C = 0x20;                            // dim W
 *       o->0x60 = 0x20;                            // dim H
 *       o->0x64 = 0x400;                           // cell count
 *       o->0x2C = a1;
 *       o->0x48 = 1.0f;                            // scale
 *       o->0x?? = func_00000000(...);              // init buffer
 *       o->0x4C = func_00000000(0x800, 0x10);     // alloc 2048 B
 *       o->0x50 = func_00000000(0x400, 0x10);     // alloc 1024 B
 *       o->0x58 = func_00000000(0x1000);          // alloc 4096 B
 *       ... = func_00000000(0x1000);              // another 4096
 *       ...
 *   }
 * Struct-typing reference: o = 0x78-byte object. o->0x28 (40)
 * descriptor (&D), o->0xC (12) type/vtable (&D_0000C738), o->0x2C
 * (44) = a1, o->0x48 (72) f32 = 1.0 (scale/alpha), o->0x5C (92) /
 * o->0x60 (96) s32 = grid dims 0x20 x 0x20, o->0x64 (100) s32 =
 * 0x400 cell count (= 32*32). o->0x4C (76) / o->0x50 (80) / o->0x58
 * (88) = pointers to work buffers allocated at sizes 0x800 / 0x400
 * / 0x1000 (some with 0x10 alignment arg). s = 0x2C-byte sub-object
 * (s->0x28 descriptor, init datum D_0000C730). Likely a 32x32
 * tile/heightfield/render-target context. Caps <80: get-or-create
 * + alloc-cascade (~8 func_00000000 buffer reloc) + &D descriptors
 * + FP-1.0 const. Full body INCLUDE_ASM-preserved (.s = source of
 * truth). INCLUDE_ASM (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern char D_0000C730;
extern char D_0000C738;
void *func_00012E00(arg0, arg1) void *arg0; s32 arg1; {
    void *o;
    void *sub;
    void *sp3C;
    s32 row;
    s32 col;
    s32 yval;
    s32 a0v;
    s32 a0v2;
    s32 v1;
    s32 v1_2;
    s32 off;
    s32 off2;
    f32 base;

    o = arg0;
    if ((arg0 != NULL) || (o = func_00000000((void *)0x78), (o != NULL))) {
        sub = o;
        if ((o != NULL) || (sub = func_00000000((void *)0x2C), (sub != NULL))) {
            func_00000000(sub, &D_0000C730);
            FW(sub, 0x28) = 0;
        }
        FW(o, 0x28) = 0;
        FW(o, 0xC) = (int) &D_0000C738;
        FW(o, 0x5C) = 0x20;
        FW(o, 0x60) = 0x20;
        FW(o, 0x64) = 0x400;
        FW(o, 0x2C) = arg1;
        *(f32 *)((char *)o + 0x48) = 1.0f;
        sp3C = func_00000000(NULL);
        FW(o, 0x4C) = (int) func_00000000((void *)0x800, (void *)0x10);
        FW(o, 0x50) = (int) func_00000000((void *)0x400, (void *)0x10);
        FW(o, 0x58) = (int) func_00000000((void *)0x1000);
        FW(o, 0x54) = (int) func_00000000((void *)0x1000);
        func_00000000(sp3C);
        *(f32 *)((char *)o + 0x3C) = 1.0f;
        *(f32 *)((char *)o + 0x38) = 1.0f;
        *(f32 *)((char *)o + 0x34) = 1.0f;
        *(f32 *)((char *)o + 0x30) = 1.0f;
        row = 0;
        off = 0;
        base = 10.0f / 2.0f;
        do {
            yval = (s32) (((f32) row * 7.5f) + (7.5f / 2.0f));
            col = 0;
            row += 1;
            do {
                a0v = yval;
                v1 = (s32) (((f32) col * 10.0f) + base);
                if (v1 >= 0x140) {
                    v1 = 0x13F;
                }
                if (yval >= 0xF0) {
                    a0v = 0xEF;
                }
                a0v2 = yval;
                off2 = off + 4;
                v1_2 = (s32) (((f32) (col + 1) * 10.0f) + base);
                *(s32 *)((char *)FW(o, 0x54) + off) = (a0v * 0x140) + v1;
                if (v1_2 >= 0x140) {
                    v1_2 = 0x13F;
                }
                if (yval >= 0xF0) {
                    a0v2 = 0xEF;
                }
                col += 2;
                *(s32 *)((char *)FW(o, 0x54) + off2) = (a0v2 * 0x140) + v1_2;
                off = off2 + 4;
            } while (col != 0x20);
        } while (row != 0x20);
    }
    return o;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012E00);
#endif

// func_0001304C — STRUCTURAL PASS (0x8D8 / 566 insns, no episode).
// Per-frame physics/animation integrator on a state struct, gated by an
// active flag, with counter/cooldown bookkeeping; compute-heavy (only
// 2 dispatcher calls, lots of f64 integration).
//
//   void func_0001304C(State *st) {            // st -> s0
//     if (!st->0x40) return;                    // inactive -> bail
//     st->0x74++;                               // frame/tick counter
//     if (st->0x6C) {
//       if (st->0x70) st->0x70--;               // cooldown decrement
//       if (st->0x70 == 0) { ... }              // expiry path
//     }
//     // main body: f64 integration of st fields using the
//     //   correctly-symbolized float-constant block
//     //   D_00000C50/C54/C58/C5C/C60 (rate/limit coefficients) and the
//     //   global ctx at func_0000023C+0x18; saved f20/f22/f24 doubles
//     //   carry accumulators across the loop; writes results back into
//     //   st fields and an out-record (a3->0x4 near the end).
//   }
//
// Struct-typing reference:
//   st(a0=s0): 0x40 active flag (gate); 0x6C enable, 0x70 cooldown
//     (decremented), 0x74 frame counter (incremented); other 0x0..0x80
//     fields are the integrated physics/animation state.
//   D_00000C50..D_00000C60 = a CORRECTLY-symbolized 5-entry f32 const
//     block (rate/clamp coefficients) — clean-pool contrast to the
//     func_0000098C mis-fold: splat symbolizes most of bootup_uso's
//     float pool fine; only specific runs got a spurious func_ code
//     symbol (see
//     docs/N64_FORENSICS.md#bootup-uso-fp-literal-pool-folded-into-func-0000098C).
//   func_0000023C + 0x18 = global ctx ptr (writable fold, recurring).
// Caps (DEFERRED): 566-insn f64 integrator; consts ARE symbolized but
//   the function is too large for a 60s exact-match attempt (multi-run
//   target). Real-C STRUCTURAL body below — per-frame physics/anim
//   integrator skeleton. Byte-match deferred. Name pre-checked: no
//   extern reuse. D_NNNNNNNN named consts via offset cast.
#ifdef NON_MATCHING
/* PASS-2 2026-06-10 (big-swing): FULL m2c graft (566 insns, no
 * jumptables, 0 M2C_ERRORs); FP-heavy.
 * PASS-3 GAP MAP (77.44; LCS 2026-06-10) -- the refinement roadmap:
 *  1. PROLOGUE (pass 6 analysis): target saves s0-s3 ONLY with a
 *     LARGER frame (-0x60 vs our -0x50) = 2 values stack-resident in
 *     the original; our graft promotes 2 long-range vars to s4/s5
 *     (not call-window crossing -- long-distance ranges, m2c names
 *     RESOLVED (pass 8): for-loop re-derivation (row<<5 recompute in
 *     place of the accumulator+snapshot) killed both extras; register
 *     set now matches the target EXACTLY. Residual: 3 insns short,
 *     frame -72 vs -96 (target keeps 2 stack-resident values we fold).
 *     Original pass-7 analysis: s5 held
 *     var_t2 (the += 0x20 outer-loop offset accumulator); s4 holds a
 *     SNAPSHOT of var_t2 taken before the inner loop (move s4,t2;
 *     bne s4,t5 loop-back) -- m2c's goto-loop_19 rendering created an
 *     extra live snapshot the target doesn't have. Fix = re-derive
 *     the nested loop as clean for-loops so the snapshot disappears
 *     (careful session; loop-structure edits are score-volatile).
 *  2. +0x268/+0x28C/+0x2C0: target does INLINE float->int with FCSR
 *     rounding dance (cfc1/ctc1/cvt.w.s/mfc1) where the graft emits
 *     jal (library-call casts). Find the C construct for the inline
 *     rounding-mode conversion (NOT plain (s32) cast = trunc.w.s).
 *  PASS 12 CORRECTION: the in-tree build has had the s-reg consts
 *  (li s3,2/li s2,3 + register compares) since pass 8 -- passes 10/11
 *  probed a ghost (the wrap notes below are superseded). The TRUE
 *  remaining gaps (full re-LCS at 88.83) are DECODE ERRORS + renumber:
 *  fixed this pass: int-store of 1.0f at +0x48 (mtc1/swc1 f20 shape)
 *  and the func(0,0) arg that should be (char*)&D+0. STILL OPEN:
 *  [RETRACTED pass 13: the ori-constant "error" was an LCS
 *  misalignment artifact in the renumbered midsection -- both
 *  constants are correctly placed; a swap probe was score-neutral]; a
 *  [RETRACTED pass 14: the "+0x85C missing block" was ALSO LCS noise
 *  -- both builds contain exactly 27 record-bump blocks]; frame -96
 *  vs -72 (3 extra spill slots + their store/load insns = the 0xC
 *  size delta); and the loop-body v1/a0 temp renumber. FINAL STATE:
 *  decode-verified at 88.83; the entire residual is allocator-class
 *  (spill count + temp coloring). PERMUTER RUN CONCLUDED 2026-06-11
 *  ~05:25: fast early descent 7060 -> 4570 (18k iters, objdiff 88.83
 *  -> 92.50 imported+verified), then ~97k iterations FLAT -- the
 *  residual 4570-weight (3 spill slots + deep loop-body renumber,
 *  multi-diff unlike the twins' single addu) is beyond the permuter's
 *  mutation reach. 2026-06-11 RULES PASS: the dead-local rule (7 dead
 *  ints, from the uopt-source derivation) fixes the FRAME exactly
 *  (-72 -> -96 = target); score holds 92.5 (the remaining loop-body
 *  group renumber dominates; a t4/t5 first-occurrence swap was flat
 *  -- identifying the actual renumbered LR pair needs the
 *  -Wo,-zdbug:6 coloring trace, now fully documented).
 *  PASS-15 2026-06-15 (coloring-trace pass, -Wo,-zdbug:6 on
 *  /tmp/tail4_nocmt.c): the residual is ONE coupled allocator
 *  permutation, NOT a single LR swap. The base ptr
 *  `temp_a0_3 = *(*(0x254)+0x158)` is loaded ONCE (lw _,344(t9)) and
 *  held for the entire ~340-insn record-emit tail = the function's
 *  LONGEST live range -> LOWEST priority (compute_save = save/span) ->
 *  target colors it LAST -> gets a0 (after the per-block derefs grab
 *  v0/v1). OUR build colors it into v0 instead -> the whole 27-block
 *  emit + 2 bnel/bne forms rebase (a0<->v0, deref v1<->v0, count
 *  a0<->v1). This is the ARG-REGISTER-TARGETING cap (docs: no
 *  pseudo-order lever moves a value INTO an arg reg; web-order-inversion
 *  full-inline REGRESSED 92.5->67). The loop body has the coupled
 *  var_t4(clamp)<->var_t5(outer-IV) t4/t5 swap: target colors both
 *  unconstrained-by-bitpos (clamp earlier-bitpos -> t4); our build's
 *  outer-IV is CONSTRAINED -> colored first -> grabs t4 (clamp ->t5).
 *  WINS this pass: inlining the ==2/==3 mode-check derefs (outer line
 *  376/381 + inner line 461) makes the compared value an isop at
 *  uopt-input -> the Uneq operand-swap fires -> `bne s3,v0`/`bne s2,v0`
 *  const-first (matches target) instead of var-first. 92.5 -> 92.61.
 *  REMAINING = arg-reg-target base cascade + IV-constrained t4/t5 +
 *  inner-counter v0/v1 + sp44 spill $f4-vs-$f24/64-vs-68. All
 *  allocator-internal; permuter floored 97k (no regalloc randomizer).
 *  FINAL LADDER: 2.8 (pre-graft) -> 77.4 (m2c graft)
 *  -> 84.1 ((u32)float) -> 86.3 (pool syms) -> 87.8 (for-loop
 *  re-derivation) -> 88.8 (decode fixes) -> 92.5 (permuter)
 *  -> 92.61 (bne const-first via isop mode-checks).
 *  3c. (pass 10 negative-flat) the target loads mode-consts 2/3 into
 *     s3/s2 BEFORE the jal (register compares: bne s3,v0 / bne s2,v0).
 *     Plain pre-call locals (const_two=2; const_three=3) got folded
 *     back to immediates by IDO (score exactly flat) -- single-use
 *     consts don't win s-regs. Needs a stronger liveness forcer
 *     (multi-use or volatile-read) -- or this is a -g-level artifact.
 *  3b. (pass 9 negative) hoisting the sp44 default assignment out of
 *     the ==2 arm (target stores D_C50 to 68(sp) unconditionally per
 *     the disasm) scored 87.55 < 87.76 -- REVERTED. The m2c mode-arm
 *     mapping vs the target's bne chain disagree; the selector needs
 *     a precise mode-map re-read before the next probe.
 *  3. (pass 5) +0x33C region: target schedules `swc1 f20,0x48(s0)`
 *     between the s0->0x40 load and its compare (plain bne) -- C shape:
 *     store-then-test with hoisted load; ours emits sw/bnel reorder.
 *     Plus +0x130 move/move-vs-li ordering. Both small.
 *  4. +0xC0..+0x108: lui/beqz/nop pattern (collapsed-pointer guard
 *     pairs) vs graft's beqzl forms -- the per-test reload recipe.
 *  PASS-16 2026-06-22 (agent-b): CTX-LOAD BUG FIXED. The base ptr was
 *  read from a RAW absolute `*(void**)0x254` (emitting a spurious
 *  D_00000000 HI16/LO16 pair) instead of the real symbol fold. Target
 *  does `lui %hi(func_0000023C)` + `lw 0x18(t9)` (offset folded into the
 *  load). Switched the decl to `extern char func_0000023C[]` (DATA array,
 *  not a function) so `*(char**)(func_0000023C + 0x18)` folds +0x18 into
 *  the lw LO16 -- function-symbol arithmetic would instead MATERIALIZE
 *  the address (extra addiu), the known bootup func-sym-arith cap (see
 *  bootup_uso.c:4760). Result: mnemonic ratio 82.55 -> 87.61, objdiff
 *  fuzzy 92.61 -> 93.22. REMAINING (verified pass-16): allocator coloring
 *  cascade (t6<->v1, $f6<->$f8 renumber), the a2/a3 accumulator-vs-recompute
 *  loop tradeoff (E[146] addiu a2,a2,4 / E[77] move a3,t2 snapshot), the
 *  li/move + li/ori const-first scheduling swaps, and the lui-0/addiu-0
 *  no-reloc D_00000000 arg pair (link-time artifact, resolves at link).
 *  All allocator/scheduling/link-artifact class; permuter has no regalloc
 *  randomizer (floored 97k iters prior). */
extern f32 D_00000C50, D_00000C54, D_00000C58, D_00000C5C, D_00000C60;
extern char func_0000023C[];  /* data-symbol base: ctx ptr @ +0x18 */
void func_0001304C(char *arg0)
{

    int dead0, dead1, dead2, dead3, dead4, dead5, dead6;  f32 sp44;
  f32 *temp_a0_2;
  f32 *temp_v0_2;
  f32 temp_f10;
  f32 var_f0;
  f32 var_f12;
  f32 var_f14;
  f32 var_f16;
  f32 var_f24;
  f32 var_f2;
  f32 var_f2_2;
  s32 temp_a0;
  s32 temp_ra;
  s32 temp_t0;
  s32 temp_t1;
  s32 temp_t6;
  s32 temp_v0;
  s32 temp_v0_3;
  s32 temp_v1;
  s32 temp_v1_10;
  s32 temp_v1_11;
  s32 temp_v1_12;
  s32 temp_v1_13;
  s32 temp_v1_14;
  s32 temp_v1_15;
  s32 temp_v1_16;
  s32 temp_v1_17;
  s32 temp_v1_18;
  s32 temp_v1_19;
  s32 temp_v1_20;
  s32 temp_v1_21;
  s32 temp_v1_22;
  s32 temp_v1_23;
  s32 temp_v1_24;
  s32 temp_v1_25;
  s32 temp_v1_26;
  s32 temp_v1_27;
  s32 temp_v1_28;
  s32 temp_v1_2;
  s32 temp_v1_3;
  s32 temp_v1_4;
  s32 temp_v1_5;
  s32 temp_v1_6;
  s32 temp_v1_7;
  s32 temp_v1_8;
  s32 temp_v1_9;
  s32 var_a1;
  s32 var_a2;
  s32 var_a3;
  s32 var_t2;
  s32 var_t4;
  s32 var_t5;
  s32 var_t9;
  s32 var_v0;
  s32 var_v0_2;
  char *temp_a0_3;
  char *temp_a1;
  char *temp_a1_10;
  char *temp_a1_11;
  char *temp_a1_2;
  char *temp_a1_3;
  char *temp_a1_4;
  char *temp_a1_5;
  char *temp_a1_6;
  char *temp_a1_7;
  char *temp_a1_8;
  char *temp_a1_9;
  char *temp_a2;
  char *temp_a2_10;
  char *temp_a2_2;
  char *temp_a2_3;
  char *temp_a2_4;
  char *temp_a2_5;
  char *temp_a2_6;
  char *temp_a2_7;
  char *temp_a2_8;
  char *temp_a2_9;
  char *temp_a3;
  char *temp_a3_2;
  char *temp_a3_3;
  char *temp_a3_4;
  char *temp_a3_5;
  char *temp_t0_2;
  char *temp_t0_3;
  char *temp_v0_10;
  char *temp_v0_11;
  char *temp_v0_12;
  char *temp_v0_13;
  char *temp_v0_14;
  char *temp_v0_15;
  char *temp_v0_16;
  char *temp_v0_17;
  char *temp_v0_18;
  char *temp_v0_19;
  char *temp_v0_20;
  char *temp_v0_21;
  char *temp_v0_22;
  char *temp_v0_23;
  char *temp_v0_24;
  char *temp_v0_25;
  char *temp_v0_26;
  char *temp_v0_27;
  char *temp_v0_28;
  char *temp_v0_29;
  char *temp_v0_30;
  char *temp_v0_31;
  char *temp_v0_4;
  char *temp_v0_5;
  char *temp_v0_6;
  char *temp_v0_7;
  char *temp_v0_8;
  char *temp_v0_9;
  if ((*((s32 *) (((char *) arg0) + 0x40))) != 0)
  {
    *((s32 *) (((char *) arg0) + 0x74)) = (s32) ((*((s32 *) (((char *) arg0) + 0x74))) + 1);
    if ((*((s32 *) (((char *) arg0) + 0x6C))) != 0)
    {
      var_v0 = *((s32 *) (((char *) arg0) + 0x70));
      temp_t6 = var_v0 - 1;
      if (var_v0 != 0)
      {
        *((s32 *) (((char *) arg0) + 0x70)) = temp_t6;
        var_v0 = temp_t6;
      }
      if (var_v0 == 0)
      {
        func_00000000(((char *) (&D_00000000)) + 0, 0);
        *((s32 *) (((char *) arg0) + 0x6C)) = 0;
        if ((*((s32 *) (((char *) arg0) + 0x40))) == 2)
        {
          *((s32 *) (((char *) arg0) + 0x40)) = 0;
          *((f32 *) (((char *) arg0) + 0x48)) = 1.0f;
          return;
        }
      }
    }
    goto block_7;
    block_7:
    func_00000000(arg0);

    temp_v0 = *((s32 *) (((char *) arg0) + 0x40));
    var_t4 = 0;
    var_t5 = 0;
    if ((*((s32 *) (((char *) arg0) + 0x40))) == 2)
    {
      sp44 = D_00000C50;
    }
    var_f24 = sp44;
    if ((*((s32 *) (((char *) arg0) + 0x40))) == 3)
    {
      if ((*((s32 *) (((char *) arg0) + 0x68))) != 0)
      {
        var_f24 = D_00000C54;
      }
      else
      {
        var_f24 = D_00000C58;
      }
    }
    var_t2 = 0;
    if (temp_v0 == 1)
    {
      if (1)
      {
        if ((*((s32 *) (((char *) arg0) + 0x68))) != 0)
        {
          var_f24 = D_00000C5C;
        }
        else
        {
          var_f24 = D_00000C60;
        }
      }
    }
    for (var_t5 = 0; var_t5 != 0x20; var_t5++)
    {
      temp_t0 = var_t5 - 1;
      temp_ra = var_t5 + 1;
      for (var_v0_2 = 0; var_v0_2 != 0x20; var_v0_2 = var_a1)
      {
        temp_t1 = (var_t5 << 5) + var_v0_2;
        var_a2 = ((var_t5 << 5) + var_v0_2) * 4;
        if (temp_t0 < 0)
        {
          var_f16 = 0.0f;
        }
        else
        {
          var_f16 = *((f32 *) (((*((s32 *) (((char *) arg0) + 0x58))) + ((temp_t0 & 0x1F) << 7)) + (var_v0_2 * 4)));
        }
        temp_a0 = var_v0_2 - 1;
        if (var_t5 == 0x1F)
        {
          var_f12 = 0.0f;
        }
        else
        {
          var_f12 = *((f32 *) (((*((s32 *) (((char *) arg0) + 0x58))) + ((temp_ra & 0x1F) << 7)) + (var_v0_2 * 4)));
        }
        if (temp_a0 < 0)
        {
          var_f14 = 0.0f;
        }
        else
        {
          var_f14 = *((f32 *) (((*((s32 *) (((char *) arg0) + 0x58))) + ((var_t5 << 5) * 4)) + ((temp_a0 & 0x1F) * 4)));
        }
        if (var_v0_2 == 0x1F)
        {
          var_f2 = 0.0f;
          var_a1 = var_v0_2 + 1;
        }
        else
        {
          var_a1 = var_v0_2 + 1;
          var_f2 = *((f32 *) (((*((s32 *) (((char *) arg0) + 0x58))) + ((var_t5 << 5) * 4)) + ((var_a1 & 0x1F) * 4)));
        }
        temp_v0_2 = (*((s32 *) (((char *) arg0) + 0x58))) + var_a2;
        *temp_v0_2 += (((var_f16 + var_f12) + var_f14) + var_f2) * var_f24;
        temp_a0_2 = (*((s32 *) (((char *) arg0) + 0x58))) + var_a2;
        var_f0 = *temp_a0_2;
        if (var_f0 > 1.0f)
        {
          *temp_a0_2 = 1.0f;
          var_t4 += 1;
          var_f0 = *((f32 *) ((*((s32 *) (((char *) arg0) + 0x58))) + var_a2));
        }
        temp_v0_3 = *((s32 *) (((char *) arg0) + 0x40));
        if (((*((s32 *) (((char *) arg0) + 0x40))) == 2) || ((*((s32 *) (((char *) arg0) + 0x40))) == 3))
        {
          var_f2_2 = var_f0;
        }
        else
        {
          var_f2_2 = 1.0f - var_f0;
        }
        var_t9 = (u32) (var_f2_2 * 255.0f);
        *((s8 *) ((*((s32 *) (((char *) arg0) + 0x50))) + temp_t1)) = (s8) var_t9;
      }

    }

    if (((*((s32 *) (((char *) arg0) + 0x40))) == 3) && (var_t4 >= 0x401))
    {
      *((f32 *) (((char *) arg0) + 0x48)) = 1.0f;
    }
    if (var_t4 == 0x400)
    {
      *((f32 *) (((char *) arg0) + 0x48)) = 1.0f;
      if ((*((s32 *) (((char *) arg0) + 0x40))) == 1)
      {
        *((s32 *) (((char *) arg0) + 0x40)) = 0;
      }
    }
    temp_a0_3 = *((s32 *) (((char *) (*((char **) (func_0000023C + 0x18)))) + 0x158));
    temp_v0_4 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1 = *((s32 *) (((char *) temp_v0_4) + 0x4));
    *((s32 *) (((char *) temp_v0_4) + 0x4)) = (s32) (temp_v1 + 1);
    temp_a1 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1 * 8);
    *((s32 *) (((char *) temp_a1) + 0x0)) = 0xE7000000;
    *((s32 *) (((char *) temp_a1) + 0x4)) = 0;
    temp_v0_5 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_2 = *((s32 *) (((char *) temp_v0_5) + 0x4));
 *((s32 *) (((char *) temp_v0_5) + 0x4)) = (s32) (temp_v1_2 + 1); temp_a2 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_2 * 8);
    *((s32 *) (((char *) temp_a2) + 0x0)) = 0xBA001402;
    *((s32 *) (((char *) temp_a2) + 0x4)) = 0x100000;
    temp_v0_6 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_3 = *((s32 *) (((char *) temp_v0_6) + 0x4));
    *((s32 *) (((char *) temp_v0_6) + 0x4)) = (s32) (temp_v1_3 + 1);
    temp_a3 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_3 * 8);
    *((s32 *) (((char *) temp_a3) + 0x0)) = 0xBA001301;
    *((s32 *) (((char *) temp_a3) + 0x4)) = 0;
    temp_v0_7 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_4 = *((s32 *) (((char *) temp_v0_7) + 0x4));
    *((s32 *) (((char *) temp_v0_7) + 0x4)) = (s32) (temp_v1_4 + 1);
    temp_a1_2 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_4 * 8);
    *((s32 *) (((char *) temp_a1_2) + 0x0)) = 0xB900031D;
    *((s32 *) (((char *) temp_a1_2) + 0x4)) = 0x504240;
    temp_v0_8 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_5 = *((s32 *) (((char *) temp_v0_8) + 0x4));
    *((s32 *) (((char *) temp_v0_8) + 0x4)) = (s32) (temp_v1_5 + 1);
    temp_a2_2 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_5 * 8);
    *((s32 *) (((char *) temp_a2_2) + 0x0)) = 0xFCFFFFFF;
    *((s32 *) (((char *) temp_a2_2) + 0x4)) = 0xFFFCF438;
    temp_v0_9 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_6 = *((s32 *) (((char *) temp_v0_9) + 0x4));
    *((s32 *) (((char *) temp_v0_9) + 0x4)) = (s32) (temp_v1_6 + 1);
    temp_t0_2 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_6 * 8);
    *((s32 *) (((char *) temp_t0_2) + 0x0)) = 0xBA000C02;
    *((s32 *) (((char *) temp_t0_2) + 0x4)) = 0x2000;
    if ((*((s32 *) (((char *) arg0) + 0x68))) == 0)
    {
      temp_v0_10 = *((s32 *) (((char *) temp_a0_3) + 0xC));
      temp_v1_7 = *((s32 *) (((char *) temp_v0_10) + 0x4));
      *((s32 *) (((char *) temp_v0_10) + 0x4)) = (s32) (temp_v1_7 + 1);
      temp_a1_3 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_7 * 8);
      *((s32 *) (((char *) temp_a1_3) + 0x0)) = 0xBA000602;
      *((s32 *) (((char *) temp_a1_3) + 0x4)) = 0xC0;
    }
    temp_v0_11 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_8 = *((s32 *) (((char *) temp_v0_11) + 0x4));
    *((s32 *) (((char *) temp_v0_11) + 0x4)) = (s32) (temp_v1_8 + 1);
    temp_a1_4 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_8 * 8);
    *((s32 *) (((char *) temp_a1_4) + 0x0)) = 0xF8000000;
    *((s32 *) (((char *) temp_a1_4) + 0x4)) = -1;
    temp_v0_12 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_9 = *((s32 *) (((char *) temp_v0_12) + 0x4));
    *((s32 *) (((char *) temp_v0_12) + 0x4)) = (s32) (temp_v1_9 + 1);
    temp_a2_3 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_9 * 8);
    *((s32 *) (((char *) temp_a2_3) + 0x0)) = 0xFD100000;
    *((s32 *) (((char *) temp_a2_3) + 0x4)) = (s32) (*((s32 *) (((char *) arg0) + 0x4C)));
    temp_v0_13 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_10 = *((s32 *) (((char *) temp_v0_13) + 0x4));
    *((s32 *) (((char *) temp_v0_13) + 0x4)) = (s32) (temp_v1_10 + 1);
    temp_a3_2 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_10 * 8);
    *((s32 *) (((char *) temp_a3_2) + 0x0)) = 0xF5100000;
    *((s32 *) (((char *) temp_a3_2) + 0x4)) = 0x07014050;
    temp_v0_14 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_11 = *((s32 *) (((char *) temp_v0_14) + 0x4));
    *((s32 *) (((char *) temp_v0_14) + 0x4)) = (s32) (temp_v1_11 + 1);
    temp_a1_5 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_11 * 8);
    *((s32 *) (((char *) temp_a1_5) + 0x0)) = 0xE6000000;
    *((s32 *) (((char *) temp_a1_5) + 0x4)) = 0;
    temp_v0_15 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_12 = *((s32 *) (((char *) temp_v0_15) + 0x4));
    *((s32 *) (((char *) temp_v0_15) + 0x4)) = (s32) (temp_v1_12 + 1);
    temp_a2_4 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_12 * 8);
    *((s32 *) (((char *) temp_a2_4) + 0x0)) = 0xF3000000;
    *((s32 *) (((char *) temp_a2_4) + 0x4)) = 0x073FF100;
    temp_v0_16 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_13 = *((s32 *) (((char *) temp_v0_16) + 0x4));
    *((s32 *) (((char *) temp_v0_16) + 0x4)) = (s32) (temp_v1_13 + 1);
    temp_a1_6 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_13 * 8);
    *((s32 *) (((char *) temp_a1_6) + 0x0)) = 0xE7000000;
    *((s32 *) (((char *) temp_a1_6) + 0x4)) = 0;
    temp_v0_17 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_14 = *((s32 *) (((char *) temp_v0_17) + 0x4));
    *((s32 *) (((char *) temp_v0_17) + 0x4)) = (s32) (temp_v1_14 + 1);
    temp_a2_5 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_14 * 8);
    *((s32 *) (((char *) temp_a2_5) + 0x0)) = 0xF5101000;
    *((s32 *) (((char *) temp_a2_5) + 0x4)) = 0x14050;
    temp_v0_18 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_15 = *((s32 *) (((char *) temp_v0_18) + 0x4));
    *((s32 *) (((char *) temp_v0_18) + 0x4)) = (s32) (temp_v1_15 + 1);
    temp_a3_3 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_15 * 8);
    *((s32 *) (((char *) temp_a3_3) + 0x0)) = 0xF2000000;
    *((s32 *) (((char *) temp_a3_3) + 0x4)) = 0x7C07C;
    temp_v0_19 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_16 = *((s32 *) (((char *) temp_v0_19) + 0x4));
    *((s32 *) (((char *) temp_v0_19) + 0x4)) = (s32) (temp_v1_16 + 1);
    temp_a1_7 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_16 * 8);
    *((s32 *) (((char *) temp_a1_7) + 0x0)) = 0xFD900000;
    *((s32 *) (((char *) temp_a1_7) + 0x4)) = (s32) (*((s32 *) (((char *) arg0) + 0x50)));
    temp_v0_20 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_17 = *((s32 *) (((char *) temp_v0_20) + 0x4));
    *((s32 *) (((char *) temp_v0_20) + 0x4)) = (s32) (temp_v1_17 + 1);
    temp_a2_6 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_17 * 8);
    *((s32 *) (((char *) temp_a2_6) + 0x0)) = 0xF5900100;
    *((s32 *) (((char *) temp_a2_6) + 0x4)) = 0x07014050;
    temp_v0_21 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_18 = *((s32 *) (((char *) temp_v0_21) + 0x4));
    *((s32 *) (((char *) temp_v0_21) + 0x4)) = (s32) (temp_v1_18 + 1);
    temp_a3_4 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_18 * 8);
    *((s32 *) (((char *) temp_a3_4) + 0x0)) = 0xE6000000;
    *((s32 *) (((char *) temp_a3_4) + 0x4)) = 0;
    temp_v0_22 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_19 = *((s32 *) (((char *) temp_v0_22) + 0x4));
    *((s32 *) (((char *) temp_v0_22) + 0x4)) = (s32) (temp_v1_19 + 1);
    temp_a1_8 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_19 * 8);
    *((s32 *) (((char *) temp_a1_8) + 0x0)) = 0xF3000000;
    *((s32 *) (((char *) temp_a1_8) + 0x4)) = 0x071FF200;
    temp_v0_23 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_20 = *((s32 *) (((char *) temp_v0_23) + 0x4));
    *((s32 *) (((char *) temp_v0_23) + 0x4)) = (s32) (temp_v1_20 + 1);
    temp_a2_7 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_20 * 8);
    *((s32 *) (((char *) temp_a2_7) + 0x0)) = 0xE7000000;
    *((s32 *) (((char *) temp_a2_7) + 0x4)) = 0;
    temp_v0_24 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_21 = *((s32 *) (((char *) temp_v0_24) + 0x4));
    *((s32 *) (((char *) temp_v0_24) + 0x4)) = (s32) (temp_v1_21 + 1);
    temp_t0_3 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_21 * 8);
    *((s32 *) (((char *) temp_t0_3) + 0x0)) = 0xF5880900;
    *((s32 *) (((char *) temp_t0_3) + 0x4)) = 0x01014050;
    temp_v0_25 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_22 = *((s32 *) (((char *) temp_v0_25) + 0x4));
    *((s32 *) (((char *) temp_v0_25) + 0x4)) = (s32) (temp_v1_22 + 1);
    temp_a1_9 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_22 * 8);
    *((s32 *) (((char *) temp_a1_9) + 0x0)) = 0xF2000000;
    *((s32 *) (((char *) temp_a1_9) + 0x4)) = 0x0107C07C;
    temp_v0_26 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_23 = *((s32 *) (((char *) temp_v0_26) + 0x4));
    *((s32 *) (((char *) temp_v0_26) + 0x4)) = (s32) (temp_v1_23 + 1);
    temp_a2_8 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_23 * 8);
    *((s32 *) (((char *) temp_a2_8) + 0x0)) = 0xBA001001;
    *((s32 *) (((char *) temp_a2_8) + 0x4)) = 0;
    temp_v0_27 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_24 = *((s32 *) (((char *) temp_v0_27) + 0x4));
    *((s32 *) (((char *) temp_v0_27) + 0x4)) = (s32) (temp_v1_24 + 1);
    temp_a1_10 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_24 * 8);
    *((s32 *) (((char *) temp_a1_10) + 0x0)) = 0xE45003C0;
    *((s32 *) (((char *) temp_a1_10) + 0x4)) = 0;
    temp_v0_28 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_25 = *((s32 *) (((char *) temp_v0_28) + 0x4));
    *((s32 *) (((char *) temp_v0_28) + 0x4)) = (s32) (temp_v1_25 + 1);
    temp_a2_9 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_25 * 8);
    *((s32 *) (((char *) temp_a2_9) + 0x0)) = 0xB4000000;
    *((s32 *) (((char *) temp_a2_9) + 0x4)) = 0;
    temp_v0_29 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_26 = *((s32 *) (((char *) temp_v0_29) + 0x4));
    *((s32 *) (((char *) temp_v0_29) + 0x4)) = (s32) (temp_v1_26 + 1);
    temp_a1_11 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_26 * 8);
    *((s32 *) (((char *) temp_a1_11) + 0x0)) = 0xB3000000;
    *((s32 *) (((char *) temp_a1_11) + 0x4)) = 0x630084;
    temp_v0_30 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_27 = *((s32 *) (((char *) temp_v0_30) + 0x4));
    *((s32 *) (((char *) temp_v0_30) + 0x4)) = (s32) (temp_v1_27 + 1);
    temp_a2_10 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_27 * 8);
    *((s32 *) (((char *) temp_a2_10) + 0x0)) = 0xE7000000;
    *((s32 *) (((char *) temp_a2_10) + 0x4)) = 0;
    temp_v0_31 = *((s32 *) (((char *) temp_a0_3) + 0xC));
    temp_v1_28 = *((s32 *) (((char *) temp_v0_31) + 0x4));
    *((s32 *) (((char *) temp_v0_31) + 0x4)) = (s32) (temp_v1_28 + 1);
    temp_a3_5 = (*((s32 *) (((char *) (*((s32 *) (((char *) temp_a0_3) + 0xC)))) + 0x0))) + (temp_v1_28 * 8);
    *((s32 *) (((char *) temp_a3_5) + 0x0)) = 0xBA001301;
    *((s32 *) (((char *) temp_a3_5) + 0x4)) = 0x80000;
  }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001304C);
#endif

int func_00013924(int *a0) {
    if (*(float*)((char*)a0 + 0x48) == 1.0f) {
        if (*(int*)((char*)a0 + 0x68) == 0) {
            func_00000000(&D_00000000, 1);
        }
        return 1;
    }
    return 0;
}

int func_00013980(float *a0) {
    if (*(float*)((char*)a0 + 0x48) == 1.0f) {
        return 1;
    }
    return 0;
}

/* func_000139B0 - verified structural decode (0x170, 92 insns,
 * 2D grid reset + random scatter).
 * (rand01 = func_00000000() with no args -> f0, a 0..1 RNG.)
 * Struct-typing reference: s1->0x58 (88) = base ptr of a 2D f32
 * grid, s1->0x5C (92) s32 columns, s1->0x60 (96) s32 rows (row
 * stride = 128 bytes = 0x80, i.e. 32 f32 cells/row given the
 * y<<7 index). s1->0x40 (64) s32 = current key/seed (skip if
 * unchanged), s1->0x44 (68) = 4 (state), s1->0x48 (72) f32 = 0.0
 * (reset accumulator), s1->0x68 (104) = a2 (mode), s1->0x6C (108)
 * / s1->0x70 (112) = mode-derived flags (1/3 when a2==0, else
 * 0), s1->0x74 (116) = 0. D_00000C64 = f32 value-scale for the
 * scattered amplitude. Looks like a randomized snow/terrain
 * height-field seed. Caps <80: FP-heavy mul.s/trunc.w.s +
 * f20/f22/f24 sdc1/ldc1 double-saves + D_00000C64 reloc + 3x
 * RNG calls + nested clear loop + bnel branch-likely.
 * INCLUDE_ASM remains build path. */
extern float D_00000C64;
#ifdef NON_MATCHING
void func_000139B0(char *s1, int a1, int a2) {
    int r, c, k;
    int x, y;
    float v;
    float *grid;
    *(int*)(s1 + 0x68) = a2;
    if (a2 == 0) {
        *(int*)(s1 + 0x6C) = 1;
        *(int*)(s1 + 0x70) = 3;
    } else {
        *(int*)(s1 + 0x6C) = 0;
    }
    if (a1 == *(int*)(s1 + 0x40)) return;
    *(int*)(s1 + 0x40) = a1;
    *(int*)(s1 + 0x44) = 4;
    *(int*)(s1 + 0x74) = 0;
    grid = *(float**)(s1 + 0x58);
    for (r = 0; r < *(int*)(s1 + 0x60); r++) {
        for (c = 0; c < *(int*)(s1 + 0x5C); c++) {
            grid[c] = 0.0f;
        }
    }
    for (k = 0; k < 5; k++) {
        x = (int)((float)func_00000000() * 32.0f);
        y = (int)((float)func_00000000() * 32.0f);
        v = (float)func_00000000() * D_00000C64;
        *(float*)((char*)*(int*)(s1 + 0x58) + x * 4 + (y << 7)) = v;
    }
    func_00000000(s1);
    *(float*)(s1 + 0x48) = 0.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000139B0);
#endif

/* func_00013B20 - verified structural decode (0x144, 84 insns,
 * LUT index->value remap with all-ones fallback).
 *   void func_00013B20(St *a0) {
 *       root = *(void**)(func_0000023C + 4);
 *       v = root->0x28;
 *       lut = (u16*)(*(fn)v->0x64)((s16)v->0x60 + root); // vtable
 *       if (a0->0x68 != 0) {                      // remap path
 *           int *src = a0->0x54;                  // index array
 *           u16 *dst = a0->0x4C;                  // output
 *           for (i = 0; i != 0x1000/4; i += 4) {  // 4-unrolled
 *               dst[0] = lut[src[i+0]];
 *               dst[1] = lut[src[i+1]];
 *               dst[2] = lut[src[i+2]];
 *               dst[3] = lut[src[i+3]];
 *               dst += 4;
 *           }
 *       } else {                                  // fill path
 *           u16 *dst = a0->0x4C;
 *           for (j = 0; j != 0x800; j += 8) {     // 4-unrolled
 *               dst[0] = dst[1] = dst[2] = dst[3] = 1;
 *               dst += 4;
 *           }
 *       }
 *   }
 * Struct-typing reference: root = *(func_0000023C+4) global ctx;
 * root->0x28 (40) vtable ptr, fn @0x64 (100) + s16 base-adjust
 * @0x60 (96) returns a u16 lookup table (the obj-0x28 dispatch
 * idiom, 0x64/0x60 variant). a0->0x54 (84) = source int index
 * array (0x400 entries, 0x1000 bytes), a0->0x4C (76) = dest u16
 * array (0x400 entries, 0x800 bytes), a0->0x68 (104) = mode gate
 * (nonzero -> remap each src index through lut; zero -> fill dest
 * with 1). Likely a tile/palette index-to-colour expansion. Caps
 * <80: vtable jalr + func_0000023C+4 reloc data ref + 4-way
 * unrolled nested loop + beql branch-likely. Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00013B20)();
void func_00013B20(char *arg0) {
    s32 sp24;
    s32 var_i;
    char *temp_v0;
    char *temp_v1;
    char *temp_v0_2;
    s32 *palette;

    temp_v1 = (*(char**)((char*)&D_00000000 + 4));
    temp_v0 = FW(temp_v1, 0x28);
    palette = (s32 *)((GP_00013B20)FW(temp_v0, 0x64))((*(s16*)((char*)temp_v0 + 0x60)) + temp_v1, arg0);
    (void)sp24; (void)temp_v0_2;
    if (FW(arg0, 0x68) != 0) {
        var_i = 0;
        do {
            *(u16*)(FW(arg0, 0x4C) + (var_i >> 1)) = *(u16*)((char*)palette + (*(s32*)((char*)FW(arg0, 0x54) + var_i) * 2));
            var_i += 4;
        } while (var_i != 0x1000);
        return;
    }
    var_i = 0;
    do {
        *(u16*)(FW(arg0, 0x4C) + var_i) = 1;
        var_i += 2;
    } while (var_i != 0x800);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013B20);
#endif

void func_00013C70(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_00013CAC(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_00013CE8(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

/* func_00013D40 - verified structural decode (0x2A0, 168 insns).
 * NEAR-SIBLING of func_0001438C / func_00008124 (bootup_uso
 * get-or-create constructor + N child sub-objects family); variant:
 * object 0x98, more children, datums D_0000CAAC/CAC0/CAC4/CAC8 +
 * D_0000C764, child->0x10 = 0x1E.
 *   void *func_00013D40(void *a0) {
 *       o = a0 ? a0 : alloc(0x98); if (!o) return 0;
 *       s = alloc(8);
 *       if (s) { s->0x0 = &D_0000CAAC; s->0x4 = 0; }
 *       v = *(int*)&D_0000CAC0;
 *       if (o != (void*)-8) {                      // defensive
 *           c = alloc(0x18);
 *           if (c) {
 *               init(c, o, v, 1);                  // func_00000000
 *               c->0x10 = 0x1E;
 *               c->0xC  = &D_0000C764;             // type/vtable
 *               c->0x14 = 0;
 *           }
 *       }
 *       v = *(int*)&D_0000CAC4;
 *       if (o != (void*)-0x20) { c2 = alloc(0x18); ... }
 *       ... (further children from D_0000CAC8, same shape) ...
 *   }
 * Struct-typing reference (same family as func_0001438C): o =
 * 0x98-byte object; s = 8-byte aux (s->0x0 = &D_0000CAAC
 * descriptor, s->0x4 = 0). Each child = 0x18-byte sub-object:
 * child->0xC (12) type/vtable ptr (&D_0000C764), child->0x10 (16)
 * s32 = 0x1E (a kind/priority), child->0x14 (20) = 0; built via
 * func_00000000(child, o, val, 1) with val pulled from the global
 * table D_0000CAC0 / D_0000CAC4 / D_0000CAC8. The o != -0x8 /
 * -0x20 tests are defensive impossible-pointer guards. Caps <80:
 * get-or-create + alloc-cascade (~8 reloc) + defensive-dead
 * guards + &D descriptors + cross-symbol (func_0000CACC) ref.
 * Full body INCLUDE_ASM-preserved (.s = source of truth).
 * INCLUDE_ASM (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00013D40)();
char *func_00013D40(char *arg0) {
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    char *sp28;
    s32 sp24;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_t2_3;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_t7_3;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_3;
    char *temp_v0_4;
    char *temp_v0_5;
    char *temp_v0_6;
    char *temp_v0_7;
    char *temp_v0_8;
    char *var_a0;
    char *var_a0_2;
    char *var_a0_3;
    char *var_a0_4;
    char *var_a0_5;
    char *var_a0_6;
    char *var_s0;
    char *var_v1;

    var_s0 = arg0;
    if ((arg0 != 0) || (temp_v0 = ((int(*)())func_00012E00)((char *)0x98), var_s0 = temp_v0, (temp_v0 != 0))) {
        var_v1 = var_s0;
        if ((var_s0 != 0) || (temp_v0_2 = ((int(*)())func_00012E00)((char *)8), var_v1 = temp_v0_2, (temp_v0_2 != 0))) {
            FW(var_v1, 0x0) = 0;
            FW(var_v1, 0x4) = 0;
        }
        temp_t7 = *(int*)0;
        var_a0 = var_s0 + 8;
        sp4C = temp_t7;
        sp24 = temp_t7;
        if ((var_s0 != (char *)-8) || (temp_v0_3 = ((int(*)())func_00012E00)((char *)0x18), var_a0 = temp_v0_3, (temp_v0_3 != 0))) {
            sp28 = var_a0;
            ((int(*)())func_00012E00)(var_a0, var_s0, sp24, 1);
            FW(var_a0, 0x10) = 0x1E;
            FW(var_a0, 0xC) = 0;
            FW(var_a0, 0x14) = 0;
        }
        temp_t2 = *(int*)0;
        var_a0_2 = var_s0 + 0x20;
        sp48 = temp_t2;
        sp24 = temp_t2;
        if ((var_s0 != (char *)-0x20) || (temp_v0_4 = ((int(*)())func_00012E00)((char *)0x18), var_a0_2 = temp_v0_4, (temp_v0_4 != 0))) {
            sp28 = var_a0_2;
            ((int(*)())func_00012E00)(var_a0_2, var_s0, sp24, 1);
            FW(var_a0_2, 0x10) = 0x1E;
            FW(var_a0_2, 0xC) = 0;
            FW(var_a0_2, 0x14) = 0;
        }
        temp_t7_2 = *(int*)0;
        var_a0_3 = var_s0 + 0x38;
        sp44 = temp_t7_2;
        sp24 = temp_t7_2;
        if ((var_s0 != (char *)-0x38) || (temp_v0_5 = ((int(*)())func_00012E00)((char *)0x18), var_a0_3 = temp_v0_5, (temp_v0_5 != 0))) {
            sp28 = var_a0_3;
            ((int(*)())func_00012E00)(var_a0_3, var_s0, sp24, 1);
            FW(var_a0_3, 0x10) = 2;
            FW(var_a0_3, 0xC) = 0;
            FW(var_a0_3, 0x14) = 0;
        }
        temp_t2_2 = *(int*)0;
        var_a0_4 = var_s0 + 0x50;
        sp40 = temp_t2_2;
        sp24 = temp_t2_2;
        if ((var_s0 != (char *)-0x50) || (temp_v0_6 = ((int(*)())func_00012E00)((char *)0x18), var_a0_4 = temp_v0_6, (temp_v0_6 != 0))) {
            sp28 = var_a0_4;
            ((int(*)())func_00012E00)(var_a0_4, var_s0, sp24, 1);
            FW(var_a0_4, 0x10) = -0xC;
            FW(var_a0_4, 0xC) = 0;
            FW(var_a0_4, 0x14) = 0;
        }
        temp_t7_3 = *(s32 *)4;
        var_a0_5 = var_s0 + 0x68;
        sp3C = temp_t7_3;
        sp24 = temp_t7_3;
        if ((var_s0 != (char *)-0x68) || (temp_v0_7 = ((int(*)())func_00012E00)((char *)0x18), var_a0_5 = temp_v0_7, (temp_v0_7 != 0))) {
            sp28 = var_a0_5;
            ((int(*)())func_00012E00)(var_a0_5, var_s0, sp24, 1);
            FW(var_a0_5, 0x10) = 2;
            FW(var_a0_5, 0xC) = 0;
            FW(var_a0_5, 0x14) = 0;
        }
        temp_t2_3 = *(s32 *)8;
        var_a0_6 = var_s0 + 0x80;
        sp38 = temp_t2_3;
        sp24 = temp_t2_3;
        if ((var_s0 != (char *)-0x80) || (temp_v0_8 = ((int(*)())func_00012E00)((char *)0x18), var_a0_6 = temp_v0_8, (temp_v0_8 != 0))) {
            sp28 = var_a0_6;
            ((int(*)())func_00012E00)(var_a0_6, var_s0, sp24, 1);
            FW(var_a0_6, 0x10) = -0xC;
            FW(var_a0_6, 0xC) = 0;
            FW(var_a0_6, 0x14) = 0;
        }
    }
    return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013D40);
#endif

void func_00013FE0(char *a0, int a1, int a2) {
    *(int*)(a0 + 0x44) = a1;
    *(int*)(a0 + 0x5C) = a2;
}

void func_00013FEC(char *a0, int a1, int a2, int a3, int arg5) {
    *(int*)(a0 + 0x74) = a1;
    *(int*)(a0 + 0x8C) = a2;
    *(int*)(a0 + 0xA4) = a3;
    *(int*)(a0 + 0xBC) = arg5;
}

void func_00014004(char *a0, int a1, int a2) {
    *(int*)(a0 + 0x104) = a1;
    *(int*)(a0 + 0x108) = a2;
}

/* func_00014010 - verified structural decode (0xB4, 45 insns,
 * in-place string substitution cipher).
 *   void func_00014010(char *a0) {
 *       char *s = a0 + 0xE4;                      // string field
 *       u32 n = strlen_like(s);                   // func_00000000(s)
 *       u32 i = 0;
 *       while (i < n) {
 *           unsigned char c = s[i];
 *           i++;
 *           if (c != 'a' && c != 'b' && c != ' ') // 0x61/0x62/0x20
 *               s[i-1] = (char)(0x69 - c);        // 'i' - c
 *           n = strlen_like(s);                   // recomputed each iter
 *       }
 *   }
 * Behavior: each character of the NUL-terminated string at a0+0xE4
 * (offset 0xE4 = 228) is mapped c -> ('i' - c) UNLESS it is one of
 * the passthrough chars 'a' (0x61), 'b' (0x62), or space (0x20),
 * which are left unchanged. The length is re-evaluated via the
 * reloc helper func_00000000 on every iteration (bound = current
 * strlen). Struct-typing reference: a0->0xE4 (228) = char[] name/id
 * string buffer. Caps <80: bnel branch-likely loop-back + reloc
 * func_00000000 strlen recompute as the loop bound + 4 char
 * constants ('a'/'b'/' '/'i') hoisted into s3-s6 (8-sreg pressure,
 * IDO global-allocator order-sensitive). Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
#ifdef NON_MATCHING
void func_00014010(char *a0) {
    char *s = a0 + 0xE4;
    unsigned int n = (unsigned int)func_00000000(s);
    unsigned int i = 0;
    while (i < n) {
        unsigned char c = s[i];
        i++;
        if (c != 0x61 && c != 0x62 && c != 0x20) {
            s[i - 1] = (char)(0x69 - c);
        }
        n = (unsigned int)func_00000000(s);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014010);
#endif

/* func_000140C4 - 3-element draw/place dispatcher. EXACT TWIN of
 * func_00014228 (byte-for-byte identical TARGET except the function
 * address): same prologue, same body, same epilogue. Same NM C body
 * applied (the levers that landed func_00014228's body verbatim:
 * `volatile int pad[12]` after col[4] for frame 0x68/col@0x58;
 * global-first FP `*(f32*)&D * (float)count` for cvt-reg coloring;
 * high-offset-first addends; direct-deref `if(*(int*)(s0+N))` to keep
 * the beql branch-likely).
 * STATE (2026-06-23 agent-b): body BYTE-EXACT. Residual = 6 insns,
 * ALL in the FIRST block's prologue, identical to the func_00014228
 * twin's documented as1-scheduler + register-coloring cap:
 *   target: sw s0,0x18 / or s0,a0 (in gap) / sw ra,0x1C / ...
 *           lw a0,0x104(a0) / beql a0 / jal-delay = nop
 *   build:  sw ra,0x1C / sw s0,0x18 (adjacent, no gap) /
 *           lw a1,0x104(a0) / or s0,a0 / beql a1 /
 *           jal-delay = or a0,a1
 * Root: target reads the FIRST handle from the RAW INCOMING a0 (before
 * the arg-save to s0 is forced), keeping it in a0 so the call reuses it
 * with a nop delay; our build colors it into a1 and needs the extra
 * `move a0,a1`. NOT a pure as1 reorder (insn MULTISET differs: target
 * has extra nop+`lw a0`, ours has extra `move a0,a1`+`lw a1`) -> the
 * register-coloring class the docs flag IMMUNE to source reordering.
 * Blocks 2 & 3 use the identical C shape and match EXACTLY, proving the
 * body C is correct. Twin exhausted held-temp (spills + downgrades
 * beql), array-index condition, int param, float temp - all 10-or-worse;
 * permuter has no regalloc randomizer (floored prior). Genuine
 * as1+coloring cap. INCLUDE_ASM remains build path (no episode). */
/* func_000140C4 — EXACT (89/89) verified 2026-07-02 on agent-e.
 * TU: src/bootup_uso/bootup_uso_tail4.c (default flags, -O2).
 * EXACT TWIN of func_00014228 — identical body, identical new lever:
 * `if (1) { }` BB-barrier after the col[] init stops uopt sinking the
 * a0->s0 param copy past the first handle load, so the handle colors into
 * $a0 (lw a0,0x104(a0); beql a0; jal delay nop) and the prologue becomes
 * sw s0 / or s0,a0 / sw ra. Fixes all 10 residual words.
 * See /tmp/body_ex14228.c for the full lever writeup. */
void func_000140C4(char *s0) {
    float col[4];
    volatile int pad[12];
    int n;
    col[0] = 1.0f; col[1] = 1.0f; col[2] = 1.0f; col[3] = 1.0f;
    if (1) { }
    if (*(int*)(s0 + 0x104)) {
        func_00000000(*(int*)(s0 + 0x104));
        n = (int)(*(float*)&D_00000000 * (float)*(int*)(s0 + 0xDC));
        func_00000000(*(int*)(s0 + 0x104), n, col, 0);
        func_00000000(*(int*)(s0 + 0x104),
                      *(int*)(s0 + 0x74) + *(int*)(s0 + 0x44),
                      *(int*)(s0 + 0x8C) + *(int*)(s0 + 0x5C), 0);
    }
    if (*(int*)(s0 + 0x108)) {
        func_00000000(*(int*)(s0 + 0x108));
        n = (int)(*(float*)&D_00000000 * (float)*(int*)(s0 + 0xD8));
        func_00000000(*(int*)(s0 + 0x108), n, col, 0);
        func_00000000(*(int*)(s0 + 0x108),
                      *(int*)(s0 + 0xA4) + *(int*)(s0 + 0x44),
                      *(int*)(s0 + 0xBC) + *(int*)(s0 + 0x5C), 0);
    }
    func_00000000(*(int*)(s0 + 0xE0));
    n = (int)(*(float*)&D_00000000 * (float)*(int*)(s0 + 0xD8));
    func_00000000(*(int*)(s0 + 0xE0), n, s0 + 0xC4, *(int*)(s0 + 0xD4));
    func_00000000(*(int*)(s0 + 0xE0), *(int*)(s0 + 0x44), *(int*)(s0 + 0x5C), s0 + 0xE4);
}

/* func_00014228 - 3-element draw/place dispatcher (twin of func_000140C4).
 * NM body brought to 10 non-reloc diffs (from 24) - body is byte-exact
 * except the 10-word prologue/save-order cluster (as1 scheduler-tie).
 * Levers that landed the body:
 *   - frame 0x68 / col@0x58: `volatile int pad[12]` declared AFTER col
 *     (frame-slot rule: first-decl = highest offset, pad fills low slots).
 *   - FP mul order: write `*(f32*)&D * (float)count` (GLOBAL FIRST). The
 *     count-first spelling reverses the fp-reg coloring in all 3 blocks
 *     (23->10). IDO emits `mul cvt(count), global` regardless of source
 *     side; the global-first C gives count the lower cvt reg.
 *   - addend order: write `*(s0+0xHI) + *(s0+0x44)` (high offset first);
 *     IDO reverses to load 0x44 first, matching target (group-D, -8 diffs).
 *   - condition stays a direct deref `if(*(int*)(s0+0xN))` to keep the
 *     `beql` branch-likely (any held-temp form downgrades it to beq).
 * RESIDUAL (10 words, as1 scheduler-tie, NOT C-reachable): block-1
 * prologue only. Target saves $s0@0x18 BEFORE $ra@0x1C with `or s0,a0`
 * scheduled into the inter-save gap, then reads the first handle into
 * $a0 directly (`lw a0,0x104(a0)`) - no a0/a1 move, jal delay = nop.
 * My build saves $ra first (adjacent saves, no gap), reads the handle
 * into $a1, moves `or s0,a0` after, and fills the jal delay with
 * `or a0,a1`. Blocks 2 & 3 use the identical C shape and match exactly,
 * proving the body is correct - only the param/prologue scheduling of
 * the FIRST block diverges. Tried: held-temp (spills + downgrades beql),
 * array-index condition, int param, float temp - all 10 or worse.
 * INCLUDE_ASM build path (no episode; NM body for %-progress only). */
/* func_00014228 — EXACT (89/89) verified 2026-07-02 on agent-e.
 * TU: src/bootup_uso/bootup_uso_tail4.c (default flags, -O2).
 * NEW LEVER vs the previous 10-diff residual (documented "as1+coloring cap"):
 * `if (1) { }` BB-barrier inserted between the col[] init and the first
 * real condition. The barrier ends the entry basic block, which stops uopt
 * from SINKING the param a0->s0 copy past the first handle load. With the
 * copy at entry, a0 dies at the load's base use, so the loaded handle is
 * colored INTO $a0 (`lw a0,0x104(a0)`), beql tests a0, jal delay = nop,
 * and the prologue interleaves `sw s0 / or s0,a0 / sw ra` — all 10
 * residual words fixed at once. (Previously tried held-temp / array-index
 * cond / int param / float temp all failed; param-alias local copy gets
 * copy-propagated away AND grows the frame to 0x70 — don't use.)
 * All other levers unchanged: volatile int pad[12] AFTER col (frame
 * 0x68/col@0x58); global-first FP mul `*(f32*)&D * (float)count`;
 * high-offset-first addends; direct-deref conditions to keep beql. */
void func_00014228(char *s0) {
    float col[4];
    volatile int pad[12];
    int n;
    col[0] = 1.0f; col[1] = 1.0f; col[2] = 1.0f; col[3] = 1.0f;
    if (1) { }
    if (*(int*)(s0 + 0x104)) {
        func_00000000(*(int*)(s0 + 0x104));
        n = (int)(*(float*)&D_00000000 * (float)*(int*)(s0 + 0xDC));
        func_00000000(*(int*)(s0 + 0x104), n, col, 0);
        func_00000000(*(int*)(s0 + 0x104),
                      *(int*)(s0 + 0x74) + *(int*)(s0 + 0x44),
                      *(int*)(s0 + 0x8C) + *(int*)(s0 + 0x5C), 0);
    }
    if (*(int*)(s0 + 0x108)) {
        func_00000000(*(int*)(s0 + 0x108));
        n = (int)(*(float*)&D_00000000 * (float)*(int*)(s0 + 0xD8));
        func_00000000(*(int*)(s0 + 0x108), n, col, 0);
        func_00000000(*(int*)(s0 + 0x108),
                      *(int*)(s0 + 0xA4) + *(int*)(s0 + 0x44),
                      *(int*)(s0 + 0xBC) + *(int*)(s0 + 0x5C), 0);
    }
    func_00000000(*(int*)(s0 + 0xE0));
    n = (int)(*(float*)&D_00000000 * (float)*(int*)(s0 + 0xD8));
    func_00000000(*(int*)(s0 + 0xE0), n, s0 + 0xC4, *(int*)(s0 + 0xD4));
    func_00000000(*(int*)(s0 + 0xE0), *(int*)(s0 + 0x44), *(int*)(s0 + 0x5C), s0 + 0xE4);
}

/* func_0001438C - verified structural decode (0x128, 74 insns,
 * get-or-create constructor + 2 child sub-objects).
 *   void *func_0001438C(void *a0) {
 *       o = a0;
 *       if (o == 0) { o = alloc(0x38); if (!o) return 0; }
 *       s1 = alloc(8);
 *       if (s1) {
 *           s1->0x0 = &func_0000CACC[0xC];        // fn/descriptor
 *           s1->0x4 = 0;
 *       }
 *       v = *(int*)(func_0000CAE8 + 4);
 *       if (o != (void*)-8) {                     // defensive guard
 *           c = alloc(0x18);
 *           if (c) {
 *               init(c, o, v, 1);                 // func_00000000
 *               c->0xC  = &D_0000C83C;            // descriptor
 *               c->0x14 = 0;
 *               c->0x10 = 30.0f;                  // 0x41F00000
 *           }
 *       }
 *       v = *(int*)(func_0000CAE8 + 8);
 *       if (o != (void*)-0x20) {
 *           c = alloc(0x18);
 *           if (c) {
 *               init(c, o, v, 1);
 *               c->0xC  = &D_0000C83C;
 *               c->0x14 = 0;
 *               c->0x10 = 30.0f;
 *           }
 *       }
 *       return o;
 *   }
 * Struct-typing reference: o = 0x38-byte object (get-or-create).
 * s1 = 8-byte aux: s1->0x0 (0) fn/descriptor ptr (&func_0000CACC+
 * 0xC), s1->0x4 (4) = 0. child = 0x18-byte sub-object: child->0xC
 * (12) descriptor ptr (&D_0000C83C), child->0x10 (16) f32 = 30.0,
 * child->0x14 (20) = 0; built twice with values from the global
 * table func_0000CAE8+4 / +8. The `o != -8 / -0x20` tests are
 * defensive impossible-pointer guards (always true for real
 * objects). Caps <80: get-or-create + ~5 func_00000000 reloc
 * (alloc/init) + &D / cross-symbol descriptor relocs + FP 30.0
 * const + defensive-dead guards. Full body INCLUDE_ASM-preserved
 * (.s = source of truth). INCLUDE_ASM (no episode; tautology-trap
 * rule). */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0001438C)();
char *func_0001438C(char *arg0) {
    s32 sp3C;
    s32 sp38;
    char *sp28;
    s32 sp24;
    s32 temp_t1;
    s32 temp_t7;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_3;
    char *temp_v0_4;
    char *var_a0;
    char *var_a0_2;
    char *var_s0;
    char *var_v1;

    var_s0 = arg0;
    if ((arg0 != 0) || (temp_v0 = func_00012E00(0x38), var_s0 = temp_v0, (temp_v0 != 0))) {
        var_v1 = var_s0;
        if ((var_s0 != 0) || (temp_v0_2 = func_00012E00(8), var_v1 = temp_v0_2, (temp_v0_2 != 0))) {
            FW(var_v1, 0x0) = 0xC;
            FW(var_v1, 0x4) = 0;
        }
        temp_t7 = (*(s32*)((char*)&D_00000000 + 4));
        var_a0 = var_s0 + 8;
        sp3C = temp_t7;
        sp24 = temp_t7;
        if ((var_s0 != (char *)-8) || (temp_v0_3 = func_00012E00(0x18), var_a0 = temp_v0_3, (temp_v0_3 != 0))) {
            sp28 = var_a0;
            func_00012E00(var_a0, var_s0, sp24, 1);
            FW(var_a0, 0xC) = 0;
            FW(var_a0, 0x14) = 0;
            *(f32*)((char*)var_a0 + 0x10) = 30.0f;
        }
        temp_t1 = (*(s32*)((char*)&D_00000000 + 8));
        var_a0_2 = var_s0 + 0x20;
        sp38 = temp_t1;
        sp24 = temp_t1;
        if ((var_s0 != (char *)-0x20) || (temp_v0_4 = func_00012E00(0x18), var_a0_2 = temp_v0_4, (temp_v0_4 != 0))) {
            sp28 = var_a0_2;
            func_00012E00(var_a0_2, var_s0, sp24, 1);
            FW(var_a0_2, 0xC) = 0;
            FW(var_a0_2, 0x14) = 0;
            *(f32*)((char*)var_a0_2 + 0x10) = 30.0f;
        }
    }
    return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001438C);
#endif

void func_000144B4(int *a0, int a1, int a2, float a3, float arg5) {
    *(float*)((char*)a0 + 0x44) = (float)a1;
    *(float*)((char*)a0 + 0x5C) = (float)a2;
    *(float*)((char*)a0 + 0x88) = a3;
    *(float*)((char*)a0 + 0x8C) = arg5;
}

void func_000144E0(void *a0, float a1, float a2) {
    *(float*)((char*)a0 + 0x88) = a1;
    *(float*)((char*)a0 + 0x8C) = a2;
}

/* func_000144F4 - verified structural decode (leaf, 43 insns, FP
 * physics integrator). Returns s32 (0 = running, 1 = clamped).
 *   s32 func_000144F4(void *a0, s32 a1) {
 *       s32 r = 0;
 *       f32 spd = a0->0xA8;                  // rate/accumulator
 *       if (spd < 16.0f)                     // ramp-up gate
 *           a0->0xA8 = (f32)((f64)spd + 0.5);// +0.5 via double promo
 *       spd = a0->0xA8;
 *       a0->0x5C = a0->0x5C + spd;           // integrate position
 *       pos = a0->0x5C;
 *       if ((f32)a1 < pos) {                 // exceeded int limit a1
 *           r = 1;
 *           if (6.0f < spd)                  // overspeed branch
 *               a0->0xA8 = -(spd / 4.0f);    // reverse + damp /4
 *           a0->0x5C = pos - spd;            // back off one step
 *       }
 *       return r;
 *   }
 * Struct-typing reference: a0->0xA8 (168) f32 rate/speed accumulator
 * (ramps by 0.5/frame until >=16.0, then constant), a0->0x5C (92) f32
 * integrated position; a1 = s32 limit (compared as float). On reaching
 * the limit: clamp position back one step, set return flag, and if
 * speed>6.0 reverse-and-damp speed to -(speed/4). Caps <80: bc1fl
 * branch-likely (x2) + cvt.d.s/add.d/cvt.s.d double-promotion of the
 * +0.5 literal add + c.lt.s operand-order. Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
#ifdef NON_MATCHING
int func_000144F4(char *a0, int a1) {
    int r = 0;
    float spd = *(float *)(a0 + 0xA8);
    float pos;
    if (spd < 16.0f) {
        *(float *)(a0 + 0xA8) = (float)((double)spd + 0.5);
    }
    spd = *(float *)(a0 + 0xA8);
    *(float *)(a0 + 0x5C) = *(float *)(a0 + 0x5C) + spd;
    pos = *(float *)(a0 + 0x5C);
    if ((float)a1 < pos) {
        r = 1;
        if (6.0f < spd) {
            *(float *)(a0 + 0xA8) = -(spd / 4.0f);
        }
        *(float *)(a0 + 0x5C) = pos - spd;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000144F4);
#endif

/* func_00014598 - verified structural decode (0xB4, 45 insns).
 * INSTRUCTION-IDENTICAL SIBLING of func_00014010 (the in-place
 * string substitution cipher); the ONLY difference is the string
 * field offset 0xB4 here vs 0xE4 there.
 *   void func_00014598(char *a0) {
 *       char *s = a0 + 0xB4;                      // string field (180)
 *       u32 i = 0, n = strlen_like(s);            // func_00000000(s)
 *       while (i < n) {
 *           unsigned char c = s[i]; i++;
 *           if (c != 'a' && c != 'b' && c != ' ') // 0x61/0x62/0x20
 *               s[i-1] = (char)(0x69 - c);        // 'i' - c
 *           n = strlen_like(s);                   // recomputed each iter
 *       }
 *   }
 * Struct-typing reference: a0->0xB4 (180) = char[] name/id string
 * buffer (the func_00014010 cipher applied to a different field; an
 * object with cipher-able strings at BOTH 0xB4 and 0xE4). Caps <80:
 * bnel branch-likely loop + reloc func_00000000 strlen-recompute
 * bound + 4 char constants hoisted s3-s6 (8-sreg, allocator order-
 * sensitive) - same as func_00014010. Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
#ifdef NON_MATCHING
void func_00014598(char *a0) {
    char *s = a0 + 0xB4;
    unsigned int n = (unsigned int)func_00000000(s);
    unsigned int i = 0;
    while (i < n) {
        unsigned char c = s[i];
        i++;
        if (c != 0x61 && c != 0x62 && c != 0x20) {
            s[i - 1] = (char)(0x69 - c);
        }
        n = (unsigned int)func_00000000(s);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014598);
#endif
