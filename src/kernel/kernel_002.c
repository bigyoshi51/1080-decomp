#include "common.h"


#ifdef NON_MATCHING
/* func_80004B10: 52-insn (0xD0) RDB read-loop with lazy init.
 * Likely __osRdbRead-style host-read function.
 *
 * Lazy-inits a message queue (D_8000A440 flag-guarded) on first call:
 *   osCreateMesgQueue(&readhost_bss_0000, &readhost_bss_0018, 1)
 *   osSetEventMesg(0xF, &readhost_bss_0000, 0)
 *
 * Then publishes (buf, ct) to global slots __osRdb_Read_Data_Buf/Ct,
 * and if ct != 0, loops osRecvMesg until accumulated recv > 0.
 * Final osSendMesg releases the queue.
 *
 * Initial structural decode - no register tuning yet. */
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
    if (ct != 0) {
        do {
            count += func_800066F0(&msg, 1, 5);
        } while (count == 0);
    }
    func_80004FE0(&readhost_bss_0000, 0, 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80004B10);
#endif


/* func_80004BE0 - verified structural decode (kernel, 0x138, 80
 * insns) = libultra osRecvMesg. Reference: libreultra
 * src/os/recvmesg.c / sendmesg.c (OSMesgQueue, __os* thread ops).
 *   s32 func_80004BE0(OSMesgQueue *mq, OSMesg *msg, s32 flag) {
 *       s = __osDisableInt();                     // func_800066B0
 *       while (mq->validCount == 0) {             // mq->0x8
 *           if (flag == OS_MESG_NOBLOCK) {        // arg2 == 0
 *               __osRestoreInt(s);                // func_800066D0
 *               return -1;
 *           }
 *           __osRunningThread->state = 8;         // D_8000A420->0x10
 *           __osEnqueueAndYield(&mq->mtqueue?);   // func_80003D0C
 *       }
 *       if (msg != NULL) {
 *           *msg = mq->msg[mq->first];            // 0x14[0xC]
 *           mq->first = (mq->first + 1) % mq->msgCount; // 0xC/0x10
 *       }
 *       mq->validCount--;
 *       if (mq->fullqueue->next != NULL)          // mq->0x4 ->0x0
 *           __osEnqueueThread(&__osRunQueue,
 *               __osPopThread(&mq->fullqueue));   // 3E54 / A110
 *       __osRestoreInt(s);
 *       return 0;
 *   }
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
 * #feedback-ido-signed-mod-break-pair); the target libultra code
 * has these too, so a plain `% mq->msgCount` is correct - this caps
 * <100 only via that scoring quirk + the interrupt bracket /
 * yield-loop shape. Full body INCLUDE_ASM-preserved (.s = source
 * of truth). INCLUDE_ASM (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80004BE0);




INCLUDE_ASM("asm/nonmatchings/kernel", func_80004D20);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004DB8);
