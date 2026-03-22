
nonmatching func_80006D7C, 0x1E0

glabel func_80006D7C
    /* 7D7C 80006D7C 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 7D80 80006D80 AFA40028 */  sw         $a0, 0x28($sp)
    /* 7D84 80006D84 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 7D88 80006D88 3C0F8002 */  lui        $t7, %hi(__rmonUtilityBuffer)
    /* 7D8C 80006D8C 25EFB6D0 */  addiu      $t7, $t7, %lo(__rmonUtilityBuffer)
    /* 7D90 80006D90 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 7D94 80006D94 AFAF0020 */  sw         $t7, 0x20($sp)
    /* 7D98 80006D98 AFAE0024 */  sw         $t6, 0x24($sp)
    /* 7D9C 80006D9C 91D80009 */  lbu        $t8, 0x9($t6)
    /* 7DA0 80006DA0 24010001 */  addiu      $at, $zero, 0x1
    /* 7DA4 80006DA4 17010004 */  bne        $t8, $at, .L80006DB8
    /* 7DA8 80006DA8 00000000 */   nop
    /* 7DAC 80006DAC 24190002 */  addiu      $t9, $zero, 0x2
    /* 7DB0 80006DB0 10000003 */  b          .L80006DC0
    /* 7DB4 80006DB4 AFB9001C */   sw        $t9, 0x1C($sp)
  .L80006DB8:
    /* 7DB8 80006DB8 24080006 */  addiu      $t0, $zero, 0x6
    /* 7DBC 80006DBC AFA8001C */  sw         $t0, 0x1C($sp)
  .L80006DC0:
    /* 7DC0 80006DC0 8FA9001C */  lw         $t1, 0x1C($sp)
    /* 7DC4 80006DC4 8FAC0020 */  lw         $t4, 0x20($sp)
    /* 7DC8 80006DC8 00095100 */  sll        $t2, $t1, 4
    /* 7DCC 80006DCC 254B0024 */  addiu      $t3, $t2, 0x24
    /* 7DD0 80006DD0 AD8B0000 */  sw         $t3, 0x0($t4)
    /* 7DD4 80006DD4 8FAD0024 */  lw         $t5, 0x24($sp)
    /* 7DD8 80006DD8 8FAE0020 */  lw         $t6, 0x20($sp)
    /* 7DDC 80006DDC 3C0C0400 */  lui        $t4, (0x4001000 >> 16)
    /* 7DE0 80006DE0 91AF0004 */  lbu        $t7, 0x4($t5)
    /* 7DE4 80006DE4 358C1000 */  ori        $t4, $t4, (0x4001000 & 0xFFFF)
    /* 7DE8 80006DE8 A1CF0004 */  sb         $t7, 0x4($t6)
    /* 7DEC 80006DEC 8FB80020 */  lw         $t8, 0x20($sp)
    /* 7DF0 80006DF0 240F1000 */  addiu      $t7, $zero, 0x1000
    /* 7DF4 80006DF4 A7000006 */  sh         $zero, 0x6($t8)
    /* 7DF8 80006DF8 8FB90024 */  lw         $t9, 0x24($sp)
    /* 7DFC 80006DFC 8FA90020 */  lw         $t1, 0x20($sp)
    /* 7E00 80006E00 24180007 */  addiu      $t8, $zero, 0x7
    /* 7E04 80006E04 8F28000C */  lw         $t0, 0xC($t9)
    /* 7E08 80006E08 AD28000C */  sw         $t0, 0xC($t1)
    /* 7E0C 80006E0C 8FAA001C */  lw         $t2, 0x1C($sp)
    /* 7E10 80006E10 8FAB0020 */  lw         $t3, 0x20($sp)
    /* 7E14 80006E14 01804021 */  addu       $t0, $t4, $zero
    /* 7E18 80006E18 AD6A0010 */  sw         $t2, 0x10($t3)
    /* 7E1C 80006E1C 8FAD0020 */  lw         $t5, 0x20($sp)
    /* 7E20 80006E20 3C0A0400 */  lui        $t2, (0x4000000 >> 16)
    /* 7E24 80006E24 ADAC0024 */  sw         $t4, 0x24($t5)
    /* 7E28 80006E28 8FAE0020 */  lw         $t6, 0x20($sp)
    /* 7E2C 80006E2C 240C1000 */  addiu      $t4, $zero, 0x1000
    /* 7E30 80006E30 ADCF0028 */  sw         $t7, 0x28($t6)
    /* 7E34 80006E34 8FB90020 */  lw         $t9, 0x20($sp)
    /* 7E38 80006E38 240F0003 */  addiu      $t7, $zero, 0x3
    /* 7E3C 80006E3C A738002C */  sh         $t8, 0x2C($t9)
    /* 7E40 80006E40 8FA90020 */  lw         $t1, 0x20($sp)
    /* 7E44 80006E44 3C180400 */  lui        $t8, (0x4000000 >> 16)
    /* 7E48 80006E48 AD280030 */  sw         $t0, 0x30($t1)
    /* 7E4C 80006E4C 8FAB0020 */  lw         $t3, 0x20($sp)
    /* 7E50 80006E50 AD6A0014 */  sw         $t2, 0x14($t3)
    /* 7E54 80006E54 8FAD0020 */  lw         $t5, 0x20($sp)
    /* 7E58 80006E58 ADAC0018 */  sw         $t4, 0x18($t5)
    /* 7E5C 80006E5C 8FAE0020 */  lw         $t6, 0x20($sp)
    /* 7E60 80006E60 A5CF001C */  sh         $t7, 0x1C($t6)
    /* 7E64 80006E64 8FB90020 */  lw         $t9, 0x20($sp)
    /* 7E68 80006E68 AF380020 */  sw         $t8, 0x20($t9)
    /* 7E6C 80006E6C 8FA8001C */  lw         $t0, 0x1C($sp)
    /* 7E70 80006E70 29010003 */  slti       $at, $t0, 0x3
    /* 7E74 80006E74 1420002F */  bnez       $at, .L80006F34
    /* 7E78 80006E78 00000000 */   nop
    /* 7E7C 80006E7C 8FAA0020 */  lw         $t2, 0x20($sp)
    /* 7E80 80006E80 3C098820 */  lui        $t1, (0x88200000 >> 16)
    /* 7E84 80006E84 240B6130 */  addiu      $t3, $zero, 0x6130
    /* 7E88 80006E88 AD490034 */  sw         $t1, 0x34($t2)
    /* 7E8C 80006E8C 8FAC0020 */  lw         $t4, 0x20($sp)
    /* 7E90 80006E90 240D0005 */  addiu      $t5, $zero, 0x5
    /* 7E94 80006E94 24180004 */  addiu      $t8, $zero, 0x4
    /* 7E98 80006E98 AD8B0038 */  sw         $t3, 0x38($t4)
    /* 7E9C 80006E9C 8FAF0020 */  lw         $t7, 0x20($sp)
    /* 7EA0 80006EA0 3C080020 */  lui        $t0, (0x200000 >> 16)
    /* 7EA4 80006EA4 240A0003 */  addiu      $t2, $zero, 0x3
    /* 7EA8 80006EA8 A5ED003C */  sh         $t5, 0x3C($t7)
    /* 7EAC 80006EAC 8FAE0020 */  lw         $t6, 0x20($sp)
    /* 7EB0 80006EB0 3C0D0400 */  lui        $t5, (0x4002000 >> 16)
    /* 7EB4 80006EB4 35AD2000 */  ori        $t5, $t5, (0x4002000 & 0xFFFF)
    /* 7EB8 80006EB8 ADC00040 */  sw         $zero, 0x40($t6)
    /* 7EBC 80006EBC 8FB90020 */  lw         $t9, 0x20($sp)
    /* 7EC0 80006EC0 3C0E0080 */  lui        $t6, (0x800000 >> 16)
    /* 7EC4 80006EC4 AF380044 */  sw         $t8, 0x44($t9)
    /* 7EC8 80006EC8 8FA90020 */  lw         $t1, 0x20($sp)
    /* 7ECC 80006ECC 24190003 */  addiu      $t9, $zero, 0x3
    /* 7ED0 80006ED0 AD280048 */  sw         $t0, 0x48($t1)
    /* 7ED4 80006ED4 8FAB0020 */  lw         $t3, 0x20($sp)
    /* 7ED8 80006ED8 A56A004C */  sh         $t2, 0x4C($t3)
    /* 7EDC 80006EDC 8FAC0020 */  lw         $t4, 0x20($sp)
    /* 7EE0 80006EE0 3C0A8820 */  lui        $t2, (0x88206130 >> 16)
    /* 7EE4 80006EE4 354A6130 */  ori        $t2, $t2, (0x88206130 & 0xFFFF)
    /* 7EE8 80006EE8 AD800050 */  sw         $zero, 0x50($t4)
    /* 7EEC 80006EEC 8FAF0020 */  lw         $t7, 0x20($sp)
    /* 7EF0 80006EF0 340C9000 */  ori        $t4, $zero, 0x9000
    /* 7EF4 80006EF4 ADED0054 */  sw         $t5, 0x54($t7)
    /* 7EF8 80006EF8 8FB80020 */  lw         $t8, 0x20($sp)
    /* 7EFC 80006EFC 240F0003 */  addiu      $t7, $zero, 0x3
    /* 7F00 80006F00 AF0E0058 */  sw         $t6, 0x58($t8)
    /* 7F04 80006F04 8FA80020 */  lw         $t0, 0x20($sp)
    /* 7F08 80006F08 A519005C */  sh         $t9, 0x5C($t0)
    /* 7F0C 80006F0C 8FA90020 */  lw         $t1, 0x20($sp)
    /* 7F10 80006F10 AD200060 */  sw         $zero, 0x60($t1)
    /* 7F14 80006F14 8FAB0020 */  lw         $t3, 0x20($sp)
    /* 7F18 80006F18 AD6A0064 */  sw         $t2, 0x64($t3)
    /* 7F1C 80006F1C 8FAD0020 */  lw         $t5, 0x20($sp)
    /* 7F20 80006F20 ADAC0068 */  sw         $t4, 0x68($t5)
    /* 7F24 80006F24 8FAE0020 */  lw         $t6, 0x20($sp)
    /* 7F28 80006F28 A5CF006C */  sh         $t7, 0x6C($t6)
    /* 7F2C 80006F2C 8FB80020 */  lw         $t8, 0x20($sp)
    /* 7F30 80006F30 AF000070 */  sw         $zero, 0x70($t8)
  .L80006F34:
    /* 7F34 80006F34 8FB90020 */  lw         $t9, 0x20($sp)
    /* 7F38 80006F38 24060001 */  addiu      $a2, $zero, 0x1
    /* 7F3C 80006F3C 03202025 */  or         $a0, $t9, $zero
    /* 7F40 80006F40 0C001CFE */  jal        func_800073F8
    /* 7F44 80006F44 8F250000 */   lw        $a1, 0x0($t9)
    /* 7F48 80006F48 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 7F4C 80006F4C 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 7F50 80006F50 00001025 */  or         $v0, $zero, $zero
    /* 7F54 80006F54 03E00008 */  jr         $ra
    /* 7F58 80006F58 00000000 */   nop
endlabel func_80006D7C
    /* 7F5C 80006F5C 00000000 */  nop
