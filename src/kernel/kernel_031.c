#include "common.h"

extern void func_800073F8(void*, s32, s32);

typedef struct { s32 pad0; u8 type; char pad5; u16 flags; s32 pad8; s32 pad12; } RmonAck;
typedef struct { s32 pad0; u8 type; } RmonMsgSmall;

/* __rmonSendAck */
s32 func_80007FE8(RmonMsgSmall* msg) {
    RmonAck ack;
    ack.type = msg->type;
    ack.pad12 = 0;
    ack.flags = 0;
    func_800073F8(&ack, 0x10, 1);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008030);
