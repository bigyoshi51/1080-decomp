nonmatching func_00011CA4, 0x34

glabel func_00011CA4
    /* DE2710 00011CA4 27BDFFF8 */  addiu      $sp, $sp, -0x8
    /* DE2714 00011CA8 00803825 */  or         $a3, $a0, $zero
    /* DE2718 00011CAC 8CE60124 */  lw         $a2, 0x124($a3)
    /* DE271C 00011CB0 24CE0001 */  addiu      $t6, $a2, 0x1
    /* DE2720 00011CB4 ACEE0124 */  sw         $t6, 0x124($a3)
    /* DE2724 00011CB8 00067880 */  sll        $t7, $a2, 2
    /* DE2728 00011CBC 008FC021 */  addu       $t8, $a0, $t7
    /* DE272C 00011CC0 AF050100 */  sw         $a1, 0x100($t8)
    /* DE2730 00011CC4 10000001 */  b          .L00011CCC
    /* DE2734 00011CC8 00000000 */   nop
  .L00011CCC:
    /* DE2738 00011CCC 27BD0008 */  addiu      $sp, $sp, 0x8
    /* DE273C 00011CD0 03E00008 */  jr         $ra
    /* DE2740 00011CD4 00000000 */   nop
endlabel func_00011CA4
