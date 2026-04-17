
nonmatching func_80008C30, 0x118

glabel func_80008C30
    /* 9C30 80008C30 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 9C34 80008C34 AFA40020 */  sw         $a0, 0x20($sp)
    /* 9C38 80008C38 8FAE0020 */  lw         $t6, 0x20($sp)
    /* 9C3C 80008C3C AFA50024 */  sw         $a1, 0x24($sp)
    /* 9C40 80008C40 8FAC0024 */  lw         $t4, 0x24($sp)
    /* 9C44 80008C44 000E7E80 */  sll        $t7, $t6, 26
    /* 9C48 80008C48 AFA0001C */  sw         $zero, 0x1C($sp)
    /* 9C4C 80008C4C 000FC683 */  sra        $t8, $t7, 26
    /* 9C50 80008C50 83A9001C */  lb         $t1, 0x1C($sp)
    /* 9C54 80008C54 0018C880 */  sll        $t9, $t8, 2
    /* 9C58 80008C58 83B8001D */  lb         $t8, 0x1D($sp)
    /* 9C5C 80008C5C 000C6EC0 */  sll        $t5, $t4, 27
    /* 9C60 80008C60 332800FC */  andi       $t0, $t9, 0xFC
    /* 9C64 80008C64 000D76C3 */  sra        $t6, $t5, 27
    /* 9C68 80008C68 312AFF03 */  andi       $t2, $t1, 0xFF03
    /* 9C6C 80008C6C 31CF001F */  andi       $t7, $t6, 0x1F
    /* 9C70 80008C70 3319FFE0 */  andi       $t9, $t8, 0xFFE0
    /* 9C74 80008C74 010A5825 */  or         $t3, $t0, $t2
    /* 9C78 80008C78 01F94825 */  or         $t1, $t7, $t9
    /* 9C7C 80008C7C AFBF0014 */  sw         $ra, 0x14($sp)
    /* 9C80 80008C80 A3AB001C */  sb         $t3, 0x1C($sp)
    /* 9C84 80008C84 A3A9001D */  sb         $t1, 0x1D($sp)
    /* 9C88 80008C88 3C040400 */  lui        $a0, (0x4001000 >> 16)
    /* 9C8C 80008C8C 34841000 */  ori        $a0, $a0, (0x4001000 & 0xFFFF)
    /* 9C90 80008C90 0C001A94 */  jal        func_80006A50
    /* 9C94 80008C94 8FA5001C */   lw        $a1, 0x1C($sp)
    /* 9C98 80008C98 3C040408 */  lui        $a0, (0x4080000 >> 16)
    /* 9C9C 80008C9C 0C001A94 */  jal        func_80006A50
    /* 9CA0 80008CA0 00002825 */   or        $a1, $zero, $zero
    /* 9CA4 80008CA4 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 9CA8 80008CA8 27BD0020 */  addiu      $sp, $sp, 0x20
    /* 9CAC 80008CAC 03E00008 */  jr         $ra
    /* 9CB0 80008CB0 00000000 */   nop
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
    /* 9D0C 80008D0C 354B0020 */  ori        $t3, $t2, 0x20
    /* 9D10 80008D10 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 9D14 80008D14 A3A9001D */  sb         $t1, 0x1D($sp)
    /* 9D18 80008D18 A3AB001E */  sb         $t3, 0x1E($sp)
    /* 9D1C 80008D1C 3C040400 */  lui        $a0, (0x4001000 >> 16)
    /* 9D20 80008D20 34841000 */  ori        $a0, $a0, (0x4001000 & 0xFFFF)
    /* 9D24 80008D24 0C001A94 */  jal        func_80006A50
    /* 9D28 80008D28 8FA5001C */   lw        $a1, 0x1C($sp)
    /* 9D2C 80008D2C 3C040408 */  lui        $a0, (0x4080000 >> 16)
    /* 9D30 80008D30 0C001A94 */  jal        func_80006A50
    /* 9D34 80008D34 00002825 */   or        $a1, $zero, $zero
    /* 9D38 80008D38 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 9D3C 80008D3C 27BD0020 */  addiu      $sp, $sp, 0x20
    /* 9D40 80008D40 03E00008 */  jr         $ra
    /* 9D44 80008D44 00000000 */   nop
endlabel func_80008C30
