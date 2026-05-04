nonmatching func_000054A0, 0x38

glabel func_000054A0
    /* DD5F0C 000054A0 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* DD5F10 000054A4 AFA40018 */  sw         $a0, 0x18($sp)
    /* DD5F14 000054A8 AFBF0014 */  sw         $ra, 0x14($sp)
    /* DD5F18 000054AC 3C040000 */  lui        $a0, %hi(D_00007E10)
    /* DD5F1C 000054B0 0C000000 */  jal        func_00000000
    /* DD5F20 000054B4 24847E10 */   addiu     $a0, $a0, %lo(D_00007E10)
    /* DD5F24 000054B8 8FA50018 */  lw         $a1, 0x18($sp)
    /* DD5F28 000054BC 00002025 */  or         $a0, $zero, $zero
    /* DD5F2C 000054C0 0C000000 */  jal        func_00000000
    /* DD5F30 000054C4 AFA50004 */   sw        $a1, 0x4($sp)
    /* DD5F34 000054C8 8FBF0014 */  lw         $ra, 0x14($sp)
    /* DD5F38 000054CC 27BD0018 */  addiu      $sp, $sp, 0x18
    /* DD5F3C 000054D0 03E00008 */  jr         $ra
    /* DD5F40 000054D4 00000000 */   nop
endlabel func_000054A0
