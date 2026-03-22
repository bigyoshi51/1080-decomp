
nonmatching func_80003C24, 0xE8

glabel func_80003C24
    /* 4C24 80003C24 00000000 */  nop
  .L80003C28:
    /* 4C28 80003C28 03E00008 */  jr         $ra
    /* 4C2C 80003C2C 27BD0008 */   addiu     $sp, $sp, 0x8
    /* 4C30 80003C30 27BDFFC8 */  addiu      $sp, $sp, -0x38
    /* 4C34 80003C34 AFBF0024 */  sw         $ra, 0x24($sp)
    /* 4C38 80003C38 AFA40038 */  sw         $a0, 0x38($sp)
    /* 4C3C 80003C3C AFB20020 */  sw         $s2, 0x20($sp)
    /* 4C40 80003C40 AFB1001C */  sw         $s1, 0x1C($sp)
    /* 4C44 80003C44 0C0019AC */  jal        func_800066B0
    /* 4C48 80003C48 AFB00018 */   sw        $s0, 0x18($sp)
    /* 4C4C 80003C4C 8FAE0038 */  lw         $t6, 0x38($sp)
    /* 4C50 80003C50 00408025 */  or         $s0, $v0, $zero
    /* 4C54 80003C54 15C00005 */  bnez       $t6, .L80003C6C
    /* 4C58 80003C58 00000000 */   nop
    /* 4C5C 80003C5C 3C0F8001 */  lui        $t7, %hi(D_8000A420)
    /* 4C60 80003C60 8DEFA420 */  lw         $t7, %lo(D_8000A420)($t7)
    /* 4C64 80003C64 10000009 */  b          .L80003C8C
    /* 4C68 80003C68 AFAF0038 */   sw        $t7, 0x38($sp)
  .L80003C6C:
    /* 4C6C 80003C6C 8FB80038 */  lw         $t8, 0x38($sp)
    /* 4C70 80003C70 24010001 */  addiu      $at, $zero, 0x1
    /* 4C74 80003C74 97190010 */  lhu        $t9, 0x10($t8)
    /* 4C78 80003C78 13210004 */  beq        $t9, $at, .L80003C8C
    /* 4C7C 80003C7C 00000000 */   nop
    /* 4C80 80003C80 8F040008 */  lw         $a0, 0x8($t8)
    /* 4C84 80003C84 0C000FFC */  jal        func_80003FF0
    /* 4C88 80003C88 03002825 */   or        $a1, $t8, $zero
  .L80003C8C:
    /* 4C8C 80003C8C 3C088001 */  lui        $t0, %hi(D_8000A41C)
    /* 4C90 80003C90 8D08A41C */  lw         $t0, %lo(D_8000A41C)($t0)
    /* 4C94 80003C94 8FA90038 */  lw         $t1, 0x38($sp)
    /* 4C98 80003C98 15090005 */  bne        $t0, $t1, .L80003CB0
    /* 4C9C 80003C9C 00000000 */   nop
    /* 4CA0 80003CA0 8D0A000C */  lw         $t2, 0xC($t0)
    /* 4CA4 80003CA4 3C018001 */  lui        $at, %hi(D_8000A41C)
    /* 4CA8 80003CA8 10000013 */  b          .L80003CF8
    /* 4CAC 80003CAC AC2AA41C */   sw        $t2, %lo(D_8000A41C)($at)
  .L80003CB0:
    /* 4CB0 80003CB0 3C118001 */  lui        $s1, %hi(D_8000A41C)
    /* 4CB4 80003CB4 8E31A41C */  lw         $s1, %lo(D_8000A41C)($s1)
    /* 4CB8 80003CB8 2401FFFF */  addiu      $at, $zero, -0x1
    /* 4CBC 80003CBC 8E2B0004 */  lw         $t3, 0x4($s1)
    /* 4CC0 80003CC0 1161000D */  beq        $t3, $at, .L80003CF8
    /* 4CC4 80003CC4 00000000 */   nop
  .L80003CC8:
    /* 4CC8 80003CC8 8E32000C */  lw         $s2, 0xC($s1)
    /* 4CCC 80003CCC 8FAC0038 */  lw         $t4, 0x38($sp)
    /* 4CD0 80003CD0 164C0004 */  bne        $s2, $t4, .L80003CE4
    /* 4CD4 80003CD4 00000000 */   nop
    /* 4CD8 80003CD8 8D8D000C */  lw         $t5, 0xC($t4)
    /* 4CDC 80003CDC 10000006 */  b          .L80003CF8
    /* 4CE0 80003CE0 AE2D000C */   sw        $t5, 0xC($s1)
  .L80003CE4:
    /* 4CE4 80003CE4 02408825 */  or         $s1, $s2, $zero
    /* 4CE8 80003CE8 8E2E0004 */  lw         $t6, 0x4($s1)
    /* 4CEC 80003CEC 2401FFFF */  addiu      $at, $zero, -0x1
    /* 4CF0 80003CF0 15C1FFF5 */  bne        $t6, $at, .L80003CC8
    /* 4CF4 80003CF4 00000000 */   nop
  .L80003CF8:
    /* 4CF8 80003CF8 3C198001 */  lui        $t9, %hi(D_8000A420)
    /* 4CFC 80003CFC 8F39A420 */  lw         $t9, %lo(D_8000A420)($t9)
    /* 4D00 80003D00 8FAF0038 */  lw         $t7, 0x38($sp)
    /* 4D04 80003D04 15F90003 */  bne        $t7, $t9, .L80003D14
    /* 4D08 80003D08 00000000 */   nop
endlabel func_80003C24
