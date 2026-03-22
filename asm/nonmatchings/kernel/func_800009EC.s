
nonmatching func_800009EC, 0x9C

glabel func_800009EC
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
endlabel func_800009EC
