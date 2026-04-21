/* stolen prologue of next function (timproc_uso_b5_func_0000E5D8): lui $v0, 0; lw $v0, 0($v0) — loads *D_00000000 into $v0 for use at 0xE5E0 (`lw $t6, 0x70($v0)`). */
glabel _pad_timproc_uso_b5_func_0000E5AC, local
.word 0x3C020000
.word 0x8C420000
endlabel _pad_timproc_uso_b5_func_0000E5AC
