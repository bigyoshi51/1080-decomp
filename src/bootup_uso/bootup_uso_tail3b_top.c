#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00012188 (0x12188, struct initializer) and func_00012244 (0x12244,
 * -O0 set-bit-and-call helper) matched at -O0 and moved to
 * bootup_uso_o0_120A8.c (the adjacent -O0 run-8 file). See that file. */

/* func_000122C4 - verified structural decode (0x12C, 75 insns,
 * scripted-sequence step gate).
 * Struct-typing reference: a0->0x154 (340) = ptr to a sequence-state
 * struct; state->0x2 (2) u16 = the current step counter (advanced
 * 0->...). a0->0x4C (76) s32 = a progress/score value gate-checked
 * (a0->0x4C + 1) against an entry of the D_0000C69C 3-int table
 * (copied to a stack tbl, indexed by the counter when it reaches
 * the c==4 stage). a1 = an event/phase id; the early stages advance
 * when a1+1 matches the counter, the c==4 stage additionally
 * requires a1==2 and the 0x4C-vs-table match. func_00000000(a0) =
 * the "advance to next scripted step" callback. Caps <80: u16
 * counter compares + re-read pattern + 3-word table copy + slti
 * range tests + reloc call. INCLUDE_ASM remains build path. */
extern int D_0000C69C[3];
#ifdef NON_MATCHING
void func_000122C4(char *a0, int a1) {
    int tbl[3];
    char *st;
    int c;
    tbl[0] = D_0000C69C[0];
    tbl[1] = D_0000C69C[1];
    tbl[2] = D_0000C69C[2];
    st = *(char**)(a0 + 0x154);
    if (*(unsigned short*)(st + 0x2) < 4) {
        if (a1 + 1 == *(unsigned short*)(st + 0x2)) {
            *(unsigned short*)(st + 0x2) += 1;
            func_00000000(a0);
        }
        return;
    }
    if (a1 != 2) return;
    c = *(unsigned short*)((*(char**)(a0 + 0x154)) + 0x2);
    if (c < 4 || c >= 5) return;
    if (*(int*)(a0 + 0x4C) + 1 == *(int*)((char*)tbl + (c * 4) - 0x10)) {
        *(unsigned short*)((*(char**)(a0 + 0x154)) + 0x2) += 1;
        func_00000000(a0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000122C4);
#endif

