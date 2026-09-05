#include "common.h"

extern int func_00000000();
extern char D_00000000;

/* bootup_uso_o0_11E00.c (formerly bootup_uso_tail3a_bot_11DF8.c, the tail slice
 * of the 2026-07-10 tail3a_bot carve; renamed + moved to -O0 2026-09-05).
 * Holds the func_00011E00 / func_00011ED4 / func_00011FA8 -O0 triplet: three
 * 53-word "find first slot whose mask word has an a1 bit set" leaves that differ
 * only in the slot mask offset (0x18 / 0x10 / 0x1C). The old -O2 -g3 setting was
 * a leftover of the "adjacent empty stub blocks the -O0 move" note: that 8-byte
 * "func_00011DF8" stub was func_00011DBC's dead -O0 `$exit` pair (absorbed into
 * o0_11DBC.c), and the 1207C/12090 fall-off tail is now o0_1207C.c, so nothing
 * blocks -O0 here. TRUNCATE_TEXT 0x27C = 3 x 0xD4 (INCLUDE_ASM path). */

#ifdef NON_MATCHING
/* func_00011E00: 53-word -O0 leaf, "first slot whose mask word has an a1 bit":
 *   if (a0->[0x18C] != 0) return 0;
 *   if (a0->[0x128] == -1) { for (i = 0; i < a0->[0x120]; i++)
 *       if (a0->slot[i]->[0x18] & a1) return 1 << i;   return 0; }
 *   if (a0->slot[a0->[0x128]]->[0x18] & a1) return 1 << a0->[0x128];
 *   return 0;
 * (slot[] = a0 + 0xE0 + 4*i; idx == -1 means scan all slots).
 *
 * 2026-09-05: unit moved to -O0 (was -O2 -g3 with a 41-word emit, 6.58%);
 * body = the 2026-07-10 w50 shape (register params = unhomed a0/a1, leaf
 * register local p colors $a2, outer ==0 nest, no-else fallthrough check arm,
 * goto ret0 = the single b to the shared return-0). In-tree -O0 emit is
 * 55 words, words 0x00..0xC4 byte-exact, fuzzy 96.23%.
 * RESIDUAL (exactly the -O0 return-value DEAD-DOUBLE-B toolchain gap,
 * docs/IDO_CODEGEN.md#feedback-ido-o0-return-value-dead-double-b): our ugen
 * emits a second dead `b epi; nop` after ret0's own `b epi; nop` (the
 * closing-brace marker; uopt would elide it but -O0 never runs uopt), so the
 * epilogue sits at +0xD0 instead of +0xC8 and the three `b epi` offsets at
 * 0x5C/0xB4/0xC0 read +0x1c/+0x06/+0x03 instead of +0x1a/+0x04/+0x01. The
 * pair is BEFORE the epilogue, so no TRUNCATE can clip it. Re-probed here:
 * K&R params, trailing `for(;;);`, `if (1) return 0;`, trailing `goto ret0;`
 * -- same or worse (each dead statement adds its own branch). Honest NM. */
int func_00011E00(register int *a0, register int a1) {
    int i;
    register int *p;
    if (a0[0x18C/4] == 0) {
        if (a0[0x128/4] == -1) {
            i = 0;
            if (a0[0x120/4] > 0) do {
                p = (int*)a0[0xE0/4 + i];
                if (p[0x18/4] & a1) return 1 << i;
            } while (++i < a0[0x120/4]);
            goto ret0;
        }
        p = (int*)a0[0xE0/4 + a0[0x128/4]];
        if (p[0x18/4] & a1) return 1 << a0[0x128/4];
    }
ret0:
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011E00);
#endif

#ifdef NON_MATCHING
/* func_00011ED4: byte-identical sibling of func_00011E00 except the mask word
 * is p->[0x10] (lw offset 0x10). Same -O0 body, same 96.23% / dead-double-b
 * residual (see func_00011E00's comment). */
int func_00011ED4(register int *a0, register int a1) {
    int i;
    register int *p;
    if (a0[0x18C/4] == 0) {
        if (a0[0x128/4] == -1) {
            i = 0;
            if (a0[0x120/4] > 0) do {
                p = (int*)a0[0xE0/4 + i];
                if (p[0x10/4] & a1) return 1 << i;
            } while (++i < a0[0x120/4]);
            goto ret0;
        }
        p = (int*)a0[0xE0/4 + a0[0x128/4]];
        if (p[0x10/4] & a1) return 1 << a0[0x128/4];
    }
ret0:
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011ED4);
#endif

#ifdef NON_MATCHING
/* func_00011FA8: byte-identical sibling of func_00011E00 except the mask word
 * is p->[0x1C] (lw offset 0x1C). Same -O0 body, same 96.23% / dead-double-b
 * residual (see func_00011E00's comment). */
int func_00011FA8(register int *a0, register int a1) {
    int i;
    register int *p;
    if (a0[0x18C/4] == 0) {
        if (a0[0x128/4] == -1) {
            i = 0;
            if (a0[0x120/4] > 0) do {
                p = (int*)a0[0xE0/4 + i];
                if (p[0x1C/4] & a1) return 1 << i;
            } while (++i < a0[0x120/4]);
            goto ret0;
        }
        p = (int*)a0[0xE0/4 + a0[0x128/4]];
        if (p[0x1C/4] & a1) return 1 << a0[0x128/4];
    }
ret0:
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011FA8);
#endif
