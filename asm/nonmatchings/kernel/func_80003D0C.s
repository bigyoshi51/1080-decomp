
nonmatching func_80003D0C, 0x28

glabel func_80003D0C
    /* 4D0C 80003D0C 0C000F99 */  jal        func_80003E64
    /* 4D10 80003D10 00000000 */   nop
  .L80003D14:
    /* 4D14 80003D14 0C0019B4 */  jal        func_800066D0
    /* 4D18 80003D18 02002025 */   or        $a0, $s0, $zero
    /* 4D1C 80003D1C 8FBF0024 */  lw         $ra, 0x24($sp)
    /* 4D20 80003D20 8FB00018 */  lw         $s0, 0x18($sp)
    /* 4D24 80003D24 8FB1001C */  lw         $s1, 0x1C($sp)
    /* 4D28 80003D28 8FB20020 */  lw         $s2, 0x20($sp)
    /* 4D2C 80003D2C 03E00008 */  jr         $ra
    /* 4D30 80003D30 27BD0038 */   addiu     $sp, $sp, 0x38
endlabel func_80003D0C
    /* 4D34 80003D34 00000000 */  nop
    /* 4D38 80003D38 00000000 */  nop
    /* 4D3C 80003D3C 00000000 */  nop
