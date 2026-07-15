/* vram 0x22D4: 3-word all-zero inter-function alignment pad between */
/* func_00002244 (ends jr ra; nop at 0x22D0) and func_000022E0. Was */
/* emitted by func_00002244's INCLUDE_ASM tail; restored as a standalone */
/* >=2-word GLOBAL_ASM orphan block (emits exactly at -O2) when 2244 was */
/* promoted to matched C 2026-07-15. NOTE: SUFFIX_BYTES_FORCE injection */
/* is UNSAFE this early in the file — inject-suffix-bytes.py shifts */
/* symbols + reloc r_offsets but NOT in-place HI16/LO16 addends of */
/* section-relative (.text) relocs, so downstream %lo words go stale */
/* (7-word ROM diff observed). The orphan block avoids injection. */
glabel _orphan_bootup_000022D4, local
    /* 0022D4 000022D4 00000000 */  .word 0x00000000
    /* 0022D8 000022D8 00000000 */  .word 0x00000000
    /* 0022DC 000022DC 00000000 */  .word 0x00000000
endlabel _orphan_bootup_000022D4
