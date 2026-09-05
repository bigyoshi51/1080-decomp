#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00010260 moved to bootup_uso_o0_1024C.c (-O0 file split, 2026-05-03). */

/* func_000102A4 moved to bootup_uso_o0_1024C.c 2026-07-10 — it was an -O0
 * island (register params, unfolded div.s by 2.0f, mtc1 load-delay nops);
 * byte-exact there. The 2-word "func_000102E8" (jr ra; nop) that used to head
 * this unit was 102A4's dead -O0 `$exit` pair, absorbed into o0_1024C.c
 * 2026-09-05. */

/* Formerly bootup_uso_tail2.c (-O2 -g3, the -g3 only bought the unfilled jr
 * delay). 2026-09-05: renamed bootup_uso_o0_102F0.c and built at -O0 like the
 * rest of the run -- the 2-word "func_00010308" (jr ra; nop) that followed
 * func_000102F0 was ugen's dead `$exit: j $31` block of this frameless
 * FALL-OFF fn (no return statement: its own `jr ra; nop` is the fall-off
 * return, the exit pair comes after it), not a function (a standalone -O0
 * empty fn is `sw a0; b .+1; nop; jr ra; nop`, func_00010310 right after
 * this unit). Our -O0 emits exactly the 0x18 body + that ONE pair = 0x20;
 * TRUNCATE_TEXT 0x20 only clips IDO's section pad. Register params keep -O0
 * from homing a0/a1 (102A4 precedent). 8/8 words. */
void func_000102F0(char *a0, int a1) {
    *(float*)(a0 + 0x70) = (float)a1;
}
