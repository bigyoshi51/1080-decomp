
/* Handwritten function */
nonmatching func_80004DB8, 0x20

glabel func_80004DB8
    /* 5DB8 80004DB8 008B6824 */  and        $t5, $a0, $t3
    /* 5DBC 80004DBC 004D1020 */  add        $v0, $v0, $t5 /* handwritten instruction */
    /* 5DC0 80004DC0 10000002 */  b          .L80004DCC
    /* 5DC4 80004DC4 00000000 */   nop
  .L80004DC8:
    /* 5DC8 80004DC8 2402FFFF */  addiu      $v0, $zero, -0x1
  .L80004DCC:
    /* 5DCC 80004DCC 40885000 */  mtc0       $t0, $10 /* handwritten instruction */
    /* 5DD0 80004DD0 03E00008 */  jr         $ra
    /* 5DD4 80004DD4 00000000 */   nop
endlabel func_80004DB8
    /* 5DD8 80004DD8 00000000 */  nop
    /* 5DDC 80004DDC 00000000 */  nop
