
nonmatching func_80006640, 0x44

glabel func_80006640
    /* 7640 80006640 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 7644 80006644 03E00008 */  jr         $ra
    /* 7648 80006648 00000000 */   nop
endlabel func_80006640
    /* 764C 8000664C 00000000 */  nop

/* glabel func_80006698 */
    /* 7698 80006698 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 769C 8000669C AFA40020 */  sw         $a0, 0x20($sp)
    /* 76A0 800066A0 8FAE0020 */  lw         $t6, 0x20($sp)
    /* 76A4 800066A4 3C010400 */  lui        $at, (0x4000000 >> 16)
    /* 76A8 800066A8 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 76AC 800066AC 01C1082B */  sltu       $at, $t6, $at
/* glabel func_800066B0 */
    /* 76B0 800066B0 14200009 */  bnez       $at, .L800066D8
    /* 76B4 800066B4 3C010500 */   lui       $at, (0x5000000 >> 16)
    /* 76B8 800066B8 01C1082B */  sltu       $at, $t6, $at
    /* 76BC 800066BC 10200006 */  beqz       $at, .L800066D8
    /* 76C0 800066C0 00000000 */   nop
    /* 76C4 800066C4 01C02025 */  or         $a0, $t6, $zero
    /* 76C8 800066C8 0C0023EC */  jal        func_80008FB0
    /* 76CC 800066CC 27A5001C */   addiu     $a1, $sp, 0x1C
endlabel func_80006640
