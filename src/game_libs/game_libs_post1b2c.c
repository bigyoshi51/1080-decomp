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

/* gl_func_0006C484 = libultra osInitialize (os/initialize.c verbatim),
 * section 0x80AF0 = export sym 2445. LANDED 2026-09-09 (agent-g) via
 * REPLACE_FUNC_BODY donor splice: real C lives in the IDO 5.3 -O1 donor
 * game_libs_ido53_6C484.c (163/163 first compile). The old 62.9% NM decode
 * ("four vector-source symbols, 64-bit stack-arg cascade") was this
 * function at the wrong opt level: the four lui/addiu pairs are the -O1
 * per-statement re-materialisation of ONE symbol (__osExceptionPreamble)
 * and the (hi,lo,0,3)/(hi,lo,0,4) jal pair is osClockRate * 3 / 4 lowered
 * to __ll_mul / __ull_div under -mips2 (in-unit 6C87C / 6C77C, blank USO
 * relocs). osClockRate / osViClock are DEFINED in the donor TU (shared
 * `lui at` u64 stores); the splice imports them as UND -> pins = 0. The
 * zero word at 0x6C710 is this object's 16-byte inter-object pad
 * (SUFFIX_BYTES_FORCE gl_func_0006C484). Body below is a placeholder for
 * the splice. */
void gl_func_0006C484(void) {
}

/* game_libs_func_0006C714 = __ull_rshift (libgcc-style u64 >> u64, twin of the
 * kernel_056 family below). BOUNDARY FIX 2026-09-09 (twenty-sixth mis-split
 * case, docs/MATCHING_WORKFLOW #leading-nop-cap-is-inter-object-pad-sym-oracle-74844):
 * the old "game_libs_func_0006C710" symbol (0x30) carried a leading zero word;
 * bootup.uso's Sym export table says section 0x80D80 (= splat 0x6C714, the
 * `sw a0,0(sp)`) is the export (sym 2590) and 0x80D7C (the zero) is not -- it
 * is the 16-byte inter-object pad closing gl_func_0006C484, restored as an
 * all-zero SUFFIX_BYTES_FORCE on 6C484. This is the "mod8=4 _pad.s sidecar
 * failure" case of #feedback-leading-nop-symbol-misplaced-on-pad; the suffix
 * shape (no sidecar) sidesteps it. Real C in the -O2 -mips3 donor
 * game_libs_mips3_6C740.c, spliced via REPLACE_FUNC_BODY (this TU is -mips2). */
u64 game_libs_func_0006C714(u64 a, u64 b) { return a >> b; }  /* __ull_rshift */

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

/* gl_func_0006CC14 = libultra osEPiLinkHandle (io/epilinkhandle.c verbatim),
 * section 0x81280 = export sym 1583 (one jal ref). LANDED 2026-09-09
 * (agent-g) via REPLACE_FUNC_BODY donor splice: real C lives in the IDO -O1
 * donor game_libs_o1_6CC14.c (19/19 incl. the jr delay nop at both 7.1 and
 * 5.3 -O1). The old 93.56% NM decode ("2-call helper, D / D_cc14_alias2,
 * volatile spill cross") was this function: both globals are __osPiTable
 * (handle->next @0 = __osPiTable; __osPiTable = handle), the sp+0x1C spill
 * is the un-`register`ed saveMask. The old 18-word .s ended at `jr ra` and
 * gl_func_0006CC14_pad.s carried the delay nop + the 16-byte inter-object
 * pad word before osEPiReadIo (6CC64); the C body emits its own delay nop,
 * so the pad.s pragma is retired and the single pad word is the all-zero
 * SUFFIX_BYTES_FORCE gl_func_0006CC14=0x00000000 in the Makefile (unit
 * layout unchanged). Body below is a placeholder for the splice. */
int gl_func_0006CC14(void *handle) {
    return 0;
}

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

/* gl_func_0006CD44 = libultra osViSetMode (io/visetmode.c verbatim),
 * section 0x813B0 = export sym 1988. LANDED 2026-09-09 (agent-g) via
 * REPLACE_FUNC_BODY donor splice: real C lives in the IDO -O1 donor
 * game_libs_o1_6CD44.c (26/26 at both 7.1 and 5.3 -O1). The old 86% NM
 * decode ("factory + 3 global-data stores + chain, D_A/D_B/D_C") was this
 * function: D_A = D_B = D_C = __osViNext (modep @8, state u16 @0 = 1,
 * control @0xC = modep->comRegs.ctrl), `register u32 saveMask` -> s0.
 * The 2-word gl_func_0006CD44_pad.s below is the inter-object pad before
 * the contpfs.c pair and is unchanged. Body below is a placeholder for
 * the splice. */
void gl_func_0006CD44(void *modep) {
}
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

/* game_libs_func_0006D894 = libultra __osProbeTLB (os/probetlb.s) --
 * HANDWRITTEN, word-for-word the libreultra LEAF: mfc0 EntryHi / andi ASID /
 * mtc0 / tlbp / mfc0 Index / tlbr / PageMask + EntryLo0|1 select, with the
 * trapping `add v0,v0,t5` and the unfilled CP0 hazard nops (IDO never emits
 * either). Section 0x81F00 is 16-aligned (no inter-object pad in this .s;
 * the two zero words of game_libs_func_0006D94C are its trailing pad).
 * Identified 2026-09-09 (agent-g). Permanent INCLUDE_ASM. */
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

/* gl_func_0006DD14 = libultra __osDevMgrMain (io/devmgr.c verbatim, 2.0I
 * struct layout): the PI device-manager thread loop. recv on dm->cmdQueue;
 * 64DD LEO block/track transfers (piHandle->type==DEVICE_TYPE_64DD, cmdType
 * 0/1) take the special path (sectorNum=-1, dramAddr rewind unless sector
 * mode, LEO_BM_CTL |0x80000000 start, evtQueue completion loop with
 * LEO_ERROR_29 reset recovery + PI_STATUS_REG clear + int-mask juggling);
 * everything else dispatches on mb->hdr.type: DMAREAD/DMAWRITE via dm->dma,
 * EDMAREAD/EDMAWRITE via dm->edma, LOOPBACK echoes, jumptable spans type
 * 10..16. Needs IDO 5.3 -O1 (stack-resident locals, ra-only frame), so the
 * real C lives in the donor unit game_libs_ido53_6DD14.c (292/292 exact; the
 * switch jumptable %lo 0x23B0 resolves via the renamed donor-local .rodata
 * reloc gl_func_0006DD14_rodata -- the USO ships the 7-entry table in its
 * data segment). Body below is a placeholder for the REPLACE_FUNC_BODY
 * splice (its bytes are replaced by the donor). */
void gl_func_0006DD14(void) {
    volatile int i;
    for (i = 0; i < 15; i++) {}
}

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

/* gl_func_0006E224 = _Putfld (Plauger libc xprintf.c verbatim) -- the
 * printf conversion dispatcher. LANDED 2026-08-22 via REPLACE_FUNC_BODY
 * donor splice: real C lives in the IDO 5.3 -O3 whole-TU donor
 * game_libs_ido53_6E224.c (see its header for the full reloc story).
 * -O3 interprocedural regalloc passes the state ptr in $s0 unsaved (the
 * long-documented "caller-set $s0 permanent cap" -- RETRACTED: it was
 * whole-TU static linkage all along); no per-function compile can emit
 * that. Body below is a placeholder for the splice. */
void gl_func_0006E224(void *px, char *pap, int code, char *ac) {
    volatile int putfld_spliced = 0;
    if (code != 0) {
        putfld_spliced = (int)pap + (int)ac;
    }
}

/* gl_func_0006E894 = _Printf (Plauger libc xprintf.c verbatim) -- the
 * printf core loop (prout callback in $s4, spaces/zeroes baked absolute
 * 0x2E460/0x2E484 in s7/s5, fchar rodata lo 9172 in s6). LANDED
 * 2026-08-22 via REPLACE_FUNC_BODY donor splice from the same IDO 5.3
 * -O3 whole-TU donor game_libs_ido53_6E224.c (ROM order Putfld-then-
 * Printf; the "extra baked jal 0x20A24" is the intra-TU call to
 * _Putfld at its original link address). Body below is a placeholder
 * for the splice. */
int gl_func_0006E894(char *(*prout)(char *, const char *, unsigned int), char *arg, const char *fmt, char *args) {
    volatile int printf_spliced = 0;
    if (fmt != 0) {
        printf_spliced = (int)arg + (int)args;
    }
    return printf_spliced;
}
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

/* gl_func_0006EF64 = libultra osEPiStartDma, 0xD4/53 body words.
 * bootup.uso Sym1320 exports Text+0x835D0; calls at 0x49BA0/0x49E40.
 * Real fixed-arity C lives in game_libs_o1_6EF64.c, compiled at -O1.
 * The former varargs/argument-home "cap" was an -O2 misdiagnosis.
 * Both IDO 7.1 and 5.3 emit the original 53 words from the reference C.
 * Retain the three existing all-zero padding words before entry 6F044. */
int gl_func_0006EF64(void *handle, void *message, int direction) {
    return 0; /* Replaced by the complete compiled -O1 donor body. */
}


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

/* game_libs_func_0006F17C = libc memcpy (Plauger verbatim, IDO 5.3 -O2
 * donor: game_libs_ido53_6F17C.c). LANDED 2026-08-22 via
 * REPLACE_FUNC_BODY donor splice: 11/11 body words exact, ZERO relocs.
 * The old "UNROLL CAP" verdict retired -- 5.3 -O2 emits the
 * NON-unrolled byte loop natively (7.1 -O2 unrolls by 4; compiler-
 * revision artifact). The symbol's 2 leading all-zero pad words
 * (0x6F17C/0x6F180) are re-homed to the _pad_pre GLOBAL_ASM block
 * below; true entry = 0x6F184, body 0x2C. Body below is a placeholder
 * for the splice. */
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/game_libs_func_0006F17C_pad.s")

void *game_libs_func_0006F17C(void *a0, void *a1, unsigned int a2) {
    volatile int memcpy_spliced = 0;
    if (a2 != 0) {
        memcpy_spliced = a2;
    }
    return a0;
}

int game_libs_func_0006F1B0(char *a0) {
    char *p = a0;
    if (*p != 0) {
        do {
            p++;
        } while (*p != 0);
    }
    return p - a0;
}

/* game_libs_func_0006F1D8 + game_libs_func_0006F1FC = libc strchr
 * (Plauger verbatim, IDO 5.3 -O2 donor: game_libs_ido53_6F1D8.c).
 * LANDED 2026-08-22 via REPLACE_FUNC_BODY donor splice (both keys from
 * the one donor, offsets 0x0:0x24 / 0x24:0x1C), 16/16 words exact,
 * ZERO relocs. splat had split the single fn at the loop-bottom label;
 * the old "leaf-branch-past-end CAP" (6F1D8) and "caller-set $v0 tail
 * fragment" (6F1FC) notes described the two halves of that split --
 * both retired. Plauger string cluster: 6F17C = memcpy, 6F1B0 = strlen
 * (matched in-unit), 6F1D8 = strchr. Bodies below are placeholders for
 * the splice. */
void game_libs_func_0006F1D8(int m) {
    volatile int strchr_head_spliced = 0;
    if (m != 0) {
        strchr_head_spliced = m;
    }
}

void game_libs_func_0006F1FC(int m) {
    volatile int strchr_tail_spliced = 0;
    if (m != 0) {
        strchr_tail_spliced = m;
    }
}

/* game_libs_func_0006F218 = libultra osCreateMesgQueue
 * (os/createmesgqueue.c verbatim shape, IDO 5.3 -O1 donor:
 * game_libs_ido53_6F218.c). LANDED 2026-08-22 via REPLACE_FUNC_BODY
 * donor splice: 11/11 body words exact; the two blank hi/lo pairs =
 * &__osThreadTail x2 (USO load-time relocs, donor externs pinned 0).
 * The old "PREFIX_BYTES can't extend the symbol" blocker solved
 * honestly: the 3 leading all-zero pad words (0x6F218/1C/20) are
 * re-homed to the _pad_pre GLOBAL_ASM block below; true entry =
 * 0x6F224, body 0x2C. Body below is a placeholder for the splice. */
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/game_libs_func_0006F218_pad.s")

void game_libs_func_0006F218(int *a0, int a1, int a2) {
    volatile int ocmq_spliced = 0;
    if (a2 != 0) {
        ocmq_spliced = a2;
    }
}

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

/* gl_func_0006F3E4 = libultra osJamMesg (jammesg.c verbatim): disable
 * ints; while (validCount >= msgCount) either set running thread
 * OS_STATE_WAITING(8) + __osEnqueueAndYield(&mq->fullqueue) when
 * flag==OS_MESG_BLOCK, or restoreInt + return -1; then first = (first +
 * msgCount - 1) % msgCount (the break7/break6 signed-div fingerprint),
 * msg[first] = msg, validCount++, osStartThread(__osPopThread(&mq->mtqueue))
 * if a receiver is blocked, restoreInt, return 0. Sits in the post1b2c
 * -O1 libultra island next to 6FB54 osGetTime / 6FE5C __osInsertTimer;
 * the old 38.75% m2c stub was an -O2 misread of the same logic.
 * WIRED 2026-07-30 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO -O1 donor unit game_libs_o1_6F3E4.c (84/84 word-exact at 7.1
 * -O1, first compile), spliced over this -O2 stand-in. Body below is a
 * placeholder for the splice. */
s32 gl_func_0006F3E4(char *arg0, s32 arg1, s32 arg2) {
    return 0;
}

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

/* gl_func_0006F634 = libultra osViSwapBuffer (io/viswapbuf.c verbatim),
 * section 0x83CA0 = export sym 1549 (two jal refs). LANDED 2026-09-09
 * (agent-g) via REPLACE_FUNC_BODY donor splice: real C lives in the IDO -O1
 * donor game_libs_o1_6F634.c (20/20 at both 7.1 and 5.3 -O1). The old NM
 * decode ("2-call + 2-global-state-update, D_6F634_state / D_6F634_flag")
 * was this function: both globals are __osViNext (framep @4 = frameBufPtr,
 * state u16 @0 |= VI_STATE_BUFFER_UPDATED 0x10), the sp+0x1C spill is the
 * un-`register`ed saveMask. No pad (game_libs_func_0006F684 follows
 * directly); the C body is the same 0x50 as the old .s. Body below is a
 * placeholder for the splice. */
void gl_func_0006F634(void *frameBufPtr) {
}


/* game_libs_func_0006F684 = libultra guPositionF (gu/position.c verbatim),
 * section 0x83CF0 = export sym 2629 (one jal ref at 0x83EE4 = 6F834+0x44, so
 * the 6F834 wrapper is guPosition -- byte-identical to the guFrustum wrapper
 * shape it was landed as). LANDED 2026-09-09 (agent-g) via REPLACE_FUNC_BODY
 * donor splice: real C lives in the IDO 5.3 -O3 donor
 * game_libs_ido53_6F684.c (108/108 in-tree; 105/108 standalone, the three
 * reloc-addend words bake through the game_libs_func_0006F684_rodata / _bss
 * pins = 0x24D0 / 0x44030). The old 84% wrap ("Vec3-style float triple *
 * D[0x24D0], six game_libs_func_0006C400 calls") was this function: the
 * literal is `dtor` (pi/180), the six calls are sinf/cosf (fsin 6A144 /
 * fcos 70FCC, blank load-time relocs), and the D+0x44030 store is IDO -O3
 * writing the `static float dtor` initialiser back into .bss on entry.
 * BOUNDARY MERGED 2026-06-02 (0006F684 6-insn hoisted head + 0006F69C body,
 * 0x18 -> 0x1B0). No pad; the C body is the same 0x1B0 as the old .s. Body
 * below is a placeholder for the splice. */
void game_libs_func_0006F684(void *mf) {
}

/* gl_func_0006F834 = libultra guFrustum (gu/frustum.c verbatim), section
 * 0x83EA0 = export sym 162. LANDED 2026-09-09 (agent-g) via REPLACE_FUNC_BODY
 * donor splice: real C lives in the IDO 5.3 -O3 donor game_libs_ido53_6F834.c
 * (26/26 at both 5.3 and 7.1 -O3). The 87.7% wrap's "2-FP-home budget cap"
 * (only two float params homed in f12/f14, third stack-homed) was -O2 vs
 * -O3 -- the same class as the guOrtho donor (70694/707E8). Callee 1 is the
 * in-unit guFrustumF = game_libs_func_0006F684 (blank import), callee 2 is
 * guMtxF2L (70854). The 2-word gl_func_0006F834_pad.s below is unchanged.
 * Body below is a placeholder for the splice. */
void gl_func_0006F834(void *m) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006F834_pad.s")

/* gl_func_0006F8A4 = libultra osEPiRawStartDma (io/epirawdma.c verbatim):
 * EPI_SYNC (PI_STATUS busy spin + __osCurrentHandle[domain] latch of the
 * four BSD DOM1/DOM2 latency/pageSize/relDuration/pulse registers that
 * differ), PI_DRAM_ADDR = osVirtualToPhysical(dramAddr), PI_CART_ADDR =
 * K1_TO_PHYS(baseAddress|devAddr), kick WR_LEN/RD_LEN by direction,
 * unknown direction -1. The old NM wrap's gl_pidma_tbl WAS
 * __osCurrentHandle and its gl_func_00062F64 call is a blank jal in the
 * ROM (osVirtualToPhysical via USO reloc), NOT the 62F64 helper. Needs
 * IDO 5.3 -O1 (stack-resident locals, direction promoted to s0), so the
 * real C lives in the donor unit game_libs_ido53_6F8A4.c (137/137 words
 * compile-exact, size-exact 0x224). Body below is a placeholder for the
 * REPLACE_FUNC_BODY splice (its bytes are replaced by the donor). */
s32 gl_func_0006F8A4(void) {
    volatile int i;
    for (i = 0; i < 15; i++) {}
    return 0;
}
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

/* gl_func_0006FB54 = libultra osGetTime (gettime.c verbatim): saveMask =
 * __osDisableInt(); tmptime = osGetCount(); elapseCount = tmptime -
 * __osBaseCounter; currentCount = __osCurrentTime;
 * __osRestoreInt(saveMask); return currentCount + elapseCount.
 * Retires the old "keeps r1 in $s0 / 64-bit spill pattern" -O2 note:
 * this is an -O1 libultra helper (`register u32 saveMask` at -O1 IS the
 * s0 coloring; the u64 add is native li-0 zero-extend + sltu carry).
 * WIRED 2026-07-30 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO -O1 donor unit game_libs_o1_6FB54.c (33/33 at both 7.1 and
 * 5.3 -O1), spliced over this -O2 stand-in. Body below is a placeholder
 * for the splice. */
long long gl_func_0006FB54(void) {
    return 0;
}

/* game_libs_func_0006FBE4 = libultra __osTimerServicesInit (os/timerintr.c
 * verbatim), 35 insns, EXACT 2026-09-09 (agent-g). Retires the old
 * "game_libs_func_0006FBD8" 18%-NM global-init wrap: its three leading zero
 * words were gl_func_0006FB54's (osGetTime, 0x84) 16-byte inter-object pad
 * (twenty-sixth mis-split case; now SUFFIX_BYTES_FORCE on 6FB54) -- bootup.uso
 * Sym export sym 2637 sits at section 0x84250 (= 0x6FBE4); 0x84244 is not
 * exported. The "at-fused register-zero stores / distinct pointer regs /
 * scheduler-determined, likely permanent" residual was the -O2-vs-O1 +
 * extern-vs-defined story: the six `lui/lw` pointer reloads are -O1 (no
 * uopt CSE of __osTimerList), and the shared-$at u64 zero store needs
 * __osCurrentTime DEFINED in the TU. Real C lives in the IDO 5.3 -O1 donor
 * game_libs_ido53_6FBE4.c, spliced via REPLACE_FUNC_BODY over this
 * placeholder. Globals: __osCurrentTime (.bss 0x44060, u64),
 * __osBaseCounter (0x44068), __osViIntrCount (0x4406C), __osTimerList
 * (.data 0x2E4B0) -> pins = 0. */
void game_libs_func_0006FBE4(void) {
}

/* __osTimerInterrupt from libreultra src/os/timerintr.c.
 * IDO 7.1 -O1 reproduces all 94 original words; the main O2 unit retains
 * the same complete C body and uses this whole-function compiler output.
 * No instruction bytes are changed. Every named USO import is pinned zero.
 * Sym[2638] exports Text+0x842DC: synthetic 6FC70 is the real entry and
 * the former 6FC78 symbol was an internal prologue split. */
typedef unsigned long long Time6FC70;
typedef void *Mesg6FC70;
typedef struct Queue6FC70_s Queue6FC70;
typedef struct Timer6FC70_s {
    struct Timer6FC70_s *next, *prev;
    Time6FC70 interval, value;
    Queue6FC70 *mq;
    Mesg6FC70 msg;
} Timer6FC70;
extern Timer6FC70 *gl_timerlist_6FC70;
extern unsigned int gl_timercounter_6FC70;
extern void gl_setcompare_6FC70(unsigned int);
extern unsigned int gl_getcount_6FC70(void);
extern void gl_settimerintr_6FC70(Time6FC70);
extern int gl_sendmesg_6FC70(Queue6FC70 *, Mesg6FC70, int);
extern Time6FC70 gl_inserttimer_6FC70(Timer6FC70 *);
void game_libs_func_0006FC70(void)
{
	Timer6FC70 *t;
	unsigned int count;
	unsigned int elapsed_cycles;

	if (gl_timerlist_6FC70->next == gl_timerlist_6FC70)
		return;
	while (1)
	{
		t = gl_timerlist_6FC70->next;
		if (t == gl_timerlist_6FC70)
		{
			gl_setcompare_6FC70(0);
			gl_timercounter_6FC70 = 0;
			break;
		}
		count = gl_getcount_6FC70();
		elapsed_cycles = count - gl_timercounter_6FC70;
		gl_timercounter_6FC70 = count;
		if (elapsed_cycles < t->value)
		{
			t->value -= elapsed_cycles;
			gl_settimerintr_6FC70(t->value);
			return;
		}
		else
		{
			t->prev->next = t->next;
			t->next->prev = t->prev;
			t->next = 0;
			t->prev = 0;
			if (t->mq != 0)
			{
				gl_sendmesg_6FC70(t->mq, t->msg, 0);
			}
			if (t->interval != 0)
			{
				t->value = t->interval;
				gl_inserttimer_6FC70(t);
			}
		}
	}
}

/* gl_func_0006FDE8 = libultra __osSetTimerIntr (os/timerintr.c verbatim,
 * 0x74): savedMask = __osDisableInt(); __osTimerCounter = osGetCount();
 * NewTime = tim + __osTimerCounter; __osSetCompare(NewTime);
 * __osRestoreInt(savedMask). Section 0x84454 = Sym 2640, jal'd from
 * __osTimerInterrupt (6FC70 +0xD4) and osSetTimer (0x87F48). Retires the
 * 73.9% "4-call cascade w/ 64-bit-add, 64-bit-stack-arg cap" decode: the
 * add is u64 + zero-extended u32 (literal-0 hi + sltu carry), the
 * "spilled-but-dead" hi word is the -O1 stack home of the u64 local, and
 * the third call takes only the low word (__osSetCompare is u32).
 * Real C lives in the IDO -O1 donor game_libs_o1_6FC70.c (same TU as
 * __osTimerInterrupt; 29/29 at both 7.1 and 5.3 -O1), spliced over this
 * placeholder via REPLACE_FUNC_BODY. Blank imports, pins = 0. */
void gl_func_0006FDE8(long long tim) {
}

/* gl_func_0006FE5C = libultra __osInsertTimer (timerintr.c verbatim):
 * walk __osTimerList->next subtracting each timer's 64-bit value from
 * tim until timep wraps to the list head or tim <= timep->value; store
 * t->value = tim, decrement the successor's value, doubly-linked insert
 * of t before timep, under __osDisableInt/__osRestoreInt; returns tim.
 * Retires the old "64-bit free-list / heap search-and-split" decode
 * (the 0x10/0x14 pair is OSTimer.value, the 0x0/0x4 links next/prev).
 * WIRED 2026-07-30 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO -O1 donor unit game_libs_o1_6FE5C.c (98/98 at both 7.1 and
 * 5.3 -O1), spliced over this -O2 stand-in. Body below is a placeholder
 * for the splice. */
long long gl_func_0006FE5C(void *t) {
    volatile void *a = t;
    (void)a;
    return 0;
}

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
