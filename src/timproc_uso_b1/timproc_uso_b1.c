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

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000011D8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001340);

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

#ifdef NON_MATCHING
/* timproc_uso_b1_func_00001908: 43-insn (0xB8) decrement-and-fire helper.
 * 2026-05-16 cap: built 43 vs target 46 — target keeps `self` in $a3
 * (loaded once from sp+0x18) and reloads only self->[0xD4] x3; C-emit
 * reloads self per-deref, collapsing 3 insns. self-alias `int *s=self`
 * REGRESSED (41 insns, further). Multi-insn structural reload/spill
 * cap — LEN-DIFF blocks INSN_PATCH. Deferred.
 *
 *   gl_func(self);                           ; pre-call
 *   sub = self->[0xD4];
 *   if (sub->[0x72C] > 0.0f) {
 *       sub->[0x72C] -= D[0x48];              ; decrement by constant
 *       sub = self->[0xD4];                    ; reload (clobbered)
 *       if (sub->[0x72C] < 0.0f) sub->[0x72C] = 0.0f;  ; clamp to 0
 *       gl_func(self, 140, sub->[0x6AC]);     ; mid-call
 *       sub = self->[0xD4];
 *       if (sub->[0x72C] <= 0.0f) gl_func(self);  ; threshold-crossed call
 *   }
 *
 * 2026-05-14: applied named-pointer-to-field idiom (`float *fp = (float*)
 * (sub + 0x72C);`) to match target's `addiu v0, a0, 1836` two-step
 * addressing per docs/IDO_CODEGEN.md#feedback-ido-named-base-forces-addiu-split.
 * Pushed 83.65% → 86.60% (+2.95pp). Remaining caps are register-name
 * cascades (self in $a0 vs $a3, sub in $v0 vs $a0, $f0 vs $f2 for zero
 * constant) — not C-controllable.
 *
 * 2026-05-16: tested the inline-deref CSE-defeat lever (#feedback-ido-
 * inline-arg-deref-defeats-cse-emit-multiple-lw) — REGRESSED 86.60% →
 * 85.96% (168B/42 insns, lost 1 more). The recipe applies when target
 * has MORE lw's than built; here target has more insns but they aren't
 * all lw's — inlining self[0xD4/4] adds compute but doesn't reach
 * target's structural shape (which uses cached self in $a3 + $a0
 * reload tracking).
 * PERMUTER-PLATEAUED 2026-05-17: 125k iters flat at score 740 (base
 * 880, ~16% progress). The cached-self-in-$a3 + per-deref-reload
 * collapse is STRUCTURAL, NOT pure-regalloc — the permuter cannot
 * cross it (session meta-finding, 0/6 permuter targets ever hit 0).
 * Prior "permuter-only" label was WRONG; this is true-structural /
 * force-SAME-LEN-INSN_PATCH territory only. */
void timproc_uso_b1_func_00001908(int *self) {
    char *base = &D_00000000;
    int *sub;
    float *fp;
    gl_func_00000000(self);
    sub = (int*)self[0xD4/4];
    fp = (float*)((char*)sub + 0x72C);
    if (*fp > 0.0f) {
        *fp -= *(float*)(base + 0x48);
        sub = (int*)self[0xD4/4];
        fp = (float*)((char*)sub + 0x72C);
        if (*fp < 0.0f) {
            *fp = 0.0f;
        }
        gl_func_00000000(self, 140, *(int*)((char*)sub + 0x6AC));
        sub = (int*)self[0xD4/4];
        fp = (float*)((char*)sub + 0x72C);
        if (*fp <= 0.0f) {
            gl_func_00000000(self);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001908);
#endif

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

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001A64);

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

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000024F4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002740);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002838);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002A8C);

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
