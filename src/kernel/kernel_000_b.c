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

/* 2026-06-24 reference-confirmed PRIVILEGED-ASM handwritten (CP0/TLB/FPU: mtc0/mfc0/tlbwi/ctc1/cfc1 — no C form, like libreultra src/os/*.s). INCLUDE_ASM is canonical/permanent; 0.0% fuzzy is CORRECT, not a pending decode. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DB0);

/* 2026-06-24 reference-confirmed PRIVILEGED-ASM handwritten (CP0/TLB/FPU: mtc0/mfc0/tlbwi/ctc1/cfc1 — no C form, like libreultra src/os/*.s). INCLUDE_ASM is canonical/permanent; 0.0% fuzzy is CORRECT, not a pending decode. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002E70);

/* 2026-06-24 reference-confirmed PRIVILEGED-ASM handwritten (CP0/TLB/FPU: mtc0/mfc0/tlbwi/ctc1/cfc1 — no C form, like libreultra src/os/*.s). INCLUDE_ASM is canonical/permanent; 0.0% fuzzy is CORRECT, not a pending decode. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80002E78);

/* func_80002F78 / func_800030D0 merged into func_80002E78.s as alabel
 * alternative entries (2026-08-22): one contiguous handwritten exception/rdb
 * handler stream -- 2E78 falls through into 2F78 (mfc0 tail, no jr ra), 2F78
 * ends with a branch whose DELAY SLOT is 30D0's first insn, and both branch
 * forward into func_800031F0's labels. jal callers (func_80002530,
 * func_80004E50, func_800058C0) resolve via the global alabel symbols. */

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031E0);

/* 2026-06-24 reference-confirmed PRIVILEGED-ASM handwritten (CP0/TLB/FPU: mtc0/mfc0/tlbwi/ctc1/cfc1 — no C form, like libreultra src/os/*.s). INCLUDE_ASM is canonical/permanent; 0.0% fuzzy is CORRECT, not a pending decode. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800031F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003C24);


/* HANDWRITTEN REGION 2026-06-10: func_80003C24..func_80004030 (through
 * 0x44CC) is one handwritten boot/PI-DMA chain, not compiler output:
 * no prologue past 3D40, t-reg-only dataflow, PI registers (0xA4600010,
 * 0x510(t3)) -- the continuation of the func_800031F0 handwritten
 * handler neighborhood. Permanent INCLUDE_ASM (same class as 31F0).
 * Fragment merges 2026-08-22: func_80003E0C absorbed into func_80003D40.s
 * (3D40's tail lw t9,0x3C(sp) falls through into 3E0C's and t1,t9,at --
 * one instruction stream on 3D40's frame); func_80003E64 absorbed into
 * func_80003E54.s (3E54 ends or v0,zero,zero, no jr ra, falls through).
 * Chain merge 2026-08-22 (second pass): func_80003E54 + func_80003FF0 +
 * func_80004030 absorbed into func_80003D40.s -- one contiguous stream
 * [0x3D40,0x44CC): 3D40 owns the ONLY full prologue (sp -0x40, ra@0x1C),
 * every fragment branches to the shared exit .L800043D4 (lw ra,0x1C;
 * addiu sp,sp,0x40; jr ra) and runs on 3D40's frame; 3E54/3FF0/4030 are
 * register-convention jal entries (live-in t-regs, no prologue), kept as
 * GLOBAL alabel alternative entries -- jal callers (44CC/4BE0/59C0/31F0/
 * 9D10 -> 3E54; 3C24/6110/7DD0 -> 3FF0; 31F0 -> 4030) resolve. The
 * embedded second prologue at 0x43E4 (sp -0x20) was already unnamed
 * inside 4030.s and stays so. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80003D40);

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
 * IDO's signed `%` guards; placement AFTER the store matches the plain C `%`
 * at -O1.
 * EXACT 59/59 (2026-07-09, standalone probe; 5.3 -O1 AND 7.1 -O1 both emit
 * the target bytes -- this TU is already 7.1 -O1, so no donor split needed).
 * The old "pure register-coloring residual" note was three missing levers:
 *   - mq/es as members of a LOCAL STRUCT (struct locals stay sp-resident at
 *     -O1) -> homed at 0x28/0x2C and reloaded per statement;
 *   - `if (1) {}` BB-barrier as the first body statement -> kills the
 *     cross-BB register forwarding of the condition's mq/es temps, forcing
 *     the body-entry reloads (lw t1,0x28 / lw t6,0x2C);
 *   - `last` as a PLAIN fn-scope local declared after v (homed store
 *     sw t7,0x24 + register reuse for the index; a struct member here emits
 *     a second store, a `register` here recolors to s-regs), `t` as
 *     `register` (colors s0, no slot; frame 0x30 with the 0x20 hole). */
extern void func_80003E0C(void *, void *);  /* __osEnqueueThread */
void func_800044CC(void) {
    struct { OSMesgQueue *mq_; OSEventState *es_; } v;
    s32 last;
    register void *t;

    if ((v.mq_ = (OSMesgQueue *)(v.es_ = &__osEventStateTab[8])->queue) != 0 &&
        v.mq_->validCount < v.mq_->msgCount) {
        if (1) {}
        last = (v.mq_->first + v.mq_->validCount) % v.mq_->msgCount;
        v.mq_->msg[last] = (s32 *)v.es_->msg;
        v.mq_->validCount++;
        if (*(void **)v.mq_->mtqueue != 0) {
            t = func_80003E54(v.mq_);
            func_80003E0C(&D_8000A418, t);
        }
    }
}
