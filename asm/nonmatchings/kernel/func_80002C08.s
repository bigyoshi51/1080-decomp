
nonmatching func_80002C08, 0x9C

glabel func_80002C08
    /* 3C08 80002C08 27BDFFF8 */  addiu      $sp, $sp, -0x8
    /* 3C0C 80002C0C AFA40008 */  sw         $a0, 0x8($sp)
    /* 3C10 80002C10 AFA5000C */  sw         $a1, 0xC($sp)
    /* 3C14 80002C14 AFA60010 */  sw         $a2, 0x10($sp)
    /* 3C18 80002C18 AFA70014 */  sw         $a3, 0x14($sp)
    /* 3C1C 80002C1C DFAF0010 */  ld         $t7, 0x10($sp)
    /* 3C20 80002C20 DFAE0008 */  ld         $t6, 0x8($sp)
    /* 3C24 80002C24 01CF001E */  ddiv       $zero, $t6, $t7
    /* 3C28 80002C28 00000000 */  nop
    /* 3C2C 80002C2C 15E00002 */  bnez       $t7, .L80002C38
    /* 3C30 80002C30 00000000 */   nop
    /* 3C34 80002C34 0007000D */  break      7
  .L80002C38:
    /* 3C38 80002C38 6401FFFF */  daddiu     $at, $zero, -0x1
    /* 3C3C 80002C3C 15E10005 */  bne        $t7, $at, .L80002C54
    /* 3C40 80002C40 64010001 */   daddiu    $at, $zero, 0x1
    /* 3C44 80002C44 00010FFC */  dsll32     $at, $at, 31
    /* 3C48 80002C48 15C10002 */  bne        $t6, $at, .L80002C54
    /* 3C4C 80002C4C 00000000 */   nop
    /* 3C50 80002C50 0006000D */  break      6
  .L80002C54:
    /* 3C54 80002C54 0000C010 */  mfhi       $t8
    /* 3C58 80002C58 FFB80000 */  sd         $t8, 0x0($sp)
    /* 3C5C 80002C5C 07010003 */  bgez       $t8, .L80002C6C
    /* 3C60 80002C60 00000000 */   nop
    /* 3C64 80002C64 1DE00007 */  bgtz       $t7, .L80002C84
    /* 3C68 80002C68 00000000 */   nop
  .L80002C6C:
    /* 3C6C 80002C6C DFB90000 */  ld         $t9, 0x0($sp)
    /* 3C70 80002C70 1B200008 */  blez       $t9, .L80002C94
    /* 3C74 80002C74 00000000 */   nop
    /* 3C78 80002C78 DFA80010 */  ld         $t0, 0x10($sp)
    /* 3C7C 80002C7C 05010005 */  bgez       $t0, .L80002C94
    /* 3C80 80002C80 00000000 */   nop
  .L80002C84:
    /* 3C84 80002C84 DFA90000 */  ld         $t1, 0x0($sp)
    /* 3C88 80002C88 DFAA0010 */  ld         $t2, 0x10($sp)
    /* 3C8C 80002C8C 012A582D */  daddu      $t3, $t1, $t2
    /* 3C90 80002C90 FFAB0000 */  sd         $t3, 0x0($sp)
  .L80002C94:
    /* 3C94 80002C94 8FA20000 */  lw         $v0, 0x0($sp)
    /* 3C98 80002C98 8FA30004 */  lw         $v1, 0x4($sp)
    /* 3C9C 80002C9C 03E00008 */  jr         $ra
    /* 3CA0 80002CA0 27BD0008 */   addiu     $sp, $sp, 0x8
endlabel func_80002C08
