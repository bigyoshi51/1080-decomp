nonmatching func_0000F23C, 0x4C

glabel func_0000F23C
    /* DDFCA8 0000F23C 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* DDFCAC 0000F240 AFBF0014 */  sw         $ra, 0x14($sp)
    /* DDFCB0 0000F244 AFA40020 */  sw         $a0, 0x20($sp)
    /* DDFCB4 0000F248 3C040000 */  lui        $a0, (0x0 >> 16)
    /* DDFCB8 0000F24C 24840000 */  addiu      $a0, $a0, 0x0
    /* DDFCBC 0000F250 27A50018 */  addiu      $a1, $sp, 0x18
    /* DDFCC0 0000F254 24060004 */  addiu      $a2, $zero, 0x4
    /* DDFCC4 0000F258 0C000000 */  jal        func_00000000
    /* DDFCC8 0000F25C 00000000 */   nop
    /* DDFCCC 0000F260 27AE0018 */  addiu      $t6, $sp, 0x18
    /* DDFCD0 0000F264 C5C40000 */  lwc1       $f4, 0x0($t6)
    /* DDFCD4 0000F268 8FAF0020 */  lw         $t7, 0x20($sp)
    /* DDFCD8 0000F26C E5E40000 */  swc1       $f4, 0x0($t7)
    /* DDFCDC 0000F270 10000001 */  b          .L0000F278
    /* DDFCE0 0000F274 00000000 */   nop
  .L0000F278:
    /* DDFCE4 0000F278 8FBF0014 */  lw         $ra, 0x14($sp)
    /* DDFCE8 0000F27C 27BD0020 */  addiu      $sp, $sp, 0x20
    /* DDFCEC 0000F280 03E00008 */  jr         $ra
    /* DDFCF0 0000F284 00000000 */   nop
endlabel func_0000F23C
