#include "common.h"

/* Forward declarations for decompiled functions */
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
extern void func_8000857C(void);
extern void func_8000785C(s32);
extern void func_80008ED0(void);
extern void func_80007760(void);
typedef void (*FuncPtr2)(void*, void*);
extern FuncPtr2 D_80012C44;
extern s32 D_8000A32C;
extern s32 D_8000A340;






































/* uso_read */
























INCLUDE_ASM("asm/nonmatchings/kernel", func_800029B0);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80002A3C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002A78);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80002AE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002B1C);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80002BA8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002C08);





INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003C24);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003D0C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004030);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800044CC);





INCLUDE_ASM("asm/nonmatchings/kernel", func_80004808);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800048CC);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80004A50);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80004BB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004CE8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004DB8);



INCLUDE_ASM("asm/nonmatchings/kernel", func_80004F50);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80005000);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80005134);


INCLUDE_ASM("asm/nonmatchings/kernel", func_800051F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800052C0);


INCLUDE_ASM("asm/nonmatchings/kernel", func_800056C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800056F0);

/* __osSiCreateAccessQueue */


/* __osPiGetAccess */

void func_80005850(void) {
    s32 msg;
    if (D_8000A480 == 0) {
        func_80005C00();
    }
    func_80004FE0(&__osPiAccessQueue, &msg, 1);
}




INCLUDE_ASM("asm/nonmatchings/kernel", func_800059C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005C00);


INCLUDE_ASM("asm/nonmatchings/kernel", func_800060F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006110);





INCLUDE_ASM("asm/nonmatchings/kernel", func_800062D0);


INCLUDE_ASM("asm/nonmatchings/kernel", func_800065B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006640);






INCLUDE_ASM("asm/nonmatchings/kernel", func_80006790);




INCLUDE_ASM("asm/nonmatchings/kernel", func_80006C64);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80006D7C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006F60);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006FF8);


INCLUDE_ASM("asm/nonmatchings/kernel", func_800071C0);


INCLUDE_ASM("asm/nonmatchings/kernel", func_800073F8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800074A0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007564);


INCLUDE_ASM("asm/nonmatchings/kernel", func_8000798C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007A98);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007B3C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007DD0);



INCLUDE_ASM("asm/nonmatchings/kernel", func_80007FC8);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80008030);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008054);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800080D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800081D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800082EC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008424);


INCLUDE_ASM("asm/nonmatchings/kernel", func_8000858C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800087B4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008848);


INCLUDE_ASM("asm/nonmatchings/kernel", func_8000898C);






INCLUDE_ASM("asm/nonmatchings/kernel", func_80008AD0);





INCLUDE_ASM("asm/nonmatchings/kernel", func_80008D4C);








INCLUDE_ASM("asm/nonmatchings/kernel", func_80009474);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009584);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800096B0);




INCLUDE_ASM("asm/nonmatchings/kernel", func_80009850);



INCLUDE_ASM("asm/nonmatchings/kernel", func_80009AA0);




INCLUDE_ASM("asm/nonmatchings/kernel", func_80009CE0);





/* osPiRawWriteIo */
s32 func_80009C90(s32 devAddr, s32 val) {
    extern s32 func_80009000(void);
    if (func_80009000() != 0) {
        return -1;
    }
    *(volatile s32*)(0xA0000000 | devAddr) = val;
    return 0;
}

/* __osResetGlobalIntMask */
extern s32 func_8000A090(s32, s32);

void __osResetGlobalIntMask(s32 arg0, s32 arg1) {
    if (func_8000A090(arg0, arg1) != 0) {
        do {
        } while (func_8000A090(arg0, arg1) != 0);
    }
}

/* osPiRawReadIo */
extern s32 func_800056C0(void);

s32 func_80004AC0(s32 devAddr, s32* data) {
    if (func_800056C0() != 0) {
        return -1;
    }
    *data = *(volatile s32*)(0xA0000000 | devAddr);
    return 0;
}

/* __osSetGlobalIntMask */
void func_800061F0(s32 mask) {
    register s32 sr = func_800066B0();
    D_8000A3E0 |= mask;
    func_800066D0(sr);
}

/* __osResetGlobalIntMask (bitwise) */
void func_80006250(s32 mask) {
    register s32 sr = func_800066B0();
    D_8000A3E0 &= ~(mask & ~0x401);
    func_800066D0(sr);
}

/* osSetEventMesg */
typedef struct { s32 queue; s32 msg; } OSEventState;
extern OSEventState __osEventStateTab[];

void func_80004DE0(s32 event, void* queue, s32 msg) {
    register s32 sr = func_800066B0();
    OSEventState* es = &__osEventStateTab[event];
    es->queue = (s32)queue;
    es->msg = msg;
    func_800066D0(sr);
}

/* osYieldThread */
extern void* D_8000A420;
extern s32 D_8000A418;
extern void func_80003D0C(s32*);

void func_80009A50(void) {
    register s32 sr = func_800066B0();
    *(s16*)((char*)D_8000A420 + 0x10) = 2;
    func_80003D0C(&D_8000A418);
    func_800066D0(sr);
}
