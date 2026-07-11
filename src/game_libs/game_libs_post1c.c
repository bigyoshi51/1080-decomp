#include "common.h"

/* DRIFT AUDIT 2026-06-10: this unit has ~2 internal byte-drop points in
 * [0x70314..0x70C44) -- gl_func_00070A14 sits -8 and gl_func_00070B04
 * -4 relative to neighbors, re-aligning by gl_func_00070C44. Candidate
 * for the dropped-former-SUFFIX class (see the confirmed B5AC case +
 * docs/MATCHING_WORKFLOW suffix-fallout audit). GAP CONTENTS verified
 * 2026-06-10: [0x70A0C..0x70A14) = lui at,0x3780; mtc1 at,$f2 (REAL
 * dropped code -- 709DC's former FP-constant suffix, prepend target =
 * gl_func_00070A14.s); the other two gaps are surplus pad words. A
 * net-zero local fix (+8 prepend, -4 -4 pad deletions) was ATTEMPTED
 * and REVERTED: the emission accounting has another contributor (the
 * section grew and diffs ran to the end) -- precise emission tracing
 * needed; relayout session. */
extern int D_00000000;
/* __osViNext / __osViCurr: DISTINCT relocatable globals (pointers to the active
 * VI context). Kept as separate symbols so the swap-tail self-copy is not DCE'd. */
extern void *gl_data_osViNext;
extern void *gl_data_osViCurr;
extern int gl_data_00000000;
extern int gl_data_67470_addr;
extern int gl_data_6C9F4_devCfg;
extern char gl_data_BE14_b;
extern char gl_data_BE14_c;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { int a, b; } Pair2;
typedef struct { float x, y, z; } Vec3;


/* game_libs_func_00070314: 3-insn `mtc0 a0, $11; jr ra; nop` Compare-register
 * write. CP0 access (mtc0) is MIPS3 runtime — IDO C can't emit CP0 ops from
 * standard C. CAP class per reference_1080_mips3_runtime_helpers. Default
 * INCLUDE_ASM remains byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070314);

/* game_libs_func_00070320: 194-insn (0x308) memmove/memcpy with overlap +
 * alignment dispatch. BOUNDARY MERGED 2026-06-02: a multi-path/multi-exit
 * routine (forward-copy, backward-copy, word-aligned, byte paths — several
 * internal `jr ra` exits) that splat carved into three symbols (70320 head +
 * 70398 middle + 70508 tail). 70320 branches forward to 0x704BC (in 70398);
 * 70398/70508 branch backward to 0x70370/0x704D8 (inside this body). Absorbed
 * 70398+70508 (0x78 -> 0x308); dropped both symbols (no external callers). All
 * branches verified in-range; ends at 0x70628 (pre-existing 0xC align pad
 * before gl_func_00070634). Reloc-blind USO; stays INCLUDE_ASM. */
#ifdef NON_MATCHING
void *game_libs_func_00070320(void *src0, void *dst0, s32 n) {
    char *s = src0;
    char *d = dst0;
    void *ret = dst0;

    if (n == 0 || d == s) {
        return ret;
    }
    if ((u32)d < (u32)s || (u32)d >= (u32)s + (u32)n) {
        /* forward copy */
        if (n >= 0x10 && ((u32)s & 3) == ((u32)d & 3)) {
            switch ((u32)s & 3) {
            case 0:
                break;
            case 1:
                d[0] = s[0];
                *(s16 *)(d + 1) = *(s16 *)(s + 1);
                s += 3; d += 3; n -= 3;
                break;
            case 2:
                *(s16 *)d = *(s16 *)s;
                s += 2; d += 2; n -= 2;
                break;
            case 3:
                d[0] = s[0];
                s += 1; d += 1; n -= 1;
                break;
            }
            while (n >= 0x20) {
                s32 w0 = ((s32 *)s)[0];
                s32 w1 = ((s32 *)s)[1];
                s32 w2 = ((s32 *)s)[2];
                s32 w3 = ((s32 *)s)[3];
                s32 w4 = ((s32 *)s)[4];
                s32 w5 = ((s32 *)s)[5];
                s32 w6 = ((s32 *)s)[6];
                s32 w7 = ((s32 *)s)[7];
                s += 0x20; d += 0x20; n -= 0x20;
                ((s32 *)d)[-8] = w0;
                ((s32 *)d)[-7] = w1;
                ((s32 *)d)[-6] = w2;
                ((s32 *)d)[-5] = w3;
                ((s32 *)d)[-4] = w4;
                ((s32 *)d)[-3] = w5;
                ((s32 *)d)[-2] = w6;
                ((s32 *)d)[-1] = w7;
            }
            while (n >= 0x10) {
                s32 w0 = ((s32 *)s)[0];
                s32 w1 = ((s32 *)s)[1];
                s32 w2 = ((s32 *)s)[2];
                s32 w3 = ((s32 *)s)[3];
                s += 0x10; d += 0x10; n -= 0x10;
                ((s32 *)d)[-4] = w0;
                ((s32 *)d)[-3] = w1;
                ((s32 *)d)[-2] = w2;
                ((s32 *)d)[-1] = w3;
            }
            while (n >= 4) {
                s32 w0 = *(s32 *)s;
                s += 4; d += 4; n -= 4;
                ((s32 *)d)[-1] = w0;
            }
        }
        if (n != 0) {
            char *end = s + n;
            do {
                *d++ = *s++;
            } while (s != end);
        }
        return ret;
    } else {
        /* backward copy */
        s += n;
        d += n;
        if (n >= 0x10 && ((u32)s & 3) == ((u32)d & 3)) {
            switch ((u32)s & 3) {
            case 0:
                break;
            case 3:
                d[-1] = s[-1];
                *(s16 *)(d - 3) = *(s16 *)(s - 3);
                s -= 3; d -= 3; n -= 3;
                break;
            case 2:
                *(s16 *)(d - 2) = *(s16 *)(s - 2);
                s -= 2; d -= 2; n -= 2;
                break;
            case 1:
                d[-1] = s[-1];
                s -= 1; d -= 1; n -= 1;
                break;
            }
            while (n >= 0x20) {
                s32 w0 = ((s32 *)s)[-1];
                s32 w1 = ((s32 *)s)[-2];
                s32 w2 = ((s32 *)s)[-3];
                s32 w3 = ((s32 *)s)[-4];
                s32 w4 = ((s32 *)s)[-5];
                s32 w5 = ((s32 *)s)[-6];
                s32 w6 = ((s32 *)s)[-7];
                s32 w7 = ((s32 *)s)[-8];
                s -= 0x20; d -= 0x20; n -= 0x20;
                ((s32 *)d)[7] = w0;
                ((s32 *)d)[6] = w1;
                ((s32 *)d)[5] = w2;
                ((s32 *)d)[4] = w3;
                ((s32 *)d)[3] = w4;
                ((s32 *)d)[2] = w5;
                ((s32 *)d)[1] = w6;
                ((s32 *)d)[0] = w7;
            }
            while (n >= 0x10) {
                s32 w0 = ((s32 *)s)[-1];
                s32 w1 = ((s32 *)s)[-2];
                s32 w2 = ((s32 *)s)[-3];
                s32 w3 = ((s32 *)s)[-4];
                s -= 0x10; d -= 0x10; n -= 0x10;
                ((s32 *)d)[3] = w0;
                ((s32 *)d)[2] = w1;
                ((s32 *)d)[1] = w2;
                ((s32 *)d)[0] = w3;
            }
            while (n >= 4) {
                s32 w0 = ((s32 *)s)[-1];
                s -= 4; d -= 4; n -= 4;
                ((s32 *)d)[0] = w0;
            }
        }
        if (n != 0) {
            char *sentinel;
            s -= 1;
            d -= 1;
            sentinel = s - n;
            do {
                char c = *s;
                s -= 1;
                d -= 1;
                d[1] = c;
            } while (s != sentinel);
        }
        return ret;
    }
}

#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070320);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00070244_pad.s")

/* gl_func_00070634 = libultra global-int-mask bit-clear. LANDED 2026-06-21 as a
 * byte-identical TWIN-PORT of matched kernel func_80006250 (kernel_013) -- NOT
 * the "85.45% 2-global cap" the prior wrap guessed: it is disable-int, AND-NOT
 * the (mask & ~0x401) bits out of ONE global int-mask word, restore-int. The
 * two calls are osDisableInt/osRestoreInt. Real C lives in the donor unit
 * game_libs_ido53_70634.c (IDO 5.3 -O1), spliced via REPLACE_FUNC_BODY. Callees
 * -> gl_func_00000000; int-mask word -> D_00000000. */
extern int gl_func_00000000();
void gl_func_00070634(int mask) {
    register int sr = gl_func_00000000();
    D_00000000 &= ~(mask & ~0x401);
    gl_func_00000000(sr);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00070634_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00070694)();
void gl_func_00070694(char *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f6;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    f32 var_f18;
    s32 var_v1;
    char *temp_v0;
    char *var_v0;

    gl_func_00062F64();
    temp_f0 = arg2 - arg1;
    var_v0 = arg0;
    temp_f12 = arg6 - arg5;
    (*(f32*)((char*)var_v0 + 0x0)) = (f32) (2.0f / temp_f0);
    temp_f2 = arg4 - arg3;
    (*(f32*)((char*)var_v0 + 0x28)) = (f32) (-2.0f / temp_f12);
    (*(f32*)((char*)var_v0 + 0x14)) = (f32) (2.0f / temp_f2);
    (*(f32*)((char*)var_v0 + 0x30)) = (f32) (-(arg2 + arg1) / temp_f0);
    (*(f32*)((char*)var_v0 + 0x34)) = (f32) (-(arg4 + arg3) / temp_f2);
    (*(f32*)((char*)var_v0 + 0x3C)) = 1.0f;
    (*(f32*)((char*)var_v0 + 0x38)) = (f32) (-(arg6 + arg5) / temp_f12);
    var_v1 = 1;
    var_f18 = (*(f32*)((char*)var_v0 + 0x4));
    var_f12 = (*(f32*)((char*)var_v0 + 0x0)) * arg7;
    var_f14 = (*(f32*)((char*)var_v0 + 0x8));
    var_f16 = (*(f32*)((char*)var_v0 + 0xC));
    if (1 != 4) {
        do {
            temp_f10 = var_f18 * arg7;
            var_f18 = (*(f32*)((char*)var_v0 + 0x14));
            temp_f6 = var_f14 * arg7;
            var_f14 = (*(f32*)((char*)var_v0 + 0x18));
            var_v1 += 1;
            temp_f4 = var_f16 * arg7;
            var_f16 = (*(f32*)((char*)var_v0 + 0x1C));
            (*(f32*)((char*)var_v0 + 0x0)) = var_f12;
            var_f12 = (*(f32*)((char*)var_v0 + 0x10)) * arg7;
            (*(f32*)((char*)var_v0 + 0x4)) = temp_f10;
            (*(f32*)((char*)var_v0 + 0x8)) = temp_f6;
            var_v0 += 0x10;
            (*(f32*)((char*)var_v0 + -0x4)) = temp_f4;
        } while (var_v1 != 4);
    }
    temp_v0 = var_v0 + 0x10;
    (*(f32*)((char*)temp_v0 + -0x10)) = var_f12;
    (*(f32*)((char*)temp_v0 + -0xC)) = (f32) (var_f18 * arg7);
    (*(f32*)((char*)temp_v0 + -0x8)) = (f32) (var_f14 * arg7);
    (*(f32*)((char*)temp_v0 + -0x4)) = (f32) (var_f16 * arg7);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070694);
#endif

#ifdef NON_MATCHING
/* gl_func_000707E8: 26-insn float-forwarding wrapper. Receives 7 floats (a1-a3
 * in arg regs + 4 on the stack) and a0; builds them into a stack scratch buffer
 * by calling the (collapsed) callback cb(buf, a1, a2, a3, f5, f6, f7, f8), then
 * processes it with cb(buf, a0). NM (reference decode): two collapsed-placeholder
 * calls (raw-.word game_libs reloc depression) + the mtc1/mfc1 float-arg
 * marshalling and K&R float promotion are not byte-reproducible. */
extern int gl_func_00000000();
void gl_func_000707E8(int a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7) {
    char buf[0x40];
    gl_func_00000000(buf, a1, a2, a3, a4, a5, a6, a7);
    gl_func_00000000(buf, a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000707E8);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00070850)();
void game_libs_func_00070850(char *arg0, char *arg1) {
    f32 var_f16;
    f32 var_f18;
    s32 temp_f12;
    s32 temp_f12_2;
    s32 temp_f14;
    s32 temp_f14_2;
    s32 var_a0;
    s32 var_a2;
    char *var_a3;
    char *var_t0;
    char *var_v0;
    char *var_v1;

    var_v0 = arg1;
    var_v1 = (int)arg1 + 0x20;
    var_a2 = 0;
    var_a3 = arg0;
    do {
        var_t0 = var_a3;
        var_a0 = 1;
        var_f18 = *(f32*)((char*)var_t0 + 0x0);
        var_f16 = *(f32*)((char*)var_t0 + 0x4) * 65536.0f;
        if (1 != 2) {
            do {
                var_a0 += 1;
                var_v0 += 4;
                var_v1 += 4;
                var_t0 += 8;
                temp_f12 = (s32) var_f16;
                temp_f14 = (s32) (var_f18 * 65536.0f);
                FW(var_v0, -0x4) = (s32) ((temp_f14 & 0xFFFF0000) | ((temp_f12 >> 0x10) & 0xFFFF));
                FW(var_v1, -0x4) = (s32) (((temp_f14 << 0x10) & 0xFFFF0000) | (temp_f12 & 0xFFFF));
                var_f18 = *(f32*)((char*)var_t0 + 0x0);
                var_f16 = *(f32*)((char*)var_t0 + 0x4) * 65536.0f;
            } while (var_a0 != 2);
        }
        var_v0 += 4;
        var_v1 += 4;
        temp_f12_2 = (s32) var_f16;
        temp_f14_2 = (s32) (var_f18 * 65536.0f);
        FW(var_v0, -0x4) = (s32) ((temp_f14_2 & 0xFFFF0000) | ((temp_f12_2 >> 0x10) & 0xFFFF));
        FW(var_v1, -0x4) = (s32) (((temp_f14_2 << 0x10) & 0xFFFF0000) | (temp_f12_2 & 0xFFFF));
        var_a2 += 1;
        var_a3 += 0x10;
    } while (var_a2 != 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070850);
#endif

#ifdef NON_MATCHING
/* game_libs_func_00070954: 4x4 identity matrix init. Outer runtime row loop;
 * inner (unrolled) cols set (row == col) ? 1.0f : 0.0f. 83% NM.
 * KEY: the single-level form (`m[0]=(row==0)?..; m[1]=(row==1)?..`) lets IDO
 * fold the ternaries (row known per unrolled iter) and FULLY unroll -> 45%. The
 * NESTED form below keeps `col` a runtime inner-loop var so `(row==col)` can't
 * fold, preserving the target's outer row loop + bnel column compares (+37pp).
 * Residual = constant-register shift (mine a1..a3/t0 for col consts 1/2/3 +
 * bound 4; target a0..a3) + first-col bne-vs-bnel — regalloc/scheduling. */
void game_libs_func_00070954(float *m) {
    int row, col;
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            m[col] = (row == col) ? 1.0f : 0.0f;
        }
        m += 4;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070954);
#endif

/* 12-insn 2-call wrapper using a 0x40-byte stack buffer (0x30). LANDED
 * fuzzy=100. The 2 trailing stolen-prologue insns for the successor
 * (lui $at,0x3780; mtc1 $at,$f0 — float-constant load) were historically
 * absorbed via SUFFIX_BYTES; mechanism REMOVED 2026-05-23 as match-faking. */
void gl_func_000709DC(int a0) {
    char buf[0x40];
    gl_func_00000000(buf);
    gl_func_00000000(buf, a0);
}

#ifdef NON_MATCHING
/* gl_func_00070A14: too-big-N-function-bundle (declared 0xEC, 59 words) — 3 functions.
 * Bundle: 1 complex bit-pack routine + 2 libultra CP0 interrupt-mask helpers.
 *
 * SUB-FUNCTION 1 (0x70A14..0x70AC4, 44 insns) — bit-pack loop:
 *     // Caller passes start_ptr_1 (a0), start_ptr_2 (a1), count (a2-ish), val (a3)
 *     // Two pointer cursors advance in lockstep through paired buffers.
 *     // Inner loop body packs `(src1[i] >> 16) | (src2[j] & 0xFFFF_0000)` and
 *     // stores to dst at offsets advancing by +8 / +0x10. Includes lwc1 + fp
 *     // conversions (`cvt.s.w` / `mul.s` / `sub.s`) and swc1 stores at -8 / -4
 *     // offsets relative to the post-incremented cursor.
 *     // Pattern: likely a vertex-compression / paired-halfword packer for
 *     // RDP F3DEX2 vertex format or audio-sample blitter.
 *
 * SUB-FUNCTION 2 (0x70AC4..0x70AE4, 8 insns) — __osDisableInt:
 *     uint32_t __osDisableInt(void) {
 *         uint32_t prev;
 *         __asm("mfc0 %0, $12" : "=r"(prev));      // read Status (CP0 reg 12)
 *         __asm("mtc0 %0, $12" : : "r"(prev & ~1)); // clear IE bit
 *         return prev & 1;                          // return old IE state
 *     }
 *
 * SUB-FUNCTION 3 (0x70AE4..0x70AFC, 6 insns) — __osSetIntMask / __osRestoreInt:
 *     void __osSetIntMask(uint32_t mask) {
 *         uint32_t prev;
 *         __asm("mfc0 %0, $12" : "=r"(prev));
 *         __asm("mtc0 %0, $12" : : "r"(prev | mask));   // OR-set Status bits
 *     }
 *
 * Notes:
 *  - f2 + f3 are canonical libultra interrupt-control primitives.
 *    See libreultra `src/os/disableInt.c` and `setIntMask.c`. Could be
 *    promoted to byte-exact via libreultra source if compiled with IDO.
 *  - f1's inner pack `(a >> 16) | (b & 0xFFFF0000)` uses lui $t2, 0xFFFF as
 *    a 32-bit mask constant. The trailing `cvt.s.w` and `mul.s/sub.s` are
 *    fixed-point → float conversion (likely for vertex normalization).
 *  - 3 internal `jr $ra` confirm 3-function bundle. Splat boundary issue.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
/* gl_func_00070A14: 4x2 nested-loop packed-short→float converter. ARCHITECTURAL CAP
 * (caller-set $f0): each inner iter recombines halfwords from two src cursors (a1, a1+0x20),
 * cvt.s.w to float, and multiplies by $f0 — but $f0 is read with NO preceding load and is
 * NOT an o32 float-arg reg (f12/f14), so it is a caller-set float the C calling convention
 * can't express (cf. feedback_caller_set_int_reg / caller-set-float cap). Permanent
 * INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070A14);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070AC0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070AE4);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00070A14_pad.s")

/* gl_func_00070B04 = libultra __osViInit (vi.c verbatim): bzero the
 * game_libs-internal vi[2] context array (baked 0x2E4C0), publish
 * __osViCurr/__osViNext, retraceCount=1 + framep=K0BASE on both,
 * osTvType-selected osViMode{Pal,Mpal,Ntsc}Lan1, state=VI_STATE_BLACK,
 * control from modep->comRegs.ctrl, spin while VI_CURRENT > 10, clear
 * VI_CONTROL, tail-call __osViSwapContext (= gl_func_00070C44, the blank
 * jal with the IO_WRITE in its delay slot). Retires the old "state-init
 * chain-walk" NM decode and its beqzl-tail note (5.3 emits the exact
 * loop shape).
 * WIRED 2026-07-10 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_70B04.c (78/78 + jr-delay
 * nop; donor symbol 0x13C). The _pad.s sidecar (8 bytes) was deleted:
 * the donor's delay nop covers 0x70C3C and the last 0x70C40 alignment
 * word is emitted as SUFFIX_BYTES_FORCE on gl_func_00070B04 itself.
 * Body below is a placeholder for the splice. */
void gl_func_00070B04(void) {
    volatile int ret = 0;
    (void)ret;
}

/* gl_func_00070C44 = libultra __osViSwapContext (viswapcontext.c
 * verbatim): field = VI_CURRENT & 1; origin = osVirtualToPhysical
 * (vc->framep) + fldRegs[field].origin; XSCALE/YSCALE_UPDATED merge
 * (f32 y.factor * nomValue with the inline f32->u32 cfc1/ctc1 cast),
 * BLACK hStart=0, REPEATLINE/FADE origin re-derivations, the 13 VI reg
 * writes, then __osViNext/__osViCurr swap + 0x30-byte context copy.
 * Confirms the prior NM decode; vc=s1/vm=s0/v2p=s2 coloring and the
 * 12-byte/iter struct-copy tail come out exactly at IDO 5.3 -O1.
 * WIRED 2026-07-10 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_70C44.c (215/215, size
 * 0x35C flush to func_00070FA0). Body below is a placeholder for the
 * splice. */
void gl_func_00070C44(void) {
    volatile int ret = 0;
    (void)ret;
}

/* game_libs_func_00070FA0 moved to its own -O1 -g3 unit
 * game_libs_o1g3_70FA4.c (2026-07-10): the "leaf-branch-past-end CAP"
 * fragment was the head of ONE function whose tail splat carved off as
 * game_libs_g3_70FBC.c; true entry 0x70FA4 (the 0x70FA0 pad nop is the
 * SUFFIX_BYTES_FORCE word on gl_func_00070C44 above). */
