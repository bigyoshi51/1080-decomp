
/* Handwritten function */
nonmatching func_80002DF0, 0x3F4

glabel func_80002DF0
    /* 3DF0 80002DF0 18A00011 */  blez       $a1, .L80002E38
    /* 3DF4 80002DF4 00000000 */   nop
    /* 3DF8 80002DF8 240B2000 */  addiu      $t3, $zero, 0x2000
    /* 3DFC 80002DFC 00AB082B */  sltu       $at, $a1, $t3
    /* 3E00 80002E00 1020000F */  beqz       $at, .L80002E40
    /* 3E04 80002E04 00000000 */   nop
    /* 3E08 80002E08 00804025 */  or         $t0, $a0, $zero
    /* 3E0C 80002E0C 00854821 */  addu       $t1, $a0, $a1
    /* 3E10 80002E10 0109082B */  sltu       $at, $t0, $t1
    /* 3E14 80002E14 10200008 */  beqz       $at, .L80002E38
    /* 3E18 80002E18 00000000 */   nop
    /* 3E1C 80002E1C 310A000F */  andi       $t2, $t0, 0xF
    /* 3E20 80002E20 2529FFF0 */  addiu      $t1, $t1, -0x10
    /* 3E24 80002E24 010A4023 */  subu       $t0, $t0, $t2
  .L80002E28:
    /* 3E28 80002E28 BD190000 */  cache      0x19, 0x0($t0) /* handwritten instruction */
    /* 3E2C 80002E2C 0109082B */  sltu       $at, $t0, $t1
    /* 3E30 80002E30 1420FFFD */  bnez       $at, .L80002E28
    /* 3E34 80002E34 25080010 */   addiu     $t0, $t0, 0x10
  .L80002E38:
    /* 3E38 80002E38 03E00008 */  jr         $ra
    /* 3E3C 80002E3C 00000000 */   nop
  .L80002E40:
    /* 3E40 80002E40 3C088000 */  lui        $t0, 0x8000
    /* 3E44 80002E44 010B4821 */  addu       $t1, $t0, $t3
    /* 3E48 80002E48 2529FFF0 */  addiu      $t1, $t1, -0x10
  .L80002E4C:
    /* 3E4C 80002E4C BD010000 */  cache      0x01, 0x0($t0) /* handwritten instruction */
    /* 3E50 80002E50 0109082B */  sltu       $at, $t0, $t1
    /* 3E54 80002E54 1420FFFD */  bnez       $at, .L80002E4C
    /* 3E58 80002E58 25080010 */   addiu     $t0, $t0, (0x80000010 & 0xFFFF)
    /* 3E5C 80002E5C 03E00008 */  jr         $ra
    /* 3E60 80002E60 00000000 */   nop
endlabel func_80002DF0
    /* 3E64 80002E64 00000000 */  nop
    /* 3E68 80002E68 00000000 */  nop
    /* 3E6C 80002E6C 00000000 */  nop

/* Handwritten function */
/* glabel func_80002E70 */
    /* 3E70 80002E70 3C1A8000 */  lui        $k0, %hi(D_80003344) /* handwritten instruction */
    /* 3E74 80002E74 275A3344 */  addiu      $k0, $k0, %lo(D_80003344) /* handwritten instruction */
/* Handwritten function */
/* glabel func_80002E78 */
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
/* Handwritten function */
/* glabel func_80002F78 */
    /* 3F78 80002F78 3C0A8002 */  lui        $t2, %hi(__kmc_pt_mode)
    /* 3F7C 80002F7C 8D4A82F0 */  lw         $t2, %lo(__kmc_pt_mode)($t2)
    /* 3F80 80002F80 154000D9 */  bnez       $t2, .L800032E8
    /* 3F84 80002F84 00000000 */   nop
    /* 3F88 80002F88 3109007C */  andi       $t1, $t0, 0x7C
    /* 3F8C 80002F8C 240A0000 */  addiu      $t2, $zero, 0x0
    /* 3F90 80002F90 152A00D5 */  bne        $t1, $t2, .L800032E8
    /* 3F94 80002F94 00000000 */   nop
    /* 3F98 80002F98 03684824 */  and        $t1, $k1, $t0
    /* 3F9C 80002F9C 312A4000 */  andi       $t2, $t1, 0x4000
    /* 3FA0 80002FA0 1140009E */  beqz       $t2, .L8000321C
    /* 3FA4 80002FA4 00000000 */   nop
    /* 3FA8 80002FA8 3C09C000 */  lui        $t1, %hi(D_C0000008)
    /* 3FAC 80002FAC 25290008 */  addiu      $t1, $t1, %lo(D_C0000008)
    /* 3FB0 80002FB0 AD200000 */  sw         $zero, 0x0($t1)
  .L80002FB4:
    /* 3FB4 80002FB4 40086800 */  mfc0       $t0, $13 /* handwritten instruction */
    /* 3FB8 80002FB8 31084000 */  andi       $t0, $t0, 0x4000
    /* 3FBC 80002FBC 1408FFFD */  bne        $zero, $t0, .L80002FB4
    /* 3FC0 80002FC0 00000000 */   nop
    /* 3FC4 80002FC4 3C0AC000 */  lui        $t2, (0xC0000000 >> 16)
    /* 3FC8 80002FC8 8D480000 */  lw         $t0, (0xC0000000 & 0xFFFF)($t2)
    /* 3FCC 80002FCC 254A0000 */  addiu      $t2, $t2, %lo(D_C0000000)
    /* 3FD0 80002FD0 240A0010 */  addiu      $t2, $zero, 0x10
    /* 3FD4 80002FD4 00084E82 */  srl        $t1, $t0, 26
    /* 3FD8 80002FD8 3129003F */  andi       $t1, $t1, 0x3F
    /* 3FDC 80002FDC 112A0041 */  beq        $t1, $t2, .L800030E4
    /* 3FE0 80002FE0 00000000 */   nop
    /* 3FE4 80002FE4 240A000E */  addiu      $t2, $zero, 0xE
    /* 3FE8 80002FE8 112A0063 */  beq        $t1, $t2, .L80003178
    /* 3FEC 80002FEC 00000000 */   nop
    /* 3FF0 80002FF0 240A0014 */  addiu      $t2, $zero, 0x14
    /* 3FF4 80002FF4 112A0022 */  beq        $t1, $t2, .L80003080
    /* 3FF8 80002FF8 00000000 */   nop
    /* 3FFC 80002FFC 240A000F */  addiu      $t2, $zero, 0xF
    /* 4000 80003000 112A0022 */  beq        $t1, $t2, .L8000308C
    /* 4004 80003004 00000000 */   nop
    /* 4008 80003008 240A0011 */  addiu      $t2, $zero, 0x11
    /* 400C 8000300C 112A0025 */  beq        $t1, $t2, .L800030A4
    /* 4010 80003010 00000000 */   nop
    /* 4014 80003014 240A000D */  addiu      $t2, $zero, 0xD
    /* 4018 80003018 112A0026 */  beq        $t1, $t2, .L800030B4
    /* 401C 8000301C 00000000 */   nop
    /* 4020 80003020 240A0012 */  addiu      $t2, $zero, 0x12
    /* 4024 80003024 112A0027 */  beq        $t1, $t2, .L800030C4
    /* 4028 80003028 00000000 */   nop
    /* 402C 8000302C 240A0013 */  addiu      $t2, $zero, 0x13
    /* 4030 80003030 112A0028 */  beq        $t1, $t2, .L800030D4
    /* 4034 80003034 00000000 */   nop
    /* 4038 80003038 240A0015 */  addiu      $t2, $zero, 0x15
    /* 403C 8000303C 112A0003 */  beq        $t1, $t2, .L8000304C
    /* 4040 80003040 00000000 */   nop
    /* 4044 80003044 1000009D */  b          .L800032BC
    /* 4048 80003048 00000000 */   nop
  .L8000304C:
    /* 404C 8000304C 00084C02 */  srl        $t1, $t0, 16
    /* 4050 80003050 240A0001 */  addiu      $t2, $zero, 0x1
    /* 4054 80003054 312900FF */  andi       $t1, $t1, 0xFF
    /* 4058 80003058 112A0005 */  beq        $t1, $t2, .L80003070
    /* 405C 8000305C 00000000 */   nop
    /* 4060 80003060 240A00A8 */  addiu      $t2, $zero, 0xA8
    /* 4064 80003064 3C018001 */  lui        $at, %hi(D_8000A408)
    /* 4068 80003068 1000009F */  b          .L800032E8
    /* 406C 8000306C AC2AA408 */   sw        $t2, %lo(D_8000A408)($at)
  .L80003070:
    /* 4070 80003070 240A00B0 */  addiu      $t2, $zero, 0xB0
    /* 4074 80003074 3C018001 */  lui        $at, %hi(D_8000A408)
    /* 4078 80003078 1000009B */  b          .L800032E8
    /* 407C 8000307C AC2AA408 */   sw        $t2, %lo(D_8000A408)($at)
  .L80003080:
    /* 4080 80003080 3C018001 */  lui        $at, %hi(D_8000A40C)
    /* 4084 80003084 10000098 */  b          .L800032E8
    /* 4088 80003088 AC28A40C */   sw        $t0, %lo(D_8000A40C)($at)
  .L8000308C:
    /* 408C 8000308C 3C0A00FF */  lui        $t2, (0xFFFFFF >> 16)
    /* 4090 80003090 354AFFFF */  ori        $t2, $t2, (0xFFFFFF & 0xFFFF)
    /* 4094 80003094 010A4824 */  and        $t1, $t0, $t2
    /* 4098 80003098 3C018001 */  lui        $at, %hi(D_8000A404)
    /* 409C 8000309C 10000087 */  b          .L800032BC
    /* 40A0 800030A0 AC29A404 */   sw        $t1, %lo(D_8000A404)($at)
  .L800030A4:
    /* 40A4 800030A4 240A0088 */  addiu      $t2, $zero, 0x88
    /* 40A8 800030A8 3C018001 */  lui        $at, %hi(D_8000A408)
    /* 40AC 800030AC 1000008E */  b          .L800032E8
    /* 40B0 800030B0 AC2AA408 */   sw        $t2, %lo(D_8000A408)($at)
  .L800030B4:
    /* 40B4 800030B4 240A0080 */  addiu      $t2, $zero, 0x80
    /* 40B8 800030B8 3C018001 */  lui        $at, %hi(D_8000A408)
    /* 40BC 800030BC 1000008A */  b          .L800032E8
    /* 40C0 800030C0 AC2AA408 */   sw        $t2, %lo(D_8000A408)($at)
  .L800030C4:
    /* 40C4 800030C4 240A0090 */  addiu      $t2, $zero, 0x90
    /* 40C8 800030C8 3C018001 */  lui        $at, (0x80010000 >> 16)
    /* 40CC 800030CC 10000086 */  b          .L800032E8
/* Handwritten function */
/* glabel func_800030D0 */
    /* 40D0 800030D0 AC2AA408 */  sw         $t2, -0x5BF8($at)
  .L800030D4:
    /* 40D4 800030D4 240A0098 */  addiu      $t2, $zero, 0x98
    /* 40D8 800030D8 3C018001 */  lui        $at, %hi(D_8000A408)
    /* 40DC 800030DC 10000082 */  b          .L800032E8
    /* 40E0 800030E0 AC2AA408 */   sw        $t2, %lo(D_8000A408)($at)
  .L800030E4:
    /* 40E4 800030E4 00084E02 */  srl        $t1, $t0, 24
    /* 40E8 800030E8 31290003 */  andi       $t1, $t1, 0x3
    /* 40EC 800030EC 10090073 */  beq        $zero, $t1, .L800032BC
    /* 40F0 800030F0 00000000 */   nop
    /* 40F4 800030F4 3C0A8002 */  lui        $t2, %hi(__osRdb_Read_Data_Ct)
    /* 40F8 800030F8 8D4A9500 */  lw         $t2, %lo(__osRdb_Read_Data_Ct)($t2)
    /* 40FC 800030FC 3C018002 */  lui        $at, %hi(__osRdb_Read_Data_Ct)
    /* 4100 80003100 01495023 */  subu       $t2, $t2, $t1
    /* 4104 80003104 AC2A9500 */  sw         $t2, %lo(__osRdb_Read_Data_Ct)($at)
    /* 4108 80003108 FF4B0070 */  sd         $t3, 0x70($k0) /* handwritten instruction */
    /* 410C 8000310C 3C0B8002 */  lui        $t3, %hi(__osRdb_Read_Data_Buf)
    /* 4110 80003110 8D6B94FC */  lw         $t3, %lo(__osRdb_Read_Data_Buf)($t3)
    /* 4114 80003114 00085402 */  srl        $t2, $t0, 16
    /* 4118 80003118 314A00FF */  andi       $t2, $t2, 0xFF
    /* 411C 8000311C 2129FFFF */  addi       $t1, $t1, -0x1 /* handwritten instruction */
    /* 4120 80003120 A16A0000 */  sb         $t2, 0x0($t3)
    /* 4124 80003124 1009000A */  beq        $zero, $t1, .L80003150
    /* 4128 80003128 216B0001 */   addi      $t3, $t3, 0x1 /* handwritten instruction */
    /* 412C 8000312C 00085202 */  srl        $t2, $t0, 8
    /* 4130 80003130 314A00FF */  andi       $t2, $t2, 0xFF
    /* 4134 80003134 2129FFFF */  addi       $t1, $t1, -0x1 /* handwritten instruction */
    /* 4138 80003138 A16A0000 */  sb         $t2, 0x0($t3)
    /* 413C 8000313C 10090004 */  beq        $zero, $t1, .L80003150
    /* 4140 80003140 216B0001 */   addi      $t3, $t3, 0x1 /* handwritten instruction */
    /* 4144 80003144 310800FF */  andi       $t0, $t0, 0xFF
    /* 4148 80003148 A1680000 */  sb         $t0, 0x0($t3)
    /* 414C 8000314C 216B0001 */  addi       $t3, $t3, 0x1 /* handwritten instruction */
  .L80003150:
    /* 4150 80003150 3C0A8002 */  lui        $t2, %hi(__osRdb_Read_Data_Ct)
    /* 4154 80003154 8D4A9500 */  lw         $t2, %lo(__osRdb_Read_Data_Ct)($t2)
    /* 4158 80003158 3C018002 */  lui        $at, %hi(__osRdb_Read_Data_Buf)
    /* 415C 8000315C AC2B94FC */  sw         $t3, %lo(__osRdb_Read_Data_Buf)($at)
    /* 4160 80003160 140A0056 */  bne        $zero, $t2, .L800032BC
    /* 4164 80003164 DF4B0070 */   ld        $t3, 0x70($k0) /* handwritten instruction */
    /* 4168 80003168 240A0078 */  addiu      $t2, $zero, 0x78
    /* 416C 8000316C 3C018001 */  lui        $at, %hi(D_8000A408)
    /* 4170 80003170 1000005D */  b          .L800032E8
    /* 4174 80003174 AC2AA408 */   sw        $t2, %lo(D_8000A408)($at)
  .L80003178:
    /* 4178 80003178 00084E02 */  srl        $t1, $t0, 24
    /* 417C 8000317C 31290003 */  andi       $t1, $t1, 0x3
    /* 4180 80003180 1009004E */  beq        $zero, $t1, .L800032BC
    /* 4184 80003184 00000000 */   nop
    /* 4188 80003188 3C0A8001 */  lui        $t2, %hi(D_8000A404)
    /* 418C 8000318C 8D4AA404 */  lw         $t2, %lo(D_8000A404)($t2)
    /* 4190 80003190 3C018001 */  lui        $at, %hi(D_8000A404)
    /* 4194 80003194 01495023 */  subu       $t2, $t2, $t1
    /* 4198 80003198 AC2AA404 */  sw         $t2, %lo(D_8000A404)($at)
    /* 419C 8000319C FF4B0070 */  sd         $t3, 0x70($k0) /* handwritten instruction */
    /* 41A0 800031A0 3C0B8002 */  lui        $t3, %hi(__osRdb_DbgRead_Buf)
    /* 41A4 800031A4 8D6B966C */  lw         $t3, %lo(__osRdb_DbgRead_Buf)($t3)
    /* 41A8 800031A8 140B0003 */  bne        $zero, $t3, .L800031B8
    /* 41AC 800031AC 00000000 */   nop
    /* 41B0 800031B0 10000042 */  b          .L800032BC
    /* 41B4 800031B4 DF4B0070 */   ld        $t3, 0x70($k0) /* handwritten instruction */
  .L800031B8:
    /* 41B8 800031B8 00085402 */  srl        $t2, $t0, 16
    /* 41BC 800031BC 314A00FF */  andi       $t2, $t2, 0xFF
    /* 41C0 800031C0 2129FFFF */  addi       $t1, $t1, -0x1 /* handwritten instruction */
    /* 41C4 800031C4 A16A0000 */  sb         $t2, 0x0($t3)
    /* 41C8 800031C8 1009000A */  beq        $zero, $t1, .L800031F4
    /* 41CC 800031CC 216B0001 */   addi      $t3, $t3, 0x1 /* handwritten instruction */
/* Handwritten function */
/* glabel func_800031D0 */
    /* 41D0 800031D0 00085202 */  srl        $t2, $t0, 8
    /* 41D4 800031D4 314A00FF */  andi       $t2, $t2, 0xFF
    /* 41D8 800031D8 2129FFFF */  addi       $t1, $t1, -0x1 /* handwritten instruction */
    /* 41DC 800031DC A16A0000 */  sb         $t2, 0x0($t3)
/* Handwritten function */
/* glabel func_800031E0 */
    /* 41E0 800031E0 10090004 */  beq        $zero, $t1, .L800031F4
    /* 41E4 800031E4 216B0001 */   addi      $t3, $t3, 0x1 /* handwritten instruction */
    /* 41E8 800031E8 310800FF */  andi       $t0, $t0, 0xFF
    /* 41EC 800031EC A1680000 */  sb         $t0, 0x0($t3)
endlabel func_80002DF0
