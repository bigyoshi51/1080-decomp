#include "common.h"

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000000);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000003F8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000052C);

void game_uso_func_000005B8(Vec3 *a0) {
    game_uso_func_000001D4(a0);
    game_uso_func_000001D4((Vec3*)((char*)a0 + 0xC));
    game_uso_func_000001D4((Vec3*)((char*)a0 + 0x18));
    game_uso_func_00000244((float*)((char*)a0 + 0x24));
    game_uso_func_00000280((int*)((char*)a0 + 0x28));
    game_uso_func_000001D4((Vec3*)((char*)a0 + 0x2C));
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000608);

#ifdef NON_MATCHING
/* 89.1% match. Reader-init + grow-array wrapper (47 insns).
 *
 * Body decoded: reads 6 typed accessors from D_00000000 into fields of
 * a0 (Quad4 at +0x0, Quad4 at +0x10, Pair2 at +0x20, Pair2 at +0x28,
 * int at +0x30, int at +0x34). Field +0x34 is a count. Then loops
 * 1..cnt, each iteration: (1) gl_func(0x38) → stored at &p[14]
 * (where p starts at a0+4 and increments by 4 per iter — i.e. a growable
 * int[] list starting at a0+0x3C); (2) gl_func(p[14]); (3) gl_func(p[14]).
 * Tail copies a0[0x3C] → a0[0x38] and shifts (a0+cnt*4)[+0x38] → [+0x3C].
 *
 * Remaining 11% gap:
 *   - Target's cnt lives in $v0, mine in $v1 (fresh lw after jal retval
 *     clobber — IDO's decision differs based on downstream usage)
 *   - Target's `addu v1, s2, t7` vs mine `addu v0, t7, s2` (commutative
 *     operand order at tail — triggered by the $v0/$v1 flip above)
 *   - Target declares `s1=1` before `s0=a0+4`; mine emits them swapped
 *     (statement-order vs allocation-order mismatch for $s-regs)
 *
 * These are IDO register-allocation details, not logic. Next-pass:
 * permuter on this with a few PERM_GENERAL / PERM_LINESWAP variants. */
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
            *(int*)((char*)p + 0x38) = gl_func_00000000(0x38);
            gl_func_00000000(*(int*)((char*)p + 0x38));
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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000858);

void game_uso_func_000008FC(int *a0) {
    int *v0 = (int*)*(int*)((char*)a0 + 0xF4);
    gl_func_00000000(*(int*)((char*)v0 + 0xB4), a0);
    gl_func_00000000(*(int*)((char*)a0 + 0x154), a0);
    *(int*)((char*)a0 + 0x264) = 0;
    gl_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000940);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000B3C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001644);

void game_uso_func_00001714(int a0, int *a1) {
    int v = *a1;
    if (v == 8 || v == 9) {
        gl_func_00000000(a0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000174C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000018FC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001D30);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000044F4);

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

/* game_uso_func_00005924: 0x110C (1100 insns, 4.3 KB) — strategy-memo spine
 * candidate #2 (~29 cross-USO calls).  0x1D0-byte stack frame.
 *
 * ENTRY PROLOGUE (insns 1-5 @ 0x5924-0x5934):
 *   addiu sp, -0x1D0
 *   sw    s0, 0x20(sp)
 *   or    s0, a0, 0          ; spill $a0 to $s0 (used throughout)
 *   bne   t6, zero, 0x6A1C   ; <-- ODDITY: $t6 is uninitialized here!
 *   sw    ra, 0x24(sp)         ; (bne delay slot)
 *
 * The bne reads $t6 before anything in this function writes it. Target
 * 0x6A1C is the epilogue (lw ra; lw s0; addiu sp,+0x1D0; jr ra; nop).
 * Possibilities: (a) original source declared `register int x asm("$t6")`
 * in a caller context; (b) caller leaked $t6 with a compile-time known
 * value; (c) this is a splat cross-function-code-sharing artifact where
 * most callers enter at a LATER address than 0x5924. Leave INCLUDE_ASM;
 * fix requires understanding the calling convention first.
 *
 * BODY STRUCTURE (rough): multiple `andi` mask extracts on a0[0x68] flag
 * byte (bit 0, bit 1, bit 2, bit 3 each gate a separate code block), then
 * falls through to a large per-frame update loop with cross-USO calls and
 * float math on a0+0x148..0x1C4 sub-buffers.
 *
 * Deferred: full decode requires typed struct for the 0x4E0-byte main
 * object (same struct constructed by game_uso_func_000044F4). Multi-run
 * decomp expected. */
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00005924);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006ECC);

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

/* game_uso_func_00007538: 0x560 (344 insns) — largest residue of the split-up
 * 0x7424 bundle (was bundled with 7424/7448/74D8/751C/7A98/7ABC, now alone).
 * Likely the "real" per-frame compute function per game_uso_map.md's heuristic.
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
 * REMAINING ~220 insns at 0x7708-0x7A98: arg1 & 0x02 arm, the merge block
 * at 0x7740 (which reads back flag_mask, does final state computation and
 * returns), and the flag2!=0 tail_case at 0x20C (that I first saw at
 * bnel @0x40). Next pass: arg1 & 0x02 arm + merge block body. */
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007538);

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
    if (v1 == NULL) return 0.0f;
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

/* game_uso_func_00009B88: 0x560 (344 insns), 0x1A8-byte stack frame.
 * Strategy-memo candidate for "per-frame compute" (1.4 KB, 11 cross-calls).
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
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00009B88);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C48C);

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

/* game_uso_func_0000D9CC: 0x830 (524 insns), 0x38-byte stack frame.
 * Strategy-memo spine: 2.0 KB, 26 cross-USO calls, "subsystem" subsystem.
 * Single function per grep -c 03E00008 (not a bundle).
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
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D9CC);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000EF20);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FABC);

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

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011124);

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

