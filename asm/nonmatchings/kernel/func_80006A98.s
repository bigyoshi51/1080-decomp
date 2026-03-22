
nonmatching func_80006A98, 0x54

glabel func_80006A98
    /* 7A98 80006A98 10000014 */  b          func_80006AEC
    /* 7A9C 80006A9C AFAA002C */   sw        $t2, 0x2C($sp)
  .L80006AA0:
    /* 7AA0 80006AA0 8FAB0030 */  lw         $t3, 0x30($sp)
    /* 7AA4 80006AA4 24010002 */  addiu      $at, $zero, 0x2
    /* 7AA8 80006AA8 1561000A */  bne        $t3, $at, .L80006AD4
    /* 7AAC 80006AAC 00000000 */   nop
    /* 7AB0 80006AB0 920C0018 */  lbu        $t4, 0x18($s0)
    /* 7AB4 80006AB4 8FAE002C */  lw         $t6, 0x2C($sp)
    /* 7AB8 80006AB8 3C01FFFF */  lui        $at, (0xFFFF00FF >> 16)
    /* 7ABC 80006ABC 342100FF */  ori        $at, $at, (0xFFFF00FF & 0xFFFF)
    /* 7AC0 80006AC0 000C6A00 */  sll        $t5, $t4, 8
    /* 7AC4 80006AC4 01C17824 */  and        $t7, $t6, $at
    /* 7AC8 80006AC8 01AFC025 */  or         $t8, $t5, $t7
    /* 7ACC 80006ACC 10000007 */  b          func_80006AEC
    /* 7AD0 80006AD0 AFB8002C */   sw        $t8, 0x2C($sp)
  .L80006AD4:
    /* 7AD4 80006AD4 8FB9002C */  lw         $t9, 0x2C($sp)
    /* 7AD8 80006AD8 92080018 */  lbu        $t0, 0x18($s0)
    /* 7ADC 80006ADC 2401FF00 */  addiu      $at, $zero, -0x100
    /* 7AE0 80006AE0 03214824 */  and        $t1, $t9, $at
    /* 7AE4 80006AE4 01095025 */  or         $t2, $t0, $t1
    /* 7AE8 80006AE8 AFAA002C */  sw         $t2, 0x2C($sp)
endlabel func_80006A98
