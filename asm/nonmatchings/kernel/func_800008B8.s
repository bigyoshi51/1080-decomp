
nonmatching func_800008B8, 0x38

glabel func_800008B8
    /* 18B8 800008B8 02403825 */  or         $a3, $s2, $zero
    /* 18BC 800008BC 26100001 */  addiu      $s0, $s0, 0x1
    /* 18C0 800008C0 2631009C */  addiu      $s1, $s1, 0x9C
    /* 18C4 800008C4 1615FFF7 */  bne        $s0, $s5, .L800008A4
    /* 18C8 800008C8 2652009C */   addiu     $s2, $s2, 0x9C
    /* 18CC 800008CC 8FBF002C */  lw         $ra, 0x2C($sp)
    /* 18D0 800008D0 8FB00014 */  lw         $s0, 0x14($sp)
    /* 18D4 800008D4 8FB10018 */  lw         $s1, 0x18($sp)
    /* 18D8 800008D8 8FB2001C */  lw         $s2, 0x1C($sp)
    /* 18DC 800008DC 8FB30020 */  lw         $s3, 0x20($sp)
    /* 18E0 800008E0 8FB40024 */  lw         $s4, 0x24($sp)
    /* 18E4 800008E4 8FB50028 */  lw         $s5, 0x28($sp)
    /* 18E8 800008E8 03E00008 */  jr         $ra
    /* 18EC 800008EC 27BD0030 */   addiu     $sp, $sp, 0x30
endlabel func_800008B8
