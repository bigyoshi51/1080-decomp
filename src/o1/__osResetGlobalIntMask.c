/* __osResetGlobalIntMask — compiled at -O1, matching C source */
#include "common.h"

/* __osResetGlobalIntMask */
extern s32 func_8000A090(s32, s32);

void __osResetGlobalIntMask(s32 arg0, s32 arg1) {
    if (func_8000A090(arg0, arg1) != 0) {
        do {
        } while (func_8000A090(arg0, arg1) != 0);
    }
}
