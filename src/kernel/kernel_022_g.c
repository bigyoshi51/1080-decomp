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
extern s32 D_8000A2E0;
extern s32 D_8000A41C;
extern s32 func_80002890(s32);
extern void func_8000A0E0(void);
extern void func_80005350(s32, s32);
extern void func_80005400(s32, s32);
extern s32 func_80008430();
extern void func_80009148(s32);
extern void func_80009030(s32, s32);
extern void func_80008498(void);
extern s32 func_80006A98(s32);
extern void func_800091F0(s32);
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



/* split from kernel_022.c - 2026-06-10 kernel ROM-order relayout */


/* func_80009474 split out to kernel_054.c (-O1, NON_MATCHING) */

/* func_80009584 (rmon debug command handler, 0x118): MATCHED 2026-07-15
 * (agent-h), retracting the "pure IDO coloring/scheduling cap, permuter
 * ~5500 iters never 0" verdict. Four levers:
 *  - `char* volatile arg0` + `s0 = arg0;` BEFORE the guard: direct home
 *    reload `lw s0,0x250(sp)` hoisted by as1 into the jal delay slot
 *    (fixes prologue sw s0 order + kills the dead `lw a0` reload).
 *  - zero-arg K&R call `func_80008430()` (extern decl de-prototyped):
 *    a0 still holds arg0 from the prologue, no arg setup emitted.
 *  - decl-order frame map: `register char* s0` reserves a DEAD HOME even
 *    at -O1 in this aggregate-bearing frame; moving its decl below `val`
 *    relocates the hole from 0x24C to 0x240 and snaps val/cnt/p to
 *    0x244/0x248/0x24C (E04-class dead-home interleave).
 *  - hdr.flags=0 store emitted in statement order: swap flags before zero0. */
extern s32 func_800066F0(void*, s32, s32);
extern void __rmonSendHeader(s32*, s32, s32);
extern void func_800090B4(s32, s32);
extern void func_800074A0(s32, s32);

typedef struct { s32 zero0; u8 type; char pad5; u16 flags; s32 pad8; s32 code; } RmonHdr16;

s32 func_80009584(char* volatile arg0) {
    char* p;
    s32 cnt;
    s32 val;
    register char* s0;
    s32 buf[128];
    RmonHdr16 hdr;
    register s32 i;
    register s32 recv;

    s0 = arg0;
    if (func_80008430() != 0) {
        return -4;
    }
    hdr.code = *(s32*)(s0 + 0xC);
    hdr.type = *(u8*)(s0 + 0x4);
    hdr.flags = 0;
    hdr.zero0 = 0x210;
    val = 0x210;
    p = (char*)&val;
    cnt = 0;
    do {
        recv = func_800066F0(p + cnt, 4 - cnt, 8);
        cnt += recv;
    } while (cnt < 4);
    __rmonSendHeader((s32*)&hdr, 0x10, 1);
    func_80009148(1);
    for (i = 0; i < 0x20; i++) {
        func_800090B4(0x3A, i);
        func_80008498();
        func_800074A0(0x04000000, 0x10);
    }
    func_800091F0(1);
    return 0;
}
