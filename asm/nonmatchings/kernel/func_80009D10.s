
nonmatching func_80009D10, 0xE0

glabel func_80009D10
    /* AD10 80009D10 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* AD14 80009D14 AFBF001C */  sw         $ra, 0x1C($sp)
    /* AD18 80009D18 AFA40028 */  sw         $a0, 0x28($sp)
    /* AD1C 80009D1C AFB10018 */  sw         $s1, 0x18($sp)
    /* AD20 80009D20 0C0019AC */  jal        func_800066B0
    /* AD24 80009D24 AFB00014 */   sw        $s0, 0x14($sp)
    /* AD28 80009D28 8FAE0028 */  lw         $t6, 0x28($sp)
    /* AD2C 80009D2C 24010001 */  addiu      $at, $zero, 0x1
    /* AD30 80009D30 00408025 */  or         $s0, $v0, $zero
    /* AD34 80009D34 95D10010 */  lhu        $s1, 0x10($t6)
    /* AD38 80009D38 1221000C */  beq        $s1, $at, .L80009D6C
    /* AD3C 80009D3C 24010008 */   addiu     $at, $zero, 0x8
    /* AD40 80009D40 1621002A */  bne        $s1, $at, .L80009DEC
    /* AD44 80009D44 00000000 */   nop
    /* AD48 80009D48 8FB80028 */  lw         $t8, 0x28($sp)
    /* AD4C 80009D4C 240F0002 */  addiu      $t7, $zero, 0x2
    /* AD50 80009D50 3C048001 */  lui        $a0, %hi(D_8000A418)
    /* AD54 80009D54 A70F0010 */  sh         $t7, 0x10($t8)
    /* AD58 80009D58 8FA50028 */  lw         $a1, 0x28($sp)
    /* AD5C 80009D5C 0C000F83 */  jal        func_80003E0C
    /* AD60 80009D60 2484A418 */   addiu     $a0, $a0, %lo(D_8000A418)
    /* AD64 80009D64 10000021 */  b          .L80009DEC
    /* AD68 80009D68 00000000 */   nop
  .L80009D6C:
    /* AD6C 80009D6C 8FB90028 */  lw         $t9, 0x28($sp)
    /* AD70 80009D70 8F280008 */  lw         $t0, 0x8($t9)
    /* AD74 80009D74 11000005 */  beqz       $t0, .L80009D8C
    /* AD78 80009D78 00000000 */   nop
    /* AD7C 80009D7C 3C098001 */  lui        $t1, %hi(D_8000A418)
    /* AD80 80009D80 2529A418 */  addiu      $t1, $t1, %lo(D_8000A418)
    /* AD84 80009D84 1509000A */  bne        $t0, $t1, .L80009DB0
    /* AD88 80009D88 00000000 */   nop
  .L80009D8C:
    /* AD8C 80009D8C 8FAB0028 */  lw         $t3, 0x28($sp)
    /* AD90 80009D90 240A0002 */  addiu      $t2, $zero, 0x2
    /* AD94 80009D94 3C048001 */  lui        $a0, %hi(D_8000A418)
    /* AD98 80009D98 A56A0010 */  sh         $t2, 0x10($t3)
    /* AD9C 80009D9C 8FA50028 */  lw         $a1, 0x28($sp)
    /* ADA0 80009DA0 0C000F83 */  jal        func_80003E0C
    /* ADA4 80009DA4 2484A418 */   addiu     $a0, $a0, %lo(D_8000A418)
    /* ADA8 80009DA8 10000010 */  b          .L80009DEC
    /* ADAC 80009DAC 00000000 */   nop
  .L80009DB0:
    /* ADB0 80009DB0 8FAD0028 */  lw         $t5, 0x28($sp)
    /* ADB4 80009DB4 240C0008 */  addiu      $t4, $zero, 0x8
    /* ADB8 80009DB8 A5AC0010 */  sh         $t4, 0x10($t5)
    /* ADBC 80009DBC 8FAE0028 */  lw         $t6, 0x28($sp)
    /* ADC0 80009DC0 8DC40008 */  lw         $a0, 0x8($t6)
    /* ADC4 80009DC4 0C000F83 */  jal        func_80003E0C
    /* ADC8 80009DC8 01C02825 */   or        $a1, $t6, $zero
    /* ADCC 80009DCC 8FAF0028 */  lw         $t7, 0x28($sp)
    /* ADD0 80009DD0 0C000F95 */  jal        func_80003E54
    /* ADD4 80009DD4 8DE40008 */   lw        $a0, 0x8($t7)
    /* ADD8 80009DD8 00408825 */  or         $s1, $v0, $zero
    /* ADDC 80009DDC 3C048001 */  lui        $a0, %hi(D_8000A418)
    /* ADE0 80009DE0 2484A418 */  addiu      $a0, $a0, %lo(D_8000A418)
    /* ADE4 80009DE4 0C000F83 */  jal        func_80003E0C
    /* ADE8 80009DE8 02202825 */   or        $a1, $s1, $zero
  .L80009DEC:
    /* ADEC 80009DEC 3C188001 */  lui        $t8, (0x80010000 >> 16)
endlabel func_80009D10
