
nonmatching func_80005184, 0x6C

glabel func_80005184
    /* 6184 80005184 27BDFFD0 */  addiu      $sp, $sp, -0x30
    /* 6188 80005188 27AE0030 */  addiu      $t6, $sp, 0x30
    /* 618C 8000518C AFBF001C */  sw         $ra, 0x1C($sp)
    /* 6190 80005190 AFA40030 */  sw         $a0, 0x30($sp)
    /* 6194 80005194 AFB00018 */  sw         $s0, 0x18($sp)
    /* 6198 80005198 AFA0002C */  sw         $zero, 0x2C($sp)
    /* 619C 8000519C AFAE0028 */  sw         $t6, 0x28($sp)
  .L800051A0:
    /* 61A0 800051A0 8FB8002C */  lw         $t8, 0x2C($sp)
    /* 61A4 800051A4 8FAF0028 */  lw         $t7, 0x28($sp)
    /* 61A8 800051A8 24190004 */  addiu      $t9, $zero, 0x4
    /* 61AC 800051AC 24060008 */  addiu      $a2, $zero, 0x8
    /* 61B0 800051B0 03382823 */  subu       $a1, $t9, $t8
    /* 61B4 800051B4 0C0019BC */  jal        func_800066F0
    /* 61B8 800051B8 01F82021 */   addu      $a0, $t7, $t8
    /* 61BC 800051BC 8FA8002C */  lw         $t0, 0x2C($sp)
    /* 61C0 800051C0 00408025 */  or         $s0, $v0, $zero
    /* 61C4 800051C4 01104821 */  addu       $t1, $t0, $s0
    /* 61C8 800051C8 AFA9002C */  sw         $t1, 0x2C($sp)
    /* 61CC 800051CC 8FAA002C */  lw         $t2, 0x2C($sp)
    /* 61D0 800051D0 29410004 */  slti       $at, $t2, 0x4
    /* 61D4 800051D4 1420FFF2 */  bnez       $at, .L800051A0
    /* 61D8 800051D8 00000000 */   nop
    /* 61DC 800051DC 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 61E0 800051E0 8FB00018 */  lw         $s0, 0x18($sp)
    /* 61E4 800051E4 27BD0030 */  addiu      $sp, $sp, 0x30
    /* 61E8 800051E8 03E00008 */  jr         $ra
    /* 61EC 800051EC 00000000 */   nop
endlabel func_80005184
