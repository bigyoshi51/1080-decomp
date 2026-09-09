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


/* game_libs_func_00070314 = libultra __osSetCompare (`mtc0 a0,$11; jr ra;
 * nop`, handwritten os/setcompare.s -- CP0 access is not emittable from IDO
 * C). Its .s now carries the 4th (zero) word 0x70320: that word is THIS
 * object's 16-byte inter-object pad (0xC -> 0x10), not bcopy's leading nop
 * (twenty-sixth mis-split case, docs/MATCHING_WORKFLOW
 * #leading-nop-cap-is-inter-object-pad-sym-oracle-74844). Oracle: section
 * 0x84980 (= 0x70314) exported sym 2639 (2 R_MIPS_26 refs), 0x8498C not.
 * Default INCLUDE_ASM remains byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070314);

/* game_libs_func_00070324 = libultra bcopy (HANDWRITTEN, libc/bcopy.s), 193
 * insns (0x304). BOUNDARY CORRECTED 2026-09-09 (agent-g): the old
 * "game_libs_func_00070320" symbol (0x308) started with __osSetCompare's pad
 * word; bootup.uso's Sym export table puts the entry at section 0x84990
 * (= 0x70324) under TWO symbols, 2378 (3 R_MIPS_26 refs) and 2642 (none) --
 * exactly bcopy.s's `.weakext bcopy _bcopy` pair -- and 0x8498C is not
 * exported. Splat's 2026-06-02 boundary merge (70320 head + 70398 middle +
 * 70508 tail, several internal `jr ra` exits) stands; only the entry moved.
 * Identity re-verified against references/libreultra/src/libc/bcopy.s word
 * by word from the first non-zero word: `move a3,a1; beqz/beq early rets;
 * blt/bge forwards-vs-backwards split (assembler macro expansions with
 * likely-branch target-copy fills 0x54200008 / 0x50200004); blt 16 byte
 * copy; andi 3 align dispatch with forw_copy2/copy3 lh/lb prefixes; 32/16/4-
 * byte lw bursts; backwards mirror; return a3`. Two decisive non-C tells:
 * the trapping `add v0,a0,a2` / `add a0,a0,a2` / `add a1,a1,a2`
 * (0x00861020 etc. -- IDO only ever emits addu for pointer/int adds at any
 * opt level) and the multiple interior `jr ra` exits. The orchestrator's
 * "memmove.c-class" hypothesis is moot: libultra has no C memmove; bcopy is
 * an asm-only file in every distribution. PERMANENT C-unmatchable
 * (handwritten-asm class); the NM body below is a faithful memmove for the
 * NM path only. Do not burn ticks trying to match it. */
#ifdef NON_MATCHING
void *game_libs_func_00070324(void *src0, void *dst0, s32 n) {
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
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070324);
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

/* gl_func_00070694 = guOrthoF + gl_func_000707E8 = guOrtho (libultra
 * gu/ortho.c verbatim, ONE IDO 5.3 -O3 -mips2 whole-TU donor:
 * game_libs_ido53_70694.c). LANDED 2026-08-22 via REPLACE_FUNC_BODY
 * donor splice, first-compile 111/111 FULL-word identical (the three
 * jal fields are already the USO's blank 0x0C000000 load-time relocs;
 * pins gl_func_00000000_{identf706,orthof706,f2l706} = 0). The old
 * "anonymous float math / K&R promotion cap" readings are RETRACTED:
 * 707E8 is the classic ANSI guOrtho wrapper (mtc1/mfc1 single-precision
 * re-marshal, Matrix mf at sp+40, guOrthoF then guMtxF2L), and 70694's
 * scale loop is -O3's software-pipelined 4x4 *= scale. Bodies below are
 * placeholders for the splice. */
void gl_func_00070694(int mf) {
    volatile int orthof_spliced = 0;
    if (mf != 0) {
        orthof_spliced = mf;
    }
}

void gl_func_000707E8(int m) {
    volatile int ortho_spliced = 0;
    if (m != 0) {
        ortho_spliced = m;
    }
}

/* game_libs_func_00070854 = guMtxF2L (libultra gu/mtxutil.c verbatim,
 * IDO 5.3 -O2 single-fn carve-out donor game_libs_ido53_70854.c, sibling
 * of guMtxIdentF 70954 below). BOUNDARY FIX 2026-09-09 (twenty-sixth
 * mis-split case, docs/MATCHING_WORKFLOW
 * #leading-nop-cap-is-inter-object-pad-sym-oracle-74844): the old
 * "game_libs_func_00070850" symbol (0x104) carried a leading zero word;
 * bootup.uso's Sym export table says section 0x84EC0 (= splat 0x70854,
 * the `lui at,0x4780` = 65536.0f) is the export (sym 1998, several
 * R_MIPS_26 refs) and 0x84EBC (the zero) is not -- it is the 16-byte
 * inter-object pad closing guOrtho (gl_func_000707E8, 0x68), restored as
 * an all-zero SUFFIX_BYTES_FORCE on 707E8. The 2026-08-22 "64/64-word
 * divergent from libreultra guMtxF2L at every opt level" negative was an
 * off-by-one-word comparison against the padded .s: the verbatim source
 * is 64/64 at IDO 5.3 -O2 (and -O3), ZERO relocs. LANDED via
 * REPLACE_FUNC_BODY donor splice; body below is a placeholder. */
void game_libs_func_00070854(int m) {
    volatile int f2l_spliced = 0;
    if (m != 0) {
        f2l_spliced = m;
    }
}

/* game_libs_func_00070954 = guMtxIdentF (libultra gu/mtxutil.c
 * verbatim, IDO 5.3 -O2 single-fn carve-out donor:
 * game_libs_ido53_70954.c). LANDED 2026-08-22 via REPLACE_FUNC_BODY
 * donor splice, 34/34 words exact, ZERO relocs. The old NM wrap had
 * the right loop nesting (runtime inner col so (row==col) can't fold)
 * but 7.1-in-unit regalloc shifted the col-const registers; the IDO
 * 5.3 donor emits the target's a0..a3 consts + bnel pattern natively.
 * (The verbatim source is the if/else diagonal form, not the ternary.)
 * Body below is a placeholder for the splice. */
void game_libs_func_00070954(int m) {
    volatile int identf_spliced = 0;
    if (m != 0) {
        identf_spliced = m;
    }
}

/* 12-insn 2-call wrapper using a 0x40-byte stack buffer (0x30). LANDED
 * fuzzy=100. The 2 trailing stolen-prologue insns for the successor
 * (lui $at,0x3780; mtc1 $at,$f0 — float-constant load) were historically
 * absorbed via SUFFIX_BYTES; mechanism REMOVED 2026-05-23 as match-faking. */
void gl_func_000709DC(int a0) {
    char buf[0x40];
    gl_func_00000000(buf);
    gl_func_00000000(buf, a0);
}

/* gl_func_00070A14 = guMtxL2F (libultra gu/mtxutil.c verbatim, IDO 5.3
 * -O2 single-fn carve-out donor: game_libs_ido53_70A14.c). LANDED
 * 2026-08-22 via REPLACE_FUNC_BODY donor splice, 45/45 words exact,
 * ZERO relocs. The .s block spans 0x70A0C..0x70AC0: the leading
 * lui $at,0x3780 / mtc1 $at,$f0 pair is the FIX32TOF 1/65536.0f
 * constant load and belongs to THIS function, so the old
 * "ARCHITECTURAL CAP caller-set $f0" verdict (and the 3-fn-bundle
 * decode note) are RETRACTED -- the $f0 producer was just across a
 * stale splat boundary. The 4x2 loop recombines 16.16 halves from
 * m (ints) and m+0x20 (fracs) into floats. Body below is a
 * placeholder for the splice. */
void gl_func_00070A14(int m) {
    volatile int l2f_spliced = 0;
    if (m != 0) {
        l2f_spliced = m;
    }
}


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
