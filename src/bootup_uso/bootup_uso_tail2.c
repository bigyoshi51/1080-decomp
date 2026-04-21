#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010260);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000102A4);

void func_000102E8(void) {
}

void func_000102F0(char *a0, int a1) {
    *(float*)(a0 + 0x70) = (float)a1;
}

void func_00010308(void) {
}

