#include "common.h"

/* -O0 sub-file covering bootup_uso offset 0x116C8..0x117FB (single function,
 * 77 insns, 0x134 bytes), split from the tail of bootup_uso_tail3a.c
 * (-O2 -g3) on 2026-07-10 (tail3a TRUNCATE_TEXT reduced alongside the
 * 0x10B6C carve; see bootup_uso_o0_10B6C.c header). Sits directly in front
 * of bootup_uso_o0_117FC.c. */

extern int func_00000000();
extern int D_00000000;
extern char D_0000C624;
extern char D_0000C65C;
extern char D_0000C694;
/* Two module-external word reads whose baked LO16 fields are 0x34 / 0x40
 * (splat mislabeled them func_00000008+0x2C / +0x38). Bare-symbol reads via
 * undefined_syms_auto.txt entries, same recipe as D_8AE4_mode (= 0x34). */
extern int D_bu_116C8_34;
extern int D_bu_116C8_40;

typedef int (*FN116C8)();

/* func_000116C8: subsystem init/teardown orchestrator (structural decode
 * retained in bootup_uso_tail3a.c history).
 * MATCHED 2026-07-10 (77/77, only link-resolved reloc fields differ pre-link).
 * Key -O0 shapes: (1) `D_00000000 = 0;` as a DIRECT global store emits the
 * $at-fused single-lui form (lui at / sw zero, 0(at)); the `*(int*)&D` cast
 * spelling emits lui/addiu/sw through a temp (+1 word). (2) the 3-arg call's
 * a1/a2 must be DIRECT bare-symbol reads (D_bu_116C8_34/_40) — spelling them
 * as *(int*)(&D+0x34) lets cfe DAG-share &D across all three args (move
 * a0,t7 + folded lws), losing the per-arg lui pairs. (3) both vtable
 * dispatches embed the register-var assignment in the CALL ARG
 * (`*(short*)((p = *(char**)((char*)&D+0x28)) + 0x10) + (int)&D`): &D is
 * DAG-shared between the p-load (folded 0x28 offset) and the trailing
 * addend (addu a0, t7, t6), and the callee expression `*(FN)*(int*)(p+0x14)`
 * reuses p; embedding the assignment in the CALLEE instead evaluates the
 * arg off the stale p first (wrong order). (4) the alloc guard is the
 * fused-|| form on the register var: `p = &local; if (p != 0 || (p =
 * alloc(0xC)) != 0) p->f0 = 8;` (same lever as o0_117FC). (5) frame -0x30 /
 * local at sp+0x24 needs TWO int locals with `local` declared SECOND
 * (first-declared sits at 0x28, unused). */
void func_000116C8(void) {
    register char *p;
    int pad;
    int local;

    func_00000000(&D_00000000);
    func_00000000(&D_00000000);
    D_00000000 = 0;
    func_00000000(1);
    func_00000000(&D_0000C624);
    func_00000000(&D_00000000);
    func_00000000();
    func_00000000(&D_0000C65C);
    func_00000000(&D_00000000, D_bu_116C8_34, D_bu_116C8_40);
    (*(FN116C8)*(int *)(p + 0x14))(
        *(short *)((p = *(char **)((char *)&D_00000000 + 0x28)) + 0x10) + (int)&D_00000000);
    p = (char *)&local;
    if (p != 0 || (p = (char *)func_00000000(0xC)) != 0) {
        *(int *)p = 8;
    }
    (*(FN116C8)*(int *)(p + 0x34))(
        *(short *)((p = *(char **)((char *)&D_00000000 + 0x28)) + 0x30) + (int)&D_00000000,
        &local);
    func_00000000(&D_0000C694);
}
