nonmatching func_00002088, 0x1C

glabel func_00002088
    /* DD2AF4 00002088 8C820104 */  lw         $v0, 0x104($a0)
    /* DD2AF8 0000208C 244E0001 */  addiu      $t6, $v0, 0x1
    /* DD2AFC 00002090 00027880 */  sll        $t7, $v0, 2
    /* DD2B00 00002094 008FC021 */  addu       $t8, $a0, $t7
    /* DD2B04 00002098 AC8E0104 */  sw         $t6, 0x104($a0)
    /* DD2B08 0000209C 03E00008 */  jr         $ra
    /* DD2B0C 000020A0 AF050108 */   sw        $a1, 0x108($t8)
endlabel func_00002088
