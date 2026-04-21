#include "common.h"

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000000);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000148);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000918);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000B58);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000D04);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000F04);

#ifdef NON_MATCHING
/* Text-width accumulator with glyph-table lookup (51 insns, 0xCC).
 *   a0 = font-info struct: +0x08 = space-width, +0x20 = glyph-table ptr
 *   a1 = string
 * For each char up to gl_func_00000000(a1) length:
 *   if ' ': total += a0[2] (space-width at +0x8)
 *   else:   key = gl_func_00000000(c);
 *           total += *(int*)(glyph_table + key*20 + 8)
 * Glyph stride = 20 bytes. Same do-while+bnel-delay-slot-reload shape as
 * gui_func_00001514 (previously NM-wrapped text-width helper). */
int gui_func_000013E8(char *a0, unsigned char *a1) {
    int total = 0;
    int i = 0;
    unsigned char *p = a1;
    unsigned char c;
    int key;

    if (gl_func_00000000(a1) != 0) {
        do {
            c = *p;
            if (c == 0x20) {
                total += *(int*)(a0 + 0x8);
            } else {
                key = gl_func_00000000(c);
                total += *(int*)(*(char**)(a0 + 0x20) + key * 20 + 8);
            }
            p++;
            i++;
        } while (i < gl_func_00000000(a1));
    }
    return total;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_000013E8);
#endif

extern int gui_func_00000000();

int gui_func_000014B4(int a0, int a1, int a2) {
    return a1 - (gui_func_00000000(a0, a2) / 2);
}

extern int gl_func_00000000();

int gui_func_000014EC(int a0, int a1, int a2) {
    return a1 - gl_func_00000000(a0, a2);
}

extern int gl_func_00000000();
int gui_func_00001514(int *a0, unsigned char *a1) {
    int total = 0;
    unsigned char *p = a1;
    unsigned int i = 0;

    if (gl_func_00000000(a1) != 0) {
        do {
            if (*p != 0x20) {
                total += a0[3];
            } else {
                total += a0[2];
            }
            p++;
            i++;
        } while (i < (unsigned int)gl_func_00000000(a1));
    }
    return total;
}

extern int gui_func_00000000();

int gui_func_000015BC(int a0, int a1, int a2) {
    return a1 - (gui_func_00000000(a0, a2) / 2);
}

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_000015F4);

extern int gl_func_00000000();
extern int gui_ref_00000150;

void gui_func_0000267C(char *a0, int a1) {
    int saved;
    *(int*)(a0 + 0x14) = a1;
    saved = gl_func_00000000(7);
    *(int*)(a0 + 0x10) = gl_func_00000000(gui_ref_00000150, *(int*)(a0 + 0x14));
    gl_func_00000000(saved);
}

void gui_func_000026CC(int *a0, int a1) {
    a0[5] = a1;
    a0[4] = 0;
}

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

