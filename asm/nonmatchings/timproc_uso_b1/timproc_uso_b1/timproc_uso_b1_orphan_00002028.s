/* vram 0x2028: 2-word stolen-prologue orphan between func_00001FE4 and */
/* func_00002030 (lui $a0,%hi(D); lw $a0,0x148($a0) -- an alternate/true */
/* entry head hoisted above 2030's prologue; USO reloc words stored raw). */
/* Standalone 2-word GLOBAL_ASM block emits exactly; replaces the banned */
/* SUFFIX_BYTES absorption removed 2026-05-23. Both neighbor fns stay */
/* matched C. */
glabel _orphan_timproc_b1_00002028, local
    /* 002028 00002028 3C040000 */  .word 0x3C040000
    /* 00202C 0000202C 8C840148 */  .word 0x8C840148
endlabel _orphan_timproc_b1_00002028
