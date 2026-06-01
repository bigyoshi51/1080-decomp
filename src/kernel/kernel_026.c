#include "common.h"








INCLUDE_ASM("asm/nonmatchings/kernel", D_80009E60);
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/D_80009E60_pad.s")

/* SOURCE=3 skip: this symbol is real `.rodata`, not code. The asm file
 * declares `.section .rodata` and contains four `.word D_8000A5*` entries.
 * See docs/PATTERNS.md#feedback-word-only-skip-rule-doesnt-block-episode-logging:
 * this is the data-misidentified-as-code case, not a `.word`-encoded USO
 * function. Do not try to decompile it as C. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009EA0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009EB0);
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/func_80009EB0_pad.s")
