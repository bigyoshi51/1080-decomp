#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

#ifdef NON_MATCHING
/* timproc_uso_b3_func_00000000: byte-identical mirror of
 * timproc_uso_b1_func_00000000 (sig=c98ad3f0ab). Standard 4-byte int
 * reader template wrapped in a `b +1` epilogue branch (composite -O0
 * shape). Same Yay0-compressed segment blocker — wrap is for grep
 * discoverability per the established pattern. */
/* K&R def so same-TU callers passing varying arg counts type-check in
 * NON_MATCHING build. See feedback_knr_def_for_inconsistent_arg_callers.md. */
void timproc_uso_b3_func_00000000(dst) int *dst; {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000000);
#endif

#ifdef NON_MATCHING
/* Quad4-reader template at -O0 (25 insns, 0x64) — byte-identical asm to
 * mgrproc_uso_func_0000004C and timproc_uso_b1_func_0000004C. Standard
 * 16-byte accessor compiled at -O0 per
 * feedback_uso_accessor_template_reuse.md.
 *
 * BLOCKED: timproc_uso_b3 is Yay0-compressed (per
 * feedback_uso_yay0_compressed.md); the file-split recipe for -O0 override
 * doesn't apply because the Yay0 rule consumes only one .o. */
void timproc_uso_b3_func_0000004C(Quad4 *dst) {
    volatile Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *(Quad4*)dst = *(Quad4*)&buf;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_0000004C);
#endif

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000000B0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000005A4);

#ifdef NON_MATCHING
/* 21-insn -O0 cleanup wrapper. Single gl_func + zero a0[0] + zero D[0x14C].
 * -O0 indicators: unfilled jal delay + `b +1; nop` BBL marker.
 *
 * Same -O0-cap class as arcproc_uso_func_00000748 / mgrproc_uso_func_000009A8.
 * BLOCKED by Yay0 pipeline (timproc_uso_b3 is compressed; file-split recipe
 * doesn't apply). Default build INCLUDE_ASM matches; wrap is for grep
 * discoverability per the established -O0-cap pattern. */
void timproc_uso_b3_func_0000065C(int *a0) {
    gl_func_00000000((int*)a0[0], 3);
    a0[0] = 0;
    *(int*)((char*)&D_00000000 + 0x14C) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_0000065C);
#endif

extern int D_b3_06B0_a;
extern int *D_b3_06B0_b;     /* pointer-typed: 2nd call passes (*D_b3_06B0_b)[0x6A8/4] */
extern int D_b3_06B0_c;
extern int D_b3_06B0_d;
void timproc_uso_b3_func_000006B0(void) {
    gl_func_00000000(D_b3_06B0_a);
    gl_func_00000000(D_b3_06B0_b[0x6A8/4]);
    gl_func_00000000(D_b3_06B0_c);
    gl_func_00000000(&D_b3_06B0_d);
}

extern int D_b3_06FC_a;
extern int D_b3_06FC_b;
extern int D_b3_06FC_c;
extern int D_b3_06FC_d;
void timproc_uso_b3_func_000006FC(void) {
    gl_func_00000000(D_b3_06FC_a);
    gl_func_00000000(D_b3_06FC_b);
    gl_func_00000000(&D_b3_06FC_c);
    gl_func_00000000(D_b3_06FC_d);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3/timproc_uso_b3_func_000006FC_pad.s")

/* Chain sibling of 0x790, 0x7D4, 0x818 (state-store + 1-call wrapper,
 * prologue-stolen v0). t7=1 here. Same recipe as b1 chain 0x734-0x800. */
extern int D_state_b3_74C;
void timproc_uso_b3_func_0000074C(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 1;
    gl_func_00000000(D_state_b3_74C, -1, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3/timproc_uso_b3_func_0000074C_pad.s")

/* Chain sibling: t7=2. */
extern int D_state_b3_790;
void timproc_uso_b3_func_00000790(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 2;
    gl_func_00000000(D_state_b3_790, -1, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3/timproc_uso_b3_func_00000790_pad.s")

/* Chain sibling: t7=3. */
extern int D_state_b3_7D4;
void timproc_uso_b3_func_000007D4(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 3;
    gl_func_00000000(D_state_b3_7D4, -1, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3/timproc_uso_b3_func_000007D4_pad.s")

/* Prologue-stolen successor: predecessor func_000007D4's tail has lui+addiu
 * setting v0 = &D_00000000 (offsets 0x810/0x814 in 7D4's .s). Build pipeline
 * splices the redundant 8-byte prefix via PROLOGUE_STEALS in Makefile.
 * Use unique extern `D_state_b3_818` (mapped to 0x0) for the gl_func arg
 * to break IDO's &D-CSE -- target emits a fresh lui+lw at the call site
 * rather than reusing v0. Per feedback_ido_cse_d_loads_unflippable.md +
 * feedback_usoplaceholder_unique_extern.md. */
extern int D_state_b3_818;
void timproc_uso_b3_func_00000818(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 0xD;
    gl_func_00000000(D_state_b3_818, -1, 0);
}

void timproc_uso_b3_func_00000854(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b3_func_00000890(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b3_func_000008CC(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void timproc_uso_b3_func_00000924(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000994);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000D60);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000DE4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000E60);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000FF4);

void timproc_uso_b3_func_00000000();

void timproc_uso_b3_func_00001090(int a0, char *a1) {
    timproc_uso_b3_func_00000000(a0, a1 + 0x00220000);
}

extern int gl_ref_00000040;
extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b3_func_000010B4(int a0) {
    gl_ref_00000040 = 9;
    gl_func_00000000(a0, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000010E4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001184);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001248);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000013B8);

#ifdef NON_MATCHING
/* timproc_uso_b3_func_00001660: 90-insn (0x168) 3-stage chained
 * allocator/constructor. Same pattern as eddproc_uso_func_0000025C —
 * gets/allocs 3 differently-sized objects (0x10C, 0xD4, 0x50 here), each
 * with a vtable-pointer set at +0x28 from a unique-extern. Defensive
 * null-checks at every stage create the documented frame-size cap (~60%).
 *
 * Structure (sketch, args inferred):
 *   void f(int *a0, int a1, int a2) {
 *       int *p1 = a0 ? a0 : alloc(0x10C);   if (!p1) return;
 *       int *p2 = (alloc passthrough) ? : alloc(0xD4);
 *       if (p2) {
 *           int *p3 = alloc(0x50);
 *           if (p3) {
 *               gl_func(p3, &D_NNN_3_template);
 *               p3->0x28 = (vtable_3);
 *           }
 *           p2->0x28 = (vtable_2);
 *       }
 *       p1->0x28 = (vtable_1);
 *   }
 *
 * Per feedback_eddproc_uso_constructor_frame_cap.md (eddproc 0x025C wrap),
 * this is a known structural cap class: defensive null-checks generate
 * dead-code branches that target's IDO-emit doesn't have, plus 8-byte
 * frame-size diff (target 0x20 vs C-emit 0x28). INSN_PATCH-blocked per
 * size mismatch.
 *
 * Default INCLUDE_ASM build matches; this wrap is for grep/discoverability. */
extern int gl_func_00000000();
extern char D_00000000;
void timproc_uso_b3_func_00001660(int *a0, int a1, int a2) {
    int *p1 = a0;
    int *p2;
    int *p3;
    if (p1 == 0) {
        p1 = (int*)gl_func_00000000(0x10C);
        if (p1 == 0) return;
    }
    p2 = (int*)gl_func_00000000(0xD4, p1, a1);
    if (p2 != 0) {
        p3 = (int*)gl_func_00000000(0x50);
        if (p3 != 0) {
            gl_func_00000000(p3, (char*)&D_00000000 + 0x3DC);
            *(int*)((char*)p3 + 0x28) = (int)&D_00000000;
        }
        *(int*)((char*)p2 + 0x28) = (int)&D_00000000;
    }
    *(int*)((char*)p1 + 0x28) = (int)&D_00000000;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001660);
#endif

void timproc_uso_b3_func_000017C8(int *a0) {
    if (gl_func_00000000(*(int*)(&D_00000000 + 0x190)) == 0) return;
    if (gl_func_00000000(&D_00000000, 0x40100) == 0) return;
    if (gl_func_00000000(a0[0x50/4]) != 0) {
        a0[0x60/4] = 1;
    } else {
        gl_func_00000000(a0, -1, 0);
    }
}

void timproc_uso_b3_func_0000183C(int *a0) {
    int *p;
    gl_func_00000000(a0);
    p = (int*)a0[0xD4/4];
    gl_func_00000000(p, 0x8C, *(int*)((char*)p + 0x6AC));
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001870);

#ifdef NON_MATCHING
/* timproc_uso_b3_func_00001928: byte-identical mirror of
 * arcproc_uso_func_00001C74 (sig=739fd8d1d3, 41-insn 0xA4 counter+
 * conditional-scale wrapper).
 *
 * Per scripts/find-byte-identical-clones.py — see arcproc_uso_func_00001C74's
 * wrap for canonical decode. Stub here for grep discoverability. */
void timproc_uso_b3_func_00001928(int *a0) {
    /* Stub — see canonical decode in arcproc_uso_func_00001C74 wrap. */
    (void)a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001928);
#endif

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000019CC);

/* Prologue-stolen successor: predecessor func_000019CC's tail has lui+lw
 * setting t6 = *(D+0x64). PROLOGUE_STEALS removes our redundant 8-byte
 * lui+lw prefix. Per feedback_combine_prologue_steals_with_unique_extern.md. */
extern int D_b3_1C28_state;
void timproc_uso_b3_func_00001C28(char *a0) {
    if (D_b3_1C28_state == 1) {
        *(int*)(a0 + 0xA0) = 50000;
    } else {
        *(int*)(a0 + 0xA0) = 30000;
    }
    *(int*)(a0 + 0xA8) = 0;
    *(int*)(a0 + 0xD8) = 1;
    gl_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001C68);

void timproc_uso_b3_func_0000205C(char *dst) {
    int tmp;
    timproc_uso_b3_func_00000854(&tmp);
    timproc_uso_b3_func_00000854((int*)(dst + 0x10));
}

void timproc_uso_b3_func_0000208C(char *dst) {
    int tmp;
    timproc_uso_b3_func_00000854(&tmp);
    timproc_uso_b3_func_00000890((float*)(dst + 0x10));
}

void timproc_uso_b3_func_000020BC(char *dst) {
    int tmp;
    timproc_uso_b3_func_00000854(&tmp);
    timproc_uso_b3_func_000008CC((Quad4*)(dst + 0x10));
}

#ifdef NON_MATCHING
/* timproc_uso_b3_func_000020EC: 36-insn (0x90) constructor — BYTE-IDENTICAL
 * mirror of eddproc_uso_func_000003BC (sig=f167638a8a, 5th clone of family).
 * Same alloc + init + list-add structure with beql speculative double-store.
 * ~60% NM cap inherited. Multi-tick decomp.
 *
 * Find via: scripts/find-byte-identical-clones.py */
void timproc_uso_b3_func_000020EC(int *arg0) {
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
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000020EC);
#endif

void timproc_uso_b3_func_0000217C(char *dst) {
    int tmp;
    timproc_uso_b3_func_00000854(&tmp);
    timproc_uso_b3_func_00000924((Vec3*)(dst + 0x10));
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3/timproc_uso_b3_func_0000217C_pad.s")

void timproc_uso_b3_func_000021B0(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 4;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

/* EXACT 2026-05-03. Recipe: 3 unique externs (D_b3_21F4_a/b/c) all mapped
 * to 0x0 in undefined_syms_auto.txt + offset cast in C — produces target's
 * 3-separate-lui shape (vs CSE'd shared-base form). Plus SUFFIX_BYTES=8 for
 * the trailing stolen-prologue tail (lui a0; lw a0, 0x148(a0)) for the
 * successor func_00002240. */
extern char D_b3_21F4_a;
extern char D_b3_21F4_b;
extern char D_b3_21F4_c;
void timproc_uso_b3_func_000021F4(void) {
    gl_func_00000000(*(int*)((char*)&D_b3_21F4_a + 0x208));
    *(int*)((char*)&D_b3_21F4_b + 0x40) = 6;
    gl_func_00000000(*(int*)((char*)&D_b3_21F4_c + 0x20C), -1, 0);
}

#ifdef NON_MATCHING
/* 97.58 % cap (2026-05-02). Prologue-stolen successor: predecessor
 * func_000021F4 ends with lui+lw setting a0 = *(D+0x148). Body is a
 * dual-branch state setter (logic correct, tried with int*+volatile +
 * unique externs at 0x208/0x20C + PROLOGUE_STEALS=8). Remaining diffs
 * are register choice only:
 *   - target uses $v0 for the cur-pointer base setup (lui+addiu+lw)
 *   - mine uses $v1 (because $v0 is dead after gl_func and IDO picks $v1)
 *   - target then uses $v1 for the constant `1` (since $v0 is taken for cur)
 *   - mine uses $a0 for that constant
 * Tried: removing the local capture of gl_func return value -- no change.
 * Tried (2026-05-02): adding explicit `int rc = gl_func(...); if (rc != 0)`
 * — REGRESSED to 0% because prologue-stolen splice mismatched (the explicit
 * capture changed IDO's prologue emit so PROLOGUE_STEALS=8 cut the wrong
 * 8 bytes). Confirms the inline-test-in-if form is load-bearing for the
 * prologue-stolen recipe; capture must happen INSIDE the if-test parens.
 * Sibling: byte-identical to timproc_uso_b1_func_00002030.
 *
 * (2026-05-03 re-measure) baseline drifted from 97.58% to 90.39% over
 * unrelated parallel-agent commits. TRIED `int *cur = (int*)D_cur_*;
 * cur[N] = ...` local-capture inside both branches to force $v0 alloc
 * — REGRESSED to 76.48%. The local-capture introduces an extra `or` move
 * after the lui+lw setup, displacing the target's tight inline-store form.
 * Cap stands at 90.39%; the v0/v1 register-pick is structural per IDO. */
extern int D_state_b3_2240;            /* 0x148 */
extern int D_call_b3_2240_a;           /* 0x208 */
extern int D_call_b3_2240_b;           /* 0x208 (separate symbol, breaks CSE) */
extern int * volatile D_cur_b3_2240;   /* 0x20C */
void timproc_uso_b3_func_00002240(void) {
    if (gl_func_00000000(((char*)D_state_b3_2240) + 4) != 0) {
        gl_func_00000000(D_call_b3_2240_a);
        D_cur_b3_2240[0x14] = 2;
        D_cur_b3_2240[0x16] = 1;
    } else {
        gl_func_00000000(D_call_b3_2240_b);
        D_cur_b3_2240[0x14] = 1;
        D_cur_b3_2240[0x16] = 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002240);
#endif

void timproc_uso_b3_func_000022BC(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 1;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b3_func_00002300(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 2;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b3_func_00002344(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 3;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

void timproc_uso_b3_func_00002388(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 0xD;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000023E4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002700);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_0000294C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002A44);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002C98);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002DF0);

#ifdef NON_MATCHING
/* timproc_uso_b3_func_00002EF0: 22-insn (0x58) prologue-stolen successor.
 *
 * Predecessor func_00002DF0 has a TRAILING `sll t6, a1, 2` (0x00057080) at
 * offset 0xFC of its declared 0x100 size — AFTER its epilogue (jr ra at
 * 0x002EE4, addiu sp at 0x002EE8). That trailing sll sets t6 = a1*4 BEFORE
 * fall-through to 2EF0, which then does `subu t6, t6, a1` (= a1*3) and
 * `sll t6, t6, 3` (= a1*24). Final t6 is the byte-offset for indexing into
 * a +0x70 table from &D_00000000.
 *
 * Decoded as 3-call wrapper indexed by a1:
 *   T *entry = (T*)((char*)&D + 0x70 + a1*24);
 *   gl_func(entry);
 *   gl_func(entry);
 *   gl_func(entry, 0xA0, a2, 3);
 *
 * Promotion path:
 *   (a) SUFFIX_BYTES on func_00002DF0 with 0x00057080 + decoded C body
 *       for the predecessor (predecessor is unmatched 0x100/64 insns).
 *       Cleanest per feedback_suffix_bytes_unblocks_4byte_stolen_prologue.md
 *       but blocked on predecessor decode.
 *   (b) PROLOGUE_STEALS=4 on func_00002EF0 with C that emits a redundant
 *       `sll, a1, 2` at start (recipe strips it). Single-function fix.
 *
 * Doc-wrap with decoded C body for now. Default INCLUDE_ASM build matches
 * via the .s file's bytes (including the predecessor's trailing sll). */
void timproc_uso_b3_func_00002EF0(int a0, int a1, int a2) {
    int spill;
    char *entry = (char*)&D_00000000 + 0x70 + a1 * 24;
    (void)a0;
    spill = (int)entry;
    gl_func_00000000(entry);
    gl_func_00000000((char*)spill);
    gl_func_00000000((char*)spill, 0xA0, a2, 3);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002EF0);
#endif

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002F48);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00003050);
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3/timproc_uso_b3_func_00003050_pad.s")

