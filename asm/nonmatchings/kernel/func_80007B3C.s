
nonmatching func_80007B3C, 0x294

glabel func_80007B3C
    /* 8B3C 80007B3C 27BDFF68 */  addiu      $sp, $sp, -0x98
    /* 8B40 80007B40 AFA40098 */  sw         $a0, 0x98($sp)
    /* 8B44 80007B44 8FAE0098 */  lw         $t6, 0x98($sp)
    /* 8B48 80007B48 AFBF0024 */  sw         $ra, 0x24($sp)
    /* 8B4C 80007B4C AFB20020 */  sw         $s2, 0x20($sp)
    /* 8B50 80007B50 AFB1001C */  sw         $s1, 0x1C($sp)
    /* 8B54 80007B54 AFB00018 */  sw         $s0, 0x18($sp)
    /* 8B58 80007B58 AFAE0094 */  sw         $t6, 0x94($sp)
    /* 8B5C 80007B5C 91D20009 */  lbu        $s2, 0x9($t6)
    /* 8B60 80007B60 00008825 */  or         $s1, $zero, $zero
    /* 8B64 80007B64 12400005 */  beqz       $s2, .L80007B7C
    /* 8B68 80007B68 24010001 */   addiu     $at, $zero, 0x1
    /* 8B6C 80007B6C 12410039 */  beq        $s2, $at, .L80007C54
    /* 8B70 80007B70 00000000 */   nop
    /* 8B74 80007B74 1000007F */  b          .L80007D74
    /* 8B78 80007B78 00000000 */   nop
  .L80007B7C:
    /* 8B7C 80007B7C 0C00270C */  jal        func_80009C30
    /* 8B80 80007B80 00000000 */   nop
    /* 8B84 80007B84 00408025 */  or         $s0, $v0, $zero
    /* 8B88 80007B88 8E0F0004 */  lw         $t7, 0x4($s0)
    /* 8B8C 80007B8C 2401FFFF */  addiu      $at, $zero, -0x1
    /* 8B90 80007B90 11E1000B */  beq        $t7, $at, .L80007BC0
    /* 8B94 80007B94 00000000 */   nop
  .L80007B98:
    /* 8B98 80007B98 8FB90094 */  lw         $t9, 0x94($sp)
    /* 8B9C 80007B9C 8E180014 */  lw         $t8, 0x14($s0)
    /* 8BA0 80007BA0 8F28000C */  lw         $t0, 0xC($t9)
    /* 8BA4 80007BA4 13080006 */  beq        $t8, $t0, .L80007BC0
    /* 8BA8 80007BA8 00000000 */   nop
    /* 8BAC 80007BAC 8E10000C */  lw         $s0, 0xC($s0)
    /* 8BB0 80007BB0 2401FFFF */  addiu      $at, $zero, -0x1
    /* 8BB4 80007BB4 8E090004 */  lw         $t1, 0x4($s0)
    /* 8BB8 80007BB8 1521FFF7 */  bne        $t1, $at, .L80007B98
    /* 8BBC 80007BBC 00000000 */   nop
  .L80007BC0:
    /* 8BC0 80007BC0 8E0A0004 */  lw         $t2, 0x4($s0)
    /* 8BC4 80007BC4 2401FFFF */  addiu      $at, $zero, -0x1
    /* 8BC8 80007BC8 15410003 */  bne        $t2, $at, .L80007BD8
    /* 8BCC 80007BCC 00000000 */   nop
    /* 8BD0 80007BD0 10000079 */  b          .L80007DB8
    /* 8BD4 80007BD4 2402FFFE */   addiu     $v0, $zero, -0x2
  .L80007BD8:
    /* 8BD8 80007BD8 960B0010 */  lhu        $t3, 0x10($s0)
    /* 8BDC 80007BDC 24010001 */  addiu      $at, $zero, 0x1
    /* 8BE0 80007BE0 11610003 */  beq        $t3, $at, .L80007BF0
    /* 8BE4 80007BE4 00000000 */   nop
    /* 8BE8 80007BE8 10000073 */  b          .L80007DB8
    /* 8BEC 80007BEC 2402FFFC */   addiu     $v0, $zero, -0x4
  .L80007BF0:
    /* 8BF0 80007BF0 960C0012 */  lhu        $t4, 0x12($s0)
    /* 8BF4 80007BF4 2401FFFC */  addiu      $at, $zero, -0x4
    /* 8BF8 80007BF8 01816824 */  and        $t5, $t4, $at
    /* 8BFC 80007BFC A60D0012 */  sh         $t5, 0x12($s0)
    /* 8C00 80007C00 8FAE0094 */  lw         $t6, 0x94($sp)
    /* 8C04 80007C04 8DCF0010 */  lw         $t7, 0x10($t6)
    /* 8C08 80007C08 31F90002 */  andi       $t9, $t7, 0x2
    /* 8C0C 80007C0C 13200003 */  beqz       $t9, .L80007C1C
    /* 8C10 80007C10 00000000 */   nop
    /* 8C14 80007C14 8DD80014 */  lw         $t8, 0x14($t6)
    /* 8C18 80007C18 AE18011C */  sw         $t8, 0x11C($s0)
  .L80007C1C:
    /* 8C1C 80007C1C 8FA80094 */  lw         $t0, 0x94($sp)
    /* 8C20 80007C20 8D090010 */  lw         $t1, 0x10($t0)
    /* 8C24 80007C24 312A0001 */  andi       $t2, $t1, 0x1
    /* 8C28 80007C28 11400008 */  beqz       $t2, .L80007C4C
    /* 8C2C 80007C2C 00000000 */   nop
    /* 8C30 80007C30 8D04000C */  lw         $a0, 0xC($t0)
    /* 8C34 80007C34 0C002312 */  jal        func_80008C48
    /* 8C38 80007C38 8E05011C */   lw        $a1, 0x11C($s0)
    /* 8C3C 80007C3C 14400003 */  bnez       $v0, .L80007C4C
    /* 8C40 80007C40 00000000 */   nop
    /* 8C44 80007C44 1000005C */  b          .L80007DB8
    /* 8C48 80007C48 2402FFFC */   addiu     $v0, $zero, -0x4
  .L80007C4C:
    /* 8C4C 80007C4C 1000004B */  b          .L80007D7C
    /* 8C50 80007C50 24110001 */   addiu     $s1, $zero, 0x1
  .L80007C54:
    /* 8C54 80007C54 0C00210C */  jal        func_80008430
    /* 8C58 80007C58 00000000 */   nop
    /* 8C5C 80007C5C 10400003 */  beqz       $v0, .L80007C6C
    /* 8C60 80007C60 00000000 */   nop
    /* 8C64 80007C64 10000054 */  b          .L80007DB8
    /* 8C68 80007C68 2402FFFC */   addiu     $v0, $zero, -0x4
  .L80007C6C:
    /* 8C6C 80007C6C 8FAB0094 */  lw         $t3, 0x94($sp)
    /* 8C70 80007C70 8D6C0010 */  lw         $t4, 0x10($t3)
    /* 8C74 80007C74 318D0002 */  andi       $t5, $t4, 0x2
    /* 8C78 80007C78 11A00007 */  beqz       $t5, .L80007C98
    /* 8C7C 80007C7C 00000000 */   nop
    /* 8C80 80007C80 8D650014 */  lw         $a1, 0x14($t3)
    /* 8C84 80007C84 3C01FBFF */  lui        $at, (0xFBFFF000 >> 16)
    /* 8C88 80007C88 3421F000 */  ori        $at, $at, (0xFBFFF000 & 0xFFFF)
    /* 8C8C 80007C8C 3C040408 */  lui        $a0, (0x4080000 >> 16)
    /* 8C90 80007C90 0C001A94 */  jal        func_80006A50
    /* 8C94 80007C94 00A12821 */   addu      $a1, $a1, $at
  .L80007C98:
    /* 8C98 80007C98 8FAF0094 */  lw         $t7, 0x94($sp)
    /* 8C9C 80007C9C 8DF90010 */  lw         $t9, 0x10($t7)
    /* 8CA0 80007CA0 332E0001 */  andi       $t6, $t9, 0x1
    /* 8CA4 80007CA4 11C00015 */  beqz       $t6, .L80007CFC
    /* 8CA8 80007CA8 00000000 */   nop
    /* 8CAC 80007CAC 0C001AA6 */  jal        func_80006A98
    /* 8CB0 80007CB0 3C040408 */   lui       $a0, (0x4080000 >> 16)
    /* 8CB4 80007CB4 3C010400 */  lui        $at, (0x4001000 >> 16)
    /* 8CB8 80007CB8 34211000 */  ori        $at, $at, (0x4001000 & 0xFFFF)
    /* 8CBC 80007CBC 00409025 */  or         $s2, $v0, $zero
    /* 8CC0 80007CC0 02413021 */  addu       $a2, $s2, $at
    /* 8CC4 80007CC4 24040001 */  addiu      $a0, $zero, 0x1
    /* 8CC8 80007CC8 0C002263 */  jal        func_8000898C
    /* 8CCC 80007CCC 240503E8 */   addiu     $a1, $zero, 0x3E8
    /* 8CD0 80007CD0 30580003 */  andi       $t8, $v0, 0x3
    /* 8CD4 80007CD4 17000003 */  bnez       $t8, .L80007CE4
    /* 8CD8 80007CD8 00000000 */   nop
    /* 8CDC 80007CDC 0C002126 */  jal        func_80008498
    /* 8CE0 80007CE0 00000000 */   nop
  .L80007CE4:
    /* 8CE4 80007CE4 0C002126 */  jal        func_80008498
    /* 8CE8 80007CE8 00000000 */   nop
    /* 8CEC 80007CEC 24090001 */  addiu      $t1, $zero, 0x1
    /* 8CF0 80007CF0 3C018002 */  lui        $at, %hi(__rmonRcpAtBreak)
    /* 8CF4 80007CF4 10000004 */  b          .L80007D08
    /* 8CF8 80007CF8 A029FF78 */   sb        $t1, %lo(__rmonRcpAtBreak)($at)
  .L80007CFC:
    /* 8CFC 80007CFC 3C018002 */  lui        $at, %hi(__rmonRcpAtBreak)
    /* 8D00 80007D00 0C00212B */  jal        func_800084AC
    /* 8D04 80007D04 A020FF78 */   sb        $zero, %lo(__rmonRcpAtBreak)($at)
  .L80007D08:
    /* 8D08 80007D08 8FAA0094 */  lw         $t2, 0x94($sp)
    /* 8D0C 80007D0C 27A40084 */  addiu      $a0, $sp, 0x84
    /* 8D10 80007D10 24050010 */  addiu      $a1, $zero, 0x10
    /* 8D14 80007D14 91480004 */  lbu        $t0, 0x4($t2)
    /* 8D18 80007D18 A7A0008A */  sh         $zero, 0x8A($sp)
    /* 8D1C 80007D1C 24060001 */  addiu      $a2, $zero, 0x1
    /* 8D20 80007D20 A3A80088 */  sb         $t0, 0x88($sp)
    /* 8D24 80007D24 8D4C000C */  lw         $t4, 0xC($t2)
    /* 8D28 80007D28 0C001CFE */  jal        func_800073F8
    /* 8D2C 80007D2C AFAC0090 */   sw        $t4, 0x90($sp)
    /* 8D30 80007D30 8FAD0094 */  lw         $t5, 0x94($sp)
    /* 8D34 80007D34 8DAB0010 */  lw         $t3, 0x10($t5)
    /* 8D38 80007D38 316F0001 */  andi       $t7, $t3, 0x1
    /* 8D3C 80007D3C 11E0000B */  beqz       $t7, .L80007D6C
    /* 8D40 80007D40 00000000 */   nop
    /* 8D44 80007D44 24040001 */  addiu      $a0, $zero, 0x1
    /* 8D48 80007D48 240503E8 */  addiu      $a1, $zero, 0x3E8
    /* 8D4C 80007D4C 0C001EA6 */  jal        func_80007A98
    /* 8D50 80007D50 27A60038 */   addiu     $a2, $sp, 0x38
    /* 8D54 80007D54 0C002343 */  jal        func_80008D0C
    /* 8D58 80007D58 27A40038 */   addiu     $a0, $sp, 0x38
    /* 8D5C 80007D5C 27A40038 */  addiu      $a0, $sp, 0x38
    /* 8D60 80007D60 2405004C */  addiu      $a1, $zero, 0x4C
    /* 8D64 80007D64 0C001CFE */  jal        func_800073F8
    /* 8D68 80007D68 24060002 */   addiu     $a2, $zero, 0x2
  .L80007D6C:
    /* 8D6C 80007D6C 10000012 */  b          .L80007DB8
    /* 8D70 80007D70 00001025 */   or        $v0, $zero, $zero
  .L80007D74:
    /* 8D74 80007D74 10000010 */  b          .L80007DB8
    /* 8D78 80007D78 2402FFFC */   addiu     $v0, $zero, -0x4
  .L80007D7C:
    /* 8D7C 80007D7C 8FB90094 */  lw         $t9, 0x94($sp)
    /* 8D80 80007D80 27A40084 */  addiu      $a0, $sp, 0x84
    /* 8D84 80007D84 24050010 */  addiu      $a1, $zero, 0x10
    /* 8D88 80007D88 932E0004 */  lbu        $t6, 0x4($t9)
    /* 8D8C 80007D8C A7A0008A */  sh         $zero, 0x8A($sp)
    /* 8D90 80007D90 24060001 */  addiu      $a2, $zero, 0x1
    /* 8D94 80007D94 A3AE0088 */  sb         $t6, 0x88($sp)
    /* 8D98 80007D98 8F38000C */  lw         $t8, 0xC($t9)
    /* 8D9C 80007D9C 0C001CFE */  jal        func_800073F8
    /* 8DA0 80007DA0 AFB80090 */   sw        $t8, 0x90($sp)
    /* 8DA4 80007DA4 12200003 */  beqz       $s1, .L80007DB4
    /* 8DA8 80007DA8 00000000 */   nop
    /* 8DAC 80007DAC 0C002844 */  jal        func_8000A110
    /* 8DB0 80007DB0 02002025 */   or        $a0, $s0, $zero
  .L80007DB4:
    /* 8DB4 80007DB4 24020001 */  addiu      $v0, $zero, 0x1
  .L80007DB8:
    /* 8DB8 80007DB8 8FBF0024 */  lw         $ra, 0x24($sp)
    /* 8DBC 80007DBC 8FB00018 */  lw         $s0, 0x18($sp)
    /* 8DC0 80007DC0 8FB1001C */  lw         $s1, 0x1C($sp)
    /* 8DC4 80007DC4 8FB20020 */  lw         $s2, 0x20($sp)
    /* 8DC8 80007DC8 03E00008 */  jr         $ra
    /* 8DCC 80007DCC 27BD0098 */   addiu     $sp, $sp, 0x98
endlabel func_80007B3C
