#include "common.h"

/* 2026-06-10 kernel-relayout: the old `_pad` GLOBAL_ASM sidecars
 * (D_80009E60_pad.s, func_80009EB0_pad.s) emitted into .TEXT (glabel
 * blocks default to .text) — an anonymous 0x30 .text block that does not
 * exist in ROM. The 0x20 of trailing zeros after D_80009E60 is .rodata
 * truth and now lives inside D_80009E60.s itself; the 1-word pad after
 * func_80009EB0 was pure drift compensation (ROM has the kernel data
 * asset directly at 0x80009FD0) and is deleted. */

INCLUDE_ASM("asm/nonmatchings/kernel", D_80009E60);

/* SOURCE=3 skip: this symbol is real `.rodata`, not code. The asm file
 * declares `.section .rodata` and contains four `.word D_8000A5*` entries.
 * See docs/PATTERNS.md#feedback-word-only-skip-rule-doesnt-block-episode-logging:
 * this is the data-misidentified-as-code case, not a `.word`-encoded USO
 * function. Do not try to decompile it as C. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009EA0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009EB0);
