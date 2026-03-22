
/* Handwritten function */
nonmatching func_80002DB0, 0x30

glabel func_80002DB0
    /* 3DB0 80002DB0 00000000 */  nop
    /* 3DB4 80002DB4 00000000 */  nop
    /* 3DB8 80002DB8 00000000 */  nop
    /* 3DBC 80002DBC 00000000 */  nop
    /* 3DC0 80002DC0 00000000 */  nop
    /* 3DC4 80002DC4 00000000 */  nop
    /* 3DC8 80002DC8 00000000 */  nop
    /* 3DCC 80002DCC 00000000 */  nop
    /* 3DD0 80002DD0 40846000 */  mtc0       $a0, $12 /* handwritten instruction */
    /* 3DD4 80002DD4 00000000 */  nop
    /* 3DD8 80002DD8 03E00008 */  jr         $ra
    /* 3DDC 80002DDC 00000000 */   nop
endlabel func_80002DB0
