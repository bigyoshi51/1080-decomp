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



INCLUDE_ASM("asm/nonmatchings/kernel", func_80008454);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008498);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800084AC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800084D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000857C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000858C);

/* Classifies a MIPS instruction: returns 1 if J/JAL/JR/JALR, else 0.
 * NON_MATCHING: IDO picks $v0 for opcode register; target uses $a1.
 * Logic identical, 37 insts, register allocation differs. */
#ifdef NON_MATCHING
s32 func_800087B4(u32 inst) {
    u32 opcode = (inst >> 26) & 0x3F;
    if (opcode == 0) {
        if (((inst >> 5) & 0x7FFF) == 0 && (inst & 0x3F) == 8) return 1;
        if (((inst >> 16) & 0x1F) == 0 && (inst & 0x7FF) == 9) return 1;
        return 0;
    }
    if (opcode == 2 || opcode == 3) return 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800087B4);
#endif


/* func_8000894C split out to kernel_054.c (-O1) */


void func_80008A08(void) {
    func_8000857C();
    func_8000785C(0);
    func_80008ED0();
}



void func_80008AA0(void) {
    func_80007760();
    func_8000785C(0);
    func_80008ED0();
}







INCLUDE_ASM("asm/nonmatchings/kernel", func_80008C30);





INCLUDE_ASM("asm/nonmatchings/kernel", func_80008E08);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008E38);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008E98);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008EA0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008ED0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008FB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008FF4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009000);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009030);

/* func_80009148 split out to kernel_054.c (-O1, absorbed func_800091F0 fragment) */

/* func_800091F0 merged into func_80009148 */

/* func_800091FC split out to kernel_054.c (-O1) */

/* rmon execute */
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

/* func_80009474 split out to kernel_054.c (-O1, NON_MATCHING) */

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009584);

/* func_8000969C split out to kernel_054.c (-O1, NON_MATCHING) */


/* __osSetFpcCsr — hand-written assembly in libultra (cfc1 $v0,$31; ctc1 $a0,$31;
 * jr $ra; nop). Matches libreultra/src/os/setfpccsr.s exactly. IDO doesn't
 * parse GCC inline asm, so there's no C form; INCLUDE_ASM is correct. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009840);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009850);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800099F0);
