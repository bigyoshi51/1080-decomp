#include "common.h"

/* -O2 sub-file covering bootup_uso offset 0xF6C4..0xF76B. Layout shim
 * after the bootup_uso_o0_F390.c -O0 cluster. F6C4 is more complex than
 * the F564-style set/clear template (indirect calls through method
 * tables, cross-function data ref) and stays as INCLUDE_ASM for now. */

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F6C4);
