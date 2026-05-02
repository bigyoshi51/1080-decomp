#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

/* Continues arcproc_uso .text at 0x12C (after arcproc_uso_o0_50.c which
 * holds 0x50..0x12C: Quad4 reader + 0xB4 -O0 ref-count/check-full).
 * Original single-file body split into arcproc_uso.c (0x0..0x50 func_00000000),
 * arcproc_uso_o0_50.c (-O0), and this tail. */

void arcproc_uso_func_00001B88(int *a0) {
    int *t;
    arcproc_uso_func_00000000(a0);
    t = *(int**)((char*)a0 + 0xD4);
    arcproc_uso_func_00000000(t, 0x8C, *(int*)((char*)t + 0x6B0));
}

/* arcproc_uso_func_0000012C and func_0000019C moved to arcproc_uso_o0_12C.c (-O0 file). */

#ifdef NON_MATCHING
/* arcproc_uso_func_00000240: 0x388 (226 insns), 0x48 stack frame.
 * Sibling of arcproc_uso_func_0000019C (-O2 here vs -O0 there). 11-way state
 * machine dispatcher: switch (a1) where a1 ranges 0..10. Bound check first
 * (`sltiu at, a1, 0xB; beq at, zero, epilogue`), then jump-table lookup
 * via .rodata at D_xxx + a1*4.
 *
 * Cases 0..10 each do various combinations of:
 *   - gl_func_00000000(a0, 1, 3, 1)    -- 4-arg helper called with constants
 *   - gl_func_00000000(a0, 1, 3, ...)  -- variants
 *   - sw constants 0x3, 0xA, 0x1 to *(0x44, 0x48, 0x40) under a single global
 *   - branches to epilogue (sets local +0x40 = 1 to indicate state advance)
 *
 * Likely a "menu state advance" handler — given a key (button press category?)
 * and target struct, dispatch to one of 11 state transitions, each calling
 * the renderer/animator helper with different constants.
 *
 * Per feedback_ido_switch_rodata_jumptable.md: IDO -O2 emits a .rodata
 * jumptable for switch w/ ≥4 dense cases. Without explicit .rodata
 * preservation in the linker script for arcproc_uso, the function may be
 * permanently INCLUDE_ASM (the jumptable address can't be reproduced).
 *
 * Multi-tick: full case decode + verification of jumptable matchability
 * deferred. Default build INCLUDE_ASM remains exact. */
void arcproc_uso_func_00000240(void) {
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000240);
#endif

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000005C8);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000688);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000748);

void arcproc_uso_func_000007B4(void) {
    gl_func_00000000(*(int*)&D_00000000);
    gl_func_00000000(*(int*)((char*)*(int**)&D_00000000 + 0x6AC));
    gl_func_00000000(*(int*)&D_00000000);
    gl_func_00000000(&D_00000000);
}

#ifdef NON_MATCHING
/* 69 % match: same orchestrator pattern as 7B4 (4 calls bracketed by D_0
 * accesses + a if/else dispatch on call-2's return). Logic decoded
 * correctly. Remaining diffs are IDO's CSE folding all `*&D_00000000`
 * accesses through one cached $v1 base, while target uses fresh
 * `lui a0,0; lw a0,0(a0)` per access. CSE-defeat would need either
 * multiple unique-named externs aliased to the same address (complex
 * undefined_syms_auto.txt setup) or `volatile` accessors. Leaving as
 * NM wrap for now — promotion is mechanical from here. */
void arcproc_uso_func_00000800(void) {
    int v;
    gl_func_00000000(*(int*)&D_00000000);
    v = gl_func_00000000(*(int*)((char*)*(int**)((char*)*(int**)&D_00000000 + 0x6AC) + 0x4C));
    if (v != 0) {
        *(int*)((char*)&D_00000000 + 0x40) = 7;
        *(int*)((char*)&D_00000000 + 0x44) = 4;
    } else {
        *(int*)((char*)&D_00000000 + 0x40) = 4;
    }
    gl_func_00000000(*(int*)&D_00000000, 4,
        *(int*)((char*)*(int**)((char*)*(int**)&D_00000000 + 0x6A8) + 0xC));
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000800);
#endif

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000880);

void arcproc_uso_func_000008FC(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void arcproc_uso_func_00000938(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void arcproc_uso_func_00000974(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void arcproc_uso_func_000009CC(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000A3C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000D70);

void arcproc_uso_func_00000E58(char *a0) {
    arcproc_uso_func_00000000(a0 + 0x6BC);
    arcproc_uso_func_00000000(a0 + 0x6D4);
    arcproc_uso_func_00000000(a0 + 0x6EC);
    arcproc_uso_func_00000000(a0 + 0x71C);
    arcproc_uso_func_00000000(a0 + 0x704);
    arcproc_uso_func_00000000(a0 + 0x734);
    arcproc_uso_func_00000000(a0 + 0x74C);
    arcproc_uso_func_00000000(a0 + 0x764);
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000EBC);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000F50);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000FA8);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001170);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000125C);

int arcproc_uso_func_00000000();

void arcproc_uso_func_00001488(void) {
    arcproc_uso_func_00000000();
}

void arcproc_uso_func_000014A8(void) {
    gl_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000014C8);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001604);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000016F4);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000199C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001B04);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001BBC);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001C74);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001D18);

void arcproc_uso_func_00001F0C(char *a0) {
    if (*(int*)((char*)&D_00000000 + 0x64) == 1) {
        *(int*)(a0 + 0xA0) = 0xC350;
    } else {
        *(int*)(a0 + 0xA0) = 0x7530;
    }
    *(int*)(a0 + 0xA8) = *(int*)(*(int*)(a0 + 0xB8) + 0x34);
    *(int*)(a0 + 0xA4) = 0;
    gl_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001F54);

void arcproc_uso_func_000022A4(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_000008FC((int*)(dst + 0x10));
}

void arcproc_uso_func_000022D4(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_00000938((float*)(dst + 0x10));
}

void arcproc_uso_func_00002304(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_00000974((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00002334);

void arcproc_uso_func_000023C4(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_000009CC((Vec3*)(dst + 0x10));
}

extern int gl_ref_00000040;
extern int gl_ref_00000070;
extern int gl_ref_00000074;

void arcproc_uso_func_000023F4(void) {
    gl_func_00000000(gl_ref_00000070);
    gl_ref_00000040 = 4;
    gl_func_00000000(gl_ref_00000074, -1, 0);
}

void arcproc_uso_func_00002438(void) {
    gl_func_00000000(gl_ref_00000070);
    gl_ref_00000040 = 1;
    gl_func_00000000(gl_ref_00000074, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000247C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000024C0);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000251C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000027BC);

void arcproc_uso_func_00002864(void) {
    arcproc_uso_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00002884);
#pragma GLOBAL_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso/arcproc_uso_func_00002884_pad.s")
