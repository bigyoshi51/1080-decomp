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

/* gl_func_00071144 = libultra osViSetSpecialFeatures (libreultra
 * io/visetspecial.c verbatim, IDO 7.1 -O1 whole-fn donor:
 * game_libs_o1_71144.c). LANDED 2026-08-22 via REPLACE_FUNC_BODY donor
 * splice, first-compile 110/110 FULL-word identical (blank
 * __osDisableInt/__osRestoreInt jals + 9x blank __osViNext hi/lo pairs
 * are the USO's load-time relocs; pins
 * gl_func_00000000_{disint711,rstint711,vinext711} = 0). The old
 * "register-allocation cap" reading is RETRACTED: the per-test stack
 * reloads/beql shape is plain IDO -O1, with `register u32 saveMask`
 * living in $a0. Body below is a placeholder for the splice. */
void gl_func_00071144(s32 arg0) {
    volatile int visetspecial_spliced = 0;
    if (arg0 != 0) {
        visetspecial_spliced = arg0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00071144_pad.s")

/* gl_func_00071304 = libultra osViSetEvent, 27/27 words exact.
 * The old 88% s0-allocation cap was an optimization-level mismatch:
 * register unsigned saveMask at IDO 7.1 -O1 reproduces the full prologue,
 * s0 return-value copy and three reloads of the SAME __osViNext pointer.
 * Real C is repeated in game_libs_o1_71304.c for the whole-function -O1
 * compile used by this mixed-opt unit. No assembly fallback or byte edits.
 * See docs/IDO_CODEGEN.md#visetevent-register-o1-71304. */
typedef struct {
    unsigned short state;
    unsigned short retraceCount;
    void *framebuffer;
    void *mode;
    unsigned int features;
    void *msgq;
    void *msg;
} ViContext71304;
extern ViContext71304 *gl_func_00000000_vinext711;
extern unsigned int gl_func_00000000_disint711(void);
extern void gl_func_00000000_rstint711(unsigned int);

void gl_func_00071304(void *mq, void *m, unsigned int retraceCount) {
    register unsigned int saveMask;
    saveMask = gl_func_00000000_disint711();
    gl_func_00000000_vinext711->msgq = mq;
    gl_func_00000000_vinext711->msg = m;
    gl_func_00000000_vinext711->retraceCount = retraceCount;
    gl_func_00000000_rstint711(saveMask);
}

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
