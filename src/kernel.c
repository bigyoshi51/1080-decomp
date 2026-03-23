#include "common.h"


/* Merged kernel — compiled at -O2 */
/* O1 decompiled functions use INCLUDE_ASM; matching C source in src/o1/ */

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



INCLUDE_ASM("asm/nonmatchings/kernel", func_80000000);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800000B0);

void func_80000118(s32 a0, s32 a1) {
    s32 saved = func_80002890(1);
    func_8000A0E0();
    func_80005350(a0, a1);
    func_80005400(a0, a1);
    func_80002890(saved);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000168);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800001DC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000020C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000260);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800003A8);

/* uso_set_alloc */
extern s32 D_8000A2E0;
void func_80000474(s32 val) {
    D_8000A2E0 = val;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000480);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800004B8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000518);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000568);

/* uso_stub_ret0 */
s32 func_8000058C(s32 arg0) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000598);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800005D8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800005DC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000060C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000660);

/* uso_advance_position */
void func_80000688(s32* file, s32 offset) {
    file[1] += offset;
}

INCLUDE_ASM("asm/nonmatchings/kernel", uso_file_open);

/* uso_skip_to_end: reads USO section headers until End (type 11) */
/* NON_MATCHING: beq operand order (cosmetic, $s2/$t6 swap in 2 instructions) */
#ifdef NON_MATCHING
s32 uso_skip_to_end(FileState* file) {
    s32 pad;
    u32 header[3];
    s32 pad2;
    do {
        if (func_800009D8(header, 12, 1, file) < 0) {
            return D_80013004;
        }
        if (header[0] != 8) {
            file->position += header[1];
        }
    } while (header[0] != 11);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", uso_skip_to_end);
#endif

/* uso_file_check — always returns 1 (success) */
s32 func_800007C4(s32 a0, s32 a1) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800007D4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000085C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000874);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000880);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800008B8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800008F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000098C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800009D8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800009EC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000A88);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000A98);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000B34);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000C88);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000D2C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000DEC);

void func_80000E58(void) {
    D_80012C44(&D_8000A32C, &D_8000A340);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000E8C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001088);

/* uso_get_vtable — returns pointer to USO vtable */
extern s32 D_80012BC0;
void* func_800010B4(void) {
    return &D_80012BC0;
}

/* uso_set_callbacks (no-op) */
void func_800010C0(s32 a0, s32 a1) {
}

void func_800010CC(s32 a0, ...) {
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800010E8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001184);

INCLUDE_ASM("asm/nonmatchings/kernel", uso_find_file);

/* uso_get_error — returns last error code */
s32 func_800012AC(s32 arg0) {
    return D_80013004;
}

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

/* uso_file_end — returns file position + size */
s32 func_80001460(s32* file) {
    return file[1] + file[3];
}

/* uso_seek — set or adjust file position */
s32 func_80001470(s32* file, s32 whence, s32 offset) {
    if (whence) {
        file[1] += offset;
    } else {
        file[1] = offset;
    }
    return file[1];
}

/* uso_file_close (no-op) */
void func_80001494(s32 arg0) {
}

/* uso_ret_zero — returns 0.0f */
float func_8000149C(void) {
    return 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800014A8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001584);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001594);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800015D0);

void func_800017B4(void) {
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800017BC);

void func_800018A8(void) {
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800018B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800018F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001994);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001ADC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001CB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001CF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001CF4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001DD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001EC8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001EDC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800020F4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800021A4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800021D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002250);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800022C8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000235C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800023E0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002530);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800025A4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002650);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000275C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800027E0);

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

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002E70);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002E78);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002F78);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800030D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031E0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003C24);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003D0C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003D40);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003E0C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003E54);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003E64);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003FF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004030);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800044CC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800045C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004650);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004730);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800047B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800047E4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004808);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000487C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800048CC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800048E8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800049B8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004A50);

/* Decompiled at -O1: see src/o1/func_80004AC0.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80004AC0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004B10);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004B30);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004BB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004BE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004C08);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004C7C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004CE8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004D20);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004DB8);

/* Decompiled at -O1: see src/o1/func_80004DE0.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80004DE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004E50);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004EC0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004F50);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004FD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004FE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005000);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800050C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005120);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005134);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005184);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800051E0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800051F0);

/* Decompiled at -O1: see src/o1/func_800052C0.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800052C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800052F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005350);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800053D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005400);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800054C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005520);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005534);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005584);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800056C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800056EC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800056F0);

void func_80005800(void) {
    D_8000A480 = 1;
    func_800053D0(&__osPiAccessQueue, &siacs_bss_0000, 1);
    func_80005DC0(&__osPiAccessQueue, 0, 0);
}

/* Decompiled at -O1: see src/o1/func_80005850.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80005850);

void func_80005894(void) {
    func_80005DC0(&__osPiAccessQueue, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800058C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005920);

/* Decompiled at -O1: see src/o1/func_800059C0.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800059C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005B10);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005C00);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005C50);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005C94);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005DC0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005F10);

/* Decompiled at -O1: see src/o1/func_800060F0.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800060F0);

/* Decompiled at -O1: see src/o1/func_80006110.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80006110);

/* Decompiled at -O1: see src/o1/func_800061F0.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800061F0);

/* __osPiReadStatus */
s32 func_80006240(void) {
    return *(volatile s32*)0xA4600010;
}

/* Decompiled at -O1: see src/o1/func_80006250.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80006250);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800062B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800062D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800062F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800064F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006510);

/* Decompiled at -O1: see src/o1/func_800065B0.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800065B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800065BC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800065F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006640);

/* Decompiled at -O1: see src/o1/__osResetGlobalIntMask.c */
INCLUDE_ASM("asm/nonmatchings/kernel", __osResetGlobalIntMask);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006698);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800066B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800066D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800066EC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800066F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006720);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006754);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006790);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000698C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800069BC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006A50);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006A98);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006AEC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006B20);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006B54);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006BD8);

/* __rmonWriteWordTo (unimplemented stub) */
s32 func_80006C58(s32 arg0) {
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006C64);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006D0C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006D7C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006F60);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006FF8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800070A0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800071C0);

INCLUDE_ASM("asm/nonmatchings/kernel", __rmonSendHeader);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800073DC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800073F8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000745C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800074A0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007564);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007698);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007760);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800077DC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000785C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000798C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800079F4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007A98);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007B3C);

/* Decompiled at -O1: see src/o1/func_80007DD0.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80007DD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007EA0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007EEC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007FC8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007FE8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008030);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008054);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800080D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000817C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800081D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008264);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800082EC);

/* Decompiled at -O1: see src/o1/func_80008424.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008424);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008430);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008454);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008498);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800084AC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800084D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000857C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000858C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800087B4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008848);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000890C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000894C);

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

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008BB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008BB4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008C00);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008C30);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008C48);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008CB4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008D0C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008D48);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008D4C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008DF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008E08);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008E38);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008E98);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008EA0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008ED0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008FB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008FF4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009000);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009030);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800090B4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009144);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009148);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800091F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800091FC);

s32 func_800092B0(s32 a0) {
    s32 result;
    if (func_80008430(a0) != 0) {
        return 0;
    }
    func_80009148(0);
    func_80009030(0x2B, a0);
    func_80008498();
    result = func_80006A98(0x04000000);
    func_800091F0(0);
    return result;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009314);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009474);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009584);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000969C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800096B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009760);

/* __osGetActiveQueue */
extern s32 D_8000A41C;
s32 func_80009830(void) {
    return D_8000A41C;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009840);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009850);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800099F0);

/* Decompiled at -O1: see src/o1/func_80009A50.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009A50);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009AA0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009AB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009B60);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009C30);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009C40);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009C50);

/* Decompiled at -O1: see src/o1/func_80009C90.c */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009C90);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009CE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009D10);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009DF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009E50);

INCLUDE_ASM("asm/nonmatchings/kernel", D_80009E60);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009EA0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009EB0);
