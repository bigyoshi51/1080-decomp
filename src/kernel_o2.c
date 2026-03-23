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

/* Boot init */
extern s32 func_80002890(s32);
extern void func_8000A0E0(void);
extern void func_80005350(s32, s32);
extern void func_80005400(s32, s32);

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

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000474);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000480);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000568);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000058C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000598);

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


INCLUDE_ASM("asm/nonmatchings/kernel", func_80002A10);



INCLUDE_ASM("asm/nonmatchings/kernel", func_80002AB4);



INCLUDE_ASM("asm/nonmatchings/kernel", func_80002B78);



INCLUDE_ASM("asm/nonmatchings/kernel", func_80002CA4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002CD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DE0);







INCLUDE_ASM("asm/nonmatchings/kernel", func_800045C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004650);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004730);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800047E4);



INCLUDE_ASM("asm/nonmatchings/kernel", func_800048E8);





INCLUDE_ASM("asm/nonmatchings/kernel", func_80004EC0);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80004FE0);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80005120);


INCLUDE_ASM("asm/nonmatchings/kernel", func_800051E0);



INCLUDE_ASM("asm/nonmatchings/kernel", func_800054C0);



/* __osSiCreateAccessQueue */

void func_80005800(void) {
    D_8000A480 = 1;
    func_800053D0(&__osPiAccessQueue, &siacs_bss_0000, 1);
    func_80005DC0(&__osPiAccessQueue, 0, 0);
}

/* __osPiGetAccess */



void func_80005894(void) {
    func_80005DC0(&__osPiAccessQueue, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005920);



INCLUDE_ASM("asm/nonmatchings/kernel", func_80005F10);



INCLUDE_ASM("asm/nonmatchings/kernel", func_80006240);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800062B0);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80006510);



INCLUDE_ASM("asm/nonmatchings/kernel", func_800066D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800066F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006720);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006754);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80006B54);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006BD8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80006C58);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80006D0C);




INCLUDE_ASM("asm/nonmatchings/kernel", func_800070A0);


INCLUDE_ASM("asm/nonmatchings/kernel", __rmonSendHeader);




INCLUDE_ASM("asm/nonmatchings/kernel", func_8000785C);





INCLUDE_ASM("asm/nonmatchings/kernel", func_80007EA0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007EEC);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80007FE8);







INCLUDE_ASM("asm/nonmatchings/kernel", func_8000857C);




INCLUDE_ASM("asm/nonmatchings/kernel", func_8000890C);



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


INCLUDE_ASM("asm/nonmatchings/kernel", func_80008BB4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008C00);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008C48);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008D0C);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80008E38);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008FB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800090B4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800091F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800091FC);

/* rmon execute */
extern s32 func_80008430(s32);
extern void func_80009148(s32);
extern void func_80009030(s32, s32);
extern void func_80008498(void);
extern s32 func_80006A98(s32);
extern void func_800091F0(s32);

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




INCLUDE_ASM("asm/nonmatchings/kernel", func_80009760);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009830);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009840);


INCLUDE_ASM("asm/nonmatchings/kernel", func_800099F0);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80009C30);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009C50);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80009E50);



