
nonmatching func_80004DE0, 0x68

glabel func_80004DE0
    /* 5DE0 80004DE0 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 5DE4 80004DE4 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 5DE8 80004DE8 AFA40028 */  sw         $a0, 0x28($sp)
    /* 5DEC 80004DEC AFA5002C */  sw         $a1, 0x2C($sp)
    /* 5DF0 80004DF0 AFA60030 */  sw         $a2, 0x30($sp)
    /* 5DF4 80004DF4 0C0019AC */  jal        func_800066B0
    /* 5DF8 80004DF8 AFB00018 */   sw        $s0, 0x18($sp)
    /* 5DFC 80004DFC 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 5E00 80004E00 3C188002 */  lui        $t8, %hi(__osEventStateTab)
    /* 5E04 80004E04 8FA8002C */  lw         $t0, 0x2C($sp)
    /* 5E08 80004E08 27189510 */  addiu      $t8, $t8, %lo(__osEventStateTab)
    /* 5E0C 80004E0C 000E78C0 */  sll        $t7, $t6, 3
    /* 5E10 80004E10 01F8C821 */  addu       $t9, $t7, $t8
    /* 5E14 80004E14 AFB90020 */  sw         $t9, 0x20($sp)
    /* 5E18 80004E18 AF280000 */  sw         $t0, 0x0($t9)
    /* 5E1C 80004E1C 8FAA0020 */  lw         $t2, 0x20($sp)
    /* 5E20 80004E20 8FA90030 */  lw         $t1, 0x30($sp)
    /* 5E24 80004E24 00408025 */  or         $s0, $v0, $zero
    /* 5E28 80004E28 02002025 */  or         $a0, $s0, $zero
    /* 5E2C 80004E2C 0C0019B4 */  jal        func_800066D0
    /* 5E30 80004E30 AD490004 */   sw        $t1, 0x4($t2)
    /* 5E34 80004E34 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 5E38 80004E38 8FB00018 */  lw         $s0, 0x18($sp)
    /* 5E3C 80004E3C 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 5E40 80004E40 03E00008 */  jr         $ra
    /* 5E44 80004E44 00000000 */   nop
endlabel func_80004DE0
    /* 5E48 80004E48 00000000 */  nop
    /* 5E4C 80004E4C 00000000 */  nop
