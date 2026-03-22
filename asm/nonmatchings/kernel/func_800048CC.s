
nonmatching func_800048CC, 0x1C

glabel func_800048CC
    /* 58CC 800048CC 30482000 */  andi       $t0, $v0, 0x2000
    /* 58D0 800048D0 1500FFFC */  bnez       $t0, .L800048C4
    /* 58D4 800048D4 00000000 */   nop
  .L800048D8:
    /* 58D8 800048D8 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 58DC 800048DC 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 58E0 800048E0 03E00008 */  jr         $ra
    /* 58E4 800048E4 00000000 */   nop
endlabel func_800048CC
