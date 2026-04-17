#include "common.h"

extern u32 D_80000308;

#define PI_STATUS (*(volatile u32*)0xA4600010)

#ifdef NON_MATCHING
/* Decompilation is logically correct but IDO assigns different temp
 * registers (target uses $a2 for the PI_STATUS reads, IDO 7.1 picks
 * $t7/$t0 here). Same instruction count, same structure. */
s32 func_800029B0(u32 arg0, u32* arg1) {
    char pad[4];
    if (PI_STATUS & 3) {
        do {} while (PI_STATUS & 3);
    }
    *arg1 = *(u32*)((D_80000308 | arg0) | 0xA0000000);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800029B0);
#endif

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002A10);
