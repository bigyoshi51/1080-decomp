#include "common.h"

extern int func_00000000();
extern char *func_00010324();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

/* Mid piece of the original bootup_uso_tail3a.c, carved 2026-07-10 so the
 * -O0 islands on either side (o0_1034C.c before, o0_10AB0.c after) can build
 * at -O0. Holds 0x10540..0x10AB0: func_00010540 (honest-NM INCLUDE_ASM,
 * itself an -O0 target -- see wrap doc) + the two tiny matched -O2 -g3
 * functions func_00010A9C / func_00010AA8. */

#ifdef NON_MATCHING
/* func_00010540 - STRUCTURAL PASS (big-swing 2026-06-02).
 * bootup_uso element/sprite render-loop, 0x55C (343 insns). Clean: no
 * folded-pool refs, single named callee func_00010324 (a draw/transform
 * primitive called with 1..4 args -> called through a cast to bypass its
 * narrow 1-arg prototype; still a direct jal).
 *
 * MATCH BLOCKER = OPT LEVEL: target is plain -O0. tail3a.c is -O2 -g3,
 * which register-caches -> only ~18% vs target 343. Logic decoded & now
 * type-corrected against the -O0 asm (see below).
 *
 * -O0 LAND SPEC (do as a focused tick): split into
 * src/bootup_uso/bootup_uso_o0_10540.c, OPT_FLAGS := -O0, and split the
 * tail3a linker .o 3-ways (tail3a-top {10324,10344,1034C} | o0_10540 |
 * tail3a-rest {10A9C..117FC}); recompute each TRUNCATE_TEXT empirically
 * (current whole-file TRUNCATE = 0x1710; o0_10540 .text = 0x55C). The -O0
 * stack frame is -0x30: ra@0x1C, a0@0x30 (incoming-arg shadow, reloaded
 * every access), s0@0x18 (holds the `node` return across the middle call),
 * loop i@0x2C-ish... pos@0x28. KEY type facts now baked into the body:
 *   - field copies unk5C..68 -> unk3C..48 (and unk4C..58) are INT (lw/sw).
 *   - unk70 is a FLOAT truncated to int then re-floated: (float)(int)f70.
 *   - RGB halving is div.s by 2.0f (lui 0x4000), per-component, base ptr
 *     recomputed each store.
 *   - the 4-field copy is a single 16-byte STRUCT assignment (loads base
 *     once); separate per-field stores reload the base and won't match.
 * 2026-06-02 LAND ATTEMPT (validated standalone -O0, this body): reaches
 * 364 insns vs target 343, BUT ~270 lines still differ -- pervasive -O0
 * operand-eval-order + temp-register divergence, because macro access
 * `*(int*)((char*)arg0+off)` evaluates the address before the local, while
 * the target (compiled from TYPED-STRUCT C) loads the local first. Closing
 * it needs a full typed-struct refactor (define the ~0x28-stride element +
 * parent struct so accesses are p->field) PLUS residual regalloc grinding.
 * That's a multi-hour focused task, NOT a loop tick. Standalone harness:
 * compile this body with `cc ... -O0` and diff via disasm-func.py --obj.
 * 2026-06-02 TICK-12 PROGRESS: typed-struct body (Obj + Quad g3C/g4C/g5C
 * 16-byte int groups copied by struct-assignment + Elem[0x28] array at
 * +0x84 + Node for the unk30 callee return) gets the STRUCTURE right
 * (int lw/sw copy w/ single base; element addressing). Remaining ~250
 * diffs are pure -O0 TEMP-REGISTER NUMBERING (t0 vs t1 ...) that cascade
 * from the FIRST divergence: `if (i != arg0->unk7C)` -- IDO evaluates the
 * complex operand (arg0->unk7C, 2 loads) before the simple local i, so it
 * emits beq(unk7C,i); target loads i first -> beq(i,unk7C). Must be fixed
 * top-down (each fix realigns downstream regs). A dedicated session should
 * start from the tick-12 typed-struct body and grind the cascade.
 * NOTE: only commit the -O0 split if it byte-matches EXACTLY -- it makes
 * the compiled C the default build path, so a non-match would corrupt the
 * segment (unlike this NM wrap, whose #else INCLUDE_ASM stays byte-exact).
 * See project_1080_o0_split_pending_candidates.
 *
 * Shape: for each of arg0->unk78 elements (skipping the "current" index
 * arg0->unk7C), compute an x-position from unk70 + i*unk74, copy a
 * color/transform quad (unk5C..unk68 -> unk3C..unk48), optionally halve
 * the RGB when the element's unk88 flag is 0, then draw via func_00010324
 * (path A when the element has a unk84 payload, else path B at
 * element+0x94). After the loop the same is done once for the current
 * index (unk7C) using unk4C..unk58, gated by arg0->unk38 & 8. */
#define FI(p, o) (*(int *)((char *)(p) + (o)))
#define FF(p, o) (*(float *)((char *)(p) + (o)))
#define FP(p, o) (*(void **)((char *)(p) + (o)))
#define EL(i) ((char *)arg0 + (i) * 0x28)

typedef int (*F324)();

void func_00010540(void *arg0) {
    int i;
    int pos;
    void *node;

    if (FP(arg0, 0x34) != NULL) {
        i = 0;
        if (FI(arg0, 0x78) > 0) {
            do {
                if (i != FI(arg0, 0x7C)) {
                    pos = (int)((float)(int)FF(arg0, 0x70) + (float)i * FF(arg0, 0x74));
                    FI(arg0, 0x3C) = FI(arg0, 0x5C);
                    FI(arg0, 0x40) = FI(arg0, 0x60);
                    FI(arg0, 0x44) = FI(arg0, 0x64);
                    FI(arg0, 0x48) = FI(arg0, 0x68);
                    if (FI(EL(i), 0x88) == 0) {
                        FF(arg0, 0x3C) = FF(arg0, 0x3C) / 2.0f;
                        FF(arg0, 0x40) = FF(arg0, 0x40) / 2.0f;
                        FF(arg0, 0x44) = FF(arg0, 0x44) / 2.0f;
                    }
                    if (FP(EL(i), 0x84) != NULL) {
                        ((F324)func_00010324)(FP(arg0, 0x30));
                        ((F324)func_00010324)(FP(arg0, 0x30), FP(arg0, 0x34), (char *)arg0 + 0x3C, 0);
                        node = FP(arg0, 0x30);
                        ((F324)func_00010324)(node,
                            ((F324)func_00010324)(FP(arg0, 0x30), FI(arg0, 0x6C), FP(EL(i), 0x84)),
                            pos - FI(node, 0x10) / 2, FP(EL(i), 0x84));
                    } else {
                        ((F324)func_00010324)((char *)EL(i) + 0x94);
                        ((F324)func_00010324)((char *)EL(i) + 0x94, FP(arg0, 0x34), (char *)arg0 + 0x3C, 0);
                        ((F324)func_00010324)((char *)EL(i) + 0x94, FI(arg0, 0x6C), pos, 3);
                    }
                }
                i++;
            } while (i < FI(arg0, 0x78));
        }
        pos = (int)((float)(int)FF(arg0, 0x70) + (float)FI(arg0, 0x7C) * FF(arg0, 0x74));
        FI(arg0, 0x3C) = FI(arg0, 0x4C);
        FI(arg0, 0x40) = FI(arg0, 0x50);
        FI(arg0, 0x44) = FI(arg0, 0x54);
        FI(arg0, 0x48) = FI(arg0, 0x58);
        if (FI(EL(i), 0x88) == 0) {
            FF(arg0, 0x3C) = FF(arg0, 0x3C) / 2.0f;
            FF(arg0, 0x40) = FF(arg0, 0x40) / 2.0f;
            FF(arg0, 0x44) = FF(arg0, 0x44) / 2.0f;
        }
        if (FI(arg0, 0x38) & 8) {
            if (FP(EL(FI(arg0, 0x7C)), 0x84) != NULL) {
                ((F324)func_00010324)(FP(arg0, 0x30));
                ((F324)func_00010324)(FP(arg0, 0x30), FP(arg0, 0x34), (char *)arg0 + 0x3C, FI(arg0, 0x38));
                node = FP(arg0, 0x30);
                ((F324)func_00010324)(node,
                    ((F324)func_00010324)(FP(arg0, 0x30), FI(arg0, 0x6C), FP(EL(FI(arg0, 0x7C)), 0x84)),
                    pos - FI(node, 0x10) / 2, FP(EL(FI(arg0, 0x7C)), 0x84));
            } else {
                i = FI(arg0, 0x7C);
                ((F324)func_00010324)((char *)EL(i) + 0x94);
                ((F324)func_00010324)((char *)EL(i) + 0x94, FP(arg0, 0x34), (char *)arg0 + 0x3C, FI(arg0, 0x38));
                ((F324)func_00010324)((char *)EL(i) + 0x94, FI(arg0, 0x6C), pos, 3);
            }
        }
    }
}
#undef FI
#undef FF
#undef FP
#undef EL
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010540);
#endif

void func_00010A9C(int *a0) {
    *(int*)((char*)a0 + 0x78) = 0;
}

void func_00010AA8(void) {
}
