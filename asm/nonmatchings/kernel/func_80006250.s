
nonmatching func_80006250, 0x58

glabel func_80006250
    /* 7250 80006250 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 7254 80006254 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 7258 80006258 AFA40028 */  sw         $a0, 0x28($sp)
    /* 725C 8000625C 0C0019AC */  jal        func_800066B0
    /* 7260 80006260 AFB00018 */   sw        $s0, 0x18($sp)
    /* 7264 80006264 8FAF0028 */  lw         $t7, 0x28($sp)
    /* 7268 80006268 3C0E8001 */  lui        $t6, %hi(__OSGlobalIntMask)
    /* 726C 8000626C 8DCEA3E0 */  lw         $t6, %lo(__OSGlobalIntMask)($t6)
    /* 7270 80006270 2401FBFE */  addiu      $at, $zero, -0x402
    /* 7274 80006274 01E1C024 */  and        $t8, $t7, $at
    /* 7278 80006278 0300C827 */  not        $t9, $t8
    /* 727C 8000627C 00408025 */  or         $s0, $v0, $zero
    /* 7280 80006280 3C018001 */  lui        $at, %hi(__OSGlobalIntMask)
    /* 7284 80006284 01D94024 */  and        $t0, $t6, $t9
    /* 7288 80006288 AC28A3E0 */  sw         $t0, %lo(__OSGlobalIntMask)($at)
    /* 728C 8000628C 0C0019B4 */  jal        func_800066D0
    /* 7290 80006290 02002025 */   or        $a0, $s0, $zero
    /* 7294 80006294 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 7298 80006298 8FB00018 */  lw         $s0, 0x18($sp)
    /* 729C 8000629C 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 72A0 800062A0 03E00008 */  jr         $ra
    /* 72A4 800062A4 00000000 */   nop
endlabel func_80006250
    /* 72A8 800062A8 00000000 */  nop
    /* 72AC 800062AC 00000000 */  nop
