nonmatching func_00005068, 0x38

glabel func_00005068
    /* DD5AD4 00005068 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* DD5AD8 0000506C AFA40018 */  sw         $a0, 0x18($sp)
    /* DD5ADC 00005070 AFBF0014 */  sw         $ra, 0x14($sp)
    /* DD5AE0 00005074 3C040000 */  lui        $a0, %hi(D_00007D94)
    /* DD5AE4 00005078 0C000000 */  jal        func_00000000
    /* DD5AE8 0000507C 24847D94 */   addiu     $a0, $a0, %lo(D_00007D94)
    /* DD5AEC 00005080 8FA50018 */  lw         $a1, 0x18($sp)
    /* DD5AF0 00005084 00002025 */  or         $a0, $zero, $zero
    /* DD5AF4 00005088 0C000000 */  jal        func_00000000
    /* DD5AF8 0000508C AFA50004 */   sw        $a1, 0x4($sp)
    /* DD5AFC 00005090 8FBF0014 */  lw         $ra, 0x14($sp)
    /* DD5B00 00005094 27BD0018 */  addiu      $sp, $sp, 0x18
    /* DD5B04 00005098 03E00008 */  jr         $ra
    /* DD5B08 0000509C 00000000 */   nop
endlabel func_00005068
