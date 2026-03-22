
nonmatching func_80004A50, 0x68

glabel func_80004A50
    /* 5A50 80004A50 2DA10009 */  sltiu      $at, $t5, 0x9
    /* 5A54 80004A54 14200014 */  bnez       $at, .L80004AA8
    /* 5A58 80004A58 00000000 */   nop
    /* 5A5C 80004A5C 3C0E8002 */  lui        $t6, %hi(kdebugserver_bss_01B0)
    /* 5A60 80004A60 25CE94D0 */  addiu      $t6, $t6, %lo(kdebugserver_bss_01B0)
    /* 5A64 80004A64 91CF0000 */  lbu        $t7, 0x0($t6)
    /* 5A68 80004A68 24010001 */  addiu      $at, $zero, 0x1
    /* 5A6C 80004A6C 15E1000E */  bne        $t7, $at, .L80004AA8
    /* 5A70 80004A70 00000000 */   nop
    /* 5A74 80004A74 0C0012EC */  jal        func_80004BB0
    /* 5A78 80004A78 25C40001 */   addiu     $a0, $t6, 0x1
    /* 5A7C 80004A7C 3C048002 */  lui        $a0, %hi(kdebugserver_bss_01B0)
    /* 5A80 80004A80 248494D0 */  addiu      $a0, $a0, %lo(kdebugserver_bss_01B0)
    /* 5A84 80004A84 AFA2001C */  sw         $v0, 0x1C($sp)
    /* 5A88 80004A88 0C0012EC */  jal        func_80004BB0
    /* 5A8C 80004A8C 24840005 */   addiu     $a0, $a0, 0x5
    /* 5A90 80004A90 AFA20020 */  sw         $v0, 0x20($sp)
    /* 5A94 80004A94 8FA50020 */  lw         $a1, 0x20($sp)
    /* 5A98 80004A98 0C00133A */  jal        func_80004CE8
    /* 5A9C 80004A9C 8FA4001C */   lw        $a0, 0x1C($sp)
    /* 5AA0 80004AA0 3C018001 */  lui        $at, %hi(D_8000A430)
    /* 5AA4 80004AA4 AC20A430 */  sw         $zero, %lo(D_8000A430)($at)
  .L80004AA8:
    /* 5AA8 80004AA8 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 5AAC 80004AAC 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 5AB0 80004AB0 03E00008 */  jr         $ra
    /* 5AB4 80004AB4 00000000 */   nop
endlabel func_80004A50
    /* 5AB8 80004AB8 00000000 */  nop
    /* 5ABC 80004ABC 00000000 */  nop
