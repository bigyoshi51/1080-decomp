
nonmatching func_80001CF4, 0xDC

glabel func_80001CF4
    /* 2CF4 80001CF4 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 2CF8 80001CF8 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 2CFC 80001CFC AFB10018 */  sw         $s1, 0x18($sp)
    /* 2D00 80001D00 AFB00014 */  sw         $s0, 0x14($sp)
    /* 2D04 80001D04 8C850054 */  lw         $a1, 0x54($a0)
    /* 2D08 80001D08 00808025 */  or         $s0, $a0, $zero
    /* 2D0C 80001D0C 50A0000D */  beql       $a1, $zero, .L80001D44
    /* 2D10 80001D10 8E050050 */   lw        $a1, 0x50($s0)
    /* 2D14 80001D14 8E060048 */  lw         $a2, 0x48($s0)
    /* 2D18 80001D18 0C0007B7 */  jal        func_80001EDC
    /* 2D1C 80001D1C 8E070010 */   lw        $a3, 0x10($s0)
    /* 2D20 80001D20 00408825 */  or         $s1, $v0, $zero
    /* 2D24 80001D24 8E040054 */  lw         $a0, 0x54($s0)
    /* 2D28 80001D28 0C000146 */  jal        func_80000518
    /* 2D2C 80001D2C 8E05001C */   lw        $a1, 0x1C($s0)
    /* 2D30 80001D30 52200004 */  beql       $s1, $zero, .L80001D44
    /* 2D34 80001D34 8E050050 */   lw        $a1, 0x50($s0)
    /* 2D38 80001D38 10000020 */  b          .L80001DBC
    /* 2D3C 80001D3C 2402FFF2 */   addiu     $v0, $zero, -0xE
    /* 2D40 80001D40 8E050050 */  lw         $a1, 0x50($s0)
  .L80001D44:
    /* 2D44 80001D44 02002025 */  or         $a0, $s0, $zero
    /* 2D48 80001D48 50A0000D */  beql       $a1, $zero, .L80001D80
    /* 2D4C 80001D4C 8E05004C */   lw        $a1, 0x4C($s0)
    /* 2D50 80001D50 8E060044 */  lw         $a2, 0x44($s0)
    /* 2D54 80001D54 0C0007B7 */  jal        func_80001EDC
    /* 2D58 80001D58 8E07000C */   lw        $a3, 0xC($s0)
    /* 2D5C 80001D5C 00408825 */  or         $s1, $v0, $zero
    /* 2D60 80001D60 8E040050 */  lw         $a0, 0x50($s0)
    /* 2D64 80001D64 0C000146 */  jal        func_80000518
    /* 2D68 80001D68 8E050018 */   lw        $a1, 0x18($s0)
    /* 2D6C 80001D6C 52200004 */  beql       $s1, $zero, .L80001D80
    /* 2D70 80001D70 8E05004C */   lw        $a1, 0x4C($s0)
    /* 2D74 80001D74 10000011 */  b          .L80001DBC
    /* 2D78 80001D78 2402FFF1 */   addiu     $v0, $zero, -0xF
    /* 2D7C 80001D7C 8E05004C */  lw         $a1, 0x4C($s0)
  .L80001D80:
    /* 2D80 80001D80 02002025 */  or         $a0, $s0, $zero
    /* 2D84 80001D84 50A0000D */  beql       $a1, $zero, .L80001DBC
    /* 2D88 80001D88 00001025 */   or        $v0, $zero, $zero
    /* 2D8C 80001D8C 8E060040 */  lw         $a2, 0x40($s0)
    /* 2D90 80001D90 0C0007B7 */  jal        func_80001EDC
    /* 2D94 80001D94 8E070008 */   lw        $a3, 0x8($s0)
    /* 2D98 80001D98 00408825 */  or         $s1, $v0, $zero
    /* 2D9C 80001D9C 8E04004C */  lw         $a0, 0x4C($s0)
    /* 2DA0 80001DA0 0C000146 */  jal        func_80000518
    /* 2DA4 80001DA4 8E050014 */   lw        $a1, 0x14($s0)
    /* 2DA8 80001DA8 52200004 */  beql       $s1, $zero, .L80001DBC
    /* 2DAC 80001DAC 00001025 */   or        $v0, $zero, $zero
    /* 2DB0 80001DB0 10000002 */  b          .L80001DBC
    /* 2DB4 80001DB4 2402FFF0 */   addiu     $v0, $zero, -0x10
    /* 2DB8 80001DB8 00001025 */  or         $v0, $zero, $zero
  .L80001DBC:
    /* 2DBC 80001DBC 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 2DC0 80001DC0 8FB00014 */  lw         $s0, 0x14($sp)
    /* 2DC4 80001DC4 8FB10018 */  lw         $s1, 0x18($sp)
    /* 2DC8 80001DC8 03E00008 */  jr         $ra
    /* 2DCC 80001DCC 27BD0020 */   addiu     $sp, $sp, 0x20
endlabel func_80001CF4
