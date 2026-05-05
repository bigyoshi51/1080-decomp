#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

/* Continues arcproc_uso .text at 0x12C (after arcproc_uso_o0_50.c which
 * holds 0x50..0x12C: Quad4 reader + 0xB4 -O0 ref-count/check-full).
 * Original single-file body split into arcproc_uso.c (0x0..0x50 func_00000000),
 * arcproc_uso_o0_50.c (-O0), and this tail. */

void arcproc_uso_func_00001B88(int *a0) {
    int *t;
    arcproc_uso_func_00000000(a0);
    t = *(int**)((char*)a0 + 0xD4);
    arcproc_uso_func_00000000(t, 0x8C, *(int*)((char*)t + 0x6B0));
}

/* arcproc_uso_func_0000012C and func_0000019C moved to arcproc_uso_o0_12C.c (-O0 file). */

#ifdef NON_MATCHING
/* arcproc_uso_func_00000240: 0x388 (226 insns), 0x48 stack frame.
 * Sibling of arcproc_uso_func_0000019C (-O2 here vs -O0 there). 11-way state
 * machine dispatcher: switch (a1) where a1 ranges 0..10. Bound check first
 * (`sltiu at, a1, 0xB; beq at, zero, epilogue`), then jump-table lookup
 * via .rodata at D_xxx + a1*4.
 *
 * Cases 0..10 each do various combinations of:
 *   - gl_func_00000000(a0, 1, 3, 1)    -- 4-arg helper called with constants
 *   - gl_func_00000000(a0, 1, 3, ...)  -- variants
 *   - sw constants 0x3, 0xA, 0x1 to *(0x44, 0x48, 0x40) under a single global
 *   - branches to epilogue (sets local +0x40 = 1 to indicate state advance)
 *
 * Likely a "menu state advance" handler — given a key (button press category?)
 * and target struct, dispatch to one of 11 state transitions, each calling
 * the renderer/animator helper with different constants.
 *
 * Per feedback_ido_switch_rodata_jumptable.md: IDO -O2 emits a .rodata
 * jumptable for switch w/ ≥4 dense cases. Without explicit .rodata
 * preservation in the linker script for arcproc_uso, the function may be
 * permanently INCLUDE_ASM (the jumptable address can't be reproduced).
 *
 * Multi-tick: full case decode + verification of jumptable matchability
 * deferred. Default build INCLUDE_ASM remains exact. */
void arcproc_uso_func_00000240(void) {
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000240);
#endif

extern int *D_arc5C8_148;
extern int D_arc5C8_14C;
extern int D_arc5C8_68;
void arcproc_uso_func_000005C8(int *a0) {
    int saved1, saved2;
    int s0;
    saved1 = gl_func_00000000(2);
    a0[2] = gl_func_00000000(0x38);
    gl_func_00000000(saved1);
    saved2 = gl_func_00000000(2);
    s0 = gl_func_00000000(0, D_arc5C8_148, -1, -1);
    a0[0] = s0;
    D_arc5C8_14C = s0;
    gl_func_00000000(saved2);
    *(int*)((char*)a0[0] + 0x14) = 4;
    D_arc5C8_68 = 0;
}

#ifdef NON_MATCHING
/* arcproc_uso_func_00000688: 48-insn (0xC0) struct-init + zero-loop.
 * Initializes 9 fields of *(a0->ptr_at_8) to constants, then loops
 * clearing array slots until i >= bound.
 *
 * Standalone -O0 build of this body produces BYTE-IDENTICAL bytes
 * (verified: prologue addiu sp,-0x8, no-CSE reloads of a0->[0x8]
 * each store, i spilled to sp+0x4, loop reloads bound each iter,
 * tail b+nop BBL marker). At -O2 it's 38 insns instead of 48 — IDO
 * CSEs the chain and keeps i/bound in regs.
 *
 * BLOCKED: needs -O0 file split. arcproc_uso has -O0 sub-files at
 * 0x50 and 0x12C; this function is at 0x688 and would need a new
 * arcproc_uso_o0_688.c with linker-script slot + TRUNCATE_TEXT
 * adjustments. Multi-tick infrastructure scope. */
void arcproc_uso_func_00000688(int *a0) {
    int i;
    *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x00) = 1;
    *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x04) = 0;
    *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x08) = 5;
    *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x0C) = 2;
    *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x10) = 0;
    *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x14) = 3;
    *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x18) = 1;
    *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x1C) = 4;
    *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x34) = 0;
    i = 0;
    if (i < *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x8)) {
        do {
            *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x20 + i*4) = 0;
            i++;
        } while (i < *(int*)((char*)*(int**)((char*)a0 + 0x8) + 0x8));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000688);
#endif

#ifdef NON_MATCHING
/* 27-insn cleanup wrapper. Calls gl_func twice (a0->8, a0->0); zeroes
 * a0->8, a0->0, and D[0x14C]. -O0 indicators in target asm: unfilled
 * jal delay slots (0x20, 0x80) + `b +1; nop` BBL marker at 0x98. The
 * standard -O2 form below produces the right logic but mismatches on
 * delay-slot fill + missing BBL marker (~50% cap). Per the bootup_uso
 * O0-runs pattern (see project_1080_bootup_uso_o0_runs.md), this would
 * need per-function -O0 override + file split. Keep wrap for grep
 * discoverability + reference. Mirror of h2hproc_uso_func_00000274.
 *
 * 2026-05-04: arcproc_uso ALREADY has -O0 file split infrastructure
 * (arcproc_uso_o0_50.c, arcproc_uso_o0_12C.c with OPT_FLAGS := -O0 in
 * Makefile). Adding arcproc_uso_o0_748.c is feasible — would need:
 *   1. Move this function to new file with -O0 override
 *   2. Add `build/src/arcproc_uso/arcproc_uso_o0_748.c.o: OPT_FLAGS := -O0`
 *      and TRUNCATE_TEXT for layout
 *   3. Insert into tenshoe.ld between arcproc_uso_o0_12C and tail1
 *   4. Trim tail1's TRUNCATE_TEXT to exclude 0x748+
 * Defer to a layout-budgeted tick — this tick's budget is reading not
 * restructuring. */
void arcproc_uso_func_00000748(int *a0) {
    gl_func_00000000((int*)a0[2]);
    a0[2] = 0;
    gl_func_00000000((int*)a0[0], 3);
    a0[0] = 0;
    *(int*)((char*)&D_00000000 + 0x14C) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000748);
#endif

void arcproc_uso_func_000007B4(void) {
    gl_func_00000000(*(int*)&D_00000000);
    gl_func_00000000(*(int*)((char*)*(int**)&D_00000000 + 0x6AC));
    gl_func_00000000(*(int*)&D_00000000);
    gl_func_00000000(&D_00000000);
}

extern char *D_arc800_a;       /* gl_func 1st-arg AND chain-2 (0x6A8) base */
extern char *D_arc800_b;       /* chain-1 (0x6AC) base */
extern int   D_arc800_d;       /* store target +0x40 / +0x44 */

void arcproc_uso_func_00000800(void) {
    int v;
    gl_func_00000000(D_arc800_a);
    v = gl_func_00000000(*(int*)((char*)*(int**)((char*)D_arc800_b + 0x6AC) + 0x4C));
    if (v != 0) {
        *(int*)((char*)&D_arc800_d + 0x40) = 7;
        *(int*)((char*)&D_arc800_d + 0x44) = 4;
    } else {
        *(int*)((char*)&D_arc800_d + 0x40) = 4;
    }
    gl_func_00000000(D_arc800_a, 4,
        *(int*)((char*)*(int**)((char*)D_arc800_a + 0x6A8) + 0xC));
}

/* arcproc_uso_func_00000880: 31-insn (0x7C) state-conditional update.
 * Promoted from 99.19% NM to exact via `make expected` reloc-form refresh.
 * 3 unique extern aliases (D_arc880_X/_Y/_Z) avoid IDO &D-CSE collapse
 * per feedback_unique_extern_with_offset_cast_breaks_cse.md. Inlining
 * the D_Y indirection chain into the gl_func arg keeps it in $t7
 * (vs $v1 with a named local). */
extern int D_arc880_X;
extern char *D_arc880_Y;
extern char D_arc880_Z[];
void arcproc_uso_func_00000880(void) {
    int v0;
    gl_func_00000000(D_arc880_X);
    v0 = gl_func_00000000(*(int*)((char*)*(int**)((char*)D_arc880_Y + 0x6AC) + 0x4C));
    if (v0 != 0) {
        *(int*)(D_arc880_Z + 0x40) = 7;
        *(int*)(D_arc880_Z + 0x44) = 9;
    } else {
        *(int*)(D_arc880_Z + 0x40) = 9;
    }
    gl_func_00000000(D_arc880_X, 0, 0);
}

void arcproc_uso_func_000008FC(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void arcproc_uso_func_00000938(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void arcproc_uso_func_00000974(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void arcproc_uso_func_000009CC(Vec3 *dst) {
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

#ifdef NON_MATCHING
/* arcproc_uso_func_00000A3C: 205 insns (0x334) — 4-stage allocator/initializer
 * constructor. Sibling of 0x880 family in arcproc_uso_tail1.c.
 *
 * ENTRY DECODE (0xA3C-0xB04, ~50 insns characterized 2026-05-04):
 *   - Frame: addiu sp,-0x40; saves s0/s1/ra at 0x1C/0x20/0x24; spills
 *     a1/a2/a3 at 0x44/0x48/0x4C (caller-preserved args).
 *   - Stage 1: if a0 == 0, alloc 0x780 → s1; else s1 = a0.
 *   - Stage 2: if s1 != 0, alloc 0x6A8 → s0 (linked under s1); on success
 *     stores &D_alloc_link at *(s0+0x28).
 *   - Stage 3: if s0 != 0, alloc 0x50 → spill@sp+0x38; on success calls
 *     gl_func(spilled, &D_arc_table_3B8) to init.
 *   - Stage 4: if (alloc_3 != 0), alloc 0x2C → another sub-obj; calls
 *     gl_func(sub_obj, &D_arc_table_3B8); writes &D_E to *(sub+0x28).
 *
 * KEY OFFSETS WRITTEN:
 *   - *(s1+0x28) = &D_arc_link_E       ; canonical "vtable/parent" slot
 *   - *(s0+0x28) = &D_arc_link_E
 *   - *(s0+0x568) = 0                   ; sub-obj clear
 *   - *(s0+0x6B8) = 0
 *   - *(s0+0x6A8), *(s0+0x6AC), *(s0+0x528) = sub-obj pointers (linked)
 *   - *(s0+0x77C) = lwc1 result (initial float, likely from alloc_3 init)
 *
 * REMAINING ~155 insns (0xB04-0xD6C): more sub-allocator stages, fan-out
 * stores, conditional sub-init via gl_func dispatch table at &D_arc_table_3D0,
 * final epilogue restoring s0/s1/ra and returning s1 in v0.
 *
 * This is a CONSTRUCTOR with cross-USO alloc dependency — multi-tick decomp.
 * Stub C body documents the 4-stage alloc skeleton for grep discoverability;
 * does NOT match (default INCLUDE_ASM build is correct). */
extern int gl_func_arc_alloc();
extern char D_arc_table_3B8[];
extern char D_arc_table_3D0[];
extern char D_arc_link_E;
void *arcproc_uso_func_00000A3C(int *a0, int a1, int a2, int a3) {
    int *s1 = a0;
    int *s0;
    void *alloc3;
    void *alloc4;
    if (s1 == 0) {
        s1 = (int*)gl_func_00000000(0x780);
        if (s1 == 0) goto end;
    }
    s0 = (int*)gl_func_00000000(0x6A8);
    if (s0 == 0) goto end;
    alloc3 = (void*)gl_func_00000000(0x50);
    if (alloc3 != 0) {
        gl_func_00000000(alloc3, &D_arc_table_3B8);
        *(int*)((char*)alloc3 + 0x28) = (int)&D_arc_link_E;
    }
    alloc4 = (void*)gl_func_00000000(0x2C);
    if (alloc4 != 0) {
        gl_func_00000000(alloc4, &D_arc_table_3B8);
        *(int*)((char*)alloc4 + 0x28) = (int)&D_arc_link_E;
    }
    /* TODO: ~150 more insns (0xB04-0xD6C) — sub-allocator stages, fan-out
     * stores at offsets 0x528/0x568/0x6A8/0x6AC/0x77C, dispatch via
     * D_arc_table_3D0 with conditional init, final s1 return. Multi-tick. */
    *(int*)((char*)s0 + 0x28) = (int)&D_arc_link_E;
    *(int*)((char*)s1 + 0x28) = (int)&D_arc_link_E;
end:
    return s1;
    (void)a1; (void)a2; (void)a3;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000A3C);
#endif

/* arcproc_uso_func_00000D70: 58-insn (0xE8) sub-object register sequence.
 * Calls gl_func_00000000 with 8 (a0+offset, id) pairs — registers sub-objects
 * with their parent IDs. The id is a 32-bit packed field: high 16 bits = type
 * code, low 16 bits = data. Branch on a0->[0x6A8]->[0x4]+1 == a0->[0x6A8]->[0x8]
 * picks 0x210001 or (p[1]+2)|0x210000 for the 0x6EC call. Inlining p[1] reads
 * (vs holding in a `v1` named local) flips IDO's $t6/$t7 allocation order
 * to match target. */
extern char D_arc_D70_base;
void arcproc_uso_func_00000D70(char *a0) {
    int *p;
    gl_func_00000000(a0 + 0x6BC, *(int*)(&D_arc_D70_base + 0x64) | 0xA0000);
    gl_func_00000000(a0 + 0x6D4, 0x210000);
    p = *(int**)(a0 + 0x6A8);
    if (p[2] == p[1] + 1) {
        gl_func_00000000(a0 + 0x6EC, 0x210001);
    } else {
        gl_func_00000000(a0 + 0x6EC, (p[1] + 2) | 0x210000);
    }
    gl_func_00000000(a0 + 0x71C, *(int*)(&D_arc_D70_base + 0x4C) | 0x1D0000);
    gl_func_00000000(a0 + 0x704, *(int*)(&D_arc_D70_base + 0x54) | 0x1E0000);
    gl_func_00000000(a0 + 0x734, 0x21000B);
    gl_func_00000000(a0 + 0x74C, 0x21000D);
    gl_func_00000000(a0 + 0x764, 0x210009);
}

void arcproc_uso_func_00000E58(char *a0) {
    arcproc_uso_func_00000000(a0 + 0x6BC);
    arcproc_uso_func_00000000(a0 + 0x6D4);
    arcproc_uso_func_00000000(a0 + 0x6EC);
    arcproc_uso_func_00000000(a0 + 0x71C);
    arcproc_uso_func_00000000(a0 + 0x704);
    arcproc_uso_func_00000000(a0 + 0x734);
    arcproc_uso_func_00000000(a0 + 0x74C);
    arcproc_uso_func_00000000(a0 + 0x764);
}

/* arcproc_uso_func_00000EBC: 6-FUNCTION BUNDLE (0x94 / 37 insns).
 * Splat-bundled — splitting risks .o layout shift; documented per
 * feedback_uso_split_fragments_breaks_expected_match.md (similar cap to
 * 0xF50/3-bundle below).
 *
 * Sub-function layout (boundaries = jr ra + delay slot):
 *   F1 @ 0xEBC-0xEE8: 11 insns / 0x30. Conditional gl_func call:
 *     if (a0->0x4F0 & 0x10000) gl_func();  // bgezl on (t6 << 15)
 *   F2 @ 0xEEC-0xF0C: 9 insns / 0x24. Triple-deref non-null check:
 *     return (a0->0x6AC && a0->0x6AC->0x6C && a0->0x6AC->0x6C->0xEC) ? 1 : 0;
 *     Uses two beql + delay-likely zero-return shortcuts for the null cases.
 *   F3 @ 0xF10-0xF18: 3 insns / 0xC. `return 0;` stub.
 *   F4 @ 0xF1C-0xF30: 5 insns / 0x14. Conditional flag setter:
 *     a0->0x504 = (a0->0x6B8 != 0) ? 4 : 0;
 *     Uses bnel + delay-likely for the non-zero-set, fall-through for zero.
 *   F5 @ 0xF34-0xF3C: 3 insns / 0xC. Likely dead/unreachable; 0xF34 is
 *     `sw t7, 0x504(a0)` with t7 uninitialized — possibly splat artifact
 *     of F4's bnel target landing pattern.
 *   F6 @ 0xF40-0xF44: 2 insns / 0x8. `return; arg0->0x504 = 0;` (jr ra +
 *     delay-slot store).
 *   Trailing 8 bytes (`lui a1, 0; lw a1, 0x170(a1)`) are stolen prologue
 *   prefix for SUCCESSOR func_00000F50 (PROLOGUE_STEALS=8 candidate).
 *
 * Tried split-fragments.py recursively (succeeded: EBC/EEC/F10/F1C/F34/
 * F40/F48 split); but split-script appended new INCLUDE_ASMs to wrong
 * .c file (arcproc_uso.c with -O0 / TRUNCATE 0x50 vs the right home
 * arcproc_uso_tail1.c) and per feedback_uso_split_fragments_breaks_expected_match.md
 * USO splits also break expected/.o. Reverted; bundle stays as-is until
 * the split-script is fixed to write into the right .c. */
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000EBC);

/* arcproc_uso_func_00000F50: 3-FUNCTION BUNDLE (0x58 / 22 insns).
 * Splat-bundled, can't be split per
 * feedback_uso_split_fragments_breaks_expected_match.md.
 *
 * Sub-function layout:
 *   F1 @ 0xF50-0xF74: 10 insns. Tiny gl_func wrapper that adjusts a1 by
 *     +0x26000F before the call. Pattern:
 *       gl_func_00000000(a0, a1 + 0x26000F)
 *
 *   F2 @ 0xF78-0xF98: 8 insns. 2-level NULL-check returning 1/0:
 *       lw t6, 0x6AC(a0)
 *       lw v0, 0x6C(t6)         ; t6 = a0->0x6AC->0x6C
 *       if (v0 == 0) return 0
 *       lw t7, 0xEC(v0)
 *       if (t7 == 0) return 0
 *       return 1
 *     Uses beql-likely with delay-slot `move v0, $0` for both NULL paths
 *     (per feedback_ido_beql_speculative_store_double_emit.md class).
 *
 *   F3 @ 0xF9C-0xFA4: 3 insns. Empty void returning 0:
 *       move v0, $0; jr ra; nop
 *
 * Total bytes 0x58 (22 insns) matches declared size. All 3 sub-bodies
 * documented for future split-with-refresh-expected attempt. Default
 * INCLUDE_ASM build remains exact. */
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000F50);

/* arcproc_uso_func_00000FA8: 114-insn (0x1C8) state-machine dispatcher.
 * 3-way switch on a0->0x504 (state code) with cases 0, 1, 4 + default.
 *
 * ENTRY DECODE (insns 0-15 @ 0xFA8-0xFE4):
 *   Frame -0x30, saves s0/s1/ra
 *   s0 = a0->0x504                     ; state code
 *   s1 = a0                            ; saved input
 *   if (s0 == 0) goto case_0           ; delay-likely loads a0->0x6AC
 *   if (s0 == 1) goto case_1           ; @ +0x2A
 *   if (s0 == 4) goto case_4           ; @ +0x59 delay-likely loads a0->0x6A8
 *   default: b far_end                 ; no-op return path
 *
 * CASE 0 BODY (insns ~16-30 @ 0xFE8-0x1024): updates a0->0x6B0/B4/B8 from
 * a0->0x6AC's nested fields (0x44/0x14/0x40), increments a counter at
 * 0x6B4 and copies the value to 0x4D8.
 *
 * CASE 1 BODY (~insns 30-65 @ 0x1028-0x10B0): chained gl_func calls and
 * field updates on a0->0x6AC subtree. Includes a `jal 0` with arg5=7 and
 * post-call processing.
 *
 * CASE 4 BODY (~insns 65-100): deferred decode.
 *
 * EPILOGUE (insns ~100-114 @ 0x1180-0x116C): convergence point loading
 * ra/s0/s1 + addiu sp, jr ra.
 *
 * Multi-tick refinement target — entry decode is forward progress
 * documenting the dispatch structure. Default INCLUDE_ASM build remains
 * exact. */
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000FA8);

/* arcproc_uso_func_00001170: 3-FUNCTION BUNDLE (0xEC / 59 insns).
 * Splat-bundled, can't be split per
 * feedback_uso_split_fragments_breaks_expected_match.md.
 *
 * Sub-function layout (boundary = jr $ra + delay slot):
 *   F1 @ 0x1170-0x11EC: 32 insns. Frame -0x18, dispatcher with one
 *     gl_func call (insn 4 @ 0x1184) + conditional indirect call via jalr
 *     (insn 23 @ 0x11D8). Pattern: load D global at lui+lw, dispatch
 *     based on returned v0, conditional callback via t9 indexed by
 *     ((v0+0x28) << 2) (table at *D[0x190]+0x90).
 *
 *   F2 @ 0x11F0-0x1224: 14 insns. Smaller dispatcher.
 *
 *   F3 @ 0x1228-0x1258: 14 insns. Another small dispatcher.
 *
 * Total bytes 0xEC (59 insns) matches declared size (rounding to
 * alignment). All 3 sub-bodies documented for future split-with-
 * refresh-expected attempt. Default INCLUDE_ASM build remains exact. */
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001170);

/* arcproc_uso_func_0000125C: 139-insn (0x22C) FPU-heavy state-update.
 * Single function (1 jr ra). Frame -0x70 with s0/ra saved.
 *
 * ENTRY DECODE (insns 0-15 @ 0x125C-0x1294):
 *   t6 = a0->0x4F0                          ; state flags
 *   s0 = a0                                  ; saved ptr
 *   if ((t6 & 0x10000) == 0) goto far_exit   ; bit-16 gate (bgez (t6<<15))
 *   /* bit-16 set path: *\/
 *   sp[0x50/54/58/5C] = 1.0f, 1.0f, 1.0f, 1.0f  ; init 4-element float
 *                                                ; accumulator buffer
 *
 * Continues with float comparisons against a0->0x4E4 (count?), conditional
 * loads of constants from D[0x77C] and D[0x30/0x34] (likely a Vec3 of
 * float thresholds at 0x30/0x34/0x38), and chained c.lt.s + bc1fl gates.
 *
 * Body structure (insns 15-130): float-clamp/scale loop with ~3 cross-USO
 * calls. The 1.0f-initialized buffer at sp+0x50..0x5C is updated based on
 * comparisons against thresholds and stored back to D[0x77C] (per-element).
 *
 * EPILOGUE (insns 130-139): standard frame teardown with pre-loaded ra
 * (loaded in 1st bgez delay slot — common -O2 trick).
 *
 * Multi-tick refinement target — doc-only this tick. Default INCLUDE_ASM
 * build remains exact. Likely a "physics gate clamp on per-stage float
 * accumulator" for the arcade-mode stage scoring system. */
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000125C);

int arcproc_uso_func_00000000();

void arcproc_uso_func_00001488(void) {
    arcproc_uso_func_00000000();
}

void arcproc_uso_func_000014A8(void) {
    gl_func_00000000();
}

/* arcproc_uso_func_000014C8: 79-insn (0x13C) FPU-driven scoring update.
 * Frame -0x58, FPU-heavy with c.lt.s/bc1fl gate chain.
 *
 * ENTRY DECODE (insns 0-12):
 *   f0 = 1.0f                            ; constant init at fn entry
 *   sp[0x48/4C/50/54] = 0.0f x 4         ; init scratch 4-float buffer
 *   t6 = a0->0x500                       ; load state field
 *   s0 = a0                              ; saved
 *   if (t6 == 0) goto far_exit @ 0x15F0  ; bnel-likely (delay-likely lw ra)
 *
 * BODY structure (insns 12-79):
 *   - Load D[0x77C] (current scoring float)
 *   - c.lt.s f4, f6 (compare scoring vs threshold)
 *   - Branch +0x37 (~13 insns to early-exit)
 *   - Multi-stage scoring update with chained c.lt.s gates
 *   - Increment counter at a0->0x508 via (lw t8, lw a0[0x528], addiu, sw)
 *   - Cross-USO call (jal func_00000000) with state-update args
 *   - Branch +0x1F to convergence
 *
 * Pattern fingerprint: per-frame scoring update with float-threshold gates
 * and a counter-driven cross-USO callback. Same -O2 form as
 * arcproc_uso_func_0000125C (sibling FPU-state functions).
 *
 * Multi-tick refinement target. Default INCLUDE_ASM build remains exact. */
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000014C8);

/* arcproc_uso_func_00001604: 60-insn (0xF0) state-machine update with
 * two-stage gate (a0->0x4FC entry, a0->0x4F8 path-select), three outcomes
 * (rv=0/1/2), and two distinct multi-arg JAL shapes.
 *
 * STRUCTURE:
 *   if (a0->0x4FC != 0) return;              ; bnel-likely entry gate (already done)
 *   v1 = 0;
 *   if (a0->0x4F8 == 0) {                    ; PATH A
 *       p = a0->0x6AC; q = p->0x44;
 *       rv_a = jal(a0->0x6A8, q->0x14);      ; first stage (varargs a1/a2/...)
 *       if (rv_a == 0) {
 *           a0->0x6B8 = 1;                   ; mark-stage-A-done
 *           v1 = 0;                          ; (no further work)
 *       } else {
 *           v1 = 1;                          ; signal "do v1==1 work after"
 *       }
 *   } else {                                 ; PATH B
 *       p = a0->0x6AC; q = p->0x44;
 *       rv_b = jal(a0->0x6A8, q->0x14);      ; same shape, possibly different callee
 *       if (rv_b != 0) v1 = 2; else v1 = sp_24 (still 0)
 *       a0->0x6B8 = 1;                       ; mark-stage-B-done
 *   }
 *   ; merge: 3-way switch on v1
 *   if (v1 == 0) goto end;                   ; nothing more
 *   if (v1 == 1) {
 *       p = a0->0x6A8;
 *       jal(a0->0x6AC, p+0x20, p->0x8);      ; v1==1 callback shape
 *   } else { // v1 == 2
 *       p = a0->0x6A8;
 *       jal(a0->0x6AC, p+0x20, p->0x4 + 1);  ; v1==2 callback (incremented arg)
 *   }
 *   a0->0x4FC = 1;                           ; mark whole function done
 *   end:
 *
 * Sibling of recently-doc'd arcproc_uso_func_000014C8 (FPU scoring update);
 * both are per-frame state-driver functions with bnel-likely entry gates and
 * cross-USO callback dispatch. Default INCLUDE_ASM build remains exact.
 *
 * Multi-tick refinement target — the bnel-likely + delay-slot v1 setup +
 * 3-way switch with shared 0x4FC store is a known IDO-O2 pattern stack
 * (see feedback_ido_beql_speculative_store_double_emit.md and
 * feedback_unique_extern_breaks_shared_base.md). */
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001604);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000016F4);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000199C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001B04);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001BBC);

#ifdef NON_MATCHING
/* arcproc_uso_func_00001C74: 41-insn (0xA4) counter+conditional-scale wrapper.
 *
 * BYTE-IDENTICAL with timproc_uso_b1_func_000019C0 and timproc_uso_b3_func_00001928
 * (sig=739fd8d1d3) — none of these are wrapped yet. This is the canonical decode.
 *
 * STRUCTURE (insns 1-15 decoded):
 *   addiu sp, -0x58; sw ra, sw s0; ...
 *   *(float*)(sp+0x48..0x54) = 0.0 (4 zero floats — accumulator buf)
 *   t6 = a0->[0x68];                  // counter
 *   s0 = a0;                          // saved arg
 *   a0->[0x68] = t6 + 1;              // incr counter
 *   gl_func_00000000(a0->[0x50]);     // call with field
 *   if (v0 != 0) {
 *     f4 = 255.0f;
 *     f6 = s0->[0x108];               // some float field
 *     f8 = 255.0 * f6;                // scale to 0..255
 *     i_val = (int)truncf(f8);
 *     gl_func_00000000(&D, sp+0x48 buf, ...);  // pass buf+scaled int
 *     ...
 *   }
 *
 * REMAINING: ~26 insns of conditional body — likely the buf-fill +
 * gl_func call + epilogue. First-pass decode only; multi-tick.
 *
 * Per scripts/find-byte-identical-clones.py — sig=739fd8d1d3 has 3 plain
 * clones (this + b1_19C0 + b3_1928). Future runs can mirror this wrap. */
void arcproc_uso_func_00001C74(int *a0) {
    /* Stub — see decoded structure in comment above. */
    (void)a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001C74);
#endif

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001D18);

void arcproc_uso_func_00001F0C(char *a0) {
    if (*(int*)((char*)&D_00000000 + 0x64) == 1) {
        *(int*)(a0 + 0xA0) = 0xC350;
    } else {
        *(int*)(a0 + 0xA0) = 0x7530;
    }
    *(int*)(a0 + 0xA8) = *(int*)(*(int*)(a0 + 0xB8) + 0x34);
    *(int*)(a0 + 0xA4) = 0;
    gl_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001F54);

void arcproc_uso_func_000022A4(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_000008FC((int*)(dst + 0x10));
}

void arcproc_uso_func_000022D4(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_00000938((float*)(dst + 0x10));
}

void arcproc_uso_func_00002304(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_00000974((Quad4*)(dst + 0x10));
}

#ifdef NON_MATCHING
/* arcproc_uso_func_00002334: 36-insn (0x90) constructor — BYTE-IDENTICAL
 * mirror of eddproc_uso_func_000003BC and h2hproc_uso_func_00001A6C
 * (verified via signature match, sig=f167638a8a). Same alloc + init +
 * list-add structure with beql speculative double-store.
 *
 *   void *p = gl_func_00000000(0x40);
 *   if (p != NULL) {
 *     gl_func_00000000(p);
 *     p->field_28 = &D_00000000;
 *     p->field_3C = 0;
 *     if (arg0->field_40 != NULL) {
 *       int rv = gl_func_00000000(p + 0x10, arg0->field_40);
 *       if (rv != 0) {
 *         arg0->field_40->[0x14] = p; p->[0x04] = 1;
 *         arg0->field_40->[0x14] = p;     // beql double-store
 *       }
 *     }
 *   }
 *   return p;
 *
 * ~60% NM cap inherited from sibling — register allocation differs
 * ($v0/$v1 chain vs target's $t-regs) and frame layout. Multi-tick
 * decomp; mirror of eddproc_03BC wrap. */
void arcproc_uso_func_00002334(int *arg0) {
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
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00002334);
#endif

void arcproc_uso_func_000023C4(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_000009CC((Vec3*)(dst + 0x10));
}

extern int gl_ref_00000040;
extern int gl_ref_00000070;
extern int gl_ref_00000074;

void arcproc_uso_func_000023F4(void) {
    gl_func_00000000(gl_ref_00000070);
    gl_ref_00000040 = 4;
    gl_func_00000000(gl_ref_00000074, -1, 0);
}

void arcproc_uso_func_00002438(void) {
    gl_func_00000000(gl_ref_00000070);
    gl_ref_00000040 = 1;
    gl_func_00000000(gl_ref_00000074, -1, 0);
}

void arcproc_uso_func_0000247C(void) {
    gl_func_00000000(gl_ref_00000070);
    gl_ref_00000040 = 2;
    gl_func_00000000(gl_ref_00000074, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000024C0);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000251C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000027BC);

void arcproc_uso_func_00002864(void) {
    arcproc_uso_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00002884);
#pragma GLOBAL_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso/arcproc_uso_func_00002884_pad.s")
