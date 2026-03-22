
nonmatching func_80005C00, 0x310

glabel func_80005C00
    /* 6C00 80005C00 ADA00018 */  sw         $zero, 0x18($t5)
    /* 6C04 80005C04 8FA80028 */  lw         $t0, 0x28($sp)
    /* 6C08 80005C08 A5180010 */  sh         $t8, 0x10($t0)
    /* 6C0C 80005C0C 8FA90028 */  lw         $t1, 0x28($sp)
    /* 6C10 80005C10 0C0019AC */  jal        func_800066B0
    /* 6C14 80005C14 A5200012 */   sh        $zero, 0x12($t1)
    /* 6C18 80005C18 3C0A8001 */  lui        $t2, %hi(D_8000A41C)
    /* 6C1C 80005C1C 8D4AA41C */  lw         $t2, %lo(D_8000A41C)($t2)
    /* 6C20 80005C20 8FAB0028 */  lw         $t3, 0x28($sp)
    /* 6C24 80005C24 00408025 */  or         $s0, $v0, $zero
    /* 6C28 80005C28 3C018001 */  lui        $at, %hi(D_8000A41C)
    /* 6C2C 80005C2C AD6A000C */  sw         $t2, 0xC($t3)
    /* 6C30 80005C30 8FB90028 */  lw         $t9, 0x28($sp)
    /* 6C34 80005C34 02002025 */  or         $a0, $s0, $zero
    /* 6C38 80005C38 0C0019B4 */  jal        func_800066D0
    /* 6C3C 80005C3C AC39A41C */   sw        $t9, %lo(D_8000A41C)($at)
    /* 6C40 80005C40 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 6C44 80005C44 8FB00018 */  lw         $s0, 0x18($sp)
    /* 6C48 80005C48 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 6C4C 80005C4C 03E00008 */  jr         $ra
/* glabel func_80005C50 */
    /* 6C50 80005C50 00000000 */  nop
    /* 6C54 80005C54 00000000 */  nop
    /* 6C58 80005C58 00000000 */  nop
    /* 6C5C 80005C5C 00000000 */  nop
    /* 6C60 80005C60 27BDFFB8 */  addiu      $sp, $sp, -0x48
    /* 6C64 80005C64 AFA40048 */  sw         $a0, 0x48($sp)
    /* 6C68 80005C68 8FAE0048 */  lw         $t6, 0x48($sp)
    /* 6C6C 80005C6C AFBF001C */  sw         $ra, 0x1C($sp)
    /* 6C70 80005C70 AFA00030 */  sw         $zero, 0x30($sp)
    /* 6C74 80005C74 AFA00044 */  sw         $zero, 0x44($sp)
    /* 6C78 80005C78 AFA00038 */  sw         $zero, 0x38($sp)
    /* 6C7C 80005C7C AFAE0034 */  sw         $t6, 0x34($sp)
  .L80005C80:
    /* 6C80 80005C80 8FAF0034 */  lw         $t7, 0x34($sp)
    /* 6C84 80005C84 27A50044 */  addiu      $a1, $sp, 0x44
    /* 6C88 80005C88 24060001 */  addiu      $a2, $zero, 0x1
    /* 6C8C 80005C8C 0C0013F8 */  jal        func_80004FE0
    /* 6C90 80005C90 8DE40008 */   lw        $a0, 0x8($t7)
/* glabel func_80005C94 */
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
/* glabel func_80005DC0 */
    /* 6DC0 80005DC0 8F080014 */  lw         $t0, 0x14($t8)
    /* 6DC4 80005DC4 250C0014 */  addiu      $t4, $t0, 0x14
    /* 6DC8 80005DC8 AFAC0028 */  sw         $t4, 0x28($sp)
    /* 6DCC 80005DCC 95990006 */  lhu        $t9, 0x6($t4)
    /* 6DD0 80005DD0 001948C0 */  sll        $t1, $t9, 3
    /* 6DD4 80005DD4 01394821 */  addu       $t1, $t1, $t9
    /* 6DD8 80005DD8 00094880 */  sll        $t1, $t1, 2
    /* 6DDC 80005DDC 01895821 */  addu       $t3, $t4, $t1
    /* 6DE0 80005DE0 256D0018 */  addiu      $t5, $t3, 0x18
    /* 6DE4 80005DE4 AFAD002C */  sw         $t5, 0x2C($sp)
    /* 6DE8 80005DE8 8D6E0018 */  lw         $t6, 0x18($t3)
    /* 6DEC 80005DEC 15C1002E */  bne        $t6, $at, .L80005EA8
    /* 6DF0 80005DF0 00000000 */   nop
    /* 6DF4 80005DF4 8D860010 */  lw         $a2, 0x10($t4)
    /* 6DF8 80005DF8 3C011000 */  lui        $at, (0x10000000 >> 16)
    /* 6DFC 80005DFC 3C050500 */  lui        $a1, (0x5000510 >> 16)
    /* 6E00 80005E00 00C15025 */  or         $t2, $a2, $at
    /* 6E04 80005E04 01403025 */  or         $a2, $t2, $zero
    /* 6E08 80005E08 34A50510 */  ori        $a1, $a1, (0x5000510 & 0xFFFF)
    /* 6E0C 80005E0C 0C0027AC */  jal        func_80009EB0
    /* 6E10 80005E10 8F040014 */   lw        $a0, 0x14($t8)
    /* 6E14 80005E14 8FAF0044 */  lw         $t7, 0x44($sp)
    /* 6E18 80005E18 8FA80028 */  lw         $t0, 0x28($sp)
    /* 6E1C 80005E1C 3C050500 */  lui        $a1, (0x5000510 >> 16)
    /* 6E20 80005E20 34A50510 */  ori        $a1, $a1, (0x5000510 & 0xFFFF)
    /* 6E24 80005E24 8DE40014 */  lw         $a0, 0x14($t7)
    /* 6E28 80005E28 0C0027AC */  jal        func_80009EB0
    /* 6E2C 80005E2C 8D060010 */   lw        $a2, 0x10($t0)
    /* 6E30 80005E30 8FB90044 */  lw         $t9, 0x44($sp)
    /* 6E34 80005E34 3C050500 */  lui        $a1, (0x5000508 >> 16)
    /* 6E38 80005E38 34A50508 */  ori        $a1, $a1, (0x5000508 & 0xFFFF)
    /* 6E3C 80005E3C 27A60024 */  addiu      $a2, $sp, 0x24
    /* 6E40 80005E40 0C002714 */  jal        func_80009C50
    /* 6E44 80005E44 8F240014 */   lw        $a0, 0x14($t9)
    /* 6E48 80005E48 8FA90024 */  lw         $t1, 0x24($sp)
    /* 6E4C 80005E4C 3C010200 */  lui        $at, (0x2000000 >> 16)
    /* 6E50 80005E50 01216824 */  and        $t5, $t1, $at
    /* 6E54 80005E54 11A0000B */  beqz       $t5, .L80005E84
    /* 6E58 80005E58 00000000 */   nop
    /* 6E5C 80005E5C 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 6E60 80005E60 8FAB0044 */  lw         $t3, 0x44($sp)
    /* 6E64 80005E64 3C010100 */  lui        $at, (0x1000000 >> 16)
    /* 6E68 80005E68 8DC60010 */  lw         $a2, 0x10($t6)
    /* 6E6C 80005E6C 3C050500 */  lui        $a1, (0x5000510 >> 16)
    /* 6E70 80005E70 34A50510 */  ori        $a1, $a1, (0x5000510 & 0xFFFF)
    /* 6E74 80005E74 00C1C025 */  or         $t8, $a2, $at
    /* 6E78 80005E78 03003025 */  or         $a2, $t8, $zero
    /* 6E7C 80005E7C 0C0027AC */  jal        func_80009EB0
    /* 6E80 80005E80 8D640014 */   lw        $a0, 0x14($t3)
  .L80005E84:
    /* 6E84 80005E84 8FAA002C */  lw         $t2, 0x2C($sp)
    /* 6E88 80005E88 240C0004 */  addiu      $t4, $zero, 0x4
    /* 6E8C 80005E8C 240F0002 */  addiu      $t7, $zero, 0x2
    /* 6E90 80005E90 3C08A460 */  lui        $t0, %hi(D_A4600010)
    /* 6E94 80005E94 3C040010 */  lui        $a0, (0x100C01 >> 16)
    /* 6E98 80005E98 AD4C0000 */  sw         $t4, 0x0($t2)
    /* 6E9C 80005E9C AD0F0010 */  sw         $t7, %lo(D_A4600010)($t0)
    /* 6EA0 80005EA0 0C00197C */  jal        func_800065F0
    /* 6EA4 80005EA4 34840C01 */   ori       $a0, $a0, (0x100C01 & 0xFFFF)
  .L80005EA8:
    /* 6EA8 80005EA8 8FB90044 */  lw         $t9, 0x44($sp)
    /* 6EAC 80005EAC 00003025 */  or         $a2, $zero, $zero
    /* 6EB0 80005EB0 8F240004 */  lw         $a0, 0x4($t9)
    /* 6EB4 80005EB4 0C001770 */  jal        func_80005DC0
    /* 6EB8 80005EB8 03202825 */   or        $a1, $t9, $zero
    /* 6EBC 80005EBC 8FA90030 */  lw         $t1, 0x30($sp)
    /* 6EC0 80005EC0 24010001 */  addiu      $at, $zero, 0x1
    /* 6EC4 80005EC4 15210008 */  bne        $t1, $at, .L80005EE8
    /* 6EC8 80005EC8 00000000 */   nop
    /* 6ECC 80005ECC 8FAD0044 */  lw         $t5, 0x44($sp)
    /* 6ED0 80005ED0 8DAB0014 */  lw         $t3, 0x14($t5)
    /* 6ED4 80005ED4 8D6E002C */  lw         $t6, 0x2C($t3)
    /* 6ED8 80005ED8 15C00003 */  bnez       $t6, .L80005EE8
    /* 6EDC 80005EDC 00000000 */   nop
    /* 6EE0 80005EE0 1000FFB0 */  b          .L80005DA4
    /* 6EE4 80005EE4 AFA00030 */   sw        $zero, 0x30($sp)
  .L80005EE8:
    /* 6EE8 80005EE8 8FB80034 */  lw         $t8, 0x34($sp)
    /* 6EEC 80005EEC 00002825 */  or         $a1, $zero, $zero
    /* 6EF0 80005EF0 00003025 */  or         $a2, $zero, $zero
    /* 6EF4 80005EF4 0C001770 */  jal        func_80005DC0
    /* 6EF8 80005EF8 8F040010 */   lw        $a0, 0x10($t8)
    /* 6EFC 80005EFC 8FAC0044 */  lw         $t4, 0x44($sp)
    /* 6F00 80005F00 24010001 */  addiu      $at, $zero, 0x1
    /* 6F04 80005F04 8D8A0014 */  lw         $t2, 0x14($t4)
    /* 6F08 80005F08 954F001A */  lhu        $t7, 0x1A($t2)
    /* 6F0C 80005F0C 15E1FF5C */  bne        $t7, $at, .L80005C80
endlabel func_80005C00
