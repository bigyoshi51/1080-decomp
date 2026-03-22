
nonmatching func_80001DD0, 0xF8

glabel func_80001DD0
    /* 2DD0 80001DD0 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 2DD4 80001DD4 AFBF0024 */  sw         $ra, 0x24($sp)
    /* 2DD8 80001DD8 AFB10020 */  sw         $s1, 0x20($sp)
    /* 2DDC 80001DDC AFB0001C */  sw         $s0, 0x1C($sp)
    /* 2DE0 80001DE0 AFA5002C */  sw         $a1, 0x2C($sp)
    /* 2DE4 80001DE4 8C910054 */  lw         $s1, 0x54($a0)
    /* 2DE8 80001DE8 00808025 */  or         $s0, $a0, $zero
    /* 2DEC 80001DEC 8FAE002C */  lw         $t6, 0x2C($sp)
    /* 2DF0 80001DF0 1220000D */  beqz       $s1, .L80001E28
    /* 2DF4 80001DF4 02202825 */   or        $a1, $s1, $zero
    /* 2DF8 80001DF8 8E060048 */  lw         $a2, 0x48($s0)
    /* 2DFC 80001DFC 8E070010 */  lw         $a3, 0x10($s0)
    /* 2E00 80001E00 0C00073C */  jal        func_80001CF0
    /* 2E04 80001E04 AFAE0010 */   sw        $t6, 0x10($sp)
    /* 2E08 80001E08 00408825 */  or         $s1, $v0, $zero
    /* 2E0C 80001E0C 8E040054 */  lw         $a0, 0x54($s0)
    /* 2E10 80001E10 0C000146 */  jal        func_80000518
    /* 2E14 80001E14 8E05001C */   lw        $a1, 0x1C($s0)
    /* 2E18 80001E18 52200004 */  beql       $s1, $zero, .L80001E2C
    /* 2E1C 80001E1C 8E050050 */   lw        $a1, 0x50($s0)
    /* 2E20 80001E20 10000024 */  b          .L80001EB4
    /* 2E24 80001E24 2402FFF2 */   addiu     $v0, $zero, -0xE
  .L80001E28:
    /* 2E28 80001E28 8E050050 */  lw         $a1, 0x50($s0)
  .L80001E2C:
    /* 2E2C 80001E2C 02002025 */  or         $a0, $s0, $zero
    /* 2E30 80001E30 8FAF002C */  lw         $t7, 0x2C($sp)
    /* 2E34 80001E34 50A0000E */  beql       $a1, $zero, .L80001E70
    /* 2E38 80001E38 8E05004C */   lw        $a1, 0x4C($s0)
    /* 2E3C 80001E3C 8E060044 */  lw         $a2, 0x44($s0)
    /* 2E40 80001E40 8E07000C */  lw         $a3, 0xC($s0)
    /* 2E44 80001E44 0C00073C */  jal        func_80001CF0
    /* 2E48 80001E48 AFAF0010 */   sw        $t7, 0x10($sp)
    /* 2E4C 80001E4C 00408825 */  or         $s1, $v0, $zero
    /* 2E50 80001E50 8E040050 */  lw         $a0, 0x50($s0)
    /* 2E54 80001E54 0C000146 */  jal        func_80000518
    /* 2E58 80001E58 8E050018 */   lw        $a1, 0x18($s0)
    /* 2E5C 80001E5C 52200004 */  beql       $s1, $zero, .L80001E70
    /* 2E60 80001E60 8E05004C */   lw        $a1, 0x4C($s0)
    /* 2E64 80001E64 10000013 */  b          .L80001EB4
    /* 2E68 80001E68 2402FFF1 */   addiu     $v0, $zero, -0xF
    /* 2E6C 80001E6C 8E05004C */  lw         $a1, 0x4C($s0)
  .L80001E70:
    /* 2E70 80001E70 02002025 */  or         $a0, $s0, $zero
    /* 2E74 80001E74 8FB8002C */  lw         $t8, 0x2C($sp)
    /* 2E78 80001E78 50A0000E */  beql       $a1, $zero, .L80001EB4
    /* 2E7C 80001E7C 00001025 */   or        $v0, $zero, $zero
    /* 2E80 80001E80 8E060040 */  lw         $a2, 0x40($s0)
    /* 2E84 80001E84 8E070008 */  lw         $a3, 0x8($s0)
    /* 2E88 80001E88 0C00073C */  jal        func_80001CF0
    /* 2E8C 80001E8C AFB80010 */   sw        $t8, 0x10($sp)
    /* 2E90 80001E90 00408825 */  or         $s1, $v0, $zero
    /* 2E94 80001E94 8E04004C */  lw         $a0, 0x4C($s0)
    /* 2E98 80001E98 0C000146 */  jal        func_80000518
    /* 2E9C 80001E9C 8E050014 */   lw        $a1, 0x14($s0)
    /* 2EA0 80001EA0 52200004 */  beql       $s1, $zero, .L80001EB4
    /* 2EA4 80001EA4 00001025 */   or        $v0, $zero, $zero
    /* 2EA8 80001EA8 10000002 */  b          .L80001EB4
    /* 2EAC 80001EAC 2402FFF0 */   addiu     $v0, $zero, -0x10
    /* 2EB0 80001EB0 00001025 */  or         $v0, $zero, $zero
  .L80001EB4:
    /* 2EB4 80001EB4 8FBF0024 */  lw         $ra, 0x24($sp)
    /* 2EB8 80001EB8 8FB0001C */  lw         $s0, 0x1C($sp)
    /* 2EBC 80001EBC 8FB10020 */  lw         $s1, 0x20($sp)
    /* 2EC0 80001EC0 03E00008 */  jr         $ra
    /* 2EC4 80001EC4 27BD0028 */   addiu     $sp, $sp, 0x28
endlabel func_80001DD0
