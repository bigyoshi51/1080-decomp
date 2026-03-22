
nonmatching func_80004AC0, 0x50

glabel func_80004AC0
    /* 5AC0 80004AC0 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 5AC4 80004AC4 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 5AC8 80004AC8 AFA40018 */  sw         $a0, 0x18($sp)
    /* 5ACC 80004ACC 0C0015B0 */  jal        func_800056C0
    /* 5AD0 80004AD0 AFA5001C */   sw        $a1, 0x1C($sp)
    /* 5AD4 80004AD4 10400003 */  beqz       $v0, .L80004AE4
    /* 5AD8 80004AD8 00000000 */   nop
    /* 5ADC 80004ADC 10000008 */  b          .L80004B00
    /* 5AE0 80004AE0 2402FFFF */   addiu     $v0, $zero, -0x1
  .L80004AE4:
    /* 5AE4 80004AE4 8FAE0018 */  lw         $t6, 0x18($sp)
    /* 5AE8 80004AE8 3C01A000 */  lui        $at, %hi(D_A0000000)
    /* 5AEC 80004AEC 8FB9001C */  lw         $t9, 0x1C($sp)
    /* 5AF0 80004AF0 01C17825 */  or         $t7, $t6, $at
    /* 5AF4 80004AF4 8DF80000 */  lw         $t8, %lo(D_A0000000)($t7)
    /* 5AF8 80004AF8 00001025 */  or         $v0, $zero, $zero
    /* 5AFC 80004AFC AF380000 */  sw         $t8, 0x0($t9)
  .L80004B00:
    /* 5B00 80004B00 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 5B04 80004B04 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 5B08 80004B08 03E00008 */  jr         $ra
    /* 5B0C 80004B0C 00000000 */   nop
endlabel func_80004AC0
