#include "common.h"

/* Forward declarations */
extern s32 __osPiAccessQueue;
extern s32 D_8000A480;
extern s32 D_80013004;
extern void func_80005DC0(s32*, s32, s32);
extern void func_80005C00(void);
extern void func_80004FE0(s32*, s32*, s32);
extern void func_800053D0(s32*, s32*, s32);
extern s32 D_8000A3E0;
extern s32 func_800066B0(void);
extern void func_800066D0(s32);
extern void func_80003D0C(s32*);
extern void* D_8000A420;
extern s32 D_8000A418;
extern s32 siacs_bss_0000;
extern s32 func_800009D8(void*, s32, s32, void*);
extern void func_80003FF0(s32, void*);
extern void* func_80003E54(void*);
extern void func_8000A110(void*);
extern void func_8000857C(void);
extern void func_8000785C(s32);
extern void func_80008ED0(void);
extern void func_80007760(void);
typedef void (*FuncPtr2)(void*, void*);
extern FuncPtr2 D_80012C44;
extern s32 D_8000A32C;
extern s32 D_8000A340;
extern s32 D_80012BC0;
extern s32 D_80012BE4;
extern s32 D_80012C64;
extern s32 D_80012C68;
extern s32 D_80012D60[];
extern s32 D_80013000;
extern s32 D_8000A2E0;
extern s32 D_8000A41C;
extern s32 func_80002890(s32);
extern void func_8000A0E0(void);
extern void func_80005350(s32, s32);
extern void func_80005400(s32, s32);
extern s32 func_80008430(s32);
extern void func_80009148(s32);
extern void func_80009030(s32, s32);
extern void func_80008498(void);
extern s32 func_80006A98(s32);
extern void func_800091F0(s32);
extern s32 func_80009EA0(void);
typedef struct { s32 pad[3]; s32 position; } FileState;

typedef struct {
    void* mtqueue;
    void* fullqueue;
    s32 validCount;
    s32 first;
    s32 msgCount;
    s32** msg;
} OSMesgQueue;

typedef struct Thread {
    s32 field0;
    s32 pri;
    s32 queue;
    s32 pad0C;
    u16 state;
} Thread;

typedef struct { s32 queue; s32 msg; } OSEventState;
extern OSEventState __osEventStateTab[];

typedef struct {
    u8 pad_00[0x98];
    u8 in_use;
    u8 pad_99[3];
} UsoSlot;

typedef struct {
    UsoSlot slots[4];
} UsoSlotGroup;

extern u8 D_80013138;
extern UsoSlot D_800130A0;
extern u8 D_800131D4;
extern UsoSlot D_8001313C;
extern u8 D_80013270;
extern UsoSlot D_800131D8;
extern UsoSlotGroup D_80013274;
extern UsoSlotGroup D_800182E4;


/* split from kernel_000.c - 2026-06-10 kernel ROM-order relayout */


/* func_800029B0 + func_80002A10 split out to kernel_045.c (-O1) */

/* func_80002A3C split out to kernel_056.c (-O2 -mips3) */

/* func_80002A78 split out to kernel_056.c (-O2 -mips3) */

/* func_80002AB4 split out to kernel_056.c (-O2 -mips3) */

/* func_80002AE0 split out to kernel_056.c (-O2 -mips3) */

/* func_80002B1C split out to kernel_056.c (-O2 -mips3) */

/* func_80002B78 split out to kernel_056.c (-O2 -mips3) */

/* func_80002BA8 split out to kernel_056.c (-O1 -mips3, d-arithmetic helper) */

/* func_80002C08 split out to kernel_056.c (-O2 -mips3) */

/* func_80002CA4 split out to kernel_056.c (-O2 -mips3) */

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002CD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002E70);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002E78);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002F78);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800030D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031E0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003C24);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80003D40);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003E0C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003E54);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003E64);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003FF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004030);

/* func_800044CC - verified structural decode (kernel, 0xEC, libultra
 * PI-event callback: inlined osSendMesg + thread wake).
 * Reference: libreultra src/os/seteventmesg.c / osSendMesg.c /
 * exceptasm.s (__osEventStateTab, __OSEventState).
 *   void func_800044CC(void) {
 *       __OSEventState *es = &__osEventStateTab[OS_EVENT_PI]; // +0x40
 *       OSMesgQueue *mq = es->queue;          // es->0x0 (at +0x40)
 *       if (mq == NULL) return;
 *       if (mq->validCount < mq->msgCount) {  // 0x8 < 0x10
 *           // inlined osSendMesg body:
 *           idx = (mq->first + mq->validCount) % mq->msgCount;
 *           mq->msg[idx] = es->message;       // es->0x4 -> mq->0x14[]
 *           mq->validCount++;                 // mq->0x8++
 *           if (mq->mtqueue->next != NULL) {  // mq->0x0 -> ->0x0
 *               t = func_80003E54(mq);        // __osPopThread
 *               func_80003E0C(&D_8000A418, t);// __osEnqueueThread
 *           }                                 //   (D_8000A418 =
 *       }                                     //    __osRunQueue)
 *   }
 * Struct-typing reference: __osEventStateTab = libultra event table,
 * __OSEventState = { OSMesgQueue *queue; OSMesg message; } (8 bytes);
 * entry +0x40 = index 8 = OS_EVENT_PI. OSMesgQueue fields used:
 * 0x0 mtqueue (blocked-thread list head), 0x8 validCount, 0xC first,
 * 0x10 msgCount, 0x14 msg[] (OSMesg array). func_80003E54 =
 * __osPopThread(&queue), func_80003E0C = __osEnqueueThread, global
 * D_8000A418 = __osRunQueue. The `div $zero,t4,t5; mfhi` + `break 7`
 * / `break 6` are IDO's signed `%` divide-by-zero (msgCount==0) and
 * INT_MIN/-1 overflow guards on the ring-index modulo. CAP REASON
 * (corrected 2026-05-23): the guards themselves DO match a C `%`; the real
 * blocker is their PLACEMENT — the target emits the break guards AFTER the
 * mq->msg[idx] store, whereas C `%` emits them right after the div (before
 * the store). Plus the event-table base resolves to 0x8001F510 here, not
 * symbol_addrs' __osEventStateTab=0x80019510 (a 0x6000 discrepancy to
 * reconcile before a match). Stays INCLUDE_ASM (no episode). */
#ifdef NON_MATCHING
extern char __osEventStateTab_real[]; /* @0x8001F510 (note: != symbol_addrs) */
extern int D_8000A418;                 /* __osRunQueue */
extern void *func_80003E54(void *);    /* __osPopThread */
extern void func_80003E0C(void *, void *); /* __osEnqueueThread */
void func_800044CC(void) {
    char *es = __osEventStateTab_real + 0x40; /* &table[OS_EVENT_PI] */
    char *mq = *(char **)es;                  /* es->queue */
    if (mq == 0) {
        return;
    }
    if (*(int *)(mq + 0x8) < *(int *)(mq + 0x10)) {   /* validCount < msgCount */
        int idx = (*(int *)(mq + 0xC) + *(int *)(mq + 0x8)) % *(int *)(mq + 0x10);
        *(int *)(mq + 0x14 + idx * 4) = *(int *)(es + 0x4); /* msg[idx] = es->message */
        *(int *)(mq + 0x8) += 1;                       /* validCount++ */
        if (*(char **)(*(char **)mq) != 0) {           /* mtqueue->next */
            void *t = func_80003E54(mq);
            func_80003E0C(&D_8000A418, t);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800044CC);
#endif
