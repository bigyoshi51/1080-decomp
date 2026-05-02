#include "common.h"

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
extern float D_00000000;
void game_uso_func_00000000(float *out, float t) {
    float omt = 1.0f - t;
    float t2 = t * t;
    float t3 = t2 * t;
    out[0] = D_00000000 * omt * omt * omt;
    out[1] = D_00000000 * (3.0f*t3 - 6.0f*t2 + 4.0f);
    out[2] = D_00000000 * (-3.0f*t3 + 3.0f*t2 + 3.0f*t + 1.0f);
    out[3] = D_00000000 * t3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000000);
#endif

#ifdef NON_MATCHING
/* 4-element dot product `a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + b[3]*a[3]`
 * (note last term swapped: matches target's load order b[3] then a[3]).
 * 16-insn leaf, returns float in $f0. ~94 % cap (15/16 insns match).
 * Remaining 1-insn diff: target's final add.s emits `add.s f0,f8,f10`
 * (last-product on left); IDO from natural source order produces
 * `add.s f0,f10,f8`. Tried `float r = ...; return b[3]*a[3] + r;` to
 * force ordering -- changed register allocation completely (worse).
 * Same arithmetic, different operand order on final reduction add. */
float game_uso_func_000000A0(float *a, float *b) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + b[3]*a[3];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000000A0);
#endif

#ifdef NON_MATCHING
/* Cubic B-spline weighted point evaluator (61 insns, FPU-only).
 * Input:  out (Vec3*),  ctrl (Vec3*[4]: 4 control point pointers),
 *         weights (float[4]: B0..B3 from game_uso_func_00000000)
 * Output: out[i] = sum over k=0..3 of (*ctrl[k])[i] * weights[k]
 *
 * Computes one Vec3 component triple as a 4-control-point weighted sum.
 * Three identical 14-insn dot-product blocks (one per x/y/z), each
 * loading 4 control-pointer dereferences + 4 weight loads, then 4 muls
 * and 3 adds. Followed by swc1 to out[0], out[4], out[8].
 *
 * Used together with game_uso_func_00000000 (basis evaluator producing
 * the weights) to compute a point on a uniform cubic B-spline curve in
 * 3D — likely camera path / track / skater limb interpolation. */
typedef struct { float x, y, z; } Vec3;
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

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
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

extern int gl_func_00000000();
extern char D_00000000;
void game_uso_func_00000244(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

extern int gl_func_00000000();
extern char D_00000000;
void game_uso_func_00000280(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

typedef struct { int a, b, c, d; } Quad4;
void game_uso_func_000002BC(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b; } Pair2;
void game_uso_func_00000314(Pair2 *dst) {
    Pair2 buf;
    gl_func_00000000(&D_00000000, &buf, 8);
    *dst = buf;
}

#ifdef NON_MATCHING
/* 98.1%: int-reader with pointer-indirect load (volatile int buf[2] trick).
 * Remaining 2 %: register choice. Target uses t7/t9/t6 (skipping t8);
 * ours allocates t6/t7/t8 sequentially. 7+ variants can't flip allocator
 * to skip t8. See feedback_ido_volatile_buf_pointer_indirect.md. */
void game_uso_func_0000035C(int *dst) {
    volatile int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000035C);
#endif

void game_uso_func_0000039C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_uso/game_uso/game_uso_func_0000039C_pad.s")

#ifdef NON_MATCHING
/* Camera/view init function. Initializes a 0x38-byte struct at $a0:
 *   a0+0x00..0x08 = Vec3(0, 0, 0)        ; eye position
 *   a0+0x0C..0x14 = Vec3(0, 0, -1000)    ; target / look-at (z = -1000)
 *   a0+0x18..0x20 = Vec3(0, 1, 0)        ; up vector (Y-up)
 *   a0+0x24       = 85.0f                ; FOV (degrees)
 *   a0+0x28       = 15 (int)             ; mode/flags
 *   a0+0x2C..0x34 = Vec3(0, 0, 0)        ; offset
 *
 * 77-insn FPU/stack-init function (size 0x134, no jal).
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

#ifdef NON_MATCHING
/* 93.86 % match. State-check function: returns 1 if any of:
 *   (a0[0]==2 || a0[0]==3) && a0[1]==1
 *   (a0[4]==2 || a0[4]==3) && a0[5]==1
 *   a0[8]==1, a0[10]==2, a0[12]==2
 *
 * IDO emits each `==` test as `xor; sltiu` (boolean compute) rather than
 * direct branch — this is the natural emit for a single-expression
 * boolean return chain. Using `if (cond) return 1;` chain regressed to
 * 20 % (multiple jr-ra epilogues, completely different shape).
 *
 * Remaining 6 % cap: $v0 vs $v1 register flip throughout. Mine loads
 * a0[0] into $v1, computes boolean result in $v0. Target loads into $v0,
 * computes boolean in $v1. Same arithmetic, swapped register naming.
 * Likely not C-flippable without inline-asm; IDO's v0/v1 choice for
 * load-target vs result-target is fixed by the expression-tree walker. */
int game_uso_func_00000674(int *a0) {
    return ((a0[0] == 2 || a0[0] == 3) && a0[1] == 1)
        || ((a0[4] == 2 || a0[4] == 3) && a0[5] == 1)
        || a0[8] == 1
        || a0[10] == 2
        || a0[12] == 2;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000674);
#endif

#ifdef NON_MATCHING
/* 90% match. Prior commit 764b62d landed this as "100%" but that was
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
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000724);
#endif

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
/* 67.4 % match. 8-arg constructor/initializer (4 reg + 4 stack args).
 *   void *f(T *a0,    // dst, alloc 0x27C if NULL
 *           int a1,   // -> a0->0x150 post-init
 *           int a2,   // -> 1st gl_func arg
 *           int a3,   // -> 2nd gl_func arg
 *           int arg4, // -> 3rd gl_func arg
 *           float arg5,  // -> 4th gl_func arg (FLOAT!)
 *           int arg6, // -> a0->0x274 post-init
 *           int arg7) // flag: if !=0, gl_func(a0, 1) midway
 *
 * Logic + writes done; the remaining 32 % cap is two structural issues:
 *   1. arg5 is a stack-passed float. Target uses lwc1+swc1 (4-byte float
 *      pass-through). My int-bits workaround uses lw+sw (same bytes BUT
 *      different opcodes). Declaring arg5 as `float` triggers K&R
 *      promote-to-double via cvt.d.s+sdc1 (8-byte stack store) which is
 *      WORSE. Per feedback_ido_knr_float_call.md: K&R-declared
 *      gl_func_00000000 can't accept float without promotion.
 *   2. Branch order: my `if (a0 != 0) skip; alloc; if (alloc fail) skip
 *      to end; else continue` emits 2 separate bne+beq pairs vs target's
 *      single beq-to-end-after-alloc-fail.
 *
 * Need a unique-extern variant of gl_func_00000000 with explicit
 * (int*, int, int, int, float) prototype to break K&R promotion (per
 * feedback_usoplaceholder_unique_extern.md technique). */
int *game_uso_func_00000858(int *a0, int arg1, int arg2, int arg3, int arg4, int arg5_bits, int arg6, int arg7) {
    if (a0 == 0) {
        a0 = (int*)gl_func_00000000(0x27C);
        if (a0 == 0) return a0;
    }
    gl_func_00000000(a0, arg2, arg3, arg4, arg5_bits);
    *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
    *(int*)((char*)a0 + 0x1D0) = 0;
    *(int*)((char*)a0 + 0x24C) = 0;
    if (arg7 != 0) {
        gl_func_00000000(a0, 1);
    }
    *(int*)((char*)a0 + 0x150) = arg1;
    *(int*)((char*)a0 + 0x26C) = 0;
    *(int*)((char*)a0 + 0x270) = 0;
    *(int*)((char*)a0 + 0x268) = 0;
    *(int*)((char*)a0 + 0x274) = arg6;
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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000940);

void game_uso_func_00000AEC(int *a0, int a1) {
    if (*(int*)((char*)*(int**)((char*)a0 + 0x158) + 0x24) > 0) {
        *(int*)((char*)a0 + 0x250) = a1;
    }
    *(int*)((char*)a0 + 0x254) = 0;
    *(int*)((char*)a0 + 0x25C) = 1;
    *(int*)((char*)a0 + 0x260) = 0;
}

#ifdef NON_MATCHING
/* game_uso_func_00000B3C: 0xB08 (706 insns, 2.8 KB) — spine candidate #6.
 * 22 cross-USO calls, 0x150-byte frame. Contains a jump-table switch at
 * 0xDB8 (`jr $t1` after `lw $t1, 0x50($at)`) — per
 * feedback_ido_switch_rodata_jumptable.md that .rodata path is discarded
 * by 1080's linker; match requires if-else or if-goto chain rewrite.
 *
 * Partial C below captures decoded entry (~first 30 insns): id-change
 * detect + 3-level LUT navigation. Remaining ~670 insns TODO.
 *
 * Struct fields identified:
 *   a0[0xF4]  — per-frame scratch (cached at sp+0x134)
 *   a0[0x150] — dispatch-list ptr
 *   a0[0x158 + N*4] — primary LUT of sub-obj ptrs
 *   a0[0x1D4 + N*4] — tertiary LUT of target ptrs
 *   a0[0x250] — primary index
 *   a0[0x254] — secondary index
 *   a0[0x258] — derived-id writeback
 *   a0[0x25C] — tertiary index
 *   a0[0x264] — cached-id (change detector)
 *   (dispatch_list + 0xA54) — current id
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
    /* TODO(next pass): decode 0xBB0-0xD00 Vec3 math + switch-arm
     * addresses at 0xDC0/0xDF0/... Arm offsets live in rodata at
     * %hi/%lo($at) — need to read them from baserom's rodata. */
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000B3C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001644);

void game_uso_func_00001714(int a0, int *a1) {
    int v = *a1;
    if (v == 8 || v == 9) {
        gl_func_00000000(a0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000174C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000018FC);

#ifdef NON_MATCHING
/* 95.9 %: 4-arg constructor-or-init for 0x124-byte object. Decoded structure:
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
 * Leaving as INCLUDE_ASM until the next pass produces enough decoded body
 * to be worth wrapping. Committing this comment IS the forward progress
 * per the skill's "NM wrap with whatever partial C you get" rule — a stub
 * void function would report ~0 % match and not compile-test meaningfully. */
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001DDC);

#ifdef NON_MATCHING
/* 54% match. 3x3 matrix-vector multiply: dst = M * v, where M is at
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
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000023D4);
#endif

extern void game_uso_func_00000000();

void game_uso_func_0000249C(char *a0) {
    game_uso_func_00000000(a0 + 0x44);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000024BC);

void game_uso_func_00002714(int *a0, int a1, int a2) {
    if (*(int*)((char*)a0 + 0x40) == a1) return;
    *(int*)((char*)a0 + 0x40) = a1;
    game_uso_func_00000000(a0, a2);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002744);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002814);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003018);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000034A4);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003A28);
#pragma GLOBAL_ASM("asm/nonmatchings/game_uso/game_uso/game_uso_func_00003A28_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003AC0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003ED4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003FAC);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000041C0);

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
 * sub-object allocation loop, type the GameState struct, then refine. */
void game_uso_func_000044F4(void *a0, int a1, int a2) {
    (void)a0; (void)a1; (void)a2;
    /* TODO: allocate 0x4E0 if a0 == NULL; init sub-objects from templates
     * at &D_0+0x6D0, &D_0+0x6D8, &D_0+0x6E8, &D_0+0x3C8 (et al.);
     * recursive child alloc at a0->field_28, a0->field_2C, etc. */
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
 * at 0x5998 with Vec3 staging and hasn't been attempted yet. */
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

    /* TODO: 1000+ insns of body-proper. Reads a0->0x30 (sub-struct
     * pointer) and stages Vec3 fields 0xB4/0xB8/0xBC onto sp+0x1B8;
     * large FPU-heavy update loop with cross-USO calls. */
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000591C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006A30);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006CF0);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006F38);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006FA8);

void game_uso_func_000071A4(int *a0) {
    *(int*)((char*)a0 + 0x64) = 1;
    *(int*)((char*)a0 + 0x70) = 0;
    if (*(int*)((char*)a0 + 0x4C4) > 0) {
        gl_func_00000000(a0);
        *(int*)((char*)a0 + 0x4C4) = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000071E0);

void game_uso_func_00007424(void *a0) {
    *(int*)((char*)a0 + 0x64) = 3;
    gl_func_00000000(a0);
}

#ifdef NON_MATCHING
/* Inverse of game_uso_func_000074D8: pulls 4 floats from table (+0x30 deref)
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
 * Partial C body below: ~20 % match guess. Captures prelude + dispatch
 * outline + epilogue; many arm bodies are TODO-stubbed with correct
 * control-flow targets but no per-bit state mutations yet. Next pass
 * should compare objdiff output per-arm and fill in the TODO placeholders
 * embedded in each arm.
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
void game_uso_func_00007538(int *a0, int a1) {
    int ret_lo = 0;
    int a1_saved = a1;
    int counter, flags, flag2;
    int *outer;
    float f0 = 0.0f, f2 = 0.0f, f_tmp;

    counter = a0[0x50 / 4];
    if (counter > 0) a0[0x50 / 4] = counter - 1;
    flags = a0[0x48 / 4];
    if ((flags & 0x10) == 0) a0[0x48 / 4] = flags - 1;

    flag2 = a0[0x6C / 4];
    if (flag2 != 0) goto trunk;

    /* ==== DISPATCH CASCADE (flag2 == 0) ==== */
    if (a1 & 0x10) {
        outer = (int*)a0[0x30 / 4];
        if (outer[0x938 / 4] != 0) {
            f_tmp = *(float*)&a0[0x38 / 4];
            *(float*)&a0[0x3C / 4] = (f_tmp >= 0.0f) ? 1.0f : -1.0f;
        }
    }
    a1 = a0[0x6C / 4];

    if (a1 & 0x01) {
        if (flags != 0) goto check_40;
        a0[0x6C / 4] = a1 | 0x01;
        a0[0x44 / 4] = 91;
        goto trunk;
    }
check_40:
    if (a1 & 0x04) {
        a0[0x6C / 4] = a1 | 0x40;
        a0[0x44 / 4] = 13;
        goto trunk;
    }
    if (a1 & 0x20) {
        if (counter != 0) goto check_80;
        /* arg1 & 0x04 arm: reset counter + set f2 = 1.0f, retHi = 1 */
        a0[0x50 / 4] = 8;
        f2 = 1.0f;
        /* retHi handling omitted — stored to v1 path */
        goto trunk;
    }
check_80:
    if (a1 & 0x80) {
        /* arg1 & 0x20 arm body: fabs(outer->0xB4) % 9 */
        outer = (int*)a0[0x30 / 4];
        f_tmp = *(float*)&outer[0xB4 / 4];
        if (f_tmp < 0.0f) f_tmp = -f_tmp;
        a0[0x44 / 4] = 60;
        a0[0x58 / 4] = (int)f_tmp % 9;
        goto trunk;
    }
    if (a1 & 0x100) {
        /* arg1 & 0x80 arm body */
        a0[0x6C / 4] = a1 | 0x80;
        a0[0x4C / 4] = 0;
        a0[0x44 / 4] = 2;
        goto trunk;
    }
    if (a1 & 0x08) {
        outer = (int*)a0[0x30 / 4];
        if (outer[0x938 / 4] == 0) {
            f2 = -1.0f;
            goto trunk;
        }
        /* else: outer->0x938 != 0 — different path — TODO */
    }
    if (a1 & 0x02) {
        outer = (int*)a0[0x30 / 4];
        if (outer[0x938 / 4] != 0) {
            ret_lo |= 0x400;
            if (a1 & 0x100) {
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
        ret_lo |= 0x100;
        counter = a0[0x44 / 4] - 1;
        a0[0x44 / 4] = counter;
        if (counter == 0) {
            a0[0x6C / 4] &= ~0x40;
            goto ret;
        }
    }
    /* TODO: bits 0x20, 0x80, 0x100, 0x08, 0x04, 0x10 — see asm 0x77A0-0x7A08 */

ret:
    /* epilogue: store ret_lo into outer->field_800->field_40 (0x7A88-0x7A94) */
    outer = (int*)a0[0x30 / 4];
    ((int*)outer[0x800 / 4])[0x40 / 4] = ret_lo;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007538);
#endif

#ifdef NON_MATCHING
/* 9 insns. Decoded semantics:
 *   table = a0->0x30
 *   v1 = table[0x908]
 *   if (v1 != NULL) return v1[0xBC] - table[0xBC]
 *   else return 0.0f
 *
 * TRICKY: target uses `beql v1, zero, +7 (.+0x28)` whose target at 0x7AC0
 * lies PAST this function's declared end (0x7ABC) — it lands in the
 * adjacent function game_uso_func_00007ABC at its 2nd insn (nop before
 * jr ra). Effectively this function and 7ABC share the "return 0.0f"
 * tail. This cross-function tail-share is unreproducible from standalone
 * C — any if-returns-0 emits its own epilogue. Keep INCLUDE_ASM; the
 * decoded body above is source-of-truth for what it computes. */
float game_uso_func_00007A98(char *a0) {
    char *table = *(char**)(a0 + 0x30);
    char *v1 = *(char**)(table + 0x908);
    if (v1 == 0) return 0.0f;
    return *(float*)(v1 + 0xBC) - *(float*)(table + 0xBC);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007A98);
#endif

#ifdef NON_MATCHING
/* ~50%: returns 0.0f via $f2 intermediate (mtc1 $0,$f2; mov.s $f0,$f2) —
 * IDO -O2 always folds `return 0.0f` / `float x=0; return x;` etc. to direct
 * mtc1 $0,$f0. The extra `nop` between mtc1 and jr suggests a pipeline stall
 * or source idiom that isn't recoverable from any tested 4-insn C body
 * (2026-04-20: tested 13+ variants: literal, local, volatile, negate, cast,
 *  union punning, arg-ignore). Likely permuter-only. */
float game_uso_func_00007ABC(void) {
    return 0.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007ABC);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007ACC);

/* game_uso_func_00007C1C: 0x10BC (1071 insns, 4.3 KB) — strategy-memo spine #3.
 * 0x3B0-byte stack frame (944 bytes — huge local storage).
 *
 * SIGNATURE (5+ args): prologue spills $a0/$a1/$a3 back to caller slots at
 *   sp+0x3B0/0x3B4/0x3BC, and loads $s0 from sp+0x3C4 (= caller's arg-5
 *   stack slot, per O32 ABI). Saves $s0/$s1/$s2, $ra, and $f20/$f22/$f24
 *   (doubleword FP saves — heavy float math ahead).
 *
 *   f(arg0, arg1, arg2_in_s2, arg3, ..., arg5_ptr_in_s0)
 *
 * ENTRY LOGIC (insns 1-20 @ 0x7C1C-0x7C6C):
 *   s0 = arg5 (5th stack arg — a pointer)
 *   s2 = arg2
 *   if (s0 != 0) *s0 = 0.0f;   // zero the output accumulator through ptr
 *   (reload a3 into $t6)
 *   f24 = 0.0
 *   v1 = &local[0x38C]
 *   if (a3 != 0) branch to big block at +0x33*4 (another sub-check)
 *
 * Float math throughout: lwc1/swc1 to sp+0x348 and sp+0x38C regions
 * (looks like two Vec3 / quaternion slots). Multiple `jal 0` cross-calls
 * interspersed.
 *
 * Deferred: 1071 insns will not match in one tick. Multi-run tightening
 * expected. Body structure TBD in next pass. */
/* game_uso_func_00007C1C: 0x10BC (1083 insns, 4.3 KB) — strategy-memo spine
 * candidate #3 (~25 cross-USO calls).  0x3B0-byte (944 byte) stack frame.
 *
 * ENTRY PROLOGUE (insns 1-20 @ 0x7C1C-0x7C6C, 2026-04-20):
 *   addiu sp, -0x3B0        ; huge frame
 *   sw    s0, 0x38(sp)
 *   lw    s0, 0x3C4(sp)     ; s0 = caller's 5th arg (arg4, from caller slot
 *                             at sp+944+20 = 0x3C4)
 *   sw    s2, 0x40(sp)
 *   or    s2, a2, 0         ; s2 = a2 (3rd arg saved)
 *   sw    ra, 0x44(sp)
 *   sw    s1, 0x3C(sp)
 *   sdc1  $f24, 0x30(sp)    ; save callee-saved double regs
 *   sdc1  $f22, 0x28(sp)
 *   sdc1  $f20, 0x20(sp)
 *   sw    a0, 0x3B0(sp)     ; spill args to caller slots
 *   sw    a1, 0x3B4(sp)
 *   beq   s0, zero, +4 (→0x7C60)   ; if 5th arg is NULL, skip init
 *   sw    a3, 0x3BC(sp)      ; DELAY: also spill a3
 *   mtc1  zero, $f24         ; f24 = 0.0
 *   nop
 *   sdc1  $f24, 0(s0)        ; *(double*)s0 = 0.0
 *   ...
 *
 * Calling convention: takes 5 args (a0, a1, a2, a3, arg4-at-sp+0x3C4).
 * Uses callee-saved double regs $f20/$f22/$f24 — arithmetic-heavy.
 * 0x3C4 arg slot pattern suggests this is a per-frame transform function
 * receiving a destination buffer (arg4) for output.
 *
 * Deferred: full decode requires typed struct understanding. 1083 insns
 * with double-precision math and many cross-USO calls. Multi-run decomp. */
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007C1C);

/* game_uso_func_00008CD8: 0xB14 (709 insns), 0x210-byte stack frame.
 * Strategy-memo spine: 2.8 KB, 16 cross-USO calls, "subsystem".
 * Single function per grep -c 03E00008 (not a bundle).
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
 * (The entry dispatch reads a Vec3 from the caller's arg3 and stamps it
 * into a freshly-allocated/returned slot with Y-zeroed. Canonical
 * "project onto ground plane" / XZ-only position pattern used by 1080's
 * snow physics. 709 insns of alternating float math + 16 cross-USO
 * calls — this is the "subsystem" heart.)
 *
 * Deferred — needs multi-pass decomp with incremental struct typing.
 * This commit is the entry-dispatch doc per the skill's multi-run
 * convention. */
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00008CD8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000097EC);

#ifdef NON_MATCHING
/* game_uso_func_00009B88: 0x560 (344 insns), 0x1A8-byte stack frame.
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
 * Deferred to future passes: full body decode is ~300 insns of float sched;
 *   one /decompile run expands prologue + body-part-1 — subsequent runs will
 *   tighten the dispatch logic and body math. The dual Vec3-copy entry
 *   strongly suggests this is a coordinate-transform function: takes
 *   (context, anchor, src-Vec3) and produces a transformed Vec3 written to
 *   one of several local slots for downstream cross-USO dispatch. */
void game_uso_func_00009B88(int *a0, int *a1, int *a2) {
    float local_190[3];   /* sp+0x190: 3-float buffer, written at entry */
    float local_DC[3];    /* sp+0xDC:  second 3-float buffer for scaled src */
    int *v0, *v1;
    float src_x, src_z;

    if (a2 == 0) {
        /* Assert: line 0x623 (1571) — panic message at &D+0x7BC / &D+0x7C8 */
        gl_func_00000000(&D_00000000 + 0x7BC, &D_00000000 + 0x7C8, 0x623);
    }

    /* Dispatch 1: first cross-call with &local_190 as arg2 */
    v1 = local_190;
    if (v1 == 0) {  /* trivially false — v1 is stack addr */
        /* dead path */
    } else {
        v0 = (int*)gl_func_00000000(a2, 0xC);  /* 2nd cross-call, size=12 */
        if (v0 != 0) {
            /* Vec3 XZ-projection: copy a2->0x30.{x,z}, zero out Y */
            src_x = *(float*)((char*)a2 + 0x30);
            src_z = *(float*)((char*)a2 + 0x38);
            *(float*)((char*)v0 + 0x4) = src_z;
            *(float*)((char*)v0 + 0x8) = 0.0f;  /* wait — target has E4620008/E4600000 */
            *(float*)((char*)v0 + 0x0) = 0.0f;  /* actually stores look like idx 0,4,8 */
            /* TODO: exact layout — target has */
            /*   swc1 f2, 0x4(v0); swc1 f2, 0x8(v0); swc1 f0, 0x0(v0) */
            /*   where f0 was loaded from a2+0x30 and f2 from a2+0x38 */
        }
    }

    /* Dispatch 2: second 3-float buffer at local_DC (sp+0xDC) — math-heavy */
    /* TODO: insns 0x9BF4-0x9C50 — produces a scaled/offset Vec3 from a1+0x30,
     * a1+0x38 against a2+0x30. Uses mtc1/mul.s/sub.s on $f8/$f10. */

    /* TODO: body-part-2 @ 0x9C54-0x10E8 — 300 insns of float math +
     * ~9 more cross-USO calls. Likely matrix/quaternion transform with
     * scale 250.0f and offset 50.0f constants. */
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00009B88);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A0E8);

#ifdef NON_MATCHING
/* 86.7%: body+control flow match; target has 2 pre-jal a1 spills:
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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AE1C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B274);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B424);

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
/* 90.2%: `char *base = a0` forces $s2 = arg0 reuse for 0x168 limit (target
 * trick). Still stuck: $s0/$s1 pair — target has counter→s0, ptr→s1; ours
 * has ptr→s0, counter→s1. Swapping `p += 0x24; i += 0x24;` order did NOT
 * flip allocation here (unlike what I thought when contaminated baseline
 * gave a false 100 %). See feedback_ido_loop_body_stmt_order_flips_allocno
 * — that memo's premise was wrong and should be retired. */
void game_uso_func_0000BF7C(char *a0) {
    int i;
    char *p;
    char *base;

    base = a0;
    game_uso_func_00000000(base + 0x224);
    game_uso_func_0000ADE0((int*)(base + 0x274));
    p = base + 0xB8;
    i = 0;
    do {
        game_uso_func_00000000(p);
        p += 0x24;
        i += 0x24;
    } while (i != 0x168);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BF7C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BFDC);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C12C);

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
/* SPINE constructor (game_uso_func_0000C48C, 0xD84 = 865 insns, 3.4 KB)
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
extern void *game_uso_func_0000C48C_TODO(void);
void *game_uso_func_0000C48C(void *a0, int a1) {
    return game_uso_func_0000C48C_TODO();
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C48C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D210);

void game_uso_func_0000D418(char *a0) {
    gl_func_00000000(a0 + 0x13C);
}

#ifdef NON_MATCHING
/* 97.5%: all logic correct; IDO allocates t6 before t7 for the two paired
 * reads (0xC0→0xC8 via $t6, 0xC4→0xCC via $t7), but target has t7 for the
 * 0xC0→0xC8 copy and t6 for the 0xC4→0xCC copy — registers SWAPPED.
 * Variants tried (2026-04-20, all produce t6/t7 in IDO-default order):
 *   (a) swap store order (0xCC first, then 0xC8): still t6 first-seen
 *   (b) 0xC8 copy BEFORE the -1000 stores, 0xCC copy AFTER: still t6 first
 *   (c) named locals `s32 a, b`: forces $v0/$v1 (wrong register class)
 * IDO's first-seen-gets-lowest-number rule is invariant to the stmt shapes
 * we can write from C. Target was likely compiled from source using
 * `register int x asm("$t7")` (GCC-only; IDO rejects per feedback_ido_no_gcc_register_asm.md).
 * Cap at 97.5 %, no further C-level fix known. */
void game_uso_func_0000D438(void *a0) {
    *(s32*)((char*)a0 + 0x64) = -1000;
    *(s32*)((char*)a0 + 0x68) = -1000;
    *(s32*)((char*)a0 + 0xC8) = *(s32*)((char*)a0 + 0xC0);
    *(s32*)((char*)a0 + 0xCC) = *(s32*)((char*)a0 + 0xC4);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D438);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D458);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D63C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D6E4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D74C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D7F4);

#ifdef NON_MATCHING
/* ~70 %: 17-insn conditional call. If (*(a0+0xB4))->field_990 != 0, call
 * gl_func_00000000(a0, *(D_00000E70), *(D_00000E74)). Target has 2 extra
 * stack spills (sw a1,4(sp); sw a2,8(sp)) which IDO -O2 doesn't produce
 * for this call shape with K&R-declared gl_func_00000000. Also register
 * chain differs (target: t6/t8/t7 via pointer-indirect; mine: v0/t6/v0).
 * Likely needs explicit call prototype + per-callsite spilling — close
 * cousin of feedback_ido_unspecified_args.md. */
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
/* game_uso_func_0000D9CC: 0x830 (524 insns), 0x38-byte stack frame.
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
 * Left as INCLUDE_ASM until enough body is decoded to support a
 * compile-testable skeleton. The entry decode is the forward progress
 * for this pass per the skill's multi-run decomp convention. */
void game_uso_func_0000D9CC(int *a0) {
    int local_28 = 0, local_2C = 0, local_30 = 1;
    int *inner;
    (void)local_28; (void)local_2C; (void)local_30;

    *(int*)((char*)a0 + 0x108) = 0;
    inner = (int*)a0[0xB4/4];

    if (*(float*)((char*)inner + 0x348) > 30.0f) {
        /* TODO: main body @ 0xDA10 — starts with a halfword load from
         * inner[0xA10], mask 0x01F0, branch on value, then a float
         * compare against 500.0f. Multiple 0x43FA... constants appear
         * (these are halfword masks or float bit patterns).
         * 26 cross-USO calls follow with state-machine dispatch. */
    } else {
        /* TODO: 30.0f-fail path @ 0xDBDC (far forward) — loads
         * constant 500.0f into $f0 at the branch's delay slot (via
         * `lui $at, 0x43FA`). Likely a secondary threshold check. */
    }
    /* TODO: remaining ~490 insns of float scheduling with mtc1 zero,
     * c.lt.s gates, and cross-USO dispatch. */
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D9CC);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E1FC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E35C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E564);

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
/* 4-call wrapper. Logic: call gl_func(a0); call gl_func(a0, D_E40, D_E44);
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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F360);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F424);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F49C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F514);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F5A8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F664);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F6D4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F8E8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F948);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FA54);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FB04);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FB7C);

void game_uso_func_0000FBF8(int *a0) {
    int v = *(int*)((char*)a0 + 0xFC);
    game_uso_func_00000000(a0, v | 2, v | 3,
        *(int*)((char*)*(int**)((char*)a0 + 0xB4) + 0x970), 0, 1);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FC34);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FD04);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FDCC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FEC8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FF48);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FFB8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001001C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010068);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010128);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000102CC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010408);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000104A4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001056C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000105DC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010650);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010694);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010840);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001094C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010A0C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010AC8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010B38);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010BAC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010C4C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010CF0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010DC8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010E2C);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010FB8);

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
 * Also has unfilled jr-ra delay slot (could be -g3 but orthogonal to arg spill). */
void game_uso_func_00011124(int *a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0xF50),
                          *(int*)((char*)&D_00000000 + 0xF54), 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011124);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011168);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011258);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000112E0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011368);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000113C8);

void game_uso_func_00011428(int *a0) {
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0x74), 4, 1, 1, 1);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011460);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000114FC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011564);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000116D4);

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

