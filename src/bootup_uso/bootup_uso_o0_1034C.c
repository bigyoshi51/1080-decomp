#include "common.h"

extern int func_00000000();
extern char D_00000000;

/* func_0001034C: -O0 island split out of bootup_uso_tail3a.c on 2026-07-10
 * and MATCHED at -O0 (125/125 target words; the 3 trailing pad words are
 * clipped by TRUNCATE_TEXT 0x1F4). Same carve recipe as o0_10B6C / o0_116C8.
 *
 * Button-scan cursor advance: on 0x2004 (back) walk the 0x28-stride record
 * ring at a0+0x88 backwards from cursor a0->0x7C to the previous active
 * record; on 0x8008 (forward) walk forwards. a0->0x34 = saturating-at-0xFF
 * counter, a0->0x38 = frame counter, a0->0x78 = ring size, a0->0x80 = lock.
 *
 * -O0 levers that produced the exact bytes:
 *  - `register char *s` (colors s0) used for the three RMW sites
 *    (0x34++, 0x38++, 0x7C--/++). Being the only register var it still
 *    reserves a dead home slot -> frame 0x28 with s0 saved at 0x18.
 *  - the 0x34 site pre-adds the offset (s = a0 + 0x34; *(int*)s += 1)
 *    while the others fold it (s = a0; *(int*)(s + 0x38) += 1) -- exactly
 *    reproduces the target's addiu-s0 vs folded-displacement split.
 *  - slot probe via ARRAY FORM ((Row34C*)(a0 + 0x88))[idx].v: gives the
 *    base-first `addu t6, t3, t5` + folded 0x88 displacement; the pointer-
 *    arithmetic spelling emits offset-first addu (9-word diff cascade).
 *  - `break` inside the do-while emits the target's b-to-merge; the
 *    while condition `++counter < a0->0x78` gives pre-inc slt operand order.
 *  - wrap fixups written as plain a0-based compares/stores (one home reload
 *    DAG-shared across both derefs of the same expression). */
typedef struct { int v; char pad[0x24]; } Row34C;

void func_0001034C(char *a0) {
    int counter;
    register char *s;

    if (*(int*)(a0 + 0x34) < 0xFF) {
        s = a0 + 0x34;
        *(int*)s += 1;
    }
    s = a0;
    *(int*)(s + 0x38) += 1;
    if (*(int*)(a0 + 0x80) == 0) {
        if (func_00000000(&D_00000000, 0x2004) != 0) {
            func_00000000(1);
            counter = 0;
            if (*(int*)(a0 + 0x78) > 0) {
                do {
                    s = a0;
                    *(int*)(s + 0x7C) -= 1;
                    if (*(int*)(a0 + 0x7C) < 0) {
                        *(int*)(a0 + 0x7C) = *(int*)(a0 + 0x78) - 1;
                    }
                    if (((Row34C*)(a0 + 0x88))[*(int*)(a0 + 0x7C)].v != 0) {
                        break;
                    }
                } while (++counter < *(int*)(a0 + 0x78));
            }
        }
    }
    if (*(int*)(a0 + 0x80) == 0) {
        if (func_00000000(&D_00000000, 0x8008) != 0) {
            func_00000000(1);
            counter = 0;
            if (*(int*)(a0 + 0x78) > 0) {
                do {
                    s = a0;
                    *(int*)(s + 0x7C) += 1;
                    if (*(int*)(a0 + 0x7C) >= *(int*)(a0 + 0x78)) {
                        *(int*)(a0 + 0x7C) = 0;
                    }
                    if (((Row34C*)(a0 + 0x88))[*(int*)(a0 + 0x7C)].v != 0) {
                        break;
                    }
                } while (++counter < *(int*)(a0 + 0x78));
            }
        }
    }
}
