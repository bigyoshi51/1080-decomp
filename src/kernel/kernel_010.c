#include "common.h"




/* func_80005C50 GRAFT-BLOCKED 2026-06-10 (boundary puzzle): its
 * jumptable jtbl_8000A770 (ROM-true entries read from the byte-exact
 * ROM) targets [0x6354..0x647C] -- INSIDE func_800062F0's span, three
 * symbols away. func_800060F0 starts with bnez (no prologue = a
 * fragment of this fn), but 6110/62F0 have real prologues. The region
 * [0x5C50..0x65B0) needs a boundary-merge analysis (which "fns" are
 * case blocks vs real entries) before any C decode. The kernel
 * relayout verified SECTION bytes, not these internal symbol
 * boundaries (unmatched INCLUDEs kept splat's guesses). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80005C50);

