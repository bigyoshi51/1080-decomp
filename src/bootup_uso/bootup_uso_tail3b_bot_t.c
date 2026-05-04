#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001266C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000126EC);

#ifdef NON_MATCHING
/* 19-insn 8-byte copy loop. Logic: copy 8 bytes from
 * (*(char**)(a0+0x154))+6 to a1[0..7].
 *
 * BLOCKED: -O0 shape (8-byte stack frame, sw/lw of i each iter, dead
 * 'b +1; nop' BB-end marker) but lives in bootup_uso_tail3b_bot_t.c
 * which builds at -O2. -O2 unrolls the loop and inlines the array base
 * load — totally different shape (still 19 insns by coincidence, but
 * 0/19 match).
 *
 * Promotion path: file split per feedback_o0_cluster_split_with_layout_shim.md.
 * Defer — infra change beyond single /decompile run scope. */
void func_000127CC(char *a0, char *a1) {
    int i;
    for (i = 0; i < 8; i++) {
        a1[i] = (*(char**)(a0 + 0x154))[i + 6];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000127CC);
#endif




