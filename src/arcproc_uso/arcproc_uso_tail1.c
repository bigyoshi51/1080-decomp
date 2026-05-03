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
/* arcproc_uso_func_00000688: -O0-compiled init function (48 insns, 0xC0).
 * Initializes 8 fields of a0->8 and zeros a 5-int array at offset 0x20.
 *
 * -O0 indicators in target asm:
 *   - Tiny frame (addiu sp, -8) with no callee-save use
 *   - Re-loads `a0[2]` (= a0->8 ptr) for EACH field write (no caching)
 *   - Sets up loop counter `i` on stack (sw zero, 4(sp))
 *   - Trailing dead `b +1; nop` before epilogue (-O0 BBL marker)
 *
 * Decoded body:
 *   void f(int *a0) {
 *       int i;
 *       int *p = (int*)a0[2];        // a0->8
 *       p[0] = 1;
 *       p[1] = 0;
 *       p[2] = 5;
 *       p[3] = 2;
 *       p[4] = 0;
 *       p[5] = 3;
 *       p[6] = 1;
 *       p[7] = 4;
 *       p[0xD] = 0;                  // skip-write at 0x34
 *       for (i = 0; i < p[2]; i++)   // p[2] = 5 (loop bound)
 *           p[8 + i] = 0;            // zero array @ 0x20..0x33
 *   }
 *
 * 1080's arcproc_uso_tail1.c.o is built at -O2 default, so a C body
 * here would compile to wrong bytes (cached `p` reload, no dead b+1).
 * To match, would need file-split into arcproc_uso_o0_688.c with
 * `OPT_FLAGS := -O0` (per project_o1o2_split.md) — multi-tick
 * infrastructure work. Default build INCLUDE_ASM remains exact.
 *
 * Pattern fingerprint: looks like a state-machine table init for an
 * arcade-mode timer/scoring object. The constants 1/0/5/2/0/3/1/4
 * could be (state_id, count, total, mode_a, mode_b, mode_c, ..., flag)
 * — typed struct emerging once arcproc subsystem is fully decoded. */
void arcproc_uso_func_00000688(int *a0) {
    int i;
    int *p = (int*)a0[2];
    p[0] = 1;
    p[1] = 0;
    p[2] = 5;
    p[3] = 2;
    p[4] = 0;
    p[5] = 3;
    p[6] = 1;
    p[7] = 4;
    p[0xD] = 0;
    for (i = 0; i < p[2]; i++) {
        p[8 + i] = 0;
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
 * discoverability + reference. Mirror of h2hproc_uso_func_00000274. */
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

#ifdef NON_MATCHING
/* arcproc_uso_func_00000880: 31-insn (0x7C) state-conditional update.
 * 3 cross-USO calls + chained indirection through 3 distinct globals.
 *
 * Decoded body:
 *   1. gl_func_00000000(*D_X)
 *   2. v0 = gl_func_00000000(*(int*)((char*)*(int**)((char*)D_Y + 0x6AC) + 0x4C))
 *      (chain through D_Y indirection inlined to avoid named local p,
 *       which would shift IDO's reg alloc from t7 to v1)
 *   3. if (v0 != 0): D_Z[0x40] = 7; D_Z[0x44] = 9
 *      else:         D_Z[0x40] = 9
 *   4. gl_func_00000000(*D_X, 0, 0)
 *
 * 3 unique extern aliases (D_arc880_X/_Y/_Z all mapped to 0x0) per
 * feedback_unique_extern_with_offset_cast_breaks_cse.md to avoid IDO
 * &D-CSE collapsing them into one base. The named local `int *p`
 * regressed by allocating to v1; INLINING the chain expression into
 * the gl_func arg keeps it in t7 (matches target). 97.9% -> 99.2%.
 *
 * 99.19% NM. Remaining diffs are pure reloc-form (jal sym vs literal,
 * lui/lw %hi/%lo vs immediate). Refresh-expected would lift to 100%
 * but is blocked: 3 sibling NM-wraps in same .o (0x240/0x688/0x748)
 * would be falsely promoted to 100% by blanket `make expected`. To
 * land 100%, surgical per-function expected refresh required. */
extern int D_arc880_X;       /* 1st-jal arg + 4th-jal arg base */
extern char *D_arc880_Y;     /* indirection chain root */
extern char D_arc880_Z[];    /* output struct base (+0x40, +0x44) */
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
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000880);
#endif

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

/* arcproc_uso_func_00000A3C: 205-insn (0x334) constructor — dual
 * alloc-or-passthrough + main initialization body.
 *
 * ENTRY DECODE (insns 0-15 @ 0xA3C-0xA84):
 *   Frame -0x40, saves s0/s1/ra, spills a1/a2/a3 to caller-arg slots.
 *   s1 = a0 ? a0 : alloc(0x780)            ; if alloc fails, return (far jump)
 *   s0 = a1 ? a1 : alloc(0x6A8)            ; if alloc fails, recover at +0x1F
 *
 * Both alloc-or-passthrough patterns per
 * feedback_ido_alloc_or_passthrough_ternary.md but using s-regs (not v1)
 * because the values survive across many calls in the body.
 *
 * BODY (~190 insns @ 0xA88+): chained gl_func dispatch on the constructed
 * objects, multiple field initializations with constant pointers loaded
 * via lui+addiu chains (likely D_arcA3C_a/b/c globals = unique externs
 * needed). Returns the bigger struct (0x780 bytes) at s1.
 *
 * Multi-tick decomp expected. Default INCLUDE_ASM build remains exact.
 * NM build will be partial until full body decode + unique-extern
 * setup. Stub body documents the alloc-or-passthrough entry only. */
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int gl_func_TODO_arcA3C_body();
void *arcproc_uso_func_00000A3C(int *a0, int a1, int a2, int a3) {
    int *s1 = a0;
    int *s0;
    if (s1 == 0) {
        s1 = (int*)gl_func_00000000(0x780);
        if (s1 == 0) return 0;
    }
    s0 = (int*)a1;
    if (s0 == 0) {
        s0 = (int*)gl_func_00000000(0x6A8);
        if (s0 == 0) {
            /* TODO: alloc-2 fail recovery path */
            return s1;
        }
    }
    /* TODO: ~190 insns of body — chained gl_func dispatch on s0/s1 with
     * field initializations from D_arcA3C globals. */
    (void)a2; (void)a3;
    gl_func_TODO_arcA3C_body();
    return s1;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000A3C);
#endif

/* arcproc_uso_func_00000D70: 58-insn (0xE8) registration function.
 * Calls gl_func ~10 times with (s0+offsetN, encoded_id) pairs to
 * register sub-objects. s0 = a0 (input struct) saved to s-reg.
 *
 * Decoded structure:
 *   gl_func_00000000(s0+0x6BC, *D_X1[0x64] | 0xA0000)
 *   gl_func_00000000(s0+0x6D4, 0x210000)
 *   v0 = s0->0x6A8                                // sub-obj ptr
 *   v1 = v0->4
 *   t6 = v0->8
 *   if (t6 == v1+1):
 *       gl_func_00000000(s0+0x6EC, 0x210001)      // sequential case
 *   else:
 *       gl_func_00000000(s0+0x6EC, (v1+2) | 0x210000)  // gap case
 *   gl_func_00000000(s0+0x71C, *D_X2[0x4C])
 *   gl_func_00000000(s0+0x704, *D_X3[0x54])
 *   gl_func_00000000(s0+0x734, 0x21000B)
 *   gl_func_00000000(s0+0x74C, 0x21000D)
 *   gl_func_00000000(s0+0x764, 0x210009)
 *
 * Pattern: each gl_func gets a different sub-obj address
 * (s0+0x6BC..0x764, stride 0x18) and a 32-bit "type code" with the high
 * 16 bits encoding a category (0xA, 0x21, 0x1D, 0x1E) and low bits a
 * sub-id. Likely a sub-object initialization sweep — this constructor's
 * job is to register 10 distinct elements with the framework.
 *
 * Multi-tick refinement target — would need 3 unique-extern aliases
 * (D_arcD70_X1/X2/X3) per feedback_unique_extern_with_offset_cast_breaks_cse.md
 * + careful ordering of the v1+1/v1+2 branch. Default INCLUDE_ASM build
 * remains exact. */
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000D70);

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

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000014C8);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001604);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000016F4);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000199C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001B04);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001BBC);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001C74);

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

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00002334);

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

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000247C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000024C0);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000251C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000027BC);

void arcproc_uso_func_00002864(void) {
    arcproc_uso_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00002884);
#pragma GLOBAL_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso/arcproc_uso_func_00002884_pad.s")
