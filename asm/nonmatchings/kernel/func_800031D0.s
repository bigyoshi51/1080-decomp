
/* Handwritten function */
nonmatching func_800031D0, 0x10

glabel func_800031D0
    /* 41D0 800031D0 00085202 */  srl        $t2, $t0, 8
    /* 41D4 800031D4 314A00FF */  andi       $t2, $t2, 0xFF
    /* 41D8 800031D8 2129FFFF */  addi       $t1, $t1, -0x1 /* handwritten instruction */
    /* 41DC 800031DC A16A0000 */  sb         $t2, 0x0($t3)
endlabel func_800031D0
