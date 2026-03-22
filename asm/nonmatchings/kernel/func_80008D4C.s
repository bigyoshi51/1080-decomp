
nonmatching func_80008D4C, 0xA4

glabel func_80008D4C
    /* 9D4C 80008D4C AFBF0014 */  sw         $ra, 0x14($sp)
    /* 9D50 80008D50 AFA40018 */  sw         $a0, 0x18($sp)
    /* 9D54 80008D54 0C001AA6 */  jal        func_80006A98
    /* 9D58 80008D58 3C040408 */   lui       $a0, (0x4080000 >> 16)
    /* 9D5C 80008D5C 3C018002 */  lui        $at, %hi(D_8001FF80)
    /* 9D60 80008D60 3C040400 */  lui        $a0, (0x4001000 >> 16)
    /* 9D64 80008D64 AC22FF80 */  sw         $v0, %lo(D_8001FF80)($at)
    /* 9D68 80008D68 0C001AA6 */  jal        func_80006A98
    /* 9D6C 80008D6C 34841000 */   ori       $a0, $a0, (0x4001000 & 0xFFFF)
    /* 9D70 80008D70 3C018002 */  lui        $at, %hi(D_8001FF84)
    /* 9D74 80008D74 AC22FF84 */  sw         $v0, %lo(D_8001FF84)($at)
    /* 9D78 80008D78 0C001AA6 */  jal        func_80006A98
    /* 9D7C 80008D7C 3C040400 */   lui       $a0, (0x4000000 >> 16)
    /* 9D80 80008D80 3C0E8002 */  lui        $t6, %hi(D_8001FF88)
    /* 9D84 80008D84 25CEFF88 */  addiu      $t6, $t6, %lo(D_8001FF88)
    /* 9D88 80008D88 ADC20000 */  sw         $v0, 0x0($t6)
    /* 9D8C 80008D8C 8FAF0018 */  lw         $t7, 0x18($sp)
    /* 9D90 80008D90 11E00013 */  beqz       $t7, .L80008DE0
    /* 9D94 80008D94 00000000 */   nop
    /* 9D98 80008D98 3C040400 */  lui        $a0, (0x4000004 >> 16)
    /* 9D9C 80008D9C 0C001AA6 */  jal        func_80006A98
    /* 9DA0 80008DA0 34840004 */   ori       $a0, $a0, (0x4000004 & 0xFFFF)
    /* 9DA4 80008DA4 3C188002 */  lui        $t8, %hi(D_8001FF88)
    /* 9DA8 80008DA8 2718FF88 */  addiu      $t8, $t8, %lo(D_8001FF88)
    /* 9DAC 80008DAC 3C040400 */  lui        $a0, (0x4000008 >> 16)
    /* 9DB0 80008DB0 AF020004 */  sw         $v0, 0x4($t8)
    /* 9DB4 80008DB4 0C001AA6 */  jal        func_80006A98
    /* 9DB8 80008DB8 34840008 */   ori       $a0, $a0, (0x4000008 & 0xFFFF)
    /* 9DBC 80008DBC 3C198002 */  lui        $t9, %hi(D_8001FF88)
    /* 9DC0 80008DC0 2739FF88 */  addiu      $t9, $t9, %lo(D_8001FF88)
    /* 9DC4 80008DC4 3C040400 */  lui        $a0, (0x400000C >> 16)
    /* 9DC8 80008DC8 AF220008 */  sw         $v0, 0x8($t9)
    /* 9DCC 80008DCC 0C001AA6 */  jal        func_80006A98
    /* 9DD0 80008DD0 3484000C */   ori       $a0, $a0, (0x400000C & 0xFFFF)
    /* 9DD4 80008DD4 3C088002 */  lui        $t0, %hi(D_8001FF88)
    /* 9DD8 80008DD8 2508FF88 */  addiu      $t0, $t0, %lo(D_8001FF88)
    /* 9DDC 80008DDC AD02000C */  sw         $v0, 0xC($t0)
  .L80008DE0:
    /* 9DE0 80008DE0 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 9DE4 80008DE4 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 9DE8 80008DE8 03E00008 */  jr         $ra
    /* 9DEC 80008DEC 00000000 */   nop
endlabel func_80008D4C
