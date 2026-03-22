
nonmatching func_80008FB0, 0x104

glabel func_80008FB0
    /* 9FB0 80008FB0 8FAE002C */  lw         $t6, 0x2C($sp)
    /* 9FB4 80008FB4 8DCF0118 */  lw         $t7, 0x118($t6)
    /* 9FB8 80008FB8 AF0F00A0 */  sw         $t7, 0xA0($t8)
    /* 9FBC 80008FBC 10000003 */  b          .L80008FCC
    /* 9FC0 80008FC0 AF200010 */   sw        $zero, 0x10($t9)
  .L80008FC4:
    /* 9FC4 80008FC4 10000006 */  b          .L80008FE0
    /* 9FC8 80008FC8 2402FFFE */   addiu     $v0, $zero, -0x2
  .L80008FCC:
    /* 9FCC 80008FCC 27A40030 */  addiu      $a0, $sp, 0x30
    /* 9FD0 80008FD0 240500A4 */  addiu      $a1, $zero, 0xA4
    /* 9FD4 80008FD4 0C001CFE */  jal        func_800073F8
    /* 9FD8 80008FD8 24060001 */   addiu     $a2, $zero, 0x1
    /* 9FDC 80008FDC 00001025 */  or         $v0, $zero, $zero
  .L80008FE0:
    /* 9FE0 80008FE0 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 9FE4 80008FE4 8FB00014 */  lw         $s0, 0x14($sp)
    /* 9FE8 80008FE8 8FB10018 */  lw         $s1, 0x18($sp)
    /* 9FEC 80008FEC 03E00008 */  jr         $ra
    /* 9FF0 80008FF0 27BD00D8 */   addiu     $sp, $sp, 0xD8
/* glabel func_80008FF4 */
    /* 9FF4 80008FF4 27BDFFC0 */  addiu      $sp, $sp, -0x40
    /* 9FF8 80008FF8 AFA40040 */  sw         $a0, 0x40($sp)
    /* 9FFC 80008FFC AFB00014 */  sw         $s0, 0x14($sp)
/* glabel func_80009000 */
    /* A000 80009000 8FB00040 */  lw         $s0, 0x40($sp)
    /* A004 80009004 AFBF001C */  sw         $ra, 0x1C($sp)
    /* A008 80009008 AFB10018 */  sw         $s1, 0x18($sp)
    /* A00C 8000900C 920E0009 */  lbu        $t6, 0x9($s0)
    /* A010 80009010 15C0003B */  bnez       $t6, .L80009100
    /* A014 80009014 00000000 */   nop
    /* A018 80009018 0C001DF7 */  jal        func_800077DC
    /* A01C 8000901C 8E04000C */   lw        $a0, 0xC($s0)
    /* A020 80009020 AFA20028 */  sw         $v0, 0x28($sp)
    /* A024 80009024 8FAF0028 */  lw         $t7, 0x28($sp)
    /* A028 80009028 15E00003 */  bnez       $t7, .L80009038
    /* A02C 8000902C 00000000 */   nop
/* glabel func_80009030 */
    /* A030 80009030 1000003F */  b          .L80009130
    /* A034 80009034 2402FFFE */   addiu     $v0, $zero, -0x2
  .L80009038:
    /* A038 80009038 8FB80028 */  lw         $t8, 0x28($sp)
    /* A03C 8000903C 24110001 */  addiu      $s1, $zero, 0x1
    /* A040 80009040 2A21001A */  slti       $at, $s1, 0x1A
    /* A044 80009044 27190020 */  addiu      $t9, $t8, 0x20
    /* A048 80009048 1020000F */  beqz       $at, .L80009088
    /* A04C 8000904C AFB90024 */   sw        $t9, 0x24($sp)
  .L80009050:
    /* A050 80009050 00114080 */  sll        $t0, $s1, 2
    /* A054 80009054 02084821 */  addu       $t1, $s0, $t0
    /* A058 80009058 8D2A0010 */  lw         $t2, 0x10($t1)
    /* A05C 8000905C 8FAB0024 */  lw         $t3, 0x24($sp)
    /* A060 80009060 26310001 */  addiu      $s1, $s1, 0x1
    /* A064 80009064 01406825 */  or         $t5, $t2, $zero
    /* A068 80009068 000A67C3 */  sra        $t4, $t2, 31
    /* A06C 8000906C AD6C0000 */  sw         $t4, 0x0($t3)
    /* A070 80009070 AD6D0004 */  sw         $t5, 0x4($t3)
    /* A074 80009074 8FAE0024 */  lw         $t6, 0x24($sp)
    /* A078 80009078 2A21001A */  slti       $at, $s1, 0x1A
    /* A07C 8000907C 25CF0008 */  addiu      $t7, $t6, 0x8
    /* A080 80009080 1420FFF3 */  bnez       $at, .L80009050
    /* A084 80009084 AFAF0024 */   sw        $t7, 0x24($sp)
  .L80009088:
    /* A088 80009088 8FB80028 */  lw         $t8, 0x28($sp)
    /* A08C 8000908C 2411001C */  addiu      $s1, $zero, 0x1C
    /* A090 80009090 2A210022 */  slti       $at, $s1, 0x22
    /* A094 80009094 271900E8 */  addiu      $t9, $t8, 0xE8
    /* A098 80009098 1020000F */  beqz       $at, .L800090D8
    /* A09C 8000909C AFB90024 */   sw        $t9, 0x24($sp)
  .L800090A0:
    /* A0A0 800090A0 00114080 */  sll        $t0, $s1, 2
    /* A0A4 800090A4 02084821 */  addu       $t1, $s0, $t0
    /* A0A8 800090A8 8D2A0010 */  lw         $t2, 0x10($t1)
    /* A0AC 800090AC 8FAB0024 */  lw         $t3, 0x24($sp)
    /* A0B0 800090B0 26310001 */  addiu      $s1, $s1, 0x1
endlabel func_80008FB0
