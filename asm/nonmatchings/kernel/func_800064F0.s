
nonmatching func_800064F0, 0x20

glabel func_800064F0
    /* 74F0 800064F0 00000000 */  nop
  .L800064F4:
    /* 74F4 800064F4 3C088002 */  lui        $t0, %hi(__osRdb_IP6_CurWrite)
    /* 74F8 800064F8 8D08930C */  lw         $t0, %lo(__osRdb_IP6_CurWrite)($t0)
    /* 74FC 800064FC 3C0F8002 */  lui        $t7, %hi(__osRdb_IP6_Size)
    /* 7500 80006500 8DEF9304 */  lw         $t7, %lo(__osRdb_IP6_Size)($t7)
    /* 7504 80006504 3C018002 */  lui        $at, %hi(__osRdb_IP6_CurWrite)
    /* 7508 80006508 25190001 */  addiu      $t9, $t0, 0x1
    /* 750C 8000650C AC39930C */  sw         $t9, %lo(__osRdb_IP6_CurWrite)($at)
endlabel func_800064F0
