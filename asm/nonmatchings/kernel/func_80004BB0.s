
nonmatching func_80004BB0, 0x30

glabel func_80004BB0
    /* 5BB0 80004BB0 1160FFF6 */  beqz       $t3, .L80004B8C
    /* 5BB4 80004BB4 00000000 */   nop
  .L80004BB8:
    /* 5BB8 80004BB8 3C048002 */  lui        $a0, %hi(readhost_bss_0000)
    /* 5BBC 80004BBC 248494E0 */  addiu      $a0, $a0, %lo(readhost_bss_0000)
    /* 5BC0 80004BC0 00002825 */  or         $a1, $zero, $zero
    /* 5BC4 80004BC4 0C0013F8 */  jal        func_80004FE0
    /* 5BC8 80004BC8 24060001 */   addiu     $a2, $zero, 0x1
    /* 5BCC 80004BCC 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 5BD0 80004BD0 8FB00018 */  lw         $s0, 0x18($sp)
    /* 5BD4 80004BD4 27BD0030 */  addiu      $sp, $sp, 0x30
    /* 5BD8 80004BD8 03E00008 */  jr         $ra
    /* 5BDC 80004BDC 00000000 */   nop
endlabel func_80004BB0
