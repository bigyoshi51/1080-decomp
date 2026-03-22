
nonmatching func_80002CD0, 0x9C

glabel func_80002CD0
    /* 3CD0 80002CD0 28A1000C */  slti       $at, $a1, 0xC
    /* 3CD4 80002CD4 1420001D */  bnez       $at, .L80002D4C
    /* 3CD8 80002CD8 00041823 */   negu      $v1, $a0
    /* 3CDC 80002CDC 30630003 */  andi       $v1, $v1, 0x3
    /* 3CE0 80002CE0 10600003 */  beqz       $v1, .L80002CF0
    /* 3CE4 80002CE4 00A32823 */   subu      $a1, $a1, $v1
    /* 3CE8 80002CE8 A8800000 */  swl        $zero, 0x0($a0)
    /* 3CEC 80002CEC 00832021 */  addu       $a0, $a0, $v1
  .L80002CF0:
    /* 3CF0 80002CF0 2401FFE0 */  addiu      $at, $zero, -0x20
    /* 3CF4 80002CF4 00A13824 */  and        $a3, $a1, $at
    /* 3CF8 80002CF8 10E0000C */  beqz       $a3, .L80002D2C
    /* 3CFC 80002CFC 00A72823 */   subu      $a1, $a1, $a3
    /* 3D00 80002D00 00E43821 */  addu       $a3, $a3, $a0
  .L80002D04:
    /* 3D04 80002D04 24840020 */  addiu      $a0, $a0, 0x20
    /* 3D08 80002D08 AC80FFE0 */  sw         $zero, -0x20($a0)
    /* 3D0C 80002D0C AC80FFE4 */  sw         $zero, -0x1C($a0)
    /* 3D10 80002D10 AC80FFE8 */  sw         $zero, -0x18($a0)
    /* 3D14 80002D14 AC80FFEC */  sw         $zero, -0x14($a0)
    /* 3D18 80002D18 AC80FFF0 */  sw         $zero, -0x10($a0)
    /* 3D1C 80002D1C AC80FFF4 */  sw         $zero, -0xC($a0)
    /* 3D20 80002D20 AC80FFF8 */  sw         $zero, -0x8($a0)
    /* 3D24 80002D24 1487FFF7 */  bne        $a0, $a3, .L80002D04
    /* 3D28 80002D28 AC80FFFC */   sw        $zero, -0x4($a0)
  .L80002D2C:
    /* 3D2C 80002D2C 2401FFFC */  addiu      $at, $zero, -0x4
    /* 3D30 80002D30 00A13824 */  and        $a3, $a1, $at
    /* 3D34 80002D34 10E00005 */  beqz       $a3, .L80002D4C
    /* 3D38 80002D38 00A72823 */   subu      $a1, $a1, $a3
    /* 3D3C 80002D3C 00E43821 */  addu       $a3, $a3, $a0
  .L80002D40:
    /* 3D40 80002D40 24840004 */  addiu      $a0, $a0, 0x4
    /* 3D44 80002D44 1487FFFE */  bne        $a0, $a3, .L80002D40
    /* 3D48 80002D48 AC80FFFC */   sw        $zero, -0x4($a0)
  .L80002D4C:
    /* 3D4C 80002D4C 18A00005 */  blez       $a1, .L80002D64
    /* 3D50 80002D50 00000000 */   nop
    /* 3D54 80002D54 00A42821 */  addu       $a1, $a1, $a0
  .L80002D58:
    /* 3D58 80002D58 24840001 */  addiu      $a0, $a0, 0x1
    /* 3D5C 80002D5C 1485FFFE */  bne        $a0, $a1, .L80002D58
    /* 3D60 80002D60 A080FFFF */   sb        $zero, -0x1($a0)
  .L80002D64:
    /* 3D64 80002D64 03E00008 */  jr         $ra
    /* 3D68 80002D68 00000000 */   nop
endlabel func_80002CD0
    /* 3D6C 80002D6C 00000000 */  nop
    /* 3D70 80002D70 00000000 */  nop
    /* 3D74 80002D74 00000000 */  nop
    /* 3D78 80002D78 00000000 */  nop
    /* 3D7C 80002D7C 00000000 */  nop
    /* 3D80 80002D80 00000000 */  nop
    /* 3D84 80002D84 00000000 */  nop
    /* 3D88 80002D88 00000000 */  nop
    /* 3D8C 80002D8C 00000000 */  nop
    /* 3D90 80002D90 00000000 */  nop
    /* 3D94 80002D94 00000000 */  nop
    /* 3D98 80002D98 00000000 */  nop
    /* 3D9C 80002D9C 00000000 */  nop
    /* 3DA0 80002DA0 00000000 */  nop
    /* 3DA4 80002DA4 00000000 */  nop
    /* 3DA8 80002DA8 00000000 */  nop
    /* 3DAC 80002DAC 00000000 */  nop
