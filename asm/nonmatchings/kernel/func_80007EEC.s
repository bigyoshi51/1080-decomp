
nonmatching func_80007EEC, 0xDC

glabel func_80007EEC
    /* 8EEC 80007EEC 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 8EF0 80007EF0 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 8EF4 80007EF4 3C048002 */  lui        $a0, %hi(__rmonMQ)
    /* 8EF8 80007EF8 3C058002 */  lui        $a1, %hi(rmonmisc_bss_01C8)
    /* 8EFC 80007EFC 24A5BE18 */  addiu      $a1, $a1, %lo(rmonmisc_bss_01C8)
    /* 8F00 80007F00 2484BC50 */  addiu      $a0, $a0, %lo(__rmonMQ)
    /* 8F04 80007F04 0C0014F4 */  jal        func_800053D0
    /* 8F08 80007F08 24060008 */   addiu     $a2, $zero, 0x8
    /* 8F0C 80007F0C 3C058002 */  lui        $a1, %hi(__rmonMQ)
    /* 8F10 80007F10 24A5BC50 */  addiu      $a1, $a1, %lo(__rmonMQ)
    /* 8F14 80007F14 2404000A */  addiu      $a0, $zero, 0xA
    /* 8F18 80007F18 0C001478 */  jal        func_800051E0
    /* 8F1C 80007F1C 24060002 */   addiu     $a2, $zero, 0x2
    /* 8F20 80007F20 3C058002 */  lui        $a1, %hi(__rmonMQ)
    /* 8F24 80007F24 24A5BC50 */  addiu      $a1, $a1, %lo(__rmonMQ)
    /* 8F28 80007F28 2404000B */  addiu      $a0, $zero, 0xB
    /* 8F2C 80007F2C 0C001478 */  jal        func_800051E0
    /* 8F30 80007F30 24060004 */   addiu     $a2, $zero, 0x4
    /* 8F34 80007F34 3C058002 */  lui        $a1, %hi(__rmonMQ)
    /* 8F38 80007F38 24A5BC50 */  addiu      $a1, $a1, %lo(__rmonMQ)
    /* 8F3C 80007F3C 2404000C */  addiu      $a0, $zero, 0xC
    /* 8F40 80007F40 0C001478 */  jal        func_800051E0
    /* 8F44 80007F44 24060008 */   addiu     $a2, $zero, 0x8
    /* 8F48 80007F48 3C058002 */  lui        $a1, %hi(__rmonMQ)
    /* 8F4C 80007F4C 24A5BC50 */  addiu      $a1, $a1, %lo(__rmonMQ)
    /* 8F50 80007F50 2404000D */  addiu      $a0, $zero, 0xD
    /* 8F54 80007F54 0C001478 */  jal        func_800051E0
    /* 8F58 80007F58 00003025 */   or        $a2, $zero, $zero
    /* 8F5C 80007F5C 3C0E8002 */  lui        $t6, %hi(rmonmisc_bss_01E8)
    /* 8F60 80007F60 25CEBE38 */  addiu      $t6, $t6, %lo(rmonmisc_bss_01E8)
    /* 8F64 80007F64 25CF4000 */  addiu      $t7, $t6, 0x4000
    /* 8F68 80007F68 3C048002 */  lui        $a0, %hi(rmonmisc_bss_0018)
    /* 8F6C 80007F6C 3C068000 */  lui        $a2, %hi(D_800055F0)
    /* 8F70 80007F70 241800FF */  addiu      $t8, $zero, 0xFF
    /* 8F74 80007F74 AFB80014 */  sw         $t8, 0x14($sp)
    /* 8F78 80007F78 24C655F0 */  addiu      $a2, $a2, %lo(D_800055F0)
    /* 8F7C 80007F7C 2484BC68 */  addiu      $a0, $a0, %lo(rmonmisc_bss_0018)
    /* 8F80 80007F80 AFAF0010 */  sw         $t7, 0x10($sp)
    /* 8F84 80007F84 00002825 */  or         $a1, $zero, $zero
    /* 8F88 80007F88 0C0017C4 */  jal        func_80005F10
    /* 8F8C 80007F8C 00003825 */   or        $a3, $zero, $zero
    /* 8F90 80007F90 3C058002 */  lui        $a1, %hi(rmonmisc_bss_4208)
    /* 8F94 80007F94 3C068002 */  lui        $a2, %hi(rmonmisc_bss_41E8)
    /* 8F98 80007F98 24C6FE38 */  addiu      $a2, $a2, %lo(rmonmisc_bss_41E8)
    /* 8F9C 80007F9C 24A5FE58 */  addiu      $a1, $a1, %lo(rmonmisc_bss_4208)
    /* 8FA0 80007FA0 24040096 */  addiu      $a0, $zero, 0x96
    /* 8FA4 80007FA4 0C001648 */  jal        func_80005920
    /* 8FA8 80007FA8 24070008 */   addiu     $a3, $zero, 0x8
    /* 8FAC 80007FAC 3C048002 */  lui        $a0, %hi(rmonmisc_bss_0018)
    /* 8FB0 80007FB0 0C002844 */  jal        func_8000A110
    /* 8FB4 80007FB4 2484BC68 */   addiu     $a0, $a0, %lo(rmonmisc_bss_0018)
    /* 8FB8 80007FB8 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 8FBC 80007FBC 27BD0020 */  addiu      $sp, $sp, 0x20
    /* 8FC0 80007FC0 03E00008 */  jr         $ra
    /* 8FC4 80007FC4 00000000 */   nop
endlabel func_80007EEC
