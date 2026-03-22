
nonmatching func_8000817C, 0x54

glabel func_8000817C
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
endlabel func_8000817C
