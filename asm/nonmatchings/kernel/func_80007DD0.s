
nonmatching func_80007DD0, 0xC0

glabel func_80007DD0
    /* 8DD0 80007DD0 27BDFFC8 */  addiu      $sp, $sp, -0x38
    /* 8DD4 80007DD4 AFBF0024 */  sw         $ra, 0x24($sp)
    /* 8DD8 80007DD8 AFA40038 */  sw         $a0, 0x38($sp)
    /* 8DDC 80007DDC AFB20020 */  sw         $s2, 0x20($sp)
    /* 8DE0 80007DE0 AFB1001C */  sw         $s1, 0x1C($sp)
    /* 8DE4 80007DE4 0C0019AC */  jal        func_800066B0
    /* 8DE8 80007DE8 AFB00018 */   sw        $s0, 0x18($sp)
    /* 8DEC 80007DEC 8FAE0038 */  lw         $t6, 0x38($sp)
    /* 8DF0 80007DF0 00408025 */  or         $s0, $v0, $zero
    /* 8DF4 80007DF4 15C00003 */  bnez       $t6, .L80007E04
    /* 8DF8 80007DF8 00000000 */   nop
    /* 8DFC 80007DFC 10000003 */  b          .L80007E0C
    /* 8E00 80007E00 24110004 */   addiu     $s1, $zero, 0x4
  .L80007E04:
    /* 8E04 80007E04 8FAF0038 */  lw         $t7, 0x38($sp)
    /* 8E08 80007E08 95F10010 */  lhu        $s1, 0x10($t7)
  .L80007E0C:
    /* 8E0C 80007E0C 02209025 */  or         $s2, $s1, $zero
    /* 8E10 80007E10 24010002 */  addiu      $at, $zero, 0x2
    /* 8E14 80007E14 1241000F */  beq        $s2, $at, .L80007E54
    /* 8E18 80007E18 24010004 */   addiu     $at, $zero, 0x4
    /* 8E1C 80007E1C 12410005 */  beq        $s2, $at, .L80007E34
    /* 8E20 80007E20 24010008 */   addiu     $at, $zero, 0x8
    /* 8E24 80007E24 1241000B */  beq        $s2, $at, .L80007E54
    /* 8E28 80007E28 00000000 */   nop
    /* 8E2C 80007E2C 10000010 */  b          .L80007E70
    /* 8E30 80007E30 00000000 */   nop
  .L80007E34:
    /* 8E34 80007E34 3C198001 */  lui        $t9, %hi(D_8000A420)
    /* 8E38 80007E38 8F39A420 */  lw         $t9, %lo(D_8000A420)($t9)
    /* 8E3C 80007E3C 24180001 */  addiu      $t8, $zero, 0x1
    /* 8E40 80007E40 00002025 */  or         $a0, $zero, $zero
    /* 8E44 80007E44 0C000F43 */  jal        func_80003D0C
    /* 8E48 80007E48 A7380010 */   sh        $t8, 0x10($t9)
    /* 8E4C 80007E4C 10000008 */  b          .L80007E70
    /* 8E50 80007E50 00000000 */   nop
  .L80007E54:
    /* 8E54 80007E54 8FA90038 */  lw         $t1, 0x38($sp)
    /* 8E58 80007E58 24080001 */  addiu      $t0, $zero, 0x1
    /* 8E5C 80007E5C A5280010 */  sh         $t0, 0x10($t1)
    /* 8E60 80007E60 8FAA0038 */  lw         $t2, 0x38($sp)
    /* 8E64 80007E64 8D440008 */  lw         $a0, 0x8($t2)
    /* 8E68 80007E68 0C000FFC */  jal        func_80003FF0
    /* 8E6C 80007E6C 01402825 */   or        $a1, $t2, $zero
  .L80007E70:
    /* 8E70 80007E70 0C0019B4 */  jal        func_800066D0
    /* 8E74 80007E74 02002025 */   or        $a0, $s0, $zero
    /* 8E78 80007E78 8FBF0024 */  lw         $ra, 0x24($sp)
    /* 8E7C 80007E7C 8FB00018 */  lw         $s0, 0x18($sp)
    /* 8E80 80007E80 8FB1001C */  lw         $s1, 0x1C($sp)
    /* 8E84 80007E84 8FB20020 */  lw         $s2, 0x20($sp)
    /* 8E88 80007E88 03E00008 */  jr         $ra
    /* 8E8C 80007E8C 27BD0038 */   addiu     $sp, $sp, 0x38
endlabel func_80007DD0
    /* 8E90 80007E90 00000000 */  nop
    /* 8E94 80007E94 00000000 */  nop
    /* 8E98 80007E98 00000000 */  nop
    /* 8E9C 80007E9C 00000000 */  nop
