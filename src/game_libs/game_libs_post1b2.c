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


/* gl_func_0006BE14: stores 1 to D_00000000, then gl_func(<sym_b>, &D+0x42800, 1)
 * and gl_func(<sym_c>, 0, 0). MATCH: the 0x42800 arg is a SYMBOL reference
 * (&D_00000000 + 0x42800 -> lui 0x4; addiu 0x2800), not a literal (which gives
 * lui; ori). Decode the symbol, don't literal-match
 * (docs/IDO_CODEGEN.md#feedback-return-const-lui-addiu-vs-lui-ori). Real size
 * 0x50 (the .s's 0x58 over-extends 2 insns into successor 0006BE64). Byte-exact. */
extern char gl_data_BE14_b;
extern char gl_data_BE14_c;
void gl_func_0006BE14(void) {
    *(int*)&D_00000000 = 1;
    gl_func_00000000(&gl_data_BE14_b, (char*)&D_00000000 + 0x42800, 1);
    gl_func_00000000(&gl_data_BE14_c, 0, 0);
}
/* game_libs_func_0006BE64 (2-word splat mis-split: lui t6,0; lw t6,0(t6)) was
 * the stolen prologue of gl_func_0006BE6C — forward-merged into it (orphan-fn
 * removed). gl_func_0006BE6C MATCHED. */
void gl_func_0006BE6C(void) {
    int local;
    int pad;
    if (*(int*)&D_00000000 == 0) {
        gl_func_00000000();
    }
    gl_func_00000000(&D_00000000, &local, 1);
}

void gl_func_0006BEA8(void) {
    gl_func_00000000(&D_00000000, 0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006BEA8_pad.s")

/*
 * gl_func_0006BF34: 81-insn struct-init constructor.
 *   Args: (T *self, int a1, int a2, int a3, int arg5, int arg6)
 *     - arg5 / arg6 are stack-passed (sp+0x3C / sp+0x38 from caller).
 *   Field writes (offsets relative to a0):
 *     +0x00 = 0          +0x04 = arg5         +0x08 = 0
 *     +0x0C = D_NNNN_a   +0x10 = (s16) 1      +0x12 = (s16) 0
 *     +0x14 = a1         +0x18 = 0
 *     +0x38/+0x3C = (long long) a3
 *     +0xF0/+0xF4 = (long long)(arg6 - 16)
 *     +0x100/+0x104 = (long long)(int) &D_NNNN
 *     +0x118 = 0xFF03    +0x11C = a2
 *     +0x128 = 0x3F      +0x12C = 0x01000800
 *   Then: v0 = gl_func_00000000(); a0->0xC = D_NNNN_a; D_NNNN_b = a0;
 *         gl_func_00000000(v0);
 *   Open: the 0x3F at +0x128 is computed via spill+and+srl of constant
 *   0x003FFF01 (lui 0x3F + ori 0xFF01); looks like a bit-field extract.
 */
#ifdef NON_MATCHING
extern int D_00000000;
void gl_func_0006BF34(int *a0, int a1, int a2, int a3, int arg5, int arg6) {
    int *volatile self = a0;                        /* force reload of base each write */
    int v0_save;
    int x = 0x3FFF01;
    *(int*)((char*)self + 0x14) = a1;
    *(int*)((char*)self + 0x4) = arg5;
    *(int*)((char*)self + 0x0) = 0;
    *(int*)((char*)self + 0x8) = 0;
    *(int*)((char*)self + 0x11C) = a2;
    *(long long*)((char*)self + 0x38) = (long long)a3;
    *(long long*)((char*)self + 0xF0) = (long long)(arg6 - 16);
    *(long long*)((char*)self + 0x100) = (long long)(int)&D_00000000;
    *(int*)((char*)self + 0x118) = 0xFF03;
    *(int*)((char*)self + 0x128) = (x & 0x3F0000) >> 16;
    *(int*)((char*)self + 0x12C) = 0x01000800;
    *(int*)((char*)self + 0x18) = 0;
    *(short*)((char*)self + 0x10) = 1;
    *(short*)((char*)self + 0x12) = 0;
    v0_save = gl_func_00000000();
    *(int*)((char*)self + 0xC) = D_00000000;
    D_00000000 = (int)self;
    gl_func_00000000(v0_save);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BF34);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006BF34_pad.s")
#endif

#ifdef NON_MATCHING
/* gl_func_0006C084: 38-insn one-time init w/ guarded heavy path (0x98, frame 0x20).
 *
 * Decoded structure (expected .o disasm):
 *   func1(a0); v0_ret = 0;                            // sw zero,28(sp) in delay
 *   if (D_lock_flag != 1) {
 *       gl_ref_00080824();                            // direct hardcoded jal 0x80824
 *       v0_ret = func3(1, &D_sym1);                   // sw v0,28(sp)
 *       func4(a0, 0, 1);                              // 3-arg, result discarded
 *   }
 *   v0_ret = func5(0, &D_sym2);                       // sw v0,28(sp)
 *   func6();                                          // result discarded
 *   D_lock_flag = 1;                                  // sb 1 to lock
 *   return v0_ret;                                    // via sp+0x1C
 *
 * `jal 0x80824` (0x0c020209) is a direct hardcoded jal-to-absolute, modeled
 * with the gl_ref recipe (needs `gl_ref_00080824 = 0x00080824;` in
 * undefined_syms_auto.txt) so it emits a direct jal, not a fn-ptr-cast
 * lui/ori/jalr triple.
 *
 * v0_ret is `volatile int` so each assignment is a genuine sp+0x1C store
 * (matches target's per-call spill of the return slot); a plain int lets IDO
 * coalesce and drop the zero-init + func3-result stores.
 *
 * Residual (70.69% fuzzy): tail func5-store / func6-call / lock-store
 * scheduling order is pure IDO instruction scheduling. INCLUDE_ASM remains
 * build path (game_libs baked-reloc, can't byte-LAND).
 */
extern int gl_ref_00080824();
int gl_func_0006C084(int a0) {
    extern char D_lock_flag;
    extern int D_sym1, D_sym2;
    volatile int v0_ret;
    gl_func_00000000(a0);
    v0_ret = 0;
    if (D_lock_flag != 1) {
        gl_ref_00080824();
        v0_ret = (int)gl_func_00000000(1, &D_sym1);
        gl_func_00000000(a0, 0, 1);
    }
    v0_ret = (int)gl_func_00000000(0, &D_sym2);
    gl_func_00000000();
    D_lock_flag = 1;
    return v0_ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C084);
#endif


/* gl_func_0006C11C: 8-byte-record decoder loop (42 insns incl. the absorbed
 * 3-word orphan game_libs_func_0006C110 — its lui/lbu count-preload pair is
 * this function's stolen prologue, so the donor's true entry is 0x6C110 and
 * the spliced symbol covers 0x6C110..0x6C1B8; the orphan INCLUDE_ASM was
 * removed here). For each record: out[4] = (rec[2]&0xC0)>>4; if 0, copy
 * u16/byte fields; out += 6, cursor += 8, count reloaded per iteration.
 * LANDED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in the
 * IDO 5.3 -O1 donor unit game_libs_ido53_6C11C.c (42/42 — 5.3 colors the
 * lwl/lwr struct-copy scratch $at; 7.1 uses $t1/$t0), spliced over this -O2
 * stand-in. Body below is a placeholder for the splice (its bytes are
 * replaced by the donor). */
void gl_func_0006C11C(char *out, char *cursor, int count) {
    unsigned char rec[8];
    volatile int i;
    volatile char *cur = cursor;
    if (count > 0) {
        i = 0;
        do {
            *(int *)rec = *(int *)cur;
            *(int *)(rec + 4) = *(int *)(cur + 4);
            *(char *)(out + 4) = (rec[2] & 0xC0) >> 4;
            if (*(unsigned char *)(out + 4) == 0) {
                *(short *)(out + 0) = *(unsigned short *)(rec + 4);
                *(char *)(out + 2) = rec[6];
                *(char *)(out + 3) = rec[7];
            }
            out += 6;
            cur += 8;
            i++;
        } while (i < 1);
    }
}

#ifdef NON_MATCHING
/* gl_func_0006C1B8: 61-insn reset-sibling of gl_func_0006BD14 (size 0xF4, frame 0x10).
 *
 * SAME STRUCTURE as gl_func_0006BD14:
 *   1. 15-iter loop clears 60-byte table at D+0..D+0x38
 *   2. Reads D+0 byte (now 0) for emit-skip gate
 *   3. Sets D+0x3C = 1 (active flag)
 *   4. Builds 8-byte template buf
 *   5. Emit-record loop GATED on orig_count > 0 — always skipped (dead)
 *   6. Writes 0xFE terminator byte at D+0
 *
 * DIFFERENCE: template bytes
 *     gl_func_0006BD14 template: {0xFF, 0x01, 0x03, a0_in,  0xFF, 0xFF, 0xFF, 0xFF}
 *     gl_func_0006C1B8 template: {0xFF, 0x01, 0x04, 0x01,   0xFF, 0xFF, 0xFF, 0xFF}
 *                                            type^^  ^subtype
 *
 *   This sibling resets-with-type=4-subtype=1 (vs 0006BD14's type=3-subtype-from-arg).
 *   Also uses NO ARGS — `a0` isn't read by this function; subtype is hardcoded 1.
 *
 * Decoded structure (raw-word disasm):
 *   void reset_type4(void) {  // takes no arg; a0 unused
 *       for (int i = 0; i < 15; i++) {
 *           *(int*)((char*)&D_00000000 + i*4) = 0;
 *       }
 *       int orig_count = *(uint8_t*)&D_00000000;     // = 0 after clear
 *       *(int*)((char*)&D_00000000 + 0x3C) = 1;       // active flag
 *
 *       // Build template: {0xFF, 0x01, 0x04, 0x01, 0xFF, 0xFF, 0xFF, 0xFF}
 *       // Note: bytes [4,5] written as `sh 0xFFFF` (halfword), [6,7] as `sb 0xFF` each
 *
 *       if (orig_count > 0) {
 *           // emit-record loop — DEAD due to clear
 *           ...
 *       }
 *       *(uint8_t*)((char*)&D_00000000) = 0xFE;        // terminator
 *   }
 *
 * Notes:
 *  - Uses `sh $tN, 0x8(sp)` (store halfword) for the middle 2 bytes vs
 *    individual `sb` stores in 0006BD14. Same byte values, different
 *    instruction widths — likely IDO register allocation chose halfword
 *    because the constant 0xFFFF fits one ori-into-low-half.
 *  - No argument used: confirms this is a fixed-shape reset for one
 *    specific record type (type=4-subtype=1).
 *  - Trailing 2-insn `lui $t6,0; lw $t6,0xC($t6)` fragment post-epilogue —
 *    incomplete fragment per feedback_splat_too_big_incomplete_fragment_tail.md.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
extern int D_00000000;
// Record-stream emitter (swl/swr 8-byte-template family). Inits the dst cursor
// to &D, zero-clears a 15-word array at &D, sets &D+0x3C=1, builds the template
// {0xFF,1,4,1, 0xFFFF(hw), 0xFF,0xFF} (type=4/subtype=1 record), emits it count
// (=*&D) times via two unaligned 4-byte stores, then a 0xFE terminator.
// Residual is the IDO stack-cursor spill cap.
void gl_func_0006C1B8(void) {
    unsigned char tmpl[8];
    unsigned char *dst;
    int i;
    dst = (unsigned char *)&D_00000000;
    for (i = 0; i < 15; i++) {
        *(int *)((char *)&D_00000000 + i * 4) = 0;
    }
    i = *(unsigned char *)&D_00000000;
    *(int *)((char *)&D_00000000 + 0x3C) = 1;
    tmpl[0] = 0xFF;
    tmpl[1] = 1;
    tmpl[2] = 4;
    tmpl[3] = 1;
    *(unsigned short *)(tmpl + 4) = 0xFFFF;
    tmpl[6] = 0xFF;
    tmpl[7] = 0xFF;
    if (i > 0) {
        i = 0;
        do {
            *(int *)dst = *(int *)tmpl;
            *(int *)(dst + 4) = *(int *)(tmpl + 4);
            i++;
            dst += 8;
        } while (i < *(unsigned char *)&D_00000000);
    }
    *dst = 0xFE;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C1B8);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C2A4);

#ifdef NON_MATCHING
/* gl_func_0006C2AC: 52-insn caller-set-$t6 gate + multi-byte/word global init (0xD0, frame 0x20).
 *
 * Decoded structure (raw-word disasm):
 *   if (caller_t6 != 0xA6000000) {                   // caller-set-$t6 gate (cap class)
 *       goto skip;                                    // return stored value
 *   }
 *   // Init: write byte/word fields to several D_sym globals:
 *   *(byte*)&D_a = 1;                                 // sb 1, &D_a+0x4
 *   *(int*) &D_b = 0xA6000000;                        // sw to +0xC
 *   *(byte*)&D_c = 0x40;                              // sb 0x40, +0x5
 *   *(byte*)&D_d = 7;                                 // sb 7, +0x8
 *   *(byte*)&D_e = 7;                                 // sb 7, +0x6
 *   *(byte*)&D_f = 2;                                 // sb 2, +0x7
 *   *(byte*)&D_g = 0;                                 // sb 0, +0x9
 *   *(int*) &D_h = 0;                                 // sw 0, +0x10
 *   func1(&D_arg + 0x14, 0x60);                       // 0x60-byte init
 *   func2();
 *   *(int*)&D_x = *(int*)&D_y;                        // copy a global
 *   func3(saved_x);                                   // post-init
 * skip:
 *   return *(int*)&D_result;
 *
 * CALLER-SET $t6 = 0xA6000000 gate (5th member of caller-set-int-reg cap
 * family — see feedback_caller_set_int_reg_cap_1080_game_libs memo).
 * The 0xA6000000 constant is unusual — not a standard N64 hardware base
 * (0xA460/0xA480/0xA404 etc.) — may be a custom MMIO or debug region.
 *
 * Sibling of gl_func_0006F088 (PI DOM2 hardware init); both are libultra-
 * style boot-time hardware register setup.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
/* Whole-body decode 2026-06-01. Guard on caller-set t6 == 0xA6000000; if not,
 * return D_result. Else init a D-state block (bytes at +4=1,+5=64,+6=7,+7=2,
 * +8=7,+9=0; words at +0xC=0xA6000000,+0x10=0), call gl(st+0x14, 0x60) + gl(),
 * then a tail (copy a D word, store a D ptr, gl(saved)) and return D_result. */
int gl_func_0006C2AC(void) {
    extern int t6_caller_state_0006C2AC;
    extern int D_result_sym_0006C2AC;
    extern char D_state_0006C2AC;
    extern int D_tailsrc_0006C2AC, D_taildst_0006C2AC, D_tailptr_0006C2AC;
    char *st = &D_state_0006C2AC;
    int saved;
    if (t6_caller_state_0006C2AC != (int)0xA6000000) {
        return D_result_sym_0006C2AC;
    }
    *(char *)(st + 4) = 1;
    *(int *)(st + 0xC) = (int)0xA6000000;
    *(char *)(st + 5) = 64;
    *(char *)(st + 8) = 7;
    *(char *)(st + 6) = 7;
    *(char *)(st + 7) = 2;
    *(char *)(st + 9) = 0;
    *(int *)(st + 0x10) = 0;
    gl_func_00000000(st + 0x14, 0x60);
    saved = gl_func_00000000();
    D_taildst_0006C2AC = D_tailsrc_0006C2AC;
    D_tailptr_0006C2AC = (int)&D_state_0006C2AC;
    gl_func_00000000(saved);
    return D_result_sym_0006C2AC;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C2AC);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006C2AC_pad.s")
