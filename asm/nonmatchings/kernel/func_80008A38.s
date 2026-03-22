
nonmatching func_80008A38, 0x68

glabel func_80008A38
    /* 9A38 80008A38 27BDFF90 */  addiu      $sp, $sp, -0x70
    /* 9A3C 80008A3C AFBF001C */  sw         $ra, 0x1C($sp)
    /* 9A40 80008A40 AFB00018 */  sw         $s0, 0x18($sp)
    /* 9A44 80008A44 0C001AA6 */  jal        func_80006A98
    /* 9A48 80008A48 3C040408 */   lui       $a0, (0x4080000 >> 16)
    /* 9A4C 80008A4C 00408025 */  or         $s0, $v0, $zero
    /* 9A50 80008A50 2605FFFC */  addiu      $a1, $s0, -0x4
    /* 9A54 80008A54 0C001A94 */  jal        func_80006A50
    /* 9A58 80008A58 3C040408 */   lui       $a0, (0x4080000 >> 16)
    /* 9A5C 80008A5C 24040001 */  addiu      $a0, $zero, 0x1
    /* 9A60 80008A60 240503E8 */  addiu      $a1, $zero, 0x3E8
    /* 9A64 80008A64 0C001EA6 */  jal        func_80007A98
    /* 9A68 80008A68 27A60024 */   addiu     $a2, $sp, 0x24
    /* 9A6C 80008A6C 0C002343 */  jal        func_80008D0C
    /* 9A70 80008A70 27A40024 */   addiu     $a0, $sp, 0x24
    /* 9A74 80008A74 27A40024 */  addiu      $a0, $sp, 0x24
    /* 9A78 80008A78 2405004C */  addiu      $a1, $zero, 0x4C
    /* 9A7C 80008A7C 0C001CFE */  jal        func_800073F8
    /* 9A80 80008A80 24060002 */   addiu     $a2, $zero, 0x2
    /* 9A84 80008A84 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 9A88 80008A88 240E0001 */  addiu      $t6, $zero, 0x1
    /* 9A8C 80008A8C 3C018002 */  lui        $at, %hi(__rmonRcpAtBreak)
    /* 9A90 80008A90 8FB00018 */  lw         $s0, 0x18($sp)
    /* 9A94 80008A94 A02EFF78 */  sb         $t6, %lo(__rmonRcpAtBreak)($at)
    /* 9A98 80008A98 03E00008 */  jr         $ra
    /* 9A9C 80008A9C 27BD0070 */   addiu     $sp, $sp, 0x70
endlabel func_80008A38
