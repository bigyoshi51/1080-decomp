
/* Handwritten function */
nonmatching func_80002DF0, 0x74

glabel func_80002DF0
    /* 3DF0 80002DF0 18A00011 */  blez       $a1, .L80002E38
    /* 3DF4 80002DF4 00000000 */   nop
    /* 3DF8 80002DF8 240B2000 */  addiu      $t3, $zero, 0x2000
    /* 3DFC 80002DFC 00AB082B */  sltu       $at, $a1, $t3
    /* 3E00 80002E00 1020000F */  beqz       $at, .L80002E40
    /* 3E04 80002E04 00000000 */   nop
    /* 3E08 80002E08 00804025 */  or         $t0, $a0, $zero
    /* 3E0C 80002E0C 00854821 */  addu       $t1, $a0, $a1
    /* 3E10 80002E10 0109082B */  sltu       $at, $t0, $t1
    /* 3E14 80002E14 10200008 */  beqz       $at, .L80002E38
    /* 3E18 80002E18 00000000 */   nop
    /* 3E1C 80002E1C 310A000F */  andi       $t2, $t0, 0xF
    /* 3E20 80002E20 2529FFF0 */  addiu      $t1, $t1, -0x10
    /* 3E24 80002E24 010A4023 */  subu       $t0, $t0, $t2
  .L80002E28:
    /* 3E28 80002E28 BD190000 */  cache      0x19, 0x0($t0) /* handwritten instruction */
    /* 3E2C 80002E2C 0109082B */  sltu       $at, $t0, $t1
    /* 3E30 80002E30 1420FFFD */  bnez       $at, .L80002E28
    /* 3E34 80002E34 25080010 */   addiu     $t0, $t0, 0x10
  .L80002E38:
    /* 3E38 80002E38 03E00008 */  jr         $ra
    /* 3E3C 80002E3C 00000000 */   nop
  .L80002E40:
    /* 3E40 80002E40 3C088000 */  lui        $t0, 0x8000
    /* 3E44 80002E44 010B4821 */  addu       $t1, $t0, $t3
    /* 3E48 80002E48 2529FFF0 */  addiu      $t1, $t1, -0x10
  .L80002E4C:
    /* 3E4C 80002E4C BD010000 */  cache      0x01, 0x0($t0) /* handwritten instruction */
    /* 3E50 80002E50 0109082B */  sltu       $at, $t0, $t1
    /* 3E54 80002E54 1420FFFD */  bnez       $at, .L80002E4C
    /* 3E58 80002E58 25080010 */   addiu     $t0, $t0, (0x80000010 & 0xFFFF)
    /* 3E5C 80002E5C 03E00008 */  jr         $ra
    /* 3E60 80002E60 00000000 */   nop
endlabel func_80002DF0
    /* 3E64 80002E64 00000000 */  nop
    /* 3E68 80002E68 00000000 */  nop
    /* 3E6C 80002E6C 00000000 */  nop
