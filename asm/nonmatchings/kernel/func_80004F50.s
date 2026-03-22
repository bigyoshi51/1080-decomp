
/* Handwritten function */
nonmatching func_80004F50, 0x74

glabel func_80004F50
    /* 5F50 80004F50 18A00011 */  blez       $a1, .L80004F98
    /* 5F54 80004F54 00000000 */   nop
    /* 5F58 80004F58 240B4000 */  addiu      $t3, $zero, 0x4000
    /* 5F5C 80004F5C 00AB082B */  sltu       $at, $a1, $t3
    /* 5F60 80004F60 1020000F */  beqz       $at, .L80004FA0
    /* 5F64 80004F64 00000000 */   nop
    /* 5F68 80004F68 00804025 */  or         $t0, $a0, $zero
    /* 5F6C 80004F6C 00854821 */  addu       $t1, $a0, $a1
    /* 5F70 80004F70 0109082B */  sltu       $at, $t0, $t1
    /* 5F74 80004F74 10200008 */  beqz       $at, .L80004F98
    /* 5F78 80004F78 00000000 */   nop
    /* 5F7C 80004F7C 310A001F */  andi       $t2, $t0, 0x1F
    /* 5F80 80004F80 2529FFE0 */  addiu      $t1, $t1, -0x20
    /* 5F84 80004F84 010A4023 */  subu       $t0, $t0, $t2
  .L80004F88:
    /* 5F88 80004F88 BD100000 */  cache      0x10, 0x0($t0) /* handwritten instruction */
    /* 5F8C 80004F8C 0109082B */  sltu       $at, $t0, $t1
    /* 5F90 80004F90 1420FFFD */  bnez       $at, .L80004F88
    /* 5F94 80004F94 25080020 */   addiu     $t0, $t0, 0x20
  .L80004F98:
    /* 5F98 80004F98 03E00008 */  jr         $ra
    /* 5F9C 80004F9C 00000000 */   nop
  .L80004FA0:
    /* 5FA0 80004FA0 3C088000 */  lui        $t0, 0x8000
    /* 5FA4 80004FA4 010B4821 */  addu       $t1, $t0, $t3
    /* 5FA8 80004FA8 2529FFE0 */  addiu      $t1, $t1, -0x20
  .L80004FAC:
    /* 5FAC 80004FAC BD000000 */  cache      0x00, 0x0($t0) /* handwritten instruction */
    /* 5FB0 80004FB0 0109082B */  sltu       $at, $t0, $t1
    /* 5FB4 80004FB4 1420FFFD */  bnez       $at, .L80004FAC
    /* 5FB8 80004FB8 25080020 */   addiu     $t0, $t0, (0x80000020 & 0xFFFF)
    /* 5FBC 80004FBC 03E00008 */  jr         $ra
    /* 5FC0 80004FC0 00000000 */   nop
endlabel func_80004F50
    /* 5FC4 80004FC4 00000000 */  nop
    /* 5FC8 80004FC8 00000000 */  nop
    /* 5FCC 80004FCC 00000000 */  nop
