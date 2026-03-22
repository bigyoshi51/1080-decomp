
nonmatching func_80007EA0, 0x4C

glabel func_80007EA0
    /* 8EA0 80007EA0 27BDFFD0 */  addiu      $sp, $sp, -0x30
    /* 8EA4 80007EA4 AFA40030 */  sw         $a0, 0x30($sp)
    /* 8EA8 80007EA8 8FAE0030 */  lw         $t6, 0x30($sp)
    /* 8EAC 80007EAC AFBF0014 */  sw         $ra, 0x14($sp)
    /* 8EB0 80007EB0 27A4001C */  addiu      $a0, $sp, 0x1C
    /* 8EB4 80007EB4 AFAE002C */  sw         $t6, 0x2C($sp)
    /* 8EB8 80007EB8 91CF0004 */  lbu        $t7, 0x4($t6)
    /* 8EBC 80007EBC A7A00022 */  sh         $zero, 0x22($sp)
    /* 8EC0 80007EC0 24050010 */  addiu      $a1, $zero, 0x10
    /* 8EC4 80007EC4 A3AF0020 */  sb         $t7, 0x20($sp)
    /* 8EC8 80007EC8 8DD8000C */  lw         $t8, 0xC($t6)
    /* 8ECC 80007ECC 24060001 */  addiu      $a2, $zero, 0x1
    /* 8ED0 80007ED0 0C001CFE */  jal        func_800073F8
    /* 8ED4 80007ED4 AFB80028 */   sw        $t8, 0x28($sp)
    /* 8ED8 80007ED8 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 8EDC 80007EDC 27BD0030 */  addiu      $sp, $sp, 0x30
    /* 8EE0 80007EE0 00001025 */  or         $v0, $zero, $zero
    /* 8EE4 80007EE4 03E00008 */  jr         $ra
    /* 8EE8 80007EE8 00000000 */   nop
endlabel func_80007EA0
