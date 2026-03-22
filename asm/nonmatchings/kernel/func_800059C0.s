
nonmatching func_800059C0, 0x23C

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
    /* 6A10 80005A10 3C098001 */  lui        $t1, %hi(D_8000A420)
    /* 6A14 80005A14 8D29A420 */  lw         $t1, %lo(D_8000A420)($t1)
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

/* glabel func_80005B10 */
    /* 6B10 80005B10 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 6B14 80005B14 AFA40028 */  sw         $a0, 0x28($sp)
    /* 6B18 80005B18 AFA5002C */  sw         $a1, 0x2C($sp)
    /* 6B1C 80005B1C 8FAE002C */  lw         $t6, 0x2C($sp)
    /* 6B20 80005B20 8FAF0028 */  lw         $t7, 0x28($sp)
    /* 6B24 80005B24 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 6B28 80005B28 AFA60030 */  sw         $a2, 0x30($sp)
    /* 6B2C 80005B2C AFA70034 */  sw         $a3, 0x34($sp)
    /* 6B30 80005B30 AFB00018 */  sw         $s0, 0x18($sp)
    /* 6B34 80005B34 ADEE0014 */  sw         $t6, 0x14($t7)
    /* 6B38 80005B38 8FB90028 */  lw         $t9, 0x28($sp)
    /* 6B3C 80005B3C 8FB8003C */  lw         $t8, 0x3C($sp)
    /* 6B40 80005B40 AF380004 */  sw         $t8, 0x4($t9)
    /* 6B44 80005B44 8FA80028 */  lw         $t0, 0x28($sp)
    /* 6B48 80005B48 AD000000 */  sw         $zero, 0x0($t0)
    /* 6B4C 80005B4C 8FA90028 */  lw         $t1, 0x28($sp)
    /* 6B50 80005B50 AD200008 */  sw         $zero, 0x8($t1)
    /* 6B54 80005B54 8FAB0028 */  lw         $t3, 0x28($sp)
    /* 6B58 80005B58 8FAA0030 */  lw         $t2, 0x30($sp)
    /* 6B5C 80005B5C AD6A011C */  sw         $t2, 0x11C($t3)
    /* 6B60 80005B60 8FAC0034 */  lw         $t4, 0x34($sp)
    /* 6B64 80005B64 8FAD0028 */  lw         $t5, 0x28($sp)
    /* 6B68 80005B68 01807825 */  or         $t7, $t4, $zero
    /* 6B6C 80005B6C 000C77C3 */  sra        $t6, $t4, 31
    /* 6B70 80005B70 ADAE0038 */  sw         $t6, 0x38($t5)
    /* 6B74 80005B74 ADAF003C */  sw         $t7, 0x3C($t5)
    /* 6B78 80005B78 8FB80038 */  lw         $t8, 0x38($sp)
    /* 6B7C 80005B7C 8FB90028 */  lw         $t9, 0x28($sp)
    /* 6B80 80005B80 3C0C8000 */  lui        $t4, %hi(D_80003FE0)
    /* 6B84 80005B84 03004825 */  or         $t1, $t8, $zero
    /* 6B88 80005B88 2D210010 */  sltiu      $at, $t1, 0x10
    /* 6B8C 80005B8C 001847C3 */  sra        $t0, $t8, 31
    /* 6B90 80005B90 01015023 */  subu       $t2, $t0, $at
    /* 6B94 80005B94 252BFFF0 */  addiu      $t3, $t1, -0x10
    /* 6B98 80005B98 AF2B00F4 */  sw         $t3, 0xF4($t9)
    /* 6B9C 80005B9C AF2A00F0 */  sw         $t2, 0xF0($t9)
    /* 6BA0 80005BA0 8FAD0028 */  lw         $t5, 0x28($sp)
    /* 6BA4 80005BA4 258C3FE0 */  addiu      $t4, $t4, %lo(D_80003FE0)
    /* 6BA8 80005BA8 01807825 */  or         $t7, $t4, $zero
    /* 6BAC 80005BAC 000C77C3 */  sra        $t6, $t4, 31
    /* 6BB0 80005BB0 ADAE0100 */  sw         $t6, 0x100($t5)
    /* 6BB4 80005BB4 ADAF0104 */  sw         $t7, 0x104($t5)
    /* 6BB8 80005BB8 8FA90028 */  lw         $t1, 0x28($sp)
    /* 6BBC 80005BBC 3C18003F */  lui        $t8, (0x3FFF01 >> 16)
    /* 6BC0 80005BC0 3718FF01 */  ori        $t8, $t8, (0x3FFF01 & 0xFFFF)
    /* 6BC4 80005BC4 AFB80020 */  sw         $t8, 0x20($sp)
    /* 6BC8 80005BC8 3408FF03 */  ori        $t0, $zero, 0xFF03
    /* 6BCC 80005BCC AD280118 */  sw         $t0, 0x118($t1)
    /* 6BD0 80005BD0 8FAA0020 */  lw         $t2, 0x20($sp)
    /* 6BD4 80005BD4 8FAC0028 */  lw         $t4, 0x28($sp)
    /* 6BD8 80005BD8 3C01003F */  lui        $at, (0x3F0000 >> 16)
    /* 6BDC 80005BDC 01415824 */  and        $t3, $t2, $at
    /* 6BE0 80005BE0 000BCC02 */  srl        $t9, $t3, 16
    /* 6BE4 80005BE4 AD990128 */  sw         $t9, 0x128($t4)
    /* 6BE8 80005BE8 8FAF0028 */  lw         $t7, 0x28($sp)
    /* 6BEC 80005BEC 3C0E0100 */  lui        $t6, (0x1000800 >> 16)
    /* 6BF0 80005BF0 35CE0800 */  ori        $t6, $t6, (0x1000800 & 0xFFFF)
    /* 6BF4 80005BF4 ADEE012C */  sw         $t6, 0x12C($t7)
    /* 6BF8 80005BF8 8FAD0028 */  lw         $t5, 0x28($sp)
    /* 6BFC 80005BFC 24180001 */  addiu      $t8, $zero, 0x1
endlabel func_800059C0
