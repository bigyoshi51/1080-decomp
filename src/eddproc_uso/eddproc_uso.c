#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_00000000);

void eddproc_uso_func_00000040(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void eddproc_uso_func_0000007C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_000000D4);

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_0000015C);

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_000001F0);

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_0000025C);

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_0000032C);

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_0000035C);

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_0000038C);

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_000003BC);

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_0000044C);

