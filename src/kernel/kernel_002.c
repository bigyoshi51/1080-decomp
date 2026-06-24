#include "common.h"


/* func_80004B10: RDB host-read with lazy message-queue init.
 * Lazy-inits a message queue (D_8000A440 flag-guarded) on first call,
 * publishes (buf, ct) to __osRdb_Read_Data_Buf/Ct, then loops the recv
 * helper until a non-zero count accumulates, and releases the queue. */
extern int func_800053D0(void*, void*, int);
extern int func_800051E0(int, void*, int);
extern int func_800066F0(void*, int, int);
extern int func_80004FE0(void*, int, int);
extern int D_8000A440;
extern int readhost_bss_0000;
extern int readhost_bss_0018;
extern int __osRdb_Read_Data_Buf;
extern int __osRdb_Read_Data_Ct;

void func_80004B10(void* buf, int ct) {
    int msg;
    int count = 0;
    if (D_8000A440 == 0) {
        func_800053D0(&readhost_bss_0000, &readhost_bss_0018, 1);
        func_800051E0(0xF, &readhost_bss_0000, 0);
        D_8000A440 = 1;
    }
    __osRdb_Read_Data_Buf = (int)buf;
    __osRdb_Read_Data_Ct = ct;
    while (count == 0) {
        count += func_800066F0(&msg, 1, 5);
    }
    func_80004FE0(&readhost_bss_0000, 0, 1);
}


/* func_80004BE0 = libultra osRecvMesg (kernel_002, -O1, byte-exact).
 * Reference: libreultra src/os/recvmesg.c. mq = OSMesgQueue (0x4
 * fullqueue blocked-sender list, 0x8 validCount, 0xC first,
 * 0x10 msgCount, 0x14 msg[]). func_800066B0/_800066D0 =
 * __osDisableInt/__osRestoreInt; func_80003D0C = __osEnqueueAndYield;
 * func_80003E54 = __osPopThread; func_8000A110 = osStartThread;
 * D_8000A420 = __osRunningThread (->0x10 = state, 8 = OS_STATE_WAITING).
 * The `div/mfhi; bnez+break 7` plus `bne at,0x8000/break 6` is
 * the IDO signed `%` div0/INT_MIN-overflow guard pair on the ring
 * index - documented C-unsuppressible (docs/IDO_CODEGEN.md
 * #feedback-ido-signed-mod-break-pair). MATCHED via libultra source
 * + 1080 struct offsets at -O1; verified byte-identical vs ROM. */
extern s32 func_800066B0(void);
extern void func_800066D0(s32 s);
extern void func_80003D0C(void *q);
extern void *func_80003E54(void *q);
extern void func_8000A110(void *t);
extern void *D_8000A420;

typedef struct RecvThread2 { struct RecvThread2 *next; } RecvThread2;
typedef struct {
    void* mtqueue;
    RecvThread2* fullqueue;
    s32 validCount;
    s32 first;
    s32 msgCount;
    s32** msg;
} RecvMesgQueue;

typedef struct RecvThread {
    s32 field0;
    s32 pri;
    s32 queue;
    s32 pad0C;
    u16 state;
} RecvThread;

/* osRecvMesg (libultra). Reference: libreultra src/os/recvmesg.c. */
s32 func_80004BE0(RecvMesgQueue *mq, s32 *msg, s32 flag) {
    register s32 saveMask = func_800066B0();

    while (mq->validCount == 0) {
        if (flag == 0) {
            func_800066D0(saveMask);
            return -1;
        }
        ((RecvThread*)D_8000A420)->state = 8;
        func_80003D0C(&mq->mtqueue);
    }

    if (msg != 0) {
        *msg = (s32)mq->msg[mq->first];
    }
    mq->first = (mq->first + 1) % mq->msgCount;
    mq->validCount--;
    if (mq->fullqueue->next != 0) {
        func_8000A110(func_80003E54(&mq->fullqueue));
    }
    func_800066D0(saveMask);
    return 0;
}
/* 2 trailing alignment nops (16-byte boundary) — spliced via pad sidecar
 * to preserve the exact .o/ROM layout (next func at 0x5D20). */
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/func_80004BE0_pad.s")


/* __osProbeTLB (libultra). Hand-written CP0/TLB assembly: probes the TLB for
 * the page mapping a virtual address and returns its physical address (or -1).
 * Byte-for-byte identical to libreultra/oot/papermario __osProbeTLB
 * (references/papermario/src/os/__osProbeTLB.s). Uses mfc0/mtc0 $10 (EntryHi),
 * tlbp, tlbr, mfc0 $0/$2/$3/$5 (Index/EntryLo0/EntryLo1/PageMask) — none of
 * which IDO C can emit, so this is a permanent hand-written INCLUDE_ASM cap
 * (same class as __osSetFpcCsr). Counterpart C wrapper would be
 * osVirtualToPhysical (libreultra src/os/virtualtophysical.c).
 *
 * The 1080 __osException dispatcher (func_800031F0) jal's the address-compute
 * tail at 0x80004DB8 directly as a code-share, which is why splat emits a
 * second label (func_80004DB8) mid-function; that tail must keep its own
 * symbol so the exception handler's jal resolves. Both fragments together
 * span 0x80004D20..0x80004DD4 (+2 alignment nops) and reconstruct the single
 * __osProbeTLB byte-exactly.
 * 2026-06-24 REFERENCE-CONFIRMED (decomp-search): __osProbeTLB is HANDWRITTEN .s in BOTH
 * libreultra (src/os/probetlb.s) and oot (src/libultra/os/probetlb.s) — uses tlbp/mtc0/
 * mfc0 (privileged, no C form). So INCLUDE_ASM is CANONICAL/PERMANENT here; 0.0% fuzzy is
 * correct (not a pending decode). */
INCLUDE_ASM("asm/nonmatchings/kernel", __osProbeTLB);

/* __osProbeTLB address-compute tail (shared jal target from __osException). */
/* 2026-06-24 reference-confirmed PRIVILEGED-ASM handwritten (CP0/TLB/FPU: mtc0/mfc0/tlbwi/ctc1/cfc1 — no C form, like libreultra src/os/*.s). INCLUDE_ASM is canonical/permanent; 0.0% fuzzy is CORRECT, not a pending decode. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80004DB8);
