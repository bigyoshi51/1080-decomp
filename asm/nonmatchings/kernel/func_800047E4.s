
nonmatching func_800047E4, 0x24

glabel func_800047E4
    /* 57E4 800047E4 014D7025 */  or         $t6, $t2, $t5
    /* 57E8 800047E8 AFAE0004 */  sw         $t6, 0x4($sp)
    /* 57EC 800047EC 908F0003 */  lbu        $t7, 0x3($a0)
    /* 57F0 800047F0 31F900FF */  andi       $t9, $t7, 0xFF
    /* 57F4 800047F4 01D94025 */  or         $t0, $t6, $t9
    /* 57F8 800047F8 AFA80004 */  sw         $t0, 0x4($sp)
    /* 57FC 800047FC 27BD0008 */  addiu      $sp, $sp, 0x8
    /* 5800 80004800 03E00008 */  jr         $ra
    /* 5804 80004804 01001025 */   or        $v0, $t0, $zero
endlabel func_800047E4
