
nonmatching func_80006F60, 0x98

glabel func_80006F60
    /* 7F60 80006F60 27BDFFD0 */  addiu      $sp, $sp, -0x30
    /* 7F64 80006F64 AFA40030 */  sw         $a0, 0x30($sp)
    /* 7F68 80006F68 8FAE0030 */  lw         $t6, 0x30($sp)
    /* 7F6C 80006F6C AFBF001C */  sw         $ra, 0x1C($sp)
    /* 7F70 80006F70 AFA50034 */  sw         $a1, 0x34($sp)
    /* 7F74 80006F74 AFA60038 */  sw         $a2, 0x38($sp)
    /* 7F78 80006F78 AFB00018 */  sw         $s0, 0x18($sp)
    /* 7F7C 80006F7C 240F0002 */  addiu      $t7, $zero, 0x2
    /* 7F80 80006F80 AFAE0028 */  sw         $t6, 0x28($sp)
    /* 7F84 80006F84 A1CF0008 */  sb         $t7, 0x8($t6)
    /* 7F88 80006F88 8FB90030 */  lw         $t9, 0x30($sp)
    /* 7F8C 80006F8C 8FB80038 */  lw         $t8, 0x38($sp)
    /* 7F90 80006F90 A3380005 */  sb         $t8, 0x5($t9)
    /* 7F94 80006F94 8FA80034 */  lw         $t0, 0x34($sp)
    /* 7F98 80006F98 AFA0002C */  sw         $zero, 0x2C($sp)
    /* 7F9C 80006F9C 11000011 */  beqz       $t0, .L80006FE4
    /* 7FA0 80006FA0 00000000 */   nop
  .L80006FA4:
    /* 7FA4 80006FA4 8FAA002C */  lw         $t2, 0x2C($sp)
    /* 7FA8 80006FA8 8FA90028 */  lw         $t1, 0x28($sp)
    /* 7FAC 80006FAC 8FAB0034 */  lw         $t3, 0x34($sp)
    /* 7FB0 80006FB0 24060008 */  addiu      $a2, $zero, 0x8
    /* 7FB4 80006FB4 012A2021 */  addu       $a0, $t1, $t2
    /* 7FB8 80006FB8 0C0019BC */  jal        func_800066F0
    /* 7FBC 80006FBC 016A2823 */   subu      $a1, $t3, $t2
    /* 7FC0 80006FC0 8FAC002C */  lw         $t4, 0x2C($sp)
    /* 7FC4 80006FC4 00408025 */  or         $s0, $v0, $zero
    /* 7FC8 80006FC8 8FAE0034 */  lw         $t6, 0x34($sp)
    /* 7FCC 80006FCC 01906821 */  addu       $t5, $t4, $s0
    /* 7FD0 80006FD0 AFAD002C */  sw         $t5, 0x2C($sp)
    /* 7FD4 80006FD4 8FAF002C */  lw         $t7, 0x2C($sp)
    /* 7FD8 80006FD8 01EE082B */  sltu       $at, $t7, $t6
    /* 7FDC 80006FDC 1420FFF1 */  bnez       $at, .L80006FA4
    /* 7FE0 80006FE0 00000000 */   nop
  .L80006FE4:
    /* 7FE4 80006FE4 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 7FE8 80006FE8 8FB00018 */  lw         $s0, 0x18($sp)
    /* 7FEC 80006FEC 27BD0030 */  addiu      $sp, $sp, 0x30
    /* 7FF0 80006FF0 03E00008 */  jr         $ra
    /* 7FF4 80006FF4 00000000 */   nop
endlabel func_80006F60
