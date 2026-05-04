nonmatching func_00011C70, 0x34

glabel func_00011C70
    /* DE26DC 00011C70 27BDFFF8 */  addiu      $sp, $sp, -0x8
    /* DE26E0 00011C74 00803825 */  or         $a3, $a0, $zero
    /* DE26E4 00011C78 8CE60120 */  lw         $a2, 0x120($a3)
    /* DE26E8 00011C7C 24CE0001 */  addiu      $t6, $a2, 0x1
    /* DE26EC 00011C80 ACEE0120 */  sw         $t6, 0x120($a3)
    /* DE26F0 00011C84 00067880 */  sll        $t7, $a2, 2
    /* DE26F4 00011C88 008FC021 */  addu       $t8, $a0, $t7
    /* DE26F8 00011C8C AF0500E0 */  sw         $a1, 0xE0($t8)
    /* DE26FC 00011C90 10000001 */  b          .L00011C98
    /* DE2700 00011C94 00000000 */   nop
  .L00011C98:
    /* DE2704 00011C98 27BD0008 */  addiu      $sp, $sp, 0x8
    /* DE2708 00011C9C 03E00008 */  jr         $ra
    /* DE270C 00011CA0 00000000 */   nop
endlabel func_00011C70
