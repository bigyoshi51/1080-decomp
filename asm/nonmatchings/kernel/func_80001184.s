
nonmatching func_80001184, 0x4C

glabel func_80001184
    /* 2184 80001184 3C018001 */  lui        $at, %hi(D_80012D5C)
    /* 2188 80001188 AC202D5C */  sw         $zero, %lo(D_80012D5C)($at)
    /* 218C 8000118C 3C018001 */  lui        $at, %hi(D_80012D30)
    /* 2190 80001190 AC202D30 */  sw         $zero, %lo(D_80012D30)($at)
    /* 2194 80001194 AC202D34 */  sw         $zero, %lo(D_80012D34)($at)
    /* 2198 80001198 3C018001 */  lui        $at, %hi(D_80012D38)
    /* 219C 8000119C 3C038001 */  lui        $v1, %hi(D_80012D3C)
    /* 21A0 800011A0 3C028001 */  lui        $v0, %hi(D_80012D5C)
    /* 21A4 800011A4 24422D5C */  addiu      $v0, $v0, %lo(D_80012D5C)
    /* 21A8 800011A8 24632D3C */  addiu      $v1, $v1, %lo(D_80012D3C)
    /* 21AC 800011AC AC202D38 */  sw         $zero, %lo(D_80012D38)($at)
  .L800011B0:
    /* 21B0 800011B0 24630010 */  addiu      $v1, $v1, 0x10
    /* 21B4 800011B4 AC60FFF0 */  sw         $zero, -0x10($v1)
    /* 21B8 800011B8 AC60FFF4 */  sw         $zero, -0xC($v1)
    /* 21BC 800011BC AC60FFF8 */  sw         $zero, -0x8($v1)
    /* 21C0 800011C0 1462FFFB */  bne        $v1, $v0, .L800011B0
    /* 21C4 800011C4 AC60FFFC */   sw        $zero, -0x4($v1)
    /* 21C8 800011C8 03E00008 */  jr         $ra
    /* 21CC 800011CC 00000000 */   nop
endlabel func_80001184
