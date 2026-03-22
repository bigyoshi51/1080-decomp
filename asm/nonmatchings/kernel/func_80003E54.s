
nonmatching func_80003E54, 0x10

glabel func_80003E54
    /* 4E54 80003E54 3C010100 */  lui        $at, (0x1000000 >> 16)
    /* 4E58 80003E58 3C0BA500 */  lui        $t3, (0xA5000000 >> 16)
    /* 4E5C 80003E5C 8F290010 */  lw         $t1, 0x10($t9)
    /* 4E60 80003E60 00001025 */  or         $v0, $zero, $zero
endlabel func_80003E54
