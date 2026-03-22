#include "common.h"

/* Forward declarations for decompiled functions */
extern s32 __osPiAccessQueue;
extern s32 D_8000A480;
extern s32 D_80013004;
extern void func_80005DC0(s32*, s32, s32);
extern void func_80005C00(void);
extern void func_80004FE0(s32*, s32*, s32);
extern void func_800053D0(s32*, s32*, s32);
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

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000000);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800000B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000118);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000168);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800001DC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000020C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000260);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800003A8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000474);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000480);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000568);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000058C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000598);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000660);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000688);

INCLUDE_ASM("asm/nonmatchings/kernel", uso_file_open);

INCLUDE_ASM("asm/nonmatchings/kernel", uso_skip_to_end);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800007C4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800007D4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800008B8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800009D8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000B34);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000C88);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000DEC);


void func_80000E58(void) {
    D_80012C44(&D_8000A32C, &D_8000A340);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000E8C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001088);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800010B4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800010C0);

void func_800010CC(s32 a0, ...) {
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800010E8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001184);

INCLUDE_ASM("asm/nonmatchings/kernel", uso_find_file);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800012AC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800012BC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001348);

/* uso_read */
s32 func_80001414(void* file, void* buf, s32 size) {
    extern s32 D_80013004;
    extern s32 func_800009D8(void*, s32, s32, void*);
    s32 result;
    result = func_800009D8(buf, size, 1, file);
    if (result < 0) {
        return D_80013004;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001460);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001470);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001494);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000149C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001584);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800015D0);

void func_800017B4(void) {
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800017BC);

void func_800018A8(void) {
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800018B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800018F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001994);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001CB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001CF4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001DD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800020F4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800021A4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800021D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800022C8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000235C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800023E0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002890);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800029A0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800029B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002A10);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002A3C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002A78);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002AB4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002AE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002B1C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002B78);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002BA8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002C08);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002CA4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002CD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003C24);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003D0C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004030);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800044CC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800045C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004650);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004730);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800047E4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004808);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800048CC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800048E8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004A50);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004AC0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004BB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004CE8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004DB8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004DE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004EC0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004F50);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004FE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005000);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005120);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005134);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800051E0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800051F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800052C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800054C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800056C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800056F0);

/* __osSiCreateAccessQueue */

void func_80005800(void) {
    D_8000A480 = 1;
    func_800053D0(&__osPiAccessQueue, &siacs_bss_0000, 1);
    func_80005DC0(&__osPiAccessQueue, 0, 0);
}

/* __osPiGetAccess */

void func_80005850(void) {
    s32 msg;
    if (D_8000A480 == 0) {
        func_80005C00();
    }
    func_80004FE0(&__osPiAccessQueue, &msg, 1);
}


void func_80005894(void) {
    func_80005DC0(&__osPiAccessQueue, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005920);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800059C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005C00);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005F10);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800060F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006110);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800061F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006240);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006250);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800062B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800062D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006510);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800065B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006640);

INCLUDE_ASM("asm/nonmatchings/kernel", __osResetGlobalIntMask);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800066D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800066F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006720);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006754);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006790);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006B54);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006BD8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006C58);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006C64);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006D0C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006D7C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006F60);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006FF8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800070A0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800071C0);

INCLUDE_ASM("asm/nonmatchings/kernel", __rmonSendHeader);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800073F8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800074A0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007564);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000785C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000798C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007A98);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007B3C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007DD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007EA0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007EEC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007FC8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007FE8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008030);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008054);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800080D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800081D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800082EC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008424);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000857C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000858C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800087B4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008848);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000890C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000898C);


void func_80008A08(void) {
    func_8000857C();
    func_8000785C(0);
    func_80008ED0();
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008A38);


void func_80008AA0(void) {
    func_80007760();
    func_8000785C(0);
    func_80008ED0();
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008AD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008BB4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008C00);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008C48);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008D0C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008D4C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008E38);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008FB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800090B4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800091F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800091FC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800092B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009314);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009474);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009584);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800096B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009760);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009830);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009840);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009850);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800099F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009A50);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009AA0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009C30);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009C50);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009C90);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009CE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009E50);



