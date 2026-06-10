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

/* split from kernel_042.c - 2026-06-10 kernel ROM-order relayout */


/* __osPiRawStartDma
 * 2026-06-10 kernel-relayout: previous load-then-loop WAIT form was a FALSE
 * match (2/57 words vs ROM; no arg homes; verified pre-relayout against a
 * shifted baseline). ROM truth is the libreultra WAIT_ON_IOBUSY
 * assign-in-condition form (homes all four args, status in $s0) -
 * byte-exact at -O1. */
s32 func_80004650(s32 direction, u32 devAddr, s32 dramAddr, u32 size) {
    register u32 status;

    while ((status = *(volatile u32*)0xA4600010) & 3) ;

    *(volatile u32*)0xA4600000 = func_80004B30(dramAddr);
    *(volatile u32*)0xA4600004 = (D_80000308 | devAddr) & 0x1FFFFFFF;

    switch (direction) {
        case 0:
            *(volatile u32*)0xA460000C = size - 1;
            break;
        case 1:
            *(volatile u32*)0xA4600008 = size - 1;
            break;
        default:
            return -1;
    }

    return 0;
}
