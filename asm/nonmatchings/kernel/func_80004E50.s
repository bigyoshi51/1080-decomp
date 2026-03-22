
nonmatching func_80004E50, 0x70

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
endlabel func_80004E50
