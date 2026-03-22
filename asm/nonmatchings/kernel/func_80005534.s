
nonmatching func_80005534, 0x50

glabel func_80005534
    /* 6534 80005534 AFA50034 */  sw         $a1, 0x34($sp)
    /* 6538 80005538 AFA60038 */  sw         $a2, 0x38($sp)
    /* 653C 8000553C 15C00067 */  bnez       $t6, .L800056DC
    /* 6540 80005540 AFA7003C */   sw        $a3, 0x3C($sp)
    /* 6544 80005544 8FA40034 */  lw         $a0, 0x34($sp)
    /* 6548 80005548 8FA50038 */  lw         $a1, 0x38($sp)
    /* 654C 8000554C 0C0014F4 */  jal        func_800053D0
    /* 6550 80005550 8FA6003C */   lw        $a2, 0x3C($sp)
    /* 6554 80005554 3C048002 */  lui        $a0, %hi(pimgr_bss_17A0)
    /* 6558 80005558 3C058002 */  lui        $a1, %hi(pimgr_bss_17B8)
    /* 655C 8000555C 24A5B628 */  addiu      $a1, $a1, %lo(pimgr_bss_17B8)
    /* 6560 80005560 2484B610 */  addiu      $a0, $a0, %lo(pimgr_bss_17A0)
    /* 6564 80005564 0C0014F4 */  jal        func_800053D0
    /* 6568 80005568 24060001 */   addiu     $a2, $zero, 0x1
    /* 656C 8000556C 3C0F8001 */  lui        $t7, %hi(__osPiAccessQueueEnabled)
    /* 6570 80005570 8DEFA480 */  lw         $t7, %lo(__osPiAccessQueueEnabled)($t7)
    /* 6574 80005574 15E00003 */  bnez       $t7, func_80005584
    /* 6578 80005578 00000000 */   nop
    /* 657C 8000557C 0C001700 */  jal        func_80005C00
    /* 6580 80005580 00000000 */   nop
endlabel func_80005534
