glabel func_0000FEA0
    /* DE090C 0000FEA0 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* DE0910 0000FEA4 AFBF001C */  sw         $ra, 0x1C($sp)
    /* DE0914 0000FEA8 AFA40028 */  sw         $a0, 0x28($sp)
    /* DE0918 0000FEAC AFB00018 */  sw         $s0, 0x18($sp)
    /* DE091C 0000FEB0 8FAE0028 */  lw         $t6, 0x28($sp)
    /* DE0920 0000FEB4 8DD00028 */  lw         $s0, 0x28($t6)
    /* DE0924 0000FEB8 860F0060 */  lh         $t7, 0x60($s0)
    /* DE0928 0000FEBC 01EE2021 */  addu       $a0, $t7, $t6
    /* DE092C 0000FEC0 8E190064 */  lw         $t9, 0x64($s0)
    /* DE0930 0000FEC4 0320F809 */  jalr       $t9
    /* DE0934 0000FEC8 00000000 */   nop
    /* DE0938 0000FECC 10000001 */  b          .L0000FED4
    /* DE093C 0000FED0 00000000 */   nop
  .L0000FED4:
    /* DE0940 0000FED4 8FB00018 */  lw         $s0, 0x18($sp)
    /* DE0944 0000FED8 8FBF001C */  lw         $ra, 0x1C($sp)
    /* DE0948 0000FEDC 27BD0028 */  addiu      $sp, $sp, 0x28
    /* DE094C 0000FEE0 03E00008 */  jr         $ra
    /* DE0950 0000FEE4 00000000 */   nop
endlabel func_0000FEA0
