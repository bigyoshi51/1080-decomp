
nonmatching func_80001CB0, 0x44

glabel func_80001CB0
    /* 2CB0 80001CB0 10000009 */  b          .L80001CD8
    /* 2CB4 80001CB4 2402FFFE */   addiu     $v0, $zero, -0x2
  .L80001CB8:
    /* 2CB8 80001CB8 348F0008 */  ori        $t7, $a0, 0x8
    /* 2CBC 80001CBC ACAF0000 */  sw         $t7, 0x0($a1)
  .L80001CC0:
    /* 2CC0 80001CC0 24A5000C */  addiu      $a1, $a1, 0xC
    /* 2CC4 80001CC4 54A6FF9D */  bnel       $a1, $a2, .L80001B3C
    /* 2CC8 80001CC8 8CA40000 */   lw        $a0, 0x0($a1)
    /* 2CCC 80001CCC AFAC0028 */  sw         $t4, 0x28($sp)
    /* 2CD0 80001CD0 AFAA0034 */  sw         $t2, 0x34($sp)
  .L80001CD4:
    /* 2CD4 80001CD4 00001025 */  or         $v0, $zero, $zero
  .L80001CD8:
    /* 2CD8 80001CD8 8FBF0024 */  lw         $ra, 0x24($sp)
    /* 2CDC 80001CDC 8FB00014 */  lw         $s0, 0x14($sp)
    /* 2CE0 80001CE0 8FB10018 */  lw         $s1, 0x18($sp)
    /* 2CE4 80001CE4 8FB2001C */  lw         $s2, 0x1C($sp)
    /* 2CE8 80001CE8 8FB30020 */  lw         $s3, 0x20($sp)
    /* 2CEC 80001CEC 03E00008 */  jr         $ra
/* glabel func_80001CF0 */
    /* 2CF0 80001CF0 27BD0050 */  addiu      $sp, $sp, 0x50
endlabel func_80001CB0
