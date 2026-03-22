
nonmatching func_80006D0C, 0x70

glabel func_80006D0C
    /* 7D0C 80006D0C 27BDFFD0 */  addiu      $sp, $sp, -0x30
    /* 7D10 80006D10 AFA40030 */  sw         $a0, 0x30($sp)
    /* 7D14 80006D14 8FAE0030 */  lw         $t6, 0x30($sp)
    /* 7D18 80006D18 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 7D1C 80006D1C 24010001 */  addiu      $at, $zero, 0x1
    /* 7D20 80006D20 AFAE002C */  sw         $t6, 0x2C($sp)
    /* 7D24 80006D24 91CF0004 */  lbu        $t7, 0x4($t6)
    /* 7D28 80006D28 A7A0001E */  sh         $zero, 0x1E($sp)
    /* 7D2C 80006D2C A3AF001C */  sb         $t7, 0x1C($sp)
    /* 7D30 80006D30 8DD8000C */  lw         $t8, 0xC($t6)
    /* 7D34 80006D34 AFB80024 */  sw         $t8, 0x24($sp)
    /* 7D38 80006D38 91D90009 */  lbu        $t9, 0x9($t6)
    /* 7D3C 80006D3C 17210004 */  bne        $t9, $at, .L80006D50
    /* 7D40 80006D40 00000000 */   nop
    /* 7D44 80006D44 24080002 */  addiu      $t0, $zero, 0x2
    /* 7D48 80006D48 10000003 */  b          .L80006D58
    /* 7D4C 80006D4C AFA80028 */   sw        $t0, 0x28($sp)
  .L80006D50:
    /* 7D50 80006D50 24090005 */  addiu      $t1, $zero, 0x5
    /* 7D54 80006D54 AFA90028 */  sw         $t1, 0x28($sp)
  .L80006D58:
    /* 7D58 80006D58 27A40018 */  addiu      $a0, $sp, 0x18
    /* 7D5C 80006D5C 24050014 */  addiu      $a1, $zero, 0x14
    /* 7D60 80006D60 0C001CFE */  jal        func_800073F8
    /* 7D64 80006D64 24060001 */   addiu     $a2, $zero, 0x1
    /* 7D68 80006D68 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 7D6C 80006D6C 27BD0030 */  addiu      $sp, $sp, 0x30
    /* 7D70 80006D70 00001025 */  or         $v0, $zero, $zero
    /* 7D74 80006D74 03E00008 */  jr         $ra
    /* 7D78 80006D78 00000000 */   nop
endlabel func_80006D0C
