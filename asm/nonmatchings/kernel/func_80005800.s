
nonmatching func_80005800, 0x50

glabel func_80005800
    /* 6800 80005800 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 6804 80005804 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 6808 80005808 240E0001 */  addiu      $t6, $zero, 0x1
    /* 680C 8000580C 3C018001 */  lui        $at, %hi(__osPiAccessQueueEnabled)
    /* 6810 80005810 3C048002 */  lui        $a0, %hi(__osPiAccessQueue)
    /* 6814 80005814 3C058002 */  lui        $a1, %hi(siacs_bss_0000)
    /* 6818 80005818 AC2EA480 */  sw         $t6, %lo(__osPiAccessQueueEnabled)($at)
    /* 681C 8000581C 24A5B630 */  addiu      $a1, $a1, %lo(siacs_bss_0000)
    /* 6820 80005820 2484B638 */  addiu      $a0, $a0, %lo(__osPiAccessQueue)
    /* 6824 80005824 0C0014F4 */  jal        func_800053D0
    /* 6828 80005828 24060001 */   addiu     $a2, $zero, 0x1
    /* 682C 8000582C 3C048002 */  lui        $a0, %hi(__osPiAccessQueue)
    /* 6830 80005830 2484B638 */  addiu      $a0, $a0, %lo(__osPiAccessQueue)
    /* 6834 80005834 00002825 */  or         $a1, $zero, $zero
    /* 6838 80005838 0C001770 */  jal        func_80005DC0
    /* 683C 8000583C 00003025 */   or        $a2, $zero, $zero
    /* 6840 80005840 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 6844 80005844 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 6848 80005848 03E00008 */  jr         $ra
    /* 684C 8000584C 00000000 */   nop
endlabel func_80005800
