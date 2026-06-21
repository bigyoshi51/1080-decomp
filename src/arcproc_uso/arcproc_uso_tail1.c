#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
extern int D_arc240_A, D_arc240_B, D_arc240_C;
typedef struct { int a, b, c, d; } Quad4;

/* Continues arcproc_uso .text at 0x12C (after arcproc_uso_o0_50.c which
 * holds 0x50..0x12C: Quad4 reader + 0xB4 -O0 ref-count/check-full).
 * Original single-file body split into arcproc_uso.c (0x0..0x50 func_00000000),
 * arcproc_uso_o0_50.c (-O0), and this tail. */

/* arcproc_uso_func_00001B88 moved to its in-offset-order slot (before
 * func_00001BBC). It was defined at the top of the file, which made IDO emit
 * it FIRST in .text — an extra 0x34-byte copy at segment offset 0x240 and a
 * 0x34-byte hole at 0x1B88, i.e. +0x34/-0x34 layout drift inside the segment
 * (function order in the TU == .text order). */

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
 * CONTROL STRUCTURE FULLY DECODED 2026-05-28 (was mislabeled a one-shot switch):
 * it is a STATE-MACHINE DO-WHILE LOOP, not a single dispatch:
 *   sp+0x40 = done_flag = 0;            // prologue `sw zero,0x40(sp)`
 *   do {
 *     state = *(sp+0x4C);               // reload a1-home (= current state)
 *     if ((u)state >= 11) break;        // sltiu at,state,11; beqz at,epilogue
 *     switch (state) {                  // jr via D_rodata[state*4]
 *       case 0:  func1B88(a0,1,3,1); D[0x44]=3; D[0x48]=10; done_flag=1; break;
 *       case 1:  func1B88(a0,1,3,1); D[0x44]=4; D[0x48]=9;  done_flag=1; break;
 *       case 2:  func1B88(a0,1,3,2); D[0x44]=4; D[0x48]=9;  done_flag=1; break;
 *       case 3:  func1B88(a0);       D[0x40]=4;            break; // no done -> loops
 *       case 4:  func1B88(a0);       D[0x40]=5;            break; // no done -> loops
 *       cases 5..10: struct-walk + multi-call + done_flag=1 (per-case TBD)
 *     }
 *     *(sp+0x4C) = D[0x40];             // loop tail: next state from D[0x40]
 *   } while (done_flag == 0);
 * KEY INSIGHT: cases that set D[0x40] but NOT done_flag re-dispatch on the new
 * state (the loop) — that's why cases 3/4 chain into other states. done_flag
 * (sp+0x40) is the loop exit condition. func_00001B88 is a K&R-variadic helper
 * called with 1..5 args across cases (declare `extern int func();`).
 *
 * 2026-06-01 (0.88->22.22%): the "jr-rodata can't reproduce" claim was WRONG
 * (re-verify principle): a single-symbol switch DOES match — IDO emits the
 * sltiu/jr-table dispatch in .text and objdiff compares only that (the .rodata
 * jumptable is a separate section, like timproc_uso_b5_func_000087F4). Wrote
 * the do-while + switch with cases 0..4 decoded and 5..10 as distinct
 * D[0x40]=N placeholders (to force the dense 11-entry table). Dispatch + cases
 * 0..4 now match. 2026-06-02 (22.22->30.62%): decoded cases 6 (gl(a0,*a0);
 * done), 8 (gl(&D,7,0,0); r=gl(0); gl(a0,1,r); done), 9 (gl(a0); D[0x40]=10;
 * loops), 10 (r=gl(0,1,0); gl(&D+16,r); if(r->0x14)r->4=1; r->0x14=&D; done).
 * REMAINING: cases 5 and 7 (complex struct-walks: case5 sets D[0x64]=q[q->4+3]
 * from a0->8, then 5 calls with 0x450000 + multiple DISTINCT D symbols needing
 * CSE-bust externs; case7 reuses D[0x64] with |0x8000 + dli 0x8000). Multi-tick
 * tail. Default build INCLUDE_ASM remains exact. */
void arcproc_uso_func_00000240(int a0, int a1) {
    int done = 0;
    int state;
    do {
        state = a1;
        if ((unsigned)state >= 11) break;
        switch (state) {
        case 0:
            gl_func_00000000(a0, 1, 3, 1);
            *(int *)((char *)&D_00000000 + 0x44) = 3;
            *(int *)((char *)&D_00000000 + 0x48) = 10;
            done = 1;
            break;
        case 1:
            gl_func_00000000(a0, 1, 3, 1);
            *(int *)((char *)&D_00000000 + 0x44) = 4;
            *(int *)((char *)&D_00000000 + 0x48) = 9;
            done = 1;
            break;
        case 2:
            gl_func_00000000(a0, 1, 3, 2);
            *(int *)((char *)&D_00000000 + 0x44) = 4;
            *(int *)((char *)&D_00000000 + 0x48) = 9;
            done = 1;
            break;
        case 3:
            gl_func_00000000(a0);
            *(int *)((char *)&D_00000000 + 0x40) = 4;
            break;
        case 4:
            gl_func_00000000(a0);
            *(int *)((char *)&D_00000000 + 0x40) = 5;
            break;
        case 5: {
            int *p = (int *)a0;
            int *q;
            int v;
            gl_func_00000000(&D_arc240_A, *(int *)((char *)&D_arc240_B + 4));
            q = (int *)p[2];
            *(int *)((char *)&D_00000000 + 0x64) = q[q[1] + 3];
            gl_func_00000000(&D_arc240_C, 4, *(int *)((char *)&D_00000000 + 0x64), 3);
            v = gl_func_00000000(p, p[0], 1);
            gl_func_00000000(0, 0x450000, v, p[2], p[0]);
            gl_func_00000000(p, 0, v);
            done = 1;
            break;
        }
        case 6:
            gl_func_00000000(a0, *(int *)a0);
            done = 1;
            break;
        case 7: {
            int *p = (int *)a0;
            int r = gl_func_00000000(*(int *)((char *)&D_00000000 + 0x64));
            gl_func_00000000(p, (*(int *)((char *)&D_00000000 + 0x64) | 0x8000) | r,
                             0x8000, p[0]);
            done = 1;
            break;
        }
        case 8: {
            int r;
            gl_func_00000000(&D_00000000, 7, 0, 0);
            r = gl_func_00000000(0);
            gl_func_00000000(a0, 1, r);
            done = 1;
            break;
        }
        case 9:
            gl_func_00000000(a0);
            *(int *)((char *)&D_00000000 + 0x40) = 10;
            break;
        case 10: {
            int *r = (int *)gl_func_00000000(0, 1, 0);
            int *base = (int *)&D_00000000;
            gl_func_00000000((char *)base + 16, r);
            if (r[0x14 / 4] != 0) {
                r[0x4 / 4] = 1;
            }
            r[0x14 / 4] = (int)base;
            done = 1;
            break;
        }
        }
        a1 = *(int *)((char *)&D_00000000 + 0x40);
    } while (done == 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000240);
#endif

/* arcproc_uso_func_000005C8: CAP (verified 2026-05-31, structure is EXACT). The C
 * below matches the target's logic insn-for-insn, but stays ~43% because the target
 * is -g3/-O0 codegen: all 6 jals have UNFILLED delay slots (nop), s0 is saved/used for
 * the alloc result, frame is 0x28 — my -O2 fills the delays, keeps the result in v0,
 * frame 0x20. Needs a per-file -g3 split (Yay0-split infra) AND the raw-word jal relocs
 * are placeholder gl_func_00000000 (USO reloc-presence). Don't re-grind at -O2. */
extern int *D_arc5C8_148;
extern int D_arc5C8_14C;
extern int D_arc5C8_68;
#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000005C8);
#endif

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
    /* The target reloads a0->0x8 before EVERY store (no CSE — IDO can't
     * prove the through-pointer stores don't alias a0+8). A plain repeated
     * deref gets CSE'd to one load; a volatile pointer-fetch forces the
     * per-store reload the target emits. */
#define P (*(int *volatile *)((char *)a0 + 8))
    P[0] = 1;
    P[1] = 0;
    P[2] = 5;
    P[3] = 2;
    P[4] = 0;
    P[5] = 3;
    P[6] = 1;
    P[7] = 4;
    P[13] = 0;
    i = 0;
    if (i < P[2]) {
        do {
            P[8 + i] = 0;
            i++;
        } while (i < P[2]);
    }
#undef P
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000688);
#endif

/* 27-insn -O0 cleanup wrapper, byte-identical sibling of the matched
 * mgrproc_uso_func_000009A8. Matched 2026-05-30 via the -O0 REPLACE_FUNC_BODY
 * donor splice (donor src/arcproc_uso/arcproc_uso_o0_748.c). arcproc is
 * non-Yay0, but the donor-splice still works: relocatable USO functions have
 * link-offset-independent bytes (jal-0 + relocs, self-relative branches), so
 * the 18->27-insn size change in tail1.c.o doesn't break downstream functions
 * (verified: arcproc held 33->34 matched, no regressions). This -O2 body is
 * what the main object compiles; the donor's -O0 bytes are spliced over it.
 * The donor splice avoided a risky 3-way file split of tail1 around a mid-file
 * function. Unblocked by the replace-function-body.py realign fix (2026-05-30).
 * See docs/MATCHING_WORKFLOW.md#feedback-replace-func-body-o0-donor. */
void arcproc_uso_func_00000748(int *a0) {
    gl_func_00000000((int*)a0[2]);
    a0[2] = 0;
    gl_func_00000000((int*)a0[0], 3);
    a0[0] = 0;
    *(int*)((char*)&D_00000000 + 0x14C) = 0;
}

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
 * 2026-06-01 (23.72 -> 27.62): confirmed member of the 0x6A8-alloc constructor
 * family (siblings: timproc_b3 994, timproc_b1 097C, titproc 1E9C). Ported the
 * proven 5-stage cascade (goto-chain dead-guards + distinct externs
 * D_arc_A3C_v0..3; self alloc 0x780, D-template 0x3B8 same as 994) + the early
 * field-init. arcproc takes a 5TH arg (a4 -> self->0x528; a3 -> self->0x6a8),
 * unlike the 4-arg siblings, and has a unique sub-loop tail. TBD: sub=gl(0xD8)
 * node + vtable-dispatch + the arcproc sub-loop (insns ~78-205 of /tmp/tarc.txt).
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
extern char D_arc_A3C_v0;
extern char D_arc_A3C_v1;
extern char D_arc_A3C_v2;
extern char D_arc_A3C_v3;
extern char D_arc_A3C_v4;
void *arcproc_uso_func_00000A3C(int *a0, int a1, int a2, int a3, int a4) {
    int *s1 = a0;
    int *n1, *n2, *n3;
    /* 5-stage get-or-create cascade (994/097C/titproc_1E9C sibling; self alloc
     * 0x780 here, D-template 0x3B8 same as 994). goto-chain dead-guards +
     * distinct-extern vtable stores (CSE-bust -> target t7/t8/t0/t1). */
    if (a0 == 0) {
        s1 = (int*)gl_func_00000000(0x780);
        if (s1 == 0) return (void*)s1;
    }
    n1 = s1;
    if (s1 == 0) { n1 = (int*)gl_func_00000000(0x6A8); if (n1 == 0) goto S_self; }
    n2 = n1;
    if (n1 == 0) { n2 = (int*)gl_func_00000000(0x50); if (n2 == 0) goto S_n1; }
    n3 = n2;
    if (n2 == 0) { n3 = (int*)gl_func_00000000(0x2C); if (n3 == 0) goto S_n2; }
    gl_func_00000000(n3, (char*)&D_00000000 + 0x3B8);
    n3[0x28 / 4] = (int)&D_arc_A3C_v0;
S_n2:
    n2[0x28 / 4] = (int)&D_arc_A3C_v1;
S_n1:
    n1[0x28 / 4] = (int)&D_arc_A3C_v2;
    gl_func_00000000((char*)n1 + 0x50);
S_self:
    s1[0x28 / 4] = (int)&D_arc_A3C_v3;
    s1[0x568 / 4] = 0;
    gl_func_00000000(s1, a1, (char*)&D_00000000 + 0x3C0, a2);
    s1[0x528 / 4] = a4;
    s1[0x6B8 / 4] = 0;
    s1[0x6A8 / 4] = a3;
    gl_func_00000000(s1);
    *(float *)&s1[0x77C / 4] = 0.0f;
    gl_func_00000000((char*)&D_00000000 + 0x3D0, 0);
    gl_func_00000000(&D_00000000, 0);
    {
        int *sub = (int*)gl_func_00000000(0xD8);
        if (sub != 0) {
            gl_func_00000000(sub);
            sub[0x28 / 4] = (int)&D_arc_A3C_v4;
            s1[0x6AC / 4] = (int)sub;
            *(int**)((char*)&D_00000000 + 0x138) = sub;
            sub[0xB4 / 4] = 7;
            gl_func_00000000(sub, s1, s1[0x568 / 4], s1[0x6A8 / 4], s1[0x528 / 4]);
            {
                int *vt = (int*)sub[0x28 / 4];
                ((void(*)(int))vt[0x5C / 4])(*(short*)((char*)vt + 0x58) + (int)sub);
            }
        }
    }
    {
        int *q = (int *)((int *)s1[0x6AC / 4])[0x44 / 4];
        q[0x18 / 4] = *(int *)((char *)s1[0x6A8 / 4] + 0x34);
        q[0x14 / 4] = *(int *)((char *)s1[0x6A8 / 4] + 0x34);
    }
    gl_func_00000000((char *)s1 + 0x10, (int *)s1[0x6AC / 4]);
    {
        int *sub = (int *)s1[0x6AC / 4];
        if (sub[0x14 / 4] != 0) {
            sub[0x4 / 4] = 1;
            sub[0x14 / 4] = (int)s1;
        }
    }
    gl_func_00000000(s1, a1);
    s1[0x48 / 4] = (int)gl_func_00000000(0);
    gl_func_00000000(s1[0x48 / 4], s1);
    gl_func_00000000(s1[0x48 / 4], (*(int *)&D_00000000 + 3) << 16, -1, &D_00000000);
    gl_func_00000000(s1[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 9, -1, &D_00000000);
    gl_func_00000000(s1[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 5, -1, &D_00000000);
    *(int *)((char *)s1[0x48 / 4] + 0x30) = s1[0x568 / 4];
    gl_func_00000000(s1[0x48 / 4]);
    gl_func_00000000((char *)s1 + 0x10, (int *)s1[0x48 / 4]);
    {
        int *n = (int *)s1[0x48 / 4];
        if (n[0x14 / 4] != 0) {
            n[0x4 / 4] = 1;
        }
        n[0x14 / 4] = (int)s1;
    }
    {
        int *node = *(int **)((char *)&D_00000000 + 0x190);
        gl_func_00000000((char *)s1 + 0x10, node);
        if (node[0x14 / 4] != 0) {
            node[0x4 / 4] = 1;
            node[0x14 / 4] = (int)s1;
        }
        gl_func_00000000(*(int **)((char *)&D_00000000 + 0x190), 1, 0);
        gl_func_00000000();
    }
    *(int *)((char *)&D_00000000 + 0x40) = 5;
    return (void*)s1;
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

/* arcproc_uso_func_00000EBC: F1 (11-insn bit-test wrapper) ONLY.
 *
 * The 2026-05-07 "SUFFIX_BYTES recipe" (25 words / 0x64 bytes absorbing
 * F2..F6 + stolen prologue) was REMOVED 2026-05-23 as instruction-byte
 * match-faking (see feedback_no_instruction_forcing_matches_policy).
 * Current state: this symbol is 0x30 / 12 insns (F1 only); F2..F6 are
 * tracked as separate symbols (split via scripts/split-fragments.py).
 * Function lands at fuzzy=100 naturally — no recipe needed.
 *
 * F2..F6 historical sub-function decode preserved below for reference.
 *
 * ORIGINAL DOC:
 * 6-FUNCTION BUNDLE (0x94 / 37 insns).
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
extern int gl_func_00000000();
void arcproc_uso_func_00000EBC(int *a0) {
    if (*(int*)((char*)a0 + 0x4F0) & 0x10000) {
        gl_func_00000000();
    }
}

/* arcproc_uso_func_00000EEC: 12-insn triple-deref non-null check, RECOVERED
 * from the 00000EBC bundle gap. Returns 1 iff a0->0x6AC->0x6C is non-null
 * and its 0xEC field is non-zero. MATCHED 2026-05-28: `goto ret0` to a
 * shared `return 0` emits the beql branch-likely idiom (12 insns); the
 * plain `if(...)return 0` form emitted bnel and grew to 14 (the prior cap).
 * Same fix as timproc_uso_b3_func_00000E30. */
int arcproc_uso_func_00000EEC(int *a0) {
    int *p = (int*)((int*)a0[0x6AC / 4])[0x6C / 4];
    if (p == 0) {
        goto ret0;
    }
    if (*(int*)((char*)p + 0xEC) == 0) {
        goto ret0;
    }
    return 1;
ret0:
    return 0;
}

/* arcproc_uso_func_00000F1C: 9-insn flag setter, RECOVERED 2026-05-28 from
 * the same bundle gap. a0->0x504 = (a0->0x6B8 != 0) ? 4 : 0, via bnel with
 * the set-4 store in the delay slot (+ a dead duplicate at 0xF34, the
 * branch-likely natural-position artifact). NM (bnel idiom not C-reachable);
 * build uses INCLUDE_ASM. */
void arcproc_uso_func_00000F1C(int *a0) {
    if (*(int*)((char*)a0 + 0x6B8) == 0) {
        *(int*)((char*)a0 + 0x504) = 0;
    } else {
        *(int*)((char*)a0 + 0x504) = 4;
    }
}

/* arcproc_uso_func_00000F40: 2-insn store stub, RECOVERED 2026-05-28.
 * a0->0x504 = 0 (store in the jr-ra delay slot). */
void arcproc_uso_func_00000F40(int *a0) {
    *(int*)((char*)a0 + 0x504) = 0;
}

/* arcproc_uso_func_00000F48: 2-insn alternate entry, RECOVERED 2026-05-28.
 * `lui a1; lw a1, 0x170(a1)` pre-loads a1 from a USO data symbol then FALLS
 * THROUGH into arcproc_uso_func_00000F50 (no jr ra of its own). Not a
 * standalone C function — INCLUDE_ASM only. */
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000F48);

/* arcproc_uso_func_00000F50 + F78 + F9C: 3-function bundle split via
 * scripts/split-fragments.py on 2026-05-07. Per
 * docs/MATCHING_WORKFLOW.md split-fragments.py wrong-file-placement
 * gotcha, the new INCLUDE_ASMs were moved manually from
 * arcproc_uso.c to arcproc_uso_tail1.c (where the parent F50 lives) so
 * the linker keeps F50/F78/F9C contiguous in .text.
 *
 * F50: 10-insn cross-USO wrapper that adds 0x26000F to a1 before
 * forwarding. IDO -O2 emits `lui+ori+addu` for the 24-bit constant
 * (since 0x26000F doesn't fit in a 16-bit signed immediate). */
extern int gl_func_00000000();
void arcproc_uso_func_00000F50(int a0, int a1) {
    gl_func_00000000(a0, a1 + 0x26000F);
}

/* arcproc_uso_func_00000F78: 12-insn 2-level NULL-check.
 *
 * BOUNDARY FIX 2026-05-08: was a 9-insn F78 + 3-insn F9C cross-function
 * tail-share — F78's beqzl branches encoded `+7` and `+4` relative
 * offsets both landing at F78+0x28 = F9C+0x4 (the `jr ra` inside F9C).
 * F9C had no other callers (verified by grep). Merged F9C's 3 insns
 * into F78's .s, deleted F9C.s, added `arcproc_uso_func_00000F9C =
 * 0xF9C;` to undefined_syms_auto.txt.
 *
 * Positive nested form matches the branch-likely structure and keeps the
 * second deref/test temp in `t7` (per docs/IDO_CODEGEN.md branch-likely
 * arm-choice guidance). */
int arcproc_uso_func_00000F78(int *a0) {
    int *v;
    v = *(int**)((char*)*(int**)((char*)a0 + 0x6AC) + 0x6C);
    if (v != 0) {
        if (*(int*)((char*)v + 0xEC) != 0) {
            return 1;
        }
    }
    return 0;
}

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
#ifdef NON_MATCHING
/* arcproc_uso_func_00000FA8: 114-insn (0x1C8) state-machine dispatcher
 * on a0->[0x504]. Frame 0x30, saves ra/s1/s0.
 *
 * Decoded entry (insns 1-13):
 *   s0 = a0->[0x504];                       // state field
 *   s1 = a0;
 *   if (s0 == 0) { v0 = a0->[0x6AC]; goto case_0; }   // beql shortcut
 *   if (s0 == 1) goto case_1;                          // beq +0x2A
 *   if (s0 == 4) { v0 = a0->[0x6A8]; goto case_4; }   // beql shortcut
 *   goto end;
 *
 * Case 0 (~22 insns @ 0xFEC-0x103C): state-0 list management.
 *   - Read a0->[0x6AC]->[0x44] (= sub-obj+0x44) and a0->[0x6AC]->[0x14]
 *     (= sub-sub+0x14). Decrement a0->[0x6B4] counter. Loop on
 *     comparison (count != 1) — likely "advance through a list".
 *
 * Case 1 (~13 insns @ 0x1058-0x108C): state-1 transition.
 *   - a0->[0x504] = 1; gl_func calls with arg 3, then 0, 1.
 *   - Sets a0->[0x6AC] (or similar) and falls through to `end`.
 *
 * Case 4 (~50 insns @ 0x1078+0x59*4 = 0x11BC area): state-4 setup.
 *   - Reads a0->[0x190] table addresses, builds sp+0x20 buf, makes
 *     several gl_func calls with sequence numbers. Likely "initialize
 *     buffered playback / arc-process state machine".
 *
 * Default exit (insns 0xFE0-0xFE4): jump to epilogue.
 *
 * Initial decode 2026-05-05 — first-pass NM. ~80 insns of body (cases
 * 0/1/4) sketched as TODO; full decode requires multiple passes. */
extern int gl_func_00000000();
/* Whole-body decode 2026-06-01. State dispatch on s0 = a0->0x504 (beql/beq
 * order 0,1,4). The prior pass mis-mapped the cases: what it labeled "case 1"
 * (gl(D[0x190],3,1); 0x504=1) is actually case 0's TAIL, and the real case 1
 * (s0==1) is a ~40-insn list-registration block. Search loop in case 0 breaks
 * when a0->0x6B0 (updated by the callee) diverges from list->0x1C. */
void arcproc_uso_func_00000FA8(char *a0) {
    int s0 = *(int*)(a0 + 0x504);
    char *s1 = a0;

    if (s0 == 0) {
        int *list = *(int**)(s1 + 0x6AC);
        int count, i;
        *(int*)(s1 + 0x6B0) = *(int*)(*(char**)((char*)list + 0x44) + 0x14);
        count = *(int*)(*(char**)((char*)list + 0x44) + 0x40);
        i = count - 1;
        if (i >= 0) {
            *(int*)(s1 + 0x6B4) = count;
            do {
                char *t0 = *(char**)(s1 + 0x528);
                gl_func_00000000(*(int*)(t0 + 0x4), i);
                if (*(int*)(s1 + 0x6B0) != *(int*)((char*)list + 0x1C)) break;
                *(int*)(s1 + 0x6B4) = *(int*)(s1 + 0x6B4) - 1;
                i--;
            } while (i >= 0);
        }
        *(int*)(s1 + 0x4D8) = 1;
        gl_func_00000000(7, 0, 0);
        gl_func_00000000(*(int*)((char*)&D_00000000 + 0x190), 3, 1);
        *(int*)(s1 + 0x504) = 1;
        return;
    }
    if (s0 == 1) {
        int v0;
        char *node, *buf;
        if (gl_func_00000000(*(int*)((char*)&D_00000000 + 0x190)) == 0) return;
        gl_func_00000000(s1);
        gl_func_00000000(&D_00000000);
        gl_func_00000000(s1);
        gl_func_00000000(7, 0, 0);
        gl_func_00000000(s1, *(int*)((char*)&D_00000000 + 0x170) + 0x26000F);
        v0 = gl_func_00000000(0, s1, 0);
        *(int*)(s1 + 0x524) = v0;
        gl_func_00000000(v0, *(int*)(s1 + 0x528));
        buf = *(char**)(s1 + 0x56C);
        node = *(char**)(s1 + 0x524);
        gl_func_00000000(buf + 16, node);
        if (*(int*)(node + 0x14) != 0) {
            *(int*)(node + 0x4) = 1;
        }
        *(int*)(node + 0x14) = (int)buf;
        gl_func_00000000(*(int*)((char*)&D_00000000 + 0x190), 1, 1);
        return;
    }
    if (s0 == 4) {
        int *v0 = *(int**)(s1 + 0x6A8);
        int idx = *(int*)((char*)v0 + 0x4);
        gl_func_00000000(s1, 4, *(int*)((char*)v0 + idx * 4 + 0x10));
        return;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000FA8);
#endif

/* arcproc_uso_func_00001170: F1 (32-insn dispatcher + indirect call) only.
 * NATURAL CEILING: 97.03% NM. The 2026-05-07 SUFFIX_BYTES recipe (28 words
 * / 0x70 bytes absorbing F2 + F3) was REMOVED 2026-05-23 as match-faking.
 * Symbol is now 0x80 / 32 insns (F1 only); F2 and F3 are separate symbols.
 * Sibling family of arcproc_uso_func_00000EBC, gl_func_000070A0,
 * timproc_uso_b3_func_00000DE4 (all same recipe-cleanup pattern).
 *
 * F1 @ 0x1170-0x11EC: gate + indirect callback via vtable.
 *   if (gl_func(D[0x190], a0)) {
 *       p = a0->[0x48]; idx = p->[0x7C];
 *       target = p + idx*0x28;
 *       if (target->[0x90]) {
 *           D[0x0] = a0;
 *           p = a0->[0x48]; idx = p->[0x7C];
 *           target = p + idx*0x28;
 *           ((void(*)())target->[0x90])();
 *       }
 *   }
 *
 * F2 @ 0x11F0-0x1224: clear bit-0x04 in two field locations:
 *   *(a0->[0x6AC]->[0x6C] + 0x18) &= ~0x04;
 *   *(a0->[0x6AC]->[0x94] + 0x18) &= ~0x04;
 *
 * F3 @ 0x1228-0x1258: same as F2 but |= 0x04 (set bit).
 *
 * 2026-06-01 source=2 sibling pass: direct-calling the vtable load
 * improves 0x1170 from 97.03% to 97.34% by keeping the final jalr target
 * in $t9. Remaining diffs are register coloring: target uses $v1 for the
 * 0x28 stride and $t6/$t0 for the two table indices; IDO still colors the
 * stride as $a0 and the indices as $v1. `register void (*fn)()` regressed
 * the call back to $a0. 2026-06-01 source=2 sibling retest: named `stride`
 * and named `offset` locals compile identically (still `$a0` stride /
 * `$v1` index), so the residual is allocator coloring rather than an
 * expression-tree issue. */
extern int gl_func_00000000();
extern char D_00000000;
#ifdef NON_MATCHING
void arcproc_uso_func_00001170(int *a0) {
    int *table_root = *(int**)((char*)&D_00000000 + 0x190);
    int *p;
    int idx;
    int offset;
    int *target;

    if (gl_func_00000000(table_root, a0) == 0) return;
    p = (int*)a0[0x48 / 4];
    idx = *(int*)((char*)p + 0x7C);
    offset = idx * 0x28;
    target = (int*)((char*)p + offset);
    if (target[0x90 / 4] == 0) return;
    *(int*)&D_00000000 = (int)a0;
    p = (int*)a0[0x48 / 4];
    idx = *(int*)((char*)p + 0x7C);
    offset = idx * 0x28;
    target = (int*)((char*)p + offset);
    ((void(*)())target[0x90 / 4])();
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001170);
#endif

/* arcproc_uso_func_000011F0: 14-insn dual-field bit-clear, RECOVERED
 * 2026-05-28 from the 00001170 bundle gap. Clears bit 2 of the 0x18 field
 * on both a0->0x6AC->0x6C and a0->0x6AC->0x94. Exact 2026-06-01: using an
 * explicit field pointer forces IDO to materialize `addiu v0, v0, 0x18`
 * before the store, matching the target's `sw ..., 0(v0)` shape. */
void arcproc_uso_func_000011F0(int *a0) {
    int *p = (int*)((int*)a0[0x6AC / 4])[0x6C / 4];
    p = (int*)((char*)p + 0x18);
    *p &= ~4;
    p = (int*)((int*)a0[0x6AC / 4])[0x94 / 4];
    p = (int*)((char*)p + 0x18);
    *p &= ~4;
}

/* arcproc_uso_func_00001228: 13-insn dual-field bit-set, RECOVERED
 * 2026-05-28 (sibling of 000011F0, sets bit 2 instead of clearing). Exact
 * 2026-06-01 via the same explicit field-pointer shape. */
void arcproc_uso_func_00001228(int *a0) {
    int *p = (int*)((int*)a0[0x6AC / 4])[0x6C / 4];
    p = (int*)((char*)p + 0x18);
    *p |= 4;
    p = (int*)((int*)a0[0x6AC / 4])[0x94 / 4];
    p = (int*)((char*)p + 0x18);
    *p |= 4;
}

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
 * Body structure:
 *   - Maintain a progress float at a0->0x77C. If a0->0x4E4 >= 11 and the
 *     progress is below D[0x30], add D[0x34]. Otherwise, while progress is
 *     positive, subtract D[0x38].
 *   - Dispatch two alpha-scaled ranges:
 *       gl_func(&D, (int)(255.0f * progress), a0+0x380, a0+0x3A4)
 *       gl_func(&D, (int)(255.0f * progress), a0+0x260, a0+0x284)
 *   - Run 0x6BC setup, then choose whether 0x6D4 or 0x6EC is the first
 *     follow-up based on a0->0x6A8->[4]+1 == a0->0x6A8->[8].
 *
 * EPILOGUE (insns 130-139): standard frame teardown with pre-loaded ra
 * (loaded in 1st bgez delay slot — common -O2 trick).
 *
 * 2026-05-20: first real C body from no-alias disassembly after m2c failed
 * on raw .word USO asm and Ghidra project was unavailable in this worktree.
 * NON_MATCHING only; default INCLUDE_ASM keeps ROM exact. Tried volatile
 * one0..one3 locals (70.72%) and inverted threshold branch layout (64.82%);
 * plain ones[4] with the >= threshold layout is best at 74.63%. */
#ifdef NON_MATCHING
void arcproc_uso_func_0000125C(char *a0) {
    float ones[4];
    float progress;
    int alpha;
    int span;
    int sum;
    int half;
    int *seq;

    if ((*(int*)(a0 + 0x4F0) & 0x10000) == 0) {
        return;
    }

    ones[0] = 1.0f;
    ones[1] = 1.0f;
    ones[2] = 1.0f;
    ones[3] = 1.0f;

    progress = *(float*)(a0 + 0x77C);
    if (*(int*)(a0 + 0x4E4) >= 11) {
        if (progress < *(float*)((char*)&D_00000000 + 0x30)) {
            progress += *(float*)((char*)&D_00000000 + 0x34);
            *(float*)(a0 + 0x77C) = progress;
        }
    } else if (progress > 0.0f) {
        progress -= *(float*)((char*)&D_00000000 + 0x38);
        *(float*)(a0 + 0x77C) = progress;
    }

    progress = *(float*)(a0 + 0x77C);
    alpha = (int)(255.0f * progress);
    gl_func_00000000(&D_00000000, alpha, a0 + 0x380, a0 + 0x3A4);

    gl_func_00000000(a0 + 0x6BC);
    gl_func_00000000(a0 + 0x6BC, 0xA0, 0xB6, 3);

    sum = *(short*)(*(char**)(a0 + 0x6FC) + 0x20) +
          *(short*)(*(char**)(a0 + 0x6E4) + 0x20) + 4;
    if (sum < 0) {
        half = (sum + 1) >> 1;
    } else {
        half = sum >> 1;
    }
    span = 0xA0 - half;

    alpha = (int)(255.0f * *(float*)(a0 + 0x77C));
    gl_func_00000000(&D_00000000, alpha, a0 + 0x260, a0 + 0x284);

    seq = *(int**)(a0 + 0x6A8);
    if (seq[2] == seq[1] + 1) {
        gl_func_00000000(a0 + 0x6EC);
        gl_func_00000000(a0 + 0x6EC, span, 0x8E, 2);
        gl_func_00000000(a0 + 0x6D4);
        gl_func_00000000(a0 + 0x6D4,
                         span + *(short*)(*(char**)(a0 + 0x6FC) + 0x20) + 4,
                         0x8E, 2);
    } else {
        gl_func_00000000(a0 + 0x6D4);
        gl_func_00000000(a0 + 0x6D4, span, 0x8E, 2);
        gl_func_00000000(a0 + 0x6EC);
        gl_func_00000000(a0 + 0x6EC,
                         span + *(short*)(*(char**)(a0 + 0x6E4) + 0x20) + 4,
                         0x8E, 2);
    }

    (void)ones;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000125C);
#endif

int arcproc_uso_func_00000000();

void arcproc_uso_func_00001488(void) {
    arcproc_uso_func_00000000();
}

void arcproc_uso_func_000014A8(void) {
    gl_func_00000000();
}

#ifdef NON_MATCHING
/* arcproc_uso_func_000014C8: gated HUD fade/draw. Sets a {1,1,1,1} Vec4 (sp48..54).
 * If arg0->0x500 != 0 && *(float*)&D <= 0.0f: fade 0x77C up by &D+0x40 (clamp <
 * &D+0x3C); 0x508++; if cb(arg0->0x528): draw a panel at 0x2F0 with alpha (int)
 * (255*0x77C), draw arg0+0x764, and on (0x508 & 8) draw it + cb(arg0, 0xA0, arg0->
 * 0x6AC->0x44->0x14); else just that last cb. Fresh decode 2026-05-29 (m2c-
 * confirmed). 85.6 -> 92.0 (2026-05-31): (1) the panel draw's 1st arg is
 * &D_00000000 (data-base draw context), not literal 0 (m2c reloc-blindness);
 * (2) the &D float consts (&D+0 compare, &D+0x3C clamp, &D+0x40 step) use
 * distinct externs (D_flt_arc0/D_0000003C/D_00000040 in undefined_syms_auto.txt)
 * to bust the &D-base CSE — each lwc1 re-materializes its own lui. Same cocktail
 * as mgrproc_uso_func_00001C90. Residual (~8%): the {1,1,1,1} Vec4 is volatile
 * (write-only — read by a callee via the stack, so no &-arg to make it an
 * address-taken array), and the target reserves ~0x20 extra frame placing it at
 * sp+0x48..0x54 (frame -88) vs mine at sp+0x28 (frame -56); the oversized-
 * volatile-array trick doesn't reproduce the layout (regressed to 90.4%). Plus
 * a0/s0 regalloc + FP-load scheduling. NON_MATCHING. */
extern int gl_func_00000000();
extern float D_flt_arc0, D_0000003C, D_00000040;
void arcproc_uso_func_000014C8(char *arg0) {
    volatile float sp54;
    volatile float sp50;
    volatile float sp4C;
    volatile float sp48;
    float f0;

    sp48 = 1.0f;
    sp4C = 1.0f;
    sp50 = 1.0f;
    sp54 = 1.0f;
    if ((*(int *)(arg0 + 0x500) != 0) && (D_flt_arc0 <= 0.0f)) {
        f0 = *(float *)(arg0 + 0x77C);
        if (f0 < D_0000003C) {
            *(float *)(arg0 + 0x77C) = f0 + D_00000040;
        }
        *(int *)(arg0 + 0x508) = *(int *)(arg0 + 0x508) + 1;
        if (gl_func_00000000(*(int *)(arg0 + 0x528)) != 0) {
            gl_func_00000000(&D_00000000, (int)(255.0f * *(float *)(arg0 + 0x77C)), arg0 + 0x2F0, arg0 + 0x314);
            gl_func_00000000(arg0 + 0x764);
            if (*(int *)(arg0 + 0x508) & 8) {
                gl_func_00000000(arg0 + 0x764, 0xA0, 0xB4, 3);
                gl_func_00000000(arg0, 0xA0, *(int *)(*(char **)(*(char **)(arg0 + 0x6AC) + 0x44) + 0x14));
            }
        } else {
            gl_func_00000000(arg0, 0xA0, *(int *)(*(char **)(*(char **)(arg0 + 0x6AC) + 0x44) + 0x14));
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000014C8);
#endif

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
 * MATCHED 2026-05-29 (m2c-assisted): two levers cracked it — (1) hoist `int v1
 * = 0;` to the top (target inits v1 before the entry gate, not per-path); (2)
 * re-read p = s0->0x6A8 INSIDE each of the v1==1/v1==2 branches (not a hoisted
 * local) — that triggers the target's `bnel` (branch-likely) with the p-reload
 * in the delay slot. cb = gl_func_00000000. */
void arcproc_uso_func_00001604(int *s0) {
    int v1 = 0;
    if (s0[0x4FC / 4] != 0) {
        return;
    }
    if (s0[0x4F8 / 4] == 0) {
        if (gl_func_00000000(s0[0x6A8 / 4], ((int *)((int *)s0[0x6AC / 4])[0x44 / 4])[0x14 / 4]) != 0) {
            v1 = 1;
        } else {
            s0[0x6B8 / 4] = 1;
        }
    } else {
        if (gl_func_00000000(s0[0x6A8 / 4], ((int *)((int *)s0[0x6AC / 4])[0x44 / 4])[0x14 / 4]) != 0) {
            v1 = 2;
        } else {
            s0[0x6B8 / 4] = 1;
        }
    }
    if (v1 != 0) {
        if (v1 == 1) {
            int *p = (int *)s0[0x6A8 / 4];
            gl_func_00000000(s0[0x6AC / 4], (char *)p + 0x20, p[8 / 4]);
        } else {
            int *p = (int *)s0[0x6A8 / 4];
            gl_func_00000000(s0[0x6AC / 4], (char *)p + 0x20, p[4 / 4] + 1);
        }
    }
    s0[0x4FC / 4] = 1;
}

/* arcproc_uso_func_000016F4 - verified structural decode (~170-insn FPU
 * render/update orchestrator; full s-reg save + 255.0f scale + 12
 * sub-object calls + div + branch-likely = documented FP/spill sub-80
 * ceiling -> INCLUDE_ASM build path; struct-typing reference).
 *   s6=a0; s8=a1; s4=a2;  sp[312..324] = 1.0f;
 *   if ((((int*)a0->0x528)->0x14 & 0x4) == 0) return;
 *   n = (int)(255.0f * *(float*)(a0+0x77C));            // 0x437f scale
 *   gl_func_00000000(&D, n, a0+0x2A8, a0+0x2CC);        // +680/+716 regions
 *   gl_func_00000000(a0+0x74C);                          // +1868
 *   m = ((int*)a0->0x75C)->0x20 / 12;                    // +1884, /12
 *   gl_func_00000000(a0+0x704);                          // +1796
 *   gl_func_00000000(a0+0x71C);                          // +1820
 *   ... (continues: ~12 sub-object dispatch calls over s6=a0 +offset
 *        regions, FPU-scaled args, per-element loop on m) ...
 * Struct-typing: a0->0x528 ctx (->0x14 bit 0x4 = render-enable gate),
 * a0->0x77C float (scaled x255 -> int count/alpha), and a cluster of
 * sub-objects/regions at a0 + {0x2A8,0x2CC, 0x704,0x71C,0x74C,0x75C}
 * (0x75C->0x20 / 12 = element count); the body dispatches
 * gl_func_00000000 over these regions with FP-derived args. Caps <80:
 * mul.s/trunc.w.s + div + 12-call s0-s8 spill frame (-328) + beql
 * branch-likely + &D %hi/%lo reloc scheduling. Full body
 * INCLUDE_ASM-preserved (.s = source of truth). INCLUDE_ASM (no
 * episode; tautology-trap rule). */
#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000016F4)();
void arcproc_uso_func_000016F4(char *arg0, s32 arg1, f32 *arg2) {
    f32 sp144;
    f32 sp140;
    f32 sp13C;
    f32 sp138;
    u8 spB8;
    s32 sp94;
    s32 sp90;
    s32 sp88;
    u8 *sp64;
    u8 *sp60;
    f32 *sp58;
    f32 *temp_a2;
    s32 temp_a1;
    s32 temp_s1_2;
    s32 temp_s2_2;
    s32 temp_s5;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s2;
    u8 *temp_s0;
    u8 *temp_s1;
    u8 *temp_s2;
    u8 *temp_s7;
    u8 *var_s0;
    char *temp_t1;
    char *temp_t2;
    char *temp_t3;

    sp138 = 1.0f;
    sp13C = 1.0f;
    sp140 = 1.0f;
    sp144 = 1.0f;
    if (FW(FW(arg0, 0x528), 0x14) & 4) {
        arcproc_uso_func_00001B88(0, (s32) (255.0f * FW(arg0, 0x77C)), (int)arg0 + 0x2A8, (int)arg0 + 0x2CC);
        temp_s7 = (int)arg0 + 0x74C;
        arcproc_uso_func_00001B88(temp_s7);
        temp_s1 = (int)arg0 + 0x704;
        temp_s5 = (s16) FW(FW(arg0, 0x75C), 0x20) / 12;
        arcproc_uso_func_00001B88(temp_s1);
        temp_s2 = (int)arg0 + 0x71C;
        arcproc_uso_func_00001B88(temp_s2);
        temp_s0 = (int)arg0 + 0x734;
        arcproc_uso_func_00001B88(temp_s0);
        arcproc_uso_func_00001B88(&spB8, 0x3D8, arg2);
        sp64 = temp_s1;
        sp60 = temp_s2;
        temp_v0 = arcproc_uso_func_00001B88(&spB8);
        temp_t3 = FW(arg0, 0x744);
        temp_t1 = FW(arg0, 0x714);
        temp_t2 = FW(arg0, 0x72C);
        temp_a2 = (int)arg1 + 0x32;
        temp_s1_2 = 0xA0 - ((s32) (FW(temp_t3, 0x20) + (temp_v0 * 0xD) + FW(temp_t1, 0x20) + FW(temp_t2, 0x20) + 0x10) / 2);
        temp_s2_2 = FW(temp_t2, 0x20) + temp_s1_2 + 4;
        temp_a1 = FW(temp_t1, 0x20) + temp_s2_2 + 4;
        sp88 = FW(temp_t3, 0x20) + temp_a1 + 8;
        sp90 = temp_s2_2;
        sp94 = temp_s1_2;
        sp58 = temp_a2;
        arcproc_uso_func_00001B88(temp_s0, temp_a1, temp_a2, (char *)2);
        var_s0 = &spB8;
        if (temp_v0 > 0) {
            var_s1 = 0;
            var_s2 = sp88;
            do {
                *var_s0 -= 0x30;
                arcproc_uso_func_00001B88(temp_s7, var_s2, (arg1 - ((s16) FW(FW(arg0, 0x75C), 0x22) / 2)) + 0x32, (char *) (*(int*)var_s0 * temp_s5), temp_s5);
                var_s1 += 0xD;
                var_s0 += 1;
                var_s2 += 0xD;
            } while (var_s1 != (temp_v0 * 0xD));
        }
        arcproc_uso_func_00001B88(0, (s32) (255.0f * FW(arg0, 0x77C)), &sp138);
        arcproc_uso_func_00001B88(sp64, sp90, sp58, (char *)2);
        arcproc_uso_func_00001B88(sp60, sp94, sp58, (char *)2);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000016F4);
#endif

/* arcproc_uso_func_0000199C — now 59.93%. 2026-06-02: the final region (field
 * inits 0xD8..0x108 + the gl(s0+0xF0, ((*&D+35)<<16)|(s0->0xD4->0x6B4+7)) call)
 * is byte-exact vs disasm; the residual ~10-insn gap is the alloc-cascade HEAD
 * dead-arm scheduling (regalloc cap). TESTED+REVERTED: rewriting the head to
 * the passthrough goto-merge form (p2=s0; if(!p2)alloc; Lp3/Lp2/Ls0 labels)
 * REGRESSES to 46.61% — the fresh-alloc nested-if below is correct; the gap is
 * pure dead-arm regalloc, not the head form. Don't re-grind the head.
 * verified structural decode (~9%, LEN-DIFF
 * 82/90; alloc-cascade defensive-dead-check + spill/reloc scheduling cap →
 * <80 INCLUDE_ASM build path; constructor struct-typing + alloc-sig ref).
 * int *f(int *a0, int a1, int a2){
 *   s0 = a0 ? a0 : gl_func_00000000(268);  if (!s0) return s0;
 *   p2 = gl_func_00000000(212);  if (!p2) goto init4;
 *   p3 = gl_func_00000000(80);   if (!p3) goto init3;
 *   p4 = gl_func_00000000(44);   if (!p4) goto init2;
 *   gl_func_00000000(p4, &D+0x3DC); p4->0x28 = &D;
 * init2: p3->0x28=&D; init3: p2->0x28=&D; init4: s0->0x28=&D;
 *   s0->0x60 = a2;
 *   s0->0xE0=160; s0->0xE4=29; s0->0xD8=160; s0->0xDC=130;
 *   s0->0xE8=160; s0->0xEC=105; *(float*)(s0+0x108)=1.0f;
 *   s0->0xD4 = a1; *(float*)(a1+0x77C)=1.0f;
 *   gl_func_00000000(s0+0xF0,
 *       ((*(int*)&D + 35) << 16) | (((int*)s0->0xD4)->0x6B4 + 7));
 *   return s0;
 * }
 * Struct-typing: object sizes — main 268(0x10C), subs 212/80/44; every
 * object has ptr @0x28 init &D_00000000. s0 fields: 0x60=a2-arg,
 * 0xD4=a1-arg, 0xD8/DC/E0/E4/E8/EC = {160,130,160,29,160,105} (3 pairs:
 * x@0xD8,y@0xDC … pattern), 0x108=1.0f, sub-call arg a1->0x77C=1.0f.
 * Caps <80: 4-level alloc cascade with defensive `if(ptr!=0)skip` dead
 * checks + heavy stack-spill round each gl_ call + &D %hi/%lo reloc
 * materialization scheduling. INCLUDE_ASM is the correct build path
 * (no episode; tautology-trap rule).
 * 2026-05-31 RULED OUT: converting to the dead-arm PASSTHROUGH cascade
 * (p2=s0; if(!p2) p2=alloc; ... goto init_pN) REGRESSES 59.9->46.6%. The
 * sub-objects ARE genuinely alloc'd (current `p2=alloc(212); if(p2){...}`
 * nested-if form is correct); the bne-skip arms are NOT passthrough. Do not
 * re-try the passthrough form. */
#ifdef NON_MATCHING
char *arcproc_uso_func_0000199C(char *a0, char *a1, int a2) {
    char *s0;
    char *p2;
    char *p3;
    char *p4;
    s0 = a0 ? a0 : (char *)gl_func_00000000(268);
    if (!s0) return s0;
    p2 = (char *)gl_func_00000000(212);
    if (p2) {
        p3 = (char *)gl_func_00000000(80);
        if (p3) {
            p4 = (char *)gl_func_00000000(44);
            if (p4) {
                gl_func_00000000(p4, (char *)&D_00000000 + 0x3DC);
                *(char **)(p4 + 0x28) = &D_00000000;
            }
            *(char **)(p3 + 0x28) = &D_00000000;
        }
        *(char **)(p2 + 0x28) = &D_00000000;
    }
    *(char **)(s0 + 0x28) = &D_00000000;
    *(int *)(s0 + 0x60) = a2;
    *(int *)(s0 + 0xE0) = 160;
    *(int *)(s0 + 0xE4) = 29;
    *(int *)(s0 + 0xD8) = 160;
    *(int *)(s0 + 0xDC) = 130;
    *(int *)(s0 + 0xE8) = 160;
    *(int *)(s0 + 0xEC) = 105;
    *(float *)(s0 + 0x108) = 1.0f;
    *(char **)(s0 + 0xD4) = a1;
    *(float *)(a1 + 0x77C) = 1.0f;
    gl_func_00000000(s0 + 0xF0,
        ((*(int *)&D_00000000 + 35) << 16) | (*(int *)(*(char **)(s0 + 0xD4) + 0x6B4) + 7));
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000199C);
#endif

#ifdef NON_MATCHING
/* arcproc_uso_func_00001B04: 33-insn / 0x84 conditional-init dispatcher.
 *
 * Calls gl_func_00000000(&D_00000000, 0x40100) — likely an alloc/init with
 * a magic flag value. If non-zero, then makes a second call passing
 * arg->[0x50] as input. The second call's return splits into two arms:
 *   v0 != 0: arg->[0x60] = 1; D[0x40] = 8; D[0x44] = 6
 *   v0 == 0: D[0x40] = 6; gl_func_00000000(arg, 7, 0)
 *
 * Initial wrap; bytes likely won't match without unique-extern aliases for
 * the 2 distinct &D references (0x1B14+0x1B20 and 0x1B34+0x1B3C). */
extern int gl_func_00000000();
extern char D_00000000;
void arcproc_uso_func_00001B04(int *arg) {
    int v0;
    int *something;
    int *D;
    v0 = gl_func_00000000(&D_00000000, 0x40100);
    if (v0 == 0) return;
    something = (int*)*(int*)((char*)arg + 0x50);
    v0 = gl_func_00000000(something);
    D = (int*)&D_00000000;
    if (v0 != 0) {
        *(int*)((char*)arg + 0x60) = 1;
        *(int*)((char*)D + 0x40) = 8;
        *(int*)((char*)D + 0x44) = 6;
    } else {
        *(int*)((char*)D + 0x40) = 6;
        gl_func_00000000(arg, 7, 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001B04);
#endif

/* K&R variadic-style helper at 0x1B88 (named directly as placeholder callee in
 * several NM bodies below). MATCHED. Must sit here in file order: IDO emits
 * .text in definition order. */
arcproc_uso_func_00001B88(a0) int * a0; {
    int *t;
    arcproc_uso_func_00000000(a0);
    t = *(int**)((char*)a0 + 0xD4);
    arcproc_uso_func_00000000(t, 0x8C, *(int*)((char*)t + 0x6B0));
}

#ifdef NON_MATCHING
/* arcproc_uso_func_00001BBC: float-gated decay updater. cb(arg0); reads
 * arg0->0xD4->0x77C; if > 0: subtract const *(float*)(&D+0x44), clamp to >=0,
 * cb(sub, 0x8C, sub->0x6B0, arg0), reload; if (value <= 0) cb(arg0). Fresh decode
 * 2026-05-29 (m2c-confirmed), upgraded from boundary bail-marker. The .s
 * over-extends 2 words (0x1C6C/0x1C70 = the stolen f0=1.0f prologue of successor
 * 0x1C74); the function proper is 44 insns ending jr-ra at 0x1C64 — those 2 tail
 * words are not part of this body, an irreducible boundary residual (1C74 is
 * clone-canonical, can't be merged). Caps: arg0/sub structs + cb prototypes
 * untyped (USO-reloc), decay-const not symbolized. NON_MATCHING. */
extern int gl_func_00000000();
void arcproc_uso_func_00001BBC(char *arg0) {
    char *t;
    float f0;

    gl_func_00000000(arg0);
    t = *(char **)(arg0 + 0xD4);
    f0 = *(float *)(t + 0x77C);
    if (f0 > 0.0f) {
        *(float *)(t + 0x77C) = *(float *)(t + 0x77C) - *(float *)((char *)&D_00000000 + 0x44);
        t = *(char **)(arg0 + 0xD4);
        if (*(float *)(t + 0x77C) < 0.0f) {
            *(float *)(t + 0x77C) = 0.0f;
        }
        gl_func_00000000(*(char **)(arg0 + 0xD4), 0x8C,
                         *(int *)(*(char **)(arg0 + 0xD4) + 0x6B0), arg0);
        f0 = *(float *)(*(char **)(arg0 + 0xD4) + 0x77C);
    }
    if (f0 <= 0.0f) {
        gl_func_00000000(arg0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001BBC);
#endif

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
 * FULL DECODE 2026-06-01: semantic body below matches the control flow and
 * call sequence. O2 residual: target has a 0x58 frame and stores incoming $f0
 * to sp+0x48..0x54 before the counter increment; straight C wants either an
 * explicit zeroing mtc1 + 0x38 frame, or worse uninitialized-local reloads.
 * Padding/local-scale probes regressed frame/offsets; keep this NM unless a
 * new IDO stack-shape lever appears.
 *
 * Per scripts/find-byte-identical-clones.py — sig=739fd8d1d3 has 3 plain
 * clones (this + b1_19C0 + b3_1928). Future runs can mirror this wrap. */
void arcproc_uso_func_00001C74(int *a0) {
    float buf[4];

    buf[0] = 0.0f;
    buf[1] = 0.0f;
    buf[2] = 0.0f;
    buf[3] = 0.0f;
    *(int *)((char *)a0 + 0x68) += 1;
    if (gl_func_00000000(*(int *)((char *)a0 + 0x50)) != 0) {
        gl_func_00000000(&D_00000000, (int)(255.0f * *(float *)((char *)a0 + 0x108)), buf);
        gl_func_00000000((char *)a0 + 0xF0);
        if ((*(int *)((char *)a0 + 0x68) & 8) != 0) {
            gl_func_00000000((char *)a0 + 0xF0, 0xA0, 0x7C, 3);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001C74);
#endif

#ifdef NON_MATCHING
/* arcproc_uso_func_00001D18: widget constructor. Field inits (0xC=0x3E4, 0xBC=
 * arg1, 0xB8=arg3, 0x54=arg2, 0xD0=0xFF, 0xD4=0, 0x4C=arg4); float quad @0xC0/C4/
 * C8/CC = {192,255,192,0}/255 (variable-divisor `float denom=255.0f` → runtime
 * div.s held in $f20). Gated on arg1->0x4F0 bit-16: 5 cb setup calls, alloc a
 * child into arg0->0x94, init it (its own {250,235,100,0}/255 quad at +0x64..+0x70,
 * +0x80/84 ints, +0xA0 ptr, clear bit 4 of +0x18, float cb via gl_proto_1d18) and
 * link into the arg0+0x10 list. Fresh decode 2026-05-29 (m2c-confirmed), upgraded
 * from structural ceiling marker. Caps: structs + cb prototypes untyped (USO-reloc).
 * NON_MATCHING. */
extern int gl_proto_1d18(void *, int, int, float, float);
void arcproc_uso_func_00001D18(char *arg0, char *arg1, int arg2, char *arg3, int arg4) {
    float denom = 255.0f;
    float r192 = 192.0f / denom;
    float r0;
    char *sub;

    *(int *)(arg0 + 0xC) = 0x3E4;
    *(char **)(arg0 + 0xBC) = arg1;
    *(char **)(arg0 + 0xB8) = arg3;
    *(int *)(arg0 + 0x54) = arg2;
    *(int *)(arg0 + 0xD0) = 0xFF;
    *(int *)(arg0 + 0xD4) = 0;
    *(int *)(arg0 + 0x4C) = arg4;
    *(float *)(arg0 + 0xC8) = r192;
    *(float *)(arg0 + 0xC0) = r192;
    r0 = 0.0f / denom;
    *(float *)(arg0 + 0xC4) = 255.0f / denom;
    *(float *)(arg0 + 0xCC) = r0;
    if (*(int *)(arg1 + 0x4F0) & 0x10000) {
        gl_func_00000000();
        gl_func_00000000(arg0, 0xE8, 0x13, *(int *)(arg0 + 0x44) + 0x10);
        gl_func_00000000(arg0, 0x69, 0x11, arg0 + 0xA0);
        gl_func_00000000(arg0, 0x123, 0xE1, 1);
        gl_func_00000000(arg0, 0x21, 0x13, arg0 + 0xA8);
        gl_func_00000000(*(int *)(arg0 + 0x8C), *(int *)(*(char **)(arg0 + 0xB8) + 0x34));
        *(char **)(arg0 + 0x94) = (char *)gl_func_00000000(0, *(int *)(arg0 + 0x58));
        gl_func_00000000(*(char **)(arg0 + 0x94), 0);
        gl_proto_1d18(*(char **)(arg0 + 0x94), 0xA0, 0x46, 1.0f, 1.0f);
        sub = *(char **)(arg0 + 0x94);
        *(int *)(sub + 0x18) = *(int *)(sub + 0x18) & ~4;
        sub = *(char **)(arg0 + 0x94);
        *(float *)(sub + 0x64) = 250.0f / denom;
        *(float *)(sub + 0x68) = 235.0f / denom;
        *(float *)(sub + 0x6C) = 100.0f / denom;
        *(float *)(sub + 0x70) = r0;
        *(int *)(*(char **)(arg0 + 0x94) + 0xA0) = *(int *)(arg0 + 0x6C) + 0x108;
        *(int *)(*(char **)(arg0 + 0x94) + 0x80) = 0;
        *(int *)(*(char **)(arg0 + 0x94) + 0x84) = -0x12;
        sub = *(char **)(arg0 + 0x94);
        gl_func_00000000(arg0 + 0x10, sub);
        if (*(int *)(sub + 0x14) != 0) {
            *(int *)(sub + 4) = 1;
        }
        *(char **)(sub + 0x14) = arg0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001D18);
#endif

/* arcproc_uso_func_00001F0C: boundary-corrected (stolen-prologue mirror). The 2
 * words `lui t6,0; lw t6,0x64(t6)` (preloading D[0x64]) sat PAST func_00001D18's
 * `jr ra` epilogue — a splat mis-attribution; they are THIS function's prologue.
 * Shrank func_00001D18.s (0x1F4 -> 0x1EC) and prepended the 2 words here
 * (0x48 -> 0x50). C emits the same lui+lw, so the merged boundary is byte-exact. */
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

#ifdef NON_MATCHING
/* arcproc_uso_func_00001F54: UI animation/draw orchestrator (sibling of the
 * mgrproc per-frame steps). Gate arg0->0xBC bit-16 && ->0x4DC==1: bump 0x30,
 * decrement 0xA0 by 0x21 (floor 0 + cleanup). Then if gated: optional 4-draw
 * block; ramp arg0->0xA8 toward arg0->0x44->0x18 by 0xFA/0x32/0x19/1; draw; in
 * states 0/1 three more draws (one with a 0.0f float arg via gl_proto_1f54); if
 * arg0->0x44->0x1C: enable a sub-widget (0x94) + ramp its 0x20 by 0x32/5/1, else
 * disable; in state 2 (0x4F8==0) blink 0x8C by (0xAC++ & 8). cb(arg0) tail. Fresh
 * decode 2026-05-29 (m2c-confirmed). 80.6% reg-blind. Residual: float-call mfc1
 * arg setup + spill regalloc. Caps: structs + cb prototypes untyped (USO-reloc).
 * NON_MATCHING. */
extern int gl_proto_1f54(void *, int, int, float, float);
void arcproc_uso_func_00001F54(char *arg0) {
    char *bc;
    char *p44;
    char *p94;
    char *p8c;
    int a1;
    int rem;
    int v0;
    int t8;
    int t2;
    int a;
    int r;

    bc = *(char **)(arg0 + 0xBC);
    if ((*(int *)(bc + 0x4F0) & 0x10000) && (*(int *)(bc + 0x4DC) == 1)) {
        *(int *)(arg0 + 0x30) = *(int *)(arg0 + 0x30) + 0x21;
        gl_func_00000000();
        gl_func_00000000(arg0);
        t2 = *(int *)(arg0 + 0xA0) - 0x21;
        *(int *)(arg0 + 0xA0) = t2;
        if (t2 < 0) {
            *(int *)(arg0 + 0xA0) = 0;
            gl_func_00000000(*(int *)(arg0 + 0x84), 0, 0);
            gl_func_00000000(*(int *)(arg0 + 0xBC));
            *(int *)(arg0 + 0x2C) = 0;
        }
    }
    gl_func_00000000(arg0);
    bc = *(char **)(arg0 + 0xBC);
    if (*(int *)(bc + 0x4F0) & 0x10000) {
        if ((*(int *)(bc + 0x4DC) == 1) && (*(int *)(*(char **)(arg0 + 0x44) + 0x34) != 0)) {
            gl_func_00000000(arg0);
            gl_func_00000000(arg0, *(int *)(arg0 + 0xA0));
            gl_func_00000000(*(int *)(arg0 + 0x84), *(int *)(arg0 + 0xA0), 0);
            gl_func_00000000(*(int *)(arg0 + 0xBC));
        }
        a1 = *(int *)(arg0 + 0xA8);
        rem = *(int *)(*(char **)(arg0 + 0x44) + 0x18) - a1;
        if (rem >= 0xFA) {
            a1 += 0xFA;
            *(int *)(arg0 + 0xA8) = a1;
        } else if (rem >= 0x32) {
            a1 += 0x32;
            *(int *)(arg0 + 0xA8) = a1;
        } else if (rem >= 0x19) {
            a1 += 0x19;
            *(int *)(arg0 + 0xA8) = a1;
        } else if (rem > 0) {
            a1 += 1;
            *(int *)(arg0 + 0xA8) = a1;
        }
        gl_func_00000000(*(int *)(arg0 + 0x8C), a1);
        v0 = *(int *)(*(char **)(arg0 + 0xBC) + 0x4DC);
        if ((v0 == 1) || (v0 == 0)) {
            gl_func_00000000(*(int *)(arg0 + 0x84), *(int *)(arg0 + 0xA0), 1);
            gl_func_00000000(*(int *)(arg0 + 0x80), *(int *)(*(char **)(arg0 + 0x44) + 0x30), 0);
            p44 = *(char **)(arg0 + 0x44);
            gl_proto_1f54(*(int *)(arg0 + 0x80), *(int *)(p44 + 8), *(int *)(p44 + 0xC), 0.0f, 0.0f);
        }
        if (*(int *)(*(char **)(arg0 + 0x44) + 0x1C) != 0) {
            gl_proto_1f54(*(int *)(arg0 + 0x94), 0xA0, 0x46, 1.0f, 1.0f);
            *(int *)(*(char **)(arg0 + 0x94) + 0x78) = 0xFF;
            p94 = *(char **)(arg0 + 0x94);
            *(int *)(p94 + 0x18) = *(int *)(p94 + 0x18) | 4;
            p44 = *(char **)(arg0 + 0x44);
            a = *(int *)(p44 + 0x20);
            r = *(int *)(p44 + 0x1C) - a;
            if (r >= 0x32) {
                *(int *)(p44 + 0x20) = *(int *)(p44 + 0x20) + 0x32;
                gl_func_00000000(0x20, 0x32);
                a = *(int *)(*(char **)(arg0 + 0x44) + 0x20);
            } else if (r >= 5) {
                *(int *)(p44 + 0x20) = *(int *)(p44 + 0x20) + 5;
                gl_func_00000000(0x20, 5);
                a = *(int *)(*(char **)(arg0 + 0x44) + 0x20);
            } else if (r > 0) {
                *(int *)(p44 + 0x20) = *(int *)(p44 + 0x20) + 1;
                gl_func_00000000(0x20, 1);
                a = *(int *)(*(char **)(arg0 + 0x44) + 0x20);
            }
            gl_func_00000000(*(int *)(arg0 + 0x94), a);
        } else {
            p94 = *(char **)(arg0 + 0x94);
            *(int *)(p94 + 0x18) = *(int *)(p94 + 0x18) & ~4;
        }
        bc = *(char **)(arg0 + 0xBC);
        if ((*(int *)(bc + 0x4DC) == 2) && (*(int *)(bc + 0x4F8) == 0)) {
            t8 = *(int *)(arg0 + 0xAC) + 1;
            *(int *)(arg0 + 0xAC) = t8;
            if (t8 & 8) {
                p8c = *(char **)(arg0 + 0x8C);
                *(int *)(p8c + 0x18) = *(int *)(p8c + 0x18) & ~4;
            } else {
                p8c = *(char **)(arg0 + 0x8C);
                *(int *)(p8c + 0x18) = *(int *)(p8c + 0x18) | 4;
            }
        }
    }
    gl_func_00000000(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001F54);
#endif

/* Original jals target fn-4 (leading-nop true entries; base never calls the
 * splat-named entries) — undefined_syms absolutes per the h2h_4DC precedent. */
extern int arcproc_uso_func_arc_8F8();
extern int arcproc_uso_func_arc_934();
extern int arcproc_uso_func_arc_970();
extern int arcproc_uso_func_arc_9C8();
void arcproc_uso_func_000022A4(char *dst) {
    int tmp;
    arcproc_uso_func_arc_8F8(&tmp);
    arcproc_uso_func_arc_8F8((int*)(dst + 0x10));
}

void arcproc_uso_func_000022D4(char *dst) {
    int tmp;
    arcproc_uso_func_arc_8F8(&tmp);
    arcproc_uso_func_arc_934((float*)(dst + 0x10));
}

void arcproc_uso_func_00002304(char *dst) {
    int tmp;
    arcproc_uso_func_arc_8F8(&tmp);
    arcproc_uso_func_arc_970((Quad4*)(dst + 0x10));
}

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
void *arcproc_uso_func_00002334(int *arg0) {
    int *p2;
    int *head;
    int *p1;
    p1 = (int*)gl_func_00000000(0x40);
    if (p1 != 0) {
        gl_func_00000000(p1);
        *(int*)((char*)p1 + 0x28) = (int)&D_00000000;
        *(int*)((char*)p1 + 0x3C) = 0;
    }
    p2 = p1;
    p1 = arg0;
    head = (int*)p1[0x40 / 4];
    if ((int*)p1[0x40 / 4] != 0) {
        gl_func_00000000((char*)p2 + 0x10, head);
        if (*(int*)((char*)head + 0x14) != 0) {
            *(int*)((char*)head + 0x4) = 1;
        }
        *(int*)((char*)head + 0x14) = (int)p2;
    }
    return p2;
}

void arcproc_uso_func_000023C4(char *dst) {
    int tmp;
    arcproc_uso_func_arc_8F8(&tmp);
    arcproc_uso_func_arc_9C8((Vec3*)(dst + 0x10));
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

/* arcproc_uso_func_000024C0: F1 + 3 trailing empty stubs (0x5C total).
 * Sibling of 23F4/2438/247C (state-set menu helpers, plain-C exact at
 * -O2). Same shape with N=9 here (vs N=4/1/2 for the others).
 *
 * F1 @ 0x24C0-0x2500: 16-insn body — the "real" function.
 * F2/F3/F4 @ 0x2504/0x250C/0x2514: 2-insn `jr ra; nop` empty stubs
 * with no callers in src/ or undefined_syms_auto.txt (dead splat-
 * bundled stubs).
 *
 * Was promoted 2026-05-17 with plain-C F1 body + SUFFIX_BYTES for the three
 * empty trailers + INSN_PATCH on the three cross-USO data ref HI/LO pairs
 * so the object carried the baked 0x70/0x40/0x74 offsets expected by the
 * pure-asm baseline. Instruction-appending SUFFIX_BYTES + INSN_PATCH REMOVED
 * 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy; docs/POST_CC_RECIPES.md
 * DEPRECATED. The all-zero/data SUFFIX_BYTES mechanism for genuine padding
 * is still allowed; here the empty trailers are jr-ra-stubs (instructions),
 * so the suffix was instruction-bytes. NATURAL CEILING: F1 body C-only
 * (plus byte-exact-via-includes for trailers via splat coverage). */
extern int gl_func_00000000();
extern int gl_ref_00000040, gl_ref_00000070, gl_ref_00000074;
void arcproc_uso_func_000024C0(void) {
    gl_func_00000000(gl_ref_00000070);
    gl_ref_00000040 = 9;
    gl_func_00000000(gl_ref_00000074, -1, 0);
}

/* arcproc_uso_func_00002504/250C/2514: 3 empty `jr ra; nop` stubs RECOVERED
 * 2026-05-28 from the 000024C0 bundle gap (dropped — no .s, missing from
 * build). `void f(void){}` compiles to exactly `jr ra; nop` (0x8) at -O2 —
 * byte-exact matches (the prior SUFFIX_BYTES fake is unnecessary). */
void arcproc_uso_func_00002504(void) {}
void arcproc_uso_func_0000250C(void) {}
void arcproc_uso_func_00002514(void) {}

/* arcproc_uso_func_0000251C - verified structural decode; SIBLING of the
 * alloc-cascade ctor family (arcproc_uso_func_0000199C /
 * timproc_uso_b1_func_000016F8) + 24F4-style registration tail.
 * Documented alloc-cascade dead-check + registration sub-80 ceiling ->
 * INCLUDE_ASM build path; struct-typing reference.
 *   s0 = a0 ? a0 : gl_func_00000000(84);   if (!s0) return s0;
 *   p2 = gl_func_00000000(80);   if (!p2) goto init;
 *   p3 = gl_func_00000000(44);   if (!p3) goto init2;
 *   gl_func_00000000(p3, &D+1160);  p3->0x28 = &D;
 * init2: p2->0x28 = &D;  init: s0->0x28 = &D;
 *   s0->0xC = &D+1168;
 *   // 24F4-style registration sequence:
 *   gl_func_00000000(&D+16,  0x280000);
 *   gl_func_00000000(&D+40,  0x280001);
 *   ... (more gl_func_00000000(&D+OFF, 0x28xxxx | k) registrations) ...
 * Struct-typing: cross-confirms the alloc-cascade ctor family - object
 * sizes 84/80/44, every sub-object ptr @0x28 = &D_00000000, main
 * s0->0xC = &D+0x490 (1168) descriptor; tail registers slots into &D
 * data regions via the 0x28-prefixed packed args (same shape as
 * timproc_uso_b1_func_000024F4). Caps <80: defensive `if(p!=0)`
 * alloc-cascade dead checks + per-call spill + &D %hi/%lo reloc
 * scheduling. Full per-slot args INCLUDE_ASM-preserved (.s = source of
 * truth). INCLUDE_ASM (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
char *arcproc_uso_func_0000251C(char *a0) {
    char *s0;
    char *p2;
    char *p3;
    s0 = a0 ? a0 : (char *)gl_func_00000000(84);
    if (!s0) return s0;
    p2 = (char *)gl_func_00000000(80);
    if (p2) {
        p3 = (char *)gl_func_00000000(44);
        if (p3) {
            gl_func_00000000(p3, (char *)&D_00000000 + 1160);
            *(char **)(p3 + 0x28) = &D_00000000;
        }
        *(char **)(p2 + 0x28) = &D_00000000;
    }
    *(char **)(s0 + 0x28) = &D_00000000;
    *(char **)(s0 + 0xC) = (char *)&D_00000000 + 1168;
    gl_func_00000000((char *)&D_00000000 + 16, 0x280000);
    gl_func_00000000((char *)&D_00000000 + 40, 0x280001);
    gl_func_00000000((char *)&D_00000000 + 64, 0x280002);
    gl_func_00000000((char *)&D_00000000 + 88, 0x280003);
    *(int *)(s0 + 72) = gl_func_00000000(0);
    gl_func_00000000(*(int *)(s0 + 72), s0);
    gl_func_00000000(*(int *)(s0 + 72), ((*(int *)&D_00000000 + 3) << 16) | 1, -1, &D_00000000);
    gl_func_00000000(*(int *)(s0 + 72), ((*(int *)&D_00000000 + 3) << 16) | 3, -1, &D_00000000);
    gl_func_00000000(*(int *)(s0 + 72), ((*(int *)&D_00000000 + 3) << 16) | 2, -1, &D_00000000);
    gl_func_00000000(*(int *)(s0 + 72), ((*(int *)&D_00000000 + 3) << 16) | 5, -1, &D_00000000);
    *(int *)(*(int *)(s0 + 72) + 48) =
        gl_func_00000000(0, &D_00000000, 72, 221, 3, 13);
    gl_func_00000000(*(int *)(s0 + 72));
    gl_func_00000000(*(int *)(s0 + 72), 120);
    {
        char *v0 = *(char **)(s0 + 72);
        char *vt = *(char **)(v0 + 40);
        ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)v0);
    }
    gl_func_00000000(s0 + 16, *(int *)(s0 + 72));
    {
        char *a3 = *(char **)(s0 + 72);
        if (*(int *)(a3 + 0x14) != 0) {
            *(int *)(a3 + 0x4) = 1;
        }
        *(int *)(a3 + 0x14) = (int)s0;
    }
    gl_func_00000000(s0 + 16, *(int *)((char *)&D_00000000 + 400));
    {
        char *a3 = *(char **)((char *)&D_00000000 + 400);
        if (*(int *)(a3 + 0x14) != 0) {
            *(int *)(a3 + 0x4) = 1;
        }
        *(int *)(a3 + 0x14) = (int)s0;
    }
    gl_func_00000000(*(int *)((char *)&D_00000000 + 400));
    *(int *)(s0 + 80) = 0;
    *(int *)(s0 + 48) = 1;
    *(int *)(s0 + 44) = 0;
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000251C);
#endif

/* arcproc_uso_func_000027BC: 42-insn string-match + vtable-dispatch.
 *
 *   if (gl_func(&D_str, 0x40100, a0) != 0) {
 *     p = a0->[0x48];
 *     idx = p->[0x7C];
 *     t9 = (p + idx*0x28)->[0x90];          // vtable fn ptr
 *     if (t9 != 0) {
 *       gl_func();                          // some callback
 *       p = a0->[0x48];                     // reload
 *       *(int*)(&D_0 + 0x70) = (int)p;
 *       *(int*)(&D_0 + 0x74) = (int)a0;
 *       idx = p->[0x7C];                    // reload
 *       (*t9)();                            // indirect dispatch
 *     }
 *   }
 *
 * Pattern: lookup-then-dispatch. The 0x7C index field selects from a
 * 0x28-byte stride table at p; vtable slot at +0x90 per entry.
 * 2026-05-18: 86.02% → 91.19% via two fixes:
 *  (1) inner gl_func arg is 5 (not 0-arg); (2) two distinct externs
 *  D_arc_27BC_g70 / g74 to defeat IDO CSE on the two &D+0x70 / &D+0x74
 *  stores so each gets its own lui (matches target's two-lui shape).
 *  Remaining: register-name $t0/$v0/$t9 vs mine $t8/$v1/$a1 — reg-alloc.
 *  2026-06-10 (15F0-recipe pass): 91.19 -> 99.29. The shared p/idx/fn
 *  variables (one lr spanning the gl(5) call) split via per-block
 *  fresh locals + dead-init (p0/p1) -- the t-pool renumber fixed.
 *  RESIDUAL 3 real diffs: one 2-op addu operand order (base+scaled,
 *  the 294C-class allocator choice) and block-2's base load v1-vs-v0
 *  (the dead-gl(5)-return reuse the target makes and mine avoids;
 *  inverse of the if(1){} lever -- CRACKED same day: a VOID-PROTOTYPED
 *  call alias (gl_func_00000000_void = 0x0) makes the return provably
 *  dead, so IDO reuses $v0 for the next load = the target shape.
 *  91.19 -> 99.52. FINAL residual: the two 2-op addu operand orders
 *  (294C class; ALL spellings probed including grouped-with-void-alias
 *  2026-06-11 -- the lever sequencing left that combo untried, now
 *  also flat) + 2 reloc-false stores. One allocator choice from
 *  exact; permuter or uopt-internals territory.
 *  2026-06-11 permuter attempt: hand-rolled scratch (base.c +
 *  expected-TU target.o) RUNS but scores TU-wide (~247k metric,
 *  meaningless for a 2-insn gate) -- the target.o must contain ONLY
 *  the fn. Use tools/decomp-permuter/import.py with PERMUTER=1 make
 *  mode (see reference_permuter_asmproc memo) for a real run.
 *  2026-06-11 SCOPED RUN (import.py): base score 60 -> best 50 within
 *  minutes via TWO new shapes: (a) the array index 0x48/4 held in a
 *  VARIABLE (new_var) -- the index-through-variable trick; (b) the
 *  condition deref spelled multiply-FIRST with p0 fully inlined.
 *  Long background run in flight (nonmatchings/arcproc_uso_func_
 *  000027BC/, log /tmp/perm27bc.log); import the best output when it
 *  plateaus or hits 0. */
extern int gl_func_00000000();
extern void gl_func_00000000_void(int);  /* void-prototyped alias (=0x0): dead-return-reuse lever */
extern char D_arc_27BC_str;
extern int D_arc_27BC_g70;
extern int D_arc_27BC_g74;
void arcproc_uso_func_000027BC(int *a0)
{
  int new_var2;
  unsigned char new_var3;
  int new_var;
 ;
  if (gl_func_00000000(&D_arc_27BC_str, 0x40100, a0) != 0)
  {
    int *p0 = 0;
    new_var2 = 0x7C / 4;
    p0 = (int *) a0[0x48 / 4];
    if ((*((int *) ((((char *) p0) + (p0[0x7C / 4] * 0x28)) + 0x90))) != ((0, 0)))
    {
      gl_func_00000000_void(5);
      D_arc_27BC_g70 = a0[new_var = 0x48 / 4];
      D_arc_27BC_g74 = (int) a0;
      {
        int *p1 = 0;
        p1 = (int *) a0[new_var];
        ((void (*)(void)) (*((int *) ((((char *) p1) + (p1[new_var2] * 0x28)) + (new_var3 = 0x90)))))();
      }
    }
  }
}

void arcproc_uso_func_00002864(void) {
    arcproc_uso_func_00000000();
}

/* arcproc_uso_func_00002884: 62-insn double-loop initializer (fresh decode
 * 2026-05-29 -> ~92% / 5-diff). Copies a 5-int table from &D+0x4A0 to a stack
 * buffer, then for each outer step (s3: 16..208 step 32) iterates the 5 buffer
 * entries (s0: 0..256 step 64), computing s1 = &D+0x10 + buf[i]*24 and calling
 * 3 funcs: f(s1); f(s1); f(s1, s0, s3, 0). Logic byte-faithful; saved-reg
 * count (8) matches. Two levers got it 62-diff -> 5-diff:
 *  - index-form `buf.w[i]` (not pointer `*p++`) keeps the buffer base out of a
 *    9th saved reg (IDO recomputes `addiu s2,sp,84` each outer iter).
 *  - REG-SWAP CRACKED via the regalloc dump (2026-05-30): the base/24-mult
 *    s4<->s5 swap was an ENCOUNTER-ORDER tiebreak. Promoted loop-invariants get
 *    saved regs in UCODE-encounter order; `s1 = base + buf[i]*24` references 24
 *    (the umpy) BEFORE base (the uadd), so 24 grabbed s4. Writing `s1 = base;
 *    s1 += buf[i]*24;` references base FIRST -> base=s4, 24=s5 (matches). [dump
 *    method: cc -Wo,-zdbug:6 -> ./uoptlist; promoted consts = the candidates
 *    created in reg-alloc-prep, regs map 14..21 = $s0..$s7.]
 *  - REMAINING 5 diffs: pure instruction-SCHEDULING order (values all correct) —
 *    3 swapped pairs where target emits the address setup (addiu s4 base / addiu
 *    s2 bufptr) BEFORE the counter init (li s3 / move s0). Resists init-statement
 *    reordering (scheduler is in ugen backend, not uopt). Stays NM at 92%.
 *  - 2026-06-21 (agent-b sweep): REMOVED the old `base++; base--;` no-op lever —
 *    it had drifted into emitting a REAL trailing `addiu s3,s3,0` (and a 2nd at the
 *    loop bottom), making the build 252b / 6-non-reloc-diff and OVERSIZE vs the
 *    248b target. Dropping it restores SIZE-EXACT 248b. Residual is now 5 non-reloc
 *    diffs = (a) base/counter saved-reg coloring TIE (target base=s4, counter=s3;
 *    build base=s3, counter=s4 — encounter-order priority, `register` hint + split
 *    decls no-op) + (b) bufptr/s0 INIT-ORDER schedule tie (target `addiu s2,sp,84`
 *    before `or s0,zero,zero`; build reverse). Both are ugen-backend allocator/
 *    scheduler ties: permuter-immune (prior run), and 6 manual levers tried this
 *    sweep (split-decl, single-expr s1, ptr-walk bp++, buf.w[0]*0 init, commuted
 *    24*buf.w[i], base-after-buf-copy) all 0-effect. IMMUNE. Stays NM, size-exact. */
typedef struct { int w[5]; } Arc2884Buf;
#ifdef NON_MATCHING
void arcproc_uso_func_00002884(void *a0) {
  Arc2884Buf buf;
  int i;
  int s0;
  int s3;
  char *base = ((char *) (&D_00000000)) + 0x10;
  buf = *((Arc2884Buf *) (((char *) (&D_00000000)) + 0x4A0));
  s3 = 16;
  do
  {
    i = 0;
    s0 = 0;
    do
    {
      char *s1 = base;
      s1 += buf.w[i] * 24;
      gl_func_00000000(s1);
      gl_func_00000000(s1);
      gl_func_00000000(s1, s0, s3, 0);
      s0 += 64;
      i++;
    }
    while (s0 != 320);
    s3 += 32;
  }
  while (s3 != 240);
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00002884);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso/arcproc_uso_func_00002884_pad.s")
