nonmatching func_00001F78, 0x50

glabel func_00001F78
    /* DD29E4 00001F78 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* DD29E8 00001F7C AFBF0014 */  sw         $ra, 0x14($sp)
    /* DD29EC 00001F80 00803825 */  or         $a3, $a0, $zero
    /* DD29F0 00001F84 AFA70018 */  sw         $a3, 0x18($sp)
    /* DD29F4 00001F88 0C000000 */  jal        func_00000000
    /* DD29F8 00001F8C 00002025 */   or        $a0, $zero, $zero
    /* DD29FC 00001F90 8FA70018 */  lw         $a3, 0x18($sp)
    /* DD2A00 00001F94 8CEE0074 */  lw         $t6, 0x74($a3)
    /* DD2A04 00001F98 8DCF0044 */  lw         $t7, 0x44($t6)
    /* DD2A08 00001F9C AC4F0044 */  sw         $t7, 0x44($v0)
    /* DD2A0C 00001FA0 8CF80074 */  lw         $t8, 0x74($a3)
    /* DD2A10 00001FA4 AF020044 */  sw         $v0, 0x44($t8)
    /* DD2A14 00001FA8 8CF90078 */  lw         $t9, 0x78($a3)
    /* DD2A18 00001FAC ACE20074 */  sw         $v0, 0x74($a3)
    /* DD2A1C 00001FB0 27280001 */  addiu      $t0, $t9, 0x1
    /* DD2A20 00001FB4 ACE80078 */  sw         $t0, 0x78($a3)
    /* DD2A24 00001FB8 8FBF0014 */  lw         $ra, 0x14($sp)
    /* DD2A28 00001FBC 27BD0018 */  addiu      $sp, $sp, 0x18
    /* DD2A2C 00001FC0 03E00008 */  jr         $ra
    /* DD2A30 00001FC4 00000000 */   nop
endlabel func_00001F78
