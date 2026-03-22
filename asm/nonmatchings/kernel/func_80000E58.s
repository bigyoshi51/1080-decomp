
nonmatching func_80000E58, 0x34

glabel func_80000E58
    /* 1E58 80000E58 3C198001 */  lui        $t9, %hi(D_80012C44)
    /* 1E5C 80000E5C 8F392C44 */  lw         $t9, %lo(D_80012C44)($t9)
    /* 1E60 80000E60 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 1E64 80000E64 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 1E68 80000E68 3C048001 */  lui        $a0, %hi(D_8000A32C)
    /* 1E6C 80000E6C 3C058001 */  lui        $a1, %hi(D_8000A340)
    /* 1E70 80000E70 24A5A340 */  addiu      $a1, $a1, %lo(D_8000A340)
    /* 1E74 80000E74 0320F809 */  jalr       $t9
    /* 1E78 80000E78 2484A32C */   addiu     $a0, $a0, %lo(D_8000A32C)
    /* 1E7C 80000E7C 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 1E80 80000E80 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 1E84 80000E84 03E00008 */  jr         $ra
    /* 1E88 80000E88 00000000 */   nop
endlabel func_80000E58
