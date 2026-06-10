/* vram 0x1BD4: 4-word stolen-prologue donation between func_00001B58 and */
/* func_00001BE4 (move $a2,$a0; lui $a0,%hi(D); addiu $a0; lw $v1,0x64($a0) */
/* -- 1BE4 reads $a2/$a0/$v1 set up by these insns; see 1B58's wrap doc). */
/* Standalone >=2-word GLOBAL_ASM block emits exactly; replaces the banned */
/* SUFFIX_BYTES absorption removed 2026-05-23. */
glabel _orphan_mgrproc_00001BD4, local
    /* 001BD4 00001BD4 00803025 */  .word 0x00803025
    /* 001BD8 00001BD8 3C040000 */  .word 0x3C040000
    /* 001BDC 00001BDC 24840000 */  .word 0x24840000
    /* 001BE0 00001BE0 8C830064 */  .word 0x8C830064
endlabel _orphan_mgrproc_00001BD4
