#include "common.h"

/* gl_func_00071864 = libultra __osSumcalc (io/contpfs.c), statically linked
 * into game_libs. Byte-exact ONLY with IDO 5.3 -O1 (this unit's per-file
 * CC/OPT_FLAGS override) from the verbatim libreultra source. The prior
 * "stack-residency + filled delay slots = un-reproducible cap" verdict
 * (docs/IDO_CODEGEN.md#feedback-ido-stack-residency-plus-filled-slots-is-o1-not-o0)
 * only tested the 7.1 project cc; the original object came from libultra
 * built with IDO 5.3. TRUNCATE_TEXT 0x5C trims the section pad nop so the
 * next unit lands at 0x718C0. */
u16 gl_func_00071864(u8 *ptr, int length)
{
    int i;
    u32 sum;
    u8 *tmp;

    sum = 0;
    tmp = ptr;
    for (i = 0; i < length; i++)
    {
        sum += *tmp++;
        sum &= 0xffff;
    }
    return sum;
}
