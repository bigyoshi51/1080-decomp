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


/* func_80004BE0 - verified structural decode (kernel, 0x138, 80
 * insns) = libultra osRecvMesg. Reference: libreultra
 * src/os/recvmesg.c / sendmesg.c (OSMesgQueue, __os* thread ops).
 * Struct-typing reference: mq = OSMesgQueue - 0x4 fullqueue
 * (blocked-sender list), 0x8 validCount, 0xC first, 0x10 msgCount,
 * 0x14 msg[] (OSMesg array). func_800066B0/_800066D0 =
 * __osDisableInt/__osRestoreInt; func_80003D0C = __osEnqueueAndYield;
 * func_80003E54 = __osPopThread; func_8000A110 = __osEnqueueThread;
 * D_8000A420 = __osRunningThread (->0x10 = state, set 8 = blocked-on-
 * recv). The `div $0,t2,t4; mfhi; bnez t4,+2; break 7` plus
 * `addiu at,-1; bne t4,at; lui at,0x8000; bne t2,at; break 6` is
 * the IDO signed `%` div0/INT_MIN-overflow guard pair on the ring
 * index - documented C-unsuppressible (docs/IDO_CODEGEN.md
 * #feedback-ido-signed-mod-break-pair). INCLUDE_ASM remains build
 * path (sub-100 cap via scoring quirk + interrupt bracket / yield-
 * loop shape; no episode; tautology-trap rule). */
extern int func_800066B0(void);
extern void func_800066D0(int s);
extern void func_80003D0C(int *q);
extern int *func_80003E54(int *q);
extern void func_8000A110(int *q, int *t);
extern int *D_8000A420;
extern int __osRunQueue;
#ifdef NON_MATCHING
s32 func_80004BE0(int *mq, int *msg, s32 flag) {
    int s = func_800066B0();
    while (*(int*)((char*)mq + 0x8) == 0) {
        if (flag == 0) {
            func_800066D0(s);
            return -1;
        }
        *(s16*)((char*)D_8000A420 + 0x10) = 8;
        func_80003D0C(mq);
    }
    if (msg != 0) {
        *msg = *(int*)((char*)mq + 0x14 + *(int*)((char*)mq + 0xC) * 4);
        *(int*)((char*)mq + 0xC) =
            (*(int*)((char*)mq + 0xC) + 1) % *(int*)((char*)mq + 0x10);
    }
    *(int*)((char*)mq + 0x8) -= 1;
    if (*(int**)((char*)mq + 0x4) != 0)
        func_8000A110(&__osRunQueue, func_80003E54((int*)((char*)mq + 0x4)));
    func_800066D0(s);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80004BE0);
#endif




INCLUDE_ASM("asm/nonmatchings/kernel", func_80004D20);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004DB8);
