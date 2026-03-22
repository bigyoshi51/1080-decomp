
nonmatching func_80008AD0, 0xDC

glabel func_80008AD0
    /* 9AD0 80008AD0 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 9AD4 80008AD4 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 9AD8 80008AD8 0C00270C */  jal        func_80009C30
    /* 9ADC 80008ADC AFB00018 */   sw        $s0, 0x18($sp)
    /* 9AE0 80008AE0 00408025 */  or         $s0, $v0, $zero
    /* 9AE4 80008AE4 8E0E0004 */  lw         $t6, 0x4($s0)
    /* 9AE8 80008AE8 2401FFFF */  addiu      $at, $zero, -0x1
    /* 9AEC 80008AEC 11C1002A */  beq        $t6, $at, .L80008B98
    /* 9AF0 80008AF0 00000000 */   nop
  .L80008AF4:
    /* 9AF4 80008AF4 8E0F0004 */  lw         $t7, 0x4($s0)
    /* 9AF8 80008AF8 19E00022 */  blez       $t7, .L80008B84
    /* 9AFC 80008AFC 00000000 */   nop
    /* 9B00 80008B00 8E180004 */  lw         $t8, 0x4($s0)
    /* 9B04 80008B04 2B010080 */  slti       $at, $t8, 0x80
    /* 9B08 80008B08 1020001E */  beqz       $at, .L80008B84
    /* 9B0C 80008B0C 00000000 */   nop
    /* 9B10 80008B10 96190012 */  lhu        $t9, 0x12($s0)
    /* 9B14 80008B14 33280001 */  andi       $t0, $t9, 0x1
    /* 9B18 80008B18 11000011 */  beqz       $t0, .L80008B60
    /* 9B1C 80008B1C 00000000 */   nop
    /* 9B20 80008B20 8E09011C */  lw         $t1, 0x11C($s0)
    /* 9B24 80008B24 3C01FC00 */  lui        $at, (0xFC00003F >> 16)
    /* 9B28 80008B28 3421003F */  ori        $at, $at, (0xFC00003F & 0xFFFF)
    /* 9B2C 80008B2C 8D2A0000 */  lw         $t2, 0x0($t1)
    /* 9B30 80008B30 01415824 */  and        $t3, $t2, $at
    /* 9B34 80008B34 2401000D */  addiu      $at, $zero, 0xD
    /* 9B38 80008B38 15610006 */  bne        $t3, $at, .L80008B54
    /* 9B3C 80008B3C AFAA0020 */   sw        $t2, 0x20($sp)
    /* 9B40 80008B40 8E040014 */  lw         $a0, 0x14($s0)
    /* 9B44 80008B44 0C002353 */  jal        func_80008D4C
    /* 9B48 80008B48 000A2983 */   sra       $a1, $t2, 6
    /* 9B4C 80008B4C 10000004 */  b          .L80008B60
    /* 9B50 80008B50 00000000 */   nop
  .L80008B54:
    /* 9B54 80008B54 8E040014 */  lw         $a0, 0x14($s0)
    /* 9B58 80008B58 0C002353 */  jal        func_80008D4C
    /* 9B5C 80008B5C 00002825 */   or        $a1, $zero, $zero
  .L80008B60:
    /* 9B60 80008B60 960C0012 */  lhu        $t4, 0x12($s0)
    /* 9B64 80008B64 318D0002 */  andi       $t5, $t4, 0x2
    /* 9B68 80008B68 11A00006 */  beqz       $t5, .L80008B84
    /* 9B6C 80008B6C 00000000 */   nop
    /* 9B70 80008B70 0C001530 */  jal        func_800054C0
    /* 9B74 80008B74 02002025 */   or        $a0, $s0, $zero
    /* 9B78 80008B78 8E040014 */  lw         $a0, 0x14($s0)
    /* 9B7C 80008B7C 0C002353 */  jal        func_80008D4C
    /* 9B80 80008B80 2405000F */   addiu     $a1, $zero, 0xF
  .L80008B84:
    /* 9B84 80008B84 8E10000C */  lw         $s0, 0xC($s0)
    /* 9B88 80008B88 2401FFFF */  addiu      $at, $zero, -0x1
    /* 9B8C 80008B8C 8E0E0004 */  lw         $t6, 0x4($s0)
    /* 9B90 80008B90 15C1FFD8 */  bne        $t6, $at, .L80008AF4
    /* 9B94 80008B94 00000000 */   nop
  .L80008B98:
    /* 9B98 80008B98 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 9B9C 80008B9C 8FB00018 */  lw         $s0, 0x18($sp)
    /* 9BA0 80008BA0 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 9BA4 80008BA4 03E00008 */  jr         $ra
    /* 9BA8 80008BA8 00000000 */   nop
endlabel func_80008AD0
    /* 9BAC 80008BAC 00000000 */  nop
