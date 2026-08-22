#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { float x, y, z; } Vec3;

/* gl_func_0007369C = libultra osEPiRawWriteIo (epirawwrite.c verbatim,
 * EPI_SYNC/UPDATE_REG piint.h macros): PI busy-wait, per-domain BSD
 * timing-reg update vs __osCurrentHandle[domain], then
 * IO_WRITE(baseAddress | devAddr, data). Sibling of osEPiRawReadIo =
 * gl_func_000730CC. BOUNDARY FIX: the 2-word orphan
 * game_libs_func_00073694 (lui/lw PI_STATUS_REG) was this function's
 * hoisted first status read scheduled before the addiu-sp prologue by
 * IDO 5.3; its INCLUDE_ASM was removed and the spliced symbol covers
 * 0x73694..0x73824. (The _Genld NM bodies below still call the old
 * game_libs_func_00073694 name from their blank-jal decode guesses --
 * extern-only, NON_MATCHING path, revisit when those are decoded.)
 * WIRED 2026-07-10 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_7369C.c (100/100). Body
 * below is a placeholder for the splice. */
int gl_func_0007369C(char *pihandle, unsigned int devAddr, unsigned int data) {
    volatile int ret = 0;
    if (pihandle == 0) {
        ret = -1;
    }
    return ret;
}

/* gl_func_00073824: 53-insn 8-word record init + u64-return call +
 * conditional u64-arg call (frame 0x20, saves ra).
 * LANDED 2026-07-09 via REPLACE_FUNC_BODY donor splice: the target is plain
 * IDO 7.1 -O1 with a (int*, u64, u64, int, int) signature — the u64 params
 * explain the "a2/a3 3-way tree" and the missing sw a1 home. Real C lives
 * in the -O1 donor unit game_libs_o1_73824.c (53/53), spliced over this
 * -O2 stand-in. Body below is a placeholder for the splice (its bytes are
 * replaced by the donor). */
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_00073824(char *obj, int a1, int a2, int a3, int arg5, int arg6, int arg7, int arg8) {
    long long rr;
    char *head;
    *(int *)(obj + 0x0) = 0;
    *(int *)(obj + 0x4) = 0;
    *(int *)(obj + 0xC) = arg6;
    *(int *)(obj + 0x8) = arg5;
    if (a2 != 0 || a3 != 0) {
        *(int *)(obj + 0x10) = a2;
        *(int *)(obj + 0x14) = a3;
    } else {
        *(int *)(obj + 0x10) = arg5;
        *(int *)(obj + 0x14) = arg6;
    }
    *(int *)(obj + 0x18) = arg7;
    *(int *)(obj + 0x1C) = arg8;
    rr = gl_func_00000000(obj);
    head = *(char **)(*(char **)&D_00000000);
    if (head == obj) {
        gl_func_00000000((int)rr);
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00073824_pad.s")

/* DRIFT ROOT CAUSE (2026-06-10): ROM has a bare jr-ra/nop stub at
 * [0x73E6C..0x73E74) that splat's 0x568 size for THIS symbol drops --
 * the source of the whole [0x743C4..0x748A0] -4 content drift. The
 * naive fix (append 2 words, size 0x570) overshoots (+8 downstream) due
 * to hidden inter-block alignment in the unit; needs an alignment-aware
 * relayout of [0x73904..0x748A4) in one focused pass. See
 * docs/MATCHING_WORKFLOW "drift-region root cause FOUND". */
/* gl_func_00073904 = _Genld (Plauger libc xldtob.c verbatim) -- the
 * printf float-formatter. LANDED 2026-08-22 via REPLACE_FUNC_BODY donor
 * splice: real C lives in the IDO 5.3 -O3 donor unit
 * game_libs_ido53_73904.c (346/346 raw words spliced; the donor TU also
 * reproduces the [0x73E6C,0x73E74) jr-ra tail word-exact, which stays
 * the separate game_libs_func_00073E6C def below.
 * The only non-zero reloc imm is the "0" string %lo,
 * .rodata base pinned 0x2540). The old "caller-set s-reg argument cap"
 * was the -O3 WHOLE-TU custom linkage: _Genld is static in xldtob.c and
 * IDO -O3 interprocedural regalloc passes its five args in $s0-$s4
 * (px, p, xexp, nsig, code) -- no per-function compile can emit that;
 * the -O3 TU donor does. Body below is a placeholder for the splice. */
void gl_func_00073904(void *px, char *p, int xexp, int nsig, int code) {
    volatile int genld_spliced = 0;
    if (code != 0) {
        genld_spliced = nsig + xexp;
    }
}

void game_libs_func_00073E6C(void) {}

/* gl_func_00073E74 = _Ldtob (Plauger libc xldtob.c verbatim) -- the
 * printf float-converter, sibling of _Genld/73904. LANDED 2026-08-22
 * from the same IDO 5.3 -O3 donor unit game_libs_ido53_73904.c
 * (340/340 raw words): at -O3 the static _Ldunscale is integrated into
 * _Ldtob (the old 74.0% "_Ldunscale-family classifier" redecode was
 * exactly that inlined classifier head), and the final call is the
 * s-reg-linkage jal to _Genld (target bakes jal 0x87F70 = the USO's
 * original-link _Genld address; donor's local .text reloc renamed
 * gl_func_00073E74_text by the splice, pinned 0x87F70). Blank jals:
 * memcpy x1 + ldiv (= gl_func_000744CC identity, "a divmod helper" as
 * the old wrap guessed). .rodata pins: pows[] table @0x2540, "Inf"
 * 0x2588 / "NaN" 0x258C / 1.0e8 @0x2598 (base 0x2540).
 * Body below is a placeholder for the splice. */
void gl_func_00073E74(void *px, int code) {
    volatile int ldtob_spliced = 0;
    if (code != 0) {
        ldtob_spliced = code;
    }
}
/* 743C0 pad word merged into gl_func_00073E74.s tail (1-word GLOBAL_ASM
 * blocks emit 2 words — asm-processor 8-byte placeholder minimum — which
 * shifted links 743C4..748A0 +4; the trailing 747F4_pad then got clipped
 * by TRUNCATE_TEXT 0x1210). */

#ifdef NON_MATCHING
/* gl_func_000743C4: 66-insn 64-bit-arithmetic timestamp/range helper (size 0x108, frame 0x30).
 *
 * Computes a 64-bit subtraction across two function-returned values, optionally
 * applies a wrap correction, and stores 4 32-bit fields to an output Obj.
 *
 * Decoded structure (raw-word disasm):
 *   void compute_delta(int *out_obj, [a0 = destination]
 *                      int unused_a1,
 *                      uint32_t a_hi, uint32_t a_lo,  // a2:a3 = first 64-bit operand
 *                      uint32_t b_hi, uint32_t b_lo,  // sp+0x40:0x44 = second
 *                      uint32_t c_hi, uint32_t c_lo)  // sp+0x48:0x4C = third? (read later)
 *   {
 *       // STAGE 1: jal #1 (a2, a3, sp_arg40_lo, sp_arg44_hi)
 *       int64_t r1 = func1(a_hi, a_lo, sp_arg44, sp_arg40);
 *
 *       // STAGE 2: jal #2 (sp_arg40, sp_arg44, r1_v0, r1_v1) — chain
 *       int64_t r2 = func2(sp_arg40, sp_arg44, r1.lo, r1.hi);
 *
 *       // STAGE 3: 64-bit subtract  diff = saved_a2:a3 - r2_v0:v1
 *       uint64_t diff = ((uint64_t)saved_a2 << 32 | saved_a3) -
 *                       ((uint64_t)r2.hi    << 32 | r2.lo);
 *       int32_t  d_hi = (int32_t)(diff >> 32);
 *       uint32_t d_lo = (uint32_t)diff;
 *
 *       // STAGE 4: range adjustment based on sign of d_hi
 *       if (d_hi > 0) {
 *           // positive: use diff as-is
 *       } else if (d_hi < 0) {
 *           // negative: subtract sp_arg40:sp_arg44 from diff (wrap correction)
 *           int64_t adj = (uint64_t)d_hi << 32 | d_lo;
 *           adj -= ((uint64_t)sp_arg40 << 32 | sp_arg44);
 *           d_hi = (int32_t)(adj >> 32);
 *           d_lo = (uint32_t)adj;
 *           // r1 also adjusted: r1.lo++; r1.hi += (r1.lo == 0 ? 1 : 0)  (saturating)
 *       }
 *       // (d_hi == 0: use diff as-is, no adjust)
 *
 *       // STAGE 5: store 4 fields to out_obj
 *       *(int*)(out_obj + 0x0) = r1.hi;
 *       *(int*)(out_obj + 0x4) = r1.lo;
 *       *(int*)(out_obj + 0x8) = d_hi;
 *       *(int*)(out_obj + 0xC) = d_lo;
 *   }
 *
 * Notes:
 *  - Uses standard 64-bit subtract sequence:
 *      subu $hi_diff, $hi_a, $hi_b
 *      sltu $borrow, $lo_a, $lo_b
 *      subu $hi_diff, $hi_diff, $borrow
 *      subu $lo_diff, $lo_a, $lo_b
 *  - The bltzl branch-likely after bgtz/bltz forms a 3-way dispatch on signed
 *    64-bit comparison (positive / negative / zero).
 *  - 4-field store is the canonical "save 64-bit timestamp pair + 64-bit delta"
 *    pattern. Likely tracks elapsed-time / lap-time / frame-counter delta.
 *  - Trailing 2-insn fragment (`mult $a1, $a2; mflo $v0`) past epilogue —
 *    likely incomplete next function fragment. Variant of
 *    feedback_splat_too_big_incomplete_fragment_tail.md.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md.
 *
 * 2026-05-28: converted the comment-only bail into a real C body, 54.77%
 * (mnemonic disasm confirms the structure). KEY 64-bit-on-mips2 finding:
 * extracting hi/lo from a long-long call return via `(int)(r>>32)` compiles to
 * a CALL to a 64-bit-shift runtime helper (huge bloat: 0x214). Use the UNION
 * idiom instead — `union{long long ll; struct{int hi,lo;} w;}` — which stores
 * v0:v1 to the stack and reads the words back, exactly matching the target's
 * `sw v0,32(sp); sw v1,36(sp); lw ...` roundtrip (got 40%→55%). All 64-bit
 * arithmetic is manual int hi/lo (subu/sltu/subu), NOT long-long ops.
 * RESIDUAL (~45%, multi-tick): (a) frame 0x40 vs 0x30 — the two union temps
 * use extra stack; the target reuses ONE result area (sp+0x20..0x2C) that the
 * call result stores into DIRECTLY (needs aliasing result[0..1] with the call
 * return). (b) the result→out_obj copy: target uses a t0=&sp[0x20] pointer
 * loop, mine does indexed loads. (c) dispatch-branch ordering. Real wrap now
 * (compilable / permuter-able / correct logic), not a comment bail. */
/* long-long-returning view of the jal-0 placeholder (returns 64-bit in v0:v1).
 * Used ONLY to capture the pair; all arithmetic is manual int hi/lo to emit the
 * target's subu/sltu/subu (long-long shifts emulate to bloated/MIPS3 ops on -mips2). */
extern long long gl_ret64_743C4();
typedef union { long long ll; struct { int hi; int lo; } w; } Pair64;
void gl_func_000743C4(int *out_obj, int a1, int a2, int a3, int b_hi, int b_lo) {
    int result[4];
    Pair64 r1, r2;
    int r1_hi, r1_lo, r2_hi, r2_lo;
    int diff_hi, diff_lo;

    r1.ll = gl_ret64_743C4(a2, a3, b_hi, b_lo);
    r1_hi = r1.w.hi;
    r1_lo = r1.w.lo;
    r2.ll = gl_ret64_743C4(b_hi, b_lo, r1_lo, r1_hi);
    r2_hi = r2.w.hi;
    r2_lo = r2.w.lo;

    /* diff = {a2:a3} - {r2_hi:r2_lo}  (manual 64-bit subtract) */
    diff_hi = a2 - r2_hi - ((unsigned int)a3 < (unsigned int)r2_lo);
    diff_lo = a3 - r2_lo;

    result[0] = r1_hi;
    result[1] = r1_lo;
    result[2] = diff_hi;
    result[3] = diff_lo;

    if (r1_hi < 0) {
        if (diff_hi > 0 || (diff_hi == 0 && diff_lo != 0)) {
            /* saturating-increment r1 */
            int nlo = r1_lo + 1;
            int nhi = r1_hi + (nlo == 0);
            /* diff -= {b_hi:b_lo} */
            int nd_hi = diff_hi - b_hi - ((unsigned int)diff_lo < (unsigned int)b_lo);
            int nd_lo = diff_lo - b_lo;
            result[0] = nhi;
            result[1] = nlo;
            result[2] = nd_hi;
            result[3] = nd_lo;
        }
    }

    out_obj[0] = result[0];
    out_obj[1] = result[1];
    out_obj[2] = result[2];
    out_obj[3] = result[3];
    (void)a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000743C4);
#endif


/* game_libs_func_000744C4 (0x8 orphan, no jr ra: div/mflo) was the HOISTED
 * HEAD of gl_func_000744CC = ldiv — absorbed into the donor splice below
 * (true entry 0x744C4, spliced symbol covers 0x744C4..0x74548). */

#if 0
/* SUPERSEDED DECODE (2026-07-18): the "caller-set $v0 quotient guess"
 * reading below was wrong — $v0 is the quotient computed by the stolen
 * pre-prologue `div $zero,$a1,$a2; mflo $v0` head (splat orphan
 * game_libs_func_000744C4). Real identity: libc ldiv (o32 struct return,
 * $a0 = sret ptr). See the donor unit game_libs_ido53_744C4.c. */
/* gl_func_000744CC: 31-insn divide-correction helper w/ IDO trap prologue (0x7C, frame 0x08).
 *
 * Decoded structure (raw-word disasm) — division codegen idioms:
 *
 *   if (a2 == 0)                          break 0x1C0;   // div-by-zero
 *   if (a2 == -1 && a1 == 0x80000000)     break 0x180;   // overflow (INT_MIN/-1)
 *
 *   // Refinement body — assumes $v0 holds a caller-pre-computed quotient guess:
 *   prod_lo = (a2 * v0).lo;            // multu $a2, $v0; mflo
 *   rem = a1 - prod_lo;
 *   if (rem < 0) { v0++; rem -= a2; }  // sign-correction step
 *   a0[0] = v0;                        // write quotient
 *   a0[1] = rem;                       // write remainder
 *   return a0;                         // ($v0 = a0 at epilogue)
 *
 * The break codes 0x180/0x1C0 are IDO's standard div-trap signatures —
 * this is IDO `div` codegen output, not a hand-rolled libgcc helper.
 * The CURIOSITY is `multu $a2, $v0` with $v0 caller-set: $v0 is not a
 * standard arg register, so this is either (a) a custom intra-USO
 * calling convention (a la float-in-$f4/$f6/$f0), or (b) the result of
 * a fall-through from another function that set v0.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-18 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path (the
 * `multu $a2, $v0` w/ caller-set v0 is unreproducible from standard C).
 */
void gl_func_000744CC(int *a0_out, int a1_dividend_lo, int a2_divisor) {
    /* Custom-convention divide-correction helper. Real C below shows shape;
     * cannot byte-match due to caller-set $v0_guess. */
    extern int v0_caller_guess;
    int v0 = v0_caller_guess;
    int prod_lo, rem;
    if (a2_divisor == 0) __builtin_trap();
    if (a2_divisor == -1 && a1_dividend_lo == (int)0x80000000) __builtin_trap();
    prod_lo = (int)((unsigned)a2_divisor * (unsigned)v0);
    rem = a1_dividend_lo - prod_lo;
    if (rem < 0) {
        v0++;
        rem -= a2_divisor;
    }
    a0_out[0] = v0;
    a0_out[1] = rem;
}
#endif

/* gl_func_000744CC = libc ldiv (xldiv.c verbatim): quot = numer/denom
 * (the div/mflo hoisted above the prologue = the absorbed 0x8 orphan),
 * rem = numer - denom*quot, then the C-rounding fixup
 * (quot<0 && rem>0 => quot++, rem-=denom), returned as an o32 sret
 * struct {quot, rem} through $a0. Needs IDO 5.3 -O2 (7.1 -O2 picks
 * $t9/$t8 for the sret copy instead of the target's $at/$t0), so the
 * real C lives in the donor unit game_libs_ido53_744C4.c (33/33 exact,
 * zero relocs). Body below is a placeholder for the REPLACE_FUNC_BODY
 * splice (its bytes are replaced by the donor). */
void gl_func_000744CC(void) {
    volatile int i;
    for (i = 0; i < 15; i++) {}
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000744CC_pad.s")

/* gl_func_00074554 = _Litob (Plauger libc xlitob.c verbatim) -- the
 * printf integer-formatter, completing the printf-machinery vein
 * (73904=_Genld, 73E74=_Ldtob, 744CC=ldiv). LANDED 2026-08-22 via
 * REPLACE_FUNC_BODY donor splice: real C in the IDO 5.3 -O2 donor unit
 * game_libs_ido53_74554.c (166/166 raw words; 7.1 -O2 diverges 77
 * words). ldigs/udigs .data base pinned 0x2E620
 * (gl_func_00074554_data); blank jals __ull_rem/__ull_div (objcopy
 * -redefined; USO load-time relocs point them at the game_libs copies
 * 6C740/6C77C), lldiv, memcpy. Body below is a placeholder for the
 * splice. */
void gl_func_00074554(void *args, int type) {
    volatile int litob_spliced = 0;
    if (type != 0) {
        litob_spliced = type;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00074554_pad.s")

/* gl_func_000747F4 = libultra __osPiRawWriteIo. LANDED 2026-06-21 as a
 * byte-identical TWIN-PORT of matched kernel func_80009C40 (kernel_046) -- the
 * write twin of the landed __osPiRawReadIo at gl_func_0006CCD4: PI-busy probe
 * (no-arg call), then uncached KSEG1 write of data to (devAddr | 0xA0000000).
 * The prior wrap guessed a 2-arg acquire call + a 4-stub bundle; it is a single
 * 19-insn fn. Real C lives in the donor unit game_libs_ido53_747F4.c (IDO 5.3
 * -O1), spliced via REPLACE_FUNC_BODY. Busy probe -> gl_func_00000000. */
int gl_func_000747F4(int devAddr, int data) {
    if (gl_func_00000000() != 0) {
        return -1;
    }
    *(volatile int *)(0xA0000000 | devAddr) = data;
    return 0;
}


/* game_libs_func_00074840 (0x10): RSP SP_STATUS (0xA4040010) WRITE accessor.
 * Body: `nop; lui t6,0xA404; jr ra; sw a0,0x10(t6)` = `*(volatile int*)0xA4040010 = a0`.
 * game_libs_func_00074850 (below) is the matching READ. CAP — the LEADING NOP is not
 * C-reproducible: a hardware-access hazard idiom (nop before the SP register touch).
 * Plain C `*(volatile int*)0xA4040010 = a0;` emits `lui t6; jr ra; sw a0,0x10(t6)` (no
 * leading nop). IDO has no inline-asm to inject a bare nop: `__asm__("nop")` compiles
 * to a JAL to a symbol `nop` (not an emitted nop), and `__asm__ volatile(...)` is a cfe
 * syntax error (feedback_ido_no_gcc_register_asm). Same leading-nop cap class as the VI
 * accessors (00069F50 etc.). Stays INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074840);

/* game_libs_func_00074850 (0x10): RSP SP_STATUS (0xA4040010) READ accessor (pair of
 * 00074840). Body: `nop; lui v0,0xA404; jr ra; lw v0,0x10(v0)` = `return
 * *(volatile int*)0xA4040010`. Same leading-nop hardware-hazard CAP — see 00074840. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074850);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074860);

/* 7488C decomposed 2026-06-10 (drift region realigned by the relayout,
 * unblocking the deferred match): 2 inter-fn pad words (orphan block)
 * + the standard collapsed int-reader at 0x74894 (lui/jr/lw with hi/lo
 * relocs; ROM stores the unrelocated zeros, D_00000000 at VRAM 0
 * resolves identically). */
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/_pad_pre_74894.s")
int game_libs_func_00074894(void) {
    return D_00000000;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000747F4_pad.s")
