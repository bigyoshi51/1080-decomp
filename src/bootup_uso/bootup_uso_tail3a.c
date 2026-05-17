#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* Array-indexing utility: return a0 + a0->field_7C * 0x28 + 0x84.
 * 7/8 NM cap structural (IDO -O2 fills jr-ra delay slot with addiu,
 * target had unfilled). Promoted to exact via INSN_PATCH at offsets
 * 0x10/0x14 (Makefile entry, ports the 2-word patch from agent-b). */
char *func_00010324(char *a0) {
    return a0 + *(int*)(a0 + 0x7C) * 0x28 + 0x84;
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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010B6C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010C8C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010FEC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000116C8);

/* func_000117FC - verified structural decode (0xE8, 58 insns,
 * handle replace-with-validation + re-init).
 *   void func_000117FC(St *a0, void *a1) {
 *       old = a0->0x2C;
 *       if (old == 0) return;
 *       if (validate(a1, old) == 0) return;       // func_00000000
 *       if (a0->0x2C != 0)
 *           reloc_free(&D_x, a0->0x2C);           // tear down old
 *       reloc_a(3);
 *       h = reloc_b(3);                           // -> sp+0x1C
 *       reloc_c(&D_y, 1);
 *       reloc_c(&D_z, a1);
 *       reloc_c(&D_w, 0);
 *       reloc_finalize(h);
 *       a0->0x2C = a1;                            // commit new handle
 *   }
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
 * reloc caps. Caps <80: ~10x func_00000000 reloc calls + multiple
 * &D relocs + the tail3a TRUNCATE_TEXT stitch. Full body
 * INCLUDE_ASM-preserved (.s = source of truth). INCLUDE_ASM (no
 * episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000117FC);

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
