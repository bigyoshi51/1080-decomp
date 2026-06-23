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

/* func_80009584 - near-exact structural decode (kernel, 0x118, rmon
 * debug command handler). All logic, callees, loop structure and frame
 * layout match the target; residual is a pure IDO coloring/scheduling
 * cap (~6 diff words of 70, 0 logic diffs). REGALLOC/SCHED residual,
 * NOT a logic bug - verified with decomp-permuter (~5500 iters, base
 * score 410 -> 255, never reached 0).
 *
 * Corrected vs prior decode: the 0xA4 call is __rmonSendHeader (real
 * symbol @0x80007360), NOT func_800073F8 (@0x800073F8) - the prior
 * fn-ptr cast pointed at the wrong address. func_800074A0 is a direct
 * jal (no cast). Both now link-direct to real kernel symbols.
 *
 * Shape: arg0 = RmonMsg (s0->0x4 u8 type, s0->0xC s32 code). Stack
 * rmon header at sp+0x30 {zero0=0x210 @+0, type @+4 (u8), flags @+6
 * (u16)=0, code @+0xC (s32)}, len 0x10. A 1-word local `val`=0x210 is
 * read over by func_800066F0(&val+cnt, 4-cnt, 8) until cnt>=4 (mirrors
 * kernel_043 func_80006FF8 bounded-read idiom). Then __rmonSendHeader
 * + func_80009148(1) begin; 0x20-iter loop emits records via
 * func_800090B4(0x3A,i)/func_80008498/func_800074A0(0x04000000,0x10);
 * func_800091F0(1) ends. Large 0x200 unused stack buffer (buf[128])
 * present in the original frame (0x250) - hence the buf decl.
 *
 * Residual diffs: (1) prologue s0-save ordering; (2) target reloads s0
 * into the delay slot of the func_80008430 call while IDO here emits a
 * dead `lw a0` + separate `lw s0` (+1 insn); (3) a 4-byte stack-pad
 * placement shift on the val/cnt/p trio (target 0x244/0x248/0x24C vs
 * 0x240/0x244/0x248); (4) branch-target offsets cascade from (2).
 * INCLUDE_ASM remains build path (no episode; not byte-exact). */
#ifdef NON_MATCHING
extern s32 func_800066F0(void*, s32, s32);
extern void __rmonSendHeader(s32*, s32, s32);
extern void func_800090B4(s32, s32);
extern void func_800074A0(s32, s32);

typedef struct { s32 zero0; u8 type; char pad5; u16 flags; s32 pad8; s32 code; } RmonHdr16;

s32 func_80009584(char* arg0) {
    register char* s0;
    char* p;
    s32 cnt;
    s32 val;
    s32 buf[128];
    RmonHdr16 hdr;
    register s32 i;
    register s32 recv;

    if (func_80008430((s32)arg0) != 0) {
        return -4;
    }
    s0 = arg0;
    hdr.code = *(s32*)(s0 + 0xC);
    hdr.type = *(u8*)(s0 + 0x4);
    hdr.zero0 = 0x210;
    hdr.flags = 0;
    val = 0x210;
    p = (char*)&val;
    cnt = 0;
    do {
        recv = func_800066F0(p + cnt, 4 - cnt, 8);
        cnt += recv;
    } while (cnt < 4);
    __rmonSendHeader((s32*)&hdr, 0x10, 1);
    func_80009148(1);
    for (i = 0; i < 0x20; i++) {
        func_800090B4(0x3A, i);
        func_80008498();
        func_800074A0(0x04000000, 0x10);
    }
    func_800091F0(1);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009584);
#endif
