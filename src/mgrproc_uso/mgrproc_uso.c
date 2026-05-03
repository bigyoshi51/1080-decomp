#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

#ifdef NON_MATCHING
/* Int-reader (pointer-indirect via volatile buf) with -O0 artifacts: 0x4C
 * (19 insns) vs -O2 template's 15 insns. Three -O0 markers in target:
 *   (a) `sw ra` BEFORE `sw a0` in prologue (-O2 opposite)
 *   (b) unfilled jal delay slot (`jal 0; nop`) — -O2 fills with `addiu a2, 4`
 *   (c) extra `b +1; nop` pair before epilogue (dead branch to next insn,
 *       characteristic -O0 basic-block boundary per feedback_ido_o0_empty_stub.md)
 * BLOCKED 2026-04-21: mgrproc_uso is Yay0-compressed. A second `.o`
 * (e.g., mgrproc_uso_o0_0.c.o) wouldn't land in ROM because the Makefile
 * Yay0 rule consumes only mgrproc_uso.c.o. Per
 * feedback_yay0_uso_blocks_file_split_recipe.md, the file-split recipe
 * (which works for bootup_uso and arcproc_uso) does NOT apply here.
 * Unblock path: add an `ld -r` pre-merge step before yay0 compression —
 * infrastructure work, out of single-tick scope.
 * Body semantics per feedback_uso_accessor_template_reuse.md int reader. */
void mgrproc_uso_func_00000000(int *dst) {
    volatile int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000000);
#endif

#ifdef NON_MATCHING
/* Quad4-reader template at -O0 (25 insns, 0x64) — sibling of
 * mgrproc_uso_func_00000000 (int reader at -O0). Per
 * feedback_uso_accessor_template_reuse.md, this is the standard 16-byte
 * accessor compiled at -O0 vs -O2 (15 insns).
 *
 * -O0 markers in target:
 *   (a) `sw ra` BEFORE `sw a0` in prologue (-O2 opposite)
 *   (b) unfilled jal delay slot (`jal 0; nop`) — -O2 fills with `addiu a2,16`
 *   (c) pointer-indirect reload (`lw t6,0x28(sp); addiu t7,sp,0x18`) instead
 *       of -O2's direct `lw tN,0x18(sp)`
 *   (d) trailing `b +1; nop` (dead branch to next insn) before epilogue
 *
 * BLOCKED: mgrproc_uso is Yay0-compressed (per feedback_uso_yay0_compressed.md);
 * the file-split recipe for -O0 override (works for bootup_uso/arcproc_uso)
 * doesn't apply because the Yay0 rule consumes only one .o. Same blocker as
 * mgrproc_uso_func_00000000 (int-reader sibling). Unblock requires `ld -r`
 * pre-merge step before yay0 compression — infrastructure work, deferred. */
void mgrproc_uso_func_0000004C(Quad4 *dst) {
    volatile Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *(Quad4*)dst = *(Quad4*)&buf;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_0000004C);
#endif

#ifdef NON_MATCHING
/* Refcount-increment wrapper (18 insns, 0x48). -O0 style matching
 * mgrproc_uso_func_00000000 (int reader at -O0).
 *
 * Body: increment a0->field_04 (as int), then call gl_func_00000000(a0).
 *
 * -O0 tells in target:
 *   (a) shadow-space save of a0 at sp+0x28, then reload into $s0 at 0xC0
 *       (`lw s0, 0x28(sp)`) AND ANOTHER reload into $a0 at 0xD0
 *       (`lw a0, 0x28(sp)`) — -O0 never shares the reload
 *   (b) unfilled jal delay slot (`jal 0; nop`)
 *   (c) dead `b +1; nop` immediately before epilogue (basic-block boundary
 *       marker per feedback_ido_o0_empty_stub.md)
 *
 * To match exact: split mgrproc_uso_func_000000B0 into its own .c with a
 * `build/src/mgrproc_uso/<file>.c.o: OPT_FLAGS := -O0` override (same infra
 * as mgrproc_uso_func_00000000 plan and bootup_uso_o0_*.c files). Defer. */
void mgrproc_uso_func_000000B0(int *a0) {
    a0[1]++;
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000000B0);
#endif

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000000F8);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_0000019C);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000504);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000005D0);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000700);

#ifdef NON_MATCHING
/* 27-insn -O0 cleanup wrapper. Mirror of arcproc_uso_func_00000748:
 * gl_func(a0->8); a0->8 = 0; gl_func(a0->0, 3); a0->0 = 0; D[0x14C] = 0.
 * -O0 indicators in target: unfilled jal delays + `b +1; nop` BBL marker.
 *
 * BLOCKED by Yay0 pipeline: mgrproc_uso is Yay0-compressed, so the -O0
 * file-split recipe doesn't apply (Yay0 rule consumes one .o). Default
 * build INCLUDE_ASM matches; wrap is for grep discoverability per the
 * established -O0-cap pattern. */
void mgrproc_uso_func_000009A8(int *a0) {
    gl_func_00000000((int*)a0[2]);
    a0[2] = 0;
    gl_func_00000000((int*)a0[0], 3);
    a0[0] = 0;
    *(int*)((char*)&D_00000000 + 0x14C) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000009A8);
#endif

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000A14);
#pragma GLOBAL_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso/mgrproc_uso_func_00000A14_pad.s")

void mgrproc_uso_func_00000AE0(void) {
    gl_func_00000000(*(int*)(&D_00000000 + 0x30));
    gl_func_00000000(*(int*)((char*)*(int**)(&D_00000000 + 0x30) + 0x6AC));
    gl_func_00000000(&D_00000000);
}

extern char D_mgr_B20_1;
extern char D_mgr_B20_2;
void mgrproc_uso_func_00000B20(void) {
    gl_func_00000000(*(int*)(&D_00000000 + 0x30));
    gl_func_00000000(*(int*)(&D_mgr_B20_1 + 0x30));
    gl_func_00000000(&D_mgr_B20_2);
}

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000B5C);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000C14);

void mgrproc_uso_func_00000CC4(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void mgrproc_uso_func_00000D00(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void mgrproc_uso_func_00000D3C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void mgrproc_uso_func_00000D94(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000E04);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000011A4);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000012AC);

void mgrproc_uso_func_00000000(void);

void mgrproc_uso_func_00001304(void) {
    mgrproc_uso_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001324);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000013C8);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000014F4);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001594);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001614);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_0000179C);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001824);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001AD0);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001B58);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001BE4);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001C90);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001F30);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002294);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002324);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000023FC);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002850);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002940);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002AFC);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002B7C);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002E3C);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002F10);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00003074);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00003240);

void mgrproc_uso_func_000032C8(char *dst) {
    int tmp;
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000CC4((int*)(dst + 0x10));
}

void mgrproc_uso_func_000032F8(char *dst) {
    int tmp;
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000D00((float*)(dst + 0x10));
}

void mgrproc_uso_func_00003328(char *dst) {
    int tmp;
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000D3C((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00003358);

void mgrproc_uso_func_000033E8(char *dst) {
    int tmp;
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000D94((Vec3*)(dst + 0x10));
}
#pragma GLOBAL_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso/mgrproc_uso_func_000033E8_pad.s")

