#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

#ifdef NON_MATCHING
/* func_0001266C: 32-insn set-low-2-bits + dispatch helper. Likely -O0
 * (every var via stack reload, 32-insn frame 0x28). Per
 * project_1080_bootup_uso_o0_runs.md, this region has scattered -O0 runs.
 *
 *   p = (unsigned short*)((char*)arg0->field_154 + 4);
 *   *p &= ~3;            // clear low 2 bits
 *   *p |= arg1;          // OR-in new low bits from arg1
 *   func_0(*p & 3);      // dispatch with the resulting low 2 bits
 *
 * Match needs file split into a -O0 .c per
 * docs/IDO_CODEGEN.md#feedback-o0-cluster-split-with-layout-shim.
 * Multi-tick. */
extern int func_00000000();
void func_0001266C(int *arg0, int arg1) {
    unsigned short *p = (unsigned short*)((char*)arg0[0x154/4] + 4);
    *p = *p & ~3;
    *p = *p | arg1;
    func_00000000(*p & 3);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001266C);
#endif

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




