nonmatching func_00010324, 0x20

glabel func_00010324
    /* DE0D90 00010324 8C8E007C */  lw         $t6, 0x7C($a0)
    /* DE0D94 00010328 000E7880 */  sll        $t7, $t6, 2
    /* DE0D98 0001032C 01EE7821 */  addu       $t7, $t7, $t6
    /* DE0D9C 00010330 000F78C0 */  sll        $t7, $t7, 3
    /* DE0DA0 00010334 008F1021 */  addu       $v0, $a0, $t7
    /* DE0DA4 00010338 24420084 */  addiu      $v0, $v0, 0x84
    /* DE0DA8 0001033C 03E00008 */  jr         $ra
    /* DE0DAC 00010340 00000000 */   nop
endlabel func_00010324
