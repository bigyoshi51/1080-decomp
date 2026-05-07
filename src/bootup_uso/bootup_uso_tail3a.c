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
extern int D_00000000;
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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010AB0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010B6C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010C8C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010FEC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000116C8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000117FC);

#ifdef NON_MATCHING
/* func_000118E4: 30-insn linked-list-prepend allocator wrapper.
 * O0-compiled emit shape (lots of sp+0x1C/0x20/0x24 reload via stack,
 * out-of-frame caller-arg-slot saves of a0/a1, no register promotion).
 *
 * Decoded structure:
 *   void func_000118E4(int *head_holder, int data) {
 *       int *node = alloc(8);            // alloc 8 bytes (next, data)
 *       node[1] = head_holder->[0x130];  // node->next = old head
 *       head_holder->[0x130] = node;     // head = node
 *       node[0] = data;                  // node->data = data
 *       init(&D_00000000, node[0]);      // init/notify with data
 *   }
 *
 * The 4-byte alloc-result + a0/a1 spill-and-reload pattern (sp+0x1C =
 * v0, sp+0x20 = a0, sp+0x24 = a1, with 4 reloads of sp+0x1C across the
 * body) is unmistakable -O0 IDO emit.
 *
 * BLOCKED: tail3a.c.o is -O2 -g3. Promotion requires an -O0 file-split
 * (per kernel's project_o1o2_split.md model — create sibling .c with
 * -O0 OPT_FLAGS, move the function, update linker script). Multi-tick
 * infra change. */
extern int func_00000000();
void func_000118E4(int *head_holder, int data) {
    int *node = (int*)func_00000000(8);
    node[1] = head_holder[0x130 / 4];
    head_holder[0x130 / 4] = (int)node;
    node[0] = data;
    func_00000000(&D_00000000, node[0]);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000118E4);
#endif

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001195C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011A34);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011AB4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011B5C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011BF0);

/* func_00011C70 split out to bootup_uso_o0_11C70.c on 2026-05-07 (verified
 * byte-exact at -O0). func_00011CA4 + func_00011CD8 also moved into that
 * file as INCLUDE_ASM stubs (INCLUDE_ASM is opt-level-independent) so the
 * 11C70..11D40 .o region is contiguous; they migrate to C bodies in
 * future passes when individually verified at -O0.
 * func_00011D40 split out to bootup_uso_o0_11D40.c on 2026-05-07.
 * func_00011D70 onwards split out to bootup_uso_tail3a_bot.c. */
