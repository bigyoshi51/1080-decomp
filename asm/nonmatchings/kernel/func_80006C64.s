
nonmatching func_80006C64, 0xA8

glabel func_80006C64
    /* 7C64 80006C64 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 7C68 80006C68 AFA40020 */  sw         $a0, 0x20($sp)
    /* 7C6C 80006C6C 8FAE0020 */  lw         $t6, 0x20($sp)
    /* 7C70 80006C70 3C0F8002 */  lui        $t7, %hi(__rmonUtilityBuffer)
    /* 7C74 80006C74 25EFB6D0 */  addiu      $t7, $t7, %lo(__rmonUtilityBuffer)
    /* 7C78 80006C78 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 7C7C 80006C7C AFAF0018 */  sw         $t7, 0x18($sp)
    /* 7C80 80006C80 AFAE001C */  sw         $t6, 0x1C($sp)
    /* 7C84 80006C84 91D80004 */  lbu        $t8, 0x4($t6)
    /* 7C88 80006C88 24010001 */  addiu      $at, $zero, 0x1
    /* 7C8C 80006C8C A1F80004 */  sb         $t8, 0x4($t7)
    /* 7C90 80006C90 8FB90018 */  lw         $t9, 0x18($sp)
    /* 7C94 80006C94 A7200006 */  sh         $zero, 0x6($t9)
    /* 7C98 80006C98 8FA8001C */  lw         $t0, 0x1C($sp)
    /* 7C9C 80006C9C 8FAA0018 */  lw         $t2, 0x18($sp)
    /* 7CA0 80006CA0 8D09000C */  lw         $t1, 0xC($t0)
    /* 7CA4 80006CA4 AD49000C */  sw         $t1, 0xC($t2)
    /* 7CA8 80006CA8 8FAB0020 */  lw         $t3, 0x20($sp)
    /* 7CAC 80006CAC 916C0009 */  lbu        $t4, 0x9($t3)
    /* 7CB0 80006CB0 15810008 */  bne        $t4, $at, .L80006CD4
    /* 7CB4 80006CB4 00000000 */   nop
    /* 7CB8 80006CB8 8FA40018 */  lw         $a0, 0x18($sp)
    /* 7CBC 80006CBC 3C058001 */  lui        $a1, %hi(D_8000A828)
    /* 7CC0 80006CC0 24A5A828 */  addiu      $a1, $a1, %lo(D_8000A828)
    /* 7CC4 80006CC4 0C001AD5 */  jal        func_80006B54
    /* 7CC8 80006CC8 24840010 */   addiu     $a0, $a0, 0x10
    /* 7CCC 80006CCC 10000006 */  b          .L80006CE8
    /* 7CD0 80006CD0 00000000 */   nop
  .L80006CD4:
    /* 7CD4 80006CD4 8FA40018 */  lw         $a0, 0x18($sp)
    /* 7CD8 80006CD8 3C058001 */  lui        $a1, %hi(D_8000A830)
    /* 7CDC 80006CDC 24A5A830 */  addiu      $a1, $a1, %lo(D_8000A830)
    /* 7CE0 80006CE0 0C001AD5 */  jal        func_80006B54
    /* 7CE4 80006CE4 24840010 */   addiu     $a0, $a0, 0x10
  .L80006CE8:
    /* 7CE8 80006CE8 8FA40018 */  lw         $a0, 0x18($sp)
    /* 7CEC 80006CEC 24050018 */  addiu      $a1, $zero, 0x18
    /* 7CF0 80006CF0 0C001CFE */  jal        func_800073F8
    /* 7CF4 80006CF4 24060001 */   addiu     $a2, $zero, 0x1
    /* 7CF8 80006CF8 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 7CFC 80006CFC 27BD0020 */  addiu      $sp, $sp, 0x20
    /* 7D00 80006D00 00001025 */  or         $v0, $zero, $zero
    /* 7D04 80006D04 03E00008 */  jr         $ra
    /* 7D08 80006D08 00000000 */   nop
endlabel func_80006C64
