
nonmatching func_80004DE0, 0xD8

glabel func_80004DE0
    /* 5DE0 80004DE0 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 5DE4 80004DE4 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 5DE8 80004DE8 AFA40028 */  sw         $a0, 0x28($sp)
    /* 5DEC 80004DEC AFA5002C */  sw         $a1, 0x2C($sp)
    /* 5DF0 80004DF0 AFA60030 */  sw         $a2, 0x30($sp)
    /* 5DF4 80004DF4 0C0019AC */  jal        func_800066B0
    /* 5DF8 80004DF8 AFB00018 */   sw        $s0, 0x18($sp)
    /* 5DFC 80004DFC 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 5E00 80004E00 3C188002 */  lui        $t8, %hi(__osEventStateTab)
    /* 5E04 80004E04 8FA8002C */  lw         $t0, 0x2C($sp)
    /* 5E08 80004E08 27189510 */  addiu      $t8, $t8, %lo(__osEventStateTab)
    /* 5E0C 80004E0C 000E78C0 */  sll        $t7, $t6, 3
    /* 5E10 80004E10 01F8C821 */  addu       $t9, $t7, $t8
    /* 5E14 80004E14 AFB90020 */  sw         $t9, 0x20($sp)
    /* 5E18 80004E18 AF280000 */  sw         $t0, 0x0($t9)
    /* 5E1C 80004E1C 8FAA0020 */  lw         $t2, 0x20($sp)
    /* 5E20 80004E20 8FA90030 */  lw         $t1, 0x30($sp)
    /* 5E24 80004E24 00408025 */  or         $s0, $v0, $zero
    /* 5E28 80004E28 02002025 */  or         $a0, $s0, $zero
    /* 5E2C 80004E2C 0C0019B4 */  jal        func_800066D0
    /* 5E30 80004E30 AD490004 */   sw        $t1, 0x4($t2)
    /* 5E34 80004E34 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 5E38 80004E38 8FB00018 */  lw         $s0, 0x18($sp)
    /* 5E3C 80004E3C 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 5E40 80004E40 03E00008 */  jr         $ra
    /* 5E44 80004E44 00000000 */   nop
endlabel func_80004DE0
    /* 5E48 80004E48 00000000 */  nop
    /* 5E4C 80004E4C 00000000 */  nop

/* glabel func_80004E50 */
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
endlabel func_80004DE0
