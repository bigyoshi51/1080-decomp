
nonmatching func_80008DF0, 0x18

glabel func_80008DF0
    /* 9DF0 80008DF0 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 9DF4 80008DF4 3C0E8002 */  lui        $t6, %hi(D_8001FF88)
    /* 9DF8 80008DF8 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 9DFC 80008DFC AFA40018 */  sw         $a0, 0x18($sp)
    /* 9E00 80008E00 25CEFF88 */  addiu      $t6, $t6, %lo(D_8001FF88)
    /* 9E04 80008E04 8DC50000 */  lw         $a1, 0x0($t6)
endlabel func_80008DF0
