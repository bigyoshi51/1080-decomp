nonmatching mgrproc_uso_func_00000B20, 0x3C

glabel mgrproc_uso_func_00000B20
    /* 000B20 00000B20 27BDFFE8 */  .word 0x27BDFFE8
    /* 000B24 00000B24 AFBF0014 */  .word 0xAFBF0014
    lui $a0, %hi(import_80263D60)   /* 000B28 3C040000 -> import_80263D60 */
    jal import_000B144C   /* 000B2C 0C000000 -> import_000B144C */
    /* 000B30 00000B30 8C840030 */  .word 0x8C840030
    lui $a0, %hi(import_80263D60)   /* 000B34 3C040000 -> import_80263D60 */
    jal import_000A5938   /* 000B38 0C000000 -> import_000A5938 */
    /* 000B3C 00000B3C 8C840030 */  .word 0x8C840030
    lui $a0, %hi(import_80020098)   /* 000B40 3C040000 -> import_80020098 */
    jal import_000A7EE0   /* 000B44 0C000000 -> import_000A7EE0 */
    /* 000B48 00000B48 24840000 */  .word 0x24840000
    /* 000B4C 00000B4C 8FBF0014 */  .word 0x8FBF0014
    /* 000B50 00000B50 27BD0018 */  .word 0x27BD0018
    /* 000B54 00000B54 03E00008 */  .word 0x03E00008
    /* 000B58 00000B58 00000000 */  .word 0x00000000
endlabel mgrproc_uso_func_00000B20
