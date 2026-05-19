#include "common.h"

extern s32 rmonsio_bss_0000;
extern s32 rmonsio_bss_0018;
extern u8 rmonRdbReadBuf;
extern void* __osRdb_DbgRead_Buf;
extern void func_800053D0(s32*, s32*, s32);
extern void func_800051E0(s32, s32*, s32);
extern void func_80004FE0(s32*, s32*, s32);
extern void func_800069BC(u8*);
extern s32 func_800066F0(u8*, u8*, s32);

/* __osRdb_ReadThread — forever-loop reading the debug read buffer. */
void func_800051F0(void) {
    s32 total;
    s32 buf;

    func_800053D0(&rmonsio_bss_0000, &rmonsio_bss_0018, 1);
    func_800051E0(0x14, &rmonsio_bss_0000, 0);
    __osRdb_DbgRead_Buf = &rmonRdbReadBuf;
loop:
    func_80004FE0(&rmonsio_bss_0000, 0, 1);
    func_800069BC(&rmonRdbReadBuf);
    __osRdb_DbgRead_Buf = &rmonRdbReadBuf;
    total = 0;
    while (total <= 0) {
        register s32 n = func_800066F0((u8*)&buf, (u8*)1, 0xB);
        total += n;
    }
    goto loop;
}
