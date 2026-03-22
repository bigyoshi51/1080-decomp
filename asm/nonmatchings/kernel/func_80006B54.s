
nonmatching func_80006B54, 0x84

glabel func_80006B54
    /* 7B54 80006B54 8D250000 */  lw         $a1, 0x0($t1)
    /* 7B58 80006B58 252A0004 */  addiu      $t2, $t1, 0x4
    /* 7B5C 80006B5C 0C001A94 */  jal        func_80006A50
    /* 7B60 80006B60 AFAA0024 */   sw        $t2, 0x24($sp)
    /* 7B64 80006B64 8E0B0010 */  lw         $t3, 0x10($s0)
    /* 7B68 80006B68 256C0004 */  addiu      $t4, $t3, 0x4
    /* 7B6C 80006B6C AE0C0010 */  sw         $t4, 0x10($s0)
    /* 7B70 80006B70 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 7B74 80006B74 01C08825 */  or         $s1, $t6, $zero
    /* 7B78 80006B78 25CDFFFF */  addiu      $t5, $t6, -0x1
    /* 7B7C 80006B7C 1620FFF3 */  bnez       $s1, .L80006B4C
    /* 7B80 80006B80 AFAD0028 */   sw        $t5, 0x28($sp)
    /* 7B84 80006B84 10000005 */  b          .L80006B9C
    /* 7B88 80006B88 00000000 */   nop
  .L80006B8C:
    /* 7B8C 80006B8C 8E040010 */  lw         $a0, 0x10($s0)
    /* 7B90 80006B90 26050018 */  addiu      $a1, $s0, 0x18
    /* 7B94 80006B94 0C001ABB */  jal        func_80006AEC
    /* 7B98 80006B98 8E060014 */   lw        $a2, 0x14($s0)
  .L80006B9C:
    /* 7B9C 80006B9C 920F0004 */  lbu        $t7, 0x4($s0)
    /* 7BA0 80006BA0 A7A0003A */  sh         $zero, 0x3A($sp)
    /* 7BA4 80006BA4 27A40034 */  addiu      $a0, $sp, 0x34
    /* 7BA8 80006BA8 A3AF0038 */  sb         $t7, 0x38($sp)
    /* 7BAC 80006BAC 8E18000C */  lw         $t8, 0xC($s0)
    /* 7BB0 80006BB0 24050010 */  addiu      $a1, $zero, 0x10
    /* 7BB4 80006BB4 24060001 */  addiu      $a2, $zero, 0x1
    /* 7BB8 80006BB8 0C001CFE */  jal        func_800073F8
    /* 7BBC 80006BBC AFB80040 */   sw        $t8, 0x40($sp)
    /* 7BC0 80006BC0 00001025 */  or         $v0, $zero, $zero
  .L80006BC4:
    /* 7BC4 80006BC4 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 7BC8 80006BC8 8FB00014 */  lw         $s0, 0x14($sp)
    /* 7BCC 80006BCC 8FB10018 */  lw         $s1, 0x18($sp)
    /* 7BD0 80006BD0 03E00008 */  jr         $ra
    /* 7BD4 80006BD4 27BD0048 */   addiu     $sp, $sp, 0x48
endlabel func_80006B54
