#include "common.h"

/* First slice of the original bootup_uso_tail3a_bot.c (0x11D70..0x120A8),
 * carved 2026-07-10 so func_00011D78 / func_00011DBC build at -O0 in their
 * own file-terminal units (o0_11D78.c / o0_11DBC.c; their -O0 emission
 * carries trailing dead jr-ra pairs that TRUNCATE_TEXT can only clip at
 * file end). Empty stubs stay in -O2 -g3 slices: at -O0 an empty fn emits
 * an extra dead jr pair (16 bytes vs the 8-byte target), so they cannot sit
 * in the -O0 files at all. Layout now: tail3a_bot {11D70} | o0_11D78 |
 * tail3a_bot_11DB4 {11DB4} | o0_11DBC | tail3a_bot_11DF8 {11DF8, 11E00,
 * 11ED4, 11FA8, 1207C, 12088, 12090, 120A0}. */

void func_00011D70(void) {
}
