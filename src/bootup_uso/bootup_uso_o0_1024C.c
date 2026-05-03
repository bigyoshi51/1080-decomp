#include "common.h"

/* -O0 empty stub; see feedback_ido_o0_empty_stub.md + feedback_non_aligned_o_split.md. */

void func_0001024C(int a0) {}

/* func_00010260 (0x44 bytes / 17 insns at -O0) — added 2026-05-03.
 * Extracted from bootup_uso_tail2.c (which is -O2 -g3); the function shows
 * standard -O0 signals (a0 spill+reload at sp+0x18, b +1 dead branch,
 * unfilled jal delays). */
extern int func_00000000();
void func_00010260(int *a0) {
    func_00000000(a0);
    a0[0x80/4] = 0;
    func_00000000(a0);
}
