#include "common.h"

/* -O0 sub-file prep for the bootup_uso 0xFBCC..0xFEE8 region. Mirrors
 * the game_libs_o0_8944.c step-0 pattern.
 *
 * STATUS — step 0 of multi-tick split. This file holds verified -O0 C
 * bodies for func_0000FBCC + sandwich INCLUDE_ASMs for the still-NM
 * neighbours (FC28, FD4C, FEA0). Bracketed with #if 0 so .o is empty
 * and link-safe — no duplicate-symbol conflict with bootup_uso_tail1.c's
 * existing wraps until full migration lands.
 *
 * Verified standalone at -O0 (2026-05-07; RE-VERIFIED 2026-05-28):
 *   func_0000FBCC: 23 insns / 0x5C, byte-exact for all 23 target insns
 *     (dead `if (0) ... else` pattern from constant-folded `set = 0` flag —
 *     4 register-typed locals p1/p2/set/t). 2026-05-28 re-test: -O0 emit is
 *     24 insns (96B); the 1 EXTRA trailing nop (past the 0x5C target) is
 *     removed by TRUNCATE_TEXT. So FBCC is a CLEAN landable match once
 *     migrated — the lone clean one of this group (FC28/FD4C/FEA0 keep
 *     ~96% dead-BB / t-reg-reuse caps per the notes below).
 *   bootup_uso is NOT Yay0-compressed → refresh-expected-baseline.py is
 *     UNBLOCKED for this migration (unlike game_uso/timproc/mgrproc USOs).
 *   LAYOUT-MATH CAVEAT (resolve before step 1): the checklist below assumes
 *     tail1 starts at 0xF8A4 (→ tail1 TRUNCATE 0x328), but the CURRENT tail1
 *     TRUNCATE_TEXT is 0xA30 and o0_100F0.c immediately follows tail1 in
 *     tenshoe.ld. Recompute from the linker layout: tail1_end = 0x100F0;
 *     func offsets FBCC@0xFBCC FC28@0xFC28 FD4C@0xFD4C FEA0@0xFEA0
 *     FEE8@0xFEE8. Derive tail1 TRUNCATE = 0xFBCC - tail1_start; o0_FBCC
 *     covers 0xFBCC..0xFEE8 (0x31C, holds FBCC+FC28+FD4C+FEA0); tail1_bot
 *     covers 0xFEE8..0x100F0 (0x208, holds FEE8). After migrating, VERIFY
 *     each function's bytes against the ORIGINAL baserom.z64 at its absolute
 *     offset — a regenerated expected/.o would mask a layout error.
 *
 * Migration checklist (from #feedback-stage-0-file-needs-if-zero-bracket
 * in docs/MATCHING_WORKFLOW.md):
 *   1. Truncate bootup_uso_tail1.c TRUNCATE_TEXT 0xA30 → ?? (compute
 *      from new layout: tail1 ends at FBCC = 0xFBCC offset within
 *      bootup_uso, tail1 starts at 0xF8A4 → new size = 0xFBCC - 0xF8A4
 *      = 0x328).
 *   2. Create bootup_uso_tail1_bot.c covering 0xFEE8..0x1024C (after
 *      the FEA0 sandwich), TRUNCATE_TEXT = 0x364 = (0x1024C - 0xFEE8).
 *   3. Update Makefile: add this file with `OPT_FLAGS := -O0` +
 *      `TRUNCATE_TEXT := 0x320` (= FBCC..FEE8 span). Add tail1_bot
 *      with -O2 + 0x364.
 *   4. Update tenshoe.ld: insert this and tail1_bot between tail1.c.o
 *      and o0_1024C.c.o.
 *   5. Strip the FBCC + FEA0 NM wraps from bootup_uso_tail1.c. Move
 *      FC28 + FD4C INCLUDE_ASMs to this file (between FBCC and FEA0).
 *   6. Remove `#if 0` brackets from FBCC body in this file.
 *   7. Add objdiff.json unit entry (-O0 c_flags).
 *   8. Refresh expected/.o via scripts/refresh-expected-baseline.py.
 *
 * Note on FEA0: standalone -O0 emits 1 extra insn (reload-t8 vs
 * target's reuse-t6 for the second a0 access). Documenting alongside
 * FBCC for grouped migration; FEA0 stays INCLUDE_ASM-sandwich until
 * a future pass solves the t-register reuse cap (likely needs
 * `register char *self = a0` alias).
 *
 * Note on FD4C (2026-05-25): DECODED + verified standalone -O0 to
 * 76/85 insns byte-exact via the docs/IDO_CODEGEN "-O0 alloc-cascade
 * 5-lever recipe" (register void *s0,s1; short-circuit || arms;
 * saved-reg reuse in tail; struct-field/typed-global direct access for
 * %hi/%lo($at) folding). RESIDUAL CAP: one un-removable -O0 dead-BB
 * `b .+1; nop` tail marker (same class as arcproc_uso_func_000000B4)
 * => ~96% NM even after migration, never a clean match. FC28 is the
 * SAME -O0 alloc-cascade pattern (0x50/0x50/0x2C arms) — the recipe
 * applies; expect the same ~96% cap. Both stay INCLUDE_ASM-sandwich. */

#if 0
extern int func_00000000();

void func_0000FBCC(int *a0) {
    register int *p1, *p2;
    register int set;
    register int *t;
    p1 = (int*)((char*)a0[0x48/4] + 0x18);
    p2 = p1;
    set = 0;
    if (set) { t = p2; *t = *t | 8; }
    else     { t = p2; *t = *t & ~8; }
}

#ifdef NON_MATCHING
/* func_0000FC28: -O0 alloc-cascade constructor (73 insns, 0x124).
 * Per docs/PATTERNS.md alloc-cascade: 3-arm allocation chain
 *   if (a0 == 0) { a0 = alloc(0x50); if (!a0) goto end; }
 *   if (s0 == 0) { s0 = alloc(0x50); if (!s0) goto skip0; }   // dead at -O0
 *   if (s1 == 0) { s1 = alloc(0x2C); if (!s1) goto skip1; }   // dead at -O0
 *   memcpy(s1, &D_0000C58C, ?); s1->[0x28] = &D_???;
 *   ... s0->[0x28] = &D_???;
 *   self->[0x28] = &D_???; self->[0xC] = &D_0000C594;
 *   D_??? = init_call(self, 0);
 *   bind_call(D_???, self);
 *   return self;
 *
 * Multi-pass NM placeholder. Default INCLUDE_ASM keeps ROM exact. */
extern int func_00000000();
extern char D_00000000;
extern char D_0000C58C;
extern char D_0000C594;
extern int D_C28_returned_handle;

void *func_0000FC28(void *a0) {
    void *self = a0;
    if (self == 0) {
        self = (void*)func_00000000(0x50);
        if (self == 0) return 0;
    }
    /* TODO 0x40-0x124: 2 more alloc-cascade arms + memcpy + init bindings */
    return self;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FC28);
#endif

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FD4C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEA0);
#endif
