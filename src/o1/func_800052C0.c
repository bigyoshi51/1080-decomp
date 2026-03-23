/* func_800052C0 — compiled at -O1, matching C source */
#include "common.h"

/* __osSiDeviceBusy */
s32 func_800052C0(void) {
    register u32 status = *(volatile u32*)0xA4800018;
    if (status & 3) {
        return 1;
    }
    return 0;
}
