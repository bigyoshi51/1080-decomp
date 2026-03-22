
nonmatching func_80005C60, 0x34

glabel func_80005C60
    /* 6C60 80005C60 27BDFFB8 */  addiu      $sp, $sp, -0x48
    /* 6C64 80005C64 AFA40048 */  sw         $a0, 0x48($sp)
    /* 6C68 80005C68 8FAE0048 */  lw         $t6, 0x48($sp)
    /* 6C6C 80005C6C AFBF001C */  sw         $ra, 0x1C($sp)
    /* 6C70 80005C70 AFA00030 */  sw         $zero, 0x30($sp)
    /* 6C74 80005C74 AFA00044 */  sw         $zero, 0x44($sp)
    /* 6C78 80005C78 AFA00038 */  sw         $zero, 0x38($sp)
    /* 6C7C 80005C7C AFAE0034 */  sw         $t6, 0x34($sp)
  .L80005C80:
    /* 6C80 80005C80 8FAF0034 */  lw         $t7, 0x34($sp)
    /* 6C84 80005C84 27A50044 */  addiu      $a1, $sp, 0x44
    /* 6C88 80005C88 24060001 */  addiu      $a2, $zero, 0x1
    /* 6C8C 80005C8C 0C0013F8 */  jal        func_80004FE0
    /* 6C90 80005C90 8DE40008 */   lw        $a0, 0x8($t7)
endlabel func_80005C60
