#include "common.h"

extern s32 func_800066B0(void);
extern void func_800066D0(s32);
extern s32 __osRdb_IP6_Data;
extern s32 __osRdb_IP6_Size;
extern s32 __osRdb_IP6_Ct;
extern s32 __osRdb_IP6_CurWrite;
extern s32 __osRdb_IP6_CurSend;

/* __osRdb_IP6_Init */
void func_800045C0(s32 addr, u32 size) {
    s32 saveMask;

    size >>= 2;
    if (addr & 3) {
        addr = (addr & 3) + 4;
        size--;
    }
    saveMask = func_800066B0();
    __osRdb_IP6_Data = addr;
    __osRdb_IP6_Size = size;
    __osRdb_IP6_Ct = 0;
    __osRdb_IP6_CurWrite = 0;
    __osRdb_IP6_CurSend = 0;
    func_800066D0(saveMask);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004650);
