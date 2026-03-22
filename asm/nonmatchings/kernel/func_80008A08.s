
nonmatching func_80008A08, 0x30

glabel func_80008A08
    /* 9A08 80008A08 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 9A0C 80008A0C AFBF0014 */  sw         $ra, 0x14($sp)
    /* 9A10 80008A10 0C00215F */  jal        func_8000857C
    /* 9A14 80008A14 00000000 */   nop
    /* 9A18 80008A18 0C001E17 */  jal        func_8000785C
    /* 9A1C 80008A1C 00002025 */   or        $a0, $zero, $zero
    /* 9A20 80008A20 0C0023B4 */  jal        func_80008ED0
    /* 9A24 80008A24 00000000 */   nop
    /* 9A28 80008A28 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 9A2C 80008A2C 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 9A30 80008A30 03E00008 */  jr         $ra
    /* 9A34 80008A34 00000000 */   nop
endlabel func_80008A08
