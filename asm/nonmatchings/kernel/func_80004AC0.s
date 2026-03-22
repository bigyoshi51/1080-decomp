
nonmatching func_80004AC0, 0xF0

glabel func_80004AC0
    /* 5AC0 80004AC0 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 5AC4 80004AC4 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 5AC8 80004AC8 AFA40018 */  sw         $a0, 0x18($sp)
    /* 5ACC 80004ACC 0C0015B0 */  jal        func_800056C0
    /* 5AD0 80004AD0 AFA5001C */   sw        $a1, 0x1C($sp)
    /* 5AD4 80004AD4 10400003 */  beqz       $v0, .L80004AE4
    /* 5AD8 80004AD8 00000000 */   nop
    /* 5ADC 80004ADC 10000008 */  b          .L80004B00
    /* 5AE0 80004AE0 2402FFFF */   addiu     $v0, $zero, -0x1
  .L80004AE4:
    /* 5AE4 80004AE4 8FAE0018 */  lw         $t6, 0x18($sp)
    /* 5AE8 80004AE8 3C01A000 */  lui        $at, %hi(D_A0000000)
    /* 5AEC 80004AEC 8FB9001C */  lw         $t9, 0x1C($sp)
    /* 5AF0 80004AF0 01C17825 */  or         $t7, $t6, $at
    /* 5AF4 80004AF4 8DF80000 */  lw         $t8, %lo(D_A0000000)($t7)
    /* 5AF8 80004AF8 00001025 */  or         $v0, $zero, $zero
    /* 5AFC 80004AFC AF380000 */  sw         $t8, 0x0($t9)
  .L80004B00:
    /* 5B00 80004B00 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 5B04 80004B04 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 5B08 80004B08 03E00008 */  jr         $ra
    /* 5B0C 80004B0C 00000000 */   nop
/* glabel func_80004B10 */
    /* 5B10 80004B10 27BDFFD0 */  addiu      $sp, $sp, -0x30
    /* 5B14 80004B14 3C0E8001 */  lui        $t6, %hi(D_8000A440)
    /* 5B18 80004B18 8DCEA440 */  lw         $t6, %lo(D_8000A440)($t6)
    /* 5B1C 80004B1C AFBF001C */  sw         $ra, 0x1C($sp)
    /* 5B20 80004B20 AFA40030 */  sw         $a0, 0x30($sp)
    /* 5B24 80004B24 AFA50034 */  sw         $a1, 0x34($sp)
    /* 5B28 80004B28 AFB00018 */  sw         $s0, 0x18($sp)
    /* 5B2C 80004B2C 15C0000F */  bnez       $t6, .L80004B6C
/* glabel func_80004B30 */
    /* 5B30 80004B30 AFA00028 */  sw         $zero, 0x28($sp)
    /* 5B34 80004B34 3C048002 */  lui        $a0, %hi(readhost_bss_0000)
    /* 5B38 80004B38 3C058002 */  lui        $a1, %hi(readhost_bss_0018)
    /* 5B3C 80004B3C 24A594F8 */  addiu      $a1, $a1, %lo(readhost_bss_0018)
    /* 5B40 80004B40 248494E0 */  addiu      $a0, $a0, %lo(readhost_bss_0000)
    /* 5B44 80004B44 0C0014F4 */  jal        func_800053D0
    /* 5B48 80004B48 24060001 */   addiu     $a2, $zero, 0x1
    /* 5B4C 80004B4C 3C058002 */  lui        $a1, %hi(readhost_bss_0000)
    /* 5B50 80004B50 24A594E0 */  addiu      $a1, $a1, %lo(readhost_bss_0000)
    /* 5B54 80004B54 2404000F */  addiu      $a0, $zero, 0xF
    /* 5B58 80004B58 0C001478 */  jal        func_800051E0
    /* 5B5C 80004B5C 00003025 */   or        $a2, $zero, $zero
    /* 5B60 80004B60 240F0001 */  addiu      $t7, $zero, 0x1
    /* 5B64 80004B64 3C018001 */  lui        $at, %hi(D_8000A440)
    /* 5B68 80004B68 AC2FA440 */  sw         $t7, %lo(D_8000A440)($at)
  .L80004B6C:
    /* 5B6C 80004B6C 8FB80030 */  lw         $t8, 0x30($sp)
    /* 5B70 80004B70 8FA80028 */  lw         $t0, 0x28($sp)
    /* 5B74 80004B74 3C018002 */  lui        $at, %hi(__osRdb_Read_Data_Buf)
    /* 5B78 80004B78 8FB90034 */  lw         $t9, 0x34($sp)
    /* 5B7C 80004B7C AC3894FC */  sw         $t8, %lo(__osRdb_Read_Data_Buf)($at)
    /* 5B80 80004B80 3C018002 */  lui        $at, %hi(__osRdb_Read_Data_Ct)
    /* 5B84 80004B84 1500000C */  bnez       $t0, .L80004BB8
    /* 5B88 80004B88 AC399500 */   sw        $t9, %lo(__osRdb_Read_Data_Ct)($at)
  .L80004B8C:
    /* 5B8C 80004B8C 27A4002C */  addiu      $a0, $sp, 0x2C
    /* 5B90 80004B90 24050001 */  addiu      $a1, $zero, 0x1
    /* 5B94 80004B94 0C0019BC */  jal        func_800066F0
    /* 5B98 80004B98 24060005 */   addiu     $a2, $zero, 0x5
    /* 5B9C 80004B9C 8FA90028 */  lw         $t1, 0x28($sp)
    /* 5BA0 80004BA0 00408025 */  or         $s0, $v0, $zero
    /* 5BA4 80004BA4 01305021 */  addu       $t2, $t1, $s0
    /* 5BA8 80004BA8 AFAA0028 */  sw         $t2, 0x28($sp)
    /* 5BAC 80004BAC 8FAB0028 */  lw         $t3, 0x28($sp)
endlabel func_80004AC0
