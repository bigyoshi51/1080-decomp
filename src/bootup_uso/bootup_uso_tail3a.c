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

#ifdef NON_MATCHING
/* func_00010B6C - verified decode, O0-BLOCKED record-append+init
 * (0x120, 72 insns). SAME -O0 family as func_00010AB0 (record at
 * a0 + a0->0x78*0x28, index recomputed from scratch for every field
 * store - the unmistakable IDO -O0 signature); a richer variant
 * that also zeroes rec->0x84 and runs a sub-init call in the
 * a2==-1 arm. Logic-exact below; NOT byte-exact at tail3a's default
 * -O2 (O2 CSEs the index). Promotion = the same bootup_uso -O0
 * file-split, and tail3a is the TRUNCATE_TEXT 3x-compile stitch -
 * see project_1080_o0_split_pending_candidates memo / func_00010AB0
 * NM comment. Deferred from /loop (mid-stitch, address-fragile).
 *
 * Struct-typing reference: a0 = container with embedded 0x28-stride
 * record array + current-index counter at a0->0x78 (120). Per call,
 * rec = a0 + a0->0x78*0x28:
 *   rec->0x88 (136) = 1;                      // in-use flag
 *   if (a2 != -1) rec->0x8C (140) = a2;
 *   else { rec->0x8C = a0->0x78;              //  = own index
 *          rec->0x84 (132) = 0;
 *          func_00000000(&rec->0x94, a1); }   // sub-init region
 *   rec->0x90 (144) = a3;
 *   a0->0x78++;
 * (vs func_00010AB0: that one sets rec->0x84 = a1 unconditionally
 * and has no sub-init call - this is the with-sub-object variant.)
 * Caps: pure -O0 codegen-shape + reloc sub-init, not C-source-
 * reachable at -O2. */
void func_00010B6C(char *a0, int a1, int a2, int a3) {
    *(int *)(a0 + *(int *)(a0 + 0x78) * 0x28 + 0x88) = 1;
    if (a2 != -1) {
        *(int *)(a0 + *(int *)(a0 + 0x78) * 0x28 + 0x8C) = a2;
    } else {
        *(int *)(a0 + *(int *)(a0 + 0x78) * 0x28 + 0x8C) =
            *(int *)(a0 + 0x78);
        *(int *)(a0 + *(int *)(a0 + 0x78) * 0x28 + 0x84) = 0;
        func_00000000(a0 + *(int *)(a0 + 0x78) * 0x28 + 0x94, a1);
    }
    *(int *)(a0 + *(int *)(a0 + 0x78) * 0x28 + 0x90) = a3;
    *(int *)(a0 + 0x78) += 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010B6C);
#endif

/* func_00010C8C: -g3 object constructor (216 insns). Inits arg0's struct
 * fields, builds a temp Vec4-ish stack record (sp6C) passed to a registrar
 * call, allocates two 0x80 sub-objects (->0xC0/->0xC4), then a sub-record
 * (->0x154) whose byte/halfword fields drive 4 callbacks + a global flag.
 *
 * Honestly NM: (1) sp6C.uC loads from the shared FP literal pool (splat
 * misresolved the reloc to .text func_00000C10 @ module-offset 0xC10; see
 * docs/N64_FORENSICS FP-pool fold) and (2) -g3 homed-arg/unfilled-delay
 * codegen. Real C body documents the struct-field semantics; the build
 * path stays INCLUDE_ASM (ROM exact). */
#ifdef NON_MATCHING
extern int *func_000000F0;
extern char D_0000C5D0;
extern char D_0000C5DC;
extern char D_0000C5E4;
extern char D_0000C5F0;
extern float D_FP_POOL_0C10[];

void func_00010C8C(int *arg0, int arg1) {
    struct { int u0; float u4; float u8; float uC; } sp6C;
    int *sp68, *sp84, *p, *c0, *c4, *sub;

    *(int *)((char *)arg0 + 0xC) = (int)&D_0000C5D0;
    *(int *)((char *)arg0 + 0x12C) = arg1;
    sp68 = (int *)func_00000000(0);
    p = (int *)&sp6C;
    if ((p != 0) || (p = (int *)func_00000000(0x10), p != 0)) {
        p[0] = 0;
        *(float *)&p[1] = 0.0f;
        *(float *)&p[2] = 0.0f;
        *(float *)&p[3] = D_FP_POOL_0C10[3];
    }
    func_000000F0 = (int *)func_00000000(0, &D_0000C5DC, 0x10, 0x12C, 0x10, 0x14,
                                         sp6C.u0, sp6C.u4, sp6C.u8, sp6C.uC);
    func_00000000(sp68);
    *(int *)((char *)arg0 + 0x130) = 0;
    *(int *)((char *)arg0 + 0x2C) = 0;
    *(int *)((char *)arg0 + 0x38) = 9;
    *(int *)((char *)arg0 + 0x6C) = -1;
    *(int *)((char *)arg0 + 0x70) = 0;
    *(int *)((char *)arg0 + 0x13C) = 0;
    sp84 = (int *)func_00000000(0);
    func_00000000(0, &D_0000C5E4);
    c0 = (int *)func_00000000(0x80);
    if (c0 != 0) {
        func_00000000(c0, 1);
    }
    *(int *)((char *)arg0 + 0xC0) = (int)c0;
    c4 = (int *)func_00000000(0x80);
    if (c4 != 0) {
        func_00000000(c4, 2);
    }
    *(int *)((char *)arg0 + 0xC4) = (int)c4;
    func_00000000(arg0);
    *(int *)((char *)arg0 + 0x84) = 0;
    *(int *)((char *)arg0 + 0x88) = 1;
    *(int *)((char *)arg0 + 0x18C) = 0;
    *(int *)((char *)arg0 + 0x134) = (int)func_00000000(0);
    *(int *)((char *)arg0 + 0x190) = (int)func_00000000(0, 0);
    *(int *)((char *)arg0 + 0x148) = (int)func_00000000(0);
    sub = (int *)func_00000000(*(int *)((char *)arg0 + 0x148));
    *(int *)((char *)arg0 + 0x154) = (int)sub;
    func_00000000(*(unsigned char *)((char *)sub + 0x12));
    func_00000000(*(unsigned char *)((char *)sub + 0x13));
    func_00000000(*(unsigned char *)((char *)sub + 0x14));
    func_00000000(*(unsigned short *)((char *)sub + 0x4) & 3);
    *(int *)&D_00000000 = (*(unsigned short *)((char *)sub + 0x4) & 4) == 4;
    *(int *)((char *)arg0 + 0x164) = *(int *)*(int *)((char *)arg0 + 0x148);
    *(int *)((char *)arg0 + 0x160) =
        (int)func_00000000(*(int *)((char *)arg0 + 0x164) << 2);
    *(int *)((char *)arg0 + 0x150) = (int)func_00000000(0, &D_0000C5F0);
    func_00000000(sp84);
    func_00000000(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010C8C);
#endif

#ifdef NON_MATCHING
void func_00010FEC(char *arg0, u32 arg1, s32 arg2) {
    char *sp3C;
    char *sp28;
    char *temp_s0;
    char *temp_s0_2;
    char *temp_s0_3;
    char *temp_s0_4;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_3;
    char *temp_v0_4;
    char *temp_v0_5;
    char *temp_v0_6;
    char *temp_v0_7;
    char *temp_v0_8;
    char *var_s2;
    char *var_s2_2;
    char *var_s2_3;
    char *var_s2_4;
    char *var_s2_5;
    char *var_s2_6;
    char *var_s2_7;
    char *var_s2_8;

    *(s32 *)((char *)(arg0) + 0x10) = 0;
    temp_s0 = *(s32 *)((char *)(arg0) + 0x134);
    func_00010324((void *)0x10, temp_s0);
    if (*(s32 *)((char *)(temp_s0) + 0x14) != 0) {
        *(s32 *)((char *)(temp_s0) + 0x4) = 1;
    }
    *(s32 *)((char *)(temp_s0) + 0x14) = 0;
    func_00010324((void *)0x10, arg0);
    if (*(s32 *)((char *)(arg0) + 0x14) != 0) {
        *(s32 *)((char *)(arg0) + 0x4) = 1;
    }
    *(s32 *)((char *)(arg0) + 0x14) = 0;
    temp_s0_2 = *(s32 *)((char *)(arg0) + 0x150);
    func_00010324(arg0 + 0x10, temp_s0_2);
    if (*(s32 *)((char *)(temp_s0_2) + 0x14) != 0) {
        *(s32 *)((char *)(temp_s0_2) + 0x4) = 1;
    }
    *(s32 *)((char *)(temp_s0_2) + 0x14) = arg0;
    func_00010324(arg0);
    *(s32 *)((char *)(arg0) + 0x74) = 0;
    *(s32 *)((char *)(arg0) + 0x78) = 0;
    temp_s0_3 = *(s32 *)((char *)&D_00000000 + 0);
    *(s32 *)((char *)&D_00000000 + 0) = (void *) (temp_s0_3 + 1);
    func_00010324(*(s32 *)((char *)&D_00000000 + 0), 0, temp_s0_3, *(s32 *)((char *)&D_00000000 + arg1 * 4));
    sp3C = func_00010324(*(s32 *)((char *)&D_00000000 + 0));
    if (sp3C != (void *)1) {
        func_00010324(0);
    }
    if (arg1 != *(s32 *)((char *)(arg0) + 0x38)) {
        *(s32 *)((char *)(arg0) + 0x34) = arg1;
        func_00010324(arg0);
        func_00010324(arg0, *(s32 *)((char *)&D_00000000 + (*(s32 *)((char *)&D_00000000 + arg1 * 4)) * 4));
        sp28 = func_00010324((void *)3);
        func_00010324(0, (void *)1);
        if (arg1 < 9U) {
            switch (arg1) {
            case 0:
                temp_v0 = func_00010324((void *)8);
                if (temp_v0 != 0) {
                    var_s2 = temp_v0;
                    if ((var_s2 != 0) || (var_s2 = func_00010324((void *)8), (var_s2 != 0))) {
                        *(s32 *)((char *)(var_s2) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0;
                break;
            case 1:
                temp_v0_2 = func_00010324((void *)8);
                if (temp_v0_2 != 0) {
                    var_s2_2 = temp_v0_2;
                    if ((var_s2_2 != 0) || (var_s2_2 = func_00010324((void *)8), (var_s2_2 != 0))) {
                        *(s32 *)((char *)(var_s2_2) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_2) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_2;
                break;
            case 3:
                temp_v0_3 = func_00010324((void *)0xC);
                if (temp_v0_3 != 0) {
                    var_s2_3 = temp_v0_3;
                    if ((var_s2_3 != 0) || (var_s2_3 = func_00010324((void *)8), (var_s2_3 != 0))) {
                        *(s32 *)((char *)(var_s2_3) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_3) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_3;
                break;
            case 2:
                temp_v0_4 = func_00010324((void *)0xC);
                if (temp_v0_4 != 0) {
                    var_s2_4 = temp_v0_4;
                    if ((var_s2_4 != 0) || (var_s2_4 = func_00010324((void *)8), (var_s2_4 != 0))) {
                        *(s32 *)((char *)(var_s2_4) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_4) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_4;
                break;
            case 4:
                temp_v0_5 = func_00010324((void *)8);
                if (temp_v0_5 != 0) {
                    var_s2_5 = temp_v0_5;
                    if ((var_s2_5 != 0) || (var_s2_5 = func_00010324((void *)8), (var_s2_5 != 0))) {
                        *(s32 *)((char *)(var_s2_5) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_5) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_5;
                break;
            case 5:
                temp_v0_6 = func_00010324((void *)0xC);
                if (temp_v0_6 != 0) {
                    var_s2_6 = temp_v0_6;
                    if ((var_s2_6 != 0) || (var_s2_6 = func_00010324((void *)8), (var_s2_6 != 0))) {
                        *(s32 *)((char *)(var_s2_6) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_6) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_6;
                break;
            case 6:
                temp_v0_7 = func_00010324((void *)8);
                if (temp_v0_7 != 0) {
                    var_s2_7 = temp_v0_7;
                    if ((var_s2_7 != 0) || (var_s2_7 = func_00010324((void *)8), (var_s2_7 != 0))) {
                        *(s32 *)((char *)(var_s2_7) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_7) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_7;
                break;
            case 7:
                temp_v0_8 = func_00010324((void *)8);
                if (temp_v0_8 != 0) {
                    var_s2_8 = temp_v0_8;
                    if ((var_s2_8 != 0) || (var_s2_8 = func_00010324((void *)8), (var_s2_8 != 0))) {
                        *(s32 *)((char *)(var_s2_8) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_8) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_8;
                break;
            }
        }
        func_00010324(0, 0);
        func_00010324(sp28);
    }
    temp_s0_4 = *(s32 *)((char *)(*(s32 *)((char *)(arg0) + 0x30)) + 0x4);
    ((void (*)())*(s32 *)((char *)(temp_s0_4) + 0xC))(*(s32 *)((char *)(temp_s0_4) + 0x8) + *(s32 *)((char *)(arg0) + 0x30), arg2);
    *(s32 *)((char *)(arg0) + 0x38) = arg1;
    func_00010324();
    func_00010324(*(s32 *)((char *)(*(s32 *)((char *)(arg0) + 0x134)) + 0x114), *(s32 *)((char *)&D_00000000 + 0));
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010FEC);
#endif

/* func_000116C8 - verified structural decode (0x134, 77 insns,
 * subsystem init/teardown orchestrator).
 *   void func_000116C8(void) {
 *       reloc(&D_a);  reloc(&D_b);
 *       *(int*)&D_c = 0;
 *       reloc(1);
 *       reloc(&D_0000C624);
 *       reloc(&D_d);
 *       reloc();
 *       reloc(&D_0000C65C);
 *       reloc(&D_e, *(int*)(func_00000008 + 0x2C),
 *                   *(int*)(func_00000008 + 0x38));
 *       g = *(void**)&D_root;
 *       v = g->0x28;
 *       (*(fn)v->0x14)((s16)v->0x10 + g);         // vtable dispatch
 *       h = alloc(0xC);                            // reloc(0xC)
 *       if (h != 0) {
 *           h->0x0 = 8;
 *           g = *(void**)&D_root;
 *           v = g->0x28;
 *           (*(fn)v->0x34)((s16)v->0x30 + g, &local);  // dispatch 2
 *           reloc(&D_0000C694);
 *       }
 *   }
 * (reloc = func_00000000.) Struct-typing reference: a fixed init
 * sequence of ~10 reloc steps with datum args D_0000C624 / C65C /
 * C694 (config/msg blocks) and a global cleared at &D_c;
 * func_00000008+0x2C / +0x38 supply two args to one step. g =
 * *(&D_root) global root, g->0x28 (40) vtable ptr exercised TWICE
 * via the engine-wide obj-0x28 dispatch idiom - 0x14/0x10 variant
 * (fn@0x14, s16 base-adjust@0x10) then 0x34/0x30 variant (fn@0x34,
 * s16@0x30) with an extra stack-local arg. alloc(0xC) handle h:
 * h->0x0 (0) = 8 (a type/kind tag). NOTE: this file
 * (bootup_uso_tail3a.c) is the TRUNCATE_TEXT 3x-compile stitch
 * (Makefile L85-100) - C-matching needs that offset re-tune too.
 * Caps <80: ~10 func_00000000 reloc + 2 obj-0x28 vtable jalr +
 * multi-&D + cross-symbol-ref + the stitch. Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000116C8)();
void func_000116C8(void) {
    s32 sp24;
    s32 *var_s0;
    char *temp_s0;
    char *temp_s0_2;

    func_00010324(0);
    func_00010324(0);
    *(int*)&D_00000000 = 0;
    func_00010324(1);
    func_00010324(0);
    func_00010324(0);
    func_00010324();
    func_00010324(0);
    func_00010324(0, (*(s32*)((char*)&D_00000000 + 0x2C)), (*(s32*)((char*)&D_00000000 + 0x38)));
    temp_s0 = (*(char**)((char*)&D_00000000 + 0x28));
    ((GP_000116C8)FW(temp_s0, 0x14))(FW(temp_s0, 0x10));
    var_s0 = &sp24;
    if ((var_s0 != 0) || (var_s0 = func_00010324(0xC), (var_s0 != 0))) {
        *var_s0 = 8;
    }
    temp_s0_2 = (*(char**)((char*)&D_00000000 + 0x28));
    ((GP_000116C8)FW(temp_s0_2, 0x34))(FW(temp_s0_2, 0x30), &sp24);
    func_00010324(0);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000116C8);
#endif

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
