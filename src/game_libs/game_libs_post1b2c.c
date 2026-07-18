#include "common.h"
extern int D_00000000;
extern int gl_data_00000000;
extern int gl_func_00062F64();
extern int gl_data_67470_addr;
extern int gl_data_6C9F4_devCfg;
extern char gl_data_BE14_b;
extern char gl_data_BE14_c;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { int a, b; } Pair2;
typedef struct { float x, y, z; } Vec3;
/* osThread subset used by gl_func_0006F534 (osSetThreadPri twin) */
typedef struct { int field0; int pri; int queue; int pad0C; unsigned short state; } Thread_0006F534;

/* game_libs_post1b2 TAIL (post1b2c): functions from 0x6C400 onward, carved
 * after gl_func_0006C384 was moved to its own -O1 unit
 * (game_libs_ido53_6C384.c). Same -O2 settings as the post1b2 head. */

/* game_libs_func_0006C400 = libultra osWritebackDCache (os/
 * writebackdcache.s) -- HANDWRITTEN (cache 0x19 HIT_WRITEBACK_D loop,
 * 16-byte lines, with the size>=0x2000 guard branching into the ALL
 * variant below, leaving li t3,0x2000 live across the boundary).
 * IDO C cannot emit the cache op; permanent INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C400);

/* game_libs_func_0006C454 = libultra osWritebackDCacheAll (os/
 * writebackdcacheall.s) -- HANDWRITTEN (cache 0x1 INDEX_WRITEBACK_
 * INVALIDATE_D over the whole dcache; reads t3=0x2000 set by the
 * PREDECESSOR osWritebackDCache's guard -- cross-fn register flow,
 * normal for the handwritten pair). Permanent INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C454);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006C384_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern int gl_vec_src0;
extern int gl_vec_src1;
extern int gl_vec_src2;
extern int gl_vec_src3;
typedef char *(*GP_0006C484)();
void gl_func_0006C484(void) {
    u32 sp34;
    u32 sp30;
    u32 sp24;
    u32 sp20;
    u32 temp_ret;
    u32 temp_ret_2;
    u32 temp_t1;
    u32 temp_t9;
    int *src0 = &gl_vec_src0;
    int *src1 = &gl_vec_src1;
    int *src2 = &gl_vec_src2;
    int *src3 = &gl_vec_src3;

    sp30 = 0;
    *(int*)0 = 1;
    gl_func_00062F64(gl_func_00062F64() | 0x20000000);
    gl_func_00062F64(0x01000800U);
    if (gl_func_00062F64(0x1FC007FCU, &sp34) != 0) {
        do {

        } while (gl_func_00062F64(0x1FC007FCU, &sp34) != 0);
    }
    if (gl_func_00062F64(0x1FC007FCU, (u32 *) (sp34 | 8)) != 0) {
        do {

        } while (gl_func_00062F64(0x1FC007FCU, (u32 *) (sp34 | 8)) != 0);
    }
    *(Quad4 *)0x80000000 = *(Quad4 *)src0;
    *(Quad4 *)0x80000080 = *(Quad4 *)src1;
    *(Quad4 *)0x80000100 = *(Quad4 *)src2;
    *(Quad4 *)0x80000180 = *(Quad4 *)src3;
    gl_func_00062F64(0x80000000U, (u32 *)0x190);
    gl_func_00062F64(0x80000000U, (u32 *)0x190);
    gl_func_00062F64();
    gl_func_00062F64(4U, &sp30);
    temp_t9 = sp30 & ~0xF;
    sp30 = temp_t9;
    if (temp_t9 != 0) {
        *(int*)0 = 0U;
        *(int *)4 = temp_t9;
    }
    temp_ret = gl_func_00062F64(*(int*)0, (u32 *) *(int *)4, 0, 3);
    sp20 = temp_ret;
    sp24 = (u32) (u64) temp_ret;
    temp_ret_2 = gl_func_00062F64(sp20, (u32 *) sp24, 0, 4);
    temp_t1 = *(int*)0;
    *(int*)0 = temp_ret_2;
    *(int *)4 = (u32) (u64) temp_ret_2;
    if (temp_t1 == 0) {
        gl_func_00062F64(0U, (u32 *)0x40);
    }
    if (*(int*)0 == 0) {
        *(int*)0 = 0x02F5B2D2U;
        return;
    }
    if (*(int*)0 == 2) {
        *(int*)0 = 0x02E6025CU;
        return;
    }
    *(int*)0 = 0x02E6D354U;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C484);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C710);

/* 64-bit libgcc helper family. LANDED 2026-06-21 as byte-identical TWIN-PORTs
 * of the matched kernel_056.c funcs (0 relocs, self-contained). Real C lives in
 * the donor unit game_libs_mips3_6C740.c (-O2 -mips3 so IDO inlines the
 * d-arithmetic); spliced in via REPLACE_FUNC_BODY because this TU is -mips2. */
u64 game_libs_func_0006C740(u64 a, u64 b) { return a % b; }   /* __ull_rem  <- func_80002A3C */

u64 game_libs_func_0006C77C(u64 a, u64 b) { return a / b; }   /* __ull_div  <- func_80002A78 */

u64 game_libs_func_0006C7B8(u64 a, u64 b) { return a << b; }  /* __ll_lshift <- func_80002AB4 */

/* __ull_rem (duplicate) <- kernel func_80002AE0. TWIN-PORT, donor game_libs_mips3_6C740.c. */
u64 game_libs_func_0006C7E4(u64 a, u64 b) { return a % b; }

s64 game_libs_func_0006C820(s64 a, s64 b) { return a / b; }   /* __ll_div   <- func_80002B1C */

s64 game_libs_func_0006C87C(s64 a, s64 b) { return a * b; }   /* __ll_mul   <- func_80002B78 */

/* 64-bit-by-short divmod. LANDED 2026-06-21 as a byte-identical TWIN-PORT of
 * kernel func_80002BA8 (kernel_056): same 0x60-byte ddivu body, no relocs.
 * Needs -O1 -mips3, which this -O2/-mips2 TU can't use, so the -O1 -mips3
 * donor (game_libs_o1_6C8AC.c) is spliced in via REPLACE_FUNC_BODY. */
void game_libs_func_0006C8AC(u64 *quot, u64 *rem, u64 val, u16 d) {
    *quot = val / d;
    *rem = val % d;
}

/* gl_func_0006C90C: Euclidean (floored) signed 64-bit modulo. LANDED 2026-06-21
 * as a byte-identical TWIN-PORT of the matched kernel func_80002C08 (kernel_056):
 * identical 0x9c-byte ddiv body, no relocs. Needs -O1 -mips3 (keeps arg-homing,
 * 39 insns; the -O2 standalone form leaf-optimizes to 33 insns), which this
 * -O2/-mips2 TU can't use, so the -O1 -mips3 donor (game_libs_o1_6C8AC.c) is
 * spliced in via REPLACE_FUNC_BODY. The earlier "4 MIPS3 sub-function bundle /
 * 57 words" decode was a splat-oversize misread — the function is a single
 * 39-insn floored-mod. */
long long gl_func_0006C90C(long long a, long long b) {
    long long r = a % b;
    if ((r < 0 && b > 0) || (r > 0 && b < 0)) r += b;
    return r;
}


/* __ll_rshift <- kernel func_80002CA4. TWIN-PORT, donor game_libs_mips3_6C740.c. */
s64 game_libs_func_0006C9A8(s64 a, s64 b) { return a >> b; }

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C9D4);

/* game_libs_func_0006C9E4: 3-insn `mfc0 v0, $12; jr ra; nop` Status-register
 * read. CP0 access (mfc0) is MIPS3 runtime — IDO C can't emit CP0 ops from
 * standard C. CAP class per reference_1080_mips3_runtime_helpers. Default
 * INCLUDE_ASM remains byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C9E4);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006C90C_pad.s")

/* gl_func_0006C9F4 = libultra __osPiRawStartDma. LANDED 2026-06-21 as a
 * byte-identical TWIN-PORT of matched kernel func_80004650 (kernel_042_b).
 * Body is IDO 5.3 -O1 (this TU is -O2), so the real C lives in the donor unit
 * game_libs_ido53_6C9F4.c and is spliced in via REPLACE_FUNC_BODY. The PI
 * register block is direct-mapped (literal lui 0xA460); the cart-base helper
 * + DMA cfg-base global collapse to the address-0 USO placeholders
 * gl_func_00000000 / D_00000000. */
extern int gl_func_00000000();
int gl_func_0006C9F4(int direction, unsigned int devAddr, int dramAddr, unsigned int size) {
    register unsigned int status;
    while ((status = *(volatile unsigned int*)0xA4600010) & 3) ;
    *(volatile unsigned int*)0xA4600000 = gl_func_00000000(dramAddr);
    *(volatile unsigned int*)0xA4600004 = (D_00000000 | devAddr) & 0x1FFFFFFF;
    switch (direction) {
        case 0: *(volatile unsigned int*)0xA460000C = size - 1; break;
        case 1: *(volatile unsigned int*)0xA4600008 = size - 1; break;
        default: return -1;
    }
    return 0;
}

/* gl_func_0006CAD4 = libultra __osSiRawStartDma (sirawdma.c verbatim):
 * SI busy guard, OS_WRITE pre-writeback, SI_DRAM_ADDR_REG =
 * osVirtualToPhysical(dramAddr), dir-selected SI_PIF_ADDR_RD64B/WR64B =
 * 0x1FC007C0 (PIF RAM), OS_READ post-invalidate. Retires the 2026-05-19
 * "factory/prep" decode: the two dir-guarded calls are osWritebackDCache /
 * osInvalDCache, and the pak block neighbors (contramread/contramwrite
 * family) are its callers.
 * WIRED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in the
 * IDO -O1 donor unit game_libs_o1_6CAD4.c (43/43 at both 7.1 and 5.3 -O1),
 * spliced over this -O2 stand-in. The jr-ra delay nop was merged from the
 * _pad.s sidecar into gl_func_0006CAD4.s (0xa8 -> 0xac; sidecar deleted).
 * Body below is a placeholder for the splice. */
int gl_func_0006CAD4(int direction, void *dramAddr) {
    volatile int ret = 0;
    if (direction == 0) {
        ret = -1;
    }
    return ret;
}

/* gl_func_0006CB84 = libultra __osSpRawStartDma (sprawdma.c verbatim):
 * SP busy guard, SP_MEM_ADDR_REG = devAddr, SP_DRAM_ADDR_REG =
 * osVirtualToPhysical(dramAddr), dir-selected SP_WR_LEN/RD_LEN = size - 1.
 * WIRED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in the
 * IDO -O1 donor unit game_libs_o1_6CB84.c (35/35 at both 7.1 and 5.3 -O1),
 * spliced over this -O2 stand-in. The jr-ra delay nop was merged from the
 * _pad.s sidecar into gl_func_0006CB84.s (0x88 -> 0x8c; sidecar deleted).
 * Body below is a placeholder for the splice. */
int gl_func_0006CB84(int direction, unsigned int devAddr, void *dramAddr, unsigned int size) {
    volatile int ret = 0;
    if (direction == 0) {
        ret = (int)(size - 1);
    }
    return ret;
}

#ifdef NON_MATCHING
/* gl_func_0006CC14: 18-insn 2-call helper.
 *   r = gl_func(a0);          (first call; a0 homed to sp+0x20 in delay slot)
 *   *a0 = D[0];               (copy global into *a0; a0 reloaded -> t7)
 *   D2 = a0;                  (store original a0 to second global; a0 reloaded
 *                              again -> t8, in the second jal's delay slot)
 *   gl_func(r);               (second call; r reloaded from its spill slot)
 *   return 0;
 *
 * Two levers got this from 65% -> 93.56%:
 *   1. ORDER: place 'D2 = a0;' BEFORE the second gl_func() call so IDO
 *      schedules the symbol store ('sw t8,0(at)') into the second jal's
 *      delay slot (target does this; original ordering parked it in the
 *      jr-ra delay slot at function end).
 *   2. CSE-BREAK: read a0 via '*(int**)&a0' for the D2 store. The plain
 *      'a0' folds both uses into one reload (a single a1); re-deref forces
 *      the two independent param-home reloads the target uses (t7 then t8).
 *   3. SPILL-SLOT CROSS (2026-07 crossing-hunt): declaring 'volatile int spill;'
 *      UNINITIALIZED and assigning it AFTER the first call earns the spill the
 *      first local slot sp+0x1C (matching target); the earlier initialized form
 *      ('volatile int spill = (int)r;') colored it at sp+0x18. With this the C
 *      BODY is byte-exact vs target (all 18 real insns + jr-ra delay nop match).
 *
 * WHY STILL NM (not promoted to plain C): target has a trailing pad word after
 * the jr-ra delay nop, supplied by gl_func_0006CC14_pad.s. The .s (INCLUDE_ASM)
 * is 18 words ending in jr ra (no delay nop); pad.s 8-byte-aligns and fills BOTH
 * the delay nop AND the pad word -> exact. A C body already emits its own delay
 * nop, so C(19w)+pad.s(8-aligned) overshoots by one word (next fn +4) and C(19w)
 * with NO pad undershoots by one word. Placing exactly one trailing zero word
 * needs a Makefile all-zero SUFFIX_BYTES entry (sanctioned padding) replacing the
 * pad.s pragma -- outside this agent's file scope. LEAD for the Makefile owner:
 *   build/src/game_libs/game_libs_post1b2c.c.o: SUFFIX_BYTES ... gl_func_0006CC14=0x00000000
 *   + drop the gl_func_0006CC14_pad.s GLOBAL_ASM here, then promote to plain C. */
extern int D_cc14_alias2;
int gl_func_0006CC14(int *a0) {
    volatile int spill;
    int *r = (int*)gl_func_00000000(a0);
    spill = (int)r;
    *a0 = *(int*)&D_00000000;
    *(int**)&D_cc14_alias2 = *(int**)&a0;
    gl_func_00000000((int*)spill);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CC14);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006CC14_pad.s")

/* gl_func_0006CC64 = libultra osViBlack (viblack.c verbatim): saveMask =
 * __osDisableInt(); __osViNext->state |= / &= ~VI_STATE_BLACK(0x20);
 * __osRestoreInt(saveMask). Retires the old "rv in s0 / frame -0x28
 * regalloc cap": `register u32 saveMask` across the call at -O1 IS the
 * s0 coloring.
 * WIRED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in the
 * IDO -O1 donor unit game_libs_o1_6CC64.c (28/28 at both 7.1 and 5.3 -O1),
 * spliced over this -O2 stand-in. Body below is a placeholder for the
 * splice. */
void gl_func_0006CC64(unsigned char active) {
    volatile unsigned char a = active;
    (void)a;
}

/* gl_func_0006CCD4 = libultra __osPiRawReadIo. LANDED 2026-06-21 as a
 * byte-identical TWIN-PORT of matched kernel func_80004AC0 (kernel_001). The
 * prior "delay-slot-fill cap (80.65%)" was an -O2 artifact: this is an -O1
 * libultra helper. At IDO 5.3 -O1 the beqz delay slot is filled by the
 * success-path lw exactly as the ROM does. Real C lives in the donor unit
 * game_libs_ido53_6CCD4.c (this TU is -O2), spliced in via REPLACE_FUNC_BODY.
 * The PI-busy probe collapses to the address-0 placeholder gl_func_00000000;
 * the uncached cart read is a KSEG1 literal (devAddr | 0xA0000000). */
int gl_func_0006CCD4(int devAddr, int *data) {
    if (gl_func_00000000() != 0) {
        return -1;
    }
    *data = *(volatile int *)(0xA0000000 | devAddr);
    return 0;
}

extern int gl_func_00000000();
int gl_func_0006CD24() {
    return gl_func_00000000(0x400);
}

#ifdef NON_MATCHING
/* gl_func_0006CD44: 26-insn factory + 3 global-data stores + chain (0x68, frame 0x28).
 *
 * Decoded structure (raw-word disasm):
 *   result = gl_func(self);                          // 1st call (arg untouched)
 *   D_A[2] = self;                                   // store self into global table
 *   *D_B = 1;                                        // set flag (short)
 *   D_C[3] = ((int**)D_C)[2][1];                     // chain: D_C[3] = (D_C[2] as int*)[1]
 *   gl_func(result);                                 // 2nd call w/ 1st-call result
 *
 * The 3 global-data accesses (D_A/D_B/D_C) interleave with the s0 spill and
 * arg-reload — IDO -O2 fills the post-1st-call delay slot with the early s0
 * spill (afb00018) and amortizes lui+lw setup across the body. No FP.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-18 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
extern int *D_A;
extern short *D_B;
extern int *D_C;
void gl_func_0006CD44(int *self) {
    int *result = (int*)gl_func_00000000(self);
    D_A[2] = (int)self;
    *D_B = 1;
    D_C[3] = ((int**)D_C)[2][1];
    gl_func_00000000(result);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CD44);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006CD44_pad.s")

/* gl_func_0006CDB4 / gl_func_0006CF54: word-identical 104-insn twins —
 * Nintendo-modified __osContRamRead-family mempack transaction verifiers
 * over an OSPfs* (queue +4, channel +8): guard word_table[channel] else
 * PFS_ERR_INVALID(5), __osSiGetAccess, __osContLastCmd=3, OS_WRITE DMA of
 * &bank[channel*64], recv, OS_READ DMA, recv, ptr walk, 40-byte format
 * readback, CHNL_ERR, __osContDataCrc(global) vs datacrc else
 * PFS_ERR_CONTRFAIL(4), __osSiRelAccess.
 * WIRED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in the
 * IDO 5.3 -O1 donor unit game_libs_ido53_6CDB4.c (104/104 each; one TU
 * defines both twins, 6C740 precedent), spliced over these -O2 stand-ins.
 * Bodies below are placeholders for the splice. */
int gl_func_0006CDB4(int *pfs) {
    volatile int ret = 0;
    if (pfs[2] == 0) {
        ret = 5;
    }
    return ret;
}

int gl_func_0006CF54(int *pfs) {
    volatile int ret = 0;
    if (pfs[2] == 0) {
        ret = 5;
    }
    return ret;
}

/* gl_func_0006D0F4: 95-insn 40-byte-record builder (count, u16 x, src,
 * out). Zeroes out[0..14], out[15]=1, builds record {0xFF,35,1,3,
 * h4=fn(x)|x<<5, data[32] from src, b38=0xFF}, zero-fills count bytes at
 * the cursor, struct-copies the record (swl/swr x3 chunk loop, $at
 * scratch), cursor += 40, 0xFE terminator.
 * LANDED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_6D0F4.c (95/95 — FOR-loop
 * shape for both byte loops, see donor header). Body below is a
 * placeholder for the splice (its bytes are replaced by the donor). */
void gl_func_0006D0F4(int count, unsigned short x, unsigned char *src, int *out) {
    volatile int i;
    for (i = 0; i < count; i++) {
        out[0] = *src + x;
    }
}

/* gl_func_0006D270 = libultra osMotorInit (motor.c verbatim): OSPfs init
 * (queue/channel/status=0/activebank=128), 32-byte 0xFE probe write
 * (retry on 2) + read (2 -> PFS_ERR_CONTRFAIL) to pak address 1024,
 * temp[31]==0xFE -> PFS_ERR_DEVICE (a mempack holds the write), same
 * probe with 0x80, then one-time _MakeMotorData(channel, 1536, buf,
 * &_MotorData[channel]) pair guarded by __osMotorinitialized[channel].
 * The baked `jal 0x81760` = _MakeMotorData (links via gl_ref_00081760).
 * WIRED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in the
 * IDO -O1 donor unit game_libs_o1_6D270.c (183/183 at both 7.1 and 5.3
 * -O1), spliced over this -O2 stand-in. The 2-word inter-function
 * alignment pad at 0x6D54C stays in its _pad.s sidecar below. Body below
 * is a placeholder for the splice. */
int gl_func_0006D270(void *mq, void *pfs, int channel) {
    volatile int ret = 0;
    if (channel == 0) {
        ret = 11;
    }
    return ret;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006D270_pad.s")

/* gl_func_0006D554: libultra osPfsIsPlug (pfsisplug.c; 1080 deltas:
 * MAXCONTROLLERS=4, compact 4-byte OSContStatus). TU siblings 6D6F4 =
 * __osPfsRequestData and 6D7CC = __osPfsGetInitData below.
 * WIRED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in the
 * IDO 7.1 -O1 donor unit game_libs_o1_6D554.c (104/104), spliced over this
 * -O2 stand-in. Body below is a placeholder for the splice. */
int gl_func_0006D554(void *queue, unsigned char *pattern) {
    volatile int ret = 0;
    *pattern = 0;
    return ret;
}

/* gl_func_0006D6F4: libultra __osPfsRequestData (pfsisplug.c TU, sibling
 * of 6D554 = osPfsIsPlug above and 6D7CC = __osPfsGetInitData below).
 * Retires the old "record-stream emit helper" decode: the template is
 * __OSContRequesFormat {FF,1,3,cmd,FF,FF,FF,FF}, the "D+0 blob" is really
 * three distinct blanked globals (__osContLastCmd / __osPfsPifRam /
 * __osMaxControllers), and the "spill cap" was just the 5.3 flavor.
 * WIRED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in the
 * IDO 5.3 -O1 donor unit game_libs_ido53_6D6F4.c (52/52), spliced over
 * this -O2 stand-in. Body below is a placeholder for the splice. */
void gl_func_0006D6F4(unsigned char cmd) {
    volatile unsigned char c = cmd;
    (void)c;
}

/* gl_func_0006D7CC: libultra __osPfsGetInitData (pfsisplug.c TU; 1080
 * compact 4-byte OSContStatus). BOUNDARY FIX: the 2-word orphan
 * game_libs_func_0006D7C4 (lui/lbu __osMaxControllers) was this
 * function's first load scheduled before the prologue by IDO 5.3; its
 * INCLUDE_ASM was removed and the spliced symbol covers 0x6D7C4..0x6D890.
 * WIRED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in the
 * IDO 5.3 -O1 donor unit game_libs_ido53_6D7CC.c (52/52), spliced over
 * this -O2 stand-in. Body below is a placeholder for the splice. */
void gl_func_0006D7CC(unsigned char *pattern, void *data) {
    *pattern = 0;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006D894);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006D94C);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006D7CC_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006D964: 67-insn command-record builder + dual-dispatch helper.
 * Size 0x10C, frame 0x28, saves s0/s1.
 *
 * Builds a 20-byte command record at *a0 then dispatches via one of two
 * jal pairs based on the kind flag `a1`. Returns -1 if the global head
 * pointer at D+0 is NULL.
 *
 * Decoded structure (raw-word disasm):
 *   int build_and_send(uint8_t *out_record,  // a0 — record buffer (≥0x14 bytes)
 *                      int kind_flag,         // a1 (1 = path A, else path B)
 *                      int type_alt,          // a2 (0 = type 0xB, else 0xC)
 *                      int arg3,              // a3
 *                      int arg5,              // sp+0x38
 *                      int arg6,              // sp+0x3C
 *                      int arg4)              // sp+0x40 — order via stack-arg slots
 *   {
 *       void *head = *(void**)&D_00000000;
 *       if (head == NULL) return -1;
 *
 *       // Build 0x14-byte command record:
 *       *(uint16_t*)(out_record + 0x00) = (type_alt == 0) ? 0xB : 0xC;
 *       *(uint8_t *)(out_record + 0x02) = (uint8_t)kind_flag;
 *       *(uint32_t*)(out_record + 0x04) = arg4;       // sp+0x40
 *       *(uint32_t*)(out_record + 0x08) = arg5;       // sp+0x38
 *       *(uint32_t*)(out_record + 0x0C) = arg3;       // a3
 *       *(uint32_t*)(out_record + 0x10) = arg6;       // sp+0x3C
 *       *(uint32_t*)(out_record + 0x14) = 0;
 *
 *       // Dispatch
 *       int s1;
 *       if (kind_flag == 1) {
 *           s1 = func_a();           // jal #1
 *       } else {
 *           s1 = func_b();           // jal #1' (different target)
 *       }
 *       return func_send(s1, out_record, 0);   // jal #2 — common dispatch
 *   }
 *
 * Notes:
 *  - The two jal-pair branches share identical structure (`jal X; s1 = v0;
 *    jal send(s1, out_record, 0)`). Only the first jal target differs.
 *    IDO appears to have emitted them as separate code paths rather than
 *    a conditional callee lookup — probably the original C had two
 *    explicit if-branches, each with its own builder function call.
 *  - Type byte 0xB or 0xC suggests a command-ID enum where 0xB = some
 *    "write" command and 0xC = a related command variant.
 *  - 20-byte record matches typical OS-level message-queue entry size
 *    (osCreateMesgQueue size and friends).
 *  - Returns -1 on NULL head (early-out), else result of send-jal.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
extern int gl_func_00000000();
extern int gl_func_0006D964_b();   /* distinct field-0 placeholder for the a1!=1 arm */
extern int D_00000000;
// Early-out -1 if *(&D)==0. Fill a 20-byte record at obj: halfword type 0xC if
// a2!=0 else 0xB; byte +2 = a1; +4=arg7, +8=arg5, +0xC=a3, +0x10=arg6, +0x14=0.
// Then a kind-gated builder pair (a1==1 vs not call different builders), each
// `s1 = build(); s0 = send(s1, obj, 0)`; return s0. Reloc-blind cbs + &D.
int gl_func_0006D964(char *obj, int a1, int a2, int a3, int arg5, int arg6, int arg7) {
    int s0, s1;
    if (*(int *)&D_00000000 == 0) {
        return -1;
    }
    if (a2 != 0) {
        *(short *)(obj + 0x0) = 12;
    } else {
        *(short *)(obj + 0x0) = 11;
    }
    *(char *)(obj + 0x2) = (char)a1;
    *(int *)(obj + 0x4) = arg7;
    *(int *)(obj + 0x8) = arg5;
    *(int *)(obj + 0xC) = a3;
    *(int *)(obj + 0x10) = arg6;
    *(int *)(obj + 0x14) = 0;
    if (a1 == 1) {
        s1 = gl_func_00000000();
        s0 = gl_func_00000000(s1, obj, 0);
    } else {
        s1 = gl_func_0006D964_b();
        s0 = gl_func_0006D964_b(s1, obj, 0);
    }
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D964);
#endif

/* gl_func_0006DA74: 98-insn osCreatePiManager (libultra pimgr.c —
 * identified 2026-07-09 against references/libreultra/src/io/pimgr.c;
 * field-for-field: creates the cmd queue, the pi event queue
 * (piEventQueue=0x43E90/piEventBuf=0x43EA8), the access queue if needed,
 * osSetEventMesg(OS_EVENT_PI=8, q, 0x22222222), thread-priority bracket,
 * __osPiDevMgr{active,thread=piThread@0x42CE0,cmdQueue,evtQueue,acsQueue,
 * dma,edma}, osCreateThread(piThread, 0, __osDevMgrMain, &__osPiDevMgr,
 * piThreadStack@0x42E90+0x1000, pri), osStartThread, __osRestoreInt,
 * priority restore.
 * LANDED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the -O1 donor unit game_libs_o1_6DA74.c (98/98 at plain 7.1 -O1 — the
 * TU-defined DevMgr produces the shared-lui $at store clusters, see donor
 * header). Body below is a placeholder for the splice (its bytes are
 * replaced by the donor). */
void gl_func_0006DA74(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    volatile int keep = arg0 + arg1 + arg2 + arg3;
    while (keep) {
        keep = 0;
    }
}

/* game_libs_func_0006DBFC (0x10 orphan, no jr ra) was 2 alignment nops
 * (osCreatePiManager donor-TU .text pad, kept as the pad sidecar below) +
 * the HOISTED HEAD of gl_func_0006DC0C = osCartRomInit — absorbed into the
 * donor splice below (true entry 0x6DC04, spliced symbol covers
 * 0x6DC04..0x6DCF8). */
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006DA74_pad.s")

#if 0
/* SUPERSEDED DECODE (2026-07-18): the "caller-set $t6" reading below was
 * wrong — $t6 is __CartRomHandle.baseAddress loaded by the stolen prologue
 * at 0x6DC04 (splat orphan game_libs_func_0006DBFC). Real identity:
 * libultra osCartRomInit. See the donor unit game_libs_ido53_6DC0C.c. */
/* gl_func_0006DC0C: 59-insn save-data / SRAM init helper (size 0xEC, frame 0x20).
 *
 * Sets up the hardware-mapped 0xB000_0000 region (N64 PI bus DOM2 = cartridge
 * SRAM / EEPROM / save-data mapping) and unpacks a status word from a
 * hardware/save-header call into byte fields in the D segment.
 *
 * PASS-3 2026-06-27: 67.6% -> 73.6% objdiff fuzzy via two register-independent
 * fixes (game_libs is baked-reloc, cannot byte-LAND):
 *   - WIDTH/SIGN: the save-header word `v` is UNSIGNED. The unpack shifts
 *     `(v>>8)&0xFF`, `(v>>16)&0xF`, `(v>>20)&0xF` emit logical `srl` (+ andi)
 *     in the target; a signed `int v` wrongly emitted arithmetic `sra` and
 *     dropped the high-byte mask. Changing to `unsigned int v` matches all
 *     three shift/mask insns. (+4.2pp)
 *   - CONTROL-FLOW / RETURN-SLOT INIT: `v = 0;` is zeroed unconditionally
 *     before the early-return guard (target stores `sw zero,0x1C(sp)` in the
 *     bne delay slot). (+1.8pp)
 *
 * Residual (~26%) is codegen-SHAPE only and objdiff-NEUTRAL to C edits:
 *   - the self-copy `*(int*)g = *(int*)g` is dead-store-eliminated by IDO -O2
 *     because the very next stmt overwrites D+0 (target keeps the lw/sw block);
 *     tmp-local and `*(volatile int*)g` variants both still elide it.
 *   - final return value v0 is kept in a reg (`move a0,v0`) instead of the
 *     target's stack spill/reload (`sw v0,24(sp)` / `lw a0,24(sp)`), which
 *     also drives the frame-size delta (0x28 vs target 0x20).
 *   These are register-coloring/spill-shape residuals, not logic bugs.
 *
 * Notes:
 *  - 0xB000_0000 is the N64 PI bus DOM2 (cart/SRAM) virtual address. Writes
 *    to *(D+0xC) here are storing the mapped pointer as a global for future
 *    code to access SRAM via *D+0xC dereference.
 *  - $t6 caller-set: the function expects caller to pass current value of
 *    `*(D+0xC)` in $t6 (the saved pointer). Fits caller-set-int-reg cap class
 *    (feedback_caller_set_int_reg_cap_1080_game_libs.md).
 *  - The unpacked byte fields look like a date+time stamp (or version
 *    YYYY-MM-DD HH:MM packed into 32 bits) parsed from save-header.
 */
extern int gl_func_00000000();
extern int D_00000000;
// t6 (caller-set, = current *(D+0xC)) gated on the 0xB0000000 PI-bus DOM2
// address: if already mapped, return the default pointer; else clear the
// flag byte (D+4), store 0xB0000000 to D+0xC, read a 32-bit save-header word
// (cb(0,&v)) and unpack it into the byte fields D+5/8/6/7 (date/time stamp),
// zero D+9/D+0x10, cb(D+0x14, 96), an alloc/create cb, the self-copy +
// pointer-restore globals, and the finalize cb. Reloc-blind &D + caller-set t6.
void *gl_func_0006DC0C(void *t6) {
    char *g = (char *)&D_00000000;
    unsigned int v;
    void *saved;
    v = 0;
    if (t6 == (void *)0xB0000000) {
        return (void *)&D_00000000;
    }
    *(char *)(g + 0x4) = 0;
    *(int *)(g + 0xC) = (int)0xB0000000;
    gl_func_00000000(0, &v);
    *(char *)(g + 0x5) = v & 0xFF;
    *(char *)(g + 0x8) = (v >> 0x8) & 0xFF;
    *(char *)(g + 0x6) = (v >> 0x10) & 0xF;
    *(char *)(g + 0x7) = (v >> 0x14) & 0xF;
    *(char *)(g + 0x9) = 0;
    *(int *)(g + 0x10) = 0;
    gl_func_00000000(g + 0x14, 96);
    saved = (void *)gl_func_00000000();
    *(int *)g = *(int *)g;
    *(int *)g = (int)&D_00000000;
    gl_func_00000000(saved);
    return (void *)&D_00000000;
}
#endif

/* gl_func_0006DC0C = libultra osCartRomInit (cartrominit.c verbatim):
 * gate on __CartRomHandle.baseAddress == PHYS_TO_K1(PI_DOM1_ADDR2)
 * (0xB0000000), else init the cart-ROM PI handle (type=DEVICE_TYPE_CART,
 * latency/pulse/pageSize/relDuration unpacked from the BSD DOM1 config
 * word read via osPiRawReadIo, domain=PI_DOMAIN1), bzero the transfer
 * info, and link into __osPiTable under disabled interrupts. Needs IDO
 * 5.3 -O1 (hoisted pre-prologue gate load + shared-$at
 * pageSize/relDuration sb pair), so the real C lives in the donor unit
 * game_libs_ido53_6DC0C.c (61/61 exact incl. the absorbed head words of
 * game_libs_func_0006DBFC). Body below is a placeholder for the
 * REPLACE_FUNC_BODY splice (its bytes are replaced by the donor). */
void *gl_func_0006DC0C(void) {
    volatile int i;
    for (i = 0; i < 15; i++) {}
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006DC0C_pad.s")

#ifdef NON_MATCHING
/* PASS-2 2026-06-26: width fixes (lbu/lhu) on register-independent type bugs.
 * +0x4 type tag is u8; +0x6 count, +0x4 mode, +0x1A flag are u16. */
void gl_func_0006DD14(char *arg0) {
    char *sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    char *sp34;
    s32 sp30;
    char *sp2C;
    char *sp28;
    s32 sp24;
    s32 temp_t1;
    u16 temp_t9_2;
    char *temp_t3;
    char *temp_t4;
    char *temp_t4_2;
    char *temp_t9;

    sp30 = 0;
    sp44 = 0;
    sp38 = 0;
    sp34 = arg0;
loop_1:
    func_00000000(*(s32 *)((char *)(sp34) + 0x8), &sp44, 1);
    temp_t9 = *(s32 *)((char *)(sp44) + 0x14);
    if ((temp_t9 != 0) && (*(u8 *)((char *)(temp_t9) + 0x4) == 2) && ((temp_t1 = *(s32 *)((char *)(temp_t9) + 0x14), (temp_t1 == 0)) || (temp_t1 == 1))) {
        temp_t4 = *(s32 *)((char *)(sp44) + 0x14) + 0x14;
        sp28 = temp_t4;
        sp2C = temp_t4 + (*(u16 *)((char *)(temp_t4) + 0x6) * 0x24) + 0x18;
        *(s32 *)((char *)(temp_t4) + 0x8) = -1;
        if (*(u16 *)((char *)(sp28) + 0x4) != 3) {
            *(s32 *)((char *)(sp2C) + 0x4) = (s32) (*(s32 *)((char *)(sp2C) + 0x4) - *(s32 *)((char *)(sp2C) + 0xC));
        }
        if ((*(u16 *)((char *)(sp28) + 0x4) == 2) && (*(s32 *)((char *)(*(s32 *)((char *)(sp44) + 0x14)) + 0x14) == 0)) {
            sp30 = 1;
        } else {
            sp30 = 0;
        }
        func_00000000(*(s32 *)((char *)(sp34) + 0x10), &sp3C, 1);
        func_00000000(0x100401);
        func_00000000(*(s32 *)((char *)(sp44) + 0x14), 0x05000510, *(s32 *)((char *)(sp28) + 0x10) | 0x80000000);
loop_12:
        func_00000000(*(s32 *)((char *)(sp34) + 0xC), &sp40, 1);
        temp_t4_2 = *(s32 *)((char *)(sp44) + 0x14) + 0x14;
        sp28 = temp_t4_2;
        temp_t3 = temp_t4_2 + (*(u16 *)((char *)(temp_t4_2) + 0x6) * 0x24);
        sp2C = temp_t3 + 0x18;
        if (*(s32 *)((char *)(temp_t3) + 0x18) == 0x1D) {
            func_00000000(*(s32 *)((char *)(sp44) + 0x14), 0x05000510, *(s32 *)((char *)(temp_t4_2) + 0x10) | 0x10000000);
            func_00000000(*(s32 *)((char *)(sp44) + 0x14), 0x05000510, *(s32 *)((char *)(sp28) + 0x10));
            func_00000000(*(s32 *)((char *)(sp44) + 0x14), 0x05000508, &sp24);
            if (sp24 & 0x02000000) {
                func_00000000(*(s32 *)((char *)(sp44) + 0x14), 0x05000510, *(s32 *)((char *)(sp28) + 0x10) | 0x01000000);
            }
            *(s32 *)((char *)(sp2C) + 0x0) = 4;
            *(s32 *)((char *)&D_00000000 + 0xA4600010) = 2;
            func_00000000(0x100C01);
        }
        func_00000000(*(s32 *)((char *)(sp44) + 0x4), sp44, 0);
        if ((sp30 == 1) && (*(s32 *)((char *)(*(s32 *)((char *)(sp44) + 0x14)) + 0x2C) == 0)) {
            sp30 = 0;
            goto loop_12;
        }
        func_00000000(*(s32 *)((char *)(sp34) + 0x10), 0, 0);
        if (*(u16 *)((char *)(*(s32 *)((char *)(sp44) + 0x14)) + 0x1A) == 1) {
            func_00000000();
        }
        goto loop_1;
    }
    temp_t9_2 = *(s32 *)((char *)(sp44) + 0x0);
    switch (temp_t9_2) {
    case 10:
        func_00000000(*(s32 *)((char *)(sp34) + 0x10), &sp3C, 1);
        sp38 = ((int (*)())*(s32 *)((char *)(sp34) + 0x14))(0, *(s32 *)((char *)(sp44) + 0xC), *(s32 *)((char *)(sp44) + 0x8), *(s32 *)((char *)(sp44) + 0x10));
        break;
    case 11:
        func_00000000(*(s32 *)((char *)(sp34) + 0x10), &sp3C, 1);
        sp38 = ((int (*)())*(s32 *)((char *)(sp34) + 0x14))(1, *(s32 *)((char *)(sp44) + 0xC), *(s32 *)((char *)(sp44) + 0x8), *(s32 *)((char *)(sp44) + 0x10));
        break;
    case 12:
        func_00000000(*(s32 *)((char *)(sp34) + 0x10), &sp3C, 1);
        sp38 = ((int (*)())*(s32 *)((char *)(sp34) + 0x18))(*(s32 *)((char *)(sp44) + 0x14), 0, *(s32 *)((char *)(sp44) + 0xC), *(s32 *)((char *)(sp44) + 0x8), *(s32 *)((char *)(sp44) + 0x10));
        break;
    case 13:
        func_00000000(*(s32 *)((char *)(sp34) + 0x10), &sp3C, 1);
        sp38 = ((int (*)())*(s32 *)((char *)(sp34) + 0x18))(*(s32 *)((char *)(sp44) + 0x14), 1, *(s32 *)((char *)(sp44) + 0xC), *(s32 *)((char *)(sp44) + 0x8), *(s32 *)((char *)(sp44) + 0x10));
        break;
    case 14:
        func_00000000(*(s32 *)((char *)(sp44) + 0x4), sp44, 0);
        sp38 = -1;
        break;
    default:
        sp38 = -1;
        break;
    }
    if (sp38 != 0) {
        goto loop_1;
    }
    func_00000000(*(s32 *)((char *)(sp34) + 0xC), &sp40, 1);
    func_00000000(*(s32 *)((char *)(sp44) + 0x4), sp44, 0);
    func_00000000(*(s32 *)((char *)(sp34) + 0x10), 0, 0);
    goto loop_1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006DD14);
#endif

/* gl_func_0006E1A4 = libultra osSetEventMesg. LANDED 2026-06-21 as a
 * byte-identical TWIN-PORT of matched kernel func_80004DE0 (kernel_003) -- NOT
 * the "62% dispatcher cap" the prior wrap guessed: it is disable-int, write
 * queue+msg into the event-state table entry, restore-int. The earlier reading
 * had the call before the table write and the wrong arg shape. Real C lives in
 * the donor unit game_libs_ido53_6E1A4.c (IDO 5.3 -O1), spliced via
 * REPLACE_FUNC_BODY. OS-API callees -> gl_func_00000000; event-state table base
 * -> D_00000000. */
typedef struct { int queue; int msg; } EventState_0006E1A4;
void gl_func_0006E1A4(int event, void *queue, int msg) {
    register int sr = gl_func_00000000();
    EventState_0006E1A4 *es = &((EventState_0006E1A4 *)&D_00000000)[event];
    es->queue = (int)queue;
    es->msg = msg;
    gl_func_00000000(sr);
}


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006E20C);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006E1A4_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006E224 - doprnt conversion-specifier dispatcher (0x670, 412 insns).
 *
 * WHOLE-BODY DECODE 2026-06-27 (param-layout + width fix over the 2026-06-20
 * decode). Argument registers realigned to the target: a0 = state pointer
 * (st), a1 = conversion char (c, read UNSIGNED via `andi 0xff`), a2 = va_list
 * cursor (ap), a3 = output byte buffer (buf). The earlier body had c->a0,
 * ap->a1, buf->a2, st->a3 (shifted by one), mismatching the entire arg file.
 *
 * PERMANENT CAP - CALLER-SET $s0 (state pointer). The target reads/writes the
 * format state struct exclusively through $s0, which is NEVER saved in the
 * prologue (only `sw a1,0x20(sp); sw ra,0x14(sp)`, frame = 0x18) NOR restored
 * NOR initialized in the body: $s0 is a live-in the CALLER sets up (the
 * documented caller-set-int-reg cap, feedback_caller_set_int_reg_cap_1080_
 * game_libs.md). IDO C cannot consume a caller-provided $s0 without saving it,
 * so the ~107 `N(s0)` state accesses are modelled as `N(a0)` here and remain
 * register-divergent by construction. The 5 flush calls also `jal 0` (baked-
 * reloc USO) so the call target is unmatchable too.
 *
 * Real flush callee takes the state pointer in a0 (`move a0,s0` precedes each
 * jal) and, for %s, returns the emitted length in $v0.
 * Args: c = conversion char (a1, stashed at sp+0x20); ap = va_list (a2);
 * buf = output buffer (a3); st = format state (a0; really $s0).
 * State offsets: 0x0/0x4 = 64-bit value hi/lo; 0x8 = end ptr; 0xC = length;
 * 0x2C = int operand (%n); 0x30 = flags (bit0 space, bit1 plus, bit3 alt);
 * 0x34 = length modifier ('l'=0x6C,'h'=0x68,'L'=0x4C); 0x24 = width clamp. */
extern s32 gl_doprnt_flush_0006E224(char *st);

void gl_func_0006E224(char *st, u8 c, s32 *ap, char *buf) {
    s32 cc = c;
    s32 width;
    s32 hi;
    char *p;

    *(s32 *)(st + 0xC) = 0;
    *(s32 *)(st + 0x10) = 0;
    *(s32 *)(st + 0x14) = 0;
    *(s32 *)(st + 0x18) = 0;
    *(s32 *)(st + 0x1C) = 0;
    *(s32 *)(st + 0x20) = 0;

    if ((cc < 0x26) || ((u32)(cc - 0x45) >= 0x34U) || ((u32)(cc - 0x46) >= 0x19U)) {
        if (cc < 0x26) {
            return;
        }
        if (cc == 0x25) {
            buf[*(s32 *)(st + 0xC)] = 0x25;
        } else {
            buf[*(s32 *)(st + 0xC)] = c;
        }
        *(s32 *)(st + 0xC) = *(s32 *)(st + 0xC) + 1;
        return;
    }

    switch (cc) {
    case 0x46:
        p = (char *)((((*(s32 *)ap) + 3) & ~3) + 4);
        *(s32 *)ap = (s32)p;
        buf[*(s32 *)(st + 0xC)] = (s8) *(s32 *)(p - 4);
        *(s32 *)(st + 0xC) = *(s32 *)(st + 0xC) + 1;
        return;

    case 0x47:
    case 0x48:
    case 0x49:
        if (*(u8 *)(st + 0x34) == 0x6C) {
            p = (char *)((((*(s32 *)ap) + 3) & ~3) + 4);
            *(s32 *)ap = (s32)p;
            hi = *(s32 *)(p - 4);
            *(s32 *)(st + 0x0) = hi >> 0x1F;
            *(s32 *)(st + 0x4) = hi;
        } else if (*(u8 *)(st + 0x34) == 0x4C) {
            p = (char *)((((*(s32 *)ap) + 7) & ~7) + 8);
            *(s32 *)ap = (s32)p;
            *(s32 *)(st + 0x0) = *(s32 *)(p - 8);
            *(s32 *)(st + 0x4) = *(s32 *)(p - 4);
        } else {
            p = (char *)((((*(s32 *)ap) + 3) & ~3) + 4);
            *(s32 *)ap = (s32)p;
            hi = *(s32 *)(p - 4);
            *(s32 *)(st + 0x0) = hi >> 0x1F;
            *(s32 *)(st + 0x4) = hi;
        }
        if (*(u8 *)(st + 0x34) == 0x68) {
            hi = (s16) *(s32 *)(st + 0x4);
            *(s32 *)(st + 0x0) = hi >> 0x1F;
            *(s32 *)(st + 0x4) = hi;
        }
    case 0x4A:
    case 0x4B:
    case 0x4C:
        if (*(s32 *)(st + 0x0) < 0) {
            buf[*(s32 *)(st + 0xC)] = 0x2D;
            *(s32 *)(st + 0xC) = *(s32 *)(st + 0xC) + 1;
        } else if (*(s32 *)(st + 0x30) & 2) {
            buf[*(s32 *)(st + 0xC)] = 0x2B;
            *(s32 *)(st + 0xC) = *(s32 *)(st + 0xC) + 1;
        } else if (*(s32 *)(st + 0x30) & 1) {
            buf[*(s32 *)(st + 0xC)] = 0x20;
            *(s32 *)(st + 0xC) = *(s32 *)(st + 0xC) + 1;
        }
        *(s32 *)(st + 0x8) = *(s32 *)(st + 0xC) + (s32)buf;
        gl_doprnt_flush_0006E224(st);
        return;

    case 0x4D:
    case 0x4E:
    case 0x4F:
        if (*(u8 *)(st + 0x34) == 0x6C) {
            p = (char *)((((*(s32 *)ap) + 3) & ~3) + 4);
            *(s32 *)ap = (s32)p;
            hi = *(s32 *)(p - 4);
            *(s32 *)(st + 0x0) = hi >> 0x1F;
            *(s32 *)(st + 0x4) = hi;
        } else if (*(u8 *)(st + 0x34) == 0x4C) {
            p = (char *)((((*(s32 *)ap) + 7) & ~7) + 8);
            *(s32 *)ap = (s32)p;
            *(s32 *)(st + 0x4) = *(s32 *)(p - 4);
            *(s32 *)(st + 0x0) = *(s32 *)(p - 8);
        } else {
            p = (char *)((((*(s32 *)ap) + 3) & ~3) + 4);
            *(s32 *)ap = (s32)p;
            hi = *(s32 *)(p - 4);
            *(s32 *)(st + 0x0) = hi >> 0x1F;
            *(s32 *)(st + 0x4) = hi;
        }
    case 0x50:
        if (*(u8 *)(st + 0x34) == 0x68) {
            *(s32 *)(st + 0x0) = 0;
            *(s32 *)(st + 0x4) = *(s32 *)(st + 0x4) & 0xFFFF;
        } else {
            *(s32 *)(st + 0x0) = 0;
        }
        if (*(s32 *)(st + 0x30) & 8) {
            buf[*(s32 *)(st + 0xC)] = 0x30;
            *(s32 *)(st + 0xC) = *(s32 *)(st + 0xC) + 1;
            if ((cc == 0x78) || (cc == 0x58)) {
                buf[*(s32 *)(st + 0xC)] = c;
                *(s32 *)(st + 0xC) = *(s32 *)(st + 0xC) + 1;
            }
        }
        *(s32 *)(st + 0x8) = *(s32 *)(st + 0xC) + (s32)buf;
        gl_doprnt_flush_0006E224(st);
        return;

    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58: {
        s32 v = *(s32 *)ap;
        char *q;
        if ((s32)v & 1) {
            q = (char *)((v & 0xFF) + 7);
            *(s32 *)ap = (s32)q;
            q -= 0x16;
        } else if ((v & 0xFF) & 2) {
            q = (char *)((v & 0xFF) + 0xA);
            *(s32 *)ap = (s32)q;
            q -= 0x28;
        } else {
            q = (char *)(((v & 0xFF) & ~7) + 8);
            *(s32 *)ap = (s32)q;
        }
        *(f64 *)(st + 0x0) = (f64) *(s32 *)(q - 8);
        if (*(u16 *)(st + 0x2) & 0x8000) {
            buf[*(s32 *)(st + 0xC)] = 0x2D;
            *(s32 *)(st + 0xC) = *(s32 *)(st + 0xC) + 1;
        } else if (*(s32 *)(st + 0x30) & 2) {
            buf[*(s32 *)(st + 0xC)] = 0x2B;
            *(s32 *)(st + 0xC) = *(s32 *)(st + 0xC) + 1;
        } else if (*(s32 *)(st + 0x30) & 1) {
            buf[*(s32 *)(st + 0xC)] = 0x20;
            *(s32 *)(st + 0xC) = *(s32 *)(st + 0xC) + 1;
        }
        *(s32 *)(st + 0x8) = *(s32 *)(st + 0xC) + (s32)buf;
        gl_doprnt_flush_0006E224(st);
        return;
    }

    case 0x59:
        if (*(u8 *)(st + 0x34) == 0x68) {
            p = (char *)((((*(s32 *)ap) + 3) & ~3) + 4);
            *(s32 *)ap = (s32)p;
            *(s16 *)(*(s32 *)(p - 4)) = (s16) *(s32 *)(st + 0x2C);
            return;
        }
    case 0x5A:
        if (*(u8 *)(st + 0x34) == 0x6C) {
            p = (char *)((((*(s32 *)ap) + 3) & ~3) + 4);
            *(s32 *)ap = (s32)p;
            *(s32 *)(*(s32 *)(p - 4)) = *(s32 *)(st + 0x2C);
            return;
        }
    case 0x5B:
        if (*(u8 *)(st + 0x34) == 0x4C) {
            p = (char *)((((*(s32 *)ap) + 3) & ~3) + 4);
            *(s32 *)ap = (s32)p;
            hi = *(s32 *)(p - 4);
            *(s32 *)(hi + 0x0) = 0;
            *(s32 *)(hi + 0x4) = *(s32 *)(st + 0x2C);
            return;
        }
    case 0x5C:
        p = (char *)((((*(s32 *)ap) + 3) & ~3) + 4);
        *(s32 *)ap = (s32)p;
        *(s32 *)(*(s32 *)(p - 4)) = *(s32 *)(st + 0x2C);
        return;

    case 0x5D:
        p = (char *)((((*(s32 *)ap) + 3) & ~3) + 4);
        *(s32 *)ap = (s32)p;
        hi = *(s32 *)(p - 4);
        *(s32 *)(st + 0x4) = hi;
        *(s32 *)(st + 0x0) = hi >> 0x1F;
        *(s32 *)(st + 0x8) = *(s32 *)(st + 0xC) + (s32)buf;
        gl_doprnt_flush_0006E224(st);
        return;

    case 0x5E: {
        s32 len;
        p = (char *)((((*(s32 *)ap) + 3) & ~3) + 4);
        *(s32 *)ap = (s32)p;
        *(s32 *)(st + 0x8) = *(s32 *)(p - 4);
        len = gl_doprnt_flush_0006E224(st);
        width = *(s32 *)(st + 0x24);
        *(s32 *)(st + 0x14) = len;
        if ((width >= 0) && (width < len)) {
            *(s32 *)(st + 0x14) = width;
        }
        return;
    }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006E224);
#endif

#ifdef NON_MATCHING
/* gl_func_0006E894 - DEEP STRUCTURAL PASS (reconstruction 2026-06-21).
 * printf/_doprnt-style formatted-string emitter (0x648, 402 insns).
 * arg0 = output callback s32(*)(s32 acc, const u8 *src, s32 n, const u8 *fmt).
 * Scans the format string; flushes literal runs via arg0; on '%' (0x25)
 * parses flags/width/precision/'*'/length-mod/conversion. Flag/length lookup
 * via gl_func_0001CA10 (spec table @ &D_00000000+0x23D4, flag bitmask table
 * @ +0x23DC). The conversion itself is formatted by gl_func_0007526C, which
 * writes a result aggregate (`Doprnt`): a prefix buffer (sp74), a body
 * pointer (+0x34) and six segment-length ints (+0x38..+0x4C). The emitter
 * then lays out left-pad / prefix / leading-zeros / body / trailing-pad
 * around that aggregate, blank-filling 0x20 bytes (' ') from D_0003E484 and
 * '0' fill from D_0003E460 in 0x20-byte chunks.
 *
 * Verified against the TRUE target disasm (raw .word, not the prior built
 * NM): va_list advances by 4 per arg (read at sp+0xE4 onward); the body is a
 * POINTER (+0x34) plus an offset, not an inline 0x40 buffer (the 2026-06-02
 * pass modelled spA8 as a buffer — corrected here). Logic now byte-faithful
 * to the target; residual is pure IDO frame-slot/regalloc divergence on a
 * 402-insn function (documented printf-family cap). Default INCLUDE_ASM path
 * is byte-exact; this body is reference-only. */
#define FW(p, o) (*(int *)((char *)(p) + (o)))
extern int gl_func_0001CA10();
extern int gl_func_0007526C();

s32 gl_func_0006E894(s32 (*arg0)(), s32 arg1, u8 *arg2, s32 arg3) {
    u8 spD4;
    s32 spD0;
    s32 spCC;
    s32 spC8;
    s32 spC4;
    int spA0;
    u8 sp74;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t6_3;
    s32 temp_t7_2;
    s32 temp_t8;
    int *temp_t8_2;
    s32 temp_t8_3;
    int *temp_t9;
    s32 temp_t9_3;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_6;
    s32 var_s0_7;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s3;
    u8 *spA8;
    int spAC;
    int spB0;
    int spB4;
    int spB8;
    int spBC;
    int spC0;
    u8 *var_a3;
    u8 *var_s2;
    u8 *var_s2_2;
    u8 temp_t7;
    u8 temp_t9_2;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 var_a1;
    u8 var_a1_2;
    u8 var_s0;

    var_a3 = arg2;
    var_s3 = arg1;
    spCC = 0;
loop_1:
    temp_v0 = *var_a3;
    var_s2 = var_a3;
    var_s0 = temp_v0;
    if ((temp_v0 != 0) && (temp_v0 != 0x25)) {
loop_3:
        temp_v0_2 = FW(var_s2, 0x1);
        var_s2 += 1;
        var_s0 = temp_v0_2;
        if (temp_v0_2 != 0) {
            if (temp_v0_2 != 0x25) {
                goto loop_3;
            }
        }
    }
    temp_v0_3 = var_s2 - var_a3;
    if (temp_v0_3 > 0) {
        temp_v0_4 = arg0(var_s3, var_a3, temp_v0_3, var_a3);
        var_s3 = temp_v0_4;
        if (temp_v0_4 != 0) {
            spCC += temp_v0_3;
            goto block_9;
        }
        return spCC;
    }
block_9:
    var_s2_2 = var_s2 + 1;
    if (var_s0 == 0) {
        return spCC;
    }
    spD0 = 0;
    temp_v0_5 = gl_func_0001CA10(0x23D4, FW(var_s2, 0x1));
    var_s0_2 = temp_v0_5;
    if (temp_v0_5 != 0) {
        do {
            var_s2_2 += 1;
            spD0 |= FW(((var_s0_2 - 0x23D4) * 4), 0x23DC);
            temp_v0_6 = gl_func_0001CA10(0x23D4, *var_s2_2);
            var_s0_2 = temp_v0_6;
        } while (temp_v0_6 != 0);
    }
    if (*var_s2_2 == 0x2A) {
        temp_t9 = (arg3 + 3) & ~3;
        arg3 = temp_t9 + 4;
        temp_t8 = *temp_t9;
        var_s2_2 += 1;
        spC8 = temp_t8;
        if (temp_t8 < 0) {
            spC8 = -temp_t8;
            spD0 |= 4;
        }
        var_a1 = *var_s2_2;
    } else {
        spC8 = 0;
        var_a1 = *var_s2_2;
        if (((s32) var_a1 >= 0x30) && ((s32) var_a1 < 0x3A)) {
loop_19:
            if (spC8 < 0x3E7) {
                spC8 = (var_a1 + (spC8 * 0xA)) - 0x30;
            }
            var_a1 = FW(var_s2_2, 0x1);
            var_s2_2 += 1;
            if (((s32) var_a1 >= 0x30) && ((s32) var_a1 < 0x3A)) {
                goto loop_19;
            }
        }
    }
    if (var_a1 != 0x2E) {
        spC4 = -1;
        var_a1_2 = FW(var_s2_2, 0x0);
    } else {
        temp_t7 = FW(var_s2_2, 0x1);
        var_s2_2 += 1;
        if (temp_t7 == 0x2A) {
            temp_t8_2 = (arg3 + 3) & ~3;
            arg3 = temp_t8_2 + 4;
            var_s2_2 += 1;
            spC4 = *temp_t8_2;
            var_a1_2 = *var_s2_2;
        } else {
            spC4 = 0;
            var_a1_2 = *var_s2_2;
            if (((s32) var_a1_2 >= 0x30) && ((s32) var_a1_2 < 0x3A)) {
loop_29:
                if (spC4 < 0x3E7) {
                    spC4 = (var_a1_2 + (spC4 * 0xA)) - 0x30;
                }
                var_a1_2 = FW(var_s2_2, 0x1);
                var_s2_2 += 1;
                if (((s32) var_a1_2 >= 0x30) && ((s32) var_a1_2 < 0x3A)) {
                    goto loop_29;
                }
            }
        }
    }
    if (gl_func_0001CA10(0x23D0, var_a1_2) != 0) {
        temp_t9_2 = *var_s2_2;
        var_s2_2 += 1;
        spD4 = temp_t9_2;
    } else {
        spD4 = 0;
    }
    if ((spD4 == 0x6C) && (*var_s2_2 == 0x6C)) {
        spD4 = 0x4C;
        var_s2_2 += 1;
    }
    gl_func_0007526C();
    temp_t9_3 = (((((spC8 - spAC) - spB0) - spB4) - spB8) - spBC) - spC0;
    spC8 = temp_t9_3;
    temp_t6 = temp_t9_3 > 0;
    if (!(spD0 & 4) && (temp_t6 != 0)) {
        var_s1 = temp_t9_3;
        if (temp_t6 != 0) {
loop_42:
            var_s0_3 = var_s1;
            if ((u32) var_s1 >= 0x21U) {
                var_s0_3 = 0x20;
            }
            if (var_s0_3 > 0) {
                temp_v0_7 = arg0(var_s3, (u8 *)0x2E460, var_s0_3);
                var_s3 = temp_v0_7;
                if (temp_v0_7 != 0) {
                    spCC += var_s0_3;
                    goto block_48;
                }
                return spCC;
            }
block_48:
            var_s1 -= var_s0_3;
            if (var_s1 <= 0) {
                goto block_49;
            }
            goto loop_42;
        }
    }
block_49:
    if (spAC > 0) {
        temp_v0_8 = arg0(var_s3, &sp74, spAC);
        var_s3 = temp_v0_8;
        if (temp_v0_8 != 0) {
            spCC += spAC;
            goto block_53;
        }
        return spCC;
    }
block_53:
    temp_t6_2 = spB0 > 0;
    if (temp_t6_2 != 0) {
        var_s1_2 = spB0;
        if (temp_t6_2 != 0) {
loop_55:
            var_s0_4 = var_s1_2;
            if ((u32) var_s1_2 >= 0x21U) {
                var_s0_4 = 0x20;
            }
            if (var_s0_4 > 0) {
                temp_v0_9 = arg0(var_s3, (u8 *)0x2E484, var_s0_4);
                var_s3 = temp_v0_9;
                if (temp_v0_9 != 0) {
                    spCC += var_s0_4;
                    goto block_61;
                }
                return spCC;
            }
block_61:
            var_s1_2 -= var_s0_4;
            if (var_s1_2 <= 0) {
                goto block_62;
            }
            goto loop_55;
        }
    }
block_62:
    if (spB4 > 0) {
        temp_v0_10 = arg0(var_s3, spA8, spB4);
        var_s3 = temp_v0_10;
        if (temp_v0_10 != 0) {
            spCC += spB4;
            goto block_66;
        }
        return spCC;
    }
block_66:
    temp_t6_3 = spB8 > 0;
    if (temp_t6_3 != 0) {
        var_s1_3 = spB8;
        if (temp_t6_3 != 0) {
loop_68:
            var_s0_5 = var_s1_3;
            if ((u32) var_s1_3 >= 0x21U) {
                var_s0_5 = 0x20;
            }
            if (var_s0_5 > 0) {
                temp_v0_11 = arg0(var_s3, (u8 *)0x2E484, var_s0_5);
                var_s3 = temp_v0_11;
                if (temp_v0_11 != 0) {
                    spCC += var_s0_5;
                    goto block_74;
                }
                return spCC;
            }
block_74:
            var_s1_3 -= var_s0_5;
            if (var_s1_3 <= 0) {
                goto block_75;
            }
            goto loop_68;
        }
    }
block_75:
    if (spBC > 0) {
        temp_v0_12 = arg0(var_s3, spA8 + spB4, spBC);
        var_s3 = temp_v0_12;
        if (temp_v0_12 != 0) {
            spCC += spBC;
            goto block_79;
        }
        return spCC;
    }
block_79:
    temp_t8_3 = spC0 > 0;
    if (temp_t8_3 != 0) {
        var_s1_4 = spC0;
        if (temp_t8_3 != 0) {
loop_81:
            var_s0_6 = var_s1_4;
            if ((u32) var_s1_4 >= 0x21U) {
                var_s0_6 = 0x20;
            }
            if (var_s0_6 > 0) {
                temp_v0_13 = arg0(var_s3, (u8 *)0x2E484, var_s0_6);
                var_s3 = temp_v0_13;
                if (temp_v0_13 != 0) {
                    spCC += var_s0_6;
                    goto block_87;
                }
                return spCC;
            }
block_87:
            var_s1_4 -= var_s0_6;
            if (var_s1_4 <= 0) {
                goto block_88;
            }
            goto loop_81;
        }
    }
block_88:
    temp_t7_2 = spC8 > 0;
    if ((spD0 & 4) && (temp_t7_2 != 0)) {
        var_s1_5 = spC8;
        if (temp_t7_2 != 0) {
loop_91:
            var_s0_7 = var_s1_5;
            if ((u32) var_s1_5 >= 0x21U) {
                var_s0_7 = 0x20;
            }
            if (var_s0_7 > 0) {
                temp_v0_14 = arg0(var_s3, (u8 *)0x2E460, var_s0_7);
                var_s3 = temp_v0_14;
                if (temp_v0_14 != 0) {
                    spCC += var_s0_7;
                    goto block_97;
                }
                return spCC;
            }
block_97:
            var_s1_5 -= var_s0_7;
            if (var_s1_5 <= 0) {
                goto block_98;
            }
            goto loop_91;
        }
    }
block_98:
    var_a3 = var_s2_2 + 1;
    goto loop_1;
}
#undef FW
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006E894);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006E894_pad.s")

extern int gl_func_00000000();
int gl_func_0006EEE4(int a0, int a1, int a2) {
    return gl_func_00000000(a0, a1) + a2;
}

/* gl_func_0006EF08: vsprintf-style varargs wrapper. MATCHED.
 *   rv = func("string@0x83550", a0, a1, &a2);   // &a2 = va_list start
 *   if (rv >= 0) a0[rv] = 0;
 *   return rv;
 *
 * Declaring it VARARGS `(char*, int, int, ...)` makes IDO home all four arg regs
 * at a 0x20 frame and reload them (was the "frame-size shift" cap), and reading
 * the 3rd call arg from memory via `((int*)&a2)[-1]` forces the reload
 * (`lw a2,36(sp)`) instead of a register move. At -O2 the body emits byte-for-byte
 * the 0x58 target function (21 insns ending `jr ra` + the delay-slot nop). The
 * function .s was previously split at 0x54 with the jr-ra delay nop carved into a
 * _pad.s sidecar — a splat boundary artifact, since a C-compiled `jr ra` always
 * owns its delay slot. Restored the delay nop into gl_func_0006EF08.s (size 0x58)
 * so the baseline function symbol matches the real -O2 codegen. The _pad.s sidecar
 * The 1-word all-zero alignment pad at 0x6EF60 (so the next fn gl_func_0006EF64
 * sits at +0x5C) is appended via SUFFIX_BYTES_FORCE (sanctioned all-zero data
 * pad; FORCE because the function ends in the natural jr-ra;nop epilogue).
 * (A -g3 unit was tried and rejected: -g3 reschedules the prologue/epilogue.) */
extern int func_00000000();
extern int D_00000000;
int gl_func_0006EF08(char *a0, int a1, int a2, ...) {
    int rv = func_00000000((char*)&D_00000000 + 0x83550, a0, ((int *)&a2)[-1], &a2);
    if (rv >= 0) {
        a0[rv] = 0;
    }
    return rv;
}

#ifdef NON_MATCHING
/* gl_func_0006EF64: VARARGS dispatch helper (frame-size/arg-home cap).
 *   The target homes a0/a1/a2 at the TOP of a 0x28 frame (sw a0,0x28;
 *   sw a1,0x2C; sw a2,0x30) and RELOADS each before every use — the
 *   classic misdiagnosed-variadic arg-home shape. Fixed-arity
 *   (int,void*,int) keeps a1 register-resident at a 0x18 frame (52.75%).
 *   Declaring it VARARGS `(int a0, void *a1, ...)` homes+reloads every
 *   arg slot; reading a0/a1/a2 from their homed slots (via the va base
 *   `&a1`) forces the `lw` reloads instead of register moves.
 *   See docs/IDO_CODEGEN.md "VARARGS declaration fixes the frame-size
 *   shift / arg-home cap". Sibling of gl_func_0006EF08. */
extern int D_6EF64_g;
extern int FUNC_6EF64_a(void);
extern int FUNC_6EF64_b(int, void *, int);
extern int FUNC_6EF64_c(void);
extern int FUNC_6EF64_d(int, void *, int);
int gl_func_0006EF64(int a0, void *a1, ...) {
    int *args = (int *)&a0;
    int s1, s0;
    if (D_6EF64_g == 0) {
        return -1;
    }
    *(int *)((char *)args[1] + 0x14) = args[0];
    if (args[2] == 0) {
        *(short *)args[1] = 0xF;
    } else {
        *(short *)args[1] = 0x10;
    }
    if (*(unsigned char *)((char *)args[1] + 2) == 1) {
        s1 = FUNC_6EF64_a();
        s0 = FUNC_6EF64_b(s1, (void *)args[1], 0);
    } else {
        s1 = FUNC_6EF64_c();
        s0 = FUNC_6EF64_d(s1, (void *)args[1], 0);
    }
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006EF64);
#endif


/* gl_func_0006F088 = libultra osLeoDiskInit (leodiskinit.c verbatim):
 * LeoDiskHandle = { type DEVICE_TYPE_64DD, base PHYS_TO_K1(PI_DOM2_ADDR1)
 * = 0xA5000000, latency 3, pulse 6, pageSize 6, relDuration 2, domain
 * PI_DOMAIN2 }; writes PI_BSD_DOM2 LAT/PWD/PGS/RLS; speed = 0;
 * bzero(&transferInfo, 0x60); interrupt-masked insert at the head of
 * __osPiTable; __osDiskHandle = &LeoDiskHandle; returns the handle.
 * BOUNDARY FIX: splat's game_libs_func_0006F038 ("descriptor initializer
 * that falls through", 0x50 incl. 3 leading pad nops) was this function's
 * HOISTED HEAD -- IDO 5.3 -O1 schedules the six field stores before the
 * addiu-sp prologue and splat split at the prologue. True entry = 0x6F044;
 * the spliced symbol covers 0x6F044..0x6F140 (the pad nops 0x6F038/3C/40
 * are emitted as SUFFIX_BYTES_FORCE on gl_func_0006EF64).
 * WIRED 2026-07-10 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_6F088.c (64/64; extern-
 * struct spelling for per-store own-lui + TU-defined 2-byte PgsRls pair
 * for the single shared-$at sb pair, osCartRomInit lever). Body below is
 * a placeholder for the splice. */
void *gl_func_0006F088(void) {
    volatile int ready = 0;
    ready = 1;
    return (void *)ready;
}

void gl_func_0006F144(int a0, ...) {
}

/* Varargs empty stub (sibling of matched gl_func_0006F144). */
void gl_func_0006F160(int a0, ...) {
}

#ifdef NON_MATCHING
/* memcpy: copy a2 bytes from a1 to a0, return a0. Reloc-free. Byte-match cap:
 * the target is a tight 13-insn non-unrolled byte loop, but IDO -O2 UNROLLS the
 * C memcpy by 4 (+ remainder) to 28 insns. Same unroll cap as 1FA20/611E4 —
 * couldn't suppress the unroll from C. */
void *game_libs_func_0006F17C(char *a0, char *a1, int a2) {
    char *p = a0;
    if (a2 != 0) {
        do {
            char c = *a1;
            a2--;
            p++;
            a1++;
            *(p - 1) = c;
        } while (a2 != 0);
    }
    return a0;
}
#else
/* game_libs_func_0006F17C = memcpy(void *dst, u8 *src, int count) -> dst. Same
 * UNROLL CAP as the memset twin 00067D50: target is the NON-unrolled byte-copy
 * loop (lower-opt build); IDO -O2 unrolls by 4. Needs a lower-opt file split. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F17C);
#endif

int game_libs_func_0006F1B0(char *a0) {
    char *p = a0;
    if (*p != 0) {
        do {
            p++;
        } while (*p != 0);
    }
    return p - a0;
}

/* game_libs_func_0006F1D8: leaf-branch-past-end CAP per
 * feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F1D8);

/* game_libs_func_0006F1FC: 7-insn string-walk loop-bottom tail-fragment:
 *   lbu v1,1(a0); addiu a0,a0,1; bne v0,v1,-0x1C; nop; move v0,a0;
 *   jr ra; nop
 * Caller-set $v0 + backward branch to 0x6F1EC (before .s start 0x6F1FC).
 * Splat captured loop tail per
 * feedback_backward_branch_before_s_start_is_loop_tail_splat_error. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F1FC);

#ifdef NON_MATCHING
/* Constructor: a0[0]=&sym1, a0[1]=&sym2, a0[2]=0, a0[3]=0, a0[4]=a2, a0[5]=a1
 * (a1 stored in jr delay slot). The function symbol includes 3 leading nops
 * (0x6F218-0x6F220) before the body at 0x6F224 — PREFIX_BYTES inject prepends
 * them to the .o but doesn't extend the symbol to cover them in the linked elf,
 * so byte-exact requires a splat boundary fix (shift symbol to 0x6F224 / absorb
 * the 3 nops as previous-fn padding), not just PREFIX_BYTES. Reloc-blind (two
 * distinct symbols both → 0; PM10 multi-symbol). Body documented; default build
 * stays INCLUDE_ASM. */
void game_libs_func_0006F218(int *a0, int a1, int a2) {
    extern int gl_func_00000000();
    a0[0] = (int)&D_00000000;
    a0[1] = (int)&gl_func_00000000;
    a0[2] = 0;
    a0[3] = 0;
    a0[4] = a2;
    a0[5] = a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F218);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F250);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F2A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F2C8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F35C);

/* gl_func_0006F38C = libultra __osSpDeviceBusy (sp.c verbatim):
 * return (*SP_STATUS_REG & (DMA_BUSY|DMA_FULL|IO_FULL)) ? 1 : 0.
 * BOUNDARY FIX: splat's game_libs_func_0006F380 3-word fragment was this
 * function's HOISTED HEAD (IDO -O1 schedules the `register` MMIO load,
 * into a0 per the register hint, before the addiu-sp prologue; splat
 * split at the prologue). True entry = 0x6F384; spliced symbol covers
 * 0x6F384..0x6F3AC (pads 0x6F380 / 0x6F3B0 via SUFFIX_BYTES_FORCE on
 * game_libs_func_0006F35C / this symbol). This RETIRES the "sp=-8 frame
 * with no stack use has no C trigger" cap -- those sweeps probed the
 * split fragment as a standalone int-arg fn at -O2.
 * WIRED 2026-07-10 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_6F38C.c (11/11). Body
 * below is a placeholder for the splice. */
int gl_func_0006F38C(void) {
    volatile int busy = 0;
    return busy;
}

/* gl_func_0006F3BC = libultra __osSiDeviceBusy (si.c verbatim):
 * return (*SI_STATUS_REG & (DMA_BUSY|RD_BUSY)) ? 1 : 0.
 * BOUNDARY FIX: splat's game_libs_func_0006F3B0 3-word "alt-entry
 * fragment" was this function's HOISTED HEAD (same phenomenon as
 * gl_func_0006F38C = __osSpDeviceBusy above). True entry = 0x6F3B4;
 * spliced symbol covers 0x6F3B4..0x6F3DC (pads 0x6F3B0 / 0x6F3E0 via
 * SUFFIX_BYTES_FORCE on gl_func_0006F38C / this symbol).
 * WIRED 2026-07-10 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_6F3BC.c (11/11; 7.1 -O1
 * agrees on this shape). Body below is a placeholder for the splice. */
int gl_func_0006F3BC(void) {
    volatile int busy = 0;
    return busy;
}

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0006F3E4)();
s32 gl_func_0006F3E4(char *arg0, s32 arg1, s32 arg2) {
    s32 temp_t7;
    char *temp_s0;

    temp_s0 = gl_func_00062F64();
    if (FW(arg0, 0x8) >= FW(arg0, 0x10)) {
loop_1:
        if (arg2 == 1) {
            FW((*(int*)0), 0x10) = 8;
            gl_func_00062F64((int)arg0 + 4);
            if (FW(arg0, 0x8) < FW(arg0, 0x10)) {
                goto block_5;
            }
            goto loop_1;
        }
        gl_func_00062F64(temp_s0);
        return -1;
    }
block_5:
    temp_t7 = FW(arg0, 0x10);
    FW(arg0, 0xC) = (s32) ((s32) ((FW(arg0, 0xC) + temp_t7) - 1) % temp_t7);
    *(int*)(FW(arg0, 0x14) + (FW(arg0, 0xC) * 4)) = arg1;
    FW(arg0, 0x8) = (s32) (FW(arg0, 0x8) + 1);
    if (*(int*)(FW(arg0, 0x0)) != 0) {
        gl_func_00062F64(gl_func_00062F64(arg0));
    }
    gl_func_00062F64(temp_s0);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F3E4);
#endif

/* gl_func_0006F534 = libultra osSetThreadPri. LANDED 2026-06-21 as a
 * byte-identical TWIN-PORT of matched kernel func_80006110 (kernel_011_b) --
 * verbatim osSetThreadPri body including the (Thread*)(void*) double-cast that
 * pins the t-reg allocno pair. Real C lives in the donor unit
 * game_libs_ido53_6F534.c (IDO 5.3 -O1; this TU is -O2), spliced in via
 * REPLACE_FUNC_BODY. All five OS-API callees collapse to the address-0
 * placeholder gl_func_00000000; the two distinct globals (running-thread ptr
 * + run-queue head) map to the two distinct zero-resolving placeholders
 * D_00000000 / gl_data_00000000 (kept separate so IDO does not CSE them). */
void gl_func_0006F534(Thread_0006F534 *thread, int pri) {
    register int sr = gl_func_00000000();
    if (thread == 0) {
        thread = (Thread_0006F534 *)D_00000000;
    }
    if (thread->pri != pri) {
        thread->pri = pri;
        if ((Thread_0006F534 *)(void *)thread != (Thread_0006F534 *)D_00000000 && thread->state != 1) {
            gl_func_00000000(thread->queue, thread);
            gl_func_00000000(thread->queue, thread);
        }
        if (((Thread_0006F534 *)D_00000000)->pri < ((Thread_0006F534 *)gl_data_00000000)->pri) {
            ((Thread_0006F534 *)D_00000000)->state = 2;
            gl_func_00000000(&gl_data_00000000);
        }
    }
    gl_func_00000000(sr);
}

extern int *D_6F614_X;
int game_libs_func_0006F614(int *a0) {
    if (a0 == 0) a0 = D_6F614_X;
    return a0[1];
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006F534_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006F634: 20-insn 2-call + 2-global-state-update.
 *   v = call(a0);
 *   p_state[1] = a0;          // D_6F634_state is int*; write [1]
 *   *p_flag |= 0x10;          // D_6F634_flag is unsigned short*
 *   call(v);
 * Two single-pointer globals (USO ind-data refs). */
extern int *D_6F634_state;
extern unsigned short *D_6F634_flag;
void gl_func_0006F634(int a0) {
    int v = gl_func_00000000(a0);
    D_6F634_state[1] = a0;
    *D_6F634_flag |= 0x10;
    gl_func_00000000(v);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F634);
#endif


/* game_libs_func_0006F684: one 108-insn (0x1B0) function. BOUNDARY MERGED
 * 2026-06-02: splat had split it into 0006F684 (6-insn FP-const prologue:
 * `lwc1 $f0,D[0x24D0]` + `mtc1 a1,$f12`/`mtc1 a2,$f14`/`mtc1 a3,$f16` (THREE
 * inputs, ARG-DERIVED — a Vec3-style float triple — hoisted above the frame;
 * the real entry) + gl_func_0006F69C (the prologue+body using f14 in
 * `mul.s $f14,$f14,$f0`). SINGLE-entry per the dual-vs-single test (f12/f14/f16
 * arg-derived + FP-op use; no callers). Absorbed 0006F69C's 102 words into
 * 0006F684 (0x18 -> 0x1B0); dropped the 0006F69C symbol. Brings f12/f14/f16
 * (=a1/a2/a3) and f0 (=D[0x24D0]) in-scope, retracting the implicit
 * caller-set-float cap; the body is decodable in a future pass. */
#ifdef NON_MATCHING
extern f32 game_libs_func_0006C400(f32);
void game_libs_func_0006F684(char *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp40;
    f32 sp3C;
    f32 sp34;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f14;
    f32 temp_f20;
    f32 temp_f22;

    temp_f0 = (*(f32*)((char*)&D_00000000 + 0x24D0));
    temp_f12 = arg1 * temp_f0;
    temp_f14 = arg2 * temp_f0;
    arg2 = temp_f14;
    arg1 = temp_f12;
    (*(f32*)((char*)&D_00000000 + 0x44030)) = temp_f0;
    arg3 *= temp_f0;
    temp_f20 = game_libs_func_0006C400(temp_f12);
    temp_f22 = game_libs_func_0006C400(arg1);
    sp40 = game_libs_func_0006C400(arg2);
    sp34 = game_libs_func_0006C400(arg2);
    sp3C = game_libs_func_0006C400(arg3);
    temp_f0_2 = game_libs_func_0006C400(arg3);
    (*(f32*)((char*)arg0 + 0x0)) = (f32) (sp34 * temp_f0_2 * arg4);
    (*(f32*)((char*)arg0 + 0x4)) = (f32) (sp34 * sp3C * arg4);
    (*(f32*)((char*)arg0 + 0xC)) = 0.0f;
    (*(f32*)((char*)arg0 + 0x8)) = (f32) (-sp40 * arg4);
    (*(f32*)((char*)arg0 + 0x1C)) = 0.0f;
    temp_f12_2 = temp_f20 * sp40;
    (*(f32*)((char*)arg0 + 0x10)) = (f32) (((temp_f12_2 * temp_f0_2) - (temp_f22 * sp3C)) * arg4);
    (*(f32*)((char*)arg0 + 0x14)) = (f32) (((temp_f12_2 * sp3C) + (temp_f22 * temp_f0_2)) * arg4);
    (*(f32*)((char*)arg0 + 0x18)) = (f32) (temp_f20 * sp34 * arg4);
    (*(f32*)((char*)arg0 + 0x2C)) = 0.0f;
    temp_f12_3 = temp_f22 * sp40;
    (*(f32*)((char*)arg0 + 0x20)) = (f32) (((temp_f12_3 * temp_f0_2) + (temp_f20 * sp3C)) * arg4);
    (*(f32*)((char*)arg0 + 0x24)) = (f32) (((temp_f12_3 * sp3C) - (temp_f20 * temp_f0_2)) * arg4);
    (*(f32*)((char*)arg0 + 0x28)) = (f32) (temp_f22 * sp34 * arg4);
    (*(f32*)((char*)arg0 + 0x30)) = arg5;
    (*(f32*)((char*)arg0 + 0x34)) = arg6;
    (*(f32*)((char*)arg0 + 0x3C)) = 1.0f;
    (*(f32*)((char*)arg0 + 0x38)) = arg7;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F684);
#endif

#ifdef NON_MATCHING
/* gl_func_0006F834: 26-insn 2-call wrapper with float-bits-passthrough.
 * Decoded shape:
 *   void f(int x0, int x1, int x2, int x3, float a, float b, float c, float d) {
 *     char buf[0x40];
 *     gl_func_00000000(buf, x1, x2, x3, a, b, c, d);
 *     gl_func_00000000(buf, x0);
 *   }
 * Caller passes 4 int reg args + 4 floats via stack at sp+0x78..0x84.
 * Callee reads stack floats via lwc1, forwards to next callee via swc1
 * outgoing slots (sp+0x10..0x1C).
 *
 * Cap: target emits a mysterious mtc1 a1,f12; mtc1 a2,f14; mtc1 a3,f16
 * at entry IMMEDIATELY followed by mfc1 a1,f12; mfc1 a2,f14; mfc1 a3,f16
 * after the lwc1 reads — a net no-op round-trip through FP regs. Likely
 * an IDO emit artifact when args are typed `float` in C but arrive in
 * int regs per O32. No standard C produces this exactly. */
void gl_func_0006F834(int x0, int x1, int x2, int x3,
                      float a, float b, float c, float d) {
    char buf[0x40];
    typedef void (*Fn8)(char*, int, int, int, float, float, float, float);
    typedef void (*Fn2)(char*, int);
    ((Fn8)gl_func_00000000)(buf, x1, x2, x3, a, b, c, d);
    ((Fn2)gl_func_00000000)(buf, x0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F834);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006F834_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
#ifndef B
#define B(p, o) (*(u8 *)((char *)(p) + (o)))
#endif
extern char *gl_pidma_tbl[];
s32 gl_func_0006F8A4(char *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    volatile s32 sp2C;
    s32 sp28;
    char *sp24;
    s32 temp_t7;
    u8 temp_t4;
    u8 temp_t5;
    u8 temp_t5_2;
    u8 temp_t5_3;
    u8 temp_t5_4;
    u8 temp_t8;
    u8 temp_t8_2;
    u8 temp_t8_3;
    u8 temp_t8_4;
    char *temp_t6;

    temp_t7 = *(s32 *)0xA4600010;
    sp2C = temp_t7;
    if (temp_t7 & 3) {
        do {
            sp2C = *(s32 *)0xA4600010;
        } while (sp2C & 3);
    }
    temp_t4 = B(arg0, 0x9);
    temp_t6 = gl_pidma_tbl[temp_t4];
    sp28 = (s32) temp_t4;
    if (temp_t6 != arg0) {
        sp24 = temp_t6;
        if (temp_t4 == 0) {
            temp_t8 = B(arg0, 0x5);
            if (B(temp_t6, 0x5) != temp_t8) {
                *(s32 *)0xA4600014 = (s32) temp_t8;
            }
            temp_t5 = B(arg0, 0x6);
            if (B(sp24, 0x6) != temp_t5) {
                *(s32 *)0xA460001C = (s32) temp_t5;
            }
            temp_t8_2 = B(arg0, 0x7);
            if (B(sp24, 0x7) != temp_t8_2) {
                *(s32 *)0xA4600020 = (s32) temp_t8_2;
            }
            temp_t5_2 = B(arg0, 0x8);
            if (B(sp24, 0x8) != temp_t5_2) {
                *(s32 *)0xA4600018 = (s32) temp_t5_2;
            }
        } else {
            temp_t8_3 = B(arg0, 0x5);
            if (B(sp24, 0x5) != temp_t8_3) {
                *(s32 *)0xA4600024 = (s32) temp_t8_3;
            }
            temp_t5_3 = B(arg0, 0x6);
            if (B(sp24, 0x6) != temp_t5_3) {
                *(s32 *)0xA460002C = (s32) temp_t5_3;
            }
            temp_t8_4 = B(arg0, 0x7);
            if (B(sp24, 0x7) != temp_t8_4) {
                *(s32 *)0xA4600030 = (s32) temp_t8_4;
            }
            temp_t5_4 = B(arg0, 0x8);
            if (B(sp24, 0x8) != temp_t5_4) {
                *(s32 *)0xA4600028 = (s32) temp_t5_4;
            }
        }
        gl_pidma_tbl[sp28] = arg0;
    }
    *(s32 *)0xA4600000 = ((int(*)())gl_func_00062F64)(arg3);
    *(s32 *)0xA4600004 = (FW(arg0, 0xC) | arg2) & 0x1FFFFFFF;
    switch (arg1) {                                 /* irregular */
    case 0:
        *(s32 *)0xA460000C = arg4 - 1;
block_27:
        return 0;
    case 1:
        *(s32 *)0xA4600008 = arg4 - 1;
        goto block_27;
    default:
        return -1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F8A4);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006F8A4_pad.s")

/* gl_func_0006FAD4: 32-insn flag-extract + conditional bit-set/clear.
 *   v0 = gl_func_00000000(a0); flag = (v0 & 0x100) ? 1 : 0;
 *   if (v0 & 0x80) { a0[1] |= flag; a0[1] &= ~2; }  return flag;
 * LANDED 2026-07-09 via REPLACE_FUNC_BODY donor splice: the target is plain
 * IDO 7.1 -O1 (args/locals sp-homed, if/else li/b/sw arms — the old wrap's
 * "beql branch-shape gap" was just this unit's -O2). Real C lives in the
 * -O1 donor unit game_libs_o1_6FAD4.c (32/32), spliced over this -O2
 * stand-in. Body below is a placeholder for the splice (its bytes are
 * replaced by the donor). */
int gl_func_0006FAD4(int* a0) {
    volatile int v0 = gl_func_00000000(a0);
    volatile int flag = (v0 & 0x100) ? 1 : 0;
    if (v0 & 0x80) {
        a0[1] = a0[1] | flag;
        a0[1] = a0[1] & ~2;
    }
    return flag;
}

/* gl_func_0006FB54: 64-bit-add-carry helper. Verified decode (m2c via disasm-func.py):
 *   r1 = helper(); r2 = helper();
 *   helper(r1);
 *   sum = (r2 - D[0]) + D[1];
 *   return ((unsigned)sum < (unsigned)D[1]) + D[0];   // carry into the high word
 * (D[0]=*(int*)&D_00000000, D[1]=*(int*)(&D+4); reads D[0] twice = two luis.)
 * Logic exact but sub-80: built 25 insns vs target 34 — the target keeps r1 in $s0
 * across the calls AND spills diff/D[0]/D[1] across the 3rd call (IDO 64-bit-codegen
 * spill pattern); -O2 C optimizes the spills away. Resume: needs the spill pattern
 * (more live ranges across the 3rd call) — multi-tick / permuter. */
#ifdef NON_MATCHING
/* gl_func_0006FB54: 33-insn 64-bit accumulator. r0 = cb(); r1 = cb(); cb(r0);
 * returns a 64-bit global base (hi:lo from two globals) plus the 32-bit delta
 * (r1 - another global), with the manual sltu carry into the high word (long long
 * return in v0:v1). NM (reference decode): three collapsed-placeholder calls +
 * several collapsed D refs (distinct globals collapsed to D_00000000 here);
 * raw-.word game_libs reloc depression. */
extern int gl_func_00000000();
extern int D_00000000;
long long gl_func_0006FB54(int a0) {
    int r0 = gl_func_00000000(a0);
    int r1 = gl_func_00000000(a0);
    int delta = r1 - *(int *)&D_00000000;
    long long base = ((long long)*(int *)&D_00000000 << 32) |
                     (unsigned int)*(int *)((char *)&D_00000000 + 4);
    gl_func_00000000(r0);
    return base + (unsigned int)delta;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FB54);
#endif

#ifdef NON_MATCHING
/* STRUCTURAL first-pass 2026-05-31 (raw-.word USO decode). Straight-line
 * global-state reset: zeroes a struct at &D_fbd8_a (words 0,4) + scalars
 * D_fbd8_b/d, and re-links several global list heads (each `*D_x` is a node
 * pointer): D_c node self-links (n->4=n); D_e n->0=n->4; D_f n->0x10=0,n->0x14=0;
 * D_g copies n->0x10/0x14 to n->8/0xC; D_h n->0x18=0; D_i n->0x1C=0. Symbols are
 * placeholder externs (real D_ names unknown in raw-.word form).
 *
 * 18% partial — NEXT-PASS RESIDUAL ANALYSIS (side-by-side 2026-05-31):
 *  (1) Direct globals (D_a struct, D_b/D_d): target is at-FUSED `lui at,%hi;
 *      sw t,OFF(at)` with the zero pre-loaded into a REGISTER (`li t6,0;
 *      li t7,0`), ours is base-local `lui v1; addiu v1,v1,0; sw zero,OFF(v1)`
 *      (extra addiu + sw $zero). Needs inline-symbol-arith + named zero temps
 *      (docs feedback-ido-inline-symbol-arith-vs-base-local).
 *  (2) Pointer globals: target keeps each `*D_x` in a DISTINCT reg
 *      (t8/t9/t1/t4/t5/t8) with lui/lw HOISTED + interleaved with other
 *      globals' stores; ours reuses $v0 sequentially. Distinct named pointer
 *      locals declared early did NOT fix it (IDO still collapsed to 32 insns
 *      vs 38 — 6 short). Exact hoist/interleave is the hard part.
 *  LIKELY PERMANENT ~18% (2026-05-31, deeper look): the target REUSES scratch
 *  temps across globals (e.g. t6/t7 hold 0 for D_a's stores @0x04/08 then are
 *  reused as D_g's loaded fields @0x68/6C) AND heavily hoists/interleaves the
 *  lui/lw — both scheduler/allocator-determined, same C-uncontrollable class as
 *  the instruction-scheduler swaps. Correct logic; don't expect a 100% match
 *  from C. */
extern int D_fbd8_a, D_fbd8_b, D_fbd8_d;
extern int *D_fbd8_c, *D_fbd8_e, *D_fbd8_f, *D_fbd8_g, *D_fbd8_h, *D_fbd8_i;
void game_libs_func_0006FBD8(void) {
    int *n;
    (&D_fbd8_a)[1] = 0;
    (&D_fbd8_a)[0] = 0;
    D_fbd8_b = 0;
    D_fbd8_d = 0;
    n = D_fbd8_c;
    n[1] = (int)n;
    n = D_fbd8_e;
    n[0] = n[1];
    n = D_fbd8_f;
    n[0x10 / 4] = 0;
    n[0x14 / 4] = 0;
    n = D_fbd8_g;
    n[8 / 4] = n[0x10 / 4];
    n[0xC / 4] = n[0x14 / 4];
    n = D_fbd8_h;
    n[0x18 / 4] = 0;
    n = D_fbd8_i;
    n[0x1C / 4] = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006FBD8);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006FC70);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FC78);

#ifdef NON_MATCHING
/* gl_func_0006FDE8: 29-insn 4-call cascade w/ 64-bit-add via carry detect (0x74, frame 0x28).
 *
 * Decoded structure (raw-word disasm):
 *   func(a0, a1);                                   // 1st call
 *   v0_2 = func();                                  // 2nd call (a0/a1 post-1st-call state)
 *   *D_global = v0_2;                                // store 2nd-call result
 *   // 64-bit add: D_X = D_X + (a0_saved:a1_saved)
 *   {
 *       int low  = *D_X_low + a1_saved;
 *       int carry = ((unsigned)low < (unsigned)a1_saved);
 *       int high = D_X_hi + carry + a0_saved;
 *       // saved to sp+0x20 / sp+0x24 (callsite stack args for func3)
 *   }
 *   func(low, ..., high_via_stack);                  // 3rd call (low in $a0, high at sp+0x20/0x24)
 *   func(v0_2);                                      // 4th call w/ 2nd-call result
 *
 * The 64-bit add via `sltu at, low, addend` + `addu carry, sym_lo` pattern is
 * IDO's standard expansion for `(s64)X = (s64)D + (s64)(a0,a1)` when args
 * 0-1 are an int64 pair (a0=hi, a1=lo).
 *
 * 2026-05-31: 47.9%->73.9% by removing a PHANTOM D_X_hi global (the high part is
 * literal 0, not a global read) + branchless carry. Residual: the 3rd call passes
 * `high` via the stack (sp+0x20) not a1 — the 64-bit-stack-arg convention (frame
 * 0x28 vs 0x20). INCLUDE_ASM remains build path.
 */
extern int D_global_val;
extern unsigned int D_X_low;
/* 64-bit-add helper. X passed as a long long in a0:a1 (hi:lo); adds the
 * 32-bit global D_X_low (zero-extended) producing a 64-bit sum spilled to
 * sp+0x20/0x24. Residual cap: the target spills sum_hi/sum_lo and passes only
 * sum_lo (a0) to the third call (sum_hi spilled-but-dead), which the clean
 * `unsigned long long` add form can't reproduce — the long-long param makes the
 * 64-bit add itself match (carry chain + literal-0 hi word) but reshapes the
 * call convention and global-store ordering (63% vs 74% manual form below). */
void gl_func_0006FDE8(int a0_hi, unsigned int a1_lo) {
    int v0_2;
    unsigned int low;
    int high;
    gl_func_00000000(a0_hi, a1_lo);
    v0_2 = gl_func_00000000();
    D_global_val = v0_2;
    low = D_X_low + a1_lo;
    high = (low < a1_lo) + a0_hi;
    gl_func_00000000(low, high);
    gl_func_00000000(v0_2);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FDE8);
#endif

#ifdef NON_MATCHING
/* gl_func_0006FE5C: 98-insn 64-bit free-list / heap-block search-and-split helper.
 * Size 0x188, frame 0x38.
 *
 * Walks a singly-linked-list of memory blocks at *(void**)&D_00000000, each
 * node holding a 64-bit free-region (offsets 0x10/0x14 = lo/hi end-pointer
 * pair, offset 0x0 = next-link, offset 0x4 = secondary link). Returns the
 * allocated block via the saved sp+0x28/0x2C pair (v0:v1 64-bit return).
 *
 * Decoded structure (raw-word disasm — high-level):
 *   struct FreeNode {
 *       FreeNode *next;        // 0x0  — list link
 *       FreeNode *secondary;   // 0x4  — secondary link (size-sorted? aux list?)
 *       uint32_t  start_lo;    // 0x10
 *       uint32_t  start_hi;    // 0x14 — alternate: end_lo
 *       // (loop reads 0x10/0x14 as 64-bit range-end pointer)
 *   };
 *
 *   uint64_t alloc_range(uint64_t size) {  // a0:a1 = size (64-bit)
 *       FreeNode *head_jal = setup_alloc(...);            // jal #1 (entry hook)
 *       FreeNode *cursor   = *(FreeNode**)&D_00000000;     // head pointer
 *       if (cursor == NULL) goto epilogue;
 *
 *       // STAGE 1: walk the list looking for a free block where
 *       //   block->[0x14]:[0x10] >= size  (64-bit unsigned compare)
 *       while (cursor != NULL) {
 *           uint64_t end   = ((u64)cursor->[0x14] << 32) | cursor->[0x10];
 *           uint64_t avail = end - cursor_base;
 *           if (avail >= size) break;
 *           cursor = cursor->next;
 *       }
 *       if (!cursor) goto epilogue;
 *
 *       // STAGE 2: split or unlink the block
 *       uint64_t new_end = (((u64)cursor->[0x14] << 32) | cursor->[0x10]) - size;
 *       // Update cursor's range: [0x10]:[0x14] = new_end (shrunk)
 *       cursor->[0x10] = (uint32_t)new_end;
 *       cursor->[0x14] = (uint32_t)(new_end >> 32);
 *
 *       // STAGE 3: chain to secondary list at offset 0x4 — propagate the shrink
 *       FreeNode *sec = cursor->[0x4];
 *       sec->[0x10] = cursor->[0x10];
 *       sec->[0x14] = cursor->[0x14];
 *       sec->[0x0]  = cursor->[0x0];    // (link rewire)
 *       cursor->[0x0]->[0x4] = sec->[0x4];
 *
 *       // STAGE 4: finalize via second jal
 *       finalize(allocated_block);                         // jal #2
 *
 *   epilogue:
 *       return v0:v1 (saved at sp+0x28:0x2C);
 *   }
 *
 * Notes:
 *  - Standard "best-fit free-list with primary+secondary links" pattern,
 *    common in N64 heap allocators. The two-link layout suggests an explicit
 *    size-sorted secondary list for fast lookup.
 *  - 64-bit comparison uses canonical `sltu/subu` chain.
 *  - 2 jal calls bookend the function (entry setup + exit finalize) — likely
 *    interrupt-mask wrap (`__osDisableInt` / `__osRestoreInt` per
 *    reference_1080_libc_export_symbols_in_game_libs.md). Heap operations
 *    must be critical-section guarded.
 *  - Return value is 64-bit v0:v1 — likely (allocated_addr_hi, allocated_addr_lo)
 *    for the K1-mapped uncached address of the new block.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
extern int gl_func_00000000();
extern int D_00000000;
// 64-bit free-list walk-and-insert. obj->0x10:0x14 is a 64-bit key. Walk the
// list at *&D from *head, subtracting each block's 0x10:0x14 from the key
// (the IDO-emitted subtract uses a borrow taken from the HI-word compare) until
// the key fits, then write the reduced key back, shrink the chosen block, and
// rewire links (obj->0=cur, obj->4=cur->4, *(cur->4)=obj, cur->4=obj). Bracketed
// by entry/finalize cbs; returns the key pair v0:v1. Reloc-blind cbs/&D.
long long gl_func_0006FE5C(char *obj) {
    int saved;
    char *cur;
    char *d;
    int key_lo, key_hi, cur_lo, cur_hi, b;

    saved = gl_func_00000000(obj);
    d = *(char **)&D_00000000;
    cur = *(char **)d;
    key_lo = *(int *)(obj + 0x10);
    key_hi = *(int *)(obj + 0x14);
    if (cur == d) {
        goto insert;
    }
    cur_lo = *(int *)(cur + 0x10);
    cur_hi = *(int *)(cur + 0x14);
    if ((unsigned int)key_lo < (unsigned int)cur_lo) {
        goto insert;
    }
    if ((unsigned int)cur_lo < (unsigned int)key_lo) {
        goto sub;
    }
    if ((unsigned int)cur_hi >= (unsigned int)key_hi) {
        goto insert;
    }
sub:
    cur_lo = *(int *)(cur + 0x10);
    cur_hi = *(int *)(cur + 0x14);
    b = (unsigned int)key_hi < (unsigned int)cur_hi;
    key_lo = (key_lo - cur_lo) - b;
    key_hi = key_hi - cur_hi;
    cur = *(char **)cur;
    if (cur == *(char **)&D_00000000) {
        goto insert;
    }
    cur_lo = *(int *)(cur + 0x10);
    cur_hi = *(int *)(cur + 0x14);
    if ((unsigned int)cur_lo < (unsigned int)key_lo) {
        goto sub;
    }
    if ((unsigned int)key_lo < (unsigned int)cur_lo) {
        goto insert;
    }
    if ((unsigned int)cur_hi < (unsigned int)key_hi) {
        goto sub;
    }
insert:
    *(int *)(obj + 0x10) = key_lo;
    *(int *)(obj + 0x14) = key_hi;
    if (cur != *(char **)&D_00000000) {
        cur_lo = *(int *)(cur + 0x10);
        cur_hi = *(int *)(cur + 0x14);
        b = (unsigned int)cur_hi < (unsigned int)key_hi;
        *(int *)(cur + 0x10) = (cur_lo - key_lo) - b;
        *(int *)(cur + 0x14) = cur_hi - key_hi;
    }
    *(char **)(obj + 0x0) = cur;
    *(int *)(obj + 0x4) = *(int *)(cur + 0x4);
    *(char **)(*(int *)(cur + 0x4)) = obj;
    *(int *)(cur + 0x4) = (int)obj;
    gl_func_00000000(saved);
    return ((long long)key_lo << 32) | (unsigned int)key_hi;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FE5C);
#endif

/* gl_func_0006FFE4 = libultra __osSetGlobalIntMask. LANDED 2026-06-21 as a
 * byte-identical TWIN-PORT of matched kernel func_800061F0 (kernel_011_b) --
 * NOT the "68.9% 2-call wrapper cap" the prior wrap guessed: it is disable-int,
 * OR the arg into the global int-mask word, restore-int. The two calls are
 * osDisableInt/osRestoreInt (both collapse to gl_func_00000000), not a callback.
 * Real C lives in the donor unit game_libs_ido53_6FFE4.c (IDO 5.3 -O1), spliced
 * via REPLACE_FUNC_BODY. Global int-mask word -> D_00000000. */
void gl_func_0006FFE4(int mask) {
    register int sr = gl_func_00000000();
    D_00000000 |= mask;
    gl_func_00000000(sr);
}

/* gl_func_00070040 = libultra osAiSetFrequency (aisetfreq.c verbatim):
 * dacRate = osViClock/(f32)freq + .5f; <132 -> -1; bitRate = dacRate/66
 * capped 16; AI_DACRATE/BITRATE = -1'd; AI_CONTROL = DMA_ON; returns
 * osViClock/dacRate. BOUNDARY FIX: the 3-word orphan
 * game_libs_func_00070030 (lui/lw osViClock + mtc1 a0,$f8) was this
 * function's hoisted head scheduled before the addiu-sp prologue by IDO
 * 5.3; its INCLUDE_ASM was removed and the spliced symbol covers
 * 0x70034..0x70194 (the orphan's leading 0x70030 pad nop is emitted as
 * SUFFIX_BYTES_FORCE on gl_func_0006FFE4).
 * WIRED 2026-07-10 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_70040.c (88/88; 7.1 -O1
 * coalesces the u8 bitRate andi-to-temp+or pair). Body below is a
 * placeholder for the splice. */
int gl_func_00070040(unsigned int frequency) {
    volatile int ret = -1;
    if (frequency != 0) {
        ret = 0;
    }
    return ret;
}
