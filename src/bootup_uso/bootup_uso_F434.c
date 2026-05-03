#include "common.h"

/* -O2 sub-file covering bootup_uso offsets 0xF434..0xF76B. Split out of
 * bootup_uso.c so the preceding 0xF390..0xF430 range can build at -O0
 * (see bootup_uso_o0_F390.c). All functions in this range are still
 * INCLUDE_ASM; the file exists as a layout shim. */

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F434);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F4CC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F564);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F5BC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F614);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F66C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F6C4);
