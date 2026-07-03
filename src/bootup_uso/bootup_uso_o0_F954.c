#include "common.h"

extern int func_00000000();
extern char D_00000000;
extern struct { int a, b, c; } func_00000188;

/* -O0 cluster split from bootup_uso_tail1.c on 2026-06-23 (F954-F9E8 are -O0;
 * moved together so tail1 keeps only the -O2 func_0000F81C and the linker stays
 * contiguous). func_0000F954 is a byte-exact -O0 C match; func_0000F9E8 is 1 word
 * off (a -O0 self-cache/eval-order residual in the indirect-call arg) so stays NM. */

/* func_0000F954: -O0 init helper. The 3rd-call arg loads func_00000188+8 via a
 * struct-field ref (folds to lui;lw 8 — an array/scalar+offset ref instead emits
 * an extra addiu materializing the address). */
void func_0000F954(int *a0, int a1, int a2) {
    if (*(int*)((char*)a0 + 0x48) != 0) {
        func_00000000(*(int*)((char*)a0 + 0x48));
    }
    func_00000000(&D_00000000);
    func_00000000(func_00000188.c, 3, 0);
    *(int*)((char*)a0 + 0x2C) = 1;
    func_00000000(a1, a2, 0);
}

/* func_0000F9E8 — 64/64 EXACT (2026-07-03, agent-e).
 * Levers: (1) single-statement embed of the vt= assignment inside the call arg
 * so `self` stays cached in t7 across the whole expression (separate statement
 * reloaded self from sp -> +1 insn + temp shift); (2) IDO -O0 evaluates the
 * RIGHT add operand first and makes it rs of addu -> source order must be
 * self[0x48/4] + *(short*)(vt...+0x58); (3) decl order vt,r,flag,x so
 * flag=s2 / x=s3 (s-regs assigned in DECLARATION order at -O0). */
void func_0000F9E8(int *self) {
    register int *vt;
    register int *r;
    register int flag;
    register int *x;

    func_00000000();
    self[0x38 / 4] = func_00000000(&D_00000000);
    ((void(*)(int))vt[0x5C / 4])(self[0x48 / 4] + (int)*(short*)((char*)(vt = (int*)((int*)self[0x48 / 4])[0x28 / 4]) + 0x58));
    ((int*)self[0x48 / 4])[0x7C / 4] = 0;
    self[0x30 / 4] = 1;
    self[0x34 / 4] = 0;
    if (self[0x4C / 4] != 0) {
        vt = (int*)((char*)self[0x4C / 4] + 0x18);
        r = vt;
        flag = 0;
        if (flag) {
            x = r;
            *x |= 8;
        } else {
            x = r;
            *x &= ~8;
        }
    }
}
