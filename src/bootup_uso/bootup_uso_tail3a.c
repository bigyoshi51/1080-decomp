#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* CRACKED 2026-05-27 (byte-exact): array-indexing form `((Row28*)base)[i].d`
 * combined with the file's existing `OPT_FLAGS := -O2 -g3` Makefile override
 * (which disables delay-slot fill, leaving the jr-ra delay as nop matching
 * target).
 *
 * The lever was the ARRAY FORM (`((Row28*)(a0+0x84))[idx].d`) per
 * docs/IDO_CODEGEN.md "addu operand order" entry — gives `addu v0, a0, t7`
 * (base-first) instead of the arithmetic form's `addu v0, t7, a0`
 * (idx-first). Verified byte-equal at .o level (all 8 instructions). */
typedef struct { char d[0x28]; } Row10324;
char *func_00010324(a0) char *a0; {
    return ((Row10324*)(a0 + 0x84))[*(int*)(a0 + 0x7C)].d;
}

void func_00010344(void) {
}

/* 2026-07-10 -O0 island carve: func_0001034C moved to bootup_uso_o0_1034C.c
 * and MATCHED there at -O0 (125/125). func_00010540 (INCLUDE_ASM, honest NM;
 * its own blocker is also -O0 but the 343-insn body has pervasive typed-struct
 * eval-order divergence, see its wrap doc) + func_00010A9C + func_00010AA8
 * moved to bootup_uso_tail3a_10540.c (-O2 -g3). func_00010AB0 moved to
 * bootup_uso_o0_10AB0.c and MATCHED there at -O0 (47/47). tail3a now ends at
 * 0x1034C (TRUNCATE_TEXT 0x848 -> 0x28). */

/* func_00010B6C (0x10B6C..0x10C8B) split to bootup_uso_o0_10B6C.c on
 * 2026-07-10 and MATCHED there at -O0 (72/72). tail3a now ends at 0x10B6C
 * (TRUNCATE_TEXT 0x848); the 0x10C8C..0x116C7 remainder (func_00010C8C +
 * func_00010FEC, both honest-NM INCLUDE_ASM) moved to
 * bootup_uso_tail3a_10C8C.c, still -O2 -g3. */


/* func_000116C8 (0x116C8..0x117FB) split to bootup_uso_o0_116C8.c on
 * 2026-07-10 and MATCHED there at -O0 (77/77); structural decode retained
 * in git history. */

/* func_000117FC (0x117FC..0x118E3) split to bootup_uso_o0_117FC.c on
 * 2026-07-10 and MATCHED there at -O0 (58/58). The 2026-05-31 note here
 * ("no standard opt level reproduces it, -O0 over-produces") was a
 * standalone-cc false cap on a wrong C body (early-return locals form);
 * the real shape is a fused-|| guard + cfe DAG-share. tail3a TRUNCATE_TEXT
 * reduced 0x1710 -> 0x1628. */

/* func_000118E4 + func_0001195C split out to bootup_uso_o0_118E4.c on
 * 2026-05-14 for -O0 build (func_000118E4 was previously NM-wrapped at
 * tail3a's -O2 -g3 OPT_FLAGS; the body's sp+0x1C/0x20/0x24 spill-and-
 * reload shape is unmistakable -O0 IDO emit). */

/* func_00011A34 split out to bootup_uso_o0_11A34.c on 2026-05-08
 * (verified byte-exact at -O0). The following 11AB4..11C70 gap lives in
 * bootup_uso_tail3a_mid.c as INCLUDE_ASM to keep the .text layout
 * contiguous before the existing 11C70 split.
 *
 * func_00011C70 split out to bootup_uso_o0_11C70.c on 2026-05-07 (verified
 * byte-exact at -O0). func_00011CA4 + func_00011CD8 also moved into that
 * file as INCLUDE_ASM stubs (INCLUDE_ASM is opt-level-independent) so the
 * 11C70..11D40 .o region is contiguous; they migrate to C bodies in
 * future passes when individually verified at -O0.
 * func_00011D40 split out to bootup_uso_o0_11D40.c on 2026-05-07.
 * func_00011D70 onwards split out to bootup_uso_tail3a_bot.c. */
