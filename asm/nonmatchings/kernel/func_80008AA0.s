
nonmatching func_80008AA0, 0x30

glabel func_80008AA0
    /* 9AA0 80008AA0 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 9AA4 80008AA4 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 9AA8 80008AA8 0C001DD8 */  jal        func_80007760
    /* 9AAC 80008AAC 00000000 */   nop
    /* 9AB0 80008AB0 0C001E17 */  jal        func_8000785C
    /* 9AB4 80008AB4 00002025 */   or        $a0, $zero, $zero
    /* 9AB8 80008AB8 0C0023B4 */  jal        func_80008ED0
    /* 9ABC 80008ABC 00000000 */   nop
    /* 9AC0 80008AC0 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 9AC4 80008AC4 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 9AC8 80008AC8 03E00008 */  jr         $ra
    /* 9ACC 80008ACC 00000000 */   nop
endlabel func_80008AA0
