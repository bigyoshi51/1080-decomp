
nonmatching func_800010CC, 0x1C

glabel func_800010CC
    /* 20CC 800010CC 27BDFFF8 */  addiu      $sp, $sp, -0x8
    /* 20D0 800010D0 AFA40008 */  sw         $a0, 0x8($sp)
    /* 20D4 800010D4 AFA5000C */  sw         $a1, 0xC($sp)
    /* 20D8 800010D8 AFA60010 */  sw         $a2, 0x10($sp)
    /* 20DC 800010DC AFA70014 */  sw         $a3, 0x14($sp)
    /* 20E0 800010E0 03E00008 */  jr         $ra
    /* 20E4 800010E4 27BD0008 */   addiu     $sp, $sp, 0x8
endlabel func_800010CC
