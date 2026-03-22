
nonmatching func_80002A10, 0x2C

glabel func_80002A10
    /* 3A10 80002A10 AFA40000 */  sw         $a0, 0x0($sp)
    /* 3A14 80002A14 AFA50004 */  sw         $a1, 0x4($sp)
    /* 3A18 80002A18 AFA60008 */  sw         $a2, 0x8($sp)
    /* 3A1C 80002A1C AFA7000C */  sw         $a3, 0xC($sp)
    /* 3A20 80002A20 DFAF0008 */  ld         $t7, 0x8($sp)
    /* 3A24 80002A24 DFAE0000 */  ld         $t6, 0x0($sp)
    /* 3A28 80002A28 01EE1016 */  dsrlv      $v0, $t6, $t7
    /* 3A2C 80002A2C 0002183C */  dsll32     $v1, $v0, 0
    /* 3A30 80002A30 0003183F */  dsra32     $v1, $v1, 0
    /* 3A34 80002A34 03E00008 */  jr         $ra
    /* 3A38 80002A38 0002103F */   dsra32    $v0, $v0, 0
endlabel func_80002A10
