#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00012188 (0x12188, struct initializer) and func_00012244 (0x12244,
 * -O0 set-bit-and-call helper) matched at -O0 and moved to
 * bootup_uso_o0_120A8.c (the adjacent -O0 run-8 file). See that file. */

/* func_000122C4 (0x12C, 75 insns, -O0): scripted-sequence step gate, EXACT
 * 2026-09-05 (agent-c). a0->0x154 = ptr to a sequence-state struct whose
 * u16 at +2 is the current step; a0->0x4C = a progress/score value; a1 = an
 * event/phase id. Steps 0..3 advance when a1+1 == step; step 4 additionally
 * needs a1 == 2 and score+1 == D_0000C69C[step-4] (3-int table copied to a
 * stack tbl; the -4 is folded into the sp offset). func_00000000(a0) is the
 * "advance to next scripted step" callback (runtime-patched reloc).
 *
 * Levers that made it match (all documented in docs/IDO_CODEGEN.md):
 * (1) cfe DAG-shares a REPEATED cast-deref chain within ONE `&&` at -O0:
 *     `if (chain >= 4 && chain < 5)` emits ONE lhu + slti/slti (no local).
 * (2) `register char *st;` for the RMW seq ptr -> $s0 in both increment
 *     blocks (an `unsigned short *` register var flips block1's operand rank).
 * (3) block1 guard `a1 + 1 == ((Obj22C4*)a0)->seq->step` -- the two-level
 *     typed member chain keeps textual (a1+1 first) order.
 * (4) THE FORMER 8-WORD "CAP" (target evaluates score+1 BEFORE the dynamic
 *     stack-table chain, sharing the a0 home load in $t6): spell the compare
 *     with the table chain on the LEFT and the score side wrapped in a
 *     RIGHT-side comma, `tbl_view[step] == (0, score + 1)` -- the comma node
 *     is ranked non-leaf and evaluated first in a plain t-reg, exactly the
 *     #feedback-ido-o0-eq-eval-order-gap lever (10FEC). The 76th word is the
 *     assembler's 16-byte .text pad, stripped by TRUNCATE_TEXT := 0x12C. */
typedef struct { int a, b, c; } Tbl3;
extern Tbl3 D_0000C69C;
typedef struct Seq22C4 { unsigned short h0; unsigned short step; } Seq22C4;
typedef struct TblView22C4 { int v[3]; } TblView22C4;
typedef struct Obj22C4 { char pad0[0x4C]; int score; char pad1[0x104]; Seq22C4 *seq; } Obj22C4;
void func_000122C4(char *a0, int a1) {
    Tbl3 tbl;
    register char *st;
    tbl = D_0000C69C;
    if (*(unsigned short*)(*(char**)(a0 + 0x154) + 2) < 4) {
        if (a1 + 1 == ((Obj22C4*)a0)->seq->step) {
            st = *(char**)(a0 + 0x154);
            *(unsigned short*)(st + 2) += 1;
            func_00000000(a0);
        }
    } else {
        if (a1 == 2) {
            if (*(unsigned short*)(*(char**)(a0 + 0x154) + 2) >= 4 &&
                *(unsigned short*)(*(char**)(a0 + 0x154) + 2) < 5) {
                if (((TblView22C4*)((char*)&tbl - 0x10))->v[((Obj22C4*)a0)->seq->step] == (0, ((Obj22C4*)a0)->score + 1)) {
                    st = *(char**)(a0 + 0x154);
                    *(unsigned short*)(st + 2) += 1;
                    func_00000000(a0);
                }
            }
        }
    }
}

