#include "common.h"

extern int func_00000000();
extern char D_00000000;

/* -O0 sub-file split out of bootup_uso_tail3a.c on 2026-05-14. Holds the
 * 0x118E4..0x1195B -O0 cluster: 118E4 (linked-list-prepend allocator) +
 * 1195C (INCLUDE_ASM stub — opt-level-independent; migrates to C body in
 * future pass when verified at -O0).
 *
 * Pattern: minimal -O0 frame, sp+0x1C/0x20/0x24 spill-and-reload of
 * alloc-result + a0/a1, no register promotion. */

/* func_000118E4: 30-insn linked-list-prepend allocator wrapper.
 * alloc(8); new->next = head_holder->[0x130]; head_holder->[0x130] = new;
 * new->data = arg1; notify(&D_0, new->data). */
void func_000118E4(int *head_holder, int data) {
    int *node = (int*)func_00000000(8);
    node[1] = head_holder[0x130 / 4];
    head_holder[0x130 / 4] = (int)node;
    node[0] = data;
    func_00000000(&D_00000000, node[0]);
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001195C);
