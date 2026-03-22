
nonmatching func_80009C30, 0x20

glabel func_80009C30
    /* AC30 80009C30 01A15025 */  or         $t2, $t5, $at
    /* AC34 80009C34 AD460000 */  sw         $a2, 0x0($t2)
    /* AC38 80009C38 03E00008 */  jr         $ra
    /* AC3C 80009C3C 00001025 */   or        $v0, $zero, $zero
/* glabel func_80009C40 */
    /* AC40 80009C40 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* AC44 80009C44 AFBF0014 */  sw         $ra, 0x14($sp)
    /* AC48 80009C48 AFA40018 */  sw         $a0, 0x18($sp)
    /* AC4C 80009C4C 0C0015B0 */  jal        func_800056C0
endlabel func_80009C30
