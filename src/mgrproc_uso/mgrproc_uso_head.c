#include "common.h"

/* [0x170, 0x19C) of the mgrproc_uso Yay0 block: ONE -O0 predicate,
 * mgrproc_uso_func_00000170 (11 words). Built -O0 with TRUNCATE_TEXT 0x2C.
 *
 * HISTORY (2026-09-05, agent-g): this unit used to be [0x140,0x19C) at -O2 -g3
 * holding six "functions": 140 / 15C / 168 / 170 / 188 / 194. 140 and 170 were
 * NM-wrapped 99% "branch-into-adjacent-return-0-leaf CAPs" whose only residual
 * was the bne offset (+2 own jr vs +4 into the "next function"); 15C/188 were
 * "return-0 leaves", 168/194 "empty stubs". They were never six functions.
 * They are TWO frameless -O0 predicates, each = [guard ; li v0,1 ; jr ra ; nop]
 * + [move v0,zero ; jr ra ; nop] (the return-0 arm laid out after the then-arm,
 * no preset-default hoist because -O0 never runs uopt) + ONE dead `jr ra ; nop`
 * (ugen's unreachable fall-off return). generate-uso-asm cut at every `jr ra`,
 * so the return-0 arm and the dead pair became "functions". The whole -O0 run of
 * this block is therefore [0x0, 0xAE0) (func_00000000 .. func_00000A14); this
 * unit exists only because our IDO 7.1 -O0 emits TWO dead trailing pairs
 * (fall-off `j $31` AND the `$exit: j $31` label block) where the shipped build
 * has ONE, so each predicate must terminate its own .o and be clipped
 * (o0_11D78 precedent). _00000140 lives at the end of mgrproc_uso_o0_0.c for
 * the same reason.
 *
 * Callers: func_000000F8 (jal, same block), mgrproc_uso.c:522 (`!= 0` test).
 * Semantics: "list is empty" -> 1 when a0->0 == NULL. */
int mgrproc_uso_func_00000170(int *a0) {
    if (a0[0] == 0) {
        return 1;
    }
    return 0;
}
