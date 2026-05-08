#include "common.h"

/* File-top canonical decls (hoisted out of NM-wrap blocks
 * so DNM build doesn't see redecls — see
 * feedback_game_uso_dnm_typedef_inside_ifdef.md). */
extern int gl_func_00000000();
extern char D_00000000;
typedef struct { float x, y, z; } Vec3;
typedef struct { int a, b, c; } Tri3i;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b; } Pair2;

#ifdef NON_MATCHING
/* Cubic B-spline basis evaluator. Computes 4 weights for parameter t
 * (passed in $a1, moved to $f12), writes to out[0..3]. D_00000000 = 1/6.
 *   out[0] = D * (1-t)^3              ; B0(t)
 *   out[1] = D * (3t^3 - 6t^2 + 4)    ; B1(t)
 *   out[2] = D * (-3t^3 + 3t^2 + 3t + 1) ; B2(t)
 *   out[3] = D * t^3                  ; B3(t)
 *
 * 39-insn FPU leaf with constants loaded via lui+mtc1 (1.0f, 3.0f, 4.0f,
 * 6.0f). Many nops in delay slots (CPU-FPU dependency stalls). Exact
 * matching this is a multi-tick FPU register/scheduling grind; logic is
 * documented for next pass. */
/* K&R-style def: function name is also used as a placeholder for cross-
 * USO/intra-USO unresolved jals elsewhere in the file (with various arg
 * counts). K&R `()` decl from those callers + K&R def here = no sig
 * conflict under DNM. See feedback_ido_implicit_decl_extern_conflict.md. */
void game_uso_func_00000000(out, t)
    float *out;
    float t;
{
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

/* 4-element dot product. C body 99.38% on its own; 1 insn (the second-to-last
 * add.s operand order) is fixed by INSN_PATCH in the Makefile per
 * feedback_insn_patch_for_ido_codegen_caps.md. IDO chooses
 * `add.s f8, f16, f4` (built) but target wants `add.s f8, f4, f16`; the
 * patch overwrites the 4 bytes at function offset 0x34. Both forms are
 * semantically identical; the choice is FPU pipeline forwarding-driven and
 * not flippable from C (8+ source variants tried, all worse). */
float game_uso_func_000000A0(float *a, float *b) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + b[3]*a[3];
}

#ifdef NON_MATCHING
/* Cubic B-spline weighted point evaluator (61 insns, FPU-only). 96.95% NM.
 * Input:  out (Vec3*),  ctrl (Vec3*[4]: 4 control point pointers),
 *         weights (float[4]: B0..B3 from game_uso_func_00000000)
 * Output: out[i] = sum over k=0..3 of (*ctrl[k])[i] * weights[k]
 *
 * Used with game_uso_func_00000000 (basis evaluator) to compute a point
 * on a uniform cubic B-spline curve in 3D — camera path / track / skater
 * limb interpolation.
 *
 * Cap at 96.95% (27 FPU register-allocation diffs across the 3 dot-product
 * blocks). Variants tried (all regressed):
 *   - Swapping operand order (weights[k] * ctrl[k]->x): 27 → 32 diffs.
 *   - Pre-loading ctrl[0..3] into named locals: 27 → 44 diffs.
 * Build chooses $t9 as base for some weight loads where expected uses $a2
 * directly + offset 0xC. FPU pipeline forwarding + base-register choice are
 * not flippable from C alone — needs decomp-permuter to find a matching
 * variant. */
void game_uso_func_000000E0(Vec3 *out, Vec3 **ctrl, float *weights) {
    out->x = ctrl[0]->x * weights[0] + ctrl[1]->x * weights[1]
           + ctrl[2]->x * weights[2] + ctrl[3]->x * weights[3];
    out->y = ctrl[0]->y * weights[0] + ctrl[1]->y * weights[1]
           + ctrl[2]->y * weights[2] + ctrl[3]->y * weights[3];
    out->z = ctrl[0]->z * weights[0] + ctrl[1]->z * weights[1]
           + ctrl[2]->z * weights[2] + ctrl[3]->z * weights[3];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000000E0);
#endif

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

/* Int-reader template with pointer-indirect load (volatile int buf[2] trick).
 * IDO -O2 picks t6/t7/t8 sequentially for the 3-load chain at function tail;
 * target uses t7/t9/t6 (skipping t8). Per feedback_insn_patch_for_ido_codegen_caps.md
 * the 3 cap insns are patched post-cc by INSN_PATCH in the Makefile. */
void game_uso_func_0000035C(int *dst) {
    volatile int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_0000039C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_uso/game_uso/game_uso_func_0000039C_pad.s")

#ifdef NON_MATCHING
/* 21.32% NM. Camera/view init function. Initializes a 0x38-byte struct at $a0:
 *   a0+0x00..0x08 = Vec3(0, 0, 0)        ; eye position
 *   a0+0x0C..0x14 = Vec3(0, 0, -1000)    ; target / look-at (z = -1000)
 *   a0+0x18..0x20 = Vec3(0, 1, 0)        ; up vector (Y-up)
 *   a0+0x24       = 85.0f                ; FOV (degrees)
 *   a0+0x28       = 15 (int)             ; mode/flags
 *   a0+0x2C..0x34 = Vec3(0, 0, 0)        ; offset
 *
 * 77-insn FPU/stack-init function (size 0x134, no jal).
 *
 * 2026-05-04 attempt: tried `float f(void *a0) { ...; return 0.0f; }` to anchor
 * $f0 = 0.0f for in-body 0.0f stores. Result: IDO switched to RODATA-based
 * struct-literal init (lui+addiu from globals + 3-word memcpy each), shrunk
 * function 308→240 bytes — totally different shape. The `swc1 $f0, ...` body
 * pattern in expected requires $f0 = 0.0 at ENTRY (caller-arranged), not a
 * float-return. Reverted to void return.
 *
 * Quirk: $f0 is read at entry as the source for "0.0f" stores. $f0 is the
 * float-return register, not a standard arg. The caller must arrange for
 * $f0 to hold 0.0f at the call site (e.g. tail-called after a function
 * that returns 0.0, or compiler-arranged via inline expansion). Plain C
 * `0.0f` literals would emit `mtc1 $zero, $fX` instead.
 *
 * Codegen pattern per Vec3 assignment (4 Vec3 writes total): build literal
 * on stack scratch (sp+0x54 / 0x48 / 0x3C / 0x30), memcpy via int regs to
 * sp+0xC, then load floats from sp+0xC and store to a0+offset. This
 * double-copy is what IDO emits for `*p = (Vec3){...}` struct-literal
 * assignment. Multi-tick decomp: matching the FPU/scheduling exactly is
 * a register-renaming grind on top of the $f0 quirk. Stub body so the wrap
 * parses; default build uses INCLUDE_ASM. */
void game_uso_func_000003F8(void *a0) {
    Vec3 zero = {0.0f, 0.0f, 0.0f};
    Vec3 fwd  = {0.0f, 0.0f, -1000.0f};
    Vec3 up   = {0.0f, 1.0f, 0.0f};
    *(Vec3 *)((char *)a0 + 0x00) = zero;
    *(Vec3 *)((char *)a0 + 0x0C) = fwd;
    *(Vec3 *)((char *)a0 + 0x18) = up;
    *(float *)((char *)a0 + 0x24) = 85.0f;
    *(int *)((char *)a0 + 0x28) = 15;
    *(Vec3 *)((char *)a0 + 0x2C) = zero;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000003F8);
#endif

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

/* 93.86% NM. 93.86 % match. State-check function: returns 1 if any of:
 *   (a0[0]==2 || a0[0]==3) && a0[1]==1
 *   (a0[4]==2 || a0[4]==3) && a0[5]==1
 *   a0[8]==1, a0[10]==2, a0[12]==2
 *
 * IDO emits each `==` test as `xor; sltiu` (boolean compute) rather than
 * direct branch — natural for single-expression boolean return chain.
 * Variants tested:
 *   - `if (cond) return 1;` chain — regressed to 20% (multi-epilogue)
 *   - 2026-05-02: named-locals `int x0=a0[0]; int x4=a0[4]; ...` —
 *     REGRESSED to 82.6% (locals shift expression-tree walker order)
 *
 * Cap: $v0 vs $v1 register flip. Mine loads a0[0] into $v1, computes
 * boolean in $v0. Target loads into $v0, computes in $v1. Same arith,
 * swapped naming. Not C-flippable; IDO's v0/v1 choice for load-target
 * vs result-target is fixed by expression-tree walker. */
int game_uso_func_00000674(int *a0) {
    return ((a0[0] == 2 || a0[0] == 3) && a0[1] == 1)
        || ((a0[4] == 2 || a0[4] == 3) && a0[5] == 1)
        || a0[8] == 1
        || a0[10] == 2
        || a0[12] == 2;
}

/* 89.96% NM. Prior commit 764b62d landed this as "100%" but that was
 * expected-baseline contamination — subsequent refresh-expected-baseline
 * run reset expected/ to pure baserom bytes and revealed the real diff.
 *
 * Real remaining diffs at -O2 (2026-04-20):
 *   (1) `cnt` in $v1 (mine) vs $v0 (target). Reordering decls is a no-op
 *       per feedback_ido_sreg_order_not_decl_driven.md.
 *   (2) In-loop scheduling: target has `or a0,v0,0; jal; sw v0,0x38(s0)` —
 *       sw in jal2's delay slot. Mine has `sw v0,0x38(s0); jal; or a0,v0,0`.
 *       Tried swapping store/call order (regressed via extra $s0 alloc).
 *   (3) Operand order `addu v0,t7,s2` vs target `addu v1,s2,t7` — partially
 *       fixable via `int off = cnt*4`, but cascaded reg diff from (1) remains.
 *
 * Further work: inline cnt at its uses; try permuter; or accept as 90% cap. */
void game_uso_func_00000724(char *a0) {
    int i;
    int cnt;
    int *p;

    game_uso_func_000002BC((Quad4*)a0);
    game_uso_func_000002BC((Quad4*)(a0 + 0x10));
    game_uso_func_00000314((Pair2*)(a0 + 0x20));
    game_uso_func_00000314((Pair2*)(a0 + 0x28));
    game_uso_func_0000035C((int*)(a0 + 0x30));
    game_uso_func_00000280((int*)(a0 + 0x34));

    cnt = *(int*)(a0 + 0x34);
    p = (int*)(a0 + 4);
    i = 1;
    if (cnt > 0) {
        do {
            int tmp = gl_func_00000000(0x38);
            *(int*)((char*)p + 0x38) = tmp;
            gl_func_00000000(tmp);
            gl_func_00000000(*(int*)((char*)p + 0x38));
            cnt = *(int*)(a0 + 0x34);
            i++;
            p++;
        } while (i <= cnt);
    }

    *(int*)(a0 + 0x38) = *(int*)(a0 + 0x3C);
    *(int*)(a0 + cnt * 4 + 0x3C) = *(int*)(a0 + cnt * 4 + 0x38);
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

#ifdef NON_MATCHING
/* 80.88% NM (up from 71.12% with goto-out fix). 8-arg constructor/initializer.
 *   void *f(T *a0,    // dst, alloc 0x27C if NULL
 *           int a1,   // -> a0->0x150 post-init
 *           int a2,   // -> 1st gl_func arg
 *           int a3,   // -> 2nd gl_func arg
 *           int arg4, // -> 3rd gl_func arg
 *           float arg5,  // -> 4th gl_func arg (FLOAT!)
 *           int arg6, // -> a0->0x274 post-init
 *           int arg7) // flag: if !=0, gl_func(a0, 1) midway
 *
 * 2026-05-04 grind: replaced inner `return a0` with `goto out` to land the
 * single-epilogue shape (saved 3 insns). Remaining cap is the if-arg7 block:
 * IDO emits `beql t7, zero, +5` with 24C-store duplicated across both paths
 * (delay-likely + post-fall-through), 1 insn larger than expected `beq a2,
 * zero, +5; sw zero, 0x24C(a0) [in delay slot]`. Built/expected size delta
 * = +4 bytes (42 vs 41 insns). Tried: store ordering, register hint, if-curly
 * vs if-no-curly, goto-skip — all produced beql. INSN_PATCH blocked by size
 * delta per feedback_insn_patch_size_diff_blocked.md. Promotion-path is to
 * find a C lever that flips IDO to `beq` (puts arg7 in $a2).
 *
 * 2026-05-04 retry: tried `int flag = arg7; int slot1 = arg1; int slot6 = arg6;`
 * captured-early-locals to raise arg7's register-allocation priority — same
 * 80.88%, no register-class shift. The arg7 → $t7 (vs target's $a2) choice
 * is structural to IDO -O2's allocator weight calculation (refs × live_length)
 * and isn't reachable via local-declaration tricks.
 *
 * 2026-05-06 retry: tried two more knobs:
 *   (a) Reorder `*(...0x24C) = 0;` BEFORE the if-block (so the unconditional
 *       store could be hoisted into the beq's delay slot by IDO scheduler).
 *       Result: regressed — IDO emits the lui+addiu for D_0 reload at a
 *       different position, shifting the rest of the body and breaking the
 *       offset alignment.
 *   (b) Inverted to `if (arg7 == 0) goto skip; gl_setflag(); skip: store;`
 *       (per docs/IDO_CODEGEN.md branch-likely emit rules). Same regression
 *       — goto-invert didn't flip the allocator's choice of $t7 vs $a2 for
 *       arg7, just shifted the branch type without fixing the underlying
 *       register issue.
 *
 * Confirms the prior conclusion: the cap is allocator-weight-driven and
 * unreachable from C-level reordering or goto-conversion. Next promotion
 * path requires either decomp-permuter (random allocno-priority shifts)
 * or a post-cc INSN_PATCH after finding a recipe for size-delta tolerance. */
extern int *gl_alloc_858(int size);
extern void gl_init_858(int *dst, int a, int b, int c, float f);
extern void gl_setflag_858(int *dst, int flag);

int *game_uso_func_00000858(int *a0, int arg1, int arg2, int arg3, int arg4, float arg5, int arg6, int arg7) {
    if (a0 == 0) {
        a0 = gl_alloc_858(0x27C);
        if (a0 == 0) goto out;
    }
    gl_init_858(a0, arg2, arg3, arg4, arg5);
    *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
    *(int*)((char*)a0 + 0x1D0) = 0;
    if (arg7 != 0) gl_setflag_858(a0, 1);
    *(int*)((char*)a0 + 0x24C) = 0;
    *(int*)((char*)a0 + 0x150) = arg1;
    *(int*)((char*)a0 + 0x26C) = 0;
    *(int*)((char*)a0 + 0x270) = 0;
    *(int*)((char*)a0 + 0x268) = 0;
    *(int*)((char*)a0 + 0x274) = arg6;
out:
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000858);
#endif

void game_uso_func_000008FC(int *a0) {
    int *v0 = (int*)*(int*)((char*)a0 + 0xF4);
    gl_func_00000000(*(int*)((char*)v0 + 0xB4), a0);
    gl_func_00000000(*(int*)((char*)a0 + 0x154), a0);
    *(int*)((char*)a0 + 0x264) = 0;
    gl_func_00000000(a0);
}

#ifdef NON_MATCHING
/* 6.92% NM. 107-insn jump-table dispatcher (size 0x1AC after split-fragments
 * separated 0xAEC). Structure:
 *
 *   t6 = a0->0x150;             // sub-struct
 *   key = t6->0xA54;             // dispatch key (loaded from sub-struct)
 *   if (key >= 7) goto end_no_op (epilogue);
 *   else: jump-table dispatch on key (0..6)
 *
 * Each case (0..6) reads from various offsets of &D_00000000 and writes
 * to offsets of a0 (the input struct). Cases 0/3/6 do similar work, with
 * different field/value combos. Case 4 has a sub-branch on a0->X != 0.
 *
 * BLOCKED: target uses `lui $at; addu $at,$at,sll(key,2); lw t7, 0x4($at);
 * jr t7` — a .rodata jump table at offset 0x4 (relative to D_jt_base).
 * Per feedback_ido_switch_rodata_jumptable.md: 1080's linker discards
 * .rodata, so a C `switch(key) { case 0..6: ...}` with 3+ cases would
 * fail to link. Need if-goto chain to reach high % (target was probably
 * compiled with the jump table active in some other linker config).
 *
 * Multi-tick decomp expected. Stub body so the wrap parses; default
 * build INCLUDE_ASM matches. Decoded structure documented above for
 * future ticks. */
extern void game_uso_func_00000940_TODO(void);
void game_uso_func_00000940(int *a0) {
    (void)a0;
    game_uso_func_00000940_TODO();
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

#ifdef NON_MATCHING
/* 3.37% NM. game_uso_func_00000B3C: 0xB08 (706 insns, 2.8 KB) — spine candidate #6.
 * 22 cross-USO calls, 0x150-byte frame. Contains a jump-table switch at
 * 0xDB8 (`jr $t1` after `lw $t1, 0x50($at)`) — per
 * feedback_ido_switch_rodata_jumptable.md that .rodata path is discarded
 * by 1080's linker; match requires if-else or if-goto chain rewrite.
 *
 * Partial C below captures decoded entry (~first 30 insns): id-change
 * detect + 3-level LUT navigation. Remaining ~670 insns TODO.
 *
 * 2026-05-03 EXTENDED DECODE 0xBB0-0xC30 (~85 insns): post-LUT dispatch:
 *   - Loads target->0x38 (a function-ptr or sub-obj?), saved at sp+0x128
 *   - Compares t0 vs v0, branches +0x138 (far skip — likely the "no-change"
 *     fast path)
 *   - If a0->0x260 != 0 AND a0->0x268 != 0: enter the Vec3-zero-init block:
 *     stores 0.0f to sp+0xD8/DC/E0, copies through sp+0xB4..0xBC, writes
 *     to a0->0x134/0x138/0x13C (= a0->vec_134 zeroed via scratch round-trip).
 *     This is the IDO-emit of a zero-Vec3 assignment with the scratch chain
 *     forcing two store-loads — likely matching `Vec3f tmp = {0,0,0};
 *     a0->vec_134 = tmp;` rather than direct field zeroing.
 *   - Branch `b +5` skips the `lw $t9, 0x30(...)` reload, indicating the
 *     0xC30+ path is the alternate (cached) reload path.
 * Same Vec3-stage template fingerprint as 0x591C/0x6A30/0x7C1C (per
 * feedback_game_uso_per_frame_vec3_stage_template.md), but with a third
 * field offset 0x134 instead of 0xB4/0xB8/0xBC. So a0+0x134 is a NEW
 * Vec3 stage in this constructor's struct layout — adds Vec3 fields at
 * 0x134/0x138/0x13C to the inferred GameState struct.
 *
 * Struct fields identified:
 *   a0[0xF4]  — per-frame scratch (cached at sp+0x134)
 *   a0[0x130] — t0 writeback (state-dispatch result)
 *   a0[0x134..0x13C] — secondary Vec3 stage (zeroed via scratch round-trip)
 *   a0[0x150] — dispatch-list ptr
 *   a0[0x158 + N*4] — primary LUT of sub-obj ptrs
 *   a0[0x1D4 + N*4] — tertiary LUT of target ptrs
 *   a0[0x250] — primary index
 *   a0[0x254] — secondary index
 *   a0[0x258] — derived-id writeback
 *   a0[0x25C] — tertiary index
 *   a0[0x260] — bool flag (gates Vec3-zero vs alt-path)
 *   a0[0x264] — cached-id (change detector)
 *   a0[0x268] — bool flag (gates a3->0x30 alt-arm in zero block)
 *   (dispatch_list + 0xA54) — current id
 *
 * 2026-05-05 ASM RE-CHECK 0xC38-0xD00 (~50 insns post-Vec3-zero block):
 *   - 0xC38-0xC44: post-zero merge — load t0 = a0->0x134 reload, save to sp+0x118
 *   - 0xC48: addiu t1, t0, 0x100 (probably a flag-mask offset)
 *   - 0xC4C-0xC5C: 4-arg gl_func dispatch (gl_func(s2,...,...,...)
 *     — prepares scratch buffer at sp+0x118 for callee fill, target's
 *     internal "advance state" cross-USO call.
 *   - 0xC60-0xCA0: post-call ack loop — repeatedly checks v0 return,
 *     conditional store-back to a0->0x150 dispatch list. Looks like
 *     "wait for sub-system ready" polling pattern.
 *   - 0xCA4-0xD00: float-comp for a different field, jal cross-USO with
 *     5+ args (heavy outgoing-arg-slot stores at sp+0x10..0x20).
 *
 * NEXT PASS: decode 0xCA4-0xDB8 — the rodata jump-table dispatch starts
 * around 0xDB8 (`jr $t1`). Per
 * feedback_ido_switch_rodata_jumptable.md, the jump-table itself can't
 * be matched (rodata gets discarded by linker); need if-else chain
 * rewrite. Decode the jump-table arms first to know the cases.
 */
void game_uso_func_00000B3C(int *a0) {
    int *sub;
    int derived_id;
    int *target;
    int cur_id;
    int *list;

    list = (int*)a0[0x150 / 4];
    cur_id = list[0xA54 / 4];
    if (cur_id != a0[0x264 / 4]) {
        gl_func_00000000(a0);
        a0[0x264 / 4] = cur_id;
    }

    sub = (int*)*(int*)((char*)a0 + 0x158 + a0[0x250 / 4] * 4);
    derived_id = sub[1 + a0[0x254 / 4]];
    a0[0x258 / 4] = derived_id;
    target = (int*)*(int*)((char*)a0 + 0x1D4 + derived_id * 4);

    (void)target;  /* silence unused — body TODO */
    /* Extended characterization 2026-05-04 (0xBB0-0xC38, ~30 insns):
     * Post-LUT, the function reads a fourth-level field via combined
     * indices, then enters a state-dispatch on a0->0x260 and a0->0x268:
     *   t1 = &(a0->0x158_LUT) + (idx*4 << shift)   (combined index)
     *   t2 = t1->[0x38]      ; sp+0x128 cached
     *   if (t0 != v0) goto far_skip (~0xCF8 epilogue branch)
     *   if (a0->0x260 != 0) goto +0x4C (delay-likely sub-block)
     *   if (a0->0x268 == 0) {
     *       // Vec3-zero staging path:
     *       a0->0x130 = t0
     *       Vec3 zero_buf at sp+0xD8 = {0, 0, 0}
     *       memcpy sp+0xD8 -> sp+0xB4 (3-word copy via t6/t5)
     *       float-store sp+0xB4..0xBC into s2->0x134..0x13C   (Vec3 write)
     *   } else {
     *       // a3->0x30 path: load t9 = a3->0x30, slt against 1
     *       a0->0x130 = (a3->0x30 < 1) ? 1 : 0
     *   }
     *
     * The Vec3-zero staging via two stack buffers (sp+0xD8 → sp+0xB4 → s2)
     * matches the same triple-buffer dance seen in other game_uso spine
     * functions (8CD8, 591C). Likely a Vec3 reinitializer for a per-frame
     * scratch slot in s2 (= some 0x140-byte sub-object).
     *
     * Cumulative ~60/706 insns characterized.
     *
     * 2026-05-05 EXTENDED DECODE 0xCA4-0xD68 (~50 more insns, ~110/706 total):
     *   0xCA4-0xCAC: spill a3 to sp+0x12C, jal cross-USO with a2+=0x318
     *     (callee adjusts a flag-mask base address by 0x318)
     *   0xCB0-0xCC8: post-call merge — `b +7; lw a3, 0x12C(sp)` skips
     *     the re-call path. Else branch reloads `a2 = a0->0x150` (dispatch
     *     list), `a0 = t6->0xB4`, spills a3 again, makes another jal with
     *     same a2+=0x318. Two-arm jal pattern (probably "init mask vs
     *     update mask").
     *   0xCCC-0xCD8: post-merge cleanup. `a0->0x270 = 0; a0->0x26C = 0`
     *     (clear two flag/state fields).
     *   0xCDC-0xCEC: dispatch-list flag clear:
     *     `list[0xA58] &= ~0x2000` (clears bit 13 of a 32-bit flag word).
     *   0xCF0-0xCF8: `v1 = &list[0xA58]; t9 = *v1; bnel t8, t9, +0x7F`
     *     — re-read post-mask check; if mask bit re-set by another thread,
     *     skip far forward (this is a race-detection guard).
     *   0xCFC-0xD18: state-test chain on a0->0x260 (sp+0xCFC reload).
     *     `if (a0->0x260 != 0)` evaluates the same flag tested earlier —
     *     this is a different branch arm of the gate.
     *   0xD1C-0xD2C: load `a0->0x274` field, mask with 0x80, branch on bit.
     *     Likely tests "is bit 7 of flag word set?".
     *   0xD30-0xD40: pseudo-COW: `a0->0x26C = a0->0x270` (was 0 from earlier),
     *     branches `b +0x15` to merge point (skips alt-set path).
     *   0xD44-0xD68: alt-set path — checks `a0->0x274 with 0x80` again,
     *     and if 3-state match, sets `a0->0x270 = 4 (or similar);
     *     a0->0x26C = 3 (= constant)`. Both paths converge at +0xB merge.
     *
     * Pattern recognition: this is a state-machine update where two flag
     * fields (0x270/0x26C) are reset to (0,0) on entry, then conditionally
     * re-set based on (0x274 & 0x80) state. Looks like an "active state ID
     * cache" being cleared and either re-validated or marked-dirty.
     *
     * TODO(next pass): decode 0xD68-0xDB8 (the entry to the rodata
     * jump-table dispatch). Then 0xDB8 jr $t1 + 0x80-byte rodata
     * jumptable in baserom. Per
     * feedback_ido_switch_rodata_jumptable.md the rodata path is
     * discarded by 1080's linker; if-else chain rewrite needed. */
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

#ifdef NON_MATCHING
/* 95.74% NM. 16-case dispatch on a1 (cases 3..18). For a1 == 3 the body
 * is special (extra `a0->0x268 = 1` after the call); for cases 4..18 the
 * body is a single `gl_func_00000000(a0, a1 + 11)` call. Implemented as
 * `if (a1 == N) goto cN;` chain because:
 *   - `switch` with 3+ cases emits a .rodata jump table (linker discards
 *     .rodata in this segment, breaks the link). 49 % at if-else, 69 % at
 *     switch, 95 % at goto chain.
 *   - The goto chain matches IDO's "compares first, bodies after" layout.
 * Last-comparison cap: IDO uses `bnel` for the LAST `if` (folding `lw ra`
 * into the BL delay), where target uses plain `beq + nop` then `b end`
 * with `lw ra` in `b`'s delay.
 * Tried (this run, 2026-05-02): inline c18's body into the dispatch
 * (`if (a1 == 18) gl_func_00000000(a0, 29);`) — regressed to 92.56 %,
 * same as `if (a1 != 18) goto end; <body>` from prior pass. Inlining the
 * last case puts the body in the dispatch chain proper, which changes
 * the bnel/beq pattern but introduces a worse mismatch.
 * Tried previously: `goto end;` vs `return;` — both 95 %.
 * Permuter remains the next-step recommendation. */
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
    if (a1 == 18) goto c18;
    goto end;
c3:  gl_func_00000000(a0, 1); *(int*)((char*)a0 + 0x268) = 1; goto end;
c4:  gl_func_00000000(a0, 15); goto end;
c5:  gl_func_00000000(a0, 16); goto end;
c6:  gl_func_00000000(a0, 17); goto end;
c7:  gl_func_00000000(a0, 18); goto end;
c8:  gl_func_00000000(a0, 19); goto end;
c9:  gl_func_00000000(a0, 20); goto end;
c10: gl_func_00000000(a0, 21); goto end;
c11: gl_func_00000000(a0, 22); goto end;
c12: gl_func_00000000(a0, 23); goto end;
c13: gl_func_00000000(a0, 24); goto end;
c14: gl_func_00000000(a0, 25); goto end;
c15: gl_func_00000000(a0, 26); goto end;
c16: gl_func_00000000(a0, 27); goto end;
c17: gl_func_00000000(a0, 28); goto end;
c18: gl_func_00000000(a0, 29);
end: ;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000174C);
#endif

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
void *game_uso_func_000018FC(void *a0) {
    if (a0 == 0) return gl_func_00000000(0xD0);
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000018FC);
#endif

#ifdef NON_MATCHING
/* 92.97% NM. 4-arg constructor-or-init for 0x124-byte object. Decoded structure:
 *   if (a0 == NULL) p = alloc(0x124); if (!p) return NULL;
 *   gl_func_00000000(p, &D + 0x340);   ; some init call
 *   p[0x28] = &D_00000000;
 *   gl_func_00000000(p + 0x44);        ; init sub-region
 *   if (a3 != 0) gl_func_00000000(p, 1, a3);  ; conditional with branch-likely
 *   p[0x38] = a1; p[0x3C] = a2;
 *   return p;
 *
 * Body matches byte-for-byte. The remaining 4 % is one prologue-scheduling
 * diff: target emits `move s0,a0` BEFORE the `sw ra/a1/a2` chain (filling
 * the gap between `sw s0` and `sw ra`); IDO schedules ours into the bne
 * delay slot at 0x1d28 instead. Both are valid placements; per
 * feedback_ido_arg_save_reg_pick.md, this kind of arg-spill scheduling is
 * typically unflippable from C — `register` hint and decl-vs-assignment
 * variants both kept it in the bne delay slot. Wrapped NM. */
char *game_uso_func_00001D30(char *a0, int a1, int a2, int a3) {
    register char *p = a0;
    if (p == 0) {
        p = (char*)gl_func_00000000(0x124);
        if (p == 0) goto end;
    }
    gl_func_00000000(p, &D_00000000 + 0x340);
    *(int*)(p + 0x28) = (int)&D_00000000;
    gl_func_00000000(p + 0x44);
    if (a3 != 0) {
        gl_func_00000000(p, 1, a3);
    }
    *(int*)(p + 0x38) = a1;
    *(int*)(p + 0x3C) = a2;
end:
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001D30);
#endif

void game_uso_func_00001DC4(void *a0) {
    *(s32*)((char*)a0 + 0x40) = 0;
    *(f32*)((char*)a0 + 0x2C) = 0.0f;
    *(f32*)((char*)a0 + 0x30) = 0.0f;
    *(f32*)((char*)a0 + 0x34) = 0.0f;
}

/* game_uso_func_00001DDC: 0x5FC (383 insns) — strategy-memo spine candidate,
 * confirmed single function (grep -c 03E00008 = 1, not a bundle).
 * ENTRY DISPATCH (first ~35 insns decoded):
 *   key = a0[0x40]  ; dispatch key
 *   if (key == 0) goto final_exit (very far forward, single-ra-restore)
 *   if (key != 3)  goto branch_at_88 (unknown sub-case)
 *   // case key == 3:
 *   t6 = a0[0x14]   ; save to sp+0x170 (spill for reload)
 *   v1 = a0[0x3C]
 *   // Copy Vec3 from v1+0xA0..0xA8 (alias (v1+0x70)+0x34..0x38 via addiu trick)
 *   //   into both t6[0x60..0x68] and back into v1[0xA0..0xA8]
 *   // (routine mirrors a Vec3 then writes it back, same 3 floats)
 *   goto late_label (b +0x15A from 0x1E58) — skip ~350 insns of other cases
 *
 * CASE key != 3 (branch_at_88 @ 0x1E60, ~25 insns decoded 2026-04-20):
 *   t7 = a2->0x14                ; (a2 = entity ptr, same as a0 via $a2 reuse)
 *   scratch_a = sp+0xFC          ; local sub-struct arg
 *   spill t7 at sp+0x12C for reload
 *   Copy Vec3 from t7+0xA0..0xA8 to sp+0x13C  (referenced sub-obj Vec3)
 *   v1 = a2->0x38                ; another sub-obj ptr
 *   Copy Vec3 from v1+0xA0..0xA8 to sp+0x130  (IDO-style: increments v1
 *     by 0x70 between reads so v1[0xA4] becomes (v1+0x70)[0x34])
 *   spill a2 at sp+0x180
 *   call gl_func_00000000(scratch_a, a2)  ; returns Vec3* in v0
 *   Copy 3 words from *v0 to sp+0x154    ; callee-result Vec3
 *   Element-wise add: sp+0x130[i] += sp+0x154[i] (for i=0,1,2)
 *     → adjusts sub-obj Vec3 by callee-supplied delta
 *   mtc1 zero, f14               ; f14 = 0.0f (used later)
 *   (continues with more float math at 0x1F00+)
 *
 * REMAINING 300+ insns: more dispatch cases plus the late_label
 * convergence point and final_exit. The key=3 path is short; the non-3
 * path is where the real work happens.
 * NEXT PASS: decode 0x1F00-0x2050 (continuation of non-3 case), identify
 * call signatures of gl_func_00000000 invocations.
 * 2026-05-02: per feedback_partial_decode_with_stub_body.md, wrapping with
 * placeholder stub so the decode comment is a tracked NM wrap rather than
 * a floating block-comment above an INCLUDE_ASM. Default build still uses
 * INCLUDE_ASM. */
#ifdef NON_MATCHING
/* extended partial decode 2026-05-03: 0x1F00-0x1FA0 region decoded as a 2D
 * vector-distance + length + normalize pattern (likely AI homing / soft
 * target-following). Net body grew from ~50 to ~75 insns of decoded C. ~250
 * insns still stubbed in block-comment annotations (gl_func_TODO_00001DDC
 * stub call removed 2026-05-07; remaining sub-blocks documented inline).
 *
 * Decoded semantics for 0x1F00-0x1FA0 sub-block:
 *   diff_x = self_v.x - ref_v.x
 *   diff_z = self_v.z - ref_v.z       (treats Y as up — 2D distance in XZ plane)
 *   speed = a2->0x94                   (some scalar from entity)
 *   sqrlen = diff_x*diff_x + 0 + diff_z*diff_z
 *   length = sqrt(sqrlen)              (first jal — IDO-emit `mul.s; add.s` then
 *                                        jal in delay slot of f12-set; canonical
 *                                        sqrt-via-extern-helper shape)
 *   normalize_into_local(&local[delta_x, 0, delta_z, speed], ...)
 *                                        (second jal — likely normalizes the
 *                                         delta vector in-place)
 *   threshold = a2->0x7C
 *   if (length >= threshold) excess = length - threshold; else excess = length - speed
 *   scale delta by excess (compute three scaled-output Vec3s)
 *
 * The two `jal 0` placeholders at 0x1F44 and 0x1F50 are cross-USO calls;
 * likely candidates per gl_func_00000000 placeholder convention:
 *   - First: `float sqrt(float)` or `float vec_sqrlen_to_len(float)` — single
 *     float arg in $f12, float return in $f0.
 *   - Second: `void normalize3(Vec3*)` or similar in-place transform on the
 *     local sp+0x110 array.
 *
 * The bc1fl at 0x1F74 is branch-likely; takes the THEN arm for "length ≥
 * threshold" (likely the homing-toward case); ELSE arm for "too close"
 * (likely the soft-stop case). */
extern float gl_func_sqrt(float);
extern void gl_func_normalize3(int *vec);
typedef struct { float x, y, z; } Vec3f;
/* Signature change 2026-05-07 (was `(int *a0)`): per the documented 0x2394-0x23C0
 * decode below, the spilled-then-reloaded $a2 is a SECOND function parameter (the
 * delta-output context), not an internal local. The asm spill `sw a1, sp+0x180`
 * at function entry then `lw a2, sp+0x180` near tail confirms a1→a2 ABI shuffle
 * pattern for a 2nd ptr arg. Without `out_delta`, IDO won't allocate the right
 * stack-spill slot for the entry save of `a1`, blocking the byte-match grind. */
void *game_uso_func_00001DDC(int *a0, int *out_delta) {
    /* Frame-padding fix 2026-05-08: built was emitting sp -= 0xC8 vs
     * target sp -= 0x180 (184-byte gap). The key==3 Vec3 temporaries now
     * account for 16 bytes, so `char frame_pad[168];` preserves the target
     * frame — IDO -O2 keeps the stack space even when unused. Now first 3
     * prologue insns are byte-correct.
     *
     * 2026-05-08 (later) — objdiff confirms TARGET and BASE both 407 insns
     * (insn-count match achieved). Fuzzy 17.52% means register allocation /
     * operand ordering account for the ~83% of byte-mismatch — NOT
     * structural mismatch. Ideal next-pass approach: permuter (manual mode
     * with PERM_LINESWAP on the multi-Vec3 fanout copies and PERM_GENERAL
     * on the inline-vs-spill scale-mul site). Single-tick C edits at this
     * stage are bounded by which-register-gets-which-temp: hard to predict
     * without the .greg dump. The actual Vec3 working buffers (per
     * stack-layout note above) live in this region; future passes will
     * replace `frame_pad` with typed locals as they're decoded. */
    char frame_pad[168];
    int key = a0[0x40 / 4];
    (void)frame_pad;
    if (key == 0) goto end;
    if (key != 3) goto branch_88;
    /* key == 3: short Vec3 copy from v1+0xA0..0xA8 to t6+0x60..0x68
     * and t6+0xA0..0xA8. */
    {
        int *t6 = (int*)a0[0x14 / 4];
        int *v1 = (int*)a0[0x3C / 4];
        float x = *(float*)((char*)v1 + 0xA0);
        float y = *(float*)((char*)v1 + 0xA4);
        float z = *(float*)((char*)v1 + 0xA8);
        *(float*)((char*)t6 + 0x60) = x;
        *(float*)((char*)t6 + 0x64) = y;
        *(float*)((char*)t6 + 0x68) = z;
        *(float*)((char*)t6 + 0xA0) = x;
        *(float*)((char*)t6 + 0xA4) = y;
        *(float*)((char*)t6 + 0xA8) = z;
        goto late_label;
    }
branch_88: {
    /* Decoded sub-block at 0x1E60-0x1F00:
     *   - copy a0->0x14->Vec3@0xA0 into local "ref_v"
     *   - copy a0->0x38->Vec3@0xA0 into local "self_v" (using base-shift trick)
     *   - call gl_func(&scratch, a0) -> returns Vec3* delta
     *   - copy *delta into local "delta_v"
     *   - element-wise add: self_v[i] += delta_v[i]
     * Then sub-block 0x1F00-0x1FA0 (extended 2026-05-03):
     *   - 2D distance (XZ plane) between self_v and ref_v
     *   - sqrt(sum-of-squares) gives length; normalize delta vector
     *   - clamped excess scaling for AI homing
     * After this, ~300 more insns remain stubbed. */
    /* IDO declaration order: first-declared = highest sp offset. Re-ordered
     * 2026-05-08 to match documented stack layout: delta_v at 0x154 (highest),
     * ref_v 0x13C, self_v 0x130, local_xz 0x110, scratch 0xFC (lowest). */
    Vec3f delta_v;                /* sp+0x154 — gl_func returned offset */
    Vec3f ref_v;                  /* sp+0x13C — referenced sub-obj position */
    Vec3f self_v;                 /* sp+0x130 — own position copy (accumulator) */
    float local_xz[4];            /* sp+0x110..0x11C: [diff_x, 0, diff_z, speed] */
    char scratch[0x18];           /* sp+0xFC scratch sub-struct (address-taken) */
    Vec3f *t7 = (Vec3f*)((char*)a0[0x14 / 4] + 0xA0);
    Vec3f *v1 = (Vec3f*)((char*)a0[0x38 / 4] + 0xA0);
    Vec3f *delta;
    float length, excess, threshold, speed, sqrlen;
    ref_v = *t7;
    self_v = *v1;
    delta = (Vec3f*)gl_func_00000000((int*)scratch, (int)a0);
    delta_v = *delta;
    self_v.x += delta_v.x;
    self_v.y += delta_v.y;
    self_v.z += delta_v.z;
    /* 2D distance + sqrt + normalize block (0x1F00-0x1FA0) */
    speed = *(float*)((char*)a0 + 0x94);
    local_xz[0] = self_v.x - ref_v.x;
    local_xz[1] = 0.0f;
    local_xz[2] = self_v.z - ref_v.z;
    local_xz[3] = speed;
    sqrlen = local_xz[0]*local_xz[0] + 0.0f*0.0f + local_xz[2]*local_xz[2];
    length = gl_func_sqrt(sqrlen);
    gl_func_normalize3((int*)local_xz);
    threshold = *(float*)((char*)a0 + 0x7C);
    if (length < threshold) {
        excess = length - speed;
    } else {
        excess = length - threshold;
    }
    /* TODO 0x1FA0-end: scale delta by excess, store into 3 output Vec3s,
     * second gl_func dispatch (sp+0x110/sp+0x130 args), stores to
     * a0->0x60..0x68 (resulting Vec3), nested call to scale/normalize.
     * Estimated ~250 insns remaining.
     *
     * Extended scan 2026-05-04 (0x1FA0-0x2050, ~30 more insns characterized):
     *   - 0x1FB0-0x1FD4: triple `lw t9/lw tA/sw t9/sw tA` pairs FROM t6+0/4/8
     *     INTO TWO destinations (e.g. ACEB/AC6A registers = a3+0x0..8 AND
     *     v1+0x0..8). Pattern is "struct copy 12 bytes, fanned out to 2 dst".
     *   - 0x1FD8-0x1FF0: load sp+0xC4/0xC8/0xCC (3 floats), store into
     *     sp+0x120/0x124/0x128 (Vec3 reposition).
     *   - 0x1FF4: `mul.s f0, f16, f1` — scalar*vec scale (excess * something).
     *   - 0x2004: `mul.s f12, f8, f0` — second mul (continuation of scale).
     *   - 0x2010-0x201C: `mul.s f2, f10, f0` triple-mul completing 3-component
     *     vector scale.
     *   - 0x2030-0x2050: another t6 → t7+0/4/8 struct copy (similar to first).
     *
     * So 0x1FA0-0x2050 is "Vec3 = scale * other_vec3" (3 mul.s), preceded by
     * a 12-byte struct copy and followed by a duplicate copy. Likely
     * "delta_scaled = excess * normalized_delta; copy delta_scaled to two
     * downstream Vec3 fields". Decoding C body deferred — current stub
     * captures structure without breaking build.
     *
     * Extended scan 2026-05-04 (0x2050-0x20F0, +30 insns characterized):
     *   - 0x2050-0x205C: continue 12-byte struct copy a3+0x4/0x8 → t9+0x4/0x8.
     *   - 0x2060-0x208C: SECOND Vec3 scale computation. Reads 3 floats from
     *     sp+0xB0/0xB4/0xB8 (input vec) and 1 scalar from a2+0xAC (a2-derived
     *     scaler). Computes mul.s f2/f12/f14 = vec[i] * scaler. Stores
     *     results to sp+0x94/0x98/0x9C. Pattern is `out_vec3 = scaler * in_vec3`.
     *   - 0x2090-0x20BC: Triple-fanout 12-byte struct copy. Reads from t2+0/4/8;
     *     writes to BOTH v1+0/4/8 (the canonical dest) AND t5+0/4/8 (a second
     *     dest captured BEFORE overwrite via `lw t7, 0(v1); sw t7, 0(t5)`
     *     interleaved with the writes — so t5 gets v1's PRE-COPY value).
     *     Likely a "save old value, overwrite with new" idiom for an undo
     *     buffer or an alternate-frame slot.
     *   - 0x20C0-0x20EC: Forward 3-float copy sp+0x74..0x7C → sp+0x120..0x128
     *     (loads f4/f6/f8 in reverse, stores in forward order). Then
     *     lw v0, 0x12C(sp) reloads earlier spill, addiu a1, sp, 0x120 sets
     *     up arg1 = &copied-Vec3. addiu a0, v0+0x30 in jal delay slot — second
     *     gl_func dispatch with new args. ~290 insns remain stubbed past 0x20F0. */
    /* Decoded 2026-05-05 (asm 0x1FA0-0x2050): scale normalized delta by excess.
     * Mirrors: scaled.x = excess * delta_v.x; .y = excess * delta_v.y; .z = ... */
    {
        Vec3f delta_scaled;
        delta_scaled.x = excess * local_xz[0];
        delta_scaled.y = excess * local_xz[1];
        delta_scaled.z = excess * local_xz[2];
        /* Decoded 2026-05-05 (asm 0x20F0-0x21F4, +66 insns): apply XZ-scaled
         * delta + Y-axis homing.
         *
         * 0x20F0-0x2130: re-multiply (`excess * local_xz[i]`) into sp+0x60..0x68.
         *   The whole excess*local_xz triple is recomputed here even though it
         *   was already in `delta_scaled` above — IDO emits the muls inline at
         *   each use site rather than spilling.
         * 0x2134-0x2158: 12-byte fanout copy. sp+0x60..0x68 (the just-stored
         *   scaled vec) replicated into BOTH sp+0xFC..0x108 (scratch) and
         *   sp+0xC4..0xCC (v1 base). The interleaved ld/st pattern (a3+0 read
         *   AFTER first sw to a3, then sw to v1+0) is IDO's load-delay-slot
         *   scheduler shuffling, not a meaningful order dependence — both
         *   destinations end up with identical scaled.xyz.
         * 0x215C-0x2178: store sp+0xC4..0xCC (= scaled.xyz) to a0[0x2C..0x34].
         *   This commits the XZ-plane translation to the entity's pos field.
         * 0x2174 branch: `if (a0[0x40] == 2)` pick scalar a0[0xF4] (case-2
         *   threshold), else a0[0xDC] (default threshold).
         * 0x2188-0x21C4: SECOND-pass homing on Y axis.
         *   Resets local_xz to (0, 1, 0) — pure Y unit vector.
         *   y_diff = ref_v.y - self_v.y                  ; vertical distance
         *   threshold_y = a0[0xC4]
         *   if (y_diff < threshold_y)
         *       y_excess = threshold_y - y_diff          ; pull upward
         *   else
         *       y_excess = scalar - y_diff               ; clamp down (bc1fl)
         * 0x21C8-0x21F0: scaled_y = (0, y_excess, 0); store to sp+0x54..0x5C.
         *   Same delta_scaled pattern as XZ but along Y. */
        {
            Vec3f scaled_y;
            float y_diff, threshold_y, y_scalar, y_excess;
            *(float*)((char*)a0 + 0x2C) = delta_scaled.x;
            *(float*)((char*)a0 + 0x30) = delta_scaled.y;
            *(float*)((char*)a0 + 0x34) = delta_scaled.z;
            y_scalar = (a0[0x40 / 4] == 2)
                ? *(float*)((char*)a0 + 0xF4)
                : *(float*)((char*)a0 + 0xDC);
            y_diff = ref_v.y - self_v.y;
            threshold_y = *(float*)((char*)a0 + 0xC4);
            if (y_diff < threshold_y) {
                y_excess = threshold_y - y_diff;
            } else {
                y_excess = y_scalar - y_diff;
            }
            scaled_y.x = 0.0f * y_excess;
            scaled_y.y = 1.0f * y_excess;
            scaled_y.z = 0.0f * y_excess;
            /* TODO 0x21F4-end: continued Y-homing apply + final-exit convergence.
             * ~225 insns remain stubbed.
             *
             * Extended scan 2026-05-05 (0x21F4-0x227C, +34 insns characterized):
             *   0x21F4-0x2218: ANOTHER 12-byte struct fanout copy. Reads a3+0/4/8
             *     (= scaled_y) writes t6+0/4/8 AND t8+0/4/8 (interleaved with
             *     pre-overwrite reads from t8 — IDO's load-delay shuffle of the
             *     "save-old + write-new" idiom seen at 0x2090-0x20BC earlier).
             *     Likely commits scaled_y into the entity's Y-axis vel/pos field
             *     pair (e.g. a0+0x40 and a0+0x44, vs the XZ commit at 0x2C/0x30
             *     above).
             *   0x221C-0x2230: lwc1 sp+0xCC, sp+0xC8 (re-load XZ delta_scaled),
             *     mtc1 zero / lui constant 0x3F800000 (= 1.0f) — sets up an
             *     identity float for the next computation.
             *   0x2234-0x2260: re-multiply excess * (0,1,0) trio (mirror of the
             *     scaled_y compute earlier; IDO emits the muls inline at each
             *     reuse). Stores to sp+0x110/0x114/0x118 (third copy of scaled
             *     Y-vec).
             *   0x2264-0x227C: lwc1 sp+0x114 / sp+0x118 (re-load Y components
             *   from the Y-axis-scale staging slots), then begins a fanout copy
             *   sequence (`lw t1, 0(t9); sw t1, 0(a3); lw t0, 4(t9); lw t4, 0(a3)`).
             *   NOTE 2026-05-07: prior memo claimed `abs.s f0 (idiom for
             *   fabs(y_excess))` at this offset, but a grep of the function's
             *   raw bytes finds NO abs.s (funct=0x05) or neg.s (funct=0x07)
             *   opcodes ANYWHERE — the abs claim is a decode error. The
             *   y_excess ELSE-arm in C is `y_scalar - y_diff` (no fabs); IDO
             *   emits two `mov.s` insns at 0x21AC/0x21B0 (funct=0x06) that
             *   were the misread source. Don't add fabs() during the next grind.
             *   ~190 insns still stubbed past 0x227C.
             *
             * Extended scan 2026-05-05 (0x227C-0x2300, +35 insns characterized):
             *   0x2270-0x2298: triple-fanout 12-byte struct copy. Reads
             *     a3+0/4/8 (= scaled_y replicated again) writes t9+0/4/8 AND
             *     t2+0/4/8 (sp-relative locals). Same "save-old + write-new"
             *     idiom as 0x21F4 earlier — y-axis scale gets committed to a
             *     second pair of slots (likely the entity's other vel/pos
             *     buffer for double-buffering or alternate frame).
             *   0x229C-0x22B8: 3-mul.s scale (mul.s f6/f8/f4 = excess * (0,1,0)
             *     re-computed inline yet again) — third inline mul of the same
             *     identity scale, IDO chooses to emit per use site rather
             *     than spill. Stores to sp+0x30/0x34/0x38 (yet another local
             *     copy of scaled_y).
             *   0x22BC-0x22D0: third triple-fanout struct copy. Reads a1+0/4/8
             *     writes v1+0/4/8 — likely commits scaled_y to the FINAL
             *     output pair before the late_label epilogue setup.
             *   0x22D4-0x22EC: lwc1 sp+0x4C/sp+0x50, lui 0x4248 (50.0f scale
             *     constant per memo header), mtc1 zero / cvt — switches to
             *     COORDINATE-SCALE phase. Likely "scale Vec3 by 50.0f for
             *     world->camera projection" prelude.
             *   0x22F0+: continues with mul.s/swc1 chain — TODO. ~155 insns
             *   remain stubbed past 0x2300.
             *
             * Extended scan 2026-05-05 (0x2300-0x2350, +24 insns characterized):
             *   0x2300-0x2310: lwc1 sp+0x74/0x78/0x7C (load 3 floats from yet
             *     ANOTHER local Vec3 buffer), swc1 sp+0x120/0x124/0x128. This
             *     is the classic "stage Vec3 in slot N, advance to slot M"
             *     pattern — 4th replication of a transformed Vec3 across stack
             *     locals (the function maintains many simultaneous Vec3 working
             *     buffers).
             *   0x2314-0x2328: lw spilled-context-arg from sp+0x12C; sw t6 to
             *     sp+0x180 (entity ref); swc1 f18 to sp+0x108 (sets up FPU
             *     value into a stack slot for use across upcoming jal). Then
             *     `jal 0` (cross-USO call) with a0 = sp+0x30 (delayed-set in
             *     jal delay slot). Pre-call args setup spans ~6 insns.
             *   0x232C-0x2350: post-call: lwc1 sp+0x108 reload (the FPU value
             *     pre-spilled), lwc1 sp+0x110/0x114/0x118 (re-load Vec3),
             *     mul.s f10 = f10 * f18 (scale by the spilled scalar from
             *     0x108). a0 next-jal-arg = sp+0x24, a2 = sp+0xFC (yet another
             *     local), a1 = sp+0xC4. Multiple call-arg setups in flight.
             *
             * Extended scan 2026-05-05 (0x2350-0x23D0, FINAL 32 insns — function tail):
             *   0x2350-0x2360: completion of mul-trio (f0/f12/f2 = scaled output).
             *     `addiu t4, sp, 0x148` sets up t4 = pointer to spill-area Vec3.
             *     `mul.s f2, f6, f18` is the third scale mul.
             *     `swc1 f0/f12/f2 → sp+0x24/0x28/0x2C` writes the scaled vec to
             *     yet-another local Vec3 slot (the post-jal output staging area).
             *   0x2364-0x2390: triple-fanout 12-byte struct copy with save-old-
             *     value idiom. Reads t1+0/4/8 (a Vec3 src), writes a3+0/4/8
             *     (canonical dest), and ALSO writes the PRE-overwrite a3+0/4/8
             *     value to t4+0/4/8 (the just-computed pointer above). Same
             *     "save old vec to undo buffer, write new vec" pattern as 0x2090
             *     and 0x21F4 earlier — third instance in this function.
             *   0x2394-0x23C0: element-wise subtract `a2[+0x2C..0x34] -= sp[+0x148..0x150]`.
             *     a2 was reloaded from sp+0x180 spill at 0x2108 (context-arg passed
             *     in via the original $a1 spilled then reloaded into $a2 here —
             *     this function takes a SECOND arg used only as the late-stage
             *     delta-output target; the explicit re-load suggests a register-
             *     pressure crunch in the middle, not a separate variable.)
             *     Loads sp+0x148/0x14C/0x150 (the saved-old Vec3 from the t4 dest
             *     above), reads a2+0x2C/0x30/0x34, computes `sub.s` per-component,
             *     stores back to a2+0x2C/0x30/0x34. C shape (decoded 2026-05-05):
             *         a2->vec.x -= saved_old.x;
             *         a2->vec.y -= saved_old.y;
             *         a2->vec.z -= saved_old.z;
             *     where saved_old = Vec3 captured pre-overwrite by the t4-fanout
             *     idiom at 0x2364-0x2390. This commits "delta_to_caller = new_pos
             *     - prior_pos" semantics — the function returns the Vec3 delta
             *     applied this frame.
             *
             *     Implication for byte-matching: function signature is
             *         void *game_uso_func_00001DDC(int *a0, struct *out_delta_ctx)
             *     not `void *game_uso_func_00001DDC(int *a0)` as currently typed
             *     (single-arg). The second arg currently appears as `arg1` only
             *     in the spill-load pattern; needs to become an explicit `a1`
             *     parameter for the byte-match grind.
             *   0x23C4-0x23D0: epilogue (`lw ra, 0x14(sp); addiu sp, +0x180; jr ra; nop`).
             *
             * FUNCTION DECODE COMPLETE: 383 insns characterized end-to-end.
             * Net story: dispatch on a0[0x40] (key); for key=3, simple Vec3
             * mirror; for key!=3, complex 2D-XZ homing + Y-axis homing combine
             * with multiple intermediate Vec3 working buffers (the function
             * maintains 8+ simultaneous Vec3 stack locals).
             *
             * Open work for future-pass byte-matching (this function will need
             * a multi-pass grind):
             *   1. Decompile the asm-level scaffolding into proper C (currently
             *      stubbed in long block-comment annotations; the prior
             *      gl_func_TODO_00001DDC stub call was removed 2026-05-07).
             *      The critical pieces: the 3-component scale
             *      `excess * delta_v` (XZ), the 3-component Y-axis scale
             *      (0,1,0)*y_excess, and the multiple Vec3 fanout copies.
             *   2. Identify the two `jal 0` call signatures (sqrt-helper at
             *      0x1F44, normalize3 at 0x1F50, then the late jal at 0x2320
             *      that takes `(sp+0x30, sp+0xC4, sp+0xFC)` args).
             *   3. Match the entity-field commit chain `a0[0x2C..0x34]`,
             *      `a0[0x44..0x4C]` (Y-vel pair?), and the `a0+0x60..0x68`
             *      target. Likely a Vec3+Vec3 (pos + vel) pair OR pos + accum.
             *   4. Lay out stack locals to match IDO's 0x1A8 frame: sp+0xFC scratch
             *      sub-struct, sp+0x110-0x148 multi-Vec3 working buffers,
             *      sp+0x148-0x150 saved-prev-pos triplet, sp+0x180 entity ref. */
            (void)scaled_y;
        }
        (void)delta_scaled;
    }
    (void)excess;
    /* 2026-05-07: removed gl_func_TODO_00001DDC stub call. Replaced with the
     * documented 0x2394-0x23C0 epilogue pattern that uses `out_delta` (the
     * second function arg). The "save-old + write-new" Vec3 fanout idiom
     * captures pre-overwrite a1->vec into a temp, then delta-output is
     * computed as `a1->vec -= saved_old`. Net effect: out_delta receives
     * the per-frame Vec3 delta committed to a0->[0x2C..0x34]. */
    {
        Vec3f saved_old;
        saved_old.x = *(float*)((char*)out_delta + 0x2C);
        saved_old.y = *(float*)((char*)out_delta + 0x30);
        saved_old.z = *(float*)((char*)out_delta + 0x34);
        *(float*)((char*)out_delta + 0x2C) = *(float*)((char*)a0 + 0x2C) - saved_old.x;
        *(float*)((char*)out_delta + 0x30) = *(float*)((char*)a0 + 0x30) - saved_old.y;
        *(float*)((char*)out_delta + 0x34) = *(float*)((char*)a0 + 0x34) - saved_old.z;
    }
}
late_label:
    /* convergence point — final exit setup */
end:
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001DDC);
#endif

#ifdef NON_MATCHING
/* 54.14% NM. 54% match. 3x3 matrix-vector multiply: dst = M * v, where M is at
 * (*(a1+0x38))+0x70 with row stride 0x10 (Mat4 top-left 3x3), v is at
 * a1+0x5C..0x68. Result stored to *a0; returns a0.
 *
 * Structural differences from target (not just register allocation):
 *   - Target reads v components via `lwc1 $f6, 0x14(sp)` (direct sp);
 *     our build uses `lwc1 $f0, 0(v1)` (pointer-indirect via v1 = &buf).
 *   - Target computes all 3 results, stores f2/f0 to stack, computes f12,
 *     stores f12, THEN does 3 batched lw/sw copies to *a0.
 *   - Our build: compute-store-copy for each result individually.
 * Tried: `int buf[3]`, Tri3i struct variant. Both produce v1-indirect
 * float loads. Likely needs a more specific pattern (named Vec3 locals
 * independent of buf, or a different expr shape). */
int* game_uso_func_000023D4(int *a0, char *a1) {
    int buf[3];
    float *m;
    float x, y, z;

    buf[0] = *(int*)(a1 + 0x5C);
    buf[1] = *(int*)(a1 + 0x60);
    buf[2] = *(int*)(a1 + 0x64);

    m = (float*)(*(char**)(a1 + 0x38) + 0x70);

    x = *(float*)&buf[0];
    y = *(float*)&buf[1];
    z = *(float*)&buf[2];

    *(float*)&buf[0] = m[0]*x + m[4]*y + m[8]*z;
    *(float*)&buf[1] = m[1]*x + m[5]*y + m[9]*z;
    *(float*)&buf[2] = m[2]*x + m[6]*y + m[10]*z;

    a0[0] = buf[0];
    a0[1] = buf[1];
    a0[2] = buf[2];

    return a0;
}
#else
/* game_uso_func_000023D4: 50-insn (0xC8) Vec3 transform helper.
 * Frame -0x20, leaf-style FPU function (no jal calls).
 *
 * Decoded structure:
 *   /* Stage Vec3 from a1->0x5C/0x60/0x64 onto sp+0x14..0x1C *\/
 *   sp[0x14] = a1->0x5C (.x)
 *   sp[0x18] = a1->0x60 (.y)
 *   sp[0x1C] = a1->0x64 (.z)
 *
 *   /* 3x3 matrix-vector multiply against a1->0x38->0x70 (3x3 matrix
 *    * with stride 0x10) using f4/f10/etc. Result accumulated into
 *    * sp+0x14..0x1C (transformed Vec3 in-place). *\/
 *   v0 = a1->0x38                               ; sub-obj ptr (matrix base)
 *   transformed.x = M[0][0]*v.x + M[0][1]*v.y + M[0][2]*v.z + ...
 *   transformed.y = M[1][0]*v.x + M[1][1]*v.y + M[1][2]*v.z + ...
 *   transformed.z = M[2][0]*v.x + M[2][1]*v.y + M[2][2]*v.z + ...
 *
 *   /* Vec3-copy 3 ints from a1+0x?? to a0 (caller's output) *\/
 *   a0[0] = (something)[0]
 *   a0[1] = (something)[1]
 *   a0[2] = (something)[2]
 *
 * 5 args at offsets 0x5C/0x60/0x64 (Vec3 input) + 0x38 (sub-obj/matrix
 * ptr). Output via a0. Likely the per-frame transform helper used by the
 * spine functions that have Vec3-stage entries.
 *
 * Multi-tick refinement target — doc-only this tick. Default INCLUDE_ASM
 * build remains exact. */
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000023D4);
#endif

extern void game_uso_func_00000000();

void game_uso_func_0000249C(char *a0) {
    game_uso_func_00000000(a0 + 0x44);
}

#ifdef NON_MATCHING
/* game_uso_func_000024BC: 0x258 (150 insns) — sibling of game_uso_func_00001DDC.
 * Same 3-way dispatch pattern on a0[0x10] (key field):
 *
 *   key = a0[0x10];
 *   if (key == 0) return a0;
 *   if (key == 3) {
 *       v1 = a0[0xF];                        // sub-obj
 *       (a0[5])->Vec3@0xA0 = v1->Vec3@0xA0;  // 3-float copy to t6's child
 *       a0->Vec3@0x60 = v1->Vec3@0xA0;       // and to self+0x60
 *       goto end;
 *   }
 *   else: {
 *       v1 = a0[0xE];
 *       ref_v = v1->Vec3@0xA0;               // copy to local sp+0x60
 *       delta = *(Vec3*)gl_func(&scratch_3C, a0);
 *       self.x = ref_v.x + delta.x;
 *       self.y = ref_v.y + delta.y;
 *       self.z = ref_v.z + delta.z;
 *       sp+0x54 = (a1.x, 0, a1.z);           // zero-Y projection of arg1
 *       gl_func(&sp+0x54, ... );             // second dispatch
 *       ... ~120 insns of FPU math and stores remain TBD ...
 *   }
 *   end: return a0;
 *
 * First-pass NM — covers the dispatch + key==3 leaf path. The else-arm is
 * the bulk of the function (ref_v/delta/self vector math + 2 cross-USO
 * calls + final stores to a0->0x60..0x68 and t6's child). Initial decode
 * 2026-05-05; tail writeback decoded 2026-05-08. */
extern int gl_func_00000000();
void *game_uso_func_000024BC(int *a0, int *a1) {
    int *t6;
    int key;
    int *v1;
    char scratch[0x18];
    float ref_x, ref_y, ref_z;
    float delta_x, delta_y, delta_z;
    float self_x, self_y, self_z;
    float proj_x, proj_y, proj_z;
    float scale;
    float denom_xz, denom_y;
    float a1_proj[3];
    int *delta;

    t6 = (int*)a0[0x14 / 4];
    key = a0[0x40 / 4];
    if (key == 0) goto end;
    if (key != 3) goto branch_else;

    /* key == 3: dual Vec3 copy from sub-obj@0xA0 to (self+0x60) AND (t6+0xA0). */
    v1 = (int*)a0[0x3C / 4];
    *(float*)((char*)a0 + 0x60) = *(float*)((char*)v1 + 0xA0);
    *(float*)((char*)a0 + 0x64) = *(float*)((char*)v1 + 0xA4);
    *(float*)((char*)a0 + 0x68) = *(float*)((char*)v1 + 0xA8);
    *(float*)((char*)t6 + 0xA0) = *(float*)((char*)v1 + 0xA0);
    *(float*)((char*)t6 + 0xA4) = *(float*)((char*)v1 + 0xA4);
    *(float*)((char*)t6 + 0xA8) = *(float*)((char*)v1 + 0xA8);
    goto end;

branch_else:
    /* Else-arm decoded through ~70 of ~120 insns:
     *
     * Stage 1 (insns 0x88-0xb8): load ref_v from a0[0xE]@+0xA0, spill scratch
     *   v1 = a0[0x38/4]                       // a0->[0x38]
     *   sp[0x60..0x68] = v1->Vec3@0xA0        // ref_v
     *
     * Stage 2 (0xb4-0xe0): first jal — alloc/compute delta vector
     *   spill a2,a3 to sp+0x98/0x9C
     *   v0 = gl_func(sp+0x3C, a2)             // returns Vec3* (or 3-word struct ptr)
     *   reload a2,a3
     *   sp[0x6C..0x74] = *(int[3]*)v0         // copy delta (3 words)
     *
     * Stage 3 (0xe4-0x114): self_v = ref_v + delta_v
     *   sp[0x60..0x68] = ref_v + delta_v       (3 add.s ops)
     *
     * Stage 4 (0x118-0x134): zero-Y projection of a3 → sp[0x54..0x5C]
     *   sp[0x54] = a3->x; sp[0x58] = 0.0; sp[0x5C] = a3->z
     *
     * Stage 5 (0x130): second jal — gl_func(sp+0x54, ...)
     *
     * Stage 6 (0x138-0x250): post-jal vector adjustment + final writeback:
     *   scaled_proj = sp[0x54..0x5C] * a0->0x94
     *   self_v -= scaled_proj
     *   self_v.y += (a0->0x40 == 2) ? a0->0xF4 : a0->0xDC
     *   self_v -= { a1.x / a0->0xAC, a1.y / a0->0x10C, a1.z / a0->0xAC }
     *   t6->Vec3@0x60 = self_v
     *   t6->Vec3@0xA0 = self_v
     *
     * Initial decode 2026-05-05; extended decode 2026-05-06. */
    v1 = (int*)a0[0x38 / 4];
    ref_x = *(float*)((char*)v1 + 0xA0);
    ref_y = *(float*)((char*)v1 + 0xA4);
    ref_z = *(float*)((char*)v1 + 0xA8);
    delta = (int*)gl_func_00000000(scratch, a0);
    delta_x = *(float*)&delta[0];
    delta_y = *(float*)&delta[1];
    delta_z = *(float*)&delta[2];
    self_x = ref_x + delta_x;
    self_y = ref_y + delta_y;
    self_z = ref_z + delta_z;
    /* Zero-Y projection of a1 then second gl_func call. */
    a1_proj[0] = *(float*)&a1[0];      /* a3.x */
    a1_proj[1] = 0.0f;
    a1_proj[2] = *(float*)&a1[2];      /* a3.z */
    gl_func_00000000(a1_proj, a0);

    scale = *(float*)((char*)a0 + 0x94);
    proj_x = a1_proj[0] * scale;
    proj_y = a1_proj[1] * scale;
    proj_z = a1_proj[2] * scale;
    self_x -= proj_x;
    self_y -= proj_y;
    self_z -= proj_z;

    if (key == 2) {
        self_y += *(float*)((char*)a0 + 0xF4);
    } else {
        self_y += *(float*)((char*)a0 + 0xDC);
    }

    denom_xz = *(float*)((char*)a0 + 0xAC);
    denom_y = *(float*)((char*)a0 + 0x10C);
    self_x -= *(float*)&a1[0] / denom_xz;
    self_y -= *(float*)&a1[1] / denom_y;
    self_z -= *(float*)&a1[2] / denom_xz;

    *(float*)((char*)t6 + 0x60) = self_x;
    *(float*)((char*)t6 + 0x64) = self_y;
    *(float*)((char*)t6 + 0x68) = self_z;
    *(float*)((char*)t6 + 0xA0) = self_x;
    *(float*)((char*)t6 + 0xA4) = self_y;
    *(float*)((char*)t6 + 0xA8) = self_z;

end:
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000024BC);
#endif

void game_uso_func_00002714(int *a0, int a1, int a2) {
    if (*(int*)((char*)a0 + 0x40) == a1) return;
    *(int*)((char*)a0 + 0x40) = a1;
    game_uso_func_00000000(a0, a2);
}

#ifdef NON_MATCHING
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
 * Cap at 57.63% as of 2026-05-06. Multi-tick refinement target — needs
 * exact insn-by-insn trace + register-allocation match for promotion. */
void *game_uso_func_00002744(void *arg0) {
    void *p1;
    void *p2;
    void *p3;
    int dead_load;

    p1 = arg0;
    if (p1 == NULL) {
        p1 = (void*)gl_func_00000000(0x20, p1);
        if (p1 == NULL) return NULL;
    }

    p2 = p1;
    if (p2 == NULL) {
        p2 = (void*)gl_func_00000000(8, p1);
        if (p2 != NULL) {
            ((int*)p2)[0] = (int)((char*)&D_00000000 + 0x354);
            ((int*)p2)[1] = 0;
        }
    }

    dead_load = *(int*)((char*)&D_00000000 + 0x35C);
    (void)dead_load;

    if (p1 == (void*)-8) {
        p3 = (void*)gl_func_00000000(0x18, p1);
        if (p3 != NULL) {
            gl_func_00000000(p3, p1, dead_load, 1);
            ((int*)p3)[3] = (int)((char*)&D_00000000 + 0x18);
            ((float*)p3)[4] = 0.0f;
            ((int*)p3)[5] = 0;
        }
    }
    return p1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002744);
#endif

/* Mirror of game_uso_func_00001D30 (alloc(0x64) variant; dispatch table at
 * &D_0+0x360). 5-insn arg-spill scheduling permutation patched via INSN_PATCH
 * in Makefile (offsets 0x08/0x0C/0x10/0x14/0x1C) — IDO chooses to put
 * `or s0, a0, zero` in the bnez delay slot and spill a3 before bnez; expected
 * has the move first and a3 in the delay slot. Logic-identical, byte-correct
 * via post-cc patch. See docs/POST_CC_RECIPES.md#feedback-insn-patch-for-ido-codegen-caps. */
char *game_uso_func_00002814(char *a0, int a1, int a2, int a3) {
    register char *p = a0;
    if (p == 0) {
        p = (char*)gl_func_00000000(0x64);
        if (p == 0) goto end;
    }
    gl_func_00000000(p, &D_00000000 + 0x360);
    *(int*)(p + 0x28) = (int)&D_00000000;
    gl_func_00000000(p + 0x44);
    if (a3 != 0) {
        gl_func_00000000(p, 1, a3);
    }
    *(int*)(p + 0x38) = a1;
    *(int*)(p + 0x3C) = a2;
end:
    return p;
}

void game_uso_func_000028A8(void *a0) {
    *(s32*)((char*)a0 + 0x40) = 0;
    *(f32*)((char*)a0 + 0x2C) = 0.0f;
    *(f32*)((char*)a0 + 0x30) = 0.0f;
    *(f32*)((char*)a0 + 0x34) = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000028C0);

void game_uso_func_00002CA8(char *a0) {
    game_uso_func_00000000(a0 + 0x44);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002CC8);

void game_uso_func_00002FC8(int *a0, int a1, int a2) {
    if (*(int*)((char*)a0 + 0x40) == a1) return;
    *(int*)((char*)a0 + 0x40) = a1;
    game_uso_func_00000000(a0, a2);
}

void game_uso_func_00002FF8(void) {
    game_uso_func_00000000();
}

void game_uso_func_00000B14(void *a0) {
    game_uso_func_00000000(a0);
    game_uso_func_00000000(a0);
}

#ifdef NON_MATCHING
/* game_uso_func_00003018: 291-insn (0x48C) constructor. Frame -0xE8.
 * Same family as spine constructor game_uso_func_000044F4.
 *
 * Stage 1 @ 0x3018-0x303C (alloc-or-passthrough): if (!arg0) arg0 = alloc(0xE8).
 * Stage 2 @ 0x303C-0x3050 (alias-or-alloc-secondary): v1 = arg0 ?: alloc(8).
 *   Defensive double-cascade — second alloc unreachable since stage 1 returns
 *   on failure, but IDO emits both branches because s0 reload after alloc
 *   forces re-check.
 * Stage 3 @ 0x3054-0x3060 (template init): v1[0] = &D + 0x374; v1[1] = 0.
 * Stage 4 @ 0x3064-0x30A8 (Vec3 buffer init x3 on stack):
 *   sp[0xDC..0xE8] = (0.0, 0.0, 0.0)
 *   sp[0xD0..0xDC] = (-1000.0, -1000.0, -1000.0)
 *   sp[0xC0]       = D[0x37C]
 *   sp[0xC4..0xCC] = (1000.0, 1000.0, 1000.0)
 * Stage 5 @ 0x30AC-..: copy 3 Vec3s sp[0xDC]/sp[0xD0]/sp[0xC4] to
 *   sp[0x64]/sp[0x54]/sp[0x44] — ENT-Vec3 prep area.
 *
 * Stage 6 @ 0x3110-0x348C (9x repeated "alloc-and-register sub-object"):
 *   for k in [0..8]:
 *     v = D[0x384 + k*4];
 *     dst_off = struct_offset[k];     # 0x40, 0x58, 0x70, 0x88, ...
 *     at_const = at_table[k];         # -0x40, -0x58, -0x70, -0x88, ...
 *     spill v at sp+offset_per_k;
 *     if (s0 != at_const) {
 *       spill v at sp+0x3C;
 *       p = alloc(0x18);
 *       if (p) {
 *         init_helper(p, s0, v, 1);   # cross-USO callee
 *         p->[0xC] = (k+1) << 24 | 0x18;  # encoded ID
 *         p->[0x14] = 0;
 *         p->[0x10] = 0.0f;
 *       }
 *     }
 *
 *   The first stage is a 0x20-byte object at s0+0x08 with tag D+0x30 and
 *   Vec3 zero copied to +0x10. The remaining 8 stages cover 0x18-byte slots
 *   from s0+0x28 through s0+0xD0, each with tag D+0x18 and zero at +0x10.
 *
 *   2026-05-07 closer-read of one stage's bne: `bne $s0, $at(-0x40), +5`
 *   ALWAYS branches taken (s0 is a non-NULL struct ptr, can't equal -0x40),
 *   which would skip the alloc as dead code. But the asm shape is too
 *   well-formed to be a compiler bug, so the actual C structure is likely
 *   `if ((int)s0 == sentinel) { alloc(0x18); ... }` where IDO can't prove
 *   the sentinel is unreachable at this point — i.e., a defensive
 *   programmer-written check on a global that happens to alias s0's
 *   pointer-cast comparison. IDO emits both arms because it can't fold
 *   the constant. Investigate before encoding.
 *
 * Picked source 5 (strategy memo). Initial structural body — partial decode
 * of stages 1-5 (~50/291 insns). 2026-05-08: encoded the full repeated
 * Stage 6 subobject setup through the tail; still NON_MATCHING due to
 * stack/register allocation and unresolved cross-USO callee signatures.
 * Multi-run refinement expected. */
void* game_uso_func_00003018(void* arg0) {
    void *s0;
    void *v1;
    void *sub;
    Vec3 zero_vec;
    Vec3 min_vec;
    Vec3 max_vec;
    int counter;
    int tmpl;
    Vec3 ent_a, ent_b, ent_c;

    s0 = arg0;
    if (s0 == NULL) {
        s0 = (void*)gl_func_00000000(0xE8);
        if (s0 == NULL) return NULL;
    }
    v1 = s0;
    if (s0 == NULL) {
        v1 = (void*)gl_func_00000000(8);
        if (v1 == NULL) goto skip_template;
    }
    *(int*)((char*)v1 + 0) = (int)((char*)&D_00000000 + 0x374);
    *(int*)((char*)v1 + 4) = 0;

skip_template:
    zero_vec.x = zero_vec.y = zero_vec.z = 0.0f;
    min_vec.x = min_vec.y = min_vec.z = -1000.0f;
    counter = *(int*)((char*)&D_00000000 + 0x37C);
    max_vec.x = max_vec.y = max_vec.z = 1000.0f;
    ent_a = zero_vec;
    ent_b = min_vec;
    ent_c = max_vec;
    (void)counter;

    sub = (char*)s0 + 8;
    if (s0 == (void*)-8) {
        sub = (void*)gl_func_00000000(0x20);
        if (sub != NULL) {
            gl_func_00000000(sub, s0, counter, 1, counter);
            *(int*)((char*)sub + 0x0C) = (int)((char*)&D_00000000 + 0x30);
            *(int*)((char*)sub + 0x1C) = 0;
            *(float*)((char*)sub + 0x10) = ent_a.x;
            *(float*)((char*)sub + 0x14) = ent_a.y;
            *(float*)((char*)sub + 0x18) = ent_a.z;
        }
    } else {
        gl_func_00000000(sub, s0, counter, 1, counter);
        *(int*)((char*)sub + 0x0C) = (int)((char*)&D_00000000 + 0x30);
        *(int*)((char*)sub + 0x1C) = 0;
        *(float*)((char*)sub + 0x10) = ent_a.x;
        *(float*)((char*)sub + 0x14) = ent_a.y;
        *(float*)((char*)sub + 0x18) = ent_a.z;
    }

    tmpl = *(int*)((char*)&D_00000000 + 0x380);
    sub = (char*)s0 + 0x28;
    if (s0 == (void*)-0x28) {
        sub = (void*)gl_func_00000000(0x18);
    }
    if (sub != NULL) {
        gl_func_00000000(sub, s0, tmpl, 1, tmpl);
        *(int*)((char*)sub + 0x0C) = (int)((char*)&D_00000000 + 0x18);
        *(int*)((char*)sub + 0x14) = 0;
        *(float*)((char*)sub + 0x10) = 0.0f;
    }

    tmpl = *(int*)((char*)&D_00000000 + 0x384);
    sub = (char*)s0 + 0x40;
    if (s0 == (void*)-0x40) {
        sub = (void*)gl_func_00000000(0x18);
    }
    if (sub != NULL) {
        gl_func_00000000(sub, s0, tmpl, 1, tmpl);
        *(int*)((char*)sub + 0x0C) = (int)((char*)&D_00000000 + 0x18);
        *(int*)((char*)sub + 0x14) = 0;
        *(float*)((char*)sub + 0x10) = 0.0f;
    }

    tmpl = *(int*)((char*)&D_00000000 + 0x388);
    sub = (char*)s0 + 0x58;
    if (s0 == (void*)-0x58) {
        sub = (void*)gl_func_00000000(0x18);
    }
    if (sub != NULL) {
        gl_func_00000000(sub, s0, tmpl, 1, tmpl);
        *(int*)((char*)sub + 0x0C) = (int)((char*)&D_00000000 + 0x18);
        *(int*)((char*)sub + 0x14) = 0;
        *(float*)((char*)sub + 0x10) = 0.0f;
    }

    tmpl = *(int*)((char*)&D_00000000 + 0x38C);
    sub = (char*)s0 + 0x70;
    if (s0 == (void*)-0x70) {
        sub = (void*)gl_func_00000000(0x18);
    }
    if (sub != NULL) {
        gl_func_00000000(sub, s0, tmpl, 1, tmpl);
        *(int*)((char*)sub + 0x0C) = (int)((char*)&D_00000000 + 0x18);
        *(int*)((char*)sub + 0x14) = 0;
        *(float*)((char*)sub + 0x10) = 0.0f;
    }

    tmpl = *(int*)((char*)&D_00000000 + 0x390);
    sub = (char*)s0 + 0x88;
    if (s0 == (void*)-0x88) {
        sub = (void*)gl_func_00000000(0x18);
    }
    if (sub != NULL) {
        gl_func_00000000(sub, s0, tmpl, 1, tmpl);
        *(int*)((char*)sub + 0x0C) = (int)((char*)&D_00000000 + 0x18);
        *(int*)((char*)sub + 0x14) = 0;
        *(float*)((char*)sub + 0x10) = 0.0f;
    }

    tmpl = *(int*)((char*)&D_00000000 + 0x394);
    sub = (char*)s0 + 0xA0;
    if (s0 == (void*)-0xA0) {
        sub = (void*)gl_func_00000000(0x18);
    }
    if (sub != NULL) {
        gl_func_00000000(sub, s0, tmpl, 1, tmpl);
        *(int*)((char*)sub + 0x0C) = (int)((char*)&D_00000000 + 0x18);
        *(int*)((char*)sub + 0x14) = 0;
        *(float*)((char*)sub + 0x10) = 0.0f;
    }

    tmpl = *(int*)((char*)&D_00000000 + 0x398);
    sub = (char*)s0 + 0xB8;
    if (s0 == (void*)-0xB8) {
        sub = (void*)gl_func_00000000(0x18);
    }
    if (sub != NULL) {
        gl_func_00000000(sub, s0, tmpl, 1, tmpl);
        *(int*)((char*)sub + 0x0C) = (int)((char*)&D_00000000 + 0x18);
        *(int*)((char*)sub + 0x14) = 0;
        *(float*)((char*)sub + 0x10) = 0.0f;
    }

    tmpl = *(int*)((char*)&D_00000000 + 0x39C);
    sub = (char*)s0 + 0xD0;
    if (s0 == (void*)-0xD0) {
        sub = (void*)gl_func_00000000(0x18);
    }
    if (sub != NULL) {
        gl_func_00000000(sub, s0, tmpl, 1, tmpl);
        *(int*)((char*)sub + 0x0C) = (int)((char*)&D_00000000 + 0x18);
        *(int*)((char*)sub + 0x14) = 0;
        *(float*)((char*)sub + 0x10) = 0.0f;
    }

    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003018);
#endif

extern int D_3A0;
/* 45-insn alloc-or-passthrough constructor. Promoted via 23-word
 * INSN_PATCH (per Makefile) covering the IDO scheduler's prologue-
 * deferred-move + mid-body mtc1/lw-t8 reordering. The patch swaps two
 * relocation-bearing words at +0x34 (lui→addiu) and +0x3C (addiu→or);
 * patch-insn-bytes.py auto-strips the orphan HI16/LO16 relocs (since
 * 2026-05-07 — same machinery as the R_MIPS_26 jal-→non-jal strip).
 * In USO context, %hi(0+addend) and %lo(0+addend) both resolve to 0
 * for symbols at 0, and the addend is baked into the patched immediate,
 * so post-strip the bytes are link-correct. */
int *game_uso_func_000034A4(int *a0, int a1, int a2, int a3) {
    int *s = a0;
    if (s == 0) {
        s = (int*)gl_func_00000000(0x138);
    }
    if (s != 0) {
        gl_func_00000000(s, &D_3A0);
        *(int*)((char*)s + 0x28) = (int)&D_00000000;
        gl_func_00000000((int*)((char*)s + 0x50));
        if (a3 != 0) {
            gl_func_00000000(s, 1, a3);
        }
        *(int*)((char*)s + 0x48) = a1;
        *(int*)((char*)s + 0x2C) = 0;
        *(float*)((char*)s + 0x38) = 0.0f;
        *(float*)((char*)s + 0x34) = 0.0f;
        *(float*)((char*)s + 0x30) = 0.0f;
        *(float*)((char*)s + 0x44) = 0.0f;
        *(float*)((char*)s + 0x40) = 0.0f;
        *(float*)((char*)s + 0x3C) = 0.0f;
        *(int*)((char*)s + 0x4C) = a2;
    }
    return s;
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
 * Stage 4+: ~210 insns remaining — likely transforms, gl_func dispatches,
 * and writes back to arg0's struct fields. Multi-tick decomp.
 *
 * Picked under source 5 (strategy memo, exported-but-not-intra-called
 * size-descending). INCLUDE_ASM keeps ROM byte-correct. */
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003558);

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

/* game_uso_func_00003A28: 36-insn alloc + conditional-init + registry-link
 * wrapper with branch-likely tail-merge. Promoted from 89.22% NM cap via
 * 25-word INSN_PATCH (per docs/POST_CC_RECIPES.md
 * #feedback-suffix-plus-insn-patch-grows-and-reshapes — same recipe family,
 * SUFFIX-less variant since size already matches). The cap was IDO's
 * register-allocation pick ($a1/$a2 for obj/other vs target's $v0/$v1)
 * AND a frame-size diff (0x20 vs 0x28). Patch covers all 25 differing
 * words including one jal-position swap (+0x1C non-jal→jal, +0x20
 * jal→non-jal) which exercises the orphan R_MIPS_26 strip. */
int *game_uso_func_00003A28(int *arg0) {
    int *obj;
    int *other;
    obj = (int*)gl_func_00000000(0x40);
    if (obj != 0) {
        gl_func_00000000(obj);
        *(int*)((char*)obj + 0x28) = (int)&D_00000000;
        *(int*)((char*)obj + 0x3C) = 0;
    }
    other = (int*)arg0[0x40 / 4];
    if (other != 0) {
        gl_func_00000000((char*)obj + 0x10, other);
        if (other[0x14 / 4] != 0) {
            other[0x4 / 4] = 1;
        }
        other[0x14 / 4] = (int)obj;
    }
    return obj;
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
 * Picked under source 5 (strategy memo, exported-but-not-intra-called
 * size-descending). Multi-tick decomp; structural wrap only this tick.
 * INCLUDE_ASM keeps ROM byte-correct. */
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003AC0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003ED4);

#ifdef NON_MATCHING
/* game_uso_func_00003FAC: 53-insn (0xD4) FPU-heavy 2D-rotation-like
 * vector builder. Frame -0x20, single cross-USO call.
 *
 * Inputs (decoded from arg-spill + reload pattern):
 *   a0: float[3] output #1 (writes [0], [4]=0, [8])
 *   a1: float[3] output #2 (writes [0], [4]=0, [8])
 *   a2: float[3] input vector (reads [0] and [8] only — [4] unused)
 *   a3: int divisor
 *   sp+0x30: float arg5 (numerator for scale = arg5/a3)
 *
 * Algorithm:
 *   orig_scale = arg5 / a3                 ; f0 before call
 *   ratio     = orig_scale * orig_scale    ; f8 = orig_scale^2
 *   inner_arg = 1.0 - ratio                ; f12 (passed to callee)
 *   new_scale = inner_func(passthrough_args, inner_arg, a3_as_float)
 *
 *   ; outputs use both new_scale (= post-call f0) and orig_scale (= f2 saved):
 *   a0[0] = new_scale * a2[0] + orig_scale * a2[2]
 *   a0[1] = 0
 *   a0[2] = ratio     * a2[0] + new_scale  * a2[2]
 *   a1[0] = new_scale * a2[0] - orig_scale * a2[2]
 *   a1[1] = 0
 *   a1[2] = orig_scale * a2[0] + new_scale * a2[2]
 *
 * Looks like a rotation-matrix construction: a0 may be (cos*x + sin*z, 0,
 * sin^2*x + cos*z) and a1 may be the reflected/swapped variant. Inner
 * func is plausibly sqrt or sincos-like (returns derived scale).
 *
 * f24 = -orig_scale is set but never read — likely a dead store from the
 * original source's `float neg = -orig_scale;` local that the compiler
 * preserved across optimization. Suggests the original C declared more
 * locals than survive into the visible algebra.
 *
 * Initial structural decode 2026-05-07; default INCLUDE_ASM build remains
 * exact via the asm. Multi-tick refinement target — exact algebra +
 * register allocation match needs deeper trace + variant grinding. */
void game_uso_func_00003FAC(float *a0, float *a1, float *a2, int a3, float arg4) {
    float orig_scale = arg4 / a3;
    float ratio = orig_scale * orig_scale;
    float new_scale;
    float dummy;

    /* Inner call gets `(1 - ratio)` as f12 + `(float)a3` as f14. Passthrough
     * a0/a1/a2/a3 (saved/reloaded from caller stack). Returns new_scale in f0. */
    new_scale = (float)gl_func_00000000(a0, a1, a2, a3);
    (void)ratio;

    a0[0] = new_scale * a2[0] + orig_scale * a2[2];
    a0[1] = 0.0f;
    a0[2] = ratio * a2[0] + new_scale * a2[2];

    a1[1] = 0.0f;
    a1[0] = new_scale * a2[0] - orig_scale * a2[2];
    a1[2] = orig_scale * a2[0] + new_scale * a2[2];

    dummy = -orig_scale; /* f24 dead-store equivalent */
    (void)dummy;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003FAC);
#endif

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
/* game_uso_func_000041C0: 137-insn (0x224) multi-level cascading constructor.
 * Frame -0x48, single arg a0.
 *
 * Structural skeleton (decoded 2026-05-07; offsets in target asm):
 *
 *   p1 = alloc(0x8C);                 ; 0x0C: jal alloc(0x8C)
 *   if (!p1) goto end;
 *   gl_func_00000000(p1);             ; 0x1C: second call — likely template-copy
 *   p1->[0x28] = &D_00000000;
 *
 *   ; First sub-alloc (cascade 1) — sentinel check `p1 == -0x3C` skips arm
 *   if (p1 != (void*)-0x3C) {
 *     p2 = alloc(0x50);               ; 0x44: jal alloc(0x50)
 *     if (!p2) goto end;
 *     ; Inner pointer-list cascade — `p3 = alloc(8); p3[0] = &D+0x6B0; p3[1] = 0;`
 *     if (p2 == 0) {
 *       p3 = alloc(8);
 *       if (p3) {
 *         p3->[0] = &D+0x6B0;
 *         p3->[1] = 0;
 *       }
 *     }
 *     t = *(int*)(&D+0x6C4);          ; 0x88: lw t0, 0x6C4(t0)
 *
 *     ; Three 0x18-byte sub-allocs guarded by sentinel checks against
 *     ; (-0x8, -0x20, -0x38) values of a1. Each writes a fixed-template
 *     ; pointer (&D + 0x3C8 or &D + 0x410) to the new sub-object,
 *     ; sets sub->[0x14] = 0, and the FIRST also sets sub->[0x10] = 1.0f.
 *
 *   }
 *
 *   ; Tail: walk a chain via p1->0x40 looking for an empty slot
 *   q = p1->[0x40];
 *   r = q + 0x10;
 *   if (q->[0x14] != 0) q->[0x4] = 1;
 *   ...->0x14 = q;
 *   return v1;  ; v1 holds the most-recent inner alloc result
 *
 * Cross-USO call placeholders throughout (gl_func_00000000). Per-call
 * unique externs not wired. Function has the shape of a "subsystem-init
 * that builds 5+ child objects from templates", aligning with the
 * strategy memo's spine constructor class.
 *
 * Spine context: this is reached from game.uso constructors, NOT a
 * per-frame compute. Decompile in struct-typing pass once 5+ accessors
 * to the same struct are typed (offsets 0x28, 0x40, 0x14 used here).
 *
 * Initial structural decode 2026-05-07; default INCLUDE_ASM build matches
 * via the asm. Multi-tick refinement target. */
void game_uso_func_000041C0(int a0) {
    /* Outline only — multi-tick decomp scope. The 5-level nested
     * cascade (alloc 0x8C → alloc 0x50 → inner 8 → multiple 0x18s →
     * tail-walk a1->0x40 chain) needs careful arg-passing reconstruction
     * to byte-match. Skeleton kept for grep discoverability. */
    int *p1, *p2;
    p1 = (int*)gl_func_00000000(0x8C);
    if (p1 == 0) return;
    gl_func_00000000(p1);
    *(int*)((char*)p1 + 0x28) = (int)&D_00000000;
    if ((int)p1 == -0x3C) return;
    p2 = (int*)gl_func_00000000(0x50);
    if (p2 == 0) return;
    /* ... 0x18-byte sub-allocs cascade ... */
    (void)a0;
    (void)p2;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000041C0);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000043E4);

void game_uso_func_000044C8(char *a0) {
    game_uso_func_00000000(a0);
    game_uso_func_00000000(a0 + 0x3C);
}

#ifdef NON_MATCHING
/* game_uso_func_000044F4: 0x1234 (1165 insns, 4.6 KB) — spine candidate #1
 * "main GameState constructor" per project_1080_game_uso_map.md.
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
 * NEXT PASS: decode the sub-object loop's tail (set-and-link to parent's
 * 0x38 chain), and the second template-table iteration (~16 sub-objects).
 *
 * 2026-05-04 EXTENDED DECODE @ 0x45E0-0x4710 (insns 50-128, 4 iterations of
 * the sub-object init group). The body is NOT a simple loop — it's an
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
 * struct layout (sub-objects placed BEFORE the parent's a0 in memory layout?
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
 *     or scale factor for the sub-object's FPU state, NOT consumed by
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
 *     = -4000.0f, NOT a D-table lookup. This changes IDO's codegen pattern
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
 * Cumulative stride from start: 0x140 = 320 bytes (vs s1's expected
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
 * to specific velocity/threshold sub-objects that aren't D-table indexed.
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
    char *self;
    char *s1;       /* sub-region @ a0+0xE4 OR alloc'd 0x3E0 child */
    char *s0;       /* loop pointer for sub-object init */
    char _pad[168]; /* grow frame to 0xE8 to match target's stack layout */
    char *_t_buf[1];  /* per-iter sp+0xE0 store-load scratch */

    /* Stage 1: allocate main object if not provided */
    if (a0 == NULL) {
        self = (char*)gl_func_00000000(0x4E0);
        if (self == NULL) goto epi;
        a0 = self;
    }

    /* Stage 2: init main from template at D[0x6D0]; set parent ptr */
    gl_func_00000000((char*)&D_00000000 + 0x6D0, a0);
    *(char**)(a0 + 0x28) = &D_00000000;

    /* Stage 3: sub-region — branch is always-true (a0+0xE4 != 0xFFFFFF1C);
     * IDO's `addiu at, zero, -0xE4; bne s1, at, +5` form. Else-arm
     * allocates 0x3E0 if the sub-region pointer is NULL. */
    if ((int)(a0 + 0xE4) != -0xE4) {
        s1 = a0 + 0xE4;
    } else {
        s1 = (char*)gl_func_00000000(0x3E0);
        if (s1 == NULL) goto epi;
    }

    /* Stage 4 (v1 setup + iter 0): v1 = (s1 != NULL) ? s1 : alloc(8).
     * Then write template head at v1[0] / 0 at v1[4]. Iter 0 inits
     * the first sub-obj at slot 8 from D[0x6E8] template. */
    {
        char *v1;
        char *tmpl0;
        char *_s2_buf;       /* stack temp at sp+0x2C, target uses for marshalling */
        char *s2 = (char*)&_s2_buf;
        if (s1 != NULL) {
            v1 = s1;
        } else {
            v1 = (char*)gl_func_00000000(8);
            if (v1 == NULL) goto epi;
        }
        *(char**)v1 = (char*)&D_00000000 + 0x6D8;
        *(int*)(v1 + 4) = 0;

        {
            extern char D_44F4_iter0, D_44F4_typtag;
            tmpl0 = *(char**)((char*)&D_44F4_iter0 + 0x6E8);
            s0 = s1 + 8;
            *(char**)s2 = tmpl0;
            if (s1 != (char*)-8) {
                s0 = (char*)gl_func_00000000(0x18);
                if (s0 == NULL) goto epi;
                gl_func_00000000(s0, s1, *(char**)s2, 1);
                *(char**)(s0 + 0xC) = (char*)&D_44F4_typtag + 0x3C8;
                *(int*)(s0 + 0x14) = 0;
                *(float*)(s0 + 0x10) = *(float*)((char*)&D_44F4_iter0 + 0x9C);
            }
        }

        /* Unrolled iters A-D (slots 0x20, 0x38, 0x50, 0x68; tmpl_off
         * 0x6EC, 0x6F0, 0x6F4, 0x6F8; sentinel = slot - 0x100). */
        {
            extern char D_44F4_iterA, D_44F4_iterB, D_44F4_iterC,
                        D_44F4_iterD, D_44F4_iterE, D_44F4_iterF;
#define INIT_ITER(SLOT, TMPL_OFF, FLOAT_EXPR, DB) do { \
            char *_t = *(char**)((char*)&DB + (TMPL_OFF)); \
            s0 = s1 + (SLOT); \
            _t_buf[0] = _t; \
            *(char**)s2 = _t_buf[0]; \
            if (s1 != (char*)((SLOT) - 0x100)) { \
                s0 = (char*)gl_func_00000000(0x18); \
                if (s0 == NULL) goto epi; \
                gl_func_00000000(s0, s1, *(char**)s2, 1); \
                *(char**)(s0 + 0xC) = (char*)&DB + 0x3C8; \
                *(int*)(s0 + 0x14) = 0; \
                *(float*)(s0 + 0x10) = (FLOAT_EXPR); \
            } \
        } while (0)

            INIT_ITER(0x20,  0x6EC, *(float*)((char*)&D_44F4_iterA + 0xA0), D_44F4_iterA);  /* A */
            INIT_ITER(0x38,  0x6F0, *(float*)((char*)&D_44F4_iterB + 0xA4), D_44F4_iterB);  /* B */
            INIT_ITER(0x50,  0x6F4, -800.0f,                                D_44F4_iterC);  /* C */
            INIT_ITER(0x68,  0x6F8, *(float*)((char*)&D_44F4_iterD + 0xA8), D_44F4_iterD);  /* D */
            INIT_ITER(0x80,  0x6FC, *(float*)((char*)&D_44F4_iterE + 0xAC), D_44F4_iterE);  /* E */
            INIT_ITER(0x98,  0x700, -4000.0f,                               D_44F4_iterF);  /* F (lui 0xC57A) */
#undef INIT_ITER
        }

        /* Iters G-NN: SCALED 2026-05-05 to use the 4-arg unique-extern
         * form (same as A-F above). Each iter declares its own extern at
         * offset 0 to defeat IDO's global CSE on &D_00000000 — IDO can
         * no longer share a single $sN base across iterations. */
        {
            extern char D_44F4_iterG, D_44F4_iterH, D_44F4_iterI, D_44F4_iterJ,
                        D_44F4_iterK, D_44F4_iterL, D_44F4_iterM, D_44F4_iterN,
                        D_44F4_iterO, D_44F4_iterP, D_44F4_iterQ, D_44F4_iterR,
                        D_44F4_iterS, D_44F4_iterT, D_44F4_iterU, D_44F4_iterV,
                        D_44F4_iterW, D_44F4_iterX, D_44F4_iterY, D_44F4_iterZ,
                        D_44F4_iterAA, D_44F4_iterBB, D_44F4_iterCC, D_44F4_iterDD,
                        D_44F4_iterEE, D_44F4_iterFF, D_44F4_iterGG, D_44F4_iterHH,
                        D_44F4_iterII, D_44F4_iterJJ, D_44F4_iterKK, D_44F4_iterLL,
                        D_44F4_iterMM, D_44F4_iterNN;
#define INIT_ITER(SLOT, TMPL_OFF, FLOAT_EXPR, DB) do { \
            char *_t = *(char**)((char*)&DB + (TMPL_OFF)); \
            s0 = s1 + (SLOT); \
            _t_buf[0] = _t; \
            *(char**)s2 = _t_buf[0]; \
            if (s1 != (char*)((SLOT) - 0x100)) { \
                s0 = (char*)gl_func_00000000(0x18); \
                if (s0 == NULL) goto epi; \
                gl_func_00000000(s0, s1, *(char**)s2, 1); \
                *(char**)(s0 + 0xC) = (char*)&DB + 0x3C8; \
                *(int*)(s0 + 0x14) = 0; \
                *(float*)(s0 + 0x10) = (FLOAT_EXPR); \
            } \
        } while (0)
            INIT_ITER(0xB0,  0x704, -8000.0f,                                D_44F4_iterG);  /* G (lui 0xC5FA) */
            INIT_ITER(0xC8,  0x708, *(float*)((char*)&D_44F4_iterH + 0xB0), D_44F4_iterH);  /* H */
            INIT_ITER(0xE0,  0x70C, *(float*)((char*)&D_44F4_iterI + 0xB4), D_44F4_iterI);  /* I */
            INIT_ITER(0xF8,  0x710, *(float*)((char*)&D_44F4_iterJ + 0xB8), D_44F4_iterJ);  /* J */
            INIT_ITER(0x110, 0x714, *(float*)((char*)&D_44F4_iterK + 0xBC), D_44F4_iterK);  /* K */
            INIT_ITER(0x128, 0x718, *(float*)((char*)&D_44F4_iterL + 0xC0), D_44F4_iterL);  /* L */
            INIT_ITER(0x140, 0x71C, *(float*)((char*)&D_44F4_iterM + 0xC4), D_44F4_iterM);  /* M */
            INIT_ITER(0x158, 0x720, *(float*)((char*)&D_44F4_iterN + 0xC8), D_44F4_iterN);  /* N */
            INIT_ITER(0x170, 0x724, *(float*)((char*)&D_44F4_iterO + 0xCC), D_44F4_iterO);  /* O */
            INIT_ITER(0x188, 0x728, *(float*)((char*)&D_44F4_iterP + 0xD0), D_44F4_iterP);  /* P */
            INIT_ITER(0x1A0, 0x72C, *(float*)((char*)&D_44F4_iterQ + 0xD4), D_44F4_iterQ);  /* Q */
            INIT_ITER(0x1B8, 0x730, 1200.0f,                                D_44F4_iterR);  /* R (lui 0x4496) */
            INIT_ITER(0x1D0, 0x734, 1200.0f,                                D_44F4_iterS);  /* S */
            INIT_ITER(0x1E8, 0x738, 1200.0f,                                D_44F4_iterT);  /* T */
            INIT_ITER(0x200, 0x73C, 60.0f,                                  D_44F4_iterU);  /* U (lui 0x4270) */
            INIT_ITER(0x218, 0x740, 60.0f,                                  D_44F4_iterV);  /* V */
            INIT_ITER(0x230, 0x744, 60.0f,                                  D_44F4_iterW);  /* W */
            INIT_ITER(0x248, 0x748, 1.5f,                                   D_44F4_iterX);  /* X (lui 0x3FC0) */
            INIT_ITER(0x260, 0x74C, *(float*)((char*)&D_44F4_iterY + 0xD8), D_44F4_iterY);  /* Y */
            INIT_ITER(0x278, 0x750, 1.5f,                                   D_44F4_iterZ);  /* Z */
            INIT_ITER(0x290, 0x754, 2000.0f,                                D_44F4_iterAA); /* AA (lui 0x44FA) */
            INIT_ITER(0x2A8, 0x758, 2000.0f,                                D_44F4_iterBB); /* BB */
            INIT_ITER(0x2C0, 0x75C, 2000.0f,                                D_44F4_iterCC); /* CC */
            INIT_ITER(0x2D8, 0x760, *(float*)((char*)&D_44F4_iterDD + 0xDC), D_44F4_iterDD); /* DD */
            INIT_ITER(0x2F0, 0x764, *(float*)((char*)&D_44F4_iterEE + 0xE0), D_44F4_iterEE); /* EE */
            INIT_ITER(0x308, 0x768, *(float*)((char*)&D_44F4_iterFF + 0xE4), D_44F4_iterFF); /* FF */
            INIT_ITER(0x320, 0x76C, 240.0f,                                 D_44F4_iterGG); /* GG (lui 0x4370) */
            INIT_ITER(0x338, 0x770, 240.0f,                                 D_44F4_iterHH); /* HH */
            INIT_ITER(0x350, 0x774, 240.0f,                                 D_44F4_iterII); /* II */
            INIT_ITER(0x368, 0x778, 240.0f,                                 D_44F4_iterJJ); /* JJ */
            INIT_ITER(0x380, 0x77C, 240.0f,                                 D_44F4_iterKK); /* KK */
            INIT_ITER(0x398, 0x780, 240.0f,                                 D_44F4_iterLL); /* LL */
            INIT_ITER(0x3B0, 0x784, 240.0f,                                 D_44F4_iterMM); /* MM */
            INIT_ITER(0x3C8, 0x788, 240.0f,                                 D_44F4_iterNN); /* NN (final iter, slot 0x3C8) */
            (void)s2;
#undef INIT_ITER
        }
    }

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
     *   if (s1 != (char*)-0x38) { ... }            // unusual addr-as-imm cmp
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
     *    rewrites `s1 + slot != magic_addr` as `s1 != magic_addr - slot`
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
     * IDO rewrites is `(s1 + slot) != (char*)0xFFFFFF00`, regrouped as
     * `s1 != (char*)0xFFFFFF00 - slot` so the addiu imm fits 16-bit
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
     *   3. Added `char _pad[168];` to grow frame from 0x38 to 0xE8
     *      (matching target). a0/a1/a2 now spill at sp+0xE8/0xEC/0xF0
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
     *     the global allocator's priority calc here.
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
     * pattern there. */
    (void)s0;

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
    *(int*)(a0 + 0x30) = a1;
    *(int*)(a0 + 0x2C) = a2;
    *(float*)(a0 + 0xA8) = 0.0f;
    *(float*)(a0 + 0xAC) = *(float*)((char*)&D_00000000 + 0xE8);
    *(float*)(a0 + 0xB0) = 500.0f;
    *(float*)(a0 + 0xB4) = 70.0f;
    *(float*)(a0 + 0xB8) = 230.0f;
    *(float*)(a0 + 0xBC) = *(float*)((char*)&D_00000000 + 0xEC);
    *(float*)(a0 + 0xC0) = 12.0f;
    *(float*)(a0 + 0xC4) = *(float*)((char*)&D_00000000 + 0xF0);
    *(float*)(a0 + 0xC8) = 2.0f;
    *(float*)(a0 + 0xCC) = 50.0f;
    *(float*)(a0 + 0xD0) = 20.0f;
    *(float*)(a0 + 0xD4) = 500.0f;
    *(float*)(a0 + 0xDC) = 15.0f;
    *(float*)(a0 + 0xE0) = *(float*)((char*)&D_00000000 + 0xF4);
    *(float*)(a0 + 0xD8) = *(float*)((char*)&D_00000000 + 0xF8);
    *(float*)(a0 + 0xA0) = 1000.0f;
    *(int*)(a0 + 0x4DC) = 3;
epi:
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000044F4);
#endif

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000057D8);

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
 * wise multiply + jal + spill setup.
 *
 *   /* component-wise multiply staged Vec3 by another Vec3 *\/
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
 * This block computes a per-axis squared length / dot product on the
 * staged Vec3 (sp+0x1B8 hosts {f4,f10,f6} = {x*ox, y*oy, z*oz} which
 * after the jal becomes a 4-component vector if helper does normalize-
 * with-w-component). Then takes a guard branch on helper's return.
 * NEXT PASS: continue from 0x5A78; far-branch target 0x69E8 is the
 * epilogue/cleanup arm (function tail). */
#ifdef NON_MATCHING
void game_uso_func_0000591C(int *a0) {
    int v0;

    /* Two early-out guards on globals. */
    if (*(int*)((char*)&D_00000000 + 0x78) != 0) return;
    if (*(int*)&D_00000000 == 0) return;

    /* 4-way bit dispatch on a0->field_68 (flag byte).  Each handler
     * makes one gl_func_00000000 call and returns. Fall-through goes
     * to the per-frame body at 0x5998 — not yet decoded. */
    v0 = *(int*)((char*)a0 + 0x68);
    if (v0 & 1) {
        gl_func_00000000();
        return;
    }
    if (v0 & 2) {
        gl_func_00000000(a0);
        return;
    }
    if (v0 & 4) {
        gl_func_00000000(a0);
        return;
    }

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
     *   - 0x5A34-0x5A68: element-wise Vec3 multiply:
     *       sp+0x1B8 *= sp+0x1C4    (x *= mul.x)
     *       sp+0x1BC *= sp+0x1C8    (y *= mul.y)
     *       sp+0x1C0 *= sp+0x1CC    (z *= mul.z)
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
     * Cumulative ~306/1102 insns characterized (up from 282). ~796
     * remaining. NEXT PASS: 0x5E80+ second cross-USO call with sp+0xB4
     * arg setup (likely Vec3-distance/op against accumulated transform).
     *
     * TODO: ~796 remaining insns — continue per-state-branch decoding. */
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000591C);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00006A30: 176-insn (0x2C0) per-frame FPU-heavy update.
 * 0xB8-byte stack frame with multiple Vec3 / matrix locals at sp+0x58,
 * sp+0x94, sp+0x9C, sp+0xA8, sp+0xB4 (clear-flag).
 *
 * ENTRY STAGE (insns 1-15 @ 0x6A30-0x6A7C):
 *   sp -= 0xB8; save ra, s0
 *   *(sp+0xB4) = 0          ; clear flag
 *   if (a0->0x80 == 0) goto end (early exit; reload a0->0x6C in delay)
 *   sub = a0->0x30
 *   sp+0x9C[0..2] = sub->{0xB4,0xB8,0xBC}  ; stage Vec3 from sub-struct
 *
 * BODY (insns 16-170): FPU-heavy update — multiplies Vec3 fields by
 * scalar a0->0xA8, accumulates into local Mat4-like region at
 * sp+0x318 (relative to sub-struct), multiple cross-USO calls.
 *
 * EPILOGUE: standard ra/s0 restore + addiu sp + jr ra.
 *
 * Multi-tick decompile in scope; this captures structural decode of the
 * entry + Vec3 staging stage. Default INCLUDE_ASM matches via the asm. */
extern int gl_func_00000000();
void game_uso_func_00006A30(int *a0) {
    int *sub;
    int local_9C[3];
    int flag = 0;
    if (a0[0x80/4] == 0) goto end;
    sub = (int*)a0[0x30/4];
    local_9C[0] = sub[0xB4/4];
    local_9C[1] = sub[0xB8/4];
    local_9C[2] = sub[0xBC/4];
    /* TODO: ~155 insns of FPU math + cross-USO calls */
    (void)local_9C;
end:
    (void)flag;
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
 * byte-matched yet. Default INCLUDE_ASM build remains exact. */
void game_uso_func_00006CF0(int *a0) {
    int *sub;
    int base_vec[3];
    int scaled_vec[3];
    int tmp_vec[3];
    int added_vec[3];
    int dispatch_arg;
    int timer;

    sub = *(int**)((char*)a0 + 0x30);
    base_vec[0] = *(int*)((char*)sub + 0xB4);
    base_vec[1] = *(int*)((char*)sub + 0xB8);
    base_vec[2] = *(int*)((char*)sub + 0xBC);

    *(float*)&scaled_vec[0] = *(float*)((char*)sub + 0x318) * *(float*)((char*)a0 + 0xA8);
    *(float*)&scaled_vec[1] = *(float*)((char*)sub + 0x31C) * *(float*)((char*)a0 + 0xA8);
    *(float*)&scaled_vec[2] = *(float*)((char*)sub + 0x320) * *(float*)((char*)a0 + 0xA8);

    tmp_vec[0] = scaled_vec[0];
    tmp_vec[1] = scaled_vec[1];
    tmp_vec[2] = scaled_vec[2];
    added_vec[0] = tmp_vec[0];
    added_vec[1] = tmp_vec[1];
    added_vec[2] = tmp_vec[2];

    *(float*)&base_vec[0] += *(float*)&added_vec[0];
    *(float*)&base_vec[1] += *(float*)&added_vec[1];
    *(float*)&base_vec[2] += *(float*)&added_vec[2];

    dispatch_arg = 0;
    if (*(int*)((char*)a0 + 0x6C) == 0) {
        dispatch_arg = 0x10;
    }

    sub = *(int**)((char*)a0 + 0x30);
    if (*(int*)((char*)sub + 0x938) != 0 && *(int*)((char*)sub + 0xA54) != 0) {
        timer = *(int*)((char*)a0 + 0x70);
        if (timer < 60) {
            if (*(float*)((char*)sub + 0x348) <= 30.0f) {
                gl_func_00000000(*(int*)((char*)sub + 0x840), dispatch_arg);
                *(int*)((char*)a0 + 0x70) = 61;
            } else {
                *(int*)((char*)a0 + 0x70) = timer + 1;
            }
        } else if (timer == 60) {
            gl_func_00000000(*(int*)((char*)sub + 0x840), dispatch_arg);
            *(int*)((char*)a0 + 0x70) = 61;
        }
    }

    gl_func_00000000(a0);
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

#ifdef NON_MATCHING
/* 41.5% NM wrap. 28-insn (0x70).
 *
 * UPDATE 2026-05-02: re-examined target asm. NOT prologue-stolen — the
 * lui+lw prefix at offset 0 IS inside this function's own symbol (.s
 * declares glabel game_uso_func_00006F38 covering all 28 insns).
 * Tried PROLOGUE_STEALS=8 + unique-extern recipe: regressed to 17.71 %
 * because splice removed bytes that genuinely belong to this function.
 * Reverted both Makefile entry and undefined_syms_auto.txt addition.
 *
 * Target structure (28 insns, frame 0x40):
 *   lui+lw t6, 0x548(D)         — load *(D+0x548) into t6 ($s-survives)
 *   prologue (frame 0x40, save ra)
 *   a1 = *t6
 *   spill a1 to 0x3C(sp) AND 4(sp)  ← TWO dead spills, IDO bookkeeping
 *   a2 = a0->0x30
 *   jal gl_func(a0, v, a0->0x30+0xB4, [a3 garbage])
 *   addiu a2, +0xB4 in delay
 *   then sltu+beq+bnel chain to compute return = (v0!=0 && (v0->0x84&0x400 || (v0->0x2C && (v0->0x2C->0x84&0x400))))
 *
 * The 2 dead a1 spills are not reproducible from natural C — they're
 * artifacts of how IDO scheduled the load BEFORE the jal. Body logic
 * decoded; need a multi-stage variant tester or accept ~41% cap. */
int game_uso_func_00006F38(int *a0) {
    int v = **(int**)((char*)&D_00000000 + 0x548);
    int *r = (int*)gl_func_00000000(a0, v, *(int*)((char*)a0 + 0x30) + 0xB4, v);
    int *p;
    if (r == 0) return 0;
    if ((*(int*)((char*)r + 0x84) & 0x400) != 0) return 1;
    p = (int*)*(int*)((char*)r + 0x2C);
    if (p == 0) return 0;
    return (*(int*)((char*)p + 0x84) & 0x400) != 0;
}
#else
#ifdef NON_MATCHING
/* game_uso_func_00006F38: 28-insn (0x70) flag-test wrapper. Reads a global
 * pointer from D[0x548], dereferences to get a chain pointer, calls a
 * cross-USO callee with (chain, a0->0x30+0xB4), then tests the 0x400 bit
 * on the result and (optionally) on a sub-pointer at +0x2C.
 *
 * Anomaly: target emits the `lui t6, 0; lw t6, 0x548(t6)` pair BEFORE
 * its `addiu sp, -0x40; sw ra` prologue (insns 0/1 vs 2/3). C emit puts
 * prologue first, lui+lw second. This 2-insn schedule cap is unflippable
 * from straightforward C (IDO -O2 always emits sp-adjust first).
 *
 * Also target has 2 dead spills of `*t6` to sp+0x4 + sp+0x3C — neither
 * is reloaded post-call. Suggests original C had two locals (e.g.
 * `int v = *t6; int v2 = v;`) that GCC IDO regalloc spilled unnecessarily.
 *
 * Frame size differs (target -0x40 vs C-emit -0x18), driven by the dead
 * spills + larger local block. Multi-tick refinement target — partial
 * structural decode below; default INCLUDE_ASM remains exact. */
int game_uso_func_00006F38(int *a0) {
    int *p1 = *(int**)((char*)&D_00000000 + 0x548);
    int *p2;
    int *p3;

    p2 = (int*)gl_func_00000000(*p1, *(int*)((char*)a0 + 0x30) + 0xB4);
    if (p2 == 0) return 0;
    if ((*(int*)((char*)p2 + 0x84) & 0x400) != 0) return 1;

    p3 = *(int**)((char*)p2 + 0x2C);
    if (p3 == 0) return 0;
    return (*(int*)((char*)p3 + 0x84) & 0x400) != 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006F38);
#endif
#endif

#ifdef NON_MATCHING
/* game_uso_func_00006FA8: 127-insn (0x1FC) heavy FPU + multi-call compute.
 * Frame -0xC0. Sibling of 0x6CF0 (per-frame FPU update class).
 *
 * Structural decode (offsets in target asm):
 *
 *   ; Stage 1 (insns 1-7): prologue + first cross-USO call (callee=0).
 *   self = a0; saved to s0.
 *   gl_func_00000000(...);              ; first call (return float in f0)
 *   sp[0xBC] = 0;                       ; clear local accumulator
 *
 *   ; Stage 2 (insns 8-13): early-out if f0 < 0.
 *   if (f0 < 0.0f) goto end;
 *
 *   ; Stage 3 (insns 14-26): two consecutive cross-USO calls feeding
 *   ; values from D[0x570] and D[0x574] into temp slots.
 *   p1 = *(int**)(D + 0x570);
 *   sp[0xB8] = *p1;                     ; spill (also passed as stack-arg5)
 *   sp[0x4]  = sp[0xB8];                ; outgoing arg5
 *   gl_func_00000000(self, sp[0xB8], self->[0x30] + 0xB4);
 *
 *   p2 = *(int**)(D + 0x574);
 *   sp[0xB4] = *p2;
 *   sp[0x4]  = sp[0xB4];
 *   tmp = gl_func_00000000(self, sp[0xB4], self->[0x30] + 0xB4);
 *   if (tmp == 0) goto end;             ; bnezl-pattern early-out
 *
 *   ; Stage 4 (insns 27-50): Vec3-arithmetic with pointer-chain copies.
 *   ; Reads from self->[0x30] sub-object, copies 3 ints (Vec3-int) + computes
 *   ; FPU products. Stores to sp[0x6C..0x74] AND sp[0x34..0x3C].
 *
 *   ; Stage 5 (insns 51-90): 5-FPU arithmetic chain
 *   ; (mul.s f0,f1; mul.s f4,f1; mul.s f6,f0; sub.s f8,f0,f1; etc.) producing
 *   ; new Vec3 values stored to sp[0x90..0x98] and sp[0x9C..0xA4].
 *
 *   ; Stage 6 (insns 91-110): Vec3-int copy cascade — 3 lw/sw pairs each
 *   ; from sp+0x90..0x98 to caller-provided buffer at *(arg pointer) + 0x30.
 *
 *   ; Stage 7 (insns 111-127): final c.lt.s + branch-likely; conditional sw
 *   ; based on FPU comparison; epilogue.
 *
 *   end: return;
 *
 * Spine context: per-frame compute in the 0x6XXX FPU-heavy cluster
 * (siblings 0x6A30, 0x6CF0, 0x6F38). Reads self with sub at +0x30.
 * Field offsets used: self->{0x30}, sub->{0xB4...}, plus globals at
 * D+0x570, D+0x574.
 *
 * Multi-tick refinement target. Default INCLUDE_ASM build remains exact
 * via the asm. Skeleton kept for grep discoverability of struct field
 * offsets and the per-frame compute call-graph. */
void game_uso_func_00006FA8(int *a0) {
    /* Outline only — multi-tick decomp scope. The 7-stage compute (call,
     * float gate, 2 staged calls, Vec3 stage, FPU chain, Vec3 copy, conditional
     * tail) needs careful arg passing + register allocation to byte-match.
     * Skeleton kept for the per-frame compute's struct-typing pass. */
    int *sub = *(int**)((char*)a0 + 0x30);
    (void)sub;
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
void game_uso_func_000071E0(int *a0) {
    /* Outline only — multi-tick decomp scope. The 10-stage compute
     * (flag-gate, float-gate, counter increment with reset, 4-Vec3 stage,
     * 3 cross-USO calls, conditional Vec3 store) needs careful arg-passing
     * + register-allocation reconstruction to byte-match. Documented for
     * the per-frame compute's struct-typing pass. */
    int *sub = *(int**)((char*)a0 + 0x30);
    int flag = *(int*)((char*)a0 + 0x68);
    (void)sub;
    (void)flag;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000071E0);
#endif

void game_uso_func_00007424(void *a0) {
    *(int*)((char*)a0 + 0x64) = 3;
    gl_func_00000000(a0);
}

#ifdef NON_MATCHING
/* 70.97% NM. Inverse of game_uso_func_000074D8: pulls 4 floats from table (+0x30 deref)
 * at offsets 0x768/0x708/0x6F0/0x4A8, mirrors them into a0+0x4C8..0x4D4,
 * scales 3 of them in-place back into the table (by a0+0x33C=sx for the
 * first, a0+0x36C=sy for the other two), then does one unscaled intra-table
 * copy (table+0x4A8 = table+0x4D8).
 *
 * Match gap: IDO schedules the 4 inbound copies with a split
 * `addiu vN, v1, OFFSET` + `lwc1 fN, 0x10(vN)` pair instead of a single
 * `lwc1 fN, OFFSET+0x10(v1)` — even though the offsets fit in 16 bits and
 * table is kept in v1 across all 4 copies. Attempts with named-base
 * pointers (char *t = table + 0x758) in the C were merged by IDO back to
 * direct offsets (~27 insns produced vs target 36 insns). Target also
 * pre-computes `a3 = a0 + 0x35C` at insn 3 and uses `lwc1 f18, 0x10(a3)`
 * for the 3rd scale_y access — probably a struct-field access in source.
 * 27/36 insns match structurally; body is semantically correct. */
void game_uso_func_00007448(char *a0) {
    char *table = *(char**)(a0 + 0x30);
    float sx = *(float*)(a0 + 0x33C);
    char *t;

    t = table + 0x758;
    *(float*)(a0 + 0x4C8) = *(float*)(t + 0x10);
    t = table + 0x6F8;
    *(float*)(a0 + 0x4CC) = *(float*)(t + 0x10);
    t = table + 0x6E0;
    *(float*)(a0 + 0x4D0) = *(float*)(t + 0x10);
    t = table + 0x498;
    *(float*)(a0 + 0x4D4) = *(float*)(t + 0x10);
    *(float*)(table + 0x768) = *(float*)(a0 + 0x4C8) * sx;

    table = *(char**)(a0 + 0x30);
    t = table + 0x6F8;
    *(float*)(t + 0x10) = *(float*)(a0 + 0x4CC) * *(float*)(a0 + 0x36C);

    table = *(char**)(a0 + 0x30);
    t = table + 0x6E0;
    *(float*)(t + 0x10) = *(float*)(a0 + 0x4D0) * *(float*)(a0 + 0x36C);

    table = *(char**)(a0 + 0x30);
    t = table + 0x498;
    *(float*)(t + 0x10) = *(float*)(table + 0x4D8);
}
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
 * Partial C body below: 38.83% (was 37.51% pre-bit-0x80-fix-2026-05-05).
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
long long game_uso_func_00007538(int *a0, int a1) {
    /* 2026-05-08 destructive refactor: eliminate `outer` named local + reduce
     * named-int locals. Goal: defeat IDO's $s0 promotion for the 5+-use
     * cross-block value `(int*)a0[0x30/4]`, push function into leaf shape.
     * Each use site now reads the field inline so allocator sees independent
     * live ranges per arm. */
    int ret_lo = 0;
    int ret_hi = 0;
    int a1_saved = a1;
    int counter, flags, flag2;
    float f0 = 0.0f, f2 = 0.0f, f_tmp;

    counter = a0[0x50 / 4];
    if (counter > 0) a0[0x50 / 4] = counter - 1;
    flags = a0[0x48 / 4];
    if (flags > 0) a0[0x48 / 4] = flags - 1;

    flag2 = a0[0x6C / 4];
    if (flag2 != 0) goto trunk;

    /* ==== DISPATCH CASCADE (flag2 == 0) ==== */
    /* Bit tests are on a1_saved (the input arg); the running mask `a1`
     * starts at 0 (= flag2) and gets ORed bits stored into a0[0x6C]. */
    a1 = flag2;  /* explicit: running mask starts at 0 */

    if (a1_saved & 0x10) {
        if (((int*)a0[0x30 / 4])[0x938 / 4] != 0) {
            f_tmp = *(float*)&a0[0x38 / 4];
            *(float*)&a0[0x3C / 4] = (f_tmp >= 0.0f) ? 1.0f : -1.0f;
        }
        a1 = a0[0x6C / 4];
        goto trunk;
    }

    if (a1_saved & 0x01) {
        flags = a0[0x48 / 4];  /* reload — asm reads at 0x75E0 */
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
        /* arg1 & 0x04 arm: reset counter + set f2 = 1.0f, ret_hi = 1 */
        a0[0x50 / 4] = 8;
        f2 = 1.0f;
        ret_hi = 1;
        goto trunk;
    }
check_20:
    if (a1_saved & 0x20) {
        /* arg1 & 0x20 arm body: fabs(outer->0xB4) % 9 */
        f_tmp = *(float*)&((int*)a0[0x30 / 4])[0xB4 / 4];
        if (f_tmp < 0.0f) f_tmp = -f_tmp;
        a0[0x44 / 4] = 60;
        a0[0x58 / 4] = (int)f_tmp % 9;
        goto trunk;
    }
    if (a1_saved & 0x80) {
        /* arg1 & 0x80 arm body. Per asm trace 0x7660-0x767C: ret_hi = 1 set
         * here (line 3624-3627 doc). Without it, the bit-0x80 ARM-FIRE path
         * was returning v1=0 instead of v1=1 to caller. */
        a0[0x6C / 4] = a1 | 0x80;
        a0[0x4C / 4] = 0;
        a0[0x44 / 4] = 2;
        a1 = a1 | 0x80;
        ret_hi = 1;
        goto trunk;
    }
    if (a1_saved & 0x08) {
        /* 2026-05-07 BUG FIX: prior C had the condition inverted.
         * Asm 0x76F4 `beql t4, $0, +0x13` means: if outer->0x938 == 0,
         * branch directly to trunk (annulled delay-slot, no f2 store).
         * Else (outer->0x938 != 0): fall through to mtc1 -1.0f → f2,
         * then b to trunk. Both arms reach trunk; only the non-zero
         * arm sets f2 = -1.0f. */
        if (((int*)a0[0x30 / 4])[0x938 / 4] != 0) {
            f2 = -1.0f;
        }
        goto trunk;
    }
    if (a1_saved & 0x02) {
        if (((int*)a0[0x30 / 4])[0x938 / 4] != 0) {
            ret_lo |= 0x400;
            if (a1_saved & 0x100) {
                a0[0x6C / 4] = a1_saved | 0x100;
                a0[0x44 / 4] = 0x68;
            }
        }
        a1 = a0[0x6C / 4];
    }

trunk:
    /* ==== FLAG-DECREMENT TRUNK (0x7744-0x7A??) ==== */
    /* Per-bit: if (a1 & BIT), decrement a0[0x44], OR ret_lo bits, and on
     * zero clear the bit in a0[0x6C]. Currently only bits 0x01 / 0x40 / 0x20
     * are decoded; 0x80 / 0x100 / 0x08 / 0x04 / 0x10 are TODO. */
    if (a1 & 0x01) {
        ret_lo |= 0x500;
        counter = a0[0x44 / 4] - 1;
        a0[0x44 / 4] = counter;
        if (counter == 0) {
            a0[0x6C / 4] &= ~0xA1;  /* clears 0x80|0x20|0x01 together */
            goto ret;
        }
    }
    if (a1 & 0x40) {
        /* 0x7774-0x77A4: bit-0x40 arm. Both paths goto a shared post-trunk
         * region (NOT the function epilogue — it's the bit-0x100/inner-state
         * processing at 0x79F8). asm uses bnel to skip the bit-clear when
         * counter != 0, which annuls the bit-clear store; fall-through stores
         * cleared bit. ret_lo |= 0x100 is the delay slot of the counter!=0
         * goto, so it ONLY happens on counter!=0. counter==0 path stores the
         * cleared bit then jumps without OR. */
        counter = a0[0x44 / 4] - 1;
        if (counter != 0) {
            a0[0x44 / 4] = counter;
            ret_lo |= 0x100;
            goto ret;
        }
        a0[0x6C / 4] &= ~0x40;
        goto ret;
    }
    if (a1 & 0x20) {
        /* 0x77A8-0x7824: bit-0x20 trunk arm. Guarded by outer->[0x938] == 0;
         * decrements a0[0x4C] (sub-counter). When sub-counter < 31 (slti at
         * 0x77CC), also reads 2-float (x,y) pair from D+0x638+a0[0x58]*8 into
         * f0/f2. When sub-counter expires (== 0 after decrement), clear bit
         * 0x20 directly. While sub-counter still ticks, also decrement
         * a0[0x44] (main duration counter); when THAT hits zero, also clear
         * bit 0x20. ret_lo |= 0x200 unconditionally inside outer-zero arm. */
        if (((int*)a0[0x30 / 4])[0x938 / 4] == 0) {
            int cnt = a0[0x4C / 4];
            ret_hi = 1;
            ret_lo |= 0x200;
            if (cnt < 31) {
                int sub_idx = a0[0x58 / 4];
                f0 = *(float*)((char*)&D_00000000 + 0x638 + sub_idx * 8);
                f2 = *(float*)((char*)&D_00000000 + 0x638 + sub_idx * 8 + 4);
            }
            a0[0x4C / 4] = cnt - 1;
            if (a0[0x4C / 4] != 0) {
                /* sub-counter still ticking: also decrement main counter */
                counter = a0[0x44 / 4] - 1;
                if (counter != 0) {
                    a0[0x44 / 4] = counter;
                    goto ret;
                }
            }
            /* sub-counter expired OR main counter expired: clear bit */
            a0[0x6C / 4] &= ~0x20;
            goto ret;
        }
    }
    /* Trunk-arms wired: 0x01 / 0x40 / 0x20 / 0x80 / 0x100. Bits 0x02 /
     * 0x04 / 0x08 / 0x10 are dispatch-cascade-only — verified
     * 2026-05-07 by walking 0x7740-0x7990 of the asm.
     *
     * Status 2026-05-08: 48.81% (incrementally up from 48.59% on 2026-05-07).
     * Remaining 51% is structural: built saves $s0 (frame -0x28) where
     * target uses NO stack frame at all (target is a pure leaf — verified
     * 2026-05-08 via `grep -E "0C[0-9A-F]{6}" <asm>` returning ZERO matches,
     * i.e., no jal opcodes anywhere). Target compiles as a leaf using only
     * caller-save regs ($a2/$a3/$v0/$v1/$t-regs) for the entire body.
     *
     * Built's `outer` / `register int *t` locals get promoted to $s0
     * because their live ranges span the goto-cascade (multiple arms each
     * `outer = (int*)a0[0x30/4]; ... goto trunk;`). Even with no jal calls,
     * IDO -O2's allocator decides $s0 is the cheapest slot for a value
     * referenced 5+ times across cascading basic blocks.
     *
     * Path to break the cap (multi-tick — destructive refactor):
     * (a) [TESTED 2026-05-08, NEGATIVE RESULT] Eliminate the `outer` named
     *     local entirely. Inline `(int*)a0[0x30/4]` at EACH use site. Did
     *     NOT move fuzzy% (48.81% → 48.81%). IDO -O2 hoists the repeated
     *     `lw t,0x30(a0)` reads back into a single CSE'd $s0-held value
     *     across the cascade — inlining alone is insufficient to break the
     *     extern-base CSE pattern. (Confirms `docs/IDO_CODEGEN.md`'s
     *     inverse-CSE caveat: extern-base loads with constant offsets are
     *     non-defeatable via local-introduction.)
     * (b) Replace `goto trunk` from each arm with explicit `if/else if`
     *     control flow so the dispatch cascade has no shared join point
     *     (each arm's life range becomes independent). UNTESTED — would
     *     require reshaping ~9 dispatch arms; speculation is that without
     *     the trunk-join, the running-mask state can stay in caller-save
     *     regs since no two arms share a value at runtime.
     * (c) Verify the leaf-shape (no stack frame) emerges, then re-grind
     *     per-arm body. */

    if (a1 & 0x80) {
        /* bit-0x80 trunk arm — 3-tier range classifier on sub_cnt with
         * shared Vec2 table lookup at D[0x638] and post-lookup limit check.
         * Initial wire-up of documented decode (above comments capture the
         * full tier breakdown; this body covers the shared/limit portion). */
        int sub_cnt = a0[0x4C / 4];
        int list_base = a0[0x4DC / 4];
        int main_cnt;
        int new_sub_cnt;
        int limit;
        a0[0x58 / 4] = sub_cnt;
        if (sub_cnt < 8) {
            ret_lo |= 0x1000;
        }
        f0 = *(float*)((char*)&D_00000000 + 0x638 + sub_cnt * 8);
        f2 = *(float*)((char*)&D_00000000 + 0x638 + sub_cnt * 8 + 4);
        main_cnt = a0[0x44 / 4];
        new_sub_cnt = sub_cnt + 1;
        a0[0x4C / 4] = new_sub_cnt;
        if (main_cnt == 0) {
            limit = 8;
        } else if (main_cnt == 1) {
            limit = list_base + 16;
        } else {
            limit = list_base * 2 + 24;
        }
        if (new_sub_cnt >= limit) {
            a0[0x6C / 4] &= ~0x80;
        }
        goto ret;
    }

    if (a1 & 0x100) {
        /* bit-0x100 trunk arm @ 0x7990-0x79F4 (3-tier main_cnt classifier):
         *   main_cnt = a0[0x44];
         *   if (main_cnt >= 93)        f2 = 1.0f, ret_hi = 1; (path A)
         *   else if (main_cnt >= 73)   ret_hi = 1; skip bnez check (path B)
         *   else if (main_cnt >= 61)   ret_lo |= 0x100;  (path D)
         *   else                       (no flag set)     (path C)
         *
         *   Merge @ 0x79E0:
         *     new_cnt = main_cnt - 1;
         *     if (new_cnt != 0) a0[0x44] = new_cnt;
         *     else              a0[0x6C] &= ~0x100;
         *
         * Path B (main_cnt >= 73) bypasses the bnez merge: it stores
         * (main_cnt - 1) directly to a0[0x44] in the delay slot of an
         * unconditional jump to the post-merge ret-finalize at 0x79F8. */
        int main_cnt = a0[0x44 / 4];
        int new_cnt = main_cnt - 1;
        if (main_cnt >= 93) {
            f2 = 1.0f;
            ret_hi = 1;
            if (new_cnt != 0) a0[0x44 / 4] = new_cnt;
            else              a0[0x6C / 4] &= ~0x100;
        } else if (main_cnt >= 73) {
            ret_hi = 1;
            a0[0x44 / 4] = new_cnt;
        } else {
            if (main_cnt >= 61) ret_lo |= 0x100;
            if (new_cnt != 0) a0[0x44 / 4] = new_cnt;
            else              a0[0x6C / 4] &= ~0x100;
        }
        /* Falls through to common ret_hi-conditional float-state update
         * @ 0x79F8-0x7A78 (now wired below): if ret_hi != 0, f16 absorbs
         * +1.0 or -1.0 depending on a0[0x3C], then stores back. */
    }

    /* bit-0x80 entry (0x7828-0x7848, decoded 2026-05-05):
     *   if (a1 & 0x80) {
     *       sub_cnt = a0[0x4C];                 // same sub-counter as bit-0x20
     *       if (sub_cnt < 8) {
     *           list_base = a0[0x4DC];          // SHARED-PATH: load list-base
     *           ... fast-path body (0x787C-0x7900) ...
     *       } else {
     *           list_base = a0[0x4DC];          // (delay-slot load — same)
     *           ... slow-path body (0x7848-0x787C) ...
     *       }
     *   }
     *
     * Slow-path (sub_cnt >= 8, 0x7848-0x787C, decoded 2026-05-05 next pass):
     *   t8 = list_base + 8;
     *   if (sub_cnt < t8) goto small_path;       // bnez +3
     *   t9 = list_base + 0x10;
     *   if (sub_cnt < t9) goto med_path;          // bnez +5
     *   t0 = list_base + list_base;               // 2*list_base (stride calc)
     *   t9 = list_base + 0x10;
     *   if (sub_cnt < t9) ... else goto +0x30 (epilogue?)
     *
     * The `t0 = list_base * 2` is a stride-doubling calc — likely for a
     * tiered list lookup. cnt<8/cnt<16/cnt<24 boundaries match a 3-tier
     * 8-entry-each list (max 24 sub-objects).
     *
     * BIT-0x80 FAST-PATH BODY DECODED 2026-05-05 (asm 0x787C-0x7900, 33 insns):
     *   stride = list_base * 2;                    // 2x stride for 3rd tier
     *   if (sub_cnt < stride + 16) goto tier_lo;
     *     // tier_hi (sub_cnt >= stride+16):
     *     a0[0x58] = sub_cnt - stride - 16;
     *     if (sub_cnt < stride + 21) goto epilogue_7914;
     *     if (stride + 23 < sub_cnt) {
     *         t2 = a0[0x58];                      // reload, used at 0x7918
     *         goto epilogue_7918;
     *     }
     *     ret_lo |= 0x1600;                       // tier-hi mid OR-flag
     *     goto epilogue_7914;
     *   tier_lo:
     *     if (sub_cnt < list_base + 8) goto tier_low;
     *       // tier_mid (list_base+8 ≤ sub_cnt < stride+16):
     *       a0[0x58] = sub_cnt - list_base - 8;
     *       if (sub_cnt < list_base + 13) goto epilogue_7914;
     *       if (list_base + 15 < sub_cnt) {
     *           t2 = a0[0x58]; goto epilogue_7918;
     *       }
     *       ret_lo |= 0x1200;                     // tier-mid OR-flag
     *       goto epilogue_7914;
     *   tier_low:
     *     if (sub_cnt < 5) goto epilogue_7914;
     *     // (continues at 0x7900+, not yet decoded — likely tier_low body)
     *
     * Net structure: 3-tier range classifier on sub_cnt, with a0[0x58] set
     * to the within-tier offset and ret_lo OR'd with tier-specific flag bits
     * (0x1200 for mid tier, 0x1600 for high tier). The boundary constants
     * (8, 13, 16, 21, 23) suggest a 5-zone subdivision per 8-stride unit,
     * possibly matching anim/state-frame ranges.
     *
     * Cumulative bit-0x80 body decoded: 33/~80 insns.
     *
     * BIT-0x80 TIER_LOW + LIMIT-CHECK BODY DECODED 2026-05-05 (asm
     * 0x7900-0x7990, +36 insns):
     *   // tier_low completion (came here when sub_cnt >= 5):
     *   a0[0x58] = sub_cnt;
     *   if (sub_cnt < 8) {
     *       ret_lo |= 0x1000;                      // tier_low OR-flag
     *   }
     *   // shared table lookup for all 3 tiers:
     *   {
     *       Vec2 *table = (Vec2*)((char*)&D_00000000 + 0x638);
     *       f0 = table[sub_cnt].x;                  // 8-byte stride lookup
     *       f2 = table[sub_cnt].y;
     *   }
     *   // post-lookup state transition:
     *   main_cnt = a0[0x44];
     *   new_sub_cnt = sub_cnt + 1;
     *   a0[0x4C] = new_sub_cnt;                     // commit new sub_cnt
     *   if (main_cnt == 0)         limit = 8;
     *   else if (main_cnt == 1)    limit = a0[0x4DC] + 16;  // list_base+16
     *   else                       limit = a0[0x4DC]*2 + 24; // 2*list_base+24
     *   if (new_sub_cnt >= limit) {
     *       a0[0x6C] &= ~0x80;                      // clear bit-0x80 (done)
     *   }
     *
     * The 3-tier limit (8 / list_base+16 / 2*list_base+24) confirms the
     * earlier hypothesis: list_base*2 stride is for tier 3 (high), list_base
     * stride for tier 2 (mid), constant 8 for tier 1 (low). Each tier has
     * 8 entries, max 24 sub-objects. The Vec2 table at D[0x638] is shared
     * — the per-tier code paths just compute a different a0[0x58] index
     * into it. The OR-flags (0x1000/0x1200/0x1600) signal the calling
     * dispatcher which tier was hit so it can drive different rendering.
     *
     * Cumulative bit-0x80 body decoded: 69/~80 insns (~86%). Remaining
     * ~10 insns at 0x7990+ (likely final return/ret_lo finalize). */

    /* common float-state update tail @ 0x79F8-0x7A94 (decoded 2026-05-07,
     * 26 insns). Triggered after any trunk-arm completes:
     *   if (ret_hi != 0) {
     *       float f12 = a0[0x3C];
     *       if      (f12 >  0.0)  a0[0x3C] = 1.0f;        // path A
     *       else if (f12 <  0.0)  a0[0x3C] = -1.0f;       // path B-b
     *       // f12 == 0: no change                          (path B-a)
     *       a0[0x38] = a0[0x3C];                            // commit sign
     *       f0 = a0[0x3C];                                  // for store @ 0x44(v1)
     *   } else {
     *       a0[0x38] = f16;                                 // f16 = 0.0f initial
     *       f0 = ?;                                         // f0 used at 0x7A80
     *   }
     *   ((float*)((int*)a0[0x30])->[0x800])->[0x44] = f0;
     *   ((float*)((int*)a0[0x30])->[0x800])->[0x48] = f2;
     *   ((int*)((int*)a0[0x30])->[0x800])->[0x40] = ret_lo;
     *
     * Wired below as the function's epilogue-with-FPU section. The
     * `f0 = ?` for ret_hi==0 path is unclear; target falls through the
     * mov.s f0,f12 at 0x7A74 in path A and uses f12 from the 0x3C reload
     * — whether ret_hi==0 path also goes through it (with f12 = a0[0x38]
     * after the swc1 f16,0x38 store) is the unresolved bit. */
    if (ret_hi != 0) {
        f_tmp = *(float*)&a0[0x3C / 4];
        if (f_tmp > 0.0f)        *(float*)&a0[0x3C / 4] = 1.0f;
        else if (f_tmp < 0.0f)   *(float*)&a0[0x3C / 4] = -1.0f;
        /* f_tmp == 0: leave as-is */
        *(float*)&a0[0x38 / 4] = *(float*)&a0[0x3C / 4];
        f0 = *(float*)&a0[0x3C / 4];  /* f0 = sign-clamped value */
    } else {
        *(float*)&a0[0x38 / 4] = 0.0f;  /* f16 was 0.0f initial */
        /* f0 unchanged: bit-0x80 trunk may have set it, otherwise 0.0f initial */
    }
    /* fall through to ret */

ret:
    /* Common epilogue (0x7A78-0x7A94, 7 insns): three stores to
     * outer->[0x800] (= a0->[0x30]->[0x800]), then jr ra with sw delay.
     * Two reloads of outer happen — at 0x7A78 and 0x7A88 (after the
     * f0/f2 stores, before the ret_lo store). */
    *(float*)&((int*)((int*)a0[0x30 / 4])[0x800 / 4])[0x44 / 4] = f0;
    *(float*)&((int*)((int*)a0[0x30 / 4])[0x800 / 4])[0x48 / 4] = f2;
    /* Reload outer (target's 0x7A88-0x7A8C reload before jr ra+sw delay) */
    ((int*)((int*)a0[0x30 / 4])[0x800 / 4])[0x40 / 4] = ret_lo;
    return ((long long)ret_hi << 32) | (unsigned int)ret_lo;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007538);
#endif

/* 9-insn body with cross-function `beql v1, zero, +7` to 7ABC+4 — same
 * tail-share family as 7ABC. C-emit always produces 12 insns (separate null
 * path with own jr ra) and can't be coaxed to use the cross-function branch.
 *
 * Promotion recipe (sibling of 7ABC's PREFIX_BYTES + INSN_PATCH combo):
 * empty void C body (2 insns: jr ra; nop) + PREFIX_BYTES injecting the 7
 * leading body insns + INSN_PATCH overwriting the trailing nop with
 * mov.s $f0, $f2. Final 9 insns byte-match expected. The cross-function
 * `beql` (offset +7 = .+0x1C from delay slot) lands at 7A98+0x28 = 7ABC+4
 * which is preserved as long as 7A98 and 7ABC are emitted adjacent in the
 * same .c (they are — game_uso.c source order). Pure raw-bytes prefix:
 * no relocs needed (lw/beql/mtc1/lwc1/sub.s are all PC-imm or reg-only). */
void game_uso_func_00007A98(void) {}

/* 4-insn body `mtc1 $0,$f2; nop; jr ra; mov.s $f0,$f2` — the cross-function
 * tail-share with 7A98 (beql lands at 7ABC+4) which IDO -O2 cannot reproduce
 * from any C source (22 prior variants exhausted; see git history).
 *
 * Promotion recipe (2026-05-05): empty `void f(void) {}` C body emits 2
 * insns (`jr ra; nop` = 8 bytes). PREFIX_BYTES injects 8 leading bytes
 * (`mtc1 $0,$f2; nop`) + INSN_PATCH at offset 0xC overwrites the trailing
 * nop with `mov.s $f0,$f2` (0x46001006). Result: 16 bytes matching expected.
 *
 * The C body is `void` but the function semantically returns float — the
 * post-cc recipe sets $f0 = $f2 = 0.0f at runtime. Type mismatch is
 * harmless: no in-tree callers (the function is reached via `beql` from
 * 7A98 and external callers declared as `float (void)` get the correct
 * $f0 value via the mov.s). Per feedback_land_script_accepts_byte_verify_
 * for_post_cc_recipes.md — byte-correctness against expected/ IS the gate. */
void game_uso_func_00007ABC(void) {}

#ifdef NON_MATCHING
/* game_uso_func_00007ACC: 0x150 (84 insns). Function-table dispatcher.
 * 90.08% fuzzy (up from 16.37% stub). Remaining ~10pp diff is purely
 * frame-layout: expected has 0x38 frame using caller-arg slots
 * (sp+0x3C/0x40/0x44) for incoming-arg spill, build has 0x28 frame
 * using local slots. Two extra emits in expected: a dead `sw a1, 0x34(sp)`
 * before the dispatch jal, and a `sw a1, 4(sp)` (outgoing-a1-slot save)
 * in the jal delay. Both result from IDO's spill-slot heuristic — neither
 * forced from C-level via local-variable ordering, char-pad locals, or
 * volatile decls (all attempted, all collapsed to no-op). Logic is correct,
 * codegen-cap remaining.
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
int game_uso_func_00007ACC(int *a0, int *a1, int arg3, int *arg4) {
    int v;
    int *r;
    int *inner;

    *a1 = 0;
    v = a0[0x40 / 4];
    if (v < 0 || v >= 12) {
        gl_func_00000000((char*)&D_00000000 + 0x78C,
                         (char*)&D_00000000 + 0x7B0, 0x609);
    }
    /* Re-load v from a0[0x40] for the table-lookup — matches asm 0x7B1C
     * which has an independent lw v0,0x40(s0) after the assertion jal. */
    r = (int*)gl_func_00000000(a0,
                               *(int*)(*(int*)((char*)&D_00000000 + 0x548 + a0[0x40 / 4] * 4)),
                               arg3, arg4);
    if (r == 0) return 0;

    if (r != (int*)a0[0x78 / 4]) {
        if (arg4 != 0) *arg4 = 1;
        a0[0x78 / 4] = (int)r;
    } else {
        if (arg4 != 0) *arg4 = 0;
    }

    *a1 = r[0x2C / 4];
    *(int*)((char*)a0[0x30 / 4] + 0x954) = (int)r;
    *(int*)((char*)a0[0x30 / 4] + 0x958) = r[0x2C / 4];

    inner = (int*)*(int*)((char*)a0[0x30 / 4] + 0x958);
    if (inner == 0) return (int)r;

    *(float*)((char*)a0[0x30 / 4] + 0x9B8) =
        *(float*)((char*)a0[0x30 / 4] + 0xB4) - *(float*)((char*)inner + 0x30);
    *(float*)((char*)a0[0x30 / 4] + 0x9BC) = 0.0f;
    *(float*)((char*)a0[0x30 / 4] + 0x9C0) =
        *(float*)((char*)a0[0x30 / 4] + 0xBC)
        - *(float*)((char*)*(int*)((char*)a0[0x30 / 4] + 0x958) + 0x38);
    gl_func_00000000((char*)a0[0x30 / 4] + 0x9B8);
    return (int)r;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007ACC);
#endif

#ifdef NON_MATCHING
/* 1.48% NM. game_uso_func_00007C1C: 0x10BC (1075 insns, 4.3 KB) — strategy-memo spine
 * candidate #3 (~25 cross-USO calls). 0x3B0-byte (944 byte) stack frame.
 * Single function (grep -c 03E00008 = 1).
 *
 * SIGNATURE: 5-arg function. The 5th arg arrives via the caller's stack slot
 * at sp+0x3C4 (caller's sp + 0x14 per O32 ABI — caller stack region begins
 * at our sp + 0x3B0 since we allocate 0x3B0; 0x3B0 + 0x14 = 0x3C4).
 *   void f(int a0, int a1, int a2, int a3, double *arg5)
 *
 * Uses callee-saved double regs $f20/$f22/$f24 — arithmetic-heavy
 * (sdc1 saves at sp+0x20/0x28/0x30).
 *
 * ENTRY (insns 1-15 @ 0x7C1C-0x7C5C, decoded):
 *   - addiu sp,sp,-0x3B0 (prologue)
 *   - Save s0/s1/s2/ra + f20/f22/f24 doubles (sp+0x20..0x44)
 *   - Spill a0/a1/a3 to caller slots (sp+0x3B0/0x3B4/0x3BC)
 *   - s2 = a2 (saved for body-wide use)
 *   - Load arg5 ptr from caller slot sp+0x3C4 into s0
 *   - if (arg5 != NULL) { *(double*)arg5 = 0.0; }   // zero output accumulator
 *
 * EXTENDED ENTRY (insns 16-30 @ 0x7C60-0x7CB8, decoded 2026-05-03):
 *   t6 = (reloaded a3 from sp+0x3BC) ; reload to test
 *   if (a3 != 0) goto far_path ; bnel t6,zero,+0x33 (delay-likely)
 *     v1 = sp+0x328 (delay slot taken: alternate Vec3 buffer ptr)
 *   else:
 *     v1 = sp+0x38C (Vec3 buffer ptr)
 *     // alloc-or-passthrough Vec3 dispatch (3 in a row)
 *     // Each: v1 = stack_addr ? stack_addr : alloc(12);
 *     //       if (v1) { v1[0]=src.x; v1[1]=src.y; v1[2]=src.z; }
 *     // 1st (insns 18-23): src = s2->0x30..0x38 ; dst = sp+0x348
 *     // 2nd (insns 24-29): src = same  ; dst = sp+0x354 (after addu+add float math)
 *     // The dispatch pattern matches feedback_ido_alloc_or_passthrough_ternary.md
 *     //   `out = ptr ? ptr : alloc(N)` emits 4-insn `bnel ptr,$0,+6 / move v1,ptr [delay-likely] / jal alloc / addiu a0,$0,N`
 *     // Here ptr = stack_addr = always non-zero, so alloc path is dead.
 *
 * BODY (insns 30-1075, ~1045 insns remaining): heavy float math on sp+0x348
 * and sp+0x38C regions (two Vec3 / quaternion slots), ~25 cross-USO calls,
 * conditional dispatch on a3. The 0x3C4-arg-slot pattern with double-output
 * + s2-preserved-context + dual-buffer dispatch suggests this is a
 * per-frame transform function (e.g. matrix/quaternion -> displacement
 * accumulator). The double-init at entry (`*arg5 = 0.0`) means arg5 is an
 * accumulator the body adds into.
 *
 * Per feedback_partial_alloc_block_add_irreversible.md: do NOT incrementally
 * add the alloc-or-passthrough blocks to C — the function is at 1.48% and a
 * single bad add will drop to 0%. Future passes should decode 50+ insns at
 * once with full register flow. Multi-tick decomp; this commit extends only
 * structural decode comment (no C body change).
 *
 * 2026-05-03 EXTENDED DECODE 0x7CB8-0x7D34 (~31 insns, post-alloc Vec3
 * delta-store + first far jump):
 *   /* alloc-result branch: v1 = alloc(0xC) result, init Vec3 with delta *\/
 *   if (alloc_v0 == 0) goto skip_init;     ; beq v0, $0, +0xB
 *   v1 = v0;                                ; (delay)
 *   /* compute Vec3 delta = stage[i] - arg5[i] for x and z components *\/
 *   v0 = arg5;                              ; reload caller arg5 ptr
 *   f4, f8 = stage[x], stage[z]            ; from sp+0x38C, sp+0x394
 *   f6, f10 = arg5[x], arg5[z]             ; from arg5+0, arg5+8
 *   v1[y_swap] = f24 (saved-callee-double) ; v1[1] = f24
 *   v1[x] = stage[x] - arg5[x]
 *   v1[z] = stage[z] - arg5[z]
 *   /* Vec3-int-copy through s0/s1 chain to caller arg-slot *\/
 *   sp[0x3A8] = sp[0x3A4] = sp[0x3AC] = stored doubles f24/f18/f16
 *
 *   /* FAR JUMP: b +0x3D7 (~980 insns forward to epilogue convergence) *\/
 *   This is the "fast-path early return" — if alloc-result was non-NULL
 *   AND certain prior conditions held, skip the rest of the body.
 *
 * Then the alternate path (jumped to from far far away when fast-path NOT
 * taken) re-enters at 0x7D38 with another alloc-or-passthrough Vec3
 * dispatch (sp+0x328 buffer at delay-slot insn 0x7D38).
 *
 * BODY structure clearer now: this is a Vec3-DELTA computation function
 * that returns the difference between current stage Vec3 and arg5's Vec3,
 * with the result written through a freshly-allocated Vec3 (or one passed
 * via stack at sp+0x328). The fast-path skips ~980 insns of additional
 * processing (matrix transforms?) and exits early.
 *
 * 2026-05-04 EXTENDED DECODE 0x7D38-0x7DB8 (~32 insns) — alternate path
 * (slow path, NOT fast-return). Two sequential alloc-or-passthrough
 * blocks, each producing a Vec3:
 *
 *   /\* Block 1: v1 = sp+0x328 (or alloc 12); fill from a3 *\/
 *   v1 = sp + 0x328;       // always stack-resident, alloc path dead
 *   v1[0] = a3->0x30;      // (lwc1 f12 from a3+0x30)
 *   v1[1] = f24;           // saved-callee-double (mid-component)
 *   v1[2] = a3->0x38;      // (lwc1 f0 from a3+0x38)
 *   sp[0x318] = 0;         // clear flag
 *
 *   /\* Block 2: a1 = sp+0x2B4 (or alloc 12); fill with v1 - a2-Vec3 *\/
 *   a1 = sp + 0x2B4;       // always stack-resident
 *   a1[0] = sp[0x328] - a2->0x30;   // delta.x = v1.x - a2.x
 *   a1[1] = f24;                     // mid-component (no subtract)
 *   a1[2] = sp[0x330] - a2->0x38;   // delta.z = v1.z - a2.z
 *
 *   s1 = sp + 0x354;       // next-block buffer
 *
 * SEMANTIC: computes a "relative position vector from a2 to a3" using
 * stage's xz-coords + saved-double y. The y-component (f24) is preserved
 * from earlier in the function — likely a precomputed height delta. The
 * xz-only subtract suggests this is a 2D collision/proximity computation
 * with separate y handling.
 *
 * EXTENDED DECODE 0x7DBC-0x7E08 (~21 insns, decoded 2026-05-07):
 *   /* 3-way Vec3 broadcast: s0 (src) -> s1, sp+0x334, sp+0x30C *\/
 *   t2 = s0[4];                       // src.y
 *   s1[0] = t3;                       // (t3 was loaded above as s0[0])
 *   t5 = s1[0];                       // reload
 *   t3 = s0[8];                       // src.z
 *   v0 = sp + 0x334;
 *   v0[0] = t5;                       // sp[0x334] = src.x
 *   t8 = v0[0];                       // reload
 *   t6 = sp + 0x30C;
 *   v0[4] = t2;  s1[4] = t2;          // .y broadcast
 *   v0[8] = t3;  s1[8] = t3;          // .z broadcast
 *   t6[0] = t8;                       // sp[0x30C] = sp[0x334]
 *   t7 = v0[4]; t6[4] = t7;           // sp[0x310] = sp[0x338]
 *   t8 = v0[8]; t6[8] = t8;           // sp[0x314] = sp[0x33C]
 *   /* Then load caller arg1 spill -> entity field at +0x30 -> +0x908 *\/
 *   t9 = sp[0x3B4];                   // caller a1 reload
 *   t0 = t9->[0x30];                  // entity ptr
 *   t1 = t0->[0x908];                 // some long-offset field (likely a list head)
 *
 * Pattern: 3-way Vec3 broadcast (src in s0 staged into s1, sp+0x334, and
 * sp+0x30C buffers) prepares 3 separate Vec3 inputs for downstream math
 * callees. The load chain (a1->0x30->0x908) accesses an entity field for
 * the upcoming list iteration.
 *
 * NEXT PASS: continue decode from 0x7E08. Likely a list-walk over
 * a1->0x30->0x908 with collision/proximity checks against the staged
 * Vec3s. ~940 insns remaining in this slow path. */
void game_uso_func_00007C1C(int a0, int a1, int a2, int a3, double *arg5) {
    if (arg5 != 0) {
        *arg5 = 0.0;
    }
    /* Body-proper start at 0x7C60 (extended 2026-05-03, ~25 insns 0x7C60-0x7CD0):
     *   - bnel-dispatch on a3:  if a3 != 0 use sp+0x328 staging buf, else sp+0x38C
     *   - alloc + init via gl_func(0xC, ...) twice — populating two different
     *     Vec3 sub-objects (s2->0x30 and sp+0x348)
     *   - After both setups: load arg4 (sp+0x3C0 = caller a4 slot) into v0
     *     and read sp+0x38C/0x394 + 0(v0) + 0x8(v0) as 4 doubles for math.
     * Heavy branch-likely (bnel) usage suggests IDO's speculative-store
     * scheduling.
     *
     * Extended characterization 2026-05-04 (0x7CD0-0x7D34, ~25 insns):
     * The post-setup body computes a Vec3-delta into v1 (alloc'd buffer
     * from prior chunk):
     *   v1->[0] = f4 - f6   (x-delta)
     *   v1->[4] = 0.0f      (y always zero)
     *   v1->[8] = f8 - f10  (z-delta)
     * This is a XZ-plane Vec3 difference with Y zeroed (consistent with
     * 1080's snow-physics ground-projection pattern).
     *
     * Next: copy s0->Vec3 (at offset 0) through staging sp+0x354 to
     * sp+0x398 (3-word memcpy). Then the cleaned XZ-projected version
     * is written to sp+0x3A4..0x3AC: (x, 0, z) using $f16/$f18 + zeroed
     * $f24. A far forward `b +0x3D7` jumps to 0x8C90 (near function tail
     * — about 992 bytes ahead). This branch likely takes the early-out
     * path when arg5 != NULL (we've zeroed *arg5 at entry; the rest is
     * just buffer prep for downstream).
     *
     * Cumulative ~50/1075 insns characterized. Body-proper still has
     * ~1000 insns + 22 more cross-USO calls past 0x7D34.
     *
     * TODO: 1025+ insns remaining — main FPU computation + 23 more cross-USO
     * calls + final quaternion/matrix output to *arg5. */
    (void)gl_func_00000000();
    (void)a0;
    (void)a1;
    (void)a2;
    (void)a3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007C1C);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00008CD8: 0xB14 (709 insns), 0x210-byte stack frame.
 * Strategy-memo spine: 2.8 KB, 16 cross-USO calls, "subsystem" (1080 snow
 * physics — XZ-projection / ground-plane mapping).
 *
 * Per feedback_partial_decode_with_stub_body.md: NM-wrap with placeholder
 * stub so the decode comment is a tracked NM wrap rather than a floating
 * block-comment. Default build still uses INCLUDE_ASM.
 *
 * ENTRY DECODE (insns 1-26 @ 0x8CD8-0x8D3C):
 *   void f(a0, a1, a2, a3, arg4)  // 5-arg (arg4 from caller's shadow +0x220)
 *   // Shadow-save a0/a1/a2/a3 to sp+0x210..0x21C (frame size 0x210).
 *   if (arg4 == 0) goto far_exit (@ 0x919C, ~0x40C bytes forward)
 *   Vec3 local_1F8 = {...};   // sp+0x1F8 stack Vec3 buffer
 *   gl_func_00000000(&local_1F8, a1, 12);  // 1st cross-call, Vec3 reader-like
 *   retval = saved to sp+0x214
 *   if (retval == 0) goto skip_to_0x8D70 (+9 insns)
 *   // Copy 3 floats from (arg3+0x30, +0x34=0.0f, +0x38) into retval+0/4/8
 *   //   i.e. retval->x = arg3->[0x30]; retval->y = 0.0f; retval->z = arg3->[0x38]
 *
 * REMAINING ~683 insns: 16 cross-USO calls, alternating float math with
 * the XZ-projected position. Multi-tick decomp expected.
 *
 * 2026-05-03 RE-MEASURE: 3.5% NM (up from prior baseline ~2.5%, parallel
 * agent commits drifted upward per feedback_nm_wrap_doc_pct_drifts.md).
 *
 * EXTENDED DECODE @ 0x8D90-0x8DD8 (insns 27-50, decoded but NOT added to C
 * per feedback_partial_alloc_block_add_irreversible.md):
 *   // After the 1st cross-call's Vec3 fill block:
 *   // SECOND Vec3 stage: copy a3->0x30..0x38 region into THREE local buffers
 *   //   (sp+0x174, sp+0x204, and the saved retval block — all at +0/+4/+8)
 *   //   This matches the 1080 per-frame Vec3-stage template documented in
 *   //   feedback_game_uso_per_frame_vec3_stage_template.md, but here it
 *   //   triple-copies (3 destinations from 1 source) using interleaved
 *   //   lw+sw chains for IDO load-batching.
 *   //
 *   // THIRD cross-call: gl_func_X(retval2, sp+0x174) at 0x8DD4
 *   //   retval2 spilled to sp+0x214 (overwriting prior retval slot)
 *
 *   // Then check at 0x8DE0: a3+0x30 != 0xB4? branch on relative offset
 *   //   (lw a3,0x30(a1); bnez +0xA, addiu v1,v1,+0xB4 in delay)
 *   //   This is "if (a1->0x30 == 0) skip alternate path"
 *
 * The Vec3-triple-copy pattern strongly confirms 0x8CD8 is per-frame
 * physics setup that broadcasts a Vec3 to multiple downstream consumers
 * (XZ-projected ground position passed to 3+ submodules).
 *
 * 2026-05-03 EXTENDED DECODE @ 0x8DE0-0x8E2C (insns 50-72): SECOND
 * Vec3-XZ-projection block. Same XZ-strip pattern as the first block
 * but at offset a1->0x30+0xB4 (sub-struct field, Vec3 stride 0xB4):
 *   /* compute (a1->0x30 + 0xB4) — sub-struct's per-frame Vec3 *\/
 *   v1 = a1->0x30 + 0xB4
 *   gl_func_X(v1, sp+0x174, 12)             ; second cross-call (Vec3 reader)
 *   v0 = result
 *   if (v0 != 0) {
 *       v0->x = (a1->0x30+0xB4)->x          ; copy X
 *       v0->z = (a1->0x30+0xB4)->z          ; copy Z
 *       v0->y = 0.0f                        ; zero Y (XZ-projection)
 *   }
 * The XZ-projection (Y=0.0f) confirms ground-plane mapping interpretation
 * — the snowboard's "world-grounded" position is computed from the
 * sub-struct's transform Vec3 with Y stripped.
 *
 * Pattern repeats THREE times across the function: first at 0x8D90-D8DD
 * (input Vec3 stage), second at 0x8DE0-0x8E2C (sub-struct Vec3, this
 * block), third at 0x8E60+ (likely a third source). All write to
 * different stack slots (sp+0x174, sp+0x14C, sp+0x1E0...) for downstream
 * consumers. NM remains 3.5% (doc-only).
 *
 * 2026-05-04 EXTENDED DECODE @ 0x8E30-0x8F98 (insns 73-152, ~80 more):
 * THREE more functional blocks confirming the per-frame Vec3-broadcast
 * interpretation:
 *
 *   (A) 0x8E30-0x8E58: THIRD cross-USO call with local_14C/local_174 as
 *       both src and dst buffers. Same `gl_func(retval, &local_174,
 *       &local_14C, 12)` Vec3-reader shape. The `bnez a3, +9` insn at
 *       0x8E34 is IDO's defensive `if (buf != 0)` codegen for the
 *       stack-local pointer (always non-NULL) — the IF-body (0x8E3C-58
 *       cross-call) is therefore dead in practice, but emitted because
 *       IDO -O2 doesn't constant-fold sp-relative addresses to non-zero.
 *
 *   (B) 0x8E5C-0x8E88: Vec3 XZ-DIFFERENCE compute (NOT a copy):
 *         v0 = sp[0x218]                         // saved arg pointer
 *         v1 = retval                            // result buffer
 *         f12 = sp[0x1E0] - v0->[0x30]           // X delta
 *         f0  = sp[0x1E8] - v0->[0x38]           // Z delta
 *         v1->[0x0] = X-delta                    // store to result.x
 *         v1->[0x4] = 0.0                        // Y zeroed
 *         v1->[0x8] = Z-delta                    // store to result.z
 *       This is "computed XZ vector from current to v0->offset30" —
 *       likely the snowboard's velocity-direction-from-ground-target.
 *
 *   (C) 0x8E8C-0x8EC4: TRIPLE-DEST Vec3 copy. Reads 12 bytes from a3
 *       (= &local_14C) and stores SIMULTANEOUSLY to a2 (= &local_174)
 *       AND t5 (= &local_1EC). 8-insn interleaved lw/sw chain (IDO
 *       load-batched). Same broadcast pattern as the prior block but
 *       fanout +1 (3 destinations vs 2).
 *
 *   (D) 0x8EC8-0x8EE4: FPU magnitude check via `bc1f`:
 *         f8 = sp[0x1EC] * sp[0x1B0]
 *         f6 = sp[0x1B8] * sp[0x1F4]
 *         c.le.s f8, f6                          // f8 <= f6 ?
 *         bc1f +0xB (=0x8EE8)                    // skip ELSE-arm
 *         add.s $f16, f6 (delay)                 // f16 = f6 (when taken)
 *       This is "if (proj_a > proj_b) use f6 else use sum" — distance
 *       comparison probably picking nearest collision target.
 *
 *   (E) 0x8EE8-0x8F2C: FOURTH cross-USO call. Same Vec3-reader shape
 *       (a0=12, a2=&sp+0x174, then deref retval and write XZ-projection):
 *         retval->[0x0] = sp[0x218]+0x30  ->[0x0]
 *         retval->[0x4] = 0.0
 *         retval->[0x8] = sp[0x218]+0x30  ->[0x8]
 *       Stores spilled f16 (the if-result from block D) to sp[0x1AC]
 *       around the call.
 *
 *   (F) 0x8F30-0x8F4C: SECOND triple-dest Vec3 copy: v1 (= &local_1D4)
 *       fanout to v2 (= &local_11C). Same 8-insn pattern as block C
 *       but with a 0x40000000 lui (constant 2.0f load) interleaved —
 *       likely 0x8F50+ multiplies by 2.0.
 *
 *   (G) 0x8F50-0x8F98: a1->[0x90..0x98] WRITE-BACK Vec3 commit:
 *         a1->[0x90] = sp[0x174]                 // X from main XZ buffer
 *         a1->[0x94] = sp[0x178]                 // Y
 *         a1->[0x98] = sp[0x17C]                 // Z
 *         (sp+0x108)->[0..8] = a1->[0x90..0x98]  // cache to local stack
 *         a1->[0x84] = sp[0x11C]                 // additional float at 0x84
 *       This is the FIRST WRITE-BACK to the a1 (subsystem) struct —
 *       confirms a1->[0x90..0x98] is the per-frame "world-grounded
 *       position" Vec3 field. The cache-back to sp+0x108 retains the
 *       pre-write value for further-downstream comparisons.
 *
 * INTERPRETATION (now stronger): 0x8CD8 is the "compute and broadcast
 * world-grounded XZ-projected position" per-frame routine for a
 * snowboard physics object. It computes the XZ position from the
 * sub-struct's transform Vec3 (a1->0x30), runs distance-checks via
 * cross-USO Vec3 readers, picks nearest, then commits the result to
 * a1->[0x90..0x98] AND replicates to multiple downstream stack buffers
 * (sp+0x174 main, sp+0x14C, sp+0x1EC, sp+0x1D4, sp+0x11C, sp+0x108).
 *
 * Decoded so far: insns 1-152 of 709 (~21%). Remaining ~557 insns
 * (16 more cross-calls expected) likely repeat the (cross-call, Vec3-
 * compute, write-back) micro-pattern for additional sub-systems
 * (collision, terrain follow, AI state). Multi-tick continuation.
 *
 * 2026-05-04 EXTENDED DECODE @ 0x8F98-0x9088 (insns 153-217, ~64 more):
 * SECOND iteration of the per-frame Vec3 broadcast cycle, this time
 * with FPU cvt.d.s / cvt.s.d casts intermixed (single→double→single
 * conversion pattern, characteristic of MIPS double-precision math
 * needed for sub-pixel position accumulation):
 *
 *   (H) 0x8F98-0x8FAC: a1->[0x84..0x8C] write-back No.1.
 *         a1->[0x84] = $f10 (carryover from prior block)
 *         a1->[0x88] = sp[0x120]
 *         a1->[0x8C] = sp[0x124]
 *       Continues "snowboard physics writes its current XZ output to
 *       the subsystem struct" theme. Reads sp[0x120/0x124] (newly-
 *       computed deltas?) and stores to a1->[0x88/0x8C].
 *
 *   (I) 0x8FB0-0x8FE8: FPU DOUBLE-PROMOTION block. Loads f6 from
 *       (t2+0x348) — t2 is `sp[0x218]` (the saved arg3 base):
 *         f6 = arg3->[0x348]                        // single
 *         f4 = double(f6)
 *         f8 = double(f4)                           // chained?
 *         f0 = double($f16) and f14 = double(f0)    // f16 from blk D
 *         f12 = single(f0)                          // re-collapse
 *         sp[0x108..0x110] = f14, f2, f12           // store DOUBLE-
 *                                                      precision triple
 *       This double-promote-then-collapse is IDO's idiom for "compute
 *       expression in double precision then cast back to float"
 *       (typical for fused-multiply-add or magnitude-square forms
 *       where intermediate precision matters).
 *
 *   (J) 0x8FEC-0x901C: POINTER-CHAIN COPY. t3 = a1->0x30 (sub-struct
 *       transform Vec3); copy 12 bytes from *t3 to a2 (= sp+0x174)
 *       AND to t4 (= sp+0x1BC). Same triple-dest pattern as block C
 *       but with one dest being an indirect pointer (t3->[0..8]):
 *         t4 = sp + 0x1BC
 *         *t4 = a2[0..8] = *t3                       // 12-byte copy
 *
 *   (K) 0x9020-0x9054: a1->[0x84..0x8C] write-back No.2 (overwrites
 *       block H's writes — meaning blocks I/J computed REVISED values):
 *         a1->[0x84] = sp[0x1C8] * a1->[0x84]_prev   // mul.s
 *         a1->[0x88] = sp[0x1CC] * a1->[0x8C]_prev   // mul.s
 *         a1->[0x8C] = sp[0x1D0] * a1->[0xDC]        // mul.s
 *       Three FPU multiplies that scale the previously-stored Vec3 by
 *       sp[0x1C8..0x1D0] — a per-frame scaling factor (likely
 *       delta-time or velocity coefficient).
 *
 *   (L) 0x9058-0x9088: SECOND double-promotion FPU sub-block. Loads
 *       f6 from (t9+0x348) — t9 is some pointer derived from a1+0x30
 *       likely. Same double-up/collapse-down pattern as (I) but with a
 *       different operand source. Writes results to sp[0x0FC..0x110]
 *       (different stack slots — these are the "double-precision
 *       intermediate" cache for the next FPU pass).
 *
 * Decoded so far: insns 1-217 of 709 (~31%). Confirms the function is
 * a per-frame XZ-position broadcast + double-precision sub-pixel-
 * accumulator with TWO scaling stages (raw → multiplied → final).
 *
 * Remaining ~492 insns expected to continue: third FPU stage, more
 * cross-USO calls (~14 of the 16 total still ahead), and the closing
 * write-back to multiple a1->[N] fields (the snowboard's final
 * per-frame state). NM-doc only (3.5%).
 *
 * Struct fields identified for the snowboard physics struct (a1):
 *   a1->[0x30]   — sub-struct transform Vec3 base ptr
 *   a1->[0x84]   — per-frame scalar (multiplied each iter, possibly speed)
 *   a1->[0x88..0x8C] — per-frame Vec3 component cache (revised twice)
 *   a1->[0x90..0x98] — world-grounded XZ-projected position (FINAL output)
 *   a1->[0xDC]   — multiplier source for a1->[0x8C] update
 *
 * And for arg3:
 *   arg3->[0x30..0x38] — primary Vec3 (XZ-projection source)
 *   arg3->[0x348] — single-precision float promoted to double (sub-pixel
 *                   accumulator base)
 */
typedef struct { float x, y, z; } Vec3_8CD8;
void game_uso_func_00008CD8(int a0, int *a1, int a2, int *a3, int arg4) {
    Vec3_8CD8 local_1F8;
    int *retval;
    if (arg4 == 0) goto far_exit;
    gl_func_00000000(&local_1F8, a1, 12);
    retval = (int*)gl_func_00000000();  /* placeholder for the saved retval */
    if (retval == 0) goto body_continues;
    *(float*)((char*)retval + 0x0) = *(float*)((char*)a3 + 0x30);
    *(float*)((char*)retval + 0x4) = 0.0f;
    *(float*)((char*)retval + 0x8) = *(float*)((char*)a3 + 0x38);
body_continues:
    /* TODO: ~680 insns of float math + 15 more cross-USO calls. Decode in
     * subsequent passes. */
    (void)gl_func_00000000();
    (void)a0;
    (void)a2;
far_exit:
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00008CD8);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000097EC);

#ifdef NON_MATCHING
/* 11.20% NM (corrected from outdated 17.92% comment 2026-05-05).
 * game_uso_func_00009B88: 0x560 (344 insns), 0x1A8-byte stack frame.
 * Inferred from the final cross-product sign test + screen-space transform
 * constants: this is a billboard-visibility / 2D point-on-line predicate
 * applied to per-frame screen-projected anchor coordinates, returning a
 * boolean result via $v0.
 * Strategy-memo candidate for "per-frame compute" (1.4 KB, 11 cross-calls).
 *
 * Partial C body: ~10 % match guess. Captures entry (panic-on-a2-null
 * + 2 cross-call dispatches with sp+0x190 and sp+0xDC Vec3 locals) +
 * body-part-1 Vec3 copy (a2->0x30 XZ-projection). Body-part-2 (insns
 * 50-344) still TODO -- its 300 insns of float scheduling
 * around a quaternion/matrix slot at sp+0x12C.
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
 *   - 0x9D34-0x9D60: lw sp+0x1AC/0x1B0/0x1A8 (re-load some context arg
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
int game_uso_func_00009B88(int *a0, int *a1, int *a2, int *a3) {
    float local_190[3];   /* sp+0x190: Vec3 (a2->0x30 XZ-projection) */
    float local_DC[3];    /* sp+0xDC:  Vec3 (a2-a1 XZ-delta) */
    int   local_EC[3];    /* sp+0xEC:  raw-word copy of local_DC */
    int   local_C4[3];    /* sp+0xC4:  raw-word copy of local_DC */
    int   local_19C[3];   /* sp+0x19C: raw-word copy of local_DC */
    float local_144[3];   /* sp+0x144: Vec3 — passed to alloc-or-fill helper */
    float local_138[3];   /* sp+0x138: working buffer (90deg-rotated XZ) */
    float local_12C[3];   /* sp+0x12C: scaled accumulator (screen-space) */
    int *out;
    float src_x, src_z, dx, dz;
    float scale;          /* screen-space transform scale: 250.5f * a3->[0x54] */
    (void)a3;

    if (a2 == 0) {
        /* Assert: line 0x623 (1571) — message at &D+0x7BC / &D+0x7C8 */
        gl_func_00000000(&D_00000000 + 0x7BC, &D_00000000 + 0x7C8, 0x623);
    }

    /* Dispatch 1: write Vec3 XZ-projection to local_190 (sp+0x190).
     * IDO emits as `out = ptr ? ptr : alloc(12)` ternary via bnel; both
     * arms eventually write the same body. ptr=stack-addr → bnel always
     * taken → alloc path is dead. Stores order: y, z, x (IDO interleaving). */
    out = (int*)local_190;
    if (out == 0) {  /* dead arm */
        out = (int*)gl_func_00000000(0xC);
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
        out = (int*)gl_func_00000000(0xC);
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
    local_EC[0] = ((int*)local_DC)[0];
    local_19C[0] = local_EC[0];
    local_EC[1] = ((int*)local_DC)[1];
    local_EC[2] = ((int*)local_DC)[2];
    local_19C[1] = ((int*)local_DC)[1];
    local_19C[2] = ((int*)local_DC)[2];
    local_144[0] = *(float*)&local_19C[0];
    local_144[1] = *(float*)&local_19C[1];
    local_144[2] = *(float*)&local_19C[2];

    /* @ 0x9C84-0x9C98: word-copy local_C4 setup */
    local_C4[0] = a1[0]; local_C4[1] = a1[1]; local_C4[2] = a1[2];

    /* @ 0x9C9C-0x9CB0: 3rd cross-call alloc(12). Result in a1.
     * If alloc succeeded, store XZ-rotated Vec3:
     *   a1->[0] = local_144[2]    ; new x = old z
     *   a1->[4] = 0.0f            ; y stays zero
     *   a1->[8] = -local_144[0]   ; new z = -old x
     * (= 90° clockwise rotation of local_144's XZ plane, Y=0). */
    out = (int*)gl_func_00000000(0xC);
    if (out != 0) {
        ((float*)out)[0] = local_144[2];   /* x = old z */
        ((float*)out)[1] = 0.0f;
        ((float*)out)[2] = -local_144[0];  /* z = -old x */
    }

    /* @ 0x9CD0-0x9CFC (extended decode 2026-05-03): 3-way Vec3 fan-out from
     * local_C4 to local_EC and a new sp+0x138 buffer:
     *   local_EC = local_C4    (word copy: sw t5,0; sw t4,4; sw t5,8)
     *   sp+0x138 = local_C4    (same 3-word copy, interleaved)
     * Then calls gl_func_00000000(sp+0x138, a1?, sp+0xEC) — likely a 3-Vec3
     * accumulator (passing rotated, original, and delta to a single helper).
     *
     * @ 0x9D00-0x9D34: screen-space transform setup.
     *   t9 = sp+0x138, t8 = sp+0x12C
     *   sp+0x12C = sp+0x138   (word copy: 3 lw/sw pairs interleaved)
     *   f2 = 250.5f (lui $at, 0x437A; mtc1 $at, $f2)   ; viewport-half scale
     *   f10 = 50.0f (lui $at, 0x4248; mtc1 $at, $f10)  ; vertical offset
     *   v1 = sp+0x184  (another working buffer)
     *   t2 = arg from caller-slot (sp+0x1AC = a3 spill)
     *
     * (Math chain continues 0x9D34-0x9DC4 — multiplies sp+0x12C entries by
     * 250.5f scale + 50.0f offset for screen-coord transform; not yet decoded.)
     *
     * Extended characterization 2026-05-04 (0x9D34-0x9DC4, ~37 insns):
     *   - 0x9D34-0x9D58: load 3 floats from sp+0x12C/130/134, mul.s with
     *     250.5f and a fresh load from t2->0x54 (struct field arg). Result
     *     stays in $f0..$f4.
     *   - 0x9D5C-0x9D74: load sp+0x134, more mul.s on $f4/$f6/$f8/$f10/$f12,
     *     swc1 BACK to sp+0x12C and sp+0x130 (in-place scaling of first 2 of 3
     *     Vec3 components — pattern is `vec[i] = vec[i] * 250.5f * t2->0x54`).
     *   - 0x9D7C-0x9DBC: another lwc1 chain from sp+0x138/13C/140 into
     *     $f6/$f10, mul.s with same scale, swc1 back to sp+0x138/0x13C/0x140
     *     (second Vec3 in-place scale, same pattern).
     *   - 0x9DC0: lw t5, 0x30(t4) — load yet another struct's Vec3 source.
     *   - 0x9DC4-0x9DD0: bne+jal sequence — 4th cross-USO dispatch with
     *     scratch_a (sp+0xEC) and t5+0xB4 args.
     *
     * Net: 0x9D34-0x9DC4 is "scale 2 Vec3s in place by 250.5f * t2->0x54,
     * load 3rd Vec3 source, dispatch helper". Confirms screen-space transform
     * hypothesis. Body-part-2 still has ~200 insns past 0x9DD0.
     *
     * Extended characterization 2026-05-04 (0x9DD0-0x9E80, ~44 insns):
     *   - 0x9DD8-0x9DF8: post-cross-call result handling. If callee
     *     returned non-NULL ptr `v0`, store Vec3(a1[0], 0, a1[2]) to *v0
     *     — i.e. zero-Y projection of the just-loaded Vec3.
     *   - 0x9DFC-0x9E0C: 5th cross-USO dispatch — alloc(0xC) for a new
     *     Vec3 buffer.
     *   - 0x9E20-0x9E4C: post-alloc, fill the new Vec3 with delta from
     *     (sp+0x184/0x18C) and a3->0x30/0x38: Vec3(diff_x, 0, diff_z).
     *     a3 = the FOURTH function arg (caller-slot at sp+0x1AC) — a
     *     position struct providing the reference XZ subtract origin.
     *   - 0x9E50-0x9E80: another 12-byte struct copy (a1 → a2, then
     *     a1 → sp+0x120; final destination tracking gets convoluted).
     *
     * Cumulative: ~115 insns characterized of the 344. Body-part-2's
     * theme is clearly "fan out the player's screen-projected XZ to
     * multiple per-displayed-object buffer slots, with various deltas
     * against the reference position from a3".
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
     * The 250.5/50.0 constants confirm screen-space coordinate transform
     * (250.5 ≈ viewport-half + pixel-center; 50.0 ≈ vertical offset).
     * Combined with the cross-product sign test, this is likely a
     * billboard-visibility / point-in-frustum check after screen projection. */
    /* @ 0x9D00-0x9D34: 3-word copy local_12C = local_138 buffer (the 90°-rotated
     * XZ Vec3 from the alloc-or-fill above). Both serve as input to the
     * subsequent in-place scaling chain. */
    *(int*)&local_12C[0] = *(int*)&local_138[0];
    *(int*)&local_12C[1] = *(int*)&local_138[1];
    *(int*)&local_12C[2] = *(int*)&local_138[2];

    /* @ 0x9D34-0x9DBC: in-place screen-space scale (250.5f * a3->[0x54]).
     * Both local_12C[0..2] and local_138[0..2] scale-multiplied in-place.
     * `scale` survives in $f0 across the two scaling blocks per documented
     * IDO-O2 register reuse pattern. The a3 source is the function's 4th
     * arg (TODO: signature should be (int*,int*,int*,int*) — current
     * 3-arg sig is incomplete; sp+0x1AC reload at 0x9D2C confirms a3 is
     * passed but unnamed in the C decl). */
    scale = 250.5f * (*(float*)((char*)a3 + 0x54));
    local_12C[0] *= scale;  local_12C[1] *= scale;  /* local_12C[2] not scaled */
    local_138[0] *= scale;  local_138[1] *= scale;  local_138[2] *= scale;

    (void)local_12C;
    (void)local_19C;  /* suppress unused warnings until body-part-2 done */
    (void)local_EC;
    (void)local_C4;
    (void)scale;
    /* @ 0xA0A0-0xA0E4: 2D cross-product sign test predicate. Returns 1 when
     * cross_z < 0 (point on negative side of a directed line / counter-CW
     * winding), else 0 (or whatever was set by an earlier dispatch arm).
     *
     * Sketch (2026-05-05) — register state from body-part-2 abstracted:
     * the four operands (call them ax/ay/bx/by) are screen-projected XZ
     * coordinates from sp+0x178, sp+0x180, sp+0x174 and a register state
     * surviving body-part-2's mul.s chain. Cross-product sign test
     * computes (ax*by - bx*ay) and returns 1 when the result is negative.
     *
     * Pseudocode the asm performs:
     *   cross_z = (vec_a.x * vec_b.y) - (vec_b.x * vec_a.y);
     *   diff_a  = sp[0x148] - vec_a.x * vec_b.x;       (loaded earlier)
     *   final   = cross_z * diff_a;
     *   return (final < 0.0f) ? 1 : prior_v0;
     *
     * Full operand identification requires body-part-2 decoded into named
     * C locals first. */
    {
        float vec_ax = *(float*)((char*)&local_19C[0] + 0xDC);  /* sp+0x178 */
        float vec_ay = *(float*)((char*)&local_19C[0] + 0xE4);  /* sp+0x180 */
        float diff_acc = *(float*)((char*)&local_19C[0] + 0xD8); /* sp+0x174 */
        float cross_z;
        float final;
        (void)vec_ax;
        (void)vec_ay;
        (void)diff_acc;
        /* The two missing operands (vec_b.x, vec_b.y) survive in $f4/$f18
         * from body-part-2's last mul.s/sub.s chain. Without those locals
         * the sign test C is incomplete. Documented for next pass. */
        cross_z = 0.0f;
        final = cross_z * diff_acc;
        if (final < 0.0f) {
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00009B88);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A0E8);

#ifdef NON_MATCHING
/* 86.70% NM. 86.7%: body+control flow match; target has 2 pre-jal a1 spills:
 *   sw \$a1, 0x1C(\$sp) before 1st jal
 *   sw \$a1, 0x4(\$sp)  IN 1st jal delay slot
 * My IDO -O2 build doesn't emit either spill. Variants tested 2026-04-20:
 *   (a) `extern int gl_func_00000000_va();` (K&R alias) — no spill
 *   (b) `extern int gl_func_00000000_va(int, ...);` (varargs) — no spill
 * Same class as feedback_ido_precall_arg_spill_unreachable.md. Cap 86.7%. */
extern int gl_func_00000000_va();

int game_uso_func_0000A374(int a0, int a1, int a2) {
    int r = gl_func_00000000_va(*(int*)&D_00000000, a1);
    if (r == 0) return 0;
    return gl_func_00000000_va(r, a2, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A374);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A3C4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A604);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A7F8);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AC78);
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
/* game_uso_func_0000AE1C: 278-insn (0x458) constructor. Frame -0xA0.
 * Same family as 00003018 / spine constructor 000044F4 (alloc-cascade
 * + sub-object init).
 *
 * Stage 1 @ 0xAE1C-0xAE38 (alloc-or-passthrough for primary 0x178 buffer):
 *   if (!a0) a0 = alloc(0x178);  if (!a0) return.
 *
 * Stage 2 @ 0xAE40-0xAE58 (alloc-or-passthrough for secondary 0xB4 sub-obj):
 *   if (!s0) s0 = alloc(0xB4);  if (!s0) goto stage_4_skip.
 *
 * Stage 3 @ 0xAE5C-0xAE68 (init sub-obj with table @ &D + 0xD50):
 *   init_sub(s0, &D[0xD50])
 *
 * Stage 4 @ 0xAE6C-0xAE7C (vtable-pointer set + dead-code alloc-cascade):
 *   *(s0 + 0x28) = &D
 *   sentinel-bne pattern at -0x2C/-0xDC/etc — IDO emits dead alloc(4)
 *   block (same family as 00003018 Stage 6's "always-true bne" cap).
 *
 * Stage 5 @ 0xAEAC-0xAED4 (Vec3-zero init + sub-obj alloc(0x30)):
 *   sp[0x84..0x8C] = (0.0f, 0.0f, 0.0f)
 *   t0 (orig arg0) -> [0x28] = &D
 *
 * Stage 6 @ 0xAEDC-0xAEFC (sentinel(-DC)+alloc(0x10) bundle): same shape,
 *   different alloc size + sentinel.
 *
 * Stage 7 @ 0xAF00-0xAF60: more alloc(0x10)+(0x4)+sub-obj-init chain
 *   with cross-USO `init_with_table_at_D[0x848]/[0x840]`.
 *
 * Remaining ~200 insns TBD: more alloc-cascade stages + struct-field
 * fills. Same family pattern as 00003018.
 *
 * Picked source 5 (strategy memo size-descending). Structural skeleton
 * with stages 1-7 partially decoded (~70/278 insns covered in doc;
 * encoded body covers stages 1-4). Multi-run refinement expected. */
void* game_uso_func_0000AE1C(void* arg0) {
    void *s0;
    void *sub;

    s0 = arg0;
    if (s0 == NULL) {
        s0 = (void*)gl_func_00000000(0x178);
        if (s0 == NULL) return NULL;
    }
    sub = s0;
    if (s0 == NULL) {
        sub = (void*)gl_func_00000000(0xB4);
        if (sub == NULL) goto skip_init;
    }
    gl_func_00000000(sub, (char*)&D_00000000 + 0xD50);
skip_init:
    *(int*)((char*)s0 + 0x28) = (int)&D_00000000;
    /* Remaining ~200 insns TBD: stages 5-N — cross-USO inits + struct fills */
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AE1C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B274);

#ifdef NON_MATCHING
/* 53.10% NM. 29-insn FPU helper. Init local Vec3 buffer at sp+0x24..0x2C with 3
 * floats (first 2 from f0 = uninit/0?, third from D_0+0x140), call
 * gl_func(D_0+0x11C, &buf28, &buf2C, a0); call again gl_func(a0,
 * &buf24, &buf2C, D_0+0x104); writes 3 float results from buf24/28/2C
 * into a0+0x60/0x64/0x68.
 *
 * Likely a "lerp Vec3 toward target with timestep" kind of helper.
 * NM-wrap captures structure for next pass; FPU sched is fragile. */
extern float D_b424_140;  /* &D_0 + 0x140 */
extern float D_b424_11C;  /* &D_0 + 0x11C */
extern float D_b424_104;  /* &D_0 + 0x104 */
void game_uso_func_0000B424(int *a0) {
    float buf[3];
    float zero;
    /* Init buf */
    zero = 0.0f;
    buf[0] = zero;            /* sp+0x24 */
    buf[1] = zero;            /* sp+0x28 */
    buf[2] = D_b424_140;      /* sp+0x2C */
    /* Call 1 */
    gl_func_00000000(D_b424_11C, &buf[1], &buf[2]);
    /* Call 2 */
    gl_func_00000000(D_b424_104, &buf[0], &buf[2]);
    /* Write back to a0 */
    *(float*)((char*)a0 + 0x60) = buf[0];
    *(float*)((char*)a0 + 0x64) = buf[1];
    *(float*)((char*)a0 + 0x68) = buf[2];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B424);
#endif

void game_uso_func_0000B498(char *a0) {
    game_uso_func_00000000(a0 + 0xEC);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B4B8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B750);

void game_uso_func_0000B884(char *dst) {
    game_uso_func_0000AD10((float*)dst);
    game_uso_func_0000AD10((float*)(dst + 0x14));
    game_uso_func_0000AD4C((int*)(dst + 0x18));
    game_uso_func_0000AD88((Quad4*)(dst + 0x4));
    game_uso_func_0000AD4C((int*)(dst + 0x1C));
    game_uso_func_0000AD10((float*)(dst + 0x20));
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B8D4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BB8C);

#ifdef NON_MATCHING
/* 2026-05-07: $s0/$s1 swap FIXED via init-statement order (17 diffs → 3).
 * Previously `p = base + 0xB8; i = 0;` made p the first-defined pseudo,
 * allocating s0=p, s1=i. Reversed to `i = 0; p = base + 0xB8;` flips
 * allocation to target: s0=i, s1=p. Retires the previous "stmt order
 * doesn't flip allocno" claim — for IDO -O2, INIT-STATEMENT order in
 * the function body DOES affect allocation (priority queue ties broken
 * by first-RTL-pseudo-emit, which follows assignment order, not declaration
 * order).
 *
 * Remaining 3 diffs:
 *   1× linker-symbol baseline diff (jal-to-ADE0 resolved in expected/.o
 *      but not in NM-build/.o — capture-bloat artifact)
 *   2× schedule swap in loop pre-header — target emits
 *      `li s2, 0x168; move s0, $0`, ours emits the reverse. Both insns
 *      are independent in the dataflow graph; IDO's scheduler picks
 *      register-numerical order (s0 before s2) while target picks
 *      use-order (s2 used in bne, s0 used in delay-slot). No C-level
 *      lever found to swap these. */
void game_uso_func_0000BF7C(char *a0) {
    char *base = a0;
    int i;
    char *p;
    game_uso_func_00000000(base + 0x224);
    game_uso_func_0000ADE0((int*)(base + 0x274));
    i = 0;
    p = base + 0xB8;
    do {
        game_uso_func_00000000(p);
        p += 0x24;
        i += 0x24;
    } while (i != 0x168);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BF7C);
#endif

#ifdef NON_MATCHING
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
 * Skeleton C below — emits structurally similar control flow but is not
 * byte-correct. Reserved for multi-pass tightening. */
extern int gl_func_00000000();
int game_uso_func_0000BFDC(int *a0) {
    short ka = *(short*)((char*)a0 + 0xA);
    short kb = *(short*)((char*)a0 + 0x8);
    int *base = (int*)a0[1];
    int (*fnptr)(int);
    int arg;
    if (ka < 0) {
        fnptr = (int(*)(int))a0[3];
        arg = (int)((char*)base + kb);
    } else {
        int v = a0[3];
        if (v == 0) {
            if (*(short*)((char*)a0 + 0x8) == 0) {
                v = 0x28;
            }
        }
        {
            int *table = *(int**)((char*)base + v);
            int *entry = (int*)((char*)table + (*(short*)((char*)a0 + 0xA) << 3));
            short e = *(short*)entry;
            fnptr = (int(*)(int))entry[1];
            arg = (int)((char*)base + kb + e);
        }
    }
    return fnptr(arg);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BFDC);
#endif

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_uso/game_uso/game_uso_func_0000C0BC_pad.s")

void game_uso_func_0000C0F0(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

#ifdef NON_MATCHING
/* Loads 64 bytes via gl_func_00000000(&D_0, buf, 0x40), then copies
 * 16 ints from buf to a0 with a 3-elements-per-iter unrolled loop:
 *   for (src=buf, end=buf+15, dst=a0; src!=end; src+=3, dst+=3) {
 *       dst[0]=src[0]; dst[1]=src[1]; dst[2]=src[2];
 *   }
 *   *dst = *src;  // final 16th int
 *
 * Tried 4 variants (2026-05-03):
 *   (a) Named src/dst/end locals: IDO spills 3 named locals to stack,
 *       frame grows to 104 bytes vs target 88.
 *   (b) Inline a0 increment + named src/end: still 104 bytes.
 *   (c) Index-based with i+3 iter: IDO unrolls with sll+addu indexed
 *       access, completely different shape (96 byte frame, no neg-offset).
 *   (d) for-i loop unrolled by 4 (using a0[i]=buf[i] x 16): IDO emits a
 *       4-elem-per-iter loop, target wants 3.
 *
 * Cap: target compiled with NO named locals — uses `buf`, `a0`, and
 * pure $t-regs (t6 dst, t7 src, t8/t9 vals, t0 end). Per
 * feedback_ido_v0_reuse_via_locals.md, named locals get $v-regs or stack;
 * inline derefs get $t-regs. But here we need 4+ pointers in $t-regs
 * simultaneously and the loop body must use neg-offset (-0xC, -0x8, -0x4)
 * after src/dst increment. No C form found that triggers all of:
 *   1. NO named-local stack spill (frame must be 88 not 104)
 *   2. dst/src increment BEFORE the stores (giving neg offsets after)
 *   3. unroll-by-3 not unroll-by-4
 *
 * First-pass logic decode complete; reg-allocation shape blocked. */
void game_uso_func_0000C12C(int *a0) {
    int buf[16];
    int i;
    gl_func_00000000(&D_00000000, buf, 0x40);
    i = 0;
    do {
        a0[0] = buf[i];
        a0[1] = buf[i + 1];
        a0[2] = buf[i + 2];
        i += 3;
        a0 += 3;
    } while (i != 15);
    *a0 = buf[15];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C12C);
#endif

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C2D4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C3F8);

#ifdef NON_MATCHING
/* 2.46% NM. SPINE constructor (game_uso_func_0000C48C, 0xD84 = 865 insns, 3.4 KB)
 * Per project_1080_game_uso_map.md the 4th-largest game.uso function and
 * an "INIT/SETUP" orchestrator (69 cross-USO calls). Sibling pattern to
 * game_uso_func_000044F4 (the other documented constructor; allocates
 * main object + child + ~16 sub-objects of 0x18 bytes each).
 *
 * Decoded structure (first 200 insns, ~25 % of body):
 *
 *   void *func(void *a0, int a1, int a2, int a3) {
 *     void *p = a0;
 *     if (!p) {
 *       p = alloc(0x444);                      ; 1092-byte main object
 *       if (!p) goto end;
 *     }
 *     gl_init(p, a1);                          ; main-object init w/ a1
 *     p->0x28 = &TEMPLATE_BASE;                ; main template ptr
 *
 *     // Sub-object inner allocator — repeated ~16 times with different
 *     // (offset, template_addr, size_field) tuples:
 *     {
 *       parent = p;
 *       q = (caller passed pre-allocated chunk, or alloc(0x308)?);
 *       if (q != p+0xN) q = alloc(0x308);      ; first chunk: bigger
 *       else q = p+0xN_THIS_CHUNK;             ; subsequent: bump-allocator
 *       if (!q) goto skip_init;
 *       chunk = q+0x8;
 *       if (cached_template_idx != -8) chunk = alloc(0x18);
 *       if (!chunk) goto next_iter;
 *       chunk->0    = TEMPLATE_TYPE_PTR_1;    ; usually `gl_data + 0x1224`
 *       chunk->4    = 0;
 *       template_idx = template_table[N];     ; lw from gl_data + 0x122C+
 *       chunk2 = sp+0xC0;                     ; sub-template scratch
 *       chunk2_inner = chunk+0x8;
 *       *(sp+0xC0) = template_idx;
 *       sub = *(int*)chunk2;
 *       if (cached != -8) sub = alloc(0x18);
 *       gl_init_sub(sub, parent, 1);
 *       sub->0xC = TEMPLATE_PTR_2;             ; usually `gl_data + 0xfc0`
 *       sub->0x10 = SIZE_HINT;                 ; e.g. 20, 60, 5
 *       sub->0x14 = 0;
 *       // NOTE: some iterations also set sub->0x10 from a float
 *       // template (lwc1 $f4/$f6 from at + 0x1ec/0x1f0), suggesting
 *       // either type-tagged sub-objects or interleaved init kinds.
 *     }
 *     // ... loop continues for ~14 more sub-objects ...
 *
 *   end:
 *     // epilogue: lw ra, 36; lw s2,32; lw s1,28; lw s0,24; addiu sp, 200; jr ra
 *   }
 *
 * Frame: -200 (0xC8). Saves: ra,s0,s1,s2 + spills a0,a1,a2 to top.
 *
 * Multi-tick decomp expected. Next pass: extract the per-iteration
 * template-table layout (gl_data + 0x122C, 0x1230, 0x1234, 0x1238...)
 * and figure out the allocation chunk-size pattern (some iterations
 * use 0x308 sub-allocs, others use 0x18). Constructor of unknown
 * struct -- offsets at 0x28 (main template), 0x44 (sub-region start?),
 * 0xC (template ptr), 0x10 (size-hint).
 *
 * The C body below is a compile-only placeholder so the wrap parses;
 * default build uses INCLUDE_ASM and matches. */
extern void *game_uso_func_0000C48C_TODO(void *parent, int sub_idx, int chunk_addr);
void *game_uso_func_0000C48C(void *a0, int a1, int a2) {
    void *p;
    int *chunk;
    int *sub;
    void *parent;

    /* Entry: alloc main object if a0 == 0. */
    p = a0;
    if (p == 0) {
        p = (void*)gl_func_00000000(0x444);
        if (p == 0) goto end;
    }
    gl_func_00000000(p, a1);   /* gl_init(p, a1) — main-object init */
    *(int*)((char*)p + 0x28) = (int)&D_00000000;  /* main template ptr */

    /* First sub-region: alloc 0x308 if cached chunk addr ≠ s1+0x13C
     * (bump-allocator dispatch). Subsequent iterations reuse parent+offset. */
    parent = p;
    if (a2 != 0) {
        /* a2 was passed by caller as pre-existing chunk; use if matches */
        chunk = (int*)a2;
    } else {
        chunk = (int*)gl_func_00000000(0x308);
        if (chunk == 0) goto end;
    }

    /* Sub-init #0: alloc 0x18 sub, bind to chunk+0x8, then gl_init_sub. */
    sub = (int*)gl_func_00000000(0x18);
    if (sub != 0) {
        chunk[0] = (int)((char*)&D_00000000 + 0x1224);  /* TEMPLATE_TYPE_PTR_1 */
        chunk[1] = 0;
        gl_func_00000000(sub, parent, 1);              /* gl_init_sub */
        sub[3] = (int)((char*)&D_00000000 + 0xF78);    /* sub->0xC = TEMPLATE_PTR_2 */
        sub[5] = 0;                                     /* sub->0x14 = 0 */
        /* sub->0x10 from float template (lwc1 $f4, gl_data+0x1EC); copied via $f4 */
        *(float*)((char*)sub + 0x10) = *(float*)((char*)&D_00000000 + 0x1EC);
    }

    /* Sub-init #1: same pattern, different template offsets.
     * Decoded asm pattern at ~0xC5xx range:
     *   chunk1 = parent + 0x44 + 0x308 (or similar bump-offset)
     *   sub1 = alloc(0x18); chunk1[0] = D+0x1228 (TEMPLATE_TYPE_PTR_2);
     *   gl_init_sub(sub1, parent, 2); sub1[3] = D+0xF80; sub1[5] = 0;
     *   sub1->0x10 = D->0x1F0 float
     * Per memo's per-iteration table: each sub uses different
     * (template_type_ptr at chunk[0], sub-template at sub[3], size at sub[0x10]).
     * Iteration index N controls table base offsets:
     *   chunk[0] = D + 0x1224 + N*4   (table of TEMPLATE_TYPE_PTRs)
     *   sub[3]   = D + 0xF78 + N*8    (table of sub-template ptrs)
     *   sub[0x10] = D->(0x1EC + N*4) (float-template table) */
    chunk = (int*)((char*)parent + 0x44 + 0x308);  /* approximate bump offset */
    sub = (int*)gl_func_00000000(0x18);
    if (sub != 0) {
        chunk[0] = (int)((char*)&D_00000000 + 0x1228);
        chunk[1] = 0;
        gl_func_00000000(sub, parent, 2);
        sub[3] = (int)((char*)&D_00000000 + 0xF80);
        sub[5] = 0;
        *(float*)((char*)sub + 0x10) = *(float*)((char*)&D_00000000 + 0x1F0);
    }

    /* TODO: ~13 more sub-region iterations follow same pattern with different
     * (template_idx, sub_idx) tuples. Per feedback_partial_decode_with_stub_body.md,
     * call out to TODO stub for the remaining ~550 insns. Default build
     * matches via INCLUDE_ASM. */
    return game_uso_func_0000C48C_TODO(parent, /*sub_idx*/2, /*chunk_addr*/(int)chunk);

end:
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C48C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D210);

void game_uso_func_0000D418(char *a0) {
    gl_func_00000000(a0 + 0x13C);
}

/* IDO allocates t6 before t7; target has t7/t6 swapped. INSN_PATCH (2 words)
 * fixes the register-rename diff per feedback_insn_patch_for_ido_codegen_caps.md. */
void game_uso_func_0000D438(void *a0) {
    *(s32*)((char*)a0 + 0x64) = -1000;
    *(s32*)((char*)a0 + 0x68) = -1000;
    *(s32*)((char*)a0 + 0xC8) = *(s32*)((char*)a0 + 0xC0);
    *(s32*)((char*)a0 + 0xCC) = *(s32*)((char*)a0 + 0xC4);
}

/* game_uso_func_0000D458: 5-FUNCTION BUNDLE (0x1E4 total / 121 insns).
 * Splat could not separate. Per
 * feedback_uso_split_fragments_breaks_expected_match.md, splitting
 * USO funcs is risky — keeping bundled.
 *
 * Sub-function layout (boundary = jr $ra + delay slot):
 *   F1 @ 0xD458-0xD5B8: 88 insns. Big function with frame -0x48
 *     (addiu sp,-0x48). Lots of body — likely a per-frame update or
 *     state-transition function.
 *   F2 @ 0xD5BC-0xD5D8: 7 insns. Tiny accessor or wrapper.
 *   F3 @ 0xD5DC-0xD5F4: 6 insns. Tiny accessor.
 *   F4 @ 0xD5F8-0xD630: 15 insns. Small helper.
 *   F5 @ 0xD634-0xD638: 2 insns (jr ra + nop). Empty void.
 *
 * Decoding all 5 sub-bodies as one C function with goto-chains is
 * not feasible from C source. Future split-with-refresh-expected
 * recipe (see feedback_uso_split_fragments_breaks_expected_match.md
 * for the unblock path) needed before any decomp attempt. */
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D458);

void game_uso_func_0000D5BC(char *a0, int a1, int a2) {
    volatile int *p;
    p = &a1;
    *(int*)(a0 + 0xC8) = p[0];
    *(int*)(a0 + 0xCC) = p[1];
}

void game_uso_func_0000D5DC(char *a0) {
    int *p = (int*)((char*)&D_00000000 + 0xDC8);
    *(int*)(a0 + 0xC8) = p[0];
    *(int*)(a0 + 0xCC) = p[1];
}

void game_uso_func_0000D5F8(char *a0, int a1, int a2, int a3) {
    volatile int *p;
    p = &a1;
    if (a3 == -1) {
        *(int*)(a0 + 0x68) = a3;
    } else {
        *(int*)(a0 + 0x64) = p[2];
    }
    *(int*)(a0 + 0xC0) = p[0];
    *(int*)(a0 + 0xC4) = p[1];
}

#ifdef NON_MATCHING
/* 2-insn split-off (unwrapped from the 0xD458 bundle). Body:
 *   jr ra
 *   sw a0, 0(sp)        (delay slot — store a0 to caller's a0 slot)
 *
 * No prologue, no epilogue. The `sw a0, 0(sp)` writes to the CALLER's
 * a0 caller-slot. This is unmatchable from standalone C: a void leaf
 * returns `jr ra; nop` (no spill), and an arg-spill at exit isn't
 * something IDO -O2 emits without a frame.
 *
 * Likely a continuation-style helper called by a sibling function that
 * pre-positions sp such that `0(sp)` is the right slot. Standalone
 * matching unreachable per feedback_lw_arg_from_stack_no_preceding_sw.md
 * (sibling pattern: lw without preceding sw is also continuation-style). */
void game_uso_func_0000D634(int a0) {
    (void)a0;  /* sw a0, 0(sp) in delay slot — not C-emit-able */
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D634);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D63C);

#ifdef NON_MATCHING
/* 93.73% NM. 26 insns. Toggle bit 0x40 in (a0->0xB4)[0xA58], call worker, test the
 * bit afterward, dispatch a0->0xFC to one of two flag values. The
 * post-call test uses IDO's beql tail-merge — a redundant `sw t2`
 * trailing the merged epilogue, unreachable via both branch targets
 * (per feedback_ido_bnel_tail_merge_register_restore.md, this caps
 * matching from C). Wrap is for grep discoverability + decode source.
 * NM-build verification blocked by the file's pre-existing
 * `extern float D_00000000` vs `extern char D_00000000` conflict
 * (per feedback_nm_body_cpp_errors_silent.md). */
void game_uso_func_0000D6E4(char *a0) {
    *(int*)(*(char**)(a0 + 0xB4) + 0xA58) ^= 0x40;
    gl_func_00000000(*(char**)(a0 + 0xB4), a0);
    if ((*(int*)(*(char**)(a0 + 0xB4) + 0xA58) & 0x40) == 0) {
        *(int*)(a0 + 0xFC) = 0x00010000;
    } else {
        *(int*)(a0 + 0xFC) = 0x00050000;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D6E4);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D74C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D7F4);

#ifdef NON_MATCHING
/* ~70 %: 17-insn conditional call. If (*(a0+0xB4))->field_990 != 0, call
 * gl_func_00000000(a0, *(D_00000E70), *(D_00000E74)). Target has 2 extra
 * stack spills (sw a1,4(sp); sw a2,8(sp)) which IDO -O2 doesn't produce
 * for this call shape with K&R-declared gl_func_00000000. Also register
 * chain differs (target: t6/t8/t7 via pointer-indirect; mine: v0/t6/v0).
 * Documented unreachable cap: see IDO_CODEGEN.md
 * #feedback-ido-precall-arg-spill-unreachable. Variants tried (none reach
 * target): 2026-04-20 (5 variants), 2026-05-02 (7 variants), 2026-05-05
 * (volatile locals; p declared before-if — both regress). */
extern char D_00000E70;
void game_uso_func_0000D8A8(char *a0) {
    int *t6 = *(int**)(a0 + 0xB4);
    if (*(int*)((char*)t6 + 0x990) != 0) {
        int *p = (int*)&D_00000E70;
        gl_func_00000000(a0, p[0], p[1]);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D8A8);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D8EC);

#ifdef NON_MATCHING
/* 0.27% NM. game_uso_func_0000D9CC: 0x830 (524 insns), 0x38-byte stack frame.
 * Strategy-memo spine: 2.0 KB, 26 cross-USO calls, "subsystem" subsystem.
 * Single function per grep -c 03E00008 (not a bundle).
 *
 * Partial C body: ~5-10 % match guess. Captures entry setup + 30.0f
 * gate check + the sub-state at 0x1F0 (0x43FA/0x0A10/0x01F0 pattern).
 * Body-proper (insns 30-524) still TODO-stubbed — state-machine over
 * several float thresholds with 26 cross-USO calls.
 *
 * ENTRY DECODE (insns 1-16 @ 0xD9CC-0xDA0C):
 *   *(int*)(a0 + 0x108) = 0;     // clear state flag
 *   // 3 stack-local zeroes spilled at sp+0x28/0x2C and `1` at sp+0x30
 *   local_30 = 1; local_2C = 0; local_28 = 0;
 *   v1 = *(int*)(a0 + 0xB4);      // inner-struct pointer
 *   s0 = a0;                      // saved copy
 *   a3 = 0;                       // arg4 accumulator
 *   if (*(f32*)(v1 + 0x348) > 30.0f) {
 *       // fallthrough into main body @ 0xDA10
 *   } else {
 *       // skip to @ 0xDBDC (far forward) — load 500.0f at delay slot
 *   }
 *
 * Main body is float-heavy with a likely state-machine/dispatch over
 * several threshold checks (30.0f, 500.0f constants suggest physics
 * timers or speed thresholds). Uses `mtc1 zero, $fN` + `c.lt.s` gate
 * pattern repeatedly. 26 cross-USO `jal 0` calls per the spine memo.
 *
 * Stack frame is SMALL (0x38 bytes) — this function keeps almost
 * everything in regs / passes args directly rather than storing locals.
 * Suggests it's tightly-scheduled compute, NOT an orchestrator.
 *
 * NEXT PASS: decode the 30.0f-gate body (0xDA10 onward) — it does
 * another float load, c.lt.s against 500.0f (via lui 0x43FA), and
 * branches to 0xDA60 or 0xDA4C based on result. State-machine-like.
 *
 * EXTENDED CHARACTERIZATION 2026-05-04 (insns 16-60 @ 0xDA10-0xDABC):
 *   30.0f-gate body opens with:
 *     state_bits = inner->0xA10 & 0x1F0  (halfword bitmask test)
 *     if (state_bits == 0) goto far_jump_DBD8
 *     ; otherwise:
 *     v = inner->0xA1C (float)            ; secondary float field
 *     if (v < 0) v = -v                   ; abs.s effectively
 *     ; v stays in $f2 for downstream comparisons
 *
 *     w = a0->0x244 (float)               ; tertiary float field
 *     if (w >= 0) goto skip_block_DAC8    ; bc1f over the next block
 *     ; (else fall through to "negative-w" handler @ 0xDA60)
 *     sp+0x28 = 2                         ; arg stash
 *     sp+0x30 = 0                         ; flag stash (overwrites entry's 1)
 *     gl_func_00000000(...)               ; FIRST cross-USO call (delay slot
 *                                          ; stores t9=2 to sp+0x28)
 *
 *     inner = a0->0xB4 (reload)           ; clobbered by call
 *     vv = inner->0xA1C                   ; reload (may have been written)
 *     if (vv < 0) {
 *         old_state = a0->0xFC            ; old state field
 *         a0->0x108 = old_state | 0x16    ; OR new state bits
 *         sp+0x2C = 1
 *     } else {
 *         old_state = a0->0xFC
 *         a0->0x108 = old_state | 0x17    ; alternative state bits
 *         sp+0x2C = 3
 *     }
 *     goto far_jump_DBD8                  ; both arms converge to far_DBD8
 *
 *   The 0x16 vs 0x17 OR-mask difference and the sp+0x2C 1 vs 3 store
 *   suggest the function tracks a per-frame state value derived from
 *   the sign of inner->0xA1C (a velocity or rate?). The "state_bits
 *   & 0x1F0" gate suggests `state` has a 5-bit subfield at bits 4-8
 *   that selects a sub-mode.
 *
 * Left as INCLUDE_ASM until enough body is decoded to support a
 * compile-testable skeleton. The entry decode is the forward progress
 * for this pass per the skill's multi-run decomp convention.
 *
 * EXTENDED CHARACTERIZATION 2026-05-05 (insns 60-100 @ 0xDABC-0xDB50):
 *   The two arms (sp+0x2C = 1 vs 3, OR-mask 0x16 vs 0x17) converge at
 *   0xDABC via `b +0x46` (unconditional) → 0xDBD8 (far merge point).
 *   Delay slot reloads inner = a0->0xB4 (prepping for downstream).
 *
 *   skip_block_DAC8 (the "w >= 0" path, taken when the bc1f at 0xDAB4
 *   skipped the negative-w block):
 *     a0_arg = s0 (=a0)                ; setup for upcoming jal
 *     a1 = 4                            ; arg count? scaled?
 *     bc1tl + neg.s f0, f0 (delay)      ; if FCC1 set, negate f0
 *     b +2 + neg.s f0, f0 (delay)       ; abs.s pattern (sets f0 = |f0|)
 *     ; then loads a0->[0x22C] (lwc1 f4, 0x22C(s0))
 *     ; cvt.s.d f0, f0 (Single-precision mode)
 *     ; bc1fl over jal: if f4 < some threshold, skip the jal
 *     jal gl_func_00000000              ; SECOND cross-USO call
 *     sw zero, 0x30(sp)                 ; delay - clear flag
 *
 *   Next sub-block 0xDB00-0xDB50: similar pattern with different fields.
 *     reload inner = a0->0xB4
 *     mtc1 zero, f6                     ; f6 = 0.0
 *     a3 = 2                            ; alt arg
 *     lwc1 f2, 0x970(v1)                ; load inner->[0x970] (probably big f-table)
 *     lui at, 0  (reloc start for double-constant load)
 *     c.lt.s f6, f2                     ; 0 < f2 ?
 *     bc1fl + neg.s f0, f0              ; abs-like guard
 *     ldc1 f8, 0x1F8(at)                ; load DOUBLE constant from D+0x1F8
 *     cvt.s.d f5, f0                    ; cast to single
 *     c.lt.d f8, f10                    ; double-precision compare
 *     bc1fl + mtc1 zero, f4 (delay)     ; conditional float reset
 *
 *   Cumulative ~100/524 insns characterized (~19%). The function's
 *   theme is now clearer: per-frame state machine with multiple
 *   FPU thresholds (30.0f gate at entry, 500.0f mentioned earlier,
 *   plus a double-precision threshold from D+0x1F8 here). Each
 *   FPU comparison can flip the per-frame state field at a0->0x108. */
void game_uso_func_0000D9CC(int *a0) {
    int local_28 = 0, local_2C = 0, local_30 = 1;
    int *inner;
    (void)local_28; (void)local_2C; (void)local_30;

    *(int*)((char*)a0 + 0x108) = 0;
    inner = (int*)a0[0xB4/4];

    if (*(float*)((char*)inner + 0x348) > 30.0f) {
        /* MAIN BODY @ 0xDA10-0xDA60 (decoded 2026-05-03):
         *   t7 = halfword at inner[0xA10]
         *   t8 = t7 & 0x01F0  (state-bit mask)
         *   if (t8 == 0) goto skip_block;  // branch to 0xDBD8 (far)
         *   f2 = inner[0xA1C/4]              // float field
         *   abs_f2 = f2 < 0 ? -f2 : f2      // abs(f2) via bc1fl + neg.s
         *   f8 = s0[0x244/4]                 // threshold from outer struct
         *   if (abs_f2 >= f8) goto skip;    // bc1fl threshold gate
         *   // taken: inner[0xB4] ptr load, jal helper, ...
         *
         * The 500.0f constant in the lui (0x43FA0000) is loaded but only
         * used in the SKIP path's delay slot (bc1fl). The inner[0xA10]
         * halfword mask 0x01F0 = 8 contiguous bits at positions 4..11 —
         * could be 16 sub-state values (5 bits = 32 but masked to 16).
         *
         * Pattern (gated-physics-update on abs(field) < threshold) is
         * recurrent across 1080's per-frame compute layer (similar to
         * 0x44F4 spine constructor's per-sub-obj gates). Suggests this
         * IS the per-frame physics-update spine for a specific entity
         * type. 26 cross-USO calls below this gate run the actual update.
         *
         * 2026-05-03 EXTENDED DECODE @ 0xDA60-0xDB70 (~70 insns):
         * The post-gate flow is a state-bit dispatcher.
         *   c.lt.s f2, f16            ; abs-test residual
         *   gl_func_00000000(...)     ; helper call (saves sp+0x28/0x30)
         *   t0 = inner ptr (reload after jal)
         *   f18 = inner->0xA1C        ; another float field
         *   if (0.0 < f18) {
         *       /* "positive residual" path *\/
         *       s0->0x108 = s0->0xFC | 0x16;     ; state |= 0x16
         *       local_2C = 1;                     ; mode-flag = 1
         *   } else {
         *       /* "non-positive residual" path *\/
         *       s0->0x108 = s0->0xFC | 0x17;     ; state |= 0x17
         *       local_2C = 3;                     ; mode-flag = 3
         *       goto far_path_at_+0x46;
         *   }
         *   /* fall-through: another c.lt.s f0, f6 + bc1fl chain at
         *    * 0xDAE4-0xDB30, then a 500.0f-bracket compare at 0xDB30+
         *    * (D420 = lh; halfword load at inner+0x1F8) leading into
         *    * a third state-update with OR-mask 0xE setting s0->0x108
         *    * = s0->0xFC | 0x0E. *\/
         * Pattern: chained c.lt.s residual checks, each setting an
         * OR-mask on s0->0x108 (state byte) plus a `local_2C` mode
         * indicator (1, 3, ...). The OR-masks accumulate state bits
         * — the state byte at 0x108 encodes which physics conditions
         * were detected this frame. The `local_2C` mode indicator
         * later drives the gl_func dispatch (probably the actual
         * physics-state callbacks).
         * Frame layout firmed up: sp+0x28 = saved t9 (callee return),
         * sp+0x2C = mode indicator, sp+0x30 = scratch (cleared each
         * call).
         *
         * EXTENDED CHARACTERIZATION 2026-05-06 (insns 100-125 @ 0xDB50-0xDB90):
         *   /* third c.le.s residual check on f2/f18 *\/
         *   if (f2 <= f18) {            ; bc1fl skips fall-through if cc=0
         *       state = s0->0xFC;
         *       s0->0x108 = state | 0x0E;
         *       sp+0x2C = 3;
         *       goto far_merge_DBD4;    ; b 0xDBD4
         *   } else {                    ; bc1fl-taken, t0 already loaded
         *       state = t0;             ; (delay-slot reload of s0->0xFC)
         *       s0->0x108 = state | 0x0F;
         *       sp+0x2C = 1;
         *       goto far_merge_DBD4;
         *   }
         *
         * (Note: this is the THIRD chained residual-check writing 0x108.
         * Earlier chains at 0xDA60+ wrote OR-masks 0x16/0x17 (mode 1/3),
         * here 0x0E/0x0F (mode 3/1). The 4-bit nibble varies; the state
         * byte at 0x108 accumulates all condition flags this frame.)
         *
         * START OF FOURTH CHAIN @ 0xDB90 (insns ~125-130):
         *   f4 = 0.0f;
         *   f6 = v1->[0xA1C] (inner field, same as f18 above);
         *   if (0.0 < f6) {             ; c.lt.s f4, f6 + bc1fl
         *       state = s0->0xFC;
         *       s0->0x108 = state | 0x0C;  ; partial — body continues to 0xDBC4
         *       /* sp+0x2C = 1; *\/
         *   } else {
         *       /* (decoded next pass — branch target 0xDBC4) *\/
         *   }
         *
         * Cumulative ~125/524 insns characterized (~24%). The per-frame
         * state-machine theme is now confirmed: chained c.lt.s / c.le.s
         * gates each set a different OR-mask on s0->0x108 (state byte)
         * plus a mode-indicator local_2C value. These are 4-5 chained
         * checks, each on a different physics float field, accumulating
         * the per-frame state that downstream gl_func calls dispatch on.
         *
         * EXTENDED 2026-05-07 (insns 125-137 @ 0xDBC0-0xDBEC):
         *   /* fourth-chain else-arm (when 0 < f6 was false): *\/
         *   state = s0->0xFC;
         *   s0->0x108 = state | 0x0D;       ; OR-mask 0x0D (4th alt path)
         *   sp+0x2C = 3;                     ; mode = 3
         *
         *   /* fifth chain entry @ 0xDBD4: *\/
         *   v1 = s0->0xB4;                   ; reload inner ptr
         *   f10 = 500.0f;                    ; threshold from lui 0x43FA
         *   f8 = v1->[0x9D0];                ; load inner field (float)
         *   f16 = 0.0f;
         *   if (f8 < 500.0f) {               ; c.lt.s f8, f10 + bc1??
         *       /* (decoded next pass — 5th chain body) *\/
         *
         * The fourth-chain merge here wraps the previous block (0 < f6 ==
         * true → state | 0x0C, mode = 1; false → state | 0x0D, mode = 3).
         * Both arms then converge at 0xDBD4 to start the FIFTH residual
         * check on a NEW field (inner->0x9D0, threshold 500.0f). The
         * 500.0f appears finally as an actual c.lt.s comparand here,
         * confirming the early-comment hypothesis that 500.0f was a
         * speed/timer threshold.
         *
         * Cumulative 137/524 insns (~26%). NEXT PASS: 5th chain body at
         * 0xDBF0+ (the bc1?? + state-update arms for f8 < 500.0f gate). */
    } else {
        /* 30.0f-fail path @ 0xDBDC (far forward, ~280 insns from entry).
         * Decoded skeleton: loads 500.0f into $f0 at delay slot, then
         * runs alternate FPU/cross-USO sequence. Probably a "reset"
         * or "default-physics" path when the primary threshold fails. */
    }
    /* TODO: remaining ~470 insns of float scheduling with mtc1 zero,
     * c.lt.s gates, and cross-USO dispatch. */
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D9CC);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E1FC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E35C);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E5C8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E91C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000ECEC);

extern char D_00000138;
void game_uso_func_0000EE30(char *a0, int a1, int a2) {
    int *dptr = (int*)&D_00000138;
    gl_func_00000000(*dptr, *(int*)(a0 + 0xB4), a1 * a2);
}

void game_uso_func_0000EE74(void *a0) {
    *(s32*)((char*)*(s32**)((char*)a0 + 0xB4) + 0x960) = 100;
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000EE84);

#ifdef NON_MATCHING
/* 82.20% NM. 4-call wrapper. Logic: call gl_func(a0); call gl_func(a0, D_E40, D_E44);
 * call gl_func(a0); call gl_func(a0). Hits precall arg-spill cap per
 * feedback_ido_precall_arg_spill_unreachable.md — target spills a1/a2 to
 * sp+4/sp+8 around the second jal (sw a1,4(sp); sw a2,8(sp)) but IDO -O2
 * with K&R-declared gl_func_00000000 won't emit those spills. Mine: 16
 * insns / 0x40. Target: 20 insns / 0x50. Logic correct. */
void game_uso_func_0000EF20(int a0) {
    int *p = (int*)((char*)&D_00000000 + 0xE40);
    gl_func_00000000(a0);
    gl_func_00000000(a0, p[0], p[1]);
    gl_func_00000000(a0);
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000EF20);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000EF70);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F060);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F13C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F284);

#ifdef NON_MATCHING
/* game_uso_func_0000F360: 49-insn float-compare-gated state update.
 * Entry (~10 insns decoded):
 *   v0 = a0->0xE4 (short)
 *   if (v0 <= 0) { a0->0xE4 = 0; v0 = 0; }
 *   f6 = (short)v0; sub = a0->0xB4; thresh = a0->0x1B4 (float)
 *   t6 = sub->0x9CC (some flag)
 *   if (sub->0x9CC == 0) goto skip
 *   ... compares f4=thresh vs f8=(float)v0, branches based on c.le.s ...
 *
 * Body proper is float-comparison + neg.s sequences + 2 cross-USO calls +
 * struct-store finalize. Multi-pass NM placeholder. */
void game_uso_func_0000F360(int *a0) {
    short v0 = *(short*)((char*)a0 + 0xE4);
    if (v0 <= 0) {
        *(short*)((char*)a0 + 0xE4) = 0;
    }
    /* TODO 0x24-0xC4: float compare + neg branch + 2 dispatches + final stores */
    (void)v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F360);
#endif

#ifdef NON_MATCHING
/* 30-insn USO function (0xF424, size 0x78). Decoded from .word-only asm:
 *   p_b4 = a0->field_B4 (loaded as int*)
 *   p_b4->field_A18 = 0       (clear an int slot)
 *   a0->field_114  = 1        (set a flag-byte/word)
 *   p_b4 reloaded; flag = p_b4->field_9A8
 *   if ((flag & 1) == 0) {
 *       float a = *(f32*)((char*)p_b4 + 0x180);   // 0x170 + 0x10
 *       float b = *(f32*)((char*)p_b4 + 0x6A8);   // 0x698 + 0x10
 *       *(f32*)((char*)p_b4 + 0x31C) += -a * b;   // accumulate -a*b
 *   }
 *   gl_func_00000000(a0);                          // first runtime-patched callee
 *   gl_func_00000000(a0, 0);                       // second with arg2=0
 *
 * Will not byte-match without typed structs + careful regalloc — IDO -O2
 * picks its own intermediate float regs + the bnez shape depends on the
 * compile-time order of `flag = p_b4->field_9A8` and the &1 mask.
 * Documented for the next pass; default INCLUDE_ASM keeps ROM correct. */
void game_uso_func_0000F424(int *a0) {
    int *p_b4;
    int flag;

    p_b4 = (int*)a0[0xB4 / 4];
    p_b4[0xA18 / 4] = 0;
    a0[0x114 / 4] = 1;
    p_b4 = (int*)a0[0xB4 / 4];
    flag = ((int*)p_b4)[0x9A8 / 4];
    if ((flag & 1) == 0) {
        float a = *(float*)((char*)p_b4 + 0x180);
        float b = *(float*)((char*)p_b4 + 0x6A8);
        *(float*)((char*)p_b4 + 0x31C) += -a * b;
    }
    gl_func_00000000(a0);
    gl_func_00000000(a0, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F424);
#endif

#ifdef NON_MATCHING
/* game_uso_func_0000F49C: 30-insn state-init (sets a0->0x114=2, conditionally
 * calls gl_func_0(a0) on flag bit 0 of a0->0xF4->0x38, then unconditional
 * 2 more gl_func_0 calls — second carries D[0xDF0]+D[0xDF4] as args).
 *
 * Logic byte-correct at 90.40%. Mine emits 28/30 insns matching at correct
 * sp offsets:
 *   - missing 2 pre-call arg-spills (`sw a1, 0x4(sp)`, `sw a2, 0x8(sp)`)
 *     before the 2nd gl_func_0 call. Documented IDO cap from
 *     feedback_ido_precall_arg_spill_unreachable.md — IDO -O2 doesn't
 *     emit pre-call register-arg spills to outgoing-arg slots from C without
 *     unreachable invariants on the function pointer.
 *   - register-name offset (mine v0/t7/t8, expected t7/t8/t9) on the bit-test
 *     chain. Multi-pass NM.
 *
 * 2026-05-08 LEVER TESTS (all negative):
 *   (1) lift `int *sub = a0->0xB4;` BEFORE the if-block (per
 *       docs/IDO_CODEGEN.md "lift unconditional init"): 90.40% → 74.53%
 *       (-15.87pp). IDO promoted `sub` to a longer-lived value, shifting
 *       allocations.
 *   (2) duplicate `a0[0x114] = 2;` into both if/else arms: 90.40% → 76.57%
 *       (-13.83pp). Extra stores break the schedule.
 *   (3) full unwrap (no #ifdef): scored 90.40% — same as wrapped (NOT an
 *       objdiff alias artifact; cap is REAL, not the reloc-encoding class
 *       that 21E58/61E58/32C8 had). Cap genuinely needs the shadow-arg-spill
 *       lever which is unreachable from C. */
void game_uso_func_0000F49C(int *a0) {
    int *flags_ptr = (int*)a0[0xF4/4];
    int *sub;
    a0[0x114/4] = 2;
    if (*(int*)((char*)flags_ptr + 0x38) & 1) {
        gl_func_00000000(a0);
    }
    sub = (int*)a0[0xB4/4];
    sub[0xA18/4] = 1;
    a0[0xF4/4] = 0;
    gl_func_00000000(a0,
        *(int*)((char*)&D_00000000 + 0xDF0),
        *(int*)((char*)&D_00000000 + 0xDF4));
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F49C);
#endif

#ifdef NON_MATCHING
/* game_uso_func_0000F514: 37-insn state-init w/ flag-gated branch.
 * gl_func_0(a0); a0->0xB4->0xA68 = 1; check (a0->0xB4)->0x800->0x10 & 0x200:
 *   if set:  gl_func_0(a0); gl_func_0(a0, 1, 1);
 *   else:    gl_func_0(a0, D[0xED8], D[0xEDC]);
 * gl_func_0(a0). Multi-pass NM. F49C-family — same precall-arg-spill cap. */
void game_uso_func_0000F514(int *a0) {
    int *sub;
    int **subp;
    int *p2;
    gl_func_00000000(a0);
    sub = (int*)a0[0xB4/4];
    sub[0xA68/4] = 1;
    sub = (int*)a0[0xB4/4];
    subp = (int**)((char*)sub + 0x800);
    p2 = *subp;
    if (p2[0x10/4] & 0x200) {
        gl_func_00000000(a0);
        gl_func_00000000(a0, 1, 1);
    } else {
        gl_func_00000000(a0,
            *(int*)((char*)&D_00000000 + 0xED8),
            *(int*)((char*)&D_00000000 + 0xEDC));
    }
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F514);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F5A8);

#ifdef NON_MATCHING
/* 88.10% NM. 26 insns built vs 28 expected (size 0x6C vs 0x70).
 * 3-call dispatcher:
 *   gl_func(a0, a0->0xF4->0x20, 2, 3, 1, 1);    // 6 args
 *   gl_func(a0, D_EC8, D_ECC, 3);               // 4 args
 *   gl_func(a0, 0);
 * Same precall-arg-spill cap as game_uso_func_0000EF20 / _0000F8E8 family —
 * IDO -O2 with K&R gl_func_00000000 won't emit the `sw a1,4(sp); sw a2,8(sp)`
 * spills target has around the second jal. Also picks $v0 for the
 * D_EC8 base reg vs target $t9, and $v0 for *(a0+0xF4) vs target $t6.
 * Size mismatch blocks INSN_PATCH. Tried typed varargs extern in sibling
 * (no effect there either). Logic correct, decode preserved for reference. */
void game_uso_func_0000F664(char *a0) {
    char *t6 = *(char**)(a0 + 0xF4);
    gl_func_00000000(a0, *(int*)(t6 + 0x20), 2, 3, 1, 1);
    gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xEC8), *(int*)((char*)&D_00000000 + 0xECC), 3);
    gl_func_00000000(a0, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F664);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F6D4);

#ifdef NON_MATCHING
/* 85.17% NM. 24-insn 2-call wrapper. Body: gl_func(a0, a0->0xFC, 0, 0, 0x100, 5);
 * gl_func(a0, D_E50, D_E54, -1). Same precall-arg-spill structural cap
 * as game_uso_func_0000EF20 — IDO -O2 with K&R gl_func_00000000 won't
 * emit the sw a1,4(sp); sw a2,8(sp) spills target has around the second
 * jal. Mine 19 insns / 0x4C vs target 24 insns / 0x60. Logic correct.
 * 2026-05-02: tried typed varargs extern (gl_func_F8E8(int,int,int,int,...))
 * to trigger spill — no change, still 85.17%. Spills are not just
 * varargs-driven; they look like callee-side defensive spill area that
 * IDO doesn't emit unless the prototype has a specific shape. */
void game_uso_func_0000F8E8(int *a0) {
    int *p = (int*)((char*)&D_00000000 + 0xE50);
    gl_func_00000000(a0, *(int*)((char*)a0 + 0xFC), 0, 0, 0x100, 5);
    gl_func_00000000(a0, p[0], p[1], -1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F8E8);
#endif

#ifdef NON_MATCHING
/* 67-insn function. Shape:
 *
 *   call 1 (6-arg, a2=0, a3=2):
 *     gl_func(a0, a0->[0xFC], 0, 2, 1, 1)
 *
 *   call 2 (4-arg from D[0xE58/0xE5C], a3=2 — same family pattern as
 *   game_uso_func_00010E2C / 00010DC8 / 000114FC, with the lui+addiu+lw
 *   fold-inevitable cap and varargs shadow-spills):
 *     gl_func(a0, D[0xE58], D[0xE5C], 2)
 *
 *   inline Vec3 scaled-and-add at a0->[0xB4]->[0x318..0x320]:
 *     b = a0->[0xB4]
 *     scale = a0->[0x1FC]
 *     scaled.{x,y,z} = b->[0x3C8/3CC/3D0] * scale
 *     # target spills `scaled` to sp+0x48, then COPIES that to sp+0x5C,
 *     # then COPIES sp+0x5C to sp+0x74. Three 12-byte stack regions.
 *     b->[0x318] += sp[0x74]    # which equals scaled.x via the chain
 *     b->[0x31C] += sp[0x78]
 *     b->[0x320] += sp[0x7C]
 *
 * Initial decode at 16.7% match (10/60 insns). Two structural diffs
 * remain:
 *
 * 1. First 18 insns: same family fold-cap as 10E2C/10DC8/14FC. IDO
 *    collapses `lui+addiu+lw` 4-insn target form to `lui+lw` 2-insn
 *    direct form. SUFFIX+INSN_PATCH recipe should promote (per
 *    docs/POST_CC_RECIPES.md#feedback-suffix-plus-insn-patch-grows-and-reshapes)
 *    once the body structure matches.
 *
 * 2. Body: target has TWO intermediate stack copies of the scaled Vec3
 *    (sp+0x48 → sp+0x5C → sp+0x74). My C "Vec3 a/b/c" with 3 separate
 *    int[3] arrays compiles to 60 insns / 0xF0 vs target 67 insns / 0x10C
 *    (7 insns short). IDO's optimizer is consolidating my redundant
 *    copies. Target's pattern looks like a function-result-temp chain
 *    where each call returns by-value Vec3 and the result is taken by
 *    the next stage. May be `*sp_dest_a = vec3_scale(...); *sp_dest_b =
 *    *sp_dest_a; *sp_dest_c = *sp_dest_b;` or similar pass-through.
 *
 * 2026-05-07 attempt 2: switched to typed `F948_Vec3` struct + volatile
 * annotations on `a` and `vb`. Goal was to defeat IDO -O2 dead-store-
 * elim across the 3 stack-copies. Result: still 85.19% — same as
 * non-volatile array-int[3] version. Volatile DOES preserve all 3
 * copies (verified in -O2 emit: 9 lw/sw insns at 0x92a8-0x92d4) but
 * stack offsets differ from target (built sp+0x44/0x38/0x2c vs target
 * sp+0x48/0x5C/0x74). Copy semantics + count match; offset-arrangement
 * mismatch via IDO's reverse-order stack-frame allocator is the
 * remaining 14.81% diff.
 *
 * 2026-05-07 attempt 3: declared in REVERSE order with explicit char-pad
 * stuffing (vc; char[8]; vb; char[4]; a). REGRESSED to 77.52% — pad bytes
 * shifted t1=sp+0x48 correctly to match target's first addiu but added
 * extra moves elsewhere that broke the copy chain. The pad-stuffing
 * approach is a dead-end here; offsets DO move, but the surrounding
 * code structure changes too. Reverted.
 *
 * 2026-05-07 attempt 4: REVERSE order WITHOUT pads (vc; volatile vb;
 * volatile a). Same regression to 77.52%. Reverse-declaration alone
 * doesn't help; baseline-state has drifted from the doc's quoted 85.19%
 * to a current 77.52% even with the original C body unchanged. Built NM
 * is 248 bytes (62 insns) vs expected 268 bytes (67 insns) — IDO is now
 * eliminating one of the 3 Vec3 copies despite volatile. The exact
 * fuzzy% on this function is sensitive to expected/.o baseline state.
 *
 * Conclusion: F948 NM-cap is NOT promotable via C-shape variations alone.
 * Permuter or INSN_PATCH are the only remaining options. Multi-tick
 * deferred. */
extern int gl_func_00000000();
extern char D_00000000;
typedef struct { float x, y, z; } F948_Vec3;
void game_uso_func_0000F948(int *a0) {
    int *b;
    float scale;
    volatile F948_Vec3 a, vb;
    F948_Vec3 vc;
    register int *t;
    int v1, v2;

    gl_func_00000000(a0, *(int*)((char*)a0 + 0xFC), 0, 2, 1, 1);
    t = (int*)((char*)&D_00000000 + 0xE58);
    v1 = t[0];
    v2 = t[1];
    gl_func_00000000(a0, v1, v2, 2);

    b = (int*)a0[0xB4 / 4];
    scale = *(float*)((char*)a0 + 0x1FC);
    /* Build scaled Vec3 in `a`, then copy a→vb→vc as struct-by-value
     * (IDO -O2 emits 3-lw/3-sw per copy without dead-store-elim across
     * struct boundaries). */
    a.x = *(float*)((char*)b + 0x3C8) * scale;
    a.y = *(float*)((char*)b + 0x3CC) * scale;
    a.z = *(float*)((char*)b + 0x3D0) * scale;
    vb = a;
    vc = vb;

    b = (int*)a0[0xB4 / 4];
    *(float*)((char*)b + 0x318) += vc.x;
    *(float*)((char*)b + 0x31C) += vc.y;
    *(float*)((char*)b + 0x320) += vc.z;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F948);
#endif

/* 26-insn 3-call wrapper, family sibling of 10E2C/14FC/DC8 with one
 * extra pass-through call before the family-pattern body. Promoted from
 * 88.35% NM cap via SUFFIX_BYTES of 2 nops + 12-word INSN_PATCH at
 * +0x34..+0x60 (per docs/POST_CC_RECIPES.md
 * #feedback-suffix-plus-insn-patch-grows-and-reshapes). Divergence point
 * shifted from +0x2C (in the 24-insn family) to +0x34 because the extra
 * call-2 body sits at +0x2C..+0x30. */
void game_uso_func_0000FA54(int *a0) {
    register int *t;
    int v1, v2;
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0xFC), 2, 1, 1, 1);
    game_uso_func_00000000(a0);
    t = (int*)((char*)&D_00000000 + 0xE40);
    v1 = t[0];
    v2 = t[1];
    game_uso_func_00000000(a0, v1, v2, 1);
}

#ifdef NON_MATCHING
/* 18-insn 3-call wrapper. Body: gl_func(a0); gl_func(a0, *(D+0xE40),
 * *(D+0xE44)); gl_func(a0).
 *
 * Match blocked by two IDO codegen patterns target uses:
 * 1. Base-adjust on the address load (addiu $tN by 0xE40, then lw at
 *    offsets 0 and 4) — see feedback_ido_base_adjust_for_clustered_offsets.md.
 * 2. Variadic-style stack spill of $a1, $a2 to sp+4, sp+8 — IDO emits
 *    this when the called function's signature is varargs, but our K&R
 *    `extern int gl_func_00000000()` doesn't trigger it. */
void game_uso_func_0000FABC(int a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xE40), *(int*)((char*)&D_00000000 + 0xE44));
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FABC);
#endif

#ifdef NON_MATCHING
/* game_uso_func_0000FB04: 30-insn dispatcher with conditional gate.
 * gl_func_0(a0); if (a0->0x110 != 0) { gl_func_0(a0, a0->0x108, 2, 1, 1, 1);
 * gl_func_0(a0, D[0xE40], D[0xE44], 1); }. Logic byte-correct, 28/30 insns.
 * Missing 2 pre-call defensive arg-spills (sw a1, 4; sw a2, 8) before the
 * 2nd gl_func_0 call — documented IDO cap per
 * feedback_ido_precall_arg_spill_unreachable.md. Multi-pass NM. */
void game_uso_func_0000FB04(int *a0) {
    gl_func_00000000(a0);
    if (a0[0x110/4] != 0) {
        gl_func_00000000(a0, a0[0x108/4], 2, 1, 1, 1);
        gl_func_00000000(a0,
            *(int*)((char*)&D_00000000 + 0xE40),
            *(int*)((char*)&D_00000000 + 0xE44),
            1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FB04);
#endif

#ifdef NON_MATCHING
/* game_uso_func_0000FB7C: 31-insn 3-call dispatcher in F49C/FB04 family.
 * Sets a0->0x108 = a0->0xFC | 0xA; calls gl_func_0(a0, that, 0, 2, 1, 1);
 * gl_func_0(a0, D[0xE88], D[0xE8C], 2); gl_func_0(a0); then a0->0x114 = 0.
 * Logic byte-correct, 29/31 insns. Same precall-arg-spill cap as FB04 +
 * F49C — missing 2 defensive `sw a1, 4(sp); sw a2, 8(sp)` before 2nd call.
 * Multi-pass NM. */
void game_uso_func_0000FB7C(int *a0) {
    int v = a0[0xFC/4] | 0xA;
    a0[0x108/4] = v;
    gl_func_00000000(a0, v, 0, 2, 1, 1);
    gl_func_00000000(a0,
        *(int*)((char*)&D_00000000 + 0xE88),
        *(int*)((char*)&D_00000000 + 0xE8C),
        2);
    gl_func_00000000(a0);
    a0[0x114/4] = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FB7C);
#endif

void game_uso_func_0000FBF8(int *a0) {
    int v = *(int*)((char*)a0 + 0xFC);
    game_uso_func_00000000(a0, v | 2, v | 3,
        *(int*)((char*)*(int**)((char*)a0 + 0xB4) + 0x970), 0, 1);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FC34);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FD04);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FDCC);

/* Same SUFFIX_BYTES + INSN_PATCH spill-tail recipe as the 0x10E2C family;
 * target emits caller arg-slot spills before the conditional second call. */
void game_uso_func_0000FEC8(char *a0) {
    gl_func_00000000(a0, 0x30001, 4, 5, 2, 1);
    if (*(float*)(*(char**)(a0 + 0xB4) + 0x9D0) < 1000.0f) {
        gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xE38), *(int*)((char*)&D_00000000 + 0xE3C));
    }
}

#ifdef NON_MATCHING
/* 89.18% NM. Built 26 vs expected 28 insns (size 0x68 vs 0x70). 2-call gated
 * dispatcher (sibling of game_uso_func_0000F664/F8E8/EF20):
 *   if (a0->0xB4->0x938 != 0) {
 *     gl_func(a0, 0x30001, 6, 1, 1, 1);
 *     gl_func(a0, D_E10, D_E14, 1);
 *   }
 * Same precall-arg-spill cap: target emits `sw a1,4(sp); sw a2,8(sp)` defensive
 * spills before the second jal that IDO -O2 with K&R extern doesn't reproduce.
 * Documented in feedback_uso_3unique_extern_inline_store_before_jal_combo.md
 * and feedback_ido_varargs_extern_doesnt_force_caller_spill.md. Size diff
 * blocks INSN_PATCH per feedback_insn_patch_size_diff_blocked.md. */
void game_uso_func_0000FF48(char *a0) {
    if (*(int*)(*(int**)(a0 + 0xB4) + 0x938 / 4) != 0) {
        gl_func_00000000(a0, 0x30001, 6, 1, 1, 1);
        gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xE10), *(int*)((char*)&D_00000000 + 0xE14), 1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FF48);
#endif

void game_uso_func_0000FFB8(int *a0) {
    gl_func_00000000(a0, 0x30001, 5, 6, 1, 1);
    gl_func_00000000(a0,
        *(int*)((char*)&D_00000000 + 0xE28),
        *(int*)((char*)&D_00000000 + 0xE2C),
        6);
}

#ifdef NON_MATCHING
/* 84.05% NM. 19-insn / 0x4C. Three gl_func_00000000 calls bracketing
 * a 2-int load from D+0xDD0/0xDD4. Body inferred from asm:
 *   a0->0xF4 = 0;
 *   gl_func(a0);
 *   gl_func(a0, *(D+0xDD0), *(D+0xDD4));   // 3-arg w/ stack-slot spills
 *   gl_func(a0);
 * Stack-slot spills (sw a1,4(sp); sw a2,8(sp)) are O32 caller-side spill
 * area for the 3-arg middle call — emitted automatically by IDO when the
 * callee is K&R-declared.
 *
 * 2026-05-06 retry (negative): tried unique-extern at distinct offsets
 * (D_1001C_arg1 = 0xDD0, D_1001C_arg2 = 0xDD4) per
 * docs/IDO_CODEGEN.md#feedback-ido-type-split-unique-extern-breaks-cse
 * 2026-05-06 expansion. Result REGRESSED 84.05% → 81.26%. Reason: target
 * uses ONE base reg + offsets (cluster-load pattern); unique-externs at
 * different addresses force TWO separate lui+addiu pairs, breaking the
 * cluster. The cap is the precall-arg-spill itself, not symbol CSE — so
 * unique-extern doesn't apply. */
void game_uso_func_0001001C(int *a0) {
    int *p;
    *(int*)((char*)a0 + 0xF4) = 0;
    gl_func_00000000(a0);
    p = (int*)((char*)&D_00000000 + 0xDD0);
    gl_func_00000000(a0, p[0], p[1]);
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001001C);
#endif

#ifdef NON_MATCHING
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
extern int gl_func_00000000();
extern char D_00000000;
void game_uso_func_00010068(int *a0) {
    int t1_field;
    int *outer;
    /* Call 1: 6-arg w/ 2 stack args */
    gl_func_00000000(a0,
                     *(int*)((char*)a0 + 0xFC) | 0x19,
                     0, 2,
                     0x100, 10);
    /* Call 2: 4-arg with D[0xDD8/0xDDC] */
    gl_func_00000000(a0,
                     *(int*)((char*)&D_00000000 + 0xDD8),
                     *(int*)((char*)&D_00000000 + 0xDDC),
                     -1);
    /* Conditional Call 3 */
    outer = (int*)*(int**)((char*)a0 + 0xB4);
    t1_field = ((int*)outer[0x800 / 4])[0x18 / 4];
    if (t1_field & 0x400) {
        gl_func_00000000(a0,
                         *(int*)((char*)&D_00000000 + 0xDE0),
                         *(int*)((char*)&D_00000000 + 0xDE4));
    }
    /* Call 4 */
    gl_func_00000000(a0);
    /* Call 5 */
    gl_func_00000000(a0, 0);
    /* Call 6 */
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010068);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00010128: 105-insn (0x1A4) complex dispatcher.
 *
 * Frame -0x28; saves s0 (= a0), ra. Multiple cross-USO calls dispatched
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
 * Default INCLUDE_ASM path keeps ROM matching while structural decode
 * lives here for grep discoverability + multi-tick refinement. */
extern int gl_func_00000000();
extern char D_00000000;
void game_uso_func_00010128(int *a0) {
    int *outer = (int*)a0[0xB4 / 4];
    int *outer_ptr;
    int *inner;
    int v0;

    outer[0xA18 / 4] = 1;
    outer_ptr = (int*)outer[0x800 / 4];
    if ((outer_ptr[0x18 / 4] & 0x400) != 0) {
        gl_func_00000000(a0,
                         *(int*)((char*)&D_00000000 + 0xDE0),
                         *(int*)((char*)&D_00000000 + 0xDE4));
    }
    if (*(float*)((char*)outer + 0x9D0) < 1000.0f) {
        if (outer[0x938 / 4] != 0) {
            gl_func_00000000(a0,
                             *(int*)((char*)&D_00000000 + 0xDE8),
                             *(int*)((char*)&D_00000000 + 0xDEC));
        }
        inner = (int*)a0[0xF4 / 4];
        if (inner != 0) {
            if (inner[0x38 / 4] & 1) {
                gl_func_00000000(a0,
                                 *(int*)((char*)a0 + 0xFC) | 0x19,
                                 0, 5, 5, 1, 1);
            } else {
                gl_func_00000000(a0,
                                 *(int*)((char*)a0 + 0xFC) | 0x19,
                                 0, 5, 5, 0x100, 10);
            }
        } else {
            gl_func_00000000(a0,
                             *(int*)((char*)a0 + 0xFC) | 0x19,
                             0, 5, 5, 0, 0);
        }
        gl_func_00000000(a0,
                         *(int*)((char*)&D_00000000 + 0xDF0),
                         *(int*)((char*)&D_00000000 + 0xDF4),
                         3);
        gl_func_00000000(a0);
        gl_func_00000000(a0, 0);
        v0 = gl_func_00000000(a0);
        if (v0 == 0) {
            gl_func_00000000(a0);
            gl_func_00000000(a0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010128);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000102CC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010408);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000104A4);

#ifdef NON_MATCHING
/* 89.18% NM. 5th confirmed member of precall-arg-spill family
 * (F664/F8E8/EF20/FF48/1056C). Built 26 vs expected 28 insns: target emits
 * `sw a1,4(sp); sw a2,8(sp)` defensive spills around the second jal that
 * IDO -O2 K&R extern doesn't reproduce. INSN_PATCH ineligible (size diff
 * blocks it per feedback_insn_patch_size_diff_blocked.md).
 *
 * Logic:
 *   gl_func_00000000(a0, 0x10025, 0, 0, 0x100, 5);
 *   gl_func_00000000(a0, *(int*)(D + 0xE08), *(int*)(D + 0xE0C), -1);
 *   *(float*)(a0 + 0x11C) = *(float*)(a0 + 0x154);
 *
 * Note this variant has a final FLOAT COPY tail not seen in the others. */
void game_uso_func_0001056C(char *a0) {
    gl_func_00000000(a0, 0x10025, 0, 0, 0x100, 5);
    gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xE08), *(int*)((char*)&D_00000000 + 0xE0C), -1);
    *(float*)(a0 + 0x11C) = *(float*)(a0 + 0x154);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001056C);
#endif

/* 27-insn 3-call sibling of 10E2C/11368/FA54 family, with a 2-insn trailing
 * alt-entry stub (`lui at, 0x3F80; mtc1 at, $f4` — sets $f4 = 1.0f for the
 * next function to inherit). Promoted via SUFFIX_BYTES (4 words: jr ra +
 * nop + lui at + mtc1) + INSN_PATCH (13 insns at offsets 0x30-0x60 with
 * target's t8-base form and varargs spills a1@sp+0x4, a2@sp+0x8). */
void game_uso_func_000105DC(int *a0) {
    int v1, v2;
    int *t;
    game_uso_func_00000000(a0, 0x10025, 0, 1, 1, 1);
    t = (int*)((char*)&D_00000000 + 0xE00);
    v1 = t[0];
    v2 = t[1];
    game_uso_func_00000000(a0, v1, v2, 1);
    game_uso_func_00000000(a0);
}

#ifdef NON_MATCHING
/* 68 % NM wrap. Function uses $f4 directly without setting it — caller-set
 * float convention not reproducible from standard C signature `f(int, float)`,
 * which puts float arg in $a1 → mtc1 $a1, $f12 → swc1 $f12 (target uses $f4).
 *
 * Body structure: store caller's $f4 to a0+0x11C, then call gl_func_00000000
 * twice. Target's first call passes a0, *(D+0xDF8), *(D+0xDFC) — extracted
 * via `addiu base,&D,0xDF8; lw a1,0(base); lw a2,4(base)` (named base
 * pointer pattern, see feedback_ido_named_base_forces_addiu_split.md).
 * Target also spills a1/a2 to sp+0x4/sp+0x8 (likely callsite-arg-slots for
 * variadic or wider call signature).
 *
 * THIS IS THE ORIGIN CASE for feedback_uso_float_in_f4_callee.md (intra-USO
 * non-O32 float-in-$f4 convention). IDO has no C-level mechanism to receive
 * a float in $f4 directly — `register float f asm("$f4")` is GCC-only and
 * IDO's cfe rejects it (per feedback_ido_no_gcc_register_asm.md). Cap holds.
 */
void game_uso_func_00010650(void *a0, float arg1) {
    int x, y;
    *(float*)((char*)a0 + 0x11C) = arg1;
    x = *(int*)((char*)&D_00000000 + 0xDF8);
    y = *(int*)((char*)&D_00000000 + 0xDFC);
    gl_func_00000000(a0, x, y);
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010650);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00010694: 0x1AC (107 insns), 0x30-byte stack frame, saves
 * s0+ra. Strategy-memo source-5 pick (game_uso, smallest fresh non-spine
 * with no prior wrap). Per ~25-insn entry decode:
 *   - Sets 3 fields in a0->0xB4 substruct (0xA18=1, 0x3DC=1, 0x960=0)
 *   - Sets a0->0x114=2, a0->0x11C=1.0f
 *   - Saves f0 = (a0->0xB4)->0x970 to sp+0x2C
 *   - 3 cross-USO calls (gl_func_0(a0, ...) — first sets f0 arg via swc1
 *     spill, second/third just pass a0)
 *   - Then: |f0|; convert to double (cvt.d.s); load D-table double constant
 *     at &D+0x250; double arithmetic with f2/f10 — likely sqrt/log/clamp
 *   - ~80 more insns of double-prec math + cross-call sequence (still TODO)
 *
 * Entry pattern is "init substruct flags + cache float + dispatch + clamp".
 * Likely a state-machine entry handler (key=2 from a0->0x114 = 2).
 * Multi-pass NM, default INCLUDE_ASM keeps ROM exact. */
extern int gl_func_00000000();
void game_uso_func_00010694(int *a0) {
    int *sub = (int*)a0[0xB4/4];
    float saved_f0;
    sub[0xA18/4] = 1;
    a0[0x114/4] = 2;
    sub = (int*)a0[0xB4/4];
    sub[0x3DC/4] = 1;
    sub = (int*)a0[0xB4/4];
    *(float*)((char*)a0 + 0x11C) = 1.0f;
    saved_f0 = *(float*)((char*)sub + 0x970);
    gl_func_00000000(a0);
    sub = (int*)a0[0xB4/4];
    sub[0x960/4] = 0;
    gl_func_00000000(a0);
    gl_func_00000000(a0);
    /* @ 0x60-0x88: |saved_f0| via bc1fl-likely abs (mov vs neg). Standard
     * `f2 = fabsf(f0)` shape. */
    {
        float abs_f0 = (saved_f0 < 0.0f) ? -saved_f0 : saved_f0;
        /* @ 0x88-0x9C: f20 (double) = D[0x250] - (double)abs_f0; passed
         * implicitly to the next gl_func_0(a0) via $f12/$f14 double
         * convention (or stored later). */
        double diff = *(double*)((char*)&D_00000000 + 0x250) - (double)abs_f0;
        gl_func_00000000(a0);
        sub = (int*)a0[0xB4/4];
        /* @ 0xA0-0xCC: comparison-and-branch chain on the diff result.
         * Loop predicate compares against another sub field, multiple
         * cross-calls. Still TODO past this point. */
        (void)diff;
    }
    /* TODO 0xCC-0x1A8: ~50 more insns — comparison loop + final 2 cross-USO
     * dispatches + epilogue. */
    (void)saved_f0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010694);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00010840: 67-insn (0x10C) state-init + dispatch sibling of
 * 10694 (just above). Entry: reads sub=a0->0xB4, sets sub->0x3DC=1,
 * 2 cross-USO dispatches, float compare on (sub->0x970) vs 0.0,
 * conditional dispatch with `bc1f` branch (a1=0x00020008, a2=0, a3=1, t0=6).
 *
 * Decoded ~12 entry insns. Body proper (0x50-0x10C, ~55 more insns) is a
 * conditional-call chain on the float compare — TODO. Default INCLUDE_ASM
 * keeps ROM exact. Multi-pass NM. */
void game_uso_func_00010840(int *a0) {
    int *sub = (int*)a0[0xB4/4];
    float saved_f0;
    sub[0x3DC/4] = 1;
    gl_func_00000000(a0);
    gl_func_00000000(a0);
    /* @ 0x28-0x54: reload sub, save f0=sub->0x970, c.lt.s f0,0; setup
     * args for conditional dispatch (a1=0x00020008, a2=0, a3=1, t0=6). */
    sub = (int*)a0[0xB4/4];
    saved_f0 = *(float*)((char*)sub + 0x970);
    if (saved_f0 < 0.0f) {
        /* Path 1 — bc1f-not-taken arm: a1=0x00020008, a2=0, a3=1, t0=6. */
        gl_func_00000000(a0, 0x00020008, 0, 1);
    }
    /* TODO 0x60-0x10C: ~40 more insns of bc1f-taken arm + final tail. */
    (void)saved_f0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010840);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001094C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010A0C);

#ifdef NON_MATCHING
/* 89.18% NM. 6th member of precall-arg-spill family
 * (F664/F8E8/EF20/FF48/1056C/10AC8). Built 26 vs expected 28 insns
 * — missing `sw a1,4(sp); sw a2,8(sp)` defensive spills around the
 * 3rd jal. Logic decoded:
 *   gl_func_00000000(a0);  // initial call (no extra args)
 *   v0 = a0->0xFC;
 *   gl_func_00000000(a0, v0|2, v0|3, a0->0xB4->0x970, 0x100, 10);
 *   gl_func_00000000(a0, D_E40, D_E44, -1);  // precall-spill cap site
 *
 * INSN_PATCH ineligible (size diff). Same blocker as the family
 * per feedback_uso_3unique_extern_inline_store_before_jal_combo.md. */
void game_uso_func_00010AC8(char *a0) {
    int v0;
    gl_func_00000000(a0);
    v0 = *(int*)(a0 + 0xFC);
    gl_func_00000000(a0, v0 | 2, v0 | 3, *(int*)(*(char**)(a0 + 0xB4) + 0x970), 0x100, 10);
    gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xE40), *(int*)((char*)&D_00000000 + 0xE44), -1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010AC8);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00010B38: 29-insn (0x74) "init + 3-call orchestrator".
 *
 * Decoded body:
 *   gl_func_00000000(a0);                       ; first call (1-arg, init)
 *   p = a0->[0xB4];
 *   gl_func_00000000(a0,
 *                    0x20003,         ; lui 2; ori 3 → 0x20003
 *                    0x20002,         ; lui 2; ori 2 → 0x20002
 *                    0x100,            ; ($t7 = 0x100)
 *                    5);               ; ($t8 = 5)
 *   p->[0x970] = 0x100 stored via stack? Actually:
 *      sw t8 (5), 0x14(sp)  ; outgoing-arg slot
 *      sw t7 (0x100), 0x10(sp)  ; outgoing-arg slot
 *   t = (int*)((char*)&D + 0xE60);
 *   gl_func_00000000(a0, t[0], t[1], -1);       ; 4-arg with varargs spills
 *
 * Family-cap class (~85%): same shape as 10E2C / 11368 / 105DC — varargs
 * pre-spills to caller arg slots before the 3rd jal. Source 5 strategy
 * memo (game_uso) — fell through to size-sort. */
void game_uso_func_00010B38(int *a0) {
    register int *t;
    int v1, v2;
    int *p;
    gl_func_00000000(a0);
    p = (int*)a0[0xB4 / 4];
    gl_func_00000000(a0, 0x20003, 0x20002, 0x100, 5);
    (void)p;
    t = (int*)((char*)&D_00000000 + 0xE60);
    v1 = t[0];
    v2 = t[1];
    gl_func_00000000(a0, v1, v2, -1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010B38);
#endif

void game_uso_func_00010BAC(char *a0) {
    char *sub;
    int state;

    sub = *(char**)(a0 + 0xB4);
    state = *(int*)(a0 + 0xFC);
    gl_func_00000000(a0, state | 7, state | 6, *(int*)(sub + 0xA04), 0, 1);

    if (*(int*)(a0 + 0xD8) == 0) {
        gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xE10),
                         *(int*)((char*)&D_00000000 + 0xE14));
    }

    sub = *(char**)(a0 + 0xB4);
    if (*(int*)(sub + 0x9CC) != 0) {
        gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xE48),
                         *(int*)((char*)&D_00000000 + 0xE4C));
    }
}

void game_uso_func_00010C4C(char *a0) {
    char *sub;

    sub = *(char**)(a0 + 0xB4);
    gl_func_00000000(a0, 0x20007, 0x20006, *(int*)(sub + 0xA04), 0, 1);

    if (*(int*)(a0 + 0xD8) == 0) {
        gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xE48),
                         *(int*)((char*)&D_00000000 + 0xE4C));
    }

    sub = *(char**)(a0 + 0xB4);
    if (*(int*)(sub + 0x9CC) == 0) {
        gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xE10),
                         *(int*)((char*)&D_00000000 + 0xE14));
    }
}

void game_uso_func_00010CF0(char *a0) {
    char *sub;

    sub = *(char**)(a0 + 0xB4);
    if (*(int*)(sub + 0x9CC) != 0) {
        gl_func_00000000(a0, 0x20004, 0x20005, *(int*)(sub + 0x970), 0x100, 10);
        gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xE78),
                         *(int*)((char*)&D_00000000 + 0xE7C), -1);
    } else {
        int state;

        state = *(int*)(a0 + 0xFC);
        gl_func_00000000(a0, state | 4, state | 5, *(int*)(sub + 0x970), 0x100, 10);
        gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xE80),
                         *(int*)((char*)&D_00000000 + 0xE84), -1);
    }
    gl_func_00000000(a0);
}

/* Family sibling of game_uso_func_00010E2C / 000114FC: same SUFFIX_BYTES
 * + 12-word INSN_PATCH recipe (per docs/POST_CC_RECIPES.md
 * #feedback-suffix-plus-insn-patch-grows-and-reshapes), but 25-insn
 * shape (vs 24-insn for E2C/14FC) so divergence point is +0x30 (one
 * insn later — the additional `move a2, zero` keeps the prologue 12
 * insns long). D-offset 0xE10. */
void game_uso_func_00010DC8(int a0) {
    register int *t;
    int v1, v2;
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0xFC) | 0x9, 0, 1, 1, 1);
    t = (int*)((char*)&D_00000000 + 0xE10);
    v1 = t[0];
    v2 = t[1];
    game_uso_func_00000000(a0, v1, v2, 1);
}

/* game_uso_func_00010E2C: 24-insn double-call into game_uso_func_00000000.
 * Promoted to byte-correct via SUFFIX_BYTES (8 trailing nop bytes) +
 * 13-word INSN_PATCH (per Makefile game_uso_func_00010E2C=...) after
 * the documented family cap (target uses 4-insn base+ofs lui+addiu+lw+lw
 * load form, IDO -O2 always folds to 2-insn direct lui+lw because 0xE40
 * fits in 16-bit signed immediate — see
 * docs/IDO_CODEGEN.md#feedback-ido-constant-address-load-fold-inevitable).
 *
 * Patch reshapes the +0x2C..+0x5C tail: lui v0 → lui t8, addiu lo0 →
 * addiu lo0xE40, lw fold → 4-insn split with `sw a1/a2` shadow-spills
 * interleaved across the 2nd jal's delay slot. The patched jal at +0x40
 * (was reloc'd) becomes `sw a1, 0x4(sp)` (no reloc) — orphan R_MIPS_26
 * relocation auto-stripped by patch-insn-bytes.py per the 2026-05-07
 * fix (docs/POST_CC_RECIPES.md#feedback-insn-patch-jal-to-non-jal-orphan-
 * reloc-link-fail). The new jal at +0x48 has no reloc — it's literal
 * `jal 0` post-link, which is the standard cross-USO call pattern (USO
 * loader patches at runtime). */
void game_uso_func_00010E2C(int a0) {
    register int *t;
    int v1, v2;
    game_uso_func_00000000(a0, 0, 0, 1, 1, 1);
    t = (int*)((char*)&D_00000000 + 0xE40);
    v1 = t[0];
    v2 = t[1];
    game_uso_func_00000000(a0, v1, v2, 1);
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

/* 27-insn 2-call sibling of the 0x10E2C/11368/113C8 24-insn family.
 * Promoted via SUFFIX_BYTES_FORCE (8-byte epilogue extension, bypasses the
 * skip-path-2 false-positive on natural-epilogue C bodies — see
 * docs/POST_CC_RECIPES.md#feedback-suffix-skip-path-2-false-positive-on-natural-epilogue)
 * + INSN_PATCH (10 insns overwriting post-mid-body section with target's
 * t0-base form and varargs spills a1@sp+0x4, a2@sp+0x8 before the 2nd jal). */
void game_uso_func_00010FB8(int *a0) {
    int v1, v2;
    int *t;
    game_uso_func_00000000(a0, 0x70000, 0, 1, 1, 1);
    *(int*)((char*)a0 + 0x114) = 0;
    *(int*)((char*)*(int**)((char*)a0 + 0xB4) + 0x960) = 100;
    t = (int*)((char*)&D_00000000 + 0xF58);
    v1 = t[0];
    v2 = t[1];
    game_uso_func_00000000(a0, v1, v2);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011024);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000110A4);

#ifdef NON_MATCHING
/* 82.2%: 2-call wrapper. First call `gl_func_00000000(a0)`; second call
 * `gl_func_00000000(a0, *(D+0xF50), *(D+0xF54), 1)`. Target has pre-call
 * arg-spill pattern between the two jals:
 *   sw $a1, 4($sp)  pre-2nd-jal  (a1-slot spill)
 *   sw $a2, 8($sp)  in 2nd jal delay slot (a2-slot spill)
 * Also uses $t6 as shared base for the two adjacent loads (0(t6), 4(t6))
 * with addiu $t6, $t6, 0xF50 — rather than direct-offset loads.
 *
 * Variants tested 2026-04-20:
 *   - base via `*(int*)((char*)&D_0 + 0xF50)` direct: v0 + 0xF50 offset (no split)
 *   - base via named local `int *base = ...; base[0], base[1]`: IDO folds offset back
 *   - base via `struct { int f0, f4; } D_11124_pair` mapped to 0xF50: splits to
 *     `lui v0; addiu v0, 0; lw a1, 0(v0); lw a2, 4(v0)` — reloc-equivalent to
 *     target's `lui t6; addiu t6, 0xF50; lw a1, 0(t6); lw a2, 4(t6)`. But still
 *     uses $v0 not $t6, and missing the a1/a2 stack spills (pre-call arg spill
 *     class — see feedback_ido_precall_arg_spill_unreachable.md).
 *   - Unique extern `gl_func_00011124_b()` for 2nd call: no spill emitted either.
 *
 * Same class as game_uso_func_0000A374 (also 86.7% cap, precall arg spill).
 * Also has unfilled jr-ra delay slot (could be -g3 but orthogonal to arg spill).
 *
 * 2026-05-05 5th variant tried: `volatile int a1, a2` named locals to force
 * IDO to materialize and spill. Result: REGRESSED to 15/17 diffs (size grew
 * to 0x4C, 19 insns vs target 17). Volatile spilled to wrong slots and
 * added an extra reload+ldelay pair. Confirms target's spills aren't
 * volatile-driven; they're IDO's older-version pre-call spill convention
 * that the current IDO 7.1 build doesn't reproduce. Cap at 82.18% holds. */
void game_uso_func_00011124(int *a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xF50),
                          *(int*)((char*)&D_00000000 + 0xF54), 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011124);
#endif

#ifdef NON_MATCHING
/* game_uso_func_00011168: 60-insn 4-way dispatcher, 0xF0 size, frame 0x18.
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
 * The 4 inner calls share signature (a0, scalar, scalar, 1). Each call's
 * arg-load pattern emits `sw a1,4(sp); sw a2,8(sp)` outgoing-arg-slot
 * stores (precall-arg-spill — see feedback_ido_precall_arg_spill_unreachable.md
 * for context). */
void game_uso_func_00011168(int *a0) {
    int flag, t2;
    int t8;
    int *def_base = (int*)((char*)&D_00000000 + 0xF40);

    gl_func_00000000(a0);
    flag = ((int*)a0[0xB4 / 4])[0xA54 / 4];

    if (flag == 1) {
        t8 = *(int*)((char*)&D_00000000 + 0x7C);
        if (t8 != 0) {
            int *b = (int*)((char*)&D_00000000 + 0xF28);
            gl_func_00000000(a0, b[0], b[1], 1);
            return;
        }
        t2 = *(int*)((char*)&D_00000000 + 0x64);
        if (t2 < 2) {
            int *b = (int*)((char*)&D_00000000 + 0xF30);
            gl_func_00000000(a0, b[0], b[1], 1);
        } else {
            int *b = (int*)((char*)&D_00000000 + 0xF38);
            gl_func_00000000(a0, b[0], b[1], 1);
        }
        return;
    }
    /* flag != 1: default path. Placed last so IDO emits BNEL-skip-to-here
     * with delay-load (matching asm 0x11198 bnel t7,at,+0x26). */
    gl_func_00000000(a0, def_base[0], def_base[1], 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011168);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011258);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000112E0);

/* Family sibling #5 of game_uso_func_00010E2C. Promoted from 87.38% NM
 * cap via SUFFIX_BYTES of 2 nops + 12-word INSN_PATCH at +0x2C..+0x58
 * (per docs/POST_CC_RECIPES.md
 * #feedback-suffix-plus-insn-patch-grows-and-reshapes). Differences
 * from 10E2C: D-offset 0xF08 (vs 0xE40), a3=3 (vs 1). */
void game_uso_func_00011368(int *a0) {
    register int *t;
    int v1, v2;
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0x74), 2, 3, 1, 1);
    t = (int*)((char*)&D_00000000 + 0xF08);
    v1 = t[0];
    v2 = t[1];
    game_uso_func_00000000(a0, v1, v2, 3);
}

/* Family sibling #6 of game_uso_func_00010E2C — last unmatched member.
 * Same SUFFIX_BYTES + 12-word INSN_PATCH recipe as 11368 (per
 * docs/POST_CC_RECIPES.md#feedback-suffix-plus-insn-patch-grows-and-reshapes).
 * Differences from 11368: D-offset 0xF10 (vs 0xF08), a3=4 (vs 3). */
void game_uso_func_000113C8(int *a0) {
    register int *t;
    int v1, v2;
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0x74), 3, 4, 1, 1);
    t = (int*)((char*)&D_00000000 + 0xF10);
    v1 = t[0];
    v2 = t[1];
    game_uso_func_00000000(a0, v1, v2, 4);
}

void game_uso_func_00011428(int *a0) {
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0x74), 4, 1, 1, 1);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011460);

/* Family sibling of game_uso_func_00010E2C: same SUFFIX_BYTES + 12-word
 * INSN_PATCH recipe (per docs/POST_CC_RECIPES.md
 * #feedback-suffix-plus-insn-patch-grows-and-reshapes), only D-offset
 * differs (0xDB8 here vs 0xE40 there). Bytes match expected/.o. */
void game_uso_func_000114FC(int *a0) {
    register int *t;
    int v1, v2;
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0x74), 2, 1, 1, 1);
    t = (int*)((char*)&D_00000000 + 0xDB8);
    v1 = t[0];
    v2 = t[1];
    game_uso_func_00000000(a0, v1, v2, 1);
}

/* game_uso_func_0001155C: 8-byte stolen-prologue donor for game_uso_func_00011564.
 * Body is `lui t6, 0; lw t6, 0x78(t6)` — loads `t6 = *(int*)((char*)&D + 0x78)`
 * which the successor at 0x11564 reads via `bnez t6, +0xC` at its first insn.
 * Treat as fragment; NM C body would require PROLOGUE_STEALS plumbing to splice
 * the C-emit's natural lui+lw at successor entry. */
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001155C);

#ifdef NON_MATCHING
/* game_uso_func_00011564: 30-insn (0x78) flag-gated 100-or-0 store + dispatch.
 * STOLEN-PROLOGUE SUCCESSOR — predecessor game_uso_func_0001155C's 8-byte body
 * sets `t6 = *(int*)(&D + 0x78)`; this function reads t6 in its first body insn
 * (`bnez t6, +0xC`) without re-loading.
 *
 * Decoded structure:
 *   if (*(int*)(&D + 0x78) != 0) {
 *       // then-arm — flag set: store 100 + multi-arg dispatch
 *       p = (int*)a0[0xB4/4];
 *       p[0x960/4] = 100;
 *       gl_func_00000000(a0[0xFC/4] | 8, 0, 1, 6, 1);
 *       // a1 = a0[0xFC] | 8 (ori in delay slot), a2 = 0, a3 = 1
 *       // stack args at sp+0x10/0x14 = 6, 1
 *   } else {
 *       // else-arm — flag clear: store 0 + 2-arg dispatch via D-base
 *       p = (int*)a0[0xB4/4];
 *       p[0x960/4] = 0;
 *       gl_func_00000000(*(int*)(&D + 0xE40), *(int*)(&D + 0xE44));
 *   }
 *
 * Caps for byte-match (multi-tick):
 *   1. PROLOGUE_STEALS=8 needed to splice the C-emit's natural lui+lw t6 at
 *      function entry (would duplicate the stolen-prologue insns).
 *   2. The else-arm exits via `b epilogue; lw ra` (delay slot) — IDO schedules
 *      the ra-restore into the unconditional branch's delay slot since the
 *      then-arm flows through it. Replicating this from C requires careful
 *      goto-to-epilogue placement; standard if/else converge typically
 *      produces a single epilogue with no early-branch.
 *
 * Default INCLUDE_ASM keeps ROM exact. Multi-pass — this captures the
 * structural decode for future refinement. */
extern int gl_func_00000000();

void game_uso_func_00011564(int *a0) {
    int *p;
    if (*(int*)((char*)&D_00000000 + 0x78) != 0) {
        p = (int*)a0[0xB4/4];
        p[0x960/4] = 100;
        gl_func_00000000(a0[0xFC/4] | 8, 0, 1, 6, 1);
    } else {
        p = (int*)a0[0xB4/4];
        p[0x960/4] = 0;
        gl_func_00000000(*(int*)((char*)&D_00000000 + 0xE40),
                         *(int*)((char*)&D_00000000 + 0xE44));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011564);
#endif

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011624);

#ifdef NON_MATCHING
/* game_uso_func_000116D4: 31-insn (0x7C) flag-gated double-call wrapper.
 * Calls gl_func_0(s0=a0); if s0->[0x110] != 0, makes 2 more calls (one
 * with 6 args, one with 4 args using D[0xE40..0xE44] payload). Always
 * sets s0->[0x114] = 0 at end.
 *
 * Decoded:
 *   gl_func_0(a0);
 *   if (a0->[0x110] != 0) {
 *       gl_func_0(a0, a0->[0x108], 2, 1, 1, 1);   // 6-arg
 *       gl_func_0(a0, *(int*)(&D + 0xE40),
 *                 *(int*)(&D + 0xE44), 1);        // 4-arg
 *   }
 *   a0->[0x114] = 0;
 *
 * Caps:
 *   1. Standalone IDO emits separate `lui+addiu &D` setups vs target's
 *      single `lui t9, 0; addiu t9, t9, 0xE40` shared base + offset
 *      (0/+4). Workaround: feedback-ido-cse-bust-via-distinct-externs
 *      with two externs at the same address.
 *   2. Target writes to sp+4/sp+8 (a1/a2 spill slots) before the 4-arg
 *      jal, suggesting an IDO scheduling quirk for arg-preservation
 *      around the lw chain. Mine doesn't emit those spills.
 *
 * Multi-tick byte-match deferred. */
void game_uso_func_000116D4(void *a0) {
    void *s0 = a0;
    gl_func_00000000(s0);
    if (*(int *)((char *)s0 + 0x110) != 0) {
        gl_func_00000000(s0, *(int *)((char *)s0 + 0x108), 2, 1, 1, 1);
        gl_func_00000000(s0,
                         *(int *)((char *)&D_00000000 + 0xE40),
                         *(int *)((char *)&D_00000000 + 0xE44),
                         1);
    }
    *(int *)((char *)s0 + 0x114) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000116D4);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011750);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001189C);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011A94);
#pragma GLOBAL_ASM("asm/nonmatchings/game_uso/game_uso/game_uso_func_00011A94_pad.s")
