
nonmatching func_800045C0, 0x8C

glabel func_800045C0
    /* 55C0 800045C0 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 55C4 800045C4 AFA40020 */  sw         $a0, 0x20($sp)
    /* 55C8 800045C8 AFA50024 */  sw         $a1, 0x24($sp)
    /* 55CC 800045CC 8FAE0024 */  lw         $t6, 0x24($sp)
    /* 55D0 800045D0 8FB80020 */  lw         $t8, 0x20($sp)
    /* 55D4 800045D4 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 55D8 800045D8 000E7882 */  srl        $t7, $t6, 2
    /* 55DC 800045DC 33190003 */  andi       $t9, $t8, 0x3
    /* 55E0 800045E0 13200005 */  beqz       $t9, .L800045F8
    /* 55E4 800045E4 AFAF0024 */   sw        $t7, 0x24($sp)
    /* 55E8 800045E8 27280004 */  addiu      $t0, $t9, 0x4
    /* 55EC 800045EC 25E9FFFF */  addiu      $t1, $t7, -0x1
    /* 55F0 800045F0 AFA80020 */  sw         $t0, 0x20($sp)
    /* 55F4 800045F4 AFA90024 */  sw         $t1, 0x24($sp)
  .L800045F8:
    /* 55F8 800045F8 0C0019AC */  jal        func_800066B0
    /* 55FC 800045FC 00000000 */   nop
    /* 5600 80004600 8FAA0020 */  lw         $t2, 0x20($sp)
    /* 5604 80004604 8FAB0024 */  lw         $t3, 0x24($sp)
    /* 5608 80004608 3C018002 */  lui        $at, %hi(__osRdb_IP6_Data)
    /* 560C 8000460C AC2A9300 */  sw         $t2, %lo(__osRdb_IP6_Data)($at)
    /* 5610 80004610 3C018002 */  lui        $at, %hi(__osRdb_IP6_Size)
    /* 5614 80004614 AC2B9304 */  sw         $t3, %lo(__osRdb_IP6_Size)($at)
    /* 5618 80004618 3C018002 */  lui        $at, %hi(__osRdb_IP6_Ct)
    /* 561C 8000461C AC209308 */  sw         $zero, %lo(__osRdb_IP6_Ct)($at)
    /* 5620 80004620 3C018002 */  lui        $at, %hi(__osRdb_IP6_CurWrite)
    /* 5624 80004624 AC20930C */  sw         $zero, %lo(__osRdb_IP6_CurWrite)($at)
    /* 5628 80004628 AFA2001C */  sw         $v0, 0x1C($sp)
    /* 562C 8000462C 3C018002 */  lui        $at, %hi(__osRdb_IP6_CurSend)
    /* 5630 80004630 AC209310 */  sw         $zero, %lo(__osRdb_IP6_CurSend)($at)
    /* 5634 80004634 0C0019B4 */  jal        func_800066D0
    /* 5638 80004638 8FA4001C */   lw        $a0, 0x1C($sp)
    /* 563C 8000463C 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 5640 80004640 27BD0020 */  addiu      $sp, $sp, 0x20
    /* 5644 80004644 03E00008 */  jr         $ra
    /* 5648 80004648 00000000 */   nop
endlabel func_800045C0
    /* 564C 8000464C 00000000 */  nop
