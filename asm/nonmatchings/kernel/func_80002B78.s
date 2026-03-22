
nonmatching func_80002B78, 0x30

glabel func_80002B78
    /* 3B78 80002B78 AFA40000 */  sw         $a0, 0x0($sp)
    /* 3B7C 80002B7C AFA50004 */  sw         $a1, 0x4($sp)
    /* 3B80 80002B80 AFA60008 */  sw         $a2, 0x8($sp)
    /* 3B84 80002B84 AFA7000C */  sw         $a3, 0xC($sp)
    /* 3B88 80002B88 DFAF0008 */  ld         $t7, 0x8($sp)
    /* 3B8C 80002B8C DFAE0000 */  ld         $t6, 0x0($sp)
    /* 3B90 80002B90 01CF001D */  dmultu     $t6, $t7
    /* 3B94 80002B94 00001012 */  mflo       $v0
    /* 3B98 80002B98 0002183C */  dsll32     $v1, $v0, 0
    /* 3B9C 80002B9C 0003183F */  dsra32     $v1, $v1, 0
    /* 3BA0 80002BA0 03E00008 */  jr         $ra
    /* 3BA4 80002BA4 0002103F */   dsra32    $v0, $v0, 0
endlabel func_80002B78
