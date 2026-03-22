
nonmatching func_800065BC, 0x34

glabel func_800065BC
    /* 75BC 800065BC 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 75C0 800065C0 AFA40028 */  sw         $a0, 0x28($sp)
    /* 75C4 800065C4 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 75C8 800065C8 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 75CC 800065CC 91CF0004 */  lbu        $t7, 0x4($t6)
    /* 75D0 800065D0 29E10035 */  slti       $at, $t7, 0x35
    /* 75D4 800065D4 14200003 */  bnez       $at, .L800065E4
    /* 75D8 800065D8 00000000 */   nop
    /* 75DC 800065DC 10000017 */  b          .L8000663C
    /* 75E0 800065E0 2402FFFF */   addiu     $v0, $zero, -0x1
  .L800065E4:
    /* 75E4 800065E4 8FB80028 */  lw         $t8, 0x28($sp)
    /* 75E8 800065E8 93190004 */  lbu        $t9, 0x4($t8)
    /* 75EC 800065EC 03002025 */  or         $a0, $t8, $zero
endlabel func_800065BC
