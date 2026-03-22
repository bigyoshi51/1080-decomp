
nonmatching func_80005520, 0x14

glabel func_80005520
    /* 6520 80005520 27BDFFD0 */  addiu      $sp, $sp, -0x30
    /* 6524 80005524 3C0E8001 */  lui        $t6, %hi(D_8000A450)
    /* 6528 80005528 8DCEA450 */  lw         $t6, %lo(D_8000A450)($t6)
    /* 652C 8000552C AFBF001C */  sw         $ra, 0x1C($sp)
    /* 6530 80005530 AFA40030 */  sw         $a0, 0x30($sp)
endlabel func_80005520
