#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000000);

#ifdef NON_MATCHING
/* Quad4 reader template — -O0 variant (per feedback_uso_accessor_o0_variant.md).
 * Three -O0 signals present:
 *   (1) unfilled jal delay slot (nop after jal 0 at 0x6C/0x70)
 *   (2) pointer-indirect buf reload: `addiu t7, sp, 0x18; lw t9, 0(t7)`
 *       (NOT direct `lw t9, 0x18(sp)`)
 *   (3) trailing `b +1; nop` before epilogue (at 0x9C/0xA0)
 * Not matchable at -O2. Promotion to exact requires per-file -O0 override:
 * split into src/arcproc_uso/arcproc_uso_o0_50.c with
 *   `build/.../arcproc_uso_o0_50.c.o: OPT_FLAGS := -O0`
 * and linker script entry. Same template as bootup_uso_o0_* accessors. */
void arcproc_uso_func_00000050(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000050);
#endif

void arcproc_uso_func_00001B88(int *a0) {
    int *t;
    arcproc_uso_func_00000000(a0);
    t = *(int**)((char*)a0 + 0xD4);
    arcproc_uso_func_00000000(t, 0x8C, *(int*)((char*)t + 0x6B0));
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000000B4);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000012C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000019C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000240);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000005C8);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000688);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000748);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000007B4);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000800);

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

/* arcproc_uso_func_000014C8: 0x13C (79 insns, 6 gl_func calls) — float-heavy
 * per-frame update. ENTRY (first 2 insns are PRE-PROLOGUE):
 *   lui $at, 0x3F80; mtc1 $at, $f0     ; f0 = 1.0f (loaded before sp-dec)
 *   addiu $sp, $sp, -0x58                ; prologue begins
 *   sw ra, 0x1C(sp); sw s0, 0x18(sp)
 *   swc1 f0, 0x48..0x54(sp)             ; zero 4 local floats... wait, f0=1.0 not 0
 *   lw t6, 0x500(a0)                    ; t6 = a0->field_500
 *   or s0, a0, zero                     ; s0 = a0 (saved)
 *   lui $at, %hi(D_XX); beql t6, zero, +0x3E (epilogue)
 *   ...(76 more insns: 6 gl_func calls, float comparisons c.lt.s/c.eq.s,
 *   conditional bc1t/bc1f dispatch, probably lerp/clamp patterns)
 *
 * Note: the f0=1.0 is HOISTED above the stack-decrement — unusual. The
 * zero-stores at 0x14DC-0x14E8 write f0 (containing 1.0) to sp+0x48..0x54 —
 * but semantically those are "zero" slots that get overwritten. Either f0
 * isn't 1.0 there (re-loaded), or the function uses 1.0 as a fence value.
 * Multi-run decomp territory. */
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000014C8);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001604);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000016F4);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000199C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001B04);

/* moved to before void-decl at line 80 to allow K&R implicit decl with args */

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001BBC);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001C74);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001D18);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001F0C);

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

