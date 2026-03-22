
nonmatching func_80002A3C, 0x3C

glabel func_80002A3C
    /* 3A3C 80002A3C AFA40000 */  sw         $a0, 0x0($sp)
    /* 3A40 80002A40 AFA50004 */  sw         $a1, 0x4($sp)
    /* 3A44 80002A44 AFA60008 */  sw         $a2, 0x8($sp)
    /* 3A48 80002A48 AFA7000C */  sw         $a3, 0xC($sp)
    /* 3A4C 80002A4C DFAF0008 */  ld         $t7, 0x8($sp)
    /* 3A50 80002A50 DFAE0000 */  ld         $t6, 0x0($sp)
    /* 3A54 80002A54 01CF001F */  ddivu      $zero, $t6, $t7
    /* 3A58 80002A58 15E00002 */  bnez       $t7, .L80002A64
    /* 3A5C 80002A5C 00000000 */   nop
    /* 3A60 80002A60 0007000D */  break      7
  .L80002A64:
    /* 3A64 80002A64 00001010 */  mfhi       $v0
    /* 3A68 80002A68 0002183C */  dsll32     $v1, $v0, 0
    /* 3A6C 80002A6C 0003183F */  dsra32     $v1, $v1, 0
    /* 3A70 80002A70 03E00008 */  jr         $ra
    /* 3A74 80002A74 0002103F */   dsra32    $v0, $v0, 0
endlabel func_80002A3C
