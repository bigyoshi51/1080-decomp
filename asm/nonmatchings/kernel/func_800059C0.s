
nonmatching func_800059C0, 0x14C

glabel func_800059C0
    /* 69C0 800059C0 27BDFFC8 */  addiu      $sp, $sp, -0x38
    /* 69C4 800059C4 AFBF0024 */  sw         $ra, 0x24($sp)
    /* 69C8 800059C8 AFA40038 */  sw         $a0, 0x38($sp)
    /* 69CC 800059CC AFA5003C */  sw         $a1, 0x3C($sp)
    /* 69D0 800059D0 AFA60040 */  sw         $a2, 0x40($sp)
    /* 69D4 800059D4 AFB20020 */  sw         $s2, 0x20($sp)
    /* 69D8 800059D8 AFB1001C */  sw         $s1, 0x1C($sp)
    /* 69DC 800059DC 0C0019AC */  jal        func_800066B0
    /* 69E0 800059E0 AFB00018 */   sw        $s0, 0x18($sp)
    /* 69E4 800059E4 8FAE0038 */  lw         $t6, 0x38($sp)
    /* 69E8 800059E8 00408025 */  or         $s0, $v0, $zero
    /* 69EC 800059EC 8DCF0008 */  lw         $t7, 0x8($t6)
    /* 69F0 800059F0 8DD80010 */  lw         $t8, 0x10($t6)
    /* 69F4 800059F4 01F8082A */  slt        $at, $t7, $t8
    /* 69F8 800059F8 14200018 */  bnez       $at, .L80005A5C
    /* 69FC 800059FC 00000000 */   nop
  .L80005A00:
    /* 6A00 80005A00 8FB90040 */  lw         $t9, 0x40($sp)
    /* 6A04 80005A04 24010001 */  addiu      $at, $zero, 0x1
    /* 6A08 80005A08 1721000A */  bne        $t9, $at, .L80005A34
    /* 6A0C 80005A0C 00000000 */   nop
    /* 6A10 80005A10 3C098001 */  lui        $t1, %hi(__osRunningThread)
    /* 6A14 80005A14 8D29A420 */  lw         $t1, %lo(__osRunningThread)($t1)
    /* 6A18 80005A18 24080008 */  addiu      $t0, $zero, 0x8
    /* 6A1C 80005A1C A5280010 */  sh         $t0, 0x10($t1)
    /* 6A20 80005A20 8FA40038 */  lw         $a0, 0x38($sp)
    /* 6A24 80005A24 0C000F43 */  jal        func_80003D0C
    /* 6A28 80005A28 24840004 */   addiu     $a0, $a0, 0x4
    /* 6A2C 80005A2C 10000005 */  b          .L80005A44
    /* 6A30 80005A30 00000000 */   nop
  .L80005A34:
    /* 6A34 80005A34 0C0019B4 */  jal        func_800066D0
    /* 6A38 80005A38 02002025 */   or        $a0, $s0, $zero
    /* 6A3C 80005A3C 1000002D */  b          .L80005AF4
    /* 6A40 80005A40 2402FFFF */   addiu     $v0, $zero, -0x1
  .L80005A44:
    /* 6A44 80005A44 8FAA0038 */  lw         $t2, 0x38($sp)
    /* 6A48 80005A48 8D4B0008 */  lw         $t3, 0x8($t2)
    /* 6A4C 80005A4C 8D4C0010 */  lw         $t4, 0x10($t2)
    /* 6A50 80005A50 016C082A */  slt        $at, $t3, $t4
    /* 6A54 80005A54 1020FFEA */  beqz       $at, .L80005A00
    /* 6A58 80005A58 00000000 */   nop
  .L80005A5C:
    /* 6A5C 80005A5C 8FAD0038 */  lw         $t5, 0x38($sp)
    /* 6A60 80005A60 8FA8003C */  lw         $t0, 0x3C($sp)
    /* 6A64 80005A64 8DAE000C */  lw         $t6, 0xC($t5)
    /* 6A68 80005A68 8DAF0008 */  lw         $t7, 0x8($t5)
    /* 6A6C 80005A6C 8DB90010 */  lw         $t9, 0x10($t5)
    /* 6A70 80005A70 8DA90014 */  lw         $t1, 0x14($t5)
    /* 6A74 80005A74 01CFC021 */  addu       $t8, $t6, $t7
    /* 6A78 80005A78 0319001A */  div        $zero, $t8, $t9
    /* 6A7C 80005A7C 00008810 */  mfhi       $s1
    /* 6A80 80005A80 00115080 */  sll        $t2, $s1, 2
    /* 6A84 80005A84 012A5821 */  addu       $t3, $t1, $t2
    /* 6A88 80005A88 AD680000 */  sw         $t0, 0x0($t3)
    /* 6A8C 80005A8C 8FAC0038 */  lw         $t4, 0x38($sp)
    /* 6A90 80005A90 17200002 */  bnez       $t9, .L80005A9C
    /* 6A94 80005A94 00000000 */   nop
    /* 6A98 80005A98 0007000D */  break      7
  .L80005A9C:
    /* 6A9C 80005A9C 2401FFFF */  addiu      $at, $zero, -0x1
    /* 6AA0 80005AA0 17210004 */  bne        $t9, $at, .L80005AB4
    /* 6AA4 80005AA4 3C018000 */   lui       $at, (0x80000000 >> 16)
    /* 6AA8 80005AA8 17010002 */  bne        $t8, $at, .L80005AB4
    /* 6AAC 80005AAC 00000000 */   nop
    /* 6AB0 80005AB0 0006000D */  break      6
  .L80005AB4:
    /* 6AB4 80005AB4 8D8E0008 */  lw         $t6, 0x8($t4)
    /* 6AB8 80005AB8 25CF0001 */  addiu      $t7, $t6, 0x1
    /* 6ABC 80005ABC AD8F0008 */  sw         $t7, 0x8($t4)
    /* 6AC0 80005AC0 8FB80038 */  lw         $t8, 0x38($sp)
    /* 6AC4 80005AC4 8F190000 */  lw         $t9, 0x0($t8)
    /* 6AC8 80005AC8 8F2D0000 */  lw         $t5, 0x0($t9)
    /* 6ACC 80005ACC 11A00006 */  beqz       $t5, .L80005AE8
    /* 6AD0 80005AD0 00000000 */   nop
    /* 6AD4 80005AD4 0C000F95 */  jal        func_80003E54
    /* 6AD8 80005AD8 03002025 */   or        $a0, $t8, $zero
    /* 6ADC 80005ADC 00409025 */  or         $s2, $v0, $zero
    /* 6AE0 80005AE0 0C002844 */  jal        func_8000A110
    /* 6AE4 80005AE4 02402025 */   or        $a0, $s2, $zero
  .L80005AE8:
    /* 6AE8 80005AE8 0C0019B4 */  jal        func_800066D0
  alabel D_80005AEC
    /* 6AEC 80005AEC 02002025 */   or        $a0, $s0, $zero
    /* 6AF0 80005AF0 00001025 */  or         $v0, $zero, $zero
  .L80005AF4:
    /* 6AF4 80005AF4 8FBF0024 */  lw         $ra, 0x24($sp)
    /* 6AF8 80005AF8 8FB00018 */  lw         $s0, 0x18($sp)
    /* 6AFC 80005AFC 8FB1001C */  lw         $s1, 0x1C($sp)
    /* 6B00 80005B00 8FB20020 */  lw         $s2, 0x20($sp)
    /* 6B04 80005B04 03E00008 */  jr         $ra
    /* 6B08 80005B08 27BD0038 */   addiu     $sp, $sp, 0x38
endlabel func_800059C0
    /* 6B0C 80005B0C 00000000 */  nop
