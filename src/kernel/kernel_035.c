#include "common.h"

extern s32 func_80006A98(s32);
extern void func_80006A50(s32, s32);
extern void func_80007A98(s32, s32, void*);
extern void func_80008D0C(void*);
extern void func_800073F8(void*, s32, s32);
extern u8 __rmonRcpAtBreak;

/* __rmonHitSpBreak */
void func_80008A38(void) {
    s32 buf[19];
    register s32 val = func_80006A98(0x04080000);
    func_80006A50(0x04080000, val - 4);
    func_80007A98(1, 0x3E8, buf);
    func_80008D0C(buf);
    func_800073F8(buf, 0x4C, 2);
    __rmonRcpAtBreak = 1;
}
