
nonmatching func_80006B20, 0x34

glabel func_80006B20
    /* 7B20 80006B20 8E0F0014 */  lw         $t7, 0x14($s0)
    /* 7B24 80006B24 31F80003 */  andi       $t8, $t7, 0x3
    /* 7B28 80006B28 13000003 */  beqz       $t8, .L80006B38
    /* 7B2C 80006B2C 00000000 */   nop
    /* 7B30 80006B30 10000024 */  b          .L80006BC4
    /* 7B34 80006B34 2402FFFB */   addiu     $v0, $zero, -0x5
  .L80006B38:
    /* 7B38 80006B38 8FB90028 */  lw         $t9, 0x28($sp)
    /* 7B3C 80006B3C 03208825 */  or         $s1, $t9, $zero
    /* 7B40 80006B40 2728FFFF */  addiu      $t0, $t9, -0x1
    /* 7B44 80006B44 12200015 */  beqz       $s1, .L80006B9C
    /* 7B48 80006B48 AFA80028 */   sw        $t0, 0x28($sp)
  .L80006B4C:
    /* 7B4C 80006B4C 8FA90024 */  lw         $t1, 0x24($sp)
    /* 7B50 80006B50 8E040010 */  lw         $a0, 0x10($s0)
endlabel func_80006B20
