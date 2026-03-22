
nonmatching func_80002AE0, 0x3C

glabel func_80002AE0
    /* 3AE0 80002AE0 AFA40000 */  sw         $a0, 0x0($sp)
    /* 3AE4 80002AE4 AFA50004 */  sw         $a1, 0x4($sp)
    /* 3AE8 80002AE8 AFA60008 */  sw         $a2, 0x8($sp)
    /* 3AEC 80002AEC AFA7000C */  sw         $a3, 0xC($sp)
    /* 3AF0 80002AF0 DFAF0008 */  ld         $t7, 0x8($sp)
    /* 3AF4 80002AF4 DFAE0000 */  ld         $t6, 0x0($sp)
    /* 3AF8 80002AF8 01CF001F */  ddivu      $zero, $t6, $t7
    /* 3AFC 80002AFC 15E00002 */  bnez       $t7, .L80002B08
    /* 3B00 80002B00 00000000 */   nop
    /* 3B04 80002B04 0007000D */  break      7
  .L80002B08:
    /* 3B08 80002B08 00001010 */  mfhi       $v0
    /* 3B0C 80002B0C 0002183C */  dsll32     $v1, $v0, 0
    /* 3B10 80002B10 0003183F */  dsra32     $v1, $v1, 0
    /* 3B14 80002B14 03E00008 */  jr         $ra
    /* 3B18 80002B18 0002103F */   dsra32    $v0, $v0, 0
endlabel func_80002AE0
