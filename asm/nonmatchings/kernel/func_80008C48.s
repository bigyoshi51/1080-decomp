
nonmatching func_80008C48, 0x6C

glabel func_80008C48
    /* 9C48 80008C48 AFA0001C */  sw         $zero, 0x1C($sp)
    /* 9C4C 80008C4C 000FC683 */  sra        $t8, $t7, 26
    /* 9C50 80008C50 83A9001C */  lb         $t1, 0x1C($sp)
    /* 9C54 80008C54 0018C880 */  sll        $t9, $t8, 2
    /* 9C58 80008C58 83B8001D */  lb         $t8, 0x1D($sp)
    /* 9C5C 80008C5C 000C6EC0 */  sll        $t5, $t4, 27
    /* 9C60 80008C60 332800FC */  andi       $t0, $t9, 0xFC
    /* 9C64 80008C64 000D76C3 */  sra        $t6, $t5, 27
    /* 9C68 80008C68 312AFF03 */  andi       $t2, $t1, 0xFF03
    /* 9C6C 80008C6C 31CF001F */  andi       $t7, $t6, 0x1F
    /* 9C70 80008C70 3319FFE0 */  andi       $t9, $t8, 0xFFE0
    /* 9C74 80008C74 010A5825 */  or         $t3, $t0, $t2
    /* 9C78 80008C78 01F94825 */  or         $t1, $t7, $t9
    /* 9C7C 80008C7C AFBF0014 */  sw         $ra, 0x14($sp)
    /* 9C80 80008C80 A3AB001C */  sb         $t3, 0x1C($sp)
    /* 9C84 80008C84 A3A9001D */  sb         $t1, 0x1D($sp)
    /* 9C88 80008C88 3C040400 */  lui        $a0, (0x4001000 >> 16)
    /* 9C8C 80008C8C 34841000 */  ori        $a0, $a0, (0x4001000 & 0xFFFF)
    /* 9C90 80008C90 0C001A94 */  jal        func_80006A50
    /* 9C94 80008C94 8FA5001C */   lw        $a1, 0x1C($sp)
    /* 9C98 80008C98 3C040408 */  lui        $a0, (0x4080000 >> 16)
    /* 9C9C 80008C9C 0C001A94 */  jal        func_80006A50
    /* 9CA0 80008CA0 00002825 */   or        $a1, $zero, $zero
    /* 9CA4 80008CA4 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 9CA8 80008CA8 27BD0020 */  addiu      $sp, $sp, 0x20
    /* 9CAC 80008CAC 03E00008 */  jr         $ra
    /* 9CB0 80008CB0 00000000 */   nop
endlabel func_80008C48
