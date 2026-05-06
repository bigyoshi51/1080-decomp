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
extern s32 func_80008430(s32);
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


void __osResetGlobalIntMask(s32 arg0, s32 arg1) {
    if (func_8000A090(arg0, arg1) != 0) {
        do {
        } while (func_8000A090(arg0, arg1) != 0);
    }
}


/* func_80006698: 21-insn MMIO read-with-range-check helper covering bytes
 * 0x80006698-0x800066EC (0x54). Splat originally split this into 3
 * fragments at 0x80006698 / 0x800066B0 / 0x800066D0; .s files merged 2026-05-05
 * (see DECOMPILED_FUNCTIONS.md "Fragment Merges Performed").
 *
 * Reads MMIO from 0x04000000-0x05000000 (SP DMEM/IMEM + RCP regs) via
 * func_80008FB0 (likely __osPiRawReadIo). Callers jal into 0x800066B0 and
 * 0x800066D0 as if standalone — those addresses remain in
 * undefined_syms_auto.txt as labels into this body (the call sites work
 * because the ROM bytes are correct; "function" semantics at the inner
 * entries are misleading but byte-stable). */
extern void func_80008FB0(s32, s32*);
s32 func_80006698(s32 a0) {
    s32 local;
    if ((u32)a0 >= 0x04000000U && (u32)a0 < 0x05000000U) {
        func_80008FB0(a0, &local);
        return local;
    }
    return 0;
}
