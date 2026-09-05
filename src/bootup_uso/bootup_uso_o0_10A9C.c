#include "common.h"

/* Bottom piece of the original bootup_uso_tail3a.c (carved 2026-07-10 as
 * bootup_uso_tail3a_10540.c). 2026-09-04: func_00010540 moved out to
 * bootup_uso_o0_10540.c where it MATCHES at -O0 (343/343). 2026-09-05: renamed
 * bootup_uso_o0_10A9C.c and built at -O0 like the rest of the run -- the
 * 2-word "func_00010AA8" (jr ra; nop) that followed func_00010A9C was ugen's
 * dead `$exit: j $31` block of this frameless FALL-OFF fn (no return
 * statement: its own `jr ra; nop` is the fall-off return, the exit pair comes
 * after it), not a function (a standalone -O0 empty fn is
 * `sw a0; b .+1; nop; jr ra; nop`, func_00010310). Our -O0 emits exactly the
 * 0xC body + that ONE pair = 0x14; TRUNCATE_TEXT 0x14 only clips IDO's
 * section pad. 102A4+"102E8" precedent;
 * docs/IDO_CODEGEN.md#o0-two-block-predicate-not-adjacent-leaf-cap. 5/5 words. */

void func_00010A9C(int *a0) {
    *(int*)((char*)a0 + 0x78) = 0;
}
