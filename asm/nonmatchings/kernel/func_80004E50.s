glabel func_80004E50
    /* 5E50 80004E50 240E0002 */  addiu      $t6, $zero, 0x2
    /* 5E54 80004E54 3C018002 */  lui        $at, %hi(D_800195D4)
    /* 5E58 80004E58 A02E95D4 */  sb         $t6, %lo(D_800195D4)($at)
    /* 5E5C 80004E5C 3C018002 */  lui        $at, %hi(D_800195DC)
    /* 5E60 80004E60 3C0FA500 */  lui        $t7, (0xA5000000 >> 16)
    /* 5E64 80004E64 AC2F95DC */  sw         $t7, %lo(D_800195DC)($at)
    /* 5E68 80004E68 3C018002 */  lui        $at, %hi(D_800195D5)
    /* 5E6C 80004E6C 24180003 */  addiu      $t8, $zero, 0x3
    /* 5E70 80004E70 A03895D5 */  sb         $t8, %lo(D_800195D5)($at)
    /* 5E74 80004E74 3C018002 */  lui        $at, %hi(D_800195D8)
    /* 5E78 80004E78 24190006 */  addiu      $t9, $zero, 0x6
    /* 5E7C 80004E7C A03995D8 */  sb         $t9, %lo(D_800195D8)($at)
    /* 5E80 80004E80 3C018002 */  lui        $at, %hi(D_800195D6)
    /* 5E84 80004E84 24080006 */  addiu      $t0, $zero, 0x6
    /* 5E88 80004E88 24090002 */  addiu      $t1, $zero, 0x2
    /* 5E8C 80004E8C A02895D6 */  sb         $t0, %lo(D_800195D6)($at)
    /* 5E90 80004E90 A02995D7 */  sb         $t1, %lo(D_800195D7)($at)
    /* 5E94 80004E94 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 5E98 80004E98 3C018002 */  lui        $at, %hi(D_800195D9)
    /* 5E9C 80004E9C 240A0001 */  addiu      $t2, $zero, 0x1
    /* 5EA0 80004EA0 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 5EA4 80004EA4 A02A95D9 */  sb         $t2, %lo(D_800195D9)($at)
    /* 5EA8 80004EA8 240B0003 */  addiu      $t3, $zero, 0x3
    /* 5EAC 80004EAC 3C0CA460 */  lui        $t4, %hi(D_A4600024)
    /* 5EB0 80004EB0 AD8B0024 */  sw         $t3, %lo(D_A4600024)($t4)
    /* 5EB4 80004EB4 3C0D8002 */  lui        $t5, %hi(D_800195D8)
    /* 5EB8 80004EB8 91AD95D8 */  lbu        $t5, %lo(D_800195D8)($t5)
    /* 5EBC 80004EBC 3C0EA460 */  lui        $t6, (0xA4600000 >> 16)
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
endlabel func_80004E50
