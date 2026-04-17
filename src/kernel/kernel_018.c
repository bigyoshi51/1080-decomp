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



INCLUDE_ASM("asm/nonmatchings/kernel", func_800066B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800066D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800066EC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800066F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006720);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006754);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006790);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000698C);








/* __rmonWriteWordTo (unimplemented stub) */
s32 func_80006C58(s32 arg0) {
    return -1;
}








INCLUDE_ASM("asm/nonmatchings/kernel", func_800070A0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800071C0);





INCLUDE_ASM("asm/nonmatchings/kernel", func_800073F8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000745C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007564);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007698);








INCLUDE_ASM("asm/nonmatchings/kernel", func_80007A98);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007B3C);
