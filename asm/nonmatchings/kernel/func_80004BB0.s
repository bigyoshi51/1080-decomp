
nonmatching func_80004BB0, 0x138

glabel func_80004BB0
    /* 5BB0 80004BB0 1160FFF6 */  beqz       $t3, .L80004B8C
    /* 5BB4 80004BB4 00000000 */   nop
  .L80004BB8:
    /* 5BB8 80004BB8 3C048002 */  lui        $a0, %hi(readhost_bss_0000)
    /* 5BBC 80004BBC 248494E0 */  addiu      $a0, $a0, %lo(readhost_bss_0000)
    /* 5BC0 80004BC0 00002825 */  or         $a1, $zero, $zero
    /* 5BC4 80004BC4 0C0013F8 */  jal        func_80004FE0
    /* 5BC8 80004BC8 24060001 */   addiu     $a2, $zero, 0x1
    /* 5BCC 80004BCC 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 5BD0 80004BD0 8FB00018 */  lw         $s0, 0x18($sp)
    /* 5BD4 80004BD4 27BD0030 */  addiu      $sp, $sp, 0x30
    /* 5BD8 80004BD8 03E00008 */  jr         $ra
    /* 5BDC 80004BDC 00000000 */   nop
/* glabel func_80004BE0 */
    /* 5BE0 80004BE0 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 5BE4 80004BE4 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 5BE8 80004BE8 AFA40028 */  sw         $a0, 0x28($sp)
    /* 5BEC 80004BEC AFA5002C */  sw         $a1, 0x2C($sp)
    /* 5BF0 80004BF0 AFA60030 */  sw         $a2, 0x30($sp)
    /* 5BF4 80004BF4 AFB10018 */  sw         $s1, 0x18($sp)
    /* 5BF8 80004BF8 0C0019AC */  jal        func_800066B0
    /* 5BFC 80004BFC AFB00014 */   sw        $s0, 0x14($sp)
    /* 5C00 80004C00 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 5C04 80004C04 00408025 */  or         $s0, $v0, $zero
/* glabel func_80004C08 */
    /* 5C08 80004C08 8DCF0008 */  lw         $t7, 0x8($t6)
    /* 5C0C 80004C0C 15E00012 */  bnez       $t7, .L80004C58
    /* 5C10 80004C10 00000000 */   nop
  .L80004C14:
    /* 5C14 80004C14 8FB80030 */  lw         $t8, 0x30($sp)
    /* 5C18 80004C18 17000005 */  bnez       $t8, .L80004C30
    /* 5C1C 80004C1C 00000000 */   nop
    /* 5C20 80004C20 0C0019B4 */  jal        func_800066D0
    /* 5C24 80004C24 02002025 */   or        $a0, $s0, $zero
    /* 5C28 80004C28 10000036 */  b          .L80004D04
    /* 5C2C 80004C2C 2402FFFF */   addiu     $v0, $zero, -0x1
  .L80004C30:
    /* 5C30 80004C30 3C088001 */  lui        $t0, %hi(D_8000A420)
    /* 5C34 80004C34 8D08A420 */  lw         $t0, %lo(D_8000A420)($t0)
    /* 5C38 80004C38 24190008 */  addiu      $t9, $zero, 0x8
    /* 5C3C 80004C3C A5190010 */  sh         $t9, 0x10($t0)
    /* 5C40 80004C40 0C000F43 */  jal        func_80003D0C
    /* 5C44 80004C44 8FA40028 */   lw        $a0, 0x28($sp)
    /* 5C48 80004C48 8FA90028 */  lw         $t1, 0x28($sp)
    /* 5C4C 80004C4C 8D2A0008 */  lw         $t2, 0x8($t1)
    /* 5C50 80004C50 1140FFF0 */  beqz       $t2, .L80004C14
    /* 5C54 80004C54 00000000 */   nop
  .L80004C58:
    /* 5C58 80004C58 8FAB002C */  lw         $t3, 0x2C($sp)
    /* 5C5C 80004C5C 11600008 */  beqz       $t3, .L80004C80
    /* 5C60 80004C60 00000000 */   nop
    /* 5C64 80004C64 8FAC0028 */  lw         $t4, 0x28($sp)
    /* 5C68 80004C68 8D8E000C */  lw         $t6, 0xC($t4)
    /* 5C6C 80004C6C 8D8D0014 */  lw         $t5, 0x14($t4)
    /* 5C70 80004C70 000E7880 */  sll        $t7, $t6, 2
    /* 5C74 80004C74 01AFC021 */  addu       $t8, $t5, $t7
    /* 5C78 80004C78 8F190000 */  lw         $t9, 0x0($t8)
/* glabel func_80004C7C */
    /* 5C7C 80004C7C AD790000 */  sw         $t9, 0x0($t3)
  .L80004C80:
    /* 5C80 80004C80 8FA80028 */  lw         $t0, 0x28($sp)
    /* 5C84 80004C84 8D09000C */  lw         $t1, 0xC($t0)
    /* 5C88 80004C88 8D0C0010 */  lw         $t4, 0x10($t0)
    /* 5C8C 80004C8C 252A0001 */  addiu      $t2, $t1, 0x1
    /* 5C90 80004C90 014C001A */  div        $zero, $t2, $t4
    /* 5C94 80004C94 00007010 */  mfhi       $t6
    /* 5C98 80004C98 AD0E000C */  sw         $t6, 0xC($t0)
    /* 5C9C 80004C9C 8FAD0028 */  lw         $t5, 0x28($sp)
    /* 5CA0 80004CA0 15800002 */  bnez       $t4, .L80004CAC
    /* 5CA4 80004CA4 00000000 */   nop
    /* 5CA8 80004CA8 0007000D */  break      7
  .L80004CAC:
    /* 5CAC 80004CAC 2401FFFF */  addiu      $at, $zero, -0x1
    /* 5CB0 80004CB0 15810004 */  bne        $t4, $at, .L80004CC4
    /* 5CB4 80004CB4 3C018000 */   lui       $at, (0x80000000 >> 16)
    /* 5CB8 80004CB8 15410002 */  bne        $t2, $at, .L80004CC4
    /* 5CBC 80004CBC 00000000 */   nop
    /* 5CC0 80004CC0 0006000D */  break      6
  .L80004CC4:
    /* 5CC4 80004CC4 8DAF0008 */  lw         $t7, 0x8($t5)
    /* 5CC8 80004CC8 25F8FFFF */  addiu      $t8, $t7, -0x1
    /* 5CCC 80004CCC ADB80008 */  sw         $t8, 0x8($t5)
    /* 5CD0 80004CD0 8FB90028 */  lw         $t9, 0x28($sp)
    /* 5CD4 80004CD4 8F2B0004 */  lw         $t3, 0x4($t9)
    /* 5CD8 80004CD8 8D690000 */  lw         $t1, 0x0($t3)
    /* 5CDC 80004CDC 11200006 */  beqz       $t1, .L80004CF8
    /* 5CE0 80004CE0 00000000 */   nop
    /* 5CE4 80004CE4 0C000F95 */  jal        func_80003E54
endlabel func_80004BB0
