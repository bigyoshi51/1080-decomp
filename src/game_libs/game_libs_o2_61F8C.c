/* IDO 7.1 -O2 donor for gl_func_00061F8C -- (cmd, val) record loader
 * (0x208 / 130 words; 130/130 word-exact apart from reloc fields).
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs_post0b.c.o (the
 * 52CD4 / 3AC5C recipe, docs/MATCHING_WORKFLOW.md#post0b-jumptable-donor-52cd4).
 * switch (cmd) cases 1..5: the 5-entry table sits at donor .rodata +0, renamed
 * gl_func_00061F8C_rodata and pinned to bootup.uso RoData +0x2080 (the
 * extractor dump at roff 0x2084 lists exactly the five arms in address order).
 *
 * Load-bearing shapes:
 *  - the stream reader (jal 0x0C01D913) and the debug print (jal 0x0C01D900)
 *    are NONZERO baked jals -> gl_ref_0007644C / gl_ref_00076400 pins; the
 *    default arm and the exit check are plain jal 0 (gl_func_00000000).
 *  - the default arm passes cmd as a1, which is why cmd is loaded into a1.
 *  - case 1 prints the value it just stored (`*(int *)(self + 0xC)`): IDO
 *    forwards the stored t7 (`or a1,t7`); passing `val` reloads it from the
 *    stack (&val escaped), and a named copy adds 8 frame bytes.
 *  - `base[1]` with base = &D_00000000 constant-folds to a fresh lui t0; a
 *    volatile read through the s3 base keeps the target's `lw t0,4(s3)`. */
#include "common.h"

extern int gl_func_00000000();
extern int D_00000000;
extern int gl_ref_0007644C(); /* baked jal 0x0C01D913: stream int reader */
extern int gl_ref_00076400(); /* baked jal 0x0C01D900: debug print */
extern char gl_ref_0002205C_61F8C[], gl_ref_00022068_61F8C[], gl_ref_00022078_61F8C[];
extern char gl_ref_00022088_61F8C[], gl_ref_00022098_61F8C[], gl_ref_000220AC_61F8C[];

void gl_func_00061F8C(char *self) {
    int *base;
    int cmd;
    int val;
    int n;
    int buf;

    base = &D_00000000;
    *(s16 *)(self + 0) = 0;
    for (;;) {
        gl_ref_0007644C(&cmd);
        gl_ref_0007644C(&val);
        if (cmd == 0) {
            break;
        }
        switch (cmd) {
        case 1:
            n = val * 8;
            if (*(int *)(self + 0x1C) == 0) {
                *(int *)(self + 0xC) = val;
                gl_ref_00076400(gl_ref_0002205C_61F8C, *(int *)(self + 0xC));
                *(int *)(self + 0x10) = gl_func_00000000(*(int *)(self + 0xC) * 8);
                gl_func_00000000(base, *(int *)(self + 0x10), n);
            } else {
                buf = gl_func_00000000(n);
                gl_func_00000000(base, buf, n);
                gl_func_00000000(buf);
            }
            break;
        case 2:
            *(s16 *)(self + 0) = val;
            gl_ref_00076400(gl_ref_00022068_61F8C, *(s16 *)(self + 0));
            break;
        case 3:
            n = val;
            gl_ref_00076400(gl_ref_00022078_61F8C, n);
            if (((volatile int *)base)[1] == 0) {
                *(int *)(self + 8) = gl_func_00000000(n, 8);
                gl_func_00000000(base, *(int *)(self + 8), n);
            } else {
                *(int *)(self + 8) = 0;
                *(int *)(self + 0x14) = gl_func_00000000(base, 1, 0);
                gl_func_00000000(base, 1, n);
            }
            break;
        case 4:
            gl_func_00000000(base, 1, val);
            break;
        case 5:
            *(s16 *)(self + 2) = val;
            gl_ref_00076400(gl_ref_00022088_61F8C, *(s16 *)(self + 2));
            break;
        default:
            gl_func_00000000(gl_ref_00022098_61F8C, cmd);
            break;
        }
    }
    if (*(s16 *)(self + 0) != 0 && *(int *)(*(char **)(self + 0x18) + 0x38) != *(s16 *)(self + 0)) {
        gl_func_00000000(gl_ref_000220AC_61F8C);
    }
    *(int *)(self + 4) = 7;
}
