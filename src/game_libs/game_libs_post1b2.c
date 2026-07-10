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

/* gl_func_0006BF34: 81-insn struct-init constructor (self, a1, a2, a3,
 * arg5, arg6; arg5/arg6 stack-passed). Fields: +0x14=a1, +0x04=arg5,
 * +0x00/+0x08/+0x18=0, +0x11C=a2, +0x38=(s64)a3, +0xF0=(s64)arg6-16,
 * +0x100=(s64)(int)&D, +0x118=0xFF03, +0x128=(0x3FFF01&0x3F0000)>>16,
 * +0x12C=0x01000800, +0x10=(s16)1, +0x12=(s16)0; then v0=fn();
 * self->0xC=D_a; D_b=self; fn2(v0).
 * LANDED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the -O1 donor unit game_libs_o1_6BF34.c (81/81 at plain 7.1 -O1 —
 * register-int tmp colors s0; unsigned local for the srl). Body below is
 * a placeholder for the splice (its bytes are replaced by the donor). */
extern int D_00000000;
void gl_func_0006BF34(int *a0, int a1, int a2, int a3, int arg5, int arg6) {
    volatile int keep = a1 + a2 + a3 + arg5 + arg6;
    a0[0] = keep;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006BF34_pad.s")

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

/* gl_func_0006C1B8: 59-insn table-reset + 8-byte record emitter,
 * reset-sibling of gl_func_0006BD14 (template {0xFF,1,4,1,0xFFFF,-1,-1},
 * type=4/subtype=1) and emitter-sibling of the landed gl_func_0006C11C
 * decoder. Zeroes D_c[0..14], sets D_c[15]=1, emits the template
 * D_a times via swl/swr struct copies, then a 0xFE terminator.
 * LANDED 2026-07-09 via REPLACE_FUNC_BODY donor splice: real C lives in
 * the IDO 5.3 -O1 donor unit game_libs_ido53_6C1B8.c (59/59 — 5.3 colors
 * the struct-copy scratch $at; FOR-loop shape sinks the cursor store into
 * the bne delay slot, see donor header). Body below is a placeholder for
 * the splice (its bytes are replaced by the donor). */
void gl_func_0006C1B8(void) {
    volatile int i;
    for (i = 0; i < 15; i++) {}
}


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
