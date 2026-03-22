
nonmatching func_800052C0, 0x2C

glabel func_800052C0
    /* 62C0 800052C0 3C0EA480 */  lui        $t6, %hi(D_A4800018)
    /* 62C4 800052C4 8DC40018 */  lw         $a0, %lo(D_A4800018)($t6)
    /* 62C8 800052C8 27BDFFF8 */  addiu      $sp, $sp, -0x8
    /* 62CC 800052CC 308F0003 */  andi       $t7, $a0, 0x3
    /* 62D0 800052D0 11E00003 */  beqz       $t7, .L800052E0
    /* 62D4 800052D4 00000000 */   nop
    /* 62D8 800052D8 10000002 */  b          .L800052E4
    /* 62DC 800052DC 24020001 */   addiu     $v0, $zero, 0x1
  .L800052E0:
    /* 62E0 800052E0 00001025 */  or         $v0, $zero, $zero
  .L800052E4:
    /* 62E4 800052E4 03E00008 */  jr         $ra
    /* 62E8 800052E8 27BD0008 */   addiu     $sp, $sp, 0x8
endlabel func_800052C0
    /* 62EC 800052EC 00000000 */  nop
