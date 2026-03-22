
/* Handwritten function */
nonmatching func_800031E0, 0x10

glabel func_800031E0
    /* 41E0 800031E0 10090004 */  beq        $zero, $t1, .L800031F4
    /* 41E4 800031E4 216B0001 */   addi      $t3, $t3, 0x1 /* handwritten instruction */
    /* 41E8 800031E8 310800FF */  andi       $t0, $t0, 0xFF
    /* 41EC 800031EC A1680000 */  sb         $t0, 0x0($t3)
endlabel func_800031E0
