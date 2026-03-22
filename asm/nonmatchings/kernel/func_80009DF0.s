
nonmatching func_80009DF0, 0x60

glabel func_80009DF0
    /* ADF0 80009DF0 8F18A420 */  lw         $t8, -0x5BE0($t8)
    /* ADF4 80009DF4 17000005 */  bnez       $t8, .L80009E0C
    /* ADF8 80009DF8 00000000 */   nop
    /* ADFC 80009DFC 0C000F99 */  jal        func_80003E64
    /* AE00 80009E00 00000000 */   nop
    /* AE04 80009E04 1000000F */  b          .L80009E44
    /* AE08 80009E08 00000000 */   nop
  .L80009E0C:
    /* AE0C 80009E0C 3C198001 */  lui        $t9, %hi(__osRunningThread)
    /* AE10 80009E10 3C098001 */  lui        $t1, %hi(__osRunQueue)
    /* AE14 80009E14 8D29A418 */  lw         $t1, %lo(__osRunQueue)($t1)
    /* AE18 80009E18 8F39A420 */  lw         $t9, %lo(__osRunningThread)($t9)
    /* AE1C 80009E1C 8D2A0004 */  lw         $t2, 0x4($t1)
    /* AE20 80009E20 8F280004 */  lw         $t0, 0x4($t9)
    /* AE24 80009E24 010A082A */  slt        $at, $t0, $t2
    /* AE28 80009E28 10200006 */  beqz       $at, .L80009E44
    /* AE2C 80009E2C 00000000 */   nop
    /* AE30 80009E30 240B0002 */  addiu      $t3, $zero, 0x2
    /* AE34 80009E34 3C048001 */  lui        $a0, %hi(__osRunQueue)
    /* AE38 80009E38 A72B0010 */  sh         $t3, 0x10($t9)
    /* AE3C 80009E3C 0C000F43 */  jal        func_80003D0C
    /* AE40 80009E40 2484A418 */   addiu     $a0, $a0, %lo(__osRunQueue)
  .L80009E44:
    /* AE44 80009E44 0C0019B4 */  jal        func_800066D0
    /* AE48 80009E48 02002025 */   or        $a0, $s0, $zero
    /* AE4C 80009E4C 8FBF001C */  lw         $ra, 0x1C($sp)
endlabel func_80009DF0
