
/* Handwritten function */
nonmatching func_80009CE0, 0x28

glabel func_80009CE0
    /* ACE0 80009CE0 3C088000 */  lui        $t0, 0x8000
    /* ACE4 80009CE4 240A2000 */  addiu      $t2, $zero, 0x2000
    /* ACE8 80009CE8 010A4821 */  addu       $t1, $t0, $t2
    /* ACEC 80009CEC 2529FFF0 */  addiu      $t1, $t1, -0x10
  .L80009CF0:
    /* ACF0 80009CF0 BD010000 */  cache      0x01, 0x0($t0) /* handwritten instruction */
    /* ACF4 80009CF4 0109082B */  sltu       $at, $t0, $t1
    /* ACF8 80009CF8 1420FFFD */  bnez       $at, .L80009CF0
    /* ACFC 80009CFC 25080010 */   addiu     $t0, $t0, (0x80000010 & 0xFFFF)
    /* AD00 80009D00 03E00008 */  jr         $ra
    /* AD04 80009D04 00000000 */   nop
endlabel func_80009CE0
    /* AD08 80009D08 00000000 */  nop
    /* AD0C 80009D0C 00000000 */  nop
