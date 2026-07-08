#include "common.h"

/* -O1 -g3 donor for gl_func_0006AF0C — 14-insn singly-linked-list unlink:
 * walk from head a3 looking for node a1; when found, store a1->next into the
 * predecessor link slot *a2 (a2 trails one node behind) and stop.
 * PROVEN EXACT 14/14 at -O1 -g3 (2026-07-07 standalone IDO 7.1 probe).
 * post1b builds -O2, where this shape is the sp-8-empty-frame/bnel/copy-prop
 * cap; the target is an -O1 -g3 island inside game_libs_post1b (region survey
 * 2026-07-08: NO branch-likely anywhere in 0x6A09C..0x6BAD4). Levers:
 *   (1) `int pad;` unused local = the addiu sp,-8/+8 bracket, zero insns;
 *   (2) `if (0) a0_unused = 0;` dead overwrite kills IDO -O1's unused-arg
 *       home store (sw a0,8(sp)) with zero emission; -g3 pins the prologue
 *       addiu ahead of the beq, leaving the target's nop delay.
 * Reloc-free body — spliced into game_libs_post1b.c.o via REPLACE_FUNC_BODY
 * (real -O1 -g3 compiler output, not instruction-forcing). */
void gl_func_0006AF0C(int a0_unused, int *a1, int *a2, int *a3) {
    int pad;
    if (0) a0_unused = 0;
    if (a3 != 0) {
        do {
            if (a3 == a1) {
                *a2 = *a1;
                break;
            }
            a2 = a3;
            a3 = *(int **)a2;
        } while (a3 != 0);
    }
}
