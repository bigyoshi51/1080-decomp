
nonmatching func_80008EA0, 0x30

glabel func_80008EA0
    /* 9EA0 80008EA0 AFB00014 */  sw         $s0, 0x14($sp)
    /* 9EA4 80008EA4 8FB000D8 */  lw         $s0, 0xD8($sp)
    /* 9EA8 80008EA8 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 9EAC 80008EAC AFB10018 */  sw         $s1, 0x18($sp)
    /* 9EB0 80008EB0 8E0E000C */  lw         $t6, 0xC($s0)
    /* 9EB4 80008EB4 AFAE003C */  sw         $t6, 0x3C($sp)
    /* 9EB8 80008EB8 920F0004 */  lbu        $t7, 0x4($s0)
    /* 9EBC 80008EBC A7A00036 */  sh         $zero, 0x36($sp)
    /* 9EC0 80008EC0 A3AF0034 */  sb         $t7, 0x34($sp)
    /* 9EC4 80008EC4 92180009 */  lbu        $t8, 0x9($s0)
    /* 9EC8 80008EC8 1700003E */  bnez       $t8, .L80008FC4
    /* 9ECC 80008ECC 00000000 */   nop
endlabel func_80008EA0
