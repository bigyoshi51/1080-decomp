nonmatching func_800066EC, 0x34

# Boundary merge 2026-09-05: the former 1-word "alias entry" func_800066EC
# (`or $a3, $a2, $zero`) is this function's own `n` copy, hoisted above the
# `addiu $sp` prologue by IDO -O1; splat split it off as an orphan. The
# former func_800066F0 symbol is where every caller jal's into (mid-function,
# after the hoisted copy) -- kept addressable as an alt-entry; while the C body
# is on the build path it is pinned in undefined_syms_auto.txt
# (`func_800066F0 = 0x800066F0;`), so drop that pin if this .s is ever
# assembled via INCLUDE_ASM again.

glabel func_800066EC
    /* 76EC 800066EC 00C03825 */  or         $a3, $a2, $zero
alabel func_800066F0
    /* 76F0 800066F0 27BDFFF8 */  addiu      $sp, $sp, -0x8
    /* 76F4 800066F4 10E00008 */  beqz       $a3, .L80006718
    /* 76F8 800066F8 24C6FFFF */   addiu     $a2, $a2, -0x1
  .L800066FC:
    /* 76FC 800066FC 90AE0000 */  lbu        $t6, 0x0($a1)
    /* 7700 80006700 00C03825 */  or         $a3, $a2, $zero
    /* 7704 80006704 24C6FFFF */  addiu      $a2, $a2, -0x1
    /* 7708 80006708 24840001 */  addiu      $a0, $a0, 0x1
    /* 770C 8000670C 24A50001 */  addiu      $a1, $a1, 0x1
    /* 7710 80006710 14E0FFFA */  bnez       $a3, .L800066FC
    /* 7714 80006714 A08EFFFF */   sb        $t6, -0x1($a0)
  .L80006718:
    /* 7718 80006718 03E00008 */  jr         $ra
    /* 771C 8000671C 27BD0008 */   addiu     $sp, $sp, 0x8
endlabel func_800066EC
