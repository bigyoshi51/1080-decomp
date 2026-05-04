nonmatching func_00002420, 0x98

glabel func_00002420
    /* DD2E8C 00002420 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* DD2E90 00002424 AFBF0014 */  sw         $ra, 0x14($sp)
    /* DD2E94 00002428 AFA5001C */  sw         $a1, 0x1C($sp)
    /* DD2E98 0000242C AFA60020 */  sw         $a2, 0x20($sp)
    /* DD2E9C 00002430 14800005 */  bnez       $a0, .L00002448
    /* DD2EA0 00002434 AFA70024 */   sw        $a3, 0x24($sp)
    /* DD2EA4 00002438 0C000000 */  jal        func_00000000
    /* DD2EA8 0000243C 24040050 */   addiu     $a0, $zero, 0x50
    /* DD2EAC 00002440 10400018 */  beqz       $v0, .L000024A4
    /* DD2EB0 00002444 00402025 */   or        $a0, $v0, $zero
  .L00002448:
    /* DD2EB4 00002448 3C050000 */  lui        $a1, %hi(D_0000731C)
    /* DD2EB8 0000244C 24A5731C */  addiu      $a1, $a1, %lo(D_0000731C)
    /* DD2EBC 00002450 0C000000 */  jal        func_00000000
    /* DD2EC0 00002454 AFA40018 */   sw        $a0, 0x18($sp)
    /* DD2EC4 00002458 8FA40018 */  lw         $a0, 0x18($sp)
    /* DD2EC8 0000245C 3C0E0000 */  lui        $t6, (0x0 >> 16)
    /* DD2ECC 00002460 25CE0000 */  addiu      $t6, $t6, 0x0
    /* DD2ED0 00002464 AC8E0028 */  sw         $t6, 0x28($a0)
    /* DD2ED4 00002468 8FAF001C */  lw         $t7, 0x1C($sp)
    /* DD2ED8 0000246C 240A2710 */  addiu      $t2, $zero, 0x2710
    /* DD2EDC 00002470 AC8F0038 */  sw         $t7, 0x38($a0)
    /* DD2EE0 00002474 8FB80020 */  lw         $t8, 0x20($sp)
    /* DD2EE4 00002478 AC980040 */  sw         $t8, 0x40($a0)
    /* DD2EE8 0000247C 8FB90024 */  lw         $t9, 0x24($sp)
    /* DD2EEC 00002480 AC99002C */  sw         $t9, 0x2C($a0)
    /* DD2EF0 00002484 8FA80028 */  lw         $t0, 0x28($sp)
    /* DD2EF4 00002488 AC880030 */  sw         $t0, 0x30($a0)
    /* DD2EF8 0000248C 8FA9002C */  lw         $t1, 0x2C($sp)
    /* DD2EFC 00002490 AC80003C */  sw         $zero, 0x3C($a0)
    /* DD2F00 00002494 AC800044 */  sw         $zero, 0x44($a0)
    /* DD2F04 00002498 AC8A0048 */  sw         $t2, 0x48($a0)
    /* DD2F08 0000249C AC80004C */  sw         $zero, 0x4C($a0)
    /* DD2F0C 000024A0 AC890034 */  sw         $t1, 0x34($a0)
  .L000024A4:
    /* DD2F10 000024A4 8FBF0014 */  lw         $ra, 0x14($sp)
    /* DD2F14 000024A8 27BD0018 */  addiu      $sp, $sp, 0x18
    /* DD2F18 000024AC 00801025 */  or         $v0, $a0, $zero
    /* DD2F1C 000024B0 03E00008 */  jr         $ra
    /* DD2F20 000024B4 00000000 */   nop
endlabel func_00002420
