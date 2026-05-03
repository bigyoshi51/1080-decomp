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


/* __rmonWriteWordTo (unimplemented stub) */
s32 func_80008424(s32 arg0) {
    return -1;
}


#ifdef NON_MATCHING
/* func_80008430: 9-insn prologue fragment of a larger __rmon function
 * splat-split into 3 pieces:
 *   - func_80008430 (this, 0x24 / 9 insns) — prologue + first slti+bnez
 *   - func_80008454 (kernel_018? 0x44 / 17 insns) — branch arms + rmonbrk_bss lookup
 *   - func_80008498 (further fragment(s) past .L80008578)
 *
 * Decoded entry semantics:
 *   s32 f(MsgPtr *a0) {
 *     SaveState *s0 = (SaveState*)a0;          // s0 spilled+reloaded from sp
 *     int idx = s0->field_0x10;
 *     if (idx >= 0x10) return -2;              // bnez at→fall-through to "b end; v0=-2"
 *     if (a0->byte_0x9 != 1) goto skip;        // bne t8, 1, .L800084D8
 *     // ...rmonbrk_bss_0088[idx] table lookup, more nested checks...
 *   }
 *
 * Likely __rmonSetBrkpt or __rmonGetBrkPC (sets/gets a hardware breakpoint).
 * Cannot match as standalone C — fragment boundary cuts mid-function and the
 * splat-merge recipe is non-trivial here (3 .o files, layout shifts). Same
 * class as func_80006698. Stub body documents the fragment relationship for
 * grep discoverability per feedback_orphan_include_asm_after_split_function_decomp.md. */
void func_80008430(void) {
    /* see func_80008454 + func_80008498 for the rest of this function;
     * merge requires linker-layout adjustment across kernel_018-021.c. */
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008430);
#endif
