
nonmatching func_8000698C, 0x30

glabel func_8000698C
    /* 798C 8000698C 27BDFFB8 */  addiu      $sp, $sp, -0x48
    /* 7990 80006990 AFA40048 */  sw         $a0, 0x48($sp)
    /* 7994 80006994 8FAE0048 */  lw         $t6, 0x48($sp)
    /* 7998 80006998 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 799C 8000699C AFB10018 */  sw         $s1, 0x18($sp)
    /* 79A0 800069A0 AFB00014 */  sw         $s0, 0x14($sp)
    /* 79A4 800069A4 91CF0009 */  lbu        $t7, 0x9($t6)
    /* 79A8 800069A8 01C08025 */  or         $s0, $t6, $zero
    /* 79AC 800069AC 15E00008 */  bnez       $t7, .L800069D0
    /* 79B0 800069B0 00000000 */   nop
    /* 79B4 800069B4 0C0012CC */  jal        func_80004B30
    /* 79B8 800069B8 8E040010 */   lw        $a0, 0x10($s0)
endlabel func_8000698C
