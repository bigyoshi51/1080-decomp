
nonmatching func_80005584, 0x13C

glabel func_80005584
    /* 6584 80005584 3C058002 */  lui        $a1, %hi(pimgr_bss_17A0)
    /* 6588 80005588 3C062222 */  lui        $a2, (0x22222222 >> 16)
    /* 658C 8000558C 34C62222 */  ori        $a2, $a2, (0x22222222 & 0xFFFF)
    /* 6590 80005590 24A5B610 */  addiu      $a1, $a1, %lo(pimgr_bss_17A0)
    /* 6594 80005594 0C001478 */  jal        func_800051E0
    /* 6598 80005598 24040008 */   addiu     $a0, $zero, 0x8
    /* 659C 8000559C 2418FFFF */  addiu      $t8, $zero, -0x1
    /* 65A0 800055A0 AFB80028 */  sw         $t8, 0x28($sp)
    /* 65A4 800055A4 0C00193C */  jal        func_800064F0
    /* 65A8 800055A8 00002025 */   or        $a0, $zero, $zero
    /* 65AC 800055AC AFA20024 */  sw         $v0, 0x24($sp)
    /* 65B0 800055B0 8FB90024 */  lw         $t9, 0x24($sp)
    /* 65B4 800055B4 8FA80030 */  lw         $t0, 0x30($sp)
    /* 65B8 800055B8 0328082A */  slt        $at, $t9, $t0
    /* 65BC 800055BC 10200005 */  beqz       $at, .L800055D4
    /* 65C0 800055C0 00000000 */   nop
    /* 65C4 800055C4 AFB90028 */  sw         $t9, 0x28($sp)
    /* 65C8 800055C8 00002025 */  or         $a0, $zero, $zero
    /* 65CC 800055CC 0C001944 */  jal        func_80006510
    /* 65D0 800055D0 01002825 */   or        $a1, $t0, $zero
  .L800055D4:
    /* 65D4 800055D4 0C0019AC */  jal        func_800066B0
    /* 65D8 800055D8 00000000 */   nop
    /* 65DC 800055DC 3C018001 */  lui        $at, %hi(D_8000A450)
    /* 65E0 800055E0 8FAB0034 */  lw         $t3, 0x34($sp)
    /* 65E4 800055E4 3C0A8002 */  lui        $t2, %hi(pimgr_bss_0000)
    /* 65E8 800055E8 3C0C8002 */  lui        $t4, %hi(pimgr_bss_17A0)
    /* 65EC 800055EC 24090001 */  addiu      $t1, $zero, 0x1
  alabel D_800055F0
    /* 65F0 800055F0 254A9E70 */  addiu      $t2, $t2, %lo(pimgr_bss_0000)
    /* 65F4 800055F4 258CB610 */  addiu      $t4, $t4, %lo(pimgr_bss_17A0)
    /* 65F8 800055F8 AC29A450 */  sw         $t1, %lo(D_8000A450)($at)
    /* 65FC 800055FC AC2AA454 */  sw         $t2, %lo(D_8000A454)($at)
    /* 6600 80005600 AC2CA45C */  sw         $t4, %lo(D_8000A45C)($at)
    /* 6604 80005604 3C188002 */  lui        $t8, %hi(pimgr_bss_01B0)
    /* 6608 80005608 AC2BA458 */  sw         $t3, %lo(D_8000A458)($at)
    /* 660C 8000560C 8FA80030 */  lw         $t0, 0x30($sp)
    /* 6610 80005610 3C018001 */  lui        $at, %hi(D_8000A460)
    /* 6614 80005614 3C0D8002 */  lui        $t5, %hi(__osPiAccessQueue)
    /* 6618 80005618 3C0E8000 */  lui        $t6, %hi(func_80004A50)
    /* 661C 8000561C 3C0F8000 */  lui        $t7, %hi(func_800056F0)
    /* 6620 80005620 2718A020 */  addiu      $t8, $t8, %lo(pimgr_bss_01B0)
    /* 6624 80005624 25ADB638 */  addiu      $t5, $t5, %lo(__osPiAccessQueue)
    /* 6628 80005628 25CE4A50 */  addiu      $t6, $t6, %lo(func_80004A50)
    /* 662C 8000562C 25EF56F0 */  addiu      $t7, $t7, %lo(func_800056F0)
    /* 6630 80005630 27191000 */  addiu      $t9, $t8, 0x1000
    /* 6634 80005634 3C068000 */  lui        $a2, %hi(D_80006060)
    /* 6638 80005638 3C078001 */  lui        $a3, %hi(D_8000A450)
    /* 663C 8000563C AFA2002C */  sw         $v0, 0x2C($sp)
    /* 6640 80005640 AC2DA460 */  sw         $t5, %lo(D_8000A460)($at)
    /* 6644 80005644 AC2EA464 */  sw         $t6, %lo(D_8000A464)($at)
    /* 6648 80005648 AC2FA468 */  sw         $t7, %lo(D_8000A468)($at)
    /* 664C 8000564C 24E7A450 */  addiu      $a3, $a3, %lo(D_8000A450)
    /* 6650 80005650 24C66060 */  addiu      $a2, $a2, %lo(D_80006060)
    /* 6654 80005654 AFB90010 */  sw         $t9, 0x10($sp)
    /* 6658 80005658 01402025 */  or         $a0, $t2, $zero
    /* 665C 8000565C 00002825 */  or         $a1, $zero, $zero
    /* 6660 80005660 0C0017C4 */  jal        func_80005F10
    /* 6664 80005664 AFA80014 */   sw        $t0, 0x14($sp)
    /* 6668 80005668 3C048002 */  lui        $a0, %hi(pimgr_bss_0000)
    /* 666C 8000566C 0C002844 */  jal        func_8000A110
    /* 6670 80005670 24849E70 */   addiu     $a0, $a0, %lo(pimgr_bss_0000)
    /* 6674 80005674 8FAC0030 */  lw         $t4, 0x30($sp)
    /* 6678 80005678 3C098002 */  lui        $t1, %hi(pimgr_bss_1360)
    /* 667C 8000567C 2529B1D0 */  addiu      $t1, $t1, %lo(pimgr_bss_1360)
    /* 6680 80005680 252B0400 */  addiu      $t3, $t1, 0x400
    /* 6684 80005684 3C048002 */  lui        $a0, %hi(pimgr_bss_11B0)
    /* 6688 80005688 3C068000 */  lui        $a2, %hi(D_80005AEC)
    /* 668C 8000568C 258DFFFF */  addiu      $t5, $t4, -0x1
    /* 6690 80005690 AFAD0014 */  sw         $t5, 0x14($sp)
    /* 6694 80005694 24C65AEC */  addiu      $a2, $a2, %lo(D_80005AEC)
    /* 6698 80005698 2484B020 */  addiu      $a0, $a0, %lo(pimgr_bss_11B0)
    /* 669C 8000569C AFAB0010 */  sw         $t3, 0x10($sp)
    /* 66A0 800056A0 00002825 */  or         $a1, $zero, $zero
    /* 66A4 800056A4 0C0017C4 */  jal        func_80005F10
    /* 66A8 800056A8 00003825 */   or        $a3, $zero, $zero
    /* 66AC 800056AC 3C048002 */  lui        $a0, %hi(pimgr_bss_11B0)
    /* 66B0 800056B0 0C002844 */  jal        func_8000A110
    /* 66B4 800056B4 2484B020 */   addiu     $a0, $a0, %lo(pimgr_bss_11B0)
    /* 66B8 800056B8 0C0019B4 */  jal        func_800066D0
    /* 66BC 800056BC 8FA4002C */   lw        $a0, 0x2C($sp)
endlabel func_80005584
