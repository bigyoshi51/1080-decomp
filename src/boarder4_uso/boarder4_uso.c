#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

void boarder4_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void boarder4_uso_func_0000003C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

INCLUDE_ASM("asm/nonmatchings/boarder4_uso/boarder4_uso", boarder4_uso_func_00000094);

void boarder4_uso_func_000000D0(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void boarder4_uso_func_0000010C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

#ifdef NON_MATCHING
/* 92.3%: composite "int + Quad4 at dst+0x10" reader body matches; 1 trailing alignment nop IDO doesn't emit from C. */
void boarder4_uso_func_00000164(char *dst) {
    int tmp;
    boarder4_uso_func_000000D0(&tmp);
    boarder4_uso_func_0000010C((Quad4*)(dst + 0x10));
}
#else
INCLUDE_ASM("asm/nonmatchings/boarder4_uso/boarder4_uso", boarder4_uso_func_00000164);
#endif

