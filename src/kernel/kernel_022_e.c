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





/* func_80008E98 / _EA0 / _ED0 / _FB0: 86-insn alt-entry rmon packet
 * builder spanning 0x80008E98-0x80008FF0 (size 0x158). Splat split into 4
 * .s files because of the alt-entry symbol at 0x80008EA0 (called by
 * func_800071C0 via `jal 0x80008EA0`). The 0x80008E98 entry adds 2-insn
 * prelude (addiu $sp, -0xD8; sw $a0, 0xD8($sp)) before falling into the
 * shared body at 0x80008EA0; the 0x80008EA0 entry expects the caller to
 * have done the frame setup itself (caller `func_800071C0` does so).
 *
 * Body shape (rmon packet builder pattern, see docs/IDO_CODEGEN.md for
 * "rmon packet builder pattern" and CLAUDE.md notes):
 *   s0 = (RmonMsg*)msg                  // reloaded from sp+0xD8 spill
 *   pkt[0xC] = s0->[0xC]                // dword field copy
 *   pkt[0x36] = (short)0
 *   pkt[0x34] = s0->[0x4]               // byte field
 *   if (s0->[0x9] != 0) goto .L80008FC4  // skip-call path
 *   ...continues in func_80008ED0 with jal func_800077DC + branch logic
 *   ...continues in func_80008FB0 with sub-packet field copy from
 *      caller's stack frame at sp+0x2C
 *   ...ends at jr $ra at 0x80008FEC, frame teardown at 0x80008FE0-FE8
 *
 * Multi-tick decomp target (alt-entry + likely -O1 file-split).
 *
 * 2026-05-06 PROGRESS: 4-fragment merge applied. The previous 4 .s files
 * (E98/EA0/ED0/FB0) are now consolidated into one 0x15C func_80008E98.s
 * with three `alabel`s (EA0 at offset 0x8, ED0 at 0x38, FB0 at 0x118)
 * preserving cross-callers' jal targets. expected/.o regenerated.
 * The merge unblocks future C decode — splat-boundary issues no longer
 * apply, and the function can be NM-wrapped or matched normally now.
 *
 * Remaining work:
 *   1. Type a RmonMsg / RmonHdr struct pair
 *   2. File-split into kernel_NNN.c with -O1 OPT_FLAGS override + linker
 *      script slot insertion
 *   3. Write C body using rmon packet builder pattern from
 *      docs/IDO_CODEGEN.md
 *   4. Optional: PROLOGUE_STEALS for the EA0 alt-entry (caller
 *      `func_800071C0` jumps into +0x8 expecting frame already set up;
 *      C-only emit duplicates the prologue at the symbol address)
 *
 * Default INCLUDE_ASM build remains byte-exact. */
/* 4-fragment merge complete: func_80008E98 + func_80008EA0 (alt-entry at +8)
 * + func_80008ED0 + func_80008FB0 -> single 0x15C (87-insn) function.
 * func_80008EA0 is preserved as `alabel` inside the merged .s, keeping the
 * alt-entry callable from func_800071C0. ED0 and FB0 .s files deleted. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
extern void *func_800077DC(s32);
extern void func_800073F8();
/* rmon register-FETCH (inverse of func_80008FF4): read the live debug context's
 * 64-bit GPRs (lo word) into a 0xA4 header's 32-bit register array, copy the 3
 * special regs, send it (func_800073F8, len 0xA4). Returns -2 on bad sub-id /
 * missing context. Multi-entry symbol (alabels EA0/ED0/FB0 kept by #else).
 *
 * 2026-06-23 DEEP RECONSTRUCT (agent-d): logic is now byte-exact in shape —
 * prologue (s0=msg reloaded from 0xD8 spill, s1=loop counter, frame -0xD8),
 * both guards (msg[9]!=0 and ctx==NULL with their two separate `li -2`
 * returns placed in ROM order), and BOTH copy loops match the target
 * mnemonic-for-mnemonic, including the dead high-word load + redundant move
 * that come from reading each GPR as a 64-bit pair and narrowing to lo
 * (`hdr.reg[i] = (s32)*src;` where src is `s64 *`). Register hints
 * (`register s32 *msg`, `register s32 i`) reproduce the s0/s1 pinning.
 *
 * RESIDUAL = IDO frame SLOT-ORDERING (a documented regalloc cap, NOT a logic
 * bug): the target assigns the spill temporaries (ctx, loop pointer) the LOW
 * stack slots (sp+0x28 / sp+0x2C) and the address-taken `hdr` aggregate the
 * HIGH slots (sp+0x30+), so its tail recomputes `&hdr` per store and reloads
 * ctx per read. IDO 7.1 here does the opposite (hdr at sp+0x24, spills high),
 * caching ctx + &hdr and skipping the redundancy. Frame SIZE matches (0xD8);
 * only the within-frame slot assignment differs, shifting every sp-relative
 * immediate by 0xC. This is the same allocno-numbering class that pins the
 * matched-family sibling func_8000969C at 99.7% NM. Tried: decl-order
 * permutation (no effect on slot zone), volatile/struct-prefix pads (worse,
 * land in the wrong zone), ctx/msg register-qualifier sweep, hdr-write
 * reorder, -O2 (wrong, drops s0/s1). Permuter fuzzy-gain is a FALSE positive
 * on a slot-offset residual (objdiff normalizes sp-offsets — docs
 * TOOLING_DECOMP), and the 3 alt-entry alabels make a clean import fragile.
 * Honest NON_MATCHING. */
s32 func_80008E98(void *arg0) {
    register s32 *msg = arg0;
    register s32 i;
    s64 *src;
    void *ctx;
    struct {
        s32 w0;
        u8 tag;     /* +4 */
        u8 p5;
        s16 zero;   /* +6 */
        s32 w8;
        s32 id;     /* +C */
        s32 reg[0x22]; /* +0x10 .. +0x98 */
        s32 sp98;
        s32 sp9C;
        s32 spA0;
    } hdr;

    hdr.id = msg[3];
    hdr.tag = ((u8 *)msg)[4];
    hdr.zero = 0;
    if (((u8 *)msg)[9] == 0) {
        ctx = func_800077DC(msg[3]);
        if (ctx == NULL) {
            return -2;
        }
        src = (s64 *)((char *)ctx + 0x20);
        for (i = 1; i < 0x1A; i++) {
            hdr.reg[i] = (s32)*src;
            src++;
        }
        src = (s64 *)((char *)ctx + 0xE8);
        for (i = 0x1C; i < 0x22; i++) {
            hdr.reg[i] = (s32)*src;
            src++;
        }
        hdr.sp98 = FW(ctx, 0x120);
        hdr.sp9C = FW(ctx, 0x11C);
        hdr.spA0 = FW(ctx, 0x118);
        hdr.reg[0] = 0;
        func_800073F8(&hdr, 0xA4, 1);
        return 0;
    }
    return -2;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008E98);
#endif

/* func_80008FF4 absorbed the former func_80009000 + func_80009030
 * (splat mis-split: 8FF4 was prologue-only, 9000 and 9030 shared the
 * same frame with 8FF4). Now one 0x150 function. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
extern void *func_800077DC(s32);
extern void func_800073F8();
/* rmon GPR-save (inverse of func_80008E98 register-FETCH): copy the message's
 * general regs into the live debug context (func_800077DC) as sign-extended
 * 64-bit pairs, stamp the 3 special regs, send a 0x10 ack header
 * (func_800073F8 = __rmonSendHeader). Returns -2 if the message targets a
 * non-zero sub-id or the context is missing. Merged symbol (0x150);
 * func_80009000/9030 are link-time alt-entry labels resolved via undefined_syms,
 * preserved by the #else INCLUDE_ASM path.
 *
 * 2026-06-23 DEEP RECONSTRUCT (agent-d): 40.75% -> 83.55% NM. Logic is now
 * byte-exact in SHAPE — prologue (s0 = arg0 reloaded from sp+0x40 spill via
 * `register s32 *msg`, s1 = loop counter via `register s32 i`, frame -0x40),
 * both guards (msg[9]!=0 and ctx==NULL with the two `li -2` returns in ROM
 * order), and BOTH sign-extend-store loops match the target mnemonic-for-
 * mnemonic, INCLUDING the redundant `or $t5,$t2,$zero` lo-half move. The crack
 * was writing each pair as a single 64-bit store `*p = (s64)msg[i+4];` with
 * `p` a `s64 *` (NOT two s32 stores via a spilled `temp` local, which forced an
 * extra +0x8 frame slot and a temp spill/reload — that variant capped at
 * 40.75%/-0x48). The s64-store form drops the temp slot, restores frame size
 * -0x40, and produces the hi(`sra ...,31`) + lo(`or ...,0`) pair the target
 * uses.
 *
 * RESIDUAL = IDO frame SLOT-ORDERING (the documented allocno-numbering cap, NOT
 * a logic bug — same class as sibling func_80008E98): the target assigns the
 * spill temporaries (ctx, loop pointer) the LOW slots (sp+0x24 ptr / sp+0x28
 * ctx) and the address-taken `hdr` aggregate the HIGH slots (sp+0x2C+); IDO 7.1
 * here does the opposite (hdr at sp+0x24, spills high at sp+0x30/0x34). Frame
 * SIZE matches (-0x40); only the within-frame zone assignment differs, shifting
 * every remaining sp-relative immediate, plus the two jal targets (link-time
 * relocs, harmless) and the derived branch displacements. Tried: decl-order
 * permutation (hdr-first vs scalars-first: no effect on zone), early-return-
 * flat restructure (82.89%, worse — moved the guard block). Permuter conceded:
 * this is a multi-diff slot-offset residual, which objdiff normalizes
 * (false-positive class, see docs/TOOLING_DECOMP) and which the factory rules
 * say plateaus and doesn't fall. Honest NON_MATCHING; default INCLUDE_ASM build
 * stays byte-exact. */
s32 func_80008FF4(void *arg0) {
    register s32 *msg = arg0;
    register s32 i;
    void *ctx;
    s64 *p;
    struct { s32 w0; u8 tag; u8 p5; s16 zero; s32 w8; s32 id; } hdr;

    if (((u8 *)msg)[9] == 0) {
        ctx = func_800077DC(msg[3]);
        if (ctx == NULL) {
            return -2;
        }
        i = 1;
        p = (s64 *)((char *)ctx + 0x20);
        if (i < 0x1A) {
            do {
                *p = (s64)msg[i + 4];
                i += 1;
                p++;
            } while (i < 0x1A);
        }
        i = 0x1C;
        p = (s64 *)((char *)ctx + 0xE8);
        if (i < 0x22) {
            do {
                *p = (s64)msg[i + 4];
                i += 1;
                p++;
            } while (i < 0x22);
        }
        FW(ctx, 0x120) = msg[0x26];
        FW(ctx, 0x11C) = msg[0x27];
        FW(ctx, 0x118) = msg[0x28];
        hdr.id = msg[3];
        hdr.zero = 0;
        hdr.tag = ((u8 *)msg)[4];
        func_800073F8(&hdr, 0x10, 1);
        return 0;
    }
    return -2;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008FF4);
#endif
