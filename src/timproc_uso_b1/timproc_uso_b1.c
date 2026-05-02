#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

#ifdef NON_MATCHING
/* Int-reader accessor variant (19 insns, 0x4C) — LIKELY -O0 compiled.
 * Logic: *dst = *(int*)D_00000000 (standard int reader template).
 *
 * -O0 indicators vs the -O2 int-reader at func_0000083C (15 insns, 0x3C):
 *   1. nop in jal delay slot (0x20) — -O2 fills with addiu.
 *   2. Pointer-indirect reload `addiu t6, sp, 0x18; lw t7, 0(t6)` (0x24/0x28)
 *      — -O2 uses direct `lw tN, 0x18(sp)`.
 *   3. Trailing `b +1; nop` (0x34/0x38) before epilogue — -O0 explicit
 *      jump-to-epilogue.
 *
 * Can't match at -O2 without per-function -O0 override. BLOCKED by Yay0
 * compression pipeline: timproc_uso_b1.c.o is objcopy'd to .text.bin then
 * yay0-compressed into timproc_uso_block1_yay0.bin — the linker consumes
 * the compressed blob, not individual .o files. So the file-split recipe
 * (see feedback_uso_accessor_o0_file_split_recipe.md) doesn't apply here:
 * splitting into timproc_uso_b1_o0_0.c.o produces TWO .o files, but the
 * Yay0 extractor only reads ONE. To unblock, would need a pre-yay0 .o
 * merge step (`ld -r`) or to run the accessor through a separate pipeline.
 * Same blocker applies to mgrproc_uso, game_uso, timproc_uso_b3/b5, and
 * map4_data_uso_b2 (all Yay0-compressed USOs). Deferred. */
void timproc_uso_b1_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000000);
#endif

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_0000004C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000000B0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000005A4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_0000065C);

extern int D_b1_06B0_a;
extern char *D_b1_06B0_b;
extern int D_b1_06B0_c;
void timproc_uso_b1_func_000006B0(void) {
    gl_func_00000000(D_b1_06B0_a);
    gl_func_00000000(*(int*)(D_b1_06B0_b + 0x6A8));
    gl_func_00000000(&D_b1_06B0_c);
}

extern int D_b1_06F0_a;
extern int D_b1_06F0_b;
extern int D_b1_06F0_c;
void timproc_uso_b1_func_000006F0(void) {
    gl_func_00000000(D_b1_06F0_a);
    gl_func_00000000(&D_b1_06F0_b);
    gl_func_00000000(D_b1_06F0_c);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_000006F0_pad.s")

/* Chain sibling of 0x778, 0x7BC, 0x800. Same recipe: PROLOGUE_STEALS for
 * stolen prefix; unique extern at gl_func arg; trailing pad sidecar emits
 * the stolen prologue for the NEXT function (0x778). */
extern int D_state_b1_734;
void timproc_uso_b1_func_00000734(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 1;
    gl_func_00000000(D_state_b1_734, -1, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_00000734_pad.s")

/* Chain sibling: t7=2. Same recipe as 0x734. */
extern int D_state_b1_778;
void timproc_uso_b1_func_00000778(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 2;
    gl_func_00000000(D_state_b1_778, -1, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_00000778_pad.s")

/* Chain sibling: t7=3. Same recipe as 0x734. */
extern int D_state_b1_7BC;
void timproc_uso_b1_func_000007BC(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 3;
    gl_func_00000000(D_state_b1_7BC, -1, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_000007BC_pad.s")

/* Byte-identical sibling of timproc_uso_b3_func_00000818. Same recipe:
 * PROLOGUE_STEALS removes redundant 8-byte lui+addiu prefix; unique extern
 * D_state_b1_800 (mapped 0x0) at the gl_func arg breaks &D-CSE so target's
 * fresh lui+lw at the call site reproduces. See
 * feedback_combine_prologue_steals_with_unique_extern.md. */
extern int D_state_b1_800;
void timproc_uso_b1_func_00000800(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 0xD;
    gl_func_00000000(D_state_b1_800, -1, 0);
}

void timproc_uso_b1_func_0000083C(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b1_func_00000878(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b1_func_000008B4(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void timproc_uso_b1_func_0000090C(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_0000097C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000D1C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000DA0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000DEC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000E40);

void timproc_uso_b1_func_00000EC0(int a0) {
    gl_func_00000000(&D_00000000 + 0x3D8);
    (void)a0;
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000EE8);

void timproc_uso_b1_func_00000000();

void timproc_uso_b1_func_000010DC(int a0, char *a1) {
    timproc_uso_b1_func_00000000(a0, a1 + 0x00220000);
}

extern int gl_ref_00000040;
extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b1_func_00001100(int a0) {
    gl_ref_00000040 = 9;
    gl_func_00000000(a0, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001130);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000011D8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001340);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000016F8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001860);

void timproc_uso_b1_func_000018D4(char *a0) {
    char *p;
    gl_func_00000000(a0);
    p = *(char**)(a0 + 0xD4);
    gl_func_00000000(p, 0x8C, *(int*)(p + 0x6AC));
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001908);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000019C0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001A64);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001BCC);

void timproc_uso_b1_func_00001E44(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_0000083C((int*)(dst + 0x10));
}

void timproc_uso_b1_func_00001E74(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_00000878((float*)(dst + 0x10));
}

void timproc_uso_b1_func_00001EA4(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_000008B4((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001ED4);

void timproc_uso_b1_func_00001F64(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_0000090C((Vec3*)(dst + 0x10));
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_00001F64_pad.s")

void timproc_uso_b1_func_00001FA0(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 4;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001FE4);

#ifdef NON_MATCHING
/* 97.58 % cap (sibling of timproc_uso_b3_func_00002240, byte-identical).
 * Dual-branch state setter, prologue-stolen successor. Same recipe and
 * register-allocator cap. See b3_2240 for full notes. */
extern int D_state_b1_2030;
extern int D_call_b1_2030_a;
extern int D_call_b1_2030_b;
extern int * volatile D_cur_b1_2030;
void timproc_uso_b1_func_00002030(void) {
    if (gl_func_00000000(((char*)D_state_b1_2030) + 4) != 0) {
        gl_func_00000000(D_call_b1_2030_a);
        D_cur_b1_2030[0x14] = 2;
        D_cur_b1_2030[0x16] = 1;
    } else {
        gl_func_00000000(D_call_b1_2030_b);
        D_cur_b1_2030[0x14] = 1;
        D_cur_b1_2030[0x16] = 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002030);
#endif

void timproc_uso_b1_func_000020AC(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 1;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

void timproc_uso_b1_func_000020F0(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 2;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b1_func_00002134(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 3;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002178);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000021D4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000024F4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002740);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002838);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002A8C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002BE4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002CE0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002D48);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002E50);
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_00002E50_pad.s")

