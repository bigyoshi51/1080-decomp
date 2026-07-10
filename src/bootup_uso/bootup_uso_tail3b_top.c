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
 *
 * 2026-07-10 REWORK (w50 island sweep) -> 67/75 words, ONE 8-word residual.
 * The old "register cascade cap" note above is RETRACTED — three new levers
 * cracked all of it except one operand-rank swap:
 * (1) cfe DAG-shares a REPEATED cast-deref chain within ONE `&&` condition
 *     at -O0: `if (chain >= 4 && chain < 5)` (chain spelled identically twice)
 *     emits ONE lhu into $t5 + slti/slti — no local, no home store, and the
 *     u16 cvt phantom reserves $t4 exactly like the target (backfilled by the
 *     next block's first load). register-int-c (old form) is WRONG (s0 + drift).
 * (2) `register char *st;` + `st = *(char**)(a0+0x154); *(u16*)(st+2) += 1;`
 *     puts the RMW seq ptr in $s0 in BOTH increment blocks (target shape).
 *     TYPE MATTERS: `register unsigned short *st` flips block1's guard
 *     operand rank (chain-first); char* does not.
 * (3) block1 guard `a1 + 1 == ((Obj22C4*)a0)->seq->step` — the 2-level typed
 *     member chain restores textual order at -O0 too (cast spelling made the
 *     chain jump ahead of a1+1; docs cfe-commutative-operand-rank entry).
 * RESIDUAL (the only diff, 8 words at 0xcc-0xe8): in the c==4 guard
 * `score + 1 == tbl_view[step]` the target creates the SCORE chain first;
 * every probed spelling creates the dynamic-subscript table chain first
 * (member-view struct, 2-hop view, IXA, cast, textual swap, long/unsigned
 * cvt phantoms, a1*0 mpy phantom, deeper &a0 root = +1 real insn). A
 * dynamic-index stack-table chain outranks all probed operand kinds at -O0.
 * Also +1 trailing alignment nop (built 76w vs 75w). NM stays. */
typedef struct { int a, b, c; } Tbl3;
extern Tbl3 D_0000C69C;
typedef struct Seq22C4 { unsigned short h0; unsigned short step; } Seq22C4;
typedef struct TblView22C4 { int v[3]; } TblView22C4;
typedef struct Obj22C4 { char pad0[0x4C]; int score; char pad1[0x104]; Seq22C4 *seq; } Obj22C4;
#ifdef NON_MATCHING
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
                if (((Obj22C4*)a0)->score + 1 == ((TblView22C4*)((char*)&tbl - 0x10))->v[((Obj22C4*)a0)->seq->step]) {
                    st = *(char**)(a0 + 0x154);
                    *(unsigned short*)(st + 2) += 1;
                    func_00000000(a0);
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000122C4);
#endif

