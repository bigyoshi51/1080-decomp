
nonmatching func_80006A50, 0x48

glabel func_80006A50
    /* 7A50 80006A50 2402FFFB */  addiu      $v0, $zero, -0x5
  .L80006A54:
    /* 7A54 80006A54 8E040010 */  lw         $a0, 0x10($s0)
    /* 7A58 80006A58 2401FFFC */  addiu      $at, $zero, -0x4
    /* 7A5C 80006A5C 00817024 */  and        $t6, $a0, $at
    /* 7A60 80006A60 0C001AA6 */  jal        func_80006A98
    /* 7A64 80006A64 01C02025 */   or        $a0, $t6, $zero
    /* 7A68 80006A68 8FAF0030 */  lw         $t7, 0x30($sp)
    /* 7A6C 80006A6C 24010001 */  addiu      $at, $zero, 0x1
    /* 7A70 80006A70 AFA2002C */  sw         $v0, 0x2C($sp)
    /* 7A74 80006A74 15E1000A */  bne        $t7, $at, .L80006AA0
    /* 7A78 80006A78 00000000 */   nop
    /* 7A7C 80006A7C 92180018 */  lbu        $t8, 0x18($s0)
    /* 7A80 80006A80 8FA8002C */  lw         $t0, 0x2C($sp)
    /* 7A84 80006A84 3C01FF00 */  lui        $at, (0xFF00FFFF >> 16)
    /* 7A88 80006A88 3421FFFF */  ori        $at, $at, (0xFF00FFFF & 0xFFFF)
    /* 7A8C 80006A8C 0018CC00 */  sll        $t9, $t8, 16
    /* 7A90 80006A90 01014824 */  and        $t1, $t0, $at
    /* 7A94 80006A94 03295025 */  or         $t2, $t9, $t1
endlabel func_80006A50
