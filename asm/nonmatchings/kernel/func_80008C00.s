
nonmatching func_80008C00, 0x2C

glabel func_80008C00
    /* 9C00 80008C00 3C0EA404 */  lui        $t6, %hi(D_A4040010)
    /* 9C04 80008C04 8DC40010 */  lw         $a0, %lo(D_A4040010)($t6)
    /* 9C08 80008C08 27BDFFF8 */  addiu      $sp, $sp, -0x8
    /* 9C0C 80008C0C 308F001C */  andi       $t7, $a0, 0x1C
    /* 9C10 80008C10 11E00003 */  beqz       $t7, .L80008C20
    /* 9C14 80008C14 00000000 */   nop
    /* 9C18 80008C18 10000002 */  b          .L80008C24
    /* 9C1C 80008C1C 24020001 */   addiu     $v0, $zero, 0x1
  .L80008C20:
    /* 9C20 80008C20 00001025 */  or         $v0, $zero, $zero
  .L80008C24:
    /* 9C24 80008C24 03E00008 */  jr         $ra
    /* 9C28 80008C28 27BD0008 */   addiu     $sp, $sp, 0x8
endlabel func_80008C00
    /* 9C2C 80008C2C 00000000 */  nop
