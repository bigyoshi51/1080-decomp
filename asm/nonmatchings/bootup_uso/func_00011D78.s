nonmatching func_00011D78, 0x3C

glabel func_00011D78
    /* DE27E4 00011D78 8C8E018C */  lw         $t6, 0x18C($a0)
    /* DE27E8 00011D7C 15C0000A */  bnez       $t6, .L00011DA8
    /* DE27EC 00011D80 00000000 */   nop
    /* DE27F0 00011D84 8C8F0128 */  lw         $t7, 0x128($a0)
    /* DE27F4 00011D88 000FC080 */  sll        $t8, $t7, 2
    /* DE27F8 00011D8C 0098C821 */  addu       $t9, $a0, $t8
    /* DE27FC 00011D90 8F2800E0 */  lw         $t0, 0xE0($t9)
    /* DE2800 00011D94 C5000000 */  lwc1       $f0, 0x0($t0)
    /* DE2804 00011D98 03E00008 */  jr         $ra
    /* DE2808 00011D9C 00000000 */   nop
    /* DE280C 00011DA0 03E00008 */  jr         $ra
    /* DE2810 00011DA4 00000000 */   nop
  .L00011DA8:
    /* DE2814 00011DA8 44800000 */  mtc1       $zero, $f0
    /* DE2818 00011DAC 03E00008 */  jr         $ra
    /* DE281C 00011DB0 00000000 */   nop
endlabel func_00011D78
