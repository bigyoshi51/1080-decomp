#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { float x, y, z; } Vec3;

/* game_libs_func_00073694: same 2-word PI_STATUS_REG load stub as
 * 73074/730C4 (no jr, falls through into the successor's wait loop). */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00073694);

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0007369C)();
s32 gl_func_0007369C(char *arg0, s32 arg1, s32 arg2, s32 arg3) {
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
    *(int*)(FW(arg0, 0xC) | arg1 | 0xA0000000) = arg2;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007369C);
#endif

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
/* gl_func_00073904 = the printf float-formatter _Genld (Plauger libc):
 * lays out the converted mantissa digits + '.' + exponent ('e'/'g'
 * handling, sign, /1000-/100-/10 exponent digits) into the _Pft state
 * (f_8=buffer, f_14=n0, f_18=nz0, f_1C=n1, f_20=nz1, f_24=precision,
 * f_28=width, f_30=flags: 8=ALT, 0x10=left-just) and computes the
 * trailing-pad split. Identified from the full m2c decode (0x30/'0',
 * 0x2E/'.', 0x2B/'+', 0x2D/'-', 0x65/'e' literals + the flag tests).
 * CAP: the original receives its FIVE args in $s0-$s4 (the prologue
 * stores the CALLER's s2/s3/s4 above its own frame, then masks them as
 * s16/s16/u8 values) -- the caller-set s-reg argument class
 * (docs/PATTERNS caller-set regs; same family as the v0/v1/t6 cases).
 * IDO C cannot receive args in s-regs; INCLUDE_ASM is the faithful
 * path. The wrap below is the m2c-derived reference body with the
 * s-regs spelled as normal parameters. Boundary note: this fn ends at
 * 0x73E6C; the ROM's bare jr-ra/nop stub at [0x73E6C..0x73E74) is the
 * dropped symbol behind the drift region (see MATCHING_WORKFLOW). */
typedef struct Pft73904 {
    char _pad0[8];
    char *f_8;          /* 0x08 buffer */
    int f_C;            /* 0x0C prefix len */
    int f_10;           /* 0x10 trailing pad */
    int f_14;           /* 0x14 n0 */
    int f_18;           /* 0x18 nz0 */
    int f_1C;           /* 0x1C n1 */
    int f_20;           /* 0x20 nz1 */
    int f_24;           /* 0x24 precision */
    int f_28;           /* 0x28 width */
    char _pad2C[4];
    int f_30;           /* 0x30 flags */
} Pft73904;

extern void game_libs_func_00073694(char *, char *, int);

#ifdef NON_MATCHING
void gl_func_00073904(Pft73904 *px, char *p, short xexp, short nsig, unsigned char code) {
    s16 xexp_;
    s16 xexp__2;
    s16 nsig_;
    s16 nsig__2;
    s16 nsig__3;
    s16 var_v1;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_v0;
    s32 var_v0_2;
    char *p__2;
    s8 temp_t8_3;
    s8 temp_t8_4;
    s8 temp_v1;
    s8 code_;
    u8 *p_;
    char *temp_s1;
    char *temp_s1_2;

    xexp_ = xexp;
    nsig_ = nsig;
    code_ = code;
    p_ = (u8 *)p;
    if (nsig_ <= 0) {
        p_ = (u8 *)0x2590;
        nsig_ = 1;
    }
    temp_v1 = code_;
    if ((code_ == 0x66) || (((temp_v1 == 0x67) || (temp_v1 == 0x47)) && (xexp_ >= -4) && (xexp_ < px->f_24))) {
        xexp__2 = xexp_ + 1;
        if (temp_v1 != 0x66) {
            var_v0 = px->f_24;
            if (!(px->f_30 & 8) && (nsig_ < var_v0)) {
                px->f_24 = (s32) nsig_;
                var_v0 = (s32) nsig_;
            }
            temp_t8 = var_v0 - xexp__2;
            px->f_24 = temp_t8;
            if (temp_t8 < 0) {
                px->f_24 = 0;
            }
        }
        if (xexp__2 <= 0) {
            var_v1 = -xexp__2;
            *(px->f_8 + px->f_14) = 0x30;
            px->f_14 = (s32) (px->f_14 + 1);
            if ((px->f_24 > 0) || (px->f_30 & 8)) {
                *(px->f_8 + px->f_14) = 0x2E;
                px->f_14 = (s32) (px->f_14 + 1);
            }
            if (px->f_24 < var_v1) {
                xexp__2 = px->f_24 * -1;
                var_v1 = -xexp__2;
            }
            temp_t8_2 = px->f_24 + xexp__2;
            px->f_18 = (s32) var_v1;
            px->f_24 = temp_t8_2;
            if (temp_t8_2 < nsig_) {
                nsig_ = (s16) temp_t8_2;
            }
            px->f_1C = (s32) nsig_;
            game_libs_func_00073694(px->f_8 + px->f_14, p_, (s32) nsig_);
            px->f_20 = (s32) (px->f_24 - nsig_);
        } else if (nsig_ < xexp__2) {
            game_libs_func_00073694(px->f_8 + px->f_14, p_, (s32) nsig_);
            px->f_14 = (s32) (px->f_14 + nsig_);
            px->f_18 = (s32) (xexp__2 - nsig_);
            if ((px->f_24 > 0) || (px->f_30 & 8)) {
                *(px->f_8 + px->f_14) = 0x2E;
                px->f_1C = (s32) (px->f_1C + 1);
            }
            px->f_20 = px->f_24;
        } else {
            game_libs_func_00073694(px->f_8 + px->f_14, p_, (s32) xexp__2);
            px->f_14 = (s32) (px->f_14 + xexp__2);
            nsig__2 = nsig_ - xexp__2;
            if ((px->f_24 > 0) || (px->f_30 & 8)) {
                *(px->f_8 + px->f_14) = 0x2E;
                px->f_14 = (s32) (px->f_14 + 1);
            }
            if ((s16) px->f_24 < nsig__2) {
                nsig__2 = (s16) px->f_24;
            }
            game_libs_func_00073694(px->f_8 + px->f_14, &p_[xexp__2], (s32) nsig__2);
            px->f_14 = (s32) (px->f_14 + nsig__2);
            px->f_18 = (s32) (px->f_24 - nsig__2);
        }
    } else {
        if ((temp_v1 == 0x67) || (temp_v1 == 0x47)) {
            var_v0_2 = px->f_24;
            code_ = 0x45;
            if (nsig_ < var_v0_2) {
                px->f_24 = (s32) nsig_;
                var_v0_2 = (s32) nsig_;
            }
            temp_t7 = var_v0_2 - 1;
            px->f_24 = temp_t7;
            if (temp_t7 < 0) {
                px->f_24 = 0;
            }
            if (temp_v1 == 0x67) {
                code_ = 0x65;
            }
        }
        *(px->f_8 + px->f_14) = *p_;
        px->f_14 = (s32) (px->f_14 + 1);
        if ((px->f_24 > 0) || (px->f_30 & 8)) {
            *(px->f_8 + px->f_14) = 0x2E;
            px->f_14 = (s32) (px->f_14 + 1);
        }
        if ((s16) px->f_24 > 0) {
            nsig__3 = nsig_ - 1;
            if ((s16) px->f_24 < nsig__3) {
                nsig__3 = (s16) px->f_24;
            }
            game_libs_func_00073694(px->f_8 + px->f_14, p_ + 1, (s32) nsig__3);
            px->f_14 = (s32) (px->f_14 + nsig__3);
            px->f_18 = (s32) (px->f_24 - nsig__3);
        }
        temp_s1 = px->f_8 + px->f_14;
        temp_s1_2 = temp_s1 + 1;
        temp_s1_2[-1] = code_;
        if (xexp_ >= 0) {
            temp_s1[1] = 0x2B;
            p__2 = temp_s1_2 + 1;
        } else {
            temp_s1[1] = 0x2D;
            p__2 = temp_s1_2 + 1;
            xexp_ *= -1;
        }
        if (xexp_ >= 0x64) {
            if (xexp_ >= 0x3E8) {
                temp_t8_3 = (xexp_ / 1000) + 0x30;
                xexp_ = (s16) (xexp_ % 1000);
                *p__2 = temp_t8_3;
                p__2 += 1;
            }
            temp_t8_4 = (xexp_ / 100) + 0x30;
            xexp_ = (s16) (xexp_ % 100);
            *p__2 = temp_t8_4;
            p__2 += 1;
        }
        p__2[0] = (xexp_ / 10) + 0x30;
        p__2[1] = (s8) ((s16) (xexp_ % 10) + 0x30);
        px->f_1C = (s32) (((p__2 + 2) - px->f_8) - px->f_14);
    }
    if ((px->f_30 & 0x14) == 0x10) {
        temp_v1_2 = px->f_28;
        temp_v0 = px->f_C + px->f_14 + px->f_18 + px->f_1C + px->f_20;
        if (temp_v0 < temp_v1_2) {
            px->f_10 = (s32) (temp_v1_2 - temp_v0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073904);
#endif

void game_libs_func_00073E6C(void) {}

/* gl_func_00073E74 = the printf float-converter _Ldtob (Plauger libc),
 * sibling of _Genld (73904, see its wrap): IEEE-754 double decompose
 * (exponent (u16&0x7FF0)>>4; 0x7FF => "Inf"/"NaN" strings at data
 * 0x2588/0x258C via the strcpy-helper 73694; mantissa renormalized to
 * 0x3FF0), base-10 exponent estimate via *0x7597/100000 (= log10(2)),
 * scaling by the powers-of-10 table at data 0x2540 in /8-digit chunks,
 * digit generation through a divmod helper (m2c labels it 73694 but
 * that is a placeholder-jal collision -- the real callee differs; the
 * wrap approximates with explicit / and %), leading-zero strip, round-at-'5' with
 * '9'-carry propagation, then the final call to game_libs_func_0007488C
 * -- which is almost certainly the S-REG MARSHALLING THUNK into _Genld
 * (73904 takes its args in $s0-$s4; 7488C is 0x14 = 5 insns, exactly a
 * load-regs-and-jump shim). NORMAL (a0,a1) args -- decompilable, unlike
 * _Genld. Pass 1 (2026-06-10): m2c-derived reference body below; the
 * three bc1f/bc1tl float-compare regions and the negative-index byte
 * scans are hand-patched approximations -- NOT yet shape-tuned. The
 * f64 pow-table chunking loops are faithful. Multi-pass target. */
#ifdef NON_MATCHING
typedef struct Ldt74 {
    short f_0;          /* 0x00 top u16 of the double (exp+mantissa hi) */
    short f_2;
    short f_4;
    short f_6;
    char *f_8;          /* 0x08 out buffer */
    char _padC[8];
    int f_14;           /* 0x14 n0 */
    char _pad18[12];
    int f_24;           /* 0x24 precision */
} Ldt74;
extern double D_73E74_pow10[];   /* data 0x2540: 1e8^(2^k) chunk table */
extern int game_libs_func_00074894();

void gl_func_00073E74(Ldt74 *px, unsigned char code) {
    char buf[0x60];
    char *s;
    double ld;
    short xexp;
    int nsig;
    int n;
    int i;
    int v;

    if (px->f_24 < 0) {
        px->f_24 = 6;
    } else if (px->f_24 == 0 && (code == 'g' || code == 'G')) {
        px->f_24 = 1;
    }
    v = ((unsigned short)px->f_0 & 0x7FF0) >> 4;
    if (v == 0x7FF) {
        xexp = 0;
        if ((px->f_0 & 0xF) || px->f_2 || px->f_4 || px->f_6) {
            n = 2;     /* NaN */
        } else {
            n = 1;     /* Inf */
        }
    } else if (v > 0) {
        px->f_0 = (px->f_0 & 0x800F) | 0x3FF0;
        xexp = v - 0x3FE;
        n = -1;
    } else if (v < 0) {
        n = 2;
    } else {
        n = 0;
        xexp = 0;
    }
    if (n > 0) {
        px->f_14 = 3;
        game_libs_func_00073694(px->f_8, n == 2 ? 0x2588 : 0x258C, 3);
        return;
    }
    if (n == 0) {
        xexp = 0;
    } else {
        ld = *(double *)&px->f_0;
        if (ld < 0.0) {
            ld = -ld;
        }
        xexp = (short)((xexp * 0x7597) / 100000) - 4;
        if (xexp < 0) {
            short e = (short)((3 - xexp) & ~3);
            xexp = -e;
            for (i = 0; e > 0; i++, e >>= 1) {
                if (e & 1) {
                    ld *= D_73E74_pow10[i];
                }
            }
        } else if (xexp > 0) {
            double factor = 1.0;
            short e = xexp & 0xFFFC;
            xexp = e;
            for (i = 0; e > 0; i++, e >>= 1) {
                if (e & 1) {
                    factor *= D_73E74_pow10[i];
                }
            }
            ld /= factor;
        }
        nsig = (code == 'f' ? xexp + 10 : 6) + px->f_24;
        if (nsig >= 0x14) {
            nsig = 0x13;
        }
        buf[0] = '0';
        s = buf + 1;
        if (nsig > 0) {
            /* 8-digit chunks: take (int)ld, emit digits backward */
            int rem = nsig;
            while (rem > 0 && ld != 0.0) {
                int chunk;
                char *w;
                v = (int)ld;
                ld = (ld - v) * 100000000.0;
                w = s + 8;
                for (chunk = 8; chunk > 0 && v > 0; chunk--) {
                    int q;
                    game_libs_func_00073694((char *)&q, (char *)v, 10);
                    q = v % 10; v = v / 10;
                    *--w = (char)('0' + q);
                }
                while (chunk-- > 0) {
                    *--w = '0';
                }
                s += 8;
                rem -= 8;
            }
        }
        /* strip leading zeros */
        n = (int)(s - buf) - 1;
        xexp += 7;
        s = buf + 1;
        while (*s == '0') {
            s++;
            n--;
            xexp--;
        }
        /* rounding at nsig digits */
        nsig = (code == 'f' ? xexp + 1 : (code == 'e' || code == 'E')) + px->f_24;
        if (n < nsig) {
            nsig = n;
        }
        if (nsig > 0) {
            char fill = (nsig < n && s[nsig] >= '5') ? '9' : '0';
            i = nsig - 1;
            while (i >= 0 && s[i] == fill) {
                i--;
            }
            if (fill == '9') {
                s[i] += 1;
            }
            if (i < 0) {
                xexp += 1;
            }
        }
    }
    game_libs_func_00074894();
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073E74);
#endif
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


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000744C4);

#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000744CC);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000744CC_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00074554)();
typedef struct { int unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } Q_00074554;
void gl_func_00074554(char *arg0, s32 arg1) {
    int sp54;
    int sp5C;
    Q_00074554 sp78;
    s32 sp70;
    s32 sp64;
    s32 sp60;
    s32 sp50;
    s32 sp4C;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s0;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t9;
    s32 temp_t9_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_s0;
    s32 var_s3;
    s32 var_t0;
    s32 var_t1;
    u32 temp_v1;
    u64 temp_ret;
    u8 *temp_t7_2;
    u8 temp_t7;

    temp_v0 = arg1 & 0xFF;
    if (temp_v0 == 0x58) {
        var_s3 = 0x2E634;
    } else {
        var_s3 = 0x2E620;
    }
    var_s0 = 0x18;
    if (temp_v0 == 0x6F) {
        var_t1 = 8;
    } else {
        var_t0 = 0x10;
        if ((temp_v0 != 0x78) && (temp_v0 != 0x58)) {
            var_t0 = 0xA;
        }
        var_t1 = var_t0;
    }
    temp_t8 = FW(arg0, 0x0);
    temp_t9 = FW(arg0, 0x4);
    sp60 = temp_t8;
    sp40 = temp_t8;
    sp44 = temp_t9;
    sp64 = temp_t9;
    if (((temp_v0 == 0x64) || (temp_v0 == 0x69)) && (sp40 <= 0)) {
        if (sp40 >= 0) {

        } else {
            temp_t8_2 = ~sp60 + (sp64 == 0);
            sp64 = -sp64;
            sp60 = temp_t8_2;
        }
    }
    if ((sp60 != 0) || (sp64 != 0) || (FW(arg0, 0x24) != 0)) {
        var_s0 = 0x17;
        sp4C = 0x17;
        sp70 = var_t1;
        temp_t7 = *(int*)((u32) game_libs_func_00070FCC(sp60, sp64, var_t1 >> 0x1F, var_t1) + var_s3);
        *(u8 *)((char *)&sp78 + 0x17) = temp_t7;
    }
    sp70 = var_t1;
    temp_ret = game_libs_func_00070FCC(sp60, sp64, var_t1 >> 0x1F, var_t1);
    temp_v0_2 = temp_ret;
    temp_v1 = (u32) temp_ret;
    FW(arg0, 0x4) = (s32) temp_v1;
    FW(arg0, 0x0) = temp_v0_2;
    if ((temp_v0_2 >= 0) && ((temp_v0_2 > 0) || (temp_v1 != 0)) && (var_s0 > 0)) {
        sp3C = var_t1;
        sp38 = var_t1 >> 0x1F;
        sp40 = FW(arg0, 0x0);
        sp44 = FW(arg0, 0x4);
loop_24:
        game_libs_func_00070FCC((s32) &sp50, sp38, sp3C);
        temp_a0 = var_s0 - 1;
        FW(arg0, 0x0) = sp50;
        FW(arg0, 0x4) = sp54;
        temp_t7_2 = &sp78 + temp_a0;
        var_s0 = temp_a0;
        *temp_t7_2 = *(int*)(sp5C + var_s3);
        temp_t8_3 = FW(arg0, 0x0);
        temp_t9_2 = FW(arg0, 0x4);
        sp40 = temp_t8_3;
        sp44 = temp_t9_2;
        if ((temp_t8_3 >= 0) && ((temp_t8_3 > 0) || (temp_t9_2 != 0))) {
            if (var_s0 > 0) {
                goto loop_24;
            }
        }
    }
    temp_a2 = 0x18 - var_s0;
    FW(arg0, 0x14) = temp_a2;
    game_libs_func_00070FCC(FW(arg0, 0x8), (s32) (&sp78 + var_s0), temp_a2);
    temp_a1 = FW(arg0, 0x14);
    temp_a0_2 = FW(arg0, 0x24);
    if (temp_a1 < temp_a0_2) {
        FW(arg0, 0x10) = (s32) (temp_a0_2 - temp_a1);
    }
    if ((temp_a0_2 < 0) && ((FW(arg0, 0x30) & 0x14) == 0x10)) {
        temp_v0_3 = FW(arg0, 0x10);
        temp_s0 = ((FW(arg0, 0x28) - FW(arg0, 0xC)) - temp_v0_3) - temp_a1;
        if (temp_s0 > 0) {
            FW(arg0, 0x10) = (s32) (temp_v0_3 + temp_s0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074554);
#endif
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
