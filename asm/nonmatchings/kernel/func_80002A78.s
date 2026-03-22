
nonmatching func_80002A78, 0x3C

glabel func_80002A78
    /* 3A78 80002A78 AFA40000 */  sw         $a0, 0x0($sp)
    /* 3A7C 80002A7C AFA50004 */  sw         $a1, 0x4($sp)
    /* 3A80 80002A80 AFA60008 */  sw         $a2, 0x8($sp)
    /* 3A84 80002A84 AFA7000C */  sw         $a3, 0xC($sp)
    /* 3A88 80002A88 DFAF0008 */  ld         $t7, 0x8($sp)
    /* 3A8C 80002A8C DFAE0000 */  ld         $t6, 0x0($sp)
    /* 3A90 80002A90 01CF001F */  ddivu      $zero, $t6, $t7
    /* 3A94 80002A94 15E00002 */  bnez       $t7, .L80002AA0
    /* 3A98 80002A98 00000000 */   nop
    /* 3A9C 80002A9C 0007000D */  break      7
  .L80002AA0:
    /* 3AA0 80002AA0 00001012 */  mflo       $v0
    /* 3AA4 80002AA4 0002183C */  dsll32     $v1, $v0, 0
    /* 3AA8 80002AA8 0003183F */  dsra32     $v1, $v1, 0
    /* 3AAC 80002AAC 03E00008 */  jr         $ra
    /* 3AB0 80002AB0 0002103F */   dsra32    $v0, $v0, 0
endlabel func_80002A78
