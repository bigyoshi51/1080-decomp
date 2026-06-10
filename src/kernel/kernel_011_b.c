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


/* split from kernel_011.c - 2026-06-10 kernel ROM-order relayout */


void func_80006110(Thread* thread, s32 pri) {
    register s32 sr = func_800066B0();
    if (thread == 0) {
        thread = (Thread*)D_8000A420;
    }
    if (thread->pri != pri) {
        thread->pri = pri;
        /* (Thread*)(void*)thread double-cast flips the t1/t2 allocno pair
         * (ROM: thread->$t1, D_8000A420->$t2; plain compare numbers them
         * the other way). Found 2026-06-10 kernel relayout audit. */
        if ((Thread*)(void*)thread != (Thread*)D_8000A420 && thread->state != 1) {
            func_80003FF0(thread->queue, thread);
            func_80003E0C(thread->queue, thread);
        }
        if (((Thread*)D_8000A420)->pri < ((Thread*)D_8000A418)->pri) {
            ((Thread*)D_8000A420)->state = 2;
            func_80003D0C(&D_8000A418);
        }
    }
    func_800066D0(sr);
}

/* __osSetGlobalIntMask */
void func_800061F0(s32 mask) {
    register s32 sr = func_800066B0();
    D_8000A3E0 |= mask;
    func_800066D0(sr);
}
