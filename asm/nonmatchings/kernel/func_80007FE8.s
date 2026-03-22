
nonmatching func_80007FE8, 0x44

glabel func_80007FE8
    /* 8FE8 80007FE8 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 8FEC 80007FEC AFA40028 */  sw         $a0, 0x28($sp)
    /* 8FF0 80007FF0 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 8FF4 80007FF4 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 8FF8 80007FF8 27A40018 */  addiu      $a0, $sp, 0x18
    /* 8FFC 80007FFC 91CF0004 */  lbu        $t7, 0x4($t6)
    /* 9000 80008000 AFA00024 */  sw         $zero, 0x24($sp)
    /* 9004 80008004 A7A0001E */  sh         $zero, 0x1E($sp)
    /* 9008 80008008 24050010 */  addiu      $a1, $zero, 0x10
    /* 900C 8000800C 24060001 */  addiu      $a2, $zero, 0x1
    /* 9010 80008010 0C001CFE */  jal        func_800073F8
    /* 9014 80008014 A3AF001C */   sb        $t7, 0x1C($sp)
    /* 9018 80008018 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 901C 8000801C 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 9020 80008020 00001025 */  or         $v0, $zero, $zero
    /* 9024 80008024 03E00008 */  jr         $ra
    /* 9028 80008028 00000000 */   nop
endlabel func_80007FE8
    /* 902C 8000802C 00000000 */  nop
