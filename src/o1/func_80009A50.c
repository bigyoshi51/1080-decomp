/* func_80009A50 — compiled at -O1, matching C source */
#include "common.h"

/* osYieldThread */
extern void* D_8000A420;
extern s32 D_8000A418;
extern void func_80003D0C(s32*);

void func_80009A50(void) {
    register s32 sr = func_800066B0();
    *(s16*)((char*)D_8000A420 + 0x10) = 2;
    func_80003D0C(&D_8000A418);
    func_800066D0(sr);
}
