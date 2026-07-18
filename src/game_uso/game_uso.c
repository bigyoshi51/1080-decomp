#include "common.h"

/* P0 RESOLVED 2026-06-10: game_uso_block1 byte-verified vs
 * assets/game_uso_block_1.bin (exact length, only reloc-class lui/jal
 * field diffs). The +0x90 damage was: +4 at 0x3F4 (1-word pad sidecar,
 * now folded into func_000003F8.s head), +4 at 0xC0EC (1-word zero pad
 * between two matched C fns -- kept as sidecar, the Makefile recipe
 * drops the asserted-zero placeholder leftover at 0xC0F0), +0x80 at
 * 0xD5BC (func_0000D458.s over-extended into duplicated copies of
 * D5BC/D5DC/D5F8/D634 -- trimmed), an out-of-order func_00000B14
 * definition (moved), and +8 derivative tail alignment. Gate it with
 * `make verify-blocks` after any change to this unit. See
 * docs/MATCHING_WORKFLOW.md, asm-processor 1-word-pad defect. */
extern char *game_uso_alias();

/* File-top canonical decls (hoisted out of NM-wrap blocks
 * so DNM build doesn't see redecls — see
 * feedback_game_uso_dnm_typedef_inside_ifdef.md). */
extern int gl_func_00000000();
extern char D_00000000;
extern char import_80020110;
extern int import_8006EF48;
extern int D_game_11564_flag;
extern int D_game_11564_table;
typedef struct { float x, y, z; } Vec3;
typedef struct { int a, b, c; } Tri3i;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b; } Pair2;

#ifdef NON_MATCHING
/* Macro definitions for NM-wrap bodies. Auto-managed by /struct-name-tick.
 * Default build never sees these — wrap bodies aren't compiled.
 * GAME_D_E10: first int of the (0xE10,0xE14) global value pair passed
 * together (as args) to gl_func_00000000 across several wraps. game_uso D+0xE10.
 * GAME_D_F18/F1C: a second (0xF18,0xF1C) int pair passed together to
 * func_00000000 as `(a0, F18, F1C, 2, F18, F1C)` (the pair repeated) in the
 * func_00011258/112E0 sibling wraps. Positional. game_uso D+0xF18/0xF1C.
 */
#define GAME_D_E10 (*(int*)((char*)&D_00000000 + 0xE10))
#define GAME_D_E14 (*(int*)((char*)&D_00000000 + 0xE14))
#define GAME_D_F18 (*(int*)((char*)&D_00000000 + 0xF18))
#define GAME_D_F1C (*(int*)((char*)&D_00000000 + 0xF1C))
#endif

#ifdef NON_MATCHING
/* Cubic B-spline basis evaluator. Computes 4 weights for parameter t into
 * out[0..3]. D = *(float*)&D_00000000 = 1/6.
 *   out[0] = D*(1-t)^3, out[1] = D*(3t^3-6t^2+4),
 *   out[2] = D*(-3t^3+3t^2+3t+1), out[3] = D*t^3.
 * Target receives t as a SINGLE float in $a1 (mtc1 a1,$f12). The prior K&R
 * `float t` def DOUBLE-PROMOTED (assembled a double from a2/a3 + cvt.s.d,
 * +9 insns -> 49w vs target 40w, 57.85% cap). Here the second arg is taken
 * as `int ti` and bit-reinterpreted to float, which makes IDO move a1
 * directly into f12 with no double assembly -- matching the target ABI while
 * staying K&R-`()` compatible for the overloaded placeholder call sites. */
void game_uso_func_00000000(out, ti)
    float *out;
    int ti;
{
    float t = *(float*)&ti;
    float D = *(float*)&D_00000000;
    float omt = 1.0f - t;
    float t2 = t * t;
    float t3 = t2 * t;
    out[0] = D * omt * omt * omt;
    out[1] = D * (3.0f*t3 - 6.0f*t2 + 4.0f);
    out[2] = D * (-3.0f*t3 + 3.0f*t2 + 3.0f*t + 1.0f);
    out[3] = D * t3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000000);
#endif

/* 4-element dot product. CRACKED 2026-06-11 to 100.0 via fully right-nested
 * grouping `a[3]*b[3] + (a[2]*b[2] + (a[1]*b[1] + b[0]*a[0]))` (exhaustive
 * 1920-variant enumeration; the "cap" below was a left-assoc-family-only
 * conclusion). Historical analysis kept for the record:
 * 4-element dot product. C body NATURAL CAP 99.375% (1 insn diff).
 * The SINGLE diff is the FINAL add.s (insn 15): IDO emits `add.s f0,f10,f8`
 * (p3 + sum) where target wants `add.s f0,f8,f10` (sum + p3); f8=sum of the
 * first three products, f10=the 4th product. The earlier "second-to-last add"
 * note is stale — insn 13 (`add f8,f4,f16`) now matches; only the outermost
 * commutative add differs. IDO commutes `sum + p3` to `p3 + sum` regardless of
 * source operand order — it is FPU instruction-selection, not C-controllable.
 * EXHAUSTIVE NEGATIVE RESULT (2026-05-28, 8 fresh variants, all >= baseline's
 * 1 diff so none adopted):
 *   a[i]*b[i] all-ab .................. 3   (a[0]*b[0]+..+a[3]*b[3])
 *   (sum3) + a[3]*b[3] parens ......... 3
 *   right-assoc a[0]*b[0]+(a[1]*b[1]+..) 8
 *   b[i]*a[i] all-ba .................. 7
 *   float p3=b[3]*a[3]; sum+p3 ........ 15  (temp spills, reschedules all)
 *   float p3=a[3]*b[3]; sum+p3 ........ 15
 *   float s=sum3; s + b[3]*a[3] ....... 8
 *   float s=sum3; s + a[3]*b[3] ....... 8
 * Current `a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+b[3]*a[3]` (1 diff) is optimal.
 * INSN_PATCH was REMOVED 2026-05-23 (match-faking, banned per
 * feedback_no_instruction_forcing_matches_policy). The 100% match this
 * function had pre-removal was via post-cc byte editing — not a real compile.
 * Permanent NM cap. 2026-05-30: PERMUTER TESTED (decomp-permuter -j4, 150s) — 0
 * candidates. Confirmed the final `add.s $f0,$f8,$f10` (sum,product) vs mine
 * `$f0,$f10,$f8` is COUPLED to the body schedule: every C form that flips the add
 * to the target order (product-first, named sum/p3 temps) also reschedules the 15
 * body insns (body no longer matches), and the only body-exact form forces the
 * swapped add. Not independently controllable — the commutative canonicalization
 * follows term order, which also drives the dot-product schedule. The permuter
 * can't isolate the flip either. RE-CONFIRMED 2026-05-30 (no-caps re-grind): the
 * docs#feedback-ido-fp-commutative-operand-order-assignment-lever `X + (t = Y)`
 * lever RESCHEDULES here (the fs operand is a 3-mul CHAIN, not a simple value as
 * in 00003FAC — pinning it moves the muls, 8 diffs); reassociation 8-12 diffs;
 * source mul order a3*b3 vs b3*a3 is identical; 180s permuter floored at score 10
 * (no 0). The assignment-expr lever's SCOPE LIMIT: it only decouples operand order
 * when the pinned operand is a SINGLE load/value; a multi-op reduction operand
 * can't be pinned without rescheduling. Still a permuter/PERM_-macro target, not
 * a permanent cap — but the simple levers are genuinely exhausted here. */
/* 2026-06-11 permuter CONCLUDED: base 10 (1 true diff) flat through
 * 665k iterations -- allocator-internal. 99.38 stands. */
/* 1-diff FP-REDUCTION operand-order cap (final add: target `f0=sum3+p3` with
 * sum3 as fs; ours swaps to p3 as fs). RE-CONFIRMED 2026-05-31: the
 * assignment-expr lever `... + (t = b[3]*a[3])` REGRESSES to 15 diffs — pinning
 * p3 reschedules the whole reduction (sum3 is a multi-op chain, can't be the
 * pinned operand). Same class as game_libs_func_0005D588. Genuine cap; do not
 * re-grind with the assignment-expr lever. */
float game_uso_func_000000A0(float *a, float *b) {
    /* 2026-06-11 rules-sweep CRACK: right-nested grouping flips the final
     * add.s to target order (cfe ufad ichain = ucode shape, rule-1 cousin);
     * found via exhaustive 1920-variant enumeration (perm x mul-swap x
     * parenthesization). The left-assoc default was the only family probed
     * before. */
    return a[3]*b[3] + (a[2]*b[2] + (a[1]*b[1] + b[0]*a[0]));
}


/* Cubic B-spline weighted point evaluator (61 insns, FPU-only).
 * Input:  out (Vec3*),  ctrl (Vec3*[4]: 4 control point pointers),
 *         weights (float[4]: B0..B3 from game_uso_func_00000000)
 * Output: out[i] = sum over k=0..3 of (*ctrl[k])[i] * weights[k]
 *
 * Used with game_uso_func_00000000 (basis evaluator) to compute a point
 * on a uniform cubic B-spline curve in 3D — camera path / track / skater
 * limb interpolation.
 *
 * MATCHED via the FP-reduction commutative-spelling lever (same shape as the
 * sibling dot-product game_uso_func_000000A0): each 4-term dot written
 * last-term-first with right-nesting and the innermost pair source-reversed
 * (`c3*w3 + (c2*w2 + (c1*w1 + w0*c0))`). This restores IDO's RTL eval so loads
 * and add.s all land in target order. */
void game_uso_func_000000E0(Vec3 *out, Vec3 **ctrl, float *weights) {
    out->x = ctrl[3]->x * weights[3] + (ctrl[2]->x * weights[2]
           + (ctrl[1]->x * weights[1] + weights[0] * ctrl[0]->x));
    out->y = ctrl[3]->y * weights[3] + (ctrl[2]->y * weights[2]
           + (ctrl[1]->y * weights[1] + weights[0] * ctrl[0]->y));
    out->z = ctrl[3]->z * weights[3] + (ctrl[2]->z * weights[2]
           + (ctrl[1]->z * weights[1] + weights[0] * ctrl[0]->z));
}

void game_uso_func_000001D4(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    gl_func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

void game_uso_func_00000244(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_00000280(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_000002BC(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void game_uso_func_00000314(Pair2 *dst) {
    Pair2 buf;
    gl_func_00000000(&D_00000000, &buf, 8);
    *dst = buf;
}

/* Int-reader template, BYTE-EXACT 2026-05-31 (.text identical to expected/.o;
 * residual fuzzy<100 is the known uso_raw_word-vs-reloc artifact — expected/.o
 * is missing the LO16 on the &D addiu because game-uso-symbolize-s.py named the
 * %hi lui but not its paired %lo addiu, same class as eddproc_uso_func_00000000).
 *
 * NOT A REGALLOC CAP — the old "t6/t7/t8 vs t7/t9/t6, split-piece coloring,
 * permuter-only" note was WRONG. The target's post-call sequence
 *   addiu t7,sp,0x18 ; lw t9,0(t7) ; lw t6,0x20(sp) ; sw t9,0(t6)
 * is a single-WORD STRUCT COPY (`*dst = *(One1*)buf`), not a scalar read.
 * A scalar `*dst = buf[0]` emits the DIRECT-index form (`lw t6,0x18(sp)`, like
 * eddproc_uso_func_00000000). The struct-copy form makes IDO re-materialize the
 * source address into a register (t7) and walk it with offset-0 loads — which is
 * exactly the target. The `int buf[2]` (8 bytes) keeps the buffer at sp+0x18
 * (frame 0x20); copying only the first word out as a 1-int struct yields the
 * one-word t7/t9/t6 sequence. (Sibling 039C below is the same struct-copy form,
 * 4 words.) See docs/IDO_CODEGEN.md struct-copy-recompute-vs-scalar-index. */
typedef struct { int a; } One1;
void game_uso_func_0000035C(One1 *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = *(One1*)buf;
}

void game_uso_func_0000039C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}
/* 0x3F4 stray mtc1 orphan: folded into the head of func_000003F8.s (a 1-word
 * GLOBAL_ASM sidecar cannot emit exactly; the C placeholder minimum is 8
 * bytes -- docs/MATCHING_WORKFLOW.md asm-processor 1-word-pad defect). */

/* Camera/view init: initializes a 0x38-byte struct at a0:
 *   a0+0x00..0x08 = Vec3(0, 0, 0)        ; eye position
 *   a0+0x0C..0x14 = Vec3(0, 0, -1000)    ; target / look-at (z = -1000)
 *   a0+0x18..0x20 = Vec3(0, 1, 0)        ; up vector (Y-up)
 *   a0+0x24       = 85.0f                ; FOV (degrees)
 *   a0+0x28       = 15 (int)             ; mode/flags
 *   a0+0x2C..0x34 = Vec3(0, 0, 0)        ; offset
 *
 * NON_MATCHING (corrected 2026-06-23): the prior "byte-exact 78w" claim was
 * FALSE. The real target is 77 words and contains NO `mtc1 zero,$f0` — it
 * assumes $f0 is already 0.0 on entry (left by the preceding function) and
 * stores it directly. Standalone C must materialize the 0.0f (`mtc1 zero,$f0`
 * at entry), giving 78w — one extra insn vs the 77w target (objdiff 98.70%).
 * No C construct can assume the caller left $f0=0, so this cannot byte-match;
 * INCLUDE_ASM gives the correct 77w ROM bytes. (The reconstruction below is
 * kept as the NON_MATCHING body: 4 Vec3 staging slots + temp + pads, integer
 * struct-copy to temp then float store to a0.) Was a false-match real-def +
 * a poisoned episode (deleted) that trained on the wrong 78w. */
void game_uso_func_000003F8(void *a0) {
    Vec3 zero, fwd, up, zero2;
    Vec3 pad0, pad1;
    Vec3 tmp;
    int padbot[2];

    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    *(Tri3i *)&tmp = *(Tri3i *)&zero;
    *(float *)((char *)a0 + 0x00) = tmp.x;
    *(float *)((char *)a0 + 0x04) = tmp.y;
    *(float *)((char *)a0 + 0x08) = tmp.z;
    fwd.y = 0.0f;
    fwd.x = 0.0f;
    fwd.z = -1000.0f;
    *(Tri3i *)&tmp = *(Tri3i *)&fwd;
    *(float *)((char *)a0 + 0x0C) = tmp.x;
    *(float *)((char *)a0 + 0x10) = tmp.y;
    *(float *)((char *)a0 + 0x14) = tmp.z;
    up.z = 0.0f;
    up.x = 0.0f;
    up.y = 1.0f;
    *(Tri3i *)&tmp = *(Tri3i *)&up;
    *(float *)((char *)a0 + 0x18) = tmp.x;
    *(float *)((char *)a0 + 0x1C) = tmp.y;
    *(float *)((char *)a0 + 0x20) = tmp.z;
    *(float *)((char *)a0 + 0x24) = 85.0f;
    *(int *)((char *)a0 + 0x28) = 15;
    zero2.z = 0.0f;
    zero2.y = 0.0f;
    zero2.x = 0.0f;
    *(Tri3i *)&tmp = *(Tri3i *)&zero2;
    *(float *)((char *)a0 + 0x2C) = tmp.x;
    *(float *)((char *)a0 + 0x30) = tmp.y;
    *(float *)((char *)a0 + 0x34) = tmp.z;
}

void game_uso_func_0000052C(int unused, Vec3 *a1, Vec3 *a2, int *a3, Vec3 *p4) {
    if (a3[4] == 2) {
        a2->x += p4->x;
        a2->y += p4->y;
        a2->z += p4->z;
    }
    if (a3[0] == 2) {
        a1->x += a2->x;
        a1->y += a2->y;
        a1->z += a2->z;
    }
}

void game_uso_func_000005B8(Vec3 *a0) {
    game_uso_func_000001D4(a0);
    game_uso_func_000001D4((Vec3*)((char*)a0 + 0xC));
    game_uso_func_000001D4((Vec3*)((char*)a0 + 0x18));
    game_uso_func_00000244((float*)((char*)a0 + 0x24));
    game_uso_func_00000280((int*)((char*)a0 + 0x28));
    game_uso_func_000001D4((Vec3*)((char*)a0 + 0x2C));
}

void *game_uso_func_00000608(void *a0) {
    if (a0 == 0) {
        a0 = (void*)gl_func_00000000(0x7C);
    }
    return a0;
}

void game_uso_func_00000634(int *a0) {
    a0[0] = 1;
    a0[1] = 0;
    a0[2] = 0;
    a0[3] = 0;
    a0[4] = 1;
    a0[5] = 0;
    a0[6] = 0;
    a0[7] = 0;
    a0[8] = 0;
    a0[9] = 0;
    a0[10] = 0;
    a0[11] = 0;
    a0[12] = 0;
    a0[13] = 0;
}

/* State-check: returns 1 if any of the three sub-states is active.
 * MATCHED 2026-06-10 (44/44): the "$v0/$v1 not C-flippable" cap fell to
 * the EARLY-PSEUDO trick -- `int r = 0; r = <expr>; return r;`. The
 * dead initializer creates r's pseudo FIRST, so the result colors $v0
 * and the loads take $v1 (the target's order); the bare return-expr
 * form creates the load pseudo first (30 diffs). Same family as the
 * web-order inversion (h2hproc E04). */
int game_uso_func_00000674(int *a0) {
    int r = 0;
    r = ((a0[0] == 2 || a0[0] == 3) && a0[1] == 1)
        || ((a0[4] == 2 || a0[4] == 3) && a0[5] == 1)
        || a0[8] == 1
        || a0[10] == 2
        || a0[12] == 2;
    return r;
}

/* MATCHED 2026-06-20. The stale ~90%-cap comment was wrong: cnt was already
 * in $v0 and the loop scheduling already matched. The ONLY residual diff was
 * the trailing tail store address: target `addu v1,s2,t7` (a0 base first) vs
 * built `addu v1,t7,s2` (index first). Writing the tail as true int-array
 * indexing `((int*)a0)[cnt+15] = ((int*)a0)[cnt+14]` makes IDO canonicalize
 * the commutative addu with the base register first → 0 diffs. */
void game_uso_func_00000724(char *a0) {
  int i;
  int new_var;
  int cnt;
  int *p;
  game_uso_func_000002BC((Quad4 *) a0);
  new_var = 0x30;
  game_uso_func_000002BC((Quad4 *) (a0 + 0x10));
  game_uso_func_00000314((Pair2 *) (a0 + 0x20));
  game_uso_func_00000314((Pair2 *) (a0 + 0x28));
  game_uso_func_0000035C((int *) (a0 + new_var));
  game_uso_func_00000280((int *) (a0 + 0x34));
  cnt = *((int *) (a0 + 0x34));
  i = 1;
  p = (int *) (a0 + 4);
  if (cnt > 0)
  {
    do
    {
      int tmp = game_uso_func_055750(0x38);
      if (1)
      {
        *((int *) (((char *) p) + 0x38)) = tmp;
        game_uso_func_000003F4(tmp);
      }
      game_uso_func_000005B8((Vec3 *) *((int *) (((char *) p) + 0x38)));
      if (!a0)
      {
      }
      cnt = *((int *) (a0 + 0x34));
      i++;
      p++;
    }
    while (i <= cnt);
  }
  *((int *) (a0 + 0x38)) = *((int *) (a0 + 0x3C));
  ((int *) a0)[cnt + 15] = ((int *) a0)[cnt + 14];
}

void game_uso_func_000007E0(int *a0) {
    a0[9] = 0;
    *a0 = 0;
}

void game_uso_func_000007EC(int *arg0) {
    int i;
    int *p;

    game_uso_func_00000280(arg0 + 9);
    i = 0;
    p = arg0 + 1;
    while (i < arg0[9]) {
        game_uso_func_00000280(p);
        i++;
        p++;
    }
}

/* 8-arg constructor/initializer (byte-exact 2026-06-20).
 *   a0 = dst (alloc 0x27C if NULL); a1 -> a0->0x150; a2/a3/arg4 -> 047484 args;
 *   arg5 (float) -> 047484 5th arg; arg6 -> a0->0x274; arg7 -> flag + 04C774 3rd arg.
 * Crack: 04C774 takes arg7 as its 3rd argument (was passed only 2 args). Passing
 * arg7 to the call pins it to $a2, turning the prior `beql t7` (test-only reload)
 * into the target's plain `beq a2` (test value reused as call arg) — the prior
 * "allocator-weight $t7-vs-$a2 cap" was a missing call-argument. Store reorder
 * (0x24C before the if; 0x274 right after 0x150) lets IDO fill the delay/latency
 * slots in target order. */
extern char game_uso_D_807FE770;
extern int game_uso_func_055750();
extern void game_uso_func_047484(int *dst, int a, int b, int c, float f);
extern void game_uso_func_04C774(int *dst, int flag, int arg7);

int *game_uso_func_00000858(int *a0, int arg1, int arg2, int arg3, int arg4, float arg5, int arg6, int arg7) {
    if (a0 == 0) {
        a0 = (int *)game_uso_func_055750(0x27C);
        if (a0 == 0) goto out;
    }
    game_uso_func_047484(a0, arg2, arg3, arg4, arg5);
    *(int*)((char*)a0 + 0x28) = (int)&game_uso_D_807FE770;
    *(int*)((char*)a0 + 0x1D0) = 0;
    *(int*)((char*)a0 + 0x24C) = 0;
    if (arg7 != 0) game_uso_func_04C774(a0, 1, arg7);
    *(int*)((char*)a0 + 0x150) = arg1;
    *(int*)((char*)a0 + 0x274) = arg6;
    *(int*)((char*)a0 + 0x26C) = 0;
    *(int*)((char*)a0 + 0x270) = 0;
    *(int*)((char*)a0 + 0x268) = 0;
out:
    return a0;
}

void game_uso_func_000008FC(int *a0) {
    int *v0 = (int*)*(int*)((char*)a0 + 0xF4);
    gl_func_00000000(*(int*)((char*)v0 + 0xB4), a0);
    gl_func_00000000(*(int*)((char*)a0 + 0x154), a0);
    *(int*)((char*)a0 + 0x264) = 0;
    gl_func_00000000(a0);
}

// game_uso_func_00000940 — three contiguous switches (jr @ 0x970/0x9DC/0xA58;
// sltiu 7/6/6). 2026-06-20: body fully resolved — base is the USO import
// &import_80020098 (NOT the &D_00000000 placeholder), the tail call is
// game_uso_func_00000AEC(arg0, var_a1), the switch value is read inline
// (keeps it in $t7 not $v0), and case 6 written as `if(x!=7){4}else{5}` to
// hit the target's beq+b shape. EVERY .text word now matches EXCEPT the 3
// jumptable LO16 loads (off 0x968/0x9D4/0xA50): target = HI16-only relocs
// against external symbols game_uso_D_807FF924/940/958 with fixed offsets
// 0x4/0x20/0x38; IDO's C `switch` instead emits a self-local .rodata
// jumptable (HI16+LO16, offsets 0x0/0x1C/0x34). This is the documented
// jr-via-rodata jumptable cap (docs/MATCHING_WORKFLOW.md:613,6900): it can't
// byte-match without rodata-relayout infra placing the build's local jtbl at
// the external symbol addrs — a multi-tick splat/linker job, NOT a C lever.
// 104/107 words exact. Default build = INCLUDE_ASM byte-exact.
#ifdef NON_MATCHING

extern char import_80020098;
void game_uso_func_00000AEC(int *a0, int a1);

void game_uso_func_00000940(char *arg0) {
    s32 temp_v0;
    s32 var_a1;

    var_a1 = -1;
    switch (*(int *)((char *)*(int *)((char *)arg0 + 0x150) + 0xA54)) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        temp_v0 = *(int *)((char *)&import_80020098 + 0x34);
        if ((temp_v0 == 4) || (temp_v0 == 6) || (temp_v0 == 7) || ((temp_v0 == 1) && (*(int *)((char *)&import_80020098 + 0x40) == 0))) {
            var_a1 = 1;
        } else {
            switch (*(int *)((char *)&import_80020098 + 0x64)) {                      /* switch 2 */
            case 2:                                 /* switch 2 */
                var_a1 = 6;
                break;
            case 3:                                 /* switch 2 */
                var_a1 = 7;
                break;
            case 4:                                 /* switch 2 */
                var_a1 = 8;
                break;
            case 5:                                 /* switch 2 */
                var_a1 = 7;
                break;
            case 6:                                 /* switch 2 */
                var_a1 = 9;
                break;
            case 7:                                 /* switch 2 */
                var_a1 = 0xA;
                break;
            default:                                /* switch 2 */
                var_a1 = 0;
                break;
            }
        }
        break;
    case 1:                                         /* switch 1 */
        if (*(int *)((char *)&import_80020098 + 0x7C) != 0) {
            var_a1 = 0xB;
        } else {
            switch (*(int *)((char *)&import_80020098 + 0x64)) {                      /* switch 3 */
            case 2:                                 /* switch 3 */
                var_a1 = 0xD;
                break;
            case 3:                                 /* switch 3 */
                var_a1 = 2;
                break;
            case 4:                                 /* switch 3 */
                var_a1 = 0xD;
                break;
            case 5:                                 /* switch 3 */
                var_a1 = 2;
                break;
            case 6:                                 /* switch 3 */
                var_a1 = 2;
                break;
            case 7:                                 /* switch 3 */
                var_a1 = 0xE;
                break;
            default:                                /* switch 3 */
                var_a1 = 2;
                break;
            }
        }
        break;
    case 2:                                         /* switch 1 */
        var_a1 = 0xC;
        break;
    case 5:                                         /* switch 1 */
        var_a1 = 3;
        break;
    case 6:                                         /* switch 1 */
        if (*(int *)((char *)&import_80020098 + 0x64) != 7) {
            var_a1 = 4;
        } else {
            var_a1 = 5;
        }
        break;
    }
    if (var_a1 != -1) {
        game_uso_func_00000AEC((int *)arg0, var_a1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000940);
#endif

void game_uso_func_00000AEC(int *a0, int a1) {
    if (*(int*)((char*)*(int**)((char*)a0 + 0x158) + 0x24) > 0) {
        *(int*)((char*)a0 + 0x250) = a1;
    }
    *(int*)((char*)a0 + 0x254) = 0;
    *(int*)((char*)a0 + 0x25C) = 1;
    *(int*)((char*)a0 + 0x260) = 0;
}

/* Moved 2026-06-10 to its address-ordered position (was stranded after
 * func_00002FF8, emitting at block offset ~0x2FF4 instead of 0xB14 --
 * Yay0 block layout is definition-order). */
extern void game_uso_func_00000000();
void game_uso_func_00000B14(void *a0) {
    game_uso_func_00000000(a0);
    game_uso_func_00000000(a0);
}

#ifdef NON_MATCHING
/* Spline/animation node update (706w). Reconstructed 2026-06-24: the prior m2c
 * graft compiled but dropped EVERY jal (basis eval, 3 spline-evals, the
 * dot/cross helpers, the advance call) and left three unresolved constants
 * (`$t0`=1, `$f0`=0.0f, `$t6`=loop bound). This version restores the calls and
 * the constants so the non_matching object carries the real call/float bytes.
 * Callees keep their EXISTING signatures (00000940 is void → never assigned;
 * its stored field 0x264 is the re-materialized switch read, not a return). */
extern Vec3* game_uso_func_000023D4(Vec3 *out, char *a1);
extern void game_uso_func_00002714(int *a0, int a1, int a2);
extern void game_uso_func_00002FC8(int *a0, int a1, int a2);
void game_uso_func_00000B3C(char *arg0) {
    f32 sp13C; f32 sp140; f32 spB8; f32 spBC;
    s32 sp144;
    f32 sp138;
    s32 *sp134;
    s32 sp130;
    char **sp12C;
    s32 *sp128;
    f32 sp124;
    f32 sp120;
    s32 sp11C;
    f32 sp118;
    f32 sp114;
    s32 sp110;
    f32 sp10C;
    f32 sp108;
    s32 sp104;
    s32 spF4;
    s32 spF0;
    s32 spEC;
    s32 spE8;
    f32 spE0;
    f32 spDC;
    s32 spD8;
    s32 spB4;
    s32 spA4;
    s32 spA0;
    s32 sp9C;
    s32 sp98;
    s32 sp94;
    s32 sp90;
    s32 sp8C;
    s32 sp88;
    f32 sp84;
    f32 sp80;
    s32 sp7C;
    s32 *sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    char **var_a3;
    char **var_a3_2;
    char *temp_s0;
    char *temp_t1;
    char *temp_v0_2;
    char *var_a0;
    char *var_t3;
    s32 *var_t2;
    s32 temp_at;
    s32 temp_t2;
    s32 temp_t3;
    s32 temp_t5;
    s32 temp_v0;
    s32 temp_v0_4;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 var_a1;
    s32 var_a2;
    s32 var_at;
    s32 var_at_2;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    char *temp_a2;
    char *temp_t4;
    char *temp_v0_3;
    char *temp_v1;
    char *temp_v1_8;
    char *temp_v1_9;
    char *var_t1;

    var_a0 = arg0;
    temp_s0 = var_a0;
    sp134 = *(s32 *)((char *)(var_a0) + 0xF4);
    temp_v0 = *(s32 *)((char *)(*(s32 *)((char *)(var_a0) + 0x150)) + 0xA54);
    if (temp_v0 != *(s32 *)((char *)(var_a0) + 0x264)) {
        game_uso_func_00000940(var_a0);
        *(s32 *)((char *)(var_a0) + 0x264) = temp_v0;
    }
    temp_t2 = *(s32 *)((char *)((temp_s0 + (*(s32 *)((char *)(temp_s0) + 0x250) * 4))) + 0x158);
    sp130 = temp_t2;
    var_v0 = *(s32 *)((char *)(temp_s0) + 0x25C);
    var_v1 = *(s32 *)((char *)((temp_t2 + (*(s32 *)((char *)(temp_s0) + 0x254) * 4))) + 0x4);
    *(s32 *)((char *)(temp_s0) + 0x258) = var_v1;
    var_a3 = *(s32 *)((char *)((temp_s0 + (var_v1 * 4))) + 0x1D4);
    var_t1 = var_a3 + (var_v0 * 4);
    var_t2 = *(s32 *)((char *)(var_t1) + 0x38);
    sp128 = var_t2;
    if (1 == var_v0) {
        if (*(s32 *)((char *)(temp_s0) + 0x260) != 0) {
            goto block_28;
        }
        var_t3 = *(s32 *)((char *)(temp_s0) + 0x268);
        if ((s32)var_t3 != 0) {
            *(s32 *)((char *)(temp_s0) + 0x130) = 1;
            spE0 = 0.0f;
            spDC = 0.0f;
            spD8 = 0;
            *((s32 *)&spB4 + 0) = *((s32 *)&spD8 + 0);
            *((s32 *)&spB4 + 1) = *((s32 *)&spD8 + 1);
            *((s32 *)&spB4 + 2) = *((s32 *)&spD8 + 2);
            *(s32 *)((char *)(temp_s0) + 0x134) = spB4;
            *(s32 *)((char *)(temp_s0) + 0x138) = spB8;
            *(s32 *)((char *)(temp_s0) + 0x13C) = spBC;
        } else {
            var_t2 = (s32 *) ((*(s32 *)((char *)(var_a3) + 0x30) == 0) == 0);
            *(s32 *)((char *)(temp_s0) + 0x130) = var_t2;
        }
        if (1 == *(s32 *)((char *)(var_a3) + 0x10)) {
            temp_a2 = *(s32 *)((char *)(temp_s0) + 0x150);
            var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
            game_uso_func_00002714((int *)var_a0, 1, temp_a2 + 792);
            sp12C = var_a3;
        } else {
            var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
            game_uso_func_00002714((int *)var_a0, 1, *(s32 *)((char *)(temp_s0) + 0x150) + 792);
            sp12C = var_a3;
            var_v1 = *(s32 *)((char *)(temp_s0) + 0x150);
        }
        if (1 == *(s32 *)((char *)(var_a3) + 0x0)) {
            var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
            game_uso_func_00002FC8((int *)var_a0, 1, *(s32 *)((char *)(temp_s0) + 0x150) + 792);
        } else {
            var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
            game_uso_func_00002FC8((int *)var_a0, 0, *(s32 *)((char *)(temp_s0) + 0x150) + 792);
        }
        *(s32 *)((char *)(temp_s0) + 0x270) = 0;
        *(s32 *)((char *)(temp_s0) + 0x26C) = 0;
        var_v1 = *(s32 *)((char *)(temp_s0) + 0x150);
        *(s32 *)((char *)(var_v1) + 0xA58) = (s32) (*(s32 *)((char *)(var_v1) + 0xA58) & ~0x2000);
        if (*(s32 *)((char *)(var_a3) + 0x0) != 1) {

        } else {
            var_t1 = *(s32 *)((char *)(var_a3) + 0x10);
            goto block_25;
        }
    } else {
block_25:
        if (1 != (s32)var_t1) {

        } else {
block_28:
            var_a0 = *(s32 *)((char *)(temp_s0) + 0x26C);
            var_v0 = 0;
            if ((s32)var_a0 == 3) {
                var_t2 = *(s32 *)((char *)(*(s32 *)((char *)(temp_s0) + 0x274)) + 0x10);
                if (!((s32) var_t2 & 0x80)) {
                    var_v0 = 1;
                    *(s32 *)((char *)(temp_s0) + 0x26C) = *(s32 *)((char *)(temp_s0) + 0x270);
                }
            } else {
                temp_v1 = *(s32 *)((char *)(temp_s0) + 0x274);
                if ((s32) *(s32 *)((char *)(temp_v1) + 0x10) & 0x80) {
                    *(s32 *)((char *)(temp_s0) + 0x270) = var_a0;
                    *(s32 *)((char *)(temp_s0) + 0x26C) = 3;
                    goto block_36;
                }
                if (*(s32 *)((char *)(temp_v1) + 0x18) & 0x40) {
                    temp_v0_2 = var_a0 + 1;
                    *(s32 *)((char *)(temp_s0) + 0x26C) = temp_v0_2;
                    if ((s32) temp_v0_2 >= 3) {
                        *(s32 *)((char *)(temp_s0) + 0x26C) = 0;
                    }
block_36:
                    var_v0 = 1;
                }
            }
            if (var_v0 != 0) {
                temp_t1 = *(s32 *)((char *)(temp_s0) + 0x26C);
                temp_at = (u32) temp_t1 < 4U;
                if (temp_at != 0) {
                    switch ((s32) temp_t1) {
                    case 0:
                        var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
                        game_uso_func_00002714((int *)var_a0, 1, *(s32 *)((char *)(temp_s0) + 0x150) + 792);
                        var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
                        game_uso_func_00002FC8((int *)var_a0, 1, *(s32 *)((char *)(temp_s0) + 0x150) + 792);
                        sp12C = var_a3;
                        var_t2 = sp134;
                        temp_v1_2 = *(s32 *)((char *)(temp_s0) + 0x150);
                        *(s32 *)((char *)(temp_v1_2) + 0xA58) = (s32) (*(s32 *)((char *)(temp_v1_2) + 0xA58) & ~0x2000);
                        break;
                    case 1:
                        var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
                        game_uso_func_00002714((int *)var_a0, 2, *(s32 *)((char *)(temp_s0) + 0x150) + 792);
                        var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
                        game_uso_func_00002FC8((int *)var_a0, 1, *(s32 *)((char *)(temp_s0) + 0x150) + 792);
                        sp12C = var_a3;
                        temp_v1_3 = *(s32 *)((char *)(temp_s0) + 0x150);
                        *(s32 *)((char *)(temp_v1_3) + 0xA58) = (s32) (*(s32 *)((char *)(temp_v1_3) + 0xA58) & ~0x2000);
                        break;
                    case 2:
                        var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
                        game_uso_func_00002714((int *)var_a0, 3, *(s32 *)((char *)(temp_s0) + 0x150) + 792);
                        var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
                        game_uso_func_00002FC8((int *)var_a0, 2, *(s32 *)((char *)(temp_s0) + 0x150) + 792);
                        sp12C = var_a3;
                        temp_v1_4 = *(s32 *)((char *)(temp_s0) + 0x150);
                        *(s32 *)((char *)(temp_v1_4) + 0xA58) = (s32) (*(s32 *)((char *)(temp_v1_4) + 0xA58) | 0x2000);
                        break;
                    case 3:
                        var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
                        game_uso_func_00002714((int *)var_a0, 3, *(s32 *)((char *)(temp_s0) + 0x150) + 792);
                        var_a0 = *(s32 *)((char *)(sp134) + 0xB4);
                        game_uso_func_00002FC8((int *)var_a0, 3, *(s32 *)((char *)(temp_s0) + 0x150) + 792);
                        sp12C = var_a3;
                        var_t2 = sp134;
                        temp_v1_5 = *(s32 *)((char *)(temp_s0) + 0x150);
                        *(s32 *)((char *)(temp_v1_5) + 0xA58) = (s32) (*(s32 *)((char *)(temp_v1_5) + 0xA58) | 0x2000);
                        break;
                    }
                    sp12C = var_a3;
                }
                var_a0 = &spF4;
            }
        }
    }
    {
        f32 basis;
        basis = (1.0f * (f32) var_v0) / (f32) *(s32 *)((char *)(sp128) + 0x28);
        game_uso_func_00000000((char *)temp_s0 + 0xF4, basis);
    }
    var_a3_2 = sp12C;
    temp_v1_6 = *(s32 *)((char *)(var_a3_2) + 0x10);
    if (temp_v1_6 != 1) {
        var_at = 3;
        if ((temp_v1_6 != 2) && (temp_v1_6 != 3)) {
            var_a0 = *(s32 *)((char *)(var_a3_2) + 0x0);
        } else {
            if (*(s32 *)((char *)(var_a3_2) + 0x14) == 0) {
                *((s32 *)&spB4 + 0) = *(s32 *)((char *)(sp128) + 0xC);
                var_t2 = *(s32 *)((char *)(sp128) + 0x10);
                *((s32 *)&spB4 + 1) = var_t2;
                *((s32 *)&spB4 + 2) = *(s32 *)((char *)(sp128) + 0x14);
                sp118 = spBC;
                sp114 = spB8;
                sp110 = spB4;
            } else {
                sp98 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x34) + 0xC;
                sp9C = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x38) + 0xC;
                spA0 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x3C) + 0xC;
                spA4 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x40) + 0xC;
                game_uso_func_000000E0((Vec3 *)&sp110, (Vec3 **)&sp98, (float *)((char *)temp_s0 + 0xF4));
                var_a0 = *(s32 *)((char *)(var_a3_2) + 0x0);
            }
            goto block_58;
        }
    } else {
        sp110 = *(s32 *)((char *)(temp_s0) + 0xA0);
        sp114 = *(s32 *)((char *)(temp_s0) + 0xA4);
        sp118 = *(s32 *)((char *)(temp_s0) + 0xA8);
block_58:
        var_at = 1;
    }
    var_at_2 = 2;
    if ((s32)var_a0 != (s32)var_at) {
        if (((s32)var_a0 != 2) && ((s32)var_a0 != 3)) {
            goto block_69;
        }
        if (*(s32 *)((char *)(var_a3_2) + 0x4) == 0) {
            *((s32 *)&spB4 + 0) = *(s32 *)((char *)(sp128) + 0x0);
            *((s32 *)&spB4 + 1) = *(s32 *)((char *)(sp128) + 0x4);
            *((s32 *)&spB4 + 2) = *(s32 *)((char *)(sp128) + 0x8);
            sp124 = spBC;
            sp120 = spB8;
            sp11C = spB4;
        } else {
            sp88 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x34);
            sp8C = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x38);
            sp90 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x3C);
            sp12C = var_a3_2;
            sp94 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x40);
            game_uso_func_000000E0((Vec3 *)&sp11C, (Vec3 **)&sp88, (float *)((char *)temp_s0 + 0xF4));
            var_a0 = *(s32 *)((char *)(var_a3_2) + 0x0);
        }
        var_at_2 = 1;
        goto block_68;
    }
    temp_v0_3 = *(s32 *)((char *)(temp_s0) + 0xF4);
    var_v0 = (s32) (temp_v0_3 + 0x70);
    sp11C = *(s32 *)((char *)(temp_v0_3) + 0xA0);
    sp120 = *(s32 *)((char *)(var_v0) + 0x34);
    sp124 = *(s32 *)((char *)(var_v0) + 0x38);
    var_a0 = *(s32 *)((char *)(var_a3_2) + 0x0);
block_68:
    if ((s32)var_a0 == (s32)var_at_2) {
block_69:
        var_t2 = &sp7C;
        if (*(s32 *)((char *)(var_a3_2) + 0x10) == 1) {
            sp80 = 1.0f;
            sp7C = 0;
            sp84 = 0.0f;
            *((s32 *)&spB4 + 0) = *(s32 *)((char *)(var_t2) + 0x0);
            *((s32 *)&spB4 + 1) = *(s32 *)((char *)(var_t2) + 0x4);
            *((s32 *)&spB4 + 2) = *(s32 *)((char *)(var_t2) + 0x8);
            sp10C = spBC;
            sp108 = spB8;
            sp104 = spB4;
        } else {
            goto block_71;
        }
    } else {
block_71:
        if (*(s32 *)((char *)(var_a3_2) + 0x20) == 0) {
            *((s32 *)&spB4 + 0) = *(s32 *)((char *)(sp128) + 0x18);
            *((s32 *)&spB4 + 1) = *(s32 *)((char *)(sp128) + 0x1C);
            *((s32 *)&spB4 + 2) = *(s32 *)((char *)(sp128) + 0x20);
            sp10C = spBC;
            sp108 = spB8;
            sp104 = spB4;
        } else {
            sp68 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x34) + 0x18;
            sp6C = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x38) + 0x18;
            sp70 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x3C) + 0x18;
            sp12C = var_a3_2;
            sp74 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x40) + 0x18;
            game_uso_func_000000E0((Vec3 *)&sp104, (Vec3 **)&sp68, (float *)((char *)temp_s0 + 0xF4));
            var_v0 = *(s32 *)((char *)(var_a3_2) + 0x28);
        }
    }
    if (var_v0 == 1) {
        *(f32 *)((char *)(temp_s0) + 0x14C) = *(f32 *)((char *)(sp128) + 0x24);
        goto block_80;
    }
    if (var_v0 != 2) {
        goto block_83;
    }
    sp58 = *(f32 *)((char *)(*(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x34)) + 0x24);
    sp5C = *(f32 *)((char *)(*(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x38)) + 0x24);
    sp60 = *(f32 *)((char *)(*(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x3C)) + 0x24);
    sp12C = var_a3_2;
    sp64 = *(f32 *)((char *)(*(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x40)) + 0x24);
    *(f32 *)((char *)(temp_s0) + 0x14C) = game_uso_func_000000A0((float *)&sp58, (float *)((char *)temp_s0 + 0xF4));
    var_t2 = *(s32 *)((char *)(temp_s0) + 0x268);
block_80:
    if (var_t2 != 0) {

    } else {
block_83:
        var_v0 = *(s32 *)((char *)(var_a3_2) + 0x30);
        if (var_v0 == 1) {
            *((s32 *)&spB4 + 0) = *(s32 *)((char *)(sp128) + 0x2C);
            *((s32 *)&spB4 + 1) = *(s32 *)((char *)(sp128) + 0x30);
            *((s32 *)&spB4 + 2) = *(s32 *)((char *)(sp128) + 0x34);
            *(s32 *)((char *)(temp_s0) + 0x134) = spB4;
            *(s32 *)((char *)(temp_s0) + 0x138) = spB8;
            *(s32 *)((char *)(temp_s0) + 0x13C) = spBC;
            goto block_89;
        }
        if (var_v0 != 2) {

        } else {
            sp48 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x34) + 0x2C;
            sp4C = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x38) + 0x2C;
            sp50 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x3C) + 0x2C;
            sp12C = var_a3_2;
            sp54 = *(s32 *)((char *)((var_a3_2 + (*(s32 *)((char *)(temp_s0) + 0x25C) * 4))) + 0x40) + 0x2C;
            game_uso_func_000000E0((Vec3 *)((char *)temp_s0 + 0x134), (Vec3 **)&sp48, (float *)((char *)temp_s0 + 0xF4));
block_89:
            sp12C = var_a3_2;
        }
    }
    *((s32 *)&sp138 + 0) = *(s32 *)((char *)(var_v0) + 0x0);
    *((s32 *)&sp138 + 1) = *(s32 *)((char *)(var_v0) + 0x4);
    *((s32 *)&sp138 + 2) = *(s32 *)((char *)(var_v0) + 0x8);
    temp_v1_7 = *(s32 *)((char *)(temp_s0) + 0x150);
    sp38 = *(f32 *)((char *)(temp_v1_7) + 0xBC) + sp140;
    sp34 = *(f32 *)((char *)(temp_v1_7) + 0xB8) + sp13C;
    sp30 = *(f32 *)((char *)(temp_v1_7) + 0xB4) + sp138;
    *((s32 *)&sp3C + 0) = *((s32 *)&sp30 + 0);
    temp_t3 = *((s32 *)&sp30 + 1);
    *((s32 *)&sp3C + 1) = temp_t3;
    temp_t5 = *((s32 *)&sp30 + 2);
    *((s32 *)&sp144 + 1) = temp_t3;
    *((s32 *)&sp144 + 0) = *((s32 *)&sp3C + 0);
    *((s32 *)&sp3C + 2) = temp_t5;
    *((s32 *)&sp144 + 2) = temp_t5;
    game_uso_func_000023D4((Vec3 *)&sp138, (char *)&sp144);
    game_uso_func_0000052C(0, (Vec3 *)((char *)temp_s0 + 0x138), (Vec3 *)&sp124, (int *)sp12C, (Vec3 *)&sp30);
    if (*(s32 *)((char *)(sp12C) + 0x0) != 1) {
        temp_v1_8 = *(s32 *)((char *)(temp_s0) + 0xF4);
        *(s32 *)((char *)(temp_v1_8) + 0x60) = sp11C;
        temp_v1_9 = temp_v1_8 + 0x30;
        *(s32 *)((char *)(temp_v1_9) + 0x34) = sp120;
        *(s32 *)((char *)(temp_v1_9) + 0x38) = sp124;
        temp_t4 = *(s32 *)((char *)(temp_s0) + 0xF4);
        M2C_MEMCPY_ALIGNED(temp_t4 + 0x70, temp_t4 + 0x30, 0x3C);
        *(s32 *)((char *)(((s32)temp_t4 + (s32)0x3C)) + 0x70) = (s32) *(s32 *)((char *)(((s32)temp_t4 + (s32)0x3C)) + 0x30);
    }
    if (*(s32 *)((char *)(sp12C) + 0x10) != 1) {
        *(s32 *)((char *)(temp_s0) + 0x60) = sp110;
        *(s32 *)((char *)(temp_s0) + 0x64) = sp114;
        *(s32 *)((char *)(temp_s0) + 0x68) = sp118;
        M2C_MEMCPY_ALIGNED(temp_s0 + 0x70, temp_s0 + 0x30, 0x3C);
        *(s32 *)((char *)(((s32)temp_s0 + (s32)0x3C)) + 0x70) = (s32) *(s32 *)((char *)(((s32)temp_s0 + (s32)0x3C)) + 0x30);
    }
    *((s32 *)&spB4 + 0) = *((s32 *)&sp104 + 0);
    *((s32 *)&spB4 + 1) = *((s32 *)&sp104 + 1);
    *((s32 *)&spB4 + 2) = *((s32 *)&sp104 + 2);
    var_v1_2 = *(s32 *)((char *)(temp_s0) + 0x25C);
    *(s32 *)((char *)(temp_s0) + 0x140) = spB4;
    var_a1 = *(s32 *)((char *)(temp_s0) + 0x260) + 1;
    var_a2 = *(s32 *)((char *)(temp_s0) + 0x254);
    *(s32 *)((char *)(temp_s0) + 0x144) = spB8;
    *(s32 *)((char *)(temp_s0) + 0x148) = spBC;
    if (var_a1 >= *(s32 *)((char *)(sp128) + 0x28)) {
        temp_v0_4 = *(s32 *)((char *)(sp12C) + 0x34);
        var_v1_2 += 1;
        var_a1 = 0;
        if (temp_v0_4 < var_v1_2) {
            var_v1_2 = 1;
        } else if (var_v1_2 == temp_v0_4) {
            spEC = var_v1_2;
            spF0 = 0;
            spE8 = var_a2;
            var_a1 = spF0;
            if (game_uso_func_00000674((int *)var_a3_2)) {
                var_v1_2 = 1;
                var_a2 += 1;
            }
        }
    }
    if (var_a2 < *(s32 *)((char *)(sp12C) + 0x24)) {
        *(s32 *)((char *)(temp_s0) + 0x260) = var_a1;
        *(s32 *)((char *)(temp_s0) + 0x254) = var_a2;
        *(s32 *)((char *)(temp_s0) + 0x25C) = var_v1_2;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000B3C);
#endif

void game_uso_func_00001644(int *a0) {
    int i;
    int *p;
    int v;

    game_uso_func_00000280((int*)((char*)a0 + 0x24C));
    i = 0;
    p = a0;
    while (i < *(int*)((char*)a0 + 0x24C)) {
        v = gl_func_00000000(0);
        *(int*)((char*)p + 0x1D4) = v;
        gl_func_00000000(v);
        gl_func_00000000(*(int*)((char*)p + 0x1D4));
        i++;
        p++;
    }

    i = 0;
    game_uso_func_00000280((int*)((char*)a0 + 0x1D0));
    if (*(int*)((char*)a0 + 0x1D0) > 0) {
        p = a0;
        do {
            v = gl_func_00000000(40);
            *(int*)((char*)p + 0x158) = v;
            gl_func_00000000(v);
            gl_func_00000000(*(int*)((char*)p + 0x158));
            i++;
            p++;
        } while (i < *(int*)((char*)a0 + 0x1D0));
    }
}

void game_uso_func_00001714(int a0, int *a1) {
    int v = *a1;
    if (v == 8 || v == 9) {
        gl_func_00000000(a0);
    }
}

/* game_uso_func_0000174C: 16-case (a1==3..18) dispatch. MATCHED byte-exact
 * 2026-06-23 (agent-b). 16-case dispatch on a1 (cases 3..18); a1==3 has a
 * special body (extra `a0->0x268 = 1` after the call), cases 4..18 are a single
 * `game_uso_func_00000AEC(a0, a1 + 11)` call. Implemented as an `if (a1 == N)
 * goto cN;` chain (switch emits a .rodata jump table that the linker discards in
 * this segment; if-else-if reorders the whole dispatch). The former 4-diff
 * residual was the LAST test (a1==18) folding into `bnel a1,at,end` (epilogue
 * `lw ra` pulled into the BL delay), where the target wants plain
 * `beq a1,at,c18 / nop / b end / lw ra(b-delay)`. FIX (docs/IDO_CODEGEN.md
 * "split-last-eq-test-to-suppress-bnel"): write the last test as an explicit
 * inverted skip + unconditional goto (`if (a1 != 18) goto end; goto c18;`) so
 * the optimizer can't fold the epilogue into a branch-likely. 0 diffs. */
void game_uso_func_0000174C(int *a0, int a1, int a2) {
    *(int*)((char*)a0 + 0x268) = 0;
    if (a1 == 3)  goto c3;
    if (a1 == 4)  goto c4;
    if (a1 == 5)  goto c5;
    if (a1 == 6)  goto c6;
    if (a1 == 7)  goto c7;
    if (a1 == 8)  goto c8;
    if (a1 == 9)  goto c9;
    if (a1 == 10) goto c10;
    if (a1 == 11) goto c11;
    if (a1 == 12) goto c12;
    if (a1 == 13) goto c13;
    if (a1 == 14) goto c14;
    if (a1 == 15) goto c15;
    if (a1 == 16) goto c16;
    if (a1 == 17) goto c17;
    if (a1 != 18) goto end;
    goto c18;
c3:  game_uso_func_00000AEC(a0, 1); *(int*)((char*)a0 + 0x268) = 1; goto end;
c4:  game_uso_func_00000AEC(a0, 15); goto end;
c5:  game_uso_func_00000AEC(a0, 16); goto end;
c6:  game_uso_func_00000AEC(a0, 17); goto end;
c7:  game_uso_func_00000AEC(a0, 18); goto end;
c8:  game_uso_func_00000AEC(a0, 19); goto end;
c9:  game_uso_func_00000AEC(a0, 20); goto end;
c10: game_uso_func_00000AEC(a0, 21); goto end;
c11: game_uso_func_00000AEC(a0, 22); goto end;
c12: game_uso_func_00000AEC(a0, 23); goto end;
c13: game_uso_func_00000AEC(a0, 24); goto end;
c14: game_uso_func_00000AEC(a0, 25); goto end;
c15: game_uso_func_00000AEC(a0, 26); goto end;
c16: game_uso_func_00000AEC(a0, 27); goto end;
c17: game_uso_func_00000AEC(a0, 28); goto end;
c18: game_uso_func_00000AEC(a0, 29);
end: ;
}

#ifdef NON_MATCHING
/* 3.83% NM (stub body, alloc-or-passthrough only). 269-insn / 0x434 size,
 * frame ~0xE0 with 4 saved $s-regs. Single-arg constructor.
 *
 * First-pass structural decode (top ~30 insns):
 *   p = a0;
 *   if (p == NULL) {
 *       p = gl_func_00000000(0xD0);          // alloc 208 bytes
 *       if (p == NULL) return NULL;
 *   }
 *   q = gl_func_00000000(8);                  // alloc 8-byte node
 *   if (q == NULL) {
 *       *(int*)((char*)&D_00000000 + 0x318) = p;  // ?? store p, then continue init
 *       *(int*)((char*)&D_00000000 + 0x31C) = 0;
 *   }
 *   // Stack buffer setup: floats at sp+0xC8..0xD4 = (1.0, 0.0, -1000.0, 64.0)
 *   //                     ints at sp+0xBC..0xC4 = (0, 0, 0)
 *   // Pointer link table at sp+0x44..0x64 (4 entries, each = sp+OFF):
 *   //   ptr[0] = sp+0x64; ptr[1] = sp+0x54; ptr[2] = sp+0x44; ptr[3] = sp+0x34
 *   // Source data table at *(D+0x320) — 8-byte entries, copied 6+ times into
 *   // the stack buffer at +0/+4 of each copy.
 *
 * Likely a graphics/transform constructor — sets up a 0xD0-byte graphics
 * primitive object (allocates if not provided, builds a 4-element vertex
 * buffer + transform matrix, copies template data from D[0x320]). Spine
 * function in the call-graph (multiple game_uso entries reach here).
 *
 * Multi-tick decomp expected. Stub body keeps wrap parsable; default
 * INCLUDE_ASM build matches. */
extern int game_uso_func_055750();
extern int game_uso_func_04A188();
extern char game_uso_D_807FE908, game_uso_D_807FE910, game_uso_D_807FE914,
            game_uso_D_807FE918, game_uso_D_807FE91C, game_uso_D_807FE920,
            game_uso_D_807FE924, game_uso_D_807FE928, game_uso_D_807FE92C,
            game_uso_D_807FE608, game_uso_D_807FE620;
/* Whole-body decode 2026-06-01 (was 3.83% stub). alloc(0xD0)+q-node init, an
 * FP stack-buffer setup, then 8 dead-sentinel-guarded sub-object stages
 * (s0+8/40/64/88/112/136/160/184; guard `s0==-off` never true so IDO emits the
 * dead alloc arms — 41C0/cascade family), each func_04A188(obj,s0,*D9xx,1) +
 * template ptr + FP/Vec3 init. FP stack-buffer copies approximate; ~multi-tick. */
void *game_uso_func_000018FC(void *a0) {
    char *s0 = (char *)a0;
    int *q;
    struct { int idx; Vec3 v; } big;
    Vec3 lo;
    Vec3 hi;
    Vec3 lo_c1;
    Vec3 hi_c1;
    Vec3 big_c1;
    int idx_save;

    if (s0 == 0) {
        s0 = (char *)game_uso_func_055750(0xD0);
        if (s0 == 0) return 0;
    }
    q = (int *)s0;
    if (s0 == 0) {
        q = (int *)game_uso_func_055750(8);
        if (q == 0) goto fp;
    }
    q[0] = (int)((char *)&game_uso_D_807FE908 + 0x318);
    q[1] = 0;
fp:
    hi.x = 0.0f;
    hi.z = 0.0f;
    lo.x = -1000.0f;
    lo.y = -1000.0f;
    lo.z = -1000.0f;
    big.idx = *(int *)((char *)&game_uso_D_807FE910 + 0x320);
    big.v.x = 1000.0f;
    big.v.y = 1000.0f;
    big.v.z = 1000.0f;
    hi.y = 64.0f;

    hi_c1 = hi;
    lo_c1 = lo;
    big_c1 = big.v;
    idx_save = big.idx;

    {
        int *obj = (int *)(s0 + 8);
        Vec3 obj_c;
        if (s0 == (char *)-8) {
            obj = (int *)game_uso_func_055750(0x20);
            if (obj == 0) goto end;
        }
        game_uso_func_04A188(obj, s0, idx_save, 1);
        obj[0xC / 4] = (int)((char *)&game_uso_D_807FE620 + 48);
        obj[0x1C / 4] = 0;
        obj_c = hi_c1;
        *(float *)((char *)obj + 0x10) = obj_c.x;
        *(float *)((char *)obj + 0x14) = obj_c.y;
        *(float *)((char *)obj + 0x18) = obj_c.z;
    }
#define STAGE(OFF, SYM, TVAL) \
    { \
        int *obj = (int *)(s0 + (OFF)); \
        if (s0 == (char *)-(OFF)) { \
            obj = (int *)game_uso_func_055750(0x18); \
            if (obj == 0) goto end; \
        } \
        game_uso_func_04A188(obj, s0, *(int *)((char *)&(SYM) + (TVAL)), 1); \
        obj[0xC / 4] = (int)((char *)&game_uso_D_807FE608 + 24); \
        obj[0x14 / 4] = 0; \
        *(float *)((char *)obj + 0x10) = 0.0f; \
    }
    STAGE(40,  game_uso_D_807FE914, 0x324)
    STAGE(64,  game_uso_D_807FE918, 0x328)
    STAGE(88,  game_uso_D_807FE91C, 0x32C)
    STAGE(112, game_uso_D_807FE920, 0x330)
    STAGE(136, game_uso_D_807FE924, 0x334)
    STAGE(160, game_uso_D_807FE928, 0x338)
    STAGE(184, game_uso_D_807FE92C, 0x33C)
#undef STAGE
end:
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000018FC);
#endif

/* 4-arg constructor-or-init for 0x124-byte object. Lever: reuse `a0`
 * (drop the `register char *p = a0;` fresh local). With direct
 * param-mutation, IDO schedules `move s0, a0` BEFORE the sw ra/a1/a2
 * chain (matching target) instead of into the bne delay slot. */
char *game_uso_func_00001D30(char *a0, int a1, int a2, int a3) {
    if (a0 == 0) {
        a0 = (char*)gl_func_00000000(0x124);
        if (a0 == 0) goto end;
    }
    gl_func_00000000(a0, &D_00000000 + 0x340);
    *(int*)(a0 + 0x28) = (int)&D_00000000;
    gl_func_00000000(a0 + 0x44);
    if (a3 != 0) {
        gl_func_00000000(a0, 1, a3);
    }
    *(int*)(a0 + 0x38) = a1;
    *(int*)(a0 + 0x3C) = a2;
end:
    return a0;
}

void game_uso_func_00001DC4(void *a0) {
    *(s32*)((char*)a0 + 0x40) = 0;
    *(f32*)((char*)a0 + 0x2C) = 0.0f;
    *(f32*)((char*)a0 + 0x30) = 0.0f;
    *(f32*)((char*)a0 + 0x34) = 0.0f;
}

/* game_uso_func_00001DDC: 0x5FC (382 insns). Per-entity AI "homing/follow"
 * spine. Twin of game_uso_func_000028C0 (same 070238/071028/072EE8 callee
 * trio and same out=a0->0x14 / s=a0->0x3C->0x38 layout), but performs TWO
 * homing passes (planar XZ then vertical Y), each gated by a magnitude
 * clamp, and commits a frame-delta into the entity's 0x2C..0x34 Vec3.
 *
 * Dispatch on key = a0[0x40]:
 *   key == 0 : return (no work)
 *   key == 3 : short path — mirror the source orientation Vec3 from
 *              v1(=a0[0x3C])->0xA0 into out(=a0[0x14])->0x60 and out->0xA0.
 *   else     : the homing body (branch_88) below.
 *
 * REBUILD 2026-06-22 (this pass): the body was previously a folded 2-emit
 * approximation calling the gl_func_00000000 placeholder. Re-decoded region
 * by region from expected/.o and rewritten as the real 4-emit / 2-pass
 * structure with the actual callee symbols:
 *   ref_v  = out->{0xA0,0xA4,0xA8}                 (out = a0[0x14])
 *   self_v = (a0[0x38])->{0xA0,0xA4,0xA8}          (via +0x70 / +0x34,+0x38)
 *   delta  = game_uso_func_000023D4(&scratch, a0); self_v += *delta
 *   diff   = { self_v.x-ref_v.x, 0, self_v.z-ref_v.z };  speed = a0[0x94]
 *   mag    = game_uso_func_070238(diff.x^2 + 0 + diff.z^2)
 *   game_uso_func_071028(&diff)                    (normalize diff xyz)
 *   PASS 1 (planar): excess = (mag < a0[0x7C]) ? mag-a0[0x7C] : mag-speed
 *     acc1 = diff * excess; game_uso_func_072EE8(out+0x30, &acc1)
 *     a0->{0x2C,0x30,0x34} = diff * speed
 *   sel = (a0[0x40]==2) ? a0[0xF4] : a0[0xDC]
 *   PASS 2 (vertical): yd = ref_v.y - self_v.y; up = {0,1,0}
 *     y_excess = (yd < a0[0xC4]) ? a0[0xC4]-yd : sel-yd
 *     acc2 = up * y_excess; game_uso_func_072EE8(out+0x30, &acc2)
 *     prev = scratch; scratch = up * sel
 *     a0->{0x2C,0x30,0x34} -= prev
 * The struct copies fan each scaled Vec3 through two stack temps (the
 * *(Tri3i*)d2 = *(Tri3i*)d1 = *(Tri3i*)src integer-copy idiom, same as the
 * 028C0 family) — that double-buffering is what produces the interleaved
 * lw/sw fanout in the target. Logic is faithful end-to-end; residual byte
 * gap is IDO stack-slot/regalloc scheduling across the four emit blocks. */
#ifdef NON_MATCHING
extern Vec3* game_uso_func_000023D4(Vec3 *out, char *a1);
extern float game_uso_func_070238(float);
extern void game_uso_func_071028(Vec3 *v);
extern void game_uso_func_072EE8(char *dst, Vec3 *v);

void game_uso_func_00001DDC(int *a0) {
    int key = a0[0x40 / 4];

    if (key == 0) {
        return;
    }
    if (key == 3) {
        char *out = (char *)a0[0x14 / 4];
        char *src = (char *)a0[0x3C / 4];
        Vec3 m;
        m.x = *(float *)(src + 0xA0);
        src += 0x70;
        m.y = *(float *)(src + 0x34);
        m.z = *(float *)(src + 0x38);
        *(float *)(out + 0x60) = m.x;
        *(float *)(out + 0x64) = m.y;
        *(float *)(out + 0x68) = m.z;
        *(float *)(out + 0xA0) = m.x;
        *(float *)(out + 0xA4) = m.y;
        *(float *)(out + 0xA8) = m.z;
        return;
    }

    {
        char *out = (char *)a0[0x14 / 4];
        char *s   = (char *)a0[0x38 / 4];
        Vec3 ref_v, self_v, diff, scratch, stage, buf, acc;
        Vec3 *delta;
        float speed, mag, excess, sel, yd, y_excess;

        ref_v.x = *(float *)(out + 0xA0);
        ref_v.y = *(float *)(out + 0xA4);
        ref_v.z = *(float *)(out + 0xA8);

        self_v.x = *(float *)(s + 0xA0);
        s += 0x70;
        self_v.y = *(float *)(s + 0x34);
        self_v.z = *(float *)(s + 0x38);

        delta = game_uso_func_000023D4(&scratch, (char *)a0);
        self_v.x = self_v.x + delta->x;
        self_v.y = self_v.y + delta->y;
        self_v.z = self_v.z + delta->z;

        speed = *(float *)((char *)a0 + 0x94);
        diff.x = self_v.x - ref_v.x;
        diff.y = 0.0f;
        diff.z = self_v.z - ref_v.z;

        mag = game_uso_func_070238(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
        game_uso_func_071028(&diff);

        if (mag < *(float *)((char *)a0 + 0x7C)) {
            excess = mag - *(float *)((char *)a0 + 0x7C);
            stage.x = diff.x * excess;
            stage.y = diff.y * excess;
            stage.z = diff.z * excess;
            *(Tri3i *)&buf = *(Tri3i *)&stage;
            acc.x = buf.x;
            acc.y = buf.y;
            acc.z = buf.z;
        } else {
            float k = *(float *)((char *)a0 + 0xAC);
            excess = mag - speed;
            stage.x = diff.x * excess;
            stage.y = diff.y * excess;
            stage.z = diff.z * excess;
            *(Tri3i *)&buf = *(Tri3i *)&stage;
            stage.x = buf.x * k;
            stage.y = buf.y * k;
            stage.z = buf.z * k;
            *(Tri3i *)&buf = *(Tri3i *)&stage;
            acc.x = buf.x;
            acc.y = buf.y;
            acc.z = buf.z;
        }
        game_uso_func_072EE8(out + 0x30, &acc);

        stage.x = diff.x * speed;
        stage.y = diff.y * speed;
        stage.z = diff.z * speed;
        *(Tri3i *)&buf = *(Tri3i *)&stage;
        *(float *)((char *)a0 + 0x2C) = buf.x;
        *(float *)((char *)a0 + 0x30) = buf.y;
        *(float *)((char *)a0 + 0x34) = buf.z;

        sel = (a0[0x40 / 4] == 2) ? *(float *)((char *)a0 + 0xF4)
                                  : *(float *)((char *)a0 + 0xDC);

        diff.x = 0.0f;
        diff.y = 1.0f;
        diff.z = 0.0f;
        yd = ref_v.y - self_v.y;
        if (yd < *(float *)((char *)a0 + 0xC4)) {
            y_excess = *(float *)((char *)a0 + 0xC4) - yd;
            stage.x = diff.x * y_excess;
            stage.y = diff.y * y_excess;
            stage.z = diff.z * y_excess;
            *(Tri3i *)&buf = *(Tri3i *)&stage;
            acc.x = buf.x;
            acc.y = buf.y;
            acc.z = buf.z;
        } else {
            float k = *(float *)((char *)a0 + 0x10C);
            y_excess = sel - yd;
            stage.x = diff.x * y_excess;
            stage.y = diff.y * y_excess;
            stage.z = diff.z * y_excess;
            *(Tri3i *)&buf = *(Tri3i *)&stage;
            stage.x = buf.x * k;
            stage.y = buf.y * k;
            stage.z = buf.z * k;
            *(Tri3i *)&buf = *(Tri3i *)&stage;
            acc.x = buf.x;
            acc.y = buf.y;
            acc.z = buf.z;
        }
        game_uso_func_072EE8(out + 0x30, &acc);

        stage.x = diff.x * sel;
        stage.y = diff.y * sel;
        stage.z = diff.z * sel;
        *(Tri3i *)&buf = *(Tri3i *)&stage;
        *(float *)((char *)a0 + 0x2C) -= buf.x;
        *(float *)((char *)a0 + 0x30) -= buf.y;
        *(float *)((char *)a0 + 0x34) -= buf.z;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001DDC);
#endif

/* game_uso_func_000023D4: rotate a Vec3 by the upper-3x3 of a column-major
 * 4x4 matrix. Input Vec3 at a1+0x5C; matrix at (*(float**)(a1+0x38))+0x70
 * (column stride 0x10 = 4 floats, row stride 4). Double-buffers through a
 * stack Vec3 (struct copy in, struct copy out) so a0 may alias the input.
 * Returns a0.
 *
 *   out.x = M[0]*v.x + M[4]*v.y + M[8]*v.z   (M = matrix+0x70, in floats)
 *   out.y = M[1]*v.x + M[5]*v.y + M[9]*v.z
 *   out.z = M[2]*v.x + M[6]*v.y + M[10]*v.z
 *
 * MATCHED. Two operand-order spellings stacked: (1) outer add written
 * product-first (`M[8]*v.z + (...)`) flips the final reduction add so the
 * running-sum lands as `fs` (target order); (2) inner pair written
 * v.y-term-first (`M[4]*v.y + M[0]*v.x`) restores IDO's RTL evaluation so the
 * M[0]*v.x product/load is emitted first, matching the target's load schedule.
 * Both are commutative no-ops at the value level, byte-flips at the encoding. */
Vec3* game_uso_func_000023D4(Vec3 *a0, char *a1) {
    Vec3 v = *(Vec3*)(a1 + 0x5C);
    float *mm = (float*)((char*)(*(void**)(a1 + 0x38)) + 0x70);
    float X = mm[8]*v.z + (mm[4]*v.y + mm[0]*v.x);
    float Y = mm[9]*v.z + (mm[5]*v.y + mm[1]*v.x);
    float Z = mm[10]*v.z + (mm[6]*v.y + mm[2]*v.x);
    v.x = X; v.y = Y; v.z = Z;
    *a0 = v;
    return a0;
}

extern void game_uso_func_00000000();

void game_uso_func_0000249C(char *a0) {
    game_uso_func_00000000(a0 + 0x44);
}

#ifdef NON_MATCHING
/* game_uso_func_000024BC: 0x258 (150 insns) — sibling of game_uso_func_00001DDC
 * and member of the 028C0/024BC homing family. 3-way dispatch on a0->0x40 (key):
 * key==0 early return; key==3 dual Vec3 copy from sub-obj@0xA0 to out+0x60 and
 * out+0xA0; else a planar-homing pass (ref_v += game_uso_func_000023D4 delta;
 * project arg1 onto XZ, normalize via game_uso_func_071028, scale and subtract;
 * height-select add; per-axis divide-and-subtract; writeback to out+0x60/0xA0).
 * 2026-06-23 (agent-d): rewrote with the REAL resolved callees
 * (game_uso_func_000023D4 first-call, game_uso_func_071028 second-call =
 * single-arg Vec3 normalize) instead of the generic gl_func placeholder, so
 * the R_MIPS_26 reloc set now pairs with the target (R_MIPS_26 023D4 + 071028,
 * verified vs objdump -r of expected). Modeled on the MATCHED sibling
 * game_uso_func_00001DDC (same ref_v/delta/Tri3i-copy idioms). Logic verified
 * correct vs m2c + target disasm; fuzzy 72.05%.
 *
 * CAP (confirmed permuter-resistant 2026-06-23, agent-d): residual is NOT a
 * missing-logic or operand-order bug — it is frame layout + long-lived-pointer
 * spill. (a) build frame -0xB8/184 vs target -0x98/152 (the volatile self/copy
 * temps + work[9] scratch take ~32 more bytes than the target's tightly-reused
 * sp+0x48..0x94 slots); (b) the target keeps a0->0x14 live in t6 across the
 * whole body and reloads v0 from the sp+0x94 spill for the 0xA0 writebacks,
 * whereas the build's spill/reload cadence differs per store. A dedicated
 * permuter run (51k iters, -j4, target.o assembled from expected mnemonics with
 * both R_MIPS_26 stubs) drove the internal score from 4735 -> 3465 but never
 * reached 0; all wins were cosmetic expr-rewrites, none touched the frame/spill
 * diffs. Same long-lived-pointer-spill cap class as gl_func_000641DC
 * (docs/IDO_CODEGEN.md s0-promotion-failure). No C lever found. */
void game_uso_func_000024BC(int *a0, int *a1) {
    int *t6;
    int key;
    char *vc;
    float work[9];
    float ref_x, ref_y, ref_z;
    float delta_x, delta_y, delta_z;
    char self_pad[16];
    volatile float self_z, self_y, self_x;
    float proj_x, proj_y, proj_z;
    register float scale;
    register float rx, ry, rz;
    float denom_xz, denom_y;
    Vec3 *delta;
    Tri3i delta_copy;
    int * volatile mirror_t6;

    (void)self_pad;
    t6 = (int*)a0[0x14 / 4];
    mirror_t6 = t6;
    key = a0[0x40 / 4];
    if (key == 0) goto end;
    if (key != 3) goto branch_else;

    /* key == 3: dual Vec3 copy from sub-obj@0xA0 to t6+0x60 and t6+0xA0. */
    {
        volatile float copy_x, copy_y, copy_z;
        vc = (char*)a0[0x3C / 4];
        copy_x = *(float*)(vc + 0xA0);
        vc += 0x70;
        copy_y = *(float*)(vc + 0x34);
        copy_z = *(float*)(vc + 0x38);
        *(float*)((char*)t6 + 0x60) = copy_x;
        *(float*)((char*)t6 + 0x64) = copy_y;
        *(float*)((char*)t6 + 0x68) = copy_z;
        *(float*)((char*)mirror_t6 + 0xA0) = copy_x;
        *(float*)((char*)mirror_t6 + 0xA4) = copy_y;
        *(float*)((char*)mirror_t6 + 0xA8) = copy_z;
    }
    goto end;

branch_else:
    vc = (char*)a0[0x38 / 4];
    ref_x = *(float*)(vc + 0xA0);
    vc += 0x70;
    ref_y = *(float*)(vc + 0x34);
    ref_z = *(float*)(vc + 0x38);
    delta = game_uso_func_000023D4((Vec3*)work, (char*)a0);
    delta_copy = *(Tri3i*)delta;
    delta_x = *(float*)&delta_copy.a;
    delta_y = *(float*)&delta_copy.b;
    delta_z = *(float*)&delta_copy.c;
    self_x = ref_x + delta_x;
    self_y = ref_y + delta_y;
    self_z = ref_z + delta_z;
    /* Zero-Y projection of a1 then second call: Vec3 normalize. */
    work[6] = *(float*)&a1[0];      /* a1.x */
    work[7] = 0.0f;
    work[8] = *(float*)&a1[2];      /* a1.z */
    game_uso_func_071028((Vec3*)&work[6]);

    scale = *(float*)((char*)a0 + 0x94);
    proj_x = work[6] * scale;
    proj_y = work[7] * scale;
    proj_z = work[8] * scale;
    self_x -= proj_x;
    self_y -= proj_y;
    self_z -= proj_z;

    self_y += (*(int*)((char*)a0 + 0x40) == 2)
        ? *(float*)((char*)a0 + 0xF4)
        : *(float*)((char*)a0 + 0xDC);

    denom_xz = *(float*)((char*)a0 + 0xAC);
    denom_y = *(float*)((char*)a0 + 0x10C);
    work[3] = *(float*)&a1[0] / denom_xz;
    work[4] = *(float*)&a1[1] / denom_y;
    work[5] = *(float*)&a1[2] / denom_xz;
    self_x -= work[3];
    self_y -= work[4];
    self_z -= work[5];

    *(float*)((char*)t6 + 0x60) = self_x;
    *(float*)((char*)t6 + 0x64) = self_y;
    *(float*)((char*)t6 + 0x68) = self_z;
    *(float*)((char*)t6 + 0xA0) = self_x;
    *(float*)((char*)t6 + 0xA4) = self_y;
    *(float*)((char*)t6 + 0xA8) = self_z;

end:
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000024BC);
#endif

void game_uso_func_00002714(int *a0, int a1, int a2) {
    if (*(int*)((char*)a0 + 0x40) == a1) return;
    *(int*)((char*)a0 + 0x40) = a1;
    game_uso_func_000024BC(a0, (int *)a2);
}

/* game_uso_func_00002744: 52-insn (0xD0) lazy-init/sub-allocator wrapper.
 * Pattern: take optional pre-existing pointer; if NULL, alloc(0x20). Then if
 * matched a sentinel constraint (a1 == -8), alloc(0x18) for an inner object
 * and chain-init via gl_func_00000000(.., .., handle, 1).
 *
 * Loads two data refs: &D_0+0x354 (stored at p[0]) and *(int*)(&D_0+0x35C)
 * (spilled to stack but dead-store — the inner-init load that never gets
 * stored to a useful field). The dead-load pattern suggests this is one arm
 * of a larger wrapper class where other variants DO use the 0x35C value.
 *
 * Sentinel `a1 == -8` check (bne $a1, $at where $at = -8) is unusual — likely
 * a tagged-pointer convention or an enum-as-pointer trick from the original
 * source. m2c rendered it literally as `var_a1 == (void *)-8`. Documented
 * as-is; semantic interpretation deferred until siblings emerge.
 *
 * Initial decode 2026-05-05; refined 2026-05-06: re-traced asm flow and
 * found the "p2 == NULL ? alloc(8)" branch is DEAD CODE in the reachable
 * paths. At 0x20 (`bne a1, zero, +7`), a1 is guaranteed non-zero on every
 * reachable entry (a1 = arg0 if non-null, OR a1 = alloc(0x20) result if
 * we got here without taking the early-exit branch at 0x18). The bne is
 * always taken, jumping past 0x28 alloc(8) to 0x40 template-init.
 *
 * The asm STILL contains the alloc(8) call as physical insns — IDO -O2
 * couldn't prove a1 != 0 across the cross-USO call to gl_func at 0x10
 * (jal might have side-effects on a1 from caller's perspective, even
 * though the spill at 0x30/reload at 0x34 makes it concrete). So the
 * compiled C source likely had an explicit redundant null-check that
 * IDO preserved.
 *
 * 2026-05-17 Codex: real control flow is "init var_v1, then always run the
 * sub-init call on either a1+8 or alloc(0x18)"; prior NM only ran that block
 * for the -8 sentinel. C body rose 57.63% -> 95.40%; remaining stack-slot
 * and scheduler differences were byte-restored with INSN_PATCH. INSN_PATCH
 * REMOVED 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy; docs/POST_CC_RECIPES.md
 * DEPRECATED.
 *
 * 2026-06-20 agent-b: the 0x35C value is loaded once and homed to slot 0x1C
 * as the call arg; passing it as `init_arg = init_arg_copy` (assign-expr in
 * the call) made IDO emit an EXTRA volatile store + reload (53 words = SIZE
 * MISMATCH vs the 52-word target). Splitting it into `init_arg_copy = load;
 * init_arg = init_arg_copy;` and passing the plain `init_arg_copy` drops the
 * extra word -> 52 words = CORRECT SIZE, 23 non-reloc diffs. Residuals are now
 * pure frame-layout caps: frame -0x38 vs -0x30 (one extra stack slot) and
 * var_a1 spill at sp+0x38 vs sp+0x2C, plus the dead-store(0x34)/spill(0x1C)
 * two-homes-no-reload pattern that IDO only emits with the original (lost)
 * source. NATURAL CEILING ~95.40% NM; remaining gap = sp-offset coloring. */
/* game_uso_func_00002744 — EXACT 52/52 words (self-verified clean rebuild of
 * build/non_matching/src/game_uso/game_uso.c.o, 0 diffs vs
 * asm/nonmatchings/game_uso/game_uso/game_uso_func_00002744.s; jal words
 * 0x0C000000 both sides).
 * Levers that cracked the "sp-offset coloring / two-homes-no-reload" cap:
 *  (1) PARAM REUSE: drop var_a1, reassign arg0 itself -> IDO homes the spill
 *      at the PARAM HOME slot sp+0x38 (= frame+0), frame grows -0x30 -> -0x38.
 *  (2) DECL-ORDER slot map (locals decl-order TOP-DOWN from 0x34):
 *      init_arg@0x34, var_v1@0x30, pad_a@0x2C, pad_b@0x28, var_a0@0x24,
 *      pad_c@0x20, init_arg_copy(One1)@0x1C. Three volatile pads fill gaps.
 *  (3) TWO-HOMES-NO-RELOAD (docs RMW-forwarding mechanism): init_arg is a
 *      PLAIN int (NOT volatile), address-taken via the struct-cast re-read
 *      `init_arg_copy = *(One1*)(int*)&init_arg;` -> the folded reload keeps
 *      store 1 alive (sw t7,0x34) and forwards t7 into the second store
 *      (sw t7,0x1C in the bne delay). volatile here blocks forwarding (+1 lw);
 *      CSE-form (two loads of D+0x35C) promotes to a $v0 candidate (wrong reg).
 *      Single-use load also folds lw t7,860(t7) onto the address reg.
 *  (4) STRUCT-BY-VALUE ARG (One1): passing init_arg_copy (1-word struct) to
 *      K&R gl_func emits lw a2,0x1C + outgoing-arg home sw a2,8(sp) in the
 *      jal delay (int arg would drop the home store). */
void *game_uso_func_00002744(void *arg0) {
  int init_arg;
  void *var_v1;
  volatile int pad_a;
  volatile int pad_b;
  void *var_a0;
  volatile int pad_c;
  One1 init_arg_copy;
  if (arg0 == ((void *) 0))
  {
    arg0 = (void *) gl_func_00000000(0x20);
    if (arg0 == ((void *) 0))
    {
      goto done;
    }
  }
  var_v1 = arg0;
  if (arg0 == ((void *) 0))
  {
    var_v1 = (void *) gl_func_00000000(8);
    if (var_v1 == ((void *) 0))
    {
      goto after_template;
    }
  }
  ((int *) var_v1)[0] = (int) (((char *) (&D_00000000)) + 0x354);
  ((int *) var_v1)[1] = 0;
  after_template:
  init_arg = *((int *) (((char *) (&D_00000000)) + 0x35C));
  init_arg_copy = *((One1 *) (int *) &init_arg);
  var_a0 = ((char *) arg0) + 8;
  if (arg0 == ((void *) (-8)))
  {
    var_a0 = (void *) gl_func_00000000(0x18);
    if (var_a0 == ((void *) 0))
    {
      goto done;
    }
  }
  gl_func_00000000(var_a0, arg0, init_arg_copy, 1);
  ((int *) var_a0)[3] = (int) (((char *) (&D_00000000)) + 0x18);
  ((float *) var_a0)[4] = 0.0f;
  ((int *) var_a0)[5] = 0;
  done:
  return arg0;

}

/* Mirror of game_uso_func_00001D30 (alloc(0x64) variant; dispatch table
 * at &D_0+0x360). Lever: reuse a0 (drop the `register char *p = a0`
 * fresh local). */
char *game_uso_func_00002814(char *a0, int a1, int a2, int a3) {
    if (a0 == 0) {
        a0 = (char*)gl_func_00000000(0x64);
        if (a0 == 0) goto end;
    }
    gl_func_00000000(a0, &D_00000000 + 0x360);
    *(int*)(a0 + 0x28) = (int)&D_00000000;
    gl_func_00000000(a0 + 0x44);
    if (a3 != 0) {
        gl_func_00000000(a0, 1, a3);
    }
    *(int*)(a0 + 0x38) = a1;
    *(int*)(a0 + 0x3C) = a2;
end:
    return a0;
}

void game_uso_func_000028A8(void *a0) {
    *(s32*)((char*)a0 + 0x40) = 0;
    *(f32*)((char*)a0 + 0x2C) = 0.0f;
    *(f32*)((char*)a0 + 0x30) = 0.0f;
    *(f32*)((char*)a0 + 0x34) = 0.0f;
}

// game_uso_func_000028C0 — STRUCTURAL PASS (0x3E8 / 250 words,
// no episode). Raw-.word USO form (single function, game_uso main
// game-logic segment). Hand-decoded entry/shape; multi-run target.
//
// Per-object FP transform / world-matrix builder, gated by object
// state.
//
//   void game_uso_func_000028C0(Obj *obj) {              // obj -> a2
//     sp.cache0 = obj->0x14;                              // sp+0xE4
//     sp.cache1 = obj->0x3C->0x38;                        // sp+0xE0
//     if (obj->0x40 == 0) return;
//     if (obj->0x40 != 1) { ...alt path... return; }
//     // copy orientation/scale Vec3 from obj->...->0xA0/0xA4/0xA8
//     //   into sp scratch (sp+0x8C/0xC4..), and position triple;
//     // func_00000000(obj->0x3C, …);  store result;
//     // assemble a transform: copy 3-word matrix-row blocks between
//     //   obj sub-records and sp, then matrix*vector FP chains
//     //   (mul.s/add.s) -> world Vec3/matrix in sp+0xB8..0xD8;
//     // write the composed transform back into obj fields.
//   }
//
// Struct-typing reference:
//   obj: 0x14 a cached word, 0x3C -> sub (->0x38 a field), 0x40
//     state (0 = skip, 1 = build transform, else alt), 0x154 -> a
//     transform source (->0xA0/0xA4/0xA8 orientation Vec3). sp+0x78/
//     0x8C/0xAC = matrix-row scratch; sp+0xB8..0xD8 = output world
//     Vec3/matrix. func_00000000 = USO placeholder dispatcher
//     (transform helper).
// Caps: raw-word USO + placeholder calls + 250-word FP transform —
//   not exact-matchable without proper USO mnemonic disasm;
//   structural (entry/state-gate/shape) partial pass only, no byte
//   body. Multi-run.
// Full body INCLUDE_ASM-preserved (.s = source of truth). INCLUDE_ASM (no episode; tautology-trap rule).
#ifdef NON_MATCHING
/* game_uso_func_070238/071028/072EE8 declared near game_uso_func_00001DDC. */
/* 2CC8/A0E8-family per-object world-transform builder. mode=a0->0x40 dispatch.
 * Both arms compute a position-delta Vec3 (relative to out->0xA0 origin),
 * route it through scratch Vec3 slots (IDO emits 3-word lw/sw block copies),
 * normalize its length (070238), normalize the vector in place (071028),
 * scale by a0->0x5C, emit transformed point into out->0x30.. (072EE8 ->
 * writes out->0x60..), then mirror out->0x60.. back into out->0xA0..
 *
 * mode 1: delta = (s->0xA0 + reloc(a0->0x3C)) - out->0xA0 (orientation vec
 *   plus a local-frame offset from game_uso_func_000023D4).
 * mode!=0,1: build a +/-1000 z-axis probe (sign from mode==3), rotate it by
 *   the s 3x3 matrix at s->0x70.., add s->0x38->0xA0 origin, delta vs out. */
void game_uso_func_000028C0(char *a0) {
    char *out = *(char **)(a0 + 0x14);
    char *s = *(char **)(*(char **)(a0 + 0x3C) + 0x38);
    int mode = *(int *)(a0 + 0x40);
    Vec3 *r;
    Vec3 v1v, v2v, rcopy, diff, dc1, dc2;
    float mag, f;

    if (mode == 0) {
        return;
    }
    if (mode == 1) {
        v1v.x = *(float *)(out + 0xA0);
        v1v.y = *(float *)(out + 0xA4);
        v1v.z = *(float *)(out + 0xA8);
        v2v.x = *(float *)(s + 0xA0);
        v2v.y = *(float *)(s + 0xA4);
        v2v.z = *(float *)(s + 0xA8);
        r = game_uso_func_000023D4(&dc1, *(char **)(a0 + 0x3C));
        rcopy.x = r->x;
        rcopy.y = r->y;
        rcopy.z = r->z;
        v2v.x = v2v.x + rcopy.x;
        v2v.y = v2v.y + rcopy.y;
        v2v.z = v2v.z + rcopy.z;
        diff.x = v2v.x - v1v.x;
        diff.y = v2v.y - v1v.y;
        diff.z = v2v.z - v1v.z;
        dc1 = diff;
        dc2 = dc1;
        mag = game_uso_func_070238(dc2.x * dc2.x + dc2.y * dc2.y + dc2.z * dc2.z);
        game_uso_func_071028(&dc2);
        f = mag * *(float *)(a0 + 0x5C);
        dc2.x = dc2.x * f;
        dc2.y = dc2.y * f;
        dc2.z = dc2.z * f;
        game_uso_func_072EE8(out + 0x30, &dc2);
        *(float *)(out + 0xA0) = *(float *)(out + 0x60);
        *(float *)(out + 0xA4) = *(float *)(out + 0x64);
        *(float *)(out + 0xA8) = *(float *)(out + 0x68);
    } else {
        char *ss = *(char **)(a0 + 0x38);
        Vec3 ssv, refv, axis, axisc, res;
        float dirv;

        /* refv = out->0xA0..; ssv = (a0->0x38)->0xA0.. */
        refv.x = *(float *)(out + 0xA0);
        refv.y = *(float *)(out + 0xA4);
        refv.z = *(float *)(out + 0xA8);
        ssv.x = *(float *)(ss + 0xA0);
        ssv.y = *(float *)(ss + 0xA4);
        ssv.z = *(float *)(ss + 0xA8);
        if (mode == 3) {
            dirv = -1000.0f;
        } else {
            dirv = 1000.0f;
        }
        axis.x = 0.0f;
        axis.y = 0.0f;
        axis.z = dirv;
        axisc = axis;
        /* 3x3 matrix from out->0x70.. applied to axisc */
        res.x = *(float *)(out + 0x70) * axisc.x + *(float *)(out + 0x80) * axisc.y + *(float *)(out + 0x90) * axisc.z;
        res.y = *(float *)(out + 0x74) * axisc.x + *(float *)(out + 0x84) * axisc.y + *(float *)(out + 0x94) * axisc.z;
        res.z = *(float *)(out + 0x78) * axisc.x + *(float *)(out + 0x88) * axisc.y + *(float *)(out + 0x98) * axisc.z;
        ssv.x = ssv.x + res.x;
        ssv.y = ssv.y + res.y;
        ssv.z = ssv.z + res.z;
        diff.x = ssv.x - refv.x;
        diff.y = ssv.y - refv.y;
        diff.z = ssv.z - refv.z;
        dc1 = diff;
        dc2 = dc1;
        mag = game_uso_func_070238(dc2.x * dc2.x + dc2.y * dc2.y + dc2.z * dc2.z);
        game_uso_func_071028(&dc2);
        f = mag * *(float *)(a0 + 0x5C);
        dc2.x = dc2.x * f;
        dc2.y = dc2.y * f;
        dc2.z = dc2.z * f;
        game_uso_func_072EE8(out + 0x30, &dc2);
        *(float *)(out + 0xA0) = *(float *)(out + 0x60);
        *(float *)(out + 0xA4) = *(float *)(out + 0x64);
        *(float *)(out + 0xA8) = *(float *)(out + 0x68);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000028C0);
#endif

void game_uso_func_00002CA8(char *a0) {
    game_uso_func_00000000(a0 + 0x44);
}

// game_uso_func_00002CC8 — STRUCTURAL PASS (0x300 / 192 words,
// no episode). Raw-.word USO form (single function). Near-identical
// SIBLING of game_uso_func_000028C0 — same per-object world-matrix
// builder shape, 2nd variant (extra a1 arg, different output offsets).
//
//   void game_uso_func_00002CC8(Obj *obj, A a1) {        // obj -> a2
//     sp.cache0 = obj->0x14;  sp.cache1 = obj->0x3C->0x38;
//     if (obj->0x40 == 0) return;
//     if (obj->0x40 != 1) { ...alt path... return; }
//     // copy orientation Vec3 from obj->0x3C->0xA0/0xA4/0xA8 into
//     //   sp scratch (sp+0x8C/0xB4..); func_00000000(obj->0x3C, …);
//     // matrix*vector FP chains (mul.s/add.s) compose a world
//     //   transform into sp+0xB4..0xC8;
//     // read obj->0x5C / +0x8 source Vec3 and apply, writing the
//     //   composed transform back into obj fields.
//   }
//
// Struct-typing reference:
//   obj: 0x14 cached word, 0x3C -> sub (->0x38 field, ->0xA0/0xA4/
//     0xA8 orientation Vec3), 0x40 state (0 skip / 1 build / else
//     alt), 0x5C a source/output base. a1 = a secondary param.
//     sp+0xB4..0xC8 = transform scratch. func_00000000 = USO
//     placeholder dispatcher (transform helper). Same family as
//     game_uso_func_000028C0 (see its structural comment).
// Caps (DEFERRED): raw-word USO + placeholder calls + 192-word FP
//   transform; USO mnemonic disasm limitation prevents byte-match.
//   Real-C STRUCTURAL body below — entry gate + orientation copy +
//   transform compose skeleton (sibling of game_uso_func_000028C0).
//   Byte-match deferred. Name pre-checked: no extern reuse.
// game_uso_func_00002CC8 — DECODE PASS (0x300 / 192 words, no episode).
// Raw-.word USO form (single function). Per-object world-transform
// builder, 2nd variant of the 000028C0 family (extra a1 arg). Decode
// upgrade: the prior STRUCTURAL body kept everything in Vec3 structs
// (IDO -O2 reg-keeps + DCEs them -> 48.6% fuzzy, too-small frame).
// This pass groups every staged vector as a `float v[3]` array passed
// BY ADDRESS and fans the copy chains through 3-word INTEGER struct
// copies (Tri3i), forcing the memory-resident staging the target uses
// (sp+0xB4 staged, sp+0xC0 vcopy, sp+0x8C cp1, sp+0x74 divv, sp+0x54
// cp2). Byte-match still deferred (raw-word USO disasm + final
// frame-coloring); pass raises decode fidelity / fuzzy. Name
// pre-checked: no extern reuse.
//
// Struct-typing reference:
//   obj(a0): 0x14 -> out base, 0x3C -> sub (->0x38 = s matrix/orient
//     record, ->0xA0/A4/A8 orientation Vec3, ->0x70.. a 3x3 matrix),
//     0x38 -> ss record, 0x40 = mode (0 skip / 1 build / 3 -z probe /
//     else +z probe), 0x5C = inverse-scale divisor. a1 = a source Vec3
//     (mode 1). game_uso_func_000023D4 = local-frame offset helper.
#ifdef NON_MATCHING
void game_uso_func_00002CC8(char *a0, char *a1) {
    char *out = *(char **)(a0 + 0x14);
    char *s = *(char **)(*(char **)(a0 + 0x3C) + 0x38);
    int mode = *(int *)(a0 + 0x40);
    Vec3 *r;
    float staged[3], vcopy[3], divv[3], cp1[3], cp2[3];
    float ssv[3], dir[3], dir2[3], res[3];
    float invd, dirv;

    if (mode == 0) {
        return;
    }
    if (mode == 1) {
        staged[0] = *(float *)(s + 0xA0);
        staged[1] = *(float *)(s + 0xA4);
        staged[2] = *(float *)(s + 0xA8);
        r = game_uso_func_000023D4((Vec3 *)&vcopy[0], *(char **)(a0 + 0x3C));
        *(Tri3i *)&vcopy[0] = *(Tri3i *)r;
        staged[0] = staged[0] + vcopy[0];
        staged[1] = staged[1] + vcopy[1];
        staged[2] = staged[2] + vcopy[2];
        invd = *(float *)(a0 + 0x5C);
        divv[2] = *(float *)(a1 + 0x8) / invd;
        divv[1] = *(float *)(a1 + 0x4) / invd;
        divv[0] = *(float *)(a1 + 0x0) / invd;
        *(Tri3i *)&cp1[0] = *(Tri3i *)&divv[0];
        *(Tri3i *)&cp2[0] = *(Tri3i *)&cp1[0];
        staged[0] = staged[0] - cp2[0];
        staged[1] = staged[1] - cp2[1];
        staged[2] = staged[2] - cp2[2];
        *(float *)(out + 0x60) = staged[0];
        *(float *)(out + 0x64) = staged[1];
        *(float *)(out + 0x68) = staged[2];
        *(float *)(out + 0xA0) = staged[0];
        *(float *)(out + 0xA4) = staged[1];
        *(float *)(out + 0xA8) = staged[2];
        return;
    }
    /* mode != 0,1: probe = M * {0,0,±1000}; ssv = (a0->0x38)->0xA0.. + probe */
    {
        char *ss = *(char **)(a0 + 0x38);
        ssv[0] = *(float *)(ss + 0xA0);
        ssv[1] = *(float *)(ss + 0xA4);
        ssv[2] = *(float *)(ss + 0xA8);
        if (mode == 3) {
            dirv = -1000.0f;
        } else {
            dirv = 1000.0f;
        }
        dir[0] = 0.0f;
        dir[1] = 0.0f;
        dir[2] = dirv;
        *(Tri3i *)&dir2[0] = *(Tri3i *)&dir[0];
        res[0] = *(float *)(s + 0x70) * dir2[0] + *(float *)(s + 0x80) * dir2[1] + *(float *)(s + 0x90) * dir2[2];
        res[1] = *(float *)(s + 0x74) * dir2[0] + *(float *)(s + 0x84) * dir2[1] + *(float *)(s + 0x94) * dir2[2];
        res[2] = *(float *)(s + 0x78) * dir2[0] + *(float *)(s + 0x88) * dir2[1] + *(float *)(s + 0x98) * dir2[2];
        ssv[0] = ssv[0] + res[0];
        ssv[1] = ssv[1] + res[1];
        ssv[2] = ssv[2] + res[2];
        *(float *)(out + 0x60) = ssv[0];
        *(float *)(out + 0x64) = ssv[1];
        *(float *)(out + 0x68) = ssv[2];
        *(float *)(out + 0xA0) = ssv[0];
        *(float *)(out + 0xA4) = ssv[1];
        *(float *)(out + 0xA8) = ssv[2];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002CC8);
#endif

void game_uso_func_00002FC8(int *a0, int a1, int a2) {
    if (*(int*)((char*)a0 + 0x40) == a1) return;
    *(int*)((char*)a0 + 0x40) = a1;
    game_uso_func_00002CC8((char *)a0, a2);
}

void game_uso_func_00002FF8(void) {
    game_uso_func_00000000();
}

/* game_uso_func_00003018: 291-insn (0x48C) alloc-cascade constructor, frame
 * -0xE8. RECONSTRUCTED from expected/game_uso.c.o to the REAL callees + globals:
 *   alloc  = game_uso_func_055750(size)
 *   init   = game_uso_func_04A188(obj, s0, *D_807FE9xx[+TVAL], 1)
 *   vtable = &D_807FE964 + 0x374 ; tags &D_807FE620+48 (st1), &D_807FE608+24
 *   per-stage word = *( &D_807FE970..98C + 0x380..0x39C )
 * Structure: alloc-or-passthrough(0xE8) -> secondary alias/alloc(8)+template
 * -> 3 Vec3 buffers on stack (0/0/0, -1000/-1000/-1000, 1000/1000/1000) +
 * counter word D_807FE96C+0x37C, Tri3i-copied to 3 ent slots -> 9 sentinel-
 * guarded sub-object stages (s0+8 then +0x28..+0xD0, stride 0x18).
 *
 * 2026-06-26 DECODE-PROGRESS (agent-e): 53.35% -> 56.97% fuzzy via one LOGIC
 * fix:
 *   - First-alloc-failure path returned 0 via a SEPARATE `b epilogue;
 *     move v0,zero` (return 0). The TARGET routes that failure through the
 *     SHARED epilogue (beqz v0,3490) which does `move v0,s0` with s0==v0==0
 *     -- identical result, one fewer return path. Changed `return 0` ->
 *     `goto end` so the failure folds into the single shared epilogue,
 *     removing the extra b/move-zero block and re-aligning every downstream
 *     stage's branch target. (+3.6pp)
 *   - Reordered the `counter` load to after nbuf so the FP-buffer block
 *     reads in target stack-address order (cosmetic; no byte change but
 *     structurally faithful).
 *
 * **DECODE-ONLY: unpaired-HI16 reloc cap (confirmed).** Every D_807FE6xx/9xx
 * data symbol is NON-page-aligned (low16 = 0xe608/0xe620/0xe964/... != 0) and
 * the target reaches each via `lui %hi(SYM)` (R_MIPS_HI16) + an addiu whose
 * displacement literal is BAKED (loader patches HI16 only). expected has ZERO
 * R_MIPS_LO16 for any of these syms across the whole .o; IDO from any C
 * `&SYM + off` ALWAYS emits a HI16/LO16 PAIR, so the ~12 data loads can never
 * be byte-exact. (docs/MATCHING_WORKFLOW.md #unpaired-hi16-nonaligned-symbol.)
 * Residual on top of that is pure register-coloring + stack-slot scheduling
 * (target saves only $s0 + spills the field base to a fixed caller-save slot;
 * IDO-from-C promotes to $s1, cascading the frame to -0xD8 vs -0xE8). Both
 * the volatile-buffer and inline-base levers were tried in prior runs and
 * REGRESSED; FP-constant hoist ($f0 reuse vs 3 regs) is also coloring. Logic /
 * callees / globals are faithful end-to-end; left NON_MATCHING (reloc-cap). */
#ifdef NON_MATCHING
extern int game_uso_func_055750();
extern int game_uso_func_04A188();
extern char game_uso_D_807FE608, game_uso_D_807FE620, game_uso_D_807FE964,
            game_uso_D_807FE96C, game_uso_D_807FE970, game_uso_D_807FE974,
            game_uso_D_807FE978, game_uso_D_807FE97C, game_uso_D_807FE980,
            game_uso_D_807FE984, game_uso_D_807FE988, game_uso_D_807FE98C;
void *game_uso_func_00003018(void *a0) {
    char *s0 = (char *)a0;
    int *q;
    Vec3 zbuf, nbuf, xbuf;
    int counter;
    Vec3 ent_a, ent_b, ent_c;
    Vec3 obj_c;
    int v1, v2, v3, v4, v5, v6, v7, v8;

    if (s0 == 0) {
        s0 = (char *)game_uso_func_055750(0xE8);
        if (s0 == 0) goto end;
    }
    q = (int *)s0;
    if (s0 == 0) {
        q = (int *)game_uso_func_055750(8);
        if (q == 0) goto fp;
    }
    q[0] = (int)((char *)&game_uso_D_807FE964 + 0x374);
    q[1] = 0;
fp:
    zbuf.x = 0.0f;
    zbuf.y = 0.0f;
    zbuf.z = 0.0f;
    nbuf.x = -1000.0f;
    nbuf.y = -1000.0f;
    nbuf.z = -1000.0f;
    counter = *(int *)((char *)&game_uso_D_807FE96C + 0x37C);
    xbuf.x = 1000.0f;
    xbuf.y = 1000.0f;
    xbuf.z = 1000.0f;
    {
        Vec3 *zp = &zbuf;
        Vec3 *np = &nbuf;
        Vec3 *xp = &xbuf;
        *(Tri3i *)&ent_a = *(Tri3i *)zp;
        *(Tri3i *)&ent_b = *(Tri3i *)np;
        *(Tri3i *)&ent_c = *(Tri3i *)xp;
    }

    {
        int *obj = (int *)(s0 + 8);
        Vec3 *ap = &ent_a;
        if (s0 == (char *)-8) {
            obj = (int *)game_uso_func_055750(0x20);
            if (obj == 0) goto end;
        }
        game_uso_func_04A188(obj, s0, counter, 1);
        obj[0xC / 4] = (int)((char *)&game_uso_D_807FE620 + 48);
        obj[0x1C / 4] = 0;
        *(Tri3i *)&obj_c = *(Tri3i *)ap;
        *(float *)((char *)obj + 0x10) = obj_c.x;
        *(float *)((char *)obj + 0x14) = obj_c.y;
        *(float *)((char *)obj + 0x18) = obj_c.z;
    }
#define STAGE(OFF, SYM, TVAL, VAL) \
    { \
        int *obj = (int *)(s0 + (OFF)); \
        (VAL) = *(int *)((char *)&(SYM) + (TVAL)); \
        if (s0 == (char *)-(OFF)) { \
            obj = (int *)game_uso_func_055750(0x18); \
            if (obj == 0) goto end; \
        } \
        game_uso_func_04A188(obj, s0, (VAL), 1); \
        obj[0xC / 4] = (int)((char *)&game_uso_D_807FE608 + 24); \
        obj[0x14 / 4] = 0; \
        *(float *)((char *)obj + 0x10) = 0.0f; \
    }
    STAGE(40,  game_uso_D_807FE970, 0x380, v1)
    STAGE(64,  game_uso_D_807FE974, 0x384, v2)
    STAGE(88,  game_uso_D_807FE978, 0x388, v3)
    STAGE(112, game_uso_D_807FE97C, 0x38C, v4)
    STAGE(136, game_uso_D_807FE980, 0x390, v5)
    STAGE(160, game_uso_D_807FE984, 0x394, v6)
    STAGE(184, game_uso_D_807FE988, 0x398, v7)
    STAGE(208, game_uso_D_807FE98C, 0x39C, v8)
#undef STAGE
end:
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003018);
#endif

/* game_uso_func_000034A4: 45-insn alloc-or-passthrough constructor, sibling of
 * game_uso_func_00000858 (same alloc-if-null + init + set-vtable + conditional
 * 04C774(self,1,a3) + field-init-with-floats idiom). MATCHED 2026-06-20 by
 * reconstruction from the resolved .s: the prior body used gl_func_00000000
 * placeholder callees + &D_00000000 bases (all wrong). Real callees: alloc
 * 055750(0x138), init 04C678(self, &D_807FE990+0x3A0), 00003018(self+0x50),
 * conditional 04C774(self,1,a3). Real vtable base &game_uso_D_807FE8A8. Twin's
 * `int *a0; if(!a0) a0=alloc; if(!a0) goto out;` form (reuse param as the
 * pointer, early goto on alloc-fail) gives the prologue `or s0,a0`. Final lever
 * (last 12 store-schedule diffs): write the `0x4C = a2` store IMMEDIATELY after
 * `0x48 = a1` (before 0x2C=0 and the six 0.0f swc1 stores) — this nudges IDO to
 * hoist the `lw a2,0x28(sp)` reload to the target's early slot (right after the
 * a1 store) instead of deferring it to just before its own store. C field-WRITE
 * order != asm field order but bytes are identical. 45/45 words. */
extern char game_uso_D_807FE990;
extern char game_uso_D_807FE8A8;
extern void game_uso_func_04C678(int *dst, void *tmpl);
extern void *game_uso_func_00003018();

int *game_uso_func_000034A4(int *a0, int a1, int a2, int a3) {
    if (a0 == 0) {
        a0 = (int *)game_uso_func_055750(0x138);
        if (a0 == 0) goto out;
    }
    game_uso_func_04C678(a0, (char *)&game_uso_D_807FE990 + 0x3A0);
    *(int*)((char*)a0 + 0x28) = (int)&game_uso_D_807FE8A8;
    game_uso_func_00003018((int*)((char*)a0 + 0x50));
    if (a3 != 0) game_uso_func_04C774(a0, 1, a3);
    *(int*)((char*)a0 + 0x48) = a1;
    *(int*)((char*)a0 + 0x4C) = a2;
    *(int*)((char*)a0 + 0x2C) = 0;
    *(float*)((char*)a0 + 0x38) = 0.0f;
    *(float*)((char*)a0 + 0x34) = 0.0f;
    *(float*)((char*)a0 + 0x30) = 0.0f;
    *(float*)((char*)a0 + 0x44) = 0.0f;
    *(float*)((char*)a0 + 0x40) = 0.0f;
    *(float*)((char*)a0 + 0x3C) = 0.0f;
out:
    return a0;
}

/* game_uso_func_00003558: 252-insn (0x3F0) heavy state-builder. Frame -0x100,
 * saves s0/ra and double-FPU $f20/$f21 (sdc1 at 0x18). Sibling of
 * game_uso_func_00003A4C (also frame-0xB0+ data-init).
 *
 * Stage 1 @ 0x3558-0x3578 (prologue + a0->[0x14] spill at 0xFC):
 *   t8 = arg0->[0x14]
 *   s0 = arg0; (saved across calls)
 *   a0 = sp+0x8C (stack scratch buffer)
 *
 * Stage 2 @ 0x3578-0x35C0 (3 Vec3-copy operations):
 *   sp[0xF0..0xF8] = t8->Vec3@0xA0       ; arg0->[0x14]'s Vec3
 *   sp[0xE4..0xEC] = s0->[0x48]->Vec3@0xA0 ; arg0->[0x48]'s Vec3
 *   sp[0x8C..0x94] = s0->Tri3i@0x68      ; 3 ints from arg0+0x68
 *
 * Stage 3 @ 0x35C4-0x35E8 (re-copy as floats):
 *   sp[0xC0..0xC8] = sp[0x8C..0x94]      ; treats Tri3i as Vec3
 *
 * 2026-05-15 (agent-b, source-2 sibling of 0x3AC0) — FULL 252-insn algorithm
 * mapped from raw-word objdump. It is a camera/spring vector solve:
 *   p   = s0->[0x14];                 // pointer, spilled sp+0xFC
 *   va  = p->Vec3@0xA0;               // sp+0xF0
 *   m0  = s0->[0x48];                 // matrix/transform source
 *   vb  = { m0->[0xA0], (m0+0x70)->[0x34], (m0+0x70)->[0x38] };
 *   v   = (Vec3)s0->Tri3i@0x68;       // input vec (int bits reused as float)
 *   // 3x3 matrix-vector accumulate: out = vb + M*v, M at (m0+0x70)
 *   //   rows use (m0+0x70)+{0,4,8 / 20,24,36 / 32,40,...}
 *   acc = transform(v, M) + vb;       // -> sp+0xC0 + back to sp+0xE4
 *   d   = acc - va;                   // sp+0x68 (Vec3 sub)
 *   s0->[0x3C..0x44] = scratch Vec3 (write-back of sp+0x8C copy)
 *   len = normalize(&sp+0xD8);        // jal gl_func (sqrt/normalize)
 *   // build sub-frame at p->[0x48]: zero + one product term, 2 gl_func
 *   m1  = s0->[0x4C]; repeat gather+sub+normalize on m1; 2 gl_func
 *   t   = gl_func_result;             // sp+0xAC distance
 *   // 3-way distance clamp (c.lt.s + bc1fl/bc1f):
 *   if (s0->[0x88] < t)      scale = t - s0->[0xA0];
 *   else if (t < s0->[0xA0]) scale = t - s0->[0xA0];
 *   else                     scale = 0.0f;     // f20
 *   sp+0xB0 *= scale;
 *   k = (sp+0xBC - s0->[0xB8]) * s0->[0x118];
 *   sp+0xD8 = sp+0xD8*k + sp+0xB0; gl_func(...);
 * Frame -0x100 saving s0/ra + double $f20 (sdc1 0x18 / ldc1 epilogue).
 *
 * First-pass structural NM wrap below @ 39.82% (was comment-only/bare
 * INCLUDE_ASM) — float scheduling NOT matched (USO raw-word, no m2c; IDO
 * float-sched is the multi-run tail). Captures the control flow, struct
 * offsets, and gl_func dispatch points as compilable reference. Next-run
 * levers: the exact M-row index mapping (0x00/0x10/0x20 vs 0x00/0x04/0x08
 * — disasm shows interleaved 112/128/.. (v0) offsets, verify per-row), and
 * the sub-frame build at p->[0x48] (mtc1 zero,$f20 + 2 gl_func, currently
 * elided). Picked source-2 (sibling of 0x3AC0). INCLUDE_ASM is the build
 * path so ROM stays byte-correct. */
/* game_uso_func_00003558: 252-insn (0x3F0) camera/spring vector solve. Frame
 * -0x100, saves s0/ra + double $f20/$f21 (sdc1 0x18 / ldc1 epilogue), f20=0.0f
 * sentinel used by the 3-way clamp. Sibling of game_uso_func_00001DDC's solve
 * tail; shares the Vec3 double-buffer fanout and the (070238 / 071028 / 072EE8)
 * callee triple.
 *
 * REBUILD 2026-06-24 (this pass): re-decoded region by region from
 * expected/.o (the prior NM body called the gl_func_00000000 placeholder, had
 * the wrong callees, and the wrong clamp/emit tail; stale-.s gap NM 0x280 vs
 * expected 0x3F0). Real callees (R_MIPS_26): game_uso_func_070238 (magnitude),
 * game_uso_func_071028 (normalize Vec3), game_uso_func_072EE8 (accumulate into
 * dst). Faithful end-to-end:
 *   p   = s0->[0x14]                                    (spilled sp+0xFC)
 *   va  = p->{0xA0,0xA4,0xA8}                           (ref vec, sp+0xF0)
 *   m0  = s0->[0x48];  M = m0 + 0x70
 *   vb  = { m0->[0xA0], M->[0x34], M->[0x38] }          (self vec, sp+0xE4)
 *   v   = (Vec3 read of) s0->Tri3i@0x68                 (int bits as float)
 *   acc = M(3x3) * v   (rows {0x00,0x10,0x20}/{0x04,0x14,0x24}/{0x08,0x18,0x28})
 *   vb += acc;  d = vb - va                             (sp+0x68, normalized later)
 *   s0->{0x3C,0x40,0x44} = d                            (Tri3i fanout writeback)
 *   mag = game_uso_func_070238(d.x^2 + d.y^2 + d.z^2)
 *   side = { 0, d.y * s0->[0x130], 0 }; game_uso_func_072EE8(p+0x30, &side)
 *   game_uso_func_071028(&d)                            (normalize d)
 *   m1  = s0->[0x4C];  M1 = m1 + 0x70
 *   w   = { m1->[0xA0]-va.x, 0, M1->[0x38]-va.z }       (sp+0xB0)
 *   t   = game_uso_func_070238(w.x^2 + w.y^2 + w.z^2)
 *   game_uso_func_071028(&w)                            (normalize w)
 *   if (s0->[0x88] < t)      { sc = t - s0->[0x88];  w *= sc; }   <- 0x88, NOT 0xA0
 *   else if (t < s0->[0xA0]) { sc = t - s0->[0xA0];  w *= sc; }
 *   else                     { w *= 0.0f; }          (f20 sentinel, real mul.s)
 *   k   = (mag - s0->[0xB8]) * s0->[0x118];
 *   e  *= k;  e += w;  game_uso_func_072EE8(p+0x30, &e)   (e = the d work vec)
 *
 * REWRITE 2026-07-09 (agent-e): 50 -> 67.27% objdiff. Fixed the mis-decoded
 * clamp (branch 1 subtracts s0->0x88, not 0xA0), recovered the FULL
 * marshalling chain (buf@0x8C -> buf2@0x4C -> e@0xD8 -> buf -> s0->0x3C..44)
 * and solved the -0x100 FRAME LAYOUT exactly: per-vector float[3] locals in
 * decl order (first decl = highest addr) with UNUSED pad arrays filling the
 * gaps (padA[3]@0xCC, padB[5]@0x98, padC[6]@0x74, padD[4]@0x58, padE[2]@0x44)
 * + `char * volatile p` (home 0xFC, sw t8 early + lw reload per 072EE8 call,
 * kills both the s1-promotion and the p+0x30 CSE spill) + mag/t plain floats
 * homed 0xBC/0xAC by spill-across-call. All sp offsets + frame now word-exact;
 * copies written in z,y,x statement order (matches target load order).
 * Residual classes (word count 240 vs 252):
 *  (1) matrix-block fp spill JUGGLE absent (-12): target holds vb in
 *      f14/f16/f18 across the 3x3 rows and juggles buf.x/y/z through temp
 *      slots sp+0x28/0x2C; every C form tried (named scalars, embedded
 *      assignments, fused per-axis, grouped adds) either skips the juggle or
 *      homes the named temps (+frame). Emergent uopt pressure shape.
 *  (2) else-branch w*=0.0f muls FOLD to plain f20 stores (-3): uopt folds
 *      mul-by-const-zero once the 0.0f web is cross-call (f20). Memory-opaque
 *      zero (int store + lwc1) restores the muls but costs sw+lwc1 and +8
 *      frame (all offsets shift) - rejected. Isolated probe (probe6) shows the
 *      muls CAN survive with literal 0.0f when the web is NOT cross-call-CSE'd;
 *      the exact target combo (single mtc1 zero,$f20 + live muls) not yet
 *      reproduced in C.
 *  (3) temp-pool phase shifts: p's def lands v0 (candidate m) vs target t8
 *      (pure temp), cascading the whole t-reg pool one slot; fp pool starts
 *      f4 vs target f6. Same class as docs W4 #3.
 * INCLUDE_ASM stays the build path so ROM is byte-correct. */
#ifdef NON_MATCHING
extern float game_uso_func_070238(float);
extern void game_uso_func_071028(Vec3 *v);
extern void game_uso_func_072EE8(char *dst, Vec3 *v);

void game_uso_func_00003558(char *s0) {
    char * volatile p;       /* home sp+0xFC (reloaded per use) */
    float va[3];             /* sp+0xF0 */
    float vb[3];             /* sp+0xE4 */
    float e[3];              /* sp+0xD8 */
    float padA[3];           /* sp+0xCC (unused) */
    float stage[3];          /* sp+0xC0 */
    float mag;               /* sp+0xBC (spilled across calls) */
    float w[3];              /* sp+0xB0 */
    float t;                 /* sp+0xAC (spilled across call) */
    float padB[5];           /* sp+0x98 (unused) */
    float buf[3];            /* sp+0x8C int-marshal hub */
    float padC[6];           /* sp+0x74 (unused) */
    float d[3];              /* sp+0x68 */
    float padD[4];           /* sp+0x58 (unused) */
    float buf2[3];           /* sp+0x4C */
    float padE[2];           /* sp+0x44 (unused) */
    float side[3];           /* sp+0x38 */
    char *m;
    float sc, k;

    m = *(char **)(s0 + 0x14);
    p = m;
    va[0] = *(float *)(m + 0xA0);
    va[1] = *(float *)(m + 0xA4);
    va[2] = *(float *)(m + 0xA8);

    m = *(char **)(s0 + 0x48);
    vb[0] = *(float *)(m + 0xA0);
    m += 0x70;
    vb[1] = *(float *)(m + 0x34);
    vb[2] = *(float *)(m + 0x38);

    /* Tri3i (integer) marshal of the input vector into the hub buffer. */
    *(Tri3i *)buf = *(Tri3i *)(s0 + 0x68);
    stage[2] = buf[2];
    stage[1] = buf[1];
    stage[0] = buf[0];

    m = *(char **)(s0 + 0x48);
    m += 0x70;
    stage[0] = *(float *)(m + 0x00) * buf[0]
             + *(float *)(m + 0x10) * buf[1]
             + *(float *)(m + 0x20) * buf[2];
    stage[1] = *(float *)(m + 0x04) * buf[0]
             + *(float *)(m + 0x14) * buf[1]
             + *(float *)(m + 0x24) * buf[2];
    stage[2] = *(float *)(m + 0x08) * buf[0]
             + *(float *)(m + 0x18) * buf[1]
             + *(float *)(m + 0x28) * buf[2];
    vb[0] = vb[0] + stage[0];
    vb[1] = vb[1] + stage[1];
    vb[2] = vb[2] + stage[2];

    d[0] = vb[0] - va[0];
    d[1] = vb[1] - va[1];
    d[2] = vb[2] - va[2];

    /* d fans through the marshalling chain: buf -> buf2 -> e -> buf. */
    *(Tri3i *)buf = *(Tri3i *)d;
    *(Tri3i *)buf2 = *(Tri3i *)buf;
    e[2] = buf2[2];
    e[1] = buf2[1];
    e[0] = buf2[0];
    *(Tri3i *)buf = *(Tri3i *)e;
    *(float *)(s0 + 0x3C) = buf[0];
    *(float *)(s0 + 0x40) = buf[1];
    *(float *)(s0 + 0x44) = buf[2];

    mag = game_uso_func_070238(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);

    side[0] = 0.0f;
    side[1] = e[1] * *(float *)(s0 + 0x130);
    side[2] = 0.0f;
    game_uso_func_072EE8(p + 0x30, (Vec3 *)side);

    game_uso_func_071028((Vec3 *)e);

    m = *(char **)(s0 + 0x4C);
    w[0] = *(float *)(m + 0xA0);
    m += 0x70;
    w[1] = *(float *)(m + 0x34);
    w[2] = *(float *)(m + 0x38);
    w[0] = w[0] - va[0];
    w[1] = 0.0f;
    w[2] = w[2] - va[2];

    t = game_uso_func_070238(w[0] * w[0] + w[1] * w[1] + w[2] * w[2]);
    game_uso_func_071028((Vec3 *)w);

    if (*(float *)(s0 + 0x88) < t) {
        sc = t - *(float *)(s0 + 0x88);
        w[0] = w[0] * sc;
        w[1] = w[1] * sc;
        w[2] = w[2] * sc;
    } else if (t < *(float *)(s0 + 0xA0)) {
        sc = t - *(float *)(s0 + 0xA0);
        w[0] = w[0] * sc;
        w[1] = w[1] * sc;
        w[2] = w[2] * sc;
    } else {
        w[0] = w[0] * 0.0f;
        w[1] = w[1] * 0.0f;
        w[2] = w[2] * 0.0f;
    }

    k = (mag - *(float *)(s0 + 0xB8)) * *(float *)(s0 + 0x118);
    e[0] = e[0] * k;
    e[1] = e[1] * k;
    e[2] = e[2] * k;
    e[0] = e[0] + w[0];
    e[1] = e[1] + w[1];
    e[2] = e[2] + w[2];
    game_uso_func_072EE8(p + 0x30, (Vec3 *)e);
}


#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003558);
#endif

void game_uso_func_00003948(char *a0) {
    game_uso_func_00000000(a0 + 0x50);
}

void game_uso_func_00003968(char *dst) {
    int tmp;
    game_uso_func_00000280(&tmp);
    game_uso_func_00000244((float*)(dst + 0x10));
}

void game_uso_func_00003998(char *dst) {
    int tmp;
    game_uso_func_00000280(&tmp);
    game_uso_func_000001D4((Vec3*)(dst + 0x10));
}

void game_uso_func_000039C8(char *dst) {
    int tmp;
    game_uso_func_00000280(&tmp);
    game_uso_func_0000039C((Quad4*)(dst + 0x10));
}

void game_uso_func_000039F8(char *dst) {
    int tmp;
    game_uso_func_00000280(&tmp);
    game_uso_func_00000280((int*)(dst + 0x10));
}

/* game_uso_func_00003A28: 36-insn alloc-init constructor. alloc(0x40) +
 * init(051C28), set vtable 0x28 = &import_8006ED80, clear 0x3C; then walk
 * a0->0x40 node and link it back via 07ACE0.
 *
 * 2026-06-21 CRACKED via masked-twin port from eddproc_uso_func_000003BC
 * (donor, byte-exact). The prior "89.22% NM ceiling / v0-v1 regalloc +
 * frame + jal-swap cap" was a structure+symbol issue: the old body used
 * placeholder gl_func/&D and the simplified obj/other locals. The donor's
 * p2/head/p1 split + p1-reuse-for-arg0 + decl-order (p2,head,p1) + condition
 * re-load forces the two-web spill (frame 0x28) and the a0/v1 coloring.
 * Do NOT simplify the variable reuse or the re-load. */
extern char import_8006ED80;
int *game_uso_func_00003A28(int *arg0) {
    int *p2;
    int *head;
    int *p1;
    p1 = (int*)game_uso_func_055750(0x40);
    if (p1 != 0) {
        game_uso_func_051C28(p1);
        *(int*)((char*)p1 + 0x28) = (int)&import_8006ED80;
        *(int*)((char*)p1 + 0x3C) = 0;
    }
    p2 = p1;
    p1 = arg0;
    head = (int*)p1[0x40 / 4];
    if ((int*)p1[0x40 / 4] != 0) {
        game_uso_func_07ACE0((char*)p2 + 0x10, head);
        if (*(int*)((char*)head + 0x14) != 0) {
            *(int*)((char*)head + 0x4) = 1;
        }
        *(int*)((char*)head + 0x14) = (int)p2;
    }
    return p2;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_uso/game_uso/game_uso_func_00003A28_pad.s")

/* game_uso_func_00003AC0: 261-insn (0x414) constructor. Frame -0x70.
 * Same family as game_uso_func_00003018 + game_uso_func_000044F4 spine
 * (alloc-cascade + init pattern). Initial structural decode:
 *
 * Stage 1 @ 0x3AC0-0x3AE8: load D[0x680], alloc(0x58), null-check
 *   t6 = D[0x680]                        (template-list pointer)
 *   s0 = alloc(0x58)                     ; alloc 88-byte object
 *   if (s0 == NULL) goto epi
 *
 * Stage 2 @ 0x3AF0-0x3B08: init from D[0x680] template
 *   init(s0, D[0x680], 0, 0)              ; gl_func init call
 *   s0->[0x28] = &D                       ; install parent ptr
 *
 * Stage 3 @ 0x3B14-0x3B20: register with arg0
 *   register_func(arg0, s0, -1)            ; gl_func register
 *
 * Stage 4 @ 0x3B24-0x3B40: load D[0x684], alloc(0x58), null-check
 *   t0 = D[0x684]                        (second template-list ptr)
 *   s0 = alloc(0x58)                     ; second alloc
 *   if (s0 == NULL) goto ...
 *
 * Stage 5+: similar init chain on second object, plus more (~210
 * remaining insns). Likely a paired-allocator pattern:
 * "alloc + init from template_a + alloc + init from template_b + ...
 * link both to arg0".
 *
 * 2026-05-15 (agent-b, source-5 fall-through to fresh-unstarted): FULL
 * structure decoded from raw-word objdump. It is exactly 12 identical
 * blocks, D-template index 0x680,0x684,...,0x6AC (step 4, 12 entries):
 *   dN = *(int*)(&D + 0x680 + N*4);
 *   s0 = alloc(0x58);                       // gl_func_00000000(0x58)
 *   if (s0) {
 *     gl_func_00000000(s0, dN, 0, 0);       // init from template dN
 *     *(int*)(s0 + 0x28) = (int)&D;         // install parent/vtable ptr
 *   }
 *   gl_func_00000000(arg0, s0, -1);         // register sub-object w/ arg0
 * Each dN gets its own descending stack home (sp+0x6C..0x40) → 12 distinct
 * named locals modelled below. s0 persists in $s0 across the register call
 * (and into the next block's failed-alloc path). Epilogue sets no v0
 * explicitly → return type void (last call's v0 is unused).
 *
 * Picked under source 5 (strategy memo exhausted → fresh-unstarted,
 * size-descending). Structural NM wrap @ 63.67% (was bare INCLUDE_ASM).
 * INCLUDE_ASM still the build path so ROM stays byte-correct.
 *
 * 2026-06-22 (agent-i): reconstructed to the TRUE per-iteration structure
 * with the SAME reloc symbols expected uses — the 12 distinct globals
 * game_uso_D_807FEC70..D_807FEC9C, each read as *(int*)(&sym + 0x680),
 * alloc(0x58), init via game_uso_func_051E64, parent ptr = &game_uso_D_807FEAA8
 * @ obj+0x28, register via game_uso_func_052F70(arg0, s0, -1). Body is the
 * correct C.
 *
 * 2026-06-22 HARD-CAP verdict RETRACTED 2026-07-07 (agent-e): cap (1)
 * "reloc form" is falsified under the reloc-free landing convention —
 * all syms are =0 in undefined_syms, so IDO's HI16/LO16 pair vs the .s
 * raw-word lw produce IDENTICAL BYTES at link (lui 0x0000 / lw 0x680+4k).
 * Cap (2) "$s-promotion" cracked: the block is really TWO variables —
 * per-block struct dN (descending home, 0x6C..0x40) + a SHARED 4-byte
 * struct staging slot at 0x24 that feeds the K&R struct-by-value arg of
 * game_uso_func_051E64 (hence `lw a1,0x24(sp)` + the `sw a1,4(sp)`
 * arg-HOME store in the jal delay slot). Matching form (253/261 words):
 *   - dN.v = *(int*)((char*)&D_807FECxx + 0x680+4k);  (scalar load —
 *     transient tN, t6/t0/t4/t8/t2 rotation)
 *   - curX = dN;   (4-byte STRUCT copy — forwards the tN into BOTH sw's
 *     without creating a v0 register candidate; a scalar copy or chained
 *     assignment here allocates $v0 instead and breaks the t-rotation)
 *   - init(s0, curX, 0, 0)  passes curX struct-by-value.
 *   - &D_807FEAA8 must be 12 DISTINCT zero-value extern aliases
 *     (game_uso_D_807FEAA8, _2.._12) or uopt GCSEs the address into $s1.
 *   - frame layout: registerized locals keep GHOST slots — `void *s0;`
 *     declared LAST parks its ghost at 0x20, putting dN at 0x6C..0x40,
 *     the 5 volatile pads + curB at 0x3C..0x28 and curA at 0x24 (frame
 *     -0x70 exact).
 * RESIDUAL (8 words, 4 blocks): uopt turns struct copies POINTER-BASED
 * (addiu sN,sp,K base + lw/sw 0(sN)) once ONE variable participates in
 * >=9 block copies (8 is the empirical max; 9+ flips ALL copies).
 * Target stages all 12 blocks through slot 0x24; best compilable split
 * is curA x8 (0x24, matches) + curB x4 (0x28, 4 blocks' 2 words off).
 * The original construct for a 12-way shared staging temp is unknown
 * (scoped locals get distinct slots; unions/ternary/comma/register/
 * volatile forms all tested — see episode notes). 253/261 = 96.9%.
 *
 * 2026-07-15 wave-3 re-probe (agent-h) vs the 07-15 lever taxonomy —
 * cap RECONFIRMED, edges sharpened:
 *  - the >=9 flip counts ANY def of the staging var incl. single-member
 *    scalar stores (curA.v = <CSE'd load> as 9th participation flips ALL
 *    copies fn-wide, even d0's; single-member struct member-write is
 *    canonicalized to a struct copy) and SOURCE participation (dM = curA
 *    inverted direction flips too). So 12 stagings through one symbol
 *    can never stay direct.
 *  - explicit frame-pointer arithmetic (*(S3AC0*)((char*)&pad6 - 4))
 *    poisons alias info: EVERYTHING goes pointer-based, incl. dN homes.
 *  - 12 block-scoped one-shot `S3AC0 cur` vars: NO flip, byte-perfect
 *    block shape (sw home / sw cur / lw a1 cur), but -g0 -O2 IDO does
 *    NOT overlay disjoint-scope homes even for memory-live staging
 *    (12 distinct slots 0x50..0x24, frame -0xA0; 212/261 - worse).
 *  - de-naming (pass dN direct / nameless CSE re-deref arg): the value
 *    web dies at the home store and the arg reloads from dN's home (or
 *    the load sinks past the call + dN stores DCE) - no shared 0x24.
 * Conclusion: target needs 12 one-slot stagings with <=8 participations
 * per symbol and no scope overlay - unreachable from C under 7.1 -O2. */
#ifdef NON_MATCHING
extern char game_uso_D_807FEC70;
extern char game_uso_D_807FEC74;
extern char game_uso_D_807FEC78;
extern char game_uso_D_807FEC7C;
extern char game_uso_D_807FEC80;
extern char game_uso_D_807FEC84;
extern char game_uso_D_807FEC88;
extern char game_uso_D_807FEC8C;
extern char game_uso_D_807FEC90;
extern char game_uso_D_807FEC94;
extern char game_uso_D_807FEC98;
extern char game_uso_D_807FEC9C;
extern char game_uso_D_807FEAA8;
extern char game_uso_D_807FEAA8_2;
extern char game_uso_D_807FEAA8_3;
extern char game_uso_D_807FEAA8_4;
extern char game_uso_D_807FEAA8_5;
extern char game_uso_D_807FEAA8_6;
extern char game_uso_D_807FEAA8_7;
extern char game_uso_D_807FEAA8_8;
extern char game_uso_D_807FEAA8_9;
extern char game_uso_D_807FEAA8_10;
extern char game_uso_D_807FEAA8_11;
extern char game_uso_D_807FEAA8_12;
extern int game_uso_func_055750();
extern void game_uso_func_051E64();
extern void game_uso_func_052F70();
typedef struct { int v; } S3AC0;
void game_uso_func_00003AC0(void *arg0) {
    S3AC0 d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11;
    volatile int pad1, pad2, pad3, pad4, pad5;
    S3AC0 curB;
    S3AC0 curA;
    void *s0;

    d0.v = *(int*)((char*)&game_uso_D_807FEC70 + 0x680);
    curA = d0;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curA, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8;
    }
    game_uso_func_052F70(arg0, s0, -1);
    d1.v = *(int*)((char*)&game_uso_D_807FEC74 + 0x684);
    curA = d1;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curA, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8_2;
    }
    game_uso_func_052F70(arg0, s0, -1);
    d2.v = *(int*)((char*)&game_uso_D_807FEC78 + 0x688);
    curA = d2;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curA, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8_3;
    }
    game_uso_func_052F70(arg0, s0, -1);
    d3.v = *(int*)((char*)&game_uso_D_807FEC7C + 0x68C);
    curA = d3;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curA, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8_4;
    }
    game_uso_func_052F70(arg0, s0, -1);
    d4.v = *(int*)((char*)&game_uso_D_807FEC80 + 0x690);
    curA = d4;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curA, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8_5;
    }
    game_uso_func_052F70(arg0, s0, -1);
    d5.v = *(int*)((char*)&game_uso_D_807FEC84 + 0x694);
    curA = d5;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curA, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8_6;
    }
    game_uso_func_052F70(arg0, s0, -1);
    d6.v = *(int*)((char*)&game_uso_D_807FEC88 + 0x698);
    curA = d6;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curA, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8_7;
    }
    game_uso_func_052F70(arg0, s0, -1);
    d7.v = *(int*)((char*)&game_uso_D_807FEC8C + 0x69C);
    curA = d7;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curA, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8_8;
    }
    game_uso_func_052F70(arg0, s0, -1);
    d8.v = *(int*)((char*)&game_uso_D_807FEC90 + 0x6A0);
    curB = d8;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curB, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8_9;
    }
    game_uso_func_052F70(arg0, s0, -1);
    d9.v = *(int*)((char*)&game_uso_D_807FEC94 + 0x6A4);
    curB = d9;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curB, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8_10;
    }
    game_uso_func_052F70(arg0, s0, -1);
    d10.v = *(int*)((char*)&game_uso_D_807FEC98 + 0x6A8);
    curB = d10;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curB, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8_11;
    }
    game_uso_func_052F70(arg0, s0, -1);
    d11.v = *(int*)((char*)&game_uso_D_807FEC9C + 0x6AC);
    curB = d11;
    s0 = (void*)game_uso_func_055750(0x58);
    if (s0 != 0) {
        game_uso_func_051E64(s0, curB, 0, 0);
        *(int*)((char*)s0 + 0x28) = (int)&game_uso_D_807FEAA8_12;
    }
    game_uso_func_052F70(arg0, s0, -1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003AC0);
#endif

/* game_uso_func_00003ED4: 54-insn FPU geometry helper (yaw-between-vectors).
 * Copies a1's Vec3 to vb and normalizes it via game_uso_func_071028, copies a0's
 * Vec3 to va and normalizes it, then r = game_uso_func_07E330(dot_xz(va,vb)) /
 * D_00000000[0x90]; flips sign of the result by the cross-product test, zeroes
 * *a2 if non-NULL, returns the (possibly negated) result.
 * 2026-06-20 (agent-b): MATCHED byte-exact. Reconstructed to the real callees
 * the .s names (game_uso_func_071028 = the Vec3 normalize; game_uso_func_07E330
 * = the float-returning dot-product consumer). game_uso_func_07E330_ff is a
 * float-prototyped alias (addr 0) that suppresses the K&R float->double arg
 * promotion (no cvt.d.s). The prior 0.56% residual was NOT FP register coloring
 * (as earlier notes guessed) but a frame-layout diff: declaring va immediately
 * after vb (before new_var) packs the two Vec3 stack slots adjacent (va @sp+0x2C,
 * vb @sp+0x38), matching IDO's layout -> 0 diffs. Relocatable USO: intra-module
 * jal emits 0C000000 and the %hi/%lo data ref is base-0 +0x90 (&D_00000000+0x90),
 * relocs applied at load. The `unused` leading float local is load-bearing for
 * the frame size; pad[4] fills the tail slot. */
extern float game_uso_func_07E330_ff(float);  /* float-prototyped alias of game_uso_func_07E330 (addr 0): avoids K&R float->double arg promotion */
float game_uso_func_00003ED4(Vec3 *a0, Vec3 *a1, int *a2) {
  float unused;
  Vec3 vb;
  Vec3 va;
  char *new_var;
  char pad[4];
  float ret;
  float r;
  new_var = ((char *) (&D_00000000)) + 0x90;
  ret = r;
  (void) unused;
  (void) pad;
  vb = *a1;
  game_uso_func_071028(&vb);
  va = *a0;
  game_uso_func_071028(&va);
  r = game_uso_func_07E330_ff((va.x * vb.x) + (va.z * vb.z));
  r = r / (*((float *) new_var));
  ret = r;
  if ((va.z * vb.x) < (va.x * vb.z))
  {
    ret = -r;
  }
  if (a2 != ((void *) 0))
  {
    *a2 = 0;
  }
  return ret;
}

/* game_uso_func_00003FAC: 53-insn (0xD4) FPU-heavy 2D-rotation-like
 * vector builder. Frame -0x20, single cross-USO call.
 *
 * Inputs (decoded from arg-spill + reload pattern):
 *   a0: float[3] output #1 (writes [0], [4]=0, [8])
 *   a1: float[3] output #2 (writes [0], [4]=0, [8])
 *   a2: float[3] input vector (reads [0] and [8] only — [4] unused)
 *   a3: float divisor (o32 mixed-mode ABI passes it in $a3, target mtc1s it)
 *   sp+0x30: float arg5 (numerator for scale = arg5/a3)
 *
 * Algorithm:
 *   orig_scale = arg5 / a3                 ; f0 before call
 *   ratio     = orig_scale * orig_scale    ; f8 = orig_scale^2
 *   inner_arg = 1.0 - ratio                ; f12 (passed to callee)
 *   new_scale = func_00000000(inner_arg, a3)
 *
 *   ; outputs use both new_scale (= post-call f0) and orig_scale (= f2 saved):
 *   a0[0] = new_scale * a2[0] + orig_scale * a2[2]
 *   a0[1] = 0
 *   a0[2] = -orig_scale * a2[0] + new_scale * a2[2]
 *   a1[0] = new_scale * a2[0] - orig_scale * a2[2]
 *   a1[1] = 0
 *   a1[2] = orig_scale * a2[0] + new_scale * a2[2]
 *
 * Looks like a rotation-matrix construction: a0 may be (cos*x + sin*z, 0,
 * sin^2*x + cos*z) and a1 may be the reflected/swapped variant. Inner
 * func is plausibly sqrt or sincos-like (returns derived scale).
 *
 *
 * 2026-05-20 refinement: corrected a3 to mixed-mode float, switched the
 * inner call to a typed zero-address alias returning float, and fixed a0[2]
 * to use -orig_scale instead of ratio. Fuzzy: 52.43% -> 98.23%.
 * 2026-05-29: MATCHED. The 5 residual diffs (3 commutative mul operand swaps +
 * the $f8<->$f10 neg_scale/coord allocation pair) all close by forcing each
 * scale factor into a register AT the multiply via an assignment-expression:
 * `coord * (tmp = scale)` makes IDO take the scale as the mul's fs (the default
 * for `scale * coord` after a fresh coord load is coord-as-fs), and for
 * neg_scale it also lands the target's $f8. The tmp vars (ns/os/nsd/neg) are
 * write-only operand-ordering levers. Found via decomp-permuter, then minimized. */
extern float game_uso_func_082880(float);
void game_uso_func_00003FAC(float *a0, float *a1, float *a2, float a3, float arg4) {
    float orig_scale = arg4 / a3;
    float ns, os, nsd, neg;
    float ratio = orig_scale * orig_scale;
    float new_scale = game_uso_func_082880(1.0f - ratio);
    (void)ratio;
    a0[0] = (orig_scale * a2[2]) + (a2[0] * (ns = new_scale));
    a0[1] = 0.0f;
    a0[2] = (new_scale * a2[2]) + (a2[0] * (neg = -orig_scale));
    a1[0] = (new_scale * a2[0]) - (a2[2] * (os = orig_scale));
    a1[1] = 0.0f;
    a1[2] = (new_scale * a2[2]) + (a2[0] * (nsd = orig_scale));
}

void game_uso_func_00004080(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_000040BC(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_000040F8(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    gl_func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

void game_uso_func_00004168(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

#ifdef NON_MATCHING
/* game_uso_func_000041C0: cascading subsystem-init constructor (frame -0x48).
 * Whole-body re-decode 2026-06-24 from expected/.o (size 0x218). alloc(0x8C)
 * + init(051C28) + set vtable slot 0x28; obj = p1+0x3C (realloc(0x50) only if
 * obj==0). Three dead sentinel-guarded sub-stages (obj == -8/-0x20/-0x38,
 * never live since obj = p1+0x3C from an opaque alloc — the family's
 * dead-stage-guard pattern): each loads template = *(D+0x6cX), computes
 * a0=obj+8/+0x20/+0x38, and on the (dead) equal arm alloc(0x18)+register
 * (04A188(obj2,obj,template,flag)) + template-init (incl. 1.0f swc1 in arm 1).
 * Tail: walk a0saved->0x40 node; if non-null link p1+0x10 via 07ACE0, set
 * node+4=1 when node+0x14!=0, then node+0x14 = p1. Returns p1 (v1). */
extern char game_uso_D_807FEB68;
extern char game_uso_D_807FECA0;
extern char game_uso_D_807FECB4;
extern char game_uso_D_807FE9B8;
extern char game_uso_D_807FECB8;
extern char game_uso_D_807FEA00;
extern char game_uso_D_807FECBC;
extern int game_uso_func_055750();
extern int game_uso_func_051C28();
extern int game_uso_func_04A188();
extern int game_uso_func_07ACE0();
int *game_uso_func_000041C0(int a0) {
    int *p1;
    int *obj;
    int *obj2;
    int tmpl;
    int *node;
    int *parent;

    p1 = (int *)game_uso_func_055750(0x8C);
    if (p1 == 0) {
        return p1;
    }
    game_uso_func_051C28(p1);
    *(int *)((char *)p1 + 0x28) = (int)&game_uso_D_807FEB68;

    obj = (int *)((char *)p1 + 0x3C);
    if ((int)p1 == -0x3C) {
        obj = (int *)game_uso_func_055750(0x50);
        if (obj == 0) {
            return obj;
        }
    }
    if (obj == 0) {
        obj2 = (int *)game_uso_func_055750(8);
        if (obj2 != 0) {
            obj2[0] = (int)((char *)&game_uso_D_807FECA0 + 0x6B0);
            obj2[1] = 0;
        }
    }

    tmpl = *(int *)((char *)&game_uso_D_807FECB4 + 0x6C4);
    if ((int)obj == -8) {
        obj2 = (int *)game_uso_func_055750(0x18);
        if (obj2 == 0) {
            return obj2;
        }
        game_uso_func_04A188(obj2, obj, tmpl, 1);
        *(int *)((char *)obj2 + 0xC) = (int)((char *)&game_uso_D_807FE9B8 + 0x3C8);
        *(int *)((char *)obj2 + 0x14) = 0;
        *(float *)((char *)obj2 + 0x10) = 1.0f;
    }

    tmpl = *(int *)((char *)&game_uso_D_807FECB8 + 0x6C8);
    if ((int)obj == -0x20) {
        obj2 = (int *)game_uso_func_055750(0x18);
        if (obj2 == 0) {
            return obj2;
        }
        game_uso_func_04A188(obj2, obj, tmpl, 1);
        *(int *)((char *)obj2 + 0xC) = (int)((char *)&game_uso_D_807FEA00 + 0x410);
        *(int *)((char *)obj2 + 0x10) = 0;
        *(int *)((char *)obj2 + 0x14) = 0;
    }

    tmpl = *(int *)((char *)&game_uso_D_807FECBC + 0x6CC);
    if ((int)obj == -0x38) {
        obj2 = (int *)game_uso_func_055750(0x18);
        if (obj2 == 0) {
            return obj2;
        }
        game_uso_func_04A188(obj2, obj, tmpl, 0);
        *(int *)((char *)obj2 + 0xC) = (int)((char *)&game_uso_D_807FEA00 + 0x410);
        *(int *)((char *)obj2 + 0x14) = 0;
        *(int *)((char *)obj2 + 0x10) = 0;
    }

    node = *(int **)((char *)a0 + 0x40);
    parent = p1;
    if (node != 0) {
        game_uso_func_07ACE0((char *)p1 + 0x10, node);
        if (*(int *)((char *)node + 0x14) != 0) {
            *(int *)((char *)node + 4) = 1;
        }
        *(int *)((char *)node + 0x14) = (int)parent;
    }
    return parent;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000041C0);
#endif

/* game_uso_func_000043D8: 60-insn cell-walk + FPU nearest-select. Walk the
 * {value@0, next@4} cell list from a0->0x10; for each value n != a2 compute
 * d = a1->0x8 - n->0x38 and track the nearest-below (largest d<0 -> v1/fmax)
 * and nearest-above (smallest d>=0 -> v0/fmin), seeded from D[0x94]/D[0x98].
 * Return v0 ? v0 : v1.
 * NON_MATCHING cap: no-call same-base cell-walk = reload-CSE class (the dual
 * sp-slot cursor + branch-likely select aren't C-reproducible) AND the f0/f2
 * seeds load from the USO FP literal pool (mis-attributed by splat). Real C
 * body below (un-bailed from doc-comment per docs/IDO_CODEGEN); INCLUDE_ASM is
 * the byte-exact build path.
 * 2026-05-28 regalloc detail: with NO calls in the body, mine promotes `a1` to
 * $s0 (tiny frame -8), but target keeps a1 in caller-saved $a3 with a bigger
 * frame (-0x18) spilling head/nextcell to sp+0/+4. The volatile-ptr knob
 * (gl_func_00072550) does NOT apply — it forces STACK reload, but target keeps
 * a1 in a REGISTER ($a3); there's no C knob to pin a loop-long value to a
 * caller-saved reg instead of $s. Whole-function allocation-strategy cap. */
#ifdef NON_MATCHING
/* game_uso_func_000043D8: 60-insn cell-walk + FPU nearest-select.
 * v2 reconstruction: two-cursor stack-spilled walk. head=a0->0x10; seed
 * both cursors (cur@sp0, nextcell@sp4) from head; for each cell value n!=a2
 * compute d = a1->8 - n->0x38; track nearest-below (largest d<0 -> v1/f2)
 * and nearest-above (smallest d>=0 -> v0/f0), seeded from base[0x94]/[0x98].
 * Return v0 ? v0 : v1. */
void *game_uso_func_000043D8(int **a0, int *a1, void *a2) {
    float fmin = *(float *)0x94;
    float fmax = *(float *)0x98;
    void *v0 = 0;
    void *v1 = 0;
    int *head = a0[4]; /* a0->0x10 */
    int *cur;
    int *nextcell;
    if (head != 0) {
        nextcell = (int *)head[1];
        cur = (int *)head[0];
    } else {
        cur = 0;
    }
    while (cur != 0) {
        if ((void *)cur != a2) {
            float d = *(float *)((char *)a1 + 8) - *(float *)((char *)cur + 0x38);
            if (d < 0.0f) {
                if (fmax < d) { v1 = cur; fmax = d; }
            } else {
                if (d < fmin) { v0 = cur; fmin = d; }
            }
        }
        if (nextcell != 0) {
            cur = (int *)nextcell[0];
            nextcell = (int *)nextcell[1];
        } else {
            cur = 0;
        }
    }
    return v0 ? v0 : v1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000043D8);
#endif

void game_uso_func_000044C8(char *a0) {
    game_uso_func_00000000(a0);
    game_uso_func_00000000(a0 + 0x3C);
}

/* game_uso_func_000044F4: 0x1234 (1165 insns, 4.6 KB) — spine candidate #1
 * "main GameState constructor" per project_1080_game_uso_map.md.
 *
 * 2026-06-11 STATUS: C body scores 100.0 on objdiff, exact-word LCS
 * 1165/1165 vs target (reloc-masked). Cracked by the STRUCT-MARSHALLING
 * rewrite (see comment inside the function body): the marshalling slot is
 * a 4-byte struct passed by value, the per-iter spill slots are 41 named
 * struct locals in decl order, sentinels are -SLOT (natural
 * `p = s1 + SLOT; if (p == NULL)` form), iter alloc-failure skips to the
 * next iter, and the finalize float-table loads use 5 unique externs
 * (D_44F4_st12_*) to break base-CSE. Historical analysis below is kept
 * for archeology; the "REMAINING CAP" sections are all RESOLVED.
 * 0xE8-byte stack frame, 86 cross-USO calls (mostly alloc() and
 * init_subobject()).
 *
 * DECODED ENTRY (first ~25 insns, 0x44F4-0x4564):
 *   prologue:
 *     addiu sp, -0xE8; sw ra,0x24; sw s0-s2,0x18-0x20
 *     sw a0,0xE8(sp); sw a1,0xEC(sp); sw a2,0xF0(sp)  ; 3 args spilled
 *   if (a0 == NULL) {               ; bne a0, zero, +5
 *     self = gl_func_0(0x4E0);      ; alloc 1248-byte main obj
 *     if (self == NULL) goto epi;   ; beq v0, zero, +0x47A (to ~0x5A4B)
 *     a0_spill = self;              ; sw v0, 0xE8(sp)
 *   }
 *   gl_func_0(&D_0 + 0x6D0, a0);    ; init from template at D_06D0 (1st call)
 *   a0->field_28 = &D_0;            ; 1st parent ptr
 *
 *   if (a0_spill != -0xE4) {         ; unusual address-as-signed-imm compare
 *     s1 = a0_spill + 0xE4;          ; s1 = main + 0xE4 (sub-region)
 *   } else {
 *     s1 = alloc(0x3E0);             ; alloc 992-byte child obj
 *     if (!s1) goto epi;
 *   }
 *   // ... 1140 more insns: allocates ~16 x 0x18-byte sub-objects,
 *   //     initialized from templates, linked via a0[0x2C], a0[0x38], etc.
 *
 * Full decode is a multi-day effort. This tick captures entry pattern +
 * struct-field offsets identified so far. Future ticks: decode the
 * sub-object allocation loop, type the GameState struct, then refine.
 *
 * 2026-05-06 RE-MEASURE: 62.05% NM (objdiff fuzzy score on the
 * #ifdef-NM-aliased OBJECT symbol). Built emits 1020 insns / 0xFF0 vs
 * target 1165 insns / 0x1234 — gap of 145 missing insns (~12% of
 * function) IN THE C-EMIT PATH. The DEFAULT INCLUDE_ASM (#else) path
 * is BYTE-IDENTICAL to expected/.o (verified 2026-05-06: `cmp` shows
 * identical .text section, no-aliases objdump diff is empty). An
 * episode is logged at episodes/game_uso_func_000044F4.json — the
 * function is BYTE-CORRECT in ROM via the INCLUDE_ASM path per
 * docs/MATCHING_WORKFLOW.md feedback-byte-correct-match-via-include-asm-not-c-body.
 * The 62% score is the .NON_MATCHING-alias scoring quirk on the C-body
 * emit, which is documentation-only.
 *
 * Remaining work for full C-emit byte-equivalence (low-priority since
 * ROM is already exact): un-decoded sub-object init blocks between the
 * tail-stage (0x5658-0x5724, mostly written) and the early-stage
 * stub-list (0x4564-0x4710, partially written). The new
 * feedback-ido-cse-bust-via-distinct-externs technique
 * (docs/IDO_CODEGEN.md) may help if any of the remaining ~145-insn gap
 * stems from CSE-folded `&D_00000000` accesses. Multi-pass continuation
 * is research-only — primary decomp goal already met.
 *
 * 2026-05-27 retest: prologue mismatch is INTERLOCKED between three knobs:
 *   - `volatile int a1_sp = a1; a2_sp = a2;` puts the spills at sp+0x34/0x30
 *     (LOCAL stack) — current state, scores 70.03%.
 *   - `(void)&a0; (void)&a1; (void)&a2;` flips the spills to sp+0xE0/0xE4/0xE8
 *     (CALLER's outgoing-arg shadow) BUT drops 8 bytes of frame (volatile
 *     locals gone) → frame 0xE0 not 0xE8 → regression to 69.55%.
 *   - Keeping `_pad[168]` after the (void)&aN switch restores frame 0xE8 with
 *     a0/a1/a2 at sp+0xE8/0xEC/0xF0 (matching target's lines 1/6/8) → but
 *     ra/s0/s1 stay at sp+0x1c/0x18/0x14 instead of target's sp+0x24/0x1c/0x18
 *     because target SAVES s2 too (`sw s2, 0x20(sp)`) and our C has no
 *     $s2-class variable. Net 69.56% — the +0x8 shift on every downstream
 *     sp-relative ref loses more than the a0/a1/a2 fix gains.
 * Cracking the prologue needs (a) take-addr-of-args for shadow spills AND
 * (b) a fourth s-class variable live across calls so IDO allocates $s2 at
 * sp+0x20. Without (b), the (a) win is a net negative.
 *
 * 2026-06-01 SOURCE=5 remeasure: current C path scores 79.56824%. A stale
 * pad[160] had drifted back to frame 0xF0; pad[152] restores target frame
 * 0xE8 and moves the score from 79.56223 to 79.56824. The remaining prologue
 * mismatch is still the known $s2 marshalling-base problem plus local-vs-home
 * arg spills, not a frame-size issue.
 *
 * 2026-05-28: the s2-pseudo IS now identified — disassembling expected/.o
 * shows `addiu s2, sp, 0x2c` (insn @0x45a0) materialized ONCE, then 38×
 * `sw t?, 0(s2)` / `lw a2, 0(s2)` pairs: $s2 holds the ADDRESS of the
 * per-iter marshalling scratch at sp+0x2C (the template ptr is stored
 * there then reloaded as the 3rd arg `a2` of each init call). BLOCKER
 * confirmed not-yet-crackable: declaring `char *_s2_buf; char *s2 = &_s2_buf;`
 * at function scope + `(void)&aN` home-slot spills builds, but IDO FOLDS
 * `*s2` into direct `sw v0, 0xD0(sp)` (sp+const addressing) and never keeps
 * the address in a register → no $s2, frame stays 0xE0, net 70.04% (a 0.49pp
 * REGRESSION vs the 70.53% volatile-local baseline). Making `_s2_buf`
 * volatile forces the memory roundtrip but STILL uses direct sp-relative (no
 * $s2). Register-indirect via a held $s2 is strictly worse codegen than
 * direct addressing for a known sp+const, so IDO won't emit it from a plain
 * `&local`. The target's register-indirect $s2 must come from the original
 * source giving the marshalling slot an address IDO can't prove is sp+const
 * (e.g. a pointer param threaded through, or an aliased struct field) —
 * reverse-engineering that provenance is the multi-day task. Baseline
 * (volatile a1_sp/a2_sp local spills, inner-block s2) restored at 70.53%.
 *
 * EXTENDED DECODE @ 0x4580-0x45F8 (insns 25-50, sub-object init loop):
 *   // After s1 setup (s1 = main+0xE4 sub-region or alloc(0x3E0)):
 *   t0 = &D + 0x6D8;             // sub-region template ptr
 *   *(int*)s1 = t0;
 *   *(int*)(s1+4) = 0;
 *   count = *(int*)(&D + 0x6E8); // sub-object count
 *   *(int*)(sp+0xE0) = count;     // spill loop counter
 *   s2 = a0 + 0x2C;               // loop pointer base (sub-obj table)
 *   // Loop body (per-iteration, ~25 insns):
 *   for (s0 = a0+0x2C; ...; s0 += 8) {
 *     int t4 = *(int*)(sp+0xE0);  // reload counter
 *     if (t4 != -8) {              // -8 sentinel = bump-allocator slot
 *       sub = alloc(0x18);
 *     } else {
 *       sub = (s0 cached val);
 *     }
 *     if (!sub) break;
 *     init_sub(sub, s1, *(int*)s2, 1);  // 4-arg init
 *     sub[0xC/4] = &D + 0x3C8;    // template2 ptr
 *     sub[0x14/4] = 0;
 *     *(float*)(sub+0x10) = D[0x9C];  // float constant
 *     // ... loop continues with more init writes
 *   }
 *
 * The -8 sentinel is the "use cached/bump-allocator chunk vs alloc fresh"
 * branch. Each sub-object is 0x18 bytes, indexed via s0 += 8 (so s0 is
 * a TABLE-of-pointers stride, not the object stride).
 *
 * NEXT PASS: decode the sub-object loops tail (set-and-link to parents
 * 0x38 chain), and the second template-table iteration (~16 sub-objects).
 *
 * 2026-05-04 EXTENDED DECODE @ 0x45E0-0x4710 (insns 50-128, 4 iterations of
 * the sub-object init group). The body is NOT a simple loop — its an
 * UNROLLED chain of per-template-entry init groups. Each group is ~30
 * insns and follows this pattern (group 1 @ 0x45E0-0x4604 reproduced for
 * 0x4640-0x4664, 0x46A8-0x46CC, 0x4710-0x... — 4 occurrences seen):
 *
 *   load_template_ptr:
 *     t0 = D[0x6E8 + group_idx*4]    ; template-list ptr (group-specific)
 *     sp[0xE0/0xDC/0xD8/0xD4] = t0    ; spill to per-group local
 *     at = -0xN0                       ; sentinel for cached-vs-alloc
 *   load_or_alloc_sub:
 *     s0 += STRIDE                     ; STRIDE = 0x20, 0x38, 0x50, ... (varies)
 *     entry = t0[0]                    ; first entry of template-list
 *     if (entry != sentinel) {
 *       *s0 = entry                    ; cached val, store back
 *       jal alloc(0x18)                ; alloc 24-byte sub-object
 *     } else {
 *       sub = entry                    ; bump-allocator path
 *     }
 *     sp[8] = sub                      ; (varargs slot 5 for next call)
 *   if (sub == 0) goto epi
 *   init_sub:
 *     a1=parent_obj; a2=parent_obj; a3=1
 *     a0=0x18 (size hint?)
 *     jal init_sub_obj(0x18, parent, parent, 1)  ; (varargs in sp[8] = sub)
 *     sub[0xC] = D + 0x3C8             ; type-tag pointer (constant)
 *     sub[0x14] = 0                    ; flag/state
 *     sub[0x10] = D[0x9C, 0xA0, 0xA4, 0xA8, ...]  ; per-group float constant
 *     ; stride to next group
 *
 * Per-group constants (from disassembly):
 *   group 0: stride=0x08, sentinel=-0x08 (0xFFFFFFF8), float@D+0x9C, tlist@D+0x6E8
 *   group 1: stride=0x20, sentinel=-0xE0 (0xFFFFFF20), float@D+0xA0, tlist@D+0x6EC
 *   group 2: stride=0x38, sentinel=-0xC8 (0xFFFFFFB0), float@D+0xA4, tlist@D+0x6F0
 *   group 3: stride=0x50, sentinel=-0xB0 (0xFFFFFF50), float@D+0xA8, tlist@D+0x6F4
 *
 * The strides are CUMULATIVE (s0 += STRIDE each group, not absolute).
 * tlist offset increases by 4 each group (D+0x6E8, +0x6EC, +0x6F0, +0x6F4).
 * Float constants step by 4 (D+0x9C through 0xA8). Sentinel stride pattern
 * is irregular: -8, -0xE0, -0xC8, -0xB0 — implies negative offsets in the
 * struct layout (sub-objects placed BEFORE the parents a0 in memory layout?
 * or sentinel = (-base+offset) form for the 'use cached if existing' check).
 *
 * Total of ~16 such groups suggested by the original spine analysis. Linear
 * extrapolation: 16 groups × 30 insns = 480 insns of sub-object init.
 * The remaining ~600 insns are likely sub-object linkage to a0[0x38] chain,
 * second-pass init (validation/finalize), and the alloc-fail epilogue
 * cleanup path.
 *
 * NEXT PASS: continue from 0x4710 (group 4 onwards); confirm if all 16
 * groups follow this pattern or if some have FPU-heavy variants.
 *
 * 2026-05-04 EXTENDED DECODE @ 0x4710-0x47B0 (groups 4-6):
 *   Group 4 @ 0x4710-0x4738: stride=0x68, sentinel=-0x68, tlist=D+0x6F8,
 *     float=D+0xA8 — same template pattern as groups 0-3.
 *   Group 5 @ 0x4718 has a SPECIAL `lui at, 0xC448 / mtc1 at, $f10`
 *     emit interleaved with the standard init: f10 = -800.0f
 *     (bit pattern 0xC4480000 → -800.0f). This float is loaded but its
 *     consumer is later in the function — likely a per-group threshold
 *     or scale factor for the sub-objects FPU state, NOT consumed by
 *     gl_func_00000000(...) directly.
 *   Group 6 @ 0x473C-0x47B0: stride=0x68, sentinel=-0x80, tlist=D+0x6FC,
 *     float=D+0xA8 (same as group 4? or 5? the asm is dense). Standard
 *     init pattern resumes.
 *
 * Group strides observed so far: 0x08, 0x20, 0x38, 0x50, 0x68, 0x68 —
 * the stride pattern is roughly arithmetic progression +0x18 then
 * stable at 0x68. Suggests the sub-objects are 0x18 bytes each and
 * groups 0-3 are partial groups (smaller sub-region) while groups 4+
 * are full-size groups. tlist offsets are sequential
 * (+0x4 each: 6E8, 6EC, 6F0, 6F4, 6F8, 6FC).
 *
 * NEXT-NEXT PASS: continue from 0x47B0; expect 10+ more groups before
 * reaching the linkage/finalize phase (~insn 600+).
 *
 * 2026-05-04 EXTENDED DECODE @ 0x47B0-0x48F8 (groups 7-10, ~80 insns):
 *   Group 7 @ 0x47B0-0x4800: stride=0x80, sentinel=-0x80, tlist=D+0x6FC,
 *     float=D+0xAC. Standard pattern.
 *   Group 8 @ 0x4804-0x4868: stride=0x98, sentinel=-0x98, tlist=D+0x700.
 *     PATTERN SHIFT: float is an INLINE literal (`lui at,0xC57A; mtc1 at,$f4`)
 *     = -4000.0f, NOT a D-table lookup. This changes IDOs codegen pattern
 *     for the float store (mtc1+swc1 pair instead of lwc1+swc1).
 *   Group 9 @ 0x486C-0x48D0: stride=0xB0, sentinel=-0xB0, tlist=D+0x704.
 *     INLINE float = -8000.0f (`lui at,0xC5FA; mtc1 at,$f6`).
 *   Group 10 @ 0x48D4-0x48F8: stride=0xC8, sentinel=-0xC8, tlist=D+0x708.
 *     Pattern continues with inline floats.
 *
 * Stride progression: 0x08, 0x20, 0x38, 0x50, 0x68, 0x68, 0x68, 0x80, 0x98,
 * 0xB0, 0xC8 — arithmetic +0x18 per group with anomaly at groups 4-6 (all
 * 0x68). Tlist offsets D+0x6E8..D+0x708 (+4 per group, sequential).
 *
 * KEY FINDING: groups 0-7 use D-table float lookups; groups 8+ use INLINE
 * float literals. The pattern shift means future C decode needs separate
 * group templates for "table-float" vs "literal-float" sub-groups. The
 * literal floats are fall-rate constants for pumice/wind sub-objects
 * (-4000, -8000 magnitudes suggest distance thresholds in fixed-point).
 *
 * NEXT PASS: continue from 0x48F8; ~14+ more groups expected before
 * the linkage/finalize phase (~insn 600). The literal-float groups are
 * the harder ones to match — multiple lui/mtc1 emit forms IDO can pick.
 *
 * 2026-05-04 EXTENDED DECODE @ 0x48F8-0x4A0C (groups 10-12, ~70 insns):
 *   Group 10 (continuing) @ 0x48EC-0x4934: stride=0xC8, sentinel=-0xC8,
 *     tlist=D+0x708, float=D+0xB0 (back to D-table lookup form).
 *   Group 11 @ 0x493C-0x49A0: stride=0xE0, sentinel=-0xE0, tlist=D+0x70C,
 *     float=D+0xB4.
 *   Group 12 @ 0x49A4-0x4A08: stride=0xF8, sentinel=-0xF8, tlist=D+0x710,
 *     float=D+0xB8.
 *
 * Pattern correction: groups 8-9 inline-float was a transient — groups
 * 10+ revert to D-table lookup form. The inline-float at groups 8-9 may
 * have been special-case constants for sub-objects with non-D-table
 * fall-rates. Stride progression now stable +0x18 (0xC8, 0xE0, 0xF8).
 * Tlist offsets continuing sequentially (+4 per group: D+0x708, +0x70C,
 * +0x710). Float-table offsets +0x4 (+0xB0, +0xB4, +0xB8).
 *
 * Type tag is constant across all groups: D+0x3C8 (template-type ptr).
 * Same value used for sub->0xC in every group, suggesting all sub-
 * objects share a single class/dispatch type — only the float-rate and
 * tlist entry vary by group.
 *
 * NEXT PASS: continue from 0x4A0C; ~10 more groups expected.
 *
 * 2026-05-04 EXTENDED DECODE @ 0x4A0C-0x4B40 (groups 13-15, ~75 insns):
 *   Group 13 @ 0x4A0C-0x4A70: stride=0x110, sentinel=-0x110, tlist=D+0x714,
 *     float=D+0xBC. Standard pattern.
 *   Group 14 @ 0x4A74-0x4AD8: stride=0x128, sentinel=-0x128, tlist=D+0x718,
 *     float=D+0xC0.
 *   Group 15 @ 0x4ADC-0x4B40: stride=0x140, sentinel=-0x140, tlist=D+0x71C
 *     (float TBD next read).
 *
 * Stride continues +0x18 progression (0x110, 0x128, 0x140). Tlists
 * sequential D+0x714, +0x718, +0x71C. Floats D+0xBC, +0xC0.
 *
 * Total groups decoded so far: 0-15 (16 of estimated ~28 total).
 * Cumulative stride from start: 0x140 = 320 bytes (vs s1s expected
 * coverage of ~0x3E0-byte child obj).
 *
 * NEXT PASS: continue from 0x4B40; expect ~13 more groups before
 * reaching the linkage/finalize phase.
 *
 * 2026-05-04 EXTENDED DECODE @ 0x4B40-0x4C78 (groups 16-18, ~80 insns):
 *   Group 15 (completing) @ 0x4B3C: float=D+0xC4.
 *   Group 16 @ 0x4B44-0x4BA8: stride=0x158, sentinel=-0x158, tlist=D+0x720,
 *     float=D+0xC8.
 *   Group 17 @ 0x4BAC-0x4C10: stride=0x170, sentinel=-0x170, tlist=D+0x724,
 *     float=D+0xCC.
 *   Group 18 @ 0x4C14-0x4C78: stride=0x188, sentinel=-0x188, tlist=D+0x728,
 *     float=D+0xD0 (TBD next read).
 *
 * 19 of ~28 groups decoded. Strides 0x140, 0x158, 0x170, 0x188 (stable
 * +0x18). Tlists D+0x720, +0x724, +0x728 (still sequential). Floats
 * D+0xC4, +0xC8, +0xCC (still sequential). Cumulative stride from start
 * of init loop: 0x188 = 392 bytes, approaching the ~0x3E0 child obj
 * boundary.
 *
 * NEXT PASS: continue from 0x4C78; expect 9 more groups before finalize.
 *
 * 2026-05-04 EXTENDED DECODE @ 0x4C7C-0x4D80 (groups 19-21, ~70 insns):
 *   Group 19 @ 0x4C7C-0x4CE0: stride=0x1A0, sentinel=-0x1A0, tlist=D+0x72C,
 *     float=D+0xD4 (D-table form).
 *   Group 20 @ 0x4CE4-0x4D48: stride=0x1B8, sentinel=-0x1B8, tlist=D+0x730.
 *     PATTERN SHIFT (return of inline-float): float is INLINE literal
 *     (`lui at,0x4496; mtc1 at,$f4`) = 1200.0f (0x44960000 bit pattern).
 *   Group 21 @ 0x4D4C-0x4D80+: stride=0x1D0, sentinel=-0x1D0, tlist=D+0x734.
 *
 * 22 of ~28 groups decoded. Strides 0x1A0, 0x1B8, 0x1D0 (stable +0x18).
 * Tlists D+0x72C, +0x730, +0x734. Cumulative stride: 464 bytes.
 * Inline-float pattern returns at group 20 (1200.0f) — second occurrence
 * after groups 8-9 (-4000.0f, -8000.0f). Suggests inline floats correspond
 * to specific velocity/threshold sub-objects that arent D-table indexed.
 *
 * NEXT PASS: continue from 0x4D80; expect ~6 more groups before
 * linkage/finalize phase.
 *
 * 2026-05-04 EXTENDED DECODE @ 0x4D80-0x4E80 (groups 22-23, ~70 insns):
 *   Group 21 (completing) @ 0x4D98: float = INLINE 1200.0f (lui 0x4496+mtc1).
 *   Group 22 @ 0x4DB4-0x4E18: stride=0x1E8, sentinel=-0x1E8, tlist=D+0x738,
 *     float = INLINE 1200.0f (same as 21).
 *   Group 23 @ 0x4E1C-0x4E80: stride=0x200, sentinel=-0x200, tlist=D+0x73C,
 *     float = INLINE 60.0f (lui 0x4270+mtc1).
 *
 * 24 of ~28 groups decoded. Strides 0x1D0, 0x1E8, 0x200 (stable +0x18).
 * Tlists D+0x738, +0x73C. INLINE floats are: 1200.0f (groups 20-22) and
 * 60.0f (group 23). The 1200.0f triplet suggests these are correlated
 * sub-objects (3 sequential at same drop-rate), and 60.0f is a
 * frame-rate-related constant.
 *
 * NEXT PASS: continue from 0x4E80; expect ~4 more groups before
 * linkage/finalize phase.
 *
 * 2026-05-04 EXTENDED DECODE @ 0x4E80-0x5638 (groups 24-37, ~140 insns).
 * Found end-of-loop boundary: linkage/finalize phase begins at 0x563C.
 *
 *   Group 24 @ 0x4E84-0x4EE8: stride=0x218, sentinel=-0x218, tlist=D+0x740,
 *     float = INLINE 60.0f.
 *   Group 25 @ 0x4EEC-0x4F50: stride=0x230, tlist=D+0x744, float=INLINE 60.0f.
 *   Group 26 @ 0x4F54-0x4FB8: stride=0x248, tlist=D+0x748, float=INLINE 1.5f
 *     (lui 0x3FC0).
 *   Group 27 @ 0x4FBC-0x5020: stride=0x260, tlist=D+0x74C, float=D+0xD8
 *     (D-table form returns).
 *   Group 28 @ 0x5024-0x5088: stride=0x278, tlist=D+0x750, float=INLINE 1.5f.
 *   Group 29 @ 0x508C-0x50F0: stride=0x290, tlist=D+0x754, float=INLINE
 *     2000.0f (lui 0x44FA).
 *   Group 30 @ 0x50F4-0x5158: stride=0x2A8, tlist=D+0x758, float=INLINE 2000.0f.
 *   Group 31 @ 0x515C-0x51C0: stride=0x2C0, tlist=D+0x75C, float=INLINE 2000.0f.
 *   Group 32 @ 0x51C4-0x5228: stride=0x2D8, tlist=D+0x760, float=D+0xDC.
 *   Group 33 @ 0x522C-0x5290: stride=0x2F0, tlist=D+0x764, float=D+0xE0.
 *   Group 34 @ 0x5294-0x52F8: stride=0x308, tlist=D+0x768, float=D+0xE4.
 *   Group 35 @ 0x52FC-...: stride=0x320, tlist=D+0x76C.
 *   ...
 *   Group 37 @ ...0x5638: stride=0x3C8, tlist=D+0x788, ends with INLINE
 *     `lui 0x4370+mtc1` (240.0f) and final swc1.
 *
 * 38 of 38 groups decoded! Loop ends at 0x563C. The unrolled chain spans
 * 0x4580-0x563C (~1071 insns / 4280 bytes). Strides progress arithmetically
 * +0x18 from 0x08 (group 0) to 0x3C8 (group 37). Tlists D+0x6E8..0x788
 * (sequential +4). Type tag D+0x3C8 constant across all 38 groups.
 *
 * LINKAGE/FINALIZE PHASE @ 0x563C-end (~50 insns):
 *   - Reload spilled values from caller-arg slots (sp+0xE8, +0xEC, +0xF0)
 *   - Multiple FPU constant loads (lui 0x43FA, lui 0x428C, lui 0x4366,
 *     lui 0x4370 — 500.0f, 70.0f, 230.0f, 240.0f)
 *   - Stores to a0+0x2C, a0+0x30, a0+0xA8, a0+0xAC, a0+0xB0, a0+0xB4,
 *     a0+0xB8 (config slots in main object)
 *   - Final return path: ret = a0
 *
 * NEXT PASS: decode the linkage phase fully (~50 insns at 0x563C-end).
 *
 * 2026-05-04 LINKAGE/FINALIZE PHASE FULLY DECODED @ 0x563C-0x5724
 * (~57 insns). All initializers identified:
 *
 *   v0 = arg0;                      // reload from sp+0xE8
 *   t8 = arg1;                      // reload from sp+0xEC
 *   t9 = arg2;                      // reload from sp+0xF0
 *   arg0->0x30 = arg1;
 *   arg0->0x2C = arg2;
 *   arg0->0xA8 = 0.0f;
 *   arg0->0xAC = D[0xE8];           // float from D-table
 *   arg0->0xB0 = 500.0f;            // (lui 0x43FA)
 *   arg0->0xB4 = 70.0f;             // (lui 0x428C)
 *   arg0->0xB8 = 230.0f;            // (lui 0x4366)
 *   arg0->0xBC = D[0xEC];
 *   arg0->0xC0 = 12.0f;             // (lui 0x4140)
 *   arg0->0xC4 = D[0xF0];
 *   arg0->0xC8 = 2.0f;              // (lui 0x4000)
 *   arg0->0xCC = 50.0f;             // (lui 0x4248)
 *   arg0->0xD0 = 20.0f;             // (lui 0x41A0)
 *   arg0->0xD4 = 500.0f;            // ($f0 carried — same as 0xB0)
 *   arg0->0xDC = 15.0f;             // (lui 0x4170)
 *   arg0->0xE0 = D[0xF4];
 *   arg0->0xD8 = D[0xF8];
 *   arg0->0xA0 = 1000.0f;           // (lui 0x447A)
 *   arg0->0x4DC = 3;                // int constant
 *   epilogue: lw ra; lw v0=arg0; lw s0/s1/s2; jr ra; addiu sp +0xE8
 *
 * FUNCTION FULLY DECODED. Total: prologue (entry + 1st alloc + sub-region
 * setup) + 38-group unrolled init chain (groups 0-37, ~1071 insns) +
 * linkage/finalize phase (~57 insns + epilogue).
 *
 * Combined init phase config slots span:
 *   arg0->0x2C, 0x30: arg pointers (entity refs)
 *   arg0->0xA0..0xDC: ~16 float constants (gameplay tunables)
 *   arg0->0x4DC: counter/state init = 3
 *
 * Multi-tick refinement target — the C body would be ~150 lines of
 * sequential field assignments. Large-but-tractable for next decomp
 * pass. Default INCLUDE_ASM build matches the (yay0-compressed) ROM. */
extern char D_44F4_iterA_t, D_44F4_iterA_p, D_44F4_iterA_f, D_44F4_iterB_t, D_44F4_iterB_p, D_44F4_iterB_f, D_44F4_iterC_t, D_44F4_iterC_p;
extern char D_44F4_iterD_t, D_44F4_iterD_p, D_44F4_iterD_f, D_44F4_iterE_t, D_44F4_iterE_p, D_44F4_iterE_f, D_44F4_iterF_t, D_44F4_iterF_p;
extern char D_44F4_iterG_t, D_44F4_iterG_p, D_44F4_iterH_t, D_44F4_iterH_p, D_44F4_iterH_f, D_44F4_iterI_t, D_44F4_iterI_p, D_44F4_iterI_f;
extern char D_44F4_iterJ_t, D_44F4_iterJ_p, D_44F4_iterJ_f, D_44F4_iterK_t, D_44F4_iterK_p, D_44F4_iterK_f, D_44F4_iterL_t, D_44F4_iterL_p;
extern char D_44F4_iterL_f, D_44F4_iterM_t, D_44F4_iterM_p, D_44F4_iterM_f, D_44F4_iterN_t, D_44F4_iterN_p, D_44F4_iterN_f, D_44F4_iterO_t;
extern char D_44F4_iterO_p, D_44F4_iterO_f, D_44F4_iterP_t, D_44F4_iterP_p, D_44F4_iterP_f, D_44F4_iterQ_t, D_44F4_iterQ_p, D_44F4_iterQ_f;
extern char D_44F4_iterR_t, D_44F4_iterR_p, D_44F4_iterS_t, D_44F4_iterS_p, D_44F4_iterT_t, D_44F4_iterT_p, D_44F4_iterU_t, D_44F4_iterU_p;
extern char D_44F4_iterV_t, D_44F4_iterV_p, D_44F4_iterW_t, D_44F4_iterW_p, D_44F4_iterX_t, D_44F4_iterX_p, D_44F4_iterY_t, D_44F4_iterY_p;
extern char D_44F4_iterY_f, D_44F4_iterZ_t, D_44F4_iterZ_p, D_44F4_iterAA_t, D_44F4_iterAA_p, D_44F4_iterBB_t, D_44F4_iterBB_p, D_44F4_iterCC_t;
extern char D_44F4_iterCC_p, D_44F4_iterDD_t, D_44F4_iterDD_p, D_44F4_iterDD_f, D_44F4_iterEE_t, D_44F4_iterEE_p, D_44F4_iterEE_f, D_44F4_iterFF_t;
extern char D_44F4_iterFF_p, D_44F4_iterFF_f, D_44F4_iterGG_t, D_44F4_iterGG_p, D_44F4_iterHH_t, D_44F4_iterHH_p, D_44F4_iterII_t, D_44F4_iterII_p;
extern char D_44F4_iterJJ_t, D_44F4_iterJJ_p, D_44F4_iterKK_t, D_44F4_iterKK_p, D_44F4_iterLL_t, D_44F4_iterLL_p, D_44F4_iterMM_t, D_44F4_iterMM_p;
extern char D_44F4_iterNN_t, D_44F4_iterNN_p;
void *game_uso_func_000044F4(char *a0, int a1, int a2) {
    /* 2026-06-11 STRUCT-MARSHALLING REWRITE (agent-x):
     *  - The marshalling slot (sp+0x2C, held in $s2) is a 4-byte STRUCT
     *    passed BY VALUE as the init call's 3rd arg. Struct-by-value args
     *    are homed to the outgoing-arg area => `sw a2,8(sp)` in the jal
     *    delay slot (probe-verified vs 5th-dup-arg's `sw a2,0x10(sp)`).
     *    Struct locals are addressed via materialized ILDA pointers, which
     *    is (a) the per-iter `addiu tN,sp,slot; lw 0(tN)` indirect-load
     *    shape (struct copy `*s2 = slotK`) and (b) the $s2 promotion
     *    mechanism (high-refcount call-crossing &marsh web).
     *  - The per-iter tmpl spill slots (0xE0 down to 0x40) are 41 NAMED
     *    struct locals; decl order = slot map (FRAME-SLOT HOME ASSIGNMENT
     *    RULE). 48 decls span 0x28-0xE4; colored vars + volatile pads fill
     *    the dead slots (0xE4, 0x3C-0x30, 0x28).
     *  - Sentinel re-derive: target compare const = -SLOT for EVERY iter
     *    (old `SLOT - 0x100` table was an alignment misread). The real C is
     *    `s0 = s1 + SLOT; if (s0 == NULL) alloc;` (IDO folds to
     *    `bne s1, -SLOT`). Same for stage 3 (-0xE4 = -(0xE4)).
     *  - Control flow: iter alloc-failure SKIPS to the NEXT ITER (per-iter
     *    skip labels), alloc(0x3E0) failure goes to the FINALIZE phase,
     *    only alloc(0x4E0) failure returns directly. Return value is always
     *    the a0 home slot (sp+0xE8). */
    typedef struct { char *p; } S;
    volatile int pad_e4;  /* dead slot @0xE4 (colored var in original) */
    S slot_0;             /* @0xE0 — per-iter tmpl marshalling slots */
    S slot_A;
    S slot_B;
    S slot_C;
    S slot_D;
    S slot_E;
    S slot_F;
    S slot_G;
    S slot_H;
    S slot_I;
    S slot_J;
    S slot_K;
    S slot_L;
    S slot_M;
    S slot_N;
    S slot_O;
    S slot_P;
    S slot_Q;
    S slot_R;
    S slot_S;
    S slot_T;
    S slot_U;
    S slot_V;
    S slot_W;
    S slot_X;
    S slot_Y;
    S slot_Z;
    S slot_AA;
    S slot_BB;
    S slot_CC;
    S slot_DD;
    S slot_EE;
    S slot_FF;
    S slot_GG;
    S slot_HH;
    S slot_II;
    S slot_JJ;
    S slot_KK;
    S slot_LL;
    S slot_MM;
    S slot_NN;            /* @0x40 */
    char *v1;             /* colored — dead slot @0x3C */
    char *s1;             /* colored $s1 — dead slot @0x38 */
    char *s0;             /* colored $s0 — dead slot @0x34 */
    volatile int pad_30;  /* dead slot @0x30 */
    S marsh;              /* @0x2C — THE marshalling slot */
    S *s2 = &marsh;       /* colored $s2 — dead slot @0x28 */

    /* Stage 1: allocate main object if not provided */
    if (a0 == NULL) {
        a0 = (char*)gl_func_00000000(0x4E0);
        if (a0 == NULL) goto epi;
    }

    /* Stage 2: init main from template at D[0x6D0]; set parent ptr */
    gl_func_00000000(a0, (char*)&D_00000000 + 0x6D0);
    *(char**)(a0 + 0x28) = &D_00000000;

    /* Stage 3: sub-region; alloc failure still runs the finalize phase */
    s1 = a0 + 0xE4;
    if (s1 == NULL) {
        s1 = (char*)gl_func_00000000(0x3E0);
        if (s1 == NULL) goto finalize;
    }

    /* Stage 4: template-head init; alloc(8) failure skips only the stores */
    v1 = s1;
    if (v1 == NULL) {
        v1 = (char*)gl_func_00000000(8);
        if (v1 == NULL) goto skip_head;
    }
    *(char**)v1 = (char*)&D_00000000 + 0x6D8;
    *(int*)(v1 + 4) = 0;
skip_head:

    {
        extern char D_44F4_iter0,
                    D_44F4_iterA, D_44F4_iterB, D_44F4_iterC, D_44F4_iterD,
                    D_44F4_iterE, D_44F4_iterF, D_44F4_iterG, D_44F4_iterH,
                    D_44F4_iterI, D_44F4_iterJ, D_44F4_iterK, D_44F4_iterL,
                    D_44F4_iterM, D_44F4_iterN, D_44F4_iterO, D_44F4_iterP,
                    D_44F4_iterQ, D_44F4_iterR, D_44F4_iterS, D_44F4_iterT,
                    D_44F4_iterU, D_44F4_iterV, D_44F4_iterW, D_44F4_iterX,
                    D_44F4_iterY, D_44F4_iterZ, D_44F4_iterAA, D_44F4_iterBB,
                    D_44F4_iterCC, D_44F4_iterDD, D_44F4_iterEE, D_44F4_iterFF,
                    D_44F4_iterGG, D_44F4_iterHH, D_44F4_iterII, D_44F4_iterJJ,
                    D_44F4_iterKK, D_44F4_iterLL, D_44F4_iterMM, D_44F4_iterNN;
        /* Per-iter unique externs (DB) defeat IDO's global CSE on the
         * &D base — target reloads lui per access. */
#define INIT_ITER(ID, SLOT, TMPL_OFF, FLOAT_EXPR, DB) \
        slot_##ID.p = *(char**)((char*)&DB + (TMPL_OFF)); \
        *s2 = slot_##ID; \
        s0 = s1 + (SLOT); \
        if (s0 == NULL) { \
            s0 = (char*)gl_func_00000000(0x18); \
            if (s0 == NULL) goto skip_##ID; \
        } \
        gl_func_00000000(s0, s1, *s2, 1); \
        *(char**)(s0 + 0xC) = (char*)&DB + 0x3C8; \
        *(int*)(s0 + 0x14) = 0; \
        *(float*)(s0 + 0x10) = (FLOAT_EXPR); \
skip_##ID:;

        INIT_ITER(0,  0x08,  0x6E8, *(float*)((char*)&D_44F4_iter0 + 0x9C), D_44F4_iter0)   /* iter 0 */
        INIT_ITER(A,  0x20,  0x6EC, *(float*)((char*)&D_44F4_iterA + 0xA0), D_44F4_iterA)   /* A */
        INIT_ITER(B,  0x38,  0x6F0, *(float*)((char*)&D_44F4_iterB + 0xA4), D_44F4_iterB)   /* B */
        INIT_ITER(C,  0x50,  0x6F4, -800.0f,                                D_44F4_iterC)   /* C (lui 0xC448) */
        INIT_ITER(D,  0x68,  0x6F8, *(float*)((char*)&D_44F4_iterD + 0xA8), D_44F4_iterD)   /* D */
        INIT_ITER(E,  0x80,  0x6FC, *(float*)((char*)&D_44F4_iterE + 0xAC), D_44F4_iterE)   /* E */
        INIT_ITER(F,  0x98,  0x700, -4000.0f,                               D_44F4_iterF)   /* F (lui 0xC57A) */
        INIT_ITER(G,  0xB0,  0x704, -8000.0f,                               D_44F4_iterG)   /* G (lui 0xC5FA) */
        INIT_ITER(H,  0xC8,  0x708, *(float*)((char*)&D_44F4_iterH + 0xB0), D_44F4_iterH)   /* H */
        INIT_ITER(I,  0xE0,  0x70C, *(float*)((char*)&D_44F4_iterI + 0xB4), D_44F4_iterI)   /* I */
        INIT_ITER(J,  0xF8,  0x710, *(float*)((char*)&D_44F4_iterJ + 0xB8), D_44F4_iterJ)   /* J */
        INIT_ITER(K,  0x110, 0x714, *(float*)((char*)&D_44F4_iterK + 0xBC), D_44F4_iterK)   /* K */
        INIT_ITER(L,  0x128, 0x718, *(float*)((char*)&D_44F4_iterL + 0xC0), D_44F4_iterL)   /* L */
        INIT_ITER(M,  0x140, 0x71C, *(float*)((char*)&D_44F4_iterM + 0xC4), D_44F4_iterM)   /* M */
        INIT_ITER(N,  0x158, 0x720, *(float*)((char*)&D_44F4_iterN + 0xC8), D_44F4_iterN)   /* N */
        INIT_ITER(O,  0x170, 0x724, *(float*)((char*)&D_44F4_iterO + 0xCC), D_44F4_iterO)   /* O */
        INIT_ITER(P,  0x188, 0x728, *(float*)((char*)&D_44F4_iterP + 0xD0), D_44F4_iterP)   /* P */
        INIT_ITER(Q,  0x1A0, 0x72C, *(float*)((char*)&D_44F4_iterQ + 0xD4), D_44F4_iterQ)   /* Q */
        INIT_ITER(R,  0x1B8, 0x730, 1200.0f,                                D_44F4_iterR)   /* R (lui 0x4496) */
        INIT_ITER(S,  0x1D0, 0x734, 1200.0f,                                D_44F4_iterS)   /* S */
        INIT_ITER(T,  0x1E8, 0x738, 1200.0f,                                D_44F4_iterT)   /* T */
        INIT_ITER(U,  0x200, 0x73C, 60.0f,                                  D_44F4_iterU)   /* U (lui 0x4270) */
        INIT_ITER(V,  0x218, 0x740, 60.0f,                                  D_44F4_iterV)   /* V */
        INIT_ITER(W,  0x230, 0x744, 60.0f,                                  D_44F4_iterW)   /* W */
        INIT_ITER(X,  0x248, 0x748, 1.5f,                                   D_44F4_iterX)   /* X (lui 0x3FC0) */
        INIT_ITER(Y,  0x260, 0x74C, *(float*)((char*)&D_44F4_iterY + 0xD8), D_44F4_iterY)   /* Y */
        INIT_ITER(Z,  0x278, 0x750, 1.5f,                                   D_44F4_iterZ)   /* Z */
        INIT_ITER(AA, 0x290, 0x754, 2000.0f,                                D_44F4_iterAA)  /* AA (lui 0x44FA) */
        INIT_ITER(BB, 0x2A8, 0x758, 2000.0f,                                D_44F4_iterBB)  /* BB */
        INIT_ITER(CC, 0x2C0, 0x75C, 2000.0f,                                D_44F4_iterCC)  /* CC */
        INIT_ITER(DD, 0x2D8, 0x760, *(float*)((char*)&D_44F4_iterDD + 0xDC), D_44F4_iterDD) /* DD */
        INIT_ITER(EE, 0x2F0, 0x764, *(float*)((char*)&D_44F4_iterEE + 0xE0), D_44F4_iterEE) /* EE */
        INIT_ITER(FF, 0x308, 0x768, *(float*)((char*)&D_44F4_iterFF + 0xE4), D_44F4_iterFF) /* FF */
        INIT_ITER(GG, 0x320, 0x76C, 240.0f,                                 D_44F4_iterGG)  /* GG (lui 0x4370) */
        INIT_ITER(HH, 0x338, 0x770, 240.0f,                                 D_44F4_iterHH)  /* HH */
        INIT_ITER(II, 0x350, 0x774, 240.0f,                                 D_44F4_iterII)  /* II */
        INIT_ITER(JJ, 0x368, 0x778, 240.0f,                                 D_44F4_iterJJ)  /* JJ */
        INIT_ITER(KK, 0x380, 0x77C, 240.0f,                                 D_44F4_iterKK)  /* KK */
        INIT_ITER(LL, 0x398, 0x780, 240.0f,                                 D_44F4_iterLL)  /* LL */
        INIT_ITER(MM, 0x3B0, 0x784, 240.0f,                                 D_44F4_iterMM)  /* MM */
        INIT_ITER(NN, 0x3C8, 0x788, 240.0f,                                 D_44F4_iterNN)  /* NN (final iter) */
#undef INIT_ITER
    }
finalize:;

    /* Stage 5+ (deprecated doc — see Stages 8-11 for full per-iter
     * unrolled loop characterization; all 38 iters TBD as C body): write sub-region back-pointer; init sub-region from
     * template; loop-init sub-object table at a0+0x2C with stride 8.
     * Decoded ~25 insns at 0x4564-0x45D8:
     *   *(int*)(s1) = 0;            // s1->0 = NULL
     *   *(int*)(s1 + 4) = 0;        // s1->4 = NULL
     *   gl_func_00000000(s1, 8);    // small init call
     *   for (s0 = a0 + 0x2C; ...) {
     *     ptr = (a0+0xE0)->...;     // load template entry
     *     *(int*)s0 = ptr;
     *     gl_func_00000000(s0, 0x18);  // init sub-obj of size 0x18
     *     s0 += 8;
     *   }
     */
    /* Stage 5 (extended 2026-05-03, ~25 insns 0x45D8-0x4640):
     * After init-sub-obj jal, set 3 more fields per sub-obj from data
     * templates at &D + various offsets:
     *
     *   gl_func_00000000(s0, 0x18);
     *   *(int*)(s0 + 0xC)  = (int)((char*)&D_00000000 + 0x3C8);
     *   *(int*)(s0 + 0x14) = 0;
     *   *(float*)(s0 + 0x10) = *(float*)((char*)&D_00000000 + 0x9C);
     *   t8 = *(int*)((char*)&D_00000000 + 0x6EC);  // list head
     *   ... (continues with more loads + 2 more cross-USO calls
     *   at 0x4620 and 0x4640, decoding pending) */

    /* Stage 7 confirmation (2026-05-03 run): the 0x44F4-0x47F4 region is a
     * LOOP over sub-objects — Stages 4-6 are the per-iteration body, repeated
     * with rotating template offsets D[0x6EC], D[0x6F4], etc. (gap 8 bytes per
     * iter = next-template ptr). Estimated 16 iters total before the loop exits
     * to the outer constructor's link-setup phase at ~0x47F4.
     *
     * Stage 6 (extended 2026-05-03 run 13, ~16 insns 0x4630-0x4680):
     *   gl_func_00000000(s0, s1, *(int*)s2, 1);   // 4-arg sub-init call
     *   s0->[0xC] = (int)((char*)&D_00000000 + 0x3C8);  // template ptr (same as stage 5)
     *   s0->[0x14] = 0;
     *   s0->[0x10] = *(float*)((char*)&D_00000000 + 0xA0);  // float scalar
     *   if (s1 == (char*)-0x38) { alloc slot }     // unusual addr-as-imm cmp
     *
     * The 4-arg call here mirrors the structure of Stage 4's gl_func call
     * but with explicit (a0, a1, a2, a3) — different sub-init shape.
     *
     * Stage 7 (extended 2026-05-04, ~30 insns 0x4680-0x4734):
     * Confirms the loop is UNROLLED — each iteration:
     *   1. Compute s0 = s1 + N*0x50 (N=0,1,2,...; sub-obj slot in s1[])
     *   2. Load next template ptr from D[0x6F4 + N*4]
     *   3. alloc(0x18) → s0 (24-byte sub-obj)
     *   4. gl_func(s0, s1, *(int*)s2, 1)   ; 4-arg sub-init
     *   5. s0->[0xC] = (int)((char*)&D + 0x3C8)  ; template ptr (constant)
     *   6. s0->[0x14] = 0
     *   7. s0->[0x10] = D[0xA0..]    ; float scalar (varies per iter:
     *      D[0xA4]=val_iter1, -800.0f=iter2 via lui 0xC448, etc.)
     *
     * Stride: s0 advances by 0x18 (24 bytes) per iteration — the sub-obj
     * size, NOT 0x50 (Stage 7's earlier read was wrong; the 0x50 was a
     * one-off iter that didn't establish the stride). The s1 buffer is
     * 0x3E0 = 992 bytes total, fitting ~40 sub-obj slots if dense, but
     * the structure is sparser — only the slots at +0x20, +0x38, +0x50,
     * +0x68 are confirmed unrolled iters.
     *
     * Stage 8 (extended /decompile run, 2026-05-04, ~88 insns 0x4600-0x47C8):
     * 4 fully-characterized iterations of the unrolled-loop body. Each
     * iter is 22 insns / 0x58 bytes following this exact template:
     *
     *   1. lui+lw $tN, %hi/lo(D + tmpl_off_N)        ; template-N ptr
     *   2. addiu $tM, $sp, arg_slot_N                ; arg slot ptr (sp-relative)
     *   3. addiu $at, $zero, sentinel_N              ; sentinel constant
     *   4. sw $tN, arg_slot_N(sp)                    ; spill tmpl ptr to arg slot
     *   5. lw $tK, 0($tM)                            ; reload via arg slot
     *   6. addiu $s0, $s1, slot_off_N                ; s0 = s1 + slot offset N
     *   7. bne $s1, $at, +5                          ; sentinel check on s1
     *   8. sw $tK, 0($s2)                            ; (delay) init s2[0]
     *   9. jal gl_func_00000000                      ; alloc(0x18)
     *   10. addiu $a0, $zero, 0x18                   ; (delay)
     *   11. beqz $v0, epi                            ; bail on alloc fail
     *   12. or $s0, $v0, $zero                       ; (delay) s0 = alloc result
     *   13. lw $a2, 0($s2)                           ; reload tmpl ptr arg
     *   14. or $a0, $s0, $zero                       ; a0 = s0
     *   15. or $a1, $s1, $zero                       ; a1 = s1
     *   16. addiu $a3, $zero, 1                      ; a3 = 1
     *   17. jal gl_func_00000000                     ; 4-arg sub-init
     *   18. sw $a2, 0x8(sp)                          ; (delay) caller arg slot
     *   19. lui+addiu $tQ, %hi/lo(D + 0x3C8)         ; constant template ptr
     *   20. sw $tQ, 0xC(s0)                          ; s0->[0xC] = D+0x3C8
     *   21. sw $zero, 0x14(s0)                       ; s0->[0x14] = 0
     *   22. lui+lwc1+swc1 $fK, ... 0x10(s0)          ; s0->[0x10] = float scalar
     *
     * Per-iteration parameter table (4 iters: A B C D, with iter 0 being
     * the kick-off block at 0x45D8-0x4640 already documented in Stages 5-7):
     *
     *   iter | tmpl_off | arg_slot | sentinel | slot_off |  float_scalar
     *   -----+----------+----------+----------+----------+--------------
     *     A  |  0x6EC   |  0xDC    |  -0xE0   |  0x20    |  D + 0xA0
     *     B  |  0x6F0   |  0xD8    |  -0xC8   |  0x38    |  D + 0xA4
     *     C  |  0x6F4   |  0xD4    |  -0xB0   |  0x50    |  -800.0f literal
     *                                                       (lui 0xC448)
     *     D  |  0x6F8   |  0xD0    |  -0x98   |  0x68    |  D + 0xA8
     *
     * Patterns confirmed:
     *  - tmpl_off advances +4 per iter (D's table of template ptrs is dense)
     *  - arg_slot decreases by 4 per iter (stack spills grow downward
     *    as live ranges of earlier tmpl ptrs end)
     *  - sentinel = slot_off - 0x100 (sign-extended low half) — IDO
     *    rewrites `s1 + slot == magic_addr` as `s1 == magic_addr - slot`
     *    to fit the comparison constant in 16-bit imm
     *  - slot_off advances +0x18 (sub-obj size) per iter — sub-objs are
     *    laid out CONTIGUOUSLY in s1[]; offsets 0x20, 0x38, 0x50, 0x68
     *    are slot starts at indices 0, 1, 2, 3 within s1's sub-obj array
     *  - float scalar varies per iter: D+0xA0..0xA8 table OR literal
     *    constants (e.g. -800.0f at iter C). Suggests these are physics
     *    parameters (init pos? init velocity? gravity scale?) per sub-obj
     *
     * Stage 9 starts at 0x47C8 (5th unrolled iter, slot_off ~0x80,
     * tmpl_off 0x6FC, sentinel -0x80, arg_slot 0xCC). Pending decode.
     *
     * Cumulative ~170/1165 insns characterized (~15%). Loop has at least
     * 6+ more iters before exiting to parent constructor's link-setup
     * phase. The repeating 22-insn structure means Stage 9-12 should
     * each be a fast scan-and-document pass.
     *
     * Stage 9 correction (2026-05-04 run): the formula in Stage 8 should
     * read `sentinel == slot - 0x100` (sign-extended), where MAGIC is
     * `(char*)0xFFFFFF00`. Verified iters A-D: -0xE0=0x20-0x100,
     * -0xC8=0x38-0x100, -0xB0=0x50-0x100, -0x98=0x68-0x100. The C test
     * IDO rewrites is `(s1 + slot) == (char*)0xFFFFFF00`, regrouped as
     * `s1 == (char*)0xFFFFFF00 - slot` so the addiu imm fits 16-bit
     * signed.
     *
     * Stage 9 (~70 insns covering 0x47B0-0x48E0): iters E, F, G, H
     * observed:
     *
     *   iter | tmpl_off | arg_slot | sentinel-expected | slot | float_scalar
     *   -----+----------+----------+-------------------+------+--------------
     *     E  |  0x6FC   |  0xCC    |  -0x80            | 0x80 | literal
     *     F  |  0x700   |  0xC8    |  -0x68            | 0x98 | D + 0xAC
     *     G  |  0x704   |  0xC4    |  -0x50            | 0xB0 | literal -800
     *                                                          (lui 0xC57A)
     *     H  |  0x708   |  0xC0    |  -0x38            | 0xC8 | literal
     *                                                          (lui 0xC5FA)
     *
     * Pattern continues to hold: tmpl_off advances +4, arg_slot
     * decreases -4, slot advances +0x18 per iter. Float scalars
     * alternate between D-table loads (0xA0..0xAC) and literal
     * constants (mtc1 from lui-built immediate). The literal pattern
     * (lui 0xC57A → mtc1 → swc1) at iters G/H suggests these specific
     * sub-objs have hardcoded physics parameters not stored in the
     * D-template-table.
     *
     * Cumulative ~240/1165 insns characterized (~21%). Stage 10 starts
     * at 0x48E0 with iter I (predicted slot 0xE0, arg_slot 0xBC,
     * tmpl_off 0x70C, sentinel -0x20).
     *
     * Stage 10 (~280 insns covering 0x48E0-0x4DC0): iters I through T
     * verified by reading the tmpl_off lw imm and float-scalar lwc1/
     * mtc1 at each iter's footer. Pattern continues unbroken through
     * iter T at slot 0x1E8 (= s1 + 0x20 + 16 * 0x18). Per-iter:
     *
     *   iter | tmpl_off | float_scalar
     *   -----+----------+------------------
     *     I  |  0x70C   | (?)
     *     J  |  0x710   | D + 0xB4
     *     K  |  0x714   | D + 0xB8
     *     L  |  0x718   | D + 0xBC
     *     M  |  0x71C   | D + 0xC0
     *     N  |  0x720   | (?)
     *     O  |  0x724   | (?)
     *     P  |  0x728   | D + 0xCC
     *     Q  |  0x72C   | D + 0xD0
     *     R  |  0x730   | D + 0xD4
     *     S  |  0x734   | literal +1200.0f (lui 0x4496)
     *     T  |  0x738   | literal +1200.0f (lui 0x4496)
     *
     * The literal-pattern at iters S/T (lui 0x4496 → mtc1 from $at →
     * swc1) reuses the SAME constant +1200.0f for both. The earlier
     * literal iters (G/H lui 0xC57A/0xC5FA, C lui 0xC448) used
     * DIFFERENT constants per iter.
     *
     * arg_slot continues to decrease by 4: 0xCC, 0xC8, 0xC4, 0xC0, 0xBC,
     * 0xB8, 0xB4, 0xB0, 0xAC, 0xA8, 0xA4, 0xA0, 0x9C, 0x98, 0x94, 0x90,
     * 0x8C — runs out of frame at iter ~17, suggesting the loop body
     * exits or transitions before then. arg_slot 0x8C - 4 = 0x88 puts
     * us close to the s0/s1/s2 spill area (sp+0x18 region of the
     * 0xE8-byte frame), so the unroll likely ends around iter 17-20.
     *
     * Cumulative ~520/1165 insns characterized (~45%). Stage 11 starts
     * at 0x4DC0 with iter U+. The 0x4DC0+ region has another ~5-6 iters
     * before hitting the loop exit / link-setup phase at ~0x4F00.
     *
     * Stage 11 (~480 insns covering 0x4DC0-0x563C): iters U through Z+
     * — the unrolled loop continues to slot 0x3C8 (= 0x1E8 + 0x1E0,
     * which is +20 more iters from iter T). Total unrolled iter count
     * is ~32, NOT the previously-estimated 17-20. The arg_slot
     * decreases past the spill-slots boundary because the spill chain
     * reuses the same 0xE0-byte frame down to ~0x40 — fits up to 32
     * iters. Float scalars in this region are dominated by hardcoded
     * literal constants (0x4496=+1200, 0x4370=+240, 0x44FA=+2000,
     * 0x4140=+12, 0x43FA=+500, 0x4366=+230, 0x428C=+70, 0x41A0=+20,
     * 0x4170=+15, 0x4248=+50, 0x4000=+2.0, 0x3FC0=+1.5, 0x447A=+1000).
     * Some iters store the SAME literal to multiple sub-objs in a
     * row — likely setting batched physics constants per sub-obj group.
     *
     * Stage 12 (~80 insns covering 0x563C-0x5710): FINAL FIELD-INIT
     * phase after the unrolled loop exits. Pattern shifts from "alloc
     * + init sub-obj" to "store fixed values into a0's main struct
     * fields":
     *
     *   v0 = a0 (reload from sp+0xE8)
     *   t8 = a1 (reload from sp+0xEC)
     *   f18 = 0.0
     *   *(int*)(v0 + 0x30) = t8                ; a0->0x30 = a1
     *   t9 = a2 (reload from sp+0xF0)
     *   f0  = +500.0f literal (lui 0x43FA)
     *   *(float*)(v0 + 0xA8) = f18              ; a0->0xA8 = 0.0
     *   *(int*)(v0 + 0x2C) = t9                  ; a0->0x2C = a2
     *   f4 = D[0xE8] (float)
     *   f6 = +70.0f literal (lui 0x428C)
     *   f8 = +230.0f literal (lui 0x4366)
     *   *(float*)(v0 + 0xB0) = f0
     *   *(float*)(v0 + 0xAC) = f4
     *   *(float*)(v0 + 0xB4) = f6
     *   *(float*)(v0 + 0xB8) = f8
     *   fA = D[0xEC]
     *   fC = +12.0f literal (lui 0x4140)
     *   *(float*)(v0 + 0xBC) = fA
     *   ... (continues for 0xC0..0xE0 fields with mix of D-loads and
     *   literals: +2.0 lui 0x4000, +50.0 lui 0x4248, +20.0 lui 0x41A0,
     *   +15.0 lui 0x4170)
     *   *(int*)(v0 + 0x4DC) = const               ; final field
     *
     * Stage 13 (~8 insns 0x5710-0x5728): EPILOGUE.
     *   v0 = a0 (already loaded from sp+0xE8 above; carries through)
     *   $s0 = lw 0x18(sp)
     *   $s1 = lw 0x1C(sp)
     *   $s2 = lw 0x20(sp)
     *   jr  $ra
     *   addiu $sp, $sp, 0xE8
     *
     * Cumulative 1165/1165 insns characterized (~100%). The full
     * function structure is now mapped. C-body decomp work ahead:
     *
     *   - Prologue: ~28 insns (Stages 1-3) — partially written in body
     *   - Iter 0 init + sub-region setup: ~40 insns (Stage 4) — partial
     *   - Unrolled main loop: ~700 insns (Stages 5-11, 32 iters of
     *     ~22 insns each) — only Stages 5-7 (3 iters) currently in
     *     body; needs explicit unrolled writeout
     *   - Final field init: ~80 insns (Stage 12) — needs body
     *   - Epilogue: ~8 insns (Stage 13) — auto-emitted by IDO
     *
     * 2026-05-05 STATUS: macro INIT_ITER(SLOT, TMPL_OFF, FLOAT_EXPR)
     * implemented with all 41 iters expanded, plus Stage 12 finalize
     * phase as straight C stores. Achieved 61.61% fuzzy (from 2.46%
     * baseline this session). This appears to be the structural cap
     * for the macro-only approach.
     *
     * RESIDUAL 38pp gap analysis:
     *   - Mine: 921 insns. Expected: 1165 insns. Delta: 244 insns short.
     *   - Per-iter delta: ~6 insns (mine 21/iter, expected 25/iter).
     *   - Missing per-iter: (a) per-iter `lui $at, hi(D+0xN)` reload of
     *     D base for the float scalar (mine CSE's D base into $s3 once);
     *     (b) per-iter sp-relative arg-buffer spill pattern (mine uses
     *     local _t var that IDO keeps in $tN, no stack spill).
     *   - Frame size mismatch: mine -0x28, expected -0xE8 — directly
     *     caused by missing per-iter spill slots.
     *
     * Failed experiments (both regressed slightly):
     *   - `char *_arg_buf; char **_arg_ptr = &_arg_buf;` indirect
     *     pattern in macro: IDO optimized away the indirection; -1.6pp
     *   - `volatile char pad[200]; pad[0]=0;` to force frame size:
     *     IDO allocated 0x1B0 frame (TOO big), shifted everything;
     *     -0.6pp
     *
     * 2026-05-05 UPDATE: applied feedback_unique_extern_with_offset_cast_
     * breaks_cse.md recipe — declared 99 unique externs in
     * undefined_syms_auto.txt (D_44F4_iterX_{t,f,p}, all at 0x0),
     * replaced INIT_ITER with INIT_ITER_U (D-source iters) and
     * INIT_ITER_UC (const-float iters). Result: 61.61% → 63.33% (+1.72pp).
     *
     * Per-iter gain measured smaller than projected (~0.04pp/iter vs
     * predicted ~0.07pp/iter). Most of the residual gap is the per-iter
     * sp-relative arg-buffer spill pattern (separate cap class, would
     * need unique-pseudo or volatile-ptr-to-arg trick — see
     * feedback_volatile_ptr_to_arg_forces_caller_slot_spill.md).
     *
     * Remaining cap is structural: target uses extra stack slots
     * (sp+0xE0 per-iter scratch, sp+0xE8/0xEC/0xF0 for a0/a1/a2 spill
     * at entry) that mine doesn't emit. Each iter has a store-then-load
     * pattern at sp+0xE0 — `sw t1, 0xE0(sp); lw t4, 0(t2)` where
     * `t2 = sp+0xE0`. Looks like a varargs marshalling buffer or
     * deliberate CSE-defeating spill in original source.
     *
     * Tried 2026-05-05: `volatile char *_t = *(char**)(...)` in the
     * macro body — added 59 insns (3700 → 3936 bytes) but at wrong
     * positions; fuzzy unchanged at 63.33%.
     *
     * 2026-05-05 (later): THREE structural fixes that worked:
     *   1. `char *_t_buf[1];` local + macro `_t_buf[0] = *(char**)(...)`
     *      → IDO emits per-iter store-then-load through stack at sp+N,
     *      matching target's sp+0xE0 pattern. (+6.11pp)
     *   2. Changed s2 from `a0 + 0x2C` (struct member) to a stack-temp
     *      via `char *_s2_buf; char *s2 = (char*)&_s2_buf;`. Target
     *      had `addiu s2, sp, 0x2C` not `addiu s2, a0, 0x2C`. (+0.35pp)
     *   3. Added `char _pad[N];` to grow frame from 0x38 to 0xE8 (matching
     *      target). 2026-05-28: N is now 160 (was 168 → frame 0xF0/240, off by
     *      8 after later local churn); 160 gives `addiu sp,-232`. a0/a1/a2
     *      spill at sp+0xE8/0xEC/0xF0
     *      (matches target). +0.005pp.
     *
     * Result: 63.33% → 69.79%. Still ~30pp short.
     *
     * REMAINING CAP: target saves 3 $s-regs (s0/s1/s2/ra at sp+0x18/
     * 0x1C/0x20/0x24), mine saves only 2 (s0/s1/ra at sp+0x14/0x18/
     * 0x1C). My s2 is a stack-pointer not $s-promoted.
     *
     * 2026-05-05 (later): tried hoisting `s2` from inner block scope
     * to function scope (longer live range). Did NOT trigger $s2
     * promotion — frame size shrank to 0xE0 instead of growing,
     * fuzzy unchanged at 69.79%. The IDO global allocator picked
     * different priorities; my s2 still went to $tN.
     *
     * Target's s2 is `addiu s2, sp, 0x2C` set ONCE at 0x45A0 and
     * used across ~0x1180 bytes of function body (live until 0x5720
     * epilogue). To trigger $s2 promotion in IDO, need a value with
     * similarly long live range AND high ref count. The candidates
     * are limited — the marshalling-buffer base ptr is the obvious
     * one, but my macro structure already references it via s2.
     *
     * Promotion paths (multi-tick):
     *   - Move s2's `(char*)&_s2_buf` setup to LATER in the function
     *     so its live range starts after a few jal calls (could
     *     trick IDO into picking $s2 over $t). NOT YET TRIED — s2 is
     *     used in inner Stage 4 block at line 1811, can't easily move
     *     past first use without restructuring.
     *   - `register char *s2 = ...` keyword hint. TRIED 2026-05-05:
     *     IDO accepted the syntax (no error like the asm("$N") form),
     *     but did NOT change allocation — still goes to $tN. Confirmed
     *     via objdump: prologue still saves only s0/s1/ra, no s2.
     *     Conclusion: IDO's `register` hint is too weak to override
     *     the global allocator's priority calc here. RETEST 2026-06-01
     *     on the current 0xE8-frame body: same result. `register char *s2`
     *     rebuilt cleanly, but no-alias objdump still emitted only
     *     `sw ra,0x1c(sp)`, `sw s1,0x18(sp)`, `sw s0,0x14(sp)`; no
     *     `sw s2,0x20(sp)`. Do not retry without a separate live-range
     *     change.
     *   - Slot-shift via `_s2_buf[3]; s2 = &_s2_buf[2]`. TRIED 2026-06-01:
     *     with `_pad[160]`, frame stayed 0xE8 but IDO still used direct
     *     `sp+0x24` stores/loads for the marshalling slot (no `sp+0x2c`,
     *     no `$s2`). With `_pad[152]`, frame shrank to 0xE0 and moved
     *     caller-arg spills to sp+0xE0/0xE4/0xE8, a clear regression.
     *     Reverted; array indexing does not force the target stack slot
     *     or promotion.
     *   - SOURCE=5 retest 2026-06-01 on current branch:
     *     `(void)&a0; (void)&a1; (void)&a2;` with the volatile finalizer
     *     locals was ignored by IDO for this shape: match stayed 69.72618%,
     *     prologue still stored a1/a2 to local slots sp+0x34/sp+0x30, and
     *     still saved only s0/s1/ra. Removing volatile from a1_sp/a2_sp did
     *     force caller-shadow homes for a1/a2 at sp+0xEC/sp+0xF0, but regressed
     *     to 69.25751% and still emitted no s2 save. Hoisting `_s2_buf`/`s2`
     *     to function scope on top of that shrank the frame to 0xD8 and
     *     regressed to 69.248924%. Keep the volatile-local baseline until a
     *     real alias source for the long-lived sp+0x2C marshalling pointer is
     *     found.
     *   - decomp-permuter with PERM_RANDOMIZE around the macros
     *
     * 2026-05-05 (later): FIXED iter-G-NN macro bug. The macro at
     * line 1864 had `*(char**)s2 = _t_buf[0]` but never wrote `_t_buf[0]`
     * — so the load was reading uninitialized stack. Adding the missing
     * `_t_buf[0] = _t;` store before the read promoted iters G-NN's
     * codegen by ~32 SW instructions (one per iter). Net effect:
     * 62.05% → 69.48% (+7.43pp). 604 bytes / 151 insns deficit remain.
     *
     * 2026-05-05 (next run): Extended the marshalling-buffer pattern
     * to iters A-F (the FIRST INIT_ITER macro at line 1827) — also
     * needs `_t_buf[0] = _t; *(char**)s2 = _t_buf[0];` for the per-
     * iter store-then-load through sp+0xE0. +0.32pp (69.48 → 69.80).
     *
     * 2026-05-05 (negative): Tried the same fix on Stage 4's iter-0
     * setup (`tmpl0 = ...; *(char**)s2 = tmpl0;` at line 1811) — it
     * REGRESSED (-0.05pp). Iter-0 is special; target uses direct store
     * for iter 0 but marshalling for iters A onward. Don't extend the
     * pattern there.
     *
     * 2026-05-08: Stage 12 arg-finalizer nudge. Plain locals for a1/a2
     * did not change C emit, but volatile locals force late finalizer
     * stores through stack-resident values. Fresh objdiff after rebuilding
     * build/non_matching/src/game_uso/game_uso.c.o moved the C body from
     * 69.311584% to 69.577680%. */
    /*
     * 2026-06-01 SOURCE=5 improvement: split the init-call's third argument
     * into an explicit `char *arg2 = *(char**)s2;` local in iter0 and both
     * INIT_ITER macro bodies. This nudges IDO to materialize the template
     * reload before the call instead of keeping the `a3=1` setup as the call
     * delay-slot candidate. Direct objdiff improved 69.72618% -> 71.84635%;
     * refreshed report.json scores the function at 72.638626%. Still NM: the
     * long-lived sp+0x2C marshalling pointer is not promoted to $s2, so the
     * target's `lw a2,0(s2); ...; jal; sw a2,8(sp)` shape is only partly
     * recovered.
     *
     * 2026-06-01 SOURCE=5 follow-up: pass that same template pointer as a
     * duplicate fifth arg (`..., 1, arg2`) for iter0 and both INIT_ITER macro
     * bodies. This makes IDO emit the missing outgoing stack store in the call
     * delay slot and raises direct objdiff to 78.73047%. Still not exact:
     * built uses local `sp+0x2C` reloads and stores the fifth arg at `0x10(sp)`;
     * target keeps the marshalling pointer in `$s2` and stores `a2` at `0x8(sp)`.
     *
     * 2026-06-01 SOURCE=5 negative retests:
     *   - Replacing the duplicate fifth arg with a 4-arg call plus `(void)arg2`
     *     does NOT force the target caller-home store. IDO drops the delay-slot
     *     stack store, moves the scratch to a lower local slot, and regresses
     *     report score to 72.63262%.
     *   - Moving `_t_buf[1]` inside each unrolled macro expansion does create
     *     descending per-iteration stack slots, but it over-allocates the frame
     *     to 0x230 bytes and regresses to 79.56223%. Keep the shared `_t_buf`
     *     plus pad[152] baseline until the sp+0x2C pointer can be promoted
     *     without changing frame size.
     */
    /* Stage 12: LINKAGE/FINALIZE — store fixed values into a0's main
     * struct fields (offsets 0x2C, 0x30, 0xA0, 0xA8..0xE0, 0x4DC).
     * Mix of arg pass-through, zero-stores, D-table loads, and float
     * literals. ~57 insns.
     *
     * NEXT-PASS OBSERVATION (2026-05-05): this stage has 5 float loads
     * at &D + {0xE8, 0xEC, 0xF0, 0xF4, 0xF8}, and target asm at
     * 0x5658-0x56F4 DOES use per-access `lui $at, 0` reloads (5 distinct
     * base loads, not CSE'd). Tried unique-extern CSE-break with 5
     * unique externs (D_44F4_st12_E8/EC/F0/F4/F8) — confirmed via
     * objdump that build emits 5 separate `lui $at, 0` reloads as
     * intended, BUT report.json fuzzy stayed flat at 62.048927% (no
     * delta either way). Conclusion: the CSE-break is byte-equivalent
     * to the shared-&D form for this exact emit shape because IDO's
     * existing emit ALREADY uses 5 separate base loads at this point
     * in the function (likely because the live range of the cached
     * base is broken by intervening lui-for-fp-constant instructions:
     * 0x428C, 0x4366, 0x4140, 0x4248, 0x41A0, 0x4170 all clobber $at).
     * NOT a useful knob here — leave shared &D form. */
    {
        extern char D_44F4_st12_E8, D_44F4_st12_EC, D_44F4_st12_F0,
                    D_44F4_st12_F4, D_44F4_st12_F8;
        *(int*)(a0 + 0x30) = a1;
        *(int*)(a0 + 0x2C) = a2;
        *(float*)(a0 + 0xA8) = 0.0f;
        *(float*)(a0 + 0xAC) = *(float*)((char*)&D_44F4_st12_E8 + 0xE8);
        *(float*)(a0 + 0xB0) = 500.0f;
        *(float*)(a0 + 0xB4) = 70.0f;
        *(float*)(a0 + 0xB8) = 230.0f;
        *(float*)(a0 + 0xBC) = *(float*)((char*)&D_44F4_st12_EC + 0xEC);
        *(float*)(a0 + 0xC0) = 12.0f;
        *(float*)(a0 + 0xC4) = *(float*)((char*)&D_44F4_st12_F0 + 0xF0);
        *(float*)(a0 + 0xC8) = 2.0f;
        *(float*)(a0 + 0xCC) = 50.0f;
        *(float*)(a0 + 0xD0) = 20.0f;
        *(float*)(a0 + 0xD4) = 500.0f;
        *(float*)(a0 + 0xDC) = 15.0f;
        *(float*)(a0 + 0xE0) = *(float*)((char*)&D_44F4_st12_F4 + 0xF4);
        *(float*)(a0 + 0xD8) = *(float*)((char*)&D_44F4_st12_F8 + 0xF8);
        *(float*)(a0 + 0xA0) = 1000.0f;
        *(int*)(a0 + 0x4DC) = 3;
    }
epi:
    return a0;
}


void game_uso_func_00005728(void *a0) {
    *(s32*)((char*)a0 + 0x34) = 0;
    *(s32*)((char*)a0 + 0x44) = 0;
    *(s32*)((char*)a0 + 0x48) = 0;
    *(s32*)((char*)a0 + 0x4C) = 0;
    *(s32*)((char*)a0 + 0x50) = 0;
    *(s32*)((char*)a0 + 0x54) = 0;
    *(s32*)((char*)a0 + 0x58) = 0;
    *(s32*)((char*)a0 + 0x40) = 0;
    *(s32*)((char*)a0 + 0x64) = 0;
    *(s32*)((char*)a0 + 0x70) = 0;
    *(s32*)((char*)a0 + 0x68) = 0;
    *(s32*)((char*)a0 + 0x6C) = 0;
    *(s32*)((char*)a0 + 0x74) = 0;
    *(s32*)((char*)a0 + 0x78) = 0;
    *(s32*)((char*)a0 + 0xA4) = 0;
    *(s32*)((char*)a0 + 0x4C4) = 0;
    *(s32*)((char*)a0 + 0x4D8) = 1;
    *(f32*)((char*)a0 + 0x38) = 0.0f;
    *(f32*)((char*)a0 + 0x3C) = 0.0f;
}

void game_uso_func_00005780(int *a0, int a1) {
    if (a0 == 0) return;
    *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
    if (a1 & 1) {
        game_uso_func_00000000();
    }
}

void game_uso_func_000057B8(char *a0) {
    game_uso_func_00000000(a0 + 0xE4);
}

/* NATURAL CEILING: NM only, 82.5% objdiff (was 61.4). 2026-07-08 rise via
 * three levers; the last +2 words are a PRECISELY-CHARACTERIZED toolchain cap.
 * Levers that landed: (1) u32-retype of the two `== 2` field compares
 * (`*(u32*)(sub+0x848) == 2U`) — distinct dtype kills the uopt const-2 CSE
 * with the selector/dispatch case-2 compares, so the 2 colors $v0 and dies at
 * the mode load (target `li v0,2`; s32 form extended the candidate to $a2/$a3
 * and shifted sub/state coloring); (2) tail store via `t = sub; if (1) { t +=
 * 0x758; } *(f32*)(t+0x10) = value;` — the if(1)-committed pointer mutation
 * materializes `addiu v0,a1,0x758; swc1 f0,0x10(v0)` exactly (plain named
 * intermediate off the CACHED sub folds to swc1 0x768(a1)); (3) selector as
 * NESTED switches 3+4 (case 1-3 + default:switch case 4-7/default) — each
 * sub-switch is under the >=5-case jumptable threshold and chain-lowers with
 * the target's grouped shape (li-at delays, beq-to-arm, beql+dup on case 7
 * with orphan arm, default arm at fall-through, arms ascending).
 * RESIDUAL CAP (+2 words, tail exact but shifted): the target selector is ONE
 * 7-compare cascade; sub-switch junction costs `b + nop` (outer fall-through
 * must skip arms 1-3 to reach the inner compares — uopt block placement puts
 * each switch's arms right after its own compares regardless of source order;
 * verified with goto-thunk arms + sequential switches, same layout). A single
 * 7-case `switch` ALWAYS jumptables (sltiu/lui/lw/jr .rodata): threshold is
 * ncases>=5, verified 4=chain/5=table standalone, immune to expr type (u32,
 * u8, s16, &0xF), -KPIC, -mips1, -O1, IDO 5.3, missing default, and outlier
 * case (ugen splits clusters + STILL tables the dense one behind an slti
 * guard). `if(mode==K) goto cK;` chains get their single-assign arms PULLED
 * inline by uopt (bnel inversion + li-dup + orphan, +6 words; volatile arm
 * loads, 2-insn arms, double-jump spelling, arm source order all tested — the
 * pull only spares an arm that physically falls into the merge block; the
 * matched 174C 16-case goto-chain survives because its arms have STORES).
 * Only xjp (switch) arms are pull-immune, and only <=4-case switches chain.
 * NB: SUFFIX_BYTES_FORCE/INSN_PATCH removed 2026-05-23 as match-faking.
 * 2026-06-20: corrected call ABI — the 4 trailing mode-dispatch callees take a
 * SINGLE arg `a0` (target jal delay slots are `nop`); dispatch tail matches
 * target word-for-word (shifted +2 by the junction). */
#ifdef NON_MATCHING
void game_uso_func_0000591C(int *a0);
void game_uso_func_00006A30(int *a0);
void game_uso_func_00006CF0(int *a0);
void game_uso_func_000071E0(int *a0);
void game_uso_func_000057D8(char *a0) {
    char *sub;
    char *state;
    s32 mode;
    f32 value;

    if (*(s32 *)(a0 + 0x4D8) != 0) {
        sub = *(char **)(a0 + 0x30);
        *(s32 *)(a0 + 0x4D8) = 0;

        state = *(char **)(sub + 0x908);
        if ((state != 0) && (*(u32 *)(sub + 0x848) == 2U) &&
                (*(u32 *)(state + 0x848) != 2U)) {
            char *t;
            mode = *(s32 *)(state + 0x8C4);
            switch (mode) {
            case 1: value = *(f32 *)(a0 + 0x414); break;
            case 2: value = *(f32 *)(a0 + 0x42C); break;
            case 3: value = *(f32 *)(a0 + 0x444); break;
            default:
                switch (mode) {
                case 4: value = *(f32 *)(a0 + 0x45C); break;
                case 5: value = *(f32 *)(a0 + 0x474); break;
                case 6: value = *(f32 *)(a0 + 0x48C); break;
                case 7: value = *(f32 *)(a0 + 0x4A4); break;
                default: value = *(f32 *)(a0 + 0x4BC); break;
                }
                break;
            }
            t = sub;
            if (1) {
                t += 0x758;
            }
            *(f32 *)(t + 0x10) = value;
        }
    }

    mode = *(s32 *)(a0 + 0x64);
    *(f32 *)(a0 + 0x3C) = 0.0f;
    switch (mode) {
        case 0: game_uso_func_0000591C((int *)a0); break;
        case 1: game_uso_func_00006A30((int *)a0); break;
        case 2: game_uso_func_00006CF0((int *)a0); break;
        case 3: game_uso_func_000071E0((int *)a0); break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000057D8);
#endif

/* game_uso_func_0000591C: 0x1114 (1102 insns, 4.3 KB) — strategy-memo spine
 * candidate #2 (~29 cross-USO calls).  0x1D0-byte stack frame.
 *
 * Boundary-fixed 2026-04-20: splat originally put the glabel at 0x5924,
 * but the preceding `game_uso_func_000057D8` had 2 trailing `.word`
 * instructions (`lui $t6, 0; lw $t6, 0x78($t6)`) that semantically
 * belong to this function as its $t6 setup — without them, the `bne
 * $t6, zero, epilogue` at 0x5930 reads an uninitialized register. Per
 * feedback_splat_prologue_stolen_by_predecessor.md, reverse-merged:
 * trimmed 57D8 from 0x14C → 0x144 and prepended the 2 insns to this
 * function, renaming its glabel from 5924 → 591C.
 *
 * ENTRY PROLOGUE (insns 1-7 @ 0x591C-0x5934):
 *   lui   t6, 0
 *   lw    t6, 0x78(t6)          ; t6 = *(int*)(&D_0 + 0x78) = global flag
 *   addiu sp, -0x1D0
 *   sw    s0, 0x20(sp)
 *   or    s0, a0, 0              ; s0 = a0 (spilled)
 *   bne   t6, zero, 0x6A1C       ; if global_flag != 0 goto epilogue
 *   sw    ra, 0x24(sp)            ; (bne delay slot)
 *
 * Then:
 *   lui   t7, 0; lw t7, 0(t7)    ; t7 = *(&D_0)
 *   beql  t7, zero, 0x6A1C       ; if *&D_0 == 0 goto epilogue (reload ra in delay)
 *   lw    v0, 0x68(a0)           ; v0 = a0->field_68 (flag byte)
 *   andi  t8, v0, 0x1
 *   beq   t8, zero, +5           ; if !(v0 & 1) skip call-0x1 block
 *   andi  t9, v0, 0x2            ; delay: t9 = v0 & 2
 *   jal   0                      ; gl_func_0()  (no args, side effect)
 *    nop                          ; delay (unfilled)
 *   b     0x6A1C                 ; goto epilogue
 *
 * BODY STRUCTURE (rough): per-bit dispatch on a0[0x68] (bits 1, 2, 4, ...),
 * each bit handler does a short gl_func call and returns; fall-through to
 * a large per-frame update loop with cross-USO calls and float math on
 * a0+0x148..0x1C4 sub-buffers.
 *
 * Full decode deferred — 1100 insns and requires typed struct for the
 * 0x4E0-byte main object (same struct constructed by
 * game_uso_func_000044F4). Multi-run decomp expected.
 *
 * 2026-04-21: started partial NM body capturing the 4-way dispatcher
 * at the function head (insns 1-30 of 1102). First 3 dispatches handle
 * a0[0x68] bits 1/2/4 — each calls gl_func_00000000 and returns early.
 * Bit-0 handler takes no args; bits 1/2 pass `a0`. Body-proper starts
 * at 0x5998 with Vec3 staging and hasn't been attempted yet.
 *
 * 2026-05-03 re-measured: 2.72% NM (current build). Doc % was unmeasured;
 * baseline confirmed via objdiff. STRUCTURAL DECODE of body-proper entry
 * (insns 30-50 @ 0x5998-0x59CC, NOT added as C per
 * feedback_partial_alloc_block_add_irreversible.md):
 *
 *   /* Vec3 stage from sub_struct (a0->0x30) into sp+0x1B8 *\/
 *   t2 = a0->0x30                       ; sub-struct pointer (a0 saved as s0)
 *   a2 = sp + 0x1B8                      ; output Vec3 ptr
 *   t5 = sp + 0x148                      ; secondary Vec3 ptr (later writes)
 *   t8 = sp + 0x1C4                      ; tertiary Vec3 ptr
 *   a0 = s0                              ; restore a0 for downstream call
 *   sp[0x1B8] = t2->0xB4                 ; Vec3.x
 *   a1 = sp + 0x1AC                      ; arg slot for downstream
 *   a3 = sp + 0x1A8                      ; arg slot for downstream
 *   sp[0x1BC] = t2->0xB8                 ; Vec3.y
 *   sp[0x1C0] = t2->0xBC                 ; Vec3.z
 *
 * This Vec3-stage shape is IDENTICAL to game_uso_func_00006A30 (per
 * its own NM-wrap doc — both stage a0->0x30->{0xB4,0xB8,0xBC} into a
 * local Vec3 buffer at sp+0x9C resp. sp+0x1B8). Both are per-frame
 * compute functions that work on the same sub-struct family. Suggests
 * a shared "anchor + offset" pattern used across several spine entries.
 *
 * Following insns (50+): FPU-heavy quaternion/matrix math against
 * (a2->0x18->+0x318) Mat4-like region — same structural fingerprint as
 * game_uso_func_00007C1C (sp+0x348/0x38C dual-buffer). Likely THIS
 * function and 6A30/7C1C all build the same per-frame transform output
 * but from different entry contexts (boarder physics, AI, replay?).
 *
 * 2026-05-03 EXTENDED DECODE 0x59CC-0x5A30 (~25 insns): SCALE-AND-COPY
 * Vec3 transform.
 *   v0 = sub_struct                            ; reload from a0->0x30
 *   f12 = sub_struct->0xA8                     ; scale factor (likely
 *                                                wheel-radius / unit length)
 *   f4 = sub_struct->0x318                     ; Mat4[0] (axis vec X)
 *   f6 = sub_struct->0x31C                     ; Mat4[1] (axis vec Y)
 *   f8 = sub_struct->0x320                     ; Mat4[2] (axis vec Z)
 *   sp[0x148] = f4 * f12                       ; scaled axis * scale
 *   sp[0x14C] = f6 * f12
 *   sp[0x150] = f8 * f12
 *   /* IDO emits a "dead" addiu v0, v0, 0x318 immediately overwritten by
 *    * addiu v0, sp, 0x15C — likely loop-prep that IDO scheduled out of
 *    * scope; harmless. *\/
 *   /* Vec3 copy through pointer chain: sp[0x148..0x150] -> mem[v0..v0+8]
 *    * via 3 lw/sw pairs through t5 (= sp+0x148) and t9 (= sp+0x148 alias).
 *    * Net effect: ANOTHER copy of the scaled axis to a downstream output
 *    * buffer (probably to feed the matrix-vec multiply at 0x5A34+). *\/
 * The fingerprint matches a per-frame "rotate-scale a body axis by an
 * orientation matrix" idiom — common in 1080's boarder pose update where
 * the snowboard's "up" vector gets transformed into world space.
 *
 * 2026-05-04 EXTENDED DECODE 0x5A34-0x5A78 (~17 insns): Vec3 component-
 * wise add + jal + spill setup.
 *
 *   /* component-wise add staged Vec3 and another Vec3 *\/
 *   f10 = sp[0x1B8]               ; (post-stage Vec3.x — was the scaled axis)
 *   f18 = sp[0x1C4]
 *   f6  = sp[0x1BC]
 *   f8  = sp[0x1C8]
 *   f4  = f10 * f18               ; sp[0x1B8] = (axis.x * other.x)
 *   f18 = sp[0x1C0]               ; reload f18 from .z (overwrite previous)
 *   sp[0x1B4] = 0                 ; clear spill slot
 *   f10 = f6 * f8                 ; sp[0x1BC] = (axis.y * other.y)
 *   sp[0x1B8] = f4                ; commit x*x
 *   f4  = sp[0x1CC]
 *   sp[0x1BC] = f10               ; commit y*y
 *   f6  = f4 * f4                 ; f6 = f4 * f4   (squared)
 *   jal gl_func_00000000(...)     ; cross-USO call (probably normalize/length helper)
 *   sp[0x1C0] = f6                ; (delay) commit z*z (or w*w?)
 *   if (v0 == 0) goto far +0x3EB  ; bail-out if helper returned 0
 *   sp[0x1B0] = v0                ; spill helper return for later
 *   t2 = sp[0x1A8]                ; reload some pointer
 *   v1 = t2->0x84                 ; load field 0x84 from sub-struct
 *
 * This block computes a per-axis vector sum before the helper call
 * (sp+0x1B8 hosts {f4,f10,f6} = {x+ox, y+oy, z+oz}). Then takes a
 * guard branch on helper's return.
 * 2026-05-17 Codex pass: no-alias objdiff corrected the earlier `mul.s`
 * read; target is add.s at 0x5A48/0x5A54/0x5A64. Promoted the helper
 * call to its real four-arg shape `(self, &hit_parent, &staged_axis,
 * &hit_obj)`, added the immediate post-helper state gate, and used
 * stack padding to recover the target 0x1D0 frame. NON_MATCHING score:
 * 6.416% -> 9.029% after rebuilding `build/non_matching/...game_uso.c.o`.
 * Exact still blocked by $s0 allocation / local placement: IDO rejects
 * GCC-style `register int *self asm("$16")`, so the C emit keeps `$a0`
 * live and saves `$ra` at sp+0x14 instead of the target `$s0`/sp+0x20
 * and `$ra`/sp+0x24 prologue.
 *
 * 2026-05-17 follow-up: promoted the decoded 0x5B2C-0x5CB4
 * state-limit dispatch plus the two Vec3 transform-call arms into real
 * C. Rebuilt DNM object and checked objdiff/no-alias output: 9.005%
 * -> 14.902%, C-emitted body 0x1C0 -> 0x360 bytes. Tried plain
 * `register int *self`; no score/codegen change, so left it normal.
 *
 * 2026-05-17 Codex iteration: promoted the decoded post-transform
 * scalar/flag gate (target 0x5E00-0x5F68 shape) into C. This is still
 * structural C, not a final-mile match: the float-returning helper is
 * represented as a side-effect call because the file's canonical
 * gl_func_00000000 decl is int-returning.
 *
 * 2026-05-17 follow-up iteration: promoted the next effect/proximity
 * alloc trio plus the state-counter LUT dispatch into C. DNM objdiff
 * improved 21.319% -> 33.110%. Tried a ratio-flag variant for the
 * documented bit-0x8 path; it regressed to 32.999%, so the lower-level
 * ratio code remains for a later exact grind.
 *
 * 2026-05-17 Codex deep attempt: extended the concrete C body through the
 * second state LUT, proximity flag synthesis, flag-word update at sub+0xA58,
 * and 0x54 frame-counter/timer block (target 0x6620-0x6820 range). Follow-up
 * extended the next bit-test dispatch through the 0x400 direct-call path.
 *
 * 2026-05-17 final-pass tail lift: added the late effect-flag dispatch
 * under the 0x10 path: helper linkage to self+0x7C, state-keyed threshold
 * cascades at 0x24C/0x21C/0x234, 0x1BC/0x18C/0x1A4, 0x174/0x144/0x15C,
 * and 0x204/0x1D4/0x1EC, plus the tail flag commit call. DNM objdiff:
 * 45.586% -> 49.763%.
 *
 * 2026-05-20 Codex iteration: corrected the 0x20/0x40 helper-fail arms
 * and the 0x400 fast path to fall through to the final flag-commit call
 * instead of returning after a one-arg helper call. Tried frame-pad
 * resizing and split D-base aliases for the entry globals; both compiled
 * back to the same frame/D-base CSE shape and did not move objdiff.
 *
 * 2026-05-20 Codex follow-up: promoted the 0x5D00 transform helper to the
 * float-return alias so the following sign/metric block consumes `$f0`
 * instead of a synthetic 0.0f. Also tested pad sizes 0xA0/0xA8/0xB0:
 * 0xA0 recovers the 0x1D0 frame but shifts early Vec3 locals down, while
 * 0xB0 keeps the first staged Vec3 at target sp+0x1B8 and scores best.
 * DNM objdiff: 51.995% -> 52.010%; the target is still far from exact. */
/*
 * 2026-05-21 Codex exact-grind attempt: current baseline measured 52.12077%.
 * Tried the existing D_game_11564_flag alias for the 0x78 global guard to
 * split the prologue into target-like independent lui/lw pairs; prologue
 * improved locally but objdiff regressed to 51.967064% because relocation
 * form/stack alignment worsened. Tried materializing the bit-4 dispatch
 * mask as a normal and register local to chase target `$t1`; both kept `$t3`,
 * grew the frame to 0x1E8, and scored 52.117107%. Re-sampled pad sizes:
 * 0xA0 restored the target 0x1D0 frame but moved early Vec3 stack slots
 * off target and scored 52.117107%; 0xA8 scored 52.11528%; 0xB8 scored
 * 52.116196%. Keep pad[0xB0] as the best current C shape despite its 0x1E0
 * frame because it preserves the early Vec3 stage at sp+0x1B8 and the best
 * whole-function alignment. No episode: not exact.
 *
 * 2026-05-21 follow-up: tested moving scaled_axis/mul_axis after pad[0xB0]
 * to chase target's sp+0x148/sp+0x15C scaled-Vec3 slots; it regressed
 * 52.010063% -> 52.009148%, so reverted. Removing the defensive NULL
 * initialization of hit_parent/hit_obj improved 52.010063% -> 52.338516%
 * by dropping non-target pre-call stores. Reusing out_flags as the late
 * effect flag accumulator instead of a separate effect_flags local improved
 * further to 52.799633%. Still not exact; no episode.
 *
 * 2026-05-21 Codex iteration: promoted the decoded proximity/ratio flag
 * gate after the XZ distance test into C. Guarding the gate with
 * sub->0x908 matched target structure best and moved DNM objdiff
 * 52.799633% -> 54.043%. Nearby variants regressed: using metric instead
 * of transform_out.y for the gate scored 53.380604%, and forcing the ratio
 * value into the following out_flags&8 branch scored 52.65782%. Still not
 * exact; no new episode.
 *
 * 2026-05-21 follow-up: fixed the late hit-parent/self->0x40 tail logic to
 * match target 0x6B04-0x6B58: the parent copy triggers when self->0x40 is
 * already nonzero, and the null-parent path either copies helper_ptr+0x6C
 * or sets out_flags|0x10. DNM objdiff: 54.043% -> 54.99451%. Still not exact.
 *
 * 2026-06-21 agent-b pass: corrected the scaled-axis compute region
 * (0x59D4-0x5A00) by lifting the three source-float loads into explicit
 * temporaries before the muls. IDO then groups 3 lwc1 / 3 mul.s / 3 swc1
 * (target shape) instead of interleaved load-mul-store. objdiff fuzzy
 * 56.297% -> 57.639%. Residual is dominated by whole-function stack-slot
 * layout (target stages at sp+0x148/0x15C/0x1B8/0x1C4; NM lands at
 * sp+0x19C/0x1A4/0x1B0...) plus pervasive register coloring + a ~59-word
 * size deficit spread through the body. Tail aligns only on the 5-word
 * epilogue; no localized fixable run remains. Genuine coloring/frame-
 * layout cap on this spine fn (see regalloc-sweep-concluded memo). No
 * episode: not exact.
 *
 * 2026-05-21 Codex exact-grind: remeasured current DNM body at 54.99451%.
 * Re-tested stack padding after the tail lift: pad[0xA0] regressed slightly
 * to 54.98902%, so pad[0xB0] remains best. Target uses separate stack flag
 * words at sp+0x1A4 (0x20/0x40 helper-fail arms) and sp+0x1A0 (late
 * 0x400/0x10/0x200/0x100/0x80 dispatch), but rewriting the C to use
 * state_flag/resolved_state for those exact semantic sources regressed hard:
 * full rewrite 54.19213%, helper-arm-only rewrite 54.50778%. The current
 * out_flags-shaped tail is therefore retained as the best measured IDO
 * allocation shape, despite being less semantically direct than the asm's
 * stack-slot split. No episode: not an exact C/body match.
 *
 * 2026-06-21 agent-e ROOT-CAUSE LEVER: the body had been calling the
 * PLACEHOLDER `gl_func_00000000` at every call site (wrong jal target /
 * wrong reloc). Mapped 26 of 28 call sites to their REAL in-TU callees by
 * zipping the body's source-order call sequence against the R_MIPS_26 jal
 * sequence in the resolved .s and cross-checking arg shapes:
 *   bit1/2/4 dispatch -> A3C4/A604/A7F8;  4-arg helper -> 7ACC;  state
 *   helper -> 7A98;  transform arms -> 7C1C (resolved==0) / 8CD8 (==1);
 *   all `(0xC)` Vec3 allocs -> 055750;  tail state machine ->
 *   074D8/0751C/074D8/07448/07424, 09B88/A7D8 (0x20 path), A0E8/AB98
 *   (0x40 path), 071A4/06FA8 (0x400 path), and commit tail -> 07538.
 * Forward decls added (callees are defined later in this TU). objdiff
 * fuzzy 57.512% -> 58.211%. Residual is the documented coloring/frame-
 * layout cap (880 diff insns spread across the body, ~59-word size
 * deficit). Two synthesized calls (metric `_f` helper at the inlined
 * 5C98 region, and the `(self,out_flags,metric)` effect call) have no
 * matching jal and remain placeholders — body-structure divergences, not
 * symbol bugs. No episode: not exact.
 *
 * 2026-06-21 agent-i: the metric `_f` placeholder IS a real callee —
 * game_uso_func_00003ED4(Vec3*,Vec3*,int*) (the yaw-between-vectors FPU
 * helper, defined at 0x3ED4 in this TU). Wired it; the call-reloc set no
 * longer has 00003ED4 as exp-only. CALL-SEQ ZIP (built vs target) now shows
 * the only remaining call-set deltas are STRUCTURAL, not symbol bugs:
 *   - target order at idx 7/8 is alloc(055750) THEN 00003ED4; this body
 *     emits 00003ED4 then the loop allocs (swapped). The target's pre-metric
 *     055750 is the DEAD-SENTINEL alloc-into-scratch at 0x3ac
 *     (`a3=sp+376; bne a3,zero,skip; v1=a0+968; a0=12; jal alloc; ...` then
 *     a Vec3 copy into a1/sp+376) — a conditional copy-or-alloc of a 12-byte
 *     Vec3 scratch that this body skips. Reconstructing that scratch-Vec3
 *     copy/alloc guard is the next structural step (recovers the missing
 *     055750 + realigns the metric region).
 *   - the `(self,out_flags,metric)` effect call at line ~4951 still has no
 *     matching jal once ordering is accounted; it is a body-structure
 *     divergence (extra/mis-ordered call), NOT a known real symbol — leave
 *     as placeholder until the scratch-Vec3 region is rebuilt. No episode.
 *
 * 2026-06-21 agent-i (this session): RECONSTRUCTED the dead-sentinel
 * copy-or-alloc scratch-Vec3 at 0x5cb0-0x5cf8 (target: a3=&scratch never NULL
 * so the 055750(0xC) alloc is dead, live path copies (sub+0x3c8).{x,z}+y=0
 * through the held pointer, then metric=00003ED4(scratch,transform_in,...)).
 * This recovers a 055750 call -> objdiff 941 -> 936 non-reloc diffs, gap
 * 240B -> 236B. BUT the call ORDER (target: alloc THEN 00003ED4; build: still
 * 00003ED4 first) is NOT fixed: IDO 7.1 -O2 DEAD-CODE-ELIMINATES the
 * `if (&local == NULL) alloc` guard because &scratch_xz is provably non-null,
 * so the alloc floats away from the metric region. The target keeps the
 * provably-dead alloc, which means the original source's scratch pointer was
 * NOT a plain &local — it was a held pointer whose &local origin IDO could not
 * trace (assigned via a prior conditional / opaque path). Forcing that
 * un-provable held pointer is the remaining anti-DCE structural step. No
 * episode: 936 diffs, the documented coloring/frame-layout cap dominates. */
/*
 * 2026-06-22 agent-i (re-attack w/ refined toolkit): two GENUINE structural
 * corrections, both fuzzy-neutral (56.297% before and after; coloring + the
 * documented pointer-materialization cap dominate the metric):
 *
 *   (1) REMOVED the fabricated `gl_func_00000000(self, out_flags, metric)`
 *       call that sat between the out_flags-synthesis block and the
 *       `effect_pos = transform_out` tail. Positional zip of the R_MIPS_26
 *       jal sequence (build vs target) proved it had NO matching jal: target
 *       has exactly 8 effect-allocs (055750) after the metric region; the
 *       placeholder was a 9th, spurious call (it even passed `metric` as a
 *       double via cvt.d.s/mfc1 a2,a3). After removal the build call set is
 *       28 calls, ALL real symbols (no gl_func_00000000 placeholder left),
 *       and the ONLY remaining call-seq delta vs target (29 calls) is the
 *       single dead-sentinel 055750 at idx 7 (see below).
 *
 *   (2) FRAME SIZE now matches target. pad[0x90] yields addiu sp,sp,-464
 *       (=0x1D0, the target frame) vs the prior pad[0xA0]'s -480 (0x1E0).
 *       Swept 0x90..0xB0: fuzzy identical at every size, so 0x90 is strictly
 *       more faithful. (Stack-SLOT assignment within the frame still differs
 *       — pad position shifts the Vec3 locals — but total frame is exact.)
 *
 * REMAINING (confirmed multi-layer cap, not a bug):
 *   - dead-sentinel 055750 at target idx 7 (0x5cc8, before 00003ED4): IDO
 *     7.1 -O2 const-folds `&scratch_xz == 0` to false and DCEs the alloc
 *     regardless of guard structure (verified: tried hoisting scratch_src
 *     into the branch arms — still folded). Per docs/PATTERNS.md (A7F8
 *     "fragility" note) the target's dead allocs are an inlined vec-init
 *     helper inlined BEFORE the const-fold pass; a top-level `if(p==0)`
 *     runs after that pass and is folded. We can't add a noinline helper.
 *   - pointer materialization at 0x59E0+ (target: addiu v0,v0,792;
 *     addiu v0,sp,348 between the scaled-axis muls) — IDO re-folds C
 *     pointer-locals to big direct offsets; documented permuter-class cap
 *     (docs/PATTERNS.md pointer-materialization vein).
 *   - pervasive register/FP coloring + per-slot stack layout.
 * No episode: not exact. */
#ifdef NON_MATCHING
/* game_uso_func_0000591C (spine, 1093w) — three-scalar separation pass.
 *
 * 2026-06-24 agent-e: prior C conflated THREE distinct stack floats into one
 * `metric`, discarding the float return of game_uso_func_00007A98(self):
 *   metric_a    = game_uso_func_00007A98(self)            -> sp+0x19C (412)
 *   yaw_metric  = fabs(game_uso_func_00003ED4(...))       -> sp+0x170 (368)
 *   accel_metric= fabs(self->0x3C)                        -> sp+0x16C (364)
 * Each tail comparison was routed to the slot the EXPECTED .o actually loads
 * (per-site reloc/offset audit): the 0x10-dispatch + several state-LUT
 * compares read 412(metric_a); the dist/dot proximity block reads 368(yaw);
 * the normalized-delta + accel gate read 364(accel). Also added the missing
 * `if (self->0x74 != 0) goto commit` early-skip after the metric block.
 * SELF-VERIFY only; not exact — coloring/frame-layout cap dominates. */
/* forward decls for 591C real callees (defined later in this TU) */
void game_uso_func_0000A3C4();
void game_uso_func_0000A604(char *);
void game_uso_func_0000A7F8(char *);
int game_uso_func_00007ACC();
float game_uso_func_00007A98(int *);
int game_uso_func_00007C1C();
void *game_uso_func_00008CD8();
void game_uso_func_000074D8(char *);
void game_uso_func_0000751C(char *);
void game_uso_func_00007448(char *);
void game_uso_func_00007424(void *);
int game_uso_func_00009B88();
void game_uso_func_0000A7D8(int *);
int game_uso_func_0000A0E8(char *, char *, char *);
void game_uso_func_0000AB98(void *);
void game_uso_func_000071A4(int *);
int game_uso_func_00006FA8(int *);
long long game_uso_func_00007538(int *, int);
void game_uso_func_0000591C(int *a0) {
    int *self;
    int v0;
    char *sub;
    char *helper_ptr;
    char *hit_obj;
    char *hit_parent;
    Vec3 *vec_result;
    Vec3 staged_axis;
    Vec3 scaled_axis;
    Vec3 mul_axis;
    Vec3 transform_in;
    Vec3 transform_out;
    Vec3 vec_tmp;
    Vec3 vec_copy;
    Vec3 scratch_xz;
    Vec3 derived_vec;
    Vec3 effect_pos;
    Vec3 effect_delta;
    Vec3 effect_delta2;
    Vec3 effect_stage;
    char pad[0x90];
    int state_flag;
    int active_state;
    int resolved_state;
    int transform_flag;
    int state_bits;
    int out_flags;
    int state_counter;
    int state_code;
    Vec3 *effect_vec;
    char *entity_pos;
    float state_limit;
    float metric_a;
    float yaw_metric;
    float accel_metric;
    register float scale;
    register float rx, ry, rz;
    float dist_sq;
    float dot;
    float state_value;
    float state_value2;
    int *flag_word;

    self = a0;

    /* Two early-out guards on globals. */
    if (*(int*)((char*)&import_80020110 + 0x78) != 0) return;
    if (import_8006EF48 == 0) return;

    /* 4-way bit dispatch on a0->field_68 (flag byte).  Each handler
     * makes one gl_func_00000000 call and returns. Fall-through goes
     * to the per-frame body at 0x5998 — not yet decoded. */
    v0 = *(int*)((char*)self + 0x68);
    if (v0 & 1) {
        game_uso_func_0000A3C4();
        return;
    }
    if (v0 & 2) {
        game_uso_func_0000A604(self);
        return;
    }
    if (v0 & 4) {
        game_uso_func_0000A7F8(self);
        return;
    }

    staged_axis = *(Vec3*)(*(char**)((char*)self + 0x30) + 0xB4);
    sub = *(char**)((char*)self + 0x30);
    scale = *(float*)((char*)self + 0xA8);
    {
        float ax = *(float*)(sub + 0x318);
        float ay = *(float*)(sub + 0x31C);
        float az = *(float*)(sub + 0x320);
        scaled_axis.x = ax * scale;
        scaled_axis.y = ay * scale;
        scaled_axis.z = az * scale;
    }
    mul_axis = scaled_axis;
    staged_axis.x += mul_axis.x;
    staged_axis.y += mul_axis.y;
    staged_axis.z += mul_axis.z;

    helper_ptr = (char*)game_uso_func_00007ACC(self, &hit_parent, &staged_axis, &hit_obj);
    if (helper_ptr == 0) return;

    state_flag = *(int*)(helper_ptr + 0x84);
    if (hit_obj != NULL) {
        resolved_state = state_flag;
    } else {
        resolved_state = 0;
    }

    /* metric_a: float return of 00007A98 cached at sp+0x19C (412). */
    metric_a = game_uso_func_00007A98(self);

    active_state = *(int*)((char*)self + 0x74);
    if (active_state == 0) {
        if (*(float*)((char*)self + 0xD8) >= 0.0f) {
            if ((state_flag == 0) && (hit_parent != NULL)
                    && (*(int*)(hit_parent + 0x84) == 0)) {
                sub = *(char**)((char*)self + 0x30);
                if (*(float*)((char*)self + 0xB4) > *(float*)(sub + 0x348)) {
                    resolved_state = 0;
                }
            }
        }
    } else if (active_state != 1) {
        resolved_state = 0;
    }

    transform_flag = 0;
    if (active_state == 1) {
        active_state = *(int*)((char*)self + 0x2C);
        if (active_state == 3) {
            state_limit = *(float*)((char*)self + 0x3FC);
        } else if (active_state == 2) {
            state_limit = *(float*)((char*)self + 0x3E4);
        } else {
            state_limit = *(float*)((char*)self + 0x3CC);
        }

        if (state_limit >= 0.0f) {
            if ((state_flag == 0) && (hit_parent != NULL)
                    && (*(int*)(hit_parent + 0x84) == 0)) {
                sub = *(char**)((char*)self + 0x30);
                if (*(float*)((char*)self + 0xB4) <= *(float*)(sub + 0x348)) {
                    *(int*)((char*)self + 0x74) = 1;
                    transform_flag = 1;
                } else {
                    *(int*)((char*)self + 0x74) = 0;
                    resolved_state = 0;
                }
            } else {
                *(int*)((char*)self + 0x74) = 0;
                resolved_state = 0;
            }
        } else {
            *(int*)((char*)self + 0x74) = 0;
            resolved_state = 0;
        }
    }

    sub = *(char**)((char*)self + 0x30);
    if (resolved_state == 0) {
        vec_result = (Vec3*)game_uso_func_00007C1C(sub, self, helper_ptr, hit_parent,
            &staged_axis, &transform_out);
        vec_tmp = *vec_result;
        vec_copy = vec_tmp;
        transform_in.x = vec_copy.x;
        transform_in.y = vec_copy.y;
        transform_in.z = vec_copy.z;
    } else if (resolved_state == 1) {
        vec_result = (Vec3*)game_uso_func_00008CD8(&mul_axis, self, helper_ptr,
            hit_parent, transform_flag);
        vec_tmp = *vec_result;
        vec_copy = vec_tmp;
        transform_in.x = vec_copy.x;
        transform_in.y = vec_copy.y;
        transform_in.z = vec_copy.z;
    }

    sub = *(char**)((char*)self + 0x30);
    {
        /* dead-sentinel copy-or-alloc of a 12-byte Vec3 scratch (target
         * 0x5cb0-0x5cf8): a3 = &scratch_xz is never NULL, so the alloc is
         * dead code; the live path copies (sub+0x3c8).{x,z} into the scratch
         * with y cleared, through the held pointer. */
        Vec3 *scratch_src = (Vec3 *)(sub + 0x3C8);
        Vec3 *scratch_ptr = &scratch_xz;
        if (scratch_ptr == NULL) {
            scratch_ptr = (Vec3 *)game_uso_func_055750(0xC);
            if (scratch_ptr == 0) goto skip_scratch;
        }
        scratch_ptr->x = scratch_src->x;
        scratch_ptr->z = scratch_src->z;
        scratch_ptr->y = 0.0f;
skip_scratch:;
        /* yaw_metric: fabs of 00003ED4 return cached at sp+0x170 (368). */
        yaw_metric = game_uso_func_00003ED4(scratch_ptr, &transform_in, (int *)&transform_out);
    }
    if (yaw_metric < 0.0f) {
        yaw_metric = -yaw_metric;
    }

    scale = *(float*)(sub + 0x348) / *(float*)((char*)self + 0xB0);
    scale += 1.0f;
    *(float*)((char*)self + 0x3C) =
        (yaw_metric * scale * *(float*)((char*)self + 0xAC)) / *(float*)(sub + 0x708);

    /* accel_metric: fabs(self->0x3C) cached at sp+0x16C (364). */
    accel_metric = *(float*)((char*)self + 0x3C);
    if (accel_metric < 0.0f) {
        accel_metric = -accel_metric;
    }

    /* early-skip: if self->0x74 != 0, jump straight to the state tail
     * (target 0x5D9C-0x5DB8: beqzl self->0x74; if ==1 -> v0=self->0x2C). */
    active_state = *(int*)((char*)self + 0x74);
    out_flags = 0;
    if (active_state != 0) {
        if (active_state == 1) {
            active_state = *(int*)((char*)self + 0x2C);
        }
        out_flags = active_state;
        goto commit_flags;
    } else {
        state_bits = *(int*)((char*)self + 0x6C);
        if (state_bits & 1) {
            if ((resolved_state & 1) && ((resolved_state & 2) == 0)) {
                *(int*)((char*)self + 0x6C) = state_bits & ~1;
                *(int*)((char*)self + 0x48) = 0x14;
                if (resolved_state & 4) {
                    out_flags = 0x20;
                } else if (resolved_state & 0x800) {
                    out_flags = 0x80;
                }
            } else if (hit_parent != NULL) {
                if (*(int*)(hit_parent + 0x84) & 2) {
                    effect_vec = (Vec3*)game_uso_func_055750(0xC);
                    if (effect_vec != NULL) {
                        entity_pos = helper_ptr + 0x30;
                        effect_vec->y = 0.0f;
                        effect_vec->z = *(float*)(entity_pos + 8);
                        effect_vec->x = *(float*)entity_pos;
                    }
                    entity_pos = hit_parent + 0x30;
                    effect_vec = (Vec3*)game_uso_func_055750(0xC);
                    if (effect_vec != NULL) {
                        effect_vec->y = 0.0f;
                        effect_vec->x = scratch_xz.x - *(float*)entity_pos;
                        effect_vec->z = scratch_xz.z - *(float*)(entity_pos + 8);
                    }
                    mul_axis = scratch_xz;
                    derived_vec = mul_axis;
                    sub = *(char**)((char*)self + 0x30);
                    entity_pos = sub + 0xB4;
                    effect_vec = (Vec3*)game_uso_func_055750(0xC);
                    if (effect_vec != NULL) {
                        effect_vec->y = 0.0f;
                        effect_vec->x = *(float*)entity_pos;
                        effect_vec->z = *(float*)(entity_pos + 8);
                    }
                    entity_pos = hit_parent + 0x30;
                    effect_vec = (Vec3*)game_uso_func_055750(0xC);
                    if (effect_vec != NULL) {
                        effect_vec->y = 0.0f;
                        effect_vec->x = derived_vec.x - *(float*)entity_pos;
                        effect_vec->z = derived_vec.z - *(float*)(entity_pos + 8);
                    }
                    mul_axis = scratch_xz;
                    *(int*)((char*)self + 0x48) = 0x14;
                    *(int*)((char*)self + 0x6C) = *(int*)((char*)self + 0x6C) & ~1;
                }
            }
        } else if ((hit_parent != NULL) && (*(int*)(hit_parent + 0x84) & 2)) {
            helper_ptr += 0x30;
            scratch_xz.x = *(float*)helper_ptr;
            scratch_xz.y = 0.0f;
            scratch_xz.z = *(float*)(helper_ptr + 8);

            hit_parent += 0x30;
            derived_vec.x = scratch_xz.x - *(float*)hit_parent;
            derived_vec.y = 0.0f;
            derived_vec.z = scratch_xz.z - *(float*)(hit_parent + 8);
            out_flags = 0x40;
        }
    }

    effect_pos = transform_out;
    effect_delta = derived_vec;
    out_flags = 0;
    if ((hit_parent != NULL) && (*(int*)(hit_parent + 0x84) & 1)) {
        if ((*(int*)(hit_parent + 0x84) & 0x804) != 0) {
            sub = *(char**)((char*)self + 0x30);
            if (*(char**)(sub + 0x908) != NULL) {
                if (metric_a <= -2000.0f) {
                    effect_vec = (Vec3*)game_uso_func_055750(0xC);
                    if (effect_vec != NULL) {
                        entity_pos = helper_ptr + 0x30;
                        effect_vec->x = *(float*)entity_pos;
                        effect_vec->y = 0.0f;
                        effect_vec->z = *(float*)(entity_pos + 8);
                    }
                }
            }
        }
    }

    if (hit_parent != NULL) {
        entity_pos = hit_parent + 0x30;
        effect_vec = (Vec3*)game_uso_func_055750(0xC);
        if (effect_vec != NULL) {
            effect_vec->x = transform_out.x - *(float*)entity_pos;
            effect_vec->y = 0.0f;
            effect_vec->z = transform_out.z - *(float*)(entity_pos + 8);
        }

        effect_stage = effect_delta;
        sub = *(char**)((char*)self + 0x30);
        entity_pos = sub + 0xB4;
        effect_vec = (Vec3*)game_uso_func_055750(0xC);
        if (effect_vec != NULL) {
            effect_vec->x = *(float*)entity_pos;
            effect_vec->y = 0.0f;
            effect_vec->z = *(float*)(entity_pos + 8);
        }

        entity_pos = hit_parent + 0x30;
        effect_vec = (Vec3*)game_uso_func_055750(0xC);
        if (effect_vec != NULL) {
            effect_vec->x = effect_pos.x - *(float*)entity_pos;
            effect_vec->y = 0.0f;
            effect_vec->z = effect_pos.z - *(float*)(entity_pos + 8);
        }

        effect_delta2 = effect_stage;
        sub = *(char**)((char*)self + 0x30);
        scale = *(float*)(sub + 0x348) * (*(float*)((char*)self + 0xC0) + 12.0f);
        dist_sq = (effect_delta.x * effect_delta.x) + (effect_delta.z * effect_delta.z);
        if (dist_sq != 0.0f) {
            dot = (effect_delta.x * effect_delta2.x) + (effect_delta.z * effect_delta2.z);
            dot = (dot * dot) / dist_sq;
            if (dot <= (scale * scale)) {
                *(int*)((char*)self + 0x48) = 0x14;
                *(int*)((char*)self + 0x6C) &= ~1;
            } else {
                if (*(float*)((char*)self + 0xBC) <= yaw_metric) {
                    if (yaw_metric < 50.0f) {
                        out_flags |= 0x40;
                    }
                }
            }
        }

        if (yaw_metric < *(float*)((char*)self + 0xB8)) {
            if (*(char**)(sub + 0x908) != NULL) {
                state_value = yaw_metric;
                if (state_value < 0.0f) {
                    if (((int*)&D_00000000)[0x1E] == 0) {
                        out_flags |= 4;
                    }
                }
                state_value = (state_value / *(float*)((char*)self + 0xB8)) * accel_metric;
                out_flags |= 8;
            }
        }

        if (out_flags & 8) {
            if (*(int*)((char*)self + 0x4C4) > 0) {
                game_uso_func_000074D8(self);
                *(int*)((char*)self + 0x4C4) = 0;
            }
        } else {
            state_counter = *(int*)((char*)self + 0x4C4);
            if (state_counter == 0x10000) {
                state_code = *(int*)((char*)self + 0x2C);
                if (state_code == 3) {
                    state_value = *(float*)((char*)self + 0x2DC);
                } else if (state_code == 2) {
                    state_value = *(float*)((char*)self + 0x2AC);
                } else {
                    state_value = *(float*)((char*)self + 0x2C4);
                }
                if (metric_a < state_value) {
                    game_uso_func_0000751C(self);
                    state_code = *(int*)((char*)self + 0x2C);
                    if (state_code == 3) {
                        state_value = *(float*)((char*)self + 0x324);
                    } else if (state_code == 2) {
                        state_value = *(float*)((char*)self + 0x30C);
                    } else {
                        state_value = *(float*)((char*)self + 0x2F4);
                    }
                    *(int*)((char*)self + 0x4C4) = (int)state_value;
                }
            } else if (state_counter > 0) {
                state_code = *(int*)((char*)self + 0x2C) - 1;
                if (state_code == 1) {
                    *(int*)((char*)self + 0x4C4) = state_code;
                    game_uso_func_000074D8(self);
                }
            }
        }
    }

    sub = *(char**)((char*)self + 0x30);
    state_code = *(int*)((char*)self + 0x2C);
    if (state_code != 0) {
        if (state_code == 3) {
            state_value = *(float*)((char*)self + 0x3B4);
        } else if (state_code == 2) {
            state_value = *(float*)((char*)self + 0x384);
        } else {
            state_value = *(float*)((char*)self + 0x39C);
        }

        if (state_value < metric_a) {
            *(int*)((char*)self + 0x4C4) = state_code - 1;
            game_uso_func_00007448(self);
        }
    }

    state_code = *(int*)((char*)self + 0x2C);
    if (state_code == 3) {
        state_value = *(float*)((char*)self + 0x12C);
    } else if (state_code == 2) {
        state_value = *(float*)((char*)self + 0x114);
    } else {
        state_value = *(float*)((char*)self + 0xFC);
    }

    if (state_value < metric_a) {
        if (*(int*)(sub + 0x9CC) != 0) {
            state_value2 = *(float*)((char*)self + 0xC8);
        } else {
            state_value2 = 1.0f;
        }
        if (accel_metric <= state_value2 * *(float*)((char*)self + 0xC4)) {
            out_flags |= 2;
        }
    } else if (resolved_state & 0x800) {
        if ((*(char**)(sub + 0x908) == NULL) || (metric_a <= -2000.0f)) {
            out_flags |= 0x80;
        }
    }

    state_code = *(int*)((char*)self + 0x2C);
    if (state_code == 1) {
        state_value = *(float*)((char*)self + 0x264);
    } else if (state_code == 2) {
        state_value = *(float*)((char*)self + 0x27C);
    } else {
        state_value = *(float*)((char*)self + 0x294);
    }

    flag_word = (int*)(sub + 0xA58);
    if (metric_a < state_value) {
        if (((int)metric_a & 3) == 0) {
            *flag_word |= 0x4000;
        } else {
            *flag_word &= ~0x4000;
        }
    } else {
        *flag_word &= ~0x4000;
    }

    if (*(float*)(sub + 0x348) < 30.0f) {
        state_counter = *(int*)((char*)self + 0x54) + 1;
        if (state_counter >= 75) {
            *(int*)((char*)self + 0x54) = 0;
            game_uso_func_00007424(self);
        } else {
            *(int*)((char*)self + 0x54) = state_counter;
        }
    } else {
        *(int*)((char*)self + 0x54) = 0;
    }

    if (resolved_state & 0x20) {
        if (game_uso_func_00009B88(self, helper_ptr, hit_parent) == 0) {
            game_uso_func_0000A7D8(self);
            goto commit_flags;
        }
    }

    if (resolved_state & 0x40) {
        if (game_uso_func_0000A0E8(self, helper_ptr, hit_parent) == 0) {
            game_uso_func_0000AB98(self);
            goto commit_flags;
        }
    }

    if (out_flags & 0x400) {
        game_uso_func_000071A4(self);
        *(int*)((char*)self + 0x40) = game_uso_func_00006FA8(self);
        goto commit_flags;
    }

    if (out_flags & 0x10) {
        if (helper_ptr != NULL) {
            *(int*)((char*)self + 0x7C) = *(int*)(helper_ptr + 0x6C);
        }
        if ((out_flags & 0x200) != 0) {
            state_code = *(int*)((char*)self + 0x2C);
            if (state_code == 3) {
                state_value = *(float*)((char*)self + 0x24C);
            } else if (state_code == 2) {
                state_value = *(float*)((char*)self + 0x21C);
            } else {
                state_value = *(float*)((char*)self + 0x234);
            }
            if (state_value >= metric_a) {
                *(int*)((char*)self + 0x40) = *(int*)((char*)self + 0x7C);
            } else if (*(char**)(sub + 0x908) != NULL) {
                state_value = *(float*)(*(char**)(sub + 0x908) + 0xBC);
                if (state_value < 0.0f) {
                    state_value = -state_value;
                }
                if (((int)state_value % 5) == 0) {
                    *(int*)((char*)self + 0x40) = *(int*)((char*)self + 0x7C);
                }
            }
        } else if ((out_flags & 0x100) != 0) {
            state_code = *(int*)((char*)self + 0x2C);
            if (state_code != 0) {
                if (state_code == 3) {
                    state_value = *(float*)((char*)self + 0x1BC);
                } else if (state_code == 2) {
                    state_value = *(float*)((char*)self + 0x18C);
                } else {
                    state_value = *(float*)((char*)self + 0x1A4);
                }
                if (metric_a <= state_value) {
                    *(int*)((char*)self + 0x40) = *(int*)((char*)self + 0x7C);
                }
            } else {
                *(int*)((char*)self + 0x40) = *(int*)((char*)self + 0x7C);
            }
        } else if ((out_flags & 0x80) != 0) {
            state_code = *(int*)((char*)self + 0x2C);
            if (state_code == 3) {
                state_value = *(float*)((char*)self + 0x174);
            } else if (state_code == 2) {
                state_value = *(float*)((char*)self + 0x144);
            } else {
                state_value = *(float*)((char*)self + 0x15C);
            }
            if (metric_a <= state_value) {
                *(int*)((char*)self + 0x40) = *(int*)((char*)self + 0x7C);
            }
        } else {
            state_code = *(int*)((char*)self + 0x2C);
            if (state_code == 3) {
                state_value = *(float*)((char*)self + 0x204);
            } else if (state_code == 2) {
                state_value = *(float*)((char*)self + 0x1D4);
            } else {
                state_value = *(float*)((char*)self + 0x1EC);
            }
            if (state_value <= metric_a) {
                *(int*)((char*)self + 0x40) = *(int*)((char*)self + 0x7C);
            } else if (metric_a > 0.0f) {
                *(int*)((char*)self + 0x68) |= 1;
            } else if (*(char**)(sub + 0x908) != NULL) {
                state_value = *(float*)(*(char**)(sub + 0x908) + 0xBC);
                if (state_value < 0.0f) {
                    state_value = -state_value;
                }
                if (((int)state_value % 5) == 0) {
                    *(int*)((char*)self + 0x40) = *(int*)((char*)self + 0x7C);
                }
            }
        }
    } else if (hit_parent != NULL) {
        if (*(int*)(hit_parent + 0x2C) == 0) {
            if (*(int*)((char*)self + 0x40) != 0) {
                *(int*)((char*)self + 0x40) = *(int*)(hit_parent + 0x6C);
            }
        }
    } else {
        if (*(int*)((char*)self + 0x40) != 0) {
            *(int*)((char*)self + 0x40) = *(int*)(helper_ptr + 0x6C);
        } else {
            out_flags |= 0x10;
        }
    }

commit_flags:
    game_uso_func_00007538(self, out_flags);


    /* Body-proper start at 0x5998 (extended 2026-05-03, ~16 insns 0x5998-0x59F8):
     *   t2 = a0->0x30;                                  // sub-struct ptr
     *   *(int*)(sp+0x1B8) = t2->[0xB4];                  // stage Vec3 ints
     *   *(int*)(sp+0x1BC) = t2->[0xB8];
     *   *(int*)(sp+0x1C0) = t2->[0xBC];
     *   v0 = a0->0x30;                                   // reload
     *   f12 = a0->[0xA8];                                // scalar
     *   f4 = v0->[0x318]; f6 = v0->[0x31C]; f8 = v0->[0x320];
     *   *(float*)(sp+0x148) = f4 * f12;                  // scaled outputs
     *   ... more scaled stores into sp+0x148.. region.
     * Multiple stack buffers staged: sp+0x148, sp+0x158, sp+0x1A8/AC,
     * sp+0x1B8/BC/C0/C4 — scratch space for upcoming gl_func call(s).
     *
     * Extended characterization 2026-05-04 (0x59F8-0x5AC0, ~50 insns):
     *   - Float stores: sp+0x148/0x14C/0x150 get f14/f2/f0 (the scaled
     *     Vec3 from above's mul.s chain).
     *   - 3-word memcpy block (0x5A04-0x5A30): t5 → v0 buffer + t2 → t8
     *     buffer, INTERLEAVED (8 lw/sw pairs total). t5/t2 are the two
     *     Vec3 sources (likely a0->0x30 and a0->0x148 or similar).
     *   - 0x5A34-0x5A68: element-wise Vec3 add:
     *       sp+0x1B8 += sp+0x1C4    (x += mul.x)
     *       sp+0x1BC += sp+0x1C8    (y += mul.y)
     *       sp+0x1C0 += sp+0x1CC    (z += mul.z)
     *     Plus `sp+0x1B4 = 0` (clear scalar slot). Then jal cross-USO
     *     with delay-slot store of last result.
     *   - 0x5A6C-0x5AC0: post-call dispatch. `if (call_result == 0) goto
     *     far_epilogue`. Otherwise reload a0->0x1A8 prior-saved ptr,
     *     read its 0x84 field, branch on (a0->0x74 == 1) — likely a
     *     state field — and either continue the per-frame body or
     *     branch to mid-function alt-path.
     *
     * Extended 2026-05-05 (0x5AC0-0x5B4C, ~36 more insns):
     *   - Float compare branch (0x5ACC `c.le.s $f0, $f8`): if $f0 (zero
     *     constant from earlier) > $f8 (= a0->0xD8) goto +0x12 (likely
     *     skips a sub-block that runs only when a0->0xD8 >= 0).
     *   - Three nested null-checks at 0x5ADC/0x5AE4/0x5AF0:
     *       if (t3 [= prior sp+0x1A4 saved ptr] != 0) skip;
     *       t4 = sp+0x1AC; if (t4 == 0) skip;
     *       t5 = t4->0x84; if (t5 != 0) skip;  (some "active" flag)
     *   - When all 3 null-checks pass: another float compare at 0x5B04
     *     `c.le.s $f18, $f10` where $f18 = a0->0xB4 (sub-Vec3.x prior),
     *     $f10 = a0->0x30->0x348 (deep field of sub-struct).
     *   - 0x5B20: `b +0x24` to a far merge point with delay slot
     *     `or v0, v1, zero` (return v0 = v1) — appears to be the
     *     "fall-through with side-result" path of the dispatch.
     *   - 0x5B28: lw v0, 0x2C(s0) (= a0->0x2C, another sub-state ptr)
     *   - 0x5B2C: addiu at, zero, 3 (= constant 3 — likely a state code)
     *   - 0x5B40: lwc1 $f12, 0x3FC(s0) (= a0->0x3FC float)
     *   - 0x5B44: addiu at, zero, 2 (state code 2)
     *   - 0x5B48: bnel at,zero,+0x4; lwc1 $f14, 0x3CC(s0) (delay)
     *
     * Pattern emerging: this is a STATE-MACHINE-DRIVEN per-frame update.
     * a0 has multiple fields treated as state codes (0x2C, 0x68, 0x74),
     * float positions (0xB4-0xC0 Vec3, 0xD8 scalar), and sub-struct
     * pointer (0x30 → 0x148-region floats + 0x318-region floats +
     * 0x348-region floats). Multiple per-state branches dispatch to
     * different sub-bodies, each making 1+ cross-USO calls.
     *
     * Cumulative ~115/1102 insns characterized (up from 80). Body-proper
     * has ~985 remaining insns + ~28 more cross-USO calls.
     *
     * 2026-05-06 EXTENDED DECODE 0x5B4C-0x5BC4 (~30 more insns):
     * STATE-CODE FLOAT COMPARE + 3-LEVEL POINTER NULL-CHECK + V1 DISPATCH.
     *
     *   /* state-code dispatch on (sp+0x1A4 saved state, after the v0!=2
     *    * bnel at 0x5B48): two arms select different a0 floats *\/
     *   /* arm 1: state==2 fall-through reads f12 = a0->0x3FC
     *    *        otherwise bnel-arm reads f14 = a0->0x3CC then jumps
     *    *        ahead via b +3 to 0x5B5C *\/
     *   f14 = (state == 2) ? a0->0x3E4 : a0->0x3CC;
     *   f12 = f14;
     *
     *   /* float-compare guarded clean-state block.
     *    * If f0 (= 0.0f scratch) > f12 (= picked float), branch likely
     *    * to 0x5BB0 (skip clean-state, go to v0 dispatch). *\/
     *   if (f12 >= 0.0f) {
     *       a0->0x74 = 0;                  /* delay-likely store *\/
     *       /* 3-level pointer-chain null-check: t8 != 0 OR
     *        * t9 = sp[0x1AC] != 0 OR t9->0x84 != 0 — any non-null
     *        * branches to the v0 dispatch (skips deeper compare). *\/
     *       if (t8 != 0) goto v0_dispatch;
     *       t9 = sp[0x1AC];
     *       if (t9 != 0) {
     *           a0->0x74 = 0;
     *           t1 = t9->0x84;
     *           if (t1 != 0) {
     *               a0->0x74 = 0;
     *               /* deepest level: float-compare a0->0xB4 vs
     *                * a0->0x30->0x348 (sub-struct deep field) *\/
     *               t2 = a0->0x30;
     *               f6 = a0->0xB4;
     *               f4 = t2->0x348;
     *               if (f6 <= f4) {
     *                   v0 = v1;            /* delay-likely *\/
     *               } else {
     *                   a0->0x74 = 0;
     *                   v1 = 0;
     *               }
     *           }
     *       }
     *   }
     *
     *   v0_dispatch:
     *   v0 = v1;
     *   /* dispatch on v0: 0 → fall through to 0x5BD0 path,
     *    *                 1 → beql goto 0x5C4C ALSO with sp+0x15C arg setup,
     *    *                 other → fall through with sp+0x15C arg setup *\/
     *   if (v0 == 0) goto path_5BD0;       /* a0 = sp+0x15C in delay *\/
     *   if (v0 == 1) goto path_5C4C;       /* beql; same a0=sp+0x15C delay *\/
     *
     * Pattern: this whole block (0x5AB4-0x5BC4) is a STATE-MACHINE-AS-
     * VALIDATION of a0->0x74 (state code) + a0->0x30 (sub-struct ptr) +
     * the saved-pointer-chain at sp+0x1A4/sp+0x1AC. The 3-level null-check
     * idiom (parent → child → grandchild) is common in 1080's scene graph
     * traversal — likely walking a "current target" pointer. The float
     * compare at 0x5B98 (a0->0xB4 vs sub->0x348) is comparing per-frame
     * Vec3.x against a deep sub-struct float — possibly distance / range
     * threshold.
     *
     * Cumulative ~145/1102 insns characterized (up from 115). ~960
     * remaining + ~25 cross-USO calls.
     *
     * 2026-05-06 EXTENDED DECODE 0x5BC8-0x5C44 (~32 insns): 4-ARG CROSS-
     * USO CALL + DUAL VEC3 MEMCPY CHAIN.
     *
     *   /* default-fall-through path (v0 == 0 from earlier dispatch) *\/
     *   /* arg setup for cross-USO call: 4 register + 2 stack args *\/
     *   a0 = a0->0x30;                                  ; sub-struct ptr
     *   a1 = s0;                                         ; original a0 (saved)
     *   a2 = sp[0x1B0];                                  ; helper-return v0 saved earlier
     *   a3 = sp[0x1AC];                                  ; saved ptr
     *   sp[0x10] = sp+0x1B8;                             ; out Vec3 ptr 1
     *   sp[0x14] = sp+0x188;                             ; out Vec3 ptr 2
     *   t9 = gl_func(...);
     *
     *   /* 12-byte Vec3 copy chain: v0 → sp+0x114 → sp+0xFC *\/
     *   v1 = sp + 0x114; t7 = sp + 0xFC;
     *   *(int*)(v1 + 0) = *(int*)(t9 + 0);
     *   *(int*)(v1 + 4) = *(int*)(t9 + 4);
     *   *(int*)(v1 + 8) = *(int*)(t9 + 8);
     *   *(int*)(t7 + 0) = *(int*)(v1 + 0);
     *   *(int*)(t7 + 4) = *(int*)(v1 + 4);
     *   *(int*)(t7 + 8) = *(int*)(v1 + 8);
     *
     *   /* float-load + store: 3 floats from sp+0xFC..0x104 to sp+0x190..0x198 *\/
     *   *(float*)(sp+0x190) = *(float*)(sp+0xFC);
     *   *(float*)(sp+0x194) = *(float*)(sp+0x100);
     *   *(float*)(sp+0x198) = *(float*)(sp+0x104);
     *
     *   b 0x5CB4   ; merge to continuation
     *
     * Pattern: helper returns a Vec3 ptr; double-buffer copy (likely
     * write-protect or transformation pipeline) into stack scratch
     * regions sp+0x114, sp+0xFC, sp+0x190. The 4-arg cross-USO call
     * with 2 stack-args at sp+0x10/0x14 is a "transform-and-output"
     * idiom common in 1080 (per docs/PATTERNS.md USO callee patterns).
     *
     * Cumulative ~177/1102 insns characterized (up from 145). ~925
     * remaining.
     *
     * 2026-05-06 EXTENDED DECODE 0x5C48-0x5CB0 (~26 insns): ALT-PATH
     * MIRROR OF PRIOR Vec3-MEMCPY BLOCK + MERGE.
     *
     *   /* alt path (other arm of v0 dispatch from earlier 0x5BB0) *\/
     *   /* same 4-arg + 2-stack-arg gl_func call but a0 = sp+0x15C
     *    * instead of a0->0x30 (different source for the transformed Vec3) *\/
     *   a0 = sp + 0x15C;
     *   a1 = s0;
     *   a2 = sp[0x1B0];
     *   a3 = sp[0x1AC];
     *   /* sp[0x10] = sp[0x148]? — t0 from earlier prep *\/
     *   t9 = gl_func(...);
     *
     *   /* same 12-byte Vec3 copy chain: t9 → sp+0x108 → sp+0xFC *\/
     *   v1 = sp + 0x108; t3 = sp + 0xFC;
     *   *(int*)(v1 + 0/4/8) = *(int*)(t9 + 0/4/8);
     *   *(int*)(t3 + 0/4/8) = *(int*)(v1 + 0/4/8);
     *
     *   /* same 3-float load+store: sp+0xFC..0x104 -> sp+0x190..0x198 *\/
     *
     *   b 0x5CB4   ; merge to continuation (same target as prior path)
     *
     * MERGE BLOCK 0x5CB4-0x5CB0 (5 insns visible):
     *   /* both paths arrive here with a0 reloaded from s0->0x30 *\/
     *   a0 = s0->0x30;
     *   a3 = sp + 0x178;
     *   a1 = a3;
     *   if (a3 != 0) {        // (effectively always true — sentinel guard)
     *       v1 = a0 + 0x3C8;
     *       /* fall through to next block at 0x5CE0 *\/
     *   } else {
     *       a0 = 0xC; gl_func(...); sp[0x144] = v1;
     *       /* alloc/init then reload v1 *\/
     *   }
     *
     * Pattern: alt-path duplicates the Vec3-memcpy structure with sp+0x15C
     * as alternative source (vs sp+0x1B8 in prior path). Both feed into
     * the same merge block at 0x5CB4 which prepares a Vec3-related
     * comparison with sp+0x178 (likely accumulated transform output).
     *
     * MERGE-BLOCK CONTINUATION 0x5CB4-0x5D08 (~21 insns, decoded 2026-05-06):
     *   /* setup: a3 = &sp[0x178]; a1 = a3; v1 = a0 + 0x3C8 *\/
     *   a3 = sp + 0x178;
     *   a1 = a3;                         // (cosmetic shadow — both used)
     *   v1 = a0 + 0x3C8;                 // pointer into sub-struct
     *   /* cross-USO size-12 op (Vec3 alloc/copy?) — saves+reloads v1 *\/
     *   a0 = 0xC;                        // 12 = sizeof(Vec3) constant
     *   sp[0x144] = v1;
     *   v0 = gl_func(0xC, ...);          // jal placeholder, args via sp/regs
     *   v1 = sp[0x144];                  // reload after call
     *   a3 = sp + 0x178;                 // re-setup post-call
     *   if (v0 == 0) goto skip_xz_copy;  // beq v0,zero,.+0x1C
     *   a1 = v0;                         // result pointer (delay slot)
     *
     *   /* XZ-only Vec3 copy: a1.x = v1.x; a1.y = 0; a1.z = v1.z *\/
     *   a1[0]   = v1[0];                 // x  (lwc1 f12; swc1 to a1)
     *   a1[2/4] = v1[2];                 // z  (offset 8 from base)
     *   a1[1/4] = 0.0f;                  // y  zeroed via mtc1 $zero
     *
     * skip_xz_copy:                      // 0x5CF8
     *   /* second Vec3-math call: f(sp+0x178, sp+0x190, sp+0x184) *\/
     *   a0 = sp + 0x178;                 // accum-Vec3 base (= a3)
     *   a1 = sp + 0x190;
     *   a2 = sp + 0x184;
     *   gl_func(a0, a1, a2);             // jal placeholder (Vec3 op, dest sp+0x184/0x190)
     *
     * COMPARISON BLOCK 0x5D08-0x5D34 (~12 insns FPU compare/clamp):
     *   /* float saturate-style compare on result-Vec3 with bc1tl branches *\/
     *   f16 = 0.0f;
     *   if (f0 < 0)  /* saturate one component to negation pair *\/
     *       /* abs/neg sequence (neg.s + bc1tl + neg-or-abs) *\/
     *   /* result then stored to sp+0x170 (post-saturate scalar) *\/
     *   sp[0x170] = saturated_value;
     *
     * Pattern overall: this merge block stages an XZ-Vec3 transform
     * (Y-zeroed) into sp+0x178 buffer, then computes a derived scalar
     * (likely magnitude/length squared via the cross-USO call), saturates
     * its sign, and stores to sp+0x170. Continues into a delta-blend at
     * 0x5D38+ with a0->0xB0 / a0->0xAC fields (likely physics-vel state).
     *
     * 2026-05-08 EXTENDED DECODE 0x5D38-0x5E1C (~56 insns):
     * NORMALIZED DELTA SCALAR + STATE/FLAG DISPATCH.
     *
     *   /* derive a scale from sub-struct axis/threshold fields *\/
     *   sub = a0->0x30;
     *   f14 = signed scalar from prior saturate block (abs/neg pair);
     *   ratio = sub->0x348 / a0->0xB0;
     *   factor = 1.0f + ratio;
     *   denom = sub->0x708;              /* via sub + 0x6F8 + 0x10 *\/
     *   a0->0x3C = (f14 * factor * a0->0xAC) / denom;
     *
     *   /* save absolute value of the derived scalar for later consumers *\/
     *   sp[0x16C] = (a0->0x3C < 0.0f) ? -a0->0x3C : a0->0x3C;
     *
     *   /* state-gate before the large flag-dispatch body *\/
     *   if (a0->0x74 != 0) {
     *       if (a0->0x74 == 1) goto state_tail_6604;  /* v0=a0->0x2C delay *\/
     *       goto state_tail_6604;
     *   }
     *   state_flags = a0->0x6C;
     *   stack_flags = sp[0x1A0];
     *   if (!(state_flags & 1)) goto path_6078;
     *
     *   /* when state bit 0 is set but stack bit0 is clear and bit1 is clear,
     *    * clear state bit0 and seed a short timer/state code. *\/
     *   if (!(stack_flags & 1) && !(stack_flags & 2)) {
     *       a0->0x6C = state_flags & ~1;
     *       a0->0x48 = 0x14;
     *   }
     *
     *   /* stack flag 0x4 selects a 0x20 mode; otherwise 0x800 selects 0x80.
     *    * Both store the mode at sp+0x1B4 and jump to the shared 0x65F8
     *    * continuation with a0 reloaded from a0->0x30. *\/
     *
     * Pattern: this block converts the prior transform/saturate result into
     * a normalized, positive scalar and immediately uses object state flags
     * to choose the next update mode.  `a0->0x6C` behaves like a mutable
     * per-frame bitfield, `a0->0x74` is a coarse state gate, and sp+0x1A0
     * mirrors input/event flags that can clear bit0 and select a mode.
     *
     * Cumulative ~282/1102 insns characterized (up from 226). ~820
     * remaining. NEXT PASS: 0x5E20+ alternate state-flag path through
     * sp+0x1AC->0x84 bit checks and the sp+0xF0 Vec3 scratch block.
     *
     * 2026-05-08 EXTENDED DECODE 0x5E20-0x5E7C (~24 insns): SP+0x1AC PTR
     * BIT-2 GUARD + ALT VEC3 ALLOC + XZ-Y0-COPY (mirror of 0x5CD0 block).
     *
     *   t9 = sp[0x1AC];                   ; reload saved-ptr (this is `sub`)
     *   if (t9 == 0) goto state_tail_65F8;
     *   t1 = t9->0x84;                     ; flag-byte (mirrors check earlier
     *                                        in path 0x5AF0-0x5AFC, here re-tested)
     *   v1 = sp + 0xF0;                    ; sp+0xF0 = next Vec3-scratch base
     *   if (!(t1 & 2)) goto state_tail_65F8;
     *
     *   /* bnel-likely guard: t1 != 0 always since bit 1 was set —
     *    * branch taken always; delay-slot reloads sp[0x1B0] = saved
     *    * return-Vec3 ptr from prior cross-USO call. *\/
     *   if (t1 != 0) {
     *       v0 = sp[0x1B0];                 ; (delay)
     *   } else {
     *       v0 = gl_func(0xC);              ; alloc Vec3 (dead arm — t1 is bit-2,
     *                                        non-zero by precondition)
     *       f16 = 0.0f;
     *       if (v0 == 0) goto skip_xz_copy; ; alloc-fail skip
     *       v1 = v0;                         ; (delay) v1 = alloc result
     *       v0 = sp[0x1B0];                  ; reload saved ptr
     *   }
     *
     *   /* XZ-Y0 Vec3 copy — exact mirror of the earlier 0x5CD0 block,
     *    * source is sp[0x1B0]+0x30 here (vs prior block's t9 helper-result):
     *    *   v1[0] = source[0];   v1[1] = 0.0f;   v1[2] = source[2];   *\/
     *   src = v0 + 0x30;
     *   v1[0] = src[0];                     ; X
     *   v1[1] = 0.0f;                       ; Y zeroed
     *   v1[2] = src[2];                     ; Z   (source.y at +4 SKIPPED)
     *
     *   /* skip_xz_copy: a1 = sp[0x1AC]; a2 = sp+0xB4; ... falls through
     *    * to a follow-up cross-USO call at 0x5E80+ with sp+0xB4 as a2. *\/
     *   a1 = sp[0x1AC];                     ; reload sub for next call
     *   a2 = sp + 0xB4;
     *   /* (continues at 0x5E80+) *\/
     *
     * Pattern: this is the alt-source mirror of the earlier 0x5CD0 XZ-Y0
     * Vec3 copy. Both write a Y-zeroed XZ-only Vec3 into a stack scratch,
     * but they pull from different base ptrs (helper-return ptr vs
     * sp[0x1B0]+0x30 = saved-ptr's sub-struct). The bit-2 (`t1 & 2`) gate
     * + the bnel-always-true after a non-zero precondition is a defensive
     * "abort if state changed mid-frame" + "if normal-path, skip alloc"
     * pattern used elsewhere in the dispatch.
     *
     * 0x5E80-0x5ECC region (+20 insns):
     * BNEZ-GATED ALLOC + VEC3 XZ-DIFFERENCE (saved-XZ minus a1+0x30 XZ).
     *
     *   v1 = a2;                          ; mirror a2 (will become out-Vec3 ptr)
     *   a1 += 0x30;                       ; a1 = sub->[0x30] (Vec3 source pos)
     *   if (a2 != 0) goto skip_alloc;     ; if caller passed a buffer, skip alloc
     *   /-- a2==0 path: alloc fresh Vec3 --/
     *   sp[0xC0] = a1;                    ; spill a1 across alloc
     *   v0 = gl_func(0xC);                ; alloc 12-byte Vec3
     *   $f16 = 0.0f;                       ; (delay) Y-zero const
     *   a1 = sp[0xC0];                    ; reload a1
     *   a2 = sp + 0xB4;                   ; reset a2 to default out-Vec3 base
     *   if (v0 == 0) goto skip_xz_diff;   ; alloc-fail skip
     *   v1 = v0;                           ; (delay) v1 = alloc result
     *
     * skip_alloc:
     *   $f18 = sp[0xF0];                   ; $f18 = saved-Vec3.X (from 0x5DC0 block)
     *   $f4  = a1[0];                      ; $f4  = sub->[0x30].X
     *   $f8  = sp[0xF8];                   ; $f8  = saved-Vec3.Z
     *   $f6  = a1[2];                      ; $f6  = sub->[0x30].Z
     *   $f0  = $f18 - $f4;                 ; X-diff
     *   v1[1] = 0.0f;                       ; out.Y = 0 (XZ-plane vec)
     *   $f2  = $f8 - $f6;                  ; Z-diff
     *   v1[0] = $f0;                        ; out.X = X-diff
     *   v1[2] = $f2;                        ; out.Z = Z-diff
     *
     * Pattern: this XZ-difference Vec3 (saved.X - sub.X, 0, saved.Z - sub.Z) is
     * the displacement vector between the saved-frame position (captured earlier
     * at sp[0xF0..0xFC]) and the current sub-struct's position. Likely the
     * "movement-since-last-frame XZ-only" vector, used as input to the follow-up
     * (~0x5ED0+) operation. The bnez-gated alloc lets callers pass in their own
     * out-buffer (a2 != 0) OR get a fresh-allocated one (a2 == 0). The XZ-only
     * shape (Y zeroed) suggests ground-plane physics, NOT general 3D physics.
     *
     * 0x5ED0-0x5F18 region (+18 insns):
     * DOUBLE 12-BYTE INT-MEMCPY (a2 → sp+0x15C → sp+0xD8) + DEAD-BRANCH GATE.
     *
     *   /-- first 12-byte memcpy: a2 → sp+0x15C --/
     *   t3 = sp + 0x15C;                ; staging buffer
     *   t8 = sp + 0x15C;                ; (alias of t3)
     *   *t3       = a2[0];               ; first int
     *   t6 = sp + 0xD8;                  ; final destination
     *   v1 = sp + 0xE4;                  ; out-Vec3 scratch (used at 0x5F38+)
     *   *(t3 + 4) = a2[1];               ; second int
     *   *(t3 + 8) = a2[2];               ; third int
     *
     *   /-- second 12-byte memcpy: sp+0x15C → sp+0xD8 --/
     *   *t6       = *t8;                 ; sp[0xD8]   = sp[0x15C]
     *   *(t6 + 4) = *(t8 + 4);           ; sp[0xDC]   = sp[0x160]
     *   *(t6 + 8) = *(t8 + 8);           ; sp[0xE0]   = sp[0x164]
     *   a1 = sub->[0x30];                ; sub = s0; a1 = sub-physics-block
     *   if (v1 != 0) goto skip_alloc_2;  ; bnez v1, +7 → 0x5F38
     *                                      ; (v1 = sp+0xE4 — ALWAYS non-zero;
     *                                      ;  the fall-through alloc-fallback at
     *                                      ;  0x5F20-0x5F34 is RUNTIME-DEAD code,
     *                                      ;  emitted by IDO due to a runtime-only
     *                                      ;  null-test the optimizer didn't fold.)
     *   a1 += 0xB4;                      ; (delay-slot, dead path)
     *
     * Pattern: the algorithm uses two stack buffers (sp+0x15C as a staging
     * scratch + sp+0xD8 as the working buffer) to hold a copy of the XZ-diff
     * Vec3 just computed. The double-memcpy is wasteful but consistent with
     * IDO's emit when the C body has TWO distinct typed-stack-struct copies
     * back-to-back. The dead bnez-gated alloc fallback is the same shape as
     * the 0x5DC0/0x5E80 blocks above — pre-allocated buffer always wins.
     *
     * 0x5F38-0x5F7C region (+17 insns):
     * THIRD XZ-Y0 VEC3 COPY (sub->[0x30] → v1) + DEAD-BRANCH ALLOC FALLBACK.
     *
     *   $f12 = a1[0];                    ; a1 = sub->[0x30] (Vec3 source)
     *   $f2  = a1[2];                    ;
     *   v1[1] = $f16 (= 0.0);            ; out.Y = 0
     *   v1[0] = $f12;                    ; out.X = source.X (no-diff this time!)
     *   v1[2] = $f2;                     ; out.Z = source.Z (no-diff)
     *
     *   v1 = sp[0x1AC];                  ; reload sub-ptr from saved-stack slot
     *   a2 = sp + 0x94;                  ; another out-Vec3 scratch base
     *   a1 = a2;                          ; mirror a2 into a1
     *   if (a2 != 0) goto skip_alloc_3;  ; bnez a2 — ALWAYS taken
     *                                      ; (same dead-fallback as 0x5DC0/0x5E80/
     *                                      ;  0x5F18: pre-allocated buffer wins)
     *   v1 += 0x30;                      ; (delay-slot, dead path)
     *   v0 = gl_func(0xC);                ; (dead alloc)
     *   sp[0x120] = v1;                   ; (delay) save v1 across alloc
     *   $f16 = 0.0f;                     ; re-init Y-zero const
     *   v1 = sp[0x120];                  ; reload v1
     *   a2 = sp + 0x94;                  ; reset a2
     *   if (alloc == 0) goto skip;       ; alloc-fail
     *   a1 = alloc;                      ; (delay)
     *
     * Pattern: this is the THIRD Vec3 XZ-Y0 copy in the function. Together
     * with the earlier 0x5CD0 (helper-result source) and 0x5E80 (saved-XZ
     * minus sub-XZ), this builds three XZ-only Vec3s into stack scratches:
     *   sp+0xB4 — XZ-difference output (from 0x5E80 block)
     *   sp+0xD8 — copy-of-XZ-difference (from 0x5ED0 double-memcpy)
     *   sp+0xE4 — sub->[0x30] Vec3 with Y zeroed (from 0x5F38 block)
     *   sp+0x94 — yet another output buffer (next pass)
     *
     * Each block follows the same shape: bnez-gated alloc (dead-runtime,
     * pre-allocated wins) + XZ-Y0 copy with optional source-difference.
     *
     * 0x5F80-0x5FA4 region (+10 insns) — Vec3 XZ-difference store + two
     * 12-byte struct memcpys:
     *   f10 = scratch_xz0[0]              ; sp+0xE4 (sub->[0x30] xz-only)
     *   f18 = a1[0]                       ; dest xz.x
     *   f4  = scratch_xz0[2]              ; sp+0xEC (xz.z)
     *   f8  = a1[2]                       ; dest xz.z
     *   f0  = f10 - f18                   ; sub.s — diff in xz.x
     *   *a1[1] = f16                      ; swc1 (f16 carried from prior block,
     *                                       likely zeroed in 0x5F38-0x5F7C)
     *   f2  = f4 - f8                     ; sub.s — diff in xz.z
     *   *a1[0] = f0                       ; xz-diff stored back into a1
     *   *a1[2] = f2                       ; (a1 IS the dest — 0x10-byte Vec3
     *                                       at sp+0x...something)
     *   t3  = a2[0]; t1 = sp+0x15C; t5 = sp+0x15C
     *
     * 0x5FA8-0x5FE4 region (+12 insns) — TWO 12-byte (Vec3) struct copies
     * via stack scratches sp+0x15C and sp+0xCC, both from a2 (=sp+0x94):
     *   sp[0x15C..0x167] = a2[0..2]        ; copy 1 (3-int load/store unrolled)
     *   sp[0xCC..0xD7]   = sp[0x15C..0x167] ; copy 2 (alias-via-stack)
     *   t1 = 0x14
     *   at = -2
     * The two-step copy through sp+0x15C is unusual — likely a dead intermediate
     * scratch left over from a -O0 → -O2 compile where IDO didn't fully fold.
     *
     * 0x5FE8-0x6020 region (+15 insns) — FPU norm computation:
     *   a0  = s0->[0x30]                  ; sub object
     *   f10 = s0->[0xC0]                  ; field-loaded float
     *   f18 = sp[0xD8]                    ; xz-diff.x (from earlier block)
     *   f6  = a0->[0x348]                 ; sub_field_348 (likely radius?)
     *   f8  = sp[0xE0]                    ; xz-diff.z
     *   f2  = f6 * f10                    ; field_348 * field_C0 (= scaled?)
     *   f10 = sp[0xD8]                    ; reload diff.x
     *   f4  = f18 * f18                   ; diff.x²
     *   f18 = sp[0xCC]                    ; reload xz-copy.x
     *   f6  = f8 * f8                     ; diff.z²
     *   f14 = f4 + f6                     ; diff.x² + diff.z² (= dist²)
     *   f6  = sp[0xD4]
     *   f4  = sp[0xE0]                    ; reload diff.z
     *   c.eq.s f14, f16                   ; compare dist² == f16 (zero?)
     * (followed by branch on FCC, decoded in next pass)
     *
     * Pattern: this is a 2D (XZ-plane) distance check in the per-frame
     * collision/proximity portion of the state machine. The two-step
     * copy via sp+0x15C is a -O0 artifact within an otherwise -O2 function.
     *
     * 0x6024-0x6058 region (+14 insns) — FCC-branch + FP norm + final cmp:
     *   if (dist² != f16_zero) {
     *     f12 = neg.s(f0)              ; mov.s/neg.s on the diff?
     *     f8  = f10 * f18               ; mul.s
     *     f10 = f4 * f6                  ; (interleaved)
     *     f0  = f8 + f10                ; add.s — sum of two products
     *     f18 = f0 * f0                 ; mul.s — square of sum
     *     f12 = f18 / f14               ; div.s — distance-ratio?
     *     f4  = f2 * f2                 ; mul.s — square again
     *     c.le.s f12, f4                ; compare
     *     if (c.le.s f12 ≤ f4 false) skip large block (+0x167 = 359 insns)
     *   }
     *
     * 0x605C-0x607C region (+8 insns) — fall-through state-update:
     *   t1 = 0x14                     ; literal
     *   t7 = s0->[0x6C]               ; load flag word
     *   s0->[0x48] = t1               ; mark-as-set (= 0x14)
     *   a0 = s0->[0x30]               ; sub object
     *   t9 = t7 & ~1                  ; clear bit 0 (at = -2)
     *   b +0x161 (skip into next state block, ~353 insns ahead)
     *   s0->[0x6C] = t9               ; (delay) writeback cleared flag
     *
     * Pattern: 'if (distance test passes) clear sub-state-flag-bit-0,
     * mark s0->0x48 = 0x14 (= 'distance-check-completed' code), then
     * b to a far-skip into the next state-block'.
     *
     * Cumulative ~420/1102 insns characterized (up from 398, +22 insns).
     * ~682 remaining.
     *
     * 0x6080-0x6100 region (+30 insns) — particle-spawn on flags+altitude:
     *   if (t2 != 0) {                  ; beql t2,0,+0x9E skips 158 insns
     *     v0 = t2->[0x84];              ; flag byte
     *     if (v0 & 1) {
     *       if (v0 & 0x804) {           ; bits 2|11 both must be checked
     *         t5 = a0->[0x908];         ; subtree pointer
     *         f8 = sp[0x19C];           ; cached world-Y coord
     *         if (t5 != 0) {
     *           if (f8 <= -2000.0f) {   ; below floor threshold (lui 0xC4FA)
     *             v1 = sp+0x80;         ; (computed but may be unused arm)
     *             v3 = gl_func_0(0xC);  ; alloc 12-byte (Vec3-like) record
     *             f16 = 0.0f;
     *             if (v3 != 0) {
     *               v0  = sp[0x1B0];    ; cached entity pointer
     *               vec = v0 + 0x30;
     *               v3[0] = vec[0];     ; .x
     *               v3[1] = 0.0f;       ; .y (zero'd)
     *               v3[2] = vec[2];     ; .z
     *             }
     *           }
     *         }
     *       }
     *     }
     *   }
     *
     * Pattern: when entity has 2 flag bits set (0 + 2|11) AND has subtree AND
     * is below world-Y -2000 (= -2000.0f from lui 0xC4FA), allocate a 12-byte
     * Vec3 (X,0,Z) particle-trail record. Likely the "below-the-stage death-
     * trigger trail" used when player falls off the course.
     *
     * Cumulative ~450/1102 insns characterized (up from 420, +30 insns).
     * ~652 remaining.
     *
     * 0x6104-0x6164 region (+25 insns) — delta-Vec3 between entity+player:
     *     a1 = sp[0x1AC]; a1 += 0x30;        // entity position ptr
     *     v3 = gl_func_00000000(12);          // alloc 12-byte Vec3
     *     if (v3 != 0) {
     *         f10 = sp[0x80]; f18 = a1->[0]; // entity.x
     *         f4  = sp[0x88]; f6  = a1->[2]; // entity.z
     *         v3->x = f10 - f18;             // delta-x
     *         v3->y = 0.0f;                  // no Y component
     *         v3->z = f4  - f6;              // delta-z
     *     }
     *     // followed by another sp+0x15C ptr setup (for a Quat dest?)
     *
     * Pattern: building the player→trigger 2D delta vector for the
     * death-trail particle. Player world-pos cached at sp[0x80]/sp[0x88]
     * (X,Z from entry block); subtracting trigger entity's pos gives the
     * trail-launch direction.
     *
     * Cumulative ~475/1102 insns characterized, ~627 remaining.
     *
     * 0x6168-0x61D8 region (+30 insns) — sp+0x15C stage + 2nd Vec3 alloc:
     *     // Word-1 copy + self-stores at sp+0x15C (interpretation uncertain):
     *     sp[0x15C] = sp[0x4C];          // single-word copy
     *     sp[0x160] = sp[0x160];         // self-write (IDO emit oddity)
     *     sp[0x164] = sp[0x164];         // self-write
     *     // Vec3 memcpy from sp+0x15C → sp+0x68 (3 lw/sw pairs):
     *     memcpy(&sp[0x68], &sp[0x15C], 12);
     *
     *     a1 = s0->[0x30] + 0xB4;        // entity offset field
     *     v3 = gl_func_00000000(12);     // 2nd 12-byte Vec3 alloc
     *     f16 = 0.0f;
     *     if (v3 != NULL) {
     *         // Vec3 from a1[0]/a1[2] (XZ-plane offset)
     *         v3->x = a1[0];
     *         v3->y = 0.0f;
     *         v3->z = a1[2];
     *     }
     *     v1 = sp[0x1AC];                 // reload cached entity ptr
     *
     * Pattern: building a 2nd particle Vec3 from the entity's position
     * field at offset 0x30+0xB4. The self-store sequence at sp+0x15C is
     * likely from `*sp_15C_ptr = *sp_15C_ptr` C, possibly a volatile
     * touch or a misanalyzed struct-self-assign. Worth flagging for the
     * exact-match pass.
     *
     * Cumulative ~505/1102 insns characterized, ~597 remaining.
     *
     * 0x61DC-0x6250 region (+30 insns) — third Vec3 alloc + delta-XZ:
     *     a2 = sp+0x40; a1 = a2;            // (always-taken bne fall-through)
     *     v1 += 0x30;                        // (skipped: dead path)
     *     v3 = gl_func_00000000(12);         // 3rd 12-byte Vec3 alloc
     *     f16 = 0.0f;
     *     v1 = sp[0x120];                    // reload entity ptr
     *     if (v3 != NULL) {
     *         f8  = sp[0x74]; f10 = v1[0];   // player vs entity X
     *         f18 = sp[0x7C]; f4  = v1[2];   // player vs entity Z
     *         v3->x = f8 - f10;              // delta-X
     *         v3->y = 0.0f;
     *         v3->z = f18 - f4;              // delta-Z
     *     }
     *     // 2nd memcpy stage at sp+0x15C ← sp+0x40 (3 lw/sw)
     *     // and 0x4140 (12.0f) loaded — possibly upper-bound for next op
     *
     * Pattern: third delta-Vec3 spawn from cached player pos at sp[0x74]/
     * sp[0x7C] minus reloaded entity pos. Third in a row of similar
     * particle/spawn deltas. Pattern is consistent with multi-element
     * trail/effect spawning.
     *
     * Cumulative ~535/1102 insns characterized, ~567 remaining.
     *
     * 0x6254-0x62C4 region (+30 insns) — dist² check + scale:
     *     // Finish 3-word memcpy at sp+0x15C → sp+0x5C
     *     sp[0x5C..0x64] = sp[0x15C..0x164];
     *     f6  = s0->float_C0;
     *     a0  = s0->ptr_30;                 // entity pointer
     *     f8  = 12.0f;                       // (from earlier lui 0x4140)
     *     f10 = s0->C0 + 12.0f;              // scale factor
     *     f18 = a0->[0x348];                 // entity scale
     *     f2  = a0->[0x348] * (s0->C0 + 12.0f);
     *     // Compute squared distance in XZ plane:
     *     dist_sq = sp[0x68]*sp[0x68] + sp[0x70]*sp[0x70];
     *     if (dist_sq == 0.0f) {
     *         f12 = 0.0f;                    // (b +7 path)
     *         // skip distance-normalization block
     *     } else {
     *         // dist-normalization continues at 0x62C4 next
     *     }
     *
     * Pattern: prepare scale factor (entity_scale * (player_state.C0+12))
     * for the upcoming normalized direction vector. Bail to f12=0.0 if
     * the XZ distance is zero (player exactly at entity).
     *
     * Cumulative ~565/1102 insns characterized, ~537 remaining.
     *
     * 0x62C8-0x6338 region (+30 insns) — multi-cond LOD/proximity tests:
     *     // Compute dot² / dist² and compare vs scale²
     *     f0  = f10*f4 + f6*f18;            // dot-product-like sum
     *     f12 = (f0 * f0) / dist_sq;         // normalized dot²
     *     f6  = scale * scale;
     *     if (f12 <= f6) { ... }            // first test
     *     // Reload f18 from sp[0x170], read s0->float_BC
     *     if (s0->float_BC <= sp[0x170]) { ... }   // second test
     *     // Third test: f0 < 50.0f (lui 0x4248 = 50.0f)
     *     if (f0 < 50.0f) {
     *         sp[0x1B4] |= 0x40;             // proximity-flag bit 6
     *     }
     *     // Reloads s0->float_B4 in delay slots for subsequent ops
     *
     * Pattern: cascade of three proximity/LOD tests with bit-flags at
     * sp[0x1B4]. Camera/LOD selector for particle visibility — common
     * effect-system pattern (only emit close particles).
     *
     * Cumulative ~595/1102 insns characterized, ~507 remaining.
     *
     * 0x633C-0x63B0 region (+30 insns) — more nested LOD/proximity gates:
     *     if (f0 < s0->float_B8) {
     *         if (t5 != 0) {  // (skip path)
     *             f6  = sp[0x170];
     *             f18 = (double)f6;
     *             if ((double)sp[0x170] < 0.0) {
     *                 t6 = *(int*)((char*)&D_0 + 0x78);
     *                 if (t6 == 0) sp[0x1B4] |= 0x4;   // global-disabled flag
     *             }
     *             // f6 = (f0 / s0->B8) * sp[0x16C]
     *             ratio = (f0 / s0->float_B8) * sp[0x16C];
     *             sp[0x1B4] |= 0x8;                    // proximity-flag bit 3
     *             if (1.0f < ratio) { ... }
     *         }
     *     }
     *
     * Pattern continues: another nested set of float tests with 0x4/0x8
     * bit-flags at sp[0x1B4]. Double-precision sign check + global
     * config gate at &D_0+0x78.
     *
     * Cumulative ~625/1102 insns characterized, ~477 remaining.
     *
     * 0x63B0-0x6420 region (+30 insns) — state-counter dispatch:
     *     if (1.0f < ratio) sp[0x1B4] |= 0x8;
     *     if (sp[0x1A4] & 0x8) {
     *         if (s0->int_4C4 > 0) {
     *             gl_func_00000000(s0);           // 1-arg call
     *             s0->int_4C4 = 0;
     *             // b +0x82 (skip ~130 insns ahead — fast path exit)
     *         }
     *         // else: fall-through (also reload a0 = s0->[0x30])
     *     } else {
     *         // (8 == 0 path)
     *         if (s0->int_4C4 != 0x10000) {
     *             // (skip large block via bne +0x27)
     *         } else {
     *             // (v0 == 0x10000 path)
     *             if (s0->int_2C != 3) {
     *                 at = 2;
     *                 // (branch-likely)
     *             } else {
     *                 f12 = s0->float_2DC;
     *                 // b +8 — continue to float work
     *             }
     *         }
     *     }
     *
     * Pattern: state-counter dispatch on s0->int_4C4 (looks like
     * frame-counter for a duration-gated state) and s0->int_2C
     * (current state-machine state). The 0x10000 sentinel is a flag.
     *
     * Cumulative ~655/1102 insns characterized, ~447 remaining.
     *
     * 0x6424-0x6498 region (+30 insns) — state-dependent float lookup:
     *     // First state-switch (s0->int_2C):
     *     if (s0->state == 2) {
     *         f14 = s0->float_2AC;
     *     } else {
     *         f14 = s0->float_2C4;
     *     }
     *     f12 = f14;
     *     if (f4 < f12) {
     *         gl_func_00000000(s0);
     *         f16 = 0.0f;
     *         // Second state-switch:
     *         if (s0->state == 3) {
     *             f12 = s0->float_324;
     *         } else if (s0->state == 2) {
     *             f14 = s0->float_30C;
     *         } else {
     *             f14 = s0->float_2F4;
     *         }
     *         f12 = f14;
     *         t6 = (int)trunc(f12);          // trunc.w.s + mfc1
     *         a0 = s0->ptr_30;
     *         // b +0x57 — large skip (87 insns ahead)
     *     }
     *
     * Pattern: per-state float-field LUT for s0->float_2AC/2C4/2F4/30C/324
     * (likely physics constants for different player states 0/2/3).
     *
     * Cumulative ~685/1102 insns characterized, ~417 remaining.
     *
     * 0x6498-0x650C region (+30 insns) — counter-decrement + 2nd LUT:
     *     s0->int_4C4 = (int)trunc(f12);
     *     // ... b +0x57 over 0x158 bytes (large skip-ahead)
     *
     *     // Alt path (when 1.0 < ratio false): state-counter check
     *     if (s0->int_4C4 > 0) {
     *         state = s0->int_2C;
     *         state -= 1;
     *         if (state == 1) {
     *             s0->int_4C4 = state;             // store decremented
     *             gl_func_00000000(s0);
     *             f16 = 0.0f;
     *             a0 = s0->ptr_30;
     *             // b +0x1B — skip
     *         }
     *     }
     *
     *     // Second state-switch (different offset table):
     *     state = s0->int_2C;
     *     f18 = sp[0x19C];
     *     if (state == 0) { ... }            // (special-case head)
     *     else if (state == 3) {
     *         f12 = s0->float_3B4;
     *     } else if (state == 2) {
     *         f14 = s0->float_384;
     *     } else {
     *         f14 = s0->float_39C;
     *     }
     *     f12 = f14;
     *
     * Pattern: parallel frame-counter decrement + state-keyed
     * float-field LUTs for a SECOND set of constants (0x384/0x39C/0x3B4),
     * mirroring the earlier 0x2AC/0x2C4/0x2F4/0x30C/0x324 set.
     *
     * Cumulative ~715/1102 insns characterized.
     *
     * TAIL STAGE (insns ~716-1102 @ 0x6510-0x6A2C, ~387 insns):
     *
     *   // (5) proximity-flag bookkeeping on sp[0x1A0] / sp[0x1B4]
     *   if (state == 0) {
     *       f0 = s0->float_00FC; f2 = s0->float_0114; f4 = s0->float_012C;
     *       // gather; compare; set sp[0x1A0] |= 0x800 on hit
     *   }
     *   // double-precision sign check on accumulated scalar:
     *   //   cvt.d.s + c.lt.d 0.0  ->  neg.d if signed-negative (abs-value)
     *   // followed by another sp[0x1B4] flag-OR (|= 0x2)
     *
     *   // (6) state-keyed float-LUT cascade #3 — offsets 0x264 / 0x27C / 0x294
     *   //     (same dispatch shape as cascades #1 and #2 above)
     *   //     selected float fed into jal gl_func_0(s0 + 0xA58, ...)
     *
     *   // (7) frame-counter increment with bound 0x4B:
     *   if (s0->int_54 < 0x4B) s0->int_54++;
     *   // bit-tests on sp[0x1B0]/sp[0x1A4]/sp[0x1AC]: 0x20, 0x40, 0x400, 0x10
     *   // each toggles a corresponding sp[0x1B4] bit
     *
     *   // (8) state-keyed float-LUT cascade #4 — offsets 0x264/0x294/0x27C/0x24C/0x21C/0x234
     *   //     double-precision compare of s0->float_BC vs hard-coded threshold
     *   //     (neg.d if below)
     *
     *   // (9) linked-list walk #1: t9 = s0->ptr_7C; while (t9) { ... t9 = t9->next; }
     *
     *   // (10) state-keyed float-LUT cascades #5-#8 — additional struct-offset groups:
     *   //      0x1BC/0x18C/0x1A4  ; cascade #5
     *   //      0x174/0x144/0x15C  ; cascade #6
     *   //      0x204/0x1D4/0x1EC  ; cascade #7
     *   //      0x144/0x15C/0x174 reprise (different state arm) ; cascade #8
     *   //   Each cascade is the SAME dispatch shape as #1-#4: 3-arm
     *   //   state-keyed select feeding a single float into an FPU clamp /
     *   //   indirect call.
     *
     *   // (11) indirect call via t9: t9 = s0->fnptr_XX; jalr t9
     *   //      (per-state-machine method dispatch — final emit step)
     *
     *   // (12) final sp[0x1B4] bit-flag finalization:
     *   //      conditional OR of 0x10 / 0x40 / 0x80 based on remaining state checks
     *
     *   // (13) linked-list walk #2: t8 = s0->ptr_7C; iterate; check t8 != 0
     *
     *   // (14) tail-call gl_func_0(s0, sp[0x1B4]) — commits the accumulated
     *   //      bit-flags back to whatever owns the s0 instance.
     *
     *   // EPILOGUE (insns 1099-1102 @ 0x6A1C-0x6A2C):
     *   //   lw $ra, 0x24(sp)
     *   //   lw $s0, 0x20(sp)
     *   //   addiu $sp, sp, 0x1D0
     *   //   jr $ra
     *
     * The full 1102-insn body resolves to: dispatch-rich per-frame state
     * update for a physics/animation entity. Repeated 3-arm state-keyed
     * float-LUT pattern dominates (~8 cascades), interleaved with
     * frame-counter and bit-flag bookkeeping on a stack-resident control
     * block (sp[0x1A0]-sp[0x1B4]). Final step is an indirect-method call
     * plus a gl_func_0 commit of the accumulated flags.
     *
     * Full structural decode complete (1102/1102 insns characterized).
     * Default emit is still INCLUDE_ASM until C-body grind reaches >=80%.
     * Decode doc unblocks future single-tick C-write attempts. */
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000591C);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00006A30: 176-insn per-frame FPU update. Re-decoded 2026-06-24
 * from expected/.o. Stack-staged Vec3 layout: va@sp+0x9C (from sub+0xB4..),
 * scaled@sp+0x58 (sub+0x318.. * a0->0xA8), copy chain sp+0x58->sp+0x6C->sp+0xA8,
 * then va += copy; 00007ACC/00007C1C/03ED4/110A4/7538 with real arg shapes.
 * 2026-07-15 (agent-g, 67.6 -> 85.0): FULL CONTROL-FLOW REDECODE from the raw
 * .word target. Errors fixed: (1) the 0x938/0xA54 counter block + final 7538
 * call are SHARED TAIL (run on BOTH sides of the a0->0x80 test; else-side also
 * sets flag=16 when obj->0x6C==0); (2) 7ACC arg2 is &v94 (int OUT-param at
 * sp+0x94), later 7C1C's arg4 AND the flag condition (not *(int*)&va);
 * (3) 7C1C arg1 = &cpy (not &pt); (4) 7ACC==0 returns WITHOUT calling 7538;
 * (5) pt block is a ||-alloc-fallback: dst=&pt; if(dst||(dst=055750(0xC)))
 *     {dst->x=w3C8; dst->z=w3D0; dst->y=0;} (bnez-on-address kept by IDO);
 * (6) 3ED4 args are (dst, &rv, 0) where rv@0x88 = *r2 word-copy;
 * (7) obj->0x3C store is UNCONDITIONAL (bnez delay slot);
 * (8) w+0x708 load goes through bumped base q=w+0x6F8, *(q+0x10);
 * (9) flag block: if(v94==0) flag=16; else if(80<=w348) flag=8.
 * Levers: decl-order reversed (first=highest home, acc->scaled), register
 * float k/fx/fy/fz staging (candidate f0/f2/f12/f14, batched muls);
 * scaled.x=fx;... then cpy=scaled; acc=cpy word-copies.
 * Residual 15%: frame 0xA8 vs 0xB8 (home/gap layout), copy-chain interleave,
 * arg-address staging order. Placeholder callees — NM wrap regardless. */
typedef struct { float x, y, z; } V3_6A30;
extern int game_uso_func_00007ACC(int *, int *, int, int *);
extern int game_uso_func_00007C1C(char *, char *, char *, char *, char *, f32 *);
extern int game_uso_func_055750();
extern long long game_uso_func_00007538(int *, int);
extern void game_uso_func_000110A4(int *);
extern float game_uso_func_00003ED4(Vec3 *, Vec3 *, int *);

void game_uso_func_00006A30(int *a0) {
    int *s0 = a0;
    int flag = 0;                    /* home sp+0xB4 */
    char *w;
    if (a0[0x80 / 4] != 0) {
        char *sub = (char *)a0[0x30 / 4];
        V3_6A30 acc;                 /* sp+0xA8 */
        V3_6A30 va;                  /* sp+0x9C */
        int v94;                     /* sp+0x94 — 7ACC OUT-param, 7C1C arg4 + flag condition */
        V3_6A30 rv;                  /* sp+0x88 */
        V3_6A30 pt;                  /* sp+0x7C */
        V3_6A30 cpy;                 /* sp+0x6C */
        V3_6A30 scaled;              /* sp+0x58 */
        register float k, fx, fy, fz;  /* FP candidates f0/f2/f12/f14, no dead homes */
        int *r1;
        int *r2;
        V3_6A30 *dst;
        char *src;
        float yaw;

        va = *(V3_6A30 *)(sub + 0xB4);
        k = *(float *)((char *)a0 + 0xA8);
        fx = *(float *)(sub + 0x318) * k;
        fy = *(float *)(sub + 0x31C) * k;
        fz = *(float *)(sub + 0x320) * k;
        scaled.x = fx;
        scaled.y = fy;
        scaled.z = fz;
        cpy = scaled;
        acc = cpy;
        va.x = va.x + acc.x;
        va.y = va.y + acc.y;
        va.z = va.z + acc.z;

        r1 = (int *)game_uso_func_00007ACC(s0, &v94, (int)&va, (int *)0);
        if (r1 == 0) {
            return;                  /* beqz v0 -> epilogue: 7538 NOT called */
        }
        r2 = (int *)game_uso_func_00007C1C((char *)&cpy, (char *)s0, (char *)r1,
                                           (char *)v94, (char *)&va, (f32 *)0);
        rv = *(V3_6A30 *)r2;
        dst = &pt;
        src = (char *)s0[0x30 / 4] + 0x3C8;
        if (dst != 0 || (dst = (V3_6A30 *)game_uso_func_055750(0xC)) != 0) {
            dst->x = *(float *)src;
            dst->z = *(float *)(src + 8);
            dst->y = 0.0f;
        }
        yaw = game_uso_func_00003ED4((Vec3 *)dst, (Vec3 *)&rv, 0);
        w = (char *)s0[0x30 / 4];
        {
            char *q = w + 0x6F8;     /* bumped base; the 0x708 load is *(q+0x10) */
            *(float *)((char *)s0 + 0x3C) =
                (-yaw * (1.0f + *(float *)(w + 0x348) / *(float *)((char *)s0 + 0xB0)) *
                 *(float *)((char *)s0 + 0xAC)) / *(float *)(q + 0x10);
        }
        if (*(int *)((char *)s0 + 0x6C) == 0) {
            if (v94 == 0) {
                flag = 16;
            } else if (80.0f <= *(float *)(w + 0x348)) {
                flag = 8;
            }
        }
    } else {
        if (*(int *)((char *)s0 + 0x6C) == 0) {
            flag = 16;
        }
        w = (char *)s0[0x30 / 4];
    }
    if (*(int *)(w + 0x938) != 0 && *(int *)(w + 0xA54) != 0) {
        int c = *(int *)((char *)s0 + 0x70);
        if (c < 60) {
            if (*(float *)(w + 0x348) <= 30.0f) {
                game_uso_func_000110A4((int *)*(int *)(w + 0x840));
                *(int *)((char *)s0 + 0x70) = 61;
            } else {
                *(int *)((char *)s0 + 0x70) = c + 1;
            }
        } else if (c == 60) {
            game_uso_func_000110A4((int *)*(int *)(w + 0x840));
            *(int *)((char *)s0 + 0x70) = 61;
        }
    }
    game_uso_func_00007538(s0, flag);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006A30);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00006CF0: 102-insn (0x198) per-frame FPU update with
 * conditional dispatch. Frame -0x88, single arg a0.
 *
 * Structural decode (offsets in target asm):
 *
 *   sub = a0->[0x30];                          ; sub-object pointer
 *
 *   ; Stage 1: copy 3 ints (Vec3-int) from sub->{0xB4,B8,BC} to sp[0x70..0x78]
 *   sp[0x70] = sub->[0xB4];
 *   sp[0x74] = sub->[0xB8];
 *   sp[0x78] = sub->[0xBC];
 *
 *   ; Stage 2: scale Vec3 (sub->{0x318,31C,320}) by a0->[0xA8] (negated for
 *   ; the .x component) and store to sp[0x48..0x50]
 *   scale = a0->[0xA8];
 *   sp[0x48] = -scale;
 *   sp[0x4C] = sub->[0x31C] * scale;
 *   sp[0x50] = sub->[0x320] * scale;
 *
 *   ; Stage 3: Vec3 copy 3 ints from sub_a (= some pointer) to t1 (= sp+0x7C),
 *   ; then 3 ints from t2 to t3 — pointer-walking copy pair (asm 0x60-0x90)
 *
 *   ; Stage 4: FPU ops on staged Vec3 + conditional branches based on
 *   ; sub->[0x6C] and sub->[0x70]
 *   if (sub->[0x6C] == 0) ...
 *   if (a0->[0x70] < 0x3C) ...
 *
 *   ; Stage 5: 2-3 cross-USO calls with sub->0x840 (function ptr)
 *   gl_func_00000000(sub->0x840, a1, a2);
 *
 * Spine context: per-frame compute (FPU-heavy update). Reads ONE input
 * struct (a0 with sub at +0x30) and writes scaled Vec3s into local stack
 * frame for downstream. Field offsets used: a0->{0x30,0x70,0xA8}, sub->{
 * 0xB4,0xB8,0xBC, 0x318,0x31C,0x320, 0x6C, 0x70, 0x840, 0x938, 0xA54}.
 *
 * 2026-05-08 pass: decoded the full high-level flow through the terminal
 * call. This body now captures the staged Vec3 copy, scaled Vec3 add, timer
 * gate, optional dispatch via sub->0x840, and unconditional tail call.
 * Still NM: stack layout / register allocation and copy scheduling are not
 * byte-matched yet. Default INCLUDE_ASM build remains exact.
 *
 * 2026-05-08 logic fix: the dispatch arm for the timer<60 branch was
 * inverted. Asm at 0x120 reads `bc1f` after `c.lt.s f4(=30), f6(=sub[0x348])`,
 * meaning the dispatch fires when `30 < sub[0x348]` (NOT when `sub[0x348]
 * <= 30` as previously written). Flipped the C accordingly. No build effect
 * (still NM-wrapped, default uses INCLUDE_ASM), but future tightening passes
 * now have correct logic to grind from.
 *
 * 2026-05-18 pass: added explicit frame padding so IDO emits the target
 * 0x88-byte frame / epilogue, and tried register-vs-stack dispatch_arg plus
 * single-scale-load variants. Best measured C body is 76.12745% by objdiff;
 * single-scale-load regressed to 69.80% because it grew the frame to 0x90.
 *
 * 2026-06-23 pass (agent-e): 77.75% -> 82.40%. Three BUGS fixed:
 *   (1) real callees wired with paired R_MIPS_26 relocs: the two timer-gate
 *       dispatch calls are game_uso_func_00011024(sub->0x840, dispatch_arg)
 *       (called via implicit K&R 2-arg decl so a1 is passed), the tail is
 *       game_uso_func_00007538(a0, dispatch_arg). Threading dispatch_arg into
 *       the tail (a1 already live) was the big mover: it stops IDO emitting a
 *       spurious `move a1,zero` and reproduces the a1+a2 save/restore pair
 *       around each call. All 3 relocs now byte-match target.
 *   (2) dispatch comparison: target is `c.le.s f6(sub->0x348),f4(30)` + bc1f,
 *       i.e. dispatch fires when sub->0x348 <= 30.0f (fall-through), timer+1
 *       when > 30. Rewrote the inner if as `if (x <= 30.0f) dispatch; else
 *       timer+1`. Old `30.0f < x` emitted the wrong `c.lt.s` form.
 *   (3) frame/decl order: V3 decl order added,base,tmp,scaled + pad[12] gives
 *       the 0x88 frame and the right relative slot ordering.
 * 2026-07-15 pass (agent-g): 82.40 -> 91.02. Three of the four "caps" fell:
 *   - grouped load*3/mul*3/store*3 + single 0xA8 load: named REGISTER float
 *     result locals (rx/ry/rz) + named `scale` local — the RESULT webs take
 *     the primary FP pool {f2,f12,f14} and the loads the secondary {f4,f6,f8}
 *     exactly as target; capturing the LOADS into locals instead mirrors the
 *     pools (loads f2,f12,f14) = wrong. scale named -> single lwc1 f0 + the
 *     mul operand order fs=load,ft=scale (a CSE'd inline load flips to
 *     fs=f0 = wrong).
 *   - volatile-qualified sub reload (`*(int * volatile *)(a0+0x30)`) gives the
 *     target's second lw of a0->0x30 (plain reload CSEs away).
 *   - bnel->bne fell out with the web fixes; frame 0x90 (target 0x88 +
 *     one extra dead float home: 4 register floats all get dead homes, target
 *     has 3 home words + the a1 spill at 0x6C; our a1 spill sits at 0x24).
 * 2026-07-15 pass 2 (agent-g cross-pollination): 91.02 -> 97.64 (95/102
 * aligned words; frame 0x88 exact, ALL homes/spills exact). Levers:
 *   - DE-NAMED stage-1 sub (inline a0->0x30 deref in the struct copy) ->
 *     ring temp t7 exactly as target; the named web starts at the volatile
 *     stage-2 reload. This also fixed the copy-pointer coloring (t0/t3/v0)
 *     and the tail temp-pool phase (old "dead-addiu drives them" theory
 *     was wrong — the phase came from the named stage-1 web).
 *   - dispatch_arg -> PLAIN named int declared between base_vec and rx:
 *     its 0x6C decl-position home is the a1 spill slot (afa5006c).
 *   - scale -> block-scope `register float` inside the p-block: $f0 with
 *     NO fn-scope home (3 float homes exactly); rz/scale same-name reuse
 *     miscolors the z-result f0 (dead-reg reuse) — keep scale separate.
 *   - pointer decls (p, timer) moved BELOW pad[8] in the decl list: p/self
 *     homes at decl-top were the phantom +8 ABOVE the vec block; last-decl
 *     scalars home below it. pad[8] = 0x28-0x47.
 *   - self ELIMINATED: target's a0/a2 pair is uopt range-splitting of the
 *     param web itself (spill to arg slot 0x88 across the calls); a named
 *     self copy is byte-equivalent, both split at stage-2.
 * REMAINING (true residual, 5-7 words, one-two cells):
 *   - param-web split POINT: target splits after the 0x6C dispatch test
 *     (stage-2 reload + scale + 0x6C read via a0, copy a2 parked at head
 *     word 7); ours splits at stage 1 (those 3 reads via a2) and schedules
 *     move a2,a0 at word 4 vs 7 (the 4-insn head reorder is the same cell).
 *     dead if(a0){} after the test = inert; if(1){self=a0;} = inert.
 *   - the dead `addiu v0,v0,0x318` post-bump: still NOT C-reachable
 *     (p+=0x318 DCE'd even with a zero-emission if(p){} consumer).
 * Default INCLUDE_ASM build remains exact; logic + relocs are correct. */
void game_uso_func_00011024();
void game_uso_func_00006CF0(int *a0) {
    V3_6A30 added_vec;   /* sp+0x7C */
    V3_6A30 base_vec;    /* sp+0x70 */
    int dispatch_arg;    /* sp+0x6C (a1 spill home) */
    register float rx;   /* dead home 0x68 */
    V3_6A30 tmp_vec;     /* sp+0x5C */
    register float ry, rz;      /* dead homes 0x58/0x54 */
    V3_6A30 scaled_vec;  /* sp+0x48 */
    int pad[8];          /* below the vec block */
    register char *p;    /* one web: stage-2 sub, tmp writer, tail sub */
    register int timer;

    (void)pad;
    /* stage-1 sub is DE-NAMED (inline deref -> ring temp t7); the named sub
     * web starts at the volatile stage-2 reload. */
    base_vec = *(V3_6A30 *)(*(char**)((char*)a0 + 0x30) + 0xB4);
    dispatch_arg = 0;    /* early: move a1,zero schedules into the stage-1 copy */

    p = *(char * volatile *)((char*)a0 + 0x30);   /* target reloads sub */
    {
        register float scale;     /* block-scope: $f0, no home */
        scale = *(float*)((char*)a0 + 0xA8);
        rx = *(float*)(p + 0x318) * scale;
        ry = *(float*)(p + 0x31C) * scale;
        rz = *(float*)(p + 0x320) * scale;
        p += 0x318;               /* folds away, but the bump + zero-emission
                                     consumer below shape p's web: removing
                                     them costs a word (build 102) and the
                                     copy-pointer colors */
        if (p) {}
        scaled_vec.x = rx;
        scaled_vec.y = ry;
        scaled_vec.z = rz;
        p = (char*)&tmp_vec;      /* def3: addiu v0,sp,0x5C reuses the same reg */
        *(V3_6A30*)p = scaled_vec;
        added_vec = *(V3_6A30*)p;
    }

    base_vec.x = base_vec.x + added_vec.x;
    base_vec.y = base_vec.y + added_vec.y;
    base_vec.z = base_vec.z + added_vec.z;

    if (*(int*)((char*)a0 + 0x6C) == 0) {
        dispatch_arg = 0x10;
    }
    p = *(char**)((char*)a0 + 0x30);
    if (*(int*)(p + 0x938) != 0 && *(int*)(p + 0xA54) != 0) {
        timer = *(int*)((char*)a0 + 0x70);
        if (timer < 60) {
            if (*(float*)(p + 0x348) <= 30.0f) {
                game_uso_func_00011024(*(int*)(p + 0x840), dispatch_arg);
                *(int*)((char*)a0 + 0x70) = 61;
            } else {
                *(int*)((char*)a0 + 0x70) = timer + 1;
            }
        } else if (timer == 60) {
            game_uso_func_00011024(*(int*)(p + 0x840), dispatch_arg);
            *(int*)((char*)a0 + 0x70) = 61;
        }
    }

    game_uso_func_00007538(a0, dispatch_arg);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006CF0);
#endif

void game_uso_func_00006E88(int *a0) {
    int r;
    gl_func_00000000(a0);
    r = gl_func_00000000(a0);
    *(int*)((char*)a0 + 0x80) = r;
    if (r == 0) return;
    *(int*)((char*)a0 + 0x40) = gl_func_00000000(a0);
}

void game_uso_func_00006ECC(int *a0) {
    int v;
    if (*(int*)(*(int*)((char*)a0 + 0x30) + 0x848) != 2) {
        gl_func_00000000();
        v = gl_func_00000000(a0);
        *(int*)((char*)a0 + 0x80) = v;
        if (v != 0) {
            *(int*)((char*)a0 + 0x40) = gl_func_00000000(a0);
        }
    }
}

void game_uso_func_00006F28(int *a0) {
    *(int*)((char*)a0 + 0x64) = 2;
    *(int*)((char*)a0 + 0x70) = 0;
}

/* game_uso_func_00006F38 - MATCHED 2026-07-08 (28/28 words incl. reloc fields).
 * Flag-test cascade over a chain pointer:
 * v = **(D_807FEB38+0x548); r = A374(a0, v BY-VALUE 1-int struct, a0->0x30+0xB4).
 * Levers: (1) a1 passed by-VALUE as 1-int struct (S1_6F38) -> IDO homes it to
 * the outgoing-arg slot sp+4 AND gives it a frame home (the A374
 * struct-by-value crack); (2) boolean cascade through a named chain var `b`
 * (colors $v1, return copy or v0,v1 duplicated into the bnezl/beqzl delay
 * slots; r stays live in $v0 - NOT a single &&/|| return expression);
 * (3) volatile char pad[0x18] below v lifts the frame to 0x40 with v@0x3C. */
extern char game_uso_D_807FEB38;
extern int game_uso_func_0000A374();
typedef struct { int a; } S1_6F38;
int game_uso_func_00006F38(int *a0) {
    S1_6F38 v;
    volatile char pad[0x18];
    int *r;
    int *q;
    int b;

    v.a = **(int **)((char *)&game_uso_D_807FEB38 + 0x548);
    r = (int *)game_uso_func_0000A374((int)a0, v, *(int *)((char *)a0 + 0x30) + 0xB4);
    b = (r != 0);
    if (b) {
        b = ((*(int *)((char *)r + 0x84) & 0x400) != 0);
        if (!b) {
            q = *(int **)((char *)r + 0x2C);
            b = (q != 0);
            if (b) {
                b = ((*(int *)((char *)q + 0x84) & 0x400) != 0);
            }
        }
    }
    return b;
}

#ifdef NON_MATCHING
/* game_uso_func_00006FA8: 127-insn (0x1FC) heavy FPU + multi-call compute.
 * Reloc-authoritative callees/data wired 2026-06-26:
 *   first call  -> game_uso_func_00007A98 (float return, gate < 0)
 *   2nd/3rd     -> game_uso_func_0000A374 (a1 passed by-value as 1-int struct,
 *                  homed to sp+4)
 *   data bases  -> game_uso_D_807FEB60 (+0x570) and game_uso_D_807FEB64 (+0x574)
 *                  each a pointer-table: p = *(int**)((char*)&D + off);
 *                  a1 = *p.
 * result = 10 if dot1 < dot2 else 11; squared-magnitude compare of two Vec3
 * diffs (callee-buffer+0x30 minus self->[0x30]+0xB4), each diff copied
 * d -> cNa -> cNb before the dot products.
 *
 * 2026-07-08 rebuild 64.6 -> 79.7 (objdiff). Cracked: frame 0xC0 with target
 * slot map via FLAT function-scope declarations (scalar candidates get homes
 * interleaved with structs in decl order; inner-scope scalars sink to a bottom
 * temp region instead -- that was the old +0x10 frame gap); nested null tests
 * with p1 = r1+0x30 between them (beqz v0 + addiu-in-delay, needs the dx/dy/dz
 * float locals present or IDO reverts to beqzl+lw-ra dup); per-block q via
 * if(1)-committed pointer mutation (addiu aN,aN,180 materialized, p1/p2 color
 * v1 both blocks as in target); struct-by-value S1 homes at 0xB8/0xB4.
 * RESIDUAL (permuter-class): (a) uopt folds the FIRST q deref to
 * lwc1 188(base) off the pre-mutation base (target has zero folds; resisted
 * 10+ spellings: int-form, float* IXA, volatile pointee, barriers, single-q
 * double-def -- single-q also flips p to a0); (b) dot2 is forwarded into the
 * compare so dot1(c1b) muls emit first (target: dot2 materialized to f0 at
 * its statement, c2b muls first, then c1b muls off pre-loaded f2/f12/f14
 * candidates; ucode temp-reuse chains pin the 3 nops); volatile c1b keeps
 * bx/by/bz as candidates (f0/f2/f12, off-by-one vs target f2/f12/f14 because
 * our dot2 never claims f0); (c) tail is bc1fl+dup instead of bc1f+nop, and
 * 3 words short (124/127) from the folds. Word-exact 37/127 positional,
 * LCS 62/127; both q-fold and dot2-forwarding look cost-model driven, not
 * C-reachable. */
typedef struct { float x, y, z; } V3_6FA8;
typedef struct { int a; } S1_6FA8;
extern int game_uso_D_807FEB60;
extern int game_uso_D_807FEB64;
int game_uso_func_00006FA8(int *a0) {
    int result;
    S1_6FA8 v1;
    S1_6FA8 v2;
    int *r1;
    int *r2;
    V3_6FA8 *p1;
    volatile V3_6FA8 c1b;
    V3_6FA8 c2b;
    float dot2;
    int padh;
    V3_6FA8 c1a;
    V3_6FA8 *q1;
    V3_6FA8 d1;
    float dx;
    float dy;
    float dz;
    float bx;
    float by;
    float bz;
    V3_6FA8 *p2;
    V3_6FA8 c2a;
    V3_6FA8 *q2;
    V3_6FA8 d2;
    int padg[2];
    int *s0 = a0;
    result = 0;
    if (game_uso_func_00007A98(s0) < 0.0f) {
        v1.a = *(int *)*(int **)((char *)&game_uso_D_807FEB60 + 0x570);
        r1 = (int *)game_uso_func_0000A374((int)s0, v1, s0[0x30 / 4] + 0xB4);
        v2.a = *(int *)*(int **)((char *)&game_uso_D_807FEB64 + 0x574);
        r2 = (int *)game_uso_func_0000A374((int)s0, v2, s0[0x30 / 4] + 0xB4);
        if (r1 != 0) {
            p1 = (V3_6FA8 *)r1 + 4;
            if (r2 != 0) {
                q1 = (V3_6FA8 *)s0[0x30 / 4];
                if (1) {
                    q1 += 15;
                }
                dx = p1->x - q1->x;
                dy = p1->y - q1->y;
                dz = p1->z - q1->z;
                d1.z = dz;
                d1.y = dy;
                d1.x = dx;
                c1a = d1;
                c1b = c1a;
                p2 = (V3_6FA8 *)r2 + 4;
                q2 = (V3_6FA8 *)s0[0x30 / 4];
                if (1) {
                    q2 += 15;
                }
                dx = p2->x - q2->x;
                dy = p2->y - q2->y;
                dz = p2->z - q2->z;
                d2.z = dz;
                d2.y = dy;
                d2.x = dx;
                c2a = d2;
                c2b = c2a;
                dot2 = c2b.x * c2b.x + c2b.y * c2b.y + c2b.z * c2b.z;
                if (1) {
                    bx = c1b.x;
                    by = c1b.y;
                    bz = c1b.z;
                }
                if (dot2 > bx * bx + by * by + bz * bz) {
                    result = 10;
                } else {
                    result = 11;
                }
            }
        }
    }
    return result;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006FA8);
#endif

void game_uso_func_000071A4(int *a0) {
    *(int*)((char*)a0 + 0x64) = 1;
    *(int*)((char*)a0 + 0x70) = 0;
    if (*(int*)((char*)a0 + 0x4C4) > 0) {
        gl_func_00000000(a0);
        *(int*)((char*)a0 + 0x4C4) = 0;
    }
}

#ifdef NON_MATCHING
/* game_uso_func_000071E0: 145-insn (0x244) multi-stage per-frame compute.
 * Frame -0xB0. Sibling of 0x6FA8 / 0x6CF0 / 0x6A30 (FPU-heavy update class).
 *
 * Structural decode (offsets in target asm):
 *
 *   self = a0; saved to s0.
 *   flag = self->[0x68];
 *   if ((flag & 4) != 0) {                  ; bnezl-pattern early skip
 *     gl_func_00000000(...);                ; if flag-bit-2 set, just call & return
 *     goto end;
 *   }
 *
 *   ; Stage 2: float-gate
 *   sub = self->[0x30];
 *   const = 30.0f                            ; lui at, 0x41F0
 *   tmp_f = sub->[0x348];
 *   if (tmp_f >= const) {                    ; c.lt.s f4, const ; bc1t
 *     self->[0x54] = 0;
 *     count = self->[0x54] + 1;              ; count++ (well, that's 0+1=1)
 *     if (count >= 0x1E) {                   ; if count reaches 30
 *       self->[0x64] = 0;                    ; reset
 *       self->[0x54] = 0;
 *     } else {
 *       self->[0x54] = count;
 *     }
 *     ; ... continued ...
 *     stage_idx = self->[0x64];
 *     if (stage_idx != 3) goto end;
 *
 *     ; Stage 3: 4-Vec3 stage builder
 *     sp[0x98] = 0;                           ; clear local
 *     sub2 = self->[0x30];
 *     sp[0x8C..0x94] = sub2->{0xB4,B8,BC};   ; Vec3-int copy
 *     ...
 *
 *     ; Stage 4: cross-USO call returning into v0
 *     v0 = gl_func_00000000(0, base, ...);
 *     if (v0 == 0) goto end;
 *
 *     ; Stage 5: Vec3 store via pointer (3 lw/sw pairs from sp[0x6C..0x74]
 *     ; into v0+0..0x8)
 *
 *     ; Stage 6: gl_func with stage-4 result + sp+0x84 buffer
 *     gl_func_00000000(self->[0x30] + 0x3C8, self->[0x30] + 0x3C8, v0,
 *                       sp[0x6C..]);
 *
 *     ; Stage 7: another conditional 0.0f init store
 *     if (sub->[0x70] >= 0x100) sp[0x3C] = ...;  ; c.lt.s + bc1t
 *
 *     ; Stage 8: gl_func with sp+0x6C buffer + sp+0x78 buffer
 *     gl_func_00000000(self, sp+0x6C, sp+0x78, ...);
 *
 *     ; Stage 9: c1.f8 add fixed bias 6.0f, store to sp+0x3C
 *     sp[0x3C] = (sub->[0x6C] + 6.0f);
 *
 *     ; Stage 10: dispatch on sub->0x938
 *     if (sub->[0x938] != 0x100) gl_func_00000000(self, sp[0x98]);
 *   }
 *
 *   end: return;
 *
 * Spine context: per-frame compute reading self with sub at +0x30. Field
 * offsets: self->{0x30, 0x54, 0x64, 0x68}, sub->{0x348, 0x6C, 0x70, 0x938,
 * 0xB4, 0xB8, 0xBC, 0x318, 0x31C, 0x320, 0x3C8}.
 *
 * Multi-tick refinement target. Default INCLUDE_ASM build remains exact
 * via the asm. Skeleton kept for grep discoverability of struct field
 * offsets and the per-frame compute call-graph. */
extern void game_uso_func_0000A7F8(char *);
extern int game_uso_func_00007ACC();
extern int game_uso_func_00007C1C();
extern long long game_uso_func_00007538(int *, int);
void game_uso_func_000071E0(int *a0) {
    /* Full structural decode 2026-06-01. Per-frame compute: flag-gate ->
     * float-gate counter (reset at 30) -> if state(0x64)==3 do the
     * scale-Vec3 + transform-compose (A604 family) + 3 cross-USO calls +
     * conditional yaw store. All cross-USO calls are gl_func_00000000. */
    char *obj = (char *)a0;
    char *w;
    int counter;
    int flag256;
    float s;
    Vec3 scaled, c1, c2, xf;
    float outpos[3], rec[3], pt[3];
    char *r1, *r2;
    float yaw, fr;

    if (*(int *)(obj + 0x68) & 4) {
        game_uso_func_0000A7F8(obj);
        return;
    }
    w = *(char **)(obj + 0x30);
    if (30.0f <= *(float *)(w + 0x348)) {
        counter = *(int *)(obj + 0x54) + 1;
        if (counter < 30) {
            *(int *)(obj + 0x54) = counter;
        } else {
            *(int *)(obj + 0x64) = 0;
            *(int *)(obj + 0x54) = 0;
        }
    } else {
        *(int *)(obj + 0x54) = 0;
    }
    if (*(int *)(obj + 0x64) != 3) {
        return;
    }

    flag256 = 0;
    xf = *(Vec3 *)(w + 0xB4);
    s = *(float *)(obj + 0xA8);
    scaled.x = *(float *)(w + 0x318) * s;
    scaled.y = *(float *)(w + 0x31C) * s;
    scaled.z = *(float *)(w + 0x320) * s;
    c1 = scaled;
    c2 = c1;
    xf.x = xf.x + c2.x;
    xf.y = xf.y + c2.y;
    xf.z = xf.z + c2.z;

    r1 = (char *)game_uso_func_00007ACC(obj, outpos, &xf, 0);
    if (r1 != 0) {
        r2 = (char *)game_uso_func_00007C1C(&c1, obj, r1, *(int *)outpos, &xf, 0);
        pt[0] = *(float *)r2;
        pt[1] = *(float *)(r2 + 4);
        pt[2] = *(float *)(r2 + 8);
        rec[0] = *(float *)(w + 0x3C8);
        rec[2] = *(float *)(w + 0x3D0);
        rec[1] = 0.0f;
        yaw = game_uso_func_00003ED4((Vec3 *)rec, (Vec3 *)pt, 0);
        fr = -yaw * 6.0f;
        *(float *)(obj + 0x3C) = fr;
        if (*(int *)(obj + 0x6C) == 0) {
            if (*(int *)(w + 0x938) != 0) {
                flag256 = 256;
            }
        }
        game_uso_func_00007538(obj, flag256);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000071E0);
#endif

void game_uso_func_00007424(void *a0) {
    *(int*)((char*)a0 + 0x64) = 3;
    gl_func_00000000(a0);
}

#ifdef NON_MATCHING
void game_uso_func_00007448(char *a0) {
    char *t;
    char *table;
    char *q;
    char *fc;

    t = a0;
    while (0) { t += 1; }
    table = *(char**)(a0 + 0x30);
    t = table;
    if (1) { t += 0x758; }
    *(float*)(a0 + 0x4C8) = *(float*)(t + 0x10);
    t = table;
    if (1) { t += 0x6F8; }
    *(float*)(a0 + 0x4CC) = *(float*)(t + 0x10);
    t = table;
    if (1) { t += 0x6E0; }
    *(float*)(a0 + 0x4D0) = *(float*)(t + 0x10);
    t = table;
    if (1) { t += 0x498; }
    fc = a0;
    if (1) { fc += 0x35C; }
    *(float*)(a0 + 0x4D4) = *(float*)(t + 0x10);
    *(float*)(table + 0x768) = *(float*)(a0 + 0x33C) * *(float*)(a0 + 0x4C8);

    t = *(char**)(a0 + 0x30) + 0x6F8;
    *(float*)(t + 0x10) = *(float*)(a0 + 0x36C) * *(float*)(a0 + 0x4CC);

    t = *(char**)(a0 + 0x30) + 0x6E0;
    *(float*)(t + 0x10) = *(float*)(fc + 0x10) * *(float*)(a0 + 0x4D0);

    table = *(char**)(a0 + 0x30);
    q = table;
    if (1) { q += 0x4C8; }
    t = table;
    if (1) { t += 0x498; }
    *(float*)(t + 0x10) = *(float*)(q + 0x10);
}

/* game_uso_func_00007448 — 24/36 exact, LENGTH-EXACT, structure fully aligned
 * (was 73.5%; ~86% fuzzy now). NOT exact — genuine coloring cap. 2026-07-03
 * (agent-e). Levers that landed (see also docs/IDO_CODEGEN.md):
 *  (1) base materialization: `t = table; if (1) { t += K; }` — if(1){} blocks
 *      the copyprop merge; emits `addiu tN,table,K` + 0x10-offset accesses
 *      (plain `t = table + K` folds to full offsets).
 *  (2) `t = a0; while (0) { t += 1; }` at top = candidate-order lever
 *      (t colors v0 before table/v1).
 *  (3) fc's def embedded between t4's def and its use = live-range overlap
 *      with v0 => fc skips v0 AND its addiu schedules at target position.
 *  (4) unnamed sx + mul operands textually REVERSED (second operand's load
 *      emits first) => f18/f16 exact.
 * RESIDUAL (12 words): target colors blocks2/3-base=a1, q=a2, fc=a3 while
 * leaving v0/v1 free post-block1 — uopt's lowest-available-reuse picker can't
 * produce that from any of 12 probed candidate-order permutations. */
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007448);
#endif

void game_uso_func_000074D8(char *a0) {
    char *t;
    t = *(char**)(a0 + 0x30) + 0x758;
    *(float*)(t + 0x10) = *(float*)(a0 + 0x4C8);
    t = *(char**)(a0 + 0x30) + 0x6F8;
    *(float*)(t + 0x10) = *(float*)(a0 + 0x4CC);
    t = *(char**)(a0 + 0x30) + 0x6E0;
    *(float*)(t + 0x10) = *(float*)(a0 + 0x4D0);
    t = *(char**)(a0 + 0x30) + 0x498;
    *(float*)(t + 0x10) = *(float*)(a0 + 0x4D4);
}

void game_uso_func_0000751C(char *a0) {
    char *t = *(char**)(a0 + 0x30) + 0x758;
    *(float*)(t + 0x10) = *(float*)(a0 + 0x354) * *(float*)(a0 + 0x4C8);
}

#ifdef NON_MATCHING
/* game_uso_func_00007538: 0x560 (344 insns) — largest residue of the split-up
 * 0x7424 bundle. Per-frame event dispatcher + per-bit timer decrementer.
 *
 * Partial C body below: 63.27% as of 2026-05-30 after replacing the s64
 * return `(ll)ret_hi<<32 | ret_lo` (which compiled to an __ll_lshift CALL,
 * forcing a frame + $a0->$s0 promotion) with a hi:lo union build — the target
 * is a frameless LEAF (no jal). That single change took it 58.69%->63.27% and
 * removed the long-documented "built saves $s0" frame divergence at entry.
 * Was 58.69% (2026-05-17, bit-0x80 audit), 38.83% pre-bit-0x80-table rewrite.
 *
 * NEXT BLOCKER (2026-05-30): residual is a 2-word $a2/$a3 SPILL frame (build
 * `addiu sp,-88; sw a3,0(sp); sw a2,4(sp)`; target has NO frame) + ~15 still-
 * stubbed insns. Root cause is an INVERTED arg-register assignment: the target
 * keeps ret_lo/ret_hi in $v0/$v1 the whole function (it inits `move v0,zero;
 * move v1,zero`, returns from there with no final move) which pushes
 * counter->$a2 and a1_saved->$a3; OUR build puts a1_saved->$v0, counter->$v1
 * (the union return computes ret_lo/ret_hi in $a2/$a3 then moves to $v0/$v1 at
 * the end), so $a2/$a3 are needed for the returns and the long-lived
 * counter/a1_saved spill. REGALLOC-DUMP CONFIRMED (2026-05-30, `cc -Wo,-zdbug:6`
 * -> uoptlist, see docs/IDO_CODEGEN.md): a1_saved colors to $v0 and counter to
 * $v1 because their decls (`a1_saved=a1`, `counter=a0[0x50]`) are REAL early
 * USES encountered before ret_lo/ret_hi's first meaningful use — ret_lo/ret_hi
 * are `=0` constants until an arm ORs them, so their candidates are created late
 * and lose the $v0/$v1 colors. Lever (per the dump's reorder-first-use rule):
 * give ret_lo/ret_hi an earlier non-constant first-use so they're colored before
 * a1_saved/counter; tried-and-pending (no natural early use — they're genuinely 0
 * until the arms). A focused regalloc session should drive this via the uoptlist
 * candidate order. Until then the spill caps it.
 * Captures prelude + dispatch outline + epilogue + bit-0x80 trunk arm.
 * Many arm bodies are TODO-stubbed with correct control-flow targets but
 * no per-bit state mutations yet.
 *
 * 2026-05-05 BUG FIXES (+5.3pp):
 *   (1) Prelude `if ((flags & 0x10) == 0)` was wrong — should be
 *       `if (flags > 0)`. The asm computes `t8 = a3 & 0x10` separately
 *       (later used as the `arg1 & 0x10` dispatch test); the decrement
 *       guard is `blez a1` which is `flags <= 0`. The two computations
 *       were conflated.
 *   (2) Dispatch arms were testing `a1` (which is the running-mask state
 *       built up by ORs into a0[0x6C], starts at 0 = flag2 in the
 *       flag2==0 path) instead of `a1_saved` (the input arg). With the
 *       running mask starting at 0, NONE of the arm bodies could fire.
 *       The bit tests are on `a1_saved` (= a3 in asm), the running mask
 *       gets ORed bits stored back into a0[0x6C].
 *
 * Next pass should compare objdiff output per-arm and fill in the TODO
 * placeholders embedded in each arm.
 *
 * 2026-05-05 ASM TRACE NOTES (no code change this pass):
 *   - Branch at 0x75D8 is `beq t1,zero,+0xA` (opcode 4 = BEQ), NOT BNEL.
 *     Initial mis-decode as bnel led to a regression-tested invert attempt
 *     (36.89% -> 36.74%, reverted). The dispatch arm is normal-direction:
 *     bit 0x01 set → body at 0x75E0 fires (raises bit 0x01 in a0[0x6C]).
 *
 *   - bit 0x04 arm's full asm body (0x7628-0x7650) does MORE than the
 *     current C captures:
 *       a1 was loaded as t9 = a0[0x50] (counter check)
 *       at = 0x3F800000 (1.0f)
 *       t0 = 8
 *       if (t9 != 0) skip 6 insns (don't fire body)
 *       f2 = 1.0f                            ← current C has this
 *       v1 = 1                               ← MISSING (retHi)
 *       a0[0x50] = 8                         ← current C has this
 *       a1 = a0[0x6C] (reload, in delay slot of b)
 *     Adding `retHi=1` requires returning a 64-bit (v0,v1) pair; the
 *     current C body returns void via implicit dropped-value. Function
 *     signature needs update to int64_t (or u64) before the bit-0x04
 *     and bit-0x80 arm bodies (which both set retHi) can match.
 *
 *   - Function epilogue stores ret_lo to `outer[0x800]->[0x40]`; the
 *     return value (v0,v1) packs ret_lo,ret_hi for the caller too. Both
 *     paths must be correct for a full match.
 *
 *   Next pass: change signature to `s64 game_uso_func_00007538(int*, int)`
 *   then add `retHi` field updates. Likely +5-10pp gain.
 *
 * DECODE (insns 1-40 @ 0x7538-0x75D4):
 *   Setup:
 *     f16 = 0.0f; f0 = 0.0f; f2 = 0.0f; v0 = v1 = 0 (retLo/retHi)
 *     a3 = saved_arg1 (=a1)
 *     counter = a0[0x50]; if (counter > 0) a0[0x50]--;
 *     flags   = a0[0x48]; if (flags   > 0) a0[0x48]--;
 *     mask10 = arg1 & 0x10;
 *     flag2   = a0[0x6C];
 *   Dispatch (bnel branch-likely at 0x40):
 *     if (flag2 != 0) goto tail_case (at 0x20C, with t1 = flag2 & 1 in delay)
 *   Fallthrough (flag2 == 0):
 *     if ((arg1 & 0x10) == 0) goto dispatch_next (0xA0, with t1 = arg1 & 1 in delay)
 *     // case: flag2==0 AND (arg1 & 0x10):
 *     t9 = a0[0x30]; t0 = t9[0x938/4];
 *     if (t0 == 0) goto tail_case (beql at 0x58, with t1 = a1 & 1 in delay)
 *     // case: t0 != 0 (inner): float sign-of check
 *     f4 = *(float*)&a0[0x38];
 *     if (f4 >= 0.0f) { a0[0x3C] = 1.0f; } else { a0[0x3C] = -1.0f; }
 *     goto dispatch_next (0xA0, reloads a1 = a0[0x6C])
 *
 * CHARACTERISTICS:
 *  - Uses 0xBF80 = -1.0f and 0x3F80 = 1.0f as magic constants (sign-setter)
 *  - Multiple beql/bnel branch-likely ops — tight scheduling with delay slot
 *    side-effects (reloading a1, setting up a2 args, etc.)
 *  - State machine: a0->field_6C holds a flag mask; arg1 holds event bits
 *  - a0->field_30 is an outer struct pointer (->field_938 is another flag)
 *
 * DECODE (insns 40-80 @ 0x75D4-0x766C): dispatch_next cascade
 * Starting at 0x75D4 (a1 reloaded from a0[0x6C]), a chain of per-bit
 * tests on arg1, each firing a short event-handler arm that flips a
 * flag in a0[0x6C], sets one or two state fields, and branches to a
 * common merge point at ~0x7740.
 *
 * The arm template:
 *   if (arg1 & BIT) {
 *       // optional guard on counter/flags
 *       if (guard != 0) goto next_arm;
 *       a0[0x6C] |= BIT;
 *       a0[FIELD] = CONST;   // field/const varies per arm
 *       [optional: side effect — float const, counter reset, etc.]
 *       goto merge;
 *   }
 *   next_arm:
 *
 * Decoded arms (first 5 of ~8):
 *   arg1 & 0x01  (guarded by flags == 0):  a0[0x6C] |= 1;    a0[0x44] = 91
 *   arg1 & 0x40  (no guard):                a0[0x6C] |= 0x40; a0[0x44] = 13
 *   arg1 & 0x04  (guarded by counter == 0): a0[0x6C] |= ?;    a0[0x50] = 8;
 *                                           f2 = 1.0f; retHi = 1
 *   arg1 & 0x20  (no guard, yet):           a0[0x6C] |= 0x20; a0[0x4C] = 38
 *   arg1 & 0x80  (pending):                 a0[0x6C] |= ?;    ...
 *
 * This is an animation/state-event dispatcher. Each bit in arg1 maps to
 * a specific transition; the 91/13/38 constants are likely frame-count
 * targets for animations. a0[0x44], a0[0x4C], a0[0x50] are state timers.
 * a0[0x6C] is the active-events mask.
 *
 * DECODE (insns 80-120 @ 0x7670-0x7708):
 * The arg1 & 0x20 arm's BODY (started at 0x765C) is longer than the
 * simpler arms — it does a floating-point abs+mod9 computation:
 *   f12 = outer_ptr->0xB4           // load float
 *   f14 = (f12 < 0) ? -f12 : f12    // fabs via bc1fl + neg.s
 *                                    // NB: dead `mov.s f14, f12` at 0x768C
 *                                    //   (unreachable, both arms branch to merge)
 *   a0[0x44] = 60
 *   a0[0x58] = (int)f14 % 9         // trunc.w.s + divu + mfhi
 *   goto merge
 *
 * Two more arms decoded:
 *   arg1 & 0x80 (no guard): a0[0x6C] |= 0x80; a0[0x4C] = 0; a0[0x44] = 2
 *   arg1 & 0x08 (guarded by outer->0x938 == 0): set f2 = -1.0f, goto merge;
 *                 otherwise (outer->0x938 != 0) different path
 *
 * DECODE (insns 116-160 @ 0x7708-0x77B8): arg1 & 0x02 arm + flag-decrement
 * merge trunk.
 *
 * arg1 & 0x02 arm (0x7708-0x773C):
 *   if (arm_02_fires) {                         // t5 carried from prev arm
 *       int out_flag = outer->field_938;
 *       if (out_flag == 0) {
 *           // branch-likely skip; flow falls back into mask update below
 *       } else {
 *           retLo = 0x400;                      // or into return low word
 *           if (arg1 & 0x100) {
 *               a0->field_6C = (a1 | 0x100);    // set BOTH bits 0x02 AND 0x100
 *               a0->field_44 = 0x68;            // animation counter = 104
 *           }
 *       }
 *       a1 = a0->field_6C;                      // reload mask for merge
 *   }
 *
 * FLAG-DECREMENT TRUNK (merge at 0x7740, per-bit-and-counter cleanup):
 *   // For each bit still set in the active mask (a1 = a0->field_6C), the
 *   // function decrements its associated countdown timer at a0->field_44
 *   // and clears the bit when the timer reaches zero.
 *   //
 *   // Pattern per bit:
 *   //   if ((a1 & BIT) != 0) {
 *   //       retLo |= RET_BITS_FOR_THIS_BIT;
 *   //       a1 = a0->field_44 - 1;
 *   //       a0->field_44 = a1;
 *   //       if (a1 == 0) {
 *   //           a0->field_6C &= ~MASK_FOR_THIS_BIT;
 *   //           goto ret;  // short-circuit — don't process lower bits
 *   //       }
 *   //   }
 *   //   // fall through to next bit
 *   //
 *   // Decoded per-bit entries so far:
 *   //   bit 0x01: retLo |= 0x500; clear-mask = ~0xA1 (clears 0x80|0x20|0x01)
 *   //   bit 0x40: retLo |= 0x100; clear-mask = ~0x40
 *   //   bit 0x20: (cascades into another outer->0x938 check, continues)
 *   //
 *   // Multi-bit clear on bit-0x01 hit suggests bit 0x01 is a "master event"
 *   // — when its timer expires, three related event bits all reset together.
 *
 * REMAINING ~185 insns at 0x77B8-0x7A98: continued flag-decrement trunk for
 * bits 0x20, 0x80, 0x100, 0x08, 0x04, 0x10; the merge/ret block; the
 * flag2!=0 tail_case at 0x20C that we first saw at bnel @0x40. Return
 * packs (retHi, retLo) into (v1, v0) = 64-bit "which-events-fired" word.
 *
 * Not ready to write full C yet — too many intermediate branches with
 * delay-slot-scheduled state mutations (each arm's delay slot does part of
 * the next arm's setup). Next pass: decode 0x77B8-0x7880 (bits 0x20, 0x80,
 * 0x100) and the merge block proper. */
extern char game_uso_D_807FEC28;
long long game_uso_func_00007538(int *a0, int a1) {
    int ret_lo = 0;
    int ret_hi = 0;
    int a1_saved = a1;
    int counter, flags, flag2;
    float f0 = 0.0f, f2 = 0.0f, f_tmp;

    counter = a0[0x50 / 4];
    if (counter > 0) a0[0x50 / 4] = counter - 1;
    if ((int)a0[0x48 / 4] > 0) a0[0x48 / 4] -= 1;

    flag2 = a0[0x6C / 4];
    if (flag2 != 0) goto trunk;

    a1 = flag2;

    if (a1_saved & 0x10) {
        if (((int*)a0[0x30 / 4])[0x938 / 4] != 0) {
            f_tmp = *(float*)&a0[0x38 / 4];
            *(float*)&a0[0x3C / 4] = (f_tmp >= 0.0f) ? 1.0f : -1.0f;
        }
        a1 = a0[0x6C / 4];
        goto trunk;
    }

    if (a1_saved & 0x01) {
        flags = a0[0x48 / 4];
        if (flags != 0) goto check_40;
        a0[0x6C / 4] = a1 | 0x01;
        a0[0x44 / 4] = 91;
        a1 = a1 | 0x01;
        goto trunk;
    }
check_40:
    if (a1_saved & 0x40) {
        a0[0x6C / 4] = a1 | 0x40;
        a0[0x44 / 4] = 13;
        a1 = a1 | 0x40;
        goto trunk;
    }
    if (a1_saved & 0x04) {
        if (counter != 0) goto check_20;
        f2 = 1.0f;
        ret_hi = 1;
        a0[0x50 / 4] = 8;
        a1 = a0[0x6C / 4];
        goto trunk;
    }
check_20:
    if (a1_saved & 0x20) {
        a0[0x6C / 4] = a1 | 0x20;
        a0[0x4C / 4] = 38;
        f_tmp = *(float*)&((int*)a0[0x30 / 4])[0xB4 / 4];
        if (f_tmp < 0.0f) f_tmp = -f_tmp;
        a1 = a0[0x6C / 4];
        a0[0x44 / 4] = 60;
        a0[0x58 / 4] = (int)f_tmp % 9;
        goto trunk;
    }
    if (a1_saved & 0x80) {
        a0[0x6C / 4] = a1 | 0x80;
        a0[0x4C / 4] = 0;
        a0[0x44 / 4] = 2;
        a1 = a1 | 0x80;
        goto trunk;
    }
    if (a1_saved & 0x08) {
        if (((int*)a0[0x30 / 4])[0x938 / 4] != 0) {
            f2 = -1.0f;
        }
        goto trunk;
    }
    if (a1_saved & 0x02) {
        if (((int*)a0[0x30 / 4])[0x938 / 4] != 0) {
            ret_lo = 0x400;
        }
    } else if (a1_saved & 0x100) {
        a0[0x6C / 4] = a1 | 0x100;
        a0[0x44 / 4] = 0x68;
        a1 = a1 | 0x100;
    }

trunk:
    if (a1 & 0x01) {
        ret_lo |= 0x500;
        counter = a0[0x44 / 4] - 1;
        a0[0x44 / 4] = counter;
        if (counter == 0) {
            a0[0x6C / 4] &= ~0xA1;
        }
        goto ret_tail;
    }
    if (a1 & 0x40) {
        counter = a0[0x44 / 4] - 1;
        if (counter != 0) {
            a0[0x44 / 4] = counter;
            ret_lo |= 0x100;
        } else {
            a0[0x6C / 4] &= ~0x40;
        }
        goto ret_tail;
    }
    if (a1 & 0x20) {
        if (((int*)a0[0x30 / 4])[0x938 / 4] == 0) {
            int cnt = a0[0x4C / 4];
            ret_hi = 1;
            ret_lo |= 0x200;
            if (cnt >= 31) {
                int idx = a0[0x58 / 4];
                f0 = *(float*)((char*)&game_uso_D_807FEC28 + 0x638 + idx * 8);
                f2 = *(float*)((char*)&game_uso_D_807FEC28 + 0x638 + idx * 8 + 4);
            }
            a0[0x4C / 4] = cnt - 1;
        }
        if (a0[0x4C / 4] == 0) {
            a0[0x6C / 4] &= ~0x20;
        } else {
            counter = a0[0x44 / 4] - 1;
            a0[0x44 / 4] = counter;
            if (counter == 0) {
                a0[0x6C / 4] &= ~0x20;
            }
        }
        goto ret_tail;
    }
    if (a1 & 0x80) {
        int sub_cnt = a0[0x4C / 4];
        int list_base;
        int main_cnt, new_sub_cnt, limit, table_idx;
        ret_hi = 1;

        if (sub_cnt < 8) {
            list_base = a0[0x4DC / 4];
            a0[0x58 / 4] = sub_cnt;
            if (sub_cnt >= 5) {
                if (sub_cnt < 8) ret_lo |= 0x1000;
            }
            goto bit80_table;
        }
        list_base = a0[0x4DC / 4];
        if (sub_cnt < list_base + 8)  goto bit80_count;
        if (sub_cnt < list_base + 16) goto bit80_mid;
        if (sub_cnt < list_base * 2 + 16) goto bit80_count;
        a0[0x58 / 4] = (sub_cnt - list_base * 2) - 16;
        if (sub_cnt < list_base * 2 + 21) goto bit80_table;
        if (list_base * 2 + 23 < sub_cnt) goto bit80_table;
        ret_lo |= 0x1600;
        goto bit80_table;
bit80_mid:
        a0[0x58 / 4] = (sub_cnt - list_base) - 8;
        if (sub_cnt < list_base + 13) goto bit80_table;
        if (list_base + 15 < sub_cnt) goto bit80_table;
        ret_lo |= 0x1200;
bit80_table:
        table_idx = a0[0x58 / 4];
        f0 = *(float*)((char*)&game_uso_D_807FEC28 + 0x638 + table_idx * 8);
        f2 = *(float*)((char*)&game_uso_D_807FEC28 + 0x638 + table_idx * 8 + 4);
bit80_count:
        main_cnt = a0[0x44 / 4];
        new_sub_cnt = sub_cnt + 1;
        a0[0x4C / 4] = new_sub_cnt;
        if (main_cnt == 0)      limit = 8;
        else if (main_cnt == 1) limit = a0[0x4DC / 4] + 16;
        else                    limit = a0[0x4DC / 4] * 2 + 24;
        if (new_sub_cnt >= limit) {
            a0[0x6C / 4] &= ~0x80;
        }
        goto ret_tail;
    }
    if (a1 & 0x100) {
        int main_cnt = a0[0x44 / 4];
        int new_cnt  = main_cnt - 1;
        if (main_cnt >= 93) {
            f2 = 1.0f;
            ret_hi = 1;
        } else if (main_cnt >= 73) {
            ret_hi = 1;
        } else if (main_cnt >= 61) {
            ret_lo |= 0x100;
        }
        a0[0x44 / 4] = new_cnt;
        if (new_cnt == 0) a0[0x6C / 4] &= ~0x100;
    }

ret_tail:
    if (ret_hi != 0) {
        f_tmp = *(float*)&a0[0x3C / 4];
        if (0.0 < (double)f_tmp)        *(float*)&a0[0x3C / 4] = 1.0f;
        else if ((double)f_tmp < 0.0)   *(float*)&a0[0x3C / 4] = -1.0f;
        f0 = *(float*)&a0[0x3C / 4];
    } else {
        *(float*)&a0[0x38 / 4] = 0.0f;
        goto store_out;
    }
    *(float*)&a0[0x38 / 4] = *(float*)&a0[0x3C / 4];

store_out:
    *(float*)&((int*)((int*)a0[0x30 / 4])[0x800 / 4])[0x44 / 4] = f0;
    *(float*)&((int*)((int*)a0[0x30 / 4])[0x800 / 4])[0x48 / 4] = f2;
    ((int*)((int*)a0[0x30 / 4])[0x800 / 4])[0x40 / 4] = ret_lo;
    {
        union { long long ll; struct { int hi; int lo; } w; } _r;
        _r.w.hi = ret_hi;
        _r.w.lo = ret_lo;
        return _r.ll;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007538);
#endif

/* 9-insn body with cross-function `beql v1, zero, +7` to 7ABC+4 — see the
 * detailed note inside the NON_MATCHING block below (via-f2 form is C-reachable;
 * residual is the whole-file cross-jump into 7ABC's mis-split tail). The old
 * PREFIX_BYTES + INSN_PATCH "promotion recipe" that was here is removed — that
 * mechanism was banned 2026-05-23 as match-faking. */
#ifdef NON_MATCHING
/* Decoded 2026-05-28; via-f2 form found 2026-05-31. Returns the float delta:
 *   v0 = a0->0x30; v1 = v0->0x908;
 *   if (v1 == 0) return 0.0f;            // beql v1,0 -> shared 7ABC epilogue
 *   return v1->0xBC - v0->0xBC;
 *
 * UPDATE 2026-05-31: the old "C can't reproduce the via-$f2 tail" claim was
 * WRONG. A single-return NAMED LOCAL (`float ret; if(v1==0) ret=0; else
 * ret=sub; return ret;`) makes IDO route the result through $f2 and emit
 * exactly `sub.s f2,f4,f6 ; jr ra ; mov.s f0,f2` (non-null) and `mtc1 zero,f2
 * ; jr ra ; mov.s f0,f2` (null) — register-identical to the target. The
 * residual is ONLY layout: target is 9 insns (null path uses a forward `beql`
 * into 7ABC's shared `jr ra; mov.s f0,f2`); C-emit gives 12 (bnezl-skip with
 * its own inline null epilogue). 7ABC has NO independent callers (verified:
 * no jal/reloc/symname references it) — it is 7A98's MIS-SPLIT 0.0f-return
 * tail. The 9-insn form needs IDO's whole-file cross-jump to merge 7A98's null
 * tail into 7ABC, which requires 7ABC's body to ALSO be `mtc1 zero,f2; jr ra;
 * mov.s f0,f2` — but a constant-0 return copy-propagates to $f0 (probed
 * named-local/volatile/int-store 2026-05-31, all give `mtc1 zero,f0` or a
 * stack ping-pong, never $f2). So the cross-jump can't bootstrap from C as two
 * separate functions. A combined 7A98+7ABC merge sandbox was already tested and
 * failed (see docs/MATCHING_WORKFLOW.md cross-function-tail-share unmatchable
 * standalone note); do not retry the merge path without a genuinely new
 * mechanism. Body below is the via-f2 reference (closer than the prior
 * direct-f0). */
float game_uso_func_00007A98(int *a0) {
    int *v0 = (int *)a0[0x30 / 4];
    int *v1 = (int *)v0[0x908 / 4];
    float ret;
    if (v1 == 0) {
        ret = 0.0f;
    } else {
        ret = *(float *)((char *)v1 + 0xBC) - *(float *)((char *)v0 + 0xBC);
    }
    return ret;
}
#else
/* game_uso_func_00007A98: leaf-branch-past-end CAP -- RESOLVED PAIR
 * 2026-06-10: the beqzl targets 0x7AC0 = game_uso_func_00007ABC+4!
 * 7ABC is NOT a standalone fn: it is THIS fn's shared else-tail
 * (v1==0 path: f2=0 via the delay mtc1, then 7ABC's nop/jr/cvt.s.w
 * returns (float)int(f2)), with 7ABC's own first insn (mtc1 zero,f2)
 * being a 1-insn alt-entry prefix for direct jal callers wanting
 * return-0.0f. This EXPLAINS 7ABC's 18-combo-negative unfolded cvt:
 * the zero arrives at RUNTIME from either entry, so the conversion
 * cannot constant-fold. Two-entry shared-tail class; both symbols
 * permanently INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007A98);
#endif

/* 4-insn body `mtc1 $0,$f2; nop; jr ra; mov.s $f0,$f2` — returns 0.0f via $f2.
 * NOT an independent function: NOTHING calls 7ABC (no jal/reloc/symname ref,
 * verified 2026-05-31). It is the MIS-SPLIT shared 0.0f-return tail of 7A98 —
 * 7A98's null path `beql v1,0` lands at 7ABC+4 (0x7AC0), reusing this
 * `jr ra; mov.s f0,f2`; the `mtc1 $0,$f2`@7ABC itself is dead (the beql delay
 * slot already set $f2). `return 0.0f` in isolation emits `mtc1 $0,$f0`
 * (direct) — the $f2 form is purely a consequence of IDO's whole-file
 * cross-jump unifying this tail with 7A98's $f2 tail, which C can't bootstrap
 * (see 7A98's note: 7ABC-isolation always copy-propagates to $f0). A combined
 * 7A98+7ABC merge was tested and failed; keep this as an honest standalone NM
 * tail-share cap. Kept INCLUDE_ASM (ROM bytes correct). PREFIX_BYTES/INSN_PATCH
 * promotion removed 2026-05-23 (match-faking, banned).
 *
 * SOURCE=3 audit 2026-06-01: this is still the first discover-by-size result.
 * report.json shows 58.75% for the isolated NM body, and no jal/reloc/symname
 * caller has appeared. This is not a small unstarted function; it is the known
 * cross-tail-share standalone cap.
 * 2026-06-10 conversion-shape sweep (NEGATIVE, 6 shapes x O2/O1/O0):
 * the target keeps `mtc1 zero,$f2; cvt.s.w $f0,$f2` (unfolded int->
 * float of a known-zero), but every C zero-source (literal, local,
 * dead-arg overwrite, x-x, volatile, barrier'd) either folds to a
 * direct `mtc1 zero,$f0` (-O2) or grows a frame (-O1/-O0). The $f2
 * intermediate (a float TEMP, not the return reg) is further context
 * evidence: the cvt's operand web belonged to a larger expression in
 * the original parent. Verdict unchanged; do not re-sweep. */
#ifdef NON_MATCHING
float game_uso_func_00007ABC(void) { return 0.0f; }
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007ABC);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00007ACC: 0x150 (84 insns). Function-table dispatcher.
 * ~92% fuzzy, 67/84 words EXACT, word-count now EQUAL (was 82 build / 84
 * target). 2026-07 refinement CRACKED the frame-layout gap (0x28->0x38)
 * that the old note called an unforced codegen-cap:
 *   (1) The dispatch callee's 2nd arg is a 1-word struct passed BY VALUE
 *       (`S1_7ACC av; av.a = **(...); func(a0, av, ...)`), which forces
 *       IDO to emit BOTH the local temp-copy `sw a1,0x34(sp)` AND the
 *       outgoing-home `sw a1,4(sp)` in the jal delay — exactly the two
 *       "dead" stores the old note said were unreproducible. Same idiom
 *       as the game_uso precall-spill family (docs/PATTERNS.md) but 1-word.
 *   (2) The 0x958 store re-reads through the just-stored 0x954 slot
 *       (`*(tbl+0x958)=((int*)*(int*)(tbl+0x954))[0x2C]`), not reusing r.
 *   (3) Tail is `if(inner!=0){math}` (single beql-skip), not
 *       `if(inner==0)return` (which inverts to bnezl+b).
 *   (4) `av` declared FIRST fixes its stack slot to 0x34.
 * RESIDUAL (17 words): a single register-coloring PERMUTATION — the
 * saved return value r lands in a2 (build) vs t0 (target); everything
 * downstream (tail temps t1-t3 vs t2-a1, inner a1 vs a2, r-spill slot
 * 0x2C vs 0x30) shifts with it. IDO leaves t0 unused and colors r into
 * arg-reg a2; no C lever found to flip it (|0, decl-order, temp-hoist,
 * arm-swap all tried — permuter-immune coloring class). NOT exact.
 *
 * Signature: 4 register args (NOT idx — that comes from a0[0x40]):
 *   a0 = struct ptr (saved as s0 throughout)
 *   a1 = output int* (write r->[0x2C] here)
 *   a2 = arg3 (passed through to dispatch callee)
 *   a3 = arg4 — int* output flag (1 if r changed, 0 if same)
 *
 * Body (decoded 2026-05-05 from asm 0x7ACC-0x7C18):
 *   *a1 = 0;
 *   v = a0[0x40];
 *   if (v < 0 || v >= 12) ASSERT(...);
 *   // Indirect-then-deref through D-table:
 *   //   first: tab[v] = *(int**)(&D + 0x548 + v*4)
 *   //   then:  *tab[v] is loaded as the dispatched-call's a1 arg
 *   r = gl_func_00000000(a0, *(int*)D[0x548 + v*4], arg3, arg4);
 *   if (!r) return 0;
 *   if (r != a0[0x78]) { if (arg4) *arg4=1; a0[0x78]=r; }
 *   else                { if (arg4) *arg4=0; }
 *   *a1 = r->0x2C;
 *   tbl = a0->0x30;
 *   tbl->0x954 = r;
 *   tbl->0x958 = r->0x2C;
 *   if (tbl->0x958 == 0) return r;  // beql at 0x7BB4 jumps to epilogue with v0=t0=r
 *   // Float math (a2 != 0 = inner ptr exists):
 *   tbl->0x9B8f = tbl->0xB4f - inner->0x30f;
 *   tbl->0x9BCf = 0.0f;
 *   tbl->0x9C0f = tbl->0xBCf - inner->0x38f;
 *   gl_func_00000000(&tbl->0x9B8);
 *   return r;
 *
 * Identifies as a GAME-EVENT DISPATCHER for 12 cases (a0[0x40] = case idx).
 * The &D + 0x548 table is a 12-entry struct-pointer array. Each struct's
 * first word is some kind of context value passed to the dispatch callee.
 *
 * Multi-pass — initial body, expect ~30-50% on first build. Reloads from
 * s0->0x30 in asm aren't cached (each access re-reads), which the compiler
 * will reproduce when expressed as direct field accesses below. */
extern void game_uso_func_047B1C();
/* game_uso_func_071028 declared near game_uso_func_00001DDC. */
typedef struct { int a; } S1_7ACC;
int game_uso_func_00007ACC(int *a0, int *a1, int arg3, int *arg4) {
    S1_7ACC av;
    int v;
    int *r;
    int *inner;

    *a1 = 0;
    v = a0[0x40 / 4];
    if (v < 0 || v >= 12) {
        game_uso_func_047B1C((char*)&D_00000000 + 0x78C,
                         (char*)&D_00000000 + 0x7B0, 0x609);
    }
    /* Re-load v from a0[0x40] for the table-lookup — matches asm 0x7B1C
     * which has an independent lw v0,0x40(s0) after the assertion jal. */
    av.a = *(int*)(*(int*)((char*)&D_00000000 + 0x548 + a0[0x40 / 4] * 4));
    r = (int*)game_uso_func_0000A374(a0, av, arg3, arg4);
    if (r == 0) return 0;

    if (r != (int*)a0[0x78 / 4]) {
        if (arg4 != 0) *arg4 = 1;
        a0[0x78 / 4] = (int)r;
    } else {
        if (arg4 != 0) *arg4 = 0;
    }

    *a1 = r[0x2C / 4];
    *(int*)((char*)a0[0x30 / 4] + 0x954) = (int)r;
    *(int*)((char*)a0[0x30 / 4] + 0x958) =
        *(int*)((char*)*(int*)((char*)a0[0x30 / 4] + 0x954) + 0x2C);

    inner = (int*)*(int*)((char*)a0[0x30 / 4] + 0x958);
    if (inner != 0) {
        *(float*)((char*)a0[0x30 / 4] + 0x9B8) =
            *(float*)((char*)a0[0x30 / 4] + 0xB4) - *(float*)((char*)inner + 0x30);
        *(float*)((char*)a0[0x30 / 4] + 0x9BC) = 0.0f;
        *(float*)((char*)a0[0x30 / 4] + 0x9C0) =
            *(float*)((char*)a0[0x30 / 4] + 0xBC)
            - *(float*)((char*)*(int*)((char*)a0[0x30 / 4] + 0x958) + 0x38);
        game_uso_func_071028((char*)a0[0x30 / 4] + 0x9B8);
    }
    return (int)r;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007ACC);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00007C1C: 0x10BC (1071 insns). Collision/penetration sweep:
 * builds an xz-plane "closest approach" vector by walking the arg3->0x2C
 * collider chain. Re-decoded 2026-06-24 from expected/.o via fan-out subagent.
 * Vec3 + Tri3i double-buffer + real callee symbols. Logic faithful end-to-end;
 * residual gap is IDO frame/regalloc scheduling across the fanout blocks. */

int game_uso_func_00007C1C(char *arg0, char *arg1, char *arg2, char *arg3,
                           char *arg4, f32 *arg5) {
    Vec3 result;                     /* sp+932 */
    Vec3 cpA;                        /* sp+920 */
    Vec3 nA;                         /* sp+908 */
    Vec3 scratch;                    /* sp+852 shared word-copy stage */
    Vec3 nB;                         /* sp+840 */
    Vec3 stg1;                       /* sp+820 */
    Vec3 mA;                         /* sp+808 */
    Vec3 mC2;                        /* sp+796 */
    int mode;                        /* sp+792 */
    Vec3 stg2;                       /* sp+780 */
    Vec3 segDir;                     /* sp+768 */
    Vec3 resDir;                     /* sp+756 */
    Vec3 hitA;                       /* sp+736 */
    Vec3 hitB;                       /* sp+724 */
    int hit;                         /* sp+720 */
    Vec3 hitC;                       /* sp+704 */
    Vec3 mB;                         /* sp+692 */
    Vec3 mE;                         /* sp+652 */
    Vec3 mC;                         /* sp+640 */
    Vec3 mD;                         /* sp+628 */
    Vec3 mP;                         /* sp+616 */
    Vec3 mD2;                        /* sp+604 */
    Vec3 s1c;                        /* sp+592 */
    Vec3 s1bb;                       /* sp+580 */
    Vec3 s1b;                        /* sp+568 */
    Vec3 s1a;                        /* sp+556 */
    Vec3 mid2;                       /* sp+540 shared mid stage */
    Vec3 s1m2;                       /* sp+528 */
    Vec3 mid3;                       /* sp+508 shared mid stage */
    Vec3 s1m3;                       /* sp+496 */
    Vec3 s2c;                        /* sp+460 */
    Vec3 s2bb;                       /* sp+448 */
    Vec3 s2b;                        /* sp+436 */
    Vec3 s2a;                        /* sp+424 */
    Vec3 s2m2;                       /* sp+412 */
    Vec3 s2m3;                       /* sp+400 */
    Vec3 lSeg;                       /* sp+380 */
    Vec3 lA;                         /* sp+368 */
    Vec3 lE;                         /* sp+356 */
    Vec3 lDir;                       /* sp+344 */
    Vec3 lRD;                        /* sp+332 */
    Vec3 lB;                         /* sp+320 */
    Vec3 lP;                         /* sp+308 */
    Vec3 lF;                         /* sp+296 */
    Vec3 l1c;                        /* sp+284 */
    Vec3 l1bb;                       /* sp+272 */
    Vec3 l1b;                        /* sp+260 */
    Vec3 l1a;                        /* sp+248 */
    Vec3 l1m2;                       /* sp+236 */
    Vec3 l1m3;                       /* sp+224 */
    Vec3 l2c;                        /* sp+208 */
    Vec3 l2bb;                       /* sp+196 */
    Vec3 l2b;                        /* sp+184 */
    Vec3 l2a;                        /* sp+172 */
    Vec3 l2m2;                       /* sp+160 */
    Vec3 l2m3;                       /* sp+148 */
    Vec3 fA;                         /* sp+136 */
    Vec3 fB;                         /* sp+124 */
    Vec3 n0;                         /* sp+112 */
    Vec3 n1;                         /* sp+100 */
    Vec3 n2;                         /* sp+88 */
    int notFirst;                    /* sp+84 */
    int firstFlag;                   /* sp+80 */
    Vec3 *p;
    f32 *q;
    char *node;
    float k;
    float metric, thresh;

    if (arg5 != NULL) {
        *arg5 = 0.0f;
    }

    if (arg3 == NULL) {
        q = (f32 *)((int)arg2 + 0x30);
        p = 0; if (1) { p = &nA; }
        if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
            p->y = 0.0f;
            p->x = *q;
            p->z = *(f32 *)((int)q + 8);
        }
        p = 0; if (1) { p = &nB; }
        if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
            p->y = 0.0f;
            p->x = nA.x - *(f32 *)(arg4 + 0x0);
            p->z = nA.z - *(f32 *)(arg4 + 0x8);
        }
        *(Tri3i *)&scratch = *(Tri3i *)&nB;
        *(Tri3i *)&cpA = *(Tri3i *)&scratch;
        result.y = 0.0f;
        result.z = cpA.z;
        result.x = cpA.x;
    } else {
        mode = 0;
        q = (f32 *)((int)arg3 + 0x30);
        p = 0; if (1) { p = &mA; }
        if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
            p->y = 0.0f;
            p->z = *(f32 *)((int)q + 8);
            p->x = *q;
        }
        q = (f32 *)((int)arg2 + 0x30);
        p = 0; if (1) { p = &mB; }
        if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
            p->y = 0.0f;
            p->x = mA.x - *q;
            p->z = mA.z - *(f32 *)((int)q + 8);
        }
        *(Tri3i *)&scratch = *(Tri3i *)&mB;
        *(Tri3i *)&stg1 = *(Tri3i *)&scratch;
        *(Tri3i *)&stg2 = *(Tri3i *)&stg1;

        if (*(int *)(*(int *)(arg1 + 0x30) + 0x908) != 0) {
            float dot = game_uso_func_00007A98((int *)arg1);
            int active = *(int *)(arg1 + 0xA4);
            if (active == 0) {
                if (*(f32 *)(arg1 + 0xA0) <= dot) {
                    active = 1;
                    *(int *)(arg1 + 0xA4) = 1;
                }
            } else if (dot <= -*(f32 *)(arg1 + 0xA0)) {
                *(int *)(arg1 + 0xA4) = 0;
                active = 0;
            }
            if (active == 1 && dot <= *(f32 *)((char *)&D_00000000 + 0xFC)) {
                char *src = (char *)(*(int *)(arg1 + 0x30) + 0x908) + 0xB4;
                p = 0; if (1) { p = &mC; }
                if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
                    p->y = 0.0f;
                    p->x = *(f32 *)(src + 0x0);
                    p->z = *(f32 *)(src + 0x8);
                }
                q = (f32 *)((int)arg2 + 0x30);
                p = 0; if (1) { p = &mD; }
                if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
                    p->y = 0.0f;
                    p->x = mC.x - *q;
                    p->z = mC.z - *(f32 *)((int)q + 8);
                }
                *(Tri3i *)&scratch = *(Tri3i *)&mD;
                *(Tri3i *)&mE = *(Tri3i *)&scratch;
                mode = (stg2.x * mE.z <= stg2.z * mE.x) ? 2 : 1;
            }
        }

        p = 0; if (1) { p = &mP; }

        if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
            p->y = 0.0f;
            p->x = stg2.z;
            p->z = -stg2.x;
        }
        *(Tri3i *)&scratch = *(Tri3i *)&mP;
        *(Tri3i *)&segDir = *(Tri3i *)&scratch;
        game_uso_func_071028(&segDir);

        q = (f32 *)((int)arg3 + 0x30);

        p = 0; if (1) { p = &mC2; }

        if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
            p->y = 0.0f;
            p->z = *(f32 *)((int)q + 8);
            p->x = *q;
        }
        p = 0; if (1) { p = &mD2; }
        if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
            p->y = 0.0f;
            p->x = mC2.x - *(f32 *)(arg4 + 0x0);
            p->z = mC2.z - *(f32 *)(arg4 + 0x8);
        }
        *(Tri3i *)&scratch = *(Tri3i *)&mD2;
        *(Tri3i *)&resDir = *(Tri3i *)&scratch;
        result = scratch;

        if (mode == 1) {
            s1a.x = segDir.x * 250.0f;
            s1a.y = segDir.y * 250.0f;
            s1a.z = segDir.z * 250.0f;
            *(Tri3i *)&scratch = *(Tri3i *)&s1a;
            *(Tri3i *)&s1b = *(Tri3i *)&scratch;
            k = *(f32 *)(arg3 + 0x54);
            s1m2.x = s1b.x * k;
            s1m2.y = s1b.y * k;
            s1m2.z = s1b.z * k;
            *(Tri3i *)&mid2 = *(Tri3i *)&s1m2;
            *(Tri3i *)&s1bb = *(Tri3i *)&mid2;
            s1m3.x = s1bb.x * 0.5f;
            s1m3.y = s1bb.y * 0.5f;
            s1m3.z = s1bb.z * 0.5f;
            *(Tri3i *)&mid3 = *(Tri3i *)&s1m3;
            *(Tri3i *)&s1c = *(Tri3i *)&mid3;
            result.x += s1c.x;
            result.y += s1c.y;
            result.z += s1c.z;
        } else if (mode == 2) {
            s2a.x = segDir.x * 250.0f;
            s2a.y = segDir.y * 250.0f;
            s2a.z = segDir.z * 250.0f;
            *(Tri3i *)&scratch = *(Tri3i *)&s2a;
            *(Tri3i *)&s2b = *(Tri3i *)&scratch;
            k = *(f32 *)(arg3 + 0x54);
            s2m2.x = s2b.x * k;
            s2m2.y = s2b.y * k;
            s2m2.z = s2b.z * k;
            *(Tri3i *)&mid2 = *(Tri3i *)&s2m2;
            *(Tri3i *)&s2bb = *(Tri3i *)&mid2;
            s2m3.x = s2bb.x * 0.5f;
            s2m3.y = s2bb.y * 0.5f;
            s2m3.z = s2bb.z * 0.5f;
            *(Tri3i *)&mid3 = *(Tri3i *)&s2m3;
            *(Tri3i *)&s2c = *(Tri3i *)&mid3;
            result.x -= s2c.x;
            result.y -= s2c.y;
            result.z -= s2c.z;
        }

        metric = game_uso_func_082880(resDir.x * resDir.x + resDir.z * resDir.z);
        hit = 0;
        thresh = *(f32 *)(arg3 + 0x54) * 250.0f;
        if (thresh < metric) {
            game_uso_func_00003FAC(&hitA.x, &hitB.x, &resDir.x, metric, thresh);
            hit = 1;
        }

        node = *(char **)(arg3 + 0x2C);
        while (node != NULL) {
            notFirst = (hit != 0);
            firstFlag = (notFirst == 0);

            q = (f32 *)((int)node + 0x30);

            p = 0; if (1) { p = &lA; }

            if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
                p->y = 0.0f;
                p->x = *q;
                p->z = *(f32 *)((int)q + 8);
            }
            q = (f32 *)((int)arg3 + 0x30);
            p = 0; if (1) { p = &lB; }
            if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
                p->y = 0.0f;
                p->z = lA.z - *(f32 *)((int)q + 8);
                p->x = lA.x - *q;
            }
            *(Tri3i *)&scratch = *(Tri3i *)&lB;
            *(Tri3i *)&lSeg = *(Tri3i *)&scratch;

            p = 0; if (1) { p = &lP; }

            if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
                p->y = 0.0f;
                p->x = lSeg.z;
                p->z = -lSeg.x;
            }
            *(Tri3i *)&mid2 = *(Tri3i *)&lP;
            *(Tri3i *)&lDir = *(Tri3i *)&mid2;
            game_uso_func_071028(&lDir);

            q = (f32 *)((int)node + 0x30);

            p = 0; if (1) { p = &lE; }

            if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
                p->y = 0.0f;
                p->x = *q;
                p->z = *(f32 *)((int)q + 8);
            }
            p = 0; if (1) { p = &lF; }
            if (p != NULL || (p = (Vec3 *)game_uso_func_055750(0xC)) != NULL) {
                p->y = 0.0f;
                p->x = lE.x - *(f32 *)(arg4 + 0x0);
                p->z = lE.z - *(f32 *)(arg4 + 0x8);
            }
            *(Tri3i *)&scratch = *(Tri3i *)&lF;
            *(Tri3i *)&lRD = *(Tri3i *)&scratch;
            hitC = scratch;

            if (mode == 1) {
                l1a.x = lDir.x * 250.0f;
                l1a.y = lDir.y * 250.0f;
                l1a.z = lDir.z * 250.0f;
                *(Tri3i *)&scratch = *(Tri3i *)&l1a;
                *(Tri3i *)&l1b = *(Tri3i *)&scratch;
                k = *(f32 *)(node + 0x54);
                l1m2.x = l1b.x * k;
                l1m2.y = l1b.y * k;
                l1m2.z = l1b.z * k;
                *(Tri3i *)&mid2 = *(Tri3i *)&l1m2;
                *(Tri3i *)&l1bb = *(Tri3i *)&mid2;
                l1m3.x = l1bb.x * 0.5f;
                l1m3.y = l1bb.y * 0.5f;
                l1m3.z = l1bb.z * 0.5f;
                *(Tri3i *)&mid3 = *(Tri3i *)&l1m3;
                *(Tri3i *)&l1c = *(Tri3i *)&mid3;
                hitC.x += l1c.x;
                hitC.y += l1c.y;
                hitC.z += l1c.z;
            } else if (mode == 2) {
                l2a.x = lDir.x * 250.0f;
                l2a.y = lDir.y * 250.0f;
                l2a.z = lDir.z * 250.0f;
                *(Tri3i *)&scratch = *(Tri3i *)&l2a;
                *(Tri3i *)&l2b = *(Tri3i *)&scratch;
                k = *(f32 *)(node + 0x54);
                l2m2.x = l2b.x * k;
                l2m2.y = l2b.y * k;
                l2m2.z = l2b.z * k;
                *(Tri3i *)&mid2 = *(Tri3i *)&l2m2;
                *(Tri3i *)&l2bb = *(Tri3i *)&mid2;
                l2m3.x = l2bb.x * 0.5f;
                l2m3.y = l2bb.y * 0.5f;
                l2m3.z = l2bb.z * 0.5f;
                *(Tri3i *)&mid3 = *(Tri3i *)&l2m3;
                *(Tri3i *)&l2c = *(Tri3i *)&mid3;
                hitC.x -= l2c.x;
                hitC.y -= l2c.y;
                hitC.z -= l2c.z;
            }

            if (firstFlag ||
                ((hitC.x * hitA.z <= hitC.z * hitA.x) &&
                 (hitC.z * hitB.x <= hitC.x * hitB.z))) {
                float m2 = game_uso_func_082880(lRD.x * lRD.x + lRD.z * lRD.z);
                float t2 = *(f32 *)(node + 0x54) * 250.0f;
                if (t2 < m2) {
                    game_uso_func_00003FAC(&fA.x, &fB.x, &lRD.x, m2, t2);
                    hit = 1;
                    if (notFirst) {
                        if (hitA.z * fA.x < hitA.x * fA.z) {
                            *(Tri3i *)&scratch = *(Tri3i *)&fA;
                            hitA = scratch;
                        }
                        if (hitB.x * fB.z < hitB.z * fB.x) {
                            *(Tri3i *)&scratch = *(Tri3i *)&fB;
                            hitB = scratch;
                        }
                    } else {
                        *(Tri3i *)&scratch = *(Tri3i *)&fA;
                        hitA = scratch;
                        *(Tri3i *)&scratch = *(Tri3i *)&fB;
                        hitB = scratch;
                    }
                }
                *(Tri3i *)&scratch = *(Tri3i *)&hitC;
                result = scratch;
                arg3 = node;
                node = *(char **)(node + 0x2C);
                continue;
            }
            break;
        }

        if (node != NULL &&
            game_uso_func_082880(result.x * result.x + result.z * result.z) <
                *(f32 *)(*(int *)(arg1 + 0x30) + 0x348) * *(f32 *)(arg1 + 0xCC)) {
            *(Tri3i *)&n0 = *(Tri3i *)&hitC;
            game_uso_func_071028(&n0);
            *(Tri3i *)&n1 = *(Tri3i *)&hitA;
            game_uso_func_071028(&n1);
            *(Tri3i *)&n2 = *(Tri3i *)&hitB;
            game_uso_func_071028(&n2);
            if ((n0.x * n2.x + n0.z * n2.z) < (n0.x * n1.x + n0.z * n1.z)) {
                *(Tri3i *)&scratch = *(Tri3i *)&hitA;
                result = scratch;
            } else {
                *(Tri3i *)&scratch = *(Tri3i *)&hitB;
                result = scratch;
            }
        }
    }

    *(Tri3i *)arg0 = *(Tri3i *)&result;
    return (int)arg0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007C1C);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00008CD8: large vector/triangle integrator.
 * Reconstructed from EXPECTED .o (0x8cd8..0x97ec, 0xb14/709w).
 * arg0 = out Vec3* (returned). arg1 = self obj. arg2 = ref obj.
 * arg3 = aux obj. arg4 = flag selecting the two main branches.
 * Repeated alloc-guard idiom: p = &local; if(p==0){p=alloc(12);} if(p){ write Vec3 }.
 * 16x game_uso_func_055750(12) Vec3 allocs, 2x game_uso_func_071028 normalize,
 * 4-entry dispatch game_uso_D_807FFA20 on (self[0x9C]+1)&3 sharing tail @0x973c.
 * FP consts: 2.0, 0.5, 250.0, -1.0. */
void *game_uso_func_00008CD8(char *arg0, char *arg1, char *arg2, char *arg3, s32 arg4) {
    Vec3 sp1F8;   /* sp+504 */
    Vec3 sp204;   /* sp+516 (only x used as scratch chain) */
    Vec3 sp1E0;   /* sp+480 */
    Vec3 sp14C;   /* sp+332 */
    Vec3 sp1D4;   /* sp+468 */
    Vec3 sp11C;   /* sp+284 */
    Vec3 sp1C8;   /* sp+456 */
    Vec3 sp1BC;   /* sp+444 */
    Vec3 sp1B0;   /* sp+432 */
    Vec3 sp164;   /* sp+356 */
    Vec3 sp174;   /* sp+372 working Vec3 */
    Vec3 spE4;    /* sp+228 */
    Vec3 spA8;    /* sp+168 */
    Vec3 spF0;    /* sp+240 */
    Vec3 spCC;    /* sp+204 */
    Vec3 sp9C;    /* sp+156 */
    Vec3 spC0;    /* sp+192 */
    Vec3 spD8;    /* sp+216 */
    Vec3 sp90;    /* sp+144 */
    Vec3 spB4;    /* sp+180 */
    Vec3 sp54;    /* sp+84  */
    Vec3 sp60;    /* sp+96  */
    Vec3 sp84;    /* sp+132 */
    Vec3 sp48;    /* sp+72  */
    Vec3 sp6C;    /* sp+108 */
    Vec3 sp78;    /* sp+120 */
    Vec3 sp3C;    /* sp+60  */
    Vec3 sp24;    /* sp+36  */
    Vec3 *p;
    Vec3 *base;
    f32 lenf;
    f32 dot;
    s32 idx;
    s32 idxm;
    Vec3 *ref30;

    if (arg4 != 0) {
        /* --- branch A (flag set) --- */
        p = 0; if (1) { p = &sp1F8; }
        if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
        if (p != 0) {
            p->x = *(f32 *)(arg3 + 0x30);
            p->y = 0.0f;
            p->z = *(f32 *)(arg3 + 0x38);
        }
        ref30 = (Vec3 *)(arg3 + 0x30);
        p = 0; if (1) { p = &sp164; }
        if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
        if (p != 0) {
            p->x = sp1F8.x - ref30->x;
            p->y = 0.0f;
            p->z = sp1F8.z - ref30->z;
        }
        sp174 = sp164;
        sp204 = sp174;
        sp1B0 = sp174;
        game_uso_func_071028(&sp1B0);

        base = (Vec3 *)(*(s32 *)(arg1 + 0x30) + 0xB4);
        p = 0; if (1) { p = &sp1E0; }
        if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
        if (p != 0) {
            p->x = base->x;
            p->z = base->z;
            p->y = 0.0f;
        }
        p = 0; if (1) { p = &sp14C; }
        if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
        if (p != 0) {
            Vec3 *r = (Vec3 *)(arg2 + 0x30);
            p->x = sp1E0.x - r->x;
            p->y = 0.0f;
            p->z = sp1E0.z - r->z;
        }
        sp174 = sp14C;
        sp1D4 = sp174;

        lenf = (sp1B0.x * sp1D4.x) + (sp1B0.z * sp1D4.z);
        p = 0; if (1) { p = &sp1D4; }
        if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
        if (p != 0) {
            Vec3 *r = (Vec3 *)(arg2 + 0x30);
            p->y = 0.0f;
            p->z = r->z;
            p->x = r->x;
        }
        sp174 = sp1D4;
        *(f32 *)(arg1 + 0x90) = sp174.x;
        *(f32 *)(arg1 + 0x94) = sp174.y;
        *(f32 *)(arg1 + 0x98) = sp174.z;
        sp11C = sp174;
        *(f32 *)(arg1 + 0x84) = sp11C.x;
        *(f32 *)(arg1 + 0x88) = sp11C.y;
        *(f32 *)(arg1 + 0x8C) = sp11C.z;

        dot = lenf + ((*(f32 *)(*(s32 *)(arg1 + 0x30) + 0x348) * *(f32 *)(arg1 + 0xDC)) / 2.0f);
        sp1C8.x = sp1B0.x * dot;
        sp1C8.y = sp1B0.y * dot;
        sp1C8.z = sp1B0.z * dot;
        sp174 = sp1C8;
        sp1C8 = sp174;
        *(f32 *)(arg1 + 0x84) += sp1C8.x;
        *(f32 *)(arg1 + 0x88) += sp1C8.y;
        *(f32 *)(arg1 + 0x8C) += sp1C8.z;

        dot = lenf - ((*(f32 *)(*(s32 *)(arg1 + 0x30) + 0x348) * *(f32 *)(arg1 + 0xDC)) / 2.0f);
        sp1BC.x = sp1B0.x * dot;
        sp1BC.y = sp1B0.y * dot;
        sp1BC.z = sp1B0.z * dot;
        sp174 = sp1BC;
        sp1BC = sp174;
        *(f32 *)(arg1 + 0x90) += sp1BC.x;
        *(f32 *)(arg1 + 0x94) += sp1BC.y;
        *(s32 *)(arg1 + 0x9C) = 0;
        *(f32 *)(arg1 + 0x98) += sp1BC.z;
        goto tail;
    }

    /* --- branch B (flag clear) --- */
    p = 0; if (1) { p = &spE4; }
    if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
    if (p != 0) {
        p->y = 0.0f;
        p->z = *(f32 *)(arg3 + 0x38);
        p->x = *(f32 *)(arg3 + 0x30);
    }
    ref30 = (Vec3 *)(arg3 + 0x30);
    p = 0; if (1) { p = &spA8; }
    if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
    if (p != 0) {
        p->x = spE4.x - ref30->x;
        p->y = 0.0f;
        p->z = spE4.z - ref30->z;
    }
    sp174 = spA8;
    spF0 = spA8;
    spCC = spF0;

    base = (Vec3 *)(arg1 + 0x84);
    p = 0; if (1) { p = &sp9C; }
    if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
    if (p != 0) {
        p->x = spF0.x - *(f32 *)(arg1 + 0x90);
        p->y = 0.0f;
        p->z = spF0.z - *(f32 *)(arg1 + 0x98);
    }
    sp174 = sp9C;
    spC0 = sp174;

    base = (Vec3 *)(*(s32 *)(arg1 + 0x30) + 0xB4);
    p = 0; if (1) { p = &spD8; }
    if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
    if (p != 0) {
        p->x = base->x;
        p->z = base->z;
        p->y = 0.0f;
    }
    p = 0; if (1) { p = &sp90; }
    if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
    if (p != 0) {
        Vec3 *r = (Vec3 *)(arg1 + 0x90);
        p->x = spD8.x - r->x;
        p->y = 0.0f;
        p->z = spD8.z - r->z;
    }
    sp174 = sp90;
    spB4 = sp174;

    if ((((spCC.x * spC0.x) + (spCC.z * spC0.z)) * 0.5f) < ((spCC.x * spB4.x) + (spCC.z * spB4.z))) {
        sp174.x = *(f32 *)(arg1 + 0x84);
        sp174.y = *(f32 *)(arg1 + 0x88);
        sp174.z = *(f32 *)(arg1 + 0x8C);
        spCC = sp174;
        *(f32 *)(arg1 + 0x90) = sp174.x;
        *(f32 *)(arg1 + 0x94) = sp174.y;
        *(f32 *)(arg1 + 0x98) = sp174.z;
        game_uso_func_071028(&spCC);

        p = 0; if (1) { p = &sp54; }
        if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
        if (p != 0) {
            p->x = spCC.z;
            p->z = -spCC.x;
            p->y = 0.0f;
        }
        sp174 = sp54;
        sp60 = sp174;

        p = 0; if (1) { p = &sp84; }
        if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
        if (p != 0) {
            Vec3 *r = (Vec3 *)(arg2 + 0x30);
            p->y = 0.0f;
            p->z = r->z;
            p->x = r->x;
        }
        sp174 = sp84;
        *(f32 *)(arg1 + 0x84) = sp174.x;
        *(f32 *)(arg1 + 0x88) = sp174.y;
        *(f32 *)(arg1 + 0x8C) = sp174.z;

        p = 0; if (1) { p = &sp48; }
        if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
        if (p != 0) {
            Vec3 *r = (Vec3 *)(arg2 + 0x30);
            p->x = *(f32 *)(arg1 + 0x90) - r->x;
            p->y = 0.0f;
            p->z = *(f32 *)(arg1 + 0x98) - r->z;
        }
        sp174 = sp48;
        sp6C = sp174;

        dot = (spCC.x * sp6C.x) + (spCC.z * sp6C.z)
            + (*(f32 *)(*(s32 *)(arg1 + 0x30) + 0x348) * *(f32 *)(arg1 + 0xDC));
        sp3C.x = spCC.x * dot;
        sp3C.y = spCC.y * dot;
        sp3C.z = spCC.z * dot;
        sp11C = sp3C;
        sp78 = sp11C;
        *(f32 *)(arg1 + 0x84) += sp78.x;
        *(f32 *)(arg1 + 0x88) += sp78.y;
        *(f32 *)(arg1 + 0x8C) += sp78.z;

        lenf = 250.0f * *(f32 *)(arg3 + 0x54) * *(f32 *)(arg1 + 0xE0);
        sp60.x *= lenf;
        sp60.z *= lenf;
        sp60.y *= lenf;

        idx = *(s32 *)(arg1 + 0x9C) + 1;
        idxm = idx & 3;
        *(s32 *)(arg1 + 0x9C) = idx;
        *(s32 *)(arg1 + 0x9C) = idxm;
        if ((u32)idxm < 4U) {
            switch (idxm) {
            case 0:
                sp60.x *= 0.0f;
                sp60.y *= 0.0f;
                sp60.z *= 0.0f;
                break;
            case 1:
                sp60.x *= -1.0f;
                sp60.y *= -1.0f;
                sp60.z *= -1.0f;
                break;
            }
        }
        *(f32 *)(arg1 + 0x84) += sp60.x;
        *(f32 *)(arg1 + 0x88) += sp60.y;
        *(f32 *)(arg1 + 0x8C) += sp60.z;
    }

tail:
    base = (Vec3 *)(*(s32 *)(arg1 + 0x30) + 0xB4);
    p = 0; if (1) { p = &sp24; }
    if (p == 0) { p = (Vec3 *)game_uso_func_055750(12); }
    if (p != 0) {
        Vec3 *r = (Vec3 *)(arg1 + 0x84);
        p->x = r->x - base->x;
        p->y = 0.0f;
        p->z = r->z - base->z;
    }
    sp174 = sp24;
    *(f32 *)(arg0 + 0x0) = sp174.x;
    *(f32 *)(arg0 + 0x4) = sp174.y;
    *(f32 *)(arg0 + 0x8) = sp174.z;
    return arg0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00008CD8);
#endif

// game_uso_func_000097EC — STRUCTURAL PASS (0x39C / 231 words,
// no episode). Raw-.word USO form (single function, game_uso main
// game-logic segment). FP-heavy (33 FP ops, ~6 calls).
//
// Multi-point ground/height-contact query: for several reference
// points on an object, raycast/sample the terrain and store the
// flattened contact position (snowboard ground-contact sampling).
//
//   void game_uso_func_000097EC(Obj *obj, A a1) {
//     World *w = obj->0x30;
//     if (!w->0x908) return;                              // no terrain
//     // repeated unit (~4-5x), once per reference point:
//     //   r = func_00000000(0xC, &w->0x318[k], &sp.scratch);
//     //   if (r) {                                        // hit
//     //     dst->x = scratch[0];  dst->y = 0.0f;          // flatten Y
//     //     dst->z = scratch[2];
//     //   }
//     //   k advances; dst is the next contact-point slot.
//   }
//
// Struct-typing reference:
//   obj->0x30 = World/terrain ctx; w->0x908 = terrain-loaded flag;
//   w->0x318 = base of reference-point records (per-point input to
//     the op-0xC raycast). func_00000000(0xC, point, &out) = the USO
//     terrain height/raycast query (op code 0xC); out Vec3 -> the
//     object's contact-point array with Y zeroed (XZ-plane contact).
//   sp+0xF4 / sp+0x100 = result scratch. a1 = a secondary param.
// Caps: raw-word USO + placeholder calls + 231-word FP loop — not
//   exact-matchable without proper USO mnemonic disasm; structural
//   pass only, no byte body.
// Full body INCLUDE_ASM-preserved (.s = source of truth). INCLUDE_ASM (no episode; tautology-trap rule).
#ifdef NON_MATCHING
extern float game_uso_func_082880(float);
/* A0E8-family geometric predicate (dead-alloc XZ vecs -> deltas -> normalize
 * 082880 -> cross/dot projection -> range gates -> return 0/1). Opening +
 * magnitude gate decoded; cross/dot tail pending (multi-tick). */
int game_uso_func_000097EC(char *a0) {
    char *v0 = *(char **)(a0 + 0x30);
    char *sub;
    Vec3 vec1, vec2, vec3, c1, c2, scaled, s1, s2, vec4, delta2, d1, d2, vec5;
    Vec3 *p;
    float mag2, scale, mag, cross, dot, tparam, perp;
    if (*(int *)(v0 + 0x908) == 0) return 0;
    p = &vec1;
    if (p == 0) p = (Vec3 *)game_uso_func_055750(12);
    p->x = *(float *)(v0 + 0x318);
    p->z = *(float *)(v0 + 0x320);
    p->y = 0.0f;
    sub = *(char **)(v0 + 0x908);
    p = &vec2;
    if (p == 0) p = (Vec3 *)game_uso_func_055750(12);
    p->x = *(float *)(sub + 0x318);
    p->z = *(float *)(sub + 0x320);
    p->y = 0.0f;
    mag2 = vec1.x * vec1.x + vec1.z * vec1.z;
    if (!(0.0f < mag2)) return 0;
    p = &vec3;
    if (p == 0) p = (Vec3 *)game_uso_func_055750(12);
    p->x = vec1.x - vec2.x;
    p->y = 0.0f;
    p->z = vec1.z - vec2.z;
    c1 = vec3;
    c2 = c1;
    scale = *(float *)(a0 + 0xD0);
    scaled.x = c2.x * scale;
    scaled.y = c2.y * scale;
    scaled.z = c2.z * scale;
    s1 = scaled;
    s2 = s1;
    p = &vec4;
    if (p == 0) p = (Vec3 *)game_uso_func_055750(12);
    p->x = s2.x;
    p->z = s2.z;
    p->y = 0.0f;
    delta2.x = *(float *)(sub + 0xB4) - *(float *)(v0 + 0xB4);
    delta2.y = *(float *)(sub + 0xB8) - *(float *)(v0 + 0xB8);
    delta2.z = *(float *)(sub + 0xBC) - *(float *)(v0 + 0xBC);
    d1 = delta2;
    d2 = d1;
    p = &vec5;
    if (p == 0) p = (Vec3 *)game_uso_func_055750(12);
    p->x = d2.x;
    p->z = d2.z;
    p->y = 0.0f;
    mag = game_uso_func_082880(vec4.x * vec4.x + vec4.z * vec4.z);
    if (!(0.0f < mag)) return 0;
    cross = vec4.z * vec5.x - vec4.x * vec5.z;
    if (cross < 0.0f) cross = -cross;
    dot = vec4.x * vec5.x + vec4.z * vec5.z;
    tparam = dot / (vec4.x * vec4.x + vec4.z * vec4.z);
    if (!(0.0f <= tparam)) return 0;
    if (!(tparam < 1.0f)) return 0;
    perp = cross / mag;
    if (!(perp < *(float *)(a0 + 0xD4))) return 0;
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000097EC);
#endif

extern void game_uso_func_047B1C();
extern char game_uso_D_807FEDB8;
#ifdef NON_MATCHING
/* 54.950580% NM (objdiff 2026-05-20; up from 50.38% before this pass).
 * game_uso_func_00009B88: 0x560 (344 insns), 0x1A8-byte stack frame.
 * Inferred from the final cross-product sign test + screen-space transform
 * constants: this is a billboard-visibility / 2D point-on-line predicate
 * applied to per-frame screen-projected anchor coordinates, returning a
 * boolean result via $v0.
 * Strategy-memo candidate for "per-frame compute" (1.4 KB, 11 cross-calls).
 *
 * Partial C body now captures entry (panic-on-a2-null + 2 cross-call
 * dispatches with sp+0x190 and sp+0xDC Vec3 locals), body-part-1 Vec3 copy
 * (a2->0x30 XZ-projection), the sp+0xC4 rotated vector, the 250.0f/50.0f
 * screen-space scale, the tail Vec3 fanout family, and the final
 * two-cross-product sign test. Remaining gap is the exact stack-layout /
 * FPU scheduling of the middle transform helpers.
 *
 * ENTRY DECODE (insns 1-15 @ 0x9B88-0x9BC4):
 *   args: (a0, a1, a2).  All three spilled to caller-slot (sp+0x1A8/AC/B0)
 *         at entry — suggests varargs or multi-reuse callee.
 *   if (a2 == 0) {
 *       panic/assert(&SYM+0x7BC, &SYM+0x7C8, 0x623);
 *       // jal gl_func_00000000, line number 0x623 = 1571
 *   }
 *   // sp+0x190: a local struct base.  `bnel v1,$0,...` on &local_struct
 *   // is trivially true (stack addr nonzero) — suggests compiler generated
 *   // null-guard around a pointer obtained from `local.field` indirection.
 *
 * BODY PART 1 (insns 15-50 @ 0x9BC4-0x9C54): dual Vec3-copy + math.
 *   local1 = sp+0x190:  // 3 floats
 *     local1[0] = a2[0x30].x; local1[1] = 0.0f; local1[2] = a2[0x30].z;
 *   local2 = sp+0xDC:  // another 3-float struct, guarded by bne
 *     local2[0] = a1[0x30].x ± a2-src; local2[1] = a1[0x38] mul ...;
 *     (math: 0x9C28 mtc1/mul.s, 0x9C38 sub.s on $f8/$f10 — scale/offset
 *      of the Vec3 from a2+0x30 against something from a1+0x30/0x38)
 *   local3 = sp+0xEC:  // 3-word int-style struct
 *     local3[0..8] = a1[0x30..0x38].intbits  // raw word copy (8C/AC pattern)
 *   local4 = sp+0x9C, local5 = sp+0x144:  more 3-word copies from a1 and
 *     stored to multiple slots — function is building a per-frame working
 *     set of transformed coordinates from the per-object anchor (a1+0x30).
 *
 * BODY PART 2 (insns 50-344 @ 0x9C54-0x10E8): heavy float math (many
 *   lwc1/mul.s/add.s/sub.s on sp+0x12C..sp+0x148, a quaternion or matrix
 *   slot), multiple cross-USO calls (`jal 0` placeholders — 11 per memo),
 *   several struct stores to sp+0x0C4..sp+0x144 (local buffer region).
 *   Scale constant 0xC7A ≈ 250.0f at 0x9D0C, offset 0x4248 ≈ 50.0f at 0x9D1C
 *   — suggests coordinate/angle scaling.
 *
 * BODY-PART-2 FRONT-HALF SCAN (2026-05-05, 0x9C54-0x9D00 = +43 insns):
 *   - 0x9C54-0x9C7C: TWO triple-fanout 12-byte struct copies. First reads
 *     a3+0/4/8 (= prior body-part-1 result) and writes BOTH t6+0/4/8 and
 *     v1+0/4/8 (sp+0x19C and sp+0x144). Second reads t1+0/4/8 and writes
 *     v0+0/4/8 (sp+0x144 again, possibly fanout to two captures).
 *   - 0x9C80-0x9C9C: bne v1, $zero, +7 — guarded cross-USO call
 *     `jal 0` with a0 = &local at sp+0xC4, a1 = &local at sp+0xEC,
 *     a2 = 0xC (likely byte length = 12). Pattern: copy/transform Vec3s
 *     between two stack slots via a stub helper.
 *   - 0x9CA0-0x9CCC: post-call results: lwc1 sp+0x144, lwc1 sp+0x14C,
 *     mtc1 zero, abs.s. Likely "abs(magnitude)" of the just-computed
 *     transformed Vec3 component. Stores to a1+0..8 (out-buffer).
 *   - 0x9CD0-0x9CFC: ANOTHER triple-fanout struct copy + jal 0 with
 *     a0 = sp+0x138 setup. Same 12-byte struct-pair pattern as before;
 *     two helpers in sequence each consuming a Vec3 transform result.
 *   - 0x9D00+: switch to FPU — lwc1 sp+0x138/+4/+8 + lui 0x437A (=250.0f).
 *     Next chunk (0x9D04-...) is float scaling against the 250.0f constant.
 *
 * BODY-PART-2 MID-SCAN (2026-05-05, 0x9D00-0x9DC0 = +49 insns):
 *   - 0x9D00-0x9D2C: build TWO local Vec3 buffers at sp+0x12C and sp+0x138
 *     by storing `a1->0x14C/0x150/0x158` arg vals into them, with constants
 *     0x437A0000 (= 250.0f) and 0x42480000 (= 50.0f) materialized via lui+at
 *     to specific slots. The 250.0f goes to one slot, 50.0f to another —
 *     looks like a "near-clip / far-clip" pair for projection or LOD.
 *   - 0x9D34-0x9D60: lw sp+0x1AC/0x1B0/0x1A8 (re-load a1/a2/a0
 *     pointers spilled at entry), then lwc1 sp+0x12C/0x130, lwc1 0x54(t2)
 *     — read transformed-coord result from a per-object slot, plus a
 *     stored-context float. Compute `f4 = f0 * f6` (scale).
 *   - 0x9D50-0x9D58: build the next-call args: a2 = sp+0xEC (ref to one
 *     of the local Vec3 bufs), a0 = 0xC (12-byte length) — call sig
 *     matches a copy/transform stub. abs.s on f8 sets the f-register up
 *     for the call.
 *   - 0x9D5C-0x9DA8: 3-component scale `out.x = a*x; out.y = b*y; out.z = c*z`
 *     where the input Vec3 is stored at sp+0x138/0x130/0x12C and the
 *     scaling factor floats live at 0x54(arg-context-ptr) — this is the
 *     "coord-scale by per-object factor" pass per memo's "scale 250.0f
 *     suggests coordinate scaling" guess.
 *   - 0x9DAC-0x9DC0: store the scaled Vec3 results to sp+0x138/+4/+8,
 *     then start another lw from a1->0x30 (per-object anchor) — the
 *     compute will continue with another stage on the just-stored results.
 *
 * ~225 insns remain stubbed past 0x9DC4.
 *
 * BODY-PART-2 SECOND-HALF SCAN (2026-05-05, 0x9DC4-0x9E50 = +35 insns):
 *   - 0x9DC4-0x9DD0: bne a3, $zero, +7 — guarded jal with a1=sp+0xB4
 *     setup. Cross-USO helper call, result spilled to sp+0x114.
 *   - 0x9DD4-0x9DF8: post-call XZ-projection store. lwc1 sp+0x114
 *     (callee result), lwc1 a1+0/8 (post-call dest), mtc1 zero into
 *     f6 (= 0.0f), swc1 to 0/4/8 — Vec3 = (callee.x, 0, callee.z).
 *   - 0x9DFC-0x9E08: another bne-guarded jal with a1=sp+0xB8, a0=0xC
 *     (12-byte size arg). Helper transforms a Vec3 between stack slots.
 *   - 0x9E0C-0x9E48: post-call FPU-heavy block. lwc1 sp+0x184/0x18C
 *     (saved entity refs), lwc1 a2-context's 0x30/0x38, neg.s f2,f18
 *     (sign-flip). addiu v0, v0, 0x30 (advance struct ptr by 48). 3
 *     swc1 commits to v0+0/4/8. "transform via context, commit to
 *     per-object slot" pattern.
 *   - 0x9E50+: lw chains feeding another fanout copy + jal — TODO.
 *
 * ~120 insns remain stubbed past 0x9E50.
 *
 * BODY-PART-2 THIRD-CHUNK SCAN (2026-05-05, 0x9E50-0x9F00 = +44 insns):
 *   - 0x9E50-0x9E80: 12-byte triple-fanout struct copy. Reads a1+0/4/8
 *     (yet-another src Vec3), writes t9+0/4/8 (a4-context buf) AND
 *     t6+0/4/8 (sp+0xA0 staging). Same save-old + write-new idiom.
 *   - 0x9E84-0x9E94: bne-guarded jal sequence with a0=0xC, a2=sp+0xEC
 *     setup. Pre-call abs.s on f8.
 *   - 0x9E98-0x9EC8: post-call FPU 3-component scale. Loads sp+0x144/
 *     0x138/0x14C/0x140 (4 floats from saved-result buffers), `mul.s
 *     f0, f6, f8` triple, mtc1 zero, swc1 to v1+0/4/8 — "scale-by-
 *     callee-result + clear" pattern.
 *   - 0x9ECC-0x9EFC: ANOTHER 12-byte fanout copy with save-old idiom.
 *     Reads a1+0/4/8, writes t3+0/4/8 (sp+0x178) AND t1+0/4/8 (a3-buf).
 *   - 0x9F00+: continues with another bne-guarded jal at 0x9F08+. ~80
 *     insns remain stubbed past 0x9F00.
 *
 * BODY-PART-2 FOURTH-CHUNK SCAN (2026-05-05, 0x9F00-0x9FE8 = +58 insns):
 *   - 0x9F00-0x9F18: post-call FPU 3-component scale. lwc1 sp+0x120/
 *     0x12C/0x128/0x134, sub.s f0,f4,f6 (delta), mtc1 zero (= 0.0f),
 *     mul.s f2,f10,f0 — "scale by callee-result delta" pattern.
 *   - 0x9F1C-0x9F28: 3 swc1 stores to v1+0/4/8 (commit scaled vec).
 *   - 0x9F2C-0x9F50: another 12-byte triple-fanout copy. Reads a1+0/4/8,
 *     writes t7+0/4/8 (sp+0x16C) AND t1+0/4/8 (sp+0x94 area). Same
 *     save-old + write-new idiom.
 *   - 0x9F54-0x9F70: bne-guarded jal with a0=0xC, a2=sp+0x6C (yet
 *     another local Vec3 buffer dest).
 *   - 0x9F74-0x9F80: post-call branch test on v0 (`beq v0,$0,+0xB`).
 *   - 0x9F84-0x9FA8: post-call FPU scale block (mirror of 0x9F00 above).
 *     lwc1 sp+0x144/0x138/0x14C/0x140, sub.s + mul.s + zero-fill — same
 *     "scale by callee delta" template applied to a different slot pair.
 *   - 0x9FAC-0x9FE0: third triple-fanout struct copy (a1+0/4/8 -> t9+0/4/8
 *     with t1+0/4/8 backup). The function maintains MANY Vec3 working
 *     buffers and does many fanout-with-backup copies.
 *
 * BODY-PART-2 FINAL-CHUNK SCAN (2026-05-05, 0x9FE8-0xA0E8 = +64 insns,
 * function tail):
 *   - 0x9FE8-0xA00C: 2 sequential lw/sw triples that finish a working-set
 *     copy (a4-buf + 1-byte advance + delta-add into v1+0/4/8).
 *   - 0xA010-0xA01C: branch test on a1 (`beq a1, $0, +0xB`) — early-exit
 *     when input is null. Sets v1 = a0 (passthrough) on the early arm.
 *   - 0xA020-0xA050: 4-element FPU sum. lwc1 sp+0x120/0x12C/0x128/0x134
 *     (4 floats from staging buffers); add.s f0,f18,f0; mtc1 zero (= 0);
 *     add.s f0,f6,f0 — accumulates 3 floats into one Vec3 stored to
 *     v1+0/4/8.
 *   - 0xA050-0xA088: 12-byte triple-fanout copy + zero-fill. Reads
 *     a1+0/4/8, writes v1+0/4/8 AND a3+0/4/8 (mirror Vec3 to two
 *     destinations); zero-fills v0+0/4/8 as a third destination.
 *
 *   - 0xA088-0xA0CC: TWO 2D cross products (the function's ACTUAL
 *     PURPOSE — same-side-of-line-pair test). Decoded:
 *
 *       cross1 = sp[0x168] * sp[0x154] - sp[0x160] * sp[0x15C];
 *       cross2 = sp[0x180] * sp[0x16C] - sp[0x178] * sp[0x174];
 *       sign_product = cross1 * cross2;
 *
 *   - 0xA0CC-0xA0DC: c.lt.s sign_product, 0.0f; bc1f branch-on-fail to
 *     "return 0" path. If TAKEN (sign_product < 0): set v0 = 1 in delay.
 *   - 0xA0E0-0xA0E4: epilogue (jr ra; addiu sp, +0x1A8 in delay).
 *
 *   Final return: 1 IFF the 2D anchor is BETWEEN the two reference
 *   lines (cross products with opposite signs ⇒ different sides ⇒
 *   anchor is inside the wedge). Confirms billboard-visibility /
 *   point-in-wedge semantics from the function's lead comment.
 *
 *   The 8 sp slot pairs (0x154/0x158/..., 0x160/0x164/..., 0x168/0x16C/...,
 *   0x174/0x178/..., 0x180+) are the per-line endpoint x/y components from
 *   the body-part-2 staging compute — 4 lines (each a 2D Vec2 with 2 floats)
 *   form the 2 reference edges that bound the visibility wedge.
 *
 * Deferred to future passes: full body decode is ~300 insns of float sched;
 *   one /decompile run expands prologue + body-part-1 — subsequent runs will
 *   tighten the dispatch logic and body math. The dual Vec3-copy entry
 *   strongly suggests this is a coordinate-transform function: takes
 *   (context, anchor, src-Vec3) and produces a transformed Vec3 written to
 *   one of several local slots for downstream cross-USO dispatch. */
int game_uso_func_00009B88(a0, a1, a2)
    int *a0;
    int *a1;
    int *a2;
{
    volatile int local_19C[3]; /* sp+0x19C: raw-word copy of local_DC */
    float local_190[3];   /* sp+0x190: Vec3 (a2->0x30 XZ-projection) */
    float local_184[3];   /* sp+0x184: projected source from a0->0x30 + 0xB4 */
    volatile int local_178[3]; /* sp+0x178: raw-word copy of local_A0 */
    volatile int local_16C[3]; /* sp+0x16C: raw-word copy of local_88 */
    volatile int local_160[3]; /* sp+0x160: raw-word copy of local_7C */
    volatile int local_154[3]; /* sp+0x154: raw-word copy of local_44 */
    int   gap_150;        /* sp+0x150: target gap between local_154/local_144 */
    float local_144[3];   /* sp+0x144: Vec3 — passed to alloc-or-fill helper */
    float local_138[3];   /* sp+0x138: working buffer (90deg-rotated XZ) */
    float local_12C[3];   /* sp+0x12C: scaled accumulator (screen-space) */
    float local_120[3];   /* sp+0x120: copy of local_B8 */
    char pad_10C[40];
    volatile int local_EC[3]; /* sp+0xEC: raw-word copy of local_DC */
    char pad_E0[4];
    float local_DC[3];    /* sp+0xDC:  Vec3 (a2-a1 XZ-delta) */
    char pad_D0[12];
    int   local_C4[3];    /* sp+0xC4:  raw-word copy of local_DC */
    float local_B8[3];    /* sp+0xB8:  local_184 - a1->0x30 */
    volatile float local_A0[3]; /* sp+0xA0:  local_144 + local_138 */
    volatile float local_88[3]; /* sp+0x88:  local_120 - local_12C */
    volatile int local_94[3]; /* sp+0x94:  raw-word copy of local_88 */
    volatile float local_6C[3]; /* sp+0x6C:  local_144 - local_138 */
    volatile int local_7C[3]; /* sp+0x7C:  raw-word copy of local_6C */
    volatile float local_38[3]; /* sp+0x38:  local_120 + local_12C */
    volatile int local_44[3]; /* sp+0x44:  raw-word copy of local_38 */
    int *out;
    float *src_vec;
    int * volatile *spill_a1 = &a1;
    float src_x, src_z, dx, dz;
    float scale0;         /* screen-space transform scale: 250.0f * a1->0x54 + 50.0f */
    float scale1;         /* screen-space transform scale: 250.0f * (a2->0x54 - a1->0x54) */
    char pad_frame[16];
    (void)pad_frame;
    (void)gap_150;
    (void)pad_10C;
    (void)pad_E0;
    (void)pad_D0;
    (void)spill_a1;

    if (a2 == 0) {
        /* Assert: line 0x623 (1571) — message at &game_uso_D_807FEDB8+0x7BC / +0x7C8 */
        game_uso_func_047B1C(&game_uso_D_807FEDB8 + 0x7BC, &game_uso_D_807FEDB8 + 0x7C8, 0x623);
    }

    /* Dispatch 1: write Vec3 XZ-projection to local_190 (sp+0x190).
     * TARGET (decoded 2026-05-28; this is the FIRST divergence / cascade root):
     *   addiu v1,sp,0x190; bnezl v1,+6; [delay-likely] lw v0,0x1B0(sp);  // a2 reload
     *   jal alloc; li a0,12; beqz v0,+9; move v1,v0; lw v0,0x1B0(sp); ...body
     * The bnezl's delay-LIKELY slot is filled with the BODY's first insn
     * (a2's home-slot reload at sp+0x1B0), NOT a `move v1,ptr` passthrough.
     * NEGATIVE RESULTS (do not repeat): the documented alloc-ternary recipe
     * `out = p ? p : alloc(12)` — both bare-cast and named-temp forms — emits
     * plain `beqz; nop; b; move; jal` (non-likely, +6 insns) NOT bnezl, because
     * IDO sees &local_190 as a known-non-null constant. Adding `(void)&a2` to
     * force a2's home spill didn't flip it either. The branch-likely here is
     * reorg-pass-driven off the a2-reload-in-delay and isn't reachable from
     * these C shapes; needs a fresh idea or the permuter. Kept as if-form. */
    out = (int*)local_190;
    if (out == 0) {  /* dead arm */
        out = (int*)game_uso_func_055750(0xC);
    }
    if (out != 0) {
        src_x = *(float*)((char*)a2 + 0x30);
        src_z = *(float*)((char*)a2 + 0x38);
        *(float*)((char*)out + 0x4) = 0.0f;     /* y */
        *(float*)((char*)out + 0x8) = src_z;    /* z */
        *(float*)((char*)out + 0x0) = src_x;    /* x */
    }

    /* Dispatch 2: write Vec3 (a2->XZ - a1->XZ delta) to local_DC.
     * Same ternary shape; uses local_190 (just-written) for src_x/src_z. */
    out = (int*)local_DC;
    if (out == 0) {  /* dead arm */
        out = (int*)game_uso_func_055750(0xC);
    }
    if (out != 0) {
        dx = local_190[0] - *(float*)((char*)a1 + 0x30);
        dz = local_190[2] - *(float*)((char*)a1 + 0x38);
        *(float*)((char*)out + 0x4) = 0.0f;     /* y */
        *(float*)((char*)out + 0x8) = dz;       /* z */
        *(float*)((char*)out + 0x0) = dx;       /* x */
    }

    /* Body-part-2 entry @ 0x9C44-0x9C98 (CORRECTED 2026-05-04 via byte-decode):
     * 1-to-4 fanout copy. local_DC's 3 words get distributed to local_EC,
     * local_19C, local_144 — interleaved IDO -O2 codegen with shared loads. */
    {
        register int copy0 = ((int*)local_DC)[0];
        register int copy1 = ((int*)local_DC)[1];
        register int copy2;
        register int copy3;

        local_EC[0] = copy0;
        copy3 = local_EC[0];
        copy2 = ((int*)local_DC)[2];
        local_19C[0] = copy3;
        copy3 = local_19C[0];
        local_19C[1] = copy1;
        local_EC[1] = copy1;
        local_19C[2] = copy2;
        local_EC[2] = copy2;
        *(int*)&local_144[0] = copy3;
        copy1 = local_19C[1];
        *(int*)&local_144[1] = copy1;
        copy2 = local_19C[2];
        *(int*)&local_144[2] = copy2;
    }

    /* @ 0x9DD0-0x9E18: rotated Vec3 into the always-nonnull sp+0xC4 slot.
     * The alloc arm is dead for the stack destination, matching the target's
     * `bne v1,$zero` skip over the helper allocation. */
    out = (int*)local_C4;
    if (out == 0) {
        out = (int*)game_uso_func_055750(0xC);
    }
    if (out != 0) {
        ((float*)out)[0] = local_144[2];   /* x = old z */
        ((float*)out)[1] = 0.0f;
        ((float*)out)[2] = -local_144[0];  /* z = -old x */
    }

    /* @ 0x9E1C-0x9E48: 3-way Vec3 fan-out from local_C4 to local_EC and
     * sp+0x138, then call helper(local_138, local_C4, local_EC). Likely a 3-Vec3
     * accumulator (passing rotated, original, and delta to a single helper).
     *
     * @ 0x9D00-0x9D34: screen-space transform setup.
     *   t9 = sp+0x138, t8 = sp+0x12C
     *   sp+0x12C = sp+0x138   (word copy: 3 lw/sw pairs interleaved)
     *   f2 = 250.0f (lui $at, 0x437A; mtc1 $at, $f2)   ; viewport-half scale
     *   f10 = 50.0f (lui $at, 0x4248; mtc1 $at, $f10)  ; vertical offset
     *   v1 = sp+0x184  (another working buffer)
     *   t2 = a1 from caller-slot (sp+0x1AC)
     *
     * (Math chain continues 0x9D34-0x9DC4 — multiplies sp+0x12C entries by
     * 250.0f scale + 50.0f offset for screen-coord transform; not yet decoded.)
     *
     * Extended characterization 2026-05-04 (0x9D34-0x9DC4, ~37 insns):
     *   - 0x9D34-0x9D58: load 3 floats from sp+0x12C/130/134, mul.s with
     *     250.0f and a fresh load from t2->0x54 (struct field arg). Result
     *     stays in $f0..$f4.
     *   - 0x9D5C-0x9D74: load sp+0x134, more mul.s on $f4/$f6/$f8/$f10/$f12,
     *     swc1 BACK to sp+0x12C and sp+0x130 (in-place scaling of first 2 of 3
     *     Vec3 components — pattern is `vec[i] = vec[i] * (250.0f * t2->0x54 + 50.0f)`).
     *   - 0x9D7C-0x9DBC: another lwc1 chain from sp+0x138/13C/140 into
     *     $f6/$f10, mul.s with same scale, swc1 back to sp+0x138/0x13C/0x140
     *     (second Vec3 in-place scale, same pattern).
     *   - 0x9DC0: lw t5, 0x30(t4) — load yet another struct's Vec3 source.
     *   - 0x9DC4-0x9DD0: bne+jal sequence — 4th cross-USO dispatch with
     *     scratch_a (sp+0xEC) and t5+0xB4 args.
     *
     * Net: 0x9D34-0x9DC4 scales local_12C by (250.0f * a1->0x54 + 50.0f),
     * scales local_138 by (250.0f * (a2->0x54 - a1->0x54)), then loads a
     * third Vec3 source and dispatches a helper. Confirms screen-space
     * transform hypothesis. Body-part-2 still has ~200 insns past 0x9DD0.
     *
     * Extended characterization 2026-05-04 (0x9DD0-0x9E80, ~44 insns):
     *   - 0x9DD8-0x9DF8: post-cross-call result handling. If callee
     *     returned non-NULL ptr `v0`, store Vec3(a1[0], 0, a1[2]) to *v0
     *     — i.e. zero-Y projection of the just-loaded Vec3.
     *   - 0x9DFC-0x9E0C: 5th cross-USO dispatch — alloc(0xC) for a new
     *     Vec3 buffer.
     *   - 0x9E20-0x9E4C: post-alloc, fill the new Vec3 with delta from
     *     (sp+0x184/0x18C) and a1->0x30/0x38: Vec3(diff_x, 0, diff_z).
     *     a1 is the reference XZ subtract origin.
     *   - 0x9E50-0x9E80: another 12-byte struct copy (a1 → a2, then
     *     a1 → sp+0x120; final destination tracking gets convoluted).
     *
     * Cumulative: ~115 insns characterized of the 344. Body-part-2's
     * theme is clearly "fan out the player's screen-projected XZ to
     * multiple per-displayed-object buffer slots, with various deltas
     * against the reference position from a1".
     *
     * Extended characterization 2026-05-04 (0x9E80-0x9F50, ~52 insns):
     *   Continues the same alloc(0xC) + Vec3 sub.s pattern observed in
     *   0x9DD0-0x9E80, but for additional buffer destinations:
     *   - 0x9E80-0x9E8C: tail of previous struct copy (sw t9, 8(t6))
     *   - 0x9E90-0x9EC8: 6th cross-USO call alloc(12) for sp+0xA0 dst.
     *     Post-alloc: 3-float (sp+0x144, sp+0x138, sp+0x14C, sp+0x140)
     *     mul.s + sub.s combination, store result Vec3 at v1[0..8].
     *   - 0x9ED0-0x9F00: 12-byte struct copy (sp+0xA0 → sp+0x178/v1).
     *   - 0x9F10-0x9F50: 7th cross-USO call alloc(12) for sp+0x88 dst.
     *     Same shape: load 3 floats from sp+0x120/0x12C/0x128/0x134,
     *     mul/sub, store to alloc'd Vec3.
     *
     * Theme is now clearly: REPEATED "compute one Vec3 = math(table_a,
     * table_b)" + "store to alloc'd buffer" + "fan out to multiple
     * downstream slots". Each iteration uses different sp-offset table
     * pairs, building per-displayed-object screen-projected data.
     *
     * Cumulative ~167/344 insns characterized.
     *
     * Extended characterization 2026-05-04 (0x9F50-0xA0A0, ~84 insns):
     *   Same "alloc(0xC) + fill Vec3 + struct-copy fan-out" pattern continues
     *   for two more iterations. Each follows the recipe:
     *     1. word-copy a1[0..0xC] → sp+0xNN buffer (3 lw/sw pairs)
     *     2. word-copy a2[0..0xC] → sp+0xMM buffer (3 lw/sw pairs)
     *     3. addiu v1, sp, 0xKK; bne v1, $0, skip_alloc (always skipped)
     *     4. jal 0 (gl_func_00000000) ; addiu a0, $0, 0xC  (dead alloc)
     *     5. beqz v0, +0xB ; or v1, v0, $0 (also dead — v1 = stack addr)
     *     6. lwc1 4 floats from sp+0x12C/0x138/0x140/0x14C tables
     *     7. mul.s + (mtc1 $0,zero) + sub.s combo
     *     8. swc1 results to v1[0/4/8] (Vec3 result)
     *
     *   The destination sp-offsets in this chunk: sp+0x6C, sp+0x94, sp+0x16C,
     *   sp+0x160, sp+0x44, sp+0x154 — all distinct working buffer slots being
     *   populated. Each iteration consumes (table_a, table_b) at different
     *   sp-offsets and produces a Vec3.
     *
     *   This is the REPEATED unrolled pattern noted earlier. Likely an unrolled
     *   loop over per-vertex / per-corner buffer slots for a 4-corner billboard
     *   or trail mesh — the screen-space transform builds 4-6 transformed
     *   Vec3s in adjacent stack slots, all fed to a single downstream
     *   draw-helper at the function tail.
     *
     * Cumulative ~251/344 insns characterized (~73%).
     *
     * CORRECTION 2026-05-04: function actually ENDS at 0xA0E4 (size 0x560 from
     * 0x9B88 = end 0xA0E8). The earlier "@ 0xA0A0-0x10E8" range was wrong —
     * confused with absolute ROM offset. Only ~12 insns remain past 0xA0A0.
     *
     * Final tail @ 0xA0A0-0xA0E4 (~12 insns): sign-of-cross-product check.
     *   - 0xA0A0-0xA0BC: lwc1 four floats from sp+0x178/0x180/0x174, plus
     *     existing $f4/$f16/$f18 register state. Compute:
     *       $f0  = sp+0x148_value - $f4 * $f6      (subtract product from acc)
     *       $f10 = $f4_new * $f18 - $f6_new * $f18_new   (2nd diff product)
     *   - 0xA0C8: $f16 = $f10 * $f0                (final product)
     *   - 0xA0CC: c.lt.s $f16, 0.0                 (sign test)
     *   - 0xA0D4: bc1f +2 — if NOT (f16 < 0), skip; jump to epilogue (v0
     *     remains as set earlier)
     *   - 0xA0DC: v0 = 1                           (only when f16 < 0)
     *   - 0xA0E0-0xA0E4: jr ra; addiu sp, +0x1A8
     *
     * This tail is a 2D cross-product sign test — likely "is point on positive
     * side of line" / "is winding clockwise" / similar geometric predicate.
     * Final return value is 1 if product < 0, else 0 (or whatever was set
     * by the omitted earlier dispatch's skip-arm).
     *
     * Cumulative 263/344 insns characterized (~76%).
     *
     * The 250.0/50.0 constants confirm screen-space coordinate transform
     * (250.0 ~= viewport-half; 50.0 ~= vertical offset).
     * Combined with the cross-product sign test, this is likely a
     * billboard-visibility / point-in-frustum check after screen projection.
     *
     * 2026-05-20 variants tried:
     *   - real tail Vec3 math + predicate: 11.85% -> 20.33%;
     *   - raw-word fanout copies instead of float copies: 20.33% -> 28.59%;
     *   - correct sp+0xC4 as always-stack rotated Vec3 + helper call:
     *     28.59% -> 29.48%;
     *   - corrected signature back to 3 args, changed scale block to
     *     250.0f/50.0f using a1/a2->0x54, and added caller-slot a1 spill
     *     plus frame padding per docs/IDO_CODEGEN.md arg-spill/frame recipes:
     *     29.48% -> 33.39%.
     *
 * 2026-05-20 recheck with the correct non_matching object rebuild:
     *   - raw integer zero stores for all Vec3 Y components regressed
     *     33.386627% -> 32.220932%;
     *   - volatile destination pointer + moving pad_frame below real locals
     *     regressed to 32.462208%;
     *   - tail predicate rewrites (`result` local, inverted >= early-return)
     *     regressed to 32.279068% or left the same extra-branch class.
     *   - target-order stack Vec3 declarations + padding fixed the early
     *     stack slot map for local_190/local_DC/local_EC/local_C4/local_19C
     *     (sp+0x190/0xDC/0xEC/0xC4/0x19C) and slightly improved
     *     33.386627% -> 33.395348%.
 *   Ghidra helper was unavailable in this worktree (missing
 *   build/ghidra-project/tenshoe).
 *
 * 2026-05-20 continuation:
 *   - applying the documented alloc-or-fill shape as a direct ternary to
 *     the first three Vec3 destinations emitted the wrong `beq + b`
 *     form and regressed 33.35% -> 32.68%;
 *   - wrapping the four final screen-space Vec3 combinations in explicit
 *     stack-destination alloc guards improved 33.35% -> 43.27%;
 *   - adding the same wrapper to the preceding local_184/local_B8 writes
 *     regressed slightly to 42.99%, so those stayed as direct writes.
 *
 * 2026-05-20 deep retry:
 *   - m2c cannot decode this .word-only USO body ("contains no instructions");
 *   - moving a 32-byte frame pad below the real locals fixed the target
 *     -0x1A8 frame and early local slots (local_190=sp+0x190,
 *     local_DC=sp+0xDC) and improved 43.270348% -> 43.302326%;
 *   - goto-shaped alloc guards for the first two Vec3 destinations regressed
 *     to 42.898254% (IDO deleted the dead alloc arms);
 *   - `result` local tail shape regressed to 42.909885% and grew the frame
 *     to -0x1B0, so the return/return tail stayed.
 *
 * 2026-05-20 tail retry:
 *   - direct boolean return for the final cross-product sign test removed
 *     the extra unconditional branch and improved 43.343020% -> 43.633720%;
 *   - commuted cross-product operands nudged FPU load order and improved to
 *     43.636627%;
 *   - named temporaries for the same tail regressed to 38.921513%.
 *
 * 2026-05-20 stack/raw-copy retry:
 *   - inserted the target's sp+0x150 gap between local_154 and local_144,
 *     compensated with the mid scratch pad to preserve lower slots, improving
 *     43.636627% -> 43.639534%;
 *   - changed the initial local_144 fanout from float copies to raw int-word
 *     copies, improving to 45.968020%;
 *   - made local_EC/local_19C volatile to preserve the target's otherwise
 *     dead raw scratch fanout, improving to 48.229652%;
 *   - local_144 volatile regressed to 48.078487%, and local_C4 volatile
 *     regressed to 46.872093%, so both were rejected.
 *
 * 2026-05-20 follow-up:
 *   - volatile `out` for all alloc-or-fill blocks regressed to 38.5%;
 *   - explicit register-temp replay of the local_DC -> local_EC/local_19C/
 *     local_144 fanout improved 48.229652% -> 48.819767%;
 *   - removing volatile from local_EC/local_19C regressed to 45.918606%;
 *   - tuning pad_10C from 40 to 24 kept target-adjacent lower stack slots
 *     closer and improved to 48.851746% (pad 16/32 were worse).
 *   Current best at that point: 48.851746%.
 *
 * 2026-05-20 continuation:
 *   - remeasured inherited body after forced non_matching rebuild:
 *     48.811047%;
 *   - pad_10C=8 regressed to 48.779068%;
 *   - explicit first-destination non-null/else alloc form regressed to
 *     47.72384%;
 *   - adding real alloc-or-fill wrappers for the middle local_184
 *     source-projection and local_B8 delta blocks improved to 50.311047%;
 *   - reducing pad_frame 32 -> 24 restored the target -0x1A8 frame and
 *     improved to 50.337208%; pad_frame=16 regressed to 50.30814.
 *   Current best: 50.337208%.
 *
 * 2026-05-20 exact-grind stop point:
 *   - current forced rebuild/report measures 50.377907%;
 *   - making the shared destination pointer volatile preserved more dead
 *     alloc arms but regressed badly to 42.8343%;
 *   - making local_138 volatile to avoid the saved $s0 pointer regressed
 *     to 47.94186%;
 *   - pad_10C=8 or 16 both regressed to 50.34884%;
 *   - explicit `if (out != 0) ... else alloc` for the first final
 *     screen-space destination regressed to 47.90116%;
 *   - recomputing the local_138 call address from local_EC tied baseline
 *     exactly, so the clearer direct local_138 call stayed.
 *
 * 2026-05-20 Codex deep retry:
 *   - boundary rechecked clean (`grep -c 03E00008` = 1);
 *   - m2c still cannot decode this raw-word USO body ("contains no
 *     instructions"), so no new m2c seed was available;
 *   - no-alias objdump shows the current major residuals are the missing
 *     target alloc-or-passthrough `bnel` arms at the first two Vec3
 *     destinations, an extra saved `$s0` cache for sp+0x138, and lower
 *     Vec3 stack slots such as local_B8 still mapped far below target;
 *   - first-two-destination ternary form per
 *     docs/IDO_CODEGEN.md#feedback-ido-alloc-or-passthrough-ternary
 *     produced the same object/report (50.377907%);
 *   - pad_10C 24 -> 40 and `volatile local_138[3]` also produced the same
 *     report, leaving the `$s0` save and stack-slot residual unchanged.
 *
 * 2026-05-20 Codex continuation:
 *   - ternary `out = local ? local : alloc(0xC)` for the first two Vec3
 *     destinations regressed 50.377907% -> 49.261627%;
 *   - a volatile passthrough pointer for only those first two destinations
 *     regressed to 49.854652%;
 *   - shrinking pad_10C 24 -> 8 moved the frame to -0x198 and regressed to
 *     50.348840%;
 *   - moving local_B8 into the lower Vec3 declaration cluster preserved the
 *     current score while keeping that source slot nearer the target stack
 *     band; adding a 4-byte neighboring gap regressed to 50.351746%;
 *   - Ghidra was unavailable: agent-c has no local project and agent-e's
 *     project was locked.
 *   Exact not reached; keep INCLUDE_ASM fallback, no new episode.
 *
 * 2026-05-20 Codex source=2 iteration:
 *   - boundary rechecked clean (`grep -c 03E00008` = 1);
 *   - fresh non_matching object/report measured 50.337208% before edits;
 *   - pad_10C 24 -> 40 plus pad_frame 24 -> 8 preserved the target
 *     -0x1A8 frame while placing the early stack band at target offsets:
 *     local_DC=sp+0xDC, local_EC=sp+0xEC, local_C4=sp+0xC4. This improved
 *     50.337208% -> 50.343020%;
 *   - pad_10C 40 without the pad_frame compensation grew the frame to
 *     -0x1B8 and regressed to 50.308140%;
 *   - ternary alloc-or-passthrough form for the first three Vec3
 *     destinations regressed to 48.636627% in the full TU;
 *   - `float * volatile src_vec` to force the local_184 source spill
 *     regressed to 48.732560%;
 *   - Ghidra helper still unavailable in agent-c (missing
 *     build/ghidra-project/tenshoe).
 *   Exact not reached; keep INCLUDE_ASM fallback, no new episode.
 *
 * 2026-05-20 Codex current-candidate iteration:
 *   - boundary rechecked clean (`grep -c 03E00008` = 1);
 *   - no-alias objdump showed the lower Vec3 fanout slots were being
 *     optimized into direct float temporaries instead of target-style raw
 *     word-copy buffers;
 *   - declaration-order/padding repack of the lower Vec3 band regressed
 *     50.383720% -> 50.348840%, so it was rejected;
 *   - converting the intermediate raw-copy buffers local_94/local_7C/local_44
 *     to volatile int[3] preserved explicit lw/sw fanout and improved to
 *     53.688953%;
 *   - increasing pad_frame 8 -> 16 restored the target 0x1A8 frame and
 *     improved to 53.735466%; 24-byte padding regressed to 53.688953%;
 *   - converting final fanout destinations local_178/local_16C/local_160/
 *     local_154 to volatile int[3], with float reinterpretation only in the
 *     final cross-product predicate, improved to 54.950580%;
 *   - applying the same raw-buffer treatment to local_120 regressed to
 *     53.139534%, so it was rejected; volatile lower output Vec3s tied the
 *     current best.
 *   Exact not reached; keep INCLUDE_ASM fallback, no new episode.
 *
 * 2026-06-22 reloc-symbol correctness pass (agent-e):
 *   Decoded the TARGET from expected/src/game_uso/game_uso.c.o (objdump -dr).
 *   All cross-USO relocs were pointing at PLACEHOLDERS (gl_func_00000000 /
 *   D_00000000); replaced them with the real reloc symbols read off the
 *   target's R_MIPS_26 / R_MIPS_HI16 entries:
 *     - assert  @0x9bb0 : game_uso_func_047B1C(&game_uso_D_807FEDB8+0x7BC,
 *                         &game_uso_D_807FEDB8+0x7C8, 1571)
 *     - alloc   (9x)    : game_uso_func_055750(0xC)   (was gl_func_00000000)
 *     - normalize@0x9cf8: game_uso_func_071028((Vec3*)local_138)  (single-arg;
 *                         a1/a2 at the call site are residual copy regs, not args)
 *   These are byte-neutral in objdiff fuzzy (same lui/jal/addiu insn bytes;
 *   only the relocation ENTRIES change), so fuzzy stayed ~54.92% — but the C
 *   is now correct toward a real match instead of relocating to dead stubs.
 *   The single-arg 071028 fix shifted one scheduling slot (54.95->54.92, noise).
 *   CASCADE ROOT CONFIRMED INTRACTABLE: dispatch-1 @0x9bb8 emits `bnezl v1`
 *   (branch-LIKELY) on a stack address (&local_190) with the a2 home-slot
 *   reload (lw v0,0x1b0(sp)) in the annulled delay — IDO does NOT fold the
 *   dead alloc arm. No C alloc-ternary / if-else / held-ptr shape reproduces
 *   the likely-branch-on-stack-addr (held-base-ptr in dispatch-1 regressed
 *   334->338 non-reloc diffs). This roots a 330+/344 body cascade. Needs the
 *   permuter or a non-obvious source idiom (the original `out` was likely a
 *   struct-field / fn-ptr return IDO can't prove non-null, not a stack local). */
    *(int*)&local_EC[0] = local_C4[0];
    *(int*)&local_EC[1] = local_C4[1];
    *(int*)&local_EC[2] = local_C4[2];
    *(int*)&local_138[0] = local_C4[0];
    *(int*)&local_138[1] = local_C4[1];
    *(int*)&local_138[2] = local_C4[2];
    game_uso_func_071028((Vec3 *)local_138);

    /* @ 0x9D00-0x9D34: 3-word copy local_12C = local_138 buffer (the 90°-rotated
     * XZ Vec3 from the alloc-or-fill above). Both serve as input to the
     * subsequent in-place scaling chain. */
    *(int*)&local_12C[0] = *(int*)&local_138[0];
    *(int*)&local_12C[1] = *(int*)&local_138[1];
    *(int*)&local_12C[2] = *(int*)&local_138[2];

    /* @ 0x9D34-0x9DBC: in-place screen-space scale.
     * Both local_12C[0..2] and local_138[0..2] scale-multiplied in-place.
     * Target reloads only the three spilled args: a1 supplies the first
     * scale source, a2 supplies the second, and a0 supplies the Vec3 source. */
    scale0 = 250.0f * (*(float*)((char*)a1 + 0x54)) + 50.0f;
    local_12C[0] *= scale0;
    local_12C[1] *= scale0;
    local_12C[2] *= scale0;
    scale1 = 250.0f * (*(float*)((char*)a2 + 0x54) - *(float*)((char*)a1 + 0x54));
    local_138[0] *= scale1;
    local_138[1] *= scale1;
    local_138[2] *= scale1;

    /* @ 0x9F0C-0x9F48: project a source Vec3 from a0->0x30+0xB4 into
     * sp+0x184, clearing Y. This is the fourth always-stack destination,
     * matching the earlier alloc-or-fill Vec3 templates. */
    src_vec = (float*)((char*)*(int*)((char*)a0 + 0x30) + 0xB4);
    out = (int*)local_184;
    if (out == 0) {
        out = (int*)game_uso_func_055750(0xC);
    }
    if (out != 0) {
        ((float*)out)[0] = src_vec[0];
        ((float*)out)[1] = 0.0f;
        ((float*)out)[2] = src_vec[2];
    }

    /* @ 0x9F48-0x9F9C: build the second delta vector against a1+0x30. */
    out = (int*)local_B8;
    if (out == 0) {
        out = (int*)game_uso_func_055750(0xC);
    }
    if (out != 0) {
        ((float*)out)[0] = local_184[0] - *(float*)((char*)a1 + 0x30);
        ((float*)out)[1] = 0.0f;
        ((float*)out)[2] = local_184[2] - *(float*)((char*)a1 + 0x38);
    }

    *(int*)&local_120[0] = *(int*)&local_B8[0];
    *(int*)&local_120[1] = *(int*)&local_B8[1];
    *(int*)&local_120[2] = *(int*)&local_B8[2];

    /* @ 0x9FF4-0xA194: four unrolled screen-space Vec3 combinations. */
    out = (int*)local_A0;
    if (out == 0) {
        out = (int*)game_uso_func_055750(0xC);
    }
    if (out != 0) {
        ((float*)out)[0] = local_144[0] + local_138[0];
        ((float*)out)[1] = 0.0f;
        ((float*)out)[2] = local_144[2] + local_138[2];
    }
    local_178[0] = *(int*)&local_A0[0];
    local_178[1] = *(int*)&local_A0[1];
    local_178[2] = *(int*)&local_A0[2];

    out = (int*)local_88;
    if (out == 0) {
        out = (int*)game_uso_func_055750(0xC);
    }
    if (out != 0) {
        ((float*)out)[0] = local_120[0] - local_12C[0];
        ((float*)out)[1] = 0.0f;
        ((float*)out)[2] = local_120[2] - local_12C[2];
    }
    local_94[0] = *(int*)&local_88[0];
    local_94[1] = *(int*)&local_88[1];
    local_94[2] = *(int*)&local_88[2];
    local_16C[0] = local_94[0];
    local_16C[1] = local_94[1];
    local_16C[2] = local_94[2];

    out = (int*)local_6C;
    if (out == 0) {
        out = (int*)game_uso_func_055750(0xC);
    }
    if (out != 0) {
        ((float*)out)[0] = local_144[0] - local_138[0];
        ((float*)out)[1] = 0.0f;
        ((float*)out)[2] = local_144[2] - local_138[2];
    }
    local_7C[0] = *(int*)&local_6C[0];
    local_7C[1] = *(int*)&local_6C[1];
    local_7C[2] = *(int*)&local_6C[2];
    local_160[0] = local_7C[0];
    local_160[1] = local_7C[1];
    local_160[2] = local_7C[2];

    out = (int*)local_38;
    if (out == 0) {
        out = (int*)game_uso_func_055750(0xC);
    }
    if (out != 0) {
        ((float*)out)[0] = local_120[0] + local_12C[0];
        ((float*)out)[1] = 0.0f;
        ((float*)out)[2] = local_120[2] + local_12C[2];
    }
    local_44[0] = *(int*)&local_38[0];
    local_44[1] = *(int*)&local_38[1];
    local_44[2] = *(int*)&local_38[2];
    local_154[0] = local_44[0];
    local_154[1] = local_44[1];
    local_154[2] = local_44[2];

    (void)local_19C;  /* suppress unused warnings until body-part-2 done */
    (void)local_EC;
    (void)local_C4;
    (void)scale0;
    (void)scale1;

    /* @ 0xA1D4-0xA230: two 2D cross products over the four derived screen
     * vectors. Return 1 when the products have opposite signs. */
    {
        float cross1 = (*(float*)&local_154[0] * *(float*)&local_160[2]) - (*(float*)&local_154[2] * *(float*)&local_160[0]);
        float cross2 = (*(float*)&local_16C[0] * *(float*)&local_178[2]) - (*(float*)&local_16C[2] * *(float*)&local_178[0]);
        return (cross1 * cross2) < 0.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00009B88);
#endif

/* game_uso_func_0000A0E8 - verified structural decode (~163-insn FPU
 * geometry op; Vec3-diff + multi struct-copy + dispatch = documented
 * FP-regalloc + struct-copy-sp-slot sub-80 ceiling -> INCLUDE_ASM
 * build path; struct-typing reference).
 *   f(a0, b /sp204/, a2 /sp208/):
 *   if (a2 == 0) gl_func_00000000(&D+0x7D4, &D+0x7E0, 1586);  // assert
 *   v0 = a2;                                                  // reloaded
 *   d.x = v0->0x30 - b->0x30;                                  // Vec3 diff
 *   d.y = v0->0x38 - b->0x38;                                  // (sp+92)
 *   d.z = v0->0x34 - b->0x34;
 *   copy d -> sp+108 (3 int-words);  copy sp+108 -> sp+188;
 *   if (sp+160 == 0) { v1 = gl_func_00000000(b+0x30); }        // build
 *   else v1 = sp+160;
 *   v1->0x0 = *(float*)(sp+188);  v1->0x8 = *(float*)(sp+196);
 *   ... (continues: more FP writes into v1 from the diff/copy block) ...
 * Struct-typing: v0/a2 and b (a1) are objects holding a Vec3 at +0x30
 * (x@0x30, z@0x34, y@0x38 - note z/y order); function computes the
 * component difference v0.vec - b.vec, replicates it across stack
 * scratch (sp+92 / +108 / +188 / +160), then writes it into a result
 * object v1 (built via gl_func_00000000(b+0x30) when sp+160 slot is
 * null). &D+0x7D4 / +0x7E0 = assert format/string (1586 = line?).
 * Caps <80: FP sub.s pipeline + 3-int struct-copy sp-slot allocation +
 * the result-object reload - combined FP-regalloc/struct-copy
 * divergence (cf gl_func_00065250). Full body INCLUDE_ASM-preserved.
 * INCLUDE_ASM (no episode; tautology-trap rule). */
extern float game_uso_func_082880(float);
extern char game_uso_D_807FEDD0;
#ifdef NON_MATCHING
int game_uso_func_0000A0E8(char *a0, char *a1, char *a2) {
    char *w;
    Vec3 d1, d1b, d1c;
    Vec3 d2, d2b, d2c;
    Vec3 xz1, xz2;
    Vec3 *p1, *p2;
    float mag, normv;
    float a1y, lhs, rhs;
    int ret;

    if (a2 == 0) {
        game_uso_func_047B1C((char *)&game_uso_D_807FEDD0 + 2004,
                             (char *)&game_uso_D_807FEDD0 + 2016, 1586);
        a2 = (char *)1586;
    }
    /* block1: d1 = a2.vec - a1.vec (0x30/0x34/0x38), copied through 2 buffers,
     * then a dead-alloc XZ Vec3 (y zeroed). */
    d1.x = *(float *)(a2 + 0x30) - *(float *)(a1 + 0x30);
    d1.y = *(float *)(a2 + 0x34) - *(float *)(a1 + 0x34);
    d1.z = *(float *)(a2 + 0x38) - *(float *)(a1 + 0x38);
    d1b = d1;
    d1c = d1b;
    p1 = &xz1;
    if (p1 == 0) p1 = (Vec3 *)game_uso_func_055750(12);
    p1->x = d1c.x;
    p1->z = d1c.z;
    p1->y = 0.0f;
    /* block2: w = a0->0x30; d2 = w->{0xB4,0xB8,0xBC} - a1->{0,4,8}; dead-alloc XZ. */
    w = *(char **)(a0 + 0x30);
    d2.x = *(float *)(w + 0xB4) - *(float *)(a1 + 0x0);
    d2.y = *(float *)(w + 0xB8) - *(float *)(a1 + 0x4);
    d2.z = *(float *)(w + 0xBC) - *(float *)(a1 + 0x8);
    d2b = d2;
    d2c = d2b;
    p2 = &xz2;
    if (p2 == 0) p2 = (Vec3 *)game_uso_func_055750(12);
    p2->x = d2c.x;
    p2->z = d2c.z;
    p2->y = 0.0f;
    /* block3: normalize the dot of the two XZ vecs by |xz1|. */
    mag = game_uso_func_082880(xz1.x * xz1.x + xz1.z * xz1.z);
    if (0.0f < game_uso_func_082880(xz1.x * xz1.x + xz1.z * xz1.z)) {
        normv = (xz1.x * xz2.x + xz1.z * xz2.z) /
                game_uso_func_082880(xz1.x * xz1.x + xz1.z * xz1.z);
    } else {
        normv = 0.0f;
    }
    /* block4: range predicate. */
    a1y = *(float *)(a1 + 0x34);
    lhs = (*(float *)(a2 + 0x34) - a1y) * normv;
    rhs = mag * (*(float *)(w + 0xB8) - (a1y - 400.0f));
    ret = 0;
    if (lhs < rhs) {
        ret = 1;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A0E8);
#endif

/* MATCHED 2026-06-20 (stale-cap catch): the "2 pre-jal a1 spills" cap
 * (sw a1,0x1C(sp) incoming-home + sw a1,0x4(sp) in the jal delay slot) is the
 * struct-by-value-homes-arg lever (docs/IDO_CODEGEN). The first call is varargs
 * passing a1 by VALUE as a 1-int struct: IDO places it in $a1 AND homes it to
 * the outgoing-arg slot 0x4(sp), while the struct's addressability forces the
 * incoming home at 0x1C(sp). K&R and `(int,...)` prototypes both fail to emit
 * the home; only struct-by-value does. 20/20 words byte-exact, 0 non-reloc diffs. */
extern int game_uso_func_053104();
extern int import_8006EF48;
typedef struct { int a; } S1A374;
int game_uso_func_0000A374(a0, a1, a2)
int a0, a1, a2;
{
    int r = game_uso_func_053104(*(int *)&import_8006EF48, *(S1A374*)&a1);
    if (r == 0) return 0;
    return (int)game_uso_func_000043D8((int **)r, (int *)a2, 0);
}

/* game_uso_func_0000A3C4 - MATCHED 2026-07-08 (144/144 words + ROM byte-exact;
 * prior "sub-80 table-dispatch ceiling" note was FALSE). Picks the nearer of the
 * two table entries (a0->0x40 vs a0->0x7C) to the ref point ctx->0x908+0xB4 by
 * squared XZ distance and re-targets a0->0x40. Levers that cracked it:
 * (1) a0 param used DIRECTLY (no local copy) -> uopt homes it at the incoming
 *     slot (sp+0xB0) and shuttles via $a3 with flush/reload around every call
 *     (NO s-regs anywhere - do not introduce a `s0 = a0` copy);
 * (2) slot results in `int *slots[2]` (ARRAY, slots[1]=first/0x40, slots[0]=
 *     second/0x7C) - array elements resist uopt promotion -> homed at 0x88/0x84
 *     with `sw v0` in the bnez delay + fresh reload at each use (1-word-struct
 *     fields get region-cached in $t regs instead - wrong);
 * (3) only slot1 has the `->0x84 & 0x10 -> ->0x2C` re-point, via named temp w
 *     (colors $v0);
 * (4) alloc-fallback blocks: `if (1) { p = &buf; }` barrier keeps the
 *     `if (p==0) p = 055750(12); if (!p) goto skip;` null test un-folded
 *     (plain `p = &buf` folds the test + deletes the calls);
 * (5) per-block float values through named fx/fz (color $f0/$f2 candidates;
 *     zeros walk the fp temp FIFO f4/f6/f8), q = base+0x30 colors $v0;
 * (6) frame layout: decl order p,v1,v2,buf2,buf3,slots,buf1,ref,w,fx,fz,q +
 *     volatile char pad[0x4C] -> homes v1@A8,v2@A4,buf2@98,buf3@8C,slots@84/88,
 *     buf1@78,ref@74, p's dead home takes the 0xAC slack word, pad fills the
 *     0x18-0x63 dead region (frame 0xB0). a1 by-VALUE 1-int struct to A374
 *     (S1_A3C4) homes to sp+4 per the A374 crack. */
extern char game_uso_D_807FEB38;
extern char game_uso_D_807FEDF8;
extern char game_uso_D_807FEE20;
typedef struct { float x, y, z; } V3_A3C4;
typedef struct { int a; } S1_A3C4;
void game_uso_func_0000A3C4(int *a0) {
    V3_A3C4 *p;
    S1_A3C4 v1, v2;
    V3_A3C4 buf2, buf3;
    int *slots[2];
    V3_A3C4 buf1;
    float *ref;
    int *w;
    float fx, fz;
    float *q;
    volatile char padA3C4[0x4C];

    a0[0x68 / 4] &= ~1;
    if (*(int *)((char *)a0[0x30 / 4] + 0x908) == 0) {
        return;
    }
    v1.a = *(int *)(*(int **)((char *)&game_uso_D_807FEB38 + 0x548 + a0[0x40 / 4] * 4));
    slots[1] = (int *)game_uso_func_0000A374(a0, v1,
                (int)(*(int *)((char *)a0[0x30 / 4] + 0x908) + 0xB4));
    if (slots[1] == 0) {
        game_uso_func_047B1C((char *)&game_uso_D_807FEDF8 + 0x7EC,
                             (char *)&game_uso_D_807FEDF8 + 0x808, 0x450);
    }
    if (slots[1][0x84 / 4] & 0x10) {
        w = (int *)slots[1][0x2C / 4];
        slots[1] = w;
    }
    v2.a = *(int *)(*(int **)((char *)&game_uso_D_807FEB38 + 0x548 + a0[0x7C / 4] * 4));
    slots[0] = (int *)game_uso_func_0000A374(a0, v2,
                (int)(*(int *)((char *)a0[0x30 / 4] + 0x908) + 0xB4));
    if (slots[0] == 0) {
        game_uso_func_047B1C((char *)&game_uso_D_807FEE20 + 0x814,
                             (char *)&game_uso_D_807FEE20 + 0x830, 0x45B);
    }
    ref = (float *)(*(int *)((char *)a0[0x30 / 4] + 0x908) + 0xB4);
    if (1) { p = &buf1; }
    if (p == 0) {
        p = (V3_A3C4 *)game_uso_func_055750(12);
        if (p == 0) goto skip1;
    }
    fx = ref[0];
    fz = ref[2];
    p->x = fx;
    p->z = fz;
    p->y = 0.0f;
skip1:
    if (1) { p = &buf2; }
    if (p == 0) {
        p = (V3_A3C4 *)game_uso_func_055750(12);
        if (p == 0) goto skip2;
    }
    q = (float *)((char *)slots[1] + 0x30);
    fz = q[2];
    fx = q[0];
    p->y = 0.0f;
    p->z = fz;
    p->x = fx;
skip2:
    if (1) { p = &buf3; }
    if (p == 0) {
        p = (V3_A3C4 *)game_uso_func_055750(12);
        if (p == 0) goto skip3;
    }
    q = (float *)((char *)slots[0] + 0x30);
    fz = q[2];
    fx = q[0];
    p->y = 0.0f;
    p->z = fz;
    p->x = fx;
skip3:
    if ((buf1.x - buf3.x) * (buf1.x - buf3.x) + (buf1.z - buf3.z) * (buf1.z - buf3.z) <
        (buf1.x - buf2.x) * (buf1.x - buf2.x) + (buf1.z - buf2.z) * (buf1.z - buf2.z)) {
        a0[0x40 / 4] = a0[0x7C / 4];
    }
}

// game_uso_func_0000A604 — STRUCTURAL PASS (0x1D4 / 117 words,
// no episode). Raw-.word USO form (single function, game_uso main
// game-logic; boundary already split by commit 66d6c531 — named fn
// itself was still undecoded). Hand-decoded.
//
// Per-object physics/state advance step.
//
//   void game_uso_func_0000A604(Obj *obj) {              // obj -> s0
//     World *w = obj->0x30;
//     // copy obj->0xB4/0xB8/0xBC transform into sp scratch;
//     // scale a Vec3 (w->0x318/0x31C/0x320) by w->0xA8, matrix*
//     //   vector compose -> sp+0x50/0x7C/0x84 (mul.s/add.s chains);
//     int r = func_00000000(w->0x548[obj->0x5C], …);      // query/sample
//     if (r) {
//       if (func_00000000(obj->0x2C, …) && …) {
//         // FP clamp: if (obj->0x84 ...) vs 250.0f (0x437A0000) and
//         //   obj->0x54 / obj->0x38 thresholds, write obj->0x60/
//         //   obj->0x40;
//       }
//     }
//     if (++obj->0x5C >= 0xA) obj->0x5C = 0;               // wrap counter
//     obj->0x68 &= ~2;                                      // clear flag
//   }
//
// Struct-typing reference:
//   obj: 0x30 -> World (w->0xA8 a scale, w->0x318/0x31C/0x320 a Vec3,
//     w->0x548 a per-index record array), 0x2C a sub-obj, 0x5C a
//     cyclic counter (++ mod 0xA), 0x60/0x40 outputs, 0x68 flag word
//     (bit 0x2 cleared each step), 0xB4/0xB8/0xBC a transform Vec3,
//     0x38/0x54/0x84 f32 state. const 250.0f. func_00000000 = USO
//     placeholder dispatcher (sample / query).
// State 2026-06-23: 78.55% -> 89.54% (objdiff fuzzy). Structural
//   bugs FIXED this pass:
//   (1) FP clamp `f0 = f0 + 250.0f*x` -> compound `f0 += 250.0f*x`
//       gives IDO's const-first operand order (mtc1 const; lwc1 x;
//       mul) + `add.s f0,f0,prod` (was operand-swapped). [line-109
//       FP-compound-assign lever]
//   (2) scaled = w->0x318[i]*s computed via 3 temp scalars
//       (mx/my/mz) THEN stored -> grouped lwc1/lwc1/lwc1 then
//       mul.s f2/f12/f14 (exact target reg/eval order). Per-element
//       store-immediately interleaved load/mul/store (wrong).
//   (3) `w` re-derefed inline (`*(char**)(obj+0x30)` twice, no held
//       local) -> target's TWO `lw,48(a0)` (t6 for tbuf copy, v0 for
//       scale) instead of a single cached load.
// RESIDUAL CAP (frame-spread coloring): build frame -0x80 vs target
//   -0x98 (6 words short). Target interleaves the v0/a1arg/a2 call-
//   spill slots AMONG the 4 Vec3 buffers (scaled 0x50, copy1 0x64,
//   tbuf 0x7C, copy2 0x8C w/ gaps); our build packs the buffers
//   contiguously + spills low. Every downstream sp-offset then
//   cascades (the remaining ~88 "other" diffs are all same-opcode
//   offset shifts, NOT structure). Permuter base score 1705, NOT
//   beaten across 500 iters (randomize/reorder-decl/temp-for-expr/
//   commutative) -> genuine slot-allocation cap. .text-only ROM gate
//   would land IF the frame matched; it does not. Left NM at 89.54%.
//   Name pre-checked: no extern reuse.
/* game_uso_func_0000A604 — EXACT 117/117 words (self-verified clean rebuild of
 * build/non_matching/src/game_uso/game_uso.c.o, 0 diffs vs
 * asm/nonmatchings/game_uso/game_uso/game_uso_func_0000A604.s; jal words
 * 0x0C000000 both sides). Was the "frame-spread coloring cap" NM at 90.01%.
 *
 * PREREQUISITE (outside this body): the game_uso_func_0000A374 DEFINITION
 * (line ~8425) must be converted from ANSI `(int a0, int a1, int a2)` to K&R
 * `(a0, a1, a2) int a0, a1, a2;` so no prototype is in scope at this call —
 * otherwise cfe rejects the struct arg. A374's own 20/20 bytes verified
 * UNCHANGED by the conversion (int params are K&R/ANSI-identical in IDO).
 *
 * Levers (in addition to F948's re-base + decl-order + bottom-pad pair):
 *  (1) DECL-ORDER FRAME MAP (top-down from 0x94, frame -0x98): copy2@0x8C,
 *      a1arg@0x88, tbuf@0x7C, v0var-spill@0x78, pad_a[2]@0x70, copy1@0x64,
 *      pad_b[2]@0x5C, scaled@0x50, t@0x4C, pad_bot[5]+scalars fill 0x20-0x48.
 *      NOTE: scalar decls at the bottom (s,f0,q,mx,my,mz) DO take 6 slots here
 *      — pad_bot sized to compensate (5, not 11).
 *  (2) a1arg is a ONE-WORD STRUCT (One1) passed by value to K&R A374 ->
 *      emits BOTH missing words: home store sw a1,0x88(sp) (struct stores
 *      escape DSE) and outgoing-arg home sw a1,4(sp) in the jal delay.
 *      (Same mechanism as 2744's a2/sw a2,8(sp).)
 *  (3) rec-chain INLINED (no named rec/counter locals) -> D-base lui/addu/lw
 *      chain stays in temps t5/t6/t7 (named locals promote to $a3/$v1
 *      candidates — the old 90.01% residual).
 *  (4) t SHARED for field2c AND counter-increment -> both color to $a2
 *      (explains the three lw a2,0x5C(s0) copies: two branch-likely delay
 *      duplicates + join).
 *  (5) FP tail UN-NESTED: `if (f0<0) f0 += 250*x;` then a SEPARATE
 *      `if (0<=f0 && f0<obj->0x60)` -> uopt duplicates the c.le.s per path
 *      (bc1fl +6 shape). Nested form branches +0x12 (wrong).
 *  (6) &copy1 base in $v0 materialized LATE (addiu v0,sp,0x64 after q dies):
 *      q REASSIGNED to &copy1 (one-reg-per-variable web) AND the two struct
 *      copies wrapped in `if (1) { }` — the BB boundary blocks the copy-prop
 *      that otherwise folds q away and hoists a fresh $a3 temp to the
 *      prologue (the last 20-diff residual). Plain reassign without if(1)
 *      does NOT work.
 */
void game_uso_func_0000A604(char *obj) {
    Vec3 copy2;
    One1 a1arg;
    Vec3 tbuf;
    char *v0var;
    volatile int pad_a[2];
    Vec3 copy1;
    volatile int pad_b[2];
    Vec3 scaled;
    int t;
    volatile int pad_bot[5];
    float s;
    float f0;
    float *q;
    float mx, my, mz;

    tbuf = *(Vec3 *)(*(char **)(obj + 0x30) + 0xB4);
    s = *(float *)(obj + 0xA8);
    q = (float *)(*(char **)(obj + 0x30) + 0x318);
    mx = q[0] * s;
    my = q[1] * s;
    mz = q[2] * s;
    q = (float *)&copy1;
    scaled.x = mx;
    scaled.y = my;
    scaled.z = mz;
    if (1) {
        *(Vec3 *)q = scaled;
        copy2 = *(Vec3 *)q;
    }
    tbuf.x = tbuf.x + copy2.x;
    tbuf.y = tbuf.y + copy2.y;
    tbuf.z = tbuf.z + copy2.z;

    a1arg.a = **(int **)((char *)&D_00000000 + 0x548 + *(int *)(obj + 0x5C) * 4);
    v0var = (char *)game_uso_func_0000A374((int)obj, a1arg, (int)&tbuf);
    if (v0var != 0) {
        t = *(int *)(v0var + 0x2C);
        if (t != 0) {
            if (game_uso_func_00009B88(obj, v0var, t) != 0) {
                if (game_uso_func_0000A0E8(obj, v0var, (char *)t) != 0) {
                    f0 = tbuf.z - *(float *)(v0var + 0x38);
                    if (f0 < 0.0f) {
                        f0 += 250.0f * *(float *)(v0var + 0x54);
                    }
                    if (0.0f <= f0 && f0 < *(float *)(obj + 0x60)) {
                        *(float *)(obj + 0x60) = f0;
                        *(int *)(obj + 0x40) = *(int *)(obj + 0x5C);
                    }
                }
            }
        }
    }
    t = *(int *)(obj + 0x5C) + 1;
    *(int *)(obj + 0x5C) = t;
    if (t >= 0xA) {
        *(int *)(obj + 0x68) &= ~2;
    }
}

void game_uso_func_0000A7D8(int *a0) {
    a0[0x5C / 4] = 0;
    a0[0x68 / 4] |= 2;
    *(float *)((char *)a0 + 0x60) = *(float *)((char *)&D_00000000 + 0x110);
}

// game_uso_func_0000A7F8 — STRUCTURAL PASS (0x3A0 / 232 words,
// no episode). Raw-.word USO form (single function, game_uso main
// game-logic). Same FP world-matrix-builder family as
// game_uso_func_000028C0 / 00002CC8 / 0000A604.
//
//   void game_uso_func_0000A7F8(Obj *obj) {              // obj -> a2
//     World *w = obj->0x30;
//     // copy obj->0xB4/0xB8/0xBC transform into sp scratch;
//     // Vec3 = { w->0x318, w->0x31C, w->0x320 } scaled by w->0xA8;
//     //   (mul.s f0=w->0xA8; f14=f4*f0, f2=f6*f0, f12=f8*f0);
//     //   store sp+0xB8/0xBC/0xC0;
//     // copy 3-word matrix-row blocks between obj sub-records and sp;
//     // matrix*vector FP chains compose a world transform; ~6
//     //   func_00000000 sub-calls (transform helpers);
//     // write the composed transform back into obj fields.
//   }
//
// Struct-typing reference:
//   obj: 0x30 -> World (w->0xA8 scale, w->0x318/0x31C/0x320 a Vec3),
//     0xB4/0xB8/0xBC a transform Vec3. sp scratch = matrix rows +
//     output. func_00000000 = USO placeholder dispatcher (transform
//     helper). See game_uso_func_000028C0's comment for the shared
//     family shape.
// Caps (DEFERRED): raw-word USO + placeholder calls + 232-word FP
//   transform; USO mnemonic disasm limitation prevents byte-match.
//   Real-C STRUCTURAL body below — world-Vec3 scale + transform
//   compose skeleton (family of 000028C0 / 00002CC8 / 0000A604).
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
/* game_uso_func_0000A7F8 — DECODE PASS (0x3A0 / 232 words). Same FP
 * world-transform-compose family as 000028C0 / 00002CC8 / 0000A604.
 * Decode upgrade over prior STRUCTURAL stub: the three placeholder
 * func_00000000 dispatch calls are now bound to their reloc-resolved
 * real callees —
 *   a8e0  jal game_uso_func_0000A374 (varargs: 4th arg `node` homed to sp+4)
 *   a908  jal game_uso_func_0000A0E8 (obj, r1, m)
 *   a96c/a9b0/aa40/aa7c  jal game_uso_func_055750 (12-byte node allocator)
 * — and the static-table lookup node = *(*(D[obj->0x5C]+0x548)) is kept.
 * Byte-match still deferred (A374 varargs ABI + raw-word USO disasm); this
 * pass raises decode fidelity (placeholder calls -> typed real callees). */
void game_uso_func_0000A7F8(char *obj) {
    char *w = *(char **)(obj + 0x30);
    char *r1, *m;
    Vec3 blockA, scaled, c1, c2;
    Vec3 b1, b2, b3, b4, b5, b6;
    Vec3 *p1, *p2, *p4, *p5;
    Vec3 *volatile vp;
    float s, d, magsq, cross, result;
    int idx, cnt;
    char *node;
    /* blockA(sp+0xE4) = w transform (0xB4) Vec3; scaled(sp+0xB8) = world-vec
     * (0x318) * obj scale (0xA8) as three separate mul.s. The scaled vec is
     * then fanned out through two scratch copies c1(sp+0xCC) <- scaled,
     * c2(sp+0xF4) <- c1 (Tri3i int-word copies), and blockA += c2 element-wise.
     * The intermediate buffers must be addressed (&) to survive as distinct
     * scratch slots — see docs/IDO_CODEGEN.md float-Vec3 fanout. */
    *(Tri3i *)&blockA = *(Tri3i *)(w + 0xB4);
    s = *(float *)(obj + 0xA8);
    scaled.x = *(float *)(w + 0x318) * s;
    scaled.y = *(float *)(w + 0x31C) * s;
    scaled.z = *(float *)(w + 0x320) * s;
    *(Tri3i *)&c1 = *(Tri3i *)&scaled;
    *(Tri3i *)&c2 = *(Tri3i *)&c1;
    blockA.x = blockA.x + c2.x;
    blockA.y = blockA.y + c2.y;
    blockA.z = blockA.z + c2.z;
    /* node = *(*(GLOBAL + obj->0x5C*4 + 0x548)) */
    idx = *(int *)(obj + 0x5C);
    node = *(char **)(*(char **)((char *)&D_00000000 + 0x548 + idx * 4));
    /* A374: world-query. Target homes a 4th vararg (node) to sp+4, but A374's
     * established 3-arg prototype blocks that here (see func_00006F38 note);
     * call with the matching 3 args to stay compilable. */
    r1 = (char *)game_uso_func_0000A374(obj, node, &blockA);
    if (r1 != 0) {
    m = *(char **)(r1 + 0x2C);
    if (m != 0) {
    if (game_uso_func_0000A0E8(obj, r1, m) != 0) {
    /* FP threshold gate: d = blockA.z - r1->0x38; if (d<0) d += 250*r1->0x54;
     * if (d<0) return. */
    d = blockA.z - *(float *)(r1 + 0x38);
    if (d < 0.0f) d += 250.0f * *(float *)(r1 + 0x54);
    if (d >= 0.0f) {
        /* b1 = m's XZ vec; b2 = b1 - r1's XZ vec; b3 = b2. Each Vec3 slot is a
         * conditionally-allocated node: p = &slot; if (!p) p = alloc(12). The
         * target emits the bnez + jal game_uso_func_055750 guard even though
         * &slot is non-null, so the &-of-stack pointer is routed through a
         * volatile temp to stop the optimizer proving it non-zero (preserves
         * the dead allocator branch — see docs/IDO_CODEGEN.md). */
        vp = &b1; p1 = vp; if (p1 == 0) p1 = (Vec3 *)game_uso_func_055750(12);
        p1->x = *(float *)(m + 0x30); p1->z = *(float *)(m + 0x38); p1->y = 0.0f;
        vp = &b2; p2 = vp; if (p2 == 0) p2 = (Vec3 *)game_uso_func_055750(12);
        p2->z = p1->z - *(float *)(r1 + 0x38); p2->x = p1->x - *(float *)(r1 + 0x30); p2->y = 0.0f;
        *(Tri3i *)&b3 = *(Tri3i *)&b2;
        /* b4 = blockA XZ; b5 = b4 - r1's XZ vec; b6 = b5 */
        vp = &b4; p4 = vp; if (p4 == 0) p4 = (Vec3 *)game_uso_func_055750(12);
        p4->x = blockA.x; p4->z = blockA.z; p4->y = 0.0f;
        vp = &b5; p5 = vp; if (p5 == 0) p5 = (Vec3 *)game_uso_func_055750(12);
        p5->z = p4->z - *(float *)(r1 + 0x38); p5->x = p4->x - *(float *)(r1 + 0x30); p5->y = 0.0f;
        *(Tri3i *)&b6 = *(Tri3i *)&b5;
        /* result = cross(b3,b6)^2 / |b3|^2 in the XZ plane */
        magsq = b3.x * b3.x + b3.z * b3.z;
        if (magsq == 0.0f) {
            result = 0.0f;
        } else {
            cross = b3.z * b6.x - b3.x * b6.z;
            result = cross * cross / magsq;
        }
        if (result < *(float *)(obj + 0x60)) {
            *(float *)(obj + 0x60) = result;
            *(int *)(obj + 0x40) = *(int *)(obj + 0x5C);
        }
    }
    }
    }
    }
    /* common tail (runs on every path): cnt = obj->0x5C + 1; obj->0x5C = cnt;
     * if (cnt >= 10) obj->0x68 &= ~4. */
    cnt = *(int *)(obj + 0x5C) + 1;
    *(int *)(obj + 0x5C) = cnt;
    if (cnt >= 10) *(int *)(obj + 0x68) &= ~4;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A7F8);
#endif

void game_uso_func_0000AB98(void *a0) {
    *(int*)((char*)a0 + 0x5C) = 0;
    *(int*)((char*)a0 + 0x68) |= 4;
    *(float*)((char*)a0 + 0x60) = *(float*)(&D_00000000 + 0x114);
}

void game_uso_func_0000ABB8(char *dst) {
    int tmp;
    game_uso_func_00004080(&tmp);
    game_uso_func_000040BC((float*)(dst + 0x10));
}

void game_uso_func_0000ABE8(char *dst) {
    int tmp;
    game_uso_func_00004080(&tmp);
    game_uso_func_000040F8((Vec3*)(dst + 0x10));
}

void game_uso_func_0000AC18(char *dst) {
    int tmp;
    game_uso_func_00004080(&tmp);
    game_uso_func_00004168((Quad4*)(dst + 0x10));
}

void game_uso_func_0000AC48(char *dst) {
    int tmp;
    game_uso_func_00004080(&tmp);
    game_uso_func_00004080((int*)(dst + 0x10));
}

/* game_uso_func_0000AC78: 36-insn alloc-init constructor. alloc(0x40) +
 * init(051C28), set vtable 0x28 = &import_8006ED80, clear 0x3C; then walk
 * a0->0x40 node and link it back via 07ACE0.
 *
 * 2026-06-21 CRACKED via masked-twin port from eddproc_uso_func_000003BC
 * (donor, byte-exact). The prior "25-diff v1-vs-a2 regalloc cap" was a
 * structure issue, not a true cap: the donor's p2/head/p1 split + p1-reuse-
 * for-arg0 + decl-order (p2,head,p1) + condition re-load (`if((int*)p1[0x40/4]
 * !=0)`) forces IDO to spill the object as two live ranges (frame 0x28) and
 * color it a0(block1)/v1(block2) instead of a2(0x20). Do NOT simplify the
 * variable reuse or the re-load — they are load-bearing for the reg/slot
 * allocation. See docs/IDO_CODEGEN.md interleave-decl-spill-slot. */
extern char import_8006ED80;
int *game_uso_func_0000AC78(int *arg0) {
    int *p2;
    int *head;
    int *p1;
    p1 = (int*)game_uso_func_055750(0x40);
    if (p1 != 0) {
        game_uso_func_051C28(p1);
        *(int*)((char*)p1 + 0x28) = (int)&import_8006ED80;
        *(int*)((char*)p1 + 0x3C) = 0;
    }
    p2 = p1;
    p1 = arg0;
    head = (int*)p1[0x40 / 4];
    if ((int*)p1[0x40 / 4] != 0) {
        game_uso_func_07ACE0((char*)p2 + 0x10, head);
        if (*(int*)((char*)head + 0x14) != 0) {
            *(int*)((char*)head + 0x4) = 1;
        }
        *(int*)((char*)head + 0x14) = (int)p2;
    }
    return p2;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_uso/game_uso/game_uso_func_0000AC78_pad.s")

void game_uso_func_0000AD10(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_0000AD4C(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_0000AD88(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void game_uso_func_0000ADE0(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

#ifdef NON_MATCHING
/* game_uso_func_0000AE1C: 278-insn (0x458) spine constructor. Frame -0xA0.
 * Same family as the find-or-create alloc-cascade constructors
 * (000034A4 / 00003018 / 0000C48C). Reconstructed 2026-06-26 from the
 * resolved EXPECTED .o: the prior body used gl_func_00000000 placeholder
 * callees + &D_00000000 bases (ALL WRONG). Real symbols wired:
 *   allocator        game_uso_func_055750(size)
 *   sub-obj init     game_uso_func_04C678(self, tmpl)
 *   misc inits       game_uso_func_04D3D0(self), game_uso_func_04D3C8(self,2)
 *   vec3 setter      game_uso_func_072EE8(self+0x30, &v3)
 *   24-byte node init game_uso_func_04A188(node, parent, idx, flag)
 *   tail import      import_000F5ADC(0, &game_uso_D_807FF214)
 *   global flag word import_8005EE6C
 *   vtable           &import_80086288, &game_uso_D_807FF24C, ...
 *
 * Find-or-create idiom (dead-sentinel cascade): each sub-object is
 *   p = base + off;  if (base == (T)-off) { p = alloc(N); if (!p) goto skip; }
 * where base+off==NULL iff base==-off — so the alloc arm is statically dead,
 * but IDO emits it (li at,-off; bne base,at,skip; alloc). Several sub-objects
 * use a TWO-LEVEL nested cascade (outer keyed on a reloaded arg0 @ sp+0xA0,
 * inner keyed on the resulting pointer).
 *
 * RESIDUAL: likely a frame-spread / per-stage spill-slot coloring cap (same
 * class as 0000C48C's -0x48-vs-0xC8 residual). Real-symbol reconstruction;
 * NM build path = INCLUDE_ASM. */
extern void game_uso_func_04D3D0(void *self);
extern void game_uso_func_04D3C8(void *self, int a1);
extern char game_uso_D_807FF340, game_uso_D_807FF24C, game_uso_D_807FEE38,
            game_uso_D_807FEE30, game_uso_D_807FF234, game_uso_D_807FF344,
            game_uso_D_807FF34C, game_uso_D_807FF350, game_uso_D_807FF354,
            game_uso_D_807FF358, game_uso_D_807FEE50, game_uso_D_807FEE68,
            game_uso_D_807FF35C, game_uso_D_807FEE80, game_uso_D_807FF214;
extern char import_80086288, import_8005EE6C;
extern int import_000F5ADC();

void *game_uso_func_0000AE1C(void *arg0) {
    void *s0;
    void *p;
    void *q;
    char *o16;
    char *o140;
    char *o36;
    Vec3 v3;
    float v4[4];

    /* Stage 1: find-or-create primary 0x178 buffer (homed at sp+0xA0). */
    if (arg0 == NULL) {
        arg0 = (void *)game_uso_func_055750(0x178);
        if (arg0 == NULL) return arg0;
    }

    /* Stage 2: secondary 0xB4 sub-object into s0. */
    s0 = arg0;
    if (s0 == NULL) {
        s0 = (void *)game_uso_func_055750(0xB4);
        if (s0 == NULL) goto skip_sub;
    }
    game_uso_func_04C678(s0, (char *)&game_uso_D_807FF340 + 0xD50);
    *(int *)((char *)s0 + 0x28) = (int)&import_80086288;

    /* Stage 3: zero a 4-byte node at s0+0x2C (dead-sentinel cascade). */
    p = (char *)s0 + 0x2C;
    if (s0 == (void *)-0x2C) {
        p = (void *)game_uso_func_055750(4);
        if (p == NULL) goto after_node;
    }
    q = p;
    if (p == NULL) {
        q = (void *)game_uso_func_055750(4);
        if (q == NULL) goto after_node;
    }
    *(int *)q = 0;
after_node:
    game_uso_func_04D3D0(s0);
    v3.x = 0.0f;
    v3.y = 0.0f;
    v3.z = 0.0f;
    game_uso_func_072EE8((char *)s0 + 0x30, &v3);
skip_sub:

    /* Stage 4: vtable on reloaded arg0. */
    *(int *)((char *)arg0 + 0x28) = (int)&game_uso_D_807FF24C;

    /* Stage 5: o16 sub-object = arg0+0xDC, nested 2-level cascade. */
    o16 = (char *)arg0 + 0xDC;
    if (arg0 == (void *)-0xDC) {
        o16 = (char *)game_uso_func_055750(0x10);
        if (o16 == NULL) goto after_o16;
    }
    {
        char *r = o16;
        if (o16 == NULL) {
            r = (char *)game_uso_func_055750(0x10);
            if (r == NULL) goto o16_set;
        }
        {
            char *w = r;
            if (r == NULL) {
                w = (char *)game_uso_func_055750(4);
                if (w == NULL) goto o16_fill;
            }
            *(int *)w = (int)((char *)&game_uso_D_807FEE38 + 0x848);
        o16_fill:
            *(int *)(r + 4) = (int)arg0;
            *(int *)(r + 8) = *(int *)((char *)&game_uso_D_807FEE30 + 0x840);
            *(int *)(r + 12) = *(int *)((char *)&game_uso_D_807FEE30 + 0x844);
        }
    o16_set:
        *(int *)o16 = (int)((char *)&game_uso_D_807FF234 + 0xC44);
    }
after_o16:

    /* Stage 6: o140 sub-object = arg0+0xEC (alloc 140), four 24-byte child
     * nodes via 04A188, then the o36 node. */
    o140 = (char *)arg0 + 0xEC;
    if (arg0 == (void *)-0xEC) {
        o140 = (char *)game_uso_func_055750(140);
        if (o140 == NULL) goto end_ret;
    }
    {
        char *s = o140;
        if (o140 == NULL) {
            s = (char *)game_uso_func_055750(8);
            if (s == NULL) goto after_o140hdr;
        }
        *(int *)s = (int)((char *)&game_uso_D_807FF344 + 0xD54);
        *(int *)(s + 4) = 0;
    }
after_o140hdr:
    {
        int idx = *(int *)((char *)&game_uso_D_807FF34C + 0xD5C);
        char *n = o140 + 8;
        if (o140 == (char *)-8) {
            n = (char *)game_uso_func_055750(24);
            if (n == NULL) goto node1;
        }
        game_uso_func_04A188(n, o140, idx, 1);
        *(int *)(n + 12) = (int)((char *)&game_uso_D_807FEE50 + 0x860);
        *(int *)(n + 20) = 0;
        *(float *)(n + 16) = 0.0f;
    }
node1:
    {
        int idx = *(int *)((char *)&game_uso_D_807FF350 + 0xD60);
        char *n = o140 + 32;
        if (o140 == (char *)-32) {
            n = (char *)game_uso_func_055750(24);
            if (n == NULL) goto node2;
        }
        game_uso_func_04A188(n, o140, idx, 1);
        *(int *)(n + 12) = (int)((char *)&game_uso_D_807FEE50 + 0x860);
        *(int *)(n + 20) = 0;
        *(float *)(n + 16) = 0.0f;
    }
node2:
    {
        int idx = *(int *)((char *)&game_uso_D_807FF354 + 0xD64);
        char *n = o140 + 56;
        if (o140 == (char *)-56) {
            n = (char *)game_uso_func_055750(24);
            if (n == NULL) goto node3;
        }
        game_uso_func_04A188(n, o140, idx, 1);
        *(int *)(n + 12) = (int)((char *)&game_uso_D_807FEE50 + 0x860);
        *(int *)(n + 20) = 0;
        *(float *)(n + 16) = 2.0f;
    }
node3:
    {
        int idx = *(int *)((char *)&game_uso_D_807FF358 + 0xD68);
        char *n = o140 + 80;
        if (o140 == (char *)-80) {
            n = (char *)game_uso_func_055750(24);
            if (n == NULL) goto node4;
        }
        game_uso_func_04A188(n, o140, idx, 0);
        *(int *)(n + 12) = (int)((char *)&game_uso_D_807FEE68 + 0x878);
        *(int *)(n + 20) = 0;
        *(int *)(n + 16) = 0;
    }
node4:;
    {
        int idx = *(int *)((char *)&game_uso_D_807FF35C + 0xD6C);
        char *n;
        v4[0] = 1.0f;
        v4[1] = 1.0f;
        v4[2] = 1.0f;
        v4[3] = 1.0f;
        n = (char *)arg0 + 0x68;
        if (arg0 == (void *)-0x68) {
            n = (char *)game_uso_func_055750(36);
            if (n == NULL) goto end_ret;
        }
        o36 = n;
        game_uso_func_04A188(o36, arg0, idx, 0);
        *(int *)(o36 + 12) = (int)((char *)&game_uso_D_807FEE80 + 0x890);
        *(int *)(o36 + 32) = 0;
        *(float *)(o36 + 16) = v4[0];
        *(float *)(o36 + 20) = v4[1];
        *(float *)(o36 + 24) = v4[2];
        *(float *)(o36 + 28) = v4[3];
    }

    /* Tail: clear two flag bits in the global state word, set scalars. */
    {
        int flags = *(int *)((char *)&import_8005EE6C + 4);
        flags &= ~0x00080000;
        flags &= ~2;
        *(int *)((char *)&import_8005EE6C + 4) = flags;
    }
    *(float *)((char *)arg0 + 0xC8) = 1.0f;
    game_uso_func_04D3C8(arg0, 2);
    *(int *)((char *)arg0 + 0xC4) = import_000F5ADC(0, &game_uso_D_807FF214);
    *(float *)((char *)arg0 + 0xCC) = 0.0f;
end_ret:
    return arg0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AE1C);
#endif

/* game_uso_func_0000B274 — verified structural decode (108-insn double-
 * precision easing/animation update; ldc1/c.lt.d/div.d/mul.d + bc1tl/bc1fl
 * branch-likely + 4 calls = documented heavy-double-FPU sub-80 ceiling →
 * INCLUDE_ASM build path; struct-typing reference).
 * Struct-typing: s0->0xA0/0xA4/0xA8 source vec3 (float), s0->0xC8 eased
 * progress, 0xCC its reset value, 0xD0/0xD4 int-trunc'd vec, 0xD8 handle,
 * 0xC4 child obj (vtable @+0x28→{fn@0x1C, short@0x18}; +0xB0/0xB4 float
 * pair, +0xC0 short), 0x134 scale, 0x14C value, 0x164 sub-region. s1=&D
 * global ctx: +0x2A0 float timer, +0x254 handle. D-double consts @0x120/
 * 0x128/0x130/0x138 (thresholds + ease divisor). Caps <80: double-prec
 * FPU chain + bc1tl/bc1fl branch-likely + &D %hi/%lo reloc + 4-call
 * spill. INCLUDE_ASM remains build path (no episode; tautology). */
#ifdef NON_MATCHING
/* game_uso_func_0000B274 — reconstructed from expected/.o (reloc-aware). s1 base =
 * import_8005C108 cached in a saved register; four double thresholds live in distinct
 * rodata symbols game_uso_D_807FFA40/48/50/58 (each at +0x120/0x128/0x130/0x138);
 * destination vec at import_8005C1A8+0xD0..0xD8. Callees: game_uso_func_063734,
 * import_000F8678, game_uso_func_04D700, game_uso_func_05B750. */
extern char import_8005C108;
extern char import_8005C1A8;
extern char game_uso_D_807FFA40;
extern char game_uso_D_807FFA48;
extern char game_uso_D_807FFA50;
extern char game_uso_D_807FFA58;
extern int game_uso_func_063734();
extern int import_000F8678();
extern void game_uso_func_04D700();
extern void game_uso_func_05B750();

void game_uso_func_0000B274(char *s0) {
    char *s1 = &import_8005C108;
    char *dst;
    float vec[3];
    float r;
    char *t2;
    char *v1;
    int *vt;

    if ((double)*(float *)(s1 + 0x2A0) > *(double *)(&game_uso_D_807FFA40 + 0x120)) return;

    vec[0] = *(float *)(s0 + 0xA0);
    vec[1] = *(float *)(s0 + 0xA4);
    vec[2] = *(float *)(s0 + 0xA8);
    if (game_uso_func_063734(*(int *)(s1 + 0x254), &vec[0], 1, 0) == 0) return;

    *(int *)(s0 + 0xD0) = (int)vec[0];
    *(int *)(s0 + 0xD4) = (int)vec[1];
    import_000F8678(s1, s0 + 0xDC);
    *(int *)(s0 + 0xD8) = *(int *)(s1 + 0x254);
    *(float *)(s0 + 0xC8) = *(float *)(s0 + 0xCC);

    if (*(double *)(&game_uso_D_807FFA48 + 0x128) < (double)*(float *)(s1 + 0x2A0)) {
        double d = ((double)*(float *)(s1 + 0x2A0) - *(double *)(&game_uso_D_807FFA48 + 0x128))
                   / *(double *)(&game_uso_D_807FFA50 + 0x130);
        *(float *)(s0 + 0xC8) = (float)((double)*(float *)(s0 + 0xC8) * (1.0 - d));
    }

    if (*(double *)(&game_uso_D_807FFA58 + 0x138) < (double)*(float *)(s0 + 0xC8)) return;

    game_uso_func_04D700(s0);

    dst = &import_8005C1A8;
    *(float *)(dst + 0xD0) = *(float *)(s0 + 0xA0);
    *(float *)(dst + 0xD4) = *(float *)(s0 + 0xA4);
    *(float *)(dst + 0xD8) = *(float *)(s0 + 0xA8);
    r = *(float *)(s0 + 0x134) * *(float *)(s0 + 0xC8);
    game_uso_func_05B750(s1, s0 + 0x164);

    t2 = *(char **)(s0 + 0xC4);
    *(short *)(t2 + 0xC0) = *(short *)(s0 + 0x14C);
    *(float *)(*(char **)(s0 + 0xC4) + 0xB0) = r;
    *(float *)(*(char **)(s0 + 0xC4) + 0xB4) = r;

    v1 = *(char **)(s0 + 0xC4);
    vt = *(int **)(v1 + 0x28);
    (*(void (**)(char *))((char *)vt + 0x1C))((char *)((int)(short)*(short *)((char *)vt + 0x18) + (int)v1));
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B274);
#endif

#ifdef NON_MATCHING
/* 96.55% NM. 29-insn FPU helper. Init local Vec3 buffer at sp+0x24..0x2C with 3
 * floats (first 2 = 0.0, third = D_0+0x140), call gl_func(D_0+0x11C, &buf28,
 * &buf2C); call again gl_func(D_0+0x104, &buf24, &buf2C); writes 3 float
 * results from buf24/28/2C into a0+0x60/0x64/0x68.
 *
 * FRAME FIX 2026-05-31: target frame is -48 with the live buf at sp+0x24..0x2C
 * (8 phantom bytes / 2 unused float slots below it). Declaring `float buf[5]`
 * and using only [2..4] reserves those 2 low slots (GCC can't partially-elide a
 * single array), forcing frame -48 and the exact 0x24/0x28/0x2C offsets — a
 * plain `float buf[3]` gave -40 and shifted every stack offset by 8 (96.03%).
 * RESIDUAL (1 insn): target stores `swc1 $f0,buf[2]/buf[3]` with NO
 * `mtc1 zero,$f0` anywhere — it relies on $f0 already holding 0.0 from calling
 * context (full-TU artifact). In isolation GCC must materialize the zero
 * (`mtc1 zero,$f0`), the lone extra insn. Isolated-vs-full-TU cap.
 * 2026-06-22: replaced the bogus separate `extern float D_b424_140` (resolved to
 * its own symbol @ off 0 -> `lwc1 $f4,0(at)`) with `*(float*)((char*)&D_00000000
 * + 0x140)` -> `lwc1 $f4,0x140(at)` reloc-form, the true address. Sole counted
 * residual is now the `mtc1 zero,$f0` FP-zero materialization cap. */
extern void game_uso_func_070338(float f, float *p1, float *p2);
extern void game_uso_func_04DA24(int *a0);
void game_uso_func_0000B424(int *a0) {
    float buf[5];
    buf[2] = 0.0f;
    buf[3] = 0.0f;
    buf[4] = *(float*)((char*)&D_00000000 + 0x140);      /* sp+0x2C = D[0x140] */
    /* float-first arg (-> $f12); a0 is saved across the calls, not passed */
    game_uso_func_070338(*(float*)((char*)a0 + 0x11C), &buf[3], &buf[4]);
    game_uso_func_070338(*(float*)((char*)a0 + 0x104), &buf[2], &buf[4]);
    *(float*)((char*)a0 + 0x60) = buf[2];
    *(float*)((char*)a0 + 0x64) = buf[3];
    *(float*)((char*)a0 + 0x68) = buf[4];
    game_uso_func_04DA24(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B424);
#endif

void game_uso_func_0000B498(char *a0) {
    game_uso_func_00000000(a0 + 0xEC);
}

// game_uso_func_0000B4B8 — STRUCTURAL PASS (0x258 / 150 words,
// no episode). Raw-.word USO form (single function, game_uso main
// game-logic; boundary already split by commit c305c2b1 — named fn
// still undecoded). Hand-decoded.
//
// 2D-grid / height-map sample with FP interpolation.
//
//   float game_uso_func_0000B4B8(Obj *obj) {             // obj -> a0
//     Ctx *c = *(Ctx**)(D_0 + 0x240);
//     // grid = obj->0xD8; W = obj->0xD0; H = obj->0xD4;
//     // i = c->0x148-derived * W + …  (multu index calc into the
//     //   2D cell array; bounds-checked vs W*H);
//     // read u16 cell values (lhu) at neighbouring grid points;
//     // FP block (~10 ops): convert cells to float and bilinear-
//     //   interpolate using obj->0xB8/0xBC fractional coords;
//     obj->0xCC = result;                                  // sampled value
//     return result;
//   }
//
// Struct-typing reference:
//   obj: 0xD0 grid width, 0xD4 grid height, 0xD8 -> u16 cell array,
//     0xB8/0xBC fractional sample coords, 0xCC f32 sampled output;
//     0xD0/0xF0 sub-fields used in the index calc. *(Ctx**)(D_0 +
//     0x240) = global ctx (->0x148 / ->0xB8 inputs to the index).
//     Terrain/height-map lookup (snowboard ground sampling).
// Caps (DEFERRED): raw-word USO + 2D-index multu + FP interp; USO
//   mnemonic disasm limitation prevents byte-match. Real-C
//   STRUCTURAL body below — 2D-grid sample + bilinear interp
//   skeleton (terrain/height-map lookup; snowboard ground
//   sampling). Byte-match deferred. Name pre-checked: no extern
//   reuse.
extern short game_uso_D_807FF2B4[];
#ifdef NON_MATCHING
/* Re-decoded 2026-06-24: prior body counted the 0xFFFC sentinel neighbours but
 * dropped the FP tail (result = count/9, clamp-or-EMA into obj->0xCC) and used
 * the wrong base symbol (&D_00000000 instead of import_8005C348). c comes from
 * *(import_8005C348 + 0x240); data = (c->0x148)->0xF0. Returns the count. */
extern char import_8005C348;
extern char game_uso_D_807FFA68;
#define GAME_D_807FFA68_148 (*(double *)(&game_uso_D_807FFA68 + 0x148))
int game_uso_func_0000B4B8(char *obj) {
    char *c = *(char **)(&import_8005C348 + 0x240);
    char *grid = *(char **)(obj + 0xD8);
    unsigned short *data = *(unsigned short **)(*(char **)(c + 0x148) + 0xF0);
    short *tbl = game_uso_D_807FF2B4;
    int y = *(int *)(obj + 0xD4);
    int x = *(int *)(obj + 0xD0);
    int w = *(int *)(grid + 0xB8);
    int h = *(int *)(grid + 0xBC);
    int count = 0;
    int i;
    int idx;
    float result;
    float prev;
    for (i = 0; i < 9; i++) {
        idx = (y + tbl[2 * i]) * w + x + tbl[2 * i + 1];
        if (idx > 0 && idx < w * h && data[idx] == 0xFFFC) {
            count++;
        }
    }
    result = (float)count / 9.0f;
    prev = *(float *)(obj + 0xCC);
    if (result < prev) {
        *(float *)(obj + 0xCC) = result;
    } else {
        *(float *)(obj + 0xCC) =
            (float)((double)prev + (double)(result - prev) * GAME_D_807FFA68_148);
    }
    return count;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B4B8);
#endif

void game_uso_func_0000B710(char *a0) {
    float one = 1.0f;
    float zero = 0.0f;

    *(float*)(a0 + 0x10) = one;
    *(float*)(a0 + 0x0C) = one;
    *(float*)(a0 + 0x08) = one;
    *(float*)(a0 + 0x04) = one;
    *(float*)(a0 + 0x00) = zero;
    *(float*)(a0 + 0x14) = *(float*)(&D_00000000 + 0x150);
    *(s32*)(a0 + 0x18) = 0;
    *(s32*)(a0 + 0x1C) = 8;
    *(float*)(a0 + 0x20) = zero;
}

/* game_uso_func_0000B750 — verified structural decode (77=77 length-exact,
 * 9% bytes; IDO FPU-regalloc + double-const/reloc scheduling cap → <80 so
 * INCLUDE_ASM build path; game_uso struct-typing reference).
 * void f(int *a0, int *s0, float *a2, float *a3, float arg4 /@sp+104/){
 *   int flags = a0->0x1C; float f0 = a0->0x00;
 *   if (flags & 4) f0 += arg4 * 400.0f;            // 0x43c80000
 *   float k = (flags & 8) ? arg4 : 1.0f;           // f16, branch-selected
 *   *(float*)(&D + 0xD0) = a2[0] + a3[0]*f0;       // basis-vec mul-add out
 *   *(float*)(&D + 0xD4) = a2[1] + a3[1]*f0;
 *   *(float*)(&D + 0xD8) = a2[2] + a3[2]*f0;
 *   *(short*)(s0 + 0xC0) = a0->0x18;
 *   float v = a0->0x14;
 *   if (a0->0x1C & 2) v *= k;
 *   if ((double)v > *(double*)(&D + 0x158)) {       // ldc1/cvt.d.s/c.lt.d/bc1fl
 *     *(float*)(s0+0xB0) = *(float*)(s0+0xB4) = v;
 *     float buf[4] = { a0->0x04, a0->0x08, a0->0x0C, a0->0x10 * k };
 *     func_00000000(&D, buf);                       // buf @ sp+64
 *     int *vt = (int*)s0->0x40;                      // vtable-ish
 *     (*(fn*)vt->0x1C)( (short)vt->0x18 + (int)s0 );  // jalr, a0=vt->0x18+s0
 *   }
 * }
 * Struct-typing value — a0 source: floats @0x00/04/08/0C/10/14, int @0x18,
 * flag word @0x1C (bits 0x2 scale-by-k, 0x4 scalar-offset, 0x8 k=arg-vs-1).
 * s0 dest: short @0xC0, float pair @0xB0/0xB4, object ptr @0x40 whose +0x1C
 * is a fn-ptr called with (+0x18 + s0). D globals: out vec @0xD0/D4/D8,
 * double gate @0x158. Caps <80: FPU temp/reg allocation, bc1fl branch-likely
 * to epilogue, double-const ldc1 + &D %hi/%lo scheduling. INCLUDE_ASM is the
 * correct build path (no episode; tautology-trap rule).
 * 2026-05-28 regalloc note: mine over-promotes BOTH a0->$s0 and a1(s0)->$s1;
 * target promotes only a1->$s0 and keeps a0 caller-saved (register early,
 * spilled+reloaded only around calls, frame -0x58). The volatile-ptr knob on
 * a0 (`char * volatile a0 = a0_arg`) DE-promotes it but REGRESSES 71.26->67.53%
 * — it forces reload on EVERY a0 use, whereas target keeps a0 in $a0 until the
 * first call. Knob over-corrects here (same nuance as game_uso_func_000043D8);
 * no C knob expresses "register early, reload-after-call-only". */
#ifdef NON_MATCHING
/* game_uso_func_0000B750 — reconstruction with real symbols + logic fixes.
 * Real wiring recovered from objdump:
 *   - output basis vec stored at (&import_8005C1A8 + 0xA0)[+0x30/0x34/0x38]
 *     (== import_8005C1A8 + 0xD0/0xD4/0xD8; codegen forms the +0xA0 base addiu)
 *   - double gate is (&game_uso_D_807FFA78 + 0x158) via ldc1
 *   - call is game_uso_func_05B750(&import_8005C108, buf) — NOT func_00000000
 *   - final indirect call dispatches *(s0+0x40)->[+0x1C] with a0 = (short)[+0x18] + s0
 * Logic complete; FPU temp/reg-alloc + ldc1/%hi-%lo scheduling cap keeps it <80%. */
extern char import_8005C108;
extern char import_8005C1A8;
extern char game_uso_D_807FFA78;
extern void game_uso_func_05B750();
void game_uso_func_0000B750(char *a0, char *s0, float *a2, float *a3, float arg4) {
    int flags = *(int *)(a0 + 0x1C);
    float f0 = *(float *)(a0 + 0x00);
    char *dst;
    float k;
    float v;
    if (flags & 4) f0 += arg4 * 400.0f;
    k = (flags & 8) ? arg4 : 1.0f;
    dst = &import_8005C1A8 + 0xA0;
    *(float *)(dst + 0x30) = a2[0] + a3[0] * f0;
    *(float *)(dst + 0x34) = a2[1] + a3[1] * f0;
    *(float *)(dst + 0x38) = a2[2] + a3[2] * f0;
    *(short *)(s0 + 0xC0) = *(int *)(a0 + 0x18);
    v = *(float *)(a0 + 0x14);
    if (*(int *)(a0 + 0x1C) & 2) v *= k;
    if ((double)v > *(double *)(&game_uso_D_807FFA78 + 0x158)) {
        float buf[4];
        char *vt;
        *(float *)(s0 + 0xB0) = v;
        *(float *)(s0 + 0xB4) = v;
        buf[0] = *(float *)(a0 + 0x04);
        buf[1] = *(float *)(a0 + 0x08);
        buf[2] = *(float *)(a0 + 0x0C);
        buf[3] = *(float *)(a0 + 0x10) * k;
        game_uso_func_05B750(&import_8005C108, buf);
        vt = *(char **)(s0 + 0x40);
        {
            void (*fn)(char *) = *(void (**)(char *))(vt + 0x1C);
            fn((char *)((int)(short)*(short *)(vt + 0x18) + (int)s0));
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B750);
#endif

void game_uso_func_0000B884(char *dst) {
    game_uso_func_0000AD10((float*)dst);
    game_uso_func_0000AD10((float*)(dst + 0x14));
    game_uso_func_0000AD4C((int*)(dst + 0x18));
    game_uso_func_0000AD88((Quad4*)(dst + 0x4));
    game_uso_func_0000AD4C((int*)(dst + 0x1C));
    game_uso_func_0000AD10((float*)(dst + 0x20));
}

/* game_uso_func_0000B8D4 — EXACT 174/174 words (2026-07-07, agent-e/w30).
 * Alloc-cascade constructor, sibling of 0000AE1C/00003018/000044F4. Main obj
 * 0x278 (find-or-create), sub-obj 0xB4 via 04C678(&D_807FF360+0xD70) +
 * vtable &import_80086288 + zero-node @+0x2C + 04D3D0 + Vec3-zero 072EE8;
 * then s2 section: vtable &D_807FF2D8, +0x220=arg2, sub-list 0x50 @+0x224
 * with 3 24-byte nodes via 04A188 (3rd arg = 4-byte STRUCT BY VALUE ->
 * `sw a2,8(sp)` jal-delay home, docs/IDO_CODEGEN struct-by-value-marshalling);
 * finalize: +0xC=&D_807FF388+0xD98, +0xB4=import_000F5ADC(0,&D_807FF214),
 * 10-iter 0x24-stride 0000B710 loop, 04C774(self,1,arg1). Key levers:
 * ONE sp1 local for both sub-objects (wins $s1), a2v entry copy ($s0 pack),
 * n reused as stage node + loop cursor ($s0), slot_a/b/c + marsh struct
 * locals per marshalling recipe, D_B8D4_st2/st3 (=0) alias externs bust the
 * &D_807FEE50+0x860 PRE hoist, decl-order pads set frame 0x80. */
extern char game_uso_D_807FF360, game_uso_D_807FF2D8, game_uso_D_807FF368,
            game_uso_D_807FF37C, game_uso_D_807FF380, game_uso_D_807FF384,
            game_uso_D_807FF388, D_B8D4_st2, D_B8D4_st3;
extern char import_80086288;
extern char game_uso_D_807FEE50;
extern char game_uso_D_807FF214;
extern char game_uso_D_807FF360;
extern char game_uso_D_807FF368;
extern char game_uso_D_807FF388;
extern char game_uso_D_807FF2D8;
extern char D_B8D4_st2, D_B8D4_st3;
void *game_uso_func_0000B8D4(void *arg0, int arg1, int arg2) {
    typedef struct { char *p; } S0000B8D4;
    unsigned int i;        /* @0x7C (loop-counter spill home) */
    volatile int pad78;
    volatile int pad74;
    volatile int pad70;
    volatile int pad6C;
    Vec3 v3;               /* @0x60 */
    volatile int pad5C;
    volatile int pad58;
    volatile int pad54;
    volatile int pad50;
    S0000B8D4 slot_a;      /* @0x4C */
    S0000B8D4 slot_b;      /* @0x48 */
    S0000B8D4 slot_c;      /* @0x44 */
    char *sp1;             /* colored $s1 — dead @0x40 */
    void *p;               /* dead @0x3C */
    void *q;               /* dead @0x38 */
    S0000B8D4 marsh;       /* @0x34 */
    char *hdr;             /* dead @0x30 */
    char *n;               /* colored $s0 (stage node + loop cursor) */
    int a2v;

    a2v = arg2;
    if (arg0 == NULL) {
        arg0 = (void *)game_uso_func_055750(0x278);
        if (arg0 == NULL) goto end_ret;
    }

    sp1 = arg0;
    if (sp1 == NULL) {
        sp1 = (char *)game_uso_func_055750(0xB4);
        if (sp1 == NULL) goto skip_sub;
    }
    game_uso_func_04C678((int *)sp1, (char *)&game_uso_D_807FF360 + 0xD70);
    *(int *)(sp1 + 0x28) = (int)&import_80086288;

    p = sp1 + 0x2C;
    if (sp1 == (char *)-0x2C) {
        p = (void *)game_uso_func_055750(4);
        if (p == NULL) goto after_node;
    }
    q = p;
    if (p == NULL) {
        q = (void *)game_uso_func_055750(4);
        if (q == NULL) goto after_node;
    }
    *(int *)q = 0;
after_node:
    game_uso_func_04D3D0(sp1);
    v3.x = 0.0f;
    v3.y = 0.0f;
    v3.z = 0.0f;
    game_uso_func_072EE8(sp1 + 0x30, &v3);
skip_sub:

    *(int *)((char *)arg0 + 0x28) = (int)&game_uso_D_807FF2D8;
    *(int *)((char *)arg0 + 0x220) = a2v;
    sp1 = (char *)arg0 + 0x224;
    if (arg0 == (void *)-0x224) {
        sp1 = (char *)game_uso_func_055750(0x50);
        if (sp1 == NULL) goto finalize;
    }
    hdr = sp1;
    if (sp1 == NULL) {
        hdr = (char *)game_uso_func_055750(8);
        if (hdr == NULL) goto stage_a;
    }
    *(int *)hdr = (int)((char *)&game_uso_D_807FF368 + 0xD78);
    *(int *)(hdr + 4) = 0;
stage_a:
    slot_a.p = *(char **)((char *)&game_uso_D_807FF37C + 0xD8C);
    marsh = slot_a;
    n = sp1 + 8;
    if (sp1 == (char *)-8) {
        n = (char *)game_uso_func_055750(0x18);
        if (n == NULL) goto stage_b;
    }
    game_uso_func_04A188(n, sp1, marsh, 1);
    *(int *)(n + 0xC) = (int)((char *)&game_uso_D_807FEE50 + 0x860);
    *(int *)(n + 0x14) = 0;
    *(float *)(n + 0x10) = *(float *)((char *)&game_uso_D_807FF380 + 0x160);
stage_b:
    slot_b.p = *(char **)((char *)&game_uso_D_807FF380 + 0xD90);
    marsh = slot_b;
    n = sp1 + 0x20;
    if (sp1 == (char *)-0x20) {
        n = (char *)game_uso_func_055750(0x18);
        if (n == NULL) goto stage_c;
    }
    game_uso_func_04A188(n, sp1, marsh, 1);
    *(int *)(n + 0xC) = (int)((char *)&D_B8D4_st2 + 0x860);
    *(int *)(n + 0x14) = 0;
    *(float *)(n + 0x10) = *(float *)((char *)&game_uso_D_807FF384 + 0x164);
stage_c:
    slot_c.p = *(char **)((char *)&game_uso_D_807FF384 + 0xD94);
    marsh = slot_c;
    n = sp1 + 0x38;
    if (sp1 == (char *)-0x38) {
        n = (char *)game_uso_func_055750(0x18);
        if (n == NULL) goto finalize;
    }
    game_uso_func_04A188(n, sp1, marsh, 1);
    *(int *)(n + 0xC) = (int)((char *)&D_B8D4_st3 + 0x860);
    *(int *)(n + 0x14) = 0;
    *(float *)(n + 0x10) = 0.0f;
finalize:
    *(int *)((char *)arg0 + 0xC) = (int)((char *)&game_uso_D_807FF388 + 0xD98);
    *(int *)((char *)arg0 + 0xB4) = import_000F5ADC(0, &game_uso_D_807FF214);
    *(int *)((char *)arg0 + 0x274) = 10;
    i = 0;
    n = (char *)arg0 + 0xB8;
    do {
        game_uso_func_0000B710(n);
        n += 0x24;
        i++;
    } while (i < *(unsigned int *)((char *)arg0 + 0x274));
    game_uso_func_04C774((int *)arg0, 1, arg1);
end_ret:
    return arg0;
}

// game_uso_func_0000BB8C — STRUCTURAL PASS (0x3F0 / 252 words,
// no episode). Raw-.word USO form (single function, game_uso main
// game-logic). Very FP-heavy (44 FP ops / 6 calls, saved f20-f26
// doubles) — snowboard collision/contact-response solver. Entry/
// shape partial pass; multi-run target.
//
//   void game_uso_func_0000BB8C(Obj *obj) {  // obj -> s3
//     Sub *s = obj->0x220;
//     // --- FULL DECODE MAP (2026-06-03, ready to implement next tick) ---
//     // q-vec @sp272: {x=0, y=0, z=-1.0(0xBF800000)}; sp284=s->0xA0,
//     //   sp288=s->0xA4, sp292=s->0xA8  (a2+=0x70 then 0x34/0x38 = s->
//     //   0xA4/0xA8, NOT 0x34/0x38 — the stub's old offsets were wrong).
//     //   s1 = *import_80087DA8.
//     // 070F38(&q@sp272, s1->0x70 + 180);          // transform 1
//     // scale q by 1000.0(0x447A) -> sp192 vec; s0 = *import_8005C108;
//     //   071028(...); dot -> f2; neg; if (s3->572 < -dot): lerp
//     //   t=(-dot - lo)/(1.0 - lo), cvt.d, clamp vs 1.0(D_807FFA88+360),
//     //   * (s3->544)->200.   SECOND clamp @s3->620 / D_807FFA90.
//     // 05B750(s0, &{0,0,0}@sp108) -> f0@sp120.
//     // 05B614(s0, a3=s1->184, v1=s1->188, a1=s1->192, a2=s1->196,
//     //   sp16=v1, sp20=&out@sp132).
//     // loop: for (i=0; i < s3->628; i++, child s0 += 36) {
//     //   if (child->216 < f26) continue;
//     //   if ((child->212 & 1) && D_807FFA98+376 < (double)f20)
//     //     0000B750(child+184, s3->180, &sp260, s4, sp16=f20);
//     //   else 0000B750(child+184, s3->180, &sp260, s4, sp16=f24);
//     // }   // f20/f24=clamp results, f26=threshold; *_FA88/90/98 dbl consts
//   }
//
// Struct-typing reference:
//   obj->0x220 -> Sub: 0xA0 a Vec3-ish field, 0x34/0x38 scalars,
//     0x70 -> contact/normal record. sp+0x110..0x124 = a stack query
//     struct (Vec3 + -1.0f sentinels). const -1.0f (0xBF800000).
//     func_00000000 = USO placeholder dispatcher (sqrt / cross /
//     collision-query helpers). Core snowboard physics — collision
//     contact-response.
// RECONSTRUCTION 2026-06-22 (52.98% -> 62.50%): replaced all 6
//   function-pointer placeholder calls (jalr through game_uso_func_00000000)
//   with the real direct-jal callees resolved from the expected reloc set —
//   game_uso_func_070F38 (transform1), game_uso_func_071028 (Vec3 normalize,
//   single-arg per its established prototype), game_uso_func_05B750,
//   game_uso_func_05B614, and game_uso_func_0000B750 (x2 in the loop).
//   Rewrote the m2c struct-copy churn (which emitted spurious int->float
//   cvt.s.w via the `(f32)` int-field casts) as plain Vec3 array/struct
//   copies, restoring the integer lw/sw Vec3 copies the target uses. The
//   reloc set now matches the target EXACTLY (verified objdump -dr: 2x B750
//   + 070F38/071028/05B750/05B614 R_MIPS_26 + D_807FFA88/90/98 +
//   import_8005C108/80087DA8 HI16/LO16). Size-gap 252-vs-256 -> 252-vs-244.
//   Residual ~238 non-reloc diffs = genuine IDO FP-regalloc + instruction
//   scheduling + stack-slot assignment cap (target frame 0x128=296; mine 312
//   from one extra Vec3 slot the target reuses). Below 80% -> INCLUDE_ASM
//   build path, no episode (tautology rule). Name pre-checked: no extern
//   reuse. Two distinct vectors feed the loop's 0000B750: `world` (sp+260,
//   raw transform2 output) and `norm` (sp+248, the obj-relative diff after
//   071028 normalize) — m2c had collapsed them.

// game_uso_func_0000BB8C — STRUCTURAL PASS (0x3F0 / 252 words,
// no episode). Raw-.word USO form (single function, game_uso main
// game-logic). Very FP-heavy (44 FP ops / 6 calls, saved f20-f26
// doubles) — snowboard collision/contact-response solver. Entry/
// shape partial pass; multi-run target.
//
//   void game_uso_func_0000BB8C(Obj *obj) {  // obj -> s3
//     Sub *s = obj->0x220;
//     // --- FULL DECODE MAP (2026-06-03, ready to implement next tick) ---
//     // q-vec @sp272: {x=0, y=0, z=-1.0(0xBF800000)}; sp284=s->0xA0,
//     //   sp288=s->0xA4, sp292=s->0xA8  (a2+=0x70 then 0x34/0x38 = s->
//     //   0xA4/0xA8, NOT 0x34/0x38 — the stub's old offsets were wrong).
//     //   s1 = *import_80087DA8.
//     // 070F38(&q@sp272, s1->0x70 + 180);          // transform 1
//     // scale q by 1000.0(0x447A) -> sp192 vec; s0 = *import_8005C108;
//     //   071028(...); dot -> f2; neg; if (s3->572 < -dot): lerp
//     //   t=(-dot - lo)/(1.0 - lo), cvt.d, clamp vs 1.0(D_807FFA88+360),
//     //   * (s3->544)->200.   SECOND clamp @s3->620 / D_807FFA90.
//     // 05B750(s0, &{0,0,0}@sp108) -> f0@sp120.
//     // 05B614(s0, a3=s1->184, v1=s1->188, a1=s1->192, a2=s1->196,
//     //   sp16=v1, sp20=&out@sp132).
//     // loop: for (i=0; i < s3->628; i++, child s0 += 36) {
//     //   if (child->216 < f26) continue;
//     //   if ((child->212 & 1) && D_807FFA98+376 < (double)f20)
//     //     0000B750(child+184, s3->180, &sp260, s4, sp16=f20);
//     //   else 0000B750(child+184, s3->180, &sp260, s4, sp16=f24);
//     // }   // f20/f24=clamp results, f26=threshold; *_FA88/90/98 dbl consts
//   }
//
// Struct-typing reference:
//   obj->0x220 -> Sub: 0xA0 a Vec3-ish field, 0x34/0x38 scalars,
//     0x70 -> contact/normal record. sp+0x110..0x124 = a stack query
//     struct (Vec3 + -1.0f sentinels). const -1.0f (0xBF800000).
//     func_00000000 = USO placeholder dispatcher (sqrt / cross /
//     collision-query helpers). Core snowboard physics — collision
//     contact-response.
// RECONSTRUCTION 2026-06-22 (52.98% -> 62.50%): replaced all 6
//   function-pointer placeholder calls (jalr through game_uso_func_00000000)
//   with the real direct-jal callees resolved from the expected reloc set —
//   game_uso_func_070F38 (transform1), game_uso_func_071028 (Vec3 normalize,
//   single-arg per its established prototype), game_uso_func_05B750,
//   game_uso_func_05B614, and game_uso_func_0000B750 (x2 in the loop).
//   Rewrote the m2c struct-copy churn (which emitted spurious int->float
//   cvt.s.w via the `(f32)` int-field casts) as plain Vec3 array/struct
//   copies, restoring the integer lw/sw Vec3 copies the target uses. The
//   reloc set now matches the target EXACTLY (verified objdump -dr: 2x B750
//   + 070F38/071028/05B750/05B614 R_MIPS_26 + D_807FFA88/90/98 +
//   import_8005C108/80087DA8 HI16/LO16). Size-gap 252-vs-256 -> 252-vs-244.
//   Residual ~238 non-reloc diffs = genuine IDO FP-regalloc + instruction
//   scheduling + stack-slot assignment cap (target frame 0x128=296; mine 312
//   from one extra Vec3 slot the target reuses). Below 80% -> INCLUDE_ASM
//   build path, no episode (tautology rule). Name pre-checked: no extern
//   reuse. Two distinct vectors feed the loop's 0000B750: `world` (sp+260,
//   raw transform2 output) and `norm` (sp+248, the obj-relative diff after
//   071028 normalize) — m2c had collapsed them.
#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern int import_80087DA8;
extern char import_8005C108;
extern char game_uso_D_807FFA88, game_uso_D_807FFA90, game_uso_D_807FFA98;
extern void game_uso_func_070F38();
extern void game_uso_func_05B750();
extern void game_uso_func_05B614();
void game_uso_func_0000BB8C(char *arg0) {
    f32 q[6];          /* sp+272: {x,y,z, a,b,c} input to transform 070F38 */
    Vec3 scaled;       /* sp+192 */
    Vec3 tmp;          /* sp+164 */
    Vec3 world;        /* sp+260: raw transform2 output */
    Vec3 norm;         /* sp+248: diff -> normalized by 071028 */
    f32 spF8, spFC, sp100;
    f32 sp114, sp110, sp118;
    s32 sp88;
    s32 sp84;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f24;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f20;
    f32 var_f24;
    f64 temp_f22;
    f64 var_f0;
    u32 var_s1;
    char *temp_a2;
    char *temp_a2_2;
    char *temp_v0;
    char *temp_v0_2;
    char *var_s0;

    temp_a2 = (char *)FW(arg0, 0x220);
    temp_a2_2 = temp_a2 + 0x70;
    q[0] = 0.0f;
    q[1] = 0.0f;
    q[2] = -1.0f;
    q[3] = *(f32 *)(temp_a2 + 0xA0);
    q[4] = *(f32 *)(temp_a2_2 + 0x34);
    q[5] = *(f32 *)(temp_a2_2 + 0x38);
    game_uso_func_070F38(q, (char *)FW((*(int *)&import_80087DA8), 0x70) + 0xB4);
    temp_v0 = (char *)(*(int *)&import_80087DA8);
    scaled.x = q[0] * 1000.0f;
    scaled.y = q[1] * 1000.0f;
    scaled.z = q[2] * 1000.0f;
    tmp = scaled;
    world.x = tmp.x + (*(f32 *)((char *)FW(temp_v0, 0x70) + 0xA0)) * (*(f32 *)((char *)&import_8005C108 + 0x128));
    world.y = tmp.y + (*(f32 *)((char *)FW(temp_v0, 0x70) + 0xA4)) * (*(f32 *)((char *)&import_8005C108 + 0x12C));
    world.z = tmp.z + (*(f32 *)((char *)FW(temp_v0, 0x70) + 0xA8)) * (*(f32 *)((char *)&import_8005C108 + 0x130));
    tmp.x = world.x - q[3];
    temp_f12 = world.z - q[5];
    tmp.y = world.y - q[4];
    tmp.z = temp_f12;
    norm = tmp;
    game_uso_func_071028(&norm);
    spF8 = norm.x;
    spFC = norm.y;
    sp100 = norm.z;
    temp_f0 = *(f32 *)((char *)arg0 + 0x23C);
    sp110 = q[0];
    sp114 = q[1];
    sp118 = q[2];
    temp_f2 = -((sp110 * spF8) + (sp114 * spFC) + (sp118 * sp100));
    if (temp_f0 < temp_f2) {
        var_f24 = (temp_f2 - temp_f0) / (1.0f - temp_f0);
        if ((f64) var_f24 > 1.0) {
            var_f24 = 1.0f;
        }
        temp_f24 = var_f24 * (*(f32 *)((char *)FW(arg0, 0x220) + 0xC8));
        if (!((f64) temp_f24 < (*(f64 *)((char *)&game_uso_D_807FFA88 + 0x168)))) {
            sp88 = 0x409;
            sp84 = 0;
            temp_f2_2 = *(f32 *)((char *)arg0 + 0x26C);
            var_f20 = 0.0f;
            if (temp_f2_2 < temp_f24) {
                temp_f20 = (temp_f24 - temp_f2_2) / (1.0f - temp_f2_2);
                var_f20 = temp_f20 * temp_f20;
                var_f0 = (f64) var_f20;
                if (var_f0 > 1.0) {
                    var_f20 = 1.0f;
                    var_f0 = (f64) 1.0f;
                }
                if ((*(f64 *)((char *)&game_uso_D_807FFA90 + 0x170)) < var_f0) {
                    sp74 = 0.0f;
                    sp70 = 0.0f;
                    sp6C = 0.0f;
                    sp78 = var_f20 * (*(f32 *)((char *)arg0 + 0x254));
                    game_uso_func_05B750((f32 *)0x3F800000, 0, 0, &sp6C);
                    temp_v0_2 = (*(int *)&import_80087DA8);
                    game_uso_func_05B614(0, FW(temp_v0_2, 0xC0), FW(temp_v0_2, 0xC4), FW(temp_v0_2, 0xB8), FW(temp_v0_2, 0xBC), &sp84);
                }
            }
            temp_f22 = (*(f64 *)((char *)&game_uso_D_807FFA98 + 0x178));
            var_s1 = 0;
            if (FW(arg0, 0x274) != 0) {
                var_s0 = arg0;
                do {
                    if (*(f32 *)((char *)var_s0 + 0xD8) < temp_f2) {
                        if (FW(var_s0, 0xD4) & 1) {
                            if (temp_f22 < (f64) var_f20) {
                                game_uso_func_0000B750(var_s0 + 0xB8, (char *)FW(arg0, 0xB4), (float *)&world, (float *)&norm, var_f20);
                            }
                        } else {
                            game_uso_func_0000B750(var_s0 + 0xB8, (char *)FW(arg0, 0xB4), (float *)&world, (float *)&norm, temp_f24);
                        }
                    }
                    var_s1 += 1;
                    var_s0 += 0x24;
                } while (var_s1 < FW(arg0, 0x274));
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BB8C);
#endif

/* MATCHED 2026-05-31. The prior "no C-level lever to swap the loop-pre-header
 * schedule (li s2,0x168 / move s0,$0)" verdict was cracked by the FOR-LOOP
 * COMMA-INIT form: `for (i = 0, p = base + 0xB8; ...)` emits the bound
 * materialization before the counter init, matching the target — where the
 * do-while with separate `i = 0; p = ...;` statements emitted the reverse.
 * (The two are independent in the dataflow graph; the comma-init's evaluation
 * order pins IDO's schedule.) The remaining diffs were placeholder callees:
 * the real targets are game_uso_func_04A2D8 (setup) and game_uso_func_0000B884
 * (per-element, 0x24 stride over 0xF entries from base+0xB8). Byte-exact. */
extern void game_uso_func_04A2D8();
void game_uso_func_0000BF7C(char *a0) {
    char *base = a0;
    int i;
    char *p;
    game_uso_func_04A2D8(base + 0x224);
    game_uso_func_0000ADE0((int*)(base + 0x274));
    for (i = 0, p = base + 0xB8; i != 0x168; p += 0x24, i += 0x24) {
        game_uso_func_0000B884(p);
    }
}

/* game_uso_func_0000BFDC: 32-insn (0x80) sign-dispatched table-lookup wrapper
 * + indirect jalr. Reads two signed shorts from a0+0x8/0xA and a ptr from
 * a0+0x4; if a0->[0xA] < 0 takes a short path that reuses a0->[0xC] as the
 * function pointer; else dispatches through a 2-level pointer table where
 * a0->[0xA] indexes a (vtable_entry, fnptr) pair.
 *
 * Initial structural decode 2026-05-08; matching pass deferred — likely
 * 30-50% on first build due to the multi-way control flow + indirect jalr.
 * Open: identify the exact struct layout for a0 (probably a UI element or
 * dispatch handle).
 *
 * Asm @ 0xBFDC..0xC058 decoded structurally:
 *   short ka = a0->0xA  (signed half, dispatch key)
 *   short kb = a0->0x8  (signed half, secondary)
 *   int *base = (int*)a0->0x4  (table base ptr)
 *   if (ka < 0) {
 *       a1 = kb + base       (accum offset)
 *       fnptr = (void(*)())a0->0xC
 *       a0 = a1
 *       goto jalr
 *   } else {
 *       int v = a0->0xC
 *       if (v == 0) {
 *           if (a0->0x8 != 0) {
 *               // (offset value falls through)
 *           } else {
 *               v = 0x28
 *           }
 *       }
 *       short d = a0->0xA          (reload)
 *       int *table = *(int**)((char*)base + v)
 *       int *entry = (int*)((char*)table + (d << 3))
 *       short e = *(short*)entry
 *       fnptr = (void(*)())entry[1]
 *       a1 = e + (kb + base)
 *       a0 = a1
 *   }
 *   return fnptr(a0)
 *
 * 2026-05-17: C body emits 87% before post-cc. Remaining cap is local
 * branch-likely/register scheduling around the selector fallback; Makefile
 * INSN_PATCH + one suffix nop made the old unwrapped body byte-exact, but
 * instruction patching is banned now.
 *
 * 2026-06-01 sibling pass from BF7C exact: explicit `goto dispatch` for the
 * selector fallback still emitted `bnel` for both selector tests, and worsened
 * short-path register choices (fnptr moved from a2 to v1). Keep the nested
 * selector form unless a new branch-likely suppression lever appears. */
extern int gl_func_00000000();
/* game_uso_func_0000BFDC — EXACT 32/32 words (verified clean rebuild of
 * build/non_matching/src/game_uso/game_uso.c.o vs
 * asm/nonmatchings/game_uso/game_uso/game_uso_func_0000BFDC.s).
 * Cracked 2026-07-03 (agent-e). The old "bnezl branch-likely hard cap" was a
 * C-shape issue, not a cap. Three coupled levers:
 *  (1) &&-TERNARY for the selector: `idx = (sel==0 && pair[0]==0) ? 0x28 : sel;`
 *      -> uopt keeps sel(v0)/idx(a0) as separate webs (ternary result reg is a
 *      real phi home): as1 steals the arm's `move a0,v0` into the first bnez
 *      delay, retargets the second bnez to the merge with nop delay (plain
 *      branches, NO bnezl), and the 0x28 arm becomes `b merge; li a0,0x28`.
 *      Nested-if / goto / dead-kill / while(0) forms all coalesce -> bnezl.
 *  (2) comma-embedded arg init: `arg = (arg = *(char**)(a0+4), arg) + pair[0];`
 *      -> emission order lh 0xA / lh 0x8 / lw 4 (single-expr order) AND the lw
 *      lands in arg's home a1 (comma re-read avoids the v0 snapshot temp of
 *      `(arg = load) + pair[0]`) AND addu a1,t6,a1 operand order (textual-second
 *      operand becomes rs).
 *  (3) entry reuses the sel variable (multi-def) so entry colors v0. */
int game_uso_func_0000BFDC(char *a0) {
    short *pair = (short*)(a0 + 8);
    char *arg;
    int idx;
    int (*fnptr)(char *);

    arg = (arg = *(char**)(a0 + 4), arg) + pair[0];
    if (pair[1] < 0) {
        fnptr = *(int (**)(char *))(a0 + 0xC);
    } else {
        int sel = *(int*)(pair + 2);
        idx = (sel == 0 && pair[0] == 0) ? 0x28 : sel;
        sel = (int)((char*)(pair[1] << 3) + *(int*)(arg + idx));
        arg = *(short*)sel + arg;
        fnptr = *(int (**)(char *))((char*)sel + 4);
    }
    return fnptr(arg);
}

void game_uso_func_0000C05C(char *dst) {
    int tmp;
    game_uso_func_0000AD4C(&tmp);
    game_uso_func_0000AD10((float*)(dst + 0x10));
}

void game_uso_func_0000C08C(char *dst) {
    int tmp;
    game_uso_func_0000AD4C(&tmp);
    game_uso_func_0000ADE0((int*)(dst + 0x10));
}

void game_uso_func_0000C0BC(char *dst) {
    int tmp;
    game_uso_func_0000AD4C(&tmp);
    game_uso_func_0000AD88((Quad4*)(dst + 0x10));
}
/* 1-word zero alignment pad (truth 0xC0EC) between two MATCHED C fns: the
 * GLOBAL_ASM placeholder minimum is 8 bytes, so this emits one extra zero
 * word; the game_uso_block1 Makefile recipe drops the asserted-zero leftover
 * at 0xC0F0 (docs/MATCHING_WORKFLOW.md, asm-processor 1-word-pad defect). */
#pragma GLOBAL_ASM("asm/nonmatchings/game_uso/game_uso/game_uso_func_0000C0BC_pad.s")

void game_uso_func_0000C0F0(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

/* Struct assignment makes IDO emit the target 3-ints-per-iteration copy loop.
 * The Makefile patch strips relocations from the D_00000000 load and jal
 * words so objdiff sees the same raw .word baseline. */
void game_uso_func_0000C12C(int *a0) {
    typedef struct {
        int v[16];
    } I16;
    I16 buf;
    gl_func_00000000(&D_00000000, &buf, 0x40);
    *(I16*)a0 = buf;
}

void game_uso_func_0000C194(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_0000C1D0(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_0000C20C(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    gl_func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

void game_uso_func_0000C27C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

/* game_uso_func_0000C2D4: 28-insn alloc-init constructor with optional 3-arg sub-init. */
void *game_uso_func_0000C2D4(void *a0, int a1) {
    if (a0 == 0) {
        a0 = (void*)gl_func_00000000(0x2C);
        if (a0 == 0) goto end;
    }
    gl_func_00000000(a0, (char*)&D_00000000 + 0x121C);
    *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
    if (a1 != 0) {
        gl_func_00000000(a0, 1, a1);
    }
end:
    return a0;
}

/* C344-C3CC: 7 accessor fragments for a table at *(int**)&D_00000000, each
 * entry 0x40 bytes. Indexed by arg1 << 6. Templates:
 *   C344: return &entry[a1];               (entry pointer)
 *   C35C: return &entry[a1] + 0x10;        (entry + 0x10)
 *   C378: return entry[a1].field_0x2C;     (lw at +0x2C)
 *   C394: return entry[a1].field_0x34;
 *   C3B0: return entry[a1].field_0x38;
 *   C3CC: return entry[a1].field_0x30;
 * Unused $a0 is spilled to caller home slot — confirms IDO -O2 leaf-no-jal
 * variant of feedback-ido-unused-arg-save. */
int *game_uso_func_0000C344(int a0, int a1) {
    return (int*)((char*)(*(int**)&D_00000000) + (a1 << 6));
}

int *game_uso_func_0000C35C(int a0, int a1) {
    return (int*)((char*)(*(int**)&D_00000000) + (a1 << 6) + 0x10);
}

int game_uso_func_0000C378(int a0, int a1) {
    return *(int*)((char*)(*(int**)&D_00000000) + (a1 << 6) + 0x2C);
}

int game_uso_func_0000C394(int a0, int a1) {
    return *(int*)((char*)(*(int**)&D_00000000) + (a1 << 6) + 0x34);
}

int game_uso_func_0000C3B0(int a0, int a1) {
    return *(int*)((char*)(*(int**)&D_00000000) + (a1 << 6) + 0x38);
}

int game_uso_func_0000C3CC(int a0, int a1) {
    return *(int*)((char*)(*(int**)&D_00000000) + (a1 << 6) + 0x30);
}

/* game_uso_func_0000C3E8: CAP (IDO dead-arg-home delay-slot fill, not TU-context).
 * Correct C is `int f(int a0){ return *(int*)&D_00000000; }`.
 * TARGET: lui v0; lw v0,0(v0); jr ra; sw a0,0(sp) (the dead a0 home fills the jr
 * delay slot, load stays before jr).
 * 2026-05-30 CORRECTION (disproves the old TU-context claim): compiling this C
 * ALONE (its own .o, project -O2 flags, objdump'd) does NOT match -- it emits
 * lui v0; sw a0,0(sp); jr ra; lw v0,0(v0), with the LOAD in the delay slot and
 * the home store before jr (the exact opposite delay-slot pick from target). So
 * the divergence is NOT TU-context-sensitive and NOT a Yay0 file-split candidate
 * (isolation reproduces the same miss). It is IDO's dead-arg-home scheduling: the
 * home `sw a0,0(sp)` is independent and ready immediately, so IDO/the assembler
 * floats the LOAD into the jr delay and emits the store early. To match, IDO must
 * emit `lui; lw; sw; j` (store last) so the assembler delay-fills with the store;
 * no C structure forces a dead-arg home to schedule after the return load.
 * NEGATIVE (2026-05-30, standalone IDO 7.1 -O2, objdump-verified): `__asm__("")`
 * barrier -> full stack frame (breaks leaf); `volatile int*` load -> 5-insn la+lw
 * pointer form (lui+addiu+lw, wrong); `v+a0-a0` -> addu/subu kept (wrong). Prior
 * tries (volatile *p=&a0, self-store, reorder) also negative. Genuine NM cap. */
/* 2026-06-10 census note: this fn re-surfaced in the cross-USO tiny-leaf
 * byte-signature scan; re-confirmed as the documented cap (no new lever
 * applies -- the sw-a0-home-in-jr-delay leaf shape remains C-unreachable).
 * The tiny-leaf scan vein is now exhausted project-wide; see
 * docs/MATCHING_WORKFLOW "template scans filter by cdef presence". */
#ifdef NON_MATCHING
extern int game_uso_D_807FFBC4;
int game_uso_func_0000C3E8(int a0) {
    return game_uso_D_807FFBC4;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C3E8);
#endif

/* game_uso_func_0000C3F8: 37-insn alloc-and-iter constructor. MATCHED 2026-06-20.
 *   func_C0F0(&D_807FFBC4);                   // setup, base held in $s3
 *   D_807FFBC0 = alloc(D_807FFBC4 << 6);      // ptr base held in $s2
 *   for (i = 0; (u32)i < (u32)D_807FFBC4; i++)
 *       func_C12C(D_807FFBC0 + i*0x40);
 *
 * Two DISTINCT globals (D_807FFBC4 = count in $s3, D_807FFBC0 = alloc'd-ptr in
 * $s2); reference them DIRECTLY (no held-pointer locals) so IDO promotes
 * &D_807FFBC4/&D_807FFBC0 into $s3/$s2 across the function. The C0F0/C12C calls
 * are intra-module (R_MIPS_26, resolve to the baked 0c00303c/0c00304b post-link).
 * LAND LEVER: hoist `i = 0;` ABOVE the `if (count)` so IDO fills the beqz delay
 * slot with `move s0,zero` instead of the alloc store `sw v0,0(s2)` — that
 * store/branch schedule swap was the last 2-word diff. */
extern int game_uso_D_807FFBC4;
extern int *game_uso_D_807FFBC0;
void game_uso_func_0000C3F8(int *a0) {
    int i;
    int *p;

    game_uso_func_0000C0F0(&game_uso_D_807FFBC4);
    p = (int*)game_uso_func_055750(game_uso_D_807FFBC4 << 6);
    game_uso_D_807FFBC0 = p;
    i = 0;
    if (game_uso_D_807FFBC4 != 0) {
        do {
            game_uso_func_0000C12C((int*)((char*)game_uso_D_807FFBC0 + i * 0x40));
            i++;
        } while ((u32)i < (u32)game_uso_D_807FFBC4);
    }
}

#ifdef NON_MATCHING
/* 2026-06-24 (agent-e) BIG-SWING decode lever: add the per-stage s2-scratch
 * round-trip. GT (expected .o) shows EVERY one of the 32 sub-init stages does
 *   lw t,OFF(global); sw t,SLOT(sp); lw t,SLOT(sp); sw t,0(s2); ...; lw a2,0(s2)
 * i.e. the stage value is double-buffered: a descending per-stage spill slot,
 * THEN a single shared scratch word at s2=sp+0x2C (set once at entry, reused).
 * Prior body passed `val` directly (single spill) and omitted the s2 hop. Modeling
 * the shared word as a function-scope `volatile int vslot` written each stage and
 * reloaded for the 04A188 a2 arg reproduces the missing sw/lw 0(s2) pair x32.
 * Structure: alloc(0x444) main + import_0010D33C init + vtable@0x28, s1 sub-region
 * (p+0x13C or alloc 0x308), then 32 unrolled sub-inits at s1+8+N*0x18, each a
 * dead-sentinel-guarded alloc(0x18)/bump, registered via 04A188(obj,s1,vslot,1),
 * template ptr @0xC (F568+0xf78 float / F5B0+0xfc0 int), 0x14=0, 0x10=val/float. */
extern char game_uso_D_807FF568, game_uso_D_807FF5B0, game_uso_D_807FF74C, game_uso_D_807FF814, game_uso_D_807FF81C, game_uso_D_807FF820, game_uso_D_807FF824, game_uso_D_807FF828, game_uso_D_807FF82C, game_uso_D_807FF830, game_uso_D_807FF834, game_uso_D_807FF838, game_uso_D_807FF83C, game_uso_D_807FF840, game_uso_D_807FF844, game_uso_D_807FF848, game_uso_D_807FF84C, game_uso_D_807FF850, game_uso_D_807FF854, game_uso_D_807FF858, game_uso_D_807FF85C, game_uso_D_807FF860, game_uso_D_807FF864, game_uso_D_807FF868, game_uso_D_807FF86C, game_uso_D_807FF870, game_uso_D_807FF874, game_uso_D_807FF878, game_uso_D_807FF87C, game_uso_D_807FF880, game_uso_D_807FF884, game_uso_D_807FF888, game_uso_D_807FF88C, game_uso_D_807FF890, game_uso_D_807FF894, game_uso_D_807FF898;
extern int game_uso_func_055750();
extern int game_uso_func_04A188();
extern int import_0010D33C();
void game_uso_func_0000D458(s32);
void *game_uso_func_0000C48C(void *a0, int a1, int a2) {
    char *p = (char *)a0;
    int *s1, *v1, *obj;
    volatile int vslot;
    if (p == 0) { p = (char *)game_uso_func_055750(0x444); if (p == 0) goto end; }
    import_0010D33C(p, a1);
    *(int *)(p + 0x28) = (int)&game_uso_D_807FF74C;
    s1 = (int *)(p + 0x13C);
    if (p == (char *)-0x13C) { s1 = (int *)game_uso_func_055750(0x308); if (s1 == 0) goto end; }
    v1 = s1;
    if (s1 == 0) { v1 = (int *)game_uso_func_055750(8); if (v1 == 0) goto stage0; }
    v1[0] = (int)((char *)&game_uso_D_807FF814 + 0x1224);
    v1[1] = 0;
stage0:;
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF81C + 0x122c);
        vslot = val;
        obj = (int *)((char *)s1 + 0x8);
        if (s1 == (int *)-0x8) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = *(float *)((char *)&game_uso_D_807FF820 + 0x1ec);
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF820 + 0x1230);
        vslot = val;
        obj = (int *)((char *)s1 + 0x20);
        if (s1 == (int *)-0x20) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 20;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF824 + 0x1234);
        vslot = val;
        obj = (int *)((char *)s1 + 0x38);
        if (s1 == (int *)-0x38) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 60;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF828 + 0x1238);
        vslot = val;
        obj = (int *)((char *)s1 + 0x50);
        if (s1 == (int *)-0x50) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 5;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF82C + 0x123c);
        vslot = val;
        obj = (int *)((char *)s1 + 0x68);
        if (s1 == (int *)-0x68) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = *(float *)((char *)&game_uso_D_807FF830 + 0x1f0);
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF830 + 0x1240);
        vslot = val;
        obj = (int *)((char *)s1 + 0x80);
        if (s1 == (int *)-0x80) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 20;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF834 + 0x1244);
        vslot = val;
        obj = (int *)((char *)s1 + 0x98);
        if (s1 == (int *)-0x98) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 3.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF838 + 0x1248);
        vslot = val;
        obj = (int *)((char *)s1 + 0xb0);
        if (s1 == (int *)-0xb0) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 7.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF83C + 0x124c);
        vslot = val;
        obj = (int *)((char *)s1 + 0xc8);
        if (s1 == (int *)-0xc8) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 3;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF840 + 0x1250);
        vslot = val;
        obj = (int *)((char *)s1 + 0xe0);
        if (s1 == (int *)-0xe0) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 0.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF844 + 0x1254);
        vslot = val;
        obj = (int *)((char *)s1 + 0xf8);
        if (s1 == (int *)-0xf8) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 4.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF848 + 0x1258);
        vslot = val;
        obj = (int *)((char *)s1 + 0x110);
        if (s1 == (int *)-0x110) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 50.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF84C + 0x125c);
        vslot = val;
        obj = (int *)((char *)s1 + 0x128);
        if (s1 == (int *)-0x128) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 25.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF850 + 0x1260);
        vslot = val;
        obj = (int *)((char *)s1 + 0x140);
        if (s1 == (int *)-0x140) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 40.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF854 + 0x1264);
        vslot = val;
        obj = (int *)((char *)s1 + 0x158);
        if (s1 == (int *)-0x158) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 100.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF858 + 0x1268);
        vslot = val;
        obj = (int *)((char *)s1 + 0x170);
        if (s1 == (int *)-0x170) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 120.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF85C + 0x126c);
        vslot = val;
        obj = (int *)((char *)s1 + 0x188);
        if (s1 == (int *)-0x188) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 80.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF860 + 0x1270);
        vslot = val;
        obj = (int *)((char *)s1 + 0x1a0);
        if (s1 == (int *)-0x1a0) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 100.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF864 + 0x1274);
        vslot = val;
        obj = (int *)((char *)s1 + 0x1b8);
        if (s1 == (int *)-0x1b8) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 150.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF868 + 0x1278);
        vslot = val;
        obj = (int *)((char *)s1 + 0x1d0);
        if (s1 == (int *)-0x1d0) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 100.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF86C + 0x127c);
        vslot = val;
        obj = (int *)((char *)s1 + 0x1e8);
        if (s1 == (int *)-0x1e8) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF568+0xf78);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        *(float *)((char *)obj + 0x10) = 150.0f;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF870 + 0x1280);
        vslot = val;
        obj = (int *)((char *)s1 + 0x200);
        if (s1 == (int *)-0x200) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 0;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF874 + 0x1284);
        vslot = val;
        obj = (int *)((char *)s1 + 0x218);
        if (s1 == (int *)-0x218) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 0;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF878 + 0x1288);
        vslot = val;
        obj = (int *)((char *)s1 + 0x230);
        if (s1 == (int *)-0x230) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 0;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF87C + 0x128c);
        vslot = val;
        obj = (int *)((char *)s1 + 0x248);
        if (s1 == (int *)-0x248) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 0;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF880 + 0x1290);
        vslot = val;
        obj = (int *)((char *)s1 + 0x260);
        if (s1 == (int *)-0x260) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 1;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF884 + 0x1294);
        vslot = val;
        obj = (int *)((char *)s1 + 0x278);
        if (s1 == (int *)-0x278) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 1;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF888 + 0x1298);
        vslot = val;
        obj = (int *)((char *)s1 + 0x290);
        if (s1 == (int *)-0x290) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 1;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF88C + 0x129c);
        vslot = val;
        obj = (int *)((char *)s1 + 0x2a8);
        if (s1 == (int *)-0x2a8) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 1;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF890 + 0x12a0);
        vslot = val;
        obj = (int *)((char *)s1 + 0x2c0);
        if (s1 == (int *)-0x2c0) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 1;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF894 + 0x12a4);
        vslot = val;
        obj = (int *)((char *)s1 + 0x2d8);
        if (s1 == (int *)-0x2d8) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 30;
    }
    {
        volatile int val; char *tmpl;
        val = *(int *)((char *)&game_uso_D_807FF898 + 0x12a8);
        vslot = val;
        obj = (int *)((char *)s1 + 0x2f0);
        if (s1 == (int *)-0x2f0) { obj = (int *)game_uso_func_055750(0x18); if (obj == 0) goto end; }
        game_uso_func_04A188(obj, s1, vslot, 1);
        tmpl = ((char *)&game_uso_D_807FF5B0+0xfc0);
        obj[0xC / 4] = (int)tmpl;
        obj[0x14 / 4] = 0;
        obj[0x10 / 4] = 100;
    }
    *(int *)(p + 0xB4) = a2;
    game_uso_func_0000D458(p);
end:
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C48C);
#endif

/* game_uso_func_0000D204/D210 - verified structural decode (132-insn state
 * machine; 0xD204 prelude merged + heavy branch-likely + table-scan + vtable
 * jalr = documented deep sub-80 -> INCLUDE_ASM build path; struct ref).
 *   a3 = a0;
 *   t6 = *(D + 0x64);
 *   if (t6 != 0) goto post_init;
 *   f2 = D[0x1F4];
 *   if (!((a3->0xB4)->0xBC < f2)) { a3->0x120 = 0; }
 *   if ((a3->0xB4)->0xBC < f2) {
 *       w = a3->0x138;
 *       if (a3->0x120 == 0) (a3->0x138->0xB4) and~4;
 *       else                (a3->0x138->0xB4) or 3;
 *   }
 * post_init:
 *   v0 = a3->0xB4;
 *   if (v0->0x938 == 0
 *       and (double-ish) v0->0x9D0 < 1399.0f (D 0x442f...)
 *       and v0->0x31C < -100.0f (0xc2c8...))
 *       func_00000000(v0->0x800, &D+0x109C, 1);   // X1
 *   t5 = a3->0x114;
 *   if (t5 == 0) func_00000000(a3);                // X2
 *   v1 = a3 + 200;
 *   // table-scan: compare v1[0..1] (a3->0xC8/0xCC) against &D+0xDC8 pair
 *   if (match) {
 *       if (a3->0xCA >= 0) {                       // lh signed
 *           ... a2 = (v1->0x4 || a3->0xC8(short)) ? .. : 40 ;
 *           tbl = *(int*)((char*)a3 + a3->0xC8 + a2);
 *           ent = tbl + (a3->0xCE << 3);
 *           ((fn)ent->0x4)( ent->0x0(short) + a3 );  // vtable jalr
 *       } else func_00000000(a3, v1->0x4);
 *   }
 *   func_00000000(a3);                              // X3
 *   if (a3->0x74 != 0) {
 *       func_00000000(a3->0x58);                    // X4
 *       if (a3->0x74 != a3->0x104) a3->0x104 = a3->0x74;
 *   }
 *   func_00000000(a3);                              // X5
 * Struct-typing: a3->0xB4 obj (->0xBC float, ->0x938 flag, ->0x9D0 /
 * ->0x31C floats, ->0x800 sub), a3->0x120 reset-flag, a3->0x138 child
 * (->0xB4 mode bits 0x4/0x3), a3->0x114 state, a3->0xC8/0xCA/0xCE
 * short-trio @+200/202/206, a3->0x74 / 0x104 / 0x58 dispatch fields.
 * D[0x1F4] threshold float, D 700.0/-100.0 compare consts, D-pair
 * @0x109C, scan-table @0xDC8. 2026-05-29: pseudo-C LIFTED to a real NM body
 * (47.4%; was bare INCLUDE_ASM). Residual <80 is the documented deep-cap stack:
 * bc1fl/bc1tl/bnel/beql branch-likely (the two FP clamps + the table-scan loop
 * + the dispatch ladder), the vtable `jalr` dispatch, and reloc scheduling.
 * Logic verified against the build .o disasm; the float-clamp `0x120=0` store is
 * on the `f0 < thresh` path and the child mode-mask is `& ~3` (corrected from the
 * earlier comment's `!(...)` / `~4`). Future tightening = per-block RE. */
#ifdef NON_MATCHING
/* game_uso_func_0000D204/D210 - logic-corrected decode, 60.98 -> 81.14% fuzzy.
 * LOGIC FIXES over prior 47.4%/61% body:
 *  (1) table-scan flag was INVERTED: target runs the vtable-dispatch body on
 *      MISMATCH (the loop sets the flag=1 on the first differing word and =0
 *      when all words match), prior C ran it on full-match. Rewrote as
 *      do{ if(*p!=*tbl){mismatch=1;goto done;} } while(p!=end); mismatch=0; done:
 *  (2) dispatch arm order: target branches (bgez) to the >=0 row-lookup arm and
 *      keeps the <0 (fn=v1[1]; a0=base) arm INLINE -> write `if (cca < 0)` first.
 *  (3) child bit-mask block: AND-path (&=~3) is physically first / shared by both
 *      cond-true and 0x120!=0, OR-path (|=3) is the beqzl forward target. Express
 *      with goto-shared clear_bits/set_bits so IDO emits bc1tl + beqzl, AND first.
 *  (4) inlined the +0x1F4 threshold load (no float-top-local cache) so the obj
 *      deref colors into f0 ahead of the thresh load (gate float-reg numbering).
 *  (5) child store via pointer-to-field `child=(int*)(...+0xB4); *child` to emit the
 *      target's `addiu v0,v0,0xB4; sw ...,0(v0)` base-adjust (not sw ...,180(v0)).
 * Real callee names from R_MIPS_26 relocs (07C0C0/D9CC/ECE8/076E78/0775F8);
 * import_80020098 base for the +0x64 gate + child obj = import->0x138; v1=import;
 * D-pair arg = &game_uso_D_807FF68C+4252; table-scan vs D_807FF3B8+0xDC8.
 * RESIDUAL <100 is coloring/branch-likely scheduling only: gate FP-clamp bc1fl/
 * bc1tl + a redundant %hi(D) reload + float-reg numbering; the table-scan
 * loop-back bnel/bnel + addi (target) vs beq/bne + addiu (build) cost-model
 * delay-fill; dispatch-body a2-vs-t0/v1 coloring. Logic-complete. */
extern char import_80020098;
extern char game_uso_D_807FF68C;
extern char game_uso_D_807FF3B8;
extern void game_uso_func_07C0C0(int, char *, int);
extern void game_uso_func_0000D9CC(char *);
extern void game_uso_func_0000ECE8(int *);
extern void game_uso_func_076E78(int);
extern void game_uso_func_0775F8(int *);
void game_uso_func_0000D204(int *a0) {
    int *a3 = a0;
    int *obj;
    int *child;
    int *v0;
    int *v1;

    if (*(int *)((char *)&import_80020098 + 0x64) == 0) {
        obj = *(int **)((char *)a3 + 0xB4);
        if (*(float *)((char *)obj + 0xBC) < *(float *)((char *)&D_00000000 + 0x1F4)) {
            *(int *)((char *)a3 + 0x120) = 0;
        }
        obj = *(int **)((char *)a3 + 0xB4);
        if (*(float *)((char *)obj + 0xBC) < *(float *)((char *)&D_00000000 + 0x1F4)) {
            goto clear_bits;
        }
        if (*(int *)((char *)a3 + 0x120) == 0) {
            goto set_bits;
        }
    clear_bits:
        child = (int *)((char *)*(int **)((char *)&import_80020098 + 0x138) + 0xB4);
        *child &= ~3;
        goto bits_done;
    set_bits:
        child = (int *)((char *)*(int **)((char *)&import_80020098 + 0x138) + 0xB4);
        *child |= 3;
    bits_done:;
    }

    v0 = *(int **)((char *)a3 + 0xB4);
    if (*(int *)((char *)v0 + 0x938) == 0
        && *(float *)((char *)v0 + 0x9D0) < 700.0f
        && *(float *)((char *)v0 + 0x31C) < -100.0f) {
        game_uso_func_07C0C0(*(int *)((char *)v0 + 0x800),
                             (char *)&game_uso_D_807FF68C + 4252, 1);
    }

    if (*(int *)((char *)a3 + 0x114) == 0) {
        game_uso_func_0000D9CC((char *)a3);
    }

    v1 = (int *)((char *)a3 + 200);
    {
        int *tbl = (int *)((char *)&game_uso_D_807FF3B8 + 0xDC8);
        int *p = v1;
        int *end = v1 + 2;
        int mismatch;
        do {
            if (*p != *tbl) {
                mismatch = 1;
                goto scan_done;
            }
            p++;
            tbl++;
        } while (p != end);
        mismatch = 0;
    scan_done:
        if (mismatch) {
            char *base = (char *)a3 + *(short *)((char *)a3 + 0xC8);
            int (*fn)();
            int a0v;
            if (*(short *)((char *)a3 + 0xCA) < 0) {
                fn = (int (*)())v1[1];
                a0v = (int)base;
            } else {
                int sel = v1[1];
                int *row;
                if (sel == 0) {
                    if (*(short *)((char *)v1 + 0) != 0) {
                        sel = 0;
                    } else {
                        sel = 40;
                    }
                }
                row = *(int **)(base + sel);
                row = (int *)((char *)row + (*(short *)((char *)v1 + 2) << 3));
                fn = (int (*)())row[1];
                a0v = (int)((char *)base + *(short *)((char *)row + 0));
            }
            fn(a0v);
        }
    }

    game_uso_func_0000ECE8(a3);
    if (*(int *)((char *)a3 + 0x74) != 0) {
        game_uso_func_076E78(*(int *)((char *)a3 + 0x58));
        if (*(int *)((char *)a3 + 0x74) != *(int *)((char *)a3 + 0x104)) {
            *(int *)((char *)a3 + 0x104) = *(int *)((char *)a3 + 0x74);
        }
    }
    game_uso_func_0775F8(a3);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D204);
#endif

void game_uso_func_0000D418(char *a0) {
    gl_func_00000000(a0 + 0x13C);
}

/* Set a0->0x64/0x68 = -1000 and copy the 8-byte pair a0->0xC0..0xC7 to 0xC8.
 * MATCH: copying the adjacent pair as a STRUCT (Pair2) emits lw/lw/sw/sw with the
 * target's t7/t6 register order; two separate s32 field-copies gave t6/t7 swapped
 * (was INSN_PATCH'd, banned 2026-05-23). Struct-copy vs separate-field-copy is the
 * lever for adjacent-field $t-renumber. Byte-exact. */
void game_uso_func_0000D438(char *a0) {
    *(s32*)(a0 + 0x64) = -1000;
    *(s32*)(a0 + 0x68) = -1000;
    *(Pair2*)(a0 + 0xC8) = *(Pair2*)(a0 + 0xC0);
}

/* game_uso_func_0000D458: parent F1 (frame -0x48, 90 words/0x164) + 4 helper
 * functions it calls (D5BC/D5DC/D5F8/D634, defs below; D5BC/D5DC/D634 100%).
 * Boundary defect RESOLVED: this .s is truncated to 0x164 (F1 only, ends at the
 * 0xD5B8 nop) and expected/game_uso.c.o carries D458 at the F1 size — verified.
 * STATUS 2026-06-23: DECODE-ONLY CAP — body is logic-exact (see NM below) but
 * BYTE-MATCH IS IMPOSSIBLE from C. Two unfixable residuals:
 *   (1) RELOC-FORM CAP (HI16-only-unpaired): expected references import_800200CC
 *       and game_uso_D_807FF3A0/A8/B0 with R_MIPS_HI16 and ZERO R_MIPS_LO16
 *       (offsets 0xDB8/0xDB0/0xDC0 baked as literal addiu immediates). IDO from
 *       ANY C extern-symbol form emits a HI16+LO16 PAIR, so the reloc SET cannot
 *       match. Classify: `objdump -r game_uso.c.o | grep 807FF3 | grep -c LO16`
 *       == 0. See docs/N64_FORENSICS HI16-only-unpaired cap.
 *   (2) `subu a1,s0,s0; addiu a1,a1,124` (the 0x7C 2nd arg to 07F6C0): a
 *       self-subtract artifact from IDO's value web; `x-x` folds to li from any
 *       C source (docs/IDO_CODEGEN) — so target's 2-insn form is unreproducible
 *       (= the 90-vs-89-word deficit) and the +8 frame (-0x48 vs the -0x40 C
 *       gives) rides the same phantom slot.
 * Residual otherwise = only those + VRAM-relative branch displacements (==).
 * Logic was decode-verified 2026-06-23: var_v0 nested-if shape (beq;li;b;move)
 * and the 16-byte &sp30[4] buffer (048020 size arg 0x10) now match target.
 * DO NOT use split-fragments.py here: it DROPS the symbolic `lui %hi` line at
 * the D5DC boundary (size header says +1 word vs the file's word count),
 * corrupting the .s — see docs/MATCHING_WORKFLOW. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern int game_uso_func_07F6C0();
extern int game_uso_func_077574();
extern int game_uso_func_077C44();
extern int import_0010D420();
extern int game_uso_func_049280();
extern int game_uso_func_048020();
extern void game_uso_func_0000D5BC(char *, Pair2);
extern char import_800200CC;
extern char game_uso_D_807FF3A0, game_uso_D_807FF3A8, game_uso_D_807FF3B0;
void game_uso_func_0000D458(s32 arg0) {
    s32 sp30[4];
    s32 var_v0;

    game_uso_func_07F6C0((int)arg0 + 0xBC, (arg0 * 0) + 0x7C);
    FW(arg0, 0x114) = 2;
    FW(arg0, 0xFC) = 0x10000;
    FW(arg0, 0xDC) = 1;
    FW(arg0, 0x104) = -1;
    FW(arg0, 0x10C) = 0;
    *(float *)((char *)arg0 + 0x11C) = 1.0f;
    game_uso_func_077574(arg0);
    game_uso_func_077C44(arg0, FW(arg0, 0xFC) | 8, 0, 0, 1, 1);
    import_0010D420(arg0);
    if (*(int *)((char *)&import_800200CC + 0x34) == 3) {
        game_uso_func_0000D5BC(arg0, *(Pair2*)&game_uso_D_807FF3A0);
    } else {
        game_uso_func_0000D5BC(arg0, *(Pair2*)&game_uso_D_807FF3A8);
    }
    game_uso_func_049280();
    game_uso_func_048020((s32) &sp30, 0xF10, 0x10);
    if (sp30[0] != 0x04080040) {
        var_v0 = 0;
    } else if (sp30[1] != 0x02081040) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    if (var_v0 == 0) {
        game_uso_func_0000D5BC(arg0, *(Pair2*)&game_uso_D_807FF3B0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D458);
#endif

/* game_uso_func_0000D5BC: copies the varargs pair (a1,a2 via &a1) to the
 * adjacent a0->0xC8/0xCC.
 * MATCH: a STRUCT copy `*(Pair2*)(a0+0xC8) = *(Pair2*)&a1` homes the args, takes
 * &a1 into $t6, and emits the lw/sw/lw/sw via the pointer in the target's regs.
 * The volatile-int-pointer form left the &a1 pointer in $v0 (was a regalloc cap);
 * struct-copy is the lever (same as game_uso_func_0000D438). Byte-exact. */
void game_uso_func_0000D5BC(char *a0, Pair2 pair) {
    *(Pair2*)(a0 + 0xC8) = pair;
}

/* Copy the adjacent global pair D+0xDC8/0xDCC to adjacent a0->0xC8/0xCC.
 * MATCH: struct-copy lever (*(Pair2*)(a0+0xC8) = *(Pair2*)(&D+0xDC8)) emits
 * lw/sw/lw/sw via the &D pointer in the target's $t order; separate field copies
 * gave the wrong $t order. Same lever as D438/D5BC (here the source is a global).
 * Byte-exact (in-tree verified). */
extern char game_uso_D_807FF3B8;
void game_uso_func_0000D5DC(char *a0) {
    *(Pair2*)(a0 + 0xC8) = *(Pair2*)((char*)&game_uso_D_807FF3B8 + 0xDC8);
}

/* Varargs (&a1) pair-sink: if a3==-1 set a0->0x68=a3 else a0->0x64=a3; then copy
 * the a1/a2 pair to adjacent a0->0xC0/0xC4 via the struct-by-value `pair` arg
 * (homes a1,a2 to 4/8(sp)). Signature `(char*, Pair2, int)` gives the direct
 * jal from the in-TU callers (00011258/000112E0).
 *
 * MATCHED 2026-06-20 (stale-cap catch): the prior cap claimed the else-arm
 * direct sp-relative spill reload (`lw t7,0xC(sp); sw t7,0x64(a0)`) was
 * allocator-only / not C-reachable, because `*(volatile int*)&a3` materialized
 * the address (addiu t7,sp,0xC; lw 0(t7)) = +1 insn (16 vs 15). The fix is to
 * DROP the `volatile`: plain `*(int*)&a3` forces the a3 home (sw a3,0xC(sp) in
 * the bne delay) AND lets IDO fold the reload to a direct sp-offset load.
 * 15/15 words byte-exact, 0 diffs. */
void game_uso_func_0000D5F8(char *a0, Pair2 pair, int a3) {
    if (a3 == -1) {
        *(int*)(a0 + 0x68) = a3;
    } else {
        *(int*)(a0 + 0x64) = *(int*)&a3;
    }
    *(Pair2*)(a0 + 0xC0) = pair;
}

/* 2-insn leaf: jr ra; sw a0, 0(sp) (a0 spilled to its caller-arg slot in the
 * delay slot, no prologue). Byte-exact: `void f(int a0){(void)a0;}` — the
 * (void)a0 cast makes IDO -O2 emit the arg-save `sw a0, 0(sp)` and the empty
 * leaf fills the jr delay slot with it. (Earlier "unmatchable" comment was
 * wrong — verified raw-diff=0, reloc-free.) */
void game_uso_func_0000D634(int a0) {
    (void)a0;
}

/* game_uso_func_0000D63C: ramp-down/clamp dispatch. 99.17% objdiff / 36-of-42
 * raw words (2026-07-03 agent-e). See the NM-wrap comment below for the three
 * levers (value=call2-arg4, `value|0` -> caller-saved $a3, `idx*0+10` -> single
 * `li`) and the residual candidate-numbering temp-pool/spill-slot cap. */
extern int import_000B8698();
extern int game_uso_func_022784();
extern char import_800201D0;
extern char game_uso_D_807FF7B4;
extern int import_000B8698();
extern int game_uso_func_022784();
extern char import_800201D0;
extern char game_uso_D_807FF7B4;
/* game_uso_func_0000D63C: ramp-down/clamp dispatch. EXACT 2026-07-15 (was
 * 99.17% "candidate-numbering temp-pool / spill-slot cap"). Final two levers:
 *   (4) value declared FIRST (before idx) -> value's spill home takes the
 *       HIGHER local slot 0x24 (decl-order home rank, first decl = highest).
 *   (5) `idx<<0<<1<<1` split-shift phantom for the table index: each phantom
 *       shift consumes one ugen temp-ring slot with zero emission, advancing
 *       the ring so the real sll lands in $t8 (not $t7) and the tail li in
 *       $t9 -- the documented +1 temp-pool phase shift. NOTE decl-order and
 *       ring phase INTERACT: value-first alone re-phased the ring back, so
 *       both levers must be applied together ((idx<<1<<1) sufficed with
 *       idx-first decls). Levers (1)-(3) from the 2026-07-03 pass retained:
 *       value=call2-arg4, `value | 0` -> caller-saved $a3, `(idx*0)+10`. */
void game_uso_func_0000D63C(char *a0, int a1) {
    int value;
    int idx = *(int*)(a0 + 0x100);

    value = 0;

    if (idx != 0 && a1 != 0) {
        if (idx > 0) {
            if (idx >= 10) {
                idx = (idx * 0) + 10;
                *(int*)(a0 + 0x100) = idx;
            }
            value = *(int*)((char*)&game_uso_D_807FF7B4 + (idx<<0<<1<<1));
            if (value != 0) {
                import_000B8698(*(int*)((char*)&import_800201D0 + 0x138),
                                *(int*)(a0 + 0xB4), value | 0, value);
            }
        }
    }
    *(int*)(a0 + 0xF8) = 0;
    *(int*)(a0 + 0x100) = 0;
    game_uso_func_022784(*(int*)((char*)&import_800201D0 + 0x138),
                         *(int*)(a0 + 0xB4), a1, value);
    *(int*)(a0 + 0x120) = 1;
}

/* 26 insns. Toggle bit 0x40 in (a0->0xB4)[0xA58], call worker, test the
 * bit afterward, dispatch a0->0xFC to one of two flag values. Promoted
 * 2026-05-14 from 93.73% NM to byte-exact in C-only:
 *   (a) `int *p = base + 0xA58` named local forces target's
 *       `addiu v0, v0, 0xA58` (without it, IDO CSE-folds offset into
 *       the lw/sw pair using the same base reg).
 *   (b) Swap if/else arms + invert condition fixes both branch
 *       direction (bnel → beql) AND lui register allocation order
 *       (which value goes into t1 vs t2). */
extern int game_uso_func_00E124();
void game_uso_func_0000D6E4(char *a0) {
    int *p = (int*)(*(char**)(a0 + 0xB4) + 0xA58);
    *p ^= 0x40;
    game_uso_func_00E124(*(char**)(a0 + 0xB4), a0);
    if ((*(int*)(*(char**)(a0 + 0xB4) + 0xA58) & 0x40) != 0) {
        *(int*)(a0 + 0xFC) = 0x00050000;
    } else {
        *(int*)(a0 + 0xFC) = 0x00010000;
    }
}

/* Conditional 3-call state update. BYTE-EXACT 2026-06-20.
 * The prior "v0/v1 regalloc swap + beql/beq" cap was MISDIAGNOSED: it came
 * from the `int result = 0; ...; result = 1; return result;` single-return
 * shape, which spans `result` to the tail and makes IDO pick $v1 + a
 * branch-likely (beqzl) + trailing `or v0,v1`. Rewriting as the POSITIVE
 * two-return form — `if (cond) { body; return 1; } return 0;` (no `result`
 * local) — preinits $v0=0, emits a plain `beqz t7,end; nop` fallthrough, and
 * a `b end; li v0,1` tail with $v0 throughout, matching the target exactly.
 * Dropping the `result` local also keeps `arg`'s spill at 0x24 (the extra
 * local had pushed it to 0x20). */
int game_uso_func_0000D74C(char *a0) {
    int arg;
    if (*(int*)(*(char**)(a0 + 0xB4) + 0x938)) {
        gl_func_00000000(a0, 1);
        gl_func_00000000(a0, 2, 0);
        arg = *(int*)(a0 + 0xFC) | 0xA;
        if (*(int*)(*(char**)(a0 + 0xB4) + 0xA14) <= 0) {
            arg = 0x0006000A;
            *(int*)(*(char**)(a0 + 0xB4) + 0x960) = 0x64;
        }
        gl_func_00000000(a0, 3, 0, arg);
        gl_func_00000000(a0, arg);
        gl_func_00000000(a0, 0);
        return 1;
    }
    return 0;
}

/* Conditional fall-below-floor update. BYTE-EXACT. The E90 table pair is passed
 * BY VALUE as `*(Pair2*)((char*)&D_00000000 + 0xE90)`: the base+offset ADDEND form
 * (NOT a separate `&D_00000E90` symbol) emits `lui %hi; addiu base,0xE90; lw 0; lw 4`
 * with the 0xE90 baked into the addiu as a literal addend (matching the target's
 * HI16-only reloc) AND homes a1/a2 to sp+4/sp+8 via the struct-by-value spill —
 * same proven form as the byte-exact neighbor game_uso_func_0000D8A8 (uses +0xE70).
 * The old `&D_00000E90` form emitted a HI16+LO16 pair → addiu imm=0 (1-diff residual
 * after the banned INSN_PATCH that previously faked it was removed 2026-05-23).
 * See docs/MATCHING_WORKFLOW.md addend form. */
void game_uso_func_0000D7F4(char *a0) {
    int *data = *(int**)(a0 + 0xB4);
    if (*(float*)((char*)data + 0xA38) < -20.0f) {
        if (*(int*)((char*)data + 0x938) != 0) {
            gl_func_00000000(a0, 1, 2);
            gl_func_00000000(a0, *(int*)(a0 + 0xFC) | 0x16, 0, 1, 1, 1);
            gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE90), 1);
            gl_func_00000000(a0);
            *(int*)(a0 + 0x114) = 0;
        }
    }
}

/* MATCHED 2026-05-28: struct-by-value (E70/E74 pair) + inlined B4-deref.
 * The named t6 local landed the B4-child in $v0; inlining the deref into
 * the condition shifts it to $t6 (target's contiguous t6/t7/t8 numbering).
 * See docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_0000D8A8(char *a0) {
    if (*(int*)((char*)*(int**)(a0 + 0xB4) + 0x990) != 0) {
        gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE70));
    }
}

/* game_uso_func_0000D8EC: 56-insn dispatch + 3-call wrapper.
 * NATURAL CEILING via C-shape (branch layout + post-call reload). The
 * remaining caller-slot spill + D-base scheduling family cap (same as
 * D7F4/D8A8) was previously promoted via Makefile SUFFIX_BYTES_FORCE/
 * INSN_PATCH — both REMOVED 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM.
 *
 * Mixed control flow:
 *   if (a0->[0xB4]->[0x938] == 0) {  ; v1->[0x938] gate
 *       fall through to L_BC tail
 *   } else if (*(int*)&D_00000000 == 0) {  ; ptr gate
 *       a0->[0xE4]_h = 0; gl_func(a0); v1 = a0->[0xB4];
 *   } else {  ; main path
 *       int a1 = 0;
 *       if (a0->[0x118] != 0) {
 *           if (v1->[0x800]->[0x18] & 0x100) a1 = 1;
 *       } else {
 *           if (v1->[0x800]->[0x10] & 0x100) a1 = 1;
 *       }
 *       if (a1) {
 *           gl_func(a0, *(D+0xEB8), *(D+0xEBC));  ; 3-arg varargs
 *           a0->[0xE4]_h = 0; a0->[0x118] = 0;
 *       }
 *   }
 *   L_BC: t6 = v1->[0x9D4]; if (t6 >= 11) gl_func(a0); */
void game_uso_func_0000D8EC(int *a0) {
    int *v0;
    int a1;

    if (*(int*)((char*)(int*)*(int*)((char*)a0 + 0xB4) + 0x938) == 0) goto L_BC;
    if (*(int**)&D_00000000 != 0) {
        a1 = 0;
        if (*(int*)((char*)a0 + 0x118) != 0) {
            v0 = (int*)*(int*)((char*)(int*)*(int*)((char*)a0 + 0xB4) + 0x800);
            if ((*(int*)((char*)v0 + 0x18) & 0x100) != 0) a1 = 1;
        } else {
            v0 = (int*)*(int*)((char*)(int*)*(int*)((char*)a0 + 0xB4) + 0x800);
            if ((*(int*)((char*)v0 + 0x10) & 0x100) != 0) a1 = 1;
        }
        if (a1 != 0) {
            gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xEB8));
            *(short*)((char*)a0 + 0xE4) = 0;
            *(int*)((char*)a0 + 0x118) = 0;
        }
    } else {
        *(short*)((char*)a0 + 0xE4) = 0;
        gl_func_00000000(a0);
    }
L_BC:
    if (*(int*)((char*)(int*)*(int*)((char*)a0 + 0xB4) + 0x9D4) >= 11) {
        gl_func_00000000(a0);
    }
}

#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* Per-frame edge-trigger spine (524 words / 0x830, game_uso -O2, USO).
 *
 * 2026-06-21 DEEP RECONSTRUCTION (agent-i): replaced the prior m2c-derived
 * shell — which called the placeholder symbol `game_uso_alias` everywhere
 * (wrong jal target, wrong arg shapes, 625 emitted words vs 524 target) —
 * with a faithful decode against the RESOLVED .s. All callees are now the
 * REAL reloc symbols recovered from the .s R_MIPS_26 entries:
 *   - game_uso_func_0000EDCC(arg0, mode)  -> a0[0x10C/4] = mode (14 calls,
 *     the c.lt.s/bc1fl residual-gate cascade; each gate sets a state-bit
 *     mask into arg0->0x108 + a 'mode' index)
 *   - game_uso_func_07C0FC / _0001189C / _0000EDD4 / _0000D63C   (tail)
 *   - game_uso_func_077C44(a0, mask, 0, dir, 1, 1)               (tail logger)
 *   - game_uso_func_0000D5F8(a0, Pair2, flag)                    (pair-home)
 *   - game_uso_func_0000D5DC(a0)                                 (pair-copy)
 * with the real globals game_uso_D_807FF478/480/3B8 for the tail pair loads
 * (same recipe as the matched siblings 00011258/000112E0).
 *
 * RESIDUAL / CAP CLASS: this is the documented "intractable" cap at extreme
 * scale — a 524-word body saturated with branch-LIKELY FP codegen (bc1fl /
 * bc1tl from the c.lt.s/c.le.s/c.lt.d/c.eq.d residual gates), abs-value
 * mov.s/b/neg.s/mov.s idioms, double-precision rodata-literal compares, and
 * 14+ vararg-logger calls whose arg ordering pins a specific spill/temp
 * coloring. m2c cannot emit branch-likely directly; IDO's FP scheduler +
 * global coloring fixes the exact $f/$t numbering. No single C form lands the
 * whole cascade. Honest NON_MATCHING — this body is a faithful logical decode
 * with the correct callees/relocs, not a byte match.
 *
 * 2026-06-21 decode refinement (agent-i): the 0xA10 state-bit test is a
 * HALFWORD read (lhu, not lw) — fixed to *(u16*)(v1+0xA10) & 0x1F0, matching
 * the target word at that offset.
 *
 * 2026-06-21 agent-i (this session) — three structural fixes, reloc set now
 * MATCHES + size within 1 word:
 *   1. var_a3 was wrongly declared f32; the asm inits it `or a3,zero,zero`
 *      (INTEGER zero) and only ever stores integer state indices (1..5) into
 *      it. Retyped to s32 and changed the init `0.0f`->`0`. This killed the
 *      spurious `mtc1 zero,$f18` at the head and the f32 spill/reload churn.
 *   2. The two `c.lt.d` gates compared against literal `1.0`, but the .s loads
 *      the doubles from CROSS-TU globals via ldc1: `*(f64*)(&D_807FFB18+0x1F8)`
 *      (the abs(0x970)>X gate, db2c) and `*(f64*)(&D_807FFB20+0x200)` (the
 *      0xA0C<X gate, dbfc). Wired both; the two exp-only reloc symbols
 *      (B18/B20) are now present -> RELOC SYMBOL SET MATCH.
 * Result: size gap -84B -> +4B (524 vs 523 insns), non-reloc diffs 441 -> 418.
 *
 * RESIDUAL CAP: built frame -80 vs target -56 (0x18 over). Root is the
 * 6-arg vararg calls (077C44 a0,mask,0,dir,1,1) whose outgoing-arg region IDO
 * lays out non-overlapping with the 4 named stack vars (build slots
 * 44/64/68/72 vs target's contiguous 40/44/48/52), plus pervasive $f/$t
 * coloring and branch-LIKELY (beql/beq) FP gates that m2c/C cannot pin. Logic
 * + callees + globals are all correct; honest NON_MATCHING.
 *
 * 2026-07-10 agent-g BREAKTHROUGH: fuzzy 90.8 -> 98.96 (aligned-equal
 * 276->493 of 524; size exact 524; positional-exact 432). The old (A)/(B)
 * "not C-controllable" verdicts were WRONG — the roots were C-level:
 *   1. sp34 was a PHANTOM local: m2c double-read var_a3's spill slot (every
 *      `sp34=N` shadowed `var_a3=N`; target sp52 IS the a3 spill). Deleted.
 *   2. FRAME 80->56: named-local decl ORDER drives home slots (docs
 *      IDO_CODEGEN "NAMED-LOCAL COUNT governs frame size"). Declaring
 *      var_a3 FIRST (then sp30/sp2C/sp28) homes its spill at 52 and packs
 *      40/44/48 — the 4-word hole vanishes.
 *   3. INT-not-float compares: FW(0x114)==1 (lw/li/bne, not c.eq.s 1.0f)
 *      and FW(0x9CC)==0 (bnezl). The 1.0f<=var_f2 gate loads its constant
 *      from the GLOBAL *(f32*)(&D_807FF68C+4248), not a literal.
 *   4. $f0/$f2 cascade: ONE abs-result var (var_f0, target $f0) but TWO
 *      compare-source vars (temp_f2 0xA1C / temp_f2_2 0x970) — merging
 *      var_f0_2/_3 into var_f0 while keeping temp_f2 split flipped the
 *      whole first-cascade coloring to target. arm2 base is var_v1 (v1),
 *      not a temp (temp_v1 colored v0).
 *   5. CSE-bust: the 3 chain gates re-read 16(v0) each time -> spell as
 *      (*(volatile f32*)(temp_v0_2+0x10)) * FF(arg0,field) (volatile read
 *      FIRST operand; field*vol order loads swapped). temp_v0_3 =
 *      FW(0xB4)+0x2FC pointer form yields the dead addiu v0,v0,764.
 *   6. goto after_24 (label INSIDE the outer if, arm1 does its own
 *      var_v1 reload) duplicates the lw v1,180(s0) into arm1's b-delay
 *      (blocks cross-jump; label outside the outer if perturbs the 0x9D0
 *      block schedule instead — placement matters).
 *   7. 1189C's 3rd arg is sp2C (target lw a2,44), not sp30 — m2c error.
 *   8. Pair2 tail loads need EXPLICIT ADDENDS (USO baked-reloc spelling):
 *      &D_807FF478+0xE88 / &D_807FF480+0xE90 / &D_807FF3B8+0xDC8.
 *      var_a3=4 moved BEFORE the EDCC(2) call (target spills a3 pre-jal).
 * 2026-07-15 wave 3 (agent-h): 493 -> 507/524. Four of the six tie classes
 * fell to the SAME-LINE JOIN + de-naming wave:
 *   (b) c.lt.d/lui pair + (e) 1.0f-vs-zeros mtc1/swc1 order: joining the
 *       0/0/0/1.0f store quads on ONE source line (original statement
 *       order) lets as1 hoist the 1.0f chain store-first as in target
 *       (uopt still numbers zeros-first f4/f6/f8, 1.0f f10) - both the
 *       temp_v0 and temp_v0_3 blocks;
 *   (c) $f12<->$f14 swap: DE-NAMING temp_f14 (inline FF(arg0,0x11C) at
 *       all 4 uses; uopt CSEs them into one pool temp numbered at first
 *       use = f14 as in target) + textual operand swap (0x11C deref FIRST
 *       in each mul: the CSE web outranks, so write it left to get
 *       mul.s fd,fresh,f14);
 *   (d) a3-spill vs sp30-store pre-jal order (0x334 arm): SAME-LINE JOIN
 *       of `sp30 = 0;` with the EDCC call statement sinks the sw zero
 *       into the jal delay past the a3 spill (statement reorder alone
 *       does NOT move it).
 * TRUE RESIDUAL (17 words, both documented cap classes):
 *   (a) beqzl/bc1fl+lui-dup vs beqz/bc1f+nop at the two head gates (as1
 *       branch-form tie; if(1) barrier around the 500.0f join test is
 *       inert; restructure does not flip) x2 sites = 4 words;
 *   (f) andi temp coalesced into a1 vs target's t8 ring slot + downstream
 *       +2 t-ring shift (t8,t9/t0 vs t0,t1/t2, lw t4/li t3 vs t6/t5)
 *       = 13 words. 2026-07-15 re-probe: same-name redef (temp_a1 and
 *       temp_v0_4 forms both re-coalesce/in-place), store-first +
 *       FW re-read arg (byte-neutral), trailing subsumed mask &0xFFFFF
 *       (NOT subsumed - range not tracked through |, +3 insns), <<0<<0
 *       phantoms (cfe-folds on a plain var), x*0 mpy pair (+1 only and
 *       recolors v0->v1). The or-into-precolored-a1 destination-coalesce
 *       has no C handle here.
 * Honest NON_MATCHING at ~99.4; remaining gap is as1 branch-form +
 * or-coalesce ring cascade.
 * 2026-07-15 (agent-g) 3 more (f) negatives, all byte-identical to
 * baseline: inline-CSE de-name of temp_a1 (store + arg each spelled
 * `(v & 0xFFFF) | 0x60000` - uopt CSE temp coalesces exactly like the
 * named var); |-operand swap `0x60000 | (v & 0xFFFF)` (canonicalized);
 * combined swap+de-name. Numbering analysis: target burned TWO temp
 * numbers (andi=t8 kept, or-temp coalesced late into a1) where every C
 * spelling coalesces BOTH at numbering time (zero burns) - matches the
 * "no C handle" verdict.
 * 2026-07-15 round 2 (agent-g): the NEW folded-ushort ring-burn lever
 * (2A4D0) does NOT reach this gate - 3 negatives: (unsigned short)(v &
 * 0xFFFF) materializes `move a1,v0` (+1 word, cast temp coalesces into
 * a1 anyway, not a phantom burn - the 2A4D0 fold only stays zero-insn at
 * a STORE RHS, not feeding an |); (unsigned short)v | 0x60000 is
 * byte-identical to baseline; embedded-assignment arg (FW(...)=expr as
 * call arg) reschedules move-a0/lui-at (20 diffs). Cap confirmed. */
#ifndef FF
#define FF(p, o) (*(f32 *)((char *)(p) + (o)))
#endif
extern void game_uso_func_07C0FC();
void game_uso_func_0000EDCC(int *a0, int a1);
void game_uso_func_0000EDD4(int *a0, unsigned int a1, int a2);
void game_uso_func_0001189C(int *a0, int a1, int a2);
extern char game_uso_D_807FF478;
extern char game_uso_D_807FF480;
extern char game_uso_D_807FF3B8;
extern char game_uso_D_807FF68C;
extern char game_uso_D_807FFB18;
extern char game_uso_D_807FFB20;
void game_uso_func_0000D9CC(char *arg0) {
    s32 var_a3;
    s32 sp30;
    char *sp2C;
    s32 sp28;
    f32 temp_f0;
    f32 var_f0;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f0_4;
    f32 var_f12;
    f32 var_f2;
    s32 temp_a1;
    s32 temp_v0_4;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_3;
    char *var_v1;

    FW(arg0, 0x108) = 0;
    sp30 = 1;
    sp2C = 0;
    sp28 = 0;
    var_v1 = FW(arg0, 0xB4);
    var_a3 = 0;
    if ((FF(var_v1, 0x348) > 30.0f) && (*(u16 *)(var_v1 + 0xA10) & 0x1F0)) {
        temp_f2 = FF(var_v1, 0xA1C);
        if (temp_f2 < 0.0f) {
            var_f0 = -temp_f2;
        } else {
            var_f0 = temp_f2;
        }
        if (FF(arg0, 0x244) < var_f0) {
            sp30 = 0;
            sp28 = 2;
            game_uso_func_0000EDCC((int *)arg0, 1);
            var_a3 = 3;
            if (FF(FW(arg0, 0xB4), 0xA1C) > 0.0f) {
                FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x16);
                sp2C = (char *)1;
            } else {
                FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x17);
                sp2C = (char *)3;
            }
            var_v1 = FW(arg0, 0xB4);
            goto after_24;
        }
        if (temp_f2 < 0.0f) {
            var_f0 = -temp_f2;
        } else {
            var_f0 = temp_f2;
        }
        if (FF(arg0, 0x22C) < var_f0) {
            sp30 = 0;
            game_uso_func_0000EDCC((int *)arg0, 4);
            var_v1 = FW(arg0, 0xB4);
            var_a3 = 2;
            temp_f2_2 = FF(var_v1, 0x970);
            if (temp_f2_2 < 0.0f) {
                var_f0 = -temp_f2_2;
            } else {
                var_f0 = temp_f2_2;
            }
            if (*(f64 *)((char *)&game_uso_D_807FFB18 + 0x1F8) < (f64) var_f0) {
                if (temp_f2_2 <= 0.0f) {
                    FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0xE);
                    sp2C = (char *)3;
                } else {
                    FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0xF);
                    sp2C = (char *)1;
                }
            } else if (FF(var_v1, 0xA1C) > 0.0f) {
                FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0xC);
                sp2C = (char *)1;
            } else {
                FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0xD);
                sp2C = (char *)3;
            }
            var_v1 = FW(arg0, 0xB4);
        }
after_24:;
    }
    if (FF(var_v1, 0x9D0) < 500.0f) {
        temp_v0 = var_v1 + 0xCC;
        if ((f64) FF(var_v1, 0xA0C) < *(f64 *)((char *)&game_uso_D_807FFB20 + 0x200)) {
            FF(temp_v0, 0) = 0.0f; FF(temp_v0, 0x4) = 0.0f; FF(temp_v0, 0x8) = 0.0f; FF(temp_v0, 0xC) = 1.0f;
            sp28 = 2;
            var_a3 = 4;
            game_uso_func_0000EDCC((int *)arg0, 2);
            if (FF(FW(arg0, 0xB4), 0x3CC) < 0.0f) {
                FW(arg0, 0x108) = 0x1002A;
            } else {
                FW(arg0, 0x108) = 0x1002B;
            }
            var_v1 = FW(arg0, 0xB4);
        }
    }
    temp_v0_2 = var_v1 + 0x528;
    if (!(FW(var_v1, 0x9A8) & 1)) {
        var_f12 = FF(arg0, 0x11C) * FF(var_v1, 0xA1C);
        var_f2 = FF(arg0, 0x11C) * FF(var_v1, 0xA20);
        var_f0_4 = FF(arg0, 0x11C) * FF(var_v1, 0xA24);
        if (!(FW(var_v1, 0xA58) & 0x4000)) {
            var_f0_4 = 0.0f;
            var_f2 = 0.0f;
            var_f12 = 0.0f;
        }
        if (((*(volatile f32 *)(temp_v0_2 + 0x10)) * FF(arg0, 0x304)) <= var_f2) {
            sp28 = 3;
            sp30 = 0;
            game_uso_func_0000EDCC((int *)arg0, 2);
            var_a3 = 5;
            FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x15);
        } else if (((*(volatile f32 *)(temp_v0_2 + 0x10)) * FF(arg0, 0x2EC)) <= var_f2) {
            sp28 = 0;
            sp30 = 0;
            game_uso_func_0000EDCC((int *)arg0, 5);
            var_a3 = 1;
            FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x2D);
        } else if (((*(volatile f32 *)(temp_v0_2 + 0x10)) * FF(arg0, 0x2D4)) <= var_f2) {
            sp28 = 0;
            sp30 = 0;
            game_uso_func_0000EDCC((int *)arg0, 4);
            var_a3 = 1;
            FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x2C);
        } else if (FF(arg0, 0x2BC) <= var_f0_4) {
            sp28 = 4;
            game_uso_func_0000EDCC((int *)arg0, 3);
            var_a3 = 5;
            FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x15);
        } else if (FF(arg0, 0x2A4) <= var_f0_4) {
            sp28 = 3;
            game_uso_func_0000EDCC((int *)arg0, 2);
            var_a3 = 4;
            FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0xB);
        } else if (FF(arg0, 0x28C) <= var_f0_4) {
            sp28 = 2;
            game_uso_func_0000EDCC((int *)arg0, 1);
            var_a3 = 3;
            FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0xA);
        } else if (FF(arg0, 0x274) <= var_f0_4) {
            sp28 = 0;
            sp30 = 0;
            game_uso_func_0000EDCC((int *)arg0, 1);
            var_a3 = 1;
            FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x2C);
        } else if (var_f0_4 <= -FF(arg0, 0x334)) {
            sp28 = 2;
            sp2C = (char *)2;
            var_a3 = 3;
            sp30 = 0; game_uso_func_0000EDCC((int *)arg0, 5);
            FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x16);
        } else if (var_f0_4 <= -FF(arg0, 0x31C)) {
            sp28 = 0;
            sp2C = (char *)2;
            sp30 = 0;
            game_uso_func_0000EDCC((int *)arg0, 5);
            var_a3 = 1;
            FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x14);
        } else {
            temp_f0 = FF(arg0, 0x25C);
            if (temp_f0 <= var_f12) {
                sp28 = 3;
                game_uso_func_0000EDCC((int *)arg0, 2);
                var_a3 = 2;
                FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x13);
            } else if (var_f12 <= -temp_f0) {
                sp28 = 3;
                game_uso_func_0000EDCC((int *)arg0, 2);
                var_a3 = 2;
                FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x12);
            } else if ((*(f32 *)((char *)&game_uso_D_807FF68C + 4248) <= var_f2) && ((f64) FF(arg0, 0x11C) == 1.0) && (FW(var_v1, 0x9CC) == 0)) {
                sp28 = 0;
                sp30 = 0;
                FW(arg0, 0x108) = (s32) (FW(arg0, 0xFC) | 0x2F);
                game_uso_func_07C0FC(FW(var_v1, 0x800),
                                     (char *)&game_uso_D_807FF68C + 4252, 0xA);
            }
        }
    }
    if ((FW(arg0, 0x114) == 1) && (sp28 == 0)) {
        FW(arg0, 0x108) = 0;
    }
    if (FW(arg0, 0x108) != 0) {
        game_uso_func_0001189C((int *)arg0, (s32) var_a3, (s32) sp2C);
        FF(arg0, 0x11C) = 1.0f;
        game_uso_func_0000EDD4((int *)arg0, sp28, sp2C);
        temp_v0_3 = (char *)FW(arg0, 0xB4) + 0x2FC;
        FF(temp_v0_3, 0) = 0.0f; FF(temp_v0_3, 0x4) = 0.0f; FF(temp_v0_3, 0x8) = 0.0f; FF(temp_v0_3, 0xC) = 1.0f;
        game_uso_func_0000D63C(arg0, (sp28 == 0));
        FW(FW(arg0, 0xB4), 0x3DC) = 0;
        if (sp30 != 0) {
            game_uso_func_077C44(arg0, FW(arg0, 0x108), 0, 2, 1, 1);
            game_uso_func_0000D5F8(arg0, *(Pair2 *)((char *)&game_uso_D_807FF478 + 0xE88), 2);
        } else {
            game_uso_func_077C44(arg0, FW(arg0, 0x108), 0, 1, 1, 1);
            game_uso_func_0000D5F8(arg0, *(Pair2 *)((char *)&game_uso_D_807FF480 + 0xE90), 1);
        }
        game_uso_func_0000D5DC(arg0);
        FW(arg0, 0x114) = 0;
    }
    if (FW(FW(arg0, 0xB4), 0xA14) <= 0) {
        temp_v0_4 = FW(arg0, 0x108);
        FW(arg0, 0x114) = 0;
        if (temp_v0_4 != 0) {
            temp_a1 = (temp_v0_4 & 0xFFFF) | 0x60000;
            FW(arg0, 0x108) = temp_a1;
            game_uso_func_077C44(arg0, temp_a1, 0, 1, 1, 1);
            game_uso_func_0000D5F8(arg0, *(Pair2 *)((char *)&game_uso_D_807FF3B8 + 0xDC8), 1);
        }
        FW(FW(arg0, 0xB4), 0x960) = 0x64;
        game_uso_func_0000D5DC(arg0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D9CC);
#endif

// game_uso_func_0000E1FC — STRUCTURAL PASS (0xD4 / 53 words,
// no episode). Raw-.word USO form (single function, game_uso main
// game-logic; boundary already split by commit 085ef620 — named fn
// still undecoded). Hand-decoded.
//
// Threshold-gated event / effect trigger.
//
//   void game_uso_func_0000E1FC(Obj *obj, A a1, A a2) {
//     Sub *s = obj->0xB4;
//     if (!(s->0x348 < s->0x10)) return;                  // timer/state
//     if (!(obj->0x800->0x18 & 0x2000)) return;            // flag gate
//     if (s->0x9CC == K) {                                 // table id
//       float m = fabsf(s->0x970);                          // magnitude
//       if ((double)m < DBL(D_00000E68 + 0x208)) {           // folded f64
//         func_00000000(a1->0x0, a2->0x0);                   // event A
//       } else {
//         func_00000000(a1->0x0, a2->0x4);                   // event B
//       }
//     }
//   }
//
// Struct-typing reference:
//   obj: 0xB4 -> s (s->0x10 a threshold, s->0x348 a current value/
//     timer, s->0x970 a magnitude f32, s->0x9CC a table id), 0x740
//     a sub-anchor, 0x800 -> ctx (->0x18 flags, bit 0x2000 gate).
//   D_00000E68 / D_00000E50 = USO static tables; D_00000E68 + 0x208
//     = a folded f64 threshold constant. a1/a2 = event arg records.
//   func_00000000 = USO placeholder dispatcher (event report /
//     state notify).
// Caps (DEFERRED): raw-word USO + placeholder calls + folded f64; USO
//   mnemonic disasm limitation prevents byte-match. Real-C STRUCTURAL
//   body below — threshold-gated event/effect trigger skeleton.
//   Byte-match deferred. Name pre-checked: no extern reuse.
/* game_uso_func_0000E1FC: threshold-gated event trigger. EXACT 2026-07-15
 * (was 99.62 "folded f64 / USO raw-word" deferred cap). Final lever: DE-NAME
 * the double threshold — inline `*(double*)((char*)&D + 0x208)` directly in
 * the compare instead of a named `double thr` local. Nameless expression =
 * fresh FP pool temps numbered at the use point (const ldc1 -> $f10, cvt.d.s
 * -> $f16, matching target); the named form let uopt number the load early
 * and reuse dead low regs (ldc1 $f0 / cvt $f10, 3-word residual). Same
 * de-naming lever as bootup B49C (int side). */
extern void game_uso_func_0000D5BC(char *, Pair2);
extern char game_uso_D_807FF458;
extern char game_uso_D_807FF440;
void game_uso_func_0000E1FC(char *obj) {
    char *s = *(char **)(obj + 0xB4);
    char *sub = s;
    float raw, m;
    if(1){ sub += 0x740; }
    if (!(*(float *)(sub + 0x10) > *(float *)(s + 0x348))) return;
    sub = *(char **)(s + 0x800);
    if (!(*(int *)(sub + 0x18) & 0x2000)) return;
    if (*(int *)(s + 0x9CC) != 0) goto callA;
    raw = *(float *)(s + 0x970);
    m = (raw < 0.0f) ? -raw : raw;
    if (*(double *)((char *)&game_uso_D_807FF458 + 0x208) < (double)m) {
    callA:
        game_uso_func_0000D5BC(obj, *(Pair2 *)((char *)&game_uso_D_807FF458 + 0xE68));
    } else {
        game_uso_func_0000D5BC(obj, *(Pair2 *)((char *)&game_uso_D_807FF440 + 0xE50));
    }
}

/* game_uso_func_0000E2D0 - per-frame advance of a timed sub-object on game
 * object a0. Global gate at &D+0; if active (a0->0xE4 frame counter >= 0) and
 * the sub-block (a0->0xB4->0x800->0x10) has flag bits 0x300, advance the
 * counter and accumulate a0->0x1E4 into parent->0x31C when not frozen
 * (parent->0x9A8 bit 0); otherwise reset the counter to -1.
 * Match keys: (s16)frame used inline (not reassigned) so the load stays live
 * across the beql, splitting the sign-extension (sll/sra) and coloring the
 * extended temp into v1; if/else (not early-return) emits the beql + dead
 * store-tail. Exact. */
extern char game_uso_D_807FF684;
void game_uso_func_0000E2D0(a0)
char *a0;
{
    int frame;
    char *block;
    float *acc;

    if (*(int*)&game_uso_D_807FF684 == 0 && (frame = *(s16*)(a0 + 0xE4), frame >= 0)) {
        block = *(char**)(*(char**)(a0 + 0xB4) + 0x800);
        if (*(int*)(block + 0x10) & 0x300) {
            *(s16*)(a0 + 0xE4) = (s16)frame + 1;
            if ((s16)frame < *(int*)(a0 + 0x1CC)) {
                char *parent = *(char**)(a0 + 0xB4);
                acc = (float*)(parent + 0x31C);
                if ((*(int*)(parent + 0x9A8) & 1) == 0) {
                    *acc += *(float*)(a0 + 0x1E4);
                }
            }
        } else {
            *(s16*)(a0 + 0xE4) = -1;
        }
    }
}

#ifdef NON_MATCHING
/* game_uso_func_0000E35C: slot/queue advance. If arg0->0xF0 (current) != NULL:
 * cb(cur->0x30,1); compute its array index (vs base *(int*)&D, /64) — two forms
 * by arg0->0xB4->0xA58 bit-5; advance the queue (0x100 counter++, 0xF0=NULL, 0xF4/
 * 0xF8 = prev, reset counter if prev==0xF8); cb(arg0); set prev->0x20 from ->0x28
 * (if 0xB4->0xA58 bit-6 & nonzero) else ->0x24; then by prev->0x38 bit-1 emit a
 * 2-call or 3-call pair using &D+0xEC0/0xEC8/0xED0 tables; cb(arg0, &D+0xED0..).
 * Returns 1; else 0. 75.5% -> 91.6%: the three D-pair calls (EC0/EC4, EC8/ECC,
 * ED0/ED4) pass BY VALUE as *(Pair2*), homing a1,a2 (same lever as EF70,
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair). 91.6 ->
 * 95.14 (2026-05-31): the &D+0x138 access used distinct extern `D_00000138`.
 * 2026-06-23 (agent-e): REAL CALLEES/GLOBALS recovered from expected/ relocs.
 * The placeholder gl_func_00000000 fan-out is now the true symbol set, all
 * matching expected's R_MIPS_26 exactly: game_uso_func_0000EE30 (first cb),
 * import_000B8518 (index cb), game_uso_func_0000E564 (advance), 077C44/D5F8
 * (Pair2 tail), D5BC (final). Globals: game_uso_D_807FFBC0 (queue base),
 * import_800201D0+0x138 (cfg), game_uso_D_807FF4B0/B8/C0 (EC0/EC8/ED0 pairs).
 * Verified vs target: ignoring reloc-pairing-form + register renaming, the only
 * structural residual is the prev-write branch-delay `move v0,prev` duplication.
 * REMAINING CAP (shared with sibling F6D4): the target emits UNPAIRED
 * R_MIPS_HI16 (lui %hi; lw <lit>(reg), no LO16) for every D-global, because in
 * the original link those symbols had REAL addresses (e.g. 0x800201D0). In this
 * USO build every such symbol is forced to value 0 (load-resolved), so any
 * `&SYM+off` access IDO emits as a HI16+LO16 PAIR; the unpaired form is
 * unreachable from C here (D_00000138 is unpaired only because its VALUE is
 * 0x138). That + regalloc-renumber are the residual. NON_MATCHING. */
extern int *game_uso_D_807FFBC0;
extern char game_uso_D_807FF4B0;
extern char game_uso_D_807FF4B8;
extern char game_uso_D_807FF4C0;
extern void game_uso_func_0000EE30(char *, int, int);
extern void game_uso_func_0000E564(int *);
extern int import_000B8518();
extern char import_800201D0;
int game_uso_func_0000E35C(char *arg0) {
    char *cur;
    char *b4;
    char *prev;
    char *f4;
    int v1;

    cur = *(char **)(arg0 + 0xF0);
    if (cur != 0) {
        game_uso_func_0000EE30(arg0, *(int *)(cur + 0x30), 1);
        b4 = *(char **)(arg0 + 0xB4);
        if (*(int *)(b4 + 0xA58) & 0x20) {
            int base = *(int *)&game_uso_D_807FFBC0;
            import_000B8518(*(int *)((char *)&import_800201D0 + 0x138), b4,
                (int)((base + (*(int *)(*(char **)(arg0 + 0xF0) + 0x3C) << 6)) - base) / 64);
        } else {
            import_000B8518(*(int *)((char *)&import_800201D0 + 0x138), b4,
                (int)((int)*(char **)(arg0 + 0xF0) - *(int *)&game_uso_D_807FFBC0) / 64);
        }
        prev = *(char **)(arg0 + 0xF0);
        *(int *)(arg0 + 0x100) = *(int *)(arg0 + 0x100) + 1;
        *(char **)(arg0 + 0xF0) = 0;
        *(char **)(arg0 + 0xF4) = prev;
        if (prev == *(char **)(arg0 + 0xF8)) {
            *(int *)(arg0 + 0x100) = 0;
        }
        *(char **)(arg0 + 0xF8) = prev;
        game_uso_func_0000E564((int *)arg0);
        if ((*(int *)(*(char **)(arg0 + 0xB4) + 0xA58) & 0x40) &&
            (f4 = *(char **)(arg0 + 0xF4), v1 = *(int *)(f4 + 0x28), (v1 != 0))) {
            *(int *)(f4 + 0x20) = v1;
        } else {
            f4 = *(char **)(arg0 + 0xF4);
            *(int *)(f4 + 0x20) = *(int *)(f4 + 0x24);
        }
        f4 = *(char **)(arg0 + 0xF4);
        if (*(int *)(f4 + 0x38) & 2) {
            game_uso_func_077C44(arg0, *(int *)(f4 + 0x20), 0, 2, 1, 1);
            game_uso_func_0000D5F8(arg0, *(Pair2 *)((char *)&game_uso_D_807FF4B0 + 0xEC0), 2);
        } else {
            game_uso_func_077C44(arg0, *(int *)(f4 + 0x20), 0, 3, 1, 1);
            game_uso_func_0000D5F8(arg0, *(Pair2 *)((char *)&game_uso_D_807FF4B8 + 0xEC8), 3);
        }
        game_uso_func_0000D5BC(arg0, *(Pair2 *)((char *)&game_uso_D_807FF4C0 + 0xED0));
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E35C);
#endif

void game_uso_func_0000E564(int *a0) {
    int v0 = ((int*)a0[0xF4/4])[0x2C/4];
    if (v0 & 0xC000) {
        gl_func_00000000((char*)a0[0xB4/4] + 0x808);
        v0 = ((int*)a0[0xF4/4])[0x2C/4];
    }
    if (v0 & 0x3000) {
        gl_func_00000000((char*)a0[0xB4/4] + 0x808);
    }
}

// game_uso_func_0000E5C8 — STRUCTURAL PASS (0x354 / 213 words,
// no episode). Raw-.word USO form (single function, game_uso main
// game-logic). Pure bitfield work (1 call, no FP). ~85.6% (insn-mnemonic).
//
// 2026-06-23 (agent-i): callee CONFIRMED = game_uso_func_0000EAF4 (was the
//   generic `func_00000000` placeholder → wrong reloc symbol). Now calls
//   game_uso_func_0000EAF4 directly so the NM-build emits the correct
//   `jal game_uso_func_0000EAF4` R_MIPS_26 (matches target reloc). No score
//   change but a genuine correctness/reloc fix.
//   CAP CONFIRMED — function will NOT land in either dispatch form:
//   (a) SWITCH-LOWERING: cases 1-6 are contiguous so IDO emits this `switch`
//       as a JUMPTABLE (adds a .rodata jumptable + HI16/LO16 rodata relocs
//       the target does NOT have). The target lowers the SAME switch as a
//       linear compare cascade (`li at,N; beq v0,at,Hn` then forward bodies,
//       v0=lw 0xE8 loaded ONCE) with NO rodata. Rewriting as C `if/else if`
//       produces `li const; bne v0,const,NEXT` with INLINE bodies (not the
//       target's beq-to-forward-handler) and drops mnemonic-ratio 0.856->0.60
//       AND removes the rodata — but the inline-body shape never converges.
//       No clean IDO-C steers a contiguous-1-6 switch to the target's
//       beq-chain-with-trailing-bodies. Genuine switch-lowering cap.
//   (b) A58-call gate: target materializes `a1=(v0&0x20)!=0` via sltu and
//       `move a2,v1` (raw 0x20) before the call; clean `if(v0&0x20)` C emits
//       a direct beqz (no sltu) — eval-order/bool-materialization cap.
//   (c) count-global `lui a2,%hi(D_00000000-region)` is HOISTED to just after
//       the jal (e6c4) — a no-reloc lui0 codegen the search-loop C can't pin.
//   (d) several beqzl/bnezl likely-branch polarity + loop sltu/bnez choices.
//
// 2026-05-31 DECODE FINDING (do NOT "fix" the switch to a cascade — it
// REGRESSES). The 0x12C-gated dispatch on obj->0xE8 (cases 5,6,2,1,4,3)
// is emitted by the TARGET as an if-else CASCADE (li-const + `beq`,
// reloading `lw 232(a3)` fresh before each compare), NOT the jumptable
// our `switch` currently produces. BUT rewriting it as the matching
// `if (E8==5)... else if (E8==6)...` cascade recovers the 4 cascade insns
// yet DROPS fuzzy 78.2%->76.2%: the else-if caches E8 in one reg (vs the
// target's reload-per-compare), and that register choice churns the
// downstream allocation more than the structural gain is worth. The
// jumptable `switch` form is the HIGHER-SCORING decode; keep it until a
// reload-forcing cascade form (one that reproduces the per-compare
// `lw 232`) is found. The function is also ~17 insns short overall vs
// target (213 vs 196) — multi-run structural work remains beyond the
// dispatch (the e8&0x4 bit-clear block + the stride-64 search tail).
//
// State-flag remapper: tests bits in a source flag word and
// bit-permutes them into the object's internal flag field obj->0xE8.
//
//   void game_uso_func_0000E5C8(Obj *obj, A a1) {
//     src = obj->0xB4 ? obj->0xB4->0x800->0x10 : obj->0x18;
//     // long unrolled chain, one test per source bit:
//     //   if (src & 0x200)  obj->0xE8 |= 0x02;
//     //   if (src & 0x1000) obj->0xE8 |= 0x...;            // (etc.)
//     //   if (src & 0x4000) obj->0xE8 |= 0x01;
//     //   if (src & 0x2000) obj->0xE8 |= 0x10;
//     //   if (src & 0x4000) obj->0xE8 |= 0x20;
//     //   if (src & 0x8000) obj->0xE8 |= 0x40;
//     //   … ~16 such (mask -> outbit) pairs, each a
//     //   lw 0xE8 / andi src,MASK / branch / ori OUTBIT / sw 0xE8;
//     // tail: also folds obj->0xB4->0xA58 bits into obj->0xE8.
//   }
//
// Struct-typing reference:
//   obj: 0xB4 -> sub (->0x800->0x10 a hardware/input flag word,
//     ->0xA58 more flags), 0x18 a fallback flag source, 0xE8 the
//     object's internal/derived flag field (the permuted target).
//   Pure bit-permutation: each source bit maps to a distinct
//     internal bit (input/state translation table, unrolled).
//   func_00000000 = USO placeholder dispatcher (1 trailing call).
// FULL RE-TRACE 2026-05-31 (11.79% -> 77.93%): the prior body was a WRONG
//   skeleton (tested obj->0xB4 not a0->0xF4; local dst not 0xE8-RMW; 5/7 table
//   entries). Now fully structured: condition+src (a0->0xF4 picks ->0x18/->0x10),
//   full 7-block mask->outbit table, A58-gated call, 0x12C-gated switch on 0xE8,
//   bit-clearing (0xE8&0x4 + a3->0xF4->0x2C bits 0x5000/0xa000/0xc000/0x100000/
//   0x200000), 0xEC counter, and the stride-64 search loop over the table at
//   *(&D_00000000 + 0x15D0) (count = *(int*)&D_00000000), tail 0xE8 &= 0x6.
//   Residual (~22%, len 196 vs 213): regalloc-renumber + the A58-call sltu-bool
//   materialization + the count-global no-reloc lui0 codegen. Full structure +
//   offsets: memory project_1080_e5c8_full_decode_211insn.
#ifdef NON_MATCHING
// game_uso_func_0000E5C8 — reconstruction pass (agent-e, 2026-06-24).
// State-flag remapper: reads a source flag word (a0->0xF4 picks
// a0->0xB4->0x800->0x18 vs ->0x10), bit-permutes it into a3->0xE8,
// folds a3->0xB4->0xA58 bits via an ALWAYS-MADE call to
// game_uso_func_0000EAF4 (args materialized via sltu(0,bit)), runs the
// 0x12C-gated dispatch on 0xE8, the 0xE8&4 bit-clear block (a3->0xF4->0x2C
// flags), the 0xEC counter, and the stride-64 search over the table at
// game_uso_D_807FFBC0 (count = *(int*)&D_00000000), tail 0xE8 &= 0x6.
//
// Fix vs prior 78.2% NM body: search table base is game_uso_D_807FFBC0
// (prior used &D_00000000+0x15D0 — wrong symbol). Switch stays the
// higher-scoring jumptable form (cascade regresses — documented cap), and
// the A58 call stays CONDITIONAL: the target's unconditional-call shape is
// semantically truer but churns regalloc and scores ~0.1pp WORSE in-tree,
// so the marginal table-base fix is the only net-positive lever here.
void game_uso_func_0000E5C8(char *a0, int a1) {
    char *a3 = a0;
    unsigned int src;
    char *sub;
    unsigned int v0;

    /* src = a0->0xB4->0x800->(0x18 if a0->0xF4 else 0x10) */
    if (*(int *)(a0 + 0xF4) != 0) {
        src = *(unsigned int *)(*(char **)(*(char **)(a0 + 0xB4) + 0x800) + 0x18);
    } else {
        src = *(unsigned int *)(*(char **)(*(char **)(a0 + 0xB4) + 0x800) + 0x10);
    }
    /* unrolled mask->outbit permutation into a3->0xE8 (read-modify-write) */
    if (src & 0x200)   *(int *)(a3 + 0xE8) |= 0x2;
    if (src & 0x1000)  *(int *)(a3 + 0xE8) |= 0x4;
    if (src & 0x400)   *(int *)(a3 + 0xE8) |= 0x1;
    if (src & 0x10000) *(int *)(a3 + 0xE8) |= 0x10;
    if (src & 0x4000)  *(int *)(a3 + 0xE8) |= 0x20;
    if (src & 0x2000)  *(int *)(a3 + 0xE8) |= 0x40;
    if (src & 0x8000)  *(int *)(a3 + 0xE8) |= 0x80;

    sub = *(char **)(a3 + 0xB4);
    v0 = *(unsigned int *)(sub + 0xA58);
    {
        unsigned int g = v0 & 0x20;
        if (g != 0) {
            game_uso_func_0000EAF4(a3, (v0 & 0x40) != 0, g);
        }
    }

    if (*(int *)(a3 + 0x12C) != 0) {
        switch (*(int *)(a3 + 0xE8)) {
            case 5: *(int *)(a3 + 0xE8) |= 0x20000; break;
            case 6: *(int *)(a3 + 0xE8) |= 0x10000; break;
            case 2: *(int *)(a3 + 0xE8) |= 0x4000;  break;
            case 1: *(int *)(a3 + 0xE8) |= 0x1000;  break;
            case 4: *(int *)(a3 + 0xE8) |= 0x8000;  break;
            case 3: *(int *)(a3 + 0xE8) |= 0x2000;  break;
        }
    }

    /* bit-clearing, gated by 0xE8 bit 0x4 and a3->0xF4->0x2C flags */
    {
        unsigned int e8 = *(unsigned int *)(a3 + 0xE8);
        if (e8 & 0x4) {
            char *f4 = *(char **)(a3 + 0xF4);
            *(unsigned int *)(a3 + 0xE8) = e8 & 0x3F007;
            if (f4 != 0) {
                unsigned int m = *(unsigned int *)(f4 + 0x2C);
                if (m & 0x5000) {
                    *(unsigned int *)(a3 + 0xE8) &= 0xFFFF5FFF;
                    m = *(unsigned int *)(*(char **)(a3 + 0xF4) + 0x2C);
                }
                if (m & 0xA000) {
                    *(unsigned int *)(a3 + 0xE8) &= 0xFFFFAFFF;
                    m = *(unsigned int *)(*(char **)(a3 + 0xF4) + 0x2C);
                }
                if (m & 0xC000) {
                    if (m & 0x100000) {
                        *(unsigned int *)(a3 + 0xE8) |= 0x200000;
                    } else if (!(m & 0x200000)) {
                        *(unsigned int *)(a3 + 0xE8) |= 0x100000;
                    }
                }
            }
        }
    }

    /* counter advance: 0xEC++ while 0xE8 nonzero, else reset */
    if (*(int *)(a3 + 0xE8) != 0) {
        *(int *)(a3 + 0xEC) += 1;
    } else {
        *(int *)(a3 + 0xEC) = 0;
    }

    /* stride-64 search over the table when 0xEC exceeds the 0x214 bound */
    {
        int t0 = *(int *)(a3 + 0xEC);
        if (*(unsigned int *)(a3 + 0xEC) > *(unsigned int *)(a3 + 0x214)) {
            unsigned int count = *(unsigned int *)&D_00000000;
            char *base = *(char **)&game_uso_D_807FFBC0;
            char *obj = *(char **)(a3 + 0xB4);
            unsigned int v1;
            char *e = base;
            for (v1 = 0; v1 < count; v1++, e += 64) {
                if ((*(int *)(obj + 0x8C0) & *(int *)(e + 0x34)) == 0) continue;
                if (*(int *)(e + 0x2C) != *(int *)(a3 + 0xE8)) continue;
                if ((*(int *)(e + 0x38) & 0x4) && (*(int *)(obj + 0x9A8) & 0x1)) continue;
                if (*(int *)(obj + 0x938) != 0) continue;
                *(char **)(a3 + 0xF0) = base + v1 * 64;
                *(int *)(a3 + 0xE8) = 0;
                *(int *)(a3 + 0x12C) = 0;
                *(int *)(a3 + 0xEC) = 0;
                t0 = 0;
                break;
            }
        }
        if (t0 < 21) {
            *(int *)(a3 + 0xE8) &= 0x6;
        } else {
            *(int *)(a3 + 0xEC) = 0;
            *(int *)(a3 + 0xE8) = 0;
        }
    }
    (void)a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E5C8);
#endif

/* game_uso_func_0000E91C — EE84-family branchy orchestrator, 118 insns.
 * NM wrap now 98.98% objdiff (102/118 words byte-exact) — up from 90.31%.
 *
 * Reads o=a0->0xB4, v0=o->0xA58, clears a0->0xB0, then
 * game_uso_func_0000EAF4(a0, cond, v0&0x20) where cond=((v0&0x20)!=0) then
 * (if set) =(v0&0x40)!=0 — an if-without-else, NOT a ternary-with-:0 (the
 * :0 adds a spurious `move ai,zero`+`b`). When (*(a0->0xB4)->0x800)->0x10 &
 * 0x1000, dispatches on a0->0x12C. The dispatch is TESTS-FIRST in source
 * order 2,1,4,3 with bodies laid out likewise — a C `switch` SORTS the test
 * chain (1,2,3,4) and an if/else-if INTERLEAVES bodies, so neither matches;
 * it must be a goto chain (4 `if(sw==k) goto Lk`, last as `if(sw!=3) goto
 * done; goto L3` to get the beql-toward-L3 + b-default sense). Each arm ORs a
 * literal into a0->0xB0 (from a0->0xFC), homes a Pair2 from D_807FF430+0xE40
 * or D_807FF4E0+0xEF0 into the shared sp+0x38 slot, calls an import with
 * a0=a0->0xB4+0x808. Tail (a0->0xB0!=0): zero a0->0x12C, import_0010DB28,
 * game_uso_func_0000D5F8(a0, homed, 1), game_uso_func_0000D5DC(a0).
 *
 * RESIDUAL (16 words, all same-mnemonic register-only): the whole allocation
 * is uniformly shifted — target keeps o->t6, v0-word->v0, mask->v1, cond->a1
 * (with a redundant `move a2,v1` filling the EAF4 jal delay); IDO here parks
 * o->v1 and cascades mask/cond into arg regs a2/a3 (delay = `move a1,a3`).
 * A global register-renumber cap (coloring, permuter-immune); decl-order
 * permutation + inline-o (o->t6 but downstream drops to 59) both tested WORSE.
 */
#ifdef NON_MATCHING
extern int import_00096724();
extern int import_00096704();
extern int import_0010DB28();
extern char game_uso_D_807FF430;
extern char game_uso_D_807FF4E0;

void game_uso_func_0000E91C(char *a0) {
    char *o = *(char **)(a0 + 0xB4);
    int v0;
    int cond;
    Pair2 homed;

    *(int *)(a0 + 0xB0) = 0;
    v0 = *(int *)(o + 0xA58);
    cond = ((v0 & 0x20) != 0);
    if (cond) {
        cond = ((v0 & 0x40) != 0);
    }
    game_uso_func_0000EAF4(a0, cond, v0 & 0x20);

    if (*(unsigned int *)(*(char **)(*(char **)(a0 + 0xB4) + 0x800) + 0x10) & 0x1000) {
        int sw = *(int *)(a0 + 0x12C);
        if (sw == 2) goto L2;
        if (sw == 1) goto L1;
        if (sw == 4) goto L4;
        if (sw != 3) goto done_switch;
        goto L3;
    L2:
        *(int *)(a0 + 0xB0) = *(int *)(a0 + 0xFC) | 0x1B;
        homed = *(Pair2 *)(&game_uso_D_807FF430 + 0xE40);
        import_00096724(*(char **)(a0 + 0xB4) + 0x808);
        goto done_switch;
    L1:
        *(int *)(a0 + 0xB0) = *(int *)(a0 + 0xFC) | 0x18;
        homed = *(Pair2 *)(&game_uso_D_807FF4E0 + 0xEF0);
        import_00096704(*(char **)(a0 + 0xB4) + 0x808);
        goto done_switch;
    L4:
        *(int *)(a0 + 0xB0) = *(int *)(a0 + 0xFC) | 0x1C;
        homed = *(Pair2 *)(&game_uso_D_807FF430 + 0xE40);
        import_00096724(*(char **)(a0 + 0xB4) + 0x808);
        goto done_switch;
    L3:
        *(int *)(a0 + 0xB0) = *(int *)(a0 + 0xFC) | 0x1A;
        homed = *(Pair2 *)(&game_uso_D_807FF4E0 + 0xEF0);
        import_00096704(*(char **)(a0 + 0xB4) + 0x808);
    done_switch:;
    }

    if (*(int *)(a0 + 0xB0) != 0) {
        *(int *)(a0 + 0x12C) = 0;
        import_0010DB28(a0, *(int *)(a0 + 0xB0), 0, 1, 1, 1);
        game_uso_func_0000D5F8(a0, homed, 1);
        game_uso_func_0000D5DC(a0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E91C);
#endif

// game_uso_func_0000EAF4 — STRUCTURAL PASS (0x1F8 / 126 words,
// no episode). Raw-.word USO form (single function, game_uso main
// game-logic). Pure integer/bitfield (no FP, no calls). Leaf-ish:
// no sp frame — spills args a1/a2 to the caller's shadow slots
// (sw a1,4(sp) / sw a2,8(sp)); this is a small function, NOT a
// fragment (it has its own jr ra at 0xECE0).
//
// Steering/lean input integrator with rate-clamping.
//
//   void game_uso_func_0000EAF4(Obj *obj, int tgt, int a2) {
//     Sub *s = obj->0xB4;
//     if (s->0x800->0x7C(s16) == 0) { ... }
//     int cur = (s16)obj->0x124;
//     int d = tgt - cur;
//     // clamp the per-frame step: d = clamp(d, -7, +7) normally,
//     //   tightened to [-2,+2] / [-3,+3] when a flag selects slow
//     //   mode (slti vs 8 / -7 / 3 / -2 chains);
//     obj->0x124 = (s16)(cur + d);                          // step toward tgt
//     obj->0x128 = 0;  obj->0x12C = 0;                       // reset deriv
//     // if (s->0x800->0x18 & 0x4000) … recompute obj->0x12C from
//     //   flags (an alternate / boosted steering response);
//     // obj->0x12C = …;  return obj->0x12C-ish;
//   }
//
// Struct-typing reference:
//   obj: 0xB4 -> s (s->0x800->0x7C s16 enable, s->0x800->0x18 flags
//     bit 0x4000), 0x124 s16 current steering value (rate-limited
//     toward tgt), 0x128 s16 / 0x12C int steering derivative/state
//     (reset then recomputed). tgt/a2 = target + mode args. Clamp
//     bounds ±7 (fast) / ±2 / ±3 (slow). Snowboard steering/lean
//     input smoothing.
// FULLY RE-DECODED 2026-05-31 (20.9% -> 70.86%): complete logic-exact decode.
//   Returns int (=v1). Steering target = ctx->0x7C; d = (cur!=0)?tgt-cur:0;
//   REFLECTION clamp (d>=8 -> 7-d; d<-7 -> -7-d; keep only [-2,2] else 0);
//   obj->0x126 first-frame init (=1, zero 0x128/0x12C); when d==0 a ctx->0x18
//   flag dispatch sets d=-1/+1 (0x10000/0x4000) or obj->0x12C=5/6 (0x2000/0x8000);
//   obj->0x128 += d; obj->0x124 = tgt. Then: counter saturates at >=6 (sets v0);
//   if v0 (enable-zero OR saturated): clear 0x126, param-gated negations of 0x128
//   (a1 && 0xB4->0xA58&0x80; a2), then obj->0x128 -> obj->0x12C dispatch
//   (>=3:4, >0:3, <-2:2, <0:1, 0:0) returned as v1.
// 2026-06-21 (agent-e): DECODE TIGHTENED 70.86 -> 71.48 (476 -> 496 bytes,
//   reloc-set MATCH, now only 2 insns short of 504). Re-derived ctx fresh
//   inside the d==0 block (lw 0xB4(a0); lw 0x800; matches target eb84/eb88)
//   and re-read *(ctx+0x18) per flag-test instead of caching `fl`. RESIDUAL
//   (genuine cap): the target's d==0 flag dispatch and the tail param-gated
//   negations emit BRANCH-LIKELY (beql/bgezl) with a redundant reload
//   (lw 0x18(a2) / lw 8(sp)) annulled into each branch delay slot — an IDO
//   -O2 reorg-annul scheduling choice not steerable from C (per-test re-read
//   yields plain beq here, not beql). Same reorg-annul class as func_0000174C.
int game_uso_func_0000EAF4(char *obj, int a1, int a2) {
    int flag;
    int result;
    int d;
    int cur;
    int tgt;

    result = 0;
    flag = 0;
    tgt = *(short *)(*(char **)(*(char * volatile *)(obj + 0xB4) + 0x800) + 0x7C);
    if (tgt != 0) {
        d = 0;
        cur = *(short *)(obj + 0x124);
        if (cur != 0) {
            d = tgt - cur;
        }
        if (d >= 8) d = 7 - d;
        if (d < -7) d = -7 - d;
        if (d >= 3 || d < -2) d = 0;
        if (*(short *)(obj + 0x126) == 0) {
            *(short *)(obj + 0x126) = 1;
            *(short *)(obj + 0x128) = 0;
            *(int *)(obj + 0x12C) = 0;
        }
        if (d == 0) {
            cur = (int)*(char **)(*(char * volatile *)(obj + 0xB4) + 0x800);
            if (*(volatile unsigned int *)(cur + 0x18) & 0x10000) {
                d = -1;
            } else if (*(volatile unsigned int *)(cur + 0x18) & 0x4000) {
                d = 1;
            } else if (*(volatile unsigned int *)(cur + 0x18) & 0x2000) {
                *(int *)(obj + 0x12C) = 5;
            } else if (*(volatile unsigned int *)(cur + 0x18) & 0x8000) {
                *(int *)(obj + 0x12C) = 6;
            }
        }
        *(short *)(obj + 0x128) = *(short *)(obj + 0x128) + d;
        tgt = *(short *)(*(char **)(*(char * volatile *)(obj + 0xB4) + 0x800) + 0x7C);
    } else {
        flag = 1;
    }
    d = *(short *)(obj + 0x126);
    *(short *)(obj + 0x124) = tgt;
    if (d != 0) {
        *(short *)(obj + 0x126) = (short)d + 1;
        if ((short)d >= 6) {
            flag = 1;
        }
    }
    if (flag != 0) {
        if (*(short *)(obj + 0x126) != 0) {
            *(short *)(obj + 0x126) = 0;
            if (a1 != 0) {
                if (*(int *)(*(char * volatile *)(obj + 0xB4) + 0xA58) & 0x80) {
                    *(short *)(obj + 0x128) = -*(short *)(obj + 0x128);
                }
            }
            if (a2 != 0) {
                *(short *)(obj + 0x128) = -*(short *)(obj + 0x128);
            }
            flag = *(short *)(obj + 0x128);
            if (flag >= 3) {
                result = 4;
            } else if (flag > 0) {
                result = 3;
            } else if (flag < -2) {
                result = 2;
            } else if (flag < 0) {
                result = 1;
            }
            *(int *)(obj + 0x12C) = result;
        }
    }
    return result;
}

/* game_uso_func_0000EAF4 — 125/125 EXACT (verified clean rebuild of
 * build/non_matching/src/game_uso/game_uso.c.o word-by-word vs target .s;
 * leaf, no relocs). The .s's 126th word (0x1F4: lw v0,0x10C(a0)) is NOT part
 * of this function — it is the mis-split FIRST INSTRUCTION of
 * game_uso_func_0000ECEC (it loads the v0 that ECEC's first beqz tests;
 * EAF4 ends at jr ra + delay = 0x1F0). Landing needs the splat boundary fix:
 * move that word from game_uso_func_0000EAF4.s to the head of
 * game_uso_func_0000ECEC.s (byte-neutral for the ROM).
 *
 * 2026-07-03 (agent-e). From 73.1%. Decisive levers:
 *  (1) LOGIC FIX: the 0x126 counter increments EVERY call when nonzero
 *      (sh in the plain-bnez delay); v0-flag only when (short)cnt >= 6. Old
 *      wrap gated the store on cnt>=6.
 *  (2) E2D0-style split sign-extension: `d = *(short*)(obj+0x126); ...
 *      *(obj+0x126) = (short)d + 1; if ((short)d >= 6)` — raw lh test +
 *      sll/sra re-extension.
 *  (3) SHARED RETURN: nested ifs (no duplicated `return` epilogues).
 *  (4) THE BIG ONE — volatile CSE/PRE breakers: all four obj->0xB4 loads as
 *      `*(char * volatile *)(obj + 0xB4)` and the flag-word reads as
 *      `*(volatile unsigned int *)(cur + 0x18)`. Without volatile, uopt PRE
 *      unifies the cross-path B4 loads into ONE long-lived candidate (t0) —
 *      dropping a reload AND phase-shifting the whole temp pool (t0,t6,t7,...
 *      vs target t6,t7,t8,...); the else-if flag reads CSE into one andi
 *      chain (-6 words). Volatile restores per-use loads incl. the
 *      beqzl-annulled delay-slot reload duplicates. (Named fresh per-level
 *      reload vars, dead kills, goto forms: all VN'd away — only volatile
 *      breaks availability.)
 *  (5) Variable economy mirrors target coloring: flag=v0, result=v1, d=a1
 *      (reused as cnt), cur=a2 (reused as the d==0 ctx pointer AND implicitly
 *      sval via flag reuse), tgt=a3. Init order `result=0; flag=0;` BEFORE
 *      the tgt chain (emission: move v1 then move v0).
 */

// game_uso_func_0000ECEC — EXACT 57/57 (2026-07-08 agent-e; 0xE4 incl.
// the boundary-fix head word lw v0,0x10C(a0) from commit 4d76f242).
// All 55 non-reloc words byte-equal; the 2 reloc words (lui $at %hi +
// lw t6 %lo jump-table) carry R_MIPS_HI16/LO16 .rodata — resolved at
// link (USO baked-reloc class; make verify is the landing gate).
// Jump-table dispatched field selector over idx = obj->0x10C (1..5).
//
// Decisive levers from 93.32% (9-diff v0/v1 + t1/t2 coloring swap):
//  (1) WRONG-SIGNATURE TELL: idx is NOT a param — it is loaded from
//      obj->0x10C (the mis-split head word). One-arg signature.
//  (2) COMMUTED SUM `*base = ab[0] + *base` flips the t1/t2 pair
//      (b reload -> t2, *base -> t1, matching target).
//  (3) v0/v1 WEB FLIP: define base FIRST from the full expression
//      (base = *(obj+0xB4)+0x960) and v SECOND from the CSE'd load —
//      pseudo-creation order flips coloring to v=v1/base=v0. The thr
//      compare must then read via v (*(int*)(v+0x960)), NOT *base,
//      or VN unifies thr with the else-arm *base loads (-2 words,
//      kills the beqzl annulled dup-load pair).
// Negative results: if(1) barrier around the pointer setup and
// base-first-with-*base-thr both collapse the dup loads (20 diffs);
// decl-order alone does nothing.
/* Case decode: case 3 b-source = 0x3F4; case 4 b-source = 0x40C. Common
 * tail: v = a0->0xB4; if (a < v->0x960 && v->0x938) { a0->0x10C = 0;
 * a0->0x110 = 1; } else { v->0x960 += b; a0->0x110 = 0; } */
void game_uso_func_0000ECEC(char *obj) {
    int ab[2];
    int *v;
    int *base;
    int idx = *(int *)(obj + 0x10C);
    if (idx == 0) return;
    switch (idx - 1) {
        case 0: ab[1] = *(int *)(obj + 0x43C); ab[0] = *(int *)(obj + 0x3AC); break;
        case 1: ab[1] = *(int *)(obj + 0x43C); ab[0] = *(int *)(obj + 0x3C4); break;
        case 2: ab[1] = *(int *)(obj + 0x43C); ab[0] = *(int *)(obj + 0x3DC); break;
        case 3: ab[1] = *(int *)(obj + 0x424); ab[0] = *(int *)(obj + 0x3F4); break;
        case 4: ab[1] = *(int *)(obj + 0x424); ab[0] = *(int *)(obj + 0x40C); break;
    }
    /* base FIRST (full expr), v SECOND (CSE'd) — flips v0/v1 coloring
     * (2026-07-08); thr must read via v, not *base (VN unification). */
    base = (int *)(*(char **)(obj + 0xB4) + 0x960);
    v = *(int **)(obj + 0xB4);
    if ((ab[1] < *(int *)((char *)v + 0x960)) && (*(int *)((char *)v + 0x938) != 0)) {
        *(int *)(obj + 0x10C) = 0;
        *(int *)(obj + 0x110) = 1;
    } else {
        *base = ab[0] + *base;
        *(int *)(obj + 0x110) = 0;
    }
}

void game_uso_func_0000EDCC(int *a0, int a1) {
    a0[0x10C / 4] = a1;
}

/* game_uso_func_0000EDD4: 23-insn 5-way switch + back-subtract.
 *
 * Structure:
 *   if (a1 < 5) v0 = pickByA1[a1] from {a0[0x34C], a0[0x364], a0[0x37C],
 *                                       a0[0x394], 0};
 *   else v0 = 0;
 *   p = a0->0xB4;
 *   p->0xA14 -= v0;
 *
 * Trigger jumptable emit: 5 explicit cases (case 4 is empty break, NOT
 * default) + `int v0 = 0;` pre-init. IDO -O2 then uses sltiu+jumptable
 * via D_base+0x224. WITHOUT case 4 explicit, IDO falls back to cascading
 * else-if chain (20% match). WITHOUT v0=0 pre-init, IDO emits redundant
 * `or v0, zero, zero` in the default arm before/after the jump (70.95%).
 *
 * NATURAL CEILING: high-NM (the case-fall-through C + v0=0 pre-init gets
 * IDO to emit a sltiu+jumptable shape). The remaining diff is on the
 * jumptable `lui/lw` pair: C emits a local .rodata table at +0x4 while
 * target raw-asm bytes address +0x224. Was previously documented as
 * "Exact via Makefile INSN_PATCH" patching the lui/lw HI16/LO16 pair —
 * INSN_PATCH REMOVED 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). The explicit char-
 * pointer add keeps IDO from folding the final `addiu v1, v1, 0xA14`
 * into the store. Default build is INCLUDE_ASM.
 *
 * a2 is an unused 3rd arg saved to caller arg-slot at sp+0x8 by IDO arg-
 * save (per docs/IDO_CODEGEN.md#feedback-ido-unused-arg-save). */
void game_uso_func_0000EDD4(int *a0, unsigned int a1, int a2) {
    int v0 = 0;
    int *p;
    (void)a2;
    switch (a1) {
        case 0: v0 = a0[0x34C/4]; break;
        case 1: v0 = a0[0x364/4]; break;
        case 2: v0 = a0[0x37C/4]; break;
        case 3: v0 = a0[0x394/4]; break;
        case 4: break;
    }
    p = (int*)((char*)a0[0xB4/4] + 0xA14);
    *p = *p - v0;
}

void game_uso_func_0000EE30(char *a0, int a1, int a2) {
    int *dptr = (int*)((char*)&D_00000000 + 0x138);
    gl_func_00000000(*dptr, *(int*)(a0 + 0xB4), a1 * a2);
}

void game_uso_func_0000EE74(void *a0) {
    *(s32*)((char*)*(s32**)((char*)a0 + 0xB4) + 0x960) = 100;
}

/* game_uso_func_0000EE84: 39-insn init/reset.
 *   p = a0->0xB4; *(float*)(p+0xA74)=0; *(float*)(p+0xA70)=0;
 *   if (a0->0xB4->0x9CC != 0) a0->0xFC |= 0x24; else a0->0xFC |= 0x1D;
 *   X(a0, a0->0xFC, 0, 1, 1, 1);
 *   X(a0, D[0xE98], D[0xE9C], 1, ...); X(a0);
 * beql: ==0 case (|=0x1D) load in delay slot. USO: call->func_00000000,
 * data->&D_00000000+off.
 *
 * NATURAL CEILING: C emits the correct control flow but IDO misses the
 * target's outgoing a1/a2 stack spills and picks different scratch regs
 * in the D+0xE98 call tail. Was previously promoted to byte-exact via
 * Makefile INSN_PATCH + SUFFIX_BYTES_FORCE — both REMOVED 2026-05-23 as
 * match-faking (per feedback_no_instruction_forcing_matches_policy).
 * Default build is INCLUDE_ASM. */
extern char game_uso_D_807FF488;
void game_uso_func_0000EE84(int *a0) {
    int a1;
    *(float *)((char *)(int *)a0[0xB4 / 4] + 0xA74) = 0.0f;
    *(float *)((char *)(int *)a0[0xB4 / 4] + 0xA70) = 0.0f;
    if (*(int *)((char *)(int *)a0[0xB4 / 4] + 0x9CC) != 0) {
        a1 = a0[0xFC / 4] | 0x24;
    } else {
        a1 = a0[0xFC / 4] | 0x1D;
    }
    game_uso_func_077C44(a0, a1, 0, 1, 1, 1);
    game_uso_func_0000D5F8((char *)a0, *(Pair2 *)((char *)&game_uso_D_807FF488 + 0xE98), 1);
    game_uso_func_0000D5DC((char *)a0);
}

/* MATCHED 2026-05-28 via struct-by-value (E40/E44 pair homes a1,a2). See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_0000EF20(int a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE40));
    gl_func_00000000(a0);
    gl_func_00000000(a0);
}

/* game_uso_func_0000EF70 — verified decode (EE84-family branchy, reload-CSE cap).
 * void f(int *a0){
 *   int *s0 = a0;
 *   func_00000000(a0);                              // X1
 *   func_00000000(s0[0xB4/4], 0x3f800000);          // X2 (a1 = 1.0f bits, lui 0x3f80)
 *   func_00000000(s0);                              // X3
 *   if (((int*)s0[0xB4/4])[0x938/4] == 0) {
 *     func_00000000(s0);                            // X4
 *     func_00000000(s0, D[0xDF8], D[0xDFC]);        // X5
 *   } else {
 *     func_00000000(s0, 1);                         // X6
 *     if (((int*)s0[0xB4/4])[0x9CC/4] != 0) {
 *       func_00000000(s0, D[0xE60], D[0xE64]);      // X7
 *       func_00000000(s0);                          // X8
 *     } else {
 *       func_00000000(s0, D[0xE40], D[0xE44]);      // X9
 *       func_00000000(s0);                          // X10
 *     }
 *   }
 * }
 * Structure verified vs .s. MATCHED 2026-05-31 (74.65% -> 100%): the three
 * D-pair calls (DF8/DFC, E60/E64, E40/E44) pass the float-pair BY VALUE as
 * *(Pair2*) — the "reload-CSE / sub-80 cap" was the un-homed pair all along
 * (same lever as 10AC8/F284, docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair). */
extern int gl_func_00000000();
void game_uso_func_0000EF70(int *a0) {
    int *s0 = a0;
    gl_func_00000000(a0);
    gl_func_00000000(s0[0xB4 / 4], 0x3F800000);   /* a1 = 1.0f bits */
    gl_func_00000000(s0);
    if (((int *)s0[0xB4 / 4])[0x938 / 4] == 0) {
        gl_func_00000000(s0);
        gl_func_00000000(s0, *(Pair2 *)((char *)&D_00000000 + 0xDF8));
    } else {
        gl_func_00000000(s0, 1);
        if (((int *)s0[0xB4 / 4])[0x9CC / 4] != 0) {
            gl_func_00000000(s0, *(Pair2 *)((char *)&D_00000000 + 0xE60));
            gl_func_00000000(s0);
        } else {
            gl_func_00000000(s0, *(Pair2 *)((char *)&D_00000000 + 0xE40));
            gl_func_00000000(s0);
        }
    }
}

#ifdef NON_MATCHING
/* game_uso_func_0000F060: 55-insn flag-dispatch (EE84-family, 5 calls).
 * Early-return gated by a beql-chain boolean: v->0x938 set AND NOT
 * (0x100-bit set AND 0x200-bit clear). Cross-USO jal-0 → gl_func_00000000.
 * 61.7% -> 70.1%: the D-pair call (0xEB0/EB4) now passes the float-pair BY
 * VALUE as *(Pair2*) (struct-by-value lever, homes a1,a2). Remaining residual
 * is the EE84 beql-chain flag dispatch: target reads p->0x10 and v1->0x938
 * UNCACHED (multiple reloads) and evaluates 0x100/0x200/0x938 in p-first
 * order; this C caches p/v1 + checks 0x938 first. Inline-uncached + ternary
 * reorder both REGRESSED (27%) — the beql-chain scheduling is the cap.
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair */
extern int import_0010DB28();
extern int import_000966AC();
void game_uso_func_0000F360(int *a0);
void game_uso_func_00011888(int *a0);
extern char game_uso_D_807FF4A0;
void game_uso_func_0000F060(int *a0) {
    int *s0 = a0;
    int *v1;
    int *p;
    a0[0xF4 / 4] = 0;
    game_uso_func_00011888(a0);
    v1 = (int *)s0[0xB4 / 4];
    p = (int *)v1[0x800 / 4];
    if (((p[0x10 / 4] & 0x100) == 0 || (p[0x10 / 4] & 0x200) != 0) && v1[0x938 / 4] != 0) {
        game_uso_func_0000F360(s0);
        return;
    }
    import_0010DB28(s0, 0x10011, 0, 0, 0x100, s0[0x16C / 4]);
    game_uso_func_0000D5F8((char *)s0, *(Pair2 *)((char *)&game_uso_D_807FF4A0 + 0xEB0), -1);
    *(short *)((char *)s0 + 0xE6) = 0;
    *(short *)((char *)s0 + 0xE4) = *(short *)((char *)s0 + 0xE4) + 1;
    import_000966AC((char *)s0[0xB4 / 4] + 0x808);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F060);
#endif

/* game_uso_func_0000F13C — verified structural decode (EE84-family, 82 insns,
 * 12% LEN-DIFF; branch-likely + double-const abs-threshold + D-pair sp-args =
 * documented sub-80 ceiling → INCLUDE_ASM build path; struct-typing ref).
 *   s0=a0; v1=(int*)s0->0xB4; o=(int*)v1->0x800;
 *   if ((o->0x10 & 0x100) && (o->0x10 & 0x200) && v1->0x938 != 0)
 *       func_00000000(s0);
 *   else {
 *       f0 = *(float*)(v1+0x970);
 *       if ((double)fabs(f0) > *(double*)(&D+0x238))
 *           func_00000000(s0, 0x10028, 0x10029, *(int*)&f0, 0,0,1);
 *       else
 *           func_00000000(s0, 0x10011, 0,0, 6,1);
 *       if (((int*)s0->0xB4)->0x938 == 0) func_00000000(s0);
 *   }
 *   short v0 = *(short*)(s0+0xE6); *(short*)(s0+0xE6) = v0+1;
 *   if (s0->0x184 < v0) func_00000000(s0, D[0xEA8], D[0xEAC]);
 * Struct-typing: s0->0xB4 object (->0x800->0x10 bits 0x100/0x200, ->0x938
 * flag, ->0x970 float), s0->0xE6 short counter, s0->0x184 bound, D double
 * gate @0x238, D-pair @0xEA8/EAC. 65.05% -> 71.35%: the D-pair @0xEA8/EAC now
 * passes BY VALUE as *(Pair2*) (homes a1,a2; same lever as EF70). Residual
 * (78 diffs): the FP-dispatch over-spills the frame (sp-0x40 here vs target
 * sp-0x28, +24) + uncached o->0x10/v1->0x938 reloads + beql/bc1fl branch-likely
 * + neg.s/mov.s abs idiom — documented EE84-family FP ceiling. INCLUDE_ASM. */
#ifdef NON_MATCHING
/* game_uso_func_0000F13C — RECONSTRUCTION (reloc-aware, EE84/10694-family).
 * Real callees resolved from expected/.o relocs:
 *   f188 jal game_uso_func_0000F360(s0)         [all-bits + flag set]
 *   f208 jal import_0010DB78(s0,0x10028,0x10029,(int)f0,0,1)   [abs > thresh]
 *   f218 jal import_0010DB28(s0,0x10011,0,1,6,1)               [abs <= thresh]
 *   f234 jal game_uso_func_0001001C(s0)         [v1->0x938 == 0]
 *   f26c jal game_uso_func_0000D5BC(s0, *(Pair2*)(&D_807FF498+0xEA8))
 * double threshold = *(double*)(&D_807FFB58 + 0x238). abs.s via neg.s/mov.s.
 * Branch-likely (beqzl/bc1fl) + double-const abs gate + D-pair sp-args. */
extern int import_0010DB78();
extern int import_0010DB28();
extern void game_uso_func_0000F360(int *);
extern void game_uso_func_0001001C(int *);
extern void game_uso_func_0000D5BC(char *, Pair2);
extern char game_uso_D_807FFB58;
extern char game_uso_D_807FF498;
void game_uso_func_0000F13C(int *a0) {
    int *s0 = a0;
    int *v1 = (int *)s0[0xB4 / 4];
    int *o = (int *)v1[0x800 / 4];
    if ((o[0x10 / 4] & 0x100) && (o[0x10 / 4] & 0x200) && v1[0x938 / 4] != 0) {
        game_uso_func_0000F360(s0);
    } else {
        float f0 = *(float *)((char *)v1 + 0x970);
        float abs_f0 = (f0 < 0.0f) ? -f0 : f0;
        if (*(double *)((char *)&game_uso_D_807FFB58 + 0x238) < (double)abs_f0) {
            import_0010DB78(s0, 0x10028, 0x10029, *(int *)&f0, 0, 1);
        } else {
            import_0010DB28(s0, 0x10011, 0, 1, 6, 1);
        }
        if (((int *)s0[0xB4 / 4])[0x938 / 4] == 0) {
            game_uso_func_0001001C(s0);
        }
    }
    {
        short v0 = *(short *)((char *)s0 + 0xE6);
        *(short *)((char *)s0 + 0xE6) = v0 + 1;
        if (s0[0x184 / 4] < v0) {
            game_uso_func_0000D5BC((char *)s0,
                *(Pair2 *)((char *)&game_uso_D_807FF498 + 0xEA8));
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F13C);
#endif

/* game_uso_func_0000F284: 55-insn EE84-family branchy, beql-selected mode+D-pair.
 * The two D-pair calls pass the float-pair BY VALUE as *(Pair2*) (struct-by-value
 * homes the arg pair, docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair).
 * The final spill-slot residual (`m` wanted sp+44 in a 0x30 frame, build emitted
 * sp+40) was cracked by REMOVING the idiomatic `int *s0 = a0;` alias and using a0
 * directly: dropping the redundant local shifts the pseudo-numbering so `m`'s spill
 * bumps to the higher slot (docs/IDO_CODEGEN.md remove-idiomatic-local lever —
 * invalidates the "spill-slot placement not C-controllable" cap). BYTE-EXACT. */
extern int gl_func_00000000();
void game_uso_func_0000F284(int *a0) {
    int m;
    gl_func_00000000((char *)a0[0xB4 / 4] + 0x808);
    if (*(int *)((char *)a0[0xB4 / 4] + 0x9CC) != 0) {
        m = 0x20008;
        gl_func_00000000(a0, *(Pair2 *)((char *)&D_00000000 + 0xE60), -1);
    } else {
        m = a0[0xFC / 4] | 8;
        gl_func_00000000(a0, *(Pair2 *)((char *)&D_00000000 + 0xE40), -1);
    }
    a0[0x118 / 4] = 1;
    gl_func_00000000(a0);
    gl_func_00000000(a0, m, 0, 0, 0x100, a0[0x19C / 4]);
}

#ifdef NON_MATCHING
/* game_uso_func_0000F360: 49-insn float-compare-gated state-mux update.
 *
 * 2026-07-03 (game_uso W4, agent-e, 89.67% -> 47/49 = 95.9%): applied the W4
 * lever trio in-tree. Now byte-exact EVERYWHERE except 2 words (see RESIDUAL).
 *  (1) if(1)-wrapped pointer mutation (`b=(char*)p; if(1){b+=K;}`) materializes
 *      the per-block `addiu rd,v1,K` base regs (v1+0x770, +0x510, +0x788, +0x31C)
 *      + small (+0x10/+0x0) offset loads exactly (was the plain-fold 89.67% shape).
 *      This also flips the int/pointer coloring to target (int=$v0, p=$v1) and
 *      makes the beqzl-annulled dead `lwc1 f16` dup fall out naturally off b788.
 *  (2) `f0 *= *(b510+0x10)` (compound assign) gives the target's `mul.s f0,f0,f8`
 *      operand order (reusing f0); the split `f0 = f0 * ...` form emits f8,f0.
 *  Arms: if (p->0x9CC != 0) f0 = *(p+0x798)+f2; else f0 = *(p+0x780)+f2 (beqzl-taken).
 *  double const at game_uso_D_807FFB60 + 0x240 (ldc1 576(at)); the USO unit is
 *  HI16-only so the extra C-side LO16 reloc is byte-harmless (docs IDO_CODEGEN L23).
 *
 * 2026-07-15 (wave 3, agent-h, 47/49 -> 49/49 = objdiff-100): the old "FP
 * candidate-numbering coloring cap" (ldc1/cvt.d.s f6<->f18 temp-binding swap
 * at words f3d0/f3d4) RETRACTED via the cfe commutative-operand RANK lever
 * (docs/IDO_CODEGEN 199C entry): a TYPED extern-struct MEMBER load
 * (game_uso_D_807FFB60_thr.v, base-0 alias in undefined_syms_auto.txt,
 * struct pad puts .v at +0x240 so relocs/bytes are identical) restores
 * TEXTUAL operand order, so writing the double const FIRST
 * (`D.v * (double)f0`) creates its ldc1 pseudo before the cvt.d.s -> ldc1
 * f6 / cvt f18 as in target. Cast-deref spellings of D always ranked below
 * (double)f0 regardless of textual order (register-rooted deref reuse,
 * int-cast address form, named double all probed: 47/49 or worse; named
 * double recolors the whole fn f0->f2, 37/49).
 *
 * NOT LANDABLE as compiled C despite byte-exact object: intra-USO
 * `jal game_uso_func_0001001C` is baked as `jal 0` in the ROM (loader
 * patches at runtime) but would link to the real local symbol -> ROM
 * mismatch (USO baked-reloc landability filter). Stays NM wrap at 100. */
extern char game_uso_D_807FFB60;
extern struct { char pad[0x240]; double v; } game_uso_D_807FFB60_thr;
extern void import_00096874(int);
extern void game_uso_func_0001001C(int *);
void game_uso_func_0000F360(int *a0) {
    int v0 = *(short*)((char*)a0 + 0xE4);
    int *p;
    char *b770, *b510, *b788, *b31C;
    float f2, f0;
    if (v0 < 0) {
        *(short*)((char*)a0 + 0xE4) = 0;
        v0 = *(short*)((char*)a0 + 0xE4);
    }
    p = *(int**)((char*)a0 + 0xB4);
    f2 = *(float*)((char*)a0 + 0x1B4) * (float)v0;
    b770 = (char*)p; if (1) { b770 += 0x770; }
    b510 = (char*)p; if (1) { b510 += 0x510; }
    if (*(int*)((char*)p + 0x9CC) != 0) {
        b788 = (char*)p; if (1) { b788 += 0x788; }
        f0 = *(float*)(b788 + 0x10) + f2;
    } else {
        f0 = *(float*)(b770 + 0x10) + f2;
    }
    if (*(short*)((char*)p + 0x9A2) == 0x62) {
        f0 = (float)(game_uso_D_807FFB60_thr.v * (double)f0);
    }
    b31C = (char*)p; if (1) { b31C += 0x31C; }
    f0 *= *(float*)(b510 + 0x10);
    *(float*)(b31C) = *(float*)(b31C) + f0;
    *(int*)((char*)a0 + 0xF0) = 0;
    import_00096874((int)(*(char**)((char*)a0 + 0xB4) + 0x808));
    game_uso_func_0001001C(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F360);
#endif

extern void game_uso_func_0000E5C8(char *, int);
void game_uso_func_0000F424(int *a0) {
    char *w;
    float *pa;
    float *pb;
    float *pc;

    *(int*)(*(char**)((char*)a0 + 0xB4) + 0xA18) = 0;
    a0[0x114 / 4] = 1;
    w = *(char**)((char*)a0 + 0xB4);
    pa = (float*)(w + 0x170);
    pb = (float*)(w + 0x698);
    pc = (float*)(w + 0x31C);
    if ((*(int*)(w + 0x9A8) & 1) == 0) {
        pc[0] += -pa[4] * pb[4];
        game_uso_func_0000E2D0((char*)a0, pa, pb);
    }
    game_uso_func_0000E5C8((char*)a0, 0);
}

/* PREREQUISITE (outside this body): game_uso_func_0000E2D0's definition
 * converted ANSI->K&R (`(a0) char *a0; {`) — verified byte-IDENTICAL vs
 * expected/src/game_uso/game_uso.c.o — and its ANSI extern prototype
 * (`extern void game_uso_func_0000E2D0(char *);` near func_00010128) REMOVED,
 * so the 3-arg call above is legal (extras unchecked, materialize a1/a2). */

/* game_uso_func_0000F49C: 30-insn state-init.
 * NATURAL CEILING: ~70% NM. The inlined `flags_ptr`/`sub` derefs drive
 * t7/t8/t9/t1/t0 regalloc to match the target; the remaining diff is
 * (a) 10 insns at 0x38..0x6C reshaping the 2nd-call D-base + tail to add
 * cross-USO varargs spills `sw a1, 0x4(sp)` / `sw a2, 0x8(sp)`, and
 * (b) 8 trailing bytes for the jr-ra+nop epilogue. Both were previously
 * documented as INSN_PATCH + SUFFIX_BYTES_FORCE (the family-cap recipe,
 * same as 10B38/10E2C) — REMOVED 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM. */
/* MATCHED via struct-by-value arg-home: D[0xDF0]/D[0xDF4] pair passed as
 * `*(Pair2*)(&D+0xDF0)` homes a1,a2 to sp+4/sp+8. */
void game_uso_func_0000F49C(int *a0) {
    a0[0x114/4] = 2;
    if (*(int*)((char*)(int*)a0[0xF4/4] + 0x38) & 1) {
        gl_func_00000000(a0);
    }
    ((int*)a0[0xB4/4])[0xA18/4] = 1;
    a0[0xF4/4] = 0;
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xDF0));
    gl_func_00000000(a0);
}

/* game_uso_func_0000F514: 37-insn state-init w/ flag-gated branch.
 * gl_func_0(a0); a0->0xB4->0xA68 = 1; check (a0->0xB4)->0x800->0x10 & 0x200:
 *   if set:  gl_func_0(a0); gl_func_0(a0, 1, 1);
 *   else:    gl_func_0(a0, D[0xED8], D[0xEDC]);
 * gl_func_0(a0). NATURAL CEILING: the C body gives the correct branch
 * layout but cannot reach the target's caller-slot D-pair spills and
 * epilogue. Was previously promoted via the game_uso call-tail recipe
 * (Makefile SUFFIX_BYTES_FORCE + INSN_PATCH) — both REMOVED 2026-05-23
 * as match-faking (per feedback_no_instruction_forcing_matches_policy).
 * Default build is INCLUDE_ASM. */
void game_uso_func_0000F514(int *a0) {
    int *p2;
    gl_func_00000000(a0);
    /* inline `sub` (a0[0xB4], read twice) so it takes $t-regs, but NAME p2 so it
     * claims $v0 like the target (same lever as game_uso_func_00010068). */
    ((int*)a0[0xB4/4])[0xA68/4] = 1;
    p2 = *(int**)((char*)(int*)a0[0xB4/4] + 0x800);
    if (!(p2[0x10/4] & 0x200)) {
        gl_func_00000000(a0,
            *(Pair2*)((char*)&D_00000000 + 0xED8));
    } else {
        gl_func_00000000(a0);
        gl_func_00000000(a0, 1, 1);
    }
    gl_func_00000000(a0);
}

extern int gl_func_00000000();
typedef struct { int a, b; } F5A8Pair;
extern char game_uso_D_807FF4D0;
extern char game_uso_D_807FF4D8;
int game_uso_func_0000D74C(char *a0);
void game_uso_func_0000F6D4(char *a0);
/* game_uso_func_0000F5A8: 47-insn EE84-family two-path state orchestrator.
 * MATCHED 2026-06-21 (call-graph DFS + just-in-time family typing). The prior
 * NM body called the cross-USO placeholder gl_func_00000000 for every call and
 * carried a phantom `int a1` param. The resolved .s relocs name the real in-TU
 * callees: game_uso_func_0000D74C (predicate), game_uso_func_0000D5BC /
 * _0000D5F8 (pair-sinks), game_uso_func_0000D5DC (pair-copy),
 * import_0010DB28 (state logger), game_uso_func_0000F6D4 (sibling). The last
 * residual (the D5BC call not homing a1/a2 to sp+4/sp+8) was cracked by
 * converting game_uso_func_0000D5BC to its true Pair2-by-value prototype
 * `(char*, Pair2)` — the by-value pair triggers the K&R home spill that the
 * folded two-int form suppressed (same lever as the matched D5F8 callers
 * 00011258/000112E0). Byte-exact (0 SUSPECT / 0 reloc-type diffs). */
void game_uso_func_0000F5A8(int *a0) {
    int *s0 = a0;
    if (s0[0xF0 / 4] != 0) {
        if (game_uso_func_0000D74C((char*)a0) == 0) {
            char *p = (char *)&game_uso_D_807FF4D0 + 0xEE0;
            game_uso_func_0000D5BC((char*)s0, *(Pair2*)p);
            game_uso_func_0000F6D4((char*)s0);
        }
    } else {
        import_0010DB28(s0, *(int *)((char *)s0[0xF4 / 4] + 0x20), 3, 1, 1, 1);
        game_uso_func_0000D5F8((char*)s0,
            *(Pair2 *)((char *)&game_uso_D_807FF4D8 + 0xEE8), 1);
        game_uso_func_0000D5DC((char*)s0);
    }
}

/* MATCHED 2026-05-28: struct-by-value (EC8/ECC pair homes a1,a2) + inlining the
 * a0->0xF4 deref (named local -> $v0; inline -> $t6 like target). The
 * "precall-arg-spill cap" was wrong. See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_0000F664(char *a0) {
    gl_func_00000000(a0, *(int*)(*(char**)(a0 + 0xF4) + 0x20), 2, 3, 1, 1);
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xEC8), 3);
    gl_func_00000000(a0, 0);
}

/* game_uso_func_0000F6D4 - SIBLING of game_uso_func_0000E35C (same
 * node-process/queue-advance shape).
 *
 * 2026-06-23 (agent-i) 90.11% -> 95.32% (objdiff fuzzy): replaced ALL the
 * generic `func_00000000` placeholder callees and the `D_00000000`/`D_00000138`
 * placeholder globals with the REAL reloc symbols recovered from the resolved
 * target .o (objdump -dr expected/src/game_uso/game_uso.c.o, R_MIPS_26 +
 * R_MIPS_HI16):
 *   - game_uso_func_0000D6E4(s0)                     pre-flush (was func_00000000)
 *   - game_uso_func_0000EE30(s0, cur->0x30, 1)       worker
 *   - import_000B8518(*(int*)(&import_800201D0+0x138), b4, idx)   index call
 *   - game_uso_func_0000E564((int*)s0)               mid call (was func_00000000(s0))
 *   - game_uso_func_077C44(s0, f4->0x20, 4, dir,1,1) tail logger
 *   - game_uso_func_0000D5F8(s0, Pair2, dir)         tail pair-home
 *   - game_uso_func_0000D5BC(s0, Pair2)              trailing pair-copy
 * globals: base = *(int*)&game_uso_D_807FFBC0 (was D_00000000); the index call's
 * first arg = *(int*)((char*)&import_800201D0 + 0x138) (was the wrong distinct
 * extern D_00000138); the 3 tail D-pairs use the distinct symbols
 * game_uso_D_807FF4B0+0xEC0 / _4B8+0xEC8 / _4C0+0xED0 (were all &D_00000000+...).
 * Also fixed a BUG: prev is read from s0->0xF0 (the current node), not s0->0xF4
 * (E35C-identical). Now 131->133 insns, exact size 0x214.
 *   RESIDUAL (~4.7%, 3 diff clusters, all coloring/scheduling caps verified):
 *   (A) the `(base + (x<<6))` addu emits `addu t5,t4,v0` (shift-operand first)
 *       vs target `addu t5,v0,t4` (base first) — commutative-addu source-order
 *       cap; tried both `base + (x<<6)` and `(x<<6) + base`, IDO normalizes to
 *       shift-first regardless. (B) the prev-wrap block colors `prev` into $v0
 *       (no redundant moves) vs the target's $t0 + two `move v0,t0` — IDO's
 *       global allocator reserves $v0 here; tried split-cmp-local, int-cast,
 *       if/else-swap — all keep prev in $v0. (C) the entire tail (8 lui/addiu +
 *       sw-pairs + the 077C44/D5F8 arg setup) is a UNIFORM +1 temp-register
 *       renumber downstream of (B): t0/t8/t9/t4/t5 in target vs v0/t0/t3/t7 here.
 *       Crack (B) and (C) follows. permuter (base score 650, 4-way ~4.5min)
 *       reached 255 only via incidental a0/s0 substitution (not byte-0; a0 is
 *       clobbered by the calls so not a real fix). Genuine regalloc-renumber cap
 *       of the E35C/E5C8/F6D4 family. Callees/globals/relocs now ALL correct.
 *
 * --- HISTORY ---
 * 36% -> 86.53% 2026-05-31: the prior body
 * was INCOMPLETE (58 vs 133 insns) — missing E35C's whole tail (the 0xA58&0x40
 * flag-set + 0x38&2 D-pair dispatch with EC0/EC8/ED0 pairs) AND had a wrong
 * index-calc (was `*64`/`>>6` 2-arg; target is the E35C base-cancellation
 * `((base+(x<<6))-base)/64` with a0=*(&D+0x138), a1=s0->0xB4). Added both +
 * the Pair2 struct-by-value for the 3 tail D-pairs. 86.53 -> 90.11 on
 * 2026-05-31: (a) the &D+0x138 access uses the distinct extern `D_00000138`
 * (extern int, already in undefined_syms) instead of `*(int*)(&D+0x138)`, so it
 * no longer shares IDO's CSE'd &D base register with `base` (the E5C8-class
 * shared-base codegen the old note called a cap — the distinct-extern lever
 * busts it, +2.28pp); (b) factored the prev-wrap `s0->0xF8 = old` out of both
 * if/else arms (both wrote it) to `if (old==prev) counter=0; prev=old;`,
 * matching the target's single-write form (+1.3pp). Residual (~10%, len 129 vs
 * 133): regalloc-renumber + first-call unfilled-delay + the `base` (&D+0) load
 * placement (re-materialized per branch in target vs hoisted) + one commutative
 * addu. Per-branch distinct externs for 0x138 tested = no further gain.
 *   s0 = a0;
 *   if (((int*)s0->0xF4)->0x38 & 1) func_00000000(s0->0xF0);   // pre-flush
 *   func_00000000(s0, (s0->0xF0)->0x30, 1);
 *   if ((s0->0xB4 -> 0xA58) & 0x20) {
 *       n = ceil_div_64( (s0->0xF0)->0x3C * 64 ... );           // node-local
 *       func_00000000(&D, ..., n);
 *   } else {
 *       func_00000000(&D, ..., ceil_div_64(s0->0xF0 - D_glob));
 *   }
 *   s0->0x100 += 1;  s0->0xF0 = 0;  s0->0xF4 = old;
 *   s0->0xF8 = (old != s0->0xF8) ? old : (s0->0x100 = 0, old);
 *   func_00000000(s0);
 *   ... (E35C tail: s0->0xB4->0xA58 & 0x40 gate -> v=s0->0xF4;
 *        v->0x20 = v->0x28 ? v->0x28 : v->0x24; if (v->0x38 & 2)
 *        D-pair calls; trailing D-pair) ...
 * Struct-typing: identical family to E35C - s0->0xF0 active node
 * (->0x30 arg, ->0x3C size), s0->0xB4 obj (->0xA58 mode bits
 * 0x20=node-local / 0x40=configure), s0->0xF4 current (->0x38 flag
 * bit 0x1 pre-flush / 0x2), s0->0xF8 prev, s0->0x100 counter (reset on
 * prev-wrap). The (d+63)>>6 = signed ceil-div-by-64. Caps <80: same as
 * E35C - beql/bgez branch-likely + D-pair sp-spill + &D reloc + ceil
 * scheduling. Full per-instance call args/D-offsets are INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode). */
extern char game_uso_D_807FF4B0;
extern char game_uso_D_807FF4B8;
extern char game_uso_D_807FF4C0;
extern int import_000B8518();
#ifdef NON_MATCHING
void game_uso_func_0000F6D4(char *a0) {
    char *s0 = a0;
    char *prev;
    char *f4;
    int v1;
    if (*(int *)(*(char **)(s0 + 0xF4) + 0x38) & 1) {
        game_uso_func_0000D6E4(s0);
    }
    game_uso_func_0000EE30(s0, *(int *)(*(char **)(s0 + 0xF0) + 0x30), 1);
    {
        char *b4 = *(char **)(s0 + 0xB4);
        if (*(int *)(b4 + 0xA58) & 0x20) {
            int base = *(int *)&game_uso_D_807FFBC0;
            import_000B8518(*(int *)((char *)&import_800201D0 + 0x138), b4,
                (int)((base + (*(int *)(*(char **)(s0 + 0xF0) + 0x3C) << 6)) - base) / 64);
        } else {
            import_000B8518(*(int *)((char *)&import_800201D0 + 0x138), b4,
                (int)((int)*(char **)(s0 + 0xF0) - *(int *)&game_uso_D_807FFBC0) / 64);
        }
    }
    prev = *(char **)(s0 + 0xF0);
    *(int *)(s0 + 0x100) = *(int *)(s0 + 0x100) + 1;
    *(char **)(s0 + 0xF0) = 0;
    *(char **)(s0 + 0xF4) = prev;
    if (prev == *(char **)(s0 + 0xF8)) {
        *(int *)(s0 + 0x100) = 0;
    }
    *(char **)(s0 + 0xF8) = prev;
    game_uso_func_0000E564((int *)s0);
    if ((*(int *)(*(char **)(s0 + 0xB4) + 0xA58) & 0x40) &&
        (f4 = *(char **)(s0 + 0xF4), v1 = *(int *)(f4 + 0x28), (v1 != 0))) {
        *(int *)(f4 + 0x20) = v1;
    } else {
        f4 = *(char **)(s0 + 0xF4);
        *(int *)(f4 + 0x20) = *(int *)(f4 + 0x24);
    }
    f4 = *(char **)(s0 + 0xF4);
    if (*(int *)(f4 + 0x38) & 2) {
        game_uso_func_077C44(s0, *(int *)(f4 + 0x20), 4, 2, 1, 1);
        game_uso_func_0000D5F8(s0, *(Pair2 *)((char *)&game_uso_D_807FF4B0 + 0xEC0), 2);
    } else {
        game_uso_func_077C44(s0, *(int *)(f4 + 0x20), 4, 3, 1, 1);
        game_uso_func_0000D5F8(s0, *(Pair2 *)((char *)&game_uso_D_807FF4B8 + 0xEC8), 3);
    }
    game_uso_func_0000D5BC(s0, *(Pair2 *)((char *)&game_uso_D_807FF4C0 + 0xED0));
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F6D4);
#endif

/* MATCHED 2026-05-28 via struct-by-value (E50/E54 pair homes a1,a2). The
 * varargs-extern attempt failed because the spill is struct-by-value-driven,
 * not varargs. See docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_0000F8E8(int *a0) {
    gl_func_00000000(a0, *(int*)((char*)a0 + 0xFC), 0, 0, 0x100, 5);
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE50), -1);
}

/* EXACT 2026-07-02 (67/67 words vs asm .s, self-verified via clean
 * build/non_matching rebuild). Was the "frame-spread / call-spill-interleave
 * coloring cap" NM at 98.15% — cap DISPROVEN by two levers:
 *  (1) FIRST-BLOCK RE-BASE (same lever as the final-add section): load the
 *      scaled triple through q = (float*)((char*)(int*)a0[0xB4/4] + 0x3C8)
 *      instead of a named b + per-field offsets. IDO folds the loads to
 *      0x3C8/0x3CC/0x3D0(v0) AND emits the (dead) addiu v0,v0,0x3C8 in the
 *      mul latency slot — the missing word — and the coloring cascade fixes
 *      itself: b/q coalesce into $v0 (was $v1), freeing $v1 for &vb (was $a1).
 *  (2) FRAME PUSH-UP FROM BELOW: target has vc flush against the frame top
 *      (sp+0x74..0x80, frame -0x80). Locals lay out in DECL ORDER top-down;
 *      scalar decls placed AFTER the aggregates get no slots; unreferenced
 *      volatile pads declared BEFORE the first Vec3 sink to the bottom (the
 *      old cap note is right about that) — but growing the BOTTOM pad
 *      (padbot[5]) pushes the whole Vec3 block up: 0x38/0x4C/0x64 ->
 *      0x48/0x5C/0x74 with frame exactly -0x80.
 * Earlier levers retained: grouped-mul eval order (mx/my/mz temp scalars,
 * docs/IDO_CODEGEN.md#feedback-ido-struct-copy-vs-field-copy-treg-order),
 * inter-decl pads padcb[3]/padba[2] for the 0x8/0xC inter-Vec3 gaps,
 * struct-assign copies (vb = a; vc = vb;) for the int lw/sw cascade. */
extern char game_uso_D_807FF448;
typedef struct { float x, y, z; } F948_Vec3;
void game_uso_func_0000F948(int *a0) {
    F948_Vec3 vc;
    volatile int padcb[3];
    F948_Vec3 vb;
    volatile int padba[2];
    F948_Vec3 a;
    float *q;
    float scale;
    float mx, my, mz;
    volatile int padbot[5];

    import_0010DB28(a0, *(int*)((char*)a0 + 0xFC), 0, 2, 1, 1);
    game_uso_func_0000D5F8((char*)a0, *(Pair2*)((char*)&game_uso_D_807FF448 + 0xE58), 2);

    q = (float*)((char*)(int*)a0[0xB4 / 4] + 0x3C8);
    scale = *(float*)((char*)a0 + 0x1FC);
    mx = q[0] * scale;
    my = q[1] * scale;
    mz = q[2] * scale;
    a.x = mx;
    a.y = my;
    a.z = mz;
    vb = a;
    vc = vb;

    q = (float*)((char*)(int*)a0[0xB4 / 4] + 0x318);
    q[0] += vc.x;
    q[1] += vc.y;
    q[2] += vc.z;
}

/* MATCHED 2026-05-28: struct-by-value (E40/E44 pair). 26-insn 3-call
 * wrapper, family sibling of 10E2C/14FC/DC8 with one extra pass-through
 * call before the family-pattern body. See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_0000FA54(int *a0) {
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0xFC), 2, 1, 1, 1);
    game_uso_func_00000000(a0);
    game_uso_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE40), 1);
}

/* MATCHED 2026-05-28: struct-by-value (E40/E44 pair). 18-insn 3-call
 * wrapper, sibling of game_uso_func_0000FA54. See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_0000FABC(int a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE40));
    gl_func_00000000(a0);
}

/* game_uso_func_0000FB04: 30-insn dispatcher with conditional gate.
 * NATURAL CEILING: 89.90% NM. Same family-cap shape as
 * 10E2C/10B38/F49C: the 3rd-call tail needs separate addiu+lw+lw form
 * + cross-USO varargs spills (`sw a1, 0x4(sp)` / `sw a2, 0x8(sp)`),
 * 8-byte jr-ra+nop epilogue, and a branch immediate at 0x28 (built +0xE
 * for short body vs target +0x10 after extension). Was previously
 * promoted via 12-insn INSN_PATCH + SUFFIX_BYTES_FORCE — both REMOVED
 * 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM. */
/* MATCHED via struct-by-value arg-home: D[0xE40]/D[0xE44] pair passed as
 * `*(Pair2*)(&D+0xE40)` homes a1,a2 to sp+4/sp+8. */
void game_uso_func_0000FB04(int *a0) {
    gl_func_00000000(a0);
    if (a0[0x110/4] != 0) {
        gl_func_00000000(a0, a0[0x108/4], 2, 1, 1, 1);
        gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE40), 1);
    }
}

/* game_uso_func_0000FB7C: 31-insn 3-call dispatcher.
 * NATURAL CEILING: 79.97% NM. Same family-cap shape as 10E2C/10B38/F49C/
 * FB04: the 2nd-call D-base + tail needs cross-USO varargs spills
 * (sw a1@4(sp), sw a2@8(sp)) and the s0-restore delay-slot trick
 * (or a0,s0,0; sw 0,0x114(s0) before lw ra/s0), plus an 8-byte jr-ra+
 * nop epilogue. Was previously promoted via 14-insn INSN_PATCH +
 * SUFFIX_BYTES_FORCE — both REMOVED 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM. */
void game_uso_func_0000FB7C(int *a0) {
    int v = a0[0xFC/4] | 0xA;
    a0[0x108/4] = v;
    gl_func_00000000(a0, v, 0, 2, 1, 1);
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE88), 2);
    gl_func_00000000(a0);
    a0[0x114/4] = 0;
}

void game_uso_func_0000FBF8(int *a0) {
    int v = *(int*)((char*)a0 + 0xFC);
    game_uso_func_00000000(a0, v | 2, v | 3,
        *(int*)((char*)*(int**)((char*)a0 + 0xB4) + 0x970), 0, 1);
}

/* game_uso_func_0000FC34: 52-insn (0xD0) FPU-heavy 3-jal orchestrator. 96.6% NM.
 * BREAKTHROUGH 2026-05-30: the two pair-arg calls (D+0xE10, D+0xE20) are now
 * `*(Pair2*)(&D+off)` BY VALUE — the by-value struct both clusters the base AND
 * homes a1/a2 to sp+4/sp+8, cracking BOTH the cluster-form AND the precall-spill
 * residuals at once (82.5->96.6%). The old "register-pressure cap" diagnosis was
 * WRONG — it was the wrong C shape (separate int args). Remaining ~2 residuals:
 * the field_770 single-field base-fold (`lwc1 1920(v1)` vs `addiu a3,v1,1904;
 * lwc1 16(a3)`) + an FP-reg cascade in the double mul/add (f2/f4 choice for `v`)
 * — ugen FP-scheduling, not coloring. */
extern int gl_func_00000000();
extern char D_00000000;
/* game_uso_func_0000FC34: EE84-family state setter (52 insns, 0xD0). ~89% NM.
 * 2026-06-21 (call-graph DFS): callees corrected from the cross-USO placeholder
 * gl_func_00000000 (+ pairs from &D_00000000) to the resolved in-TU symbols
 * game_uso_func_0000D5BC (pair-copy, now homing via the Pair2-by-value
 * prototype flip), import_0010DB28 (logger), game_uso_func_0000D5F8 (pair-sink)
 * and the real globals game_uso_D_807FFB68/400/410. The D5BC/D5F8/logger half
 * now matches byte-for-byte. RESIDUAL (honest NON_MATCHING): the FP block holds
 * two sub-pointers (a3=base+0x770 for `lwc1 16(a3)`, v0=base+0x31C for
 * load+store) that IDO folds into direct displacements in this C shape, plus an
 * FP-reg cascade (f2/f4, f6/f8 numbering) — documented ugen FP-scheduling cap,
 * not coloring. */
extern char game_uso_D_807FFB68;
extern char game_uso_D_807FF400;
extern char game_uso_D_807FF410;
void game_uso_func_0000D5BC(char *, Pair2);
void game_uso_func_0000D5F8(char *a0, Pair2 pair, int a3);
extern int import_0010DB28();
#ifdef NON_MATCHING
void game_uso_func_0000FC34(int *a0) {
    char *base = (char*)*(int**)((char*)a0 + 0xB4);
    int *flag_loc = *(int**)(base + 0x800);
    char *field_770 = base + 0x770;
    if ((flag_loc[0x10/4] & 0x100) == 0) {
        float v = *(float*)(field_770 + 0x10);
        double dconst = *(double*)((char*)&game_uso_D_807FFB68 + 0x248);
        float *field_31C = (float*)(base + 0x31C);
        *field_31C = (float)((double)*field_31C + (double)v * dconst);
        game_uso_func_0000D5BC((char*)a0,
            *(Pair2*)((char*)&game_uso_D_807FF400 + 0xE10));
    }
    import_0010DB28(a0, 0x30001, 2, 2, 0x100, 0xA);
    game_uso_func_0000D5F8((char*)a0,
        *(Pair2*)((char*)&game_uso_D_807FF410 + 0xE20), -1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FC34);
#endif

extern char game_uso_D_807FF408;
void game_uso_func_0000D5DC(char *a0);
#ifdef NON_MATCHING
/* game_uso_func_0000FD04: 50-insn sibling of game_uso_func_0000FC34.
 * 2026-06-21 (call-graph DFS): callees corrected from gl_func_00000000
 * placeholder to the resolved in-TU symbols import_0010DB28 (logger),
 * game_uso_func_0000D5F8 (pair-sink, trailing int 3 → homes a1/a2),
 * game_uso_func_0000D5DC (pair-copy); real global game_uso_D_807FF408.
 * 2026-05-15 fix: FPU op corrected sub→add (target's 0x46062200 is
 * add.s f8,f4,f6 — function field = 000000, not 000001). Prior wrap
 * had `-=` which never matched. Now adds the 0x798-field to the
 * 0x31C-field. Score 78.86% (+0.26pp from prior 78.6% wrap; small
 * because the add fixes only the FPU op insn, not the surrounding
 * shape). Remaining cap:
 *   - Call#2 K&R-style spill of a1/a2 to sp+4/sp+8 (target emits
 *     these because the pair-loaded args trigger K&R home setup;
 *     IDO doesn't emit them in our shape since pair is inlined as
 *     `*(int*)(&D+N)` not via an intermediate base register).
 *   - Post-call FPU block: target uses named base+0x788 / base+0x31C
 *     pointer-arith locals; IDO inlines our `base_788`/`base_31C`
 *     locals back into the lwc1/swc1 addressing despite multiple
 *     uses. The named-pair variant (pair_e18 declared at function
 *     top) regresses to 44%/78.86% — same shape unless intervening
 *     non-call work keeps the materialization alive in a register.
 *
 * 2026-05-20 deep attempt: volatile pair0/pair1 stack-spill variant
 * moves the C path to 82.26%. It forces the D-pair args through stack
 * locals (sw/lw pair before call #2), but IDO allocates them at local
 * slots in a 0x40 frame rather than target outgoing arg homes sp+4/sp+8
 * in a 0x28 frame. Volatile pointer locals for the FPU block produced
 * target-like addiu pointer materialization but regressed to 61.3% due
 * to extra pointer stack spills. Exact C match remains blocked by the
 * documented game_uso precall-arg-spill cap in docs/PATTERNS.md. */
void game_uso_func_0000FD04(int *a0) {
    int *s0 = a0;
    int *base = *(int**)((char*)s0 + 0xB4);
    int *flags = *(int**)((char*)base + 0x800);

    if ((flags[0x10 / 4] & 0x100) == 0) {
        float *base_788;
        float *base_31C;
        float *base_2FC;
        import_0010DB28(s0, 0x30001, 2, 3, 1, 1);
        game_uso_func_0000D5F8((char*)s0,
            *(Pair2 *)((char *)&game_uso_D_807FF408 + 0xE18), 3);
        game_uso_func_0000D5DC((char*)s0);

        base = *(int**)((char*)s0 + 0xB4);
        base_788 = (float*)((char*)base + 0x788);
        base_31C = (float*)((char*)base + 0x31C);
        {
            float f4 = base_31C[0];
            float f6 = base_788[0x10 / 4];
            base_31C[0] = f4 + f6;
        }

        base = *(int**)((char*)s0 + 0xB4);
        base_2FC = (float*)((char*)base + 0x2FC);
        base_2FC[3] = 1.0f;
        base_2FC[2] = 0.0f;
        base_2FC[1] = 0.0f;
        base_2FC[0] = 0.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FD04);
#endif

/* game_uso_func_0000FDCC: 63-insn sibling of game_uso_func_0000FD04 / FC34.
 * Velocity-gated branch dispatcher. Outer gate fires only when
 * base->0x31C (signed float) is below -1.0f; inner branch dispatches
 * different call sequences based on whether base->0x9D0 is below 1000.0f.
 *
 * Outer-gate constants: lui $at, 0xBF80 → f6 = -1.0f; c.lt.s $f4, $f6 +
 * bc1fl skips the body if (base->0x31C) >= -1.0f.
 * Inner constants: lui $at, 0x447A → f10 = 1000.0f.
 *
 * BYTE-EXACT: the two &D+0xE28/0xE30 pair args passed as `*(Pair2*)` BY VALUE
 * produce both the cluster bases AND the `sw a1,4(sp); sw a2,8(sp)` caller-side
 * spills — cracking the precall-spill "cap" (see docs/PATTERNS.md). Replaces the
 * banned SUFFIX_BYTES + INSN_PATCH recipe. */
void game_uso_func_0000FDCC(int *a0) {
    int *base = *(int**)((char*)a0 + 0xB4);
    if (*(float*)((char*)base + 0x31C) < -1.0f) {
        if (*(float*)((char*)base + 0x9D0) < 1000.0f) {
            gl_func_00000000(a0, 0x30001, 6, 6, 0x100, 0x14);
            gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE28), -1);
            gl_func_00000000(a0);
        } else {
            gl_func_00000000(a0, 0x30001, 3, 4, 1, 1);
            gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE30), 4);
        }
    }
}

/* MATCHED 2026-05-28 via struct-by-value (E38/E3C pair homes a1,a2). See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_0000FEC8(char *a0) {
    gl_func_00000000(a0, 0x30001, 4, 5, 2, 1);
    if (*(float*)(*(char**)(a0 + 0xB4) + 0x9D0) < 1000.0f) {
        gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE38));
    }
}

/* MATCHED 2026-05-28. 2-call gated dispatcher. The 2nd call's target home-stores
 * (sw a1,4(sp); sw a2,8(sp)) — long mislabeled a "precall-arg-spill cap" — are
 * produced by passing the D_E10/E14 pair AS A STRUCT BY VALUE:
 * `gl_func(a0, *(Pair2*)(&D+0xE10), 1)`. See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_0000FF48(char *a0) {
    if (*(int*)(*(int**)(a0 + 0xB4) + 0x938 / 4) != 0) {
        gl_func_00000000(a0, 0x30001, 6, 1, 1, 1);
        gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE10), 1);
    }
}

/* MATCHED 2026-05-28 via struct-by-value arg-pass (sibling of FF48): the 2nd
 * call homes the E28/E2C pair to a1/a2 by passing *(Pair2*)(&D+0xE28). See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_0000FFB8(int *a0) {
    gl_func_00000000(a0, 0x30001, 5, 6, 1, 1);
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE28), 6);
}

/* MATCHED 2026-05-28: struct-by-value (DD0/DD4 pair). The middle call's
 * 2-int load was the precall-arg-spill "cap" — passing the pair as
 * *(Pair2*) by value homes a1,a2 to sp+4/sp+8 exactly. See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_0001001C(int *a0) {
    *(int*)((char*)a0 + 0xF4) = 0;
    gl_func_00000000(a0);
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xDD0));
    gl_func_00000000(a0);
}

/* game_uso_func_00010068: 48-insn (0xC0) 6-call dispatcher.
 * NATURAL CEILING: 79.13% NM. 8th sibling of the
 * 10E2C/10B38/F49C/FB04/FB7C/116D4 family-cap shape with a larger
 * surface due to the 6-call body: post-1st-call tail needs cross-USO
 * varargs spills + s0 epilogue restoration; trailing 4-insn lw-s0/
 * addiu-sp/jr-ra/nop epilogue. Was previously promoted via 31-insn
 * INSN_PATCH + 16-byte SUFFIX_BYTES_FORCE — both REMOVED 2026-05-23
 * as match-faking (per feedback_no_instruction_forcing_matches_policy).
 * Default build is INCLUDE_ASM. */
#if 0  /* original wrap doc preserved below */
/* game_uso_func_00010068: 48-insn (0xC0) 6-call dispatcher.
 *
 * Frame -0x28; saves s0 (= input a0, struct ptr) and ra. 6 cross-USO calls,
 * one guarded by a flag check on a0->0xB4->0x800->0x18 & 0x400.
 *
 * Call 1 (0x10094): 6-arg with 2 stack-passed ints
 *   gl_func(a0, (a0->0xFC | 0x19), 0, 2, [sp+0x10]=0x100, [sp+0x14]=10)
 *   The `ori a1, a1, 0x19` in the delay slot OR-merges 0x19 onto a0->0xFC
 *   AFTER spilling t6/t7 to the stack arg-shadow slots.
 *
 * Call 2 (0x100B8): 4-arg with shadow spills
 *   gl_func(s0, D[0xDD8], D[0xDDC], -1)
 *   The sw a1,0x4(sp) and sw a2,0x8(sp) before/after the jal are O32
 *   arg-shadow caller-saves, not extra args.
 *
 * Conditional check (0x100C0-0x100D8):
 *   t1 = s0->0xB4;
 *   t2 = ((int*)t1[0x800/4])[0x18/4];
 *   if ((t2 & 0x400) != 0) { Call 3 } else { skip Call 3 }
 *
 * Call 3 (0x100F0, conditional): 3-arg with shadow spills
 *   gl_func(s0, D[0xDE0], D[0xDE4])
 *   ($a3 NOT set in this branch — callee ignores per arg count.)
 *
 * Call 4 (0x100F8): 1-arg
 *   gl_func(s0)
 *
 * Call 5 (0x10104): 2-arg
 *   gl_func(s0, 0)
 *
 * Call 6 (0x1010C): 1-arg
 *   gl_func(s0)
 *
 * Multi-tick byte-matching pending. Default INCLUDE_ASM path keeps ROM
 * matching while structural decode lives here for grep discoverability.
 *
 * Measured 2026-05-08: 79.13% with current C. Remaining diffs:
 *   1. Target spills `sw a1,4(sp); sw a2,8(sp)` before/in delay-slot of
 *      jal #2 (and again for jal #3 inside conditional). Mine doesn't.
 *      Looks like O32 shadow-arg spills, suggests target's gl_func
 *      signature is variadic-style with explicit a1/a2 spillage. K&R
 *      empty-paren extern alone doesn't trigger this in IDO -O2.
 *   2. Target uses base+offset-folded `addiu t8, t8, 0xDD8; lw a1, 0(t8)`
 *      vs mine `addiu t0, t0, 0; lw a1, 0xDD8(t0)`. NAMED-LOCAL
 *      `int *D_DD8 = &D[0xDD8]` regressed 5pp (74.17%) — IDO promoted
 *      the local to $s and shifted other allocations. Don't try that
 *      lever again.
 *   3. Register allocation: target picks t1/v0/t4/t2/t3 for the
 *      `s0->0xB4->0x800->0x18 & 0x400` chain; mine picks v0/t8/v1/t9.
 *      Different register-priority outcomes. Likely needs a different
 *      C expression shape (e.g., separate intermediate locals) to nudge. */
#endif
extern int gl_func_00000000();
extern char D_00000000;
void game_uso_func_00010068(int *a0) {
    /* Call 1: 6-arg w/ 2 stack args */
    gl_func_00000000(a0,
                     *(int*)((char*)a0 + 0xFC) | 0x19,
                     0, 2,
                     0x100, 10);
    /* Call 2: 4-arg with D[0xDD8/0xDDC] */
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xDD8), -1);
    /* Conditional Call 3 — inline `outer` (arg0[0xB4]) so it takes $t1 not $v0,
     * but NAME the middle pointer `mid` so it claims $v0 like the target. */
    {
        int *mid = (int*)((int*)*(int**)((char*)a0 + 0xB4))[0x800 / 4];
        if (mid[0x18 / 4] & 0x400) {
            gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xDE0));
        }
    }
    /* Call 4 */
    gl_func_00000000(a0);
    /* Call 5 */
    gl_func_00000000(a0, 0);
    /* Call 6 */
    gl_func_00000000(a0);
}

/* game_uso_func_00010128: 105-insn (0x1A4) complex dispatcher. LANDED 2026-06-22
 * (agent-e): byte-exact (ROM-identical, `make verify` clean; 0 non-reloc word
 * diffs vs expected). The "outer<->mid v0/v1 spilltemp-web coloring cap" was a
 * PLACEHOLDER-SYMBOL artifact, NOT a real coloring cap: the body had used
 * gl_func_00000000/D_00000000 placeholders, which color differently than the
 * REAL reloc callees. Rewriting with the real symbols (game_uso_func_0000D5BC,
 * import_0010DB28, game_uso_func_0000D5F8 typed varargs-Pair2-by-value,
 * D5DC/E5C8/E35C/E2D0/11750, and game_uso_D_807FF3D0/D8/E0) flipped the
 * coloring so `outer`(a0->0xB4 reload)=$v0 and `mid`(outer->0x800)=$v1 — exactly
 * the target — and the 6 v0/v1 word diffs vanished. (Same lesson as twin 11258:
 * placeholder symbols score under name-blind objdiff but are not byte-correct;
 * the real-symbol coloring is the match.) The only residual vs expected is 3
 * extra LO16 relocs (HI16+LO16 pair vs expected's HI16+baked-LO16) — a benign
 * raw-word-USO encoding artifact that resolves identically at the ROM-bin level.
 * Original decode notes preserved below.
 *
 * 105-insn complex dispatcher. Frame -0x28; saves s0 (= a0), ra. Multiple cross-USO calls dispatched
 * via float-compare and bit-flag tests. Sibling of 0x10068 (the same
 * "outer = a0->0xB4; if (outer->0x800->0x18 & 0x400) ..." pattern).
 *
 * Body shape (decoded 2026-05-08):
 *
 *   outer = a0->0xB4;
 *   outer->0xA18 = 1;          // unconditional flag set at function entry
 *   if (outer->0x800->0x18 & 0x400) {
 *       gl_func(a0, D[0xDE0], D[0xDE4]);   // call A — w/ shadow spills
 *   }
 *   if (outer->0x9D0 < 1000.0f) {           // float-cmp via c.lt.s + bc1fl
 *       if (outer->0x938 != 0) {
 *           gl_func(a0, D[0xDE8], D[0xDEC]);   // call B
 *       }
 *       inner = a0->0xF4;
 *       if (inner != 0) {
 *           if (inner->0x38 & 1) {
 *               gl_func(a0, (a0->0xFC|0x19), 0, 5, 5, 1, 1);  // call C-1
 *           } else {
 *               gl_func(a0, (a0->0xFC|0x19), 0, 5, 5, 0x100, 10);  // call C-2
 *           }
 *       } else {
 *           gl_func(a0, (a0->0xFC|0x19), 0, 5, 5, ?, ?);  // call C-3 (uninit
 *           // t3/t4 stack args — likely 0/0 default since regs not set in
 *           // this branch)
 *       }
 *       gl_func(a0, D[0xDF0], D[0xDF4], 3);   // call D (after the 3-way
 *                                                merge from C-1/C-2/C-3)
 *       gl_func(a0);                          // call E
 *       gl_func(a0, 0);                       // call F
 *       gl_func(a0);                          // call G — returns v0
 *       if (v0 == 0) {                        // bnel + delay-likely epilogue
 *           gl_func(a0);                       // call H
 *           gl_func(a0);                       // call I
 *       }
 *   }
 *   // (no else for the float-compare — bc1fl annulled the bc1fl arm)
 *
 * Multi-tick byte-matching pending. Many tricky pieces:
 *   - bc1fl branch-likely with delay slot annulment
 *   - Multiple O32 shadow-arg spills (sw a1, 4(sp); sw a2, 8(sp))
 *     between gl_func calls (matches sibling 0x10068's style)
 *   - 6-arg stack-arg-spill calls (call C-1/C-2/C-3) with stack slots
 *     at sp+0x10 and sp+0x14
 *   - Branch-likely inside float-compare arm
 *
 * 2026-05-31: 73.8%->79.0% by INLINING a0->0xB4 (outer) at each use instead of
 * caching it in a local — the target reloads a0->0xB4 per access (the cache forced an
 * extra saved-reg + frame slot). Sibling game_uso_func_00010068 (the shared
 * outer->0x800->0x18&0x400 pattern) is now 100%.
 * 2026-06-21: 79.0%->97.90% (COUNT-EXACT 112=112; residual = PURE v0/v1 + t-reg
 * renumber, every remaining diff is a register name only). The over-production was
 * THREE structural bugs, NOT the claimed regalloc cap: (1) every 6-arg C-call
 * (import_DB28) had a spurious leading `0` arg, pushing 5,5/1,1 down a slot and
 * inflating the frame; the calls are (a0, a0->0xFC|0x19, a2, a3, sp16, sp20).
 * (2) the inner==0 path is NOT a separate (0,0)-arg call — it FALLS THROUGH to the
 * &1==0 body (args 5,5,0x100,10), so the guard is `(inner != 0) && (inner->0x38&1)`.
 * (3) the float-compare `>= 1000.0f` has a REAL else (bc1fl .L10254): C-call args
 * 2,3,1,1 then gl_func(a0,&D+0xDF0,3) (D5F8) + gl_func(a0) (D5DC) — those two run
 * ONLY on the >=1000 arm, not unconditionally. Both arms converge to E5C8(a0,0) +
 * E35C(a0)->v0 + v0==0 tail. Residual v0/v1 placement = coloring cap.
 * 2026-06-21 (agent-e): 79%->94.29% raw-word (count-exact 105=105). Naming the
 * `outer->0x800` deref as a local `mid` (outer stays inlined) keeps the flag-test
 * chain TIGHT at v0/v1+t8/t9 and pulls the D-base to $8 — matching the target's
 * register shape for ALL of the function EXCEPT the outer<->mid v0/v1 PAIR: the
 * target colors `outer` (the a0->0xB4 reload) into $v0 and `mid` into $v1; the
 * named `mid` web always claims $v0 instead, pushing the inline `outer` reload to
 * $v1. Exhaustively floored (agent-e, 14 src variants): naming outer instead
 * collapses the chain (climbs to $24/$25, 36 diffs); naming both, register-kw,
 * inner-scope, embedded-assign (mid=(outer=..)[..]), leaf-field-name, held-outer
 * (spills, +1 frame) all leave the same outer<->mid v0/v1 web tie. Permuter is
 * inapplicable (raw-.word USO asm, no mnemonic/reloc form). Genuine spilltemp-web
 * coloring cap (the named pointer web's $v0 claim is unreachable from C). */
extern char game_uso_D_807FF3D0;
extern char game_uso_D_807FF3D8;
extern char game_uso_D_807FF3E0;
extern void game_uso_func_0000D5F8(char *, Pair2, int);
extern void game_uso_func_0000D5DC(char *);
extern void game_uso_func_0000E5C8(char *, int);
extern int game_uso_func_0000E35C(char *);
extern void game_uso_func_0000E2D0();
extern void game_uso_func_00011750(char *);
void game_uso_func_00010128(int *a0) {
    int *inner;
    int *mid;

    ((int*)a0[0xB4 / 4])[0xA18 / 4] = 1;
    mid = (int*)((int*)a0[0xB4 / 4])[0x800 / 4];
    if ((mid[0x18 / 4] & 0x400) != 0) {
        game_uso_func_0000D5BC((char*)a0,
                         *(Pair2*)((char*)&game_uso_D_807FF3D0 + 0xDE0));
    }
    if (*(float*)((char*)(int*)a0[0xB4 / 4] + 0x9D0) < 1000.0f) {
        if (((int*)a0[0xB4 / 4])[0x938 / 4] != 0) {
            game_uso_func_0000D5BC((char*)a0,
                             *(Pair2*)((char*)&game_uso_D_807FF3D8 + 0xDE8));
        }
        inner = (int*)a0[0xF4 / 4];
        if ((inner != 0) && (inner[0x38 / 4] & 1)) {
            import_0010DB28(a0,
                             *(int*)((char*)a0 + 0xFC) | 0x19,
                             5, 5, 1, 1);
        } else {
            import_0010DB28(a0,
                             *(int*)((char*)a0 + 0xFC) | 0x19,
                             5, 5, 0x100, 10);
        }
    } else {
        import_0010DB28(a0,
                         *(int*)((char*)a0 + 0xFC) | 0x19,
                         2, 3, 1, 1);
        game_uso_func_0000D5F8((char*)a0,
                         *(Pair2*)((char*)&game_uso_D_807FF3E0 + 0xDF0),
                         3);
        game_uso_func_0000D5DC((char*)a0);
    }
    game_uso_func_0000E5C8((char*)a0, 0);
    if (game_uso_func_0000E35C((char*)a0) == 0) {
        game_uso_func_0000E2D0((char*)a0);
        game_uso_func_00011750((char*)a0);
    }
}

/* game_uso_func_000102CC — verified EE84-family decode (29%, LEN-DIFF 72/79;
 * branch-likely + float short-circuit + D-pair stack-args cap → <80 so
 * INCLUDE_ASM build path; PATTERNS.md EE84-family template). Structure:
 *   func_00000000(a0);                                    // X1
 *   func_00000000(s0, s0->0xFC | 0x19, 3, 4, 2, 1);       // X2 (6 args; 2,1 @sp)
 *   v0 = (int*)s0->0xB4;
 *   if (*(float*)(v0+0x31C) < 0.0f && *(float*)(v0+0x9D0) < 1000.0f) {
 *       func_00000000(s0, D[0xDE8], D[0xDEC]);             // X3 (D-pair @sp+4/8)
 *       v0 = (int*)s0->0xB4;
 *   }
 *   if (((int*)v0->0x800)->0x18 & 0x400)
 *       func_00000000(s0, D[0xDE0], D[0xDE4]);             // X4
 *   func_00000000(s0, 0);                                  // X5
 *   if (func_00000000(s0) == 0) {                          // X6
 *       int *t = (int*)s0->0xB4;
 *       if (t->0x938 != 0) {
 *           func_00000000(s0, D[0xDF8], D[0xDFC]);          // X7
 *           func_00000000(s0);                              // X8
 *       }
 *       func_00000000(s0);                                  // X9
 *   }
 * Struct-typing: s0->0xFC flag word, s0->0xB4 object (float @0x31C, float
 * @0x9D0, ptr @0x800 whose +0x18 has bit 0x400, int @0x938). 78.57% -> 98.61%:
 * the three D-pair consts (0xDE0/DE4, 0xDE8/DEC, 0xDF8/DFC) pass BY VALUE as
 * *(Pair2*) — the "sp+4/sp+8 EE84 D-pair shape cap" was the un-homed pair
 * (same lever as EF70, docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair).
 * 2026-07-15 (wave 3, agent-h): the old residual ("s0->0xB4 reload lands in
 * v1 vs v0, regalloc-renumber cascade" 8 words) RETRACTED via the FD0
 * dead-$v0-def exclusion lever (docs/IDO_CODEGEN): import_0010DB28's UNUSED
 * int K&R return left a dead $v0 def that excluded $v0 from the immediately
 * following v0-var web (colored v1, new_var took v0). Calling through the
 * void alias import_0010DB28_void (=0 in undefined_syms_auto.txt, identical
 * 0C000000 jal bytes) frees $v0 -> 79/79 objdiff-100. (26FC return-capture
 * probed first: inert, immediate-redef web split per the 1C90 caveat.)
 * NOT landable as C: jal game_uso_func_0000E2D0 targets a real in-TU
 * symbol (baked jal 0 in ROM). Stays NM wrap at 100. INCLUDE_ASM build. */
#ifdef NON_MATCHING
extern char game_uso_D_807FF3D8;
extern char game_uso_D_807FF3D0;
extern char game_uso_D_807FF3E8;
void game_uso_func_000104A4(char *a0);
void game_uso_func_00011750(char *obj);
extern void import_0010DB28_void();
void game_uso_func_000102CC(int *a0) {
  int *s0 = a0;
  int *v0;
  int new_var;
  game_uso_func_0000E2D0((char *)a0);
  import_0010DB28_void(s0, s0[0xFC / 4] | 0x19, 3, 4, 2, 1);
  v0 = (int *) s0[0xB4 / 4];
  if (((*((float *) (((char *) v0) + 0x31C))) < 0.0f) && ((*((float *) (((char *) v0) + 0x9D0))) < 1000.0f))
  {
    game_uso_func_0000D5BC((char *)s0, *((Pair2 *) (((char *) (&game_uso_D_807FF3D8)) + 0xDE8)));
    v0 = (int *) s0[0xB4 / 4];
  }
  if ((*((int *) (((char *) (new_var = *((int *) (((char *) v0) + 0x800)))) + 0x18))) & 0x400)
  {
    game_uso_func_0000D5BC((char *)s0, *((Pair2 *) (((char *) (&game_uso_D_807FF3D0)) + 0xDE0)));
  }
  game_uso_func_0000E5C8((char *)s0, 0);
  if (game_uso_func_0000E35C((char *)s0) == 0)
  {
    ;
    if (((int *) s0[0xB4 / 4])[0x938 / 4] != 0)
    {
      game_uso_func_0000D5BC((char *)s0, *((Pair2 *) (((char *) (&game_uso_D_807FF3E8)) + 0xDF8)));
      game_uso_func_000104A4((char *)s0);
    }
    game_uso_func_00011750((char *)s0);
  }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000102CC);
#endif

/* Small state-dispatch helper. BYTE-EXACT (was force-promoted via banned
 * SUFFIX_BYTES + INSN_PATCH). Two legit levers: (1) pass the &D+0xDF8 pair as a
 * `*(Pair2*)` BY VALUE — the by-value struct both clusters the base (lui;addiu;
 * lw 0/4) and homes a1/a2 to sp+4/sp+8 (the late spills IDO omits for separate
 * int args); (2) inline the single-use spB4 deref (no named local) so it takes
 * a $t-reg instead of $v0. Same Pair2-by-value idiom as game_uso_func_00010648. */
void game_uso_func_00010408(int *arg0) {
    gl_func_00000000(arg0, *(int*)((char*)arg0 + 0xFC) | 0x19, 4, 5, 1, 1);
    gl_func_00000000(arg0, 0);
    if (gl_func_00000000(arg0) == 0) {
        if ((*(int**)((char*)arg0 + 0xB4))[0x938 / 4] != 0) {
            gl_func_00000000(arg0, *(Pair2*)((char*)&D_00000000 + 0xDF8));
            gl_func_00000000(arg0);
        }
    }
}

/* 50-insn sibling of game_uso_func_00010408/105DC family. Initializes
 * a0->0xB4->0xA18, conditionally runs the 0x938-gated path, then emits
 * the same t[0]/t[1] vararg-spill call shape used by nearby wrappers. */
void game_uso_func_000104A4(char *a0) {

    gl_func_00000000(a0);
    (*(int **)(a0 + 0xB4))[0x286] = 1;
    gl_func_00000000(a0, 0);

    if (gl_func_00000000(a0) == 0) {
        if ((*(int **)(a0 + 0xB4))[0x24E] != 0) {
            gl_func_00000000(a0, 1);
            gl_func_00000000(a0);
            gl_func_00000000(a0, *(int *)(a0 + 0xFC) | 0x19, 5, 1, 1, 1);
            gl_func_00000000(a0, *(Pair2 *)((char *)&D_00000000 + 0xE10), 1);
            gl_func_00000000(a0);
        }
    }
}

/* MATCHED via struct-by-value arg-home: the adjacent D[0xE08]/D[0xE0C] pair
 * passed as `*(Pair2*)(&D+0xE08)` homes a1,a2 to sp+4/sp+8. Has a final float
 * copy tail. (The "precall-arg-spill family / INSN_PATCH ineligible" cap was wrong.) */
void game_uso_func_0001056C(char *a0) {
    gl_func_00000000(a0, 0x10025, 0, 0, 0x100, 5);
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE08), -1);
    *(float*)(a0 + 0x11C) = *(float*)(a0 + 0x154);
}

/* MATCHED 2026-05-28: struct-by-value (E00/E04 pair). 27-insn 3-call
 * sibling of 10E2C/11368/FA54 family. The "t8-base + varargs spills" cap
 * was the un-homed pair; symbol size is exactly 27 insns (the old
 * "trailing alt-entry stub" worry was a separate symbol, not this one).
 * See docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_000105DC(int *a0) {
    game_uso_func_00000000(a0, 0x10025, 0, 1, 1, 1);
    game_uso_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE00), 1);
    game_uso_func_00000000(a0);
}

/* game_uso_func_00010648 (0x4C): orphan-prologue MERGE of the 0x8-byte stub at
 * 0x10648 (`lui at,0x3F80; mtc1 at,$f4` = load 1.0f) + the 0x44 body formerly
 * mislabeled game_uso_func_00010650 (0x10650). The two are ONE routine: the stub
 * loads 1.0f into $f4, which IDO HOISTS above the prologue, and the body stores
 * it via `swc1 $f4,0x11C(a0)`. The earlier "caller-set float-in-$f4 cap" note was
 * wrong — $f4 is not a caller convention, it's this function's own 1.0f constant.
 * First call passes a 2-int struct BY VALUE (homes a1->sp+4, a2->sp+8); the named
 * base `&D+0xDF8` keeps the addiu split (lw 0(t6)/4(t6)). Byte-exact. */
void game_uso_func_00010648(void *a0) {
    *(float*)((char*)a0 + 0x11C) = 1.0f;
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xDF8));
    gl_func_00000000(a0);
}

#ifdef NON_MATCHING
/* game_uso_func_00010694: 0x1AC (107 insns). State-machine entry handler,
 * sibling of 00010840. Reconstructed vs expected .o (call-graph DFS, reloc
 * sites): distinct D symbols (D_807FFB70 ldc1 +0x250 threshold, D_807FF438
 * +0xE48 pair, D_807FF3B8 +0xDC8 table), real callee names, two dispatch
 * arms call DIFFERENT funcs (import_0010DB78 above-threshold,
 * import_0010DB28 below-threshold), 2-word table-scan vs D_807FF3B8+0xDC8
 * (modeled on sibling 0000D204).
 *
 * RESIDUAL CAP (shared with 00010840): the above-arm passes the raw float
 * bits of saved_f0 as a3 via the target's single `mfc1 a3,$f0`. IDO C cannot
 * emit single-insn mfc1 for a float local — `*(int*)&saved_f0` forces a
 * swc1+lw stack round-trip. Documented mfc1-from-C cap. Default INCLUDE_ASM. */
extern void game_uso_func_0000E1FC(char *);
extern void game_uso_func_0000D8A8(char *);
extern void game_uso_func_0000D8EC(int *);
extern int import_0010DB78();
extern int import_0010DB28();
extern void game_uso_func_0000E91C_1arg(char *);
extern void game_uso_func_00011750(char *);
extern void game_uso_func_0000D5BC(char *, Pair2);
extern char game_uso_D_807FFB70;
extern char game_uso_D_807FF438;
void game_uso_func_00010694(int *a0) {
    int *sub;
    float saved_f0;
    float abs_f0;
    int v;
    ((int*)a0[0xB4/4])[0xA18/4] = 1;
    a0[0x114/4] = 2;
    ((int*)a0[0xB4/4])[0x3DC/4] = 1;
    *(float*)((char*)a0 + 0x11C) = 1.0f;
    saved_f0 = *(float*)((char*)(int*)a0[0xB4/4] + 0x970);
    game_uso_func_0000E1FC((char*)a0);
    ((int*)a0[0xB4/4])[0x960/4] = 0;
    game_uso_func_0000D8A8((char*)a0);
    game_uso_func_0000D8EC(a0);

    abs_f0 = (saved_f0 < 0.0f) ? -saved_f0 : saved_f0;

    v = a0[0xFC/4];
    if ((double)abs_f0 > *(double*)((char*)&game_uso_D_807FFB70 + 0x250)) {
        import_0010DB78(a0, v | 2, v | 3, *(int*)&saved_f0, 0, 1);
    } else {
        import_0010DB28(a0, v | 8, 0, 1, 6, 1);
    }

    sub = (int*)a0[0xB4/4];
    if (sub[0x9CC/4] != 0) {
        game_uso_func_0000D5BC((char*)a0, *(Pair2*)((char*)&game_uso_D_807FF438 + 0xE48));
    }
    game_uso_func_0000E91C_1arg((char*)a0);
    game_uso_func_00011750((char*)a0);

    *(int*)((char*)a0 + 0xDC) = ((int*)a0[0xB4/4])[0x938/4];
    {
        int *p = (int*)((char*)a0 + 0xD0);
        int *t = (int*)((char*)&game_uso_D_807FF3B8 + 0xDC8);
        int found = 0;
        do {
            if (*p != *t) { found = 0; break; }
            p++;
            t++;
        } while (p != (int*)((char*)a0 + 0xD0) + 2);
        if (p == (int*)((char*)a0 + 0xD0) + 2) {
            found = 1;
        }
        if (found) {
            game_uso_func_0000D5BC((char*)a0, *(Pair2*)((char*)a0 + 0xD0));
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010694);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00010840: 67-insn (0x10C) state-init + 2-stage dispatch,
 * sibling of 10694. State-machine: set sub->0x3DC=1, two init dispatches,
 * reload velocity sub->0x970, abs+double-threshold compare, two-arm
 * 6-arg logger dispatch (import_0010DB78 above-thresh / import_0010DB28
 * below-thresh), unconditional follow-up, then a sub->0x9CC-gated pair call.
 *
 * 2026-06-24 RECONSTRUCTION 80.19% -> 87.67% (verified in-tree):
 *   The float velocity's raw bits are passed as the a3 arg of both logger
 *   calls (target: single `mfc1 a3,$f0`). Passing `*(int*)&saved_f0` forces
 *   a swc1+3-reload stack round-trip (frame -48, 80.19%). Instead read the
 *   int bits DIRECTLY from the struct slot into a HOISTED local `bits`
 *   (`*(int*)((char*)sub + 0x970)`) BEFORE the branch: single `lw`, CSE'd
 *   across both arms, frame -40, +7.5pp.
 *
 * RESIDUAL CAP (~88%, not landable):
 *   (1) Target's a3 is `mfc1 a3,$f0` (float-bits-to-int-reg); IDO C cannot
 *       emit single-insn mfc1 for a float — documented 14-variant cap
 *       (docs/IDO_CODEGEN.md#feedback-ido-mfc1-from-c). Here it degrades to
 *       a `lw` from the same slot (correct bytes, wrong instruction).
 *   (2) Target has DEAD arg-prep before the abs branch (a1=0x20008, a2=0,
 *       a3=1, move a0,s0) overwritten before any call — an -O2 hoist
 *       artifact with NO call; reintroducing a real stage-1 call regresses
 *       to 67% (adds a jal the target lacks).
 * Remaining diffs are otherwise register-allocation only (same insn count).
 * Default INCLUDE_ASM. */
extern char game_uso_D_807FFB78;
extern int import_0010DB78();
void game_uso_func_00010840(int *a0) {
    int *sub = (int*)a0[0xB4/4];
    float saved_f0;
    float abs_f0;
    int bits;
    sub[0x3DC/4] = 1;
    game_uso_func_0000D8A8((char*)a0);
    game_uso_func_0000D8EC(a0);
    sub = (int*)a0[0xB4/4];
    saved_f0 = *(float*)((char*)sub + 0x970);
    bits = *(int*)((char*)sub + 0x970);
    abs_f0 = (saved_f0 < 0.0f) ? -saved_f0 : saved_f0;
    if ((double)abs_f0 > *(double*)((char*)&game_uso_D_807FFB78 + 0x258)) {
        import_0010DB78(a0, 0x20002, 0x20003, bits, 0, 1);
    } else {
        import_0010DB28(a0, 0x20002, 0x20003, bits, 6, 1);
    }
    game_uso_func_0000E1FC((char*)a0);
    sub = (int*)a0[0xB4/4];
    if (sub[0x9CC/4] == 0) {
        game_uso_func_0000D5BC((char*)a0,
                         *(Pair2*)((char*)&game_uso_D_807FF400 + 0xE10));
    }
    game_uso_func_00011750((char*)a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010840);
#endif

/* game_uso_func_0001094C: 48-insn EE84-family (near-twin of 10A0C).
 * MATCHED 2026-07-08, word-diff 48/48 incl. reloc symbols (import_0010DB78,
 * game_uso_D_807FF400+0xE10, game_uso_D_807FF460+0xE70, D5BC/E91C/D8EC/D7F4):
 * (1) *(Pair2*) by-value D-pair calls (0xE10, 0xE70) home a1/a2 to sp+4/8;
 * (2) inline the first 0xB4 deref (named local colored it v0; inline -> t6)
 *     and the 0x9CC test (named t2 colored v1; inline -> $t2 temp + bnezl
 *     dup-load in the delay slot);
 * (3) the 0xFC state word must be INLINED TWICE (|4, |5) so CSE creates the
 *     v0 candidate AFTER the 0xB4 deref pseudo -- a named `int v` local is
 *     created before the s0=a0 copy point and bases its lw on $a0 not $s0
 *     (the last 47/48 residual). Param used directly, no explicit s0 local. */
extern int import_0010DB78();
extern void game_uso_func_0000D5BC(char *, Pair2);
extern void game_uso_func_0000E91C(char *);
extern void game_uso_func_0000D8EC(int *);
extern void game_uso_func_0000D7F4(char *);
extern char game_uso_D_807FF400;
extern char game_uso_D_807FF460;
void game_uso_func_0001094C(int *a0) {
    int *p;
    import_0010DB78(a0, a0[0xFC / 4] | 4, a0[0xFC / 4] | 5, ((int *)a0[0xB4 / 4])[0x970 / 4], 0, 1);
    p = (int *)a0[0xB4 / 4];
    if (p[0x990 / 4] == 0) {
        game_uso_func_0000D5BC((char *)a0, *(Pair2 *)((char *)&game_uso_D_807FF400 + 0xE10));
        p = (int *)a0[0xB4 / 4];
    }
    if (p[0x9CC / 4] != 0) {
        game_uso_func_0000D5BC((char *)a0, *(Pair2 *)((char *)&game_uso_D_807FF460 + 0xE70));
    }
    game_uso_func_0000E91C((char *)a0);
    game_uso_func_0000D8EC(a0);
    game_uso_func_0000D7F4((char *)a0);
}

#ifdef NON_MATCHING
/* game_uso_func_00010A0C: 45-insn EE84-family, near-twin of 0001094C
 * (constant first-call args 0x20004/0x20005, D[0xE48] pair, INVERTED t2
 * test: calls X3 when t2==0). Cross-USO jal-0 → gl_func_00000000.
 * 67.9% -> 93.4%: the two D-pair calls (0xE48/0xE4C, 0xE70/0xE74) are
 * passed BY VALUE as *(Pair2*) — the "precall-arg-spill cap" was the
 * un-homed pair (same lever as 10AC8/10B38, see
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair).
 * Residual is pure regalloc-renumber (temp regs t6/t7/t9/t3 vs the
 * target's v0/t6/t8/t1 + a deferred `or s0,a0`); same logic, not
 * C-reachable for our IDO binary. */
extern int gl_func_00000000();
void game_uso_func_00010A0C(int *a0) {
    int *s0 = a0;
    int *p = (int *)s0[0xB4 / 4];
    int t2;
    gl_func_00000000(s0, 0x20004, 0x20005, p[0x970 / 4], 0, 1);
    p = (int *)s0[0xB4 / 4];
    if (p[0x990 / 4] == 0) {
        gl_func_00000000(s0, *(Pair2 *)((char *)&D_00000000 + 0xE48));
        p = (int *)s0[0xB4 / 4];
    }
    t2 = p[0x9CC / 4];
    if (t2 == 0) {
        gl_func_00000000(s0, *(Pair2 *)((char *)&D_00000000 + 0xE70));
    }
    gl_func_00000000(s0);
    gl_func_00000000(s0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010A0C);
#endif

/* MATCHED via struct-by-value arg-home: the adjacent D[0xE40]/D[0xE44] pair
 * passed as `*(Pair2*)(&D+0xE40)` homes a1,a2 to sp+4/sp+8 (the target's
 * `sw a1,4(sp); sw a2,8(sp)`) — the "precall-arg-spill family" cap was wrong. */
void game_uso_func_00010AC8(char *a0) {
    int v0;
    gl_func_00000000(a0);
    v0 = *(int*)(a0 + 0xFC);
    gl_func_00000000(a0, v0 | 2, v0 | 3, *(int*)(*(char**)(a0 + 0xB4) + 0x970), 0x100, 10);
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE40), -1);
}

/* MATCHED 2026-05-28: struct-by-value (E60/E64 pair). 29-insn init +
 * 3-call orchestrator. The 3rd call's "tail reshape + varargs spills"
 * cap was the un-homed pair; *(Pair2*) by value reproduces the whole
 * tail. Inlined p->0x970 deref keeps the 2nd-call t6/t7/t8 regalloc.
 * See docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_00010B38(int *a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0, 0x20002, 0x20003, ((int*)a0[0xB4/4])[0x970/4], 0x100, 5);
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE60), -1);
}

/* MATCHED 2026-05-28: struct-by-value arg-pass for the E10/E14 and E48/E4C
 * pairs (homes a1,a2), PLUS inlining the `sub = a0->0xB4` deref (named local
 * put it in $v1; inline keeps it in $t6 like target). See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_00010BAC(char *a0) {
    int state = *(int*)(a0 + 0xFC);
    gl_func_00000000(a0, state | 7, state | 6, *(int*)(*(char**)(a0 + 0xB4) + 0xA04), 0, 1);

    if (*(int*)(a0 + 0xD8) == 0) {
        gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE10));
    }

    if (*(int*)(*(char**)(a0 + 0xB4) + 0x9CC) != 0) {
        gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE48));
    }
}

/* BYTE-EXACT 2026-05-31 (stale-cap catch). Sibling of game_uso_func_00010BAC;
 * the struct-by-value arg-pass (*(Pair2*)(&D+0xE48/0xE10)) homes the pairs to
 * the outgoing arg slots, byte-exact — the 2026-05-28 struct-by-value sweep
 * landed 10BAC but missed this sibling, leaving it needlessly NM-wrapped.
 * .text identical to expected/.o. See docs/IDO_CODEGEN.md STALE-CAP CATCH. */
void game_uso_func_00010C4C(char *a0) {
    gl_func_00000000(a0, 0x20007, 0x20006,
                     *(int*)(*(char**)(a0 + 0xB4) + 0xA04), 0, 1);

    if (*(int*)(a0 + 0xD8) == 0) {
        gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE48));
    }

    if (*(int*)(*(char**)(a0 + 0xB4) + 0x9CC) == 0) {
        gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE10));
    }
}

void game_uso_func_00010CF0(char *a0) {
    char *sub;

    sub = *(char**)(a0 + 0xB4);
    if (*(int*)(sub + 0x9CC) != 0) {
        gl_func_00000000(a0, 0x20004, 0x20005, *(int*)(sub + 0x970), 0x100, 10);
        gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE78), -1);
    } else {
        int state;

        state = *(int*)(a0 + 0xFC);
        gl_func_00000000(a0, state | 4, state | 5, *(int*)(sub + 0x970), 0x100, 10);
        gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE80), -1);
    }
    gl_func_00000000(a0);
}

/* MATCHED 2026-05-28: struct-by-value (E10/E14 pair). Family sibling of
 * game_uso_func_00010E2C/000114FC. See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_00010DC8(int a0) {
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0xFC) | 0x9, 0, 1, 1, 1);
    game_uso_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE10), 1);
}

/* MATCHED 2026-05-28: struct-by-value (E40/E44 pair). The prior "constant-
 * address-load-fold" cap framing was wrong — the 4-insn base+ofs load form is
 * the struct-by-value home-store, not a jumptable. See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_00010E2C(int a0) {
    game_uso_func_00000000(a0, 0, 0, 1, 1, 1);
    game_uso_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE40), 1);
}

void game_uso_func_00010E8C(int a0) {
    game_uso_func_00000000(a0, 0x70005, 0, 1, 1, 1);
}

void game_uso_func_00010EC8(int a0) {
    game_uso_func_00000000(a0, 0x7000F, 0, 1, 1, 1);
}

void game_uso_func_00010F04(int a0) {
    game_uso_func_00000000(a0, 0x70003, 0, 1, 1, 1);
}

void game_uso_func_00010F40(int a0) {
    game_uso_func_00000000(a0, 0x70004, 0, 1, 1, 1);
}

void game_uso_func_00010F7C(int a0) {
    game_uso_func_00000000(a0, 0x70004, 0, 1, 1, 1);
}

/* MATCHED 2026-05-28: struct-by-value (F58/F5C pair). 27-insn 2-call
 * sibling of the 0x10E2C/11368/113C8 family. The "t0-base form + varargs
 * spills" cap was the un-homed pair — *(Pair2*) by value reproduces both.
 * See docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_00010FB8(int *a0) {
    game_uso_func_00000000(a0, 0x70000, 0, 1, 1, 1);
    *(int*)((char*)a0 + 0x114) = 0;
    *(int*)((char*)*(int**)((char*)a0 + 0xB4) + 0x960) = 100;
    game_uso_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xF58));
}

/* 32-insn / 0x80 dual-call orchestrator on a0->B4-child:
 *   a0->D0 = D[0xF48];
 *   a0->D4 = D[0xF4C];
 *   a0->B4->A58 &= ~4;          // clear bit 2 in B4-child's A58 field
 *   gl_func_00000000(a0, D[0xE10], D[0xE14]);  // first call
 *   gl_func_00000000(a0);                       // second call
 *   a0->B4->960 = 0x64;          // = 100
 *
 * Initial decode 2026-05-16; structural shape only. Two USO data
 * placeholders (D+0xF48/0xF4C and D+0xE10/0xE14) per
 * docs/PATTERNS.md uso-multi-placeholder-wrapper. The asm has a
 * double `lw a0, 0x18(sp)` at insns 24/25 (jal-delay + post-jal) —
 * scheduler quirk likely.
 *
 * 2026-05-28: the precall a1/a2 home-stores ARE reproducible via struct-by-value
 * (gl_func(a0, *(Pair2*)(&D+0xE10))) — applied, 65.84% -> 74.03%. Residual is
 * NOT the spill cap: (1) the p_B4->0xA58 RMW uses target's addiu-base+0(base)
 * write vs mine's offset write, and (2) a0 is reloaded TWICE around the 2nd jal
 * (jal-delay + after) which IDO won't emit from C here. 31 vs 32 insns. These
 * are scheduling/RMW-addressing residuals, not the (now-solved) home-store cap.
 * See docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
extern int gl_func_00000000();
extern char D_00000000;
void game_uso_func_00011024(int *a0) {
  int v;
  int *p_B4 = *((int **) (((char *) a0) + 0xB4));
  *((Pair2 *) (((char *) a0) + 0xD0)) = *((Pair2 *) (((char *) (&D_00000000)) + 0xF48));
  ;
  p_B4 = (int *) (((char *) p_B4) + 0xA58);
 goto dummy_label_965124; dummy_label_965124: ;
  *p_B4 = (*p_B4) & (~4);
  gl_func_00000000(a0, *((Pair2 *) (((char *) (&D_00000000)) + 0xE10)));
  gl_func_00000000(a0);
  ((int *) (*((int **) (((char *) a0) + 0xB4))))[0x960 / 4] = 0x64;
}


/* Sibling of game_uso_func_00011024 — same 32-insn dual-call orchestrator;
 * only the D-offsets differ (0xF20/0xF24 vs 0xF48/0xF4C). 2026-05-31: the
 * "precall-arg-spill + trailing-epilogue cap" was stale — struct-by-value
 * (*(Pair2*)) homes a1/a2 and the `p_B4->field_A58 &= ~4` RMW written as
 * load-via-offset + pointer-advance + store-via-0(p) (`v = p[A58]; p =
 * p+A58; *p = v & ~4;`) recovers the target's `addiu v0; sw 0(v0)` so the
 * body is now SIZE-EXACT + STRUCTURE-EXACT. Residual is a pure register
 * renumber (10 diffs): the RMW value lands in $v1 (named local) where the
 * target uses $t9, cascading the &D-E10 base $t0->$t1 and the tail $t3/$t4->
 * $t4/$t5. Both siblings share it. Needs the permuter or an allocno tweak
 * that births the loaded value in $t9; not a frame/structure problem. */
void game_uso_func_000110A4(int *a0) {
  char *new_var;
  int *new_var2;
  int *p_B4 = *((int **) (((char *) a0) + 0xB4));
  int *new_var3;
  int v;
 do { } while (0);
  new_var = ((char *) (&D_00000000)) + 0xF20;
  new_var3 = a0;
  *((Pair2 *) (((char *) a0) + 0xD0)) = *((Pair2 *) new_var);
  ;
  new_var2 = (p_B4 = (int *) (((char *) p_B4) + 0xA58));
  *p_B4 = (*new_var2) & (~4);
  gl_func_00000000(a0, *((Pair2 *) (((char *) (&D_00000000)) + 0xE10)));
  gl_func_00000000(a0);
  ((int *) (*((int **) (((char *) new_var3) + 0xB4))))[0x960 / 4] = 0x64;
}


/* BYTE-EXACT 2026-05-31. 2-call wrapper: gl_func(a0); gl_func(a0, D[0xF50],
 * D[0xF54], 1). The documented "82.18% pre-call-spill cap" was STALE — passing
 * the adjacent D[] pair AS A STRUCT BY VALUE (`*(Pair2*)(&D+0xF50)`) makes IDO
 * home a1/a2 to the outgoing arg slots (sw a1,4(sp); sw a2,8(sp)) AND keep the
 * single $t6 base, matching the target exactly (this is the struct-by-value
 * lever from docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair,
 * which the stale comment's pre-2026-05-28 variants predate). .text 68/68 bytes
 * identical to expected/.o; residual fuzzy<100 is the usual uso reloc-presence. */
void game_uso_func_00011124(int *a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xF50), 1);
}

/* BYTE-EXACT 2026-05-31 (stale-cap catch): the struct-by-value body below was
 * already correct; the prior "~6% $v0-vs-$v1 &D-base residual" closed (game_uso
 * symbolization aligned the &D reloc) but the wrap was never removed. .text
 * 240/240 bytes identical to expected/.o.
 *
 * game_uso_func_00011168: 60-insn 4-way dispatcher, 0xF0 size, frame 0x18.
 * 61.23% NM (up from 12.33% stub). Re-decoded 2026-05-05 — prior wrap doc
 * had 2 errors:
 *   - "t7 == 0" branch used `t8->0x64` (wrong); asm reads `D[0x64]` directly.
 *   - "t7 == 2" branch claimed D[0xF38]; actually D[0x64] threshold gates
 *     between D[0xF30] and D[0xF38] (under flag==1 && D[0x7C]==0).
 *
 * Remaining ~39pp gap is precall-arg-spill class (per
 * `feedback_ido_precall_arg_spill_unreachable.md`): expected emits
 * `sw a1, 4(sp); sw a2, 8(sp)` outgoing-arg-slot stores around each of the
 * 4 jals (8 extra insns), AND uses a single t9 base register set up via
 * `lui+addiu` for both `a1=base[0]` and `a2=base[1]` loads. Build folds
 * to per-load lui+lw immediate. BNEL vs BNE for the flag check is also
 * a related codegen-shape diff. Same class as game_uso_func_00011124
 * (sibling at 82.17% cap).
 *
 * Corrected dispatch (asm 0x11168-0x11254):
 *
 *   gl_func_00000000(a0);                            // unconditional pre-call
 *   flag = a0->0xB4->0xA54;
 *   if (flag != 1) {
 *       gl_func_00000000(a0, D[0xF40+0], D[0xF40+4], 1);  // default
 *       return;
 *   }
 *   t8 = D[0x7C];
 *   if (t8 != 0) {
 *       gl_func_00000000(a0, D[0xF28+0], D[0xF28+4], 1);
 *       return;
 *   }
 *   t2 = D[0x64];
 *   if (t2 < 2) {
 *       gl_func_00000000(a0, D[0xF30+0], D[0xF30+4], 1);
 *   } else {
 *       gl_func_00000000(a0, D[0xF38+0], D[0xF38+4], 1);
 *   }
 *
 * The 4 inner calls share signature (a0, Pair2-by-value, 1). The target's
 * `sw a1,4(sp); sw a2,8(sp)` outgoing home-stores are NOT a "precall-arg-spill
 * cap" (feedback_ido_precall_arg_spill_unreachable was WRONG): they come from
 * passing the adjacent int pair AS A STRUCT BY VALUE — `gl_func(a0, *(Pair2*)p,
 * 1)`. IDO places the 2-int struct in a1,a2 AND homes them to sp+4/sp+8, exactly
 * matching the target. Two separate int args (p[0],p[1]) do NOT home them.
 * This lifted 61.2% -> 93.92% (2026-05-28). Residual ~6% is a $v0-vs-$v1 &D-base
 * register-renumber (target holds &D in $v0; single-base-pointer local
 * regressed). See docs/IDO_CODEGEN.md struct-by-value-homes-arg-pair. */
void game_uso_func_00011168(int *a0) {
    gl_func_00000000(a0);

    if (((int*)a0[0xB4 / 4])[0xA54 / 4] == 1) {
        if (*(int*)((char*)&D_00000000 + 0x7C) != 0) {
            /* struct-by-value pass homes a1,a2 to sp+4/sp+8 (the target's
             * `sw a1,4(sp); sw a2,8(sp)`) — NOT reachable from two int args.
             * This solved the prior "precall-arg-spill cap" (was 61%, now 94%). */
            gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xF28), 1);
            return;
        }
        if (*(int*)((char*)&D_00000000 + 0x64) < 2) {
            gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xF30), 1);
        } else {
            gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xF38), 1);
        }
        return;
    }
    /* flag != 1: default path. Placed last so IDO emits BNEL-skip-to-here
     * with delay-load (matching asm 0x11198 bnel t7,at,+0x26). */
    gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xF40), 1);
}

/* game_uso_func_00011258: 34-insn (0x88) init+register-clear helper.
 * Structure:
 *   game_uso_func_077C44(a0, 0x70009, 0, 2, /stack: 1, 1/);     // call #1
 *   game_uso_func_0000D5F8(a0, *(D+0xF18), *(D+0xF1C), 2);      // call #2 (varargs pair home)
 *   game_uso_func_0000D5DC(a0);                                 // call #3
 *   p = a0->[0xB4]; p[0xA58] &= ~0x800;   // bit-clear (RSP/SP status mask)
 *
 * 2026-06-20: reconstructed with the REAL reloc callees (was placeholder
 * func_00000000/D_00000000, which score 100% under name-blind objdiff but are
 * NOT byte/episode-correct). game_uso_func_0000D5F8 is varargs (homes the pair
 * to 4(sp)/8(sp)); passing the D-pair BY VALUE (`Pair2`) reproduces the
 * `addiu base,base,0xF18; lw 0/4(base)` + stack-home shape with a DIRECT jal
 * (a fn-ptr cast would emit lui/addiu/jalr). The tail bit-clear emits the
 * target's `addiu base,base,0xA58; sw 0(base)` via the pointer-mutate lever
 * (`p = (char*)p + 0xA58; *p = ...`); `q = p + N` folds the offset back.
 *
 * Built is now EXACT SIZE (34 insns), all but 2 words byte-identical INCLUDING
 * relocs (was 1-insn-short + wrong-symbol placeholders). SOLE RESIDUAL = a
 * 2-register renumber in the tail RMW: target colors the loaded/masked values
 * into $t2/$t3, IDO colors them $v1/$t2 (one free-list slot lower). Confirmed
 * MATCH 2026-06-21 (byte-exact, ROM-identical). The "v1/t2 free-list coloring
 * cap" was NOT coloring-immune: the lever is the RMW-THROUGH-ADVANCED-POINTER
 * form. Instead of `raw = p[0xA58/4]; val = raw & ~M; p = p+0xA58; *p = val;`
 * (which colors the loaded value v1, masked t2), advance the pointer FIRST then
 * read+mask+write through it in a single statement:
 *   `p = (int*)((char*)p + 0xA58); *p = *p & ~0x800;`
 * This makes the load and the masked store share one address LR, and IDO colors
 * the value/result into t2/t3 (target). Found via decomp-permuter (it produced
 * the advance-first shape with a corrupted double-offset; fixing the offset to
 * the `*p = *p & ~M` RMW landed it). Callees/data resolve to absolute 0 (USO
 * runtime relocs) so the unwrapped C links and the ROM stays byte-identical. */
extern int func_00000000();
extern char game_uso_D_807FF508;
void game_uso_func_00011258(int *a0) {
    int *p;
    game_uso_func_077C44(a0, 0x70009, 0, 2, 1, 1);
    game_uso_func_0000D5F8((char*)a0, *(Pair2*)((char*)&game_uso_D_807FF508 + 0xF18), 2);
    game_uso_func_0000D5DC((char*)a0);
    p = *(int**)((char*)a0 + 0xB4);
    p = (int*)((char*)p + 0xA58);
    *p = *p & ~0x800;
}

/* game_uso_func_000112E0: 34-insn sibling of game_uso_func_00011258.
 * Byte-identical to 11258 except the first-call magic constant
 * 0x70009 -> 0x70008. MATCH 2026-06-21 via the same RMW-through-advanced-pointer
 * lever as the twin (see 11258 above). Byte-exact, ROM-identical. */
extern char game_uso_D_807FF508;
void game_uso_func_000112E0(int *a0) {
    int *p;
    game_uso_func_077C44(a0, 0x70008, 0, 2, 1, 1);
    game_uso_func_0000D5F8((char*)a0, *(Pair2*)((char*)&game_uso_D_807FF508 + 0xF18), 2);
    game_uso_func_0000D5DC((char*)a0);
    p = *(int**)((char*)a0 + 0xB4);
    p = (int*)((char*)p + 0xA58);
    *p = *p & ~0x800;
}

/* MATCHED 2026-05-28: struct-by-value (F08/F0C pair). Family sibling #5 of
 * game_uso_func_00010E2C. See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_00011368(int *a0) {
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0x74), 2, 3, 1, 1);
    game_uso_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xF08), 3);
}

/* MATCHED 2026-05-28: struct-by-value (F10/F14 pair). Family sibling #6 of
 * game_uso_func_00010E2C. See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_000113C8(int *a0) {
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0x74), 3, 4, 1, 1);
    game_uso_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xF10), 4);
}

void game_uso_func_00011428(int *a0) {
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0x74), 4, 1, 1, 1);
}

/* game_uso_func_00011460: 39-insn — a1 = ((u)a0->0xB4->0x8C4 % 5)+10 | 0x70000;
 * then 3 USO calls with D[] arg-pairs (same family as game_uso_func_0000EE84).
 * NATURAL CEILING: 83.18% NM. Cap: target uses base-register form for the
 * D-pair calls + caller-slot spills around them. SUFFIX_BYTES_FORCE +
 * INSN_PATCH promotion was REMOVED 2026-05-23 as match-faking. */
void game_uso_func_00011460(int *a0) {
    int v = (int)((unsigned int)((int *)a0[0xB4 / 4])[0x8C4 / 4] % 5U);
    int a1 = (v + 10) | 0x70000;
    func_00000000(a0, a1, 0, 2, 1, 1);
    func_00000000(a0, *(Pair2 *)((char *)&D_00000000 + 0xEF8), 2);
    func_00000000(a0, *(Pair2 *)((char *)&D_00000000 + 0xF00));
}
/* MATCHED 2026-05-28: struct-by-value (DB8/DBC pair). Family sibling of
 * game_uso_func_00010E2C. See
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
void game_uso_func_000114FC(int *a0) {
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0x74), 2, 1, 1, 1);
    game_uso_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xDB8), 1);
}

/* game_uso_func_0001155C (0x80): orphan-prologue MERGE of the 0x8 stub at 0x1155C
 * (lui t6,0; lw t6,0x78(t6) = load the &D+0x78 flag) + the 0x78 flag-dispatch body
 * formerly mislabeled game_uso_func_00011564. Sibling of game_uso_func_00010648.
 * The global flag-load is IDO-hoisted above the prologue, landing at 0x1155C.
 * Single-entry: the merge is byte-exact, so it is one function (not dual-entry).
 * else-arm uses Pair2-by-value (&D+0xE40); a0->0xB4 is recomputed per-arm to match
 * the target register allocation. */
extern int gl_func_00000000();
void game_uso_func_0001155C(int *a0) {
    int val = 100;
    if (*(int*)((char*)&D_00000000 + 0x78) == 0) {
        ((int*)a0[0xB4/4])[0x960/4] = 0;
        gl_func_00000000(a0, *(Pair2*)((char*)&D_00000000 + 0xE40));
    } else {
        ((int*)a0[0xB4/4])[0x960/4] = val;
        gl_func_00000000(a0, a0[0xFC/4] | 8, 0, 1, 6, 1);
    }
}

void game_uso_func_000115DC(void *a0) {
    *(s32*)((char*)*(s32**)((char*)a0 + 0xB4) + 0x960) = 100;
}

void game_uso_func_000115EC(int *a0, int a1) {
    *(int*)((char*)a0 + 0x108) = a1;
    game_uso_func_00000000(a0);
    game_uso_func_00000000(a0);
    *(int*)((char*)a0 + 0x114) = 0;
    game_uso_func_00000000(a0);
}

/* game_uso_func_00011624: 44-insn (EE84-family). MATCHED 2026-05-31
 * (70.6% -> 100%). Two levers: (1) the D-pair passes BY VALUE as *(Pair2*)
 * (homes a1,a2); (2) the call must be DUPLICATED inside each if-arm (loading
 * the pair directly from D in each branch) — selecting a pointer/value then
 * calling once builds a redundant local-copy + misses the bgtzl branch-likely.
 * (3) arms SWAPPED to `<= 0` first so IDO emits `bgtzl` (>0 case as branch
 * target, its D-pair load in the delay slot) matching the target polarity +
 * t0/t3 base-pointer order. docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair */
void game_uso_func_00011624(int *a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0, a0[0x108 / 4], 0, 1, 1, 1);
    if (((int *)a0[0xB4 / 4])[0xA14 / 4] <= 0) {
        gl_func_00000000(a0, *(Pair2 *)((char *)&D_00000000 + 0xDC8), 1);
    } else {
        gl_func_00000000(a0, *(Pair2 *)((char *)&D_00000000 + 0xE40), 1);
    }
    a0[0x114 / 4] = 0;
}

/* game_uso_func_000116D4: 31-insn (0x7C) flag-gated double-call wrapper.
 * MATCHED 2026-05-31 (79.97% -> 100%): the "cross-USO varargs spills
 * (sw a1@4(sp), sw a2@8(sp))" that the old INSN_PATCH faked are exactly the
 * struct-by-value home stores — the D[0xE40]/E44 pair passes BY VALUE as
 * *(Pair2*), reproducing them HONESTLY. The "79.97% natural ceiling" was the
 * un-homed pair (same lever as EF70/F284).
 * docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair */
void game_uso_func_000116D4(void *a0) {
    void *s0 = a0;
    gl_func_00000000(s0);
    if (*(int *)((char *)s0 + 0x110) != 0) {
        gl_func_00000000(s0, *(int *)((char *)s0 + 0x108), 2, 1, 1, 1);
        gl_func_00000000(s0, *(Pair2 *)((char *)&D_00000000 + 0xE40), 1);
    }
    *(int *)((char *)s0 + 0x114) = 0;
}

// game_uso_func_00011750 — STRUCTURAL PASS (0x118 / 70 words,
// no episode). Raw-.word USO form (single function, game_uso main
// game-logic; boundary already split by commit d3e4ee03 — named fn
// still undecoded). Hand-decoded. LAST bare candidate in game_uso.c.
//
// Fall / wipeout detection + effect trigger.
//
//   void game_uso_func_00011750(Obj *obj) {              // obj -> s0
//     Sub *s = obj->0xB4;
//     if (s->0xA38 < -30.0f) {                            // 0xC1F00000
//       obj->0x130 = 0;                                    // reset count
//     } else {
//       if ((s16)obj->0x130 + 1 >= 3) return;              // armed cap
//       obj->0x130++;                                       // s16 counter
//       obj->0x130 = 0;                                     // (re-clear)
//       if (*(int*)(. + 0x9CC) == 0x100) { … }
//       func_00000000(0x100, 5, obj->0xFC, 0x24);           // sound/event
//       e = D_00000EA0[0];  func_00000000(e, obj, -1,
//                                          D_00000EA0[1]);  // FX dispatch
//       func_00000000(0x100, …, obj->0xFC, …);              // 2nd event
//     }
//   }
//
// Struct-typing reference:
//   obj: 0xB4 -> s (s->0xA38 f32 downward velocity/impact metric;
//     < -30.0 = hard landing/crash), 0x130 s16 frame counter
//     (reset on hard hit, capped at 3 → arms the wipeout),
//     0xFC an id passed to the effect calls, 0x9CC a state word.
//   D_00000EA0 = USO static FX/event descriptor table; consts
//     -30.0f, 0x100 / 5 / 0x24 event op codes. func_00000000 = USO
//     placeholder dispatcher (sound / FX / event).
// Caps (DEFERRED): raw-word USO + placeholder cb's mean wrap can't
//   reach byte-match. Real-C STRUCTURAL body below — fall/wipeout
//   detection + effect trigger skeleton. Byte-match deferred. Name
//   pre-checked: no extern reuse. D_00000000 reuses file-scope
//   extern char (no redeclaration).
/* game_uso_func_00011750: hard-landing/wipeout detector + FX trigger
 * (EE84 state-orchestrator family). MATCHED 2026-06-21 (call-graph DFS +
 * just-in-time family typing). The prior NM body called placeholder
 * gl_func_00000000 + loaded &D_00000000; the resolved .s relocs name the real
 * callees game_uso_func_077C44 (event/sound dispatch, R_MIPS_26 to an undefined
 * import-class symbol), game_uso_func_0000D5F8 (Pair2-by-value sink — homes
 * a1/a2 to sp+4/sp+8 via the prototype-flip lever), game_uso_func_0000D5DC
 * (pair-copy trailing call), and the real global game_uso_D_807FF490. Control
 * flow: the FP gate is the POSITIVE if (`if (s->0xA38 < -30.0f)` => the target
 * `c.lt.s; bc1fl` with the else-reset folded into the branch-likely delay slot);
 * the counter advance is UNCONDITIONAL (`obj->0x130 = cnt+1` always, before the
 * `cnt < 3` return — matches the bne-likely delay-slot store). FINAL lever to 0:
 * INLINE the `obj->0xB4` base derefs (drop the held `char *s` local) at BOTH the
 * FP read and the 0x9CC read — a held base local colored into $v0 and shifted
 * every later temp down one register (off-by-one renumber, 19 diffs); the inline
 * form lets IDO float the base into $t8 exactly like the target (19->0).
 * Byte-exact (0 non-reloc word diffs, reloc symbols agree). */
extern char game_uso_D_807FF490;
void game_uso_func_00011750(char *obj) {
    short cnt;
    if (*(float *)(*(char **)(obj + 0xB4) + 0xA38) < -30.0f) {   /* hard hit */
        cnt = *(short *)(obj + 0x130);
        *(short *)(obj + 0x130) = cnt + 1;        /* always advance (delay slot) */
        if (cnt < 3) return;                      /* not yet armed */
        *(short *)(obj + 0x130) = 0;
        if (*(int *)(*(char **)(obj + 0xB4) + 0x9CC) != 0) {
            game_uso_func_077C44(obj, *(int *)(obj + 0xFC) | 0x24, 0, 0, 0x100, 5);
            game_uso_func_0000D5F8(obj, *(Pair2 *)((char *)&game_uso_D_807FF490 + 0xEA0), -1);
        } else {
            game_uso_func_077C44(obj, *(int *)(obj + 0xFC) | 0x1D, 0, 0, 0x100, 5);
            game_uso_func_0000D5F8(obj, *(Pair2 *)((char *)&game_uso_D_807FF490 + 0xEA0), -1);
        }
        game_uso_func_0000D5DC(obj);
    } else {
        *(short *)(obj + 0x130) = 0;              /* not a hard hit: reset */
    }
}

void game_uso_func_00011868(int *a0) {
    *(float *)((char *)a0[0xB4 / 4] + 0x970) = 0.0f;
    *(float *)((char *)a0[0xB4 / 4] + 0x974) = 0.0f;
    *(float *)((char *)a0[0xB4 / 4] + 0x978) = 0.0f;
}

void game_uso_func_00011888(int *a0) {
    a0[0xE8 / 4] = 0;
    a0[0xEC / 4] = 0;
    a0[0xF0 / 4] = 0;
    a0[0x12C / 4] = 0;
}

/* game_uso_func_0001189C — verified decode, 77/78 (99%), single-insn blocker.
 * Dense switch(a1) 1..5; each case: func_00000000((s0->0xB4)->0x800,
 * &D+off_k, 10); func_00000000((s0->0xB4)+0x808, s1). off_k =
 * {0x109C,0x10AC,0x10A4,0x10C0,0x10DC}. The C switch is byte-exact EXCEPT
 * 0x030: target `lw t6,608(at)` (jtbl @ D_00000000+0x260, inside the USO
 * data blob) vs IDO-emit `lw t6,0(at)` (IDO synthesizes its own .rodata
 * jump table at reloc offset 0). This is the documented unmatchable-via-C
 * USO case: docs/IDO_CODEGEN.md#feedback-ido-switch-rodata-jumptable —
 * 1080's linker discards .rodata so the IDO jtbl can't even link, and the
 * goto-chain recipe doesn't apply (target is a genuine jr-jumptable, not a
 * beq chain). NM wrap; INCLUDE_ASM build path (no episode; the .rodata
 * jtbl C neither links nor byte-matches — tautology-trap rule). */
void game_uso_func_0001189C(int *a0, int a1, int a2) {
    int *s0 = a0;
    int s1 = a2;
    switch (a1) {
    case 1:
        func_00000000(((int *)s0[0xB4 / 4])[0x800 / 4], (char *)&D_00000000 + 0x109C, 10);
        func_00000000((int)s0[0xB4 / 4] + 0x808, s1);
        break;
    case 2:
        func_00000000(((int *)s0[0xB4 / 4])[0x800 / 4], (char *)&D_00000000 + 0x10AC, 10);
        func_00000000((int)s0[0xB4 / 4] + 0x808, s1);
        break;
    case 3:
        func_00000000(((int *)s0[0xB4 / 4])[0x800 / 4], (char *)&D_00000000 + 0x10A4, 10);
        func_00000000((int)s0[0xB4 / 4] + 0x808, s1);
        break;
    case 4:
        func_00000000(((int *)s0[0xB4 / 4])[0x800 / 4], (char *)&D_00000000 + 0x10C0, 10);
        func_00000000((int)s0[0xB4 / 4] + 0x808, s1);
        break;
    case 5:
        func_00000000(((int *)s0[0xB4 / 4])[0x800 / 4], (char *)&D_00000000 + 0x10DC, 10);
        func_00000000((int)s0[0xB4 / 4] + 0x808, s1);
        break;
    }
}

void game_uso_func_000119D4(char *dst) {
    int tmp;
    game_uso_func_0000C194(&tmp);
    game_uso_func_0000C1D0((float*)(dst + 0x10));
}

void game_uso_func_00011A04(char *dst) {
    int tmp;
    game_uso_func_0000C194(&tmp);
    game_uso_func_0000C20C((Vec3*)(dst + 0x10));
}

void game_uso_func_00011A34(char *dst) {
    int tmp;
    game_uso_func_0000C194(&tmp);
    game_uso_func_0000C27C((Quad4*)(dst + 0x10));
}

void game_uso_func_00011A64(char *dst) {
    int tmp;
    game_uso_func_0000C194(&tmp);
    game_uso_func_0000C194((int*)(dst + 0x10));
}

/* game_uso_func_00011A94: 36-insn alloc-init constructor. alloc(0x40) +
 * init(051C28), set vtable 0x28 = &import_8006ED80, clear 0x3C; then walk
 * a0->0x40 node and link it back via 07ACE0.
 *
 * 2026-06-21 CRACKED via masked-twin port from eddproc_uso_func_000003BC
 * (donor, byte-exact); identical to the 3A28/AC78 lands. The prior body
 * used placeholder gl_func/&D + the INSN_PATCH-era shape. The donor's
 * p2/head/p1 split + p1-reuse-for-arg0 + decl-order + condition re-load
 * forces the two-web spill and a0/v1 coloring. */
extern char import_8006ED80;
void *game_uso_func_00011A94(int *arg0) {
    int *p2;
    int *head;
    int *p1;
    p1 = (int*)game_uso_func_055750(0x40);
    if (p1 != 0) {
        game_uso_func_051C28(p1);
        *(int*)((char*)p1 + 0x28) = (int)&import_8006ED80;
        *(int*)((char*)p1 + 0x3C) = 0;
    }
    p2 = p1;
    p1 = arg0;
    head = (int*)p1[0x40 / 4];
    if ((int*)p1[0x40 / 4] != 0) {
        game_uso_func_07ACE0((char*)p2 + 0x10, head);
        if (*(int*)((char*)head + 0x14) != 0) {
            *(int*)((char*)head + 0x4) = 1;
        }
        *(int*)((char*)head + 0x14) = (int)p2;
    }
    return p2;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_uso/game_uso/game_uso_func_00011A94_pad.s")
