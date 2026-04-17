
nonmatching func_8000969C, 0xC4

glabel func_8000969C
    /* A69C 8000969C 27BDFFC8 */  addiu      $sp, $sp, -0x38
    /* A6A0 800096A0 AFBF001C */  sw         $ra, 0x1C($sp)
    /* A6A4 800096A4 AFA40038 */  sw         $a0, 0x38($sp)
    /* A6A8 800096A8 AFB00014 */  sw         $s0, 0x14($sp)
    /* A6AC 800096AC AFB10018 */  sw         $s1, 0x18($sp)
    /* A6B0 800096B0 0C00210C */  jal        func_80008430
    /* A6B4 800096B4 8FB00038 */   lw        $s0, 0x38($sp)
    /* A6B8 800096B8 10400003 */  beqz       $v0, .L800096C8
    /* A6BC 800096BC 00000000 */   nop
    /* A6C0 800096C0 10000022 */  b          .L8000974C
    /* A6C4 800096C4 2402FFFC */   addiu     $v0, $zero, -0x4
  .L800096C8:
    /* A6C8 800096C8 0C002452 */  jal        func_80009148
    /* A6CC 800096CC 24040001 */   addiu     $a0, $zero, 0x1
    /* A6D0 800096D0 00008825 */  or         $s1, $zero, $zero
    /* A6D4 800096D4 2A210020 */  slti       $at, $s1, 0x20
    /* A6D8 800096D8 10200010 */  beqz       $at, .L8000971C
    /* A6DC 800096DC 00000000 */   nop
  .L800096E0:
    /* A6E0 800096E0 00117080 */  sll        $t6, $s1, 2
    /* A6E4 800096E4 020E2821 */  addu       $a1, $s0, $t6
    /* A6E8 800096E8 24A50010 */  addiu      $a1, $a1, 0x10
    /* A6EC 800096EC 3C040400 */  lui        $a0, (0x4000000 >> 16)
    /* A6F0 800096F0 0C001AC8 */  jal        func_80006B20
    /* A6F4 800096F4 24060004 */   addiu     $a2, $zero, 0x4
    /* A6F8 800096F8 24040032 */  addiu      $a0, $zero, 0x32
    /* A6FC 800096FC 0C00242D */  jal        func_800090B4
    /* A700 80009700 02202825 */   or        $a1, $s1, $zero
    /* A704 80009704 0C002126 */  jal        func_80008498
    /* A708 80009708 00000000 */   nop
    /* A70C 8000970C 26310001 */  addiu      $s1, $s1, 0x1
    /* A710 80009710 2A210020 */  slti       $at, $s1, 0x20
    /* A714 80009714 1420FFF2 */  bnez       $at, .L800096E0
    /* A718 80009718 00000000 */   nop
  .L8000971C:
    /* A71C 8000971C 0C00247C */  jal        func_800091F0
    /* A720 80009720 24040001 */   addiu     $a0, $zero, 0x1
    /* A724 80009724 8E0F000C */  lw         $t7, 0xC($s0)
    /* A728 80009728 27A40024 */  addiu      $a0, $sp, 0x24
    /* A72C 8000972C 24050010 */  addiu      $a1, $zero, 0x10
    /* A730 80009730 AFAF0030 */  sw         $t7, 0x30($sp)
    /* A734 80009734 92180004 */  lbu        $t8, 0x4($s0)
    /* A738 80009738 A7A0002A */  sh         $zero, 0x2A($sp)
    /* A73C 8000973C 24060001 */  addiu      $a2, $zero, 0x1
    /* A740 80009740 0C001CFE */  jal        func_800073F8
    /* A744 80009744 A3B80028 */   sb        $t8, 0x28($sp)
    /* A748 80009748 00001025 */  or         $v0, $zero, $zero
  .L8000974C:
    /* A74C 8000974C 8FBF001C */  lw         $ra, 0x1C($sp)
    /* A750 80009750 8FB00014 */  lw         $s0, 0x14($sp)
    /* A754 80009754 8FB10018 */  lw         $s1, 0x18($sp)
    /* A758 80009758 03E00008 */  jr         $ra
    /* A75C 8000975C 27BD0038 */   addiu     $sp, $sp, 0x38
endlabel func_8000969C
