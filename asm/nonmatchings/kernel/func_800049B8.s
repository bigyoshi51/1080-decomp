
nonmatching func_800049B8, 0x98

glabel func_800049B8
    /* 59B8 800049B8 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 59BC 800049BC AFBF0014 */  sw         $ra, 0x14($sp)
    /* 59C0 800049C0 AFA40028 */  sw         $a0, 0x28($sp)
    /* 59C4 800049C4 AFA00024 */  sw         $zero, 0x24($sp)
  .L800049C8:
    /* 59C8 800049C8 8FAE0024 */  lw         $t6, 0x24($sp)
    /* 59CC 800049CC 3C188001 */  lui        $t8, %hi(D_8000A430)
    /* 59D0 800049D0 8F18A430 */  lw         $t8, %lo(D_8000A430)($t8)
    /* 59D4 800049D4 03AE7821 */  addu       $t7, $sp, $t6
    /* 59D8 800049D8 91EF0029 */  lbu        $t7, 0x29($t7)
    /* 59DC 800049DC 3C198001 */  lui        $t9, %hi(D_8000A430)
    /* 59E0 800049E0 8F39A430 */  lw         $t9, %lo(D_8000A430)($t9)
    /* 59E4 800049E4 3C018002 */  lui        $at, %hi(kdebugserver_bss_01B0)
    /* 59E8 800049E8 8FA90024 */  lw         $t1, 0x24($sp)
    /* 59EC 800049EC 00380821 */  addu       $at, $at, $t8
    /* 59F0 800049F0 A02F94D0 */  sb         $t7, %lo(kdebugserver_bss_01B0)($at)
    /* 59F4 800049F4 3C018001 */  lui        $at, %hi(D_8000A430)
    /* 59F8 800049F8 27280001 */  addiu      $t0, $t9, 0x1
    /* 59FC 800049FC AC28A430 */  sw         $t0, %lo(D_8000A430)($at)
    /* 5A00 80004A00 252A0001 */  addiu      $t2, $t1, 0x1
    /* 5A04 80004A04 2D410003 */  sltiu      $at, $t2, 0x3
    /* 5A08 80004A08 1420FFEF */  bnez       $at, .L800049C8
    /* 5A0C 80004A0C AFAA0024 */   sw        $t2, 0x24($sp)
    /* 5A10 80004A10 3C0B8002 */  lui        $t3, %hi(kdebugserver_bss_01B0)
    /* 5A14 80004A14 256B94D0 */  addiu      $t3, $t3, %lo(kdebugserver_bss_01B0)
    /* 5A18 80004A18 916C0000 */  lbu        $t4, 0x0($t3)
    /* 5A1C 80004A1C 24010002 */  addiu      $at, $zero, 0x2
    /* 5A20 80004A20 15810009 */  bne        $t4, $at, .L80004A48
    /* 5A24 80004A24 00000000 */   nop
    /* 5A28 80004A28 3C048001 */  lui        $a0, %hi(D_8000A420)
    /* 5A2C 80004A2C 8C84A420 */  lw         $a0, %lo(D_8000A420)($a0)
    /* 5A30 80004A30 24050190 */  addiu      $a1, $zero, 0x190
    /* 5A34 80004A34 0C00133A */  jal        func_80004CE8
    /* 5A38 80004A38 24840020 */   addiu     $a0, $a0, 0x20
    /* 5A3C 80004A3C 3C018001 */  lui        $at, %hi(D_8000A430)
    /* 5A40 80004A40 10000019 */  b          .L80004AA8
    /* 5A44 80004A44 AC20A430 */   sw        $zero, %lo(D_8000A430)($at)
  .L80004A48:
    /* 5A48 80004A48 3C0D8001 */  lui        $t5, %hi(D_8000A430)
    /* 5A4C 80004A4C 8DADA430 */  lw         $t5, %lo(D_8000A430)($t5)
endlabel func_800049B8
