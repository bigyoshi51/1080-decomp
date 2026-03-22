
nonmatching func_800061F0, 0x4C

glabel func_800061F0
    /* 71F0 800061F0 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 71F4 800061F4 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 71F8 800061F8 AFA40028 */  sw         $a0, 0x28($sp)
    /* 71FC 800061FC 0C0019AC */  jal        func_800066B0
    /* 7200 80006200 AFB00018 */   sw        $s0, 0x18($sp)
    /* 7204 80006204 3C0E8001 */  lui        $t6, %hi(__OSGlobalIntMask)
    /* 7208 80006208 8DCEA3E0 */  lw         $t6, %lo(__OSGlobalIntMask)($t6)
    /* 720C 8000620C 8FAF0028 */  lw         $t7, 0x28($sp)
    /* 7210 80006210 00408025 */  or         $s0, $v0, $zero
    /* 7214 80006214 3C018001 */  lui        $at, %hi(__OSGlobalIntMask)
    /* 7218 80006218 01CFC025 */  or         $t8, $t6, $t7
    /* 721C 8000621C AC38A3E0 */  sw         $t8, %lo(__OSGlobalIntMask)($at)
    /* 7220 80006220 0C0019B4 */  jal        func_800066D0
    /* 7224 80006224 02002025 */   or        $a0, $s0, $zero
    /* 7228 80006228 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 722C 8000622C 8FB00018 */  lw         $s0, 0x18($sp)
    /* 7230 80006230 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 7234 80006234 03E00008 */  jr         $ra
    /* 7238 80006238 00000000 */   nop
endlabel func_800061F0
    /* 723C 8000623C 00000000 */  nop
