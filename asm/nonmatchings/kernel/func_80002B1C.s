
nonmatching func_80002B1C, 0x5C

glabel func_80002B1C
    /* 3B1C 80002B1C AFA40000 */  sw         $a0, 0x0($sp)
    /* 3B20 80002B20 AFA50004 */  sw         $a1, 0x4($sp)
    /* 3B24 80002B24 AFA60008 */  sw         $a2, 0x8($sp)
    /* 3B28 80002B28 AFA7000C */  sw         $a3, 0xC($sp)
    /* 3B2C 80002B2C DFAF0008 */  ld         $t7, 0x8($sp)
    /* 3B30 80002B30 DFAE0000 */  ld         $t6, 0x0($sp)
    /* 3B34 80002B34 01CF001E */  ddiv       $zero, $t6, $t7
    /* 3B38 80002B38 00000000 */  nop
    /* 3B3C 80002B3C 15E00002 */  bnez       $t7, .L80002B48
    /* 3B40 80002B40 00000000 */   nop
    /* 3B44 80002B44 0007000D */  break      7
  .L80002B48:
    /* 3B48 80002B48 6401FFFF */  daddiu     $at, $zero, -0x1
    /* 3B4C 80002B4C 15E10005 */  bne        $t7, $at, .L80002B64
    /* 3B50 80002B50 64010001 */   daddiu    $at, $zero, 0x1
    /* 3B54 80002B54 00010FFC */  dsll32     $at, $at, 31
    /* 3B58 80002B58 15C10002 */  bne        $t6, $at, .L80002B64
    /* 3B5C 80002B5C 00000000 */   nop
    /* 3B60 80002B60 0006000D */  break      6
  .L80002B64:
    /* 3B64 80002B64 00001012 */  mflo       $v0
    /* 3B68 80002B68 0002183C */  dsll32     $v1, $v0, 0
    /* 3B6C 80002B6C 0003183F */  dsra32     $v1, $v1, 0
    /* 3B70 80002B70 03E00008 */  jr         $ra
    /* 3B74 80002B74 0002103F */   dsra32    $v0, $v0, 0
endlabel func_80002B1C
