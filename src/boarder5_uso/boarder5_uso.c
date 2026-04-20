#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/boarder5_uso/boarder5_uso", boarder5_uso_func_00000000);

void boarder5_uso_func_00000040(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void boarder5_uso_func_00000098(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    boarder5_uso_func_00000040((Quad4*)(dst + 0x10));
}
#pragma GLOBAL_ASM("asm/nonmatchings/boarder5_uso/boarder5_uso/boarder5_uso_func_00000098_pad.s")

void boarder5_uso_func_000000D4(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void boarder5_uso_func_00000110(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void boarder5_uso_func_00000168(char *dst) {
    int tmp;
    boarder5_uso_func_000000D4(&tmp);
    boarder5_uso_func_00000110((Quad4*)(dst + 0x10));
}
#pragma GLOBAL_ASM("asm/nonmatchings/boarder5_uso/boarder5_uso/boarder5_uso_func_00000168_pad.s")
