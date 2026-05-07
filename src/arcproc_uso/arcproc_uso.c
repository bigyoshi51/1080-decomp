#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;

/* USO entry-0: leading `beq zero,zero,+0x6F00` trampoline (loader-patched
 * at runtime) followed by the standard int-reader template body at -O0.
 * The 4-byte trampoline is injected post-cc by scripts/inject-prefix-bytes.py
 * (per PREFIX_BYTES Makefile var); the body is compiled at -O0 via the
 * arcproc_uso.c.o OPT_FLAGS override. The script inserts the bytes at the
 * function's start, shifts subsequent symbols, and grows the function symbol
 * to cover the full 0x50-byte target extent.
 *
 * Fuzzy cap (95.00%, intentional): byte-correct ROM build matches expected
 * EXACTLY (the post-cc PREFIX_BYTES injection runs only on build/, not on
 * build/non_matching/). objdiff scores the non_matching .o (19 insns, no
 * trampoline) against expected (20 insns, with trampoline) → 19/20 = 95%.
 * This is the design — feedback_non_matching_build_for_fuzzy_scoring.md
 * keeps fuzzy as a "C-only" metric; post-cc tricks are excluded. There is
 * no C-level lever that emits an arbitrary `0x10006F00` word BEFORE the
 * function's prologue (IDO doesn't parse __asm__; goto-far requires a real
 * label at +0x6F00 bytes). 95% is the structural fuzzy cap; the function
 * IS byte-correct in the actual ROM. Same class as boarder5_uso_func_00000000,
 * eddproc_uso_func_00000000, n64proc_uso_func_00000000, h2hproc_uso_func_00000000. */
void arcproc_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

