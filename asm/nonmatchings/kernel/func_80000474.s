
nonmatching func_80000474, 0xC

glabel func_80000474
    /* 1474 80000474 3C018001 */  lui        $at, %hi(D_8000A2E0)
    /* 1478 80000478 03E00008 */  jr         $ra
    /* 147C 8000047C AC24A2E0 */   sw        $a0, %lo(D_8000A2E0)($at)
endlabel func_80000474
