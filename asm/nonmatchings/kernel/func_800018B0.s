
nonmatching func_800018B0, 0x40

glabel func_800018B0
    /* 28B0 800018B0 240E0001 */  addiu      $t6, $zero, 0x1
    /* 28B4 800018B4 A08E0099 */  sb         $t6, 0x99($a0)
    /* 28B8 800018B8 AC800038 */  sw         $zero, 0x38($a0)
    /* 28BC 800018BC AC80003C */  sw         $zero, 0x3C($a0)
    /* 28C0 800018C0 24830008 */  addiu      $v1, $a0, 0x8
    /* 28C4 800018C4 2404000E */  addiu      $a0, $zero, 0xE
    /* 28C8 800018C8 24020002 */  addiu      $v0, $zero, 0x2
  .L800018CC:
    /* 28CC 800018CC 24420004 */  addiu      $v0, $v0, 0x4
    /* 28D0 800018D0 AC600038 */  sw         $zero, 0x38($v1)
    /* 28D4 800018D4 AC60003C */  sw         $zero, 0x3C($v1)
    /* 28D8 800018D8 AC600040 */  sw         $zero, 0x40($v1)
    /* 28DC 800018DC AC600044 */  sw         $zero, 0x44($v1)
    /* 28E0 800018E0 1444FFFA */  bne        $v0, $a0, .L800018CC
    /* 28E4 800018E4 24630010 */   addiu     $v1, $v1, 0x10
    /* 28E8 800018E8 03E00008 */  jr         $ra
    /* 28EC 800018EC 00000000 */   nop
endlabel func_800018B0
