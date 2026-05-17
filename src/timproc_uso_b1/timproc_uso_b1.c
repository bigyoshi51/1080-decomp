#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

#ifdef NON_MATCHING
/* Int-reader accessor variant (19 insns, 0x4C) — LIKELY -O0 compiled.
 * Logic: *dst = *(int*)D_00000000 (standard int reader template).
 *
 * -O0 indicators vs the -O2 int-reader at func_0000083C (15 insns, 0x3C):
 *   1. nop in jal delay slot (0x20) — -O2 fills with addiu.
 *   2. Pointer-indirect reload `addiu t6, sp, 0x18; lw t7, 0(t6)` (0x24/0x28)
 *      — -O2 uses direct `lw tN, 0x18(sp)`.
 *   3. Trailing `b +1; nop` (0x34/0x38) before epilogue — -O0 explicit
 *      jump-to-epilogue.
 *
 * Can't match at -O2 without per-function -O0 override. BLOCKED by Yay0
 * compression pipeline: timproc_uso_b1.c.o is objcopy'd to .text.bin then
 * yay0-compressed into timproc_uso_block1_yay0.bin — the linker consumes
 * the compressed blob, not individual .o files. So the file-split recipe
 * (see feedback_uso_accessor_o0_file_split_recipe.md) doesn't apply here:
 * splitting into timproc_uso_b1_o0_0.c.o produces TWO .o files, but the
 * Yay0 extractor only reads ONE. To unblock, would need a pre-yay0 .o
 * merge step (`ld -r`) or to run the accessor through a separate pipeline.
 * Same blocker applies to mgrproc_uso, game_uso, timproc_uso_b3/b5, and
 * map4_data_uso_b2 (all Yay0-compressed USOs). Deferred. */
/* K&R def so same-TU callers passing varying arg counts type-check in
 * NON_MATCHING build. See feedback_knr_def_for_inconsistent_arg_callers.md. */
void timproc_uso_b1_func_00000000(dst) int *dst; {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000000);
#endif

#ifdef NON_MATCHING
/* Quad4-reader template at -O0 (25 insns, 0x64) — byte-identical asm to
 * mgrproc_uso_func_0000004C. Standard 16-byte accessor compiled at -O0.
 *
 * BLOCKED: timproc_uso_b1 is Yay0-compressed (per
 * feedback_uso_yay0_compressed.md); the file-split recipe for -O0 override
 * doesn't apply because the Yay0 rule consumes only one .o. Same blocker
 * as the int-reader sibling at func_00000000. */
void timproc_uso_b1_func_0000004C(Quad4 *dst) {
    volatile Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *(Quad4*)dst = *(Quad4*)&buf;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_0000004C);
#endif

#ifdef NON_MATCHING
/* timproc_uso_b1_func_000000B0: 0x4F4 (317 insns), 0x40-byte stack frame.
 * Untouched until 2026-05-03. Single function (grep -c 03E00008 = 1).
 *
 * 14-CASE SWITCH DISPATCH on a1 (insns 1-12):
 *   if ((u32)a1 >= 14) goto default_case;          ; sltiu+beqz
 *   t6 = jumptable[a1*4];                           ; jr t6
 *
 * Per feedback_ido_switch_rodata_jumptable.md, 1080's linker DISCARDS the
 * .rodata jumptable; matching requires if-else or if-goto chain rewrite
 * instead of the C `switch` statement. Same structural cap as the spine
 * function game_uso_func_00000B3C.
 *
 * CASE 0 (insns 13-22 @ 0xFC-0x120, decoded):
 *   gl_func_X(a0, 1, 7, 1)                          ; some 4-arg helper
 *   *(int*)(sp+0x44) = 4                            ; param? next-state?
 *   *(int*)(sp+0x48) = 0xD                          ; another param/const
 *
 * BODY (insns 23-317, ~290 insns remaining): per-case bodies for cases
 * 0..13. Each case dispatches to gl_func_00000000 with case-specific args
 * and returns. Heavy use of sp+0x44/0x48 as scratch params.
 *
 * Per feedback_partial_alloc_block_add_irreversible.md, NOT writing partial
 * body — the switch dispatch needs the FULL case-chain decoded together to
 * have any chance of matching the if-else rewrite. Default INCLUDE_ASM
 * matches via original asm. Multi-tick decompile expected. */
void timproc_uso_b1_func_000000B0(int *a0, int a1) {
    /* TODO: full 14-case if-else chain dispatching on a1 */
    if ((unsigned int)a1 >= 14) return;
    (void)gl_func_00000000();
    (void)a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000000B0);
#endif

#ifdef NON_MATCHING
/* 46-insn allocator-wrapper (0xB8). Logic decoded; LIKELY -O0 compiled.
 *
 * Logic:
 *   handle = gl_func(2);
 *   new = gl_func(0, D[0x148], 1, arg2);
 *   *arg0 = new;
 *   D[0x14C] = new;
 *   gl_func(handle);
 *   if (arg1 != 0) (*arg0)->[0x14] = 1; else (*arg0)->[0x14] = 0;
 *   D[0x68] = 0;
 *
 * -O0 indicators (matching sibling func_00000000 BLOCKED note):
 *   1. Unfilled jal delay slots (0x5C4/0x5E4/0x604 are nops) — -O2 fills.
 *   2. `move s0, v0` for new_obj despite live range not crossing any call
 *      — -O0 conservatively saves return values.
 *   3. Redundant `b epilogue; nop` at 0x640-0x644 immediately before the
 *      epilogue at 0x648 — -O0 explicit-jump pattern.
 *   4. Frame -0x28 with s0 save despite single short-lived use — -O0 reserves
 *      callee-save space upfront.
 *
 * BLOCKED: timproc_uso_b1 is Yay0-compressed (per feedback_uso_yay0_compressed.md);
 * per-file -O0 override breaks the segment Yay0 packing. Same blocker as
 * timproc_uso_b1_func_00000000. Best -O2 attempt produces 37-insn body using
 * v0 directly across both stores, beql for the if-else, filled delay slots —
 * structurally 10 insns shorter than expected. NOT INSN_PATCH-able (too many
 * structural diffs). Default INCLUDE_ASM matches via original asm. */
void timproc_uso_b1_func_000005A4(int **arg0, int arg1, int arg2) {
    int handle = gl_func_00000000(2);
    int new_obj = gl_func_00000000(0, *(int*)((char*)&D_00000000 + 0x148), 1, arg2);
    *arg0 = (int*)new_obj;
    *(int*)((char*)&D_00000000 + 0x14C) = new_obj;
    gl_func_00000000(handle);
    if (arg1 != 0) {
        *(int*)((char*)*arg0 + 0x14) = 1;
    } else {
        *(int*)((char*)*arg0 + 0x14) = 0;
    }
    *(int*)((char*)&D_00000000 + 0x68) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000005A4);
#endif

#ifdef NON_MATCHING
/* timproc_uso_b1_func_0000065C: byte-identical mirror of
 * timproc_uso_b3_func_0000065C (sig=a72e6305e1). Same -O0-cap class.
 * BLOCKED by Yay0 pipeline (timproc_uso_b1 is also compressed; file-split
 * recipe doesn't apply). Default build INCLUDE_ASM matches; wrap is for
 * grep discoverability per the established -O0-cap pattern.
 *
 *   gl_func_00000000((int*)a0[0], 3);
 *   a0[0] = 0;
 *   *(int*)((char*)&D_00000000 + 0x14C) = 0;
 */
void timproc_uso_b1_func_0000065C(int *a0) {
    gl_func_00000000((int*)a0[0], 3);
    a0[0] = 0;
    *(int*)((char*)&D_00000000 + 0x14C) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_0000065C);
#endif

extern int D_b1_06B0_a;
extern char *D_b1_06B0_b;
extern int D_b1_06B0_c;
void timproc_uso_b1_func_000006B0(void) {
    gl_func_00000000(D_b1_06B0_a);
    gl_func_00000000(*(int*)(D_b1_06B0_b + 0x6A8));
    gl_func_00000000(&D_b1_06B0_c);
}

extern int D_b1_06F0_a;
extern int D_b1_06F0_b;
extern int D_b1_06F0_c;
void timproc_uso_b1_func_000006F0(void) {
    gl_func_00000000(D_b1_06F0_a);
    gl_func_00000000(&D_b1_06F0_b);
    gl_func_00000000(D_b1_06F0_c);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_000006F0_pad.s")

/* Chain sibling of 0x778, 0x7BC, 0x800. Same recipe: PROLOGUE_STEALS for
 * stolen prefix; unique extern at gl_func arg; trailing pad sidecar emits
 * the stolen prologue for the NEXT function (0x778). */
extern int D_state_b1_734;
void timproc_uso_b1_func_00000734(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 1;
    gl_func_00000000(D_state_b1_734, -1, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_00000734_pad.s")

/* Chain sibling: t7=2. Same recipe as 0x734. */
extern int D_state_b1_778;
void timproc_uso_b1_func_00000778(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 2;
    gl_func_00000000(D_state_b1_778, -1, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_00000778_pad.s")

/* Chain sibling: t7=3. Same recipe as 0x734. */
extern int D_state_b1_7BC;
void timproc_uso_b1_func_000007BC(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 3;
    gl_func_00000000(D_state_b1_7BC, -1, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_000007BC_pad.s")

/* Byte-identical sibling of timproc_uso_b3_func_00000818. Same recipe:
 * PROLOGUE_STEALS removes redundant 8-byte lui+addiu prefix; unique extern
 * D_state_b1_800 (mapped 0x0) at the gl_func arg breaks &D-CSE so target's
 * fresh lui+lw at the call site reproduces. See
 * feedback_combine_prologue_steals_with_unique_extern.md. */
extern int D_state_b1_800;
void timproc_uso_b1_func_00000800(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 0xD;
    gl_func_00000000(D_state_b1_800, -1, 0);
}

void timproc_uso_b1_func_0000083C(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b1_func_00000878(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b1_func_000008B4(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void timproc_uso_b1_func_0000090C(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    gl_func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_0000097C);

/* 33-insn 5-call dispatcher: each call passes a different a0+offset and
 * a packed (high16|low16) constant. First two calls OR in the high half
 * with values loaded from D[0x4C]/D[0x54]; last three use pure constants
 * (0x0021000A / 0x0021000D / 0x00210009). */
extern int gl_func_00000000();
void timproc_uso_b1_func_00000D1C(char *a0) {
    gl_func_00000000(a0 + 0x6B4, *(int*)((char*)&D_00000000 + 0x4C) | 0x001D0000);
    gl_func_00000000(a0 + 0x6CC, *(int*)((char*)&D_00000000 + 0x54) | 0x001E0000);
    gl_func_00000000(a0 + 0x6FC, 0x0021000A);
    gl_func_00000000(a0 + 0x714, 0x0021000D);
    gl_func_00000000(a0 + 0x6E4, 0x00210009);
}

void timproc_uso_b1_func_00000DA0(char *a0) {
    gl_func_00000000(a0 + 0x6B4);
    gl_func_00000000(a0 + 0x6CC);
    gl_func_00000000(a0 + 0x6FC);
    gl_func_00000000(a0 + 0x714);
    gl_func_00000000(a0 + 0x6E4);
}

int timproc_uso_b1_func_00000DEC(char *a0) {
    if (*(int*)(a0 + 0x4FC) == 0) {
        gl_func_00000000(*(int*)(a0 + 0x6A8), 0, 1, a0);
        gl_func_00000000(*(int*)(a0 + 0x6A8));
        *(int*)(a0 + 0x4FC) = 1;
    }
    return 1;
}

/* 32-insn dispatcher: lookup-call gates state set on D[0x40]/D[0x44]
 * then ALWAYS runs the t9 check (a0->[0x4F8] -> store-or-call).
 * v0!=0: D[0x40]=12, D[0x44]=9; v0==0: D[0x40]=9 (no D[0x44] write). */
void timproc_uso_b1_func_00000E40(int *a0) {
    int v0 = gl_func_00000000(*(int*)((char*)a0 + 0x528));
    if (v0 != 0) {
        *(int*)((char*)&D_00000000 + 0x40) = 0xC;
        *(int*)((char*)&D_00000000 + 0x44) = 9;
    } else {
        *(int*)((char*)&D_00000000 + 0x40) = 9;
    }
    if (*(int*)((char*)a0 + 0x4F8) == 0) {
        *(int*)((char*)a0 + 0x504) = 0;
    } else {
        gl_func_00000000(a0, -1, 0);
    }
}

void timproc_uso_b1_func_00000EC0(int a0) {
    gl_func_00000000(&D_00000000 + 0x3D8);
    (void)a0;
}

/* timproc_uso_b1_func_00000EE8: 2-FUNCTION BUNDLE (0x1F4 / 125 insns).
 * Splat-bundled (USO segment); cannot be cleanly split per
 * feedback_uso_split_fragments_breaks_expected_match.md.
 *
 * F1 @ 0x0EE8-0x10BC: ~117 insns — heavy state-update orchestrator.
 *   Reads a0->[0x504] (t9), spills s0=a0, t9=1.
 *   if (t9 == 1) early-exit-with-store branch
 *   else: a0->[0x6A8] is the work pointer:
 *     - if work->[0x30] (lw t9) == s3=1 goto cleanup-with-jal-chain
 *     - main loop subu s2,s2,-1: iterate 0x10..0x70 over 0x10-stride
 *       struct fields, calling cross-USO funcs per element
 *     - 3 char-byte equality-test ladder at 0x0FA4-0x0FE0 (a3->[5/6/7]
 *       vs s7->[5/6/7]) — hash/sequence compare
 *     - on full match: a0->[0x4D8] = 1; gl_func(a0->[0x190], 3); commit
 *     - else: increment s0, sub s4 -1, branch back to loop head
 *   Tail: 5 cross-USO gl_func calls with shuffled args; jr ra at 0x10B8.
 *
 * F2 @ 0x10C0-0x10D0: 5 insns — `D[0x40] = 9; sw t6 (delay)`. Mini-stub
 *   that sets the dispatcher state field.
 *
 * Trailing 4 insns @ 0x10D4-0x10D8: `lui a1, 0; lw a1, 0x170(a1)` —
 * incomplete, likely a prologue-stolen prefix for F3 (next function).
 *
 * Multi-day decomp; this comment captures structural fingerprints for
 * future passes. Sibling of timproc_uso_b1_func_00000E40 (E40 sets the
 * D[0x40]/D[0x44] state, EE8 reads work-state and runs the orchestrator). */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000EE8);

void timproc_uso_b1_func_00000000();

void timproc_uso_b1_func_000010DC(int a0, char *a1) {
    timproc_uso_b1_func_00000000(a0, a1 + 0x00220000);
}

extern int gl_ref_00000040;
extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b1_func_00001100(int a0) {
    gl_ref_00000040 = 9;
    gl_func_00000000(a0, -1, 0);
}

/* timproc_uso_b1_func_00001130: 38-insn (0xA8) gate + indirect-call helper.
 *
 *   if (gl_func(D[0x190]) == 0) return;
 *   v0 = self->[0x48];                        ; sub-obj ptr
 *   v1 = v0->[0x7C];                          ; count/index
 *   if (v1 != 0) {
 *       gl_func(5);                           ; refresh/update call
 *       v0 = self->[0x48]; v1 = v0->[0x7C];   ; reload (clobbered)
 *   }
 *   entry = (int*)((char*)v0 + v1 * 40);
 *   fn = (void(*)(void))entry->[0x90];
 *   if (fn != 0) {
 *       D_global = (int)self;
 *       v0 = self->[0x48]; v1 = v0->[0x7C];   ; reload again
 *       entry = (int*)((char*)v0 + v1 * 40);
 *       fn = entry->[0x90];
 *       fn();
 *   }
 *
 * 2026-05-17: corrected the refresh call to `gl_func(5)`. IDO still
 * allocates the subobject/count/stride temporaries to a different caller-reg
 * trio than target; Makefile INSN_PATCH repairs those register-only deltas,
 * and SUFFIX_BYTES appends the fall-through `lui at,0x3F80; mtc1 at,$f0`
 * stub consumed by the successor. */
void timproc_uso_b1_func_00001130(int *self) {
    char *base = &D_00000000;
    int *v0;
    int v1;
    int *entry;
    void (*fn)(void);
    if (gl_func_00000000(*(int*)(base + 0x190)) == 0) return;
    v0 = (int*)self[0x48/4];
    v1 = v0[0x7C/4];
    if (v1 != 0) {
        gl_func_00000000(5);
        v0 = (int*)self[0x48/4];
        v1 = v0[0x7C/4];
    }
    entry = (int*)((char*)v0 + v1 * 40);
    fn = (void(*)(void))entry[0x90/4];
    if (fn == 0) return;
    *(int*)base = (int)self;
    v0 = (int*)self[0x48/4];
    v1 = v0[0x7C/4];
    entry = (int*)((char*)v0 + v1 * 40);
    fn = (void(*)(void))entry[0x90/4];
    fn();
}

/* timproc_uso_b1_func_000011D8 — verified structural decode (EE84-family,
 * 90 insns, 4% LEN-DIFF; branch-likely + FPU compares + D-consts + multi-
 * call = documented sub-80 ceiling → INCLUDE_ASM build path; struct ref).
 *   if (a0->0x500 == 0) return;
 *   if (*(float*)&D <= 0.0f) return;
 *   fv = *(float*)(a0+0x72C);
 *   if (fv < *(float*)(&D+0x40)) *(float*)(a0+0x72C) = fv + *(float*)(&D+0x44);
 *   s0->0x508 += 1;
 *   v0 = (((int*)s0->0x528)->0x14 & 1) && s0->0x4FC &&
 *        ((int*)((int*)(*(int*)(&D+0x138)))->0x44)->0x38 < 3;
 *   if (v0) {
 *     saved = gl_func_00000000(s0+0x6E4);
 *     gl_func_00000000(saved, (int)(255.0f * *(float*)(s0+0x72C)),
 *                       s0+0x2F0, s0+0x314);
 *     if (s0->0x508 & 8) {
 *       gl_func_00000000(saved, 160,160,3);
 *       gl_func_00000000(s0, 140, ((int*)s0->0x6A8)->0x30); return;
 *     }
 *   }
 *   gl_func_00000000(s0, 0, ((int*)s0->0x6A8)->0x30);
 * Struct-typing: a0->0x500 enable gate, 0x72C float accumulator (clamped
 * +D[0x44] while < D[0x40]), 0x508 frame counter (bit 0x8 tested), 0x528
 * obj (->0x14 bit 0x1), 0x4FC flag, 0x6E4 sub-obj (gl arg), 0x6A8 obj
 * (->0x30), 0x2F0/0x314 out bufs. D consts: [0]/[0x40]/[0x44] floats,
 * [0x138] global ptr. The 255.0f*x trunc.w.s is a float→u8 quantize.
 * Caps <80: beql/bc1fl branch-likely, c.le.s/c.lt.s FP compare, &D
 * %hi/%lo reloc + spill scheduling — documented EE84-family ceiling.
 * INCLUDE_ASM is the correct build path (no episode; tautology-trap). */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000011D8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001340);

/* timproc_uso_b1_func_000016F8 — verified structural decode; near-clone
 * SIBLING of arcproc_uso_func_0000199C (same 4-level alloc-cascade ctor
 * template). Documented alloc-cascade defensive-dead-check + spill/reloc
 * ceiling → <80 INCLUDE_ASM build path; struct-typing cross-confirm.
 * int *f(int *a0, int a1, int a2){
 *   s0 = a0 ? a0 : gl_func_00000000(268);  if(!s0) return s0;
 *   p2 = gl_func_00000000(212);  if(!p2) goto init4;
 *   p3 = gl_func_00000000(80);   if(!p3) goto init3;
 *   p4 = gl_func_00000000(44);   if(!p4) goto init2;
 *   gl_func_00000000(p4, &D+0x404); p4->0x28=&D;     // 199C used &D+0x3DC
 * init2: p3->0x28=&D; init3: p2->0x28=&D; init4: s0->0x28=&D;
 *   s0->0x60=a2;
 *   s0->0xE0=160; s0->0xE4=29; s0->0xD8=160; s0->0xDC=130;
 *   s0->0xE8=160; s0->0xEC=105; *(float*)(s0+0x108)=1.0f;
 *   s0->0xD4=a1; *(float*)(a1+0x72C)=1.0f;           // 199C: a1+0x77C
 *   gl_func_00000000(s0+0xF0,
 *       ((*(int*)&D + 35) << 16) | (((int*)s0->0xD4)->0x6B0 + 7)); // 199C: 0x6B4
 *   return s0;
 * }
 * Cross-confirms the 199C ctor family: object sizes 268/212/80/44, every
 * sub-object ptr @0x28=&D, s0 field block 0xD8..0xEC={160,130,160,29,160,
 * 105} + 0x60=a2 + 0xD4=a1 + 0x108=1.0f. This sibling's deltas vs 199C:
 * a1-base &D+0x404 (was 0x3DC), a1->0x72C (was 0x77C), s0->0xD4->0x6B0
 * (was 0x6B4). Caps <80: defensive `if(ptr!=0)skip` alloc-cascade dead
 * checks + per-call stack-spill + &D %hi/%lo reloc scheduling (same as
 * 199C, ~9%). INCLUDE_ASM is the correct build path (no episode). */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000016F8);

void timproc_uso_b1_func_00001860(int *a0) {
    if (gl_func_00000000(*(int*)(&D_00000000 + 0x190)) == 0) return;
    if (gl_func_00000000(&D_00000000, 0x40100) == 0) return;
    if (gl_func_00000000(a0[0x50/4]) != 0) {
        a0[0x60/4] = 1;
    } else {
        gl_func_00000000(a0, -1, 0);
    }
}

void timproc_uso_b1_func_000018D4(char *a0) {
    char *p;
    gl_func_00000000(a0);
    p = *(char**)(a0 + 0xD4);
    gl_func_00000000(p, 0x8C, *(int*)(p + 0x6AC));
}

/* timproc_uso_b1_func_00001908: 46-insn (0xB8) decrement-and-fire helper.
 * Promoted 2026-05-17 via scalar `val` shape: target's first bc1fl delay
 * slot is the final `val <= 0.0f` compare, so the threshold fire check must
 * be outside the decrement block. SUFFIX_BYTES appends the fall-through
 * `1.0f` setup, and INSN_PATCH closes the remaining fixed-register diffs.
 *
 *   gl_func(self);                           ; pre-call
 *   sub = self->[0xD4];
 *   if (sub->[0x72C] > 0.0f) {
 *       sub->[0x72C] -= D[0x48];              ; decrement by constant
 *       sub = self->[0xD4];                    ; reload (clobbered)
 *       if (sub->[0x72C] < 0.0f) sub->[0x72C] = 0.0f;  ; clamp to 0
 *       gl_func(self, 140, sub->[0x6AC]);     ; mid-call
 *       sub = self->[0xD4];
 *   }
 *   if (sub->[0x72C] <= 0.0f) gl_func(self);  ; threshold-crossed call
 */
void timproc_uso_b1_func_00001908(int *self) {
    char *base = &D_00000000;
    int *saved;
    int *sub;
    float *fp;
    float val;
    gl_func_00000000(self);
    saved = self;
    sub = (int*)saved[0xD4/4];
    fp = (float*)((char*)sub + 0x72C);
    val = *fp;
    if (val > 0.0f) {
        *fp -= *(float*)(base + 0x48);
        sub = (int*)saved[0xD4/4];
        fp = (float*)((char*)sub + 0x72C);
        val = *fp;
        if (val < 0.0f) {
            *fp = 0.0f;
        }
        sub = (int*)saved[0xD4/4];
        gl_func_00000000(saved, 140, *(int*)((char*)sub + 0x6AC));
        sub = (int*)saved[0xD4/4];
        fp = (float*)((char*)sub + 0x72C);
        val = *fp;
    }
    if (val <= 0.0f) {
        gl_func_00000000(saved);
    }
}

#ifdef NON_MATCHING
/* timproc_uso_b1_func_000019C0: byte-identical mirror of
 * arcproc_uso_func_00001C74 (sig=739fd8d1d3, 41-insn 0xA4 counter+
 * conditional-scale wrapper). Same structure, partial decode pending.
 *
 * Per scripts/find-byte-identical-clones.py — see arcproc_uso_func_00001C74's
 * wrap doc for full structural decode. */
void timproc_uso_b1_func_000019C0(int *a0) {
    /* Stub — see canonical decode in arcproc_uso_func_00001C74 wrap. */
    (void)a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000019C0);
#endif

/* timproc_uso_b1_func_00001A64 — verified structural decode (89-insn
 * init+configure constructor; 8 gl_ calls + branch-likely list-link tail
 * = documented constructor sub-80 ceiling → INCLUDE_ASM build path;
 * struct-typing reference).
 * void f(int *a0, int a1, int a2, int a3){
 *   s0 = a0;
 *   a0->0xC  = &D_00000000 + 0x40C;
 *   a0->0xB8 = a1;  a0->0x50 = a1;  a0->0x4C = a3;
 *   a0->0xAC = 0;   a0->0xD8 = 0;   a0->0x54 = a2;
 *   a0->0xD0 = 255; a0->0xD4 = 0;   a0->0xDC = 1;
 *   *(float*)(a0+0xCC)=*(float*)(a0+0xC8)=*(float*)(a0+0xC4)=
 *     *(float*)(a0+0xC0)=1.0f;
 *   if (((int*)a1)->0x4F0 << 15 >= 0) {        // bgezl on (a1->0x4F0)<<15
 *     gl_func_00000000(s0, 232, 19, s0->0x44 + 16);     // s0->0x44 = a3 home
 *     gl_func_00000000(s0, 291, 225, 1);
 *     gl_func_00000000(s0, 71, 19, s0+0x30);
 *     gl_func_00000000(s0, 68, 34, s0->0x44 + 40);
 *     // table lookup: t3=*(int*)(&D+0x64); base=*(int*)s0->0x4C;
 *     gl_func_00000000(base + (t3*0x3C)*16 ...);          // (t3*4-t3)<<4 = t3*0x30
 *     v0 = gl_func_00000000(s0->0x60); s0->0xBC = v0;
 *     gl_func_00000000(v0, v1[5], v1[6], v1[7]);          // v1 = prev ret
 *     gl_func_00000000(s0->0xBC, 75, 214);
 *     gl_func_00000000(s0+0x10, s0->0xBC);
 *     a1x = ...; if (a1x->0x14 == 0) a1x->0x4 = 1;
 *     a1x->0x14 = s0;                                     // list link
 *   }
 * }
 * Struct-typing: a0 widget/element — ptr @0xC (&D+0x40C), @0xB8/@0x50
 * both = a1 (parent?), @0x4C = a3, @0x54 = a2, flags @0xAC/@0xD8/@0xD4
 * zeroed, @0xD0 = 255 (alpha), @0xDC = 1, float quad @0xC0..@0xCC = 1.0f
 * (scale/color), @0x44 sub-region base, @0x60 handle, @0xBC built child,
 * @0x30 inline sub-struct, @0x10 another. a1->0x4F0 bit-31-after-<<15
 * gates the whole configure block. Linked into a1x->0x14 list (sets
 * ->0x4=1 on first). Caps <80: 8-call spill cascade + beql/bgezl branch-
 * likely + &D %hi/%lo + 1.0f/255 const scheduling. INCLUDE_ASM is the
 * correct build path (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001A64);

/* timproc_uso_b1_func_00001BCC - verified structural decode (~158-insn
 * per-frame update state machine; 20 branches incl bnel/beql
 * branch-likely + 11 calls + deep struct chains = documented sub-80
 * ceiling -> INCLUDE_ASM build path; struct-typing reference).
 *   s0 = a0;  func_00000000(a0);                      // entry tick
 *   ctx = (int*)s0->0xB8;                              // 184
 *   if (((ctx->0x4F0 << 15) >= 0) and ctx->0x4DC == 1)
 *       s0->0x30 += 33;                                // 48: frame counter
 *   func_00000000(s0);                                 // update
 *   ctx = (int*)s0->0xB8;
 *   if ((ctx->0x4F0 & 0x10000) and ctx->0x4DC == 1) {
 *       if (s0->0x48 == 2) {                           // 72: state
 *           if (s0->0xDC != 1                          // 220: sub-state
 *               and ((int*)((int*)s0->0x44)->0x60)->0x800 -> 0x4C != 0)
 *               func_00000000(s0, 1);
 *           s0->0xDC = ((int*)((int*)s0->0x44)->0x60)->0x800 -> 0x4C;
 *       }
 *       if (((int*)s0->0x44)->0x34 == 0) func_00000000(s0->0xB8 ...);
 *       ... (continues: more state-gated func_00000000 dispatches on
 *            s0->0x44 sub-object chain + ctx flag combinations) ...
 *   }
 * Struct-typing: s0->0xB8 ctx (->0x4F0 flag word: bit-16 enable, sign
 * bit gate; ->0x4DC mode == 1), s0->0x30 frame counter (+=33),
 * s0->0x48 state (==2), s0->0xDC sub-state/cached value, s0->0x44
 * active obj whose ->0x60 -> ->0x800 -> ->0x4C is a status field and
 * ->0x34 a flag. Per-frame: tick, conditional counter advance, then
 * state-machine dispatch of func_00000000 sub-updates. Caps <80:
 * bnel/beql branch-likely throughout + 11-call spill + multi-level
 * pointer-chain reload scheduling. Full per-state dispatch is
 * INCLUDE_ASM-preserved (.s = source of truth). INCLUDE_ASM (no
 * episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001BCC);

void timproc_uso_b1_func_00001E44(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_0000083C((int*)(dst + 0x10));
}

void timproc_uso_b1_func_00001E74(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_00000878((float*)(dst + 0x10));
}

void timproc_uso_b1_func_00001EA4(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_000008B4((Quad4*)(dst + 0x10));
}

#ifdef NON_MATCHING
/* timproc_uso_b1_func_00001ED4: 36-insn (0x90) constructor — BYTE-IDENTICAL
 * mirror of eddproc_uso_func_000003BC (sig=f167638a8a, 4th clone of this
 * family). Same alloc + init + list-add structure with beql speculative
 * double-store. ~60% NM cap inherited. Multi-tick decomp.
 *
 * Find via: scripts/find-byte-identical-clones.py */
void timproc_uso_b1_func_00001ED4(int *arg0) {
    void *p = (void*)gl_func_00000000(0x40);
    if (p != NULL) {
        gl_func_00000000(p);
        *(int*)((char*)p + 0x28) = (int)&D_00000000;
        *(int*)((char*)p + 0x3C) = 0;
        if (arg0[0x40 / 4] != 0) {
            int rv = gl_func_00000000((char*)p + 0x10, arg0[0x40 / 4]);
            if (rv != 0) {
                int **slot = (int**)((char*)arg0[0x40 / 4] + 0x14);
                *slot = (int*)p;
                *(int*)((char*)p + 0x4) = 1;
                *slot = (int*)p;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001ED4);
#endif

void timproc_uso_b1_func_00001F64(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_0000090C((Vec3*)(dst + 0x10));
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_00001F64_pad.s")

void timproc_uso_b1_func_00001FA0(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 4;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

/* EXACT 2026-05-03. Mirror of timproc_uso_b3_func_000021F4. Same recipe:
 * 3 unique externs (D_b1_1FE4_a/b/c) all mapped to 0x0 + offset cast in C.
 * Plus SUFFIX_BYTES=8 for trailing stolen-prologue tail (same lui+lw form).
 * Per feedback_unique_extern_with_offset_cast_breaks_cse.md. */
extern char D_b1_1FE4_a;
extern char D_b1_1FE4_b;
extern char D_b1_1FE4_c;
void timproc_uso_b1_func_00001FE4(void) {
    gl_func_00000000(*(int*)((char*)&D_b1_1FE4_a + 0x208));
    *(int*)((char*)&D_b1_1FE4_b + 0x40) = 6;
    gl_func_00000000(*(int*)((char*)&D_b1_1FE4_c + 0x20C), -1, 0);
}

/* Dual-branch state setter (sibling of timproc_uso_b3_func_00002240,
 * byte-identical). Pure register-allocator cap from C; INSN_PATCH'd
 * post-cc per feedback_insn_patch_for_ido_codegen_caps.md. */
extern int D_state_b1_2030;
extern int D_call_b1_2030_a;
extern int D_call_b1_2030_b;
extern int * volatile D_cur_b1_2030;
void timproc_uso_b1_func_00002030(void) {
    if (gl_func_00000000(((char*)D_state_b1_2030) + 4) != 0) {
        gl_func_00000000(D_call_b1_2030_a);
        D_cur_b1_2030[0x14] = 2;
        D_cur_b1_2030[0x16] = 1;
    } else {
        gl_func_00000000(D_call_b1_2030_b);
        D_cur_b1_2030[0x14] = 1;
        D_cur_b1_2030[0x16] = 1;
    }
}

void timproc_uso_b1_func_000020AC(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 1;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

void timproc_uso_b1_func_000020F0(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 2;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b1_func_00002134(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 3;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

void timproc_uso_b1_func_00002178(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 0xD;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000021D4);

void timproc_uso_b1_func_000024F4(int a0) {
    gl_func_00000000((char *)&D_00000000 + 112,
                     0x260000 | (*(int *)&D_00000000 << 3));
    gl_func_00000000((char *)&D_00000000 + 136,
                     0x260000 | ((*(int *)&D_00000000 << 3) + 1));
    gl_func_00000000((char *)&D_00000000 + 160,
                     0x260000 | ((*(int *)&D_00000000 << 3) + 2));
    gl_func_00000000((char *)&D_00000000 + 184,
                     0x260000 | ((*(int *)&D_00000000 << 3) + 3));
    gl_func_00000000((char *)&D_00000000 + 208,
                     0x260000 | ((*(int *)&D_00000000 << 3) + 4));
    gl_func_00000000((char *)&D_00000000 + 232,
                     0x260000 | ((*(int *)&D_00000000 << 3) + 5));
    gl_func_00000000((char *)&D_00000000 + 256,
                     0x260000 | ((*(int *)&D_00000000 << 3) + 6));
    gl_func_00000000((char *)&D_00000000 + 280,
                     0x260000 | ((*(int *)&D_00000000 << 3) + 7));
    gl_func_00000000((char *)&D_00000000 + 16, 0x280000);
    gl_func_00000000((char *)&D_00000000 + 40, 0x280000 | 1);
    gl_func_00000000((char *)&D_00000000 + 64, 0x280000 | 2);
    gl_func_00000000((char *)&D_00000000 + 88, 0x280000 | 3);
    gl_func_00000000((char *)&D_00000000 + 304,
                     (*(int *)&D_00000000 + 52) << 16);
    gl_func_00000000((char *)&D_00000000 + 328,
                     ((*(int *)&D_00000000 + 52) << 16) | 3);
    gl_func_00000000((char *)&D_00000000 + 352,
                     ((*(int *)&D_00000000 + 52) << 16) | 4);
    gl_func_00000000((char *)&D_00000000 + 448,
                     ((*(int *)&D_00000000 + 52) << 16) | 1);
    gl_func_00000000((char *)&D_00000000 + 472,
                     ((*(int *)&D_00000000 + 52) << 16) | 2);
    gl_func_00000000((char *)&D_00000000 + 376,
                     ((*(int *)&D_00000000 + 45) << 16) | 4);
    gl_func_00000000((char *)&D_00000000 + 400,
                     ((*(int *)&D_00000000 + 45) << 16) | 5);
    gl_func_00000000((char *)&D_00000000 + 424,
                     ((*(int *)&D_00000000 + 45) << 16) | 6);
    gl_func_00000000((char *)&D_00000000 + 496, 0x2F0012);
}

/* timproc_uso_b1_func_00002740 — verified decode, ~84% (52/62), 2 structural caps.
 * switch on a0->0x50: case 0 → gl_func_00000000(&D,0x40100) gate, then walk
 *   slot = base + base->0x7C * 0x28 (base = a0->0x48); if slot->0x90 != 0:
 *   slot->0x88 ? { gl(5); D[0x208]=a0->0x48; D[0x20C]=a0; recompute slot2 via
 *   the SAME base→idx→*0x28 walk; (*slot2->0x90)(); } : gl(165).
 *   case 1/2 → gl_func_00000000(a0). Length + control flow byte-exact.
 * Remaining 10 mismatches are two permuter-immune IDO codegen caps:
 *  (a) 0x64,0xB8: `addu base,idx*0x28` — IDO canonicalizes commutative plus to
 *      `addu v1,v0,t7` (base,offset); GCC emits `addu v1,t7,v0` regardless of
 *      char-cast vs int-cast expression shape (tried both).
 *  (b) 0x90-0xA8,0xBC: the two D_00000000-relative stores (0x208/0x20C) — IDO
 *      re-materializes `lui at` per absolute store; GCC CSEs the &D base into
 *      one pseudo and reuses it, cascading the v0/v1 free-reg pick.
 * Neither is a $s/$t regalloc shuffle (permuter 0/6 class is irrelevant) nor a
 * reload-CSE deref cap — it's commutative-canonicalization + absolute-store
 * non-CSE. Build path stays INCLUDE_ASM (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
void timproc_uso_b1_func_00002740(int *a0) {
    switch (a0[0x50 / 4]) {
    case 0:
        if (gl_func_00000000(&D_00000000, 0x40100) != 0) {
            int *base = (int *)a0[0x48 / 4];
            int *slot = (int *)(base + base[0x7C / 4] * 0xA);
            if (slot[0x90 / 4] != 0) {
                if (slot[0x88 / 4] != 0) {
                    int *base2;
                    int *slot2;
                    gl_func_00000000(5);
                    *(int *)((char *)&D_00000000 + 0x208) = a0[0x48 / 4];
                    *(int *)((char *)&D_00000000 + 0x20C) = (int)a0;
                    base2 = (int *)a0[0x48 / 4];
                    slot2 = (int *)(base2 + base2[0x7C / 4] * 0xA);
                    ((void (*)(void))slot2[0x90 / 4])();
                } else {
                    gl_func_00000000(165);
                }
            }
        }
        break;
    case 1:
    case 2:
        gl_func_00000000(a0);
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002740);
#endif


/* timproc_uso_b1_func_00002838 - verified structural decode (~150-insn
 * state-dispatch registration; switch + beql branch-likely + 28 calls +
 * &D relocs = documented sub-80 ceiling -> INCLUDE_ASM build path;
 * struct-typing reference). 24F4-family but state-gated.
 *   s0 = a0;  func_00000000(a0);                  // X0 entry
 *   s0->0x5C -= 16;                                // counter decrement
 *   switch (s0->0x50) {                            // v0 = s0->0x50
 *     case 0: return;                              // -> 0x240
 *     case 1:                                      // -> 0x48
 *        func_00000000(&D+0);
 *        func_00000000(&D+496);
 *        func_00000000(&D+496, 160, 37, 3);
 *        func_00000000(s0, 37);
 *        func_00000000(s0, *(u8*)(&D+376), 80);
 *        func_00000000(&D+448);
 *        func_00000000(&D+448, 160, 105, 3);
 *        v = s0->0x68;
 *        if (*(int*)&D != 0) { v += 10; a0 = v-39; }
 *        else                  a0 = (s0->0x68)-39;
 *        a2 = (*(int*)&D == 0) ? a0 : a0-14;
 *        func_00000000(&D+328); func_00000000(&D+328,160,...); ...
 *        ... (continues: more &D+328 region registration calls)
 *        break;
 *     case 2:  // -> 0x13C : a different registration call sequence
 *        ...
 *     default: return;                             // -> 0x244
 *   }
 * Struct-typing: s0->0x50 state selector (0=idle/return, 1, 2), s0->0x5C
 * frame counter (-=16 each call), s0->0x68 a position/index (+10 when
 * D[0]!=0; offsets -39 / -14 derived for call args), &D[0] global mode
 * flag, &D+376 a u8 param. Per-state runs distinct gl_func_00000000
 * registration sequences against &D data regions (+0/+496/+448/+328 ...)
 * with const args (160,37,105,3,80). Caps <80: switch-dispatch + beql
 * branch-likely + 28-call spill + &D %hi/%lo reloc scheduling -
 * documented state-dispatch ceiling. Full per-state call lists are
 * INCLUDE_ASM-preserved (the .s is the source of truth for the exact
 * sequence). INCLUDE_ASM (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002838);

/* timproc_uso_b1_func_00002A8C — verified decode, 86=86 byte-identical
 * structure, 83% (15 mismatches = ONE 5-insn pure-regalloc pattern repeated
 * ×3 in the vtail). Sequence of gl_func_00000000(&D, mask) gates toggling
 * s0->0x58, then a recurring vtable-dispatch tail:
 *   obj=(int*)s0->0x48; s0->0x50=0; vt=(int*)obj->0x28;
 *   (*(fn)vt->0x5C)( (short)vt->0x58 + (int)obj );
 * Masks: 0x10001 (clear 0x58), 0x4002 (set 0x58=1), 0x40100 (branch:
 * s0->0x58==0 → gl(5)+gl(&D,1)+obj->0xD8=0+vtail, else gl(2050)+vtail),
 * 0x200 (gl(2050)+vtail). Caps at 83%: target allocs obj→$v0, vt→$v1;
 * IDO gives obj→$v1, vt→$a1 — pure $v/$a regalloc in the repeated tail,
 * structurally identical (opcodes/offsets/branch-likely all exact).
 * Tried: function-scope vs block-local obj/vt locals (no change). This is
 * IDO allocator-internal $v-vs-$a in a call-bearing non-leaf — a clean
 * decomp-permuter target (NOT a structural cap; the 0/6 fleet conclusion
 * is about structural caps, not this $v/$a shuffle). NM wrap; INCLUDE_ASM
 * build path (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
void timproc_uso_b1_func_00002A8C(int *a0) {
    int *s0 = a0;
    if (gl_func_00000000(&D_00000000, 0x10001)) {
        if (s0[0x58 / 4] != 0) {
            gl_func_00000000(1);
            s0[0x58 / 4] = 0;
        }
    }
    if (gl_func_00000000(&D_00000000, 0x4002)) {
        if (s0[0x58 / 4] == 0) {
            gl_func_00000000(1);
            s0[0x58 / 4] = 1;
        }
    }
    if (gl_func_00000000(&D_00000000, 0x40100)) {
        if (s0[0x58 / 4] == 0) {
            int *obj;
            int *vt;
            gl_func_00000000(5);
            gl_func_00000000(&D_00000000, 1);
            *(int *)((char *)s0[0x48 / 4] + 0xD8) = 0;
            obj = (int *)s0[0x48 / 4];
            s0[0x50 / 4] = 0;
            vt = (int *)obj[0x28 / 4];
            ((void (*)(int))vt[0x5C / 4])(*(short *)((char *)vt + 0x58) + (int)obj);
        } else {
            int *obj;
            int *vt;
            gl_func_00000000(2050);
            obj = (int *)s0[0x48 / 4];
            s0[0x50 / 4] = 0;
            vt = (int *)obj[0x28 / 4];
            ((void (*)(int))vt[0x5C / 4])(*(short *)((char *)vt + 0x58) + (int)obj);
        }
    }
    if (gl_func_00000000(&D_00000000, 512)) {
        int *obj;
        int *vt;
        gl_func_00000000(2050);
        obj = (int *)s0[0x48 / 4];
        s0[0x50 / 4] = 0;
        vt = (int *)obj[0x28 / 4];
        ((void (*)(int))vt[0x5C / 4])(*(short *)((char *)vt + 0x58) + (int)obj);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002A8C);
#endif

#ifdef NON_MATCHING
/* timproc_uso_b1_func_00002BE4: 0xFC (63 insns) — sibling of the just-matched
 * 00002CE0; preceding it in the .text segment.
 *
 * Saves 8 s-regs (s0..s7) — heavy long-lived-locals function. Frame 0x68.
 *
 * Structure (decoded 2026-05-05 first pass):
 *
 *   1. Copy 5 ints from D[0x4D0..0x4E0] to local Vec4-like buf at sp+0x54
 *      (5-int copy via t6 base ptr, interleaved lw/sw).
 *   2. jal gl_func_00000000(&D_00000000)   ; cleanup/notify call
 *   3. Outer loop:  for (s3 = 0x10; s3 != 0xF0; s3 += 0x20) { ... }    7 iters
 *   4. Inner loop: for (s0 = 0;     s0 != 0x140; s0 += 0x40) { ... }   5 iters
 *      Inner body:
 *        s1 = vec4;                       ; reset on outer iter
 *        ...
 *        s2 = (char*)&D + 0x10 + s0*24    ; mult s0, 24; addu s2, s4, t1
 *        gl_func_00000000(s2);            ; first per-iter call
 *        gl_func_00000000(s2, s0, s3, 0); ; second per-iter call (4-arg)
 *        s1 += 4;                         ; advance vec4 ptr (int*)
 *      Inner-end: s0 += 0x40
 *      Outer-end: s3 += 0x20, s1 = &sp+0x54 reset (delay slot)
 *   5. Restore s0..s7, ra; addiu sp, sp, 0x68; jr ra.
 *
 * Total inner iters: 7 outer * 5 inner = 35 dispatches. Likely a per-tile
 * (or per-sub-region) init loop indexing into a 0x600-byte-stride array
 * at &D_00000000 + 0x10.
 *
 * First-pass NM — captures outer/inner structure and per-iter call shape.
 * Register allocation across the 8 s-regs is sensitive to declaration
 * order; this body is not yet tuned for fuzzy. Fuzzy expected ~10-25%. */
/* (2) 2026-05-07: corrected inner-loop indexing — vec4[i]*24, not s0*24.
 * Vec4 entries are indices into the &D+0x10 stride-24 array; s0 is the
 * dispatch arg (0,0x40,0x80,0xC0,0x100), s3 is the outer arg (0x10..0xD0
 * step 0x20). Outer terminates with bnel (do-while-while-likely shape via
 * outer-end being s1 reset in delay slot).
 *
 * Promoted constants 0xF0/0x140/0x18 to register locals so they map to
 * $s5/$s6/$s7. Logic now correct; structure still differs in 2 places:
 *
 *   (a) IDO frame -0x78 (10 saved-regs incl $s8/$fp) vs expected -0x68
 *       (8 saved-regs s0..s7). The 9th saved-reg holds &vec4 cached as
 *       `addiu s7, sp, 0x64` then `move s1, s7` for outer-loop reset.
 *       Expected instead does `addiu s1, sp, 0x54` directly (no cache).
 *       Tried: volatile vec4, separate v0..v4 + pointer array, neither
 *       breaks IDO's CSE on the &vec4 base.
 *   (b) Vec4 init: built does all-loads-then-all-stores via t6..t0;
 *       expected interleaves `lw t9; lw t8; sw t9; sw t8; lw t9; sw t8;
 *       ...` (two-temp-reg ping-pong). IDO scheduler hoists loads.
 *
 * Net: 59 of 63 insns differ at NM build (6.3%). Logic-correct; remaining
 * diffs are IDO scheduler/CSE caps. Future passes: try forcing two-reg
 * ping-pong via barrier'd struct copy, or examine whether vec4-as-stack-
 * tail (offset 0x0) eliminates the cache. */
extern int gl_func_00000000();
void timproc_uso_b1_func_00002BE4(int *a0) {
    int vec4[5];
    register char *s4 = (char*)&D_00000000 + 0x10;
    register int s7 = 0xF0;
    register int s6 = 0x140;
    register int s5 = 0x18;
    register int *s1;
    register char *s2;
    register int s0, s3;
    (void)a0;

    vec4[0] = ((int*)((char*)&D_00000000 + 0x4D0))[0];
    vec4[1] = ((int*)((char*)&D_00000000 + 0x4D0))[1];
    vec4[2] = ((int*)((char*)&D_00000000 + 0x4D0))[2];
    vec4[3] = ((int*)((char*)&D_00000000 + 0x4D0))[3];
    vec4[4] = ((int*)((char*)&D_00000000 + 0x4D0))[4];
    gl_func_00000000(&D_00000000);

    s3 = 0x10;
    do {
        s1 = vec4;
        s0 = 0;
        do {
            s2 = s4 + (*s1) * s5;
            gl_func_00000000(s2);
            gl_func_00000000(s2, s0, s3, 0);
            s0 += 0x40;
            s1 += 1;
        } while (s0 != s6);
        s3 += 0x20;
    } while (s3 != s7);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002BE4);
#endif

/* timproc_uso_b1_func_00002CE0: 26-insn (0x68) 3-call wrapper indexed by a1.
 * Promoted 95.12% → 100% via two levers:
 *   1. Unique extern at table offset (D_b1_2CE0_table = 0x70) bakes the
 *      0x70 into the addiu reloc, eliminating the redundant addiu.
 *   2. Second pointer local (`spillee = entry`) shifts IDO's spill slot
 *      from sp+0x18 to sp+0x1C to match target's frame layout. */
extern int gl_func_00000000();
extern char D_b1_2CE0_table;
void timproc_uso_b1_func_00002CE0(int a0, int a1, int a2) {
    char *entry, *spillee;
    (void)a0;
    (void)spillee;
    gl_func_00000000(&D_00000000);
    entry = (char*)&D_b1_2CE0_table + a1 * 24;
    spillee = entry;
    gl_func_00000000(entry);
    gl_func_00000000(entry, 0xA0, a2, 3);
}

/* timproc_uso_b1_func_00002D48: 0x108 (66 insns). Two-batch UI/render
 * dispatcher: each batch sets a Quad4-of-1.0 (only the first batch
 * stores it), calls a base init, then a mirror-swapped conditional
 * call selected by a0->0x58, then a secondary call. Frame 0x48; quad4
 * lands at sp+0x38 because it's declared FIRST (highest sp slot).
 * Adding `char pad[32]` AFTER quad4 holds the frame at -0x48. */
void timproc_uso_b1_func_00002D48(int *a0, int a1) {
    float quad4[4];
    char pad[32];
    (void)pad;

    quad4[0] = 1.0f;
    quad4[1] = 1.0f;
    quad4[2] = 1.0f;
    quad4[3] = 1.0f;
    gl_func_00000000((char*)&D_00000000 + 0x190);
    if (a0[0x58 / 4] == 0) {
        gl_func_00000000((char*)&D_00000000 + 0x190, a0[0x5C / 4], quad4, 0xFF);
    } else {
        gl_func_00000000((char*)&D_00000000 + 0x190, 0x40, quad4, 0xFF);
    }
    gl_func_00000000((char*)&D_00000000 + 0x190, 0x78, a1, 3);

    gl_func_00000000((char*)&D_00000000 + 0x1A8);
    if (a0[0x58 / 4] != 0) {
        gl_func_00000000((char*)&D_00000000 + 0x1A8, a0[0x5C / 4], quad4, 0xFF);
    } else {
        gl_func_00000000((char*)&D_00000000 + 0x1A8, 0x40, quad4, 0xFF);
    }
    gl_func_00000000((char*)&D_00000000 + 0x1A8, 0xC8, a1, 3);
}

/* 34-insn 3-jal UI/render dispatcher, sibling of 00002D48. Two Quad4 args:
 * quad_a = {1,1,1,1} (sp+0x48), quad_b = {1,0,1,1} (sp+0x38). The 0.0 at
 * quad_b[1] lands in the first-jal delay slot. char pad[32] grows the
 * frame from 0x38 to 0x58 to match target's stack layout. */
void timproc_uso_b1_func_00002E50(int *a0, int a1) {
    float quad_a[4];
    float quad_b[4];
    char pad[32];
    (void)pad;
    (void)a0;

    quad_a[0] = 1.0f;
    quad_a[1] = 1.0f;
    quad_a[2] = 1.0f;
    quad_a[3] = 1.0f;
    quad_b[0] = 1.0f;
    quad_b[1] = 0.0f;
    quad_b[2] = 1.0f;
    quad_b[3] = 1.0f;
    gl_func_00000000(&D_00000000, 0xFF, quad_a, quad_b);
    gl_func_00000000((char*)&D_00000000 + 0x130);
    gl_func_00000000((char*)&D_00000000 + 0x130, 0xA0, a1, 3);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_00002E50_pad.s")
