#include "common.h"

/* 8-byte empty-stub slice between the o0_11D78 and o0_11DBC -O0 carve units
 * (2026-07-10 carve of the original bootup_uso_tail3a_bot.c; that file was
 * retired 2026-09-05 when its only content, "func_00011D70", turned out to be
 * func_00011D40's dead -O0 exit pair -- this stub is very likely 11D78's exit
 * pair by the same argument, see o0_11D40.c). */

void func_00011DB4(void) {
}
