#include "common.h"

extern s32 func_800066F0(void*, s32, s32);

/* __rmonSendData */
void func_80006F60(char* buf, s32 size, s32 domain) {
    s32 totalSent;
    char* p = buf;

    *(u8*)(buf + 8) = 2;
    *(u8*)(buf + 5) = domain;
    totalSent = 0;
    if (size != 0) {
        do {
            register s32 sent = func_800066F0(p + totalSent, size - totalSent, 8);
            totalSent += sent;
        } while ((u32)totalSent < (u32)size);
    }
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006FF8);
