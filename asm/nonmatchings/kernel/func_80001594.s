
nonmatching func_80001594, 0x3C

glabel func_80001594
    /* 2594 80001594 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 2598 80001598 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 259C 8000159C AFB00018 */  sw         $s0, 0x18($sp)
    /* 25A0 800015A0 00A08025 */  or         $s0, $a1, $zero
    /* 25A4 800015A4 0C000561 */  jal        func_80001584
    /* 25A8 800015A8 AFA40020 */   sw        $a0, 0x20($sp)
    /* 25AC 800015AC 3C0E8001 */  lui        $t6, %hi(D_800130A0)
    /* 25B0 800015B0 25CE30A0 */  addiu      $t6, $t6, %lo(D_800130A0)
    /* 25B4 800015B4 3C018001 */  lui        $at, %hi(D_8001309C)
    /* 25B8 800015B8 AC2E309C */  sw         $t6, %lo(D_8001309C)($at)
    /* 25BC 800015BC 0C00021D */  jal        func_80000874
    /* 25C0 800015C0 8FA40020 */   lw        $a0, 0x20($sp)
    /* 25C4 800015C4 3C078001 */  lui        $a3, %hi(D_80012BC0)
    /* 25C8 800015C8 24E72BC0 */  addiu      $a3, $a3, %lo(D_80012BC0)
    /* 25CC 800015CC 3C0F8000 */  lui        $t7, (0x80000000 >> 16)
endlabel func_80001594
