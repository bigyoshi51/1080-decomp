
nonmatching func_800056C0, 0x2C

glabel func_800056C0
    /* 66C0 800056C0 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 66C4 800056C4 2401FFFF */  addiu      $at, $zero, -0x1
    /* 66C8 800056C8 11C10004 */  beq        $t6, $at, .L800056DC
    /* 66CC 800056CC 00000000 */   nop
    /* 66D0 800056D0 00002025 */  or         $a0, $zero, $zero
    /* 66D4 800056D4 0C001944 */  jal        func_80006510
    /* 66D8 800056D8 01C02825 */   or        $a1, $t6, $zero
  .L800056DC:
    /* 66DC 800056DC 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 66E0 800056E0 27BD0030 */  addiu      $sp, $sp, 0x30
    /* 66E4 800056E4 03E00008 */  jr         $ra
    /* 66E8 800056E8 00000000 */   nop
endlabel func_800056C0
