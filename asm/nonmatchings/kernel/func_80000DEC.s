
nonmatching func_80000DEC, 0x6C

glabel func_80000DEC
    /* 1DEC 80000DEC 10000013 */  b          .L80000E3C
    /* 1DF0 80000DF0 24020001 */   addiu     $v0, $zero, 0x1
  .L80000DF4:
    /* 1DF4 80000DF4 0C0002CD */  jal        func_80000B34
    /* 1DF8 80000DF8 02002025 */   or        $a0, $s0, $zero
    /* 1DFC 80000DFC 04410004 */  bgez       $v0, .L80000E10
    /* 1E00 80000E00 02002025 */   or        $a0, $s0, $zero
    /* 1E04 80000E04 3C028001 */  lui        $v0, %hi(D_80013004)
    /* 1E08 80000E08 1000000C */  b          .L80000E3C
    /* 1E0C 80000E0C 8C423004 */   lw        $v0, %lo(D_80013004)($v0)
  .L80000E10:
    /* 1E10 80000E10 0C0002A6 */  jal        func_80000A98
    /* 1E14 80000E14 02202825 */   or        $a1, $s1, $zero
    /* 1E18 80000E18 5440FFEF */  bnel       $v0, $zero, .L80000DD8
    /* 1E1C 80000E1C 8FAA003C */   lw        $t2, 0x3C($sp)
  .L80000E20:
    /* 1E20 80000E20 0C000263 */  jal        func_8000098C
    /* 1E24 80000E24 02002025 */   or        $a0, $s0, $zero
    /* 1E28 80000E28 8E6B0014 */  lw         $t3, 0x14($s3)
    /* 1E2C 80000E2C 26730014 */  addiu      $s3, $s3, 0x14
    /* 1E30 80000E30 5560FFE1 */  bnel       $t3, $zero, .L80000DB8
    /* 1E34 80000E34 02002025 */   or        $a0, $s0, $zero
  .L80000E38:
    /* 1E38 80000E38 00001025 */  or         $v0, $zero, $zero
  .L80000E3C:
    /* 1E3C 80000E3C 8FBF0024 */  lw         $ra, 0x24($sp)
    /* 1E40 80000E40 8FB00014 */  lw         $s0, 0x14($sp)
    /* 1E44 80000E44 8FB10018 */  lw         $s1, 0x18($sp)
    /* 1E48 80000E48 8FB2001C */  lw         $s2, 0x1C($sp)
    /* 1E4C 80000E4C 8FB30020 */  lw         $s3, 0x20($sp)
    /* 1E50 80000E50 03E00008 */  jr         $ra
    /* 1E54 80000E54 27BD0090 */   addiu     $sp, $sp, 0x90
endlabel func_80000DEC
