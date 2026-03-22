
/* Handwritten function */
nonmatching func_800031F0, 0xA34

glabel func_800031F0
    /* 41F0 800031F0 216B0001 */  addi       $t3, $t3, 0x1 /* handwritten instruction */
  .L800031F4:
    /* 41F4 800031F4 3C0A8001 */  lui        $t2, %hi(D_8000A404)
    /* 41F8 800031F8 8D4AA404 */  lw         $t2, %lo(D_8000A404)($t2)
    /* 41FC 800031FC 3C018002 */  lui        $at, %hi(__osRdb_DbgRead_Buf)
    /* 4200 80003200 AC2B966C */  sw         $t3, %lo(__osRdb_DbgRead_Buf)($at)
    /* 4204 80003204 140A002D */  bne        $zero, $t2, .L800032BC
    /* 4208 80003208 DF4B0070 */   ld        $t3, 0x70($k0) /* handwritten instruction */
    /* 420C 8000320C 240A00A0 */  addiu      $t2, $zero, 0xA0
    /* 4210 80003210 3C018001 */  lui        $at, %hi(D_8000A408)
    /* 4214 80003214 10000034 */  b          .L800032E8
    /* 4218 80003218 AC2AA408 */   sw        $t2, %lo(D_8000A408)($at)
  .L8000321C:
    /* 421C 8000321C 312A2000 */  andi       $t2, $t1, 0x2000
    /* 4220 80003220 11400031 */  beqz       $t2, .L800032E8
    /* 4224 80003224 00000000 */   nop
    /* 4228 80003228 3C09C000 */  lui        $t1, (0xC000000C >> 16)
    /* 422C 8000322C AD20000C */  sw         $zero, (0xC000000C & 0xFFFF)($t1)
    /* 4230 80003230 3C0A8002 */  lui        $t2, %hi(__osRdb_IP6_Ct)
    /* 4234 80003234 8D4A9308 */  lw         $t2, %lo(__osRdb_IP6_Ct)($t2)
    /* 4238 80003238 2529000C */  addiu      $t1, $t1, %lo(D_C000000C)
    /* 423C 8000323C 15400005 */  bnez       $t2, .L80003254
    /* 4240 80003240 00000000 */   nop
    /* 4244 80003244 240A0001 */  addiu      $t2, $zero, 0x1
    /* 4248 80003248 3C018001 */  lui        $at, %hi(__osRdb_IP6_Empty)
    /* 424C 8000324C 1000001B */  b          .L800032BC
    /* 4250 80003250 AC2AA490 */   sw        $t2, %lo(__osRdb_IP6_Empty)($at)
  .L80003254:
    /* 4254 80003254 3C098002 */  lui        $t1, %hi(__osRdb_IP6_CurSend)
    /* 4258 80003258 8D299310 */  lw         $t1, %lo(__osRdb_IP6_CurSend)($t1)
    /* 425C 8000325C 3C088002 */  lui        $t0, %hi(__osRdb_IP6_Data)
    /* 4260 80003260 8D089300 */  lw         $t0, %lo(__osRdb_IP6_Data)($t0)
    /* 4264 80003264 214AFFFF */  addi       $t2, $t2, -0x1 /* handwritten instruction */
    /* 4268 80003268 3C018002 */  lui        $at, %hi(__osRdb_IP6_Ct)
    /* 426C 8000326C AC2A9308 */  sw         $t2, %lo(__osRdb_IP6_Ct)($at)
  alabel D_80003270
    /* 4270 80003270 00095080 */  sll        $t2, $t1, 2
    /* 4274 80003274 01484020 */  add        $t0, $t2, $t0 /* handwritten instruction */
    /* 4278 80003278 8D0A0000 */  lw         $t2, 0x0($t0)
    /* 427C 8000327C 3C088002 */  lui        $t0, %hi(__osRdb_IP6_Size)
    /* 4280 80003280 8D089304 */  lw         $t0, %lo(__osRdb_IP6_Size)($t0)
    /* 4284 80003284 21290001 */  addi       $t1, $t1, 0x1 /* handwritten instruction */
    /* 4288 80003288 01094022 */  sub        $t0, $t0, $t1 /* handwritten instruction */
    /* 428C 8000328C 1D000002 */  bgtz       $t0, .L80003298
    /* 4290 80003290 00000000 */   nop
    /* 4294 80003294 24090000 */  addiu      $t1, $zero, 0x0
  .L80003298:
    /* 4298 80003298 3C018002 */  lui        $at, %hi(__osRdb_IP6_CurSend)
    /* 429C 8000329C AC299310 */  sw         $t1, %lo(__osRdb_IP6_CurSend)($at)
  .L800032A0:
    /* 42A0 800032A0 40086800 */  mfc0       $t0, $13 /* handwritten instruction */
    /* 42A4 800032A4 31082000 */  andi       $t0, $t0, 0x2000
    /* 42A8 800032A8 1408FFFD */  bne        $zero, $t0, .L800032A0
    /* 42AC 800032AC 00000000 */   nop
    /* 42B0 800032B0 3C08C000 */  lui        $t0, %hi(D_C0000000)
    /* 42B4 800032B4 25080000 */  addiu      $t0, $t0, %lo(D_C0000000)
    /* 42B8 800032B8 AD0A0000 */  sw         $t2, 0x0($t0)
  .L800032BC:
    /* 42BC 800032BC DF480058 */  ld         $t0, 0x58($k0) /* handwritten instruction */
    /* 42C0 800032C0 DF490060 */  ld         $t1, 0x60($k0) /* handwritten instruction */
    /* 42C4 800032C4 DF4A0068 */  ld         $t2, 0x68($k0) /* handwritten instruction */
    /* 42C8 800032C8 DF410020 */  ld         $at, 0x20($k0) /* handwritten instruction */
    /* 42CC 800032CC 8F5B0118 */  lw         $k1, 0x118($k0) /* handwritten instruction */
    /* 42D0 800032D0 409B6000 */  mtc0       $k1, $12 /* handwritten instruction */
    /* 42D4 800032D4 00000000 */  nop
    /* 42D8 800032D8 00000000 */  nop
    /* 42DC 800032DC 00000000 */  nop
    /* 42E0 800032E0 00000000 */  nop
    /* 42E4 800032E4 42000018 */  eret /* handwritten instruction */
  .L800032E8:
    /* 42E8 800032E8 03404025 */  or         $t0, $k0, $zero
    /* 42EC 800032EC 3C1A8001 */  lui        $k0, %hi(__osRunningThread) /* handwritten instruction */
    /* 42F0 800032F0 8F5AA420 */  lw         $k0, %lo(__osRunningThread)($k0) /* handwritten instruction */
    /* 42F4 800032F4 DD090020 */  ld         $t1, 0x20($t0)
    /* 42F8 800032F8 FF490020 */  sd         $t1, 0x20($k0) /* handwritten instruction */
    /* 42FC 800032FC DD090118 */  ld         $t1, 0x118($t0)
    /* 4300 80003300 FF490118 */  sd         $t1, 0x118($k0) /* handwritten instruction */
    /* 4304 80003304 DD090058 */  ld         $t1, 0x58($t0)
    /* 4308 80003308 FF490058 */  sd         $t1, 0x58($k0) /* handwritten instruction */
    /* 430C 8000330C DD090060 */  ld         $t1, 0x60($t0)
    /* 4310 80003310 FF490060 */  sd         $t1, 0x60($k0) /* handwritten instruction */
    /* 4314 80003314 DD090068 */  ld         $t1, 0x68($t0)
    /* 4318 80003318 FF490068 */  sd         $t1, 0x68($k0) /* handwritten instruction */
    /* 431C 8000331C 8F5B0118 */  lw         $k1, 0x118($k0) /* handwritten instruction */
    /* 4320 80003320 00004012 */  mflo       $t0
    /* 4324 80003324 FF480108 */  sd         $t0, 0x108($k0) /* handwritten instruction */
    /* 4328 80003328 00004010 */  mfhi       $t0
    /* 432C 8000332C 3369FF00 */  andi       $t1, $k1, 0xFF00 /* handwritten instruction */
    /* 4330 80003330 FF420028 */  sd         $v0, 0x28($k0) /* handwritten instruction */
    /* 4334 80003334 FF430030 */  sd         $v1, 0x30($k0) /* handwritten instruction */
    /* 4338 80003338 FF440038 */  sd         $a0, 0x38($k0) /* handwritten instruction */
    /* 433C 8000333C FF450040 */  sd         $a1, 0x40($k0) /* handwritten instruction */
    /* 4340 80003340 FF460048 */  sd         $a2, 0x48($k0) /* handwritten instruction */
  alabel D_80003344
    /* 4344 80003344 FF470050 */  sd         $a3, 0x50($k0) /* handwritten instruction */
    /* 4348 80003348 FF4B0070 */  sd         $t3, 0x70($k0) /* handwritten instruction */
    /* 434C 8000334C FF4C0078 */  sd         $t4, 0x78($k0) /* handwritten instruction */
    /* 4350 80003350 FF4D0080 */  sd         $t5, 0x80($k0) /* handwritten instruction */
    /* 4354 80003354 FF4E0088 */  sd         $t6, 0x88($k0) /* handwritten instruction */
    /* 4358 80003358 FF4F0090 */  sd         $t7, 0x90($k0) /* handwritten instruction */
    /* 435C 8000335C FF500098 */  sd         $s0, 0x98($k0) /* handwritten instruction */
    /* 4360 80003360 FF5100A0 */  sd         $s1, 0xA0($k0) /* handwritten instruction */
    /* 4364 80003364 FF5200A8 */  sd         $s2, 0xA8($k0) /* handwritten instruction */
    /* 4368 80003368 FF5300B0 */  sd         $s3, 0xB0($k0) /* handwritten instruction */
    /* 436C 8000336C FF5400B8 */  sd         $s4, 0xB8($k0) /* handwritten instruction */
    /* 4370 80003370 FF5500C0 */  sd         $s5, 0xC0($k0) /* handwritten instruction */
    /* 4374 80003374 FF5600C8 */  sd         $s6, 0xC8($k0) /* handwritten instruction */
    /* 4378 80003378 FF5700D0 */  sd         $s7, 0xD0($k0) /* handwritten instruction */
    /* 437C 8000337C FF5800D8 */  sd         $t8, 0xD8($k0) /* handwritten instruction */
    /* 4380 80003380 FF5900E0 */  sd         $t9, 0xE0($k0) /* handwritten instruction */
    /* 4384 80003384 FF5C00E8 */  sd         $gp, 0xE8($k0) /* handwritten instruction */
    /* 4388 80003388 FF5D00F0 */  sd         $sp, 0xF0($k0) /* handwritten instruction */
    /* 438C 8000338C FF5E00F8 */  sd         $fp, 0xF8($k0) /* handwritten instruction */
    /* 4390 80003390 FF5F0100 */  sd         $ra, 0x100($k0) /* handwritten instruction */
    /* 4394 80003394 11200011 */  beqz       $t1, .L800033DC
    /* 4398 80003398 FF480110 */   sd        $t0, 0x110($k0) /* handwritten instruction */
    /* 439C 8000339C 3C088001 */  lui        $t0, %hi(__OSGlobalIntMask)
    /* 43A0 800033A0 2508A3E0 */  addiu      $t0, $t0, %lo(__OSGlobalIntMask)
    /* 43A4 800033A4 8D080000 */  lw         $t0, 0x0($t0)
    /* 43A8 800033A8 2401FFFF */  addiu      $at, $zero, -0x1
    /* 43AC 800033AC 01015026 */  xor        $t2, $t0, $at
    /* 43B0 800033B0 3C01FFFF */  lui        $at, (0xFFFF00FF >> 16)
    /* 43B4 800033B4 314AFF00 */  andi       $t2, $t2, 0xFF00
    /* 43B8 800033B8 342100FF */  ori        $at, $at, (0xFFFF00FF & 0xFFFF)
    /* 43BC 800033BC 012A6025 */  or         $t4, $t1, $t2
    /* 43C0 800033C0 03615824 */  and        $t3, $k1, $at
    /* 43C4 800033C4 3108FF00 */  andi       $t0, $t0, 0xFF00
    /* 43C8 800033C8 016C5825 */  or         $t3, $t3, $t4
    /* 43CC 800033CC 01284824 */  and        $t1, $t1, $t0
    /* 43D0 800033D0 0361D824 */  and        $k1, $k1, $at
    /* 43D4 800033D4 AF4B0118 */  sw         $t3, 0x118($k0) /* handwritten instruction */
    /* 43D8 800033D8 0369D825 */  or         $k1, $k1, $t1
  .L800033DC:
    /* 43DC 800033DC 3C09A430 */  lui        $t1, %hi(D_A430000C)
    /* 43E0 800033E0 8D29000C */  lw         $t1, %lo(D_A430000C)($t1)
    /* 43E4 800033E4 1120000B */  beqz       $t1, .L80003414
    /* 43E8 800033E8 00000000 */   nop
    /* 43EC 800033EC 3C088001 */  lui        $t0, %hi(__OSGlobalIntMask)
    /* 43F0 800033F0 2508A3E0 */  addiu      $t0, $t0, %lo(__OSGlobalIntMask)
    /* 43F4 800033F4 8D080000 */  lw         $t0, 0x0($t0)
    /* 43F8 800033F8 8F4C0128 */  lw         $t4, 0x128($k0) /* handwritten instruction */
    /* 43FC 800033FC 2401FFFF */  addiu      $at, $zero, -0x1
    /* 4400 80003400 00084402 */  srl        $t0, $t0, 16
    /* 4404 80003404 01014026 */  xor        $t0, $t0, $at
    /* 4408 80003408 3108003F */  andi       $t0, $t0, 0x3F
    /* 440C 8000340C 010C4024 */  and        $t0, $t0, $t4
    /* 4410 80003410 01284825 */  or         $t1, $t1, $t0
  .L80003414:
    /* 4414 80003414 AF490128 */  sw         $t1, 0x128($k0) /* handwritten instruction */
    /* 4418 80003418 40087000 */  mfc0       $t0, $14 /* handwritten instruction */
    /* 441C 8000341C AF48011C */  sw         $t0, 0x11C($k0) /* handwritten instruction */
    /* 4420 80003420 8F480018 */  lw         $t0, 0x18($k0) /* handwritten instruction */
    /* 4424 80003424 11000014 */  beqz       $t0, .L80003478
    /* 4428 80003428 00000000 */   nop
    /* 442C 8000342C 4448F800 */  cfc1       $t0, $31
    /* 4430 80003430 00000000 */  nop
    /* 4434 80003434 AF48012C */  sw         $t0, 0x12C($k0) /* handwritten instruction */
    /* 4438 80003438 F7400130 */  sdc1       $f0, 0x130($k0)
    /* 443C 8000343C F7420138 */  sdc1       $f2, 0x138($k0)
    /* 4440 80003440 F7440140 */  sdc1       $f4, 0x140($k0)
    /* 4444 80003444 F7460148 */  sdc1       $f6, 0x148($k0)
    /* 4448 80003448 F7480150 */  sdc1       $f8, 0x150($k0)
    /* 444C 8000344C F74A0158 */  sdc1       $f10, 0x158($k0)
    /* 4450 80003450 F74C0160 */  sdc1       $f12, 0x160($k0)
    /* 4454 80003454 F74E0168 */  sdc1       $f14, 0x168($k0)
    /* 4458 80003458 F7500170 */  sdc1       $f16, 0x170($k0)
    /* 445C 8000345C F7520178 */  sdc1       $f18, 0x178($k0)
    /* 4460 80003460 F7540180 */  sdc1       $f20, 0x180($k0)
    /* 4464 80003464 F7560188 */  sdc1       $f22, 0x188($k0)
    /* 4468 80003468 F7580190 */  sdc1       $f24, 0x190($k0)
    /* 446C 8000346C F75A0198 */  sdc1       $f26, 0x198($k0)
    /* 4470 80003470 F75C01A0 */  sdc1       $f28, 0x1A0($k0)
    /* 4474 80003474 F75E01A8 */  sdc1       $f30, 0x1A8($k0)
  .L80003478:
    /* 4478 80003478 40086800 */  mfc0       $t0, $13 /* handwritten instruction */
    /* 447C 8000347C AF480120 */  sw         $t0, 0x120($k0) /* handwritten instruction */
    /* 4480 80003480 24090002 */  addiu      $t1, $zero, 0x2
    /* 4484 80003484 A7490010 */  sh         $t1, 0x10($k0) /* handwritten instruction */
    /* 4488 80003488 3C048001 */  lui        $a0, %hi(D_8000A40C)
    /* 448C 8000348C 8C84A40C */  lw         $a0, %lo(D_8000A40C)($a0)
    /* 4490 80003490 10800005 */  beqz       $a0, .L800034A8
    /* 4494 80003494 3C018001 */   lui       $at, %hi(D_8000A40C)
    /* 4498 80003498 0C00136E */  jal        func_80004DB8
    /* 449C 8000349C AC20A40C */   sw        $zero, %lo(D_8000A40C)($at)
    /* 44A0 800034A0 10000178 */  b          .L80003A84
    /* 44A4 800034A4 00000000 */   nop
  .L800034A8:
    /* 44A8 800034A8 3C048001 */  lui        $a0, %hi(D_8000A408)
    /* 44AC 800034AC 8C84A408 */  lw         $a0, %lo(D_8000A408)($a0)
    /* 44B0 800034B0 10800004 */  beqz       $a0, .L800034C4
    /* 44B4 800034B4 3C018001 */   lui       $at, %hi(D_8000A408)
    /* 44B8 800034B8 0C000F09 */  jal        func_80003C24
    /* 44BC 800034BC AC20A408 */   sw        $zero, %lo(D_8000A408)($at)
    /* 44C0 800034C0 8F480120 */  lw         $t0, 0x120($k0) /* handwritten instruction */
  .L800034C4:
    /* 44C4 800034C4 3109007C */  andi       $t1, $t0, 0x7C
    /* 44C8 800034C8 240A0024 */  addiu      $t2, $zero, 0x24
    /* 44CC 800034CC 112A00B0 */  beq        $t1, $t2, .L80003790
    /* 44D0 800034D0 00000000 */   nop
    /* 44D4 800034D4 240A002C */  addiu      $t2, $zero, 0x2C
    /* 44D8 800034D8 112A00FF */  beq        $t1, $t2, .L800038D8
    /* 44DC 800034DC 00000000 */   nop
    /* 44E0 800034E0 240A0000 */  addiu      $t2, $zero, 0x0
    /* 44E4 800034E4 152A00C3 */  bne        $t1, $t2, .L800037F4
    /* 44E8 800034E8 00000000 */   nop
    /* 44EC 800034EC 03688024 */  and        $s0, $k1, $t0
  .L800034F0:
    /* 44F0 800034F0 3209FF00 */  andi       $t1, $s0, 0xFF00
    /* 44F4 800034F4 00095302 */  srl        $t2, $t1, 12
    /* 44F8 800034F8 15400003 */  bnez       $t2, .L80003508
    /* 44FC 800034FC 00000000 */   nop
    /* 4500 80003500 00095202 */  srl        $t2, $t1, 8
    /* 4504 80003504 214A0010 */  addi       $t2, $t2, 0x10 /* handwritten instruction */
  .L80003508:
    /* 4508 80003508 3C018001 */  lui        $at, %hi(D_8000A700)
    /* 450C 8000350C 002A0821 */  addu       $at, $at, $t2
    /* 4510 80003510 902AA700 */  lbu        $t2, %lo(D_8000A700)($at)
    /* 4514 80003514 3C018001 */  lui        $at, %hi(jtbl_8000A720)
    /* 4518 80003518 002A0821 */  addu       $at, $at, $t2
    /* 451C 8000351C 8C2AA720 */  lw         $t2, %lo(jtbl_8000A720)($at)
    /* 4520 80003520 01400008 */  jr         $t2
    /* 4524 80003524 00000000 */   nop
    /* 4528 80003528 2401DFFF */  addiu      $at, $zero, -0x2001
    /* 452C 8000352C 1000FFF0 */  b          .L800034F0
    /* 4530 80003530 02018024 */   and       $s0, $s0, $at
    /* 4534 80003534 2401BFFF */  addiu      $at, $zero, -0x4001
    /* 4538 80003538 1000FFED */  b          .L800034F0
    /* 453C 8000353C 02018024 */   and       $s0, $s0, $at
    /* 4540 80003540 40095800 */  mfc0       $t1, $11 /* handwritten instruction */
    /* 4544 80003544 40895800 */  mtc0       $t1, $11 /* handwritten instruction */
    /* 4548 80003548 0C000F09 */  jal        func_80003C24
    /* 454C 8000354C 24040018 */   addiu     $a0, $zero, 0x18
    /* 4550 80003550 3C01FFFF */  lui        $at, (0xFFFF7FFF >> 16)
    /* 4554 80003554 34217FFF */  ori        $at, $at, (0xFFFF7FFF & 0xFFFF)
    /* 4558 80003558 1000FFE5 */  b          .L800034F0
    /* 455C 8000355C 02018024 */   and       $s0, $s0, $at
    /* 4560 80003560 2401F7FF */  addiu      $at, $zero, -0x801
    /* 4564 80003564 02018024 */  and        $s0, $s0, $at
    /* 4568 80003568 240A0004 */  addiu      $t2, $zero, 0x4
    /* 456C 8000356C 3C018001 */  lui        $at, %hi(D_8000A3F0)
    /* 4570 80003570 002A0821 */  addu       $at, $at, $t2
    /* 4574 80003574 8C2AA3F0 */  lw         $t2, %lo(D_8000A3F0)($at)
    /* 4578 80003578 3C1D8002 */  lui        $sp, %hi(D_80018300)
    /* 457C 8000357C 27BD8300 */  addiu      $sp, $sp, %lo(D_80018300)
    /* 4580 80003580 24040010 */  addiu      $a0, $zero, 0x10
    /* 4584 80003584 11400007 */  beqz       $t2, .L800035A4
    /* 4588 80003588 27BD0FF0 */   addiu     $sp, $sp, 0xFF0
    /* 458C 8000358C 0140F809 */  jalr       $t2
    /* 4590 80003590 00000000 */   nop
    /* 4594 80003594 10400003 */  beqz       $v0, .L800035A4
    /* 4598 80003598 24040010 */   addiu     $a0, $zero, 0x10
    /* 459C 8000359C 10000082 */  b          .L800037A8
    /* 45A0 800035A0 00000000 */   nop
  .L800035A4:
    /* 45A4 800035A4 0C000F09 */  jal        func_80003C24
    /* 45A8 800035A8 00000000 */   nop
    /* 45AC 800035AC 1000FFD0 */  b          .L800034F0
    /* 45B0 800035B0 00000000 */   nop
    /* 45B4 800035B4 3C088001 */  lui        $t0, %hi(__OSGlobalIntMask)
    /* 45B8 800035B8 2508A3E0 */  addiu      $t0, $t0, %lo(__OSGlobalIntMask)
    /* 45BC 800035BC 8D080000 */  lw         $t0, 0x0($t0)
    /* 45C0 800035C0 3C11A430 */  lui        $s1, %hi(D_A4300008)
    /* 45C4 800035C4 8E310008 */  lw         $s1, %lo(D_A4300008)($s1)
    /* 45C8 800035C8 00084402 */  srl        $t0, $t0, 16
    /* 45CC 800035CC 02288824 */  and        $s1, $s1, $t0
    /* 45D0 800035D0 32290001 */  andi       $t1, $s1, 0x1
    /* 45D4 800035D4 11200013 */  beqz       $t1, .L80003624
    /* 45D8 800035D8 00000000 */   nop
    /* 45DC 800035DC 3C0CA404 */  lui        $t4, %hi(D_A4040010)
    /* 45E0 800035E0 8D8C0010 */  lw         $t4, %lo(D_A4040010)($t4)
    /* 45E4 800035E4 34098008 */  ori        $t1, $zero, 0x8008
    /* 45E8 800035E8 3C01A404 */  lui        $at, %hi(D_A4040010)
    /* 45EC 800035EC 318C0300 */  andi       $t4, $t4, 0x300
    /* 45F0 800035F0 3231003E */  andi       $s1, $s1, 0x3E
    /* 45F4 800035F4 11800007 */  beqz       $t4, .L80003614
    /* 45F8 800035F8 AC290010 */   sw        $t1, %lo(D_A4040010)($at)
    /* 45FC 800035FC 0C000F09 */  jal        func_80003C24
    /* 4600 80003600 24040020 */   addiu     $a0, $zero, 0x20
    /* 4604 80003604 12200038 */  beqz       $s1, .L800036E8
    /* 4608 80003608 00000000 */   nop
    /* 460C 8000360C 10000005 */  b          .L80003624
    /* 4610 80003610 00000000 */   nop
  .L80003614:
    /* 4614 80003614 0C000F09 */  jal        func_80003C24
    /* 4618 80003618 24040058 */   addiu     $a0, $zero, 0x58
    /* 461C 8000361C 12200032 */  beqz       $s1, .L800036E8
    /* 4620 80003620 00000000 */   nop
  .L80003624:
    /* 4624 80003624 32290008 */  andi       $t1, $s1, 0x8
    /* 4628 80003628 11200007 */  beqz       $t1, .L80003648
    /* 462C 8000362C 3C01A440 */   lui       $at, %hi(D_A4400010)
    /* 4630 80003630 32310037 */  andi       $s1, $s1, 0x37
    /* 4634 80003634 AC200010 */  sw         $zero, %lo(D_A4400010)($at)
    /* 4638 80003638 0C000F09 */  jal        func_80003C24
    /* 463C 8000363C 24040038 */   addiu     $a0, $zero, 0x38
    /* 4640 80003640 12200029 */  beqz       $s1, .L800036E8
    /* 4644 80003644 00000000 */   nop
  .L80003648:
    /* 4648 80003648 32290004 */  andi       $t1, $s1, 0x4
    /* 464C 8000364C 11200009 */  beqz       $t1, .L80003674
    /* 4650 80003650 00000000 */   nop
    /* 4654 80003654 24090001 */  addiu      $t1, $zero, 0x1
    /* 4658 80003658 3C01A450 */  lui        $at, %hi(D_A450000C)
    /* 465C 8000365C 3231003B */  andi       $s1, $s1, 0x3B
    /* 4660 80003660 AC29000C */  sw         $t1, %lo(D_A450000C)($at)
    /* 4664 80003664 0C000F09 */  jal        func_80003C24
    /* 4668 80003668 24040030 */   addiu     $a0, $zero, 0x30
    /* 466C 8000366C 1220001E */  beqz       $s1, .L800036E8
    /* 4670 80003670 00000000 */   nop
  .L80003674:
    /* 4674 80003674 32290002 */  andi       $t1, $s1, 0x2
    /* 4678 80003678 11200007 */  beqz       $t1, .L80003698
    /* 467C 8000367C 3C01A480 */   lui       $at, %hi(D_A4800018)
    /* 4680 80003680 3231003D */  andi       $s1, $s1, 0x3D
    /* 4684 80003684 AC200018 */  sw         $zero, %lo(D_A4800018)($at)
    /* 4688 80003688 0C000F09 */  jal        func_80003C24
    /* 468C 8000368C 24040028 */   addiu     $a0, $zero, 0x28
    /* 4690 80003690 12200015 */  beqz       $s1, .L800036E8
    /* 4694 80003694 00000000 */   nop
  .L80003698:
    /* 4698 80003698 32290010 */  andi       $t1, $s1, 0x10
    /* 469C 8000369C 11200009 */  beqz       $t1, .L800036C4
    /* 46A0 800036A0 00000000 */   nop
    /* 46A4 800036A4 24090002 */  addiu      $t1, $zero, 0x2
    /* 46A8 800036A8 3C01A460 */  lui        $at, %hi(D_A4600010)
    /* 46AC 800036AC 3231002F */  andi       $s1, $s1, 0x2F
    /* 46B0 800036B0 AC290010 */  sw         $t1, %lo(D_A4600010)($at)
    /* 46B4 800036B4 0C000F09 */  jal        func_80003C24
    /* 46B8 800036B8 24040040 */   addiu     $a0, $zero, 0x40
    /* 46BC 800036BC 1220000A */  beqz       $s1, .L800036E8
    /* 46C0 800036C0 00000000 */   nop
  .L800036C4:
    /* 46C4 800036C4 32290020 */  andi       $t1, $s1, 0x20
    /* 46C8 800036C8 11200007 */  beqz       $t1, .L800036E8
    /* 46CC 800036CC 00000000 */   nop
    /* 46D0 800036D0 24090800 */  addiu      $t1, $zero, 0x800
    /* 46D4 800036D4 3C01A430 */  lui        $at, %hi(D_A4300000)
    /* 46D8 800036D8 3231001F */  andi       $s1, $s1, 0x1F
    /* 46DC 800036DC AC290000 */  sw         $t1, %lo(D_A4300000)($at)
    /* 46E0 800036E0 0C000F09 */  jal        func_80003C24
    /* 46E4 800036E4 24040048 */   addiu     $a0, $zero, 0x48
  .L800036E8:
    /* 46E8 800036E8 2401FBFF */  addiu      $at, $zero, -0x401
    /* 46EC 800036EC 1000FF80 */  b          .L800034F0
    /* 46F0 800036F0 02018024 */   and       $s0, $s0, $at
    /* 46F4 800036F4 8F5B0118 */  lw         $k1, 0x118($k0) /* handwritten instruction */
    /* 46F8 800036F8 2401EFFF */  addiu      $at, $zero, -0x1001
    /* 46FC 800036FC 3C098001 */  lui        $t1, %hi(D_8000A3DC)
    /* 4700 80003700 0361D824 */  and        $k1, $k1, $at
    /* 4704 80003704 AF5B0118 */  sw         $k1, 0x118($k0) /* handwritten instruction */
    /* 4708 80003708 2529A3DC */  addiu      $t1, $t1, %lo(D_8000A3DC)
    /* 470C 8000370C 8D2A0000 */  lw         $t2, 0x0($t1)
    /* 4710 80003710 11400003 */  beqz       $t2, .L80003720
    /* 4714 80003714 2401EFFF */   addiu     $at, $zero, -0x1001
    /* 4718 80003718 10000023 */  b          .L800037A8
    /* 471C 8000371C 02018024 */   and       $s0, $s0, $at
  .L80003720:
    /* 4720 80003720 240A0001 */  addiu      $t2, $zero, 0x1
    /* 4724 80003724 AD2A0000 */  sw         $t2, 0x0($t1)
    /* 4728 80003728 0C000F09 */  jal        func_80003C24
    /* 472C 8000372C 24040070 */   addiu     $a0, $zero, 0x70
    /* 4730 80003730 3C0A8001 */  lui        $t2, %hi(__osRunQueue)
    /* 4734 80003734 8D4AA418 */  lw         $t2, %lo(__osRunQueue)($t2)
    /* 4738 80003738 2401EFFF */  addiu      $at, $zero, -0x1001
    /* 473C 8000373C 02018024 */  and        $s0, $s0, $at
    /* 4740 80003740 8D5B0118 */  lw         $k1, 0x118($t2) /* handwritten instruction */
    /* 4744 80003744 0361D824 */  and        $k1, $k1, $at
    /* 4748 80003748 10000017 */  b          .L800037A8
    /* 474C 8000374C AD5B0118 */   sw        $k1, 0x118($t2) /* handwritten instruction */
    /* 4750 80003750 2401FDFF */  addiu      $at, $zero, -0x201
    /* 4754 80003754 01014024 */  and        $t0, $t0, $at
    /* 4758 80003758 40886800 */  mtc0       $t0, $13 /* handwritten instruction */
    /* 475C 8000375C 0C000F09 */  jal        func_80003C24
    /* 4760 80003760 24040008 */   addiu     $a0, $zero, 0x8
    /* 4764 80003764 2401FDFF */  addiu      $at, $zero, -0x201
    /* 4768 80003768 1000FF61 */  b          .L800034F0
    /* 476C 8000376C 02018024 */   and       $s0, $s0, $at
    /* 4770 80003770 2401FEFF */  addiu      $at, $zero, -0x101
    /* 4774 80003774 01014024 */  and        $t0, $t0, $at
    /* 4778 80003778 40886800 */  mtc0       $t0, $13 /* handwritten instruction */
    /* 477C 8000377C 0C000F09 */  jal        func_80003C24
    /* 4780 80003780 24040000 */   addiu     $a0, $zero, 0x0
    /* 4784 80003784 2401FEFF */  addiu      $at, $zero, -0x101
    /* 4788 80003788 1000FF59 */  b          .L800034F0
    /* 478C 8000378C 02018024 */   and       $s0, $s0, $at
  .L80003790:
    /* 4790 80003790 24090001 */  addiu      $t1, $zero, 0x1
    /* 4794 80003794 A7490012 */  sh         $t1, 0x12($k0) /* handwritten instruction */
    /* 4798 80003798 0C000F09 */  jal        func_80003C24
    /* 479C 8000379C 24040050 */   addiu     $a0, $zero, 0x50
    /* 47A0 800037A0 10000001 */  b          .L800037A8
    /* 47A4 800037A4 00000000 */   nop
  .L800037A8:
    /* 47A8 800037A8 3C0A8001 */  lui        $t2, %hi(__osRunQueue)
    /* 47AC 800037AC 8D4AA418 */  lw         $t2, %lo(__osRunQueue)($t2)
    /* 47B0 800037B0 8F490004 */  lw         $t1, 0x4($k0) /* handwritten instruction */
    /* 47B4 800037B4 8D4B0004 */  lw         $t3, 0x4($t2)
    /* 47B8 800037B8 012B082A */  slt        $at, $t1, $t3
    /* 47BC 800037BC 10200007 */  beqz       $at, .L800037DC
    /* 47C0 800037C0 00000000 */   nop
    /* 47C4 800037C4 3C048001 */  lui        $a0, %hi(__osRunQueue)
    /* 47C8 800037C8 03402825 */  or         $a1, $k0, $zero
    /* 47CC 800037CC 0C000F83 */  jal        func_80003E0C
    /* 47D0 800037D0 2484A418 */   addiu     $a0, $a0, %lo(__osRunQueue)
    /* 47D4 800037D4 08000F99 */  j          func_80003E64
    /* 47D8 800037D8 00000000 */   nop
  .L800037DC:
    /* 47DC 800037DC 3C098001 */  lui        $t1, %hi(__osRunQueue)
    /* 47E0 800037E0 2529A418 */  addiu      $t1, $t1, %lo(__osRunQueue)
    /* 47E4 800037E4 8D2A0000 */  lw         $t2, 0x0($t1)
    /* 47E8 800037E8 AF4A0000 */  sw         $t2, 0x0($k0) /* handwritten instruction */
    /* 47EC 800037EC 08000F99 */  j          func_80003E64
    /* 47F0 800037F0 AD3A0000 */   sw        $k0, 0x0($t1) /* handwritten instruction */
  .L800037F4:
    /* 47F4 800037F4 3C018001 */  lui        $at, %hi(D_8000A424)
    /* 47F8 800037F8 AC3AA424 */  sw         $k0, %lo(D_8000A424)($at) /* handwritten instruction */
    /* 47FC 800037FC 24090001 */  addiu      $t1, $zero, 0x1
    /* 4800 80003800 A7490010 */  sh         $t1, 0x10($k0) /* handwritten instruction */
    /* 4804 80003804 24090002 */  addiu      $t1, $zero, 0x2
    /* 4808 80003808 A7490012 */  sh         $t1, 0x12($k0) /* handwritten instruction */
    /* 480C 8000380C 400A4000 */  mfc0       $t2, $8 /* handwritten instruction */
    /* 4810 80003810 AF4A0124 */  sw         $t2, 0x124($k0) /* handwritten instruction */
    /* 4814 80003814 0C000F09 */  jal        func_80003C24
    /* 4818 80003818 24040060 */   addiu     $a0, $zero, 0x60
    /* 481C 8000381C 08000F99 */  j          func_80003E64
    /* 4820 80003820 00000000 */   nop
    /* 4824 80003824 3C0A8002 */  lui        $t2, %hi(__osEventStateTab)
    /* 4828 80003828 254A9510 */  addiu      $t2, $t2, %lo(__osEventStateTab)
    /* 482C 8000382C 01445021 */  addu       $t2, $t2, $a0
    /* 4830 80003830 8D490000 */  lw         $t1, 0x0($t2)
    /* 4834 80003834 03E09025 */  or         $s2, $ra, $zero
    /* 4838 80003838 11200025 */  beqz       $t1, .L800038D0
    /* 483C 8000383C 00000000 */   nop
    /* 4840 80003840 8D2B0008 */  lw         $t3, 0x8($t1)
    /* 4844 80003844 8D2C0010 */  lw         $t4, 0x10($t1)
    /* 4848 80003848 016C082A */  slt        $at, $t3, $t4
    /* 484C 8000384C 10200020 */  beqz       $at, .L800038D0
    /* 4850 80003850 00000000 */   nop
    /* 4854 80003854 8D2D000C */  lw         $t5, 0xC($t1)
    /* 4858 80003858 01AB6821 */  addu       $t5, $t5, $t3
    /* 485C 8000385C 01AC001A */  div        $zero, $t5, $t4
    /* 4860 80003860 15800002 */  bnez       $t4, .L8000386C
    /* 4864 80003864 00000000 */   nop
    /* 4868 80003868 0007000D */  break      7
  .L8000386C:
    /* 486C 8000386C 2401FFFF */  addiu      $at, $zero, -0x1
    /* 4870 80003870 15810004 */  bne        $t4, $at, .L80003884
    /* 4874 80003874 3C018000 */   lui       $at, (0x80000000 >> 16)
    /* 4878 80003878 15A10002 */  bne        $t5, $at, .L80003884
    /* 487C 8000387C 00000000 */   nop
    /* 4880 80003880 0006000D */  break      6
  .L80003884:
    /* 4884 80003884 8D2C0014 */  lw         $t4, 0x14($t1)
    /* 4888 80003888 00006810 */  mfhi       $t5
    /* 488C 8000388C 000D6880 */  sll        $t5, $t5, 2
    /* 4890 80003890 018D6021 */  addu       $t4, $t4, $t5
    /* 4894 80003894 8D4D0004 */  lw         $t5, 0x4($t2)
    /* 4898 80003898 256A0001 */  addiu      $t2, $t3, 0x1
    /* 489C 8000389C AD8D0000 */  sw         $t5, 0x0($t4)
    /* 48A0 800038A0 AD2A0008 */  sw         $t2, 0x8($t1)
    /* 48A4 800038A4 8D2A0000 */  lw         $t2, 0x0($t1)
    /* 48A8 800038A8 8D4B0000 */  lw         $t3, 0x0($t2)
    /* 48AC 800038AC 11600008 */  beqz       $t3, .L800038D0
    /* 48B0 800038B0 00000000 */   nop
    /* 48B4 800038B4 0C000F95 */  jal        func_80003E54
    /* 48B8 800038B8 01202025 */   or        $a0, $t1, $zero
    /* 48BC 800038BC 00405025 */  or         $t2, $v0, $zero
    /* 48C0 800038C0 3C048001 */  lui        $a0, %hi(__osRunQueue)
    /* 48C4 800038C4 01402825 */  or         $a1, $t2, $zero
    /* 48C8 800038C8 0C000F83 */  jal        func_80003E0C
    /* 48CC 800038CC 2484A418 */   addiu     $a0, $a0, %lo(__osRunQueue)
  .L800038D0:
    /* 48D0 800038D0 02400008 */  jr         $s2
    /* 48D4 800038D4 00000000 */   nop
  .L800038D8:
    /* 48D8 800038D8 3C013000 */  lui        $at, (0x30000000 >> 16)
    /* 48DC 800038DC 01014824 */  and        $t1, $t0, $at
    /* 48E0 800038E0 00094F02 */  srl        $t1, $t1, 28
    /* 48E4 800038E4 240A0001 */  addiu      $t2, $zero, 0x1
    /* 48E8 800038E8 152AFFC2 */  bne        $t1, $t2, .L800037F4
    /* 48EC 800038EC 00000000 */   nop
    /* 48F0 800038F0 8F5B0118 */  lw         $k1, 0x118($k0) /* handwritten instruction */
    /* 48F4 800038F4 3C012000 */  lui        $at, (0x20000000 >> 16)
    /* 48F8 800038F8 24090001 */  addiu      $t1, $zero, 0x1
    /* 48FC 800038FC 0361D825 */  or         $k1, $k1, $at
    /* 4900 80003900 AF490018 */  sw         $t1, 0x18($k0) /* handwritten instruction */
    /* 4904 80003904 1000FFB5 */  b          .L800037DC
    /* 4908 80003908 AF5B0118 */   sw        $k1, 0x118($k0) /* handwritten instruction */
    /* 490C 8000390C 3C058001 */  lui        $a1, %hi(__osRunningThread)
    /* 4910 80003910 8CA5A420 */  lw         $a1, %lo(__osRunningThread)($a1)
    /* 4914 80003914 40086000 */  mfc0       $t0, $12 /* handwritten instruction */
    /* 4918 80003918 8CBB0018 */  lw         $k1, 0x18($a1) /* handwritten instruction */
    /* 491C 8000391C 35080002 */  ori        $t0, $t0, 0x2
    /* 4920 80003920 ACA80118 */  sw         $t0, 0x118($a1)
    /* 4924 80003924 FCB00098 */  sd         $s0, 0x98($a1)
    /* 4928 80003928 FCB100A0 */  sd         $s1, 0xA0($a1)
    /* 492C 8000392C FCB200A8 */  sd         $s2, 0xA8($a1)
    /* 4930 80003930 FCB300B0 */  sd         $s3, 0xB0($a1)
    /* 4934 80003934 FCB400B8 */  sd         $s4, 0xB8($a1)
    /* 4938 80003938 FCB500C0 */  sd         $s5, 0xC0($a1)
    /* 493C 8000393C FCB600C8 */  sd         $s6, 0xC8($a1)
    /* 4940 80003940 FCB700D0 */  sd         $s7, 0xD0($a1)
    /* 4944 80003944 FCBC00E8 */  sd         $gp, 0xE8($a1)
    /* 4948 80003948 FCBD00F0 */  sd         $sp, 0xF0($a1)
    /* 494C 8000394C FCBE00F8 */  sd         $fp, 0xF8($a1)
    /* 4950 80003950 FCBF0100 */  sd         $ra, 0x100($a1)
    /* 4954 80003954 13600009 */  beqz       $k1, .L8000397C /* handwritten instruction */
    /* 4958 80003958 ACBF011C */   sw        $ra, 0x11C($a1)
    /* 495C 8000395C 445BF800 */  cfc1       $k1, $31
    /* 4960 80003960 F4B40180 */  sdc1       $f20, 0x180($a1)
    /* 4964 80003964 F4B60188 */  sdc1       $f22, 0x188($a1)
    /* 4968 80003968 F4B80190 */  sdc1       $f24, 0x190($a1)
    /* 496C 8000396C F4BA0198 */  sdc1       $f26, 0x198($a1)
    /* 4970 80003970 F4BC01A0 */  sdc1       $f28, 0x1A0($a1)
    /* 4974 80003974 F4BE01A8 */  sdc1       $f30, 0x1A8($a1)
    /* 4978 80003978 ACBB012C */  sw         $k1, 0x12C($a1) /* handwritten instruction */
  .L8000397C:
    /* 497C 8000397C 8CBB0118 */  lw         $k1, 0x118($a1) /* handwritten instruction */
    /* 4980 80003980 3369FF00 */  andi       $t1, $k1, 0xFF00 /* handwritten instruction */
    /* 4984 80003984 1120000D */  beqz       $t1, .L800039BC
    /* 4988 80003988 00000000 */   nop
    /* 498C 8000398C 3C088001 */  lui        $t0, %hi(__OSGlobalIntMask)
    /* 4990 80003990 2508A3E0 */  addiu      $t0, $t0, %lo(__OSGlobalIntMask)
    /* 4994 80003994 8D080000 */  lw         $t0, 0x0($t0)
    /* 4998 80003998 2401FFFF */  addiu      $at, $zero, -0x1
    /* 499C 8000399C 01014026 */  xor        $t0, $t0, $at
    /* 49A0 800039A0 3C01FFFF */  lui        $at, (0xFFFF00FF >> 16)
    /* 49A4 800039A4 3108FF00 */  andi       $t0, $t0, 0xFF00
    /* 49A8 800039A8 342100FF */  ori        $at, $at, (0xFFFF00FF & 0xFFFF)
    /* 49AC 800039AC 01284825 */  or         $t1, $t1, $t0
    /* 49B0 800039B0 0361D824 */  and        $k1, $k1, $at
    /* 49B4 800039B4 0369D825 */  or         $k1, $k1, $t1
    /* 49B8 800039B8 ACBB0118 */  sw         $k1, 0x118($a1) /* handwritten instruction */
  .L800039BC:
    /* 49BC 800039BC 3C1BA430 */  lui        $k1, %hi(D_A430000C) /* handwritten instruction */
    /* 49C0 800039C0 8F7B000C */  lw         $k1, %lo(D_A430000C)($k1) /* handwritten instruction */
    /* 49C4 800039C4 1360000B */  beqz       $k1, .L800039F4 /* handwritten instruction */
    /* 49C8 800039C8 00000000 */   nop
    /* 49CC 800039CC 3C1A8001 */  lui        $k0, %hi(__OSGlobalIntMask) /* handwritten instruction */
    /* 49D0 800039D0 275AA3E0 */  addiu      $k0, $k0, %lo(__OSGlobalIntMask) /* handwritten instruction */
    /* 49D4 800039D4 8F5A0000 */  lw         $k0, 0x0($k0) /* handwritten instruction */
    /* 49D8 800039D8 8CA80128 */  lw         $t0, 0x128($a1)
    /* 49DC 800039DC 2401FFFF */  addiu      $at, $zero, -0x1
    /* 49E0 800039E0 001AD402 */  srl        $k0, $k0, 16
    /* 49E4 800039E4 0341D026 */  xor        $k0, $k0, $at
    /* 49E8 800039E8 335A003F */  andi       $k0, $k0, 0x3F /* handwritten instruction */
    /* 49EC 800039EC 0348D024 */  and        $k0, $k0, $t0
    /* 49F0 800039F0 037AD825 */  or         $k1, $k1, $k0
  .L800039F4:
    /* 49F4 800039F4 10800003 */  beqz       $a0, .L80003A04
    /* 49F8 800039F8 ACBB0128 */   sw        $k1, 0x128($a1) /* handwritten instruction */
    /* 49FC 800039FC 0C000F83 */  jal        func_80003E0C
    /* 4A00 80003A00 00000000 */   nop
  .L80003A04:
    /* 4A04 80003A04 08000F99 */  j          func_80003E64
    /* 4A08 80003A08 00000000 */   nop
    /* 4A0C 80003A0C 8C980000 */  lw         $t8, 0x0($a0)
    /* 4A10 80003A10 8CAF0004 */  lw         $t7, 0x4($a1)
    /* 4A14 80003A14 0080C825 */  or         $t9, $a0, $zero
    /* 4A18 80003A18 8F0E0004 */  lw         $t6, 0x4($t8)
    /* 4A1C 80003A1C 01CF082A */  slt        $at, $t6, $t7
    /* 4A20 80003A20 14200007 */  bnez       $at, .L80003A40
    /* 4A24 80003A24 00000000 */   nop
  .L80003A28:
    /* 4A28 80003A28 0300C825 */  or         $t9, $t8, $zero
    /* 4A2C 80003A2C 8F180000 */  lw         $t8, 0x0($t8)
    /* 4A30 80003A30 8F0E0004 */  lw         $t6, 0x4($t8)
    /* 4A34 80003A34 01CF082A */  slt        $at, $t6, $t7
    /* 4A38 80003A38 1020FFFB */  beqz       $at, .L80003A28
    /* 4A3C 80003A3C 00000000 */   nop
  .L80003A40:
    /* 4A40 80003A40 8F380000 */  lw         $t8, 0x0($t9)
    /* 4A44 80003A44 ACB80000 */  sw         $t8, 0x0($a1)
    /* 4A48 80003A48 AF250000 */  sw         $a1, 0x0($t9)
    /* 4A4C 80003A4C 03E00008 */  jr         $ra
    /* 4A50 80003A50 ACA40008 */   sw        $a0, 0x8($a1)
    /* 4A54 80003A54 8C820000 */  lw         $v0, 0x0($a0)
    /* 4A58 80003A58 8C590000 */  lw         $t9, 0x0($v0)
    /* 4A5C 80003A5C 03E00008 */  jr         $ra
    /* 4A60 80003A60 AC990000 */   sw        $t9, 0x0($a0)
    /* 4A64 80003A64 3C048001 */  lui        $a0, %hi(__osRunQueue)
    /* 4A68 80003A68 0C000F95 */  jal        func_80003E54
    /* 4A6C 80003A6C 2484A418 */   addiu     $a0, $a0, %lo(__osRunQueue)
    /* 4A70 80003A70 3C018001 */  lui        $at, %hi(__osRunningThread)
    /* 4A74 80003A74 AC22A420 */  sw         $v0, %lo(__osRunningThread)($at)
    /* 4A78 80003A78 24080004 */  addiu      $t0, $zero, 0x4
    /* 4A7C 80003A7C A4480010 */  sh         $t0, 0x10($v0)
    /* 4A80 80003A80 0040D025 */  or         $k0, $v0, $zero
  .L80003A84:
    /* 4A84 80003A84 3C088001 */  lui        $t0, %hi(__OSGlobalIntMask)
    /* 4A88 80003A88 8F5B0118 */  lw         $k1, 0x118($k0) /* handwritten instruction */
    /* 4A8C 80003A8C 2508A3E0 */  addiu      $t0, $t0, %lo(__OSGlobalIntMask)
    /* 4A90 80003A90 8D080000 */  lw         $t0, 0x0($t0)
    /* 4A94 80003A94 3C01FFFF */  lui        $at, (0xFFFF00FF >> 16)
    /* 4A98 80003A98 3369FF00 */  andi       $t1, $k1, 0xFF00 /* handwritten instruction */
    /* 4A9C 80003A9C 342100FF */  ori        $at, $at, (0xFFFF00FF & 0xFFFF)
    /* 4AA0 80003AA0 3108FF00 */  andi       $t0, $t0, 0xFF00
    /* 4AA4 80003AA4 01284824 */  and        $t1, $t1, $t0
    /* 4AA8 80003AA8 0361D824 */  and        $k1, $k1, $at
    /* 4AAC 80003AAC 0369D825 */  or         $k1, $k1, $t1
    /* 4AB0 80003AB0 409B6000 */  mtc0       $k1, $12 /* handwritten instruction */
    /* 4AB4 80003AB4 DF5B0108 */  ld         $k1, 0x108($k0) /* handwritten instruction */
    /* 4AB8 80003AB8 DF410020 */  ld         $at, 0x20($k0) /* handwritten instruction */
    /* 4ABC 80003ABC DF420028 */  ld         $v0, 0x28($k0) /* handwritten instruction */
    /* 4AC0 80003AC0 03600013 */  mtlo       $k1
    /* 4AC4 80003AC4 DF5B0110 */  ld         $k1, 0x110($k0) /* handwritten instruction */
    /* 4AC8 80003AC8 DF430030 */  ld         $v1, 0x30($k0) /* handwritten instruction */
    /* 4ACC 80003ACC DF440038 */  ld         $a0, 0x38($k0) /* handwritten instruction */
    /* 4AD0 80003AD0 DF450040 */  ld         $a1, 0x40($k0) /* handwritten instruction */
    /* 4AD4 80003AD4 DF460048 */  ld         $a2, 0x48($k0) /* handwritten instruction */
    /* 4AD8 80003AD8 DF470050 */  ld         $a3, 0x50($k0) /* handwritten instruction */
    /* 4ADC 80003ADC DF480058 */  ld         $t0, 0x58($k0) /* handwritten instruction */
    /* 4AE0 80003AE0 DF490060 */  ld         $t1, 0x60($k0) /* handwritten instruction */
    /* 4AE4 80003AE4 DF4A0068 */  ld         $t2, 0x68($k0) /* handwritten instruction */
    /* 4AE8 80003AE8 DF4B0070 */  ld         $t3, 0x70($k0) /* handwritten instruction */
    /* 4AEC 80003AEC DF4C0078 */  ld         $t4, 0x78($k0) /* handwritten instruction */
    /* 4AF0 80003AF0 DF4D0080 */  ld         $t5, 0x80($k0) /* handwritten instruction */
    /* 4AF4 80003AF4 DF4E0088 */  ld         $t6, 0x88($k0) /* handwritten instruction */
    /* 4AF8 80003AF8 DF4F0090 */  ld         $t7, 0x90($k0) /* handwritten instruction */
    /* 4AFC 80003AFC DF500098 */  ld         $s0, 0x98($k0) /* handwritten instruction */
    /* 4B00 80003B00 DF5100A0 */  ld         $s1, 0xA0($k0) /* handwritten instruction */
    /* 4B04 80003B04 DF5200A8 */  ld         $s2, 0xA8($k0) /* handwritten instruction */
    /* 4B08 80003B08 DF5300B0 */  ld         $s3, 0xB0($k0) /* handwritten instruction */
    /* 4B0C 80003B0C DF5400B8 */  ld         $s4, 0xB8($k0) /* handwritten instruction */
    /* 4B10 80003B10 DF5500C0 */  ld         $s5, 0xC0($k0) /* handwritten instruction */
    /* 4B14 80003B14 DF5600C8 */  ld         $s6, 0xC8($k0) /* handwritten instruction */
    /* 4B18 80003B18 DF5700D0 */  ld         $s7, 0xD0($k0) /* handwritten instruction */
    /* 4B1C 80003B1C DF5800D8 */  ld         $t8, 0xD8($k0) /* handwritten instruction */
    /* 4B20 80003B20 DF5900E0 */  ld         $t9, 0xE0($k0) /* handwritten instruction */
    /* 4B24 80003B24 DF5C00E8 */  ld         $gp, 0xE8($k0) /* handwritten instruction */
    /* 4B28 80003B28 03600011 */  mthi       $k1
    /* 4B2C 80003B2C DF5D00F0 */  ld         $sp, 0xF0($k0) /* handwritten instruction */
    /* 4B30 80003B30 DF5E00F8 */  ld         $fp, 0xF8($k0) /* handwritten instruction */
    /* 4B34 80003B34 DF5F0100 */  ld         $ra, 0x100($k0) /* handwritten instruction */
    /* 4B38 80003B38 8F5B011C */  lw         $k1, 0x11C($k0) /* handwritten instruction */
    /* 4B3C 80003B3C 409B7000 */  mtc0       $k1, $14 /* handwritten instruction */
    /* 4B40 80003B40 8F5B0018 */  lw         $k1, 0x18($k0) /* handwritten instruction */
    /* 4B44 80003B44 13600013 */  beqz       $k1, .L80003B94 /* handwritten instruction */
    /* 4B48 80003B48 00000000 */   nop
    /* 4B4C 80003B4C 8F5B012C */  lw         $k1, 0x12C($k0) /* handwritten instruction */
    /* 4B50 80003B50 44DBF800 */  ctc1       $k1, $31
    /* 4B54 80003B54 D7400130 */  ldc1       $f0, 0x130($k0)
    /* 4B58 80003B58 D7420138 */  ldc1       $f2, 0x138($k0)
    /* 4B5C 80003B5C D7440140 */  ldc1       $f4, 0x140($k0)
    /* 4B60 80003B60 D7460148 */  ldc1       $f6, 0x148($k0)
    /* 4B64 80003B64 D7480150 */  ldc1       $f8, 0x150($k0)
    /* 4B68 80003B68 D74A0158 */  ldc1       $f10, 0x158($k0)
    /* 4B6C 80003B6C D74C0160 */  ldc1       $f12, 0x160($k0)
    /* 4B70 80003B70 D74E0168 */  ldc1       $f14, 0x168($k0)
    /* 4B74 80003B74 D7500170 */  ldc1       $f16, 0x170($k0)
    /* 4B78 80003B78 D7520178 */  ldc1       $f18, 0x178($k0)
    /* 4B7C 80003B7C D7540180 */  ldc1       $f20, 0x180($k0)
    /* 4B80 80003B80 D7560188 */  ldc1       $f22, 0x188($k0)
    /* 4B84 80003B84 D7580190 */  ldc1       $f24, 0x190($k0)
    /* 4B88 80003B88 D75A0198 */  ldc1       $f26, 0x198($k0)
    /* 4B8C 80003B8C D75C01A0 */  ldc1       $f28, 0x1A0($k0)
    /* 4B90 80003B90 D75E01A8 */  ldc1       $f30, 0x1A8($k0)
  .L80003B94:
    /* 4B94 80003B94 8F5B0128 */  lw         $k1, 0x128($k0) /* handwritten instruction */
    /* 4B98 80003B98 3C1A8001 */  lui        $k0, %hi(__OSGlobalIntMask) /* handwritten instruction */
    /* 4B9C 80003B9C 275AA3E0 */  addiu      $k0, $k0, %lo(__OSGlobalIntMask) /* handwritten instruction */
    /* 4BA0 80003BA0 8F5A0000 */  lw         $k0, 0x0($k0) /* handwritten instruction */
    /* 4BA4 80003BA4 001AD402 */  srl        $k0, $k0, 16
    /* 4BA8 80003BA8 037AD824 */  and        $k1, $k1, $k0
    /* 4BAC 80003BAC 001BD840 */  sll        $k1, $k1, 1
    /* 4BB0 80003BB0 3C1A8001 */  lui        $k0, %hi(__osRcpImTable) /* handwritten instruction */
    /* 4BB4 80003BB4 275AA680 */  addiu      $k0, $k0, %lo(__osRcpImTable) /* handwritten instruction */
    /* 4BB8 80003BB8 037AD821 */  addu       $k1, $k1, $k0
    /* 4BBC 80003BBC 977B0000 */  lhu        $k1, 0x0($k1) /* handwritten instruction */
    /* 4BC0 80003BC0 3C1AA430 */  lui        $k0, %hi(D_A430000C) /* handwritten instruction */
    /* 4BC4 80003BC4 275A000C */  addiu      $k0, $k0, %lo(D_A430000C) /* handwritten instruction */
    /* 4BC8 80003BC8 AF5B0000 */  sw         $k1, 0x0($k0) /* handwritten instruction */
    /* 4BCC 80003BCC 00000000 */  nop
    /* 4BD0 80003BD0 00000000 */  nop
    /* 4BD4 80003BD4 00000000 */  nop
    /* 4BD8 80003BD8 00000000 */  nop
    /* 4BDC 80003BDC 42000018 */  eret /* handwritten instruction */
    /* 4BE0 80003BE0 0C00100C */  jal        func_80004030
    /* 4BE4 80003BE4 00002025 */   or        $a0, $zero, $zero
    /* 4BE8 80003BE8 00000000 */  nop
    /* 4BEC 80003BEC 00000000 */  nop
    /* 4BF0 80003BF0 00803025 */  or         $a2, $a0, $zero
    /* 4BF4 80003BF4 8CC70000 */  lw         $a3, 0x0($a2)
    /* 4BF8 80003BF8 27BDFFF8 */  addiu      $sp, $sp, -0x8
    /* 4BFC 80003BFC 10E0000A */  beqz       $a3, .L80003C28
    /* 4C00 80003C00 00000000 */   nop
  .L80003C04:
    /* 4C04 80003C04 14E50004 */  bne        $a3, $a1, .L80003C18
    /* 4C08 80003C08 00000000 */   nop
    /* 4C0C 80003C0C 8CAE0000 */  lw         $t6, 0x0($a1)
    /* 4C10 80003C10 10000005 */  b          .L80003C28
    /* 4C14 80003C14 ACCE0000 */   sw        $t6, 0x0($a2)
  .L80003C18:
    /* 4C18 80003C18 00E03025 */  or         $a2, $a3, $zero
    /* 4C1C 80003C1C 8CC70000 */  lw         $a3, 0x0($a2)
    /* 4C20 80003C20 14E0FFF8 */  bnez       $a3, .L80003C04
endlabel func_800031F0
