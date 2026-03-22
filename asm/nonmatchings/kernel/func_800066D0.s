
nonmatching func_800066D0, 0x1C

glabel func_800066D0
    /* 76D0 800066D0 10000002 */  b          .L800066DC
    /* 76D4 800066D4 8FA2001C */   lw        $v0, 0x1C($sp)
  .L800066D8:
    /* 76D8 800066D8 00001025 */  or         $v0, $zero, $zero
  .L800066DC:
    /* 76DC 800066DC 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 76E0 800066E0 27BD0020 */  addiu      $sp, $sp, 0x20
    /* 76E4 800066E4 03E00008 */  jr         $ra
    /* 76E8 800066E8 00000000 */   nop
endlabel func_800066D0
