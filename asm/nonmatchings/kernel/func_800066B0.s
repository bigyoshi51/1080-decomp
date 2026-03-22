
nonmatching func_800066B0, 0x20

glabel func_800066B0
    /* 76B0 800066B0 14200009 */  bnez       $at, .L800066D8
    /* 76B4 800066B4 3C010500 */   lui       $at, (0x5000000 >> 16)
    /* 76B8 800066B8 01C1082B */  sltu       $at, $t6, $at
    /* 76BC 800066BC 10200006 */  beqz       $at, .L800066D8
    /* 76C0 800066C0 00000000 */   nop
    /* 76C4 800066C4 01C02025 */  or         $a0, $t6, $zero
    /* 76C8 800066C8 0C0023EC */  jal        func_80008FB0
    /* 76CC 800066CC 27A5001C */   addiu     $a1, $sp, 0x1C
endlabel func_800066B0
