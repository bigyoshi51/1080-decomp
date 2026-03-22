
nonmatching func_800047B0, 0x34

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
endlabel func_800047B0
