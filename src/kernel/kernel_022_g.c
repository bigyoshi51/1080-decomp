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



/* split from kernel_022.c - 2026-06-10 kernel ROM-order relayout */


/* func_80009474 split out to kernel_054.c (-O1, NON_MATCHING) */

/* func_80009584 - verified structural decode (kernel, 0x118, rmon
 * debug command handler). SIBLING of the rmon family (calls
 * __rmonSendHeader; cf. func_8000798C / func_80007A98 / RmonMsg).
 * Struct-typing reference: s0 = RmonMsg (same layout as the
 * func_8000798C family) - s0->0x4 (4) u8 domain, s0->0xC (12) type;
 * stack rmon header at sp+0x30 {type@+0, 0x210 const at +4,
 * flags@+0x6 (u16), domain@+0xA (u8)}. func_800066F0(dst, maxlen,
 * chunk) = bounded read returning bytes read; needs >=4 to proceed.
 * __rmonSendHeader(hdr, len=0x10, flag=1) = the shared rmon emit.
 * The 0x20-iteration loop (func_800090B4(0x3A,i) build +
 * func_80008498 + func_800074A0(0x04000000=PI/cart, 0x10) IO)
 * streams 32 records; func_80009148(1)/func_800091F0(1) = bracket
 * begin/end. Caps <80: rmon stack-struct builder + bounded-read +
 * 32x callee loop + 8 distinct callees. INCLUDE_ASM remains build
 * path (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
extern int func_800066F0(void *dst, int maxlen, int chunk);
extern void func_80009148(int x);
extern void func_800090B4(int a, int b);
extern void func_80008498(void);
extern void func_800091F0(int x);
extern void func_800073F8();   /* fn-ptr-cast at call site below */
extern void func_800074A0();   /* fn-ptr-cast at call site below */
s32 func_80009584(char *s0) {
    int hdr[4];
    int buf[128];  /* sp+0x244 */
    int *bufptr;
    int cnt = 0;
    int n;
    int i;
    if (func_80008430((s32)s0) == 0) return -4;
    hdr[0] = *(int*)(s0 + 0xC);
    hdr[1] = 0x210;
    *(unsigned short*)((char*)hdr + 0x6) = 0;
    *(unsigned char*)((char*)hdr + 0xA) = *(unsigned char*)(s0 + 0x4);
    bufptr = buf;
    n = func_800066F0((char*)bufptr + cnt, 4 - cnt, 8);
    cnt += n;
    if (cnt >= 4) {
        ((void (*)(void*, int, int))func_800073F8)(hdr, 0x10, 1);
        func_80009148(1);
        for (i = 0; i < 0x20; i++) {
            func_800090B4(0x3A, i);
            func_80008498();
            ((void (*)(unsigned int, int))func_800074A0)(0x04000000U, 0x10);
        }
    }
    func_800091F0(1);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009584);
#endif
