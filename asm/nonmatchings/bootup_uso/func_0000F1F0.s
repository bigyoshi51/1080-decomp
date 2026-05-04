nonmatching func_0000F1F0, 0x4C

glabel func_0000F1F0
    /* DDFC5C 0000F1F0 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* DDFC60 0000F1F4 AFBF0014 */  sw         $ra, 0x14($sp)
    /* DDFC64 0000F1F8 AFA40020 */  sw         $a0, 0x20($sp)
    /* DDFC68 0000F1FC 3C040000 */  lui        $a0, (0x0 >> 16)
    /* DDFC6C 0000F200 24840000 */  addiu      $a0, $a0, 0x0
    /* DDFC70 0000F204 27A50018 */  addiu      $a1, $sp, 0x18
    /* DDFC74 0000F208 24060004 */  addiu      $a2, $zero, 0x4
    /* DDFC78 0000F20C 0C000000 */  jal        func_00000000
    /* DDFC7C 0000F210 00000000 */   nop
    /* DDFC80 0000F214 27AE0018 */  addiu      $t6, $sp, 0x18
    /* DDFC84 0000F218 8DCF0000 */  lw         $t7, 0x0($t6)
    /* DDFC88 0000F21C 8FB80020 */  lw         $t8, 0x20($sp)
    /* DDFC8C 0000F220 AF0F0000 */  sw         $t7, 0x0($t8)
    /* DDFC90 0000F224 10000001 */  b          .L0000F22C
    /* DDFC94 0000F228 00000000 */   nop
  .L0000F22C:
    /* DDFC98 0000F22C 8FBF0014 */  lw         $ra, 0x14($sp)
    /* DDFC9C 0000F230 27BD0020 */  addiu      $sp, $sp, 0x20
    /* DDFCA0 0000F234 03E00008 */  jr         $ra
    /* DDFCA4 0000F238 00000000 */   nop
endlabel func_0000F1F0
