
nonmatching func_80005894, 0x2C

glabel func_80005894
    /* 6894 80005894 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 6898 80005898 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 689C 8000589C 3C048002 */  lui        $a0, %hi(__osPiAccessQueue)
    /* 68A0 800058A0 2484B638 */  addiu      $a0, $a0, %lo(__osPiAccessQueue)
    /* 68A4 800058A4 00002825 */  or         $a1, $zero, $zero
    /* 68A8 800058A8 0C001770 */  jal        func_80005DC0
    /* 68AC 800058AC 00003025 */   or        $a2, $zero, $zero
    /* 68B0 800058B0 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 68B4 800058B4 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 68B8 800058B8 03E00008 */  jr         $ra
    /* 68BC 800058BC 00000000 */   nop
endlabel func_80005894
