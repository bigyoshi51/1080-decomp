#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00012188 (0x12188, struct initializer) and func_00012244 (0x12244,
 * -O0 set-bit-and-call helper) matched at -O0 and moved to
 * bootup_uso_o0_120A8.c (the adjacent -O0 run-8 file). See that file. */

/* func_000122C4 [-O0 eval-order+reg-alloc CAP, 88.75%]: comparison-operand
 * inversion does NOT flip the eval order — IDO loads the memory operand of
 * `a1+1 == *field` first regardless of which side a1+1 is on (target computes
 * a1+1 first). Also the increment block uses s0 for the field ptr where the
 * build uses a temp. Correct logic, divergent -O0 codegen; leave NM (2026-06-23).
 *
 * func_000122C4 - verified structural decode (0x12C, 75 insns,
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
 * -O0 PROGRESS (2026-05-30): file at -O0 (it isolates this fn); NM body
 * rewritten for the -O0 shape -> 88.7% (was 34.4% at -O2-g3, then 69.4%).
 * Structure now EXACT (75/75 insns). Keys: (1) tbl copy is a 12-byte STRUCT
 * copy (Tbl3 tbl = D_0000C69C) so &tbl/&D materialize once; (2) all
 * st=a0->0x154 / st->2 reads inline-fresh (target reloads a0 each use);
 * (3) the gates are NESTED POSITIVE conditions if(a1==2){if(c>=4){if(c<5)
 * -- a flat if(!cond)return/goto inverts to a beq+b split; nested positive
 * gives the target's direct bne/bnez/beqz to the shared exit (see
 * docs/IDO_CODEGEN.md#ido-o0-nested-positive-gates); (4) the range
 * c>=4 && c<5 reads c ONCE via register int c (plain re-reads, +3 insns).
 * REMAINING ~11% = -O0 register cascade: target holds the range c in a TEMP
 * and the RMW st ptr in $s0, but register-c forces c into $s0 and leaves st
 * in a temp; c-in-temp-read-once AND st-in-$s0 together isn't reachable from
 * C. -O0 register-renumber cap; structure is otherwise byte-exact. */
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
    } else {
        if (a1 == 2) {
            register int c = *(unsigned short*)(*(char**)(a0 + 0x154) + 2);
            if (c >= 4) {
                if (c < 5) {
                    if (*(int*)(a0 + 0x4C) + 1 ==
                        *(int*)((char*)&tbl + (*(unsigned short*)(*(char**)(a0 + 0x154) + 2)) * 4 - 0x10)) {
                        *(unsigned short*)(*(char**)(a0 + 0x154) + 2) += 1;
                        func_00000000(a0);
                    }
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000122C4);
#endif

