#include "common.h"




/* func_80005C50 GRAFT-BLOCKED 2026-06-10 (boundary puzzle): its
 * jumptable jtbl_8000A770 (ROM-true entries read from the byte-exact
 * ROM) targets [0x6354..0x647C] -- INSIDE func_800062F0's span, three
 * symbols away. func_800060F0 starts with bnez (no prologue = a
 * fragment of this fn), but 6110/62F0 have real prologues. The region
 * [0x5C50..0x65B0) needs a boundary-merge analysis (which "fns" are
 * case blocks vs real entries) before any C decode. The kernel
 * relayout verified SECTION bytes, not these internal symbol
 * boundaries (unmatched INCLUDEs kept splat's guesses).
 * 2026-06-10 PROLOGUE-DERIVED TRUE MAP of [0x5C50..0x65B0) from the
 * byte-exact ROM (addiu sp,-N after jr-ra boundaries):
 *   A 0x5C50..0x5C90 (-32)   B 0x5C94..0x5CC4 (-24)
 *   C 0x5CC8..0x5DB4 (-32)   D 0x5DC0..0x5F08 (-56)
 *   E 0x5F10..0x6054 (-40)   F 0x6060..0x6508 (-72, two jr-ra)
 *   G 0x6510.. (-40)
 * OPEN PARADOX: the jtbl_8000A770 dispatch sits at 0x5F4C (inside E)
 * but the table entries target [0x6354..0x647C] (inside F) -- a
 * compiler can't emit that. Either the dispatch's %lo resolution is
 * misattributed (different table at the lw) or E/F share structure
 * unusually. Resolve FIRST in the merge session; then each true fn is
 * m2c-direct decodable with real syms. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80005C50);

