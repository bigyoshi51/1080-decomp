#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { int a, b; } Pair2;
typedef struct { float x, y, z; } Vec3;
#ifdef NON_MATCHING
#define GL_COUNT_2070 (*(int*)((char*)&D_00000000 + 0x2070))
#endif

/* game_libs_func_00070FCC = libultra fcos/__cosf (gu/cosf.c verbatim).
 * BOUNDARY FIX (2026-07-10): ONE function that splat had split into
 * FOUR fragments at interior branch targets / extra return points:
 * 70FCC (head; 2 leading pad nops -> covered by the -g3 padding of
 * game_libs_o1g3_70FA4.c, true entry 0x70FD4), 710F8 (the old
 * "caller-set $f2 double polynomial CAP" = the n-odd negated-result
 * tail), 71114 (the NaN check), 71130 (the old "prologue-stolen $at
 * CAP" = the return zero.f tail). Those two CAP wraps are RETIRED --
 * they were mid-function fragments, not functions.
 * WIRED via REPLACE_FUNC_BODY donor splice: real C lives in the IDO
 * 7.1 -O2 donor unit game_libs_o2_70FCC.c (90/90; rodata P/rpi/pihi/
 * pilo/zero baked at gl_data 0x24E0..0x2523). Body below is a
 * placeholder for the splice. */
float game_libs_func_00070FCC(float x) {
    volatile float ret = 0.0f;
    if (x != 0.0f) {
        ret = x;
    }
    return ret;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00070C44_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* gl_func_00071144: 8 independent flag-bit blocks over arg0, each toggling
 * a bit in field 0xC of a distinct global struct (lui+lw snapshot), plus a
 * trailing 16-bit OR into field 0x0. arg0 is re-read from its stack home
 * before each test (taken via &arg0). Residual = branch-likely vs plain
 * beqz+nop and s0/frame coloring (codegen-shape, register-allocation cap). */
void gl_func_00071144(s32 arg0) {
    s32 temp_s0;
    s32 *zero = (s32 *)0;
    s32 *ap = &arg0;

    temp_s0 = gl_ph_70FCC();
    if (*ap & 1) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) | 8;
    }
    if (*ap & 2) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) & ~8;
    }
    if (*ap & 4) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) | 4;
    }
    if (*ap & 8) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) & ~4;
    }
    if (*ap & 0x10) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) | 0x10;
    }
    if (*ap & 0x20) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) & ~0x10;
    }
    if (*ap & 0x40) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) | 0x10000;
        p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) & ~0x300;
    }
    if (*ap & 0x80) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) & 0xFFFEFFFF;
        p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) | (FW(FW(p, 0x8), 0x4) & 0x300);
    }
    {
        void *p = (void *)*zero;
        FW(p, 0x0) = (u16)(FW(p, 0x0) | 8);
    }
    gl_ph_70FCC(temp_s0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071144);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00071144_pad.s")

#ifdef NON_MATCHING
/* gl_func_00071304: 27-insn 2-call wrapper. Three distinct extern POINTERS
 * (D_71304_A/B/C), each loaded via lui+lw, then stored to via offset.
 * Applied unique-extern recipe per
 * docs/IDO_CODEGEN.md#feedback-ido-cse-bust-via-distinct-externs.
 *
 * NEAR-MISS (88%, SIZE-MISMATCH: mine 24 insns vs target 27). Logic is exact;
 * the body, store order (a0->D_A+0x10, a1->D_B+0x14, a2->D_C+2), arg-home/reload
 * and the three hoisted lui's all match. The ONLY divergence: the 1st call's
 * result `rv` (passed as the 2nd call's a0). TARGET parks rv in callee-saved
 * $s0 (`or s0,v0` / `or a0,s0`), paying +1 move + `sw/lw s0` + frame 0x18->0x28.
 * Natural -O2 C keeps rv in $v0 and does `move a0,v0` (no s0, frame 0x18) -- a
 * SHORTER, more-optimized body than the target. IDO only promotes a cross-call
 * value to a callee-saved REGISTER when it's used 2+ times after the call; rv is
 * used 0 times after the 2nd call, so no C structure induces the s0 round-trip.
 * NEGATIVE RESULTS (do not repeat, all 2026-05-30, standalone IDO 7.1 -O2):
 *   - `register int rv` / `register int rv asm("$16")`: hint ignored / IDO rejects
 *     gcc register-asm (feedback_ido_no_gcc_register_asm). Still $v0.
 *   - `return rv` (rv live across 2nd call): IDO SPILLS TO STACK (sw $2,28(sp) +
 *     lw), frame 0x20, NOT s0 -- and target doesn't return rv anyway.
 *   - -O1: also stack-spills rv (frame 0x20), not s0.
 *   - rv used twice (stored to D_A AND passed), 2-arg 2nd call, tail-return,
 *     1st-call-takes-(a0,a1,a2), rv-as-pointer-base: all keep rv in $v0 / frame
 *     0x18. The s0-for-single-use-cross-call-arg form is not -O2-reachable. NM. */
extern int *D_71304_A;
extern int *D_71304_B;
extern short *D_71304_C;
void gl_func_00071304(int a0, int a1, int a2) {
    int rv = gl_func_00000000();
    *(int*)((char*)D_71304_A + 0x10) = a0;
    *(int*)((char*)D_71304_B + 0x14) = a1;
    *(short*)((char*)D_71304_C + 2) = (short)a2;
    gl_func_00000000(rv);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071304);
#endif

/* game_libs_func_00071370: leading-nop FPU-control-reg wrapper
 * (cfc1/ctc1 pair, libreultra __osSetFpcCsr-style). Hand-written MIPS
 * asm; INCLUDE_ASM stays. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00071370);

/* gl_func_00071384 = libultra osPfsInitPak (io/pfsinitpak.c verbatim,
 * 1080 2.0-era OSPfs layout) -- the pfs-family head. The old NM body
 * (46.3%) had the exact call/field skeleton; only IDO 5.3 -O1 reproduces
 * the stack-resident locals + sequential sp-reload chains.
 * LANDED 2026-07-30 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_71384.c (165/165 raw-word
 * identical incl. reloc imms; no data relocs, 10 blank USO jals =
 * __osSiGetAccess, __osPfsGetStatus=gl_func_00071624, __osSiRelAccess,
 * __osPfsSelectBank, __osContRamRead x2, __osIdCheckSum=gl_func_000718C0,
 * __osCheckPackId=gl_func_00071D40, __osRepairPackId=gl_func_00071928,
 * osPfsChecker). Body below is a placeholder for the splice. */
int gl_func_00071384(void *queue, void *pfs, int channel) {
    volatile int ret = 0;
    if (channel != 0) {
        ret = channel;
    }
    return ret;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00071384_pad.s")

/* gl_func_00071624 = libultra __osPfsGetStatus (io/pfsgetstatus.c
 * verbatim, 2.0I layout) -- pfs sibling family of gl_func_00071384 =
 * osPfsInitPak (its PFS_GET_STATUS head jals this). The old NM body had
 * the exact semantics (status-flag decode 2/1/4) but 7.1 -O2 register
 * shapes; only IDO 5.3 -O1 reproduces the stack-resident locals.
 * LANDED 2026-07-30 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_71624.c (57/57 raw-word
 * identical incl. reloc imms; __osPfsPifRam = blank D_00000000, callees
 * = blank USO jals: __osPfsRequestOneChannel, __osSiRawStartDma x2,
 * osRecvMesg x2, __osPfsGetOneChannelData=gl_func_000717CC).
 * Body below is a placeholder for the splice. */
int gl_func_00071624(void *queue, int channel) {
    volatile int ret = 0;
    if (channel != 0) {
        ret = channel;
    }
    return ret;
}

/* gl_func_00071708: 48-insn record-stream emitter, 6-byte template
 * {1,3,0,0xFF,0xFF,0xFF} (swl/swr family; sibling of gl_func_0006D6F4).
 * Clears the flag byte at &D, sets &D+0x3C=1, zeroes a0 leading bytes via
 * the cursor, writes the template, lays a 0xFE terminator.
 * LANDED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in the
 * IDO 5.3 -O1 donor unit game_libs_ido53_71708.c (48/48 — 5.3 colors the
 * template struct-copy scratch $at; 7.1 uses $t1/$t0), spliced over this
 * -O2 stand-in. The old .s's 49th trailing word (lui $t6 at 0x717C8) is
 * gl_func_000717CC's stolen prologue -- since 2026-07-30 folded into the
 * gl_func_000717CC symbol itself (= __osPfsGetOneChannelData, true entry
 * 0x717C8). Body is a placeholder for the splice. */
extern int D_00000000;
void gl_func_00071708(int a0) {
    unsigned char tmpl[8];
    unsigned char *dst;
    int i;
    *(char *)&D_00000000 = 0;
    *(int *)((char *)&D_00000000 + 0x3C) = 1;
    dst = (unsigned char *)&D_00000000;
    tmpl[0] = 1;
    tmpl[1] = 3;
    tmpl[2] = 0;
    tmpl[3] = 0xFF;
    tmpl[4] = 0xFF;
    tmpl[5] = 0xFF;
    for (i = 0; i < a0; i++) {
        *dst = 0;
        dst++;
    }
    *(int *)dst = *(int *)tmpl;
    dst[4] = tmpl[4];
    dst[5] = tmpl[5];
    dst += 6;
    *dst = 0xFE;
}


/* gl_func_000717CC = libultra __osPfsGetOneChannelData (io/pfsgetstatus.c
 * verbatim, 2.0I layout) -- pfs sibling family; gl_func_00071624 =
 * __osPfsGetStatus jals this last. TRUE ENTRY 0x717C8: the compiled
 * fn's first insn (lui $t6,%hi(__osPfsPifRam)) was the old
 * _pad_pre_717CC stolen-prologue orphan inside gl_func_000717CC.s,
 * folded into the symbol 2026-07-30 (expected/ baseline refreshed).
 * LANDED via REPLACE_FUNC_BODY donor splice: real C lives in the IDO
 * 5.3 -O1 donor unit game_libs_ido53_717C8.c (39/39 raw-word identical
 * incl. the addend-0 __osPfsPifRam lui/addiu pair = blank D_00000000;
 * leaf, no jals). Body below is a placeholder for the splice. */
void gl_func_000717CC(int channel, void *data) {
    volatile int ret = 0;
    if (channel != 0) {
        ret = channel;
    }
}
