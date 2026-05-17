#include "common.h"

extern s32 __osPiAccessQueue;
extern s32 D_8000A480;
extern s32 siacs_bss_0000;
extern void func_800053D0(s32*, s32*, s32);
extern void func_80005DC0(s32*, s32, s32);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005350);

/* func_80005520 - verified structural decode (kernel, 0x1CC, 115
 * insns) = libultra osCreatePiManager. Reference: libreultra
 * src/io/pimgr.c (__osPiDevMgr, __osPiAccessQueue,
 * __osPiCreateAccessQueue, osCreateThread/osStartThread).
 *   void func_80005520(OSPri pri, OSMesgQueue *cmdQ,
 *                      OSMesg *cmdBuf, s32 cmdMsgCnt) {
 *       if (__osPiDevMgr.active) return;          // D_8000A450
 *       osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);   // 800053D0
 *       osCreateMesgQueue(&__osPiAccessQueue,
 *                         &pimgr_bss_17B8, 1);
 *       if (D_8000A480) func_80005584();          // accessQ enable
 *       else {
 *           func_80005C00();
 *           osCreateThread(8, &pimgr_bss_17A0, ...,
 *                          stack(0x22222222 fill));     // 800051E0
 *           ...
 *           if (osGetThreadPri(NULL) < pri)            // 800064F0
 *               osSetThreadPri(NULL, pri);             // 80006510
 *           s = __osDisableInt();                      // 800066B0
 *           __osPiDevMgr.active     = 1;               // D_8000A450
 *           __osPiDevMgr.cmdQueue   = pimgr_bss_0000;  // D_8000A454
 *           __osPiDevMgr.cmdQueue2  = cmdQ;            // D_8000A458
 *           __osPiDevMgr.thread     = &pimgr_bss_17A0; // D_8000A45C
 *           ... osStartThread + __osRestoreInt(s) ...
 *       }
 *   }
 * Struct-typing reference: D_8000A450 = __osPiDevMgr.active flag
 * (created-once guard), D_8000A454/0x458/0x45C = devmgr fields
 * (evt/cmd queues, mgr thread); __osPiAccessQueue = the access
 * mesg-queue; pimgr_bss_0000/01B0/17A0/17B8 = PI-manager BSS
 * (thread struct, stack, queue storage); D_8000A480 = an
 * access-queue-enable selector. func_800053D0 = osCreateMesgQueue,
 * func_800051E0 = osCreateThread (stack pre-filled 0x22222222),
 * func_800064F0/_80006510 = osGetThreadPri/osSetThreadPri,
 * func_800066B0 = __osDisableInt. Caps <80: libultra thread+queue
 * init + interrupt bracket + ~8 callees + many &D global stores.
 * Full body INCLUDE_ASM-preserved (.s = source of truth).
 * INCLUDE_ASM (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80005520);




INCLUDE_ASM("asm/nonmatchings/kernel", func_800056F0);

/* __osSiCreateAccessQueue */
void func_80005800(void) {
    D_8000A480 = 1;
    func_800053D0(&__osPiAccessQueue, &siacs_bss_0000, 1);
    func_80005DC0(&__osPiAccessQueue, 0, 0);
}
