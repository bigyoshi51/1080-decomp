#include "common.h"

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000000);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000148);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000918);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000B58);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000D04);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000F04);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_000013E8);

extern int gui_func_00000000();

int gui_func_000014B4(int a0, int a1, int a2) {
    return a1 - (gui_func_00000000(a0, a2) / 2);
}

extern int gl_func_00000000();

int gui_func_000014EC(int a0, int a1, int a2) {
    return a1 - gl_func_00000000(a0, a2);
}

#ifdef NON_MATCHING
/* Text-width accumulator (~42 insns, 0xA8): given font-info struct a0 and
 * string a1, sum per-char widths with branch-likely reload pattern.
 *   a0[2] = space-width  (field 0x8)
 *   a0[3] = non-space char-width (field 0xC)
 * Calls gl_func_00000000(a1) at entry (skip if 0) and again per iter as
 * the loop termination length. bnel delay slot reloads the next char.
 * Kept NM: the do-while with bnel+delay-slot reload pattern at -O2 is
 * tricky to reproduce exactly; logic is correct but codegen drifts. */
extern int gl_func_00000000();
int gui_func_00001514(int *a0, unsigned char *a1) {
    int total = 0;
    int i = 0;
    unsigned char *p = a1;
    unsigned char c;

    if (gl_func_00000000(a1) != 0) {
        do {
            c = *p;
            p++;
            i++;
            if (c == 0x20) {
                total += a0[2];
            } else {
                total += a0[3];
            }
        } while (i < gl_func_00000000(a1));
    }
    return total;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00001514);
#endif

extern int gui_func_00000000();

int gui_func_000015BC(int a0, int a1, int a2) {
    return a1 - (gui_func_00000000(a0, a2) / 2);
}

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_000015F4);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_0000267C);

extern int gui_func_00000000();
extern int gui_ref_00000150;

void gui_func_000026D8(char *a0) {
    if (*(int*)(a0 + 0x10) != 0) {
        gui_func_00000000(gui_ref_00000150, *(int*)(a0 + 0x14), a0);
    }
    *(int*)(a0 + 0x10) = 0;
}

extern int gl_func_00000000();
void gui_func_0000271C(char *a0) {
    int saved;
    int v0;
    int v1;
    if (*(int*)(a0 + 0x14) == -1) {
        *(int*)(a0 + 0x14) = 0;
    }
    saved = gl_func_00000000(7);
    v0 = gl_func_00000000(gui_ref_00000150, *(int*)(a0 + 0x14));
    v1 = *(int*)(a0 + 0x10);
    if (v1 == 0 || v0 != v1) {
        *(int*)(a0 + 0x10) = gl_func_00000000(gui_ref_00000150, *(int*)(a0 + 0x14));
    }
    gl_func_00000000(saved);
}

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_000027A0);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00002BB0);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00002DE0);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_0000329C);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00003714);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00003B80);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00004568);

