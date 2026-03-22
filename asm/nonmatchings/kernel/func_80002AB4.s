
nonmatching func_80002AB4, 0x2C

glabel func_80002AB4
    /* 3AB4 80002AB4 AFA40000 */  sw         $a0, 0x0($sp)
    /* 3AB8 80002AB8 AFA50004 */  sw         $a1, 0x4($sp)
    /* 3ABC 80002ABC AFA60008 */  sw         $a2, 0x8($sp)
    /* 3AC0 80002AC0 AFA7000C */  sw         $a3, 0xC($sp)
    /* 3AC4 80002AC4 DFAF0008 */  ld         $t7, 0x8($sp)
    /* 3AC8 80002AC8 DFAE0000 */  ld         $t6, 0x0($sp)
    /* 3ACC 80002ACC 01EE1014 */  dsllv      $v0, $t6, $t7
    /* 3AD0 80002AD0 0002183C */  dsll32     $v1, $v0, 0
    /* 3AD4 80002AD4 0003183F */  dsra32     $v1, $v1, 0
    /* 3AD8 80002AD8 03E00008 */  jr         $ra
    /* 3ADC 80002ADC 0002103F */   dsra32    $v0, $v0, 0
endlabel func_80002AB4
