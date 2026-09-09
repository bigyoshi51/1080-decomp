/* IDO 7.1 -O2 donor for gl_func_00068990 -- record-stream reader that
 * fills an object header from a tagged token stream (exported bootup.uso
 * sym 2482, section 0x7CFFC, 0x174 / 93 words). PROVEN EXACT 93/93 words
 * standalone (the six link-resolved words are the five reloc jals and the
 * jumptable %lo, see below).
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs_post1b.c.o (the
 * 2E290 / 6DD14 recipe, docs/MATCHING_WORKFLOW.md#donor-splice-switch-
 * jumptable-rodata-rename): the C `switch` puts its 6-entry jumptable in
 * the donor's local .rodata; the splice renames that reloc to
 * gl_func_00068990_rodata, pinned in undefined_syms_auto.txt to the table
 * the USO ships in bootup.uso RoData at +0x2220 (RoDataReloc symIdx 1 x 6).
 * Shipped words 0x2220..0x2238 = 0, 68AB0, 68AB8, 68A04, 68A28, 68AB8 and an
 * unrelocated 68A38 just past the table -- the 2E290 "zero first entry +
 * spilled last arm" linker quirk, read as the one-slot shift:
 *   tag -1 -> done (68AB0), 0/3/default -> 68AB8, 1 -> 68A04, 2 -> 68A28,
 *   4 -> 68A38.
 *
 * Reloc identities (bootup.uso TextReloc, kind 1 = blank jal):
 *   baked jals 7C8EC / 7C860 / 7C928 = the in-unit int readers
 *     gl_func_00068280 / gl_func_000681F4 / gl_func_000682BC (section-
 *     relative relocs: called via gl_ref_0007C8EC / _7C860 / _7C928 pins,
 *     the host symbols themselves link at splat addresses, 0x1466C low);
 *   sym 627 = gl_func_00042090 (x2: save/restore a current-context handle),
 *   sym 113 = gl_func_000410E4, sym 74 = gl_func_00035440,
 *   sym 454 = gl_func_00035648 (x3), sym 306 = gl_func_00061478 -- all
 *   blank load-time relocs, named through the catch-all gl_func_00000000;
 *   s2 = &import_0005C6E0 (sym 73, pinned 0), s6 = Data +0x2B430 (sym 2).
 *
 * Load-bearing shapes:
 *  - `switch (tag)` with labels -1..4 gives `addiu t7,t6,1; sltiu at,t7,6`;
 *    `case 0: case 3: default:` keeps the table dense, arms in SOURCE
 *    order (1, 2, 4, -1, default).
 *  - The loop must be `for (;;) { ... if (done != 0) break; }`: a
 *    `do { } while (done == 0)` / `while (done == 0)` spelling colours
 *    `done` s4 and `&a` s3 (target: done s3, &a s4, &b s5).
 *  - Named-scalar homes top-down in declaration order: done 0x4C, b 0x48,
 *    a 0x44, saved 0x40, v 0x3C (frame 0x50; a/b are the address-taken
 *    reader slots, the other three are dead -O2 homes).
 *  - The taken-arm `or a0,s2; li a1,1` hoisted above `bnez t0` is uopt's
 *    own scheduling of the else-arm call args; no C needed. */
#include "common.h"

typedef struct {
    int unk0;
    int unk4;
} Ctx68990;

extern Ctx68990 import_0005C6E0;
extern int D_00000000;
/* the three in-unit readers, called through gl_ref_<section-addr> pins so the
 * link bakes the USO section-relative words 0x0C01F23B / 0x0C01F218 / 0x0C01F24A
 * (the host symbol gl_func_00068280 links at its splat address 0x68280) */
extern void gl_ref_0007C8EC(int *); /* gl_func_00068280 */
extern void gl_ref_0007C860(int *); /* gl_func_000681F4 */
extern void gl_ref_0007C928(int *); /* gl_func_000682BC */
extern int gl_func_00000000();

void gl_func_00068990(char *o) {
    int done;
    int b;
    int a;
    int saved;
    int v;

    done = 0;
    for (;;) {
        gl_ref_0007C8EC(&b);
        switch (b) {
        case 1:
            gl_ref_0007C8EC(&a);
            *(short *)(o + 0x20) = a;
            gl_ref_0007C8EC(&a);
            *(short *)(o + 0x22) = a;
            break;
        case 2:
            gl_ref_0007C860((int *)(o + 0x24));
            break;
        case 4:
            gl_ref_0007C928((int *)(o + 0x2C));
            if (import_0005C6E0.unk4 == 0) {
                saved = gl_func_00000000(0);
                v = gl_func_00000000(*(int *)(o + 0x2C));
                *(int *)(o + 8) = v;
                gl_func_00000000(&import_0005C6E0, v, *(int *)(o + 0x2C));
                gl_func_00000000(saved);
            } else {
                *(int *)(o + 0x28) = gl_func_00000000(&import_0005C6E0, 1, 0);
                gl_func_00000000(&import_0005C6E0, 1, *(int *)(o + 0x2C));
            }
            break;
        case -1:
            done = 1;
            break;
        case 0:
        case 3:
        default:
            gl_func_00000000((char *)&D_00000000 + 0x2B430, gl_func_00000000(&import_0005C6E0, 1, 0));
            break;
        }
        if (done != 0) break;
    }
}
