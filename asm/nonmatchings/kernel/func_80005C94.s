
nonmatching func_80005C94, 0x12C

glabel func_80005C94
    /* 6C94 80005C94 8FB80044 */  lw         $t8, 0x44($sp)
    /* 6C98 80005C98 8F190014 */  lw         $t9, 0x14($t8)
    /* 6C9C 80005C9C 132000A1 */  beqz       $t9, .L80005F24
    /* 6CA0 80005CA0 00000000 */   nop
    /* 6CA4 80005CA4 93280004 */  lbu        $t0, 0x4($t9)
    /* 6CA8 80005CA8 24010002 */  addiu      $at, $zero, 0x2
    /* 6CAC 80005CAC 1501009D */  bne        $t0, $at, .L80005F24
    /* 6CB0 80005CB0 00000000 */   nop
    /* 6CB4 80005CB4 8F290014 */  lw         $t1, 0x14($t9)
    /* 6CB8 80005CB8 11200003 */  beqz       $t1, .L80005CC8
    /* 6CBC 80005CBC 24010001 */   addiu     $at, $zero, 0x1
    /* 6CC0 80005CC0 15210098 */  bne        $t1, $at, .L80005F24
    /* 6CC4 80005CC4 00000000 */   nop
  .L80005CC8:
    /* 6CC8 80005CC8 8FAA0044 */  lw         $t2, 0x44($sp)
    /* 6CCC 80005CCC 2408FFFF */  addiu      $t0, $zero, -0x1
    /* 6CD0 80005CD0 24010003 */  addiu      $at, $zero, 0x3
    /* 6CD4 80005CD4 8D4B0014 */  lw         $t3, 0x14($t2)
    /* 6CD8 80005CD8 256C0014 */  addiu      $t4, $t3, 0x14
    /* 6CDC 80005CDC AFAC0028 */  sw         $t4, 0x28($sp)
    /* 6CE0 80005CE0 958D0006 */  lhu        $t5, 0x6($t4)
    /* 6CE4 80005CE4 000D70C0 */  sll        $t6, $t5, 3
    /* 6CE8 80005CE8 01CD7021 */  addu       $t6, $t6, $t5
    /* 6CEC 80005CEC 000E7080 */  sll        $t6, $t6, 2
    /* 6CF0 80005CF0 018E7821 */  addu       $t7, $t4, $t6
    /* 6CF4 80005CF4 25F80018 */  addiu      $t8, $t7, 0x18
    /* 6CF8 80005CF8 AFB8002C */  sw         $t8, 0x2C($sp)
    /* 6CFC 80005CFC AD880008 */  sw         $t0, 0x8($t4)
    /* 6D00 80005D00 8FB90028 */  lw         $t9, 0x28($sp)
    /* 6D04 80005D04 97290004 */  lhu        $t1, 0x4($t9)
    /* 6D08 80005D08 11210006 */  beq        $t1, $at, .L80005D24
    /* 6D0C 80005D0C 00000000 */   nop
    /* 6D10 80005D10 8FAA002C */  lw         $t2, 0x2C($sp)
    /* 6D14 80005D14 8D4B0004 */  lw         $t3, 0x4($t2)
    /* 6D18 80005D18 8D4D000C */  lw         $t5, 0xC($t2)
    /* 6D1C 80005D1C 016D7023 */  subu       $t6, $t3, $t5
    /* 6D20 80005D20 AD4E0004 */  sw         $t6, 0x4($t2)
  .L80005D24:
    /* 6D24 80005D24 8FAF0028 */  lw         $t7, 0x28($sp)
    /* 6D28 80005D28 24010002 */  addiu      $at, $zero, 0x2
    /* 6D2C 80005D2C 95F80004 */  lhu        $t8, 0x4($t7)
    /* 6D30 80005D30 17010009 */  bne        $t8, $at, .L80005D58
    /* 6D34 80005D34 00000000 */   nop
    /* 6D38 80005D38 8FA80044 */  lw         $t0, 0x44($sp)
    /* 6D3C 80005D3C 8D0C0014 */  lw         $t4, 0x14($t0)
    /* 6D40 80005D40 8D990014 */  lw         $t9, 0x14($t4)
    /* 6D44 80005D44 17200004 */  bnez       $t9, .L80005D58
    /* 6D48 80005D48 00000000 */   nop
    /* 6D4C 80005D4C 24090001 */  addiu      $t1, $zero, 0x1
    /* 6D50 80005D50 10000002 */  b          .L80005D5C
    /* 6D54 80005D54 AFA90030 */   sw        $t1, 0x30($sp)
  .L80005D58:
    /* 6D58 80005D58 AFA00030 */  sw         $zero, 0x30($sp)
  .L80005D5C:
    /* 6D5C 80005D5C 8FAB0034 */  lw         $t3, 0x34($sp)
    /* 6D60 80005D60 27A5003C */  addiu      $a1, $sp, 0x3C
    /* 6D64 80005D64 24060001 */  addiu      $a2, $zero, 0x1
    /* 6D68 80005D68 0C0013F8 */  jal        func_80004FE0
    /* 6D6C 80005D6C 8D640010 */   lw        $a0, 0x10($t3)
    /* 6D70 80005D70 3C040010 */  lui        $a0, (0x100401 >> 16)
    /* 6D74 80005D74 0C001994 */  jal        __osResetGlobalIntMask
    /* 6D78 80005D78 34840401 */   ori       $a0, $a0, (0x100401 & 0xFFFF)
    /* 6D7C 80005D7C 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 6D80 80005D80 8FAD0044 */  lw         $t5, 0x44($sp)
    /* 6D84 80005D84 3C018000 */  lui        $at, (0x80000000 >> 16)
    /* 6D88 80005D88 8DC60010 */  lw         $a2, 0x10($t6)
    /* 6D8C 80005D8C 3C050500 */  lui        $a1, (0x5000510 >> 16)
    /* 6D90 80005D90 34A50510 */  ori        $a1, $a1, (0x5000510 & 0xFFFF)
    /* 6D94 80005D94 00C15025 */  or         $t2, $a2, $at
    /* 6D98 80005D98 01403025 */  or         $a2, $t2, $zero
    /* 6D9C 80005D9C 0C0027AC */  jal        func_80009EB0
    /* 6DA0 80005DA0 8DA40014 */   lw        $a0, 0x14($t5)
  .L80005DA4:
    /* 6DA4 80005DA4 8FAF0034 */  lw         $t7, 0x34($sp)
    /* 6DA8 80005DA8 27A50040 */  addiu      $a1, $sp, 0x40
    /* 6DAC 80005DAC 24060001 */  addiu      $a2, $zero, 0x1
    /* 6DB0 80005DB0 0C0013F8 */  jal        func_80004FE0
    /* 6DB4 80005DB4 8DE4000C */   lw        $a0, 0xC($t7)
    /* 6DB8 80005DB8 8FB80044 */  lw         $t8, 0x44($sp)
    /* 6DBC 80005DBC 2401001D */  addiu      $at, $zero, 0x1D
endlabel func_80005C94
