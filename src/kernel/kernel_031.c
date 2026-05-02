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
 * for the result. Mine emits (~36 bytes / 9 insns at -O2 with standard C):
 *   - $t6/$t7/$t8 chain instead of single $t0 (IDO assigns fresh temps
 *     for each pseudo)
 *   - $v1 for result + final `or v0,v1,zero` move (vs target's direct $v0)
 *
 * Cap is IDO register-allocator: at -O1 (the file's OPT_FLAGS), spills the
 * v=0 to stack; at -O2, uses 3 distinct $t-temps + v0/v1 split. Target's
 * single-register chain isn't reachable from any std C shape (12 variants
 * tried 2026-05-02). Bytes match in semantics; not byte-match. */
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
