#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { float x, y, z; } Vec3;

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

#ifdef NON_MATCHING
/* gl_func_00073824: 53-insn 8-arg structure initializer + chained registration.
 * Size 0xD4, frame 0x20.
 *
 * Initializes an Obj at `a0` from 7 caller-provided fields (a2/a3 plus 5 stack
 * args at sp+0x30/0x34/0x38/0x3C plus default-fallback args), calls a
 * registration hook, then optionally chains a second hook if the object is the
 * currently-active global.
 *
 * Decoded structure (raw-word disasm):
 *   int init_and_register(Obj *obj, void *_unused_a1, int a2, int a3,
 *                         int arg5, int arg6, int arg7, int arg8) {
 *       obj->[0x0]  = 0;                       // zero head fields
 *       obj->[0x4]  = 0;
 *       obj->[0xC]  = arg6;                    // 6th arg (sp+0x34)
 *       obj->[0x8]  = arg5;                    // 5th arg (sp+0x30)
 *
 *       // Conditional field default: if both a2 and a3 are zero, use arg5/arg6 as fallback
 *       if (a2 != 0) {
 *           obj->[0x10] = a2;
 *           obj->[0x14] = a3;
 *       } else if (a3 != 0) {
 *           obj->[0x10] = a2;                  // = 0
 *           obj->[0x14] = a3;
 *       } else {
 *           obj->[0x10] = arg5;                // fallback to stack-arg defaults
 *           obj->[0x14] = arg6;
 *       }
 *
 *       obj->[0x18] = arg7;                    // 7th arg (sp+0x38)
 *       obj->[0x1C] = arg8;                    // 8th arg (sp+0x3C)
 *
 *       void *result = register_obj(obj);      // jal <func>(obj)
 *
 *       // Chain handler if this is the current global object
 *       if (obj->[0x0] == obj) {               // self-ref test (jal may have set [0])
 *           chain_handler(saved_v0, saved_v1);  // jal <func>
 *       }
 *
 *       return 0;
 *   }
 *
 * Notes:
 *  - The `obj->[0x0] == obj` self-reference check after the jal is unusual:
 *    register_obj() likely populates obj->[0x0] with the back-pointer for
 *    head-tracking. When the back-pointer is self, this object is its own
 *    "head" (i.e., the active one) — fire the chain handler.
 *  - Args 5-8 passed on stack (O32 ABI args 5+ at sp+0x30..0x3C after our
 *    frame adjust).
 *  - The a2/a3 branch is functionally equivalent to "if !(a2==0 && a3==0)
 *    use a2/a3 else use arg5/arg6" but IDO emits a 3-way tree.
 *  - v0:v1 from first jal saved at sp+0x18/0x1C (64-bit-return pair) then
 *    re-loaded as a0/a1 for the chain call.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
extern int gl_func_00000000();
extern long long gl_chain_cb_00073824();   /* 64-bit-return placeholder (field-0 jal) */
extern int D_00000000;
// Zero obj->0/4, store arg5/arg6 to obj->8/0xC, then select the obj->0x10/0x14
// pair: a2/a3 unless both zero (then arg5/arg6). obj->0x18/0x1C = arg7/arg8.
// Register the node via a 64-bit-return chain cb (v0:v1), and if **&D == obj
// (this node is the active head) re-fire the chain handler with that pair.
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
    rr = gl_chain_cb_00073824(obj);
    head = *(char **)(*(char **)&D_00000000);
    if (head == obj) {
        gl_chain_cb_00073824(rr);
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073824);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00073824_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073904);

void game_libs_func_00073E6C(void) {}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073E74);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00073E74_pad.s")

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

#ifdef NON_MATCHING
/* gl_func_000747F4: 19-insn uncached-write helper + 4-stub BUNDLE (0xAC declared,
 * real fn is 19 insns = 0x4C; rest are 4 small leaf utilities).
 *
 * Decoded fn 1 (gl_func_000747F4 proper):
 *   if (func_acquire() != 0) return -1;
 *   *(volatile int*)((uintptr_t)a0 | 0xA0000000) = a1;  // KSEG1 uncached write
 *   return 0;
 *
 * The `lui at, 0xA000; or t8, t7, at` is KSEG0→KSEG1 conversion: forces
 * write to bypass dcache (DMA-buffer poke / hardware register).
 *
 * Bundled siblings @0x4C-0xAC (need fragment-split for byte-exact):
 *   - @0x4C: `*(volatile int*)0xA4040010 = a0;`     // SP_STATUS_REG write
 *   - @0x58: `return *(volatile int*)0xA4040010;`   // SP_STATUS_REG read
 *   - @0x68: icache invalidate 0x80000000..0x80002000 (8KB via `cache 0x01`)
 *   - @0x94: getter — returns *(int*)&D_sym
 *
 * The cache-invalidate loop is the libultra-style `osInvalDCache` / icache
 * primitive — directly invokes `cache 0x01, off(t0)` insn for SI-related
 * hardware operations.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
int gl_func_000747F4(void *a0, int a1) {
    int rc = (int)gl_func_00000000(a0, a1);
    if (rc != 0) return -1;
    *(volatile int*)((unsigned int)a0 | 0xA0000000) = a1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000747F4);
#endif


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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0007488C);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000747F4_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000748A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074AC0);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00074AC0_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern int D_00000000;   // D_a: fixed data arg threaded to the cb (lui+addiu)
extern int D_74C_b;      // D_b: address compared against arg0->0x8
extern int *D_74C_c;     // *&D_c: gate pointer + record (->4)
extern int *D_74C_d;     // *&D_d: peer record stored into (->0x10)
// State-machine step keyed on the u16 arg0->0x10. st==1: if the handle
// arg0->0x8 is null or the sentinel &D_b, demote to 2 and notify(&D_a,arg0);
// else promote to 8, notify(handle,arg0) and notify(&D_a, notify(handle)).
// st==8: demote to 2 + notify(&D_a,arg0). Then a global-record pass: if *&D_c
// is null, notify(); else if (*&D_d)->4 < (*&D_c)->4 demote (*&D_d)->0x10 to 2
// + notify(&D_a). Finally notify(s0) with the saved first-call result. The cb
// (game_libs_func_00070FCC) and &D globals are reloc-blind (field-0 matchable).
// CAP: the target spill-reloads arg0 from its stack home (lw tX, 40(sp)) before
// every field access instead of holding it in a saved reg — that regalloc
// choice (~16 reload insns) can't be forced from C here, so fuzzy stays ~43%
// despite the now-correct structure (halfword fields, &D globals, sentinel ||).
void gl_func_00074C04(char *arg0) {
    char *s0;
    unsigned short st;
    int r;

    s0 = (char *)game_libs_func_00070FCC();
    st = *(unsigned short *)(arg0 + 0x10);
    if (st == 1) {
        char *h = *(char **)(arg0 + 0x8);
        if ((h == 0) || (h == (char *)&D_74C_b)) {
            *(unsigned short *)(arg0 + 0x10) = 2;
            game_libs_func_00070FCC((char *)&D_00000000, arg0);
        } else {
            *(unsigned short *)(arg0 + 0x10) = 8;
            game_libs_func_00070FCC(*(char **)(arg0 + 0x8), arg0);
            r = game_libs_func_00070FCC(*(char **)(arg0 + 0x8));
            game_libs_func_00070FCC((char *)&D_00000000, r);
        }
    } else if (st == 8) {
        *(unsigned short *)(arg0 + 0x10) = 2;
        game_libs_func_00070FCC((char *)&D_00000000, arg0);
    }
    if (D_74C_c == 0) {
        game_libs_func_00070FCC();
    } else {
        if (D_74C_d[1] < D_74C_c[1]) {
            *(unsigned short *)((char *)D_74C_d + 0x10) = 2;
            game_libs_func_00070FCC((char *)&D_00000000);
        }
    }
    game_libs_func_00070FCC(s0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074C04);
#endif

#ifdef NON_MATCHING
/* gl_func_00074D54: 22-insn float-arg + global-state wrapper.
 *   rv = func_a(f);            // jal#1 takes float
 *   g->[0x24] = f;              // store f as float
 *   *(short*)g |= 4;            // bit-set in halfword
 *   return func_b(rv);          // jal#2 takes int
 *
 * 2026-05-15 — applied unique-extern recipe (gl_data_00074_a and
 * gl_data_00074_b separate symbols added to undefined_syms_auto.txt) to
 * break IDO's CSE on the duplicate `lui+lw 0(*)` pair. Plus `register`
 * hint on rv. Result: 19/22 insns (still 3 short). Target uses $s0 for
 * rv across the FPU work; IDO sees rv's only post-jal use is the next
 * jal (immediate tail-call style) and keeps it in $v0 → no $s0 save.
 * The "rv needs $s0" can't be forced without an artificial extra use
 * that would add MORE insns. Cap holds at the documented 67-86% range. */
extern int gl_data_00074_a;
extern int gl_data_00074_b;
int gl_func_00074D54(int a0, float arg1) {
    int rv = gl_func_00000000(a0);
    *(float*)((char*)gl_data_00074_a + 0x24) = arg1;
    *(short*)gl_data_00074_b |= 4;
    return gl_func_00000000(rv);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074D54);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00074D54_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074DB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074EDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074EFC);

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0007507C)();
void gl_func_0007507C(char *arg0) {
    char *sp34;
    char *sp30;
    u16 *sp2C;
    s32 sp28;
    char *sp24;
    s32 temp_t6;
    u16 temp_s0;
    u16 temp_t3;
    u16 temp_t7;
    char *temp_t3_2;
    char *temp_t5;
    char *temp_t8;

    sp2C = 0;
    sp28 = 0;
    sp34 = game_libs_func_00070FCC();
    temp_t7 = FW(sp34, 0x2);
    *(u16 *)0x45290 = temp_t7;
    if (temp_t7 == 0) {
        *(char *)0x45290 = 1U;
    }
    sp30 = arg0;
loop_3:
    game_libs_func_00070FCC(FW(sp30, 0xC), &sp2C, 1);
    temp_s0 = *(int*)sp2C;
    if (temp_s0 == 0xD) {
        game_libs_func_00070FCC();
        temp_t3 = *(char *)0x45290 - 1;
        *(char *)0x45290 = temp_t3;
        if (!(temp_t3 & 0xFFFF)) {
            sp34 = game_libs_func_00070FCC();
            temp_t6 = FW(sp34, 0x10);
            if (temp_t6 != 0) {
                game_libs_func_00070FCC(temp_t6, FW(sp34, 0x14), 0);
            }
            *(char *)0x45290 = (u16) FW(sp34, 0x2);
        }
        *(int*)0 = (char *) (*(int*)0 + 1);
        if (sp28 != 0) {
            sp24 = game_libs_func_00070FCC();
            *(int*)0 = 0;
            *(char **)4 = sp24;
            sp28 = 0;
        }
        sp24 = *(int*)0;
        *(int*)0 = game_libs_func_00070FCC();
        temp_t3_2 = *(char *)4;
        temp_t8 = *(int*)0 - (int)sp24;
        temp_t5 = temp_t8 + (int)temp_t3_2;
        *(int*)0 = (char *) (((u32) temp_t5 < (u32) temp_t3_2) + *(int*)0);
        sp24 = temp_t8;
        *(char *)4 = temp_t5;
        goto loop_3;
    }
    if (temp_s0 != 0xE) {
        goto loop_3;
    }
    game_libs_func_00070FCC();
    goto loop_3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007507C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00075248);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00075260);

#ifdef NON_MATCHING
/* SP_PC_REG (uncached, 0xA4080000) conditional writer.
 *   if ((flag & 1) != 0) { *(volatile u32*)0xA4080000 = pc; return 0; }
 *   else { return -1; }
 *
 * 11-insn target with `addiu sp, -8` + matching `addiu sp, sp, 8` at the
 * very end — fake stack frame even though no body uses it. Per
 * feedback_ido_sp_frame_without_stack_use.md: IDO -O2 won't allocate a
 * frame from standard C unless something actually touches the stack.
 *   - With body alone: 9 insns, no frame (mismatch).
 *   - With `volatile int x = 0;` to force a slot: 11 insns + frame BUT also
 *     emits `sw zero, 4(sp)` in the delay slot AND shifts $tN registers up
 *     by 1 (target uses t7/t8; mine t6/t7). Mismatch.
 *
 * Cap: ~85 % via the volatile-int form. Real fix needs a way to allocate
 * frame without stack use — which IDO doesn't expose.
 *
 * 2026-05-30 — DUAL-ENTRY context: the predecessor orphan game_libs_func_00075260
 * (`nop; lui t6,0xA404; lw a1,0x10(t6)`, no jr ra) loads this body's `flag` (a1)
 * from the RSP register 0xA4040010 (SP_STATUS read), then falls through. So the fn
 * is an RSP-poll: entered via 0x75260, flag = SP_STATUS; entered directly here,
 * flag = caller's. NOT an orphan-merge candidate — (a) dual-entry (body callable
 * with caller flag), and (b) the merged single-entry C reads SP_STATUS into $v0 and
 * emits a different leaf shape (no frame), so it can't reproduce the body's frame.
 * The hw write target 0xA4080000 = SP_PC_REG (RSP program counter). Both INCLUDE_ASM. */
int gl_func_0007526C(unsigned int pc, int flag) {
    volatile int x = 0;
    if ((flag & 1) == 0) {
        return -1;
    }
    *(volatile unsigned int*)0xA4080000 = pc;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007526C);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0007526C_pad.s")
#endif
