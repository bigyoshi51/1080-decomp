#include "common.h"

/* 0x1207C..0x120A8: the last two frameless -O0 FALL-OFF fns of the tail3a_bot
 * run, carved out of bootup_uso_tail3a_bot_11DF8.c (-O2 -g3) 2026-09-05.
 * Each fn has no return statement, so ugen emits its own fall-off `jr ra; nop`
 * INSIDE the fn and a dead `$exit: jr ra; nop` pair right after it -- those
 * pairs were the fake 2-word "empty fns" func_00012088 / func_000120A0 (merged
 * into the heads' .s). Both fns in one TU at -O0 emit exactly the ROM layout
 * `sw; jr; nop | jr; nop | addiu; sw; jr; nop | jr; nop` = 0x2C; TRUNCATE_TEXT
 * 0x2C only drops IDO's 16-byte section pad. The -O2 -g3 bodies were
 * word-for-word these -O0 bodies (the -g3 only bought the unfilled jr delay).
 * See docs/MATCHING_WORKFLOW.md twenty-first beql case. */

void func_0001207C(int *a0, int a1) {
    *(int*)((char*)a0 + 0x128) = a1;
}

void func_00012090(int *a0) {
    *(int*)((char*)a0 + 0x128) = -1;
}
