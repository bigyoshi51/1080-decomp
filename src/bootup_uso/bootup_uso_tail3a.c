#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* CRACKED 2026-05-27 (byte-exact): array-indexing form `((Row28*)base)[i].d`
 * combined with the file's existing `OPT_FLAGS := -O2 -g3` Makefile override
 * (which disables delay-slot fill, leaving the jr-ra delay as nop matching
 * target).
 *
 * The lever was the ARRAY FORM (`((Row28*)(a0+0x84))[idx].d`) per
 * docs/IDO_CODEGEN.md "addu operand order" entry — gives `addu v0, a0, t7`
 * (base-first) instead of the arithmetic form's `addu v0, t7, a0`
 * (idx-first). Verified byte-equal at .o level (all 8 instructions). */
typedef struct { char d[0x28]; } Row10324;
char *func_00010324(a0) char *a0; {
    return ((Row10324*)(a0 + 0x84))[*(int*)(a0 + 0x7C)].d;
}

void func_00010344(void) {
}

#ifdef NON_MATCHING
/* func_0001034C: 125-insn -O0 dispatch with circular-buffer slot reservation.
 * Sibling of recently-matched func_000102A4 (offset-adjacent in bootup_uso).
 *
 * Compiled at -O0 (per `lw $t6, 0x28($sp)` immediate-reload-after-store
 * pattern at offset 0x10 — classic O0 spill-then-reload codegen the IDO -O2
 * file default doesn't produce). To byte-match, this function needs a
 * file-split into bootup_uso_o0_1034C.c with `OPT_FLAGS := -O0`, mirroring
 * the bootup_uso_o0_F1F0/F390/F7F4/FBCC/etc. recipe.
 *
 * Decoded entry block (asm 0x1034C-0x10458, ~50 insns):
 *   if (a0->field_34 < 0xFF) a0->field_34++;
 *   a0->field_38++;
 *   if (a0->field_80 != 0) goto exit;
 *   if (!func_00000000(&D_0, 0x2004)) goto exit;
 *   func_00000000(1);
 *   counter = 0;
 *   if (a0->field_78 <= 0) goto exit;
 *   do {
 *       a0->field_7C--;
 *       if (a0->field_7C < 0) a0->field_7C = a0->field_78 - 1;
 *       slot = (char*)a0 + 0x88 + a0->field_7C * 0x68;
 *       if (*(int*)slot != 0) goto exit;
 *       counter++;
 *   } while (counter < a0->field_78);
 * exit:
 *   ... ~75 more insns remain (post-loop body: slot-fill, dispatch, epilogue).
 *
 * Pattern: circular-buffer reservation — walk backwards through 0x68-byte
 * slots starting from a0->field_7C, find first empty slot, fill it. The
 * 0x68 stride matches the per-slot record size; field_78 is total slots,
 * field_7C is current cursor.
 *
 * Multi-pass: this iteration captures entry-block semantics. Next pass
 * decodes the post-exit body (slot-fill, return path) and considers the
 * file-split for byte-match. */
/* 2026-06-04 RECONSTRUCT via Ghidra 29.7% -> 41.5%: fixed the slot stride
 * (0x68 -> 0x28 = (idx*5)<<3) and added the missing 2nd button block (0x8008,
 * forward-scan increment loop) mirroring the 1st (0x2004, backward decrement).
 * Both loops scan a0->0x78 slots at a0+0x88 (stride 0x28) for the next active
 * one, wrapping a0->0x7c. Residual ~58%: target holds a0 in $a2 where mine
 * spills it to its stack home (-g3 regalloc) + 0x8 frame delta. */
void func_0001034C(int *a0) {
    int counter;
    if (*(int*)((char*)a0 + 0x34) < 0xFF) {
        *(int*)((char*)a0 + 0x34) += 1;
    }
    *(int*)((char*)a0 + 0x38) += 1;
    if (*(int*)((char*)a0 + 0x80) == 0 && func_00000000(&D_00000000, 0x2004) != 0) {
        func_00000000(1);
        counter = 0;
        if (*(int*)((char*)a0 + 0x78) > 0) {
            do {
                *(int*)((char*)a0 + 0x7C) -= 1;
                if (*(int*)((char*)a0 + 0x7C) < 0) {
                    *(int*)((char*)a0 + 0x7C) = *(int*)((char*)a0 + 0x78) - 1;
                }
            } while (*(int*)((char*)a0 + *(int*)((char*)a0 + 0x7C) * 0x28 + 0x88) == 0
                     && (counter++, counter < *(int*)((char*)a0 + 0x78)));
        }
    }
    if (*(int*)((char*)a0 + 0x80) == 0 && func_00000000(&D_00000000, 0x8008) != 0) {
        func_00000000(1);
        counter = 0;
        if (*(int*)((char*)a0 + 0x78) > 0) {
            do {
                *(int*)((char*)a0 + 0x7C) += 1;
                if (*(int*)((char*)a0 + 0x78) <= *(int*)((char*)a0 + 0x7C)) {
                    *(int*)((char*)a0 + 0x7C) = 0;
                }
            } while (*(int*)((char*)a0 + *(int*)((char*)a0 + 0x7C) * 0x28 + 0x88) == 0
                     && (counter++, counter < *(int*)((char*)a0 + 0x78)));
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001034C);
#endif

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

#ifdef NON_MATCHING
/* func_00010AB0 - verified decode, O0-BLOCKED record-append (0xBC,
 * 47 insns). The asm is unmistakably IDO -O0: a0->0x78 index +
 * record-base (idx*0x28) is recomputed from scratch for EVERY field
 * store (no CSE), `or t0,a0,zero` reg-move before the increment, and
 * a redundant `b .L00010B60` to the very next instruction. The C
 * below is logically exact and compiles to this shape at -O0; it is
 * NOT byte-exact at the file's default -O2 (O2 CSEs the index calc).
 *
 * Promotion path (deferred - needs a focused non-loop session):
 * the documented bootup_uso -O0 file-split recipe (cf. commit
 * 067b549f / Makefile lines 60-75): extract into
 * src/bootup_uso/bootup_uso_o0_10AB0.c, add
 *   build/src/bootup_uso/bootup_uso_o0_10AB0.c.o \
 *   build/non_matching/src/bootup_uso/bootup_uso_o0_10AB0.c.o: \
 *       OPT_FLAGS := -O0
 * and a tenshoe.ld (.text) entry at the 0x10AB0 slot. Risk: tail3a
 * is a multi-function blob already split tail3a/_mid/_bot; pulling a
 * mid-file function out requires re-segmenting the containing piece
 * so following addresses don't shift - too address-fragile to do +
 * verify under a 60s loop tick without risking a main-breaking push.
 * Wrapped NM so the exact C is preserved for that session.
 *
 * Struct-typing reference: a0 = container with an embedded array of
 * 0x28-stride records and a current-index counter at a0->0x78 (120).
 * record[i] = a0 + i*0x28; per append: rec->0x88 (136) = 1 (in-use
 * flag), rec->0x8C (140) = (a2 == -1 ? a0->0x78 : a2), rec->0x84
 * (132) = a1, rec->0x90 (144) = a3, then a0->0x78++. Caps: pure -O0
 * codegen-shape (not C-source-reachable at -O2). */
void func_00010AB0(char *a0, int a1, int a2, int a3) {
    *(int *)(a0 + *(int *)(a0 + 0x78) * 0x28 + 0x88) = 1;
    if (a2 == -1) {
        *(int *)(a0 + *(int *)(a0 + 0x78) * 0x28 + 0x8C) =
            *(int *)(a0 + 0x78);
    } else {
        *(int *)(a0 + *(int *)(a0 + 0x78) * 0x28 + 0x8C) = a2;
    }
    *(int *)(a0 + *(int *)(a0 + 0x78) * 0x28 + 0x84) = a1;
    *(int *)(a0 + *(int *)(a0 + 0x78) * 0x28 + 0x90) = a3;
    *(int *)(a0 + 0x78) += 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010AB0);
#endif

/* func_00010B6C (0x10B6C..0x10C8B) split to bootup_uso_o0_10B6C.c on
 * 2026-07-10 and MATCHED there at -O0 (72/72). tail3a now ends at 0x10B6C
 * (TRUNCATE_TEXT 0x848); the 0x10C8C..0x116C7 remainder (func_00010C8C +
 * func_00010FEC, both honest-NM INCLUDE_ASM) moved to
 * bootup_uso_tail3a_10C8C.c, still -O2 -g3. */


/* func_000116C8 (0x116C8..0x117FB) split to bootup_uso_o0_116C8.c on
 * 2026-07-10 and MATCHED there at -O0 (77/77); structural decode retained
 * in git history. */

/* func_000117FC (0x117FC..0x118E3) split to bootup_uso_o0_117FC.c on
 * 2026-07-10 and MATCHED there at -O0 (58/58). The 2026-05-31 note here
 * ("no standard opt level reproduces it, -O0 over-produces") was a
 * standalone-cc false cap on a wrong C body (early-return locals form);
 * the real shape is a fused-|| guard + cfe DAG-share. tail3a TRUNCATE_TEXT
 * reduced 0x1710 -> 0x1628. */

/* func_000118E4 + func_0001195C split out to bootup_uso_o0_118E4.c on
 * 2026-05-14 for -O0 build (func_000118E4 was previously NM-wrapped at
 * tail3a's -O2 -g3 OPT_FLAGS; the body's sp+0x1C/0x20/0x24 spill-and-
 * reload shape is unmistakable -O0 IDO emit). */

/* func_00011A34 split out to bootup_uso_o0_11A34.c on 2026-05-08
 * (verified byte-exact at -O0). The following 11AB4..11C70 gap lives in
 * bootup_uso_tail3a_mid.c as INCLUDE_ASM to keep the .text layout
 * contiguous before the existing 11C70 split.
 *
 * func_00011C70 split out to bootup_uso_o0_11C70.c on 2026-05-07 (verified
 * byte-exact at -O0). func_00011CA4 + func_00011CD8 also moved into that
 * file as INCLUDE_ASM stubs (INCLUDE_ASM is opt-level-independent) so the
 * 11C70..11D40 .o region is contiguous; they migrate to C bodies in
 * future passes when individually verified at -O0.
 * func_00011D40 split out to bootup_uso_o0_11D40.c on 2026-05-07.
 * func_00011D70 onwards split out to bootup_uso_tail3a_bot.c. */
