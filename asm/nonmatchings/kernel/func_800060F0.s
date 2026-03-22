
nonmatching func_800060F0, 0x18

glabel func_800060F0
    /* 70F0 800060F0 14800003 */  bnez       $a0, .L80006100
    /* 70F4 800060F4 00000000 */   nop
    /* 70F8 800060F8 3C048001 */  lui        $a0, %hi(__osRunningThread)
    /* 70FC 800060FC 8C84A420 */  lw         $a0, %lo(__osRunningThread)($a0)
  .L80006100:
    /* 7100 80006100 03E00008 */  jr         $ra
    /* 7104 80006104 8C820004 */   lw        $v0, 0x4($a0)
endlabel func_800060F0
    /* 7108 80006108 00000000 */  nop
    /* 710C 8000610C 00000000 */  nop
