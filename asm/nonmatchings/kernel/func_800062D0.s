
/* Handwritten function */
nonmatching func_800062D0, 0x1C

glabel func_800062D0
    /* 72D0 800062D0 40086000 */  mfc0       $t0, $12 /* handwritten instruction */
    /* 72D4 800062D4 01044025 */  or         $t0, $t0, $a0
    /* 72D8 800062D8 40886000 */  mtc0       $t0, $12 /* handwritten instruction */
    /* 72DC 800062DC 00000000 */  nop
    /* 72E0 800062E0 00000000 */  nop
    /* 72E4 800062E4 03E00008 */  jr         $ra
    /* 72E8 800062E8 00000000 */   nop
endlabel func_800062D0
    /* 72EC 800062EC 00000000 */  nop
