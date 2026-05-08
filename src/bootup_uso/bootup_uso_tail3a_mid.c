#include "common.h"

/* Mid-tail assembly gap after func_00011A34 was split to an -O0 file.
 * Holds 0x11AB4..0x11C70 so the following o0_11C70 split keeps its offset. */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011AB4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011B5C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011BF0);
