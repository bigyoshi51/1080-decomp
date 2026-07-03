#include "common.h"

/* gui_uso flag-carve unit: gui_func_00000000, the segment-entry char mapper.
 * Byte-exact ONLY with -Wo,-zcopy:0 (uopt copy-propagation kill switch, per-file
 * CC_ONLY_FLAGS override): the target keeps `or v0,a0` from a plain copy whose
 * branch uses copy-prop otherwise rewrites to a0 (see docs/IDO_CODEGEN.md
 * bnel-dispatch 2026-07-02 entry + uoptcopy.c find_replacements analysis).
 * Word 0 of the ROM unit is the 1-word USO entry trampoline `b 0x1cdc0`
 * (PREFIX_BYTES gui_func_00000000=0x1000736F, same class as boarder5_uso).
 * TRUNCATE_TEXT on gui_uso.c.o shrank 0x4880->0x4738 to compensate. */
int gui_func_00000000(c)
int c;
{
    int m;
    unsigned char *pa = (unsigned char *)&c;
    c = c & 0xFF;
    m = c;
    if (c == 0x21) { c = 0x27; goto ret; }
    if (m == 0x2C) { c = 0x28; goto ret; }
    if (m == 0x2F) { c = 0x29; goto ret; }
    if (m == 0x5B) { c = 0x26; goto ret; }
    if (m == 0x5D) { c = 0x27; goto ret; }
    if (m == 0x2B) { c = 0x24; goto ret; }
    if (m == 0x5F) { c = 0x25; goto ret; }
    if (m == 0x2E) { c = 0x25; goto ret; }
    if (m == 0x2D) { c = 0x25; goto ret; }
    if (m >= 0x61 && m < 0x7B) { c = m - 0x57; goto ret; }
    if (m >= 0x41 && m < 0x5B) { c = m - 0x37; goto ret; }
    if (m >= 0x30 && m < 0x3A) { c = (m - 0x30) & 0xFF; }
ret:
    return c & 0xFF;
}
