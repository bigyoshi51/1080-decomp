#include "common.h"

extern s32 func_80006A98(s32);
extern s32 D_8001FF80;
extern s32 D_8001FF84;
extern s32 D_8001FF88;

/* __rmonSaveRegs */
void func_80008D4C(s32 extended) {
    D_8001FF80 = func_80006A98(0x04080000);
    D_8001FF84 = func_80006A98(0x04001000);
    *(s32*)&D_8001FF88 = func_80006A98(0x04000000);
    if (extended != 0) {
        *((s32*)&D_8001FF88 + 1) = func_80006A98(0x04000004);
        *((s32*)&D_8001FF88 + 2) = func_80006A98(0x04000008);
        *((s32*)&D_8001FF88 + 3) = func_80006A98(0x0400000C);
    }
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008DF0);
