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

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000F50);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000FA8);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001170);

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
