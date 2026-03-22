
nonmatching func_80009148, 0xA8

glabel func_80009148
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
endlabel func_80009148
