#include "common.h"

extern s32 rmonbrk_bss_0000;
extern s32 D_8001FEF4;
extern s32 D_8001FEF0;
extern void func_800031F0(void*, s32);
extern void func_80005350(void*, s32);






/* func_80007FC8: 8-word infinite-loop stub (likely __osPanic/__halt-class).
 * Target (TRUNCATE_TEXT=0x20): `b self; nop x5; jr ra; nop` — dead epilogue
 * `jr ra` sits at offset 0x18.
 *
 * CAP (re-verified 2026-06-23, standalone-cc sweep): IDO emits an infinite
 * self-loop's dead epilogue at a FIXED offset 0x20, NOT 0x18 — i.e. `b self`
 * at 0x00, 7 pad nops (0x04-0x1C), `jr ra` at 0x20, nop at 0x24. This is
 * invariant across `for(;;);` / `while(1){}` / `while(1);` / `goto self` /
 * `do{}while(1)` / non-empty loop bodies AND across -O0/-O1/-O2/-O3 and
 * -g/-g3. Because the unit truncates to 0x20, IDO's `jr ra` (at 0x20) is cut
 * off, leaving `b self; nop x7` — which mismatches the target's `jr ra` at
 * 0x18 (8 bytes too late). No C body shifts the epilogue earlier; the 0x18
 * placement is unreachable.
 *
 * Previously "matched" via `void f(void){}` + PREFIX_BYTES (instruction-
 * appending), REMOVED 2026-05-27 per feedback_no_instruction_forcing_matches
 * _policy. Function stays NM (INCLUDE_ASM build path); honest unmatched. */
#ifdef NON_MATCHING
void func_80007FC8(void) {}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80007FC8);
#endif
