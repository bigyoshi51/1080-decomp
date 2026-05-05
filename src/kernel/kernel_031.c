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

#ifdef NON_MATCHING
/* SP idle-check: returns 1 if SP_STATUS_REG (0xA4040010) HALT|BROKE bits
 * (mask 0x3) are clear, else 0. Reads RCP register space directly.
 *
 * 9-insn target uses single $t0 throughout for SP read+andi+test, and $v0
 * for the result.
 *
 * 2026-05-04 re-verification: built emits 12 insns at -O1 (file's
 * default OPT_FLAGS), with stack frame + spill of `v` and `stat`. Target
 * has no frame, no spill — that's -O2 codegen. To match: file-split this
 * function into a kernel_031b.c with `OPT_FLAGS := -O2`. INSN_PATCH won't
 * close the gap (size differs 12 vs 9). Multi-pass setup. */
extern u32 D_A4040010;  /* SP_STATUS_REG */
s32 func_80008030(void) {
    s32 v = 0;
    u32 stat = D_A4040010 & 3;
    if (stat == 0) v = v | 1;
    return v;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008030);
#endif
