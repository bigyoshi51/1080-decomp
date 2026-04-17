
nonmatching func_80009C40, 0x4C

glabel func_80009C40
    /* AC40 80009C40 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* AC44 80009C44 AFBF0014 */  sw         $ra, 0x14($sp)
    /* AC48 80009C48 AFA40018 */  sw         $a0, 0x18($sp)
    /* AC4C 80009C4C 0C0015B0 */  jal        func_800056C0
    /* AC50 80009C50 AFA5001C */  sw         $a1, 0x1C($sp)
    /* AC54 80009C54 10400003 */  beqz       $v0, .L80009C64
    /* AC58 80009C58 00000000 */   nop
    /* AC5C 80009C5C 10000007 */  b          .L80009C7C
    /* AC60 80009C60 2402FFFF */   addiu     $v0, $zero, -0x1
  .L80009C64:
    /* AC64 80009C64 8FAF0018 */  lw         $t7, 0x18($sp)
    /* AC68 80009C68 8FAE001C */  lw         $t6, 0x1C($sp)
    /* AC6C 80009C6C 3C01A000 */  lui        $at, %hi(D_A0000000)
    /* AC70 80009C70 01E1C025 */  or         $t8, $t7, $at
    /* AC74 80009C74 00001025 */  or         $v0, $zero, $zero
    /* AC78 80009C78 AF0E0000 */  sw         $t6, %lo(D_A0000000)($t8)
  .L80009C7C:
    /* AC7C 80009C7C 8FBF0014 */  lw         $ra, 0x14($sp)
    /* AC80 80009C80 27BD0018 */  addiu      $sp, $sp, 0x18
    /* AC84 80009C84 03E00008 */  jr         $ra
    /* AC88 80009C88 00000000 */   nop
    /* AC8C 80009C8C 00000000 */  nop
endlabel func_80009C40
