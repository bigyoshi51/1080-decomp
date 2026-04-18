#include "common.h"

extern u32 D_80000308;

#define PI_STATUS (*(volatile u32*)0xA4600010)

s32 func_800029B0(u32 arg0, u32* arg1) {
    char pad[4];
    register u32 s;
    s = PI_STATUS;
    if (s & 3) {
        do { s = PI_STATUS; } while (s & 3);
    }
    *arg1 = *(u32*)((D_80000308 | arg0) | 0xA0000000);
    return 0;
}

/* func_80002A10 split out to kernel_056.c (-O1 -mips3, 64-bit helper) */
