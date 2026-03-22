
nonmatching func_800073DC, 0x1C

glabel func_800073DC
    /* 83DC 800073DC 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 83E0 800073E0 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 83E4 800073E4 AFA40028 */  sw         $a0, 0x28($sp)
    /* 83E8 800073E8 0C00270C */  jal        func_80009C30
    /* 83EC 800073EC AFB00018 */   sw        $s0, 0x18($sp)
    /* 83F0 800073F0 8FAE0028 */  lw         $t6, 0x28($sp)
    /* 83F4 800073F4 00408025 */  or         $s0, $v0, $zero
endlabel func_800073DC
