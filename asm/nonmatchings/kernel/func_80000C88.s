
nonmatching func_80000C88, 0xA4

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
endlabel func_80000C88
