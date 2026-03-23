#include "common.h"

extern s32 func_80009000(void);

/* osSpRawReadIo */
s32 func_80008BB4(s32 devAddr, s32* data) {
    if (func_80009000() != 0) {
        return -1;
    }
    *data = *(volatile s32*)(0xA0000000 | devAddr);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008C00);
