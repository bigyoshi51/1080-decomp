#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

void func_0001266C(char *a0, int a1) {
    register u16 *p;

    p = (u16 *)(*(char **)(a0 + 0x154) + 4);
    *p = *p & ~3;
    p = (u16 *)(*(char **)(a0 + 0x154) + 4);
    *p = *p | a1;
    func_00000000((*(u16 *)(*(char **)(a0 + 0x154) + 4)) & 3);
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000126EC);

/* 19-insn 8-byte copy loop. Logic: copy 8 bytes from
 * (*(char**)(a0+0x154))+6 to a1[0..7].
 * Promoted from NM wrap 2026-05-17 (file is -O0 per file split). */
void func_000127CC(char *a0, char *a1) {
    int i;
    for (i = 0; i < 8; i++) {
        a1[i] = (*(char**)(a0 + 0x154))[i + 6];
    }
}
