#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

void boarder2_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void boarder2_uso_func_0000003C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

#ifdef NON_MATCHING
/* 80%: body matches standard "int + Quad4 at dst+0x10" composite template.
 * Diff is 3 trailing alignment nops IDO doesn't emit from C. See feedback_function_trailing_nop_padding.md. */
void boarder2_uso_func_00000094(char *dst) {
    int tmp;
    boarder2_uso_func_00000000(&tmp);
    boarder2_uso_func_0000003C((Quad4*)(dst + 0x10));
}
#else
INCLUDE_ASM("asm/nonmatchings/boarder2_uso/boarder2_uso", boarder2_uso_func_00000094);
#endif

void boarder2_uso_func_000000D0(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void boarder2_uso_func_0000010C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void boarder2_uso_func_00000164(char *dst) {
    int tmp;
    boarder2_uso_func_000000D0(&tmp);
    boarder2_uso_func_0000010C((Quad4*)(dst + 0x10));
}

