
nonmatching func_80008CB4, 0x58

glabel func_80008CB4
    /* 9CB4 80008CB4 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 9CB8 80008CB8 AFA40020 */  sw         $a0, 0x20($sp)
    /* 9CBC 80008CBC 8FAE0020 */  lw         $t6, 0x20($sp)
    /* 9CC0 80008CC0 AFA0001C */  sw         $zero, 0x1C($sp)
    /* 9CC4 80008CC4 83A9001C */  lb         $t1, 0x1C($sp)
    /* 9CC8 80008CC8 000E7E80 */  sll        $t7, $t6, 26
    /* 9CCC 80008CCC 000FC683 */  sra        $t8, $t7, 26
    /* 9CD0 80008CD0 AFA50024 */  sw         $a1, 0x24($sp)
    /* 9CD4 80008CD4 0018C880 */  sll        $t9, $t8, 2
    /* 9CD8 80008CD8 8FAC0024 */  lw         $t4, 0x24($sp)
    /* 9CDC 80008CDC 332800FC */  andi       $t0, $t9, 0xFC
    /* 9CE0 80008CE0 312AFF03 */  andi       $t2, $t1, 0xFF03
    /* 9CE4 80008CE4 010A5825 */  or         $t3, $t0, $t2
    /* 9CE8 80008CE8 83B8001D */  lb         $t8, 0x1D($sp)
    /* 9CEC 80008CEC 83A8001E */  lb         $t0, 0x1E($sp)
    /* 9CF0 80008CF0 000C6EC0 */  sll        $t5, $t4, 27
    /* 9CF4 80008CF4 000D76C3 */  sra        $t6, $t5, 27
    /* 9CF8 80008CF8 A3AB001C */  sb         $t3, 0x1C($sp)
    /* 9CFC 80008CFC 31CF001F */  andi       $t7, $t6, 0x1F
    /* 9D00 80008D00 3319FFE0 */  andi       $t9, $t8, 0xFFE0
    /* 9D04 80008D04 310AFF07 */  andi       $t2, $t0, 0xFF07
    /* 9D08 80008D08 01F94825 */  or         $t1, $t7, $t9
endlabel func_80008CB4
