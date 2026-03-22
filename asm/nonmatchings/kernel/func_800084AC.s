
nonmatching func_800084AC, 0x24

glabel func_800084AC
    /* 94AC 800084AC 3C01FC00 */  lui        $at, (0xFC00003F >> 16)
    /* 94B0 800084B0 3421003F */  ori        $at, $at, (0xFC00003F & 0xFFFF)
    /* 94B4 800084B4 01616024 */  and        $t4, $t3, $at
    /* 94B8 800084B8 2401000D */  addiu      $at, $zero, 0xD
    /* 94BC 800084BC 15810021 */  bne        $t4, $at, .L80008544
    /* 94C0 800084C0 00000000 */   nop
    /* 94C4 800084C4 8E240000 */  lw         $a0, 0x0($s1)
    /* 94C8 800084C8 0C001A94 */  jal        func_80006A50
    /* 94CC 800084CC 8E250004 */   lw        $a1, 0x4($s1)
endlabel func_800084AC
