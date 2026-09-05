#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

/* Formerly bootup_uso_tail3b_bot_b.c (-O2 -g3, {12BF8, 12C08}). 2026-09-05:
 * renamed bootup_uso_o0_12BF8.c and built at -O0 like the rest of the run --
 * the 2-word "func_00012C08" (jr ra; nop) that followed func_00012BF8 was
 * ugen's dead `$exit: j $31` block of this frameless FALL-OFF fn (no return
 * statement: its own `jr ra; nop` is the fall-off return, the exit pair comes
 * after it), not a function (a standalone -O0 empty fn is
 * `sw a0; b .+1; nop; jr ra; nop`, func_00010310). Our -O0 emits exactly the
 * 0x10 body + that ONE pair = 0x18; TRUNCATE_TEXT 0x18 only clips IDO's
 * section pad. 102A4+"102E8" / 10A9C+"10AA8" precedents;
 * docs/IDO_CODEGEN.md#o0-two-block-predicate-not-adjacent-leaf-cap. 6/6 words. */
void func_00012BF8(int *a0) {
    *(int*)((char*)a0 + 0x168) = 0;
    *(int*)((char*)a0 + 0x16C) = 0;
}
