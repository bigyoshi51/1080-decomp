
nonmatching func_80005C00, 0x50

glabel func_80005C00
    /* 6C00 80005C00 ADA00018 */  sw         $zero, 0x18($t5)
    /* 6C04 80005C04 8FA80028 */  lw         $t0, 0x28($sp)
    /* 6C08 80005C08 A5180010 */  sh         $t8, 0x10($t0)
    /* 6C0C 80005C0C 8FA90028 */  lw         $t1, 0x28($sp)
    /* 6C10 80005C10 0C0019AC */  jal        func_800066B0
    /* 6C14 80005C14 A5200012 */   sh        $zero, 0x12($t1)
    /* 6C18 80005C18 3C0A8001 */  lui        $t2, %hi(D_8000A41C)
    /* 6C1C 80005C1C 8D4AA41C */  lw         $t2, %lo(D_8000A41C)($t2)
    /* 6C20 80005C20 8FAB0028 */  lw         $t3, 0x28($sp)
    /* 6C24 80005C24 00408025 */  or         $s0, $v0, $zero
    /* 6C28 80005C28 3C018001 */  lui        $at, %hi(D_8000A41C)
    /* 6C2C 80005C2C AD6A000C */  sw         $t2, 0xC($t3)
    /* 6C30 80005C30 8FB90028 */  lw         $t9, 0x28($sp)
    /* 6C34 80005C34 02002025 */  or         $a0, $s0, $zero
    /* 6C38 80005C38 0C0019B4 */  jal        func_800066D0
    /* 6C3C 80005C3C AC39A41C */   sw        $t9, %lo(D_8000A41C)($at)
    /* 6C40 80005C40 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 6C44 80005C44 8FB00018 */  lw         $s0, 0x18($sp)
    /* 6C48 80005C48 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 6C4C 80005C4C 03E00008 */  jr         $ra
endlabel func_80005C00
