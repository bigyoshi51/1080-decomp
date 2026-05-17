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

#ifdef NON_MATCHING
/* timproc_uso_b3_func_000000B0: 0x4F4 (317 insns), 0x40-byte stack frame.
 * Boundary-checked 2026-05-08: one jr ra, so this is one real function.
 *
 * Sibling of timproc_uso_b1_func_000000B0. The entry is a 14-case dispatch
 * on a1 using a jump table, followed by per-case gl_func_00000000 calls and
 * stores to D[0x40]/D[0x44]/D[0x48]. Matching will need the same full
 * if/goto-chain rewrite as the b1 sibling because 1080's linker discards
 * normal C jump-table rodata.
 *
 * This first pass preserves the decoded entry/default shape for future
 * refinement while default builds continue to use the original asm. */
void timproc_uso_b3_func_000000B0(int *a0, int a1) {
    if ((unsigned int)a1 >= 14) return;
    (void)gl_func_00000000();
    (void)a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000000B0);
#endif

#ifdef NON_MATCHING
/* timproc_uso_b3_func_000005A4: byte-identical mirror of
 * timproc_uso_b1_func_000005A4 except the mode literal is 2 instead of 1.
 *
 * -O0 indicators match the b1 sibling: unfilled jal delay slots, saved s0 for
 * a short-lived return value, redundant `b +1; nop`, and a conservative stack
 * frame. Current -O2 NM build is 35.11% and 0x90 bytes vs target 0xB8, losing
 * the unfilled delay slots and conservative stores. BLOCKED by the Yay0
 * pipeline: timproc_uso_b3 is compressed, so the per-file -O0 split recipe
 * does not apply. Default build stays INCLUDE_ASM; wrap preserves the decoded
 * body for future tooling. */
void timproc_uso_b3_func_000005A4(int **arg0, int arg1, int arg2) {
    int handle = gl_func_00000000(2);
    int new_obj = gl_func_00000000(0, *(int*)((char*)&D_00000000 + 0x148), 2, arg2);
    *arg0 = (int*)new_obj;
    *(int*)((char*)&D_00000000 + 0x14C) = new_obj;
    gl_func_00000000(handle);
    if (arg1 != 0) {
        *(int*)((char*)*arg0 + 0x14) = 2;
    } else {
        *(int*)((char*)*arg0 + 0x14) = 0;
    }
    *(int*)((char*)&D_00000000 + 0x68) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000005A4);
#endif

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

/* timproc_uso_b3_func_00000D60: 33-insn (0x84) 5-call gl_func_00000000
 * dispatcher with computed (s0+offset, immediate-or-globalload) args.
 * First 2 calls use D[0x4C/0x54] OR'd with high-half flags 0x001D/0x001E;
 * latter 3 use precomputed 32-bit constants 0x0021_xxxx. */
void timproc_uso_b3_func_00000D60(char *a0) {
    gl_func_00000000(a0 + 0x6B4, *(int*)((char*)&D_00000000 + 0x4C) | 0x001D0000);
    gl_func_00000000(a0 + 0x6CC, *(int*)((char*)&D_00000000 + 0x54) | 0x001E0000);
    gl_func_00000000(a0 + 0x6FC, 0x0021000B);
    gl_func_00000000(a0 + 0x714, 0x0021000D);
    gl_func_00000000(a0 + 0x6E4, 0x00210009);
}

/* timproc_uso_b3_func_00000DE4: F1 (19-insn 5-call wrapper) + F2 + F3
 * splat-bundled sub-functions (0x7C total).
 *
 * 2026-05-07: promoted via SUFFIX_BYTES recipe (12 words / 0x30 bytes
 * absorbing F2 + F3) — sibling family of arcproc_uso_func_00000EBC,
 * gl_func_000070A0.
 *
 * F1 @ 0xDE4-0xE2C: 5-call passthrough wrapper.
 * F2 @ 0xE30-0xE50: triple-deref non-null check (returns 0/1 on
 *     a0->[0x6A8]->[0x6C]->[0xEC] != 0).
 * F3 @ 0xE54-0xE5C: `return 0;` 3-insn stub. */
extern int func_00000000();
void timproc_uso_b3_func_00000DE4(char *a0) {
    func_00000000(a0 + 0x6B4);
    func_00000000(a0 + 0x6CC);
    func_00000000(a0 + 0x6FC);
    func_00000000(a0 + 0x714);
    func_00000000(a0 + 0x6E4);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000E60);

/* timproc_uso_b3_func_00000FF4: F1 (32-insn 0x80) gate-then-update wrapper
 * + SUFFIX bundle (5-insn D[0x40]=9 stub at 0x1074 + 2-insn fragment at
 * 0x1088, latter is the start of the next function whose first 2 words got
 * pulled into this .s by splat). Promoted via SUFFIX_BYTES recipe (7 words /
 * 0x1C bytes) — sibling family of timproc_uso_b3_func_00000DE4 /
 * arcproc_uso_func_00000EBC.
 *
 * F1: gate=gl_func(a0->0x528). If non-zero set D[0x40]=0xC,D[0x44]=9.
 *     Else set D[0x40]=9. Tail: if(a0->0x4F8) gl_func(a0,-1,0); else a0->0x504=0. */
void timproc_uso_b3_func_00000FF4(char *a0) {
    if (gl_func_00000000(*(char**)(a0 + 0x528)) != 0) {
        *(int*)((char*)&D_00000000 + 0x40) = 0xC;
        *(int*)((char*)&D_00000000 + 0x44) = 9;
    } else {
        *(int*)((char*)&D_00000000 + 0x40) = 9;
    }
    if (*(int*)(a0 + 0x4F8) == 0) {
        *(int*)(a0 + 0x504) = 0;
    } else {
        gl_func_00000000(a0, -1, 0);
    }
}

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

/* timproc_uso_b3_func_000010E4: 40-insn (0xA0) gate + indirect-call helper.
 * b3 mirror of timproc_uso_b1_func_00001130 (just promoted this session
 * — see that wrap doc). Same recipe: \`gl_func(5)\` inner call + INSN_PATCH
 * for register-allocator deltas + SUFFIX_BYTES for stolen fall-through. */
void timproc_uso_b3_func_000010E4(int *self) {
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

/* timproc_uso_b3_func_00001184: 20-insn (func1 of the split bundle).
 *   if (a0->0x4FC == 0) { X(a0->0x6A8,0,1); X(a0->0x6A8); a0->0x4FC=1; }
 * orig a0 saved @sp+0x18, reloaded across the 2 calls. USO: call ->
 * func_00000000. */
void timproc_uso_b3_func_00001184(int *a0) {
    if (a0[0x4FC / 4] == 0) {
        func_00000000((int *)a0[0x6A8 / 4], 0, 1);
        func_00000000((int *)a0[0x6A8 / 4]);
        a0[0x4FC / 4] = 1;
    }
}

void timproc_uso_b3_func_000011D4(int *a0) {
    int *p;

    p = (int*)*(int*)((char*)a0[0x6A8 / 4] + 0x6C);
    p = (int*)((char*)p + 0x18);
    *p &= ~4;
    p = (int*)*(int*)((char*)a0[0x6A8 / 4] + 0x94);
    p = (int*)((char*)p + 0x18);
    *p &= ~4;
}

void timproc_uso_b3_func_0000120C(int *a0) {
    int *p;

    p = (int*)*(int*)((char*)a0[0x6A8 / 4] + 0x6C);
    p = (int*)((char*)p + 0x18);
    *p |= 4;
    p = (int*)*(int*)((char*)a0[0x6A8 / 4] + 0x94);
    p = (int*)((char*)p + 0x18);
    *p |= 4;
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001240);

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

/* timproc_uso_b3_func_00001870: byte-identical clone of
 * arcproc_uso_func_00001BBC (same FPU body: jal; reload a3; f2=0;
 * a0=a3->0xD4; lwc1 f0,OFF; sub.s D-const; bc1fl x3; 2 calls — only
 * data offsets differ: 0x72C/72(at)/1708 vs 1BBC's 0x77C/68/1712).
 * SAME stolen-prologue boundary: declared 0xB8 but real 0xB0; trailing
 * `lui at,0x3f80; mtc1 at,$f0` (=1.0f) @+0xB0/0xB4 is the successor's
 * stolen f0 prologue. Defer identically to arcproc_uso_func_00001BBC
 * (see its wrap in arcproc_uso_tail1.c + docs/MATCHING_WORKFLOW
 * forward-merge FPU-variant + clone-canonical exclusion). Do NOT
 * cold-re-derive: it's the 739fd8d1d3 clone family. Decode only
 * alongside the SUFFIX_BYTES+PROLOGUE_STEALS pair for this family. */
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
 * mirror of eddproc_uso_func_000003BC family (5th clone). Apply the
 * eddproc lever (volatile-ptr-to-arg + late head reload) per
 * docs/IDO_CODEGEN.md#feedback-ido-arg-addr-via-volatile-ptr-forces-caller-spill.
 * Expected to land in the 89% file-context band per
 * docs/IDO_CODEGEN.md#feedback-ido-file-context-affects-frame-size
 * (timproc_uso_b3.c is a large multi-function file). */
void *timproc_uso_b3_func_000020EC(int *arg0) {
    int *p;
    int *head;
    volatile int **p_arg0;
    p_arg0 = (volatile int**)&arg0;
    p = (int*)gl_func_00000000(0x40);
    if (p != 0) {
        gl_func_00000000(p);
        *(int*)((char*)p + 0x28) = (int)&D_00000000;
        *(int*)((char*)p + 0x3C) = 0;
    }
    head = (int*)((int*)*p_arg0)[0x10];
    if (head != 0) {
        gl_func_00000000((char*)p + 0x10, head);
        if (*(int*)((char*)head + 0x14) != 0) {
            *(int*)((char*)p + 0x4) = 1;
        }
        *(int*)((char*)head + 0x14) = (int)p;
    }
    return p;
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

/* timproc_uso_b3_func_0000294C - verified structural decode (0xF8,
 * 62 insns, state dispatcher + record-vtable dispatch).
 *   void timproc_uso_b3_func_0000294C(St *a2) {
 *       switch (a2->0x50) {
 *       case 0:
 *           if (gl_func_00000000(&D_00000000, 0x40100) == 0)
 *               return;
 *           q   = a2->0x48;
 *           rec = (char*)q + q->0x7C * 0x28;       // 0x28-stride
 *           if (rec->0x90 == 0) return;            // no handler
 *           if (rec->0x88 != 0) {
 *               gl_func_00000000(5);
 *               *(void**)&D_a = a2->0x48;          // publish ctx
 *               *(void**)&D_b = a2;
 *               q = a2->0x48;
 *               rec = (char*)q + q->0x7C * 0x28;
 *               (*(fn)rec->0x90)();                // vtable dispatch
 *           } else {
 *               gl_func_00000000(165);
 *           }
 *           return;
 *       case 1:
 *       case 2:
 *           gl_func_00000000(a2);
 *           return;
 *       default:
 *           return;
 *       }
 *   }
 * Struct-typing reference: a2->0x50 (80) s32 state selector (0 =
 * active/record path, 1|2 = simple forward, else no-op); a2->0x48
 * (72) ptr to a record container; container->0x7C (124) s32 current
 * record index; record = container + idx*0x28 (the recurring
 * 0x28-stride record array, cf. func_00010AB0); record->0x88 (136)
 * s32 = ready/arm gate, record->0x90 (144) = handler fn ptr (vtable
 * dispatch when armed). Globals &D_a/&D_b (offsets 520/524 of a &D
 * block) published as {ctx = a2->0x48, owner = a2} before the
 * dispatch. gl_func_00000000(&D,0x40100) = a gated precondition;
 * gl_func_00000000(165) / (5) / (a2) = reloc callbacks. Caps <80:
 * switch (beq chain) + record-vtable jalr + 4x gl_func_00000000
 * reloc + &D-global publishes. Full body INCLUDE_ASM-preserved
 * (.s = source of truth). INCLUDE_ASM (no episode; tautology-trap
 * rule). */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_0000294C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002A44);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002C98);

#ifdef NON_MATCHING
/* timproc_uso_b3_func_00002DF0: 64-insn (0x100) grid-render setup.
 *
 * Structure:
 *   1. Copy 5 ints from D[0x4A0..0x4B0] into a local stack buf[5]
 *   2. Initial setup call: gl_func(&D + 0, <passthrough a1/a2/a3>)
 *   3. Nested loop (7 outer × 5 inner = 35 calls per cell):
 *      - Outer y: 0x10..0xF0 step 0x20
 *      - Inner x: 0..0x140 step 0x40, indexed via buf[0..4]
 *      - Each iter: idx = buf[i]; entry = &D + 0x10 + idx*0x18;
 *                   gl_func(entry); gl_func(entry, x, y, 0);
 *   4. Trailing `sll t6, a1, 2` at offset 0xFC sets t6 = a1*4 — this is
 *      the prologue-stolen successor donation to func_00002EF0 (see its
 *      wrap comment); it lives in 00002DF0's symbol footprint per
 *      docs/POST_CC_RECIPES.md#feedback-suffix-bytes-unblocks-4byte-stolen-prologue.
 *
 * Match path (per 00002EF0 wrap path (a)): SUFFIX_BYTES on this function
 * with 0x00057080 to put the trailing sll back after C-emit. C body
 * matching first (any %), then SUFFIX_BYTES, then the successor matches
 * naturally without needing PROLOGUE_STEALS.
 *
 * 2026-05-15 status: 61.83%. buf-copy switched to the pointer-walk form
 * (`int *src = &D+0x4A0; buf[i]=src[i]`) — that IS the target shape
 * (`addiu t7,&D+0x4A0; lw t9,0(t7); sw t9,0(sp+0x54); ...`), flat fuzzy
 * but a more faithful decode. Dominant remaining blockers, in order:
 *   1. Frame size: built -0x70 (112) vs target -0x68 (104). Built saves
 *      $s4/$s8 (10 sreg slots) where target saves only $s0-$s7 (8).
 *      The extra $s4-as-&D-base + $s8 are the regression source.
 *   2. built materializes `&D` into $s4 once (`lui s4; addiu s4; or a0,s4`)
 *      and reloads all 0x4A0+ fields off it; target keeps NO persistent
 *      &D base — it re-lui's per use (t7 for the copy, fresh a0 for the
 *      setup call). Need to inline `(char*)&D + N` at every site (the
 *      feedback-ido-inline-symbol-arith-vs-base-local recipe) so no
 *      $s4 base local is created.
 *   3. After 1+2 collapse the frame to -0x68, the nested-loop $s-reg
 *      assignment still needs to land x/y/p/idx in the target's slots.
 * Path (a) gate is "predecessor byte-exact"; #1+#2 are the next concrete
 * multi-tick steps. Defer SUFFIX_BYTES until then.
 *
 * Inner-loop calls are placeholder `jal 0` relocations resolved at USO
 * load time — both calls labeled gl_func_00000000 by convention. The
 * 24-byte stride (s5 = 0x18) matches the 00002EF0 wrap's struct size.
 * Likely a sprite-grid placement: 7 rows × 5 cols of tiles, each tile
 * indexed by buf[col] selecting from a 24-byte struct table at &D+0x10. */
void timproc_uso_b3_func_00002DF0(int a0, int a1, int a2, int a3) {
    int buf[5];
    int x, y;
    int *p;
    int idx;
    char *entry;

    (void)a0;  /* a0 spilled at entry, unused in body */

    {
        int *src = (int*)((char*)&D_00000000 + 0x4A0);
        buf[0] = src[0];
        buf[1] = src[1];
        buf[2] = src[2];
        buf[3] = src[3];
        buf[4] = src[4];
    }

    gl_func_00000000(&D_00000000, a1, a2, a3);

    for (y = 0x10; y != 0xF0; y += 0x20) {
        p = buf;
        for (x = 0; x != 0x140; x += 0x40) {
            idx = *p;
            entry = (char*)&D_00000000 + 0x10 + idx * 0x18;
            gl_func_00000000(entry);
            gl_func_00000000(entry, x, y, 0);
            p++;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002DF0);
#endif

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
 * Exact via PROLOGUE_STEALS=4. Unique extern D_b3_2EF0_table bakes the
 * +0x70 table offset into the relocation; the second pointer local keeps the
 * target 0x28-byte frame and sp+0x1C spill slot. */
extern char D_b3_2EF0_table;
void timproc_uso_b3_func_00002EF0(int a0, int a1, int a2) {
    char *entry, *spillee;
    (void)a0;
    (void)spillee;
    entry = (char*)&D_b3_2EF0_table + a1 * 24;
    spillee = entry;
    gl_func_00000000(entry);
    gl_func_00000000(entry);
    gl_func_00000000(entry, 0xA0, a2, 3);
}

/* timproc_uso_b3_func_00002F48: 66-insn (0x108) two-pass render-helper.
 * Sibling of recently-NM-wrapped func_00002EF0.
 *
 * Decoded structure:
 *   void f(int *a0, int a1) {
 *     float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };  // 4-float white at sp+0x38
 *     // Pass 1: table at &D + 0x190
 *     gl_func(&D + 0x190, ...);
 *     if (a0->0x58 != 0) {
 *       gl_func(&D + 0x190, 0x40, &color, 0xFF);
 *     } else {
 *       gl_func(&D + 0x190, a0->0x5C, &color, 0xFF);
 *     }
 *     gl_func(&D + 0x190, 0x78, a1, 3);
 *     gl_func(&D + 0x1A8);
 *     // Pass 2: table at &D + 0x1A8
 *     if (a0->0x58 == 0) {
 *       gl_func(&D + 0x1A8, 0x40, &color, 0xFF);
 *     } else {
 *       gl_func(&D + 0x1A8, a0->0x5C, &color, 0xFF);
 *     }
 *     gl_func(&D + 0x1A8, 0xC8, a1, 3);
 *   }
 *
 * 1.0f via lui at, 0x3F80 + mtc1 (-O2 standard pattern). 4 swc1 stores
 * to sp+0x38..0x44 fill the color quad. Two-pass structure renders into
 * paired tables at &D+0x190 (alpha?) and &D+0x1A8 (RGB?).
 *
 * Exact via a stack struct that places color[4] at sp+0x38 and the
 * unprefixed func_00000000 cross-USO placeholder calls. objdiff still reports
 * relocation-symbol arg mismatches against the raw .word baseline, but
 * no-alias disassembly and byte-verify match. */
extern int gl_func_00000000();
extern int func_00000000();
extern char D_00000000;
void timproc_uso_b3_func_00002F48(int *a0, int a1) {
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

/* timproc_uso_b3_func_00003050: byte-identical mirror of
 * timproc_uso_b1_func_00002E50. Same Quad4 dispatcher recipe — see
 * the b1 wrap doc for the structural notes. */
void timproc_uso_b3_func_00003050(int *a0, int a1) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3/timproc_uso_b3_func_00003050_pad.s")
