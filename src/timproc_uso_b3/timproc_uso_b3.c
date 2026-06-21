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

#ifdef NON_MATCHING
/* timproc_uso_b3_func_000000B0: 0x4F4 (317 insns), 0x40-byte stack frame.
 * Boundary-checked 2026-05-19: one jr ra plus an internal jump-table jr.
 *
 * Full state-machine decode of the 14 jump-table arms. This is still
 * NON_MATCHING because IDO's C switch emits a normal rodata jump table, while
 * this raw-word USO target has the original relocatable table shape. The
 * explicit body preserves the real call/field map for the next pass:
 * state 4/6/8/9 loop by writing D[0x40]; all other decoded arms set done.
 * Current score: 36.09% (up from 3.36%). Tried volatile stack locals
 * (regressed to 32.28%) and a forced -O0 probe (blocked by pad sidecars). */
timproc_uso_b3_func_000000B0(a0, a1) int * a0; int a1; {
    int done;
    int tmp;
    int *node;
    char *base;
    char *link;

    done = 0;
    do {
        switch ((unsigned int)a1) {
        case 0:
            gl_func_00000000(a0, 1, 7, 1);
            *(int*)((char*)&D_00000000 + 0x44) = 4;
            TIMB3_D_48 = 0xD;
            done = 1;
            break;
        case 1:
            gl_func_00000000(a0, 1, 7, 1);
            *(int*)((char*)&D_00000000 + 0x44) = 4;
            TIMB3_D_48 = 0xD;
            done = 1;
            break;
        case 2:
            gl_func_00000000(a0, 1, 7, 2);
            *(int*)((char*)&D_00000000 + 0x44) = 4;
            TIMB3_D_48 = 0xD;
            done = 1;
            break;
        case 3:
            gl_func_00000000(a0, 1, 7, 4);
            *(int*)((char*)&D_00000000 + 0x44) = 4;
            TIMB3_D_48 = 0xD;
            done = 1;
            break;
        case 4:
            gl_func_00000000(a0, 1, TIMB3_D_64);
            *(int*)((char*)&D_00000000 + 0x40) = 5;
            break;
        case 5:
            gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000 + 4));
            gl_func_00000000(&D_00000000, 4, TIMB3_D_64, 2);
            tmp = gl_func_00000000(a0, *a0, 1);
            tmp = gl_func_00000000(0, 0x410000, tmp, *a0);
            tmp = gl_func_00000000(a0, 0, tmp);
            done = 1;
            break;
        case 6:
            gl_func_00000000(a0, 0, *(unsigned char*)((char*)&D_00000000 + 0x178));
            *(int*)((char*)&D_00000000 + 0x40) = 7;
            break;
        case 7:
            gl_func_00000000(&D_00000000, 0xA, TIMB3_D_64, 2);
            tmp = gl_func_00000000(a0, *a0, 1);
            tmp = gl_func_00000000(
                0, *(int*)((char*)&D_00000000 + 0x170) + 0x1A000F, tmp, *a0);
            tmp = gl_func_00000000(a0, 0, tmp);
            done = 1;
            break;
        case 8:
            gl_func_00000000(a0);
            *(int*)((char*)&D_00000000 + 0x40) =
                *(int*)((char*)&D_00000000 + 0x44);
            break;
        case 9:
            gl_func_00000000(a0);
            *(int*)((char*)&D_00000000 + 0x40) = 0xA;
            break;
        case 10:
            gl_func_00000000(&D_00000000, 7, 0, 0);
            tmp = gl_func_00000000(0);
            gl_func_00000000(a0, 1, tmp);
            done = 1;
            break;
        case 11:
            tmp = gl_func_00000000(a0, *a0, 4);
            tmp = gl_func_00000000(
                0, *(int*)((char*)&D_00000000 + 0x170) + 0x20000, tmp, *a0);
            node = (int*)tmp;
            base = &D_00000000;
            link = base + 0x10;
            gl_func_00000000(link, node);
            if (node[5] != 0) {
                node[1] = 1;
            }
            node[5] = (int)base;
            gl_func_00000000(a0, *a0);
            done = 1;
            break;
        case 12:
            tmp = gl_func_00000000(TIMB3_D_64);
            gl_func_00000000(
                a0, (TIMB3_D_64 | 0x4000) | tmp, 0x4000, *a0);
            done = 1;
            break;
        case 13:
            tmp = gl_func_00000000(0, 1, 0);
            base = &D_00000000;
            link = base + 0x10;
            gl_func_00000000(link, tmp);
            node = (int*)tmp;
            if (node[5] != 0) {
                node[1] = 1;
            }
            node[5] = (int)base;
            done = 1;
            break;
        }
        a1 = *(int*)((char*)&D_00000000 + 0x40);
    } while (done == 0);
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

/* timproc_uso_b3_func_00000994: 243-insn constructor. The jal-0 calls are the
 * cross-USO placeholder gl_func_00000000 (K&R, the disasm mislabels them as the
 * nearest symbol func_000000B0). Alloc self (0x730) if a0==NULL, return NULL on
 * fail; field inits self->0x568=0, self->0x528=arg3, self->0x72C=0.0f; alloc 0xDC
 * sub-node -> self->0x6A8 (+ D[0x138]=it); a 6-iter unrolled registration loop
 * gl(self->0x48, ((D+3)<<16)|N, -1) for N in {0,1,4,3,2,5}; tail cmd calls.
 * Returns self. NM wrap (m2c can't read raw-.word USO; decoded from objdump).
 *
 * 2026-06-01 (32.32 -> 44.91): the function's PROLOGUE is a 5-stage eddproc-style
 * get-or-create cascade (alloc self 0x730 / n1 0x6a8 / n2 0x50 / n3 0x2c, dead
 * stage-guards kept via goto-chain, each node->0x28 = vtable via distinct extern
 * to bust the &D address CSE) — NOT the single self-alloc the old body assumed.
 * Cascade reproduced (frame -0x38, target t6/t7/t8/t9 vtable stores).
 * 2026-06-01b (44.91 -> 49.33): post-cascade field-init block corrected —
 * func(self, a1, &D+0x3c0, a2) (was gl(&D,a1,a2)); added gl(self) call after
 * self->0x528=a3; sub vtable via distinct extern D_b3_994_v4.
 * 2026-06-01d (59.28 -> 65.72): wrapped the registration loop in the 2nd
 * `if ((self->0x4f0<<15) < 0)` block with preamble (self->0x48=gl(0);
 * gl(self->0x48,self); self->0x48->0x30=self->0x568) + post-loop gl(self+0x10,
 * self->0x48) + beql self->0x48->0x14 dance. The earlier 22% regression was
 * confined to the MERGE-TAIL block (added separately, gated).
 * 2026-06-01c (49.33 -> 59.28): added the VTABLE-DISPATCH block between
 * `D[0x138]=sub` and the reg loop: sub->0xb4 = ((self->0x4f0<<15)<0)?11:0;
 * gl(sub,self,self->0x568,self->0x528); virtual call
 * ((void(*)(int))((int*)sub->0x28)[0x5c/4])(*(short*)(vt+0x58)+sub) [jalr];
 * gl(self+0x10,sub); beql sub->0x14 dance.
 * TBD (multi-tick): the remaining MERGE TAIL (after the reg-loop conditional):
 *   self->0x4f4 = arg1 & 0xffff;  self->0x48 = 0;  node = D[0x190];
 *   gl(self+0x10, node);  beql node->0x14 dance;  gl(node,1,0);  gl().
 * CAUTION (confirmed 2026-06-01, gated 3×): adding the merge tail — even a
 * conservative version, and even with `(void)&a1` to force arg1 homing —
 * REGRESSES 65.72 -> 21.6. So arg1 live-range is NOT the (sole) cause.
 *
 * THE REAL BLOCKER (precisely located 2026-06-01): build frame is -0x40 vs
 * target -0x38 (8 bytes too big). The extra 8 bytes is ONE extra in-frame spill
 * slot at sp+0x38(56): the build spills the cascade node n2 (a2) to a FRESH
 * slot 56 across the stage-3 alloc, where the target REUSES 0x30(48)/0x34(52)
 * for the cascade a2/a3 spills. That single extra slot shifts the framesize,
 * hence EVERY arg-home (a1/a2/a3 at 0x44/0x48/0x4c vs target 0x3c/0x40/0x44)
 * and stack offset by 8 — a global diff that caps the present body AND makes
 * the merge tail (which adds more spills) blow the layout up further. NEXT
 * APPROACH: drive the cascade spill slots down to reuse 0x30/0x34 (fewer
 * simultaneously-live cascade locals, or the `-Wo,-zdbug:6` regalloc dump per
 * project_1080_regalloc_dump_unlocked to see the exact slot coloring). The reg
 * loop's per-call D[0] re-load may also need distinct externs (CSE-bust). Build
 * 207/243 insns; self IS in s0 (matches target). */
#ifdef NON_MATCHING
extern char D_b3_994_v0;
extern char D_b3_994_v1;
extern char D_b3_994_v2;
extern char D_b3_994_v3;
extern char D_b3_994_v4;
void *timproc_uso_b3_func_00000994(int *a0, int a1, int a2, int a3) {
    int *self = a0;
    int *n1, *n2, *n3;
    int *sub;
    /* 5-stage get-or-create cascade (eddproc-style): alloc self(0x730) /
     * n1(0x6a8) / n2(0x50) / n3(0x2c); dead stage-guards kept via goto-chain;
     * each obtained node->0x28 = vtable via a DISTINCT extern (CSE-bust so IDO
     * re-materializes lui;addiu per store = target t6/t7/t8/t9). */
    if (a0 == 0) {
        self = (int *)gl_func_00000000(0x730);
        if (self == 0) return self;
    }
    n1 = self;
    if (self == 0) { n1 = (int *)gl_func_00000000(0x6a8); if (n1 == 0) goto S_self; }
    n2 = n1;
    if (n1 == 0) { n2 = (int *)gl_func_00000000(0x50); if (n2 == 0) goto S_n1; }
    n3 = n2;
    if (n2 == 0) { n3 = (int *)gl_func_00000000(0x2c); if (n3 == 0) goto S_n2; }
    gl_func_00000000(n3, (char *)&D_00000000 + 0x3b8);
    n3[0x28 / 4] = (int)&D_b3_994_v0;
S_n2:
    n2[0x28 / 4] = (int)&D_b3_994_v1;
S_n1:
    n1[0x28 / 4] = (int)&D_b3_994_v2;
    gl_func_00000000((char *)n1 + 0x50);
S_self:
    self[0x28 / 4] = (int)&D_b3_994_v3;
    self[0x568 / 4] = 0;
    gl_func_00000000(self, a1, (char *)&D_00000000 + 0x3C0, a2);
    self[0x528 / 4] = a3;
    gl_func_00000000(self);
    *(float *)&self[0x72C / 4] = 0.0f;
    gl_func_00000000((char *)&D_00000000 + 0x3D0, 0);
    gl_func_00000000(&D_00000000, 0);
    sub = (int *)gl_func_00000000(0xDC);
    if (sub != 0) {
        sub[0x28 / 4] = (int)&D_b3_994_v4;
    }
    self[0x6A8 / 4] = (int)sub;
    *(int **)((char *)&D_00000000 + 0x138) = sub;

    /* vtable-dispatch block */
    if ((self[0x4F0 / 4] << 15) >= 0) {
        sub[0xB4 / 4] = 0;
    } else {
        sub[0xB4 / 4] = 11;
    }
    gl_func_00000000(sub, self, self[0x568 / 4], self[0x528 / 4]);
    {
        int *vt = (int *)sub[0x28 / 4];
        ((void (*)(int))vt[0x5C / 4])(*(short *)((char *)vt + 0x58) + (int)sub);
    }
    gl_func_00000000((char *)self + 0x10, sub);
    if (sub[0x14 / 4] != 0) {
        sub[0x4 / 4] = 1;
    }
    sub[0x14 / 4] = (int)self;

    if ((self[0x4F0 / 4] << 15) < 0) {
        self[0x48 / 4] = (int)gl_func_00000000(0);
        gl_func_00000000(self[0x48 / 4], self);
        *(int *)((char *)self[0x48 / 4] + 0x30) = self[0x568 / 4];
        gl_func_00000000(self[0x48 / 4], (*(int *)&D_00000000 + 3) << 16, -1, &D_00000000);
        gl_func_00000000(self[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 1, -1, &D_00000000);
        gl_func_00000000(self[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 4, -1, &D_00000000);
        gl_func_00000000(self[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 3, -1, &D_00000000);
        gl_func_00000000(self[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 2, -1, &D_00000000);
        gl_func_00000000(self[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 5, -1, &D_00000000);
        gl_func_00000000(self[0x48 / 4]);
        gl_func_00000000((char *)self + 0x10, self[0x48 / 4]);
        if (*(int *)((char *)self[0x48 / 4] + 0x14) != 0) {
            *(int *)((char *)self[0x48 / 4] + 0x4) = 1;
        }
        *(int *)((char *)self[0x48 / 4] + 0x14) = (int)self;
    }
    return self;
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
#ifdef NON_MATCHING
extern int D_arg_b3_10E4[];
extern int D_cur_b3_10E4;
void timproc_uso_b3_func_000010E4(int *self) {
  int *v0;
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
    v0 = (int *) self[0x48 / 4];
    /* Twin of b1's 1130: direct inline-loaded indirect call coalesces the
     * index web into the $t9 call register; 39/40 words. Single residual
     * is the addr addu operand order (product-rs vs target base-rs), a cap
     * coupled to the $t9 coalesce (see the b1 twin's comment). */
    (*((void (**)(void)) ((((char *) v0) + (v0[0x7C / 4] * stride)) + 0x90)))();
  }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b3/timproc_uso_b3", timproc_uso_b3_func_000010E4);
#endif

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
#ifdef NON_MATCHING
void timproc_uso_b3_func_00001240(char *a0) {
    float color[4];
    char pad[32];
    char *saved;
    int armed;
    char *tmp;

    color[0] = 1.0f;
    color[1] = 1.0f;
    color[2] = 1.0f;
    color[3] = 1.0f;
    (void)color;
    (void)pad;

    if (*(int*)(a0 + 0x500) != 0) {
        if (D_b3_1240_f0 <= 0.0f) {
            if (*(float*)(a0 + 0x72C) < D_b3_1240_f40) {
                *(float*)(a0 + 0x72C) += D_b3_1240_f44;
            }

            *(int*)(a0 + 0x508) = *(int*)(a0 + 0x508) + 1;
            armed = 0;
            if ((*(int*)(*(char**)(a0 + 0x528) + 0x14) & 2) != 0 &&
                *(int*)(a0 + 0x4FC) != 0 &&
                *(int*)(*(char**)(D_b3_1240_ptr138 + 0x44) + 0x3C) < 3) {
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
                    tmp = *(char**)(a0 + 0x6A8);
                    tmp = *(char**)(tmp + 0x44);
                    gl_func_00000000(a0, 0x8C, *(int*)(tmp + 0x14));
                }
            } else {
                tmp = *(char**)(a0 + 0x6A8);
                tmp = *(char**)(tmp + 0x44);
                gl_func_00000000(a0, 0x8C, *(int*)(tmp + 0x14));
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
 * 2026-05-31: completed the missing field-init block 38.2->56.3%. The sketch
 * had ONLY the alloc cascade + 0x28 vtable sets; added p1->0x60=a2, the
 * {0xD8:160,0xDC:130,0xE0:160,0xE4:29,0xE8:160,0xEC:105} field set, two 1.0f
 * stores (p1->0x108 and a1->0x72C), p1->0xD4=a1, the final dispatch call
 * gl_func(p1+0xF0, ((D[0]+35)<<16)|(a1->0x6B0+7)), and return p1. Logic now
 * complete. RESIDUAL (56->100) is the alloc-or-passthrough cascade dead-arm
 * form (build 70 vs 90 insns — target emits the defensive passthrough arms per
 * docs/PATTERNS.md#feedback-alloc-or-passthrough-cascade-includes-dead-arms)
 * + the 8-byte frame-size cap. INCLUDE_ASM remains build path.
 *
 * Default INCLUDE_ASM build matches; this wrap is for grep/discoverability. */
extern int gl_func_00000000();
extern char D_00000000;
int *timproc_uso_b3_func_00001660(int *a0, char *a1, int a2) {
    int *p1 = a0;
    int *p2;
    int *p3;
    if (p1 == 0) {
        p1 = (int*)gl_func_00000000(0x10C);
        if (p1 == 0) return 0;
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
    *(int*)((char*)p1 + 0x60) = a2;
    *(int*)((char*)p1 + 0xE0) = 160;
    *(int*)((char*)p1 + 0xE4) = 29;
    *(int*)((char*)p1 + 0xD8) = 160;
    *(int*)((char*)p1 + 0xDC) = 130;
    *(int*)((char*)p1 + 0xE8) = 160;
    *(int*)((char*)p1 + 0xEC) = 105;
    *(float*)((char*)p1 + 0x108) = 1.0f;
    *(int*)((char*)p1 + 0xD4) = (int)a1;
    *(float*)(a1 + 0x72C) = 1.0f;
    gl_func_00000000((char*)p1 + 0xF0,
        ((*(int*)&D_00000000 + 35) << 16) | (*(int*)(a1 + 0x6B0) + 7));
    return p1;
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
 * wrap for canonical decode. Mirrored source=4 2026-06-01; expected to share
 * the canonical O2 residual (target 0x58 frame + incoming-$f0 stores vs C's
 * explicit-zero smaller frame). */
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

#ifdef NON_MATCHING
/* timproc_uso_b3_func_000019CC: widget constructor (clone of arcproc_uso_func_
 * 00001D18). Field inits (0xC=0x3E4, 0xB8/0x50=arg1, 0x4C=arg3, 0xAC=0). Gated on
 * arg1->0x4F0 bit-16: sets 0x54=arg2, 0xD0=0xFF, 0xD4=0, 1.0f quad at 0xC0/C4/C8/
 * CC; 5 cb setup calls; allocs child 0xBC (from a 0x30-stride table indexed by
 * *(int*)(&D+0x64)) + links it; allocs child 0x94, inits its {250,235,100,0}/255
 * color quad (var-divisor div.s) + ints/ptr + float cb (gl_proto_19cc) + links it.
 * Fresh decode 2026-05-29 (m2c-confirmed). 82.8% reg-blind (148/149 insns).
 * Residual: float-call mfc1 setup + spill regalloc. Caps: structs + cb prototypes
 * untyped (USO-reloc), &D not symbolized. NON_MATCHING. */
extern int gl_proto_19cc(void *, int, int, float, float);
void timproc_uso_b3_func_000019CC(char *arg0, char *arg1, int arg2, int *arg3) {
    char *sp44;
    char *o;
    char *sub;
    float denom = 255.0f;

    *(int *)(arg0 + 0xC) = 0x3E4;
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
        sp44 = (char *)gl_func_00000000(*(int *)(*(int **)(arg0 + 0x4C)) + (*(int *)((char *)&D_00000000 + 0x64) * 0x30), 0);
        o = (char *)gl_func_00000000(0, *(int *)(arg0 + 0x60));
        *(char **)(arg0 + 0xBC) = o;
        gl_func_00000000(o, *(int *)(sp44 + 4));
        gl_func_00000000(*(char **)(arg0 + 0xBC), 0x35, 0xD6);
        gl_func_00000000(arg0 + 0x10, *(char **)(arg0 + 0xBC));
        if (*(int *)(*(char **)(arg0 + 0xBC) + 0x14) != 0) {
            *(int *)(*(char **)(arg0 + 0xBC) + 4) = 1;
        }
        *(char **)(*(char **)(arg0 + 0xBC) + 0x14) = arg0;
        sub = (char *)gl_func_00000000(0, *(int *)(arg0 + 0x58), *(char **)(arg0 + 0xBC));
        *(char **)(arg0 + 0x94) = sub;
        gl_func_00000000(sub, 0);
        gl_proto_19cc(*(char **)(arg0 + 0x94), 0xA0, 0x46, 1.0f, 1.0f);
        sub = *(char **)(arg0 + 0x94);
        *(int *)(sub + 0x18) = *(int *)(sub + 0x18) & ~4;
        sub = *(char **)(arg0 + 0x94);
        *(float *)(sub + 0x64) = 250.0f / denom;
        *(float *)(sub + 0x68) = 235.0f / denom;
        *(float *)(sub + 0x6C) = 100.0f / denom;
        *(float *)(sub + 0x70) = 0.0f / denom;
        *(int *)(*(char **)(arg0 + 0x94) + 0xA0) = *(int *)(arg0 + 0x6C) + 0x108;
        *(int *)(*(char **)(arg0 + 0x94) + 0x80) = 0;
        *(int *)(*(char **)(arg0 + 0x94) + 0x84) = -0x12;
        sub = *(char **)(arg0 + 0x94);
        gl_func_00000000(arg0 + 0x10, sub, sub + 0x64);
        if (*(int *)(sub + 0x14) != 0) {
            *(int *)(sub + 4) = 1;
        }
        *(char **)(sub + 0x14) = arg0;
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
 * 0xD8 from arg0->0x44->0x60->0x800->0x4C (cb on change); optional draw block;
 * ramp 0xA8 toward 0x44->0x18 by 0xFA/0x32/0x19/1; state-1 draws (float arg via
 * gl_proto_1c68); 0x94 sub-widget enable + 0x32/5/1 ramp on 0x44->0x20 else
 * disable; state-2 (0x4F8==0) blink 0x8C by (0xAC++ & 8). cb(arg0) tail. Fresh
 * decode 2026-05-29 (m2c-confirmed). 84.02%. Caps: structs + cb prototypes
 * untyped (USO-reloc). NON_MATCHING.
 *
 * 2026-06-01 PRECISE GAP MAP (reloc-aware difflib, build 239 insns vs target
 * 253 = 14 short — but NOT one missing block; logic is all present, the deficit
 * is BRANCH-FORM, so this is regalloc/scheduling-class, not addable-logic):
 *   - insn 5+ : `bc=arg0->0xB8` colors to v0 (build) vs a0 (target) — the
 *     v0-reuse-after-void-call cap (gl_func() return frees v0; target uses a0).
 *     Cascades through bc->0x4F0/0x4DC reads. See IDO_CODEGEN v0-reuse entry.
 *   - built[67:94] vs target[66:94] (state-2 sync, the `if (v0 && bc->0x4DC==1)`
 *     + `arg0->0x48==2` block): target emits `beqz nop beqz nop` (two split
 *     branches) where the `&&` here folds differently; +1 insn.
 *   - built[173:189] vs target[176:198] (+6) and built[193:207] vs [202:219]
 *     (+3): the 0x94 sub-widget ramp (r>=0x32/5/1) — target uses a `bnezl`
 *     branch-likely and a different li/li/addiu/jal/sw arg-setup schedule per
 *     ramp stage; the plain if-elseif chain here emits the un-likely form.
 *   - float-arg setup for the two gl_proto_1c68(...,Nf,Nf) calls differs.
 * Next attack (targeted, per-region): convert the 0x94 ramp to the branch-likely
 * shared-tail goto shape (see /decompile branch-likely recipe) — that single
 * block is ~9 of the 14 missing insns. Branch-form/regalloc residual.
 * CASCADE ORDER MATTERS: the length divergence begins at the state-2 sync
 * block (built[67]/target[66]); fixing the LATER 0x94 ramp alone is
 * byte-neutral on fuzzy (verified 2026-06-01: &p44->0x20 pointer-form for the
 * +0x32/+5 stages compiled identically, 84.02% unchanged) because everything
 * after the first divergence stays mis-shifted. Must realign from the FIRST
 * length diff (state-2 sync `&&`/branch-likely forms) outward, not from the
 * tail. */
extern int gl_proto_1c68(void *, int, int, float, float);
void timproc_uso_b3_func_00001C68(char *arg0) {
    char *bc;
    char *p44;
    char *p94;
    char *p8c;
    int v0;
    int v0b;
    int a1;
    int rem;
    int r;
    int t1;
    int t2;

    gl_func_00000000();
    bc = *(char **)(arg0 + 0xB8);
    if ((*(int *)(bc + 0x4F0) & 0x10000) && (*(int *)(bc + 0x4DC) == 1)) {
        *(int *)(arg0 + 0x30) = *(int *)(arg0 + 0x30) + 0x21;
        gl_func_00000000(arg0);
        t2 = *(int *)(arg0 + 0xA0) - 0x21;
        *(int *)(arg0 + 0xA0) = t2;
        if (t2 < 0) {
            *(int *)(arg0 + 0xA0) = 0;
            gl_func_00000000(*(int *)(arg0 + 0x84), 0, 0);
            gl_func_00000000(*(int *)(arg0 + 0xB8));
            *(float *)(*(char **)(arg0 + 0xB8) + 0x554) = 192.0f;
            *(int *)(*(char **)(arg0 + 0xB8) + 0x544) = 0xFF;
            *(int *)(arg0 + 0x2C) = 0;
        }
    }
    gl_func_00000000(arg0);
    bc = *(char **)(arg0 + 0xB8);
    v0 = *(int *)(bc + 0x4F0) & 0x10000;
    if ((v0 != 0) && (*(int *)(bc + 0x4DC) == 1)) {
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
            gl_func_00000000(*(int *)(arg0 + 0xB8));
            v0 = *(int *)(*(char **)(arg0 + 0xB8) + 0x4F0) & 0x10000;
        }
    }
    if (v0 != 0) {
        t1 = *(int *)(arg0 + 0xA8);
        rem = *(int *)(*(char **)(arg0 + 0x44) + 0x18) - t1;
        if (rem >= 0xFA) {
            *(int *)(arg0 + 0xA8) = t1 + 0xFA;
            v0b = *(int *)(*(char **)(arg0 + 0xB8) + 0x4DC);
        } else if (rem >= 0x32) {
            *(int *)(arg0 + 0xA8) = t1 + 0x32;
            v0b = *(int *)(*(char **)(arg0 + 0xB8) + 0x4DC);
        } else if (rem >= 0x19) {
            *(int *)(arg0 + 0xA8) = t1 + 0x19;
            v0b = *(int *)(*(char **)(arg0 + 0xB8) + 0x4DC);
        } else {
            if (rem > 0) {
                *(int *)(arg0 + 0xA8) = t1 + 1;
            }
            v0b = *(int *)(*(char **)(arg0 + 0xB8) + 0x4DC);
        }
        if (v0b == 1) {
            gl_func_00000000(*(int *)(arg0 + 0x84), *(int *)(arg0 + 0xA0), 1);
            gl_func_00000000(*(int *)(arg0 + 0x80), *(int *)(*(char **)(arg0 + 0x44) + 0x30), 0);
            p44 = *(char **)(arg0 + 0x44);
            gl_proto_1c68(*(int *)(arg0 + 0x80), *(int *)(p44 + 8), *(int *)(p44 + 0xC), 0.0f, 0.0f);
        }
        if (*(int *)(*(char **)(arg0 + 0x44) + 0x1C) != 0) {
            gl_proto_1c68(*(int *)(arg0 + 0x94), 0xA0, 0x46, 1.0f, 1.0f);
            *(int *)(*(char **)(arg0 + 0x94) + 0x78) = 0xFF;
            p94 = *(char **)(arg0 + 0x94);
            *(int *)(p94 + 0x18) = *(int *)(p94 + 0x18) | 4;
            p44 = *(char **)(arg0 + 0x44);
            a1 = *(int *)(p44 + 0x20);
            r = *(int *)(p44 + 0x1C) - a1;
            if (r >= 0x32) {
                *(int *)(p44 + 0x20) = *(int *)(p44 + 0x20) + 0x32;
                gl_func_00000000(0x20, 0x32);
                a1 = *(int *)(*(char **)(arg0 + 0x44) + 0x20);
            } else if (r >= 5) {
                *(int *)(p44 + 0x20) = *(int *)(p44 + 0x20) + 5;
                gl_func_00000000(0x20, 5);
                a1 = *(int *)(*(char **)(arg0 + 0x44) + 0x20);
            } else if (r > 0) {
                *(int *)(p44 + 0x20) = *(int *)(p44 + 0x20) + 1;
                gl_func_00000000(0x20, 1);
                a1 = *(int *)(*(char **)(arg0 + 0x44) + 0x20);
            }
            gl_func_00000000(*(int *)(arg0 + 0x94), a1);
        } else {
            p94 = *(char **)(arg0 + 0x94);
            *(int *)(p94 + 0x18) = *(int *)(p94 + 0x18) & ~4;
        }
        bc = *(char **)(arg0 + 0xB8);
        if ((*(int *)(bc + 0x4DC) == 2) && (*(int *)(bc + 0x4F8) == 0)) {
            t1 = *(int *)(arg0 + 0xAC) + 1;
            *(int *)(arg0 + 0xAC) = t1;
            if (t1 & 8) {
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
 * 2026-06-02. */
#ifdef NON_MATCHING
char *timproc_uso_b3_func_000023E4(char *a0) {
    char *s0;
    char *p2;
    char *p3;
    s0 = a0 ? a0 : (char *)gl_func_00000000(108);
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
    gl_func_00000000(s0);
    *(int *)(s0 + 96) = 120;
    *(int *)(s0 + 100) = 161;
    *(int *)(s0 + 104) = 191;
    *(int *)(s0 + 72) = gl_func_00000000(0);
    gl_func_00000000(*(int *)(s0 + 72), s0);
    gl_func_00000000(*(int *)(s0 + 72), ((*(int *)&D_00000000 + 3) << 16) | 1, -1, &D_00000000);
    gl_func_00000000(*(int *)(s0 + 72), ((*(int *)&D_00000000 + 3) << 16) | 6, -1, &D_00000000);
    gl_func_00000000(*(int *)(s0 + 72), ((*(int *)&D_00000000 + 3) << 16) | 7, -1, &D_00000000);
    gl_func_00000000(*(int *)(s0 + 72), ((*(int *)&D_00000000 + 3) << 16) | 4, -1, &D_00000000);
    gl_func_00000000(*(int *)(s0 + 72), ((*(int *)&D_00000000 + 3) << 16) | 3, -1, &D_00000000);
    gl_func_00000000(*(int *)(s0 + 72), ((*(int *)&D_00000000 + 3) << 16) | 2, -1, &D_00000000);
    gl_func_00000000(*(int *)(s0 + 72), ((*(int *)&D_00000000 + 3) << 16) | 5, -1, &D_00000000);
    *(int *)(*(int *)(s0 + 72) + 48) =
        gl_func_00000000(0, &D_00000000, 72, 221, 3, 13);
    gl_func_00000000(*(int *)(s0 + 72));
    gl_func_00000000(*(int *)(s0 + 72), 140);
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
    if (*(int *)((char *)&D_00000000 + 388) == 0 || *(int *)&D_00000000 != 0x17D7) {
        *(int *)(*(int *)(s0 + 72) + 0xD8) = 0;
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
    *(int *)(s0 + 84) = 0;
    *(int *)(s0 + 80) = 0;
    *(int *)(s0 + 48) = 1;
    *(int *)(s0 + 44) = 0;
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
