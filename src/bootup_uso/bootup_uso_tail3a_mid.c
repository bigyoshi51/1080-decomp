#include "common.h"

extern int func_00000000();

/* Mid-tail assembly gap after func_00011AB4 was split to an -O0 file.
 * Holds 0x11B5C..0x11C70 so the following o0_11C70 split keeps its offset. */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011B5C);

void func_00011BF0(char *a0) {
    s32 i;

    i = 0;
    if (*(s32*)(a0 + 0x124) > 0) {
        do {
            func_00000000(*(s32*)(a0 + 0x100 + i * 4), 0);
        } while (++i < *(s32*)(a0 + 0x124));
    }
    *(s32*)(a0 + 0x188) = 0;
}
