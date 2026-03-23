#include "common.h"

extern s32 func_80007A98(s32, s32, void*);
extern void func_800073F8(void*, s32, s32);

typedef struct { s32 pad0; u8 type; char pad5; s16 flags; s32 data[17]; } RmonBuf76;
typedef struct { s32 pad0; u8 type; char pad5[4]; u8 domain; char padA[2]; s32 id; } RmonMsg;

/* __rmonGetGRegisters */
s32 func_8000798C(RmonMsg* msg) {
    RmonMsg* p = msg;
    RmonBuf76 buf;
    if (func_80007A98(p->domain, p->id, &buf) != 0) {
        return -2;
    }
    buf.type = p->type;
    buf.flags = 0;
    func_800073F8(&buf, 0x4C, 1);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800079F4);
