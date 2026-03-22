
/* Handwritten function */
nonmatching func_800030D0, 0x100

glabel func_800030D0
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
endlabel func_800030D0
