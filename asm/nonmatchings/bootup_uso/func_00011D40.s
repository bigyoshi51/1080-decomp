nonmatching func_00011D40, 0x30

glabel func_00011D40
    /* DE27AC 00011D40 8C8E0120 */  lw         $t6, 0x120($a0)
    /* DE27B0 00011D44 01C5082A */  slt        $at, $t6, $a1
    /* DE27B4 00011D48 10200004 */  beqz       $at, .L00011D5C
    /* DE27B8 00011D4C 00000000 */   nop
    /* DE27BC 00011D50 00001025 */  or         $v0, $zero, $zero
    /* DE27C0 00011D54 03E00008 */  jr         $ra
    /* DE27C4 00011D58 00000000 */   nop
  .L00011D5C:
    /* DE27C8 00011D5C 00057880 */  sll        $t7, $a1, 2
    /* DE27CC 00011D60 008FC021 */  addu       $t8, $a0, $t7
    /* DE27D0 00011D64 8F0200DC */  lw         $v0, 0xDC($t8)
    /* DE27D4 00011D68 03E00008 */  jr         $ra
    /* DE27D8 00011D6C 00000000 */   nop
endlabel func_00011D40
