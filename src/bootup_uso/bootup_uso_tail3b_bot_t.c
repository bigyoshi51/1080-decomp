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

#ifdef NON_MATCHING
/* 19-insn 8-byte copy loop. Logic: copy 8 bytes from
 * (*(char**)(a0+0x154))+6 to a1[0..7].
 *
 * 2026-05-11: this file now builds at -O0 for func_0001266C, and this
 * body remeasures at 100% in the non_matching report. Left wrapped for a
 * separate one-function episode/landing pass.
 *
 * Promotion path: unwrap, log, and land in a dedicated pass. */
void func_000127CC(char *a0, char *a1) {
    int i;
    for (i = 0; i < 8; i++) {
        a1[i] = (*(char**)(a0 + 0x154))[i + 6];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000127CC);
#endif
