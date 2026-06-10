/* vram 0x2238: 2-word stolen-prologue orphan between func_000021F4 and */
/* func_00002240 (lui $a0,%hi(D); lw $a0,0x148($a0) hoisted ahead of */
/* 2240's prologue; twin of timproc_uso_b1's 0x2028 orphan). Standalone */
/* 2-word GLOBAL_ASM block emits exactly. */
glabel _orphan_timproc_b3_00002238, local
    /* 002238 00002238 3C040000 */  .word 0x3C040000
    /* 00223C 0000223C 8C840148 */  .word 0x8C840148
endlabel _orphan_timproc_b3_00002238
