nonmatching func_0000F1B4, 0x30

glabel func_0000F1B4
    /* DDFC20 0000F1B4 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* DDFC24 0000F1B8 AFBF0014 */  sw         $ra, 0x14($sp)
    /* DDFC28 0000F1BC AFA40020 */  sw         $a0, 0x20($sp)
    /* DDFC2C 0000F1C0 0C003C48 */  jal        func_0000F120
    /* DDFC30 0000F1C4 27A4001C */   addiu     $a0, $sp, 0x1C
    /* DDFC34 0000F1C8 8FA40020 */  lw         $a0, 0x20($sp)
    /* DDFC38 0000F1CC 0C003C57 */  jal        func_0000F15C
    /* DDFC3C 0000F1D0 24840010 */   addiu     $a0, $a0, 0x10
    /* DDFC40 0000F1D4 8FBF0014 */  lw         $ra, 0x14($sp)
    /* DDFC44 0000F1D8 27BD0020 */  addiu      $sp, $sp, 0x20
    /* DDFC48 0000F1DC 03E00008 */  jr         $ra
    /* DDFC4C 0000F1E0 00000000 */   nop
endlabel func_0000F1B4
    /* DDFC50 0000F1E4 00000000 */  nop
    /* DDFC54 0000F1E8 00000000 */  nop
    /* DDFC58 0000F1EC 00000000 */  nop
