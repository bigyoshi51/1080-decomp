
nonmatching func_80004C7C, 0x6C

glabel func_80004C7C
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
endlabel func_80004C7C
