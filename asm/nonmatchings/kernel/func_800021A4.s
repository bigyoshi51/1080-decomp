
nonmatching func_800021A4, 0x2C

glabel func_800021A4
    /* 31A4 800021A4 8C82003C */  lw         $v0, 0x3C($a0)
    /* 31A8 800021A8 54400004 */  bnel       $v0, $zero, .L800021BC
    /* 31AC 800021AC 8C850004 */   lw        $a1, 0x4($a0)
    /* 31B0 800021B0 03E00008 */  jr         $ra
    /* 31B4 800021B4 00001025 */   or        $v0, $zero, $zero
    /* 31B8 800021B8 8C850004 */  lw         $a1, 0x4($a0)
  .L800021BC:
    /* 31BC 800021BC 00001825 */  or         $v1, $zero, $zero
    /* 31C0 800021C0 00403025 */  or         $a2, $v0, $zero
    /* 31C4 800021C4 18A0001F */  blez       $a1, .L80002244
    /* 31C8 800021C8 240A0003 */   addiu     $t2, $zero, 0x3
    /* 31CC 800021CC 24090004 */  addiu      $t1, $zero, 0x4
endlabel func_800021A4
