#include "common.h"

/* -O0 sub-file covering bootup_uso offset 0x10B6C..0x10C8B (single function,
 * 72 insns, 0x120 bytes), split from the middle of bootup_uso_tail3a.c
 * (-O2 -g3) on 2026-07-10. tail3a TRUNCATE_TEXT reduced 0x14D8 -> 0x848;
 * the 0x10C8C..0x116C7 remainder moved to bootup_uso_tail3a_10C8C.c
 * (INCLUDE_ASM, still -O2 -g3) and 0x116C8 to bootup_uso_o0_116C8.c. */

extern int func_00000000();

/* func_00010B6C: record-append+init, the with-sub-object sibling of
 * func_00010AB0 (same 0x28-stride record array at +0x84, counter at +0x78).
 * MATCHED 2026-07-10 (72/72, zero diffs pre-link).
 * Key -O0 shapes: (1) STRUCT MEMBER-ARRAY form is load-bearing for the call
 * arg: `&a0->recs[a0->count].sub` emits `addu a0, <base>, <idx>` (base-first,
 * matching target 0x10C2C); every pointer-arithmetic / cast-array spelling
 * of the same address emits idx-first (addu a0, t7, t2) — probed 10 variants.
 * Store addresses fold either way (offset folded into sw), so only the
 * address-as-value site distinguishes the forms. (2) cfe DAG-share inside
 * the else-arm statement `recs[count].f8C = count` reuses the count load
 * for both index and stored value (sw t9 after t9-indexed addu). (3) the
 * final `count += 1` goes through a REGISTER pointer var (p = a0; p->count
 * += 1) — that is what colors s0 (lw s0, 0x28(sp)) and forces the s0
 * save/restore at 0x18(sp). */
typedef struct {
    int f84;
    int f88;   /* in-use flag */
    int f8C;   /* link index */
    int f90;
    char sub[0x18]; /* sub-init region handed to func_00000000 */
} Rec10B6C;

typedef struct {
    char pad[0x78];
    int count;
    char pad2[0x8];
    Rec10B6C recs[1];
} Container10B6C;

void func_00010B6C(Container10B6C *a0, void *a1, int a2, int a3) {
    register Container10B6C *p;

    a0->recs[a0->count].f88 = 1;
    if (a2 != -1) {
        a0->recs[a0->count].f8C = a2;
    } else {
        a0->recs[a0->count].f8C = a0->count;
    }
    a0->recs[a0->count].f84 = 0;
    func_00000000(&a0->recs[a0->count].sub, a1);
    a0->recs[a0->count].f90 = a3;
    p = a0;
    p->count += 1;
}
