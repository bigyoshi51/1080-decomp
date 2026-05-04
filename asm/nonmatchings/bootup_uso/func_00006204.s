nonmatching func_00006204, 0x24

glabel func_00006204
    /* DD6C70 00006204 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* DD6C74 00006208 3C040000 */  lui        $a0, (0x0 >> 16)
    /* DD6C78 0000620C AFBF0014 */  sw         $ra, 0x14($sp)
    /* DD6C7C 00006210 0C000000 */  jal        func_00000000
    /* DD6C80 00006214 24840000 */   addiu     $a0, $a0, 0x0
    /* DD6C84 00006218 8FBF0014 */  lw         $ra, 0x14($sp)
    /* DD6C88 0000621C 27BD0018 */  addiu      $sp, $sp, 0x18
    /* DD6C8C 00006220 03E00008 */  jr         $ra
    /* DD6C90 00006224 00000000 */   nop
endlabel func_00006204
