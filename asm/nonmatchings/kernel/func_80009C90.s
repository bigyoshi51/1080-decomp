
nonmatching func_80009C90, 0x4C

glabel func_80009C90
    /* AC90 80009C90 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* AC94 80009C94 AFBF0014 */  sw         $ra, 0x14($sp)
    /* AC98 80009C98 AFA40018 */  sw         $a0, 0x18($sp)
    /* AC9C 80009C9C 0C002400 */  jal        func_80009000
    /* ACA0 80009CA0 AFA5001C */   sw        $a1, 0x1C($sp)
    /* ACA4 80009CA4 10400003 */  beqz       $v0, .L80009CB4
    /* ACA8 80009CA8 00000000 */   nop
    /* ACAC 80009CAC 10000007 */  b          .L80009CCC
    /* ACB0 80009CB0 2402FFFF */   addiu     $v0, $zero, -0x1
  .L80009CB4:
    /* ACB4 80009CB4 8FAF0018 */  lw         $t7, 0x18($sp)
    /* ACB8 80009CB8 8FAE001C */  lw         $t6, 0x1C($sp)
    /* ACBC 80009CBC 3C01A000 */  lui        $at, %hi(D_A0000000)
    /* ACC0 80009CC0 01E1C025 */  or         $t8, $t7, $at
    /* ACC4 80009CC4 00001025 */  or         $v0, $zero, $zero
    /* ACC8 80009CC8 AF0E0000 */  sw         $t6, %lo(D_A0000000)($t8)
  .L80009CCC:
    /* ACCC 80009CCC 8FBF0014 */  lw         $ra, 0x14($sp)
    /* ACD0 80009CD0 27BD0018 */  addiu      $sp, $sp, 0x18
    /* ACD4 80009CD4 03E00008 */  jr         $ra
    /* ACD8 80009CD8 00000000 */   nop
endlabel func_80009C90
    /* ACDC 80009CDC 00000000 */  nop
