#include "common.h"

/* P0 AUDIT WARNING 2026-06-10: the decompressed block3 build differs
 * from ROM (assets/timproc_uso_block_3.bin) by 963 words in
 * [0x690..0x30D0]. After the 87F4/88A0 circular-false-positive
 * retraction (docs/MATCHING_WORKFLOW post-mortem), every b3 match/
 * episode in that range is SUSPECT until per-symbol-verified against
 * the block bin ground truth. Do not refresh expected/ for this unit
 * until resolved. */

extern int gl_func_00000000();
extern char D_00000000;
extern char D_00000001;
extern char D_00000002, D_00000003, D_00000004, D_00000005;
extern char D_00000006, D_00000007, D_00000008, D_00000009;
typedef struct { int a, b, c, d; } Quad4;

#ifdef NON_MATCHING
/* Macro definitions for NM-wrap bodies. Auto-managed by /struct-name-tick.
 * Default build never sees these — wrap bodies aren't compiled.
 * TIMB3_D_64: int value passed to gl_func_00000000 calls and OR'd with
 * flag 0x4000 (positional name pending semantics). timproc_uso_b3 D+0x64.
 * TIMB3_D_48: int state-companion slot, set to 0xD alongside D+0x44=4 across
 * the dispatch wraps. Positional. timproc_uso_b3 D+0x48.
 */
#define TIMB3_D_64 (*(int*)((char*)&D_00000000 + 0x64))
#define TIMB3_D_48 (*(int*)((char*)&D_00000000 + 0x48))
#endif

/* timproc_uso_b3_func_00000000 / _0000004C (contiguous -O0 run, 0x0..0xB0) live
 * in timproc_uso_b3_o0_0.c — carved into a dedicated -O0 sub-unit and
 * concatenated into the Yay0 block (region 0) before compression. See the
 * timproc_uso_block3_yay0 rule in the Makefile. */

/* timproc_uso_b3_func_000000B0: 317-insn (0x4F4) -O0 state-machine
 * dispatcher: 14-case jumptable switch on arg1, loops re-reading the next
 * state from D+0x40 until a case sets `done`. EXACT 2026-07-09 via the -O0
 * donor timproc_uso_b3_o0_B0.c spliced in through REPLACE_FUNC_BODY (same
 * recipe as 5A4/65C below). This in-TU body is a compile stand-in only —
 * its bytes are replaced by the donor's in build/.../timproc_uso_b3.c.o.
 * The old "rodata jumptable = structural cap" note applied to the -O2
 * in-TU compile; the -O0 donor emits its jumptable at .rodata offset 0,
 * so the lui/lw dispatch words carry in-place addend 0 = the target's raw
 * pre-USO-reloc words. Twin: timproc_uso_b1_func_000000B0 (4 immediates
 * differ: case5/case7 second-a3 1->2, case12 mask 0x2000->0x4000). */
timproc_uso_b3_func_000000B0(a0, a1) int * a0; int a1; {
    char *d = (char *)&D_00000000;
    int done = 0;
    int v, s0v;
    do {
        switch (a1) {
        case 0:
            gl_func_00000000(a0, 1, 7, 1);
            *(int *)(d + 0x44) = 4; *(int *)(d + 0x48) = 13; done = 1;
            break;
        case 1:
            gl_func_00000000(a0, 1, 7, 1);
            *(int *)(d + 0x44) = 4; *(int *)(d + 0x48) = 13; done = 1;
            break;
        case 2:
            gl_func_00000000(a0, 1, 7, 2);
            *(int *)(d + 0x44) = 4; *(int *)(d + 0x48) = 13; done = 1;
            break;
        case 3:
            gl_func_00000000(a0, 1, 7, 4);
            *(int *)(d + 0x44) = 4; *(int *)(d + 0x48) = 13; done = 1;
            break;
        case 4:
            gl_func_00000000(a0, 1, *(int *)(d + 0x64));
            *(int *)(d + 0x40) = 5;
            break;
        case 5:
            gl_func_00000000(d, *(int *)(d + 4));
            gl_func_00000000(d, 4, *(int *)(d + 0x64), 2);
            v = gl_func_00000000(a0, *a0, 1);
            s0v = gl_func_00000000(0, 0x410000, v, *a0);
            gl_func_00000000(a0, 0, s0v);
            done = 1;
            break;
        case 6:
            gl_func_00000000(a0, 0, *(unsigned char *)(d + 0x178));
            *(int *)(d + 0x40) = 7;
            break;
        case 7:
            gl_func_00000000(d, 10, *(int *)(d + 0x64), 2);
            v = gl_func_00000000(a0, *a0, 1);
            s0v = gl_func_00000000(0, *(int *)(d + 0x170) + 0x1A000F, v, *a0);
            gl_func_00000000(a0, 0, s0v);
            done = 1;
            break;
        case 8:
            gl_func_00000000(a0);
            *(int *)(d + 0x40) = *(int *)(d + 0x44);
            break;
        case 9:
            gl_func_00000000(a0);
            *(int *)(d + 0x40) = 10;
            break;
        case 10:
            gl_func_00000000(d, 7, 0, 0);
            s0v = gl_func_00000000(0);
            gl_func_00000000(a0, 1, s0v);
            done = 1;
            break;
        case 11:
            v = gl_func_00000000(a0, *a0, 4);
            s0v = gl_func_00000000(0, *(int *)(d + 0x170) + 0x20000, v, *a0);
            {
                char *r = (char *)s0v;
                gl_func_00000000(d + 0x10, r);
                if (*(int *)(r + 0x14) != 0) *(int *)(r + 4) = 1;
                *(int *)(r + 0x14) = (int)d;
            }
            gl_func_00000000(a0, *a0);
            done = 1;
            break;
        case 12:
            s0v = gl_func_00000000(*(int *)(d + 0x64));
            gl_func_00000000(a0, (*(int *)(d + 0x64) | 0x4000) | s0v, 0x4000, *a0);
            done = 1;
            break;
        case 13:
            s0v = gl_func_00000000(0, 1, 0);
            {
                char *r = (char *)s0v;
                gl_func_00000000(d + 0x10, r);
                if (*(int *)(r + 0x14) != 0) *(int *)(r + 4) = 1;
                *(int *)(r + 0x14) = (int)d;
            }
            done = 1;
            break;
        }
        a1 = *(int *)(d + 0x40);
    } while (done == 0);
}

extern int D_00000148;
extern int D_0000014C;
extern int D_00000068;

/* 46-insn -O0 allocator-wrapper (0xB8). LANDED 2026-06-21 as a masked-shape
 * TWIN-PORT of timproc_uso_b1_func_000005A4: the two target functions are
 * instruction-for-instruction identical except two immediates (b1 0x1, b3
 * 0x2). Matched via the same splice-import-donor-relocs recipe as b1 — the
 * -O0 donor timproc_uso_b3_o0_5A4.c is spliced in via REPLACE_FUNC_BODY, which
 * imports the donor HI16/LO16/26 relocs; D_00000148/0x14C/0x68 in
 * undefined_syms_auto.txt resolve to the reloc-blind expected/.o bytes. The
 * earlier "BLOCKED by Yay0 pipeline" note was wrong: the splice operates on
 * the .o, independent of Yay0 compression. fuzzy=100.
 *
 * -O0 indicators preserved (the donor IS compiled at -O0): unfilled jal delay
 * slots, `move s0,v0` save, trailing `b epilogue; nop`, frame -0x28. */
void timproc_uso_b3_func_000005A4(int **arg0, int arg1, int arg2) {
    int handle = gl_func_00000000(2);
    register int new_obj = gl_func_00000000(0, D_00000148, 2, arg2);
    *arg0 = (int*)new_obj;
    D_0000014C = new_obj;
    gl_func_00000000(handle);
    if (arg1 != 0) {
        *(int*)((char*)*arg0 + 0x14) = 2;
    } else {
        *(int*)((char*)*arg0 + 0x14) = 0;
    }
    D_00000068 = 0;
}

/* 21-insn -O0 cleanup wrapper. Single gl_func + zero a0[0] + zero D[0x14C].
 * Byte-identical .s to the EXACT timproc_uso_b1_func_0000065C (same 0x65C).
 * Matched 2026-05-30 via the -O0 REPLACE_FUNC_BODY donor splice (donor
 * src/timproc_uso_b3/timproc_uso_b3_o0_65C.c). This was unblocked by fixing
 * scripts/replace-function-body.py to re-align post-.text sections after the
 * size-growing (+0x1C) splice — previously the misaligned sections made
 * objdiff reject the object. This -O2 body is what the main object compiles;
 * the donor's -O0 bytes are spliced over it. */
void timproc_uso_b3_func_0000065C(int *a0) {
    gl_func_00000000((int*)a0[0], 3);
    a0[0] = 0;
    *(int*)((char*)&D_00000000 + 0x14C) = 0;
}

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
/* Chain sibling of 0x790, 0x7D4, 0x818. MATCHED via pad-sidecar boundary
 * correction (orphan lui v0,0; addiu v0,0 moved from func_000006FC's pad into
 * this fn's .s; 0x3C->0x44, starts 0x744). Same recipe as b1 chain 0x734-0x800. */
extern int D_state_b3_74C;
void timproc_uso_b3_func_0000074C(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 1;
    gl_func_00000000(D_state_b3_74C, -1, 0);
}
/* Chain sibling: t7=2. MATCHED via pad-sidecar boundary correction (orphan
 * moved from func_0000074C's pad into this fn's .s; 0x3C->0x44, starts 0x788). */
extern int D_state_b3_790;
void timproc_uso_b3_func_00000790(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 2;
    gl_func_00000000(D_state_b3_790, -1, 0);
}
/* Chain sibling: t7=3. MATCHED via pad-sidecar boundary correction (orphan
 * moved from func_00000790's pad into this fn's .s; 0x3C->0x44, starts 0x7CC). */
extern int D_state_b3_7D4;
void timproc_uso_b3_func_000007D4(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 3;
    gl_func_00000000(D_state_b3_7D4, -1, 0);
}
/* End of b3 chain. MATCHED via pad-sidecar boundary correction (orphan lui v0,0;
 * addiu v0,0 moved from func_000007D4's pad into this fn's .s; 0x3C->0x44, starts
 * 0x810). Unique extern D_state_b3_818 (=0) at the gl_func arg breaks IDO's
 * &D-CSE so the target's fresh lui+lw at the call site reproduces. */
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

/* timproc_uso_b3_func_00000994: 230-insn constructor (sibling of titproc
 * 1E9C / timproc_b1 97C / timproc_b5 478). jal-0 = cross-USO placeholder
 * gl_func_00000000 (disasm mislabels as func_000000B0).
 *
 * 2026-07-10: 65.7% -> 225/230 words (97.8%), frame -72 + all named homes
 * exact, via the two-s-reg constructor kit (docs/IDO_CODEGEN.md) minus the
 * register-node (this sibling has only s0=self):
 *  - arg0-as-self (param reassign) colors s0; alloc-fail exits via its own
 *    `b .Lepilogue; lw ra` (write `return (void *)a0;` inside the guard);
 *  - 4-level cascade n1/n2/n3 colors a2/v1/a0, homes 64/60/56 (decl order);
 *  - SIX-CALL registration block: each call passes &D_00000000 as an
 *    INVISIBLE 4TH ARG -> lui a3/addiu a3 materialization + lw a1,0(a3)
 *    (every held-pointer/if(1)/goto/array-decay/volatile spelling folds or
 *    lands in t-ring; the arg-precolor is what makes it a3);
 *  - tail node: `int * volatile nd` + arg-fold `gl(slot, nd = *(...+0x190))`
 *    loads straight to a1 + spills to its decl home 44 in the jal delay;
 *    single reload into plain nd2, and nd2 passed as invisible 4th arg to
 *    the 0139B0-equiv call -> a3 precolor for the whole flag block;
 *  - registration flag blocks re-read the object field per use (fresh
 *    derefs; the [0x4/4]=1 store forces the target's if-arm reload while
 *    the beql-annulled else path reuses the old reg);
 *  - decl order sub,n1,n2,n3,vt,nd2,nd,padA,slot(volatile),padB lays the
 *    exact 10-word hole map (68/52/48/40/32 holes);
 *  - vt PRELOADED as a statement (`vt = ...; gl(slot = ..., vt)`) sinks the
 *    volatile slot store into the jal delay (folding vt into arg2 makes as1
 *    pick the lw for the delay instead).
 * RESIDUAL (5 words, as1/ugen-internal pair-order class): [or s0,a0] vs
 * [sw a3,84] prologue delay-fill pick; [addiu a0,s0,16] vs [lw a1,1704]
 * adjacent order at the slot call; tail hi-temp lui a1 vs lui a3. Same
 * cap family as titproc 1E9C / b5 478 residuals. Default build INCLUDE_ASM. */
#ifdef NON_MATCHING
extern char D_b3_994_v0;
extern char D_b3_994_v1;
extern char D_b3_994_v2;
extern char D_b3_994_v3;
extern char D_b3_994_v4;
void *timproc_uso_b3_func_00000994(int *a0, int a1, int a2, int a3) {
    int *sub;             /* v0-colored node temps (phantom 68) */
    int *n1;              /* cascade 1: colors a2, home 64 */
    int *n2;              /* cascade 2: colors v1, home 60 */
    int *n3;              /* cascade 3: colors a0, home 56 */
    int *vt;              /* vtable temp: colors a1 (phantom 52) */
    int *nd2;             /* reload of nd: a3 via 4th-arg precolor (phantom 48) */
    int * volatile nd;    /* tail node: home 44, spilled from a1 in delay */
    volatile int padA;    /* 40 hole */
    int * volatile slot;  /* home 36 */
    volatile int padB;    /* 32 hole */

    if (a0 == 0) {
        a0 = (int *)gl_func_00000000(0x730);
        if (a0 == 0) return (void *)a0;
    }
    n1 = a0;
    if (n1 == 0) {
        n1 = (int *)gl_func_00000000(0x6A8);
        if (n1 == 0) goto after_n1;
    }
    n2 = n1;
    if (n2 == 0) {
        n2 = (int *)gl_func_00000000(0x50);
        if (n2 == 0) goto after_n2;
    }
    n3 = n2;
    if (n3 == 0) {
        n3 = (int *)gl_func_00000000(0x2C);
        if (n3 == 0) goto after_n3;
    }
    gl_func_00000000(n3, (char *)&D_00000000 + 0x3B8);
    n3[0x28 / 4] = (int)&D_b3_994_v0;
after_n3:
    n2[0x28 / 4] = (int)&D_b3_994_v1;
after_n2:
    n1[0x28 / 4] = (int)&D_b3_994_v2;
    gl_func_00000000((char *)n1 + 0x50);
after_n1:
    a0[0x28 / 4] = (int)&D_b3_994_v3;
    a0[0x568 / 4] = 0;
    gl_func_00000000(a0, a1, (char *)&D_00000000 + 0x3C0, a2);
    a0[0x528 / 4] = a3;
    gl_func_00000000(a0);
    *(float *)&a0[0x72C / 4] = 0.0f;
    gl_func_00000000((char *)&D_00000000 + 0x3D0, 0);
    gl_func_00000000(&D_00000000, 0);
    sub = (int *)gl_func_00000000(0xDC);
    if (sub != 0) {
        sub[0x28 / 4] = (int)&D_b3_994_v4;
    }
    a0[0x6A8 / 4] = (int)sub;
    *(int **)((char *)&D_00000000 + 0x138) = sub;
    if ((a0[0x4F0 / 4] << 15) >= 0) {
        sub[0xB4 / 4] = 0;
    } else {
        sub[0xB4 / 4] = 11;
    }
    gl_func_00000000(a0[0x6A8 / 4], a0, a0[0x568 / 4], a0[0x528 / 4]);
    vt = (int *)((int *)a0[0x6A8 / 4])[0x28 / 4];
    ((void (*)(int))vt[0x5C / 4])(*(short *)((char *)vt + 0x58) + a0[0x6A8 / 4]);
    vt = (int *)a0[0x6A8 / 4];
    gl_func_00000000(slot = (int *)((char *)a0 + 0x10), vt);
    if (((int *)a0[0x6A8 / 4])[0x14 / 4] != 0) {
        ((int *)a0[0x6A8 / 4])[0x4 / 4] = 1;
    }
    ((int *)a0[0x6A8 / 4])[0x14 / 4] = (int)a0;

    if ((a0[0x4F0 / 4] << 15) < 0) {
        sub = (int *)gl_func_00000000(0);
        a0[0x48 / 4] = (int)sub;
        gl_func_00000000(sub, a0);
        *(int *)((char *)a0[0x48 / 4] + 0x30) = a0[0x568 / 4];
        gl_func_00000000(a0[0x48 / 4], (*(int *)&D_00000000 + 3) << 16, -1, &D_00000000);
        gl_func_00000000(a0[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 1, -1, &D_00000000);
        gl_func_00000000(a0[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 4, -1, &D_00000000);
        gl_func_00000000(a0[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 3, -1, &D_00000000);
        gl_func_00000000(a0[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 2, -1, &D_00000000);
        gl_func_00000000(a0[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 5, -1, &D_00000000);
        gl_func_00000000(a0[0x48 / 4]);
        gl_func_00000000(slot, a0[0x48 / 4]);
        if (((int *)a0[0x48 / 4])[0x14 / 4] != 0) {
            ((int *)a0[0x48 / 4])[0x4 / 4] = 1;
        }
        ((int *)a0[0x48 / 4])[0x14 / 4] = (int)a0;
    } else {
        a0[0x4F4 / 4] = a1 & 0xFFFF;
        a0[0x48 / 4] = 0;
    }

    gl_func_00000000(slot, nd = *(int **)((char *)&D_00000000 + 0x190));
    nd2 = nd;
    if (nd2[0x14 / 4] != 0) {
        nd2[0x4 / 4] = 1;
    }
    nd2[0x14 / 4] = (int)a0;
    gl_func_00000000(*(int **)((char *)&D_00000000 + 0x190), 1, 0, nd2);
    gl_func_00000000();
done:
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000994);
#endif

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

/* timproc_uso_b3_func_00000DE4: F1 (19-insn 5-call wrapper) only.
 *
 * The 2026-05-07 SUFFIX_BYTES recipe (absorbing 12 words / 0x30 bytes for
 * F2 + F3) was REMOVED 2026-05-23 as instruction-byte match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Current state: symbol
 * is 0x4C / 19 insns (F1 only); F2 and F3 are tracked as separate
 * symbols. Function lands at fuzzy=100 naturally with just F1's C.
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

/* timproc_uso_b3_func_00000E30: triple-deref non-null check RECOVERED +
 * MATCHED 2026-05-28 from the Yay0 block_3 gap. Returns 1 iff a0->0x6A8->
 * 0x6C is non-null and its 0xEC field is non-zero. KEY: `goto ret0` to a
 * shared `return 0` produces the beql branch-likely idiom (v0=0 in the
 * delay slot) — the plain `if(...)return 0` form emits bnel and grows to
 * 14 insns (the cap that NM'd sibling arcproc_uso_func_00000EEC). */
int timproc_uso_b3_func_00000E30(int *a0) {
    int *p = (int*)((int*)a0[0x6A8 / 4])[0x6C / 4];
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

/* timproc_uso_b3_func_00000E60: state-machine dispatcher, sibling of
 * timproc_uso_b1_func_00000EE8 and arcproc_uso_func_00000FA8.
 *
 * Decoded state 0 and state 1 bodies from the target asm. State 0 walks a
 * 0x30-stride table selected by D[0x64], searching for an entry whose
 * returned [4] matches a0->[0x6AC]. State 1 runs the setup/commit chain and
 * links a0->[0x56C] under the object returned into a0->[0x524].
 *
 * 2026-05-20: NON_MATCHING body reached 95.237625% via objdiff report.
 * Tried plain char* base, register int* base, goto-shaped dispatch, inverted
 * loop branch, and volatile int* base. Volatile base is required to get the
 * target $s3 global-base lifetime and 0x28 stack frame. Remaining no-alias
 * diffs are codegen-level: entry emits bne+b instead of beq+default branch,
 * the state-0 compare still uses bnel, and loop temporaries choose different
 * caller registers around the table stride multiply.
 *
 * 2026-05-21: inverted the state-1 guard to recover the target beq+default
 * dispatch shape (C-only 96.86%). Remaining same-size register/scheduler
 * diffs were closed with INSN_PATCH in Makefile; INSN_PATCH REMOVED
 * 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy — fn rolled back to NM-wrap;
 * NATURAL CEILING 96.86% NM.
 */
#ifdef NON_MATCHING
void timproc_uso_b3_func_00000E60(char *a0) {
    volatile int *base = (int*)&D_00000000;
    char *saved = a0;
    int state = *(int*)(a0 + 0x504);
    char *obj;
    int count;
    int *ret;
    int *created;
    char *link;

    if (state == 0) {
        goto state0;
    }
    if (state != 1) {
        return;
    }
    goto state1;

state0:
        obj = *(char**)(saved + 0x6A8);
        *(int*)(saved + 0x6AC) = *(int*)(*(char**)(obj + 0x44) + 0x14);
        count = *(int*)(*(char**)(obj + 0x44) + 0x3C);
        state = count - 1;
        *(int*)(saved + 0x6B0) = count;
        while (state >= 0) {
            char *table = *(char**)(saved + 0x528);
            ret = (int*)gl_func_00000000(*(char**)table + (base[0x64 / 4] * 0x30), state);
            if (*(int*)(saved + 0x6AC) != ret[1]) {
                goto state0_done;
            }
            *(int*)(saved + 0x6B0) = *(int*)(saved + 0x6B0) - 1;
            state--;
        }
state0_done:
        base = (volatile int*)&D_00000000;
        *(int*)(saved + 0x4D8) = 1;
        gl_func_00000000(base[0x190 / 4], 3, 1);
        *(int*)(saved + 0x504) = 1;
        return;

state1:
        if (gl_func_00000000(base[0x190 / 4]) == 0) {
            return;
        }
        gl_func_00000000(saved);
        gl_func_00000000(base);
        gl_func_00000000(saved);
        gl_func_00000000(saved, base[0x170 / 4] + 0x00220000);
        *(int*)(saved + 0x524) = gl_func_00000000(0, saved, 0);
        gl_func_00000000(*(int*)(saved + 0x524), *(int*)(saved + 0x528));
        created = *(int**)(saved + 0x524);
        link = *(char**)(saved + 0x56C);
        gl_func_00000000(link + 0x10, created);
        if (created[0x14 / 4] != 0) {
            created[1] = 1;
        }
        created[0x14 / 4] = (int)link;
        gl_func_00000000(base[0x190 / 4], 1, 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00000E60);
#endif

/* timproc_uso_b3_func_00000FF4: F1 (32-insn 0x80) gate-then-update wrapper
 * only. The 2026-05-07 SUFFIX_BYTES recipe (absorbing 7 words / 0x1C bytes
 * for the trailing D[0x40]=9 stub at 0x1074 and the 2-word splat-pulled
 * fragment at 0x1088) was REMOVED 2026-05-23 as instruction-byte
 * match-faking. Symbol is now 0x80 / 32 insns (F1 only); the absorbed
 * pieces are tracked as separate symbols. Function lands at fuzzy=100
 * naturally — same pattern as timproc_uso_b3_func_00000DE4 /
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

/* 00001074/00001088: RECOVERED 2026-05-28 from the Yay0 block_3 gap (no .s,
 * missing from build — segment was 7 words short). 00001074: MATCHED —
 * D[0x40]=9 setter with unused-arg save; the global-store-in-delay-slot
 * vs arg-save order matches in-tree (standalone diverged, see
 * MATCHING_WORKFLOW.md#feedback-standalone-false-convergence-verify-in-tree).
 * 00001088: 2-insn alt-entry that loads a1 and falls through into 00001090.
 * SOURCE=4 audit 2026-06-01: not an accessor-template miss. This mirrors
 * timproc_uso_b1_func_000010D4: the fragment seeds $a1 from D[0x170], while
 * the successor's C body consumes that inherited $a1 before adding 0x220000.
 * Keep INCLUDE_ASM; there is no standalone C body for the preload fragment. */
void timproc_uso_b3_func_00001074(int a0) {
    *(int*)((char*)&D_00000000 + 0x40) = 9;
}
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001088);

void timproc_uso_b3_func_00000000();

void timproc_uso_b3_func_00001090(int a0, char *a1) {
    timproc_uso_b3_func_00000000(a0, a1 + 0x00220000);
}

extern int gl_ref_00000040;
extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b3_func_000010B4(int a0) {
    *(int *)((char *)&D_00000000 + 0x40) = 9;
    gl_func_00000000(a0, -1, 0);
}

/* Vtable-entry dispatcher (twin of timproc_uso_b1_func_00001130). Pass 2 2026-06-10:
 * re-decode fixed the OLD body's structure -- the *40 is a real multu
 * with the stride in a register (variable stride; old body's shift
 * decomposition was wrong), the gl(5) arg loads EARLY into a0 before
 * the beqzl, and the if(1){} BB-split after the call is load-bearing
 * (the 4-for-4 v0/v1 lever). 29/40 -> 11 word-diffs remaining: stride
 * colors a2 vs target a0 (the 5-then-40 single-web trick did not take;
 * k still splits), and the fn-temp renumber downstream of it.
 * 2026-06-10 pseudo-order family sweep NEGATIVE: early-pseudo (stride
 * dead-initialized / pre-declared first) and decl reorders all leave
 * stride in a2. The residual is ARG-REGISTER coloring of a non-arg
 * value (a0 freed after the jal consumed the 5); none of the three
 * pseudo-order levers (BB-split / web-inversion / early-pseudo)
 * address arg-reg targeting. Remaining lever: uoptlist dump. */
/* EXACT (2026-06-21, ported from byte-identical twin timproc_uso_b1_func_00001130).
 * The single residual addu operand-order diff (target `addu rd,base,prod` vs the
 * inline-web's `addu rd,prod,base`) is resolved by two scheduler/coloring nudges:
 *   - `self[(0x48 / 4) ^ 0]` (identity XOR) re-orders the index web so the final
 *     addr addu emits base-rs while preserving the $t9 coalesce, and
 *   - `(new_var = 0x90)` parks the +0x90 offset in a throwaway local, fixing the
 *     temp-numbering of the call register.
 * Both are semantic no-ops; verified in-tree (0 non-reloc word diffs). */
extern int D_arg_b3_10E4[];
extern int D_cur_b3_10E4;
void timproc_uso_b3_func_000010E4(int *self) {
  int *v0;
  int new_var;
  int v1;
  int stride;
  if (gl_func_00000000(D_arg_b3_10E4[0x190 / 4]) == 0) {
    return;
  }
  v0 = (int *) self[0x48 / 4];
  v1 = v0[0x7C / 4];
  if (v1 != 0) {
    gl_func_00000000(5);
    if (1) {
    }
    v0 = (int *) self[0x48 / 4];
    v1 = v0[0x7C / 4];
  }
  stride = 40;
  if (((void (*)(void)) (*((int *) ((((char *) v0) + (v1 * stride)) + 0x90)))) != 0) {
    D_cur_b3_10E4 = (int) self;
    if (1) {
    }
    v0 = (int *) self[(0x48 / 4) ^ 0];
    (*((void (**)(void)) ((((char *) v0) + (v0[0x7C / 4] * stride)) + (new_var = 0x90))))();
  }
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

/* timproc_uso_b3_func_00001240: 94-insn FP accumulator/dispatch helper.
 * b3 variant of timproc_uso_b1_func_000011D8. Boundary-checked: one jr ra.
 *
 * Structure:
 *   if (a0->0x500 == 0) return;
 *   if (*(float*)&D > 0.0f) return;
 *   if (a0->0x72C < D[0x40]) a0->0x72C += D[0x44];
 *   a0->0x508++;
 *   armed = (a0->0x528->0x14 & 2) && a0->0x4FC &&
 *           D[0x138]->0x44->0x3C < 3;
 *   if (armed) {
 *     gl_func(&D, (int)(255.0f * a0->0x72C), a0+0x2F0, a0+0x314);
 *     saved = a0+0x6E4; gl_func(saved);
 *     if (a0->0x508 & 8) {
 *       gl_func(saved, 160, 160, 3);
 *       gl_func(a0, 140, a0->0x6A8->0x44->0x14);
 *     }
 *   } else {
 *     gl_func(a0, 140, a0->0x6A8->0x44->0x14);
 *   }
 *
 * NATURAL CEILING: NM only. Was previously documented as "Exact via
 * targeted INSN_PATCH for IDO register/scheduling deltas: D-reloc offsets
 * on unique externs, mtc1/lwc1 order, saved stack slot offset, and the
 * final nested pointer temp registers" — INSN_PATCH REMOVED 2026-05-23
 * as match-faking (per feedback_no_instruction_forcing_matches_policy).
 * Unique-extern split (D_b3_1240_*) is retained to keep the structural
 * decode honest in the NM body. Default build is INCLUDE_ASM. */
extern char D_b3_1240_base;
extern float D_b3_1240_f0;
extern float D_b3_1240_f40;
extern float D_b3_1240_f44;
extern char *D_b3_1240_ptr138;
/* timproc_uso_b3_func_00001240 — IMPROVED 2026-07-03: 81/94 -> 92/94 raw words.
 *
 * REQUIRES undefined_syms_auto.txt edits (distinct base-alias, value 0x0):
 *   D_b3_1240_f40    = 0x00000000;   (was 0x00000040)
 *   D_b3_1240_f44    = 0x00000000;   (was 0x00000044)
 *   D_b3_1240_ptr138 = 0x00000000;   (was 0x00000138)
 * The offset is now baked in the load instruction as an addend (struct-cast-fold)
 * so the raw .o word carries offset 0x40/0x44/0x138 with a reloc to the base
 * (matches target C4280040/C42A0044/8D6B0138). Keeping them as DISTINCT symbols
 * (rather than a single &D_base) is required to defeat IDO's lui-CSE — the target
 * re-lui's the base per read; a shared symbol drops 3 luis and shifts everything.
 *
 * Fixes applied (all legitimate C, verified in-tree word-diff):
 *   1. f40/f44/ptr138: struct-cast base+offset fold (idx 22/28/44).
 *   2. ptr-temp chain FULLY INLINED (no named `tmp` local) -> target's distinct
 *      t9->t0 register chain instead of v0-reuse (idx 75/78/80/83/86/88).
 *   3. Removing the now-unused `char *tmp` local fixes the a0-spill slot
 *      0x20 -> 0x24 (named-local-count frame rule) (idx 66/68).
 *
 * RESIDUAL CAP (2 words, idx 53/54): the `255.0f * x` multiply schedules
 * lwc1(x)-then-mtc1(const) into f18/f4 vs target's mtc1(const)-then-lwc1(x).
 * Same-register scheduler swap ("mtc1/lwc1 order"). Tried preload-x-local,
 * const-float-local, double-const, operand swap — all regress. IDO scheduler
 * cap; was formerly the INSN_PATCH item. 92/94 is the natural NM ceiling.
 */
#ifdef NON_MATCHING
void timproc_uso_b3_func_00001240(char *a0) {
    float color[4];
    char pad[32];
    char *saved;
    int armed;

    color[0] = 1.0f;
    color[1] = 1.0f;
    color[2] = 1.0f;
    color[3] = 1.0f;
    (void)color;
    (void)pad;

    if (*(int*)(a0 + 0x500) != 0) {
        if (D_b3_1240_f0 <= 0.0f) {
            if (*(float*)(a0 + 0x72C) < *(float*)((char*)&D_b3_1240_f40 + 0x40)) {
                *(float*)(a0 + 0x72C) += *(float*)((char*)&D_b3_1240_f44 + 0x44);
            }

            *(int*)(a0 + 0x508) = *(int*)(a0 + 0x508) + 1;
            armed = 0;
            if ((*(int*)(*(char**)(a0 + 0x528) + 0x14) & 2) != 0 &&
                *(int*)(a0 + 0x4FC) != 0 &&
                *(int*)(*(char**)(*(char**)((char*)&D_b3_1240_ptr138 + 0x138) + 0x44) + 0x3C) < 3) {
                armed = 1;
            }

            if (armed != 0) {
                gl_func_00000000(&D_b3_1240_base,
                                 (int)(255.0f * *(float*)(a0 + 0x72C)),
                                 a0 + 0x2F0,
                                 a0 + 0x314);
                saved = a0 + 0x6E4;
                gl_func_00000000(saved);
                if ((*(int*)(a0 + 0x508) & 8) != 0) {
                    gl_func_00000000(saved, 0xA0, 0xA0, 3);
                    gl_func_00000000(a0, 0x8C, *(int*)(*(char**)(*(char**)(a0 + 0x6A8) + 0x44) + 0x14));
                }
            } else {
                gl_func_00000000(a0, 0x8C, *(int*)(*(char**)(*(char**)(a0 + 0x6A8) + 0x44) + 0x14));
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001240);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef int (*GP_000013B8)();
void timproc_uso_b3_func_000013B8(char *arg0, s32 arg1, f32 *arg2) {
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
    if (FW(FW(arg0, 0x528), 0x14) & 2) {
        timproc_uso_b3_func_000000B0(0, (s32) (255.0f * FW(arg0, 0x72C)), (int)arg0 + 0x2A8, (int)arg0 + 0x2CC);
        temp_s7 = (int)arg0 + 0x714;
        timproc_uso_b3_func_000000B0(temp_s7);
        temp_s1 = (int)arg0 + 0x6CC;
        temp_s5 = (s16) FW(FW(arg0, 0x724), 0x20) / 12;
        timproc_uso_b3_func_000000B0(temp_s1);
        temp_s2 = (int)arg0 + 0x6B4;
        timproc_uso_b3_func_000000B0(temp_s2);
        temp_s0 = (int)arg0 + 0x6FC;
        timproc_uso_b3_func_000000B0(temp_s0);
        timproc_uso_b3_func_000000B0(&spB8, 0x3D8, arg2);
        sp64 = temp_s1;
        sp60 = temp_s2;
        temp_v0 = timproc_uso_b3_func_000000B0(&spB8);
        temp_t3 = FW(arg0, 0x70C);
        temp_t1 = FW(arg0, 0x6DC);
        temp_t2 = FW(arg0, 0x6C4);
        temp_a2 = (int)arg1 + 0x32;
        temp_s1_2 = 0xA0 - ((s32) (FW(temp_t3, 0x20) + (temp_v0 * 0xD) + FW(temp_t1, 0x20) + FW(temp_t2, 0x20) + 0x10) / 2);
        temp_s2_2 = FW(temp_t2, 0x20) + temp_s1_2 + 4;
        temp_a1 = FW(temp_t1, 0x20) + temp_s2_2 + 4;
        sp88 = FW(temp_t3, 0x20) + temp_a1 + 8;
        sp90 = temp_s2_2;
        sp94 = temp_s1_2;
        sp58 = temp_a2;
        timproc_uso_b3_func_000000B0(temp_s0, temp_a1, temp_a2, (char *)2);
        var_s0 = &spB8;
        if (temp_v0 > 0) {
            var_s1 = 0;
            var_s2 = sp88;
            do {
                *var_s0 -= 0x30;
                timproc_uso_b3_func_000000B0(temp_s7, var_s2, (arg1 - ((s16) FW(FW(arg0, 0x724), 0x22) / 2)) + 0x32, (char *) (*(int*)var_s0 * temp_s5), temp_s5);
                var_s1 += 0xD;
                var_s0 += 1;
                var_s2 += 0xD;
            } while (var_s1 != (temp_v0 * 0xD));
        }
        timproc_uso_b3_func_000000B0(0, (s32) (255.0f * FW(arg0, 0x72C)), &sp138);
        timproc_uso_b3_func_000000B0(sp64, sp90, sp58, (char *)2);
        timproc_uso_b3_func_000000B0(sp60, sp94, sp58, (char *)2);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000013B8);
#endif

/* timproc_uso_b3_func_00001660 — EXACT (90/90 words incl. relocs, 2026-07-09).
 * Twin of arcproc_uso_func_0000199C (same 4-level alloc-cascade ctor
 * template; deltas: init-call base +0x3dc, a1 float @+0x72c,
 * packed-id ptr field @+0x6b0). Crack lever: the packed-id call's id
 * chain must be ucode-created before the ptr chain — spell the ptr chain
 * as a two-level typed member chain ((Tim1660_A *)arg0)->b->v (cfe then
 * follows textual order). Siblings: arcproc 199C, timproc_b1 16F8, mgrproc 2940. */
extern int gl_func_00000000();
extern char D_tim1660_v[];   /* init-call a1 base (&sym+0x3dc) */
extern char D_tim1660_w[];   /* a0->0x28 (level-4) */
extern char D_tim1660_x[];   /* v1->0x28 (level-3) */
extern char D_tim1660_y[];   /* a2->0x28 (level-2) */
extern char D_tim1660_z[];   /* s0->0x28 (level-1/main) */
extern int D_tim1660_id;     /* packed-id value read */

typedef struct Tim1660_B { char pad[0x6b0]; int v; } Tim1660_B;
typedef struct Tim1660_A { char p0[0xD4]; Tim1660_B *b; } Tim1660_A;

char *timproc_uso_b3_func_00001660(char *arg0, char *arg1, int arg2) {
    char *a2;   /* level-2 (0xD4), home 0x2C(sp) */
    char *v1;   /* level-3 (0x50), home 0x28(sp) */
    char *a0;   /* level-4 (0x2C), home 0x24(sp) */

    if ((arg0 != 0) || (arg0 = (char *)gl_func_00000000(0x10C), (arg0 != 0))) {
        a2 = arg0;
        if ((arg0 != 0) || (a2 = (char *)gl_func_00000000(0xD4), (a2 != 0))) {
            v1 = a2;
            if ((a2 != 0) || (v1 = (char *)gl_func_00000000(0x50), (v1 != 0))) {
                a0 = v1;
                if ((v1 != 0) || (a0 = (char *)gl_func_00000000(0x2C), (a0 != 0))) {
                    gl_func_00000000(a0, D_tim1660_v + 0x3dc); *(char **)(a0 + 0x28) = D_tim1660_w;
                }
                *(char **)(v1 + 0x28) = D_tim1660_x;
            }
            *(char **)(a2 + 0x28) = D_tim1660_y;
        }
        *(char **)(arg0 + 0x28) = D_tim1660_z;
        *(int *)(arg0 + 0x60) = arg2;
        *(char **)(arg0 + 0xD4) = arg1;
        *(int *)(arg0 + 0xE0) = 0xA0;
        *(int *)(arg0 + 0xE4) = 0x1D;
        *(int *)(arg0 + 0xD8) = 0xA0;
        *(int *)(arg0 + 0xDC) = 0x82;
        *(int *)(arg0 + 0xE8) = 0xA0;
        *(int *)(arg0 + 0xEC) = 0x69;
        *(float *)(arg0 + 0x108) = 1.0f;
        *(float *)(arg1 + 0x72c) = 1.0f;
        gl_func_00000000(arg0 + 0xF0,
            ((D_tim1660_id + 0x23) << 16) | (((Tim1660_A *)arg0)->b->v + 7));
    }
    return arg0;
}

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

/* Decay-tick handler: decrement sub->f_72C by the global rate (D+0x48),
 * clamp at 0, fire the 140-event mid-call, and on reaching <= 0 fire
 * the threshold call. MATCHED 2026-06-10 (44/44): the old wrap had a
 * DECODE ERROR (the mid-call's arg0 is SUB, not self) and a misplaced
 * sub-reload (only the clamp-taken path reloads); the final read goes
 * through the inlined full chain (fresh temp t6) rather than the sub
 * variable (whose web would color a0). bc1fl delay structure falls out
 * naturally from the val-carried if/if shape. */
void timproc_uso_b3_func_00001870(int *self) {
    char *base = &D_00000000;
    int *sub;
    float *fp;
    float val;

    gl_func_00000000(self);
    sub = (int *)self[0xD4 / 4];
    fp = (float *)((char *)sub + 0x72C);
    val = *fp;
    if (val > 0.0f) {
        *fp -= *(float *)(base + 0x48);
        sub = (int *)self[0xD4 / 4];
        if (*(float *)((char *)sub + 0x72C) < 0.0f) {
            *(float *)((char *)sub + 0x72C) = 0.0f;
            sub = (int *)self[0xD4 / 4];
        }
        gl_func_00000000(sub, 140, *(int *)((char *)sub + 0x6AC));
        val = *(float *)((char *)(int *)self[0xD4 / 4] + 0x72C);
    }
    if (val <= 0.0f) {
        gl_func_00000000(self);
    }
}


/* 2026-06-10 (via the b1 twin 19C0 re-test): the incoming-$f0 quad-
 * store cap STANDS -- uninit `float g; buf[i]=g` and `register float g`
 * both emit lwc1-from-home first; the store-only $f0 x4 form is
 * C-unreachable. See docs/IDO_CODEGEN uninit-register-float addendum. */
/* timproc_uso_b3_func_00001920: 2-insn alt-entry (set f0=1.0f, falls into
 * 00001928). RECOVERED 2026-05-28 from the Yay0 block_3 gap. SOURCE=4 audit
 * 2026-06-01: not an accessor-template miss; this mirrors
 * timproc_uso_b1_func_000011D0's float-constant preload. INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001920);

#ifdef NON_MATCHING
/* timproc_uso_b3_func_00001928: byte-identical mirror of
 * arcproc_uso_func_00001C74 (sig=739fd8d1d3, 41-insn 0xA4 counter+
 * conditional-scale wrapper).
 *
 * Per scripts/find-byte-identical-clones.py — see arcproc_uso_func_00001C74's
 * wrap for canonical decode. Mirrored source=4 2026-06-01.
 * NOTE CORRECTED 2026-07-15: the "alt-entry" func_00001920 above is NOT an
 * entry — it is 1928's own hoisted 1.0f const materialization (stolen
 * prologue; buf[] = 1.0f, not 0.0f). 1C74 canonical recipe reproduces
 * 41/43 true bytes; residual = version-independent FP pair-swap. See
 * arcproc 1C74's wrap + docs/IDO_CODEGEN FP-const-hoist entry. */
void timproc_uso_b3_func_00001928(int *a0) {
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
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001928);
#endif

/* timproc_uso_b3_func_000019CC 2026-07-15 (agent-g wave 3): 94.04 -> 99.81.
 * Levers: (1) sp44-call arg swapped to (D_64*0x30) + *(*arg3) (right-first +
 * eval numbers the ptr chain t0/t1 like target); (2) 0x18 RMW respelled as
 * single-mutated pointer q with if(1){} advance (B850/C044 idiom: lw 24(a2),
 * addiu a2,a2,24, sw 0(a2)) and the fp block as a second q mutation (+0x64);
 * both de-named loads keep ring temps; (3) the final registration call is
 * 3-ARG with q (= sub+0x64) as arg 3 -- constrains the whole q web to $a2
 * with ZERO emission (target a2 = leftover q, K&R); a plain 2-arg drop left
 * q in $v1; (4) frame 64->80 + slot map via decl order o,sub,sp44,q +
 * volatile pad1..pad4 AFTER the named ptrs (pads claim 44-56; o-spill 76,
 * v0-spill 68 exact). RESIDUAL ~10 words: a0-spill slot 40 vs 44 (one rank
 * below the outgoing-arg spill unreachable by pads: E6E8 compiler-spill
 * class), sub-spill 72 vs 76 (target SHARES o's slot -- name-merge injects
 * an or-copy at link-1 instead), tail link-block reload $v1 vs $a2
 * (free-pick tie, if(1)/merge probed). NON_MATCHING. */
#ifdef NON_MATCHING
extern int gl_proto_19cc(void *, int, int, float, float);
extern char D_b3_19CC_0C;
void timproc_uso_b3_func_000019CC(char *arg0, char *arg1, int arg2, int *arg3) {
    char *o;
    char *sub;
    char *sp44;
    char *q;
    volatile int pad1;
    volatile int pad2;
    volatile int pad3;
    volatile int pad4;
    float denom = 255.0f;

    *(int *)(arg0 + 0xC) = (int)(&D_b3_19CC_0C + 0x3E4);
    *(char **)(arg0 + 0xB8) = arg1;
    *(char **)(arg0 + 0x50) = arg1;
    *(int **)(arg0 + 0x4C) = arg3;
    *(int *)(arg0 + 0xAC) = 0;
    if (*(int *)(arg1 + 0x4F0) & 0x10000) {
        *(int *)(arg0 + 0x54) = arg2;
        *(int *)(arg0 + 0xD0) = 0xFF;
        *(int *)(arg0 + 0xD4) = 0;
        *(float *)(arg0 + 0xCC) = 1.0f;
        *(float *)(arg0 + 0xC8) = 1.0f;
        *(float *)(arg0 + 0xC4) = 1.0f;
        *(float *)(arg0 + 0xC0) = 1.0f;
        gl_func_00000000();
        gl_func_00000000(arg0, 0xE8, 0x13, *(int *)(arg0 + 0x44) + 0x10);
        gl_func_00000000(arg0, 0x69, 0x11, arg0 + 0xA0);
        gl_func_00000000(arg0, 0x123, 0xE1, 1);
        gl_func_00000000(arg0, 0x21, 0x13, arg0 + 0xA8);
        gl_func_00000000(*(int *)(arg0 + 0x8C), 0);
        sp44 = (char *)gl_func_00000000((*(int *)((char *)&D_00000000 + 0x64) * 0x30) + *(int *)(*(int **)(arg0 + 0x4C)), 0);
        o = (char *)gl_func_00000000(0, *(int *)(arg0 + 0x60));
        *(char **)(arg0 + 0xBC) = o;
        gl_func_00000000(o, *(int *)(sp44 + 4));
        gl_func_00000000(*(char **)(arg0 + 0xBC), 0x35, 0xD6);
        o = *(char **)(arg0 + 0xBC);
        gl_func_00000000(arg0 + 0x10, o);
        if (*(int *)(o + 0x14) != 0) {
            *(int *)(o + 4) = 1;
        }
        *(char **)(o + 0x14) = arg0;
        sub = (char *)gl_func_00000000(0, *(int *)(arg0 + 0x58), o);
        *(char **)(arg0 + 0x94) = sub;
        gl_func_00000000(sub, 0);
        gl_proto_19cc(*(char **)(arg0 + 0x94), 0xA0, 0x46, 1.0f, 1.0f);
        {
            q = *(char **)(arg0 + 0x94);
            if (1) { q = q + 0x18; }
            *(int *)q = *(int *)q & ~4;
            q = *(char **)(arg0 + 0x94);
            if (1) { q = q + 0x64; }
            ((float *)q)[0] = 250.0f / denom;
            ((float *)q)[1] = 235.0f / denom;
            ((float *)q)[2] = 100.0f / denom;
            ((float *)q)[3] = 0.0f / denom;
        }
        *(int *)(*(char **)(arg0 + 0x94) + 0xA0) = *(int *)(arg0 + 0x6C) + 0x108;
        *(int *)(*(char **)(arg0 + 0x94) + 0x80) = 0;
        *(int *)(*(char **)(arg0 + 0x94) + 0x84) = -0x12;
        o = *(char **)(arg0 + 0x94);
        sub = *(char **)(arg0 + 0x94);
        gl_func_00000000(arg0 + 0x10, sub, q);
        if (1) {
            if (*(int *)(sub + 0x14) != 0) {
                *(int *)(sub + 4) = 1;
            }
            *(char **)(sub + 0x14) = arg0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000019CC);
#endif

/* timproc_uso_b3_func_00001C20: orphan-merge of a stolen-prologue. The orphan
 * timproc_uso_b3_func_00001C20 (lui t6; lw t6,0x64(t6) = TIMB3_D_64) was the
 * stolen prologue of func_00001C28 — it loads the global compared to 1 at the
 * top. Merged FORWARD (one 0x48 symbol; successor .s deleted, no jal targets).
 * Reading TIMB3_D_64 inline at the `== 1` test hoists the lui;lw above the
 * prologue (same recipe as game_libs_func_00026B40). Also fixed the old decode:
 * a0->0xD8 = 1 (the SAME literal 1 IDO materializes for the `== 1` test, in v0,
 * stored in the jal delay slot — NOT the call return). MATCHED 2026-05-30. */
void timproc_uso_b3_func_00001C20(char *a0) {
    if (*(int*)((char*)&D_00000000 + 0x64) == 1) {
        *(int*)(a0 + 0xA0) = 50000;
    } else {
        *(int*)(a0 + 0xA0) = 30000;
    }
    *(int*)(a0 + 0xA8) = 0;
    *(int*)(a0 + 0xD8) = 1;
    gl_func_00000000();
}

#ifdef NON_MATCHING
/* timproc_uso_b3_func_00001C68: UI animation/draw orchestrator (sibling of
 * arcproc_uso_func_00001F54 / mgrproc per-frame steps). cb(); gate arg0->0xB8
 * bit-16 && ->0x4DC==1: bump 0x30, decrement 0xA0 by 0x21 (floor 0 + cleanup that
 * sets sub->0x554=192.0f, ->0x544=0xFF). cb(arg0). Gated block: state-2 sync of
 * 0xD8; optional draw block; ramp 0xA8 toward 0x44->0x18 by 0xFA/0x32/0x19/1;
 * state-1 draws (float arg via gl_proto_1c68); 0x94 sub-widget enable + 0x32/5/1
 * ramp on 0x44->0x20 else disable; state-2 (0x4F8==0) blink 0x8C by (0xAC++ & 8).
 *
 * 2026-07-10 95.09% fuzzy (was 84.02; 251/253 words). Levers (agent-h):
 *  - NO bc local: direct *(char **)(arg0+0xB8) derefs everywhere; the load-CSE
 *    web (one char** ichain) then carries the a0 precolor from the two
 *    gl_func(*(arg0+0xB8)) call args (cupcosts lu->reg discount) -> bc web
 *    colors a0 like target, both gates + post-call rereads + arm-4 join.
 *  - v0b ramp arm loads are INT-typed (*(int *)(arg0+0xB8)): different ichain
 *    from the char** web -> no CSE with the held a0 pointer, forcing the
 *    per-arm fresh t-reg reloads the target shows. Arm 4 (join) stays char**
 *    (it IS an a0-web reload in target).
 *  - 0xA0/0xAC RMWs in compound deref form (no t2/t1 temp locals) =
 *    un-coalesced two-reg lw/addiu/sw shape.
 *  - flag RMWs (p94/p8c +0x18, p44 +0x20 arms 1-2) via held ptr assigned from
 *    the DIRECT deref chain: fl=(int *)(*(char **)(arg0+0x94)+0x18); *fl|=4;
 *    gives the target addiu+lw/sw-0(v0) form (a p94-local base folds to
 *    24(reg) instead). Arm 3 (+1) is the FOLDED 32(v1) form in target - spell
 *    it as a plain compound deref.
 * RESIDUAL (~15 words, one family): as1/uopt adjacent-pair picks - (a) the
 * conditional gl(arg0,1) call hoists addiu a1,1 into the cond load-delay slot
 * where target hoists or a0,s0 (probe-immune: casts/1u/arg-splits inert);
 * (b) arm-1's fl addiu is como-hoisted above the bnel (single-path uadd still
 * hoists; fl2-split/cast probes inert) which steals v0, knocking r->a0 and
 * a1-var->a2+copy (target r->v0, a1-var->a1); (c) one addiu-vs-or zero-arg
 * materialization at the state-1 draw call (0u probe inert). Same
 * allocator/scheduler-internal class as the Two-s-reg kit II residuals. */
extern int gl_proto_1c68(void *, int, int, float, float);
void timproc_uso_b3_func_00001C68(char *arg0) {
    int *fl;
    int v0;
    int v0b;
    register int a1;
    int rem;
    int r;
    int t1;

    gl_func_00000000();
    if ((*(int *)(*(char **)(arg0 + 0xB8) + 0x4F0) & 0x10000) && (*(int *)(*(char **)(arg0 + 0xB8) + 0x4DC) == 1)) {
        *(int *)(arg0 + 0x30) = *(int *)(arg0 + 0x30) + 0x21;
        gl_func_00000000(arg0);
        *(int *)(arg0 + 0xA0) = *(int *)(arg0 + 0xA0) - 0x21;
        if (*(int *)(arg0 + 0xA0) < 0) {
            *(int *)(arg0 + 0xA0) = 0;
            gl_func_00000000(*(int *)(arg0 + 0x84), 0, 0);
            gl_func_00000000(*(char **)(arg0 + 0xB8));
            *(float *)(*(char **)(arg0 + 0xB8) + 0x554) = 192.0f;
            *(int *)(*(char **)(arg0 + 0xB8) + 0x544) = 0xFF;
            *(int *)(arg0 + 0x2C) = 0;
        }
    }
    gl_func_00000000(arg0);
    v0 = *(int *)(*(char **)(arg0 + 0xB8) + 0x4F0) & 0x10000;
    if ((v0 != 0) && (*(int *)(*(char **)(arg0 + 0xB8) + 0x4DC) == 1)) {
        if (*(int *)(arg0 + 0x48) == 2) {
            if ((*(int *)(arg0 + 0xD8) == 1) &&
                (*(int *)(*(char **)(*(char **)(*(char **)(arg0 + 0x44) + 0x60) + 0x800) + 0x4C) == 0)) {
                gl_func_00000000(arg0, 1);
            }
            *(int *)(arg0 + 0xD8) = *(int *)(*(char **)(*(char **)(*(char **)(arg0 + 0x44) + 0x60) + 0x800) + 0x4C);
            v0 = *(int *)(*(char **)(arg0 + 0xB8) + 0x4F0) & 0x10000;
        }
        if (*(int *)(*(char **)(arg0 + 0x44) + 0x34) != 0) {
            if (v0 != 0) {
                gl_func_00000000(arg0);
                gl_func_00000000(arg0, *(int *)(arg0 + 0xA0));
                gl_func_00000000(*(int *)(arg0 + 0x84), *(int *)(arg0 + 0xA0), 0);
            }
            gl_func_00000000(*(char **)(arg0 + 0xB8));
            v0 = *(int *)(*(char **)(arg0 + 0xB8) + 0x4F0) & 0x10000;
        }
    }
    if (v0 != 0) {
        t1 = *(int *)(arg0 + 0xA8);
        rem = *(int *)(*(char **)(arg0 + 0x44) + 0x18) - t1;
        if (rem >= 0xFA) {
            *(int *)(arg0 + 0xA8) = t1 + 0xFA;
            v0b = *(int *)(*(int *)(arg0 + 0xB8) + 0x4DC);
        } else if (rem >= 0x32) {
            *(int *)(arg0 + 0xA8) = t1 + 0x32;
            v0b = *(int *)(*(int *)(arg0 + 0xB8) + 0x4DC);
        } else if (rem >= 0x19) {
            *(int *)(arg0 + 0xA8) = t1 + 0x19;
            v0b = *(int *)(*(int *)(arg0 + 0xB8) + 0x4DC);
        } else {
            if (rem > 0) {
                *(int *)(arg0 + 0xA8) = t1 + 1;
            }
            v0b = *(int *)(*(char **)(arg0 + 0xB8) + 0x4DC);
        }
        if (v0b == 1) {
            gl_func_00000000(*(int *)(arg0 + 0x84), *(int *)(arg0 + 0xA0), 1);
            gl_func_00000000(*(int *)(arg0 + 0x80), *(int *)(*(char **)(arg0 + 0x44) + 0x30), 0);
            gl_proto_1c68(*(int *)(arg0 + 0x80), *(int *)(*(char **)(arg0 + 0x44) + 8), *(int *)(*(char **)(arg0 + 0x44) + 0xC), 0.0f, 0.0f);
        }
        if (*(int *)(*(char **)(arg0 + 0x44) + 0x1C) != 0) {
            gl_proto_1c68(*(int *)(arg0 + 0x94), 0xA0, 0x46, 1.0f, 1.0f);
            *(int *)(*(char **)(arg0 + 0x94) + 0x78) = 0xFF;
            fl = (int *)(*(char **)(arg0 + 0x94) + 0x18);
            *fl = *fl | 4;
            a1 = *(int *)(*(char **)(arg0 + 0x44) + 0x20);
            r = *(int *)(*(char **)(arg0 + 0x44) + 0x1C) - a1;
            if (r >= 0x32) {
                fl = (int *)(*(char **)(arg0 + 0x44) + 0x20);
                *fl = *fl + 0x32;
                gl_func_00000000(0x20, 0x32);
                a1 = *(int *)(*(char **)(arg0 + 0x44) + 0x20);
            } else if (r >= 5) {
                fl = (int *)(*(char **)(arg0 + 0x44) + 0x20);
                *fl = *fl + 5;
                gl_func_00000000(0x20, 5);
                a1 = *(int *)(*(char **)(arg0 + 0x44) + 0x20);
            } else if (r > 0) {
                *(int *)(*(char **)(arg0 + 0x44) + 0x20) = *(int *)(*(char **)(arg0 + 0x44) + 0x20) + 1;
                gl_func_00000000(0x20, 1);
                a1 = *(int *)(*(char **)(arg0 + 0x44) + 0x20);
            }
            gl_func_00000000(*(int *)(arg0 + 0x94), a1);
        } else {
            fl = (int *)(*(char **)(arg0 + 0x94) + 0x18);
            *fl = *fl & ~4;
        }
        if ((*(int *)(*(char **)(arg0 + 0xB8) + 0x4DC) == 2) && (*(int *)(*(char **)(arg0 + 0xB8) + 0x4F8) == 0)) {
            *(int *)(arg0 + 0xAC) = *(int *)(arg0 + 0xAC) + 1;
            if (*(int *)(arg0 + 0xAC) & 8) {
                fl = (int *)(*(char **)(arg0 + 0x8C) + 0x18);
                *fl = *fl & ~4;
            } else {
                fl = (int *)(*(char **)(arg0 + 0x8C) + 0x18);
                *fl = *fl | 4;
            }
        }
    }
    gl_func_00000000(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00001C68);
#endif

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

/* timproc_uso_b3_func_000020EC: 36-insn (0x90) constructor — BYTE-IDENTICAL
 * mirror of eddproc_uso_func_000003BC family (5th clone). Apply the
 * eddproc lever (volatile-ptr-to-arg + late head reload) per
 * docs/IDO_CODEGEN.md#feedback-ido-arg-addr-via-volatile-ptr-forces-caller-spill.
 * Expected to land in the 89% file-context band per
 * docs/IDO_CODEGEN.md#feedback-ido-file-context-affects-frame-size
 * (timproc_uso_b3.c is a large multi-function file). */
void *timproc_uso_b3_func_000020EC(int *arg0) {
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

/* timproc_uso_b3_func_0000217C: 2-call wrapper. UN-MATCHED 2026-06-10
 * to FIX BLOCK3 (the 1-word-pad placeholder mechanism, solved in
 * MATCHING_WORKFLOW): a 1-word pad sidecar cannot emit correctly (the
 * minimum C placeholder is 8 bytes, +4 shifting the whole block since
 * April). The fn+pad now emit as ONE 13-word GLOBAL_ASM (exact); the
 * proven matching C is preserved below for the day a tools-side
 * placeholder-shrink patch lands. */
#ifdef NON_MATCHING
void timproc_uso_b3_func_0000217C(char *dst) {
    int tmp;
    timproc_uso_b3_func_00000854(&tmp);
    timproc_uso_b3_func_00000924((Vec3*)(dst + 0x10));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3/timproc_uso_b3_func_0000217C.s")
#endif

void timproc_uso_b3_func_000021B0(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 4;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

/* func_000021F4 (0x44): byte-identical twin of timproc_uso_b1_func_000020AC
 * (matched) except the state constant (li 6 vs li 1). Ported donor body w/
 * gl_ref_00000040 = 6. */
void timproc_uso_b3_func_000021F4(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 6;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

/* vram 0x2238: 2-word stolen-prologue orphan (lui $a0,%hi; lw $a0,0x148($a0)
 * ahead of func_00002240's prologue; twin of b1's 0x2028 orphan).
 * Standalone 2-word GLOBAL_ASM emits exactly. */
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3/timproc_uso_b3_orphan_00002238.s")

/* Dual-branch state setter, twin of timproc_uso_b1_func_00002030.
 * MATCHED 2026-06-10 (31/31) -- see the b1 twin for the full story:
 * first call arg = PARAM+4 (old decode error), one shared +0x208 call
 * target, volatile pointer-fetch cur (+0x20C), and the if(1){} BB-split
 * in each arm (v0/v1 lever). */
extern int D_call_b3_2240_a;
extern int * volatile D_cur_b3_2240;
void timproc_uso_b3_func_00002240(char *a0) {
    if (gl_func_00000000(a0 + 4) != 0) {
        gl_func_00000000(D_call_b3_2240_a);
        if (1) {}
        D_cur_b3_2240[0x14] = 2;
        D_cur_b3_2240[0x16] = 1;
    } else {
        gl_func_00000000(D_call_b3_2240_a);
        if (1) {}
        D_cur_b3_2240[0x14] = 1;
        D_cur_b3_2240[0x16] = 1;
    }
}

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

/* 000023CC/23D4/23DC: 3 empty stubs RECOVERED 2026-05-28 from the Yay0 gap
 * (no .s, missing from build; bytes from block_3). void f(void){} -> jr ra;nop. */
void timproc_uso_b3_func_000023CC(void) {}
void timproc_uso_b3_func_000023D4(void) {}
void timproc_uso_b3_func_000023DC(void) {}

/* Alloc-cascade ctor (sibling of arcproc_uso_func_0000251C): alloc 108/80/44
 * + ->0x28=&D + &D+1160/1168 descriptors, then a registration tail. Decoded
 * 2026-06-02. Reconstructed 2026-06-22 (agent-e): 59.73 -> 95.54%.
 *  - Whole body wrapped in the `(arg0 != 0 || (alloc; cond))` short-circuit
 *    ladder so the alloc-failure paths fall through to `return s0` (matches
 *    the nested `bne X,zero;<delay assignment>` cascade exactly).
 *  - Distinct extern symbols per global-deref site (D_00000002..8 for the 7
 *    OR'd-value reads; D_00000001 for the 4th-arg pointer) DEFEAT IDO's CSE
 *    that hoisted &D into a saved $s1: target re-materializes the base with a
 *    fresh `lui` per call. This collapsed the size gap -24 -> -1 word and
 *    dropped 162 -> 57 reloc-filtered diffs. (relocs are masked by the gate.)
 *  - `(D[0] == 0x17D7) == 0` form emits the target's `xori;sltiu;bnel`
 *    seq-idiom (a plain `!= 0x17D7` regresses to li+beql).
 * RESIDUAL (~57 diffs, -1 word): deterministic IDO frame-layout/regalloc —
 *  spill-slot numbering off-by-4 (target 0x2C/0x38/0x3C vs base 0x28/0x34/
 *  0x38), bne-delay-slot fill (or s0,a0 vs sw ra at entry), and the indirect-
 *  call object/vtable v0/a3 -> v1/a1 renumber. Not C-controllable (cap class
 *  per docs/TOOLING_DECOMP "register PLACEMENT" / preheader slot order). */
#ifdef NON_MATCHING
char *timproc_uso_b3_func_000023E4(char *a0) {
    char *s0;
    char *a3;
    char *p;
    char *v0;
    char *vt;
    s0 = a0;
    if (a0 != 0 ||
        (s0 = (char *)gl_func_00000000(108), s0 != 0)) {
        a3 = s0;
        if (s0 != 0 ||
            (a3 = (char *)gl_func_00000000(80), a3 != 0)) {
            p = a3;
            if (a3 != 0 ||
                (p = (char *)gl_func_00000000(44), p != 0)) {
                gl_func_00000000(p, (char *)&D_00000000 + 1160);
                *(char **)(p + 0x28) = &D_00000000;
            }
            *(char **)(a3 + 0x28) = &D_00000000;
        }
        *(char **)(s0 + 0x28) = &D_00000000;
        *(char **)(s0 + 0xC) = (char *)&D_00000000 + 1168;
        gl_func_00000000(s0);
        *(int *)(s0 + 0x60) = 120;
        *(int *)(s0 + 0x64) = 161;
        *(int *)(s0 + 0x68) = 191;
        *(int *)(s0 + 0x48) = gl_func_00000000(0);
        gl_func_00000000(*(int *)(s0 + 0x48), s0);
        gl_func_00000000(*(int *)(s0 + 0x48), ((*(int *)&D_00000002 + 3) << 16) | 1, -1, &D_00000001);
        gl_func_00000000(*(int *)(s0 + 0x48), ((*(int *)&D_00000003 + 3) << 16) | 6, -1, &D_00000001);
        gl_func_00000000(*(int *)(s0 + 0x48), ((*(int *)&D_00000004 + 3) << 16) | 7, -1, &D_00000001);
        gl_func_00000000(*(int *)(s0 + 0x48), ((*(int *)&D_00000005 + 3) << 16) | 4, -1, &D_00000001);
        gl_func_00000000(*(int *)(s0 + 0x48), ((*(int *)&D_00000006 + 3) << 16) | 3, -1, &D_00000001);
        gl_func_00000000(*(int *)(s0 + 0x48), ((*(int *)&D_00000007 + 3) << 16) | 2, -1, &D_00000001);
        gl_func_00000000(*(int *)(s0 + 0x48), ((*(int *)&D_00000008 + 3) << 16) | 5, -1, &D_00000001);
        *(int *)(*(int *)(s0 + 0x48) + 0x30) =
            gl_func_00000000(0, &D_00000000, 72, 221, 3, 13);
        gl_func_00000000(*(int *)(s0 + 0x48));
        gl_func_00000000(*(int *)(s0 + 0x48), 140);
        v0 = *(char **)(s0 + 0x48);
        vt = *(char **)(v0 + 0x28);
        ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)v0);
        v0 = (char *)*(int *)(s0 + 0x48);
        gl_func_00000000(s0 + 0x10, (int)v0);
        a3 = v0;
        if (*(int *)(a3 + 0x14) != 0) {
            *(int *)(a3 + 0x4) = 1;
        }
        *(int *)(a3 + 0x14) = (int)s0;
        if (*(int *)((char *)&D_00000000 + 388) == 0 ||
            (*(int *)&D_00000000 == 0x17D7) == 0) {
            *(int *)(*(int *)(s0 + 0x48) + 0xD8) = 0;
        }
        a3 = *(char **)((char *)&D_00000000 + 400);
        gl_func_00000000(s0 + 0x10, a3);
        if (*(int *)(a3 + 0x14) != 0) {
            *(int *)(a3 + 0x4) = 1;
        }
        *(int *)(a3 + 0x14) = (int)s0;
        gl_func_00000000(*(int *)((char *)&D_00000009 + 400), 1, 0, a3);
        *(int *)(s0 + 0x54) = 0;
        *(int *)(s0 + 0x50) = 0;
        *(int *)(s0 + 0x30) = 1;
        *(int *)(s0 + 0x2C) = 0;
    }
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000023E4);
#endif

/* Byte-identical sibling of timproc_uso_b1_func_000024F4 (147 insns).
 * Same display-list build pattern. The 0x260000-series `or a1, s1, tN` wants
 * the hoisted constant (s1) as rs; IDO defaults to value-as-rs. Forced via the
 * assignment-expression operand-order lever `value | (t = 0x260000)` (pins the
 * const as rs at the op; CSE keeps the single lui). See
 * docs/IDO_CODEGEN.md#feedback-ido-commutative-op-operand-order. */
void timproc_uso_b3_func_00002700(int a0) {
    int t;
    gl_func_00000000((char *)&D_00000000 + 112,
                     (*(int *)&D_00000000 << 3) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 136,
                     ((*(int *)&D_00000000 << 3) + 1) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 160,
                     ((*(int *)&D_00000000 << 3) + 2) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 184,
                     ((*(int *)&D_00000000 << 3) + 3) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 208,
                     ((*(int *)&D_00000000 << 3) + 4) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 232,
                     ((*(int *)&D_00000000 << 3) + 5) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 256,
                     ((*(int *)&D_00000000 << 3) + 6) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 280,
                     ((*(int *)&D_00000000 << 3) + 7) | (t = 0x260000));
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
    (void)a0;
}

/* Twin of timproc_uso_b1_func_00002740 (byte-identical). MATCHED 2026-06-11
 * via the array-IXA lever derived from the uopt source (references/ido):
 * a 2D-array row index (Row294C *base; base[idx]) keeps the IXA ucode form,
 * which ugen lowers as addu rd, base, scaled (base FIRST); flat ptr-arith
 * (base + idx*0xA) goes through cfe's ADD path which evaluates the deeper
 * mpy operand first -> addu rd, scaled, base. See docs/IDO_CODEGEN.md
 * "addu operand order" uopt-source entry. */
extern int D_b3_294C_g208;
extern int D_b3_294C_g20C;
void timproc_uso_b3_func_0000294C(int *a0)
{
  int new_var;
  switch (a0[0x50 / 4])
  {
    case 0:
      if (gl_func_00000000(&D_00000000, 0x40100) != 0)
    {
      typedef int Row294C[10];
      Row294C *base = (Row294C *) a0[0x48 / 4];
      int *slot = base[((int *) base)[0x7C / 4]];
      if (slot[0x90 / 4] != 0)
      {
        if (slot[0x88 / 4] != 0)
        {
          int *base2;
          int *slot2;
          gl_func_00000000(5);
          if (1)
          {
          }
          slot = a0;
          D_b3_294C_g208 = slot[0x48 / 4];
          D_b3_294C_g20C = (int) a0;
          base2 = (int *) slot[0x48 / 4];
          ;
          ((void (*)(void)) ((int *) (base2 + (base2[0x7C / 4] * 0xA)))[(0x90 ^ 0) / (new_var = 4)])();
        }
        else
        {
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

#ifdef NON_MATCHING
/* timproc_uso_b3_func_00002A44: HUD draw dispatcher (near-exact clone of
 * timproc_uso_b1_func_00002838; only the middle panel ID differs 0x1C0->0x1D8).
 * switch arg0->0x50 (0/1/2); draw-target IDs are &D-relative addresses; both
 * 0x178 loads are lbu; case 2 falls through to case 0 (return). Fresh decode
 * 2026-05-29 (m2c-confirmed). Caps: structs + cb prototypes untyped (USO-reloc),
 * &D not symbolized. NON_MATCHING. */
extern int gl_func_00000000();
void timproc_uso_b3_func_00002A44(char *arg0) {
    int v0;
    int a2;
    int t1;

    gl_func_00000000();
    *(int *)(arg0 + 0x5C) = *(int *)(arg0 + 0x5C) - 0x10;
    switch (*(int *)(arg0 + 0x50)) {
    case 1:
        gl_func_00000000(0);
        gl_func_00000000((char *)&D_00000000 + 0x1F0);
        gl_func_00000000((char *)&D_00000000 + 0x1F0, 0xA0, 0x25, 3);
        gl_func_00000000(arg0, 0x25);
        gl_func_00000000(arg0, *(unsigned char *)((char *)&D_00000000 + 0x178), 0x50);
        gl_func_00000000((char *)&D_00000000 + 0x1D8);
        gl_func_00000000((char *)&D_00000000 + 0x1D8);
        gl_func_00000000((char *)&D_00000000 + 0x1D8, 0xA0, 0x69, 3);
        t1 = *(int *)&D_00000000;
        v0 = *(int *)(arg0 + 0x68);
        if (t1 != 0) {
            v0 += 0xA;
        }
        a2 = v0 - 0x27;
        if (t1 != 0) {
            a2 -= 0xE;
        }
        gl_func_00000000((char *)&D_00000000 + 0x148);
        gl_func_00000000((char *)&D_00000000 + 0x148);
        gl_func_00000000((char *)&D_00000000 + 0x148, 0xA0, a2, 3);
        gl_func_00000000(arg0, v0 - 0x14);
        return;
    case 2:
        gl_func_00000000(0);
        gl_func_00000000((char *)&D_00000000 + 0x1F0);
        gl_func_00000000((char *)&D_00000000 + 0x1F0, 0xA0, 0x25, 3);
        gl_func_00000000(arg0, 0x25);
        gl_func_00000000(arg0, *(unsigned char *)((char *)&D_00000000 + 0x178), 0x50);
        gl_func_00000000((char *)&D_00000000 + 0x1D8);
        gl_func_00000000((char *)&D_00000000 + 0x1D8);
        gl_func_00000000((char *)&D_00000000 + 0x1D8, 0xA0, 0x69, 3);
        gl_func_00000000((char *)&D_00000000 + 0x160);
        gl_func_00000000((char *)&D_00000000 + 0x160);
        gl_func_00000000((char *)&D_00000000 + 0x160, 0xA0, 0x8E, 3);
        v0 = *(int *)(arg0 + 0x68);
        if (*(int *)&D_00000000 != 0) {
            v0 -= 8;
        }
        gl_func_00000000((char *)&D_00000000 + 0x178);
        gl_func_00000000((char *)&D_00000000 + 0x178);
        gl_func_00000000((char *)&D_00000000 + 0x178, 0xA0, v0 - 0x13, 3);
        gl_func_00000000(arg0, v0);
        break;
    case 0:
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_00002A44);
#endif

/* 4-stage state dispatcher on obj->0x58: each stage queries gl_func(&D, flag);
 * on hit, conditionally toggles obj->0x58 or fires a virtual method
 * ((*vt->0x5C)((short)vt->0x58 + o48)) on the obj->0x48 sub-object. The empty
 * `if (1) {}` before each o48 load is load-bearing: it forces an IDO
 * basic-block boundary that colors o48 into the dead $v0 (vt into $v1),
 * matching the target (was a 98.26% v0/v1 near-miss). Same lever as
 * mgrproc_uso_func_00001324 / the timproc_uso_b5 dispatch family. */
void timproc_uso_b3_func_00002C98(char *obj) {
    char *o48;
    char *vt;

    if (gl_func_00000000((char *)&D_00000000, 0x10001) != 0 && *(int *)(obj + 0x58) != 0) {
        gl_func_00000000(1);
        *(int *)(obj + 0x58) = 0;
    }
    if (gl_func_00000000((char *)&D_00000000, 0x4002) != 0 && *(int *)(obj + 0x58) == 0) {
        gl_func_00000000(1);
        *(int *)(obj + 0x58) = 1;
    }
    if (gl_func_00000000((char *)&D_00000000, 0x40100) != 0) {
        if (*(int *)(obj + 0x58) == 0) {
            gl_func_00000000(5);
            gl_func_00000000((char *)&D_00000000, 2);
            *(int *)(*(char **)(obj + 0x48) + 0xD8) = 0;
            if (1) {}
            o48 = *(char **)(obj + 0x48);
            *(int *)(obj + 0x50) = 0;
            vt = *(char **)(o48 + 0x28);
            ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)o48);
        } else {
            gl_func_00000000(0x802);
            if (1) {}
            o48 = *(char **)(obj + 0x48);
            *(int *)(obj + 0x50) = 0;
            vt = *(char **)(o48 + 0x28);
            ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)o48);
        }
    }
    if (gl_func_00000000((char *)&D_00000000, 0x200) != 0) {
        gl_func_00000000(0x802);
        if (1) {}
        o48 = *(char **)(obj + 0x48);
        *(int *)(obj + 0x50) = 0;
        vt = *(char **)(o48 + 0x28);
        ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)o48);
    }
}

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
 *      wrap comment); it lives in 00002DF0's symbol footprint.
 *
 * Old recipe: docs/POST_CC_RECIPES.md "SUFFIX_BYTES on this function with
 * 0x00057080 to put the trailing sll back after C-emit; then successor
 * matches without PROLOGUE_STEALS." Instruction-appending SUFFIX_BYTES
 * REMOVED 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy;
 * docs/POST_CC_RECIPES.md DEPRECATED. Real fix needs splat boundary
 * correction so the trailing sll belongs to func_00002EF0's symbol — not
 * tick-safe.
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

/* 3-call wrapper over the +0x70 records table, indexed by a1*24.
 * MATCHED 2026-06-10 (23/23): the old wrap's hand-spelled shift form
 * ((a1<<2)-a1)<<3 SPLIT the index chain across t6/t7/t8; plain a1*24
 * lets IDO emit its own x24 decomposition -- (a1<<2 - a1)<<3 with
 * single-reg t6 reuse and the first sll hoisted above the prologue --
 * exactly the target. Lesson: write the arithmetic PLAINLY and let the
 * compiler pick the decomposition (inverse of the explicit-shift CSE-
 * bust lever; both directions now documented). Boundary: reverse-merge
 * from 2DF0's tail, done 2026-05-30. */
extern char D_b3_2EF0_table;
void timproc_uso_b3_func_00002EEC(int a0, int a1, int a2) {
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

/* timproc_uso_b3_func_00000E30 + 00000E54: SUFFIX_BYTES-absorbed orphans ←
 * timproc_uso_b3_func_00000DE4 (12 words exact:
 *   0x8C8E06A8,0x8DC2006C,0x50400007,0x00001025,0x8C4F00EC,0x51E00004,
 *   0x00001025,0x03E00008,0x24020001,0x00001025,0x03E00008,0x00000000).
 * _00000E54 was a C-body stub (`int f(void) { return 0; }`) with both
 * own SUFFIX_BYTES (1 nop trailer) and INSN_PATCH (force `move v0,zero;
 * jr ra`); removed entirely along with both recipes. No external callers,
 * so dropping the symbol is safe. The 3 trailing recipe words of
 * _00000DE4 (`move v0,zero; jr ra; nop`) emit the same bytes at vram
 * 0xE54-0xE5F. */

/* SUFFIX_BYTES-absorbed orphan (per
 * docs/MATCHING_WORKFLOW.md#feedback-splat-orphan-duplicate-symbol-pruning,
 * no-truncate variant): timproc_uso_b3_func_00001074 (7 words) ←
 * timproc_uso_b3_func_00000FF4 SUFFIX_BYTES (exact 7-word match
 * 0x240E0009,0x3C010000,0xAFA40000,0x03E00008,0xAC2E0040,0x3C050000,0x8CA50170).
 * Pre-prune the orphan symbol was at .o offset 0x3114 (tail). */

/* timproc_uso_b3_func_000023CC + 000023D4: SUFFIX_BYTES-absorbed orphans
 * ← timproc_uso_b3_func_00002388 (6 words exact:
 *   0x03E00008,0x00000000,0x03E00008,0x00000000,0x03E00008,0x00000000).
 * _000023D4 had its own 2-word SUFFIX_BYTES recipe (`0x00000000,0x00000000`)
 * that emitted 2 nops at the .o tail past its orphan position — those
 * bytes weren't at any meaningful linked-vram, so dropping the recipe is
 * neutral. Removed alongside the .s deletion (per docs/MATCHING_WORKFLOW.md
 * orphan-attached-recipes blocker note). */

/* Orphan/gap status (resolved 2026-06-10):
 *   _00001920: exists as its own 8-byte NM symbol after 1870 (correct).
 *   _000021F4: was missing entirely (no INCLUDE_ASM line; -0x4C damage) --
 *   restored at its address-ordered position after 21B0.
 *   _00002238: 2-word stolen-prologue orphan, now a standalone GLOBAL_ASM
 *   block after 21F4. Block byte-verified vs assets/timproc_uso_block_3.bin
 *   (only reloc-class lui/jal field diffs remain). */
