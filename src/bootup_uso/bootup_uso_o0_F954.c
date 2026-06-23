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

#ifdef NON_MATCHING
/* func_0000F9E8: -O0 init helper, sibling of FAE8 (flag=0 -> clear-bit live arm).
 * 65w vs 64w target — 1 word off: in the indirect-call arg `off + self[0x48]` the
 * -O0 target keeps self in t7 (cached from the vt computation) and reloads only aux,
 * while the build re-loads self. A pure -O0 self-caching/eval-order residual. */
void func_0000F9E8(int *self) {
    register int *vt;
    register int *r, *x;
    register int flag;

    func_00000000();
    self[0x38 / 4] = func_00000000(&D_00000000);
    vt = (int*)((int*)self[0x48 / 4])[0x28 / 4];
    ((void(*)(int))vt[0x5C / 4])((int)*(short*)((char*)vt + 0x58) + self[0x48 / 4]);
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
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F9E8);
#endif
