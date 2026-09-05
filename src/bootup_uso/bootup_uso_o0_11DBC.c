#include "common.h"

/* func_00011DBC: byte-identical sibling of func_00011D78 (reads p[1] = .y
 * instead of p[0] = .x). Carved 2026-07-10, MATCHED at -O0. 17/17 words =
 * 0x44 since 2026-09-05: the 2-word "func_00011DF8" (jr ra; nop) that headed
 * tail3a_bot_11DF8.c was this fn's own dead `$exit: j $31` block, not a
 * function (11D40/"11D70" and 11D78/"11DB4" precedents; docs/IDO_CODEGEN.md
 * #o0-two-block-predicate-not-adjacent-leaf-cap). Our -O0 emits the 0x3C
 * body + TWO dead pairs, shipped ONE: file-terminal + TRUNCATE_TEXT 0x44.
 * Same levers as o0_11D78.c: register param, array-form index, dead bare
 * `return;`. */
float func_00011DBC(register char *a0) {
    if (*(int*)(a0 + 0x18C) == 0) {
        return (((float**)(a0 + 0xE0))[*(int*)(a0 + 0x128)])[1];
        return;
    }
    return 0.0f;
}
