nonmatching func_00000A9C, 0x78

glabel func_00000A9C
    /* DD1508 00000A9C 10A00011 */  beqz       $a1, .L00000AE4
    /* DD150C 00000AA0 AFA40000 */   sw        $a0, 0x0($sp)
    /* DD1510 00000AA4 24010065 */  addiu      $at, $zero, 0x65
    /* DD1514 00000AA8 10A10010 */  beq        $a1, $at, .L00000AEC
    /* DD1518 00000AAC 24010064 */   addiu     $at, $zero, 0x64
    /* DD151C 00000AB0 10A10010 */  beq        $a1, $at, .L00000AF4
    /* DD1520 00000AB4 2401006D */   addiu     $at, $zero, 0x6D
    /* DD1524 00000AB8 10A10010 */  beq        $a1, $at, .L00000AFC
    /* DD1528 00000ABC 24010074 */   addiu     $at, $zero, 0x74
    /* DD152C 00000AC0 10A10010 */  beq        $a1, $at, .L00000B04
    /* DD1530 00000AC4 2401006E */   addiu     $at, $zero, 0x6E
    /* DD1534 00000AC8 10A10010 */  beq        $a1, $at, .L00000B0C
    /* DD1538 00000ACC 24030008 */   addiu     $v1, $zero, 0x8
    /* DD153C 00000AD0 24010073 */  addiu      $at, $zero, 0x73
    /* DD1540 00000AD4 10A1000D */  beq        $a1, $at, .L00000B0C
    /* DD1544 00000AD8 00000000 */   nop
    /* DD1548 00000ADC 03E00008 */  jr         $ra
    /* DD154C 00000AE0 24020002 */   addiu     $v0, $zero, 0x2
  .L00000AE4:
    /* DD1550 00000AE4 03E00008 */  jr         $ra
    /* DD1554 00000AE8 24020001 */   addiu     $v0, $zero, 0x1
  .L00000AEC:
    /* DD1558 00000AEC 03E00008 */  jr         $ra
    /* DD155C 00000AF0 24020004 */   addiu     $v0, $zero, 0x4
  .L00000AF4:
    /* DD1560 00000AF4 03E00008 */  jr         $ra
    /* DD1564 00000AF8 24020010 */   addiu     $v0, $zero, 0x10
  .L00000AFC:
    /* DD1568 00000AFC 03E00008 */  jr         $ra
    /* DD156C 00000B00 24020040 */   addiu     $v0, $zero, 0x40
  .L00000B04:
    /* DD1570 00000B04 03E00008 */  jr         $ra
    /* DD1574 00000B08 24020020 */   addiu     $v0, $zero, 0x20
  .L00000B0C:
    /* DD1578 00000B0C 03E00008 */  jr         $ra
    /* DD157C 00000B10 00601025 */   or        $v0, $v1, $zero
endlabel func_00000A9C
