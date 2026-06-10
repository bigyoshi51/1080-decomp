/* vram 0x2E34: 2-word FPU-const stolen prologue between func_00002B7C and */
/* func_00002E3C (lui $at,0x3F80; mtc1 $at,$f0 = the 1.0f that 2E3C stores */
/* from $f0 -- see 2E3C's wrap doc; twin of timproc_uso_b1's 0x19B8 orphan). */
/* Standalone 2-word GLOBAL_ASM block emits exactly. */
glabel _orphan_mgrproc_00002E34, local
    /* 002E34 00002E34 3C013F80 */  .word 0x3C013F80
    /* 002E38 00002E38 44810000 */  .word 0x44810000
endlabel _orphan_mgrproc_00002E34
