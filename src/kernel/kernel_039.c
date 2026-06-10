#include "common.h"

extern s32 func_800077DC(s32);
extern s32 func_800096B0(s32);
extern s32 D_8000A41C;

/* __rmonGetRegisterContents */
s32 func_80009760(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == 0) {
        if (arg2 > 0 && arg2 < 0x1A) {
            arg2 -= 1;
        } else if (arg2 >= 0x1C && arg2 < 0x20) {
            arg2 -= 3;
        } else {
            return 0;
        }
        {
            s32* ptr;
            s32 ctx = func_800077DC(arg1);
            if (ctx == 0) {
                return 0;
            }
            ptr = (s32*)(ctx + 0x20);
            ptr = (s32*)((char*)ptr + arg2 * 4);
            return *ptr;
        }
    }
    return func_800096B0(arg2);
}
