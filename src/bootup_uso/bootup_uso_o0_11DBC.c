#include "common.h"

/* func_00011DBC: byte-identical sibling of func_00011D78 (reads p[1] = .y
 * instead of p[0] = .x). Carved 2026-07-10, MATCHED at -O0 (15/15 target
 * words = 0x3C, trailing dead pairs clipped by TRUNCATE_TEXT). Same levers
 * as o0_11D78.c: register param, array-form index, dead bare `return;`. */
float func_00011DBC(register char *a0) {
    if (*(int*)(a0 + 0x18C) == 0) {
        return (((float**)(a0 + 0xE0))[*(int*)(a0 + 0x128)])[1];
        return;
    }
    return 0.0f;
}
