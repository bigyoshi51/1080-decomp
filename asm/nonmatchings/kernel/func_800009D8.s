
nonmatching func_800009D8, 0x15C

glabel func_800009D8
    /* 19D8 800009D8 8FB10018 */  lw         $s1, 0x18($sp)
    /* 19DC 800009DC 8FB2001C */  lw         $s2, 0x1C($sp)
    /* 19E0 800009E0 8FB30020 */  lw         $s3, 0x20($sp)
    /* 19E4 800009E4 03E00008 */  jr         $ra
    /* 19E8 800009E8 27BD0028 */   addiu     $sp, $sp, 0x28
/* glabel func_800009EC */
    /* 19EC 800009EC 27BDFF80 */  addiu      $sp, $sp, -0x80
    /* 19F0 800009F0 3C198001 */  lui        $t9, %hi(D_80012C44)
    /* 19F4 800009F4 8F392C44 */  lw         $t9, %lo(D_80012C44)($t9)
    /* 19F8 800009F8 AFB00018 */  sw         $s0, 0x18($sp)
    /* 19FC 800009FC 2402FFFF */  addiu      $v0, $zero, -0x1
    /* 1A00 80000A00 3C018001 */  lui        $at, %hi(D_80012C64)
    /* 1A04 80000A04 00808025 */  or         $s0, $a0, $zero
    /* 1A08 80000A08 AC222C64 */  sw         $v0, %lo(D_80012C64)($at)
    /* 1A0C 80000A0C AFBF0024 */  sw         $ra, 0x24($sp)
    /* 1A10 80000A10 AFB20020 */  sw         $s2, 0x20($sp)
    /* 1A14 80000A14 3C018001 */  lui        $at, %hi(D_80012C68)
    /* 1A18 80000A18 3C048001 */  lui        $a0, %hi(D_8000A314)
    /* 1A1C 80000A1C AFB1001C */  sw         $s1, 0x1C($sp)
    /* 1A20 80000A20 AC222C68 */  sw         $v0, %lo(D_80012C68)($at)
    /* 1A24 80000A24 00009025 */  or         $s2, $zero, $zero
    /* 1A28 80000A28 2484A314 */  addiu      $a0, $a0, %lo(D_8000A314)
    /* 1A2C 80000A2C 0320F809 */  jalr       $t9
    /* 1A30 80000A30 02002825 */   or        $a1, $s0, $zero
    /* 1A34 80000A34 3C028001 */  lui        $v0, %hi(D_80012BC0)
    /* 1A38 80000A38 3C118001 */  lui        $s1, %hi(D_80012FC0)
    /* 1A3C 80000A3C 26312FC0 */  addiu      $s1, $s1, %lo(D_80012FC0)
    /* 1A40 80000A40 24422BC0 */  addiu      $v0, $v0, %lo(D_80012BC0)
    /* 1A44 80000A44 3C068001 */  lui        $a2, %hi(D_80012F80)
    /* 1A48 80000A48 AC400018 */  sw         $zero, 0x18($v0)
    /* 1A4C 80000A4C A440002C */  sh         $zero, 0x2C($v0)
    /* 1A50 80000A50 24C62F80 */  addiu      $a2, $a2, %lo(D_80012F80)
    /* 1A54 80000A54 02202825 */  or         $a1, $s1, $zero
    /* 1A58 80000A58 0C000198 */  jal        func_80000660
    /* 1A5C 80000A5C 02002025 */   or        $a0, $s0, $zero
    /* 1A60 80000A60 3C068001 */  lui        $a2, %hi(D_8000A328)
    /* 1A64 80000A64 24C6A328 */  addiu      $a2, $a2, %lo(D_8000A328)
    /* 1A68 80000A68 27A40050 */  addiu      $a0, $sp, 0x50
    /* 1A6C 80000A6C 0C00022E */  jal        func_800008B8
    /* 1A70 80000A70 02202825 */   or        $a1, $s1, $zero
    /* 1A74 80000A74 14400003 */  bnez       $v0, .L80000A84
    /* 1A78 80000A78 AFA2004C */   sw        $v0, 0x4C($sp)
    /* 1A7C 80000A7C 1000007C */  b          .L80000C70
    /* 1A80 80000A80 2402FFEF */   addiu     $v0, $zero, -0x11
  .L80000A84:
    /* 1A84 80000A84 8C4E0000 */  lw         $t6, 0x0($v0)
/* glabel func_80000A88 */
    /* 1A88 80000A88 3C018001 */  lui        $at, %hi(D_8000A2D8)
    /* 1A8C 80000A8C 3C118001 */  lui        $s1, (0x80010000 >> 16)
    /* 1A90 80000A90 AC2EA2D8 */  sw         $t6, %lo(D_8000A2D8)($at)
    /* 1A94 80000A94 8C4F0004 */  lw         $t7, 0x4($v0)
/* glabel func_80000A98 */
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
endlabel func_800009D8
