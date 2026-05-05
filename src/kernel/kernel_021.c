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
 * splat-split into a 4+ fragment chain (verified 2026-05-05 via asm/.s
 * cross-reference):
 *
 *   - func_80008430 (this, 0x24 / 9 insns) — prologue + first slti+bnez
 *     to .L80008460 (inside func_80008454). Frame -0x48, saves s0/s1/ra.
 *   - func_80008454 (0x44 / 17 insns) — body + dispatch:
 *       0x80008454+0: nop (delay slot of 80008430's bnez)
 *       0x80008458: b .L80008578 (far branch, target inside next fragment)
 *       0x800084??: .L80008460 — `lw t7, 0x48(sp); bnez t8 != 1, .L800084D8`
 *       0x8000848C: bnez t2, .L8000849C (inside func_80008498)
 *       0x80008494: b .L80008578 (far branch, target past 80008498)
 *   - func_80008498 (0x14 / 5 insns) — `.L8000849C: jal func_80006A98(...)`
 *     fragment for the `t2 != 0` arm. Externally-callable (extern void
 *     func_80008498(void) in kernel_054.c).
 *   - func_800084AC, func_800084D0 (further fragments) — `.L800084D8` target
 *     is in 800084D0+; `.L80008578` is also in this range.
 *   - func_8000857C (next standalone function, externally callable from
 *     kernel_000.c) — boundary; 80008430's chain ends just before.
 *
 * Decoded entry semantics:
 *   s32 f(MsgPtr *a0) {
 *     SaveState *s0 = (SaveState*)a0;          // s0 spilled+reloaded from sp
 *     int idx = s0->field_0x10;
 *     if (idx >= 0x10) return -2;              // bnez at→fall-through to "b end; v0=-2"
 *     if (a0->byte_0x9 != 1) goto skip;        // bne t8, 1, .L800084D8
 *     int *entry = rmonbrk_bss_0088 + idx*8;
 *     if (entry[0] != 0) goto skip2;            // .L8000849C
 *     // ...continued in fragments past 80008498...
 *   }
 *
 * Likely __rmonSetBrkpt or __rmonGetBrkPC (sets/gets a hardware breakpoint).
 * MERGE BLOCKED: func_80008498 is externally-callable (alt-entry pattern,
 * not pure fragment) per `extern void func_80008498(void)` in kernel_054.c.
 * Standard merge-fragments removes the alt-entry symbol and breaks callers.
 * Resolution path: keep INCLUDE_ASM with no merge; document the chain for
 * future Ghidra-assisted decode (the rmon family has full struct types in
 * Ghidra). Same class as func_80006698 / func_800047E4 cross-file blockers.
 *
 * Stub body documents the fragment relationship for grep discoverability per
 * feedback_orphan_include_asm_after_split_function_decomp.md. */
/* Match the file-top extern's signature so NON_MATCHING build doesn't error
 * with redeclaration / incompatible-return-type. Stub body — bytes never
 * match anyway since the byte-correct path is INCLUDE_ASM (#else branch). */
s32 func_80008430(s32 a0) {
    /* see func_80008454 + func_80008498 for the rest of this function;
     * merge requires linker-layout adjustment across kernel_018-021.c. */
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008430);
#endif
