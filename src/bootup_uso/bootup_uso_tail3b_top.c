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
 * range tests + reloc call. INCLUDE_ASM remains build path.
 *
 * -O0 PROGRESS (2026-05-30): file flipped to -O0 (it isolates this fn);
 * NM body rewritten for the -O0 shape -> 69.4% (was 34.4% at -O2-g3).
 * Three structural keys found: (1) the tbl copy is a 12-byte STRUCT copy
 * (`Tbl3 tbl = D_0000C69C`) so &tbl/&D materialize once and reuse, not
 * per-element; (2) NO cached `st`/`c` locals — every st=a0->0x154 and
 * st->2 read is inline-fresh (target reloads a0 from 0x30(sp) + re-derefs
 * each use); (3) the gate exits are `goto ret` to a shared label, NOT
 * `return` (return generates a beq+b split; goto gives the target's direct
 * bne/bnez/beqz-to-epilogue). Table index = `*(int*)((char*)&tbl + c*4 -
 * 0x10)` with c the fresh re-read. REMAINING gap (~76 vs 75 insns +
 * register cascade): the chained-branch epilogue (target `b 0x110`->`b
 * 0x118`->ret, a -O0 nested-block-exit artifact) and -O0 temp renumbering.
 * Next: match the chained-exit + temp numbering. Same vein as 188/244. */
typedef struct { int a, b, c; } Tbl3;
extern Tbl3 D_0000C69C;
#ifdef NON_MATCHING
void func_000122C4(char *a0, int a1) {
    Tbl3 tbl;
    tbl = D_0000C69C;
    if (*(unsigned short*)(*(char**)(a0 + 0x154) + 2) < 4) {
        if (a1 + 1 == *(unsigned short*)(*(char**)(a0 + 0x154) + 2)) {
            *(unsigned short*)(*(char**)(a0 + 0x154) + 2) += 1;
            func_00000000(a0);
        }
        goto ret;
    }
    if (a1 != 2) goto ret;
    if (*(unsigned short*)(*(char**)(a0 + 0x154) + 2) < 4) goto ret;
    if (*(unsigned short*)(*(char**)(a0 + 0x154) + 2) >= 5) goto ret;
    if (*(int*)(a0 + 0x4C) + 1 ==
        *(int*)((char*)&tbl + (*(unsigned short*)(*(char**)(a0 + 0x154) + 2)) * 4 - 0x10)) {
        *(unsigned short*)(*(char**)(a0 + 0x154) + 2) += 1;
        func_00000000(a0);
    }
ret: ;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000122C4);
#endif

