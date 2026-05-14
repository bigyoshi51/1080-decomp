nonmatching func_800047B0, 0x58

glabel func_800047B0
    /* 57B0 800047B0 908E0000 */  lbu        $t6, 0x0($a0)
    /* 57B4 800047B4 27BDFFF8 */  addiu      $sp, $sp, -0x8
    /* 57B8 800047B8 31CF00FF */  andi       $t7, $t6, 0xFF
    /* 57BC 800047BC 000FC600 */  sll        $t8, $t7, 24
    /* 57C0 800047C0 AFB80004 */  sw         $t8, 0x4($sp)
    /* 57C4 800047C4 90990001 */  lbu        $t9, 0x1($a0)
    /* 57C8 800047C8 332800FF */  andi       $t0, $t9, 0xFF
    /* 57CC 800047CC 00084C00 */  sll        $t1, $t0, 16
    /* 57D0 800047D0 03095025 */  or         $t2, $t8, $t1
    /* 57D4 800047D4 AFAA0004 */  sw         $t2, 0x4($sp)
    /* 57D8 800047D8 908B0002 */  lbu        $t3, 0x2($a0)
    /* 57DC 800047DC 316C00FF */  andi       $t4, $t3, 0xFF
    /* 57E0 800047E0 000C6A00 */  sll        $t5, $t4, 8
    /* 57E4 800047E4 014D7025 */  or         $t6, $t2, $t5
    /* 57E8 800047E8 AFAE0004 */  sw         $t6, 0x4($sp)
    /* 57EC 800047EC 908F0003 */  lbu        $t7, 0x3($a0)
    /* 57F0 800047F0 31F900FF */  andi       $t9, $t7, 0xFF
    /* 57F4 800047F4 01D94025 */  or         $t0, $t6, $t9
    /* 57F8 800047F8 AFA80004 */  sw         $t0, 0x4($sp)
    /* 57FC 800047FC 27BD0008 */  addiu      $sp, $sp, 0x8
    /* 5800 80004800 03E00008 */  jr         $ra
    /* 5804 80004804 01001025 */   or        $v0, $t0, $zero
endlabel func_800047B0
