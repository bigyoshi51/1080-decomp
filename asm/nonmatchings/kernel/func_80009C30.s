
nonmatching func_80009C30, 0x10

glabel func_80009C30
    /* AC30 80009C30 01A15025 */  or         $t2, $t5, $at
    /* AC34 80009C34 AD460000 */  sw         $a2, 0x0($t2)
    /* AC38 80009C38 03E00008 */  jr         $ra
    /* AC3C 80009C3C 00001025 */   or        $v0, $zero, $zero
endlabel func_80009C30
