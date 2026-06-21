#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Vec3i;
typedef struct { float x, y, z; } Vec3;





/* gl_func_00073034: DECODE CORRECTED 2026-06-09 -- THREE placeholder jals,
 * not two, and there is NO stolen-prologue donation (the fn is a clean
 * 16-insn unit ending jr+delay at 0x40). Structure:
 *   call1(a0, a1?)          -- jal with `sw s0` scheduled into its delay
 *   v = call2(a0, a1)       -- a0 reloaded before, a1 in the jal delay
 *   call3()                 -- `move s0,v0` (capture call2's v0) in delay
 *   return v                -- v0 = s0 round-trip across the epilogue
 * v lives in s0 because it crosses call3 (register-class residency).
 * 5.3 -O1 with `register int v` reproduces frame 0x28 + s0 save + the
 * round-trip exactly; residual 11/16 word diffs are pure scheduling: the
 * register keyword makes cc reload a1 (and dup-reload a0) before call1
 * instead of using live args + delay-slot sw s0. Plain int spills v to
 * stack instead (17 insns). Permuter-range residual; both 5.3 and 7.1
 * emit identically. */
#ifdef NON_MATCHING
extern int gl_func_00000000();

int gl_func_00073034(int a0, int a1) {
    register int v;
    gl_func_00000000(a0, a1);
    v = gl_func_00000000(a0, a1);
    gl_func_00000000();
    return v;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073034);
#endif


/* game_libs_func_00073074: 2-word no-jr PI_STATUS_REG (0xA4600010) load
 * stub falling through into the successor -- the stolen leading guard
 * of the following PI-wait loop (same two-entry class as 6F038). */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00073074);

#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007307C);
#endif


/* game_libs_func_000730C4: same 2-word PI_STATUS_REG load stub as 73074. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000730C4);

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000730CC)();
s32 gl_func_000730CC(char *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    char *sp4;
    u8 temp_t0;
    char *temp_t7;

    if (arg3 & 3) {
        do {

        } while (*(s32 *)0xA4600010 & 3);
    }
    temp_t0 = FW(arg0, 0x9);
    if (*(int*)(temp_t0 * 4) != (int)arg0) {
        temp_t7 = *(int*)(temp_t0 * 4);
        sp4 = temp_t7;
        if (temp_t0 == 0) {
            if (FW(temp_t7, 0x5) != FW(arg0, 0x5)) {
                *(s32 *)0xA4600014 = (s32) FW(arg0, 0x5);
            }
            if (FW(sp4, 0x6) != FW(arg0, 0x6)) {
                *(s32 *)0xA460001C = (s32) FW(arg0, 0x6);
            }
            if (FW(sp4, 0x7) != FW(arg0, 0x7)) {
                *(s32 *)0xA4600020 = (s32) FW(arg0, 0x7);
            }
            if (FW(sp4, 0x8) != FW(arg0, 0x8)) {
                *(s32 *)0xA4600018 = (s32) FW(arg0, 0x8);
            }
        } else {
            if (FW(sp4, 0x5) != FW(arg0, 0x5)) {
                *(s32 *)0xA4600024 = (s32) FW(arg0, 0x5);
            }
            if (FW(sp4, 0x6) != FW(arg0, 0x6)) {
                *(s32 *)0xA460002C = (s32) FW(arg0, 0x6);
            }
            if (FW(sp4, 0x7) != FW(arg0, 0x7)) {
                *(s32 *)0xA4600030 = (s32) FW(arg0, 0x7);
            }
            if (FW(sp4, 0x8) != FW(arg0, 0x8)) {
                *(s32 *)0xA4600028 = (s32) FW(arg0, 0x8);
            }
        }
        *(int*)(temp_t0 * 4) = arg0;
    }
    *arg2 = *(int*)(FW(arg0, 0xC) | arg1 | 0xA0000000);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000730CC);
#endif

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

/* VI-status read leaf (VI_CURRENT/STATUS 0xA4400010 & 1). The old
 * PREFIX_BYTES + INSN_PATCH fake was removed 2026-05-23. STRUCTURE
 * 2026-06-10: the symbol = 1 misattributed leading pad nop (the 3ECDC
 * class -- split a _pad sidecar + rename body to 73314 at the relayout
 * pass) + a 5-insn body whose residual is the `andi t7,v0,1; jr ra;
 * move v0,t7` tail -- the AND lands in a TEMP with the copy in the
 * delay. Shape sweep NEGATIVE (6 forms x O1/O2/g/g3): direct expr and
 * -g3 emit andi-to-v0; named/volatile vars grow frames; nothing
 * produces the temp+move-in-delay pair. Same family as the 69F54 VI
 * reader (relayout backlog). Honest INCLUDE_ASM. */
#ifdef NON_MATCHING
u32 game_libs_func_00073310(void) {
    return *(volatile u32 *)0xA4400010 & 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00073310);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000732C4_pad.s")
