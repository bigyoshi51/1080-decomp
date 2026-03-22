
nonmatching func_800090B4, 0x13C

glabel func_800090B4
    /* A0B4 800090B4 01406825 */  or         $t5, $t2, $zero
    /* A0B8 800090B8 000A67C3 */  sra        $t4, $t2, 31
    /* A0BC 800090BC AD6C0000 */  sw         $t4, 0x0($t3)
    /* A0C0 800090C0 AD6D0004 */  sw         $t5, 0x4($t3)
    /* A0C4 800090C4 8FAE0024 */  lw         $t6, 0x24($sp)
    /* A0C8 800090C8 2A210022 */  slti       $at, $s1, 0x22
    /* A0CC 800090CC 25CF0008 */  addiu      $t7, $t6, 0x8
    /* A0D0 800090D0 1420FFF3 */  bnez       $at, .L800090A0
    /* A0D4 800090D4 AFAF0024 */   sw        $t7, 0x24($sp)
  .L800090D8:
    /* A0D8 800090D8 8E180098 */  lw         $t8, 0x98($s0)
    /* A0DC 800090DC 8FB90028 */  lw         $t9, 0x28($sp)
    /* A0E0 800090E0 AF380120 */  sw         $t8, 0x120($t9)
    /* A0E4 800090E4 8FA90028 */  lw         $t1, 0x28($sp)
    /* A0E8 800090E8 8E08009C */  lw         $t0, 0x9C($s0)
    /* A0EC 800090EC AD28011C */  sw         $t0, 0x11C($t1)
    /* A0F0 800090F0 8FAC0028 */  lw         $t4, 0x28($sp)
    /* A0F4 800090F4 8E0A00A0 */  lw         $t2, 0xA0($s0)
    /* A0F8 800090F8 10000003 */  b          .L80009108
    /* A0FC 800090FC AD8A0118 */   sw        $t2, 0x118($t4)
  .L80009100:
    /* A100 80009100 1000000B */  b          .L80009130
    /* A104 80009104 2402FFFE */   addiu     $v0, $zero, -0x2
  .L80009108:
    /* A108 80009108 8E0D000C */  lw         $t5, 0xC($s0)
    /* A10C 8000910C 27A4002C */  addiu      $a0, $sp, 0x2C
    /* A110 80009110 24050010 */  addiu      $a1, $zero, 0x10
    /* A114 80009114 AFAD0038 */  sw         $t5, 0x38($sp)
    /* A118 80009118 920B0004 */  lbu        $t3, 0x4($s0)
    /* A11C 8000911C A7A00032 */  sh         $zero, 0x32($sp)
    /* A120 80009120 24060001 */  addiu      $a2, $zero, 0x1
    /* A124 80009124 0C001CFE */  jal        func_800073F8
    /* A128 80009128 A3AB0030 */   sb        $t3, 0x30($sp)
    /* A12C 8000912C 00001025 */  or         $v0, $zero, $zero
  .L80009130:
    /* A130 80009130 8FBF001C */  lw         $ra, 0x1C($sp)
    /* A134 80009134 8FB00014 */  lw         $s0, 0x14($sp)
    /* A138 80009138 8FB10018 */  lw         $s1, 0x18($sp)
    /* A13C 8000913C 03E00008 */  jr         $ra
    /* A140 80009140 27BD0040 */   addiu     $sp, $sp, 0x40
/* glabel func_80009144 */
    /* A144 80009144 27BDFF38 */  addiu      $sp, $sp, -0xC8
/* glabel func_80009148 */
    /* A148 80009148 AFA400C8 */  sw         $a0, 0xC8($sp)
    /* A14C 8000914C 8FAE00C8 */  lw         $t6, 0xC8($sp)
    /* A150 80009150 AFBF001C */  sw         $ra, 0x1C($sp)
    /* A154 80009154 AFB00018 */  sw         $s0, 0x18($sp)
    /* A158 80009158 91CF0009 */  lbu        $t7, 0x9($t6)
    /* A15C 8000915C 01C08025 */  or         $s0, $t6, $zero
    /* A160 80009160 11E00003 */  beqz       $t7, .L80009170
    /* A164 80009164 00000000 */   nop
    /* A168 80009168 1000001F */  b          .L800091E8
    /* A16C 8000916C 2402FFFE */   addiu     $v0, $zero, -0x2
  .L80009170:
    /* A170 80009170 44802000 */  mtc1       $zero, $f4
    /* A174 80009174 00000000 */  nop
    /* A178 80009178 E7A40020 */  swc1       $f4, 0x20($sp)
    /* A17C 8000917C 0C001DF7 */  jal        func_800077DC
    /* A180 80009180 8E04000C */   lw        $a0, 0xC($s0)
    /* A184 80009184 AFA20024 */  sw         $v0, 0x24($sp)
    /* A188 80009188 8FB80024 */  lw         $t8, 0x24($sp)
    /* A18C 8000918C 17000003 */  bnez       $t8, .L8000919C
    /* A190 80009190 00000000 */   nop
    /* A194 80009194 10000014 */  b          .L800091E8
    /* A198 80009198 2402FFFE */   addiu     $v0, $zero, -0x2
  .L8000919C:
    /* A19C 8000919C 8FA50024 */  lw         $a1, 0x24($sp)
    /* A1A0 800091A0 27A40028 */  addiu      $a0, $sp, 0x28
    /* A1A4 800091A4 24840010 */  addiu      $a0, $a0, 0x10
    /* A1A8 800091A8 24060020 */  addiu      $a2, $zero, 0x20
    /* A1AC 800091AC 0C001AC8 */  jal        func_80006B20
    /* A1B0 800091B0 24A50130 */   addiu     $a1, $a1, 0x130
    /* A1B4 800091B4 8FB90024 */  lw         $t9, 0x24($sp)
    /* A1B8 800091B8 27A40028 */  addiu      $a0, $sp, 0x28
    /* A1BC 800091BC 24050098 */  addiu      $a1, $zero, 0x98
    /* A1C0 800091C0 8F28012C */  lw         $t0, 0x12C($t9)
    /* A1C4 800091C4 24060001 */  addiu      $a2, $zero, 0x1
    /* A1C8 800091C8 AFA800B8 */  sw         $t0, 0xB8($sp)
    /* A1CC 800091CC 92090004 */  lbu        $t1, 0x4($s0)
    /* A1D0 800091D0 A7A0002E */  sh         $zero, 0x2E($sp)
    /* A1D4 800091D4 A3A9002C */  sb         $t1, 0x2C($sp)
    /* A1D8 800091D8 8E0A000C */  lw         $t2, 0xC($s0)
    /* A1DC 800091DC 0C001CFE */  jal        func_800073F8
    /* A1E0 800091E0 AFAA0034 */   sw        $t2, 0x34($sp)
    /* A1E4 800091E4 00001025 */  or         $v0, $zero, $zero
  .L800091E8:
    /* A1E8 800091E8 8FBF001C */  lw         $ra, 0x1C($sp)
    /* A1EC 800091EC 8FB00018 */  lw         $s0, 0x18($sp)
endlabel func_800090B4
