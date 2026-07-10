#include "common.h"

/* func_00010AB0: -O0 island split out of bootup_uso_tail3a.c on 2026-07-10
 * and MATCHED at -O0 (47/47 target words; 1 trailing pad word clipped by
 * TRUNCATE_TEXT 0xBC). Record-append into the 0x28-stride ring at a0+0x84:
 * rec.f88 = 1 (in-use), rec.f8C = (a2 == -1 ? cursor : a2), rec.f84 = a1,
 * rec.f90 = a3, then a0->0x78++ (ring cursor).
 *
 * -O0 levers that produced the exact bytes:
 *  - REGISTER PARAMS (register char *a0, register int a1/a2/a3): suppresses
 *    the -O0 arg homing entirely (args used straight from a0-a3, matching
 *    the island's unhomed shape).
 *  - `register char *s` -- leaf fn, so the register local colors t0 (the
 *    `or t0, a0, zero` before the cursor increment), and as the only
 *    (register-first) local it reserves a dead home slot -> frame 0x8.
 *  - every field store recomputes the record base from scratch via the
 *    ARRAY FORM ((RecAB0*)(a0 + 0x84))[cursor].fXX: base-first addu
 *    (addu $t9, $a0, $t8) + per-field folded displacement.
 *  - `if (a2 != -1) {...} else {...}` puts the a2-store arm first with the
 *    b-over-else, matching the target block order. */
typedef struct { int f84, f88, f8C, f90; char pad[0x18]; } RecAB0;

void func_00010AB0(register char *a0, register int a1, register int a2, register int a3) {
    register char *s;

    ((RecAB0*)(a0 + 0x84))[*(int*)(a0 + 0x78)].f88 = 1;
    if (a2 != -1) {
        ((RecAB0*)(a0 + 0x84))[*(int*)(a0 + 0x78)].f8C = a2;
    } else {
        ((RecAB0*)(a0 + 0x84))[*(int*)(a0 + 0x78)].f8C = *(int*)(a0 + 0x78);
    }
    ((RecAB0*)(a0 + 0x84))[*(int*)(a0 + 0x78)].f84 = a1;
    ((RecAB0*)(a0 + 0x84))[*(int*)(a0 + 0x78)].f90 = a3;
    s = a0;
    *(int*)(s + 0x78) += 1;
}
