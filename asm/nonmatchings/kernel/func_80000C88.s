
nonmatching func_80000C88, 0x164

glabel func_80000C88
    /* 1C88 80000C88 3C028001 */  lui        $v0, %hi(D_80012C68)
    /* 1C8C 80000C8C 8C422C68 */  lw         $v0, %lo(D_80012C68)($v0)
    /* 1C90 80000C90 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 1C94 80000C94 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 1C98 80000C98 04410003 */  bgez       $v0, .L80000CA8
    /* 1C9C 80000C9C 00027080 */   sll       $t6, $v0, 2
    /* 1CA0 80000CA0 1000001E */  b          .L80000D1C
    /* 1CA4 80000CA4 2402FFFF */   addiu     $v0, $zero, -0x1
  .L80000CA8:
    /* 1CA8 80000CA8 3C038001 */  lui        $v1, %hi(D_80012D60)
    /* 1CAC 80000CAC 006E1821 */  addu       $v1, $v1, $t6
    /* 1CB0 80000CB0 8C632D60 */  lw         $v1, %lo(D_80012D60)($v1)
    /* 1CB4 80000CB4 3C058001 */  lui        $a1, %hi(D_80012C64)
    /* 1CB8 80000CB8 14600003 */  bnez       $v1, .L80000CC8
    /* 1CBC 80000CBC 00000000 */   nop
    /* 1CC0 80000CC0 10000016 */  b          .L80000D1C
    /* 1CC4 80000CC4 2402FFFF */   addiu     $v0, $zero, -0x1
  .L80000CC8:
    /* 1CC8 80000CC8 8CA52C64 */  lw         $a1, %lo(D_80012C64)($a1)
    /* 1CCC 80000CCC 04A30004 */  bgezl      $a1, .L80000CE0
    /* 1CD0 80000CD0 8C66003C */   lw        $a2, 0x3C($v1)
    /* 1CD4 80000CD4 10000011 */  b          .L80000D1C
    /* 1CD8 80000CD8 2402FFFF */   addiu     $v0, $zero, -0x1
    /* 1CDC 80000CDC 8C66003C */  lw         $a2, 0x3C($v1)
  .L80000CE0:
    /* 1CE0 80000CE0 00057880 */  sll        $t7, $a1, 2
    /* 1CE4 80000CE4 01E57823 */  subu       $t7, $t7, $a1
    /* 1CE8 80000CE8 14C00003 */  bnez       $a2, .L80000CF8
    /* 1CEC 80000CEC 000F7880 */   sll       $t7, $t7, 2
  alabel D_80000CF0
    /* 1CF0 80000CF0 1000000A */  b          .L80000D1C
    /* 1CF4 80000CF4 2402FFFF */   addiu     $v0, $zero, -0x1
  .L80000CF8:
    /* 1CF8 80000CF8 00CFC021 */  addu       $t8, $a2, $t7
    /* 1CFC 80000CFC 8F020004 */  lw         $v0, 0x4($t8)
    /* 1D00 80000D00 3C048001 */  lui        $a0, %hi(D_80012BC0)
    /* 1D04 80000D04 24842BC0 */  addiu      $a0, $a0, %lo(D_80012BC0)
    /* 1D08 80000D08 0040F809 */  jalr       $v0
    /* 1D0C 80000D0C 00000000 */   nop
    /* 1D10 80000D10 3C018001 */  lui        $at, %hi(D_80012BE4)
    /* 1D14 80000D14 AC222BE4 */  sw         $v0, %lo(D_80012BE4)($at)
    /* 1D18 80000D18 00001025 */  or         $v0, $zero, $zero
  .L80000D1C:
    /* 1D1C 80000D1C 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 1D20 80000D20 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 1D24 80000D24 03E00008 */  jr         $ra
    /* 1D28 80000D28 00000000 */   nop
/* glabel func_80000D2C */
    /* 1D2C 80000D2C 3C0F8001 */  lui        $t7, %hi(D_80012D60)
    /* 1D30 80000D30 27BDFF70 */  addiu      $sp, $sp, -0x90
    /* 1D34 80000D34 25EF2D60 */  addiu      $t7, $t7, %lo(D_80012D60)
    /* 1D38 80000D38 00057080 */  sll        $t6, $a1, 2
    /* 1D3C 80000D3C 01CF3021 */  addu       $a2, $t6, $t7
    /* 1D40 80000D40 8CC70000 */  lw         $a3, 0x0($a2)
    /* 1D44 80000D44 AFB30020 */  sw         $s3, 0x20($sp)
    /* 1D48 80000D48 AFB2001C */  sw         $s2, 0x1C($sp)
    /* 1D4C 80000D4C 3C138001 */  lui        $s3, %hi(D_8000A2E0)
    /* 1D50 80000D50 00A09025 */  or         $s2, $a1, $zero
    /* 1D54 80000D54 AFBF0024 */  sw         $ra, 0x24($sp)
    /* 1D58 80000D58 AFB10018 */  sw         $s1, 0x18($sp)
    /* 1D5C 80000D5C AFB00014 */  sw         $s0, 0x14($sp)
    /* 1D60 80000D60 AFA40090 */  sw         $a0, 0x90($sp)
    /* 1D64 80000D64 10E0000F */  beqz       $a3, .L80000DA4
    /* 1D68 80000D68 8E73A2E0 */   lw        $s3, %lo(D_8000A2E0)($s3)
    /* 1D6C 80000D6C 90E20072 */  lbu        $v0, 0x72($a3)
    /* 1D70 80000D70 00001825 */  or         $v1, $zero, $zero
    /* 1D74 80000D74 10400009 */  beqz       $v0, .L80000D9C
    /* 1D78 80000D78 A0820000 */   sb        $v0, 0x0($a0)
    /* 1D7C 80000D7C 8FA40090 */  lw         $a0, 0x90($sp)
  .L80000D80:
    /* 1D80 80000D80 8CD90000 */  lw         $t9, 0x0($a2)
    /* 1D84 80000D84 24630001 */  addiu      $v1, $v1, 0x1
    /* 1D88 80000D88 24840001 */  addiu      $a0, $a0, 0x1
    /* 1D8C 80000D8C 03234021 */  addu       $t0, $t9, $v1
    /* 1D90 80000D90 91020072 */  lbu        $v0, 0x72($t0)
    /* 1D94 80000D94 1440FFFA */  bnez       $v0, .L80000D80
    /* 1D98 80000D98 A0820000 */   sb        $v0, 0x0($a0)
  .L80000D9C:
    /* 1D9C 80000D9C 10000027 */  b          .L80000E3C
    /* 1DA0 80000DA0 24020002 */   addiu     $v0, $zero, 0x2
  .L80000DA4:
    /* 1DA4 80000DA4 8E690000 */  lw         $t1, 0x0($s3)
    /* 1DA8 80000DA8 27B10038 */  addiu      $s1, $sp, 0x38
    /* 1DAC 80000DAC 27B00064 */  addiu      $s0, $sp, 0x64
    /* 1DB0 80000DB0 11200021 */  beqz       $t1, .L80000E38
    /* 1DB4 80000DB4 02002025 */   or        $a0, $s0, $zero
  .L80000DB8:
    /* 1DB8 80000DB8 0C000220 */  jal        func_80000880
    /* 1DBC 80000DBC 02602825 */   or        $a1, $s3, $zero
    /* 1DC0 80000DC0 02002025 */  or         $a0, $s0, $zero
    /* 1DC4 80000DC4 0C0002A6 */  jal        func_80000A98
    /* 1DC8 80000DC8 02202825 */   or        $a1, $s1, $zero
    /* 1DCC 80000DCC 10400014 */  beqz       $v0, .L80000E20
    /* 1DD0 80000DD0 00000000 */   nop
    /* 1DD4 80000DD4 8FAA003C */  lw         $t2, 0x3C($sp)
  .L80000DD8:
    /* 1DD8 80000DD8 15520006 */  bne        $t2, $s2, .L80000DF4
    /* 1DDC 80000DDC 00000000 */   nop
    /* 1DE0 80000DE0 8FA40090 */  lw         $a0, 0x90($sp)
    /* 1DE4 80000DE4 0C000177 */  jal        func_800005DC
    /* 1DE8 80000DE8 27A50044 */   addiu     $a1, $sp, 0x44
endlabel func_80000C88
