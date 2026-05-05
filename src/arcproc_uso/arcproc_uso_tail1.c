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

/* arcproc_uso_func_00000880: 31-insn (0x7C) state-conditional update.
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

#ifdef NON_MATCHING
/* arcproc_uso_func_00000D70: 58-insn (0xE8) sub-object register sequence —
 * sibling of 0x880 family. Calls gl_func_00000000 with 8 (a0+offset, id)
 * pairs — likely "register sub-objects with their parent IDs". The id is
 * a 32-bit packed field: high 16 bits = type code, low 16 bits = data
 * (loaded from D extern OR a constant). One conditional branch on
 * a0->[0x6A8]->[0x4]+1 == a0->[0x6A8]->[0x8] determines whether the 0x6EC
 * call uses 0x210001 or (counter+2) | 0x210000.
 *
 * D extern offsets: 0x64 (used twice) and 0x4C, 0x54.
 *
 * Stub C body — won't match exactly without per-offset unique externs +
 * IDO-CSE-busting casts (per feedback_unique_extern_with_offset_cast_breaks_cse.md).
 * Documents structure for next pass. */
extern int D_arc_D70_64;
extern int D_arc_D70_4C;
extern int D_arc_D70_54;
void arcproc_uso_func_00000D70(char *a0) {
    int *p;
    int v1;
    gl_func_00000000(a0 + 0x6BC, D_arc_D70_64 | 0xA0000);
    gl_func_00000000(a0 + 0x6D4, 0x210000);
    p = *(int**)(a0 + 0x6A8);
    v1 = p[1];
    if (p[2] == v1 + 1) {
        gl_func_00000000(a0 + 0x6EC, 0x210001);
    } else {
        gl_func_00000000(a0 + 0x6EC, (v1 + 2) | 0x210000);
    }
    gl_func_00000000(a0 + 0x71C, D_arc_D70_4C | 0x1D0000);
    gl_func_00000000(a0 + 0x704, D_arc_D70_54 | 0x1E0000);
    gl_func_00000000(a0 + 0x734, 0x21000B);
    gl_func_00000000(a0 + 0x74C, 0x21000D);
    gl_func_00000000(a0 + 0x764, 0x210009);
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000D70);
#endif

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
