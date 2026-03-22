
nonmatching func_80006698, 0x18

glabel func_80006698
    /* 7698 80006698 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 769C 8000669C AFA40020 */  sw         $a0, 0x20($sp)
    /* 76A0 800066A0 8FAE0020 */  lw         $t6, 0x20($sp)
    /* 76A4 800066A4 3C010400 */  lui        $at, (0x4000000 >> 16)
    /* 76A8 800066A8 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 76AC 800066AC 01C1082B */  sltu       $at, $t6, $at
endlabel func_80006698
