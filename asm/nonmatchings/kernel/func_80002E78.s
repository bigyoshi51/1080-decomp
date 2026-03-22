
/* Handwritten function */
nonmatching func_80002E78, 0x100

glabel func_80002E78
    /* 3E78 80002E78 03400008 */  jr         $k0
    /* 3E7C 80002E7C 00000000 */   nop
    /* 3E80 80002E80 AFBAFFF0 */  sw         $k0, -0x10($sp) /* handwritten instruction */
    /* 3E84 80002E84 10000003 */  b          .L80002E94
    /* 3E88 80002E88 3C1A8000 */   lui       $k0, %hi(.L800032A0) /* handwritten instruction */
    /* 3E8C 80002E8C 00000000 */  nop
    /* 3E90 80002E90 00000000 */  nop
  .L80002E94:
    /* 3E94 80002E94 275A32A0 */  addiu      $k0, $k0, %lo(.L800032A0) /* handwritten instruction */
    /* 3E98 80002E98 03400008 */  jr         $k0
    /* 3E9C 80002E9C 00000000 */   nop
    /* 3EA0 80002EA0 401A6800 */  mfc0       $k0, $13 /* handwritten instruction */
    /* 3EA4 80002EA4 335A007C */  andi       $k0, $k0, 0x7C /* handwritten instruction */
    /* 3EA8 80002EA8 17400008 */  bnez       $k0, .L80002ECC /* handwritten instruction */
    /* 3EAC 80002EAC 001AD082 */   srl       $k0, $k0, 2
    /* 3EB0 80002EB0 401A6800 */  mfc0       $k0, $13 /* handwritten instruction */
    /* 3EB4 80002EB4 00000000 */  nop
    /* 3EB8 80002EB8 335A4000 */  andi       $k0, $k0, 0x4000 /* handwritten instruction */
    /* 3EBC 80002EBC 13400021 */  beqz       $k0, .L80002F44 /* handwritten instruction */
    /* 3EC0 80002EC0 00000000 */   nop
    /* 3EC4 80002EC4 08000CBA */  j          .L800032E8
    /* 3EC8 80002EC8 00000000 */   nop
  .L80002ECC:
    /* 3ECC 80002ECC AFBBFFF8 */  sw         $k1, -0x8($sp) /* handwritten instruction */
    /* 3ED0 80002ED0 3C1B8001 */  lui        $k1, %hi(D_8000A744) /* handwritten instruction */
    /* 3ED4 80002ED4 277BA744 */  addiu      $k1, $k1, %lo(D_8000A744) /* handwritten instruction */
    /* 3ED8 80002ED8 037AD820 */  add        $k1, $k1, $k0 /* handwritten instruction */
    /* 3EDC 80002EDC 937A0000 */  lbu        $k0, 0x0($k1) /* handwritten instruction */
    /* 3EE0 80002EE0 13400018 */  beqz       $k0, .L80002F44 /* handwritten instruction */
    /* 3EE4 80002EE4 00000000 */   nop
  .L80002EE8:
    /* 3EE8 80002EE8 3C1AA460 */  lui        $k0, %hi(D_A4600010) /* handwritten instruction */
    /* 3EEC 80002EEC 8F5A0010 */  lw         $k0, %lo(D_A4600010)($k0) /* handwritten instruction */
    /* 3EF0 80002EF0 00000000 */  nop
    /* 3EF4 80002EF4 335A0003 */  andi       $k0, $k0, 0x3 /* handwritten instruction */
    /* 3EF8 80002EF8 1740FFFB */  bnez       $k0, .L80002EE8 /* handwritten instruction */
    /* 3EFC 80002EFC 00000000 */   nop
    /* 3F00 80002F00 3C1ABFF1 */  lui        $k0, %hi(D_BFF08004) /* handwritten instruction */
    /* 3F04 80002F04 8F5A8004 */  lw         $k0, %lo(D_BFF08004)($k0) /* handwritten instruction */
    /* 3F08 80002F08 00000000 */  nop
    /* 3F0C 80002F0C 335A0008 */  andi       $k0, $k0, 0x8 /* handwritten instruction */
    /* 3F10 80002F10 17400005 */  bnez       $k0, .L80002F28 /* handwritten instruction */
    /* 3F14 80002F14 3C1ABFF0 */   lui       $k0, (0xBFF00014 >> 16) /* handwritten instruction */
    /* 3F18 80002F18 375A0014 */  ori        $k0, $k0, (0xBFF00014 & 0xFFFF) /* handwritten instruction */
    /* 3F1C 80002F1C 8FBBFFF8 */  lw         $k1, -0x8($sp) /* handwritten instruction */
    /* 3F20 80002F20 03400008 */  jr         $k0
    /* 3F24 80002F24 27BDFFA0 */   addiu     $sp, $sp, -0x60
  .L80002F28:
    /* 3F28 80002F28 401A7000 */  mfc0       $k0, $14 /* handwritten instruction */
    /* 3F2C 80002F2C 3C1BBFF1 */  lui        $k1, %hi(D_BFF08000) /* handwritten instruction */
    /* 3F30 80002F30 AF7A8000 */  sw         $k0, %lo(D_BFF08000)($k1) /* handwritten instruction */
    /* 3F34 80002F34 8FBBFFF8 */  lw         $k1, -0x8($sp) /* handwritten instruction */
    /* 3F38 80002F38 8FBAFFF0 */  lw         $k0, -0x10($sp) /* handwritten instruction */
    /* 3F3C 80002F3C 42000018 */  eret /* handwritten instruction */
    /* 3F40 80002F40 00000000 */  nop
  .L80002F44:
    /* 3F44 80002F44 3C1A8002 */  lui        $k0, %hi(D_80019320) /* handwritten instruction */
    /* 3F48 80002F48 275A9320 */  addiu      $k0, $k0, %lo(D_80019320) /* handwritten instruction */
    /* 3F4C 80002F4C FF410020 */  sd         $at, 0x20($k0) /* handwritten instruction */
    /* 3F50 80002F50 401B6000 */  mfc0       $k1, $12 /* handwritten instruction */
    /* 3F54 80002F54 AF5B0118 */  sw         $k1, 0x118($k0) /* handwritten instruction */
    /* 3F58 80002F58 2401FFFC */  addiu      $at, $zero, -0x4
    /* 3F5C 80002F5C 0361D824 */  and        $k1, $k1, $at
    /* 3F60 80002F60 409B6000 */  mtc0       $k1, $12 /* handwritten instruction */
    /* 3F64 80002F64 FF480058 */  sd         $t0, 0x58($k0) /* handwritten instruction */
    /* 3F68 80002F68 FF490060 */  sd         $t1, 0x60($k0) /* handwritten instruction */
    /* 3F6C 80002F6C FF4A0068 */  sd         $t2, 0x68($k0) /* handwritten instruction */
    /* 3F70 80002F70 AF400018 */  sw         $zero, 0x18($k0) /* handwritten instruction */
    /* 3F74 80002F74 40086800 */  mfc0       $t0, $13 /* handwritten instruction */
endlabel func_80002E78
