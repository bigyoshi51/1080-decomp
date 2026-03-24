
nonmatching func_80005B10, 0x140

glabel func_80005B10
    /* 6B10 80005B10 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 6B14 80005B14 AFA40028 */  sw         $a0, 0x28($sp)
    /* 6B18 80005B18 AFA5002C */  sw         $a1, 0x2C($sp)
    /* 6B1C 80005B1C 8FAE002C */  lw         $t6, 0x2C($sp)
    /* 6B20 80005B20 8FAF0028 */  lw         $t7, 0x28($sp)
    /* 6B24 80005B24 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 6B28 80005B28 AFA60030 */  sw         $a2, 0x30($sp)
    /* 6B2C 80005B2C AFA70034 */  sw         $a3, 0x34($sp)
    /* 6B30 80005B30 AFB00018 */  sw         $s0, 0x18($sp)
    /* 6B34 80005B34 ADEE0014 */  sw         $t6, 0x14($t7)
    /* 6B38 80005B38 8FB90028 */  lw         $t9, 0x28($sp)
    /* 6B3C 80005B3C 8FB8003C */  lw         $t8, 0x3C($sp)
    /* 6B40 80005B40 AF380004 */  sw         $t8, 0x4($t9)
    /* 6B44 80005B44 8FA80028 */  lw         $t0, 0x28($sp)
    /* 6B48 80005B48 AD000000 */  sw         $zero, 0x0($t0)
    /* 6B4C 80005B4C 8FA90028 */  lw         $t1, 0x28($sp)
    /* 6B50 80005B50 AD200008 */  sw         $zero, 0x8($t1)
    /* 6B54 80005B54 8FAB0028 */  lw         $t3, 0x28($sp)
    /* 6B58 80005B58 8FAA0030 */  lw         $t2, 0x30($sp)
    /* 6B5C 80005B5C AD6A011C */  sw         $t2, 0x11C($t3)
    /* 6B60 80005B60 8FAC0034 */  lw         $t4, 0x34($sp)
    /* 6B64 80005B64 8FAD0028 */  lw         $t5, 0x28($sp)
    /* 6B68 80005B68 01807825 */  or         $t7, $t4, $zero
    /* 6B6C 80005B6C 000C77C3 */  sra        $t6, $t4, 31
    /* 6B70 80005B70 ADAE0038 */  sw         $t6, 0x38($t5)
    /* 6B74 80005B74 ADAF003C */  sw         $t7, 0x3C($t5)
    /* 6B78 80005B78 8FB80038 */  lw         $t8, 0x38($sp)
    /* 6B7C 80005B7C 8FB90028 */  lw         $t9, 0x28($sp)
    /* 6B80 80005B80 3C0C8000 */  lui        $t4, %hi(D_80003FE0)
    /* 6B84 80005B84 03004825 */  or         $t1, $t8, $zero
    /* 6B88 80005B88 2D210010 */  sltiu      $at, $t1, 0x10
    /* 6B8C 80005B8C 001847C3 */  sra        $t0, $t8, 31
    /* 6B90 80005B90 01015023 */  subu       $t2, $t0, $at
    /* 6B94 80005B94 252BFFF0 */  addiu      $t3, $t1, -0x10
    /* 6B98 80005B98 AF2B00F4 */  sw         $t3, 0xF4($t9)
    /* 6B9C 80005B9C AF2A00F0 */  sw         $t2, 0xF0($t9)
    /* 6BA0 80005BA0 8FAD0028 */  lw         $t5, 0x28($sp)
    /* 6BA4 80005BA4 258C3FE0 */  addiu      $t4, $t4, %lo(D_80003FE0)
    /* 6BA8 80005BA8 01807825 */  or         $t7, $t4, $zero
    /* 6BAC 80005BAC 000C77C3 */  sra        $t6, $t4, 31
    /* 6BB0 80005BB0 ADAE0100 */  sw         $t6, 0x100($t5)
    /* 6BB4 80005BB4 ADAF0104 */  sw         $t7, 0x104($t5)
    /* 6BB8 80005BB8 8FA90028 */  lw         $t1, 0x28($sp)
    /* 6BBC 80005BBC 3C18003F */  lui        $t8, (0x3FFF01 >> 16)
    /* 6BC0 80005BC0 3718FF01 */  ori        $t8, $t8, (0x3FFF01 & 0xFFFF)
    /* 6BC4 80005BC4 AFB80020 */  sw         $t8, 0x20($sp)
    /* 6BC8 80005BC8 3408FF03 */  ori        $t0, $zero, 0xFF03
    /* 6BCC 80005BCC AD280118 */  sw         $t0, 0x118($t1)
    /* 6BD0 80005BD0 8FAA0020 */  lw         $t2, 0x20($sp)
    /* 6BD4 80005BD4 8FAC0028 */  lw         $t4, 0x28($sp)
    /* 6BD8 80005BD8 3C01003F */  lui        $at, (0x3F0000 >> 16)
    /* 6BDC 80005BDC 01415824 */  and        $t3, $t2, $at
    /* 6BE0 80005BE0 000BCC02 */  srl        $t9, $t3, 16
    /* 6BE4 80005BE4 AD990128 */  sw         $t9, 0x128($t4)
    /* 6BE8 80005BE8 8FAF0028 */  lw         $t7, 0x28($sp)
    /* 6BEC 80005BEC 3C0E0100 */  lui        $t6, (0x1000800 >> 16)
    /* 6BF0 80005BF0 35CE0800 */  ori        $t6, $t6, (0x1000800 & 0xFFFF)
    /* 6BF4 80005BF4 ADEE012C */  sw         $t6, 0x12C($t7)
    /* 6BF8 80005BF8 8FAD0028 */  lw         $t5, 0x28($sp)
    /* 6BFC 80005BFC 24180001 */  addiu      $t8, $zero, 0x1
    /* 6C00 80005C00 ADA00018 */  sw         $zero, 0x18($t5)
    /* 6C04 80005C04 8FA80028 */  lw         $t0, 0x28($sp)
    /* 6C08 80005C08 A5180010 */  sh         $t8, 0x10($t0)
    /* 6C0C 80005C0C 8FA90028 */  lw         $t1, 0x28($sp)
    /* 6C10 80005C10 0C0019AC */  jal        func_800066B0
    /* 6C14 80005C14 A5200012 */   sh        $zero, 0x12($t1)
    /* 6C18 80005C18 3C0A8001 */  lui        $t2, %hi(D_8000A41C)
    /* 6C1C 80005C1C 8D4AA41C */  lw         $t2, %lo(D_8000A41C)($t2)
    /* 6C20 80005C20 8FAB0028 */  lw         $t3, 0x28($sp)
    /* 6C24 80005C24 00408025 */  or         $s0, $v0, $zero
    /* 6C28 80005C28 3C018001 */  lui        $at, %hi(D_8000A41C)
    /* 6C2C 80005C2C AD6A000C */  sw         $t2, 0xC($t3)
    /* 6C30 80005C30 8FB90028 */  lw         $t9, 0x28($sp)
    /* 6C34 80005C34 02002025 */  or         $a0, $s0, $zero
    /* 6C38 80005C38 0C0019B4 */  jal        func_800066D0
    /* 6C3C 80005C3C AC39A41C */   sw        $t9, %lo(D_8000A41C)($at)
    /* 6C40 80005C40 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 6C44 80005C44 8FB00018 */  lw         $s0, 0x18($sp)
    /* 6C48 80005C48 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 6C4C 80005C4C 03E00008 */  jr         $ra
endlabel func_80005B10
