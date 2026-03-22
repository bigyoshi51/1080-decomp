
nonmatching func_80004EC0, 0x90

glabel func_80004EC0
    /* 5EC0 80004EC0 3C0F8002 */  lui        $t7, %hi(D_800195D6)
    /* 5EC4 80004EC4 ADCD0028 */  sw         $t5, 0x28($t6)
    /* 5EC8 80004EC8 91EF95D6 */  lbu        $t7, %lo(D_800195D6)($t7)
    /* 5ECC 80004ECC 3C18A460 */  lui        $t8, %hi(D_A460002C)
    /* 5ED0 80004ED0 3C198002 */  lui        $t9, %hi(D_800195D7)
    /* 5ED4 80004ED4 AF0F002C */  sw         $t7, %lo(D_A460002C)($t8)
    /* 5ED8 80004ED8 933995D7 */  lbu        $t9, %lo(D_800195D7)($t9)
    /* 5EDC 80004EDC 3C08A460 */  lui        $t0, %hi(D_A4600030)
    /* 5EE0 80004EE0 3C048002 */  lui        $a0, %hi(D_800195D0)
    /* 5EE4 80004EE4 3C018002 */  lui        $at, %hi(D_800195E0)
    /* 5EE8 80004EE8 248495D0 */  addiu      $a0, $a0, %lo(D_800195D0)
    /* 5EEC 80004EEC AD190030 */  sw         $t9, %lo(D_A4600030)($t0)
    /* 5EF0 80004EF0 AC2095E0 */  sw         $zero, %lo(D_800195E0)($at)
    /* 5EF4 80004EF4 24840014 */  addiu      $a0, $a0, 0x14
    /* 5EF8 80004EF8 0C000C34 */  jal        func_800030D0
    /* 5EFC 80004EFC 24050060 */   addiu     $a1, $zero, 0x60
    /* 5F00 80004F00 0C0019AC */  jal        func_800066B0
    /* 5F04 80004F04 00000000 */   nop
    /* 5F08 80004F08 3C098001 */  lui        $t1, %hi(D_8000A46C)
    /* 5F0C 80004F0C 8D29A46C */  lw         $t1, %lo(D_8000A46C)($t1)
    /* 5F10 80004F10 3C018002 */  lui        $at, %hi(D_800195D0)
    /* 5F14 80004F14 3C0A8002 */  lui        $t2, %hi(D_800195D0)
    /* 5F18 80004F18 AC2995D0 */  sw         $t1, %lo(D_800195D0)($at)
    /* 5F1C 80004F1C 3C018001 */  lui        $at, %hi(D_8000A46C)
    /* 5F20 80004F20 254A95D0 */  addiu      $t2, $t2, %lo(D_800195D0)
    /* 5F24 80004F24 AC2AA46C */  sw         $t2, %lo(D_8000A46C)($at)
    /* 5F28 80004F28 AFA2001C */  sw         $v0, 0x1C($sp)
    /* 5F2C 80004F2C 3C018002 */  lui        $at, %hi(D_80019644)
    /* 5F30 80004F30 AC2A9644 */  sw         $t2, %lo(D_80019644)($at)
    /* 5F34 80004F34 0C0019B4 */  jal        func_800066D0
    /* 5F38 80004F38 8FA4001C */   lw        $a0, 0x1C($sp)
    /* 5F3C 80004F3C 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 5F40 80004F40 3C028002 */  lui        $v0, %hi(D_800195D0)
    /* 5F44 80004F44 244295D0 */  addiu      $v0, $v0, %lo(D_800195D0)
    /* 5F48 80004F48 03E00008 */  jr         $ra
    /* 5F4C 80004F4C 27BD0020 */   addiu     $sp, $sp, 0x20
endlabel func_80004EC0
