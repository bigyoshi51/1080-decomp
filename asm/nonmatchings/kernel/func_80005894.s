
nonmatching func_80005894, 0x8C

glabel func_80005894
    /* 6894 80005894 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 6898 80005898 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 689C 8000589C 3C048002 */  lui        $a0, %hi(__osPiAccessQueue)
    /* 68A0 800058A0 2484B638 */  addiu      $a0, $a0, %lo(__osPiAccessQueue)
    /* 68A4 800058A4 00002825 */  or         $a1, $zero, $zero
    /* 68A8 800058A8 0C001770 */  jal        func_80005DC0
    /* 68AC 800058AC 00003025 */   or        $a2, $zero, $zero
    /* 68B0 800058B0 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 68B4 800058B4 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 68B8 800058B8 03E00008 */  jr         $ra
    /* 68BC 800058BC 00000000 */   nop
/* glabel func_800058C0 */
    /* 68C0 800058C0 3C0E8002 */  lui        $t6, %hi(D_8001B65C)
    /* 68C4 800058C4 8DCEB65C */  lw         $t6, %lo(D_8001B65C)($t6)
    /* 68C8 800058C8 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 68CC 800058CC 3C01B000 */  lui        $at, (0xB0000000 >> 16)
    /* 68D0 800058D0 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 68D4 800058D4 15C10004 */  bne        $t6, $at, .L800058E8
    /* 68D8 800058D8 AFA0001C */   sw        $zero, 0x1C($sp)
    /* 68DC 800058DC 3C028002 */  lui        $v0, %hi(CartRomHandle)
    /* 68E0 800058E0 10000030 */  b          .L800059A4
    /* 68E4 800058E4 2442B650 */   addiu     $v0, $v0, %lo(CartRomHandle)
  .L800058E8:
    /* 68E8 800058E8 3C018002 */  lui        $at, %hi(D_8001B654)
    /* 68EC 800058EC A020B654 */  sb         $zero, %lo(D_8001B654)($at)
    /* 68F0 800058F0 3C018002 */  lui        $at, %hi(D_8001B65C)
    /* 68F4 800058F4 3C0FB000 */  lui        $t7, (0xB0000000 >> 16)
    /* 68F8 800058F8 AC2FB65C */  sw         $t7, %lo(D_8001B65C)($at)
    /* 68FC 800058FC 00002025 */  or         $a0, $zero, $zero
    /* 6900 80005900 0C000B6C */  jal        func_80002DB0
    /* 6904 80005904 27A5001C */   addiu     $a1, $sp, 0x1C
    /* 6908 80005908 8FB8001C */  lw         $t8, 0x1C($sp)
    /* 690C 8000590C 3C018002 */  lui        $at, %hi(D_8001B655)
    /* 6910 80005910 3C048002 */  lui        $a0, (0x80020000 >> 16)
    /* 6914 80005914 331900FF */  andi       $t9, $t8, 0xFF
    /* 6918 80005918 A039B655 */  sb         $t9, %lo(D_8001B655)($at)
    /* 691C 8000591C 00184202 */  srl        $t0, $t8, 8
endlabel func_80005894
