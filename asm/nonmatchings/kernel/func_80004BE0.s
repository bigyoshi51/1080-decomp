
nonmatching func_80004BE0, 0x28

glabel func_80004BE0
    /* 5BE0 80004BE0 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 5BE4 80004BE4 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 5BE8 80004BE8 AFA40028 */  sw         $a0, 0x28($sp)
    /* 5BEC 80004BEC AFA5002C */  sw         $a1, 0x2C($sp)
    /* 5BF0 80004BF0 AFA60030 */  sw         $a2, 0x30($sp)
    /* 5BF4 80004BF4 AFB10018 */  sw         $s1, 0x18($sp)
    /* 5BF8 80004BF8 0C0019AC */  jal        func_800066B0
    /* 5BFC 80004BFC AFB00014 */   sw        $s0, 0x14($sp)
    /* 5C00 80004C00 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 5C04 80004C04 00408025 */  or         $s0, $v0, $zero
endlabel func_80004BE0
