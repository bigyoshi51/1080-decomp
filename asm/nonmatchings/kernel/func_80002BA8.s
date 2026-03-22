
nonmatching func_80002BA8, 0x60

glabel func_80002BA8
    /* 3BA8 80002BA8 87AF0012 */  lh         $t7, 0x12($sp)
    /* 3BAC 80002BAC AFA60008 */  sw         $a2, 0x8($sp)
    /* 3BB0 80002BB0 AFA7000C */  sw         $a3, 0xC($sp)
    /* 3BB4 80002BB4 DFAE0008 */  ld         $t6, 0x8($sp)
    /* 3BB8 80002BB8 01E0C025 */  or         $t8, $t7, $zero
    /* 3BBC 80002BBC 0300C825 */  or         $t9, $t8, $zero
    /* 3BC0 80002BC0 01D9001F */  ddivu      $zero, $t6, $t9
    /* 3BC4 80002BC4 17200002 */  bnez       $t9, .L80002BD0
    /* 3BC8 80002BC8 00000000 */   nop
    /* 3BCC 80002BCC 0007000D */  break      7
  .L80002BD0:
    /* 3BD0 80002BD0 00004012 */  mflo       $t0
    /* 3BD4 80002BD4 FC880000 */  sd         $t0, 0x0($a0)
    /* 3BD8 80002BD8 87AA0012 */  lh         $t2, 0x12($sp)
    /* 3BDC 80002BDC DFA90008 */  ld         $t1, 0x8($sp)
    /* 3BE0 80002BE0 01405825 */  or         $t3, $t2, $zero
    /* 3BE4 80002BE4 01606025 */  or         $t4, $t3, $zero
    /* 3BE8 80002BE8 012C001F */  ddivu      $zero, $t1, $t4
    /* 3BEC 80002BEC 15800002 */  bnez       $t4, .L80002BF8
    /* 3BF0 80002BF0 00000000 */   nop
    /* 3BF4 80002BF4 0007000D */  break      7
  .L80002BF8:
    /* 3BF8 80002BF8 00006810 */  mfhi       $t5
    /* 3BFC 80002BFC FCAD0000 */  sd         $t5, 0x0($a1)
    /* 3C00 80002C00 03E00008 */  jr         $ra
    /* 3C04 80002C04 00000000 */   nop
endlabel func_80002BA8
