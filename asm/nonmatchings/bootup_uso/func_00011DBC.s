nonmatching func_00011DBC, 0x3C

glabel func_00011DBC
    /* DE2828 00011DBC 8C8E018C */  lw         $t6, 0x18C($a0)
    /* DE282C 00011DC0 15C0000A */  bnez       $t6, .L00011DEC
    /* DE2830 00011DC4 00000000 */   nop
    /* DE2834 00011DC8 8C8F0128 */  lw         $t7, 0x128($a0)
    /* DE2838 00011DCC 000FC080 */  sll        $t8, $t7, 2
    /* DE283C 00011DD0 0098C821 */  addu       $t9, $a0, $t8
    /* DE2840 00011DD4 8F2800E0 */  lw         $t0, 0xE0($t9)
    /* DE2844 00011DD8 C5000004 */  lwc1       $f0, 0x4($t0)
    /* DE2848 00011DDC 03E00008 */  jr         $ra
    /* DE284C 00011DE0 00000000 */   nop
    /* DE2850 00011DE4 03E00008 */  jr         $ra
    /* DE2854 00011DE8 00000000 */   nop
  .L00011DEC:
    /* DE2858 00011DEC 44800000 */  mtc1       $zero, $f0
    /* DE285C 00011DF0 03E00008 */  jr         $ra
    /* DE2860 00011DF4 00000000 */   nop
endlabel func_00011DBC
