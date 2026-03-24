#include "common.h"

typedef struct Thread {
    s32 field0;
    s32 pri;
    s32 queue;
    s32 pad0C;
    u16 state;
} Thread;

extern void* D_8000A418;
extern void* D_8000A420;
extern s32 func_800066B0(void);
extern void func_800066D0(s32);
extern void func_80003E0C(void*, void*);
extern void* func_80003E54(void*);
extern void func_80003E64(void);
extern void func_80003D0C(void*);

/* osStartThread */
void func_80009D10(Thread* t) {
    register s32 saveMask = func_800066B0();
    switch (t->state) {
    case 8: /* OS_STATE_WAITING */
        t->state = 2;
        func_80003E0C(&D_8000A418, t);
        break;
    case 1: /* OS_STATE_STOPPED */
        if (t->queue == 0 || t->queue == (s32)&D_8000A418) {
            t->state = 2;
            func_80003E0C(&D_8000A418, t);
        } else {
            t->state = 8;
            func_80003E0C((void*)t->queue, t);
            func_80003E0C(&D_8000A418, func_80003E54((void*)t->queue));
        }
        break;
    }
    if ((s32)D_8000A420 == 0) {
        func_80003E64();
    } else {
        if (((Thread*)D_8000A420)->pri < ((Thread*)D_8000A418)->pri) {
            ((Thread*)D_8000A420)->state = 2;
            func_80003D0C(&D_8000A418);
        }
    }
    func_800066D0(saveMask);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009E50);
