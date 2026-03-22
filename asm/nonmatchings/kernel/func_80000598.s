
nonmatching func_80000598, 0x40

glabel func_80000598
    /* 1598 80000598 00C03825 */  or         $a3, $a2, $zero
    /* 159C 8000059C 00801025 */  or         $v0, $a0, $zero
    /* 15A0 800005A0 00A01825 */  or         $v1, $a1, $zero
    /* 15A4 800005A4 10C0000A */  beqz       $a2, .L800005D0
    /* 15A8 800005A8 24C6FFFF */   addiu     $a2, $a2, -0x1
  .L800005AC:
    /* 15AC 800005AC 00402025 */  or         $a0, $v0, $zero
    /* 15B0 800005B0 908E0000 */  lbu        $t6, 0x0($a0)
    /* 15B4 800005B4 00603825 */  or         $a3, $v1, $zero
    /* 15B8 800005B8 00C02825 */  or         $a1, $a2, $zero
    /* 15BC 800005BC 24630001 */  addiu      $v1, $v1, 0x1
    /* 15C0 800005C0 24420001 */  addiu      $v0, $v0, 0x1
    /* 15C4 800005C4 A0EE0000 */  sb         $t6, 0x0($a3)
    /* 15C8 800005C8 14C0FFF8 */  bnez       $a2, .L800005AC
    /* 15CC 800005CC 24C6FFFF */   addiu     $a2, $a2, -0x1
  .L800005D0:
    /* 15D0 800005D0 03E00008 */  jr         $ra
    /* 15D4 800005D4 00000000 */   nop
endlabel func_80000598
