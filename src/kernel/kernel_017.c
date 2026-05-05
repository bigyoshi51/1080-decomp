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


void __osResetGlobalIntMask(s32 arg0, s32 arg1) {
    if (func_8000A090(arg0, arg1) != 0) {
        do {
        } while (func_8000A090(arg0, arg1) != 0);
    }
}


/* func_80006698 is a 21-insn (0x54 byte) function that splat split into 3
 * fragments: func_80006698 (0x18, has prologue + addr-range start), 0x800066B0
 * (0x20, range-end check + jal func_80008FB0), 0x800066D0 (0x1C, return-merge
 * + epilogue). The 0x800066B0 fragment starts with `bnez $at, ...` using the
 * $at set by the predecessor's tail `sltu $at, $t6, $at` — classic
 * splat-fragment-via-register-flow pattern (per
 * feedback_splat_fragment_via_register_flow.md).
 *
 * Merging is non-trivial here: callers in kernel_003/017/019.c reference
 * `func_800066B0` and `func_800066D0` as if they were standalone (probably
 * a misidentified __osDisableInt/__osRestoreInt pair). After merge, those
 * callers would jal into the middle of the merged function with
 * uninitialized $at/$t6 — undefined behavior. ROM-bytes-wise the calls work
 * because asm-processor pastes the 3 INCLUDE_ASMs contiguously, but the
 * "function" semantics at 0x800066B0 are not what the callers think.
 *
 * Merging also requires linker layout adjustment: kernel_017.c.o would grow
 * 0x3C bytes (0x18 → 0x54) which shifts kernel_018.c.o's start. Since the 3
 * fragments currently live in kernel_018.c, removing them shrinks kernel_018
 * by the same 0x3C — but the per-file .text positioning needs verification
 * before the merge can land.
 *
 * Documented decode (NOT compiled in default build):
 *
 *   s32 func_80006698(s32 a0) {
 *       s32 local;
 *       if (a0 < 0x04000000 || a0 >= 0x05000000) return 0;
 *       func_80008FB0(a0, &local);
 *       return local;
 *   }
 *
 * Reads MMIO from the 0x04000000-0x05000000 range (SP DMEM/IMEM + RCP
 * register space) via func_80008FB0 (likely __osPiRawReadIo or similar).
 * Returns 0 if address is out of range.
 *
 * 2026-05-05: 800066B0 (which previously absorbed 800066D0 via same-file
 * merge in kernel_018.c) MOVED here from kernel_018.c so all 3 fragments
 * now live in this -O1 .c file. Layout-neutral move (kernel_017.c.o grows
 * +0x3C, kernel_018.c.o shrinks -0x3C; both .o's are in adjacent slots in
 * tenshoe.ld). Next pass: same-file merge 80006698 + 800066B0 into a
 * single u32 helper. Per
 * feedback_cross_file_fragment_unblock_via_move_then_merge.md. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80006698);

/* Continuation of func_80006698. See above wrap doc for the merged-body
 * decode (range check + jal func_80008FB0 + return). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800066B0);
