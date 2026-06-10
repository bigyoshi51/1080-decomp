#include "common.h"

/* gl_func_00070194 = libultra __osContAddressCrc and gl_func_00070244 =
 * __osContDataCrc (io/crc.c), statically linked into game_libs. Both
 * byte-exact ONLY with IDO 5.3 -O1 (per-file CC/OPT_FLAGS override) from
 * VERBATIM libreultra source — same compiler-version story as the contpfs
 * pair at 0x71864/0x718C0 (see docs/MATCHING_WORKFLOW.md ido53-carve
 * recipe). TRUNCATE_TEXT 0x180 normalizes section align so the unit sits
 * flush at USO 0x70194. */
u8 gl_func_00070194(u16 addr)
{
    u8 temp;
    u8 temp2;
    int i;
    temp = 0;
    for (i = 0; i < 16; i++)
    {
        if (temp & 0x10)
            temp2 = 21;
        else
            temp2 = 0;

        temp <<= 1;
        temp |= (u8)((addr & 0x400) ? 1 : 0);
        addr <<= 1;
        temp ^= temp2;
    }
    return temp & 0x1f;
}

u8 gl_func_00070244(u8 *data)
{
    u8 temp;
    u8 temp2;
    int i;
    int j;
    temp = 0;
    for (i = 0; i <= 32; i++, data++)
    {
        for (j = 7; j >= 0; j--)
        {
            if (temp & 0x80)
                temp2 = 133;
            else
                temp2 = 0;
            temp <<= 1;
            if (i == 32)
                temp &= -1;
            else
                temp |= ((*data & (1 << j)) ? 1 : 0);
            temp ^= temp2;
        }
    }
    return temp;
}
