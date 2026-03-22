
/* Handwritten function */
nonmatching func_800062B0, 0x20

glabel func_800062B0
    /* 72B0 800062B0 40086000 */  mfc0       $t0, $12 /* handwritten instruction */
    /* 72B4 800062B4 2401FFFE */  addiu      $at, $zero, -0x2
    /* 72B8 800062B8 01014824 */  and        $t1, $t0, $at
    /* 72BC 800062BC 40896000 */  mtc0       $t1, $12 /* handwritten instruction */
    /* 72C0 800062C0 31020001 */  andi       $v0, $t0, 0x1
    /* 72C4 800062C4 00000000 */  nop
    /* 72C8 800062C8 03E00008 */  jr         $ra
    /* 72CC 800062CC 00000000 */   nop
endlabel func_800062B0
