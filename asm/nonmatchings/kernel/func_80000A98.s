
nonmatching func_80000A98, 0x9C

glabel func_80000A98
    /* 1A98 80000A98 3C018001 */  lui        $at, %hi(D_8000A2DC)
    /* 1A9C 80000A9C 3C108001 */  lui        $s0, %hi(D_80013112)
    /* 1AA0 80000AA0 AFA00048 */  sw         $zero, 0x48($sp)
    /* 1AA4 80000AA4 26103112 */  addiu      $s0, $s0, %lo(D_80013112)
    /* 1AA8 80000AA8 263130A0 */  addiu      $s1, $s1, 0x30A0
    /* 1AAC 80000AAC 00001825 */  or         $v1, $zero, $zero
    /* 1AB0 80000AB0 AC2FA2DC */  sw         $t7, %lo(D_8000A2DC)($at)
  .L80000AB4:
    /* 1AB4 80000AB4 3C058001 */  lui        $a1, %hi(D_80012F80)
    /* 1AB8 80000AB8 24A52F80 */  addiu      $a1, $a1, %lo(D_80012F80)
    /* 1ABC 80000ABC 02002025 */  or         $a0, $s0, $zero
    /* 1AC0 80000AC0 0C00015A */  jal        func_80000568
    /* 1AC4 80000AC4 AFA30044 */   sw        $v1, 0x44($sp)
    /* 1AC8 80000AC8 1440001A */  bnez       $v0, func_80000B34
    /* 1ACC 80000ACC 8FA30044 */   lw        $v1, 0x44($sp)
    /* 1AD0 80000AD0 AFB10048 */  sw         $s1, 0x48($sp)
    /* 1AD4 80000AD4 02202025 */  or         $a0, $s1, $zero
    /* 1AD8 80000AD8 0C00072C */  jal        func_80001CB0
    /* 1ADC 80000ADC AFA30044 */   sw        $v1, 0x44($sp)
    /* 1AE0 80000AE0 8FA30044 */  lw         $v1, 0x44($sp)
    /* 1AE4 80000AE4 3C088001 */  lui        $t0, %hi(D_80012D60)
    /* 1AE8 80000AE8 25082D60 */  addiu      $t0, $t0, %lo(D_80012D60)
    /* 1AEC 80000AEC 0003C080 */  sll        $t8, $v1, 2
    /* 1AF0 80000AF0 03081021 */  addu       $v0, $t8, $t0
    /* 1AF4 80000AF4 A6230070 */  sh         $v1, 0x70($s1)
    /* 1AF8 80000AF8 8C490000 */  lw         $t1, 0x0($v0)
    /* 1AFC 80000AFC 02202025 */  or         $a0, $s1, $zero
    /* 1B00 80000B00 51200004 */  beql       $t1, $zero, .L80000B14
    /* 1B04 80000B04 AC510000 */   sw        $s1, 0x0($v0)
    /* 1B08 80000B08 10000059 */  b          .L80000C70
    /* 1B0C 80000B0C 2402FFED */   addiu     $v0, $zero, -0x13
    /* 1B10 80000B10 AC510000 */  sw         $s1, 0x0($v0)
  .L80000B14:
    /* 1B14 80000B14 8E2A0094 */  lw         $t2, 0x94($s1)
    /* 1B18 80000B18 27A50050 */  addiu      $a1, $sp, 0x50
    /* 1B1C 80000B1C 0C0008B2 */  jal        func_800022C8
    /* 1B20 80000B20 AFAA0054 */   sw        $t2, 0x54($sp)
    /* 1B24 80000B24 10400008 */  beqz       $v0, .L80000B48
    /* 1B28 80000B28 00409025 */   or        $s2, $v0, $zero
    /* 1B2C 80000B2C 10000051 */  b          .L80000C74
    /* 1B30 80000B30 8FBF0024 */   lw        $ra, 0x24($sp)
endlabel func_80000A98
