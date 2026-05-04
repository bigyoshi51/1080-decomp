nonmatching func_0000F288, 0x64

glabel func_0000F288
    /* DDFCF4 0000F288 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* DDFCF8 0000F28C AFBF0014 */  sw         $ra, 0x14($sp)
    /* DDFCFC 0000F290 AFA40028 */  sw         $a0, 0x28($sp)
    /* DDFD00 0000F294 3C040000 */  lui        $a0, (0x0 >> 16)
    /* DDFD04 0000F298 24840000 */  addiu      $a0, $a0, 0x0
    /* DDFD08 0000F29C 27A50018 */  addiu      $a1, $sp, 0x18
    /* DDFD0C 0000F2A0 24060010 */  addiu      $a2, $zero, 0x10
    /* DDFD10 0000F2A4 0C000000 */  jal        func_00000000
    /* DDFD14 0000F2A8 00000000 */   nop
    /* DDFD18 0000F2AC 8FAE0028 */  lw         $t6, 0x28($sp)
    /* DDFD1C 0000F2B0 27AF0018 */  addiu      $t7, $sp, 0x18
    /* DDFD20 0000F2B4 8DF90000 */  lw         $t9, 0x0($t7)
    /* DDFD24 0000F2B8 ADD90000 */  sw         $t9, 0x0($t6)
    /* DDFD28 0000F2BC 8DF80004 */  lw         $t8, 0x4($t7)
    /* DDFD2C 0000F2C0 ADD80004 */  sw         $t8, 0x4($t6)
    /* DDFD30 0000F2C4 8DF90008 */  lw         $t9, 0x8($t7)
    /* DDFD34 0000F2C8 ADD90008 */  sw         $t9, 0x8($t6)
    /* DDFD38 0000F2CC 8DF8000C */  lw         $t8, 0xC($t7)
    /* DDFD3C 0000F2D0 ADD8000C */  sw         $t8, 0xC($t6)
    /* DDFD40 0000F2D4 10000001 */  b          .L0000F2DC
    /* DDFD44 0000F2D8 00000000 */   nop
  .L0000F2DC:
    /* DDFD48 0000F2DC 8FBF0014 */  lw         $ra, 0x14($sp)
    /* DDFD4C 0000F2E0 27BD0028 */  addiu      $sp, $sp, 0x28
    /* DDFD50 0000F2E4 03E00008 */  jr         $ra
    /* DDFD54 0000F2E8 00000000 */   nop
endlabel func_0000F288
