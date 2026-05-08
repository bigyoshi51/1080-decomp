#include "common.h"

extern int func_00000000();

/* Mid-tail assembly gap after func_00011AB4 was split to an -O0 file.
 * Holds 0x11B5C..0x11C70 so the following o0_11C70 split keeps its offset. */
#ifdef NON_MATCHING
/* func_00011B5C: 37-insn -O0-style flag-set + per-element-1-call loop.
 * Sibling of func_00011BF0 (just-landed) but saves/returns the old _188
 * flag and sets _188=1 + calls helper(arg, 1) per item. -O0 spill
 * pattern requires file split for byte-exact match. */
s32 func_00011B5C(s32 *a0) {
    s32 saved = *(s32*)((char*)a0 + 0x188);
    s32 i;
    *(s32*)((char*)a0 + 0x188) = 1;
    i = 0;
    if (*(s32*)((char*)a0 + 0x124) > 0) {
        do {
            func_00000000(*(s32*)((char*)a0 + 0x100 + i * 4), 1);
        } while (++i < *(s32*)((char*)a0 + 0x124));
    }
    return saved;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011B5C);
#endif

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
