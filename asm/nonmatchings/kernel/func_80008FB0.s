
nonmatching func_80008FB0, 0x44

glabel func_80008FB0
    /* 9FB0 80008FB0 8FAE002C */  lw         $t6, 0x2C($sp)
    /* 9FB4 80008FB4 8DCF0118 */  lw         $t7, 0x118($t6)
    /* 9FB8 80008FB8 AF0F00A0 */  sw         $t7, 0xA0($t8)
    /* 9FBC 80008FBC 10000003 */  b          .L80008FCC
    /* 9FC0 80008FC0 AF200010 */   sw        $zero, 0x10($t9)
  .L80008FC4:
    /* 9FC4 80008FC4 10000006 */  b          .L80008FE0
    /* 9FC8 80008FC8 2402FFFE */   addiu     $v0, $zero, -0x2
  .L80008FCC:
    /* 9FCC 80008FCC 27A40030 */  addiu      $a0, $sp, 0x30
    /* 9FD0 80008FD0 240500A4 */  addiu      $a1, $zero, 0xA4
    /* 9FD4 80008FD4 0C001CFE */  jal        func_800073F8
    /* 9FD8 80008FD8 24060001 */   addiu     $a2, $zero, 0x1
    /* 9FDC 80008FDC 00001025 */  or         $v0, $zero, $zero
  .L80008FE0:
    /* 9FE0 80008FE0 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 9FE4 80008FE4 8FB00014 */  lw         $s0, 0x14($sp)
    /* 9FE8 80008FE8 8FB10018 */  lw         $s1, 0x18($sp)
    /* 9FEC 80008FEC 03E00008 */  jr         $ra
    /* 9FF0 80008FF0 27BD00D8 */   addiu     $sp, $sp, 0xD8
endlabel func_80008FB0
