
nonmatching func_8000698C, 0x24C

glabel func_8000698C
    /* 798C 8000698C 27BDFFB8 */  addiu      $sp, $sp, -0x48
    /* 7990 80006990 AFA40048 */  sw         $a0, 0x48($sp)
    /* 7994 80006994 8FAE0048 */  lw         $t6, 0x48($sp)
    /* 7998 80006998 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 799C 8000699C AFB10018 */  sw         $s1, 0x18($sp)
    /* 79A0 800069A0 AFB00014 */  sw         $s0, 0x14($sp)
    /* 79A4 800069A4 91CF0009 */  lbu        $t7, 0x9($t6)
    /* 79A8 800069A8 01C08025 */  or         $s0, $t6, $zero
    /* 79AC 800069AC 15E00008 */  bnez       $t7, .L800069D0
    /* 79B0 800069B0 00000000 */   nop
    /* 79B4 800069B4 0C0012CC */  jal        func_80004B30
    /* 79B8 800069B8 8E040010 */   lw        $a0, 0x10($s0)
    /* 79BC 800069BC 2401FFFF */  addiu      $at, $zero, -0x1
    /* 79C0 800069C0 14410003 */  bne        $v0, $at, .L800069D0
    /* 79C4 800069C4 00000000 */   nop
    /* 79C8 800069C8 1000007E */  b          .L80006BC4
    /* 79CC 800069CC 2402FFFB */   addiu     $v0, $zero, -0x5
  .L800069D0:
    /* 79D0 800069D0 8E180014 */  lw         $t8, 0x14($s0)
    /* 79D4 800069D4 2F010401 */  sltiu      $at, $t8, 0x401
    /* 79D8 800069D8 14200003 */  bnez       $at, .L800069E8
    /* 79DC 800069DC 00000000 */   nop
    /* 79E0 800069E0 10000078 */  b          .L80006BC4
    /* 79E4 800069E4 2402FFF8 */   addiu     $v0, $zero, -0x8
  .L800069E8:
    /* 79E8 800069E8 8E190010 */  lw         $t9, 0x10($s0)
    /* 79EC 800069EC 3C010400 */  lui        $at, (0x4000000 >> 16)
    /* 79F0 800069F0 0321082B */  sltu       $at, $t9, $at
    /* 79F4 800069F4 14200008 */  bnez       $at, .L80006A18
    /* 79F8 800069F8 00000000 */   nop
    /* 79FC 800069FC 8E080010 */  lw         $t0, 0x10($s0)
    /* 7A00 80006A00 8E090014 */  lw         $t1, 0x14($s0)
    /* 7A04 80006A04 3C010500 */  lui        $at, (0x5000000 >> 16)
    /* 7A08 80006A08 01095021 */  addu       $t2, $t0, $t1
    /* 7A0C 80006A0C 0141082B */  sltu       $at, $t2, $at
    /* 7A10 80006A10 14200003 */  bnez       $at, .L80006A20
    /* 7A14 80006A14 00000000 */   nop
  .L80006A18:
    /* 7A18 80006A18 10000002 */  b          .L80006A24
    /* 7A1C 80006A1C 00008825 */   or        $s1, $zero, $zero
  .L80006A20:
    /* 7A20 80006A20 24110001 */  addiu      $s1, $zero, 0x1
  .L80006A24:
    /* 7A24 80006A24 12200059 */  beqz       $s1, .L80006B8C
    /* 7A28 80006A28 00000000 */   nop
    /* 7A2C 80006A2C 8E0B0010 */  lw         $t3, 0x10($s0)
    /* 7A30 80006A30 316C0003 */  andi       $t4, $t3, 0x3
    /* 7A34 80006A34 11800035 */  beqz       $t4, .L80006B0C
    /* 7A38 80006A38 AFAC0030 */   sw        $t4, 0x30($sp)
    /* 7A3C 80006A3C 8E0D0014 */  lw         $t5, 0x14($s0)
    /* 7A40 80006A40 24010001 */  addiu      $at, $zero, 0x1
    /* 7A44 80006A44 11A10003 */  beq        $t5, $at, .L80006A54
    /* 7A48 80006A48 00000000 */   nop
    /* 7A4C 80006A4C 1000005D */  b          .L80006BC4
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
    /* 7AEC 80006AEC 8E040010 */  lw         $a0, 0x10($s0)
    /* 7AF0 80006AF0 2401FFFC */  addiu      $at, $zero, -0x4
    /* 7AF4 80006AF4 8FA5002C */  lw         $a1, 0x2C($sp)
    /* 7AF8 80006AF8 00815824 */  and        $t3, $a0, $at
    /* 7AFC 80006AFC 0C001A94 */  jal        func_80006A50
    /* 7B00 80006B00 01602025 */   or        $a0, $t3, $zero
    /* 7B04 80006B04 10000025 */  b          .L80006B9C
    /* 7B08 80006B08 00000000 */   nop
  .L80006B0C:
    /* 7B0C 80006B0C 8E0C0014 */  lw         $t4, 0x14($s0)
    /* 7B10 80006B10 260D0018 */  addiu      $t5, $s0, 0x18
    /* 7B14 80006B14 AFAD0024 */  sw         $t5, 0x24($sp)
    /* 7B18 80006B18 000C7082 */  srl        $t6, $t4, 2
    /* 7B1C 80006B1C AFAE0028 */  sw         $t6, 0x28($sp)
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
endlabel func_8000698C
