
nonmatching func_8000898C, 0x7C

glabel func_8000898C
    /* 998C 8000898C 8FAF0074 */  lw         $t7, 0x74($sp)
    /* 9990 80008990 2401000F */  addiu      $at, $zero, 0xF
    /* 9994 80008994 15E10005 */  bne        $t7, $at, .L800089AC
    /* 9998 80008998 00000000 */   nop
    /* 999C 8000899C 24180001 */  addiu      $t8, $zero, 0x1
    /* 99A0 800089A0 24190002 */  addiu      $t9, $zero, 0x2
    /* 99A4 800089A4 A7B80048 */  sh         $t8, 0x48($sp)
    /* 99A8 800089A8 A7B9004A */  sh         $t9, 0x4A($sp)
  .L800089AC:
    /* 99AC 800089AC 8FA80074 */  lw         $t0, 0x74($sp)
    /* 99B0 800089B0 29010010 */  slti       $at, $t0, 0x10
    /* 99B4 800089B4 10200003 */  beqz       $at, .L800089C4
    /* 99B8 800089B8 00000000 */   nop
    /* 99BC 800089BC 10000004 */  b          .L800089D0
    /* 99C0 800089C0 AFA00074 */   sw        $zero, 0x74($sp)
  .L800089C4:
    /* 99C4 800089C4 8FA90074 */  lw         $t1, 0x74($sp)
    /* 99C8 800089C8 252AFFF0 */  addiu      $t2, $t1, -0x10
    /* 99CC 800089CC AFAA0074 */  sw         $t2, 0x74($sp)
  .L800089D0:
    /* 99D0 800089D0 8FAB0074 */  lw         $t3, 0x74($sp)
    /* 99D4 800089D4 11600003 */  beqz       $t3, .L800089E4
    /* 99D8 800089D8 00000000 */   nop
    /* 99DC 800089DC 240C000D */  addiu      $t4, $zero, 0xD
    /* 99E0 800089E0 AFAC0040 */  sw         $t4, 0x40($sp)
  .L800089E4:
    /* 99E4 800089E4 27A40024 */  addiu      $a0, $sp, 0x24
    /* 99E8 800089E8 2405004C */  addiu      $a1, $zero, 0x4C
    /* 99EC 800089EC 0C001CFE */  jal        func_800073F8
    /* 99F0 800089F0 24060002 */   addiu     $a2, $zero, 0x2
    /* 99F4 800089F4 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 99F8 800089F8 8FB00018 */  lw         $s0, 0x18($sp)
    /* 99FC 800089FC 27BD0070 */  addiu      $sp, $sp, 0x70
    /* 9A00 80008A00 03E00008 */  jr         $ra
    /* 9A04 80008A04 00000000 */   nop
endlabel func_8000898C
