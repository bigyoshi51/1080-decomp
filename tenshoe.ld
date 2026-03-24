SECTIONS
{
    __romPos = 0;
    header_ROM_START = __romPos;
    header_VRAM = ADDR(.header);
    .header : AT(header_ROM_START)
    {
        FILL(0x00000000);
        header_DATA_START = .;
        build/assets/header.bin.o(.data);
        header_DATA_END = .;
        header_DATA_SIZE = ABSOLUTE(header_DATA_END - header_DATA_START);
    }
    __romPos += SIZEOF(.header);
    header_ROM_END = __romPos;
    header_VRAM_END = .;

    ipl3_ROM_START = __romPos;
    ipl3_VRAM = ADDR(.ipl3);
    .ipl3 : AT(ipl3_ROM_START)
    {
        FILL(0x00000000);
        ipl3_DATA_START = .;
        build/assets/ipl3.bin.o(.data);
        ipl3_DATA_END = .;
        ipl3_DATA_SIZE = ABSOLUTE(ipl3_DATA_END - ipl3_DATA_START);
    }
    __romPos += SIZEOF(.ipl3);
    ipl3_ROM_END = __romPos;
    ipl3_VRAM_END = .;

    kernel_ROM_START = __romPos;
    kernel_VRAM = ADDR(.kernel);
    .kernel 0x80000000 : AT(kernel_ROM_START)
    {
        FILL(0x00000000);
        kernel_TEXT_START = .;
        build/src/kernel/kernel_000.c.o(.text);
        build/src/kernel/kernel_027.c.o(.text);
        build/src/kernel/kernel_001.c.o(.text);
        build/src/kernel/kernel_002.c.o(.text);
        build/src/kernel/kernel_003.c.o(.text);
        build/src/kernel/kernel_004.c.o(.text);
        build/src/kernel/kernel_005.c.o(.text);
        build/src/kernel/kernel_006.c.o(.text);
        build/src/kernel/kernel_007.c.o(.text);
        build/src/kernel/kernel_008.c.o(.text);
        build/src/kernel/kernel_009.c.o(.text);
        build/src/kernel/kernel_010.c.o(.text);
        build/src/kernel/kernel_011.c.o(.text);
        build/src/kernel/kernel_013.c.o(.text);
        build/src/kernel/kernel_014.c.o(.text);
        build/src/kernel/kernel_015.c.o(.text);
        build/src/kernel/kernel_016.c.o(.text);
        build/src/kernel/kernel_017.c.o(.text);
        build/src/kernel/kernel_018.c.o(.text);
        build/src/kernel/kernel_036.c.o(.text);
        build/src/kernel/kernel_032.c.o(.text);
        build/src/kernel/kernel_033.c.o(.text);
        build/src/kernel/kernel_034.c.o(.text);
        build/src/kernel/kernel_029.c.o(.text);
        build/src/kernel/kernel_019.c.o(.text);
        build/src/kernel/kernel_020.c.o(.text);
        build/src/kernel/kernel_030.c.o(.text);
        build/src/kernel/kernel_031.c.o(.text);
        build/src/kernel/kernel_021.c.o(.text);
        build/src/kernel/kernel_022.c.o(.text);
        build/src/kernel/kernel_028.c.o(.text);
        build/src/kernel/kernel_035.c.o(.text);
        build/src/kernel/kernel_023.c.o(.text);
        build/src/kernel/kernel_024.c.o(.text);
        build/src/kernel/kernel_025.c.o(.text);
        build/src/kernel/kernel_026.c.o(.text);
        build/src/kernel/kernel_037.c.o(.text);
        kernel_TEXT_END = .;
        kernel_TEXT_SIZE = ABSOLUTE(kernel_TEXT_END - kernel_TEXT_START);
        kernel_RODATA_START = .;
        build/src/kernel/*.c.o(.rodata);
        kernel_RODATA_END = .;
        kernel_RODATA_SIZE = ABSOLUTE(kernel_RODATA_END - kernel_RODATA_START);
        kernel_DATA_START = .;
        build/assets/kernel.data.bin.o(.data);
        kernel_DATA_END = .;
        kernel_DATA_SIZE = ABSOLUTE(kernel_DATA_END - kernel_DATA_START);
    }
    kernel_bss_VRAM = ADDR(.kernel_bss);
    .kernel_bss (NOLOAD) :
    {
        FILL(0x00000000);
        kernel_BSS_START = .;
        build/src/kernel/*.c.o(.bss);
        kernel_BSS_END = .;
        kernel_BSS_SIZE = ABSOLUTE(kernel_BSS_END - kernel_BSS_START);
    }
    __romPos += SIZEOF(.kernel);
    __romPos = ALIGN(__romPos, 16);
    kernel_ROM_END = __romPos;
    kernel_VRAM_END = .;

    mainuso_data_ROM_START = __romPos;
    mainuso_data_VRAM = ADDR(.mainuso_data);
    .mainuso_data : AT(mainuso_data_ROM_START)
    {
        FILL(0x00000000);
        mainuso_data_DATA_START = .;
        build/assets/mainuso_data.bin.o(.data);
        mainuso_data_DATA_END = .;
        mainuso_data_DATA_SIZE = ABSOLUTE(mainuso_data_DATA_END - mainuso_data_DATA_START);
    }
    __romPos += SIZEOF(.mainuso_data);
    mainuso_data_ROM_END = __romPos;
    mainuso_data_VRAM_END = .;

    rom_fs_ROM_START = __romPos;
    rom_fs_VRAM = ADDR(.rom_fs);
    .rom_fs : AT(rom_fs_ROM_START)
    {
        FILL(0x00000000);
        rom_fs_DATA_START = .;
        build/assets/rom_fs.bin.o(.data);
        rom_fs_DATA_END = .;
        rom_fs_DATA_SIZE = ABSOLUTE(rom_fs_DATA_END - rom_fs_DATA_START);
    }
    __romPos += SIZEOF(.rom_fs);
    rom_fs_ROM_END = __romPos;
    rom_fs_VRAM_END = .;

    bootup_uso_ROM_START = __romPos;
    bootup_uso_VRAM = ADDR(.bootup_uso);
    .bootup_uso : AT(bootup_uso_ROM_START)
    {
        FILL(0x00000000);
        bootup_uso_DATA_START = .;
        build/assets/bootup_uso.bin.o(.data);
        bootup_uso_DATA_END = .;
        bootup_uso_DATA_SIZE = ABSOLUTE(bootup_uso_DATA_END - bootup_uso_DATA_START);
    }
    __romPos += SIZEOF(.bootup_uso);
    bootup_uso_ROM_END = __romPos;
    bootup_uso_VRAM_END = .;

    game_libs_ROM_START = __romPos;
    game_libs_VRAM = ADDR(.game_libs);
    .game_libs : AT(game_libs_ROM_START)
    {
        FILL(0x00000000);
        game_libs_DATA_START = .;
        build/assets/game_libs.bin.o(.data);
        game_libs_DATA_END = .;
        game_libs_DATA_SIZE = ABSOLUTE(game_libs_DATA_END - game_libs_DATA_START);
    }
    __romPos += SIZEOF(.game_libs);
    game_libs_ROM_END = __romPos;
    game_libs_VRAM_END = .;

    game_data_ROM_START = __romPos;
    game_data_VRAM = ADDR(.game_data);
    .game_data : AT(game_data_ROM_START)
    {
        FILL(0x00000000);
        game_data_DATA_START = .;
        build/assets/game_data.bin.o(.data);
        game_data_DATA_END = .;
        game_data_DATA_SIZE = ABSOLUTE(game_data_DATA_END - game_data_DATA_START);
    }
    __romPos += SIZEOF(.game_data);
    game_data_ROM_END = __romPos;
    game_data_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
