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
char *func_00010324(char *a0) {
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
void func_0001034C(int *a0) {
    int counter;
    char *slot;
    if (*(int*)((char*)a0 + 0x34) < 0xFF) {
        *(int*)((char*)a0 + 0x34) += 1;
    }
    *(int*)((char*)a0 + 0x38) += 1;
    if (*(int*)((char*)a0 + 0x80) != 0) goto exit;
    if (!func_00000000(&D_00000000, 0x2004)) goto exit;
    func_00000000(1);
    counter = 0;
    if (*(int*)((char*)a0 + 0x78) <= 0) goto exit;
    do {
        *(int*)((char*)a0 + 0x7C) -= 1;
        if (*(int*)((char*)a0 + 0x7C) < 0) {
            *(int*)((char*)a0 + 0x7C) = *(int*)((char*)a0 + 0x78) - 1;
        }
        slot = (char*)a0 + 0x88 + *(int*)((char*)a0 + 0x7C) * 0x68;
        if (*(int*)slot != 0) goto exit;
        counter++;
    } while (counter < *(int*)((char*)a0 + 0x78));
exit:
    /* TODO: ~75 more insns at 0x1045C+ — slot-fill, dispatch, epilogue. */
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001034C);
#endif

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010540);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010FEC);

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
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000116C8);

/* func_000117FC - verified structural decode (0xE8, 58 insns,
 * handle replace-with-validation + re-init).
 * Struct-typing reference: a0->0x2C (44) = the live handle/resource
 * slot (NULL = nothing to replace). a1 = the candidate replacement.
 * validate(a1, old) (func_00000000) gates the swap; on success the
 * old handle is freed (func_00000000(&D, old)), a fresh resource is
 * built via the reloc init sequence (two func_00000000(3) calls -
 * likely alloc/type-3 ctor - then three &D registrations with
 * args 1 / a1 / 0, then a finalize on the new handle h), and the
 * slot is updated to a1. NOTE: this file (bootup_uso_tail3a.c) is
 * the TRUNCATE_TEXT 3x-compile stitch (Makefile L85-100) - any
 * future C match must also respect that offset tuning, not just the
 * reloc caps. Caps <80: ~10x reloc calls + multiple &D relocs +
 * the tail3a TRUNCATE_TEXT stitch. INCLUDE_ASM remains build path.
 * 2026-05-31: the target has UNFILLED jal delay slots (8/8 nop) while this -O2 -g3
 * file FILLS them (compiler reorg). HOWEVER — CORRECTION: this is NOT a clean
 * -O0/-g flag fix. Standalone-cc of the C body byte-compares vs expected (232B):
 *   -O0 -> 256B (spills t7, bigger frame), -O2 -g2/-g1/-g -> 224B, -O2 -> 176B.
 * NONE match 232B. So the residual is more than delay-slot filling: the frame
 * size + ~2 insns + the C-body structure all differ, AND no standard opt/-g level
 * reproduces it. (Standalone-cc can false-cap vs full-TU, so the exact flag is not
 * proven, but -O0 over-produces, so a plain -O0 split is NOT the answer.) Genuine
 * unverified cap — needs deeper per-fn RE (exact flag + C-body match), not a quick
 * split. INCLUDE_ASM remains build path. */
#ifdef NON_MATCHING
void func_000117FC(char *a0, void *a1) {
    void *old = *(void**)(a0 + 0x2C);
    void *h;
    if (old == 0) return;
    if (func_00000000(a1, old) == 0) return;
    if (*(void**)(a0 + 0x2C) != 0)
        func_00000000(&D_00000000, *(void**)(a0 + 0x2C));
    func_00000000(3);
    h = (void*)func_00000000(3);
    func_00000000(&D_00000000, 1);
    func_00000000(&D_00000000, a1);
    func_00000000(&D_00000000, 0);
    func_00000000(h);
    *(void**)(a0 + 0x2C) = a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000117FC);
#endif

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
