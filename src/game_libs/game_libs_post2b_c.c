#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Vec3i;
typedef struct { float x, y, z; } Vec3;





/* gl_func_00073034: 16-insn 3-call sandwich returning call-2's result:
 * hook(); r = work(a0, a1); unhook(); return r.
 * 2026-07-17 (agent-h): raw-word IDENTICAL twin (16/16) of exact
 * gl_func_0006B974 found by the sibling scan — the old "permuter-range
 * scheduling residual / v lives in s0" grind is RETRACTED; this is the
 * documented -O1 island call-sandwich (0x6B7A0..0x73824 batch). Real C
 * lives in the -O1 donor unit game_libs_o1_73034.c (mirror of the
 * proven 6B974 donor: plain a0/a1 homing + `register int r` = $s0
 * across call 3), spliced over this -O2 stand-in via REPLACE_FUNC_BODY. */
extern int gl_func_00000000();

int gl_func_00073034(int a0, int a1) {
    register int r;
    gl_func_00000000();
    r = gl_func_00000000(a0, a1);
    gl_func_00000000();
    return r;
}


/* game_libs_func_00073074 (0x8 orphan, no jr ra: lui/lw PI_STATUS_REG)
 * was the HOISTED HEAD of gl_func_0007307C = osPiRawWriteIo — absorbed
 * into the donor splice below (true entry 0x73074, spliced symbol covers
 * 0x73074..0x730C4). */

#if 0
/* SUPERSEDED DECODE (2026-07-18): the "caller-set $a2" implication below
 * was wrong — $a2 is the first PI_STATUS read, hoisted above the prologue
 * by IDO 5.3 -O1 (splat orphan game_libs_func_00073074). Real identity:
 * libultra osPiRawWriteIo variant, write-side twin of gl_func_0006BA7C
 * __osPiRawReadIo. See the donor unit game_libs_ido53_73074.c. */
/* gl_func_0007307C: 18-insn PI DMA-write helper. If (a2 & 3), spin-wait
 * for PI not busy. Then write a1 to (D_0 | a0) via KSEG1 uncached.
 * Returns 0.
 *
 * Symbol size 0x50 includes 2 trailing literal `.word` (lui+lw of
 * PI_STATUS_REG) — splat-absorbed boundary, solo SUFFIX_BYTES can
 * append (no relocs).
 *
 * 2026-05-14 C-only attempts:
 *   - Plain `while (D_A4600010 & 3) {}` — 68 bytes, no prologue+epilogue
 *     (IDO -O2 elides frame because no locals); 12 bytes short of target
 *   - `volatile u32 status` local — 96 bytes (too many stack roundtrips)
 *
 * Target has small 8-byte frame (`addiu sp,-8` / `addiu sp,+8`) even
 * without spillable locals — likely forced by the body's mid-function
 * `addiu sp,+8` BEFORE the trailing stores. INSN_PATCH+SUFFIX_BYTES
 * promotion path: ~17 entry INSN_PATCH + 2-word SUFFIX_BYTES for the
 * literal trailing. Deferred for now. */
int gl_func_0007307C(int a0, int a1, int a2) {
    extern s32 D_A4600010;
    if (a2 & 3) {
        while (D_A4600010 & 3) {}
    }
    *(int*)((D_00000000 | a0) | 0xA0000000) = a1;
    return 0;
}
#endif

/* gl_func_0007307C = libultra osPiRawWriteIo variant: spin while
 * PI_STATUS & 3 (the first read hoisted above the prologue = the absorbed
 * 0x8 orphan), then write data to the KSEG1-uncached cart word
 * ((cartBase | devAddr) | 0xA0000000), return 0. Needs IDO 5.3 -O1, so
 * the real C lives in the donor unit game_libs_ido53_73074.c (20/20
 * exact). Body below is a placeholder for the REPLACE_FUNC_BODY splice
 * (its bytes are replaced by the donor). */
int gl_func_0007307C(void) {
    volatile int i;
    for (i = 0; i < 15; i++) {}
    return 0;
}


/* gl_func_000730CC = libultra osEPiRawReadIo (epirawread.c verbatim,
 * EPI_SYNC/UPDATE_REG piint.h macros): PI busy-wait, per-domain BSD
 * timing-reg update vs __osCurrentHandle[domain], then
 * *data = IO_READ(baseAddress | devAddr). BOUNDARY FIX: the 2-word
 * orphan game_libs_func_000730C4 (lui/lw PI_STATUS_REG) was this
 * function's hoisted first status read scheduled before the addiu-sp
 * prologue by IDO 5.3; its INCLUDE_ASM was removed and the spliced
 * symbol covers 0x730C4..0x73258.
 * WIRED 2026-07-10 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_730CC.c (101/101). Body
 * below is a placeholder for the splice. */
int gl_func_000730CC(char *pihandle, unsigned int devAddr, unsigned int *data) {
    volatile int ret = 0;
    if (pihandle == 0) {
        ret = -1;
    }
    return ret;
}

/* game_libs_func_00073258 = libultra osMapTLBRdb (os/maptlbrdb.s) --
 * HANDWRITTEN assembly in libreultra (LEAF macro, mfc0/mtc0/tlbwi: maps
 * TLB entry 31 -> 0xC0000000 rdb area). IDO C cannot emit CP0/TLB ops;
 * permanent INCLUDE_ASM, same class as the MIPS3-runtime helpers. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00073258);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000730CC_pad.s")

/* gl_func_000732C4 = libultra scheduler yield/dispatch. LANDED 2026-06-21 as a
 * byte-identical TWIN-PORT of matched kernel func_80009A50 (kernel_023):
 * disable-int, set the running-thread state word (running_ptr + 0x10) to 2,
 * dispatch the run-queue head, restore-int. The prior wrap mis-read the running
 * ptr as a direct value and missed the &run-queue dispatch arg. Real C lives in
 * the donor unit game_libs_ido53_732C4.c (IDO 5.3 -O1), spliced via
 * REPLACE_FUNC_BODY. Callees -> gl_func_00000000; running-thread ptr ->
 * D_00000000, run-queue head -> gl_data_00000000 (distinct, no CSE). */
extern int gl_func_00000000();
extern int gl_data_00000000;
void gl_func_000732C4(void) {
    register int sr = gl_func_00000000();
    *(short *)((char *)D_00000000 + 0x10) = 2;
    gl_func_00000000(&gl_data_00000000);
    gl_func_00000000(sr);
}

/* game_libs_func_00073310 = libultra osViGetCurrentField (vigetfield.c
 * verbatim: IO_READ(VI_CURRENT_REG) & 1). The 2026-06-10 "temp+move-in-
 * delay unreachable" negative sweep was 7.1-only: IDO 5.3 -O1 emits the
 * exact `andi t7,v0,1; jr ra; or v0,t7,zero` pair. True entry = 0x73314
 * (5 words); the .s's leading 0x73310 pad nop is emitted as
 * SUFFIX_BYTES_FORCE on gl_func_000732C4.
 * WIRED 2026-07-10 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_73310.c (5/5). Body below
 * is a placeholder for the splice. */
u32 game_libs_func_00073310(void) {
    volatile u32 ret = 1;
    return ret;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000732C4_pad.s")
