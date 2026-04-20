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


void func_80004DE0(s32 event, void* queue, s32 msg) {
    register s32 sr = func_800066B0();
    OSEventState* es = &__osEventStateTab[event];
    es->queue = (s32)queue;
    es->msg = msg;
    func_800066D0(sr);
}


#ifdef NON_MATCHING
/* PI DOM2 timing + system init. Structurally correct but IDO emits separate
 * `lui $at` for each extern byte (D_800195D4/D5/D6/D7/D8/D9) instead of
 * sharing the base across adjacent bytes (target has e.g. sb t0, D6(at);
 * sb t1, D7(at) with a single at). To match, all these bytes must live in
 * a single struct or array so IDO sees them as one symbol. */
extern u8 D_800195D4;
extern u8 D_800195D5;
extern u8 D_800195D6;
extern u8 D_800195D7;
extern u8 D_800195D8;
extern u8 D_800195D9;
extern s32 D_800195D0;
extern s32 D_800195DC;
extern s32 D_800195E0;
extern s32 D_80019644;
extern void* D_8000A46C;
extern s32 func_800030D0(s32*, s32);

#define IO_WRITE(addr, val) (*(volatile s32*)(addr) = (val))

void* func_80004E50(void) {
    s32 sr;
    D_800195D4 = 2;
    D_800195DC = 0xA5000000;
    D_800195D5 = 3;
    D_800195D8 = 6;
    D_800195D6 = 6;
    D_800195D7 = 2;
    D_800195D9 = 1;
    IO_WRITE(0xA4600024, 3);
    IO_WRITE(0xA4600028, D_800195D8);
    IO_WRITE(0xA460002C, D_800195D6);
    IO_WRITE(0xA4600030, D_800195D7);
    D_800195E0 = 0;
    func_800030D0(&D_800195E0 + 1, 0x60);
    sr = func_800066B0();
    D_800195D0 = (s32)D_8000A46C;
    D_8000A46C = &D_800195D0;
    D_80019644 = (s32)&D_800195D0;
    func_800066D0(sr);
    return &D_800195D0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80004E50);
#endif
