
nonmatching func_80008ED0, 0xE0

glabel func_80008ED0
    /* 9ED0 80008ED0 0C001DF7 */  jal        func_800077DC
    /* 9ED4 80008ED4 8E04000C */   lw        $a0, 0xC($s0)
    /* 9ED8 80008ED8 AFA2002C */  sw         $v0, 0x2C($sp)
    /* 9EDC 80008EDC 8FB9002C */  lw         $t9, 0x2C($sp)
    /* 9EE0 80008EE0 17200003 */  bnez       $t9, .L80008EF0
    /* 9EE4 80008EE4 00000000 */   nop
    /* 9EE8 80008EE8 1000003D */  b          .L80008FE0
    /* 9EEC 80008EEC 2402FFFE */   addiu     $v0, $zero, -0x2
  .L80008EF0:
    /* 9EF0 80008EF0 8FA8002C */  lw         $t0, 0x2C($sp)
    /* 9EF4 80008EF4 24110001 */  addiu      $s1, $zero, 0x1
    /* 9EF8 80008EF8 2A21001A */  slti       $at, $s1, 0x1A
    /* 9EFC 80008EFC 25090020 */  addiu      $t1, $t0, 0x20
    /* 9F00 80008F00 1020000E */  beqz       $at, .L80008F3C
    /* 9F04 80008F04 AFA90028 */   sw        $t1, 0x28($sp)
  .L80008F08:
    /* 9F08 80008F08 8FAA0028 */  lw         $t2, 0x28($sp)
    /* 9F0C 80008F0C 00117080 */  sll        $t6, $s1, 2
    /* 9F10 80008F10 03AE7821 */  addu       $t7, $sp, $t6
    /* 9F14 80008F14 8D4D0004 */  lw         $t5, 0x4($t2)
    /* 9F18 80008F18 8D4C0000 */  lw         $t4, 0x0($t2)
    /* 9F1C 80008F1C 26310001 */  addiu      $s1, $s1, 0x1
    /* 9F20 80008F20 01A05825 */  or         $t3, $t5, $zero
    /* 9F24 80008F24 ADEB0040 */  sw         $t3, 0x40($t7)
    /* 9F28 80008F28 8FB80028 */  lw         $t8, 0x28($sp)
    /* 9F2C 80008F2C 2A21001A */  slti       $at, $s1, 0x1A
    /* 9F30 80008F30 27190008 */  addiu      $t9, $t8, 0x8
    /* 9F34 80008F34 1420FFF4 */  bnez       $at, .L80008F08
    /* 9F38 80008F38 AFB90028 */   sw        $t9, 0x28($sp)
  .L80008F3C:
    /* 9F3C 80008F3C 8FA8002C */  lw         $t0, 0x2C($sp)
    /* 9F40 80008F40 2411001C */  addiu      $s1, $zero, 0x1C
    /* 9F44 80008F44 2A210022 */  slti       $at, $s1, 0x22
    /* 9F48 80008F48 250900E8 */  addiu      $t1, $t0, 0xE8
    /* 9F4C 80008F4C 1020000E */  beqz       $at, .L80008F88
    /* 9F50 80008F50 AFA90028 */   sw        $t1, 0x28($sp)
  .L80008F54:
    /* 9F54 80008F54 8FAA0028 */  lw         $t2, 0x28($sp)
    /* 9F58 80008F58 00117080 */  sll        $t6, $s1, 2
    /* 9F5C 80008F5C 03AE7821 */  addu       $t7, $sp, $t6
    /* 9F60 80008F60 8D4D0004 */  lw         $t5, 0x4($t2)
    /* 9F64 80008F64 8D4C0000 */  lw         $t4, 0x0($t2)
    /* 9F68 80008F68 26310001 */  addiu      $s1, $s1, 0x1
    /* 9F6C 80008F6C 01A05825 */  or         $t3, $t5, $zero
    /* 9F70 80008F70 ADEB0040 */  sw         $t3, 0x40($t7)
    /* 9F74 80008F74 8FB80028 */  lw         $t8, 0x28($sp)
    /* 9F78 80008F78 2A210022 */  slti       $at, $s1, 0x22
    /* 9F7C 80008F7C 27190008 */  addiu      $t9, $t8, 0x8
    /* 9F80 80008F80 1420FFF4 */  bnez       $at, .L80008F54
    /* 9F84 80008F84 AFB90028 */   sw        $t9, 0x28($sp)
  .L80008F88:
    /* 9F88 80008F88 8FA8002C */  lw         $t0, 0x2C($sp)
    /* 9F8C 80008F8C 27AA0030 */  addiu      $t2, $sp, 0x30
    /* 9F90 80008F90 27AB0030 */  addiu      $t3, $sp, 0x30
    /* 9F94 80008F94 8D090120 */  lw         $t1, 0x120($t0)
    /* 9F98 80008F98 27B80030 */  addiu      $t8, $sp, 0x30
    /* 9F9C 80008F9C 27B90030 */  addiu      $t9, $sp, 0x30
    /* 9FA0 80008FA0 AD490098 */  sw         $t1, 0x98($t2)
    /* 9FA4 80008FA4 8FAC002C */  lw         $t4, 0x2C($sp)
    /* 9FA8 80008FA8 8D8D011C */  lw         $t5, 0x11C($t4)
    /* 9FAC 80008FAC AD6D009C */  sw         $t5, 0x9C($t3)
endlabel func_80008ED0
