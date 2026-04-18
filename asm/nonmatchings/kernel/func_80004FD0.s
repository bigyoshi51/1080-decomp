
nonmatching func_80004FD0, 0x2C

glabel func_80004FD0
    /* 5FD0 80004FD0 3C0E8001 */  lui        $t6, %hi(D_8000A410)
    /* 5FD4 80004FD4 3C0F8001 */  lui        $t7, %hi(D_8000A410)
    /* 5FD8 80004FD8 25CEA410 */  addiu      $t6, $t6, %lo(D_8000A410)
    /* 5FDC 80004FDC 25EFA410 */  addiu      $t7, $t7, %lo(D_8000A410)
    /* 5FE0 80004FE0 AC8E0000 */  sw         $t6, 0x0($a0)
    /* 5FE4 80004FE4 AC8F0004 */  sw         $t7, 0x4($a0)
    /* 5FE8 80004FE8 AC800008 */  sw         $zero, 0x8($a0)
    /* 5FEC 80004FEC AC80000C */  sw         $zero, 0xC($a0)
    /* 5FF0 80004FF0 AC860010 */  sw         $a2, 0x10($a0)
    /* 5FF4 80004FF4 03E00008 */  jr         $ra
    /* 5FF8 80004FF8 AC850014 */   sw        $a1, 0x14($a0)
    /* 5FFC 80004FFC 00000000 */  nop
endlabel func_80004FD0
