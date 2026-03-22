
nonmatching func_800080D0, 0x100

glabel func_800080D0
    /* 90D0 800080D0 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 90D4 800080D4 AFA40018 */  sw         $a0, 0x18($sp)
    /* 90D8 800080D8 8FAE0018 */  lw         $t6, 0x18($sp)
    /* 90DC 800080DC AFBF0014 */  sw         $ra, 0x14($sp)
    /* 90E0 800080E0 AFA5001C */  sw         $a1, 0x1C($sp)
    /* 90E4 800080E4 8DCF0000 */  lw         $t7, 0x0($t6)
    /* 90E8 800080E8 3C188002 */  lui        $t8, %hi(rmonbrk_bss_0000)
    /* 90EC 800080EC 2718FE70 */  addiu      $t8, $t8, %lo(rmonbrk_bss_0000)
    /* 90F0 800080F0 AF0F0004 */  sw         $t7, 0x4($t8)
    /* 90F4 800080F4 8FA80018 */  lw         $t0, 0x18($sp)
    /* 90F8 800080F8 2419040D */  addiu      $t9, $zero, 0x40D
    /* 90FC 800080FC 24050004 */  addiu      $a1, $zero, 0x4
    /* 9100 80008100 AD190000 */  sw         $t9, 0x0($t0)
    /* 9104 80008104 0C000C7C */  jal        func_800031F0
    /* 9108 80008108 8FA40018 */   lw        $a0, 0x18($sp)
    /* 910C 8000810C 8FA40018 */  lw         $a0, 0x18($sp)
    /* 9110 80008110 0C0014D4 */  jal        func_80005350
    /* 9114 80008114 24050004 */   addiu     $a1, $zero, 0x4
    /* 9118 80008118 8FA90018 */  lw         $t1, 0x18($sp)
    /* 911C 8000811C 3C0A8002 */  lui        $t2, %hi(rmonbrk_bss_0000)
    /* 9120 80008120 254AFE70 */  addiu      $t2, $t2, %lo(rmonbrk_bss_0000)
    /* 9124 80008124 AD490000 */  sw         $t1, 0x0($t2)
    /* 9128 80008128 8FAB001C */  lw         $t3, 0x1C($sp)
    /* 912C 8000812C 1160000F */  beqz       $t3, .L8000816C
    /* 9130 80008130 00000000 */   nop
    /* 9134 80008134 8D6C0000 */  lw         $t4, 0x0($t3)
    /* 9138 80008138 3C018002 */  lui        $at, %hi(D_8001FEF4)
    /* 913C 8000813C 240D040D */  addiu      $t5, $zero, 0x40D
    /* 9140 80008140 AC2CFEF4 */  sw         $t4, %lo(D_8001FEF4)($at)
    /* 9144 80008144 AD6D0000 */  sw         $t5, 0x0($t3)
    /* 9148 80008148 8FA4001C */  lw         $a0, 0x1C($sp)
    /* 914C 8000814C 0C000C7C */  jal        func_800031F0
    /* 9150 80008150 24050004 */   addiu     $a1, $zero, 0x4
    /* 9154 80008154 8FA4001C */  lw         $a0, 0x1C($sp)
    /* 9158 80008158 0C0014D4 */  jal        func_80005350
    /* 915C 8000815C 24050004 */   addiu     $a1, $zero, 0x4
    /* 9160 80008160 8FAE001C */  lw         $t6, 0x1C($sp)
    /* 9164 80008164 3C018002 */  lui        $at, %hi(D_8001FEF0)
    /* 9168 80008168 AC2EFEF0 */  sw         $t6, %lo(D_8001FEF0)($at)
  .L8000816C:
    /* 916C 8000816C 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 9170 80008170 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 9174 80008174 03E00008 */  jr         $ra
    /* 9178 80008178 00000000 */   nop
/* glabel func_8000817C */
    /* 917C 8000817C 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 9180 80008180 3C0E8002 */  lui        $t6, %hi(rmonbrk_bss_0000)
    /* 9184 80008184 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 9188 80008188 25CEFE70 */  addiu      $t6, $t6, %lo(rmonbrk_bss_0000)
    /* 918C 8000818C 8DCF0000 */  lw         $t7, 0x0($t6)
    /* 9190 80008190 11E00018 */  beqz       $t7, .L800081F4
    /* 9194 80008194 00000000 */   nop
    /* 9198 80008198 8DF80000 */  lw         $t8, 0x0($t7)
    /* 919C 8000819C 3C01FC00 */  lui        $at, (0xFC00003F >> 16)
    /* 91A0 800081A0 3421003F */  ori        $at, $at, (0xFC00003F & 0xFFFF)
    /* 91A4 800081A4 0301C824 */  and        $t9, $t8, $at
    /* 91A8 800081A8 2401000D */  addiu      $at, $zero, 0xD
    /* 91AC 800081AC 1721000E */  bne        $t9, $at, .L800081E8
    /* 91B0 800081B0 AFB8001C */   sw        $t8, 0x1C($sp)
    /* 91B4 800081B4 8DC80004 */  lw         $t0, 0x4($t6)
    /* 91B8 800081B8 8DC90000 */  lw         $t1, 0x0($t6)
    /* 91BC 800081BC 3C0A8002 */  lui        $t2, %hi(rmonbrk_bss_0000)
    /* 91C0 800081C0 254AFE70 */  addiu      $t2, $t2, %lo(rmonbrk_bss_0000)
    /* 91C4 800081C4 AD280000 */  sw         $t0, 0x0($t1)
    /* 91C8 800081C8 8D440000 */  lw         $a0, 0x0($t2)
    /* 91CC 800081CC 0C000C7C */  jal        func_800031F0
endlabel func_800080D0
