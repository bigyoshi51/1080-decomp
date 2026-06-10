/* vram 0x19B8: 2-word stolen-prologue orphan between func_00001908 and */
/* func_000019C0 (lui $at,0x3F80; mtc1 $at,$f0 = loads 1.0f into $f0 ahead */
/* of 19C0's entry; 19C0's body stores $f0 with no in-fn set -- this is */
/* where the value comes from). Emitted as a standalone 2-word GLOBAL_ASM */
/* block (exact: skip-1 + 1 filler placeholder = 8 bytes). Replaces the */
/* banned SUFFIX_BYTES absorption that was removed 2026-05-23. */
glabel _orphan_timproc_b1_000019B8, local
    /* 0019B8 000019B8 3C013F80 */  .word 0x3C013F80
    /* 0019BC 000019BC 44810000 */  .word 0x44810000
endlabel _orphan_timproc_b1_000019B8
