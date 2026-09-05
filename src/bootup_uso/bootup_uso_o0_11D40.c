#include "common.h"

/* -O0 sub-file split out of bootup_uso_tail3a.c so this single function
 * builds at -O0 (matching its target shape) while neighbours stay -O2 -g3.
 * Same recipe as the existing bootup_uso_o0_F1F0.c / o0_F390.c cluster.
 *
 * Body verified byte-for-byte at -O0 (see kept-in-comment trace at
 * tail3a.c's 2026-05-06 RE-DIAGNOSED #2 entry, archived below).
 *
 * 2026-09-05: the 2-word "func_00011D70" (jr ra; nop) that followed this
 * fn was never a function -- it is ugen's dead `$exit: j $31` block for
 * THIS fn (last statement is a return, so both return arms emit their own
 * `jr ra` and the exit label block is unreachable). A standalone -O0 empty
 * fn is `b .+1; nop; jr ra; nop` (see func_00010310), never a bare 2-word
 * pair. Our -O0 emits TWO dead pairs, the shipped build ONE, so TRUNCATE_TEXT
 * grew 0x30 -> 0x38 and the -O2 -g3 "empty fn" unit bootup_uso_tail3a_bot.c
 * was retired. Same shape as mgrproc_uso 140+168 (docs/IDO_CODEGEN.md
 * #o0-two-block-predicate-not-adjacent-leaf-cap). */
int func_00011D40(int *a0, int a1) {
    if (*(int*)((char*)a0 + 0x120) < a1) return 0;
    return *(int*)((char*)a0 + a1 * 4 + 0xDC);
}
