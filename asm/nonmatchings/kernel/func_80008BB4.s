
nonmatching func_80008BB4, 0x4C

glabel func_80008BB4
    /* 9BB4 80008BB4 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 9BB8 80008BB8 AFA40018 */  sw         $a0, 0x18($sp)
    /* 9BBC 80008BBC 0C002400 */  jal        func_80009000
    /* 9BC0 80008BC0 AFA5001C */   sw        $a1, 0x1C($sp)
    /* 9BC4 80008BC4 10400003 */  beqz       $v0, .L80008BD4
    /* 9BC8 80008BC8 00000000 */   nop
    /* 9BCC 80008BCC 10000008 */  b          .L80008BF0
    /* 9BD0 80008BD0 2402FFFF */   addiu     $v0, $zero, -0x1
  .L80008BD4:
    /* 9BD4 80008BD4 8FAE0018 */  lw         $t6, 0x18($sp)
    /* 9BD8 80008BD8 3C01A000 */  lui        $at, %hi(D_A0000000)
    /* 9BDC 80008BDC 8FB9001C */  lw         $t9, 0x1C($sp)
    /* 9BE0 80008BE0 01C17825 */  or         $t7, $t6, $at
    /* 9BE4 80008BE4 8DF80000 */  lw         $t8, %lo(D_A0000000)($t7)
    /* 9BE8 80008BE8 00001025 */  or         $v0, $zero, $zero
    /* 9BEC 80008BEC AF380000 */  sw         $t8, 0x0($t9)
  .L80008BF0:
    /* 9BF0 80008BF0 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 9BF4 80008BF4 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 9BF8 80008BF8 03E00008 */  jr         $ra
    /* 9BFC 80008BFC 00000000 */   nop
endlabel func_80008BB4
