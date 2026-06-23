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

/* HANDWRITTEN REGION 2026-06-10: func_80003C24..func_80004030 (through
 * 0x44CC) is one handwritten boot/PI-DMA chain, not compiler output:
 * no prologue at any symbol (3E64: or t2,t1,at first insn; 3FF0: addu
 * t3,t9,t2; 4030: bnez t9 reading the predecessor's t5/t9 loads),
 * t-reg-only dataflow, PI registers (0xA4600010, 0x510(t3)) -- the
 * continuation of the func_800031F0 handwritten handler neighborhood.
 * Permanent INCLUDE_ASM (same class as 31F0). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80003E64);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003FF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004030);

/* func_800044CC - kernel PI-event message dispatch (inlined send_mesg from
 * libultra exceptasm.s). Sends __osEventStateTab[OS_EVENT_PI].message to the
 * registered queue and wakes any blocked thread.
 * Reference: libreultra src/os/exceptasm.s send_mesg / __osPopThread /
 * __osEnqueueThread; src/os/seteventmesg.c (__osEventStateTab, __OSEventState).
 *   __osEventStateTab : __OSEventState[16] @ 0x80019510 (REAL reloc base;
 *                       prior "0x8001F510 discrepancy" note was WRONG).
 *   __OSEventState    : { OSMesgQueue *messageQueue; OSMesg message; } (8B).
 *   entry [8] = +0x40 = OS_EVENT_PI.
 *   OSMesgQueue fields: 0x0 mtqueue, 0x8 validCount, 0xC first,
 *                       0x10 msgCount, 0x14 msg[] (OSMesg*).
 *   func_80003E54 = __osPopThread, func_80003E0C = __osEnqueueThread,
 *   D_8000A418 = __osRunQueue.
 * The div/mfhi + break 7 (div-by-zero) + break 6 (INT_MIN/-1 overflow) are
 * IDO's signed `%` guards; placement AFTER the store DOES match a plain C `%`
 * at -O1 (verified standalone). Compiles at -O1 to within a few words of the
 * target; residual = whether IDO spills mq/es to stack (target reloads on each
 * use) vs keeps them live in regs (this C). Pure register-coloring residual,
 * not a logic diff. */
#ifdef NON_MATCHING
/* Reuses existing OSMesgQueue (mtqueue/validCount/first/msgCount/msg) and the
 * OSEventState event table declared above. __OSEventState entry = 8 bytes:
 * { OSMesgQueue *messageQueue @0x0; void *message @0x4 }. */
typedef struct __OSEventState {
    OSMesgQueue *messageQueue;
    void *message;
} __OSEventState;
/* D_8000A418 (__osRunQueue) and func_80003E54 (__osPopThread) are declared
 * earlier in this file; func_80003E0C is __osEnqueueThread. */
extern void func_80003E0C(void *, void *);  /* __osEnqueueThread */
void func_800044CC(void) {
    __OSEventState *es = &((__OSEventState *)__osEventStateTab)[8]; /* OS_EVENT_PI */
    OSMesgQueue *mq = es->messageQueue;
    if (mq != 0 && mq->validCount < mq->msgCount) {
        int last = (mq->first + mq->validCount) % mq->msgCount;
        mq->msg[last] = (s32 *)es->message;
        mq->validCount++;
        if (((void **)mq->mtqueue)[0] != 0) {
            register void *t = func_80003E54(mq);
            func_80003E0C(&D_8000A418, t);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800044CC);
#endif
