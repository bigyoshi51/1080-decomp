#include "common.h"

extern s32 D_80000308;
extern s32 D_A4600000;
extern s32 D_A4600004;
extern s32 D_A4600008;
extern s32 D_A460000C;
extern s32 D_A4600010;
extern s32 func_80004B30(s32);
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

/* __osPiRawStartDma */
s32 func_80004650(s32 direction, u32 devAddr, s32 dramAddr, u32 size) {
    register u32 status;

    status = D_A4600010;
    while (status & 3) {
        status = D_A4600010;
    }

    D_A4600000 = func_80004B30(dramAddr);
    D_A4600004 = (D_80000308 | devAddr) & 0x1FFFFFFF;

    switch (direction) {
        case 0:
            D_A460000C = size - 1;
            break;
        case 1:
            D_A4600008 = size - 1;
            break;
        default:
            return -1;
    }

    return 0;
}
