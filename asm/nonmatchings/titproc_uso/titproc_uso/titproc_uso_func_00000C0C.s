nonmatching titproc_uso_func_00000C0C, 0x48

glabel titproc_uso_func_00000C0C
    /* 59A8D8 00000C0C 27BDFFE8 */  .word 0x27BDFFE8
    /* 59A8DC 00000C10 AFBF0014 */  .word 0xAFBF0014
    /* 59A8E0 00000C14 8C860000 */  .word 0x8C860000
    /* 59A8E4 00000C18 00803825 */  .word 0x00803825
    /* 59A8E8 00000C1C 24050003 */  .word 0x24050003
    /* 59A8EC 00000C20 10C00007 */  .word 0x10C00007
    /* 59A8F0 00000C24 00C02025 */  .word 0x00C02025
    /* 59A8F4 00000C28 0C000000 */  jal        titproc_uso_func_01F7FC
    /* 59A8F8 00000C2C AFA70018 */  .word 0xAFA70018
    /* 59A8FC 00000C30 8FA70018 */  .word 0x8FA70018
    /* 59A900 00000C34 3C010000 */  lui        $at, %hi(import_00020098 + 0x14C)
    /* 59A904 00000C38 ACE00000 */  .word 0xACE00000
    /* 59A908 00000C3C AC20014C */  sw         $zero, %lo(import_00020098 + 0x14C)($at)
    /* 59A90C 00000C40 8FBF0014 */  .word 0x8FBF0014
    /* 59A910 00000C44 3C010000 */  lui        $at, %hi(import_00020098 + 0x168)
    /* 59A914 00000C48 AC200168 */  sw         $zero, %lo(import_00020098 + 0x168)($at)
    /* 59A918 00000C4C 03E00008 */  .word 0x03E00008
    /* 59A91C 00000C50 27BD0018 */  .word 0x27BD0018
endlabel titproc_uso_func_00000C0C
