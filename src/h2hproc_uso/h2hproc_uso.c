#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000000);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_0000000C);

void h2hproc_uso_func_00000014(int *a0, int a1) {
    a0[a1]++;
}

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_0000002C);

void h2hproc_uso_func_0000020C(int *a0) {
    int saved = gl_func_00000000(2);
    a0[2] = gl_func_00000000(8);
    gl_func_00000000(saved);
    *a0 = 0;
    *(int*)((char*)&D_00000000 + 0x14C) = 0;
    *(int*)a0[2] = 0;
    *(int*)(a0[2] + 4) = 0;
    *(int*)((char*)&D_00000000 + 0x68) = 0;
}

void h2hproc_uso_func_00000274(int *a0) {
    gl_func_00000000((int*)a0[2]);
    a0[2] = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso/h2hproc_uso_func_00000274_pad.s")

#ifdef NON_MATCHING
/* 97.95%: 3-call orchestrator with 2 side-effect stores.
 *   call 1: gl_func_00000000(*(int*)(&D_00000000 + 4))
 *   (*(int*)(&D_00000000 + 0x40)) = 5; call 2: gl_func_00000000(&D_00000000)
 *   (*(int**)&D_00000000)->0x30 = 0; call 3: gl_func_00000000(*(int*)&D_00000000, -1, 0)
 *
 * Variants tested 2026-04-20 (none improved match, some REGRESSED):
 *   v2: `int *d = (int*)&D_0; d[0x10] = 5; gl_func(d)` — same output as
 *       original (31 insns). Using a named `d` local doesn't affect codegen.
 *   v3: `register char *base = &D_0;` + use `base` throughout — FIXES the
 *       delay-slot `sw t6, 0x40(a0)` pattern (lui+addiu directly into a0,
 *       matches target first half). But second half EXPANDS: base isn't
 *       kept alive across calls, so IDO re-materializes &D_0 via fresh
 *       lui+lw for each subsequent access. Total: 33 insns (worse than
 *       original 31; target is 22).
 *   v6 (2026-04-20 extended): pass `p` to call 3 instead of `*&D_0` —
 *       **first half MATCHES target byte-perfect** (lui a0; addiu a0, a0
 *       DIRECT, no a3). But IDO then CSE's the `p = *&D_0` read with the
 *       earlier, so it loads p into $a0 directly at 0x28 (lui a0; lw
 *       a0, 0(a0)), SKIPPING the "base cached in $v0" pattern target
 *       emits. Total 19 insns (3 fewer than target 22).
 *   v8 (named `int *base = &D_0;` + base[16]=6 + pass base[0] to call 3):
 *       first half matches, but v8 uses v0 as BOTH base AND loaded-ptr
 *       (`v0 = *v0`), not target's t7 = *v0 pattern. Also 19 insns.
 *   v9-v11 (volatile, cast tricks, register hints): no improvement
 *       beyond v6/v8; cap holds at 97.95%. The target's "base cached in
 *       $v0 + separate t7 for deref" pattern isn't reproducible because
 *       IDO CSE's the two *&D_0 reads into one load-to-the-arg-reg.
 *
 * Fundamental issue: target keeps `v0 = &D_0` alive as a base pointer across
 * all of the second half (4 refs with only 22 insns). IDO-O2 declines to
 * hold `&D_0` in a register past call 2 because the spill-vs-rematerialize
 * cost is close. `register` hint + 5+ refs still doesn't persuade it.
 *
 * Cap at 97.95%. Real fix would be permuter-only or a compile-time hint
 * IDO doesn't expose. Committing this comment IS the forward progress. */
void h2hproc_uso_func_000002A4(void) {
    int *p;
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x4));
    *(int*)((char*)&D_00000000 + 0x40) = 5;
    gl_func_00000000(&D_00000000);
    p = *(int**)&D_00000000;
    *(int*)((char*)p + 0x30) = 0;
    gl_func_00000000(*(int*)&D_00000000, -1, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000002A4);
#endif

#ifdef NON_MATCHING
/* 97.95%: sibling of func_000002A4 — same 3-call + 2-side-effect-store
 * structure but writes 2 (not 5) at D_0[0x40]. Same `lui a3; addiu a0, a3`
 * intermediate-register cap documented in func_000002A4's NM comment.
 * Cap at ~22-of-23 bytes match; the a3-intermediate is an IDO invariant. */
void h2hproc_uso_func_000002FC(void) {
    int *p;
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x4));
    *(int*)((char*)&D_00000000 + 0x40) = 2;
    gl_func_00000000(&D_00000000);
    p = *(int**)&D_00000000;
    *(int*)((char*)p + 0x30) = 0;
    gl_func_00000000(*(int*)&D_00000000, -1, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000002FC);
#endif

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000354);

#ifdef NON_MATCHING
/* 97.95%: sibling of 0x2A4 family (0x2A4=5, 0x2FC=2, 0x354=3); writes 4
 * at D_0[0x40]. Same 3-call + 2-store shape; same a3-intermediate cap. */
void h2hproc_uso_func_000003AC(void) {
    int *p;
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x4));
    *(int*)((char*)&D_00000000 + 0x40) = 4;
    gl_func_00000000(&D_00000000);
    p = *(int**)&D_00000000;
    *(int*)((char*)p + 0x30) = 0;
    gl_func_00000000(*(int*)&D_00000000, -1, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000003AC);
#endif

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000404);

void h2hproc_uso_func_0000045C(void) {
    gl_func_00000000(*(int*)&D_00000000);
    gl_func_00000000(*(int*)(*(char**)&D_00000000 + 0x6B0));
    gl_func_00000000(&D_00000000);
}

/* h2hproc_uso_func_0000049C: 2-insn fragment (0x8), NO jr ra (grep -c=0).
 *   lui   a0, 0
 *   lw    a0, 0(a0)        ; a0 = *D_00000000
 * Falls through directly into func_000004A4 (real prologue at 0x4A4).
 * Alternate entry point: callers `jal 0x49C` get a0 reset to
 * *D_00000000 before the 4A4 body runs (callers don't supply a0).
 * Not reachable from C (no standalone function signature for an
 * alt-entry that falls through). Per feedback_split_fragments_unreachable_tail
 * class — leave INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_0000049C);

void h2hproc_uso_func_000004A4(char *a0) {
    gl_func_00000000(a0, *(int*)(a0 + 0x6B4) ^ 1);
    gl_func_00000000(*(int*)&D_00000000);
    gl_func_00000000(&D_00000000);
}

void h2hproc_uso_func_000004E0(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void h2hproc_uso_func_0000051C(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void h2hproc_uso_func_00000558(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void h2hproc_uso_func_000005B0(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000620);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000008EC);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000944);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_0000099C);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000009F8);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000A88);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000BAC);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000C18);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000E04);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000EB0);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000F60);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000FD0);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00001204);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00001360);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000015F0);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000017A0);

void h2hproc_uso_func_000019DC(char *dst) {
    int tmp;
    h2hproc_uso_func_000004E0(&tmp);
    h2hproc_uso_func_000004E0((int*)(dst + 0x10));
}

void h2hproc_uso_func_00001A0C(char *dst) {
    int tmp;
    h2hproc_uso_func_000004E0(&tmp);
    h2hproc_uso_func_0000051C((float*)(dst + 0x10));
}

void h2hproc_uso_func_00001A3C(char *dst) {
    int tmp;
    h2hproc_uso_func_000004E0(&tmp);
    h2hproc_uso_func_00000558((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00001A6C);

#ifdef NON_MATCHING
/* 92.3 %: standard composite-reader template (int + Vec3 at +0x10) but the two
 * inner calls are USO-internal jal placeholders (target=0x4DC and 0x5AC, the
 * trailing-nop area before the actual h2h reader funcs). Body matches; the two
 * jal target bytes (0x0C000137 / 0x0C00016B vs our 0x0C000000+reloc) are
 * unreachable from C without inline asm. */
extern int h2hproc_uso_func_h2h_4DC();
extern int h2hproc_uso_func_h2h_5AC();

void h2hproc_uso_func_00001AFC(char *a0) {
    int tmp;
    h2hproc_uso_func_h2h_4DC(&tmp);
    h2hproc_uso_func_h2h_5AC(a0 + 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00001AFC);
#pragma GLOBAL_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso/h2hproc_uso_func_00001AFC_pad.s")
#endif

