
nonmatching func_80000A88, 0x10

glabel func_80000A88
    /* 1A88 80000A88 3C018001 */  lui        $at, %hi(D_8000A2D8)
    /* 1A8C 80000A8C 3C118001 */  lui        $s1, (0x80010000 >> 16)
    /* 1A90 80000A90 AC2EA2D8 */  sw         $t6, %lo(D_8000A2D8)($at)
    /* 1A94 80000A94 8C4F0004 */  lw         $t7, 0x4($v0)
endlabel func_80000A88
