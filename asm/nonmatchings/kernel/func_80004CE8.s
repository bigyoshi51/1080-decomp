
nonmatching func_80004CE8, 0x30

glabel func_80004CE8
    /* 5CE8 80004CE8 27240004 */  addiu      $a0, $t9, 0x4
    /* 5CEC 80004CEC 00408825 */  or         $s1, $v0, $zero
    /* 5CF0 80004CF0 0C002844 */  jal        func_8000A110
    /* 5CF4 80004CF4 02202025 */   or        $a0, $s1, $zero
  .L80004CF8:
    /* 5CF8 80004CF8 0C0019B4 */  jal        func_800066D0
    /* 5CFC 80004CFC 02002025 */   or        $a0, $s0, $zero
    /* 5D00 80004D00 00001025 */  or         $v0, $zero, $zero
  .L80004D04:
    /* 5D04 80004D04 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 5D08 80004D08 8FB00014 */  lw         $s0, 0x14($sp)
    /* 5D0C 80004D0C 8FB10018 */  lw         $s1, 0x18($sp)
    /* 5D10 80004D10 03E00008 */  jr         $ra
    /* 5D14 80004D14 27BD0028 */   addiu     $sp, $sp, 0x28
endlabel func_80004CE8
    /* 5D18 80004D18 00000000 */  nop
    /* 5D1C 80004D1C 00000000 */  nop
