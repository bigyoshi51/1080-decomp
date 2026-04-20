#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000000);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_0000004C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000000B0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000005A4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_0000065C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000006B0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000006FC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_0000074C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000790);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000007D4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000818);

void timproc_uso_b3_func_00000854(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b3_func_00000890(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b3_func_000008CC(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void timproc_uso_b3_func_00000924(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000994);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000D60);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000DE4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000E60);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000FF4);

void timproc_uso_b3_func_00000000();

void timproc_uso_b3_func_00001090(int a0, char *a1) {
    timproc_uso_b3_func_00000000(a0, a1 + 0x00220000);
}

extern int gl_ref_00000040;
extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b3_func_000010B4(int a0) {
    gl_ref_00000040 = 9;
    gl_func_00000000(a0, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000010E4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001184);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001248);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000013B8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001660);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000017C8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_0000183C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001870);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001928);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000019CC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001C28);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001C68);

void timproc_uso_b3_func_0000205C(char *dst) {
    int tmp;
    timproc_uso_b3_func_00000854(&tmp);
    timproc_uso_b3_func_00000854((int*)(dst + 0x10));
}

void timproc_uso_b3_func_0000208C(char *dst) {
    int tmp;
    timproc_uso_b3_func_00000854(&tmp);
    timproc_uso_b3_func_00000890((float*)(dst + 0x10));
}

void timproc_uso_b3_func_000020BC(char *dst) {
    int tmp;
    timproc_uso_b3_func_00000854(&tmp);
    timproc_uso_b3_func_000008CC((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000020EC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_0000217C);

void timproc_uso_b3_func_000021B0(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 4;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000021F4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002240);

void timproc_uso_b3_func_000022BC(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 1;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b3_func_00002300(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 2;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b3_func_00002344(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 3;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002388);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000023E4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002700);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_0000294C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002A44);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002C98);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002DF0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002EF0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002F48);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00003050);

