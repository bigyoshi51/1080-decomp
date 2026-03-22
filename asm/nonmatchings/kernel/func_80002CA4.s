
nonmatching func_80002CA4, 0x2C

glabel func_80002CA4
    /* 3CA4 80002CA4 AFA40000 */  sw         $a0, 0x0($sp)
    /* 3CA8 80002CA8 AFA50004 */  sw         $a1, 0x4($sp)
    /* 3CAC 80002CAC AFA60008 */  sw         $a2, 0x8($sp)
    /* 3CB0 80002CB0 AFA7000C */  sw         $a3, 0xC($sp)
    /* 3CB4 80002CB4 DFAF0008 */  ld         $t7, 0x8($sp)
    /* 3CB8 80002CB8 DFAE0000 */  ld         $t6, 0x0($sp)
    /* 3CBC 80002CBC 01EE1017 */  dsrav      $v0, $t6, $t7
    /* 3CC0 80002CC0 0002183C */  dsll32     $v1, $v0, 0
    /* 3CC4 80002CC4 0003183F */  dsra32     $v1, $v1, 0
    /* 3CC8 80002CC8 03E00008 */  jr         $ra
    /* 3CCC 80002CCC 0002103F */   dsra32    $v0, $v0, 0
endlabel func_80002CA4
