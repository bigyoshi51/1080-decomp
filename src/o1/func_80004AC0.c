/* func_80004AC0 — compiled at -O1, matching C source */
#include "common.h"

/* osPiRawReadIo */
extern s32 func_800056C0(void);

s32 func_80004AC0(s32 devAddr, s32* data) {
    if (func_800056C0() != 0) {
        return -1;
    }
    *data = *(volatile s32*)(0xA0000000 | devAddr);
    return 0;
}
