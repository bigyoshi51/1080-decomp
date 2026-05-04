nonmatching func_000054D8, 0x64

glabel func_000054D8
    /* DD5F44 000054D8 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* DD5F48 000054DC AFBF0014 */  sw         $ra, 0x14($sp)
    /* DD5F4C 000054E0 AFA40028 */  sw         $a0, 0x28($sp)
    /* DD5F50 000054E4 AFA4001C */  sw         $a0, 0x1C($sp)
    /* DD5F54 000054E8 0C000000 */  jal        func_00000000
    /* DD5F58 000054EC 24040058 */   addiu     $a0, $zero, 0x58
    /* DD5F5C 000054F0 1040000D */  beqz       $v0, .L00005528
    /* DD5F60 000054F4 00402025 */   or        $a0, $v0, $zero
    /* DD5F64 000054F8 8FA5001C */  lw         $a1, 0x1C($sp)
    /* DD5F68 000054FC 3C060000 */  lui        $a2, (0x0 >> 16)
    /* DD5F6C 00005500 3C070000 */  lui        $a3, (0x0 >> 16)
    /* DD5F70 00005504 24E70000 */  addiu      $a3, $a3, 0x0
    /* DD5F74 00005508 8CC60000 */  lw         $a2, 0x0($a2)
    /* DD5F78 0000550C AFA20020 */  sw         $v0, 0x20($sp)
    /* DD5F7C 00005510 0C000000 */  jal        func_00000000
    /* DD5F80 00005514 AFA50004 */   sw        $a1, 0x4($sp)
    /* DD5F84 00005518 8FA40020 */  lw         $a0, 0x20($sp)
    /* DD5F88 0000551C 3C180000 */  lui        $t8, %hi(D_000078D8)
    /* DD5F8C 00005520 271878D8 */  addiu      $t8, $t8, %lo(D_000078D8)
    /* DD5F90 00005524 AC980028 */  sw         $t8, 0x28($a0)
  .L00005528:
    /* DD5F94 00005528 8FBF0014 */  lw         $ra, 0x14($sp)
    /* DD5F98 0000552C 27BD0028 */  addiu      $sp, $sp, 0x28
    /* DD5F9C 00005530 00801025 */  or         $v0, $a0, $zero
    /* DD5FA0 00005534 03E00008 */  jr         $ra
    /* DD5FA4 00005538 00000000 */   nop
endlabel func_000054D8
