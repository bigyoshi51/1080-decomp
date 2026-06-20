nonmatching func_0000D900, 0x4C4

glabel func_0000D900
    /* DDE36C 0000D900 27BDFF70 */  addiu      $sp, $sp, -0x90
    /* DDE370 0000D904 AFBF0014 */  sw         $ra, 0x14($sp)
    /* DDE374 0000D908 8CA20000 */  lw         $v0, 0x0($a1)
    /* DDE378 0000D90C 24010014 */  addiu      $at, $zero, 0x14
    /* DDE37C 0000D910 00803825 */  or         $a3, $a0, $zero
    /* DDE380 0000D914 1041001D */  beq        $v0, $at, .L0000D98C
    /* DDE384 0000D918 24010009 */   addiu     $at, $zero, 0x9
    /* DDE388 0000D91C 104100A6 */  beq        $v0, $at, .L0000DBB8
    /* DDE38C 0000D920 24030006 */   addiu     $v1, $zero, 0x6
    /* DDE390 0000D924 104300A8 */  beq        $v0, $v1, .L0000DBC8
    /* DDE394 0000D928 240103E8 */   addiu     $at, $zero, 0x3E8
    /* DDE398 0000D92C 104100CB */  beq        $v0, $at, .L0000DC5C
    /* DDE39C 0000D930 240C0001 */   addiu     $t4, $zero, 0x1
    /* DDE3A0 0000D934 240103E9 */  addiu      $at, $zero, 0x3E9
    /* DDE3A4 0000D938 104100D3 */  beq        $v0, $at, .L0000DC88
    /* DDE3A8 0000D93C 240F0002 */   addiu     $t7, $zero, 0x2
    /* DDE3AC 0000D940 240103EB */  addiu      $at, $zero, 0x3EB
    /* DDE3B0 0000D944 104100DB */  beq        $v0, $at, .L0000DCB4
    /* DDE3B4 0000D948 24080003 */   addiu     $t0, $zero, 0x3
    /* DDE3B8 0000D94C 240103EA */  addiu      $at, $zero, 0x3EA
    /* DDE3BC 0000D950 104100E5 */  beq        $v0, $at, .L0000DCE8
    /* DDE3C0 0000D954 240B0004 */   addiu     $t3, $zero, 0x4
    /* DDE3C4 0000D958 240103EC */  addiu      $at, $zero, 0x3EC
    /* DDE3C8 0000D95C 104100E4 */  beq        $v0, $at, .L0000DCF0
    /* DDE3CC 0000D960 240C0005 */   addiu     $t4, $zero, 0x5
    /* DDE3D0 0000D964 240103ED */  addiu      $at, $zero, 0x3ED
    /* DDE3D4 0000D968 104100E3 */  beq        $v0, $at, .L0000DCF8
    /* DDE3D8 0000D96C 3C040001 */   lui       $a0, %hi(func_00008B44 + 0x10)
    /* DDE3DC 0000D970 240103EE */  addiu      $at, $zero, 0x3EE
    /* DDE3E0 0000D974 104100E0 */  beq        $v0, $at, .L0000DCF8
    /* DDE3E4 0000D978 240103EF */   addiu     $at, $zero, 0x3EF
    /* DDE3E8 0000D97C 504100DF */  beql       $v0, $at, .L0000DCFC
    /* DDE3EC 0000D980 ACE30A54 */   sw        $v1, 0xA54($a3)
    /* DDE3F0 0000D984 10000109 */  b          .L0000DDAC
    /* DDE3F4 0000D988 00000000 */   nop
  .L0000D98C:
    /* DDE3F8 0000D98C 8CEE0A80 */  lw         $t6, 0xA80($a3)
    /* DDE3FC 0000D990 55C00109 */  bnel       $t6, $zero, .L0000DDB8
    /* DDE400 0000D994 8FBF0014 */   lw        $ra, 0x14($sp)
    /* DDE404 0000D998 8CA20004 */  lw         $v0, 0x4($a1)
    /* DDE408 0000D99C 3C010000 */  lui        $at, %hi(D_00000988)
    /* DDE40C 0000D9A0 D4260988 */  ldc1       $f6, %lo(D_00000988)($at)
    /* DDE410 0000D9A4 C442000C */  lwc1       $f2, 0xC($v0)
    /* DDE414 0000D9A8 46001121 */  cvt.d.s    $f4, $f2
    /* DDE418 0000D9AC 4626203C */  c.lt.d     $f4, $f6
    /* DDE41C 0000D9B0 00000000 */  nop
    /* DDE420 0000D9B4 4502000B */  bc1fl      .L0000D9E4
    /* DDE424 0000D9B8 44806000 */   mtc1      $zero, $f12
    /* DDE428 0000D9BC 8C4F0028 */  lw         $t7, 0x28($v0)
    /* DDE42C 0000D9C0 24010074 */  addiu      $at, $zero, 0x74
    /* DDE430 0000D9C4 95F8000C */  lhu        $t8, 0xC($t7)
    /* DDE434 0000D9C8 57010006 */  bnel       $t8, $at, .L0000D9E4
    /* DDE438 0000D9CC 44806000 */   mtc1      $zero, $f12
    /* DDE43C 0000D9D0 0C000000 */  jal        func_00000000
    /* DDE440 0000D9D4 24E40808 */   addiu     $a0, $a3, 0x808
    /* DDE444 0000D9D8 100000F7 */  b          .L0000DDB8
    /* DDE448 0000D9DC 8FBF0014 */   lw        $ra, 0x14($sp)
    /* DDE44C 0000D9E0 44806000 */  mtc1       $zero, $f12
  .L0000D9E4:
    /* DDE450 0000D9E4 46001006 */  mov.s      $f0, $f2
    /* DDE454 0000D9E8 3C014248 */  lui        $at, (0x42480000 >> 16)
    /* DDE458 0000D9EC 460C103C */  c.lt.s     $f2, $f12
    /* DDE45C 0000D9F0 00000000 */  nop
    /* DDE460 0000D9F4 45020004 */  bc1fl      .L0000DA08
    /* DDE464 0000D9F8 44816000 */   mtc1      $at, $f12
    /* DDE468 0000D9FC 1000000A */  b          .L0000DA28
    /* DDE46C 0000DA00 46006086 */   mov.s     $f2, $f12
    /* DDE470 0000DA04 44816000 */  mtc1       $at, $f12
  .L0000DA08:
    /* DDE474 0000DA08 00000000 */  nop
    /* DDE478 0000DA0C 4600603C */  c.lt.s     $f12, $f0
    /* DDE47C 0000DA10 00000000 */  nop
    /* DDE480 0000DA14 45020004 */  bc1fl      .L0000DA28
    /* DDE484 0000DA18 46000086 */   mov.s     $f2, $f0
    /* DDE488 0000DA1C 10000002 */  b          .L0000DA28
    /* DDE48C 0000DA20 46006086 */   mov.s     $f2, $f12
    /* DDE490 0000DA24 46000086 */  mov.s      $f2, $f0
  .L0000DA28:
    /* DDE494 0000DA28 C4480000 */  lwc1       $f8, 0x0($v0)
    /* DDE498 0000DA2C C44A0004 */  lwc1       $f10, 0x4($v0)
    /* DDE49C 0000DA30 46001306 */  mov.s      $f12, $f2
    /* DDE4A0 0000DA34 46024002 */  mul.s      $f0, $f8, $f2
    /* DDE4A4 0000DA38 C4500008 */  lwc1       $f16, 0x8($v0)
    /* DDE4A8 0000DA3C 27B90048 */  addiu      $t9, $sp, 0x48
    /* DDE4AC 0000DA40 46025082 */  mul.s      $f2, $f10, $f2
    /* DDE4B0 0000DA44 27A30054 */  addiu      $v1, $sp, 0x54
    /* DDE4B4 0000DA48 27AA006C */  addiu      $t2, $sp, 0x6C
    /* DDE4B8 0000DA4C 460C8382 */  mul.s      $f14, $f16, $f12
    /* DDE4BC 0000DA50 E7A00048 */  swc1       $f0, 0x48($sp)
    /* DDE4C0 0000DA54 3C010000 */  lui        $at, %hi(func_0000098C + 0x4)
    /* DDE4C4 0000DA58 E7A2004C */  swc1       $f2, 0x4C($sp)
    /* DDE4C8 0000DA5C E7AE0050 */  swc1       $f14, 0x50($sp)
    /* DDE4CC 0000DA60 8F290000 */  lw         $t1, 0x0($t9)
    /* DDE4D0 0000DA64 AC690000 */  sw         $t1, 0x0($v1)
    /* DDE4D4 0000DA68 8F280004 */  lw         $t0, 0x4($t9)
    /* DDE4D8 0000DA6C 8C6C0000 */  lw         $t4, 0x0($v1)
    /* DDE4DC 0000DA70 AC680004 */  sw         $t0, 0x4($v1)
    /* DDE4E0 0000DA74 8F290008 */  lw         $t1, 0x8($t9)
    /* DDE4E4 0000DA78 2419000A */  addiu      $t9, $zero, 0xA
    /* DDE4E8 0000DA7C AC690008 */  sw         $t1, 0x8($v1)
    /* DDE4EC 0000DA80 AD4C0000 */  sw         $t4, 0x0($t2)
    /* DDE4F0 0000DA84 8C6B0004 */  lw         $t3, 0x4($v1)
    /* DDE4F4 0000DA88 AD4B0004 */  sw         $t3, 0x4($t2)
    /* DDE4F8 0000DA8C 8C6C0008 */  lw         $t4, 0x8($v1)
    /* DDE4FC 0000DA90 AD4C0008 */  sw         $t4, 0x8($t2)
    /* DDE500 0000DA94 C7A4006C */  lwc1       $f4, 0x6C($sp)
    /* DDE504 0000DA98 C4F200B4 */  lwc1       $f18, 0xB4($a3)
    /* DDE508 0000DA9C C4E800B8 */  lwc1       $f8, 0xB8($a3)
    /* DDE50C 0000DAA0 94ED0A10 */  lhu        $t5, 0xA10($a3)
    /* DDE510 0000DAA4 46049180 */  add.s      $f6, $f18, $f4
    /* DDE514 0000DAA8 C4F200BC */  lwc1       $f18, 0xBC($a3)
    /* DDE518 0000DAAC 35AE01F0 */  ori        $t6, $t5, 0x1F0
    /* DDE51C 0000DAB0 E4E600B4 */  swc1       $f6, 0xB4($a3)
    /* DDE520 0000DAB4 C7AA0070 */  lwc1       $f10, 0x70($sp)
    /* DDE524 0000DAB8 460A4400 */  add.s      $f16, $f8, $f10
    /* DDE528 0000DABC C4E80318 */  lwc1       $f8, 0x318($a3)
    /* DDE52C 0000DAC0 E4F000B8 */  swc1       $f16, 0xB8($a3)
    /* DDE530 0000DAC4 C7A40074 */  lwc1       $f4, 0x74($sp)
    /* DDE534 0000DAC8 46049180 */  add.s      $f6, $f18, $f4
    /* DDE538 0000DACC C4F2031C */  lwc1       $f18, 0x31C($a3)
    /* DDE53C 0000DAD0 E4E600BC */  swc1       $f6, 0xBC($a3)
    /* DDE540 0000DAD4 C7AA006C */  lwc1       $f10, 0x6C($sp)
    /* DDE544 0000DAD8 460A4400 */  add.s      $f16, $f8, $f10
    /* DDE548 0000DADC C4E80320 */  lwc1       $f8, 0x320($a3)
    /* DDE54C 0000DAE0 E4F00318 */  swc1       $f16, 0x318($a3)
    /* DDE550 0000DAE4 C7A40070 */  lwc1       $f4, 0x70($sp)
    /* DDE554 0000DAE8 46049180 */  add.s      $f6, $f18, $f4
    /* DDE558 0000DAEC C4F203BC */  lwc1       $f18, 0x3BC($a3)
    /* DDE55C 0000DAF0 E4E6031C */  swc1       $f6, 0x31C($a3)
    /* DDE560 0000DAF4 C7AA0074 */  lwc1       $f10, 0x74($sp)
    /* DDE564 0000DAF8 460A4400 */  add.s      $f16, $f8, $f10
    /* DDE568 0000DAFC C4E803C0 */  lwc1       $f8, 0x3C0($a3)
    /* DDE56C 0000DB00 E4F00320 */  swc1       $f16, 0x320($a3)
    /* DDE570 0000DB04 C7A4006C */  lwc1       $f4, 0x6C($sp)
    /* DDE574 0000DB08 C7AA0070 */  lwc1       $f10, 0x70($sp)
    /* DDE578 0000DB0C 46049182 */  mul.s      $f6, $f18, $f4
    /* DDE57C 0000DB10 C4E403C4 */  lwc1       $f4, 0x3C4($a3)
    /* DDE580 0000DB14 460A4402 */  mul.s      $f16, $f8, $f10
    /* DDE584 0000DB18 C7A80074 */  lwc1       $f8, 0x74($sp)
    /* DDE588 0000DB1C 46082282 */  mul.s      $f10, $f4, $f8
    /* DDE58C 0000DB20 C4E80A1C */  lwc1       $f8, 0xA1C($a3)
    /* DDE590 0000DB24 46103480 */  add.s      $f18, $f6, $f16
    /* DDE594 0000DB28 D4300990 */  ldc1       $f16, %lo(func_0000098C + 0x4)($at)
    /* DDE598 0000DB2C 3C013FE0 */  lui        $at, (0x3FE00000 >> 16)
    /* DDE59C 0000DB30 44814800 */  mtc1       $at, $f9
    /* DDE5A0 0000DB34 460A9000 */  add.s      $f0, $f18, $f10
    /* DDE5A4 0000DB38 460044A1 */  cvt.d.s    $f18, $f8
    /* DDE5A8 0000DB3C 460001A1 */  cvt.d.s    $f6, $f0
    /* DDE5AC 0000DB40 46303102 */  mul.d      $f4, $f6, $f16
    /* DDE5B0 0000DB44 C4F003C8 */  lwc1       $f16, 0x3C8($a3)
    /* DDE5B4 0000DB48 46249280 */  add.d      $f10, $f18, $f4
    /* DDE5B8 0000DB4C C4E403CC */  lwc1       $f4, 0x3CC($a3)
    /* DDE5BC 0000DB50 462051A0 */  cvt.s.d    $f6, $f10
    /* DDE5C0 0000DB54 E4E60A1C */  swc1       $f6, 0xA1C($a3)
    /* DDE5C4 0000DB58 C7A8006C */  lwc1       $f8, 0x6C($sp)
    /* DDE5C8 0000DB5C C7AA0070 */  lwc1       $f10, 0x70($sp)
    /* DDE5CC 0000DB60 46088482 */  mul.s      $f18, $f16, $f8
    /* DDE5D0 0000DB64 C4E803D0 */  lwc1       $f8, 0x3D0($a3)
    /* DDE5D4 0000DB68 460A2182 */  mul.s      $f6, $f4, $f10
    /* DDE5D8 0000DB6C C7A40074 */  lwc1       $f4, 0x74($sp)
    /* DDE5DC 0000DB70 A4EE0A10 */  sh         $t6, 0xA10($a3)
    /* DDE5E0 0000DB74 46044282 */  mul.s      $f10, $f8, $f4
    /* DDE5E4 0000DB78 44804000 */  mtc1       $zero, $f8
    /* DDE5E8 0000DB7C 46069400 */  add.s      $f16, $f18, $f6
    /* DDE5EC 0000DB80 460A8000 */  add.s      $f0, $f16, $f10
    /* DDE5F0 0000DB84 C4F00A24 */  lwc1       $f16, 0xA24($a3)
    /* DDE5F4 0000DB88 46000487 */  neg.s      $f18, $f0
    /* DDE5F8 0000DB8C 460082A1 */  cvt.d.s    $f10, $f16
    /* DDE5FC 0000DB90 460091A1 */  cvt.d.s    $f6, $f18
    /* DDE600 0000DB94 46283102 */  mul.d      $f4, $f6, $f8
    /* DDE604 0000DB98 46245480 */  add.d      $f18, $f10, $f4
    /* DDE608 0000DB9C 462091A0 */  cvt.s.d    $f6, $f18
    /* DDE60C 0000DBA0 E4E60A24 */  swc1       $f6, 0xA24($a3)
    /* DDE610 0000DBA4 8C4F0028 */  lw         $t7, 0x28($v0)
    /* DDE614 0000DBA8 95F8000C */  lhu        $t8, 0xC($t7)
    /* DDE618 0000DBAC ACF90A80 */  sw         $t9, 0xA80($a3)
    /* DDE61C 0000DBB0 10000080 */  b          .L0000DDB4
    /* DDE620 0000DBB4 A4F809A4 */   sh        $t8, 0x9A4($a3)
  .L0000DBB8:
    /* DDE624 0000DBB8 0C000000 */  jal        func_00000000
    /* DDE628 0000DBBC 00E02025 */   or        $a0, $a3, $zero
    /* DDE62C 0000DBC0 1000007D */  b          .L0000DDB8
    /* DDE630 0000DBC4 8FBF0014 */   lw        $ra, 0x14($sp)
  .L0000DBC8:
    /* DDE634 0000DBC8 8CA90004 */  lw         $t1, 0x4($a1)
    /* DDE638 0000DBCC 27A80020 */  addiu      $t0, $sp, 0x20
    /* DDE63C 0000DBD0 3C014080 */  lui        $at, (0x40800000 >> 16)
    /* DDE640 0000DBD4 8D2B00E0 */  lw         $t3, 0xE0($t1)
    /* DDE644 0000DBD8 44810000 */  mtc1       $at, $f0
    /* DDE648 0000DBDC 44801000 */  mtc1       $zero, $f2
    /* DDE64C 0000DBE0 AD0B0000 */  sw         $t3, 0x0($t0)
    /* DDE650 0000DBE4 8D2A00E4 */  lw         $t2, 0xE4($t1)
    /* DDE654 0000DBE8 AD0A0004 */  sw         $t2, 0x4($t0)
    /* DDE658 0000DBEC 8D2B00E8 */  lw         $t3, 0xE8($t1)
    /* DDE65C 0000DBF0 AD0B0008 */  sw         $t3, 0x8($t0)
    /* DDE660 0000DBF4 C7A80020 */  lwc1       $f8, 0x20($sp)
    /* DDE664 0000DBF8 C7AA0024 */  lwc1       $f10, 0x24($sp)
    /* DDE668 0000DBFC C7B20028 */  lwc1       $f18, 0x28($sp)
    /* DDE66C 0000DC00 46004402 */  mul.s      $f16, $f8, $f0
    /* DDE670 0000DC04 00000000 */  nop
    /* DDE674 0000DC08 46005102 */  mul.s      $f4, $f10, $f0
    /* DDE678 0000DC0C 00000000 */  nop
    /* DDE67C 0000DC10 46009182 */  mul.s      $f6, $f18, $f0
    /* DDE680 0000DC14 E7B00020 */  swc1       $f16, 0x20($sp)
    /* DDE684 0000DC18 E7A40024 */  swc1       $f4, 0x24($sp)
    /* DDE688 0000DC1C E7A60028 */  swc1       $f6, 0x28($sp)
    /* DDE68C 0000DC20 C4E800B4 */  lwc1       $f8, 0xB4($a3)
    /* DDE690 0000DC24 C4E400B8 */  lwc1       $f4, 0xB8($a3)
    /* DDE694 0000DC28 46104280 */  add.s      $f10, $f8, $f16
    /* DDE698 0000DC2C C4E800BC */  lwc1       $f8, 0xBC($a3)
    /* DDE69C 0000DC30 E4EA00B4 */  swc1       $f10, 0xB4($a3)
    /* DDE6A0 0000DC34 C7B20024 */  lwc1       $f18, 0x24($sp)
    /* DDE6A4 0000DC38 46122180 */  add.s      $f6, $f4, $f18
    /* DDE6A8 0000DC3C E4E600B8 */  swc1       $f6, 0xB8($a3)
    /* DDE6AC 0000DC40 C7B00028 */  lwc1       $f16, 0x28($sp)
    /* DDE6B0 0000DC44 E4E20320 */  swc1       $f2, 0x320($a3)
    /* DDE6B4 0000DC48 E4E2031C */  swc1       $f2, 0x31C($a3)
    /* DDE6B8 0000DC4C 46104280 */  add.s      $f10, $f8, $f16
    /* DDE6BC 0000DC50 E4E20318 */  swc1       $f2, 0x318($a3)
    /* DDE6C0 0000DC54 10000057 */  b          .L0000DDB4
    /* DDE6C4 0000DC58 E4EA00BC */   swc1      $f10, 0xBC($a3)
  .L0000DC5C:
    /* DDE6C8 0000DC5C 8CED0A58 */  lw         $t5, 0xA58($a3)
    /* DDE6CC 0000DC60 ACEC0A54 */  sw         $t4, 0xA54($a3)
    /* DDE6D0 0000DC64 8CE40804 */  lw         $a0, 0x804($a3)
    /* DDE6D4 0000DC68 35AE0004 */  ori        $t6, $t5, 0x4
    /* DDE6D8 0000DC6C 0C000000 */  jal        func_00000000
    /* DDE6DC 0000DC70 ACEE0A58 */   sw        $t6, 0xA58($a3)
    /* DDE6E0 0000DC74 3C040001 */  lui        $a0, %hi(func_00008AEC + 0x4C)
    /* DDE6E4 0000DC78 0C000000 */  jal        func_00000000
    /* DDE6E8 0000DC7C 24848B38 */   addiu     $a0, $a0, %lo(func_00008AEC + 0x4C)
    /* DDE6EC 0000DC80 1000004D */  b          .L0000DDB8
    /* DDE6F0 0000DC84 8FBF0014 */   lw        $ra, 0x14($sp)
  .L0000DC88:
    /* DDE6F4 0000DC88 8CF80A58 */  lw         $t8, 0xA58($a3)
    /* DDE6F8 0000DC8C ACEF0A54 */  sw         $t7, 0xA54($a3)
    /* DDE6FC 0000DC90 8CE40804 */  lw         $a0, 0x804($a3)
    /* DDE700 0000DC94 37190004 */  ori        $t9, $t8, 0x4
    /* DDE704 0000DC98 0C000000 */  jal        func_00000000
    /* DDE708 0000DC9C ACF90A58 */   sw        $t9, 0xA58($a3)
    /* DDE70C 0000DCA0 3C040001 */  lui        $a0, %hi(func_00008AEC + 0x54)
    /* DDE710 0000DCA4 0C000000 */  jal        func_00000000
    /* DDE714 0000DCA8 24848B40 */   addiu     $a0, $a0, %lo(func_00008AEC + 0x54)
    /* DDE718 0000DCAC 10000042 */  b          .L0000DDB8
    /* DDE71C 0000DCB0 8FBF0014 */   lw        $ra, 0x14($sp)
  .L0000DCB4:
    /* DDE720 0000DCB4 8CE90A58 */  lw         $t1, 0xA58($a3)
    /* DDE724 0000DCB8 ACE80A54 */  sw         $t0, 0xA54($a3)
    /* DDE728 0000DCBC 3C040001 */  lui        $a0, %hi(func_00008B44 + 0x4)
    /* DDE72C 0000DCC0 352A0004 */  ori        $t2, $t1, 0x4
    /* DDE730 0000DCC4 ACEA0A58 */  sw         $t2, 0xA58($a3)
    /* DDE734 0000DCC8 AFA70090 */  sw         $a3, 0x90($sp)
    /* DDE738 0000DCCC 0C000000 */  jal        func_00000000
    /* DDE73C 0000DCD0 24848B48 */   addiu     $a0, $a0, %lo(func_00008B44 + 0x4)
    /* DDE740 0000DCD4 8FA70090 */  lw         $a3, 0x90($sp)
    /* DDE744 0000DCD8 0C000000 */  jal        func_00000000
    /* DDE748 0000DCDC 8CE40804 */   lw        $a0, 0x804($a3)
    /* DDE74C 0000DCE0 10000035 */  b          .L0000DDB8
    /* DDE750 0000DCE4 8FBF0014 */   lw        $ra, 0x14($sp)
  .L0000DCE8:
    /* DDE754 0000DCE8 10000032 */  b          .L0000DDB4
    /* DDE758 0000DCEC ACEB0A54 */   sw        $t3, 0xA54($a3)
  .L0000DCF0:
    /* DDE75C 0000DCF0 10000030 */  b          .L0000DDB4
    /* DDE760 0000DCF4 ACEC0A54 */   sw        $t4, 0xA54($a3)
  .L0000DCF8:
    /* DDE764 0000DCF8 ACE30A54 */  sw         $v1, 0xA54($a3)
  .L0000DCFC:
    /* DDE768 0000DCFC AFA70090 */  sw         $a3, 0x90($sp)
    /* DDE76C 0000DD00 0C000000 */  jal        func_00000000
    /* DDE770 0000DD04 24848B54 */   addiu     $a0, $a0, %lo(func_00008B44 + 0x10)
    /* DDE774 0000DD08 8FA70090 */  lw         $a3, 0x90($sp)
    /* DDE778 0000DD0C 24010002 */  addiu      $at, $zero, 0x2
    /* DDE77C 0000DD10 3C0E0001 */  lui        $t6, %hi(func_00008B44 + 0x24)
    /* DDE780 0000DD14 8CED0848 */  lw         $t5, 0x848($a3)
    /* DDE784 0000DD18 3C0F0001 */  lui        $t7, %hi(func_00008B44 + 0x28)
    /* DDE788 0000DD1C 25CE8B68 */  addiu      $t6, $t6, %lo(func_00008B44 + 0x24)
    /* DDE78C 0000DD20 15A10007 */  bne        $t5, $at, .L0000DD40
    /* DDE790 0000DD24 25EF8B6C */   addiu     $t7, $t7, %lo(func_00008B44 + 0x28)
    /* DDE794 0000DD28 AFAE0084 */  sw         $t6, 0x84($sp)
    /* DDE798 0000DD2C 8CE40840 */  lw         $a0, 0x840($a3)
    /* DDE79C 0000DD30 0C000000 */  jal        func_00000000
    /* DDE7A0 0000DD34 AFA70090 */   sw        $a3, 0x90($sp)
    /* DDE7A4 0000DD38 10000006 */  b          .L0000DD54
    /* DDE7A8 0000DD3C 8FA70090 */   lw        $a3, 0x90($sp)
  .L0000DD40:
    /* DDE7AC 0000DD40 AFAF0084 */  sw         $t7, 0x84($sp)
    /* DDE7B0 0000DD44 8CE40840 */  lw         $a0, 0x840($a3)
    /* DDE7B4 0000DD48 0C000000 */  jal        func_00000000
    /* DDE7B8 0000DD4C AFA70090 */   sw        $a3, 0x90($sp)
    /* DDE7BC 0000DD50 8FA70090 */  lw         $a3, 0x90($sp)
  .L0000DD54:
    /* DDE7C0 0000DD54 8FB80084 */  lw         $t8, 0x84($sp)
    /* DDE7C4 0000DD58 3C040000 */  lui        $a0, (0x0 >> 16)
    /* DDE7C8 0000DD5C 8C840000 */  lw         $a0, 0x0($a0)
    /* DDE7CC 0000DD60 8F050000 */  lw         $a1, 0x0($t8)
    /* DDE7D0 0000DD64 AFA70090 */  sw         $a3, 0x90($sp)
    /* DDE7D4 0000DD68 00003025 */  or         $a2, $zero, $zero
    /* DDE7D8 0000DD6C AFA5008C */  sw         $a1, 0x8C($sp)
    /* DDE7DC 0000DD70 0C000000 */  jal        func_00000000
    /* DDE7E0 0000DD74 AFA50004 */   sw        $a1, 0x4($sp)
    /* DDE7E4 0000DD78 10400006 */  beqz       $v0, .L0000DD94
    /* DDE7E8 0000DD7C 8FA70090 */   lw        $a3, 0x90($sp)
    /* DDE7EC 0000DD80 00E02025 */  or         $a0, $a3, $zero
    /* DDE7F0 0000DD84 0C000000 */  jal        func_00000000
    /* DDE7F4 0000DD88 24450030 */   addiu     $a1, $v0, 0x30
    /* DDE7F8 0000DD8C 1000000A */  b          .L0000DDB8
    /* DDE7FC 0000DD90 8FBF0014 */   lw        $ra, 0x14($sp)
  .L0000DD94:
    /* DDE800 0000DD94 3C040001 */  lui        $a0, %hi(func_00008B44 + 0x2C)
    /* DDE804 0000DD98 24848B70 */  addiu      $a0, $a0, %lo(func_00008B44 + 0x2C)
    /* DDE808 0000DD9C 0C000000 */  jal        func_00000000
    /* DDE80C 0000DDA0 8FA50084 */   lw        $a1, 0x84($sp)
    /* DDE810 0000DDA4 10000004 */  b          .L0000DDB8
    /* DDE814 0000DDA8 8FBF0014 */   lw        $ra, 0x14($sp)
  .L0000DDAC:
    /* DDE818 0000DDAC 0C000000 */  jal        func_00000000
    /* DDE81C 0000DDB0 00E02025 */   or        $a0, $a3, $zero
  .L0000DDB4:
    /* DDE820 0000DDB4 8FBF0014 */  lw         $ra, 0x14($sp)
  .L0000DDB8:
    /* DDE824 0000DDB8 27BD0090 */  addiu      $sp, $sp, 0x90
    /* DDE828 0000DDBC 03E00008 */  jr         $ra
    /* DDE82C 0000DDC0 00000000 */   nop
endlabel func_0000D900
