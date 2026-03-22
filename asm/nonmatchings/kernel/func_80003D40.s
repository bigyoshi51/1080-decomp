
nonmatching func_80003D40, 0xCC

glabel func_80003D40
    /* 4D40 80003D40 3C0E8002 */  lui        $t6, %hi(D_80019644)
    /* 4D44 80003D44 8DCE9644 */  lw         $t6, %lo(D_80019644)($t6)
    /* 4D48 80003D48 27BDFFC0 */  addiu      $sp, $sp, -0x40
    /* 4D4C 80003D4C AFBF001C */  sw         $ra, 0x1C($sp)
    /* 4D50 80003D50 25CF0014 */  addiu      $t7, $t6, 0x14
    /* 4D54 80003D54 AFA0003C */  sw         $zero, 0x3C($sp)
    /* 4D58 80003D58 AFAF0030 */  sw         $t7, 0x30($sp)
    /* 4D5C 80003D5C 95D8001A */  lhu        $t8, 0x1A($t6)
    /* 4D60 80003D60 3C0AA460 */  lui        $t2, %hi(D_A4600010)
    /* 4D64 80003D64 0018C8C0 */  sll        $t9, $t8, 3
    /* 4D68 80003D68 0338C821 */  addu       $t9, $t9, $t8
    /* 4D6C 80003D6C 0019C880 */  sll        $t9, $t9, 2
    /* 4D70 80003D70 01F94021 */  addu       $t0, $t7, $t9
    /* 4D74 80003D74 25090018 */  addiu      $t1, $t0, 0x18
    /* 4D78 80003D78 AFA9002C */  sw         $t1, 0x2C($sp)
    /* 4D7C 80003D7C 8D4B0010 */  lw         $t3, %lo(D_A4600010)($t2)
    /* 4D80 80003D80 AFAB0038 */  sw         $t3, 0x38($sp)
    /* 4D84 80003D84 8FAC0038 */  lw         $t4, 0x38($sp)
    /* 4D88 80003D88 318D0001 */  andi       $t5, $t4, 0x1
    /* 4D8C 80003D8C 11A0000C */  beqz       $t5, .L80003DC0
    /* 4D90 80003D90 00000000 */   nop
    /* 4D94 80003D94 3C0E8001 */  lui        $t6, %hi(D_8000A3E0)
    /* 4D98 80003D98 8DCEA3E0 */  lw         $t6, %lo(D_8000A3E0)($t6)
    /* 4D9C 80003D9C 2401F7FF */  addiu      $at, $zero, -0x801
    /* 4DA0 80003DA0 240F001D */  addiu      $t7, $zero, 0x1D
    /* 4DA4 80003DA4 01C1C024 */  and        $t8, $t6, $at
    /* 4DA8 80003DA8 3C018001 */  lui        $at, %hi(D_8000A3E0)
    /* 4DAC 80003DAC AC38A3E0 */  sw         $t8, %lo(D_8000A3E0)($at)
    /* 4DB0 80003DB0 0C001233 */  jal        func_800048CC
    /* 4DB4 80003DB4 AD0F0018 */   sw        $t7, 0x18($t0)
    /* 4DB8 80003DB8 10000186 */  b          .L800043D4
    /* 4DBC 80003DBC 24020001 */   addiu     $v0, $zero, 0x1
  .L80003DC0:
    /* 4DC0 80003DC0 3C19A460 */  lui        $t9, %hi(D_A4600010)
    /* 4DC4 80003DC4 8F290010 */  lw         $t1, %lo(D_A4600010)($t9)
    /* 4DC8 80003DC8 AFA90038 */  sw         $t1, 0x38($sp)
    /* 4DCC 80003DCC 8FAA0038 */  lw         $t2, 0x38($sp)
    /* 4DD0 80003DD0 314B0003 */  andi       $t3, $t2, 0x3
    /* 4DD4 80003DD4 11600008 */  beqz       $t3, .L80003DF8
    /* 4DD8 80003DD8 00000000 */   nop
  .L80003DDC:
    /* 4DDC 80003DDC 3C0CA460 */  lui        $t4, %hi(D_A4600010)
    /* 4DE0 80003DE0 8D8D0010 */  lw         $t5, %lo(D_A4600010)($t4)
    /* 4DE4 80003DE4 AFAD0038 */  sw         $t5, 0x38($sp)
    /* 4DE8 80003DE8 8FAE0038 */  lw         $t6, 0x38($sp)
    /* 4DEC 80003DEC 31D80003 */  andi       $t8, $t6, 0x3
    /* 4DF0 80003DF0 1700FFFA */  bnez       $t8, .L80003DDC
    /* 4DF4 80003DF4 00000000 */   nop
  .L80003DF8:
    /* 4DF8 80003DF8 3C0FA500 */  lui        $t7, %hi(D_A5000508)
    /* 4DFC 80003DFC 8DE80508 */  lw         $t0, %lo(D_A5000508)($t7)
    /* 4E00 80003E00 3C010200 */  lui        $at, (0x2000000 >> 16)
    /* 4E04 80003E04 AFA8003C */  sw         $t0, 0x3C($sp)
    /* 4E08 80003E08 8FB9003C */  lw         $t9, 0x3C($sp)
endlabel func_80003D40
