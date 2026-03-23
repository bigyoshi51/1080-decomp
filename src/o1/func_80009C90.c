/* func_80009C90 — compiled at -O1, matching C source */
#include "common.h"

/* osPiRawWriteIo */
s32 func_80009C90(s32 devAddr, s32 val) {
    extern s32 func_80009000(void);
    if (func_80009000() != 0) {
        return -1;
    }
    *(volatile s32*)(0xA0000000 | devAddr) = val;
    return 0;
}
