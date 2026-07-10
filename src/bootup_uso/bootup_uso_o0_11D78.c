#include "common.h"

/* func_00011D78: -O0 island carved out of bootup_uso_tail3a_bot.c on
 * 2026-07-10 and MATCHED at -O0 (15/15 target words = 0x3C; the 3 trailing
 * dead jr-ra pairs our -O0 emits are clipped by TRUNCATE_TEXT — o0_11D40
 * precedent, which is why this fn must terminate its file).
 *
 * Indexed-pointer-array float load with early-out: slot ptr array at
 * a0+0xE0, index at a0+0x128, gate at a0+0x18C; returns slot->x or 0.0f.
 *
 * -O0 levers (supersede the old "-O0 inter-block dead-pair irreducible"
 * cap note — that analysis predated the register-param + dead-bare-return
 * levers): register param (unhomed a0, frameless leaf); array-form
 * ((float**)(a0+0xE0))[idx] for base-first addu $t9,$a0,$t8 + folded 0xE0;
 * the target's interior dead jr-ra pair between the main return and the
 * zero block is a lexically-dead bare `return;` INSIDE the if arm. */
float func_00011D78(register char *a0) {
    if (*(int*)(a0 + 0x18C) == 0) {
        return *(((float**)(a0 + 0xE0))[*(int*)(a0 + 0x128)]);
        return;
    }
    return 0.0f;
}
