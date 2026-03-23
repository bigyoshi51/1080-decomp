#include "common.h"

extern s32 func_80005120(void*);

/* osVirtualToPhysical */
u32 func_80004730(void* vaddr) {
    if ((u32)vaddr >= 0x80000000U && (u32)vaddr < 0xA0000000U) {
        return (u32)vaddr & 0x1FFFFFFF;
    }
    if ((u32)vaddr >= 0xA0000000U && (u32)vaddr < 0xC0000000U) {
        return (u32)vaddr & 0x1FFFFFFF;
    }
    return func_80005120(vaddr);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800047B0);
