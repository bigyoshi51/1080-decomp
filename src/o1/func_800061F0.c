/* func_800061F0 — compiled at -O1, matching C source */
#include "common.h"

/* __osSetGlobalIntMask */
void func_800061F0(s32 mask) {
    register s32 sr = func_800066B0();
    D_8000A3E0 |= mask;
    func_800066D0(sr);
}
