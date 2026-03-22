
nonmatching func_80004B10, 0x20

glabel func_80004B10
    /* 5B10 80004B10 27BDFFD0 */  addiu      $sp, $sp, -0x30
    /* 5B14 80004B14 3C0E8001 */  lui        $t6, %hi(D_8000A440)
    /* 5B18 80004B18 8DCEA440 */  lw         $t6, %lo(D_8000A440)($t6)
    /* 5B1C 80004B1C AFBF001C */  sw         $ra, 0x1C($sp)
    /* 5B20 80004B20 AFA40030 */  sw         $a0, 0x30($sp)
    /* 5B24 80004B24 AFA50034 */  sw         $a1, 0x34($sp)
    /* 5B28 80004B28 AFB00018 */  sw         $s0, 0x18($sp)
    /* 5B2C 80004B2C 15C0000F */  bnez       $t6, .L80004B6C
endlabel func_80004B10
