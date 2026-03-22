
nonmatching func_80001460, 0x10

glabel func_80001460
    /* 2460 80001460 8C8E000C */  lw         $t6, 0xC($a0)
    /* 2464 80001464 8C8F0004 */  lw         $t7, 0x4($a0)
    /* 2468 80001468 03E00008 */  jr         $ra
    /* 246C 8000146C 01CF1021 */   addu      $v0, $t6, $t7
endlabel func_80001460
