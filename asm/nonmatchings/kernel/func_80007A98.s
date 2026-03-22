
nonmatching func_80007A98, 0xA4

glabel func_80007A98
    /* 8A98 80007A98 00000000 */  nop
    /* 8A9C 80007A9C 0C002126 */  jal        func_80008498
    /* 8AA0 80007AA0 00000000 */   nop
    /* 8AA4 80007AA4 10000003 */  b          .L80007AB4
    /* 8AA8 80007AA8 00000000 */   nop
  .L80007AAC:
    /* 8AAC 80007AAC 1000001E */  b          .L80007B28
    /* 8AB0 80007AB0 2402FFFC */   addiu     $v0, $zero, -0x4
  .L80007AB4:
    /* 8AB4 80007AB4 8FAA0078 */  lw         $t2, 0x78($sp)
    /* 8AB8 80007AB8 8FAB0074 */  lw         $t3, 0x74($sp)
    /* 8ABC 80007ABC 27A60028 */  addiu      $a2, $sp, 0x28
    /* 8AC0 80007AC0 91440009 */  lbu        $a0, 0x9($t2)
    /* 8AC4 80007AC4 0C001EA6 */  jal        func_80007A98
    /* 8AC8 80007AC8 8D65000C */   lw        $a1, 0xC($t3)
    /* 8ACC 80007ACC 10400003 */  beqz       $v0, .L80007ADC
    /* 8AD0 80007AD0 00000000 */   nop
    /* 8AD4 80007AD4 10000014 */  b          .L80007B28
    /* 8AD8 80007AD8 2402FFFE */   addiu     $v0, $zero, -0x2
  .L80007ADC:
    /* 8ADC 80007ADC 8FAC0074 */  lw         $t4, 0x74($sp)
    /* 8AE0 80007AE0 27A40028 */  addiu      $a0, $sp, 0x28
    /* 8AE4 80007AE4 2405004C */  addiu      $a1, $zero, 0x4C
    /* 8AE8 80007AE8 918D0004 */  lbu        $t5, 0x4($t4)
    /* 8AEC 80007AEC A7A0002E */  sh         $zero, 0x2E($sp)
    /* 8AF0 80007AF0 24060001 */  addiu      $a2, $zero, 0x1
    /* 8AF4 80007AF4 0C001CFE */  jal        func_800073F8
    /* 8AF8 80007AF8 A3AD002C */   sb        $t5, 0x2C($sp)
    /* 8AFC 80007AFC 8FAE0034 */  lw         $t6, 0x34($sp)
    /* 8B00 80007B00 24010001 */  addiu      $at, $zero, 0x1
    /* 8B04 80007B04 15C10007 */  bne        $t6, $at, .L80007B24
    /* 8B08 80007B08 00000000 */   nop
    /* 8B0C 80007B0C 240F0004 */  addiu      $t7, $zero, 0x4
    /* 8B10 80007B10 A3AF002C */  sb         $t7, 0x2C($sp)
    /* 8B14 80007B14 27A40028 */  addiu      $a0, $sp, 0x28
    /* 8B18 80007B18 2405004C */  addiu      $a1, $zero, 0x4C
    /* 8B1C 80007B1C 0C001CFE */  jal        func_800073F8
    /* 8B20 80007B20 24060002 */   addiu     $a2, $zero, 0x2
  .L80007B24:
    /* 8B24 80007B24 00001025 */  or         $v0, $zero, $zero
  .L80007B28:
    /* 8B28 80007B28 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 8B2C 80007B2C 8FB00018 */  lw         $s0, 0x18($sp)
    /* 8B30 80007B30 27BD0078 */  addiu      $sp, $sp, 0x78
    /* 8B34 80007B34 03E00008 */  jr         $ra
    /* 8B38 80007B38 00000000 */   nop
endlabel func_80007A98
