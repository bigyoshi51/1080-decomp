
nonmatching func_80004C08, 0x74

glabel func_80004C08
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
    /* 5C30 80004C30 3C088001 */  lui        $t0, %hi(__osRunningThread)
    /* 5C34 80004C34 8D08A420 */  lw         $t0, %lo(__osRunningThread)($t0)
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
endlabel func_80004C08
