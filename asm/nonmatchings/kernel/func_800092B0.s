
nonmatching func_800092B0, 0x64

glabel func_800092B0
    /* A2B0 800092B0 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* A2B4 800092B4 AFBF0014 */  sw         $ra, 0x14($sp)
    /* A2B8 800092B8 0C00210C */  jal        func_80008430
    /* A2BC 800092BC AFA40020 */   sw        $a0, 0x20($sp)
    /* A2C0 800092C0 10400003 */  beqz       $v0, .L800092D0
    /* A2C4 800092C4 00000000 */   nop
    /* A2C8 800092C8 1000000E */  b          .L80009304
    /* A2CC 800092CC 00001025 */   or        $v0, $zero, $zero
  .L800092D0:
    /* A2D0 800092D0 0C002452 */  jal        func_80009148
    /* A2D4 800092D4 00002025 */   or        $a0, $zero, $zero
    /* A2D8 800092D8 2404002B */  addiu      $a0, $zero, 0x2B
    /* A2DC 800092DC 0C00240C */  jal        func_80009030
    /* A2E0 800092E0 8FA50020 */   lw        $a1, 0x20($sp)
    /* A2E4 800092E4 0C002126 */  jal        func_80008498
    /* A2E8 800092E8 00000000 */   nop
    /* A2EC 800092EC 0C001AA6 */  jal        func_80006A98
    /* A2F0 800092F0 3C040400 */   lui       $a0, (0x4000000 >> 16)
    /* A2F4 800092F4 AFA2001C */  sw         $v0, 0x1C($sp)
    /* A2F8 800092F8 0C00247C */  jal        func_800091F0
    /* A2FC 800092FC 00002025 */   or        $a0, $zero, $zero
    /* A300 80009300 8FA2001C */  lw         $v0, 0x1C($sp)
  .L80009304:
    /* A304 80009304 8FBF0014 */  lw         $ra, 0x14($sp)
    /* A308 80009308 27BD0020 */  addiu      $sp, $sp, 0x20
    /* A30C 8000930C 03E00008 */  jr         $ra
    /* A310 80009310 00000000 */   nop
endlabel func_800092B0
