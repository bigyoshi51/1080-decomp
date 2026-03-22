
nonmatching func_800007C4, 0x10

glabel func_800007C4
    /* 17C4 800007C4 AFA40000 */  sw         $a0, 0x0($sp)
    /* 17C8 800007C8 AFA50004 */  sw         $a1, 0x4($sp)
    /* 17CC 800007CC 03E00008 */  jr         $ra
    /* 17D0 800007D0 24020001 */   addiu     $v0, $zero, 0x1
endlabel func_800007C4
