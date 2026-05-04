nonmatching func_000020AC, 0x2C

glabel func_000020AC
    /* DD2B18 000020AC 8C8E00C0 */  lw         $t6, 0xC0($a0)
    /* DD2B1C 000020B0 000E78C0 */  sll        $t7, $t6, 3
    /* DD2B20 000020B4 008FC021 */  addu       $t8, $a0, $t7
    /* DD2B24 000020B8 AF0600C8 */  sw         $a2, 0xC8($t8)
    /* DD2B28 000020BC 8C8200C0 */  lw         $v0, 0xC0($a0)
    /* DD2B2C 000020C0 24590001 */  addiu      $t9, $v0, 0x1
    /* DD2B30 000020C4 000240C0 */  sll        $t0, $v0, 3
    /* DD2B34 000020C8 00884821 */  addu       $t1, $a0, $t0
    /* DD2B38 000020CC AC9900C0 */  sw         $t9, 0xC0($a0)
    /* DD2B3C 000020D0 03E00008 */  jr         $ra
    /* DD2B40 000020D4 AD2500C4 */   sw        $a1, 0xC4($t1)
endlabel func_000020AC
