
nonmatching func_80008D0C, 0x40

glabel func_80008D0C
    /* 9D0C 80008D0C 354B0020 */  ori        $t3, $t2, 0x20
    /* 9D10 80008D10 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 9D14 80008D14 A3A9001D */  sb         $t1, 0x1D($sp)
    /* 9D18 80008D18 A3AB001E */  sb         $t3, 0x1E($sp)
    /* 9D1C 80008D1C 3C040400 */  lui        $a0, (0x4001000 >> 16)
    /* 9D20 80008D20 34841000 */  ori        $a0, $a0, (0x4001000 & 0xFFFF)
    /* 9D24 80008D24 0C001A94 */  jal        func_80006A50
    /* 9D28 80008D28 8FA5001C */   lw        $a1, 0x1C($sp)
    /* 9D2C 80008D2C 3C040408 */  lui        $a0, (0x4080000 >> 16)
    /* 9D30 80008D30 0C001A94 */  jal        func_80006A50
    /* 9D34 80008D34 00002825 */   or        $a1, $zero, $zero
    /* 9D38 80008D38 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 9D3C 80008D3C 27BD0020 */  addiu      $sp, $sp, 0x20
    /* 9D40 80008D40 03E00008 */  jr         $ra
    /* 9D44 80008D44 00000000 */   nop
/* glabel func_80008D48 */
    /* 9D48 80008D48 27BDFFE8 */  addiu      $sp, $sp, -0x18
endlabel func_80008D0C
