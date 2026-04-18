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
        build/src/kernel/kernel_045.c.o(.text);
        build/src/kernel/kernel_042.c.o(.text);
        build/src/kernel/kernel_027.c.o(.text);
        build/src/kernel/kernel_001.c.o(.text);
        build/src/kernel/kernel_002.c.o(.text);
        build/src/kernel/kernel_003.c.o(.text);
        build/src/kernel/kernel_004.c.o(.text);
        build/src/kernel/kernel_050.c.o(.text);
        build/src/kernel/kernel_051.c.o(.text);
        build/src/kernel/kernel_005.c.o(.text);
        build/src/kernel/kernel_006.c.o(.text);
        build/src/kernel/kernel_007.c.o(.text);
        build/src/kernel/kernel_008.c.o(.text);
        build/src/kernel/kernel_009.c.o(.text);
        build/src/kernel/kernel_010.c.o(.text);
        build/src/kernel/kernel_038.c.o(.text);
        build/src/kernel/kernel_011.c.o(.text);
        build/src/kernel/kernel_013.c.o(.text);
        build/src/kernel/kernel_014.c.o(.text);
        build/src/kernel/kernel_015.c.o(.text);
        build/src/kernel/kernel_016.c.o(.text);
        build/src/kernel/kernel_017.c.o(.text);
        build/src/kernel/kernel_018.c.o(.text);
        build/src/kernel/kernel_047.c.o(.text);
        build/src/kernel/kernel_048.c.o(.text);
        build/src/kernel/kernel_049.c.o(.text);
        build/src/kernel/kernel_043.c.o(.text);
        build/src/kernel/kernel_036.c.o(.text);
        build/src/kernel/kernel_032.c.o(.text);
        build/src/kernel/kernel_033.c.o(.text);
        build/src/kernel/kernel_034.c.o(.text);
        build/src/kernel/kernel_029.c.o(.text);
        build/src/kernel/kernel_019.c.o(.text);
        build/src/kernel/kernel_020.c.o(.text);
        build/src/kernel/kernel_040.c.o(.text);
        build/src/kernel/kernel_030.c.o(.text);
        build/src/kernel/kernel_031.c.o(.text);
        build/src/kernel/kernel_021.c.o(.text);
        build/src/kernel/kernel_022.c.o(.text);
        build/src/kernel/kernel_039.c.o(.text);
        build/src/kernel/kernel_041.c.o(.text);
        build/src/kernel/kernel_044.c.o(.text);
        build/src/kernel/kernel_028.c.o(.text);
        build/src/kernel/kernel_035.c.o(.text);
        build/src/kernel/kernel_023.c.o(.text);
        build/src/kernel/kernel_024.c.o(.text);
        build/src/kernel/kernel_046.c.o(.text);
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

    audio_bank_uso_tail_ROM_START = __romPos;
    audio_bank_uso_tail_VRAM = ADDR(.audio_bank_uso_tail);
    .audio_bank_uso_tail : AT(audio_bank_uso_tail_ROM_START)
    {
        FILL(0x00000000);
        audio_bank_uso_tail_DATA_START = .;
        build/assets/audio_bank_uso_tail.bin.o(.data);
        audio_bank_uso_tail_DATA_END = .;
        audio_bank_uso_tail_DATA_SIZE = ABSOLUTE(audio_bank_uso_tail_DATA_END - audio_bank_uso_tail_DATA_START);
    }
    __romPos += SIZEOF(.audio_bank_uso_tail);
    audio_bank_uso_tail_ROM_END = __romPos;
    audio_bank_uso_tail_VRAM_END = .;

    audio_seq_uso_ROM_START = __romPos;
    audio_seq_uso_VRAM = ADDR(.audio_seq_uso);
    .audio_seq_uso : AT(audio_seq_uso_ROM_START)
    {
        FILL(0x00000000);
        audio_seq_uso_DATA_START = .;
        build/assets/audio_seq_uso.bin.o(.data);
        audio_seq_uso_DATA_END = .;
        audio_seq_uso_DATA_SIZE = ABSOLUTE(audio_seq_uso_DATA_END - audio_seq_uso_DATA_START);
    }
    __romPos += SIZEOF(.audio_seq_uso);
    audio_seq_uso_ROM_END = __romPos;
    audio_seq_uso_VRAM_END = .;

    audio_wave_uso_ROM_START = __romPos;
    audio_wave_uso_VRAM = ADDR(.audio_wave_uso);
    .audio_wave_uso : AT(audio_wave_uso_ROM_START)
    {
        FILL(0x00000000);
        audio_wave_uso_DATA_START = .;
        build/assets/audio_wave_uso.bin.o(.data);
        audio_wave_uso_DATA_END = .;
        audio_wave_uso_DATA_SIZE = ABSOLUTE(audio_wave_uso_DATA_END - audio_wave_uso_DATA_START);
    }
    __romPos += SIZEOF(.audio_wave_uso);
    audio_wave_uso_ROM_END = __romPos;
    audio_wave_uso_VRAM_END = .;

    tahoe151_uso_ROM_START = __romPos;
    tahoe151_uso_VRAM = ADDR(.tahoe151_uso);
    .tahoe151_uso : AT(tahoe151_uso_ROM_START)
    {
        FILL(0x00000000);
        tahoe151_uso_DATA_START = .;
        build/assets/tahoe151_uso.bin.o(.data);
        tahoe151_uso_DATA_END = .;
        tahoe151_uso_DATA_SIZE = ABSOLUTE(tahoe151_uso_DATA_END - tahoe151_uso_DATA_START);
    }
    __romPos += SIZEOF(.tahoe151_uso);
    tahoe151_uso_ROM_END = __romPos;
    tahoe151_uso_VRAM_END = .;

    merlot147_uso_ROM_START = __romPos;
    merlot147_uso_VRAM = ADDR(.merlot147_uso);
    .merlot147_uso : AT(merlot147_uso_ROM_START)
    {
        FILL(0x00000000);
        merlot147_uso_DATA_START = .;
        build/assets/merlot147_uso.bin.o(.data);
        merlot147_uso_DATA_END = .;
        merlot147_uso_DATA_SIZE = ABSOLUTE(merlot147_uso_DATA_END - merlot147_uso_DATA_START);
    }
    __romPos += SIZEOF(.merlot147_uso);
    merlot147_uso_ROM_END = __romPos;
    merlot147_uso_VRAM_END = .;

    blin149_uso_ROM_START = __romPos;
    blin149_uso_VRAM = ADDR(.blin149_uso);
    .blin149_uso : AT(blin149_uso_ROM_START)
    {
        FILL(0x00000000);
        blin149_uso_DATA_START = .;
        build/assets/blin149_uso.bin.o(.data);
        blin149_uso_DATA_END = .;
        blin149_uso_DATA_SIZE = ABSOLUTE(blin149_uso_DATA_END - blin149_uso_DATA_START);
    }
    __romPos += SIZEOF(.blin149_uso);
    blin149_uso_ROM_END = __romPos;
    blin149_uso_VRAM_END = .;

    scout156_uso_ROM_START = __romPos;
    scout156_uso_VRAM = ADDR(.scout156_uso);
    .scout156_uso : AT(scout156_uso_ROM_START)
    {
        FILL(0x00000000);
        scout156_uso_DATA_START = .;
        build/assets/scout156_uso.bin.o(.data);
        scout156_uso_DATA_END = .;
        scout156_uso_DATA_SIZE = ABSOLUTE(scout156_uso_DATA_END - scout156_uso_DATA_START);
    }
    __romPos += SIZEOF(.scout156_uso);
    scout156_uso_ROM_END = __romPos;
    scout156_uso_VRAM_END = .;

    tahoe155_uso_ROM_START = __romPos;
    tahoe155_uso_VRAM = ADDR(.tahoe155_uso);
    .tahoe155_uso : AT(tahoe155_uso_ROM_START)
    {
        FILL(0x00000000);
        tahoe155_uso_DATA_START = .;
        build/assets/tahoe155_uso.bin.o(.data);
        tahoe155_uso_DATA_END = .;
        tahoe155_uso_DATA_SIZE = ABSOLUTE(tahoe155_uso_DATA_END - tahoe155_uso_DATA_START);
    }
    __romPos += SIZEOF(.tahoe155_uso);
    tahoe155_uso_ROM_END = __romPos;
    tahoe155_uso_VRAM_END = .;

    scoutltd162_uso_ROM_START = __romPos;
    scoutltd162_uso_VRAM = ADDR(.scoutltd162_uso);
    .scoutltd162_uso : AT(scoutltd162_uso_ROM_START)
    {
        FILL(0x00000000);
        scoutltd162_uso_DATA_START = .;
        build/assets/scoutltd162_uso.bin.o(.data);
        scoutltd162_uso_DATA_END = .;
        scoutltd162_uso_DATA_SIZE = ABSOLUTE(scoutltd162_uso_DATA_END - scoutltd162_uso_DATA_START);
    }
    __romPos += SIZEOF(.scoutltd162_uso);
    scoutltd162_uso_ROM_END = __romPos;
    scoutltd162_uso_VRAM_END = .;

    merlot143_uso_ROM_START = __romPos;
    merlot143_uso_VRAM = ADDR(.merlot143_uso);
    .merlot143_uso : AT(merlot143_uso_ROM_START)
    {
        FILL(0x00000000);
        merlot143_uso_DATA_START = .;
        build/assets/merlot143_uso.bin.o(.data);
        merlot143_uso_DATA_END = .;
        merlot143_uso_DATA_SIZE = ABSOLUTE(merlot143_uso_DATA_END - merlot143_uso_DATA_START);
    }
    __romPos += SIZEOF(.merlot143_uso);
    merlot143_uso_ROM_END = __romPos;
    merlot143_uso_VRAM_END = .;

    blin154_uso_ROM_START = __romPos;
    blin154_uso_VRAM = ADDR(.blin154_uso);
    .blin154_uso : AT(blin154_uso_ROM_START)
    {
        FILL(0x00000000);
        blin154_uso_DATA_START = .;
        build/assets/blin154_uso.bin.o(.data);
        blin154_uso_DATA_END = .;
        blin154_uso_DATA_SIZE = ABSOLUTE(blin154_uso_DATA_END - blin154_uso_DATA_START);
    }
    __romPos += SIZEOF(.blin154_uso);
    blin154_uso_ROM_END = __romPos;
    blin154_uso_VRAM_END = .;

    penguin_uso_ROM_START = __romPos;
    penguin_uso_VRAM = ADDR(.penguin_uso);
    .penguin_uso : AT(penguin_uso_ROM_START)
    {
        FILL(0x00000000);
        penguin_uso_DATA_START = .;
        build/assets/penguin_uso.bin.o(.data);
        penguin_uso_DATA_END = .;
        penguin_uso_DATA_SIZE = ABSOLUTE(penguin_uso_DATA_END - penguin_uso_DATA_START);
    }
    __romPos += SIZEOF(.penguin_uso);
    penguin_uso_ROM_END = __romPos;
    penguin_uso_VRAM_END = .;

    boarder1_uso_ROM_START = __romPos;
    boarder1_uso_VRAM = ADDR(.boarder1_uso);
    .boarder1_uso : AT(boarder1_uso_ROM_START)
    {
        FILL(0x00000000);
        boarder1_uso_DATA_START = .;
        build/assets/boarder1_uso.bin.o(.data);
        boarder1_uso_DATA_END = .;
        boarder1_uso_DATA_SIZE = ABSOLUTE(boarder1_uso_DATA_END - boarder1_uso_DATA_START);
    }
    __romPos += SIZEOF(.boarder1_uso);
    boarder1_uso_ROM_END = __romPos;
    boarder1_uso_VRAM_END = .;

    boarder2_uso_ROM_START = __romPos;
    boarder2_uso_VRAM = ADDR(.boarder2_uso);
    .boarder2_uso : AT(boarder2_uso_ROM_START)
    {
        FILL(0x00000000);
        boarder2_uso_DATA_START = .;
        build/assets/boarder2_uso.bin.o(.data);
        boarder2_uso_DATA_END = .;
        boarder2_uso_DATA_SIZE = ABSOLUTE(boarder2_uso_DATA_END - boarder2_uso_DATA_START);
    }
    __romPos += SIZEOF(.boarder2_uso);
    boarder2_uso_ROM_END = __romPos;
    boarder2_uso_VRAM_END = .;

    boarder3_uso_ROM_START = __romPos;
    boarder3_uso_VRAM = ADDR(.boarder3_uso);
    .boarder3_uso : AT(boarder3_uso_ROM_START)
    {
        FILL(0x00000000);
        boarder3_uso_DATA_START = .;
        build/assets/boarder3_uso.bin.o(.data);
        boarder3_uso_DATA_END = .;
        boarder3_uso_DATA_SIZE = ABSOLUTE(boarder3_uso_DATA_END - boarder3_uso_DATA_START);
    }
    __romPos += SIZEOF(.boarder3_uso);
    boarder3_uso_ROM_END = __romPos;
    boarder3_uso_VRAM_END = .;

    boarder4_uso_ROM_START = __romPos;
    boarder4_uso_VRAM = ADDR(.boarder4_uso);
    .boarder4_uso : AT(boarder4_uso_ROM_START)
    {
        FILL(0x00000000);
        boarder4_uso_DATA_START = .;
        build/assets/boarder4_uso.bin.o(.data);
        boarder4_uso_DATA_END = .;
        boarder4_uso_DATA_SIZE = ABSOLUTE(boarder4_uso_DATA_END - boarder4_uso_DATA_START);
    }
    __romPos += SIZEOF(.boarder4_uso);
    boarder4_uso_ROM_END = __romPos;
    boarder4_uso_VRAM_END = .;

    boarder5_uso_ROM_START = __romPos;
    boarder5_uso_VRAM = ADDR(.boarder5_uso);
    .boarder5_uso : AT(boarder5_uso_ROM_START)
    {
        FILL(0x00000000);
        boarder5_uso_DATA_START = .;
        build/assets/boarder5_uso.bin.o(.data);
        boarder5_uso_DATA_END = .;
        boarder5_uso_DATA_SIZE = ABSOLUTE(boarder5_uso_DATA_END - boarder5_uso_DATA_START);
    }
    __romPos += SIZEOF(.boarder5_uso);
    boarder5_uso_ROM_END = __romPos;
    boarder5_uso_VRAM_END = .;

    gui_uso_ROM_START = __romPos;
    gui_uso_VRAM = ADDR(.gui_uso);
    .gui_uso : AT(gui_uso_ROM_START)
    {
        FILL(0x00000000);
        gui_uso_DATA_START = .;
        build/assets/gui_uso.bin.o(.data);
        gui_uso_DATA_END = .;
        gui_uso_DATA_SIZE = ABSOLUTE(gui_uso_DATA_END - gui_uso_DATA_START);
    }
    __romPos += SIZEOF(.gui_uso);
    gui_uso_ROM_END = __romPos;
    gui_uso_VRAM_END = .;

    n64proc_uso_ROM_START = __romPos;
    n64proc_uso_VRAM = ADDR(.n64proc_uso);
    .n64proc_uso : AT(n64proc_uso_ROM_START)
    {
        FILL(0x00000000);
        n64proc_uso_DATA_START = .;
        build/assets/n64proc_uso.bin.o(.data);
        n64proc_uso_DATA_END = .;
        n64proc_uso_DATA_SIZE = ABSOLUTE(n64proc_uso_DATA_END - n64proc_uso_DATA_START);
    }
    __romPos += SIZEOF(.n64proc_uso);
    n64proc_uso_ROM_END = __romPos;
    n64proc_uso_VRAM_END = .;

    titproc_uso_ROM_START = __romPos;
    titproc_uso_VRAM = ADDR(.titproc_uso);
    .titproc_uso : AT(titproc_uso_ROM_START)
    {
        FILL(0x00000000);
        titproc_uso_DATA_START = .;
        build/assets/titproc_uso.bin.o(.data);
        titproc_uso_DATA_END = .;
        titproc_uso_DATA_SIZE = ABSOLUTE(titproc_uso_DATA_END - titproc_uso_DATA_START);
    }
    __romPos += SIZEOF(.titproc_uso);
    titproc_uso_ROM_END = __romPos;
    titproc_uso_VRAM_END = .;

    eddproc_uso_ROM_START = __romPos;
    eddproc_uso_VRAM = ADDR(.eddproc_uso);
    .eddproc_uso : AT(eddproc_uso_ROM_START)
    {
        FILL(0x00000000);
        eddproc_uso_DATA_START = .;
        build/assets/eddproc_uso.bin.o(.data);
        eddproc_uso_DATA_END = .;
        eddproc_uso_DATA_SIZE = ABSOLUTE(eddproc_uso_DATA_END - eddproc_uso_DATA_START);
    }
    __romPos += SIZEOF(.eddproc_uso);
    eddproc_uso_ROM_END = __romPos;
    eddproc_uso_VRAM_END = .;

    mgrproc_uso_ROM_START = __romPos;
    mgrproc_uso_VRAM = ADDR(.mgrproc_uso);
    .mgrproc_uso : AT(mgrproc_uso_ROM_START)
    {
        FILL(0x00000000);
        mgrproc_uso_DATA_START = .;
        build/assets/mgrproc_uso.bin.o(.data);
        mgrproc_uso_DATA_END = .;
        mgrproc_uso_DATA_SIZE = ABSOLUTE(mgrproc_uso_DATA_END - mgrproc_uso_DATA_START);
    }
    __romPos += SIZEOF(.mgrproc_uso);
    mgrproc_uso_ROM_END = __romPos;
    mgrproc_uso_VRAM_END = .;

    arcproc_uso_ROM_START = __romPos;
    arcproc_uso_VRAM = ADDR(.arcproc_uso);
    .arcproc_uso : AT(arcproc_uso_ROM_START)
    {
        FILL(0x00000000);
        arcproc_uso_DATA_START = .;
        build/assets/arcproc_uso.bin.o(.data);
        arcproc_uso_DATA_END = .;
        arcproc_uso_DATA_SIZE = ABSOLUTE(arcproc_uso_DATA_END - arcproc_uso_DATA_START);
    }
    __romPos += SIZEOF(.arcproc_uso);
    arcproc_uso_ROM_END = __romPos;
    arcproc_uso_VRAM_END = .;

    h2hproc_uso_ROM_START = __romPos;
    h2hproc_uso_VRAM = ADDR(.h2hproc_uso);
    .h2hproc_uso : AT(h2hproc_uso_ROM_START)
    {
        FILL(0x00000000);
        h2hproc_uso_DATA_START = .;
        build/assets/h2hproc_uso.bin.o(.data);
        h2hproc_uso_DATA_END = .;
        h2hproc_uso_DATA_SIZE = ABSOLUTE(h2hproc_uso_DATA_END - h2hproc_uso_DATA_START);
    }
    __romPos += SIZEOF(.h2hproc_uso);
    h2hproc_uso_ROM_END = __romPos;
    h2hproc_uso_VRAM_END = .;

    timproc_uso_ROM_START = __romPos;
    timproc_uso_VRAM = ADDR(.timproc_uso);
    .timproc_uso : AT(timproc_uso_ROM_START)
    {
        FILL(0x00000000);
        timproc_uso_DATA_START = .;
        build/assets/timproc_uso.bin.o(.data);
        timproc_uso_DATA_END = .;
        timproc_uso_DATA_SIZE = ABSOLUTE(timproc_uso_DATA_END - timproc_uso_DATA_START);
    }
    __romPos += SIZEOF(.timproc_uso);
    timproc_uso_ROM_END = __romPos;
    timproc_uso_VRAM_END = .;

    map4_data_uso_ROM_START = __romPos;
    map4_data_uso_VRAM = ADDR(.map4_data_uso);
    .map4_data_uso : AT(map4_data_uso_ROM_START)
    {
        FILL(0x00000000);
        map4_data_uso_DATA_START = .;
        build/assets/map4_data_uso.bin.o(.data);
        map4_data_uso_DATA_END = .;
        map4_data_uso_DATA_SIZE = ABSOLUTE(map4_data_uso_DATA_END - map4_data_uso_DATA_START);
    }
    __romPos += SIZEOF(.map4_data_uso);
    map4_data_uso_ROM_END = __romPos;
    map4_data_uso_VRAM_END = .;

    game_uso_ROM_START = __romPos;
    game_uso_VRAM = ADDR(.game_uso);
    .game_uso : AT(game_uso_ROM_START)
    {
        FILL(0x00000000);
        game_uso_DATA_START = .;
        build/assets/game_uso.bin.o(.data);
        game_uso_DATA_END = .;
        game_uso_DATA_SIZE = ABSOLUTE(game_uso_DATA_END - game_uso_DATA_START);
    }
    __romPos += SIZEOF(.game_uso);
    game_uso_ROM_END = __romPos;
    game_uso_VRAM_END = .;

    bg3tex_uso_ROM_START = __romPos;
    bg3tex_uso_VRAM = ADDR(.bg3tex_uso);
    .bg3tex_uso : AT(bg3tex_uso_ROM_START)
    {
        FILL(0x00000000);
        bg3tex_uso_DATA_START = .;
        build/assets/bg3tex_uso.bin.o(.data);
        bg3tex_uso_DATA_END = .;
        bg3tex_uso_DATA_SIZE = ABSOLUTE(bg3tex_uso_DATA_END - bg3tex_uso_DATA_START);
    }
    __romPos += SIZEOF(.bg3tex_uso);
    bg3tex_uso_ROM_END = __romPos;
    bg3tex_uso_VRAM_END = .;

    bg6tex_uso_ROM_START = __romPos;
    bg6tex_uso_VRAM = ADDR(.bg6tex_uso);
    .bg6tex_uso : AT(bg6tex_uso_ROM_START)
    {
        FILL(0x00000000);
        bg6tex_uso_DATA_START = .;
        build/assets/bg6tex_uso.bin.o(.data);
        bg6tex_uso_DATA_END = .;
        bg6tex_uso_DATA_SIZE = ABSOLUTE(bg6tex_uso_DATA_END - bg6tex_uso_DATA_START);
    }
    __romPos += SIZEOF(.bg6tex_uso);
    bg6tex_uso_ROM_END = __romPos;
    bg6tex_uso_VRAM_END = .;

    bg7tex_uso_ROM_START = __romPos;
    bg7tex_uso_VRAM = ADDR(.bg7tex_uso);
    .bg7tex_uso : AT(bg7tex_uso_ROM_START)
    {
        FILL(0x00000000);
        bg7tex_uso_DATA_START = .;
        build/assets/bg7tex_uso.bin.o(.data);
        bg7tex_uso_DATA_END = .;
        bg7tex_uso_DATA_SIZE = ABSOLUTE(bg7tex_uso_DATA_END - bg7tex_uso_DATA_START);
    }
    __romPos += SIZEOF(.bg7tex_uso);
    bg7tex_uso_ROM_END = __romPos;
    bg7tex_uso_VRAM_END = .;

    bg8tex_uso_ROM_START = __romPos;
    bg8tex_uso_VRAM = ADDR(.bg8tex_uso);
    .bg8tex_uso : AT(bg8tex_uso_ROM_START)
    {
        FILL(0x00000000);
        bg8tex_uso_DATA_START = .;
        build/assets/bg8tex_uso.bin.o(.data);
        bg8tex_uso_DATA_END = .;
        bg8tex_uso_DATA_SIZE = ABSOLUTE(bg8tex_uso_DATA_END - bg8tex_uso_DATA_START);
    }
    __romPos += SIZEOF(.bg8tex_uso);
    bg8tex_uso_ROM_END = __romPos;
    bg8tex_uso_VRAM_END = .;

    player_data_ROM_START = __romPos;
    player_data_VRAM = ADDR(.player_data);
    .player_data : AT(player_data_ROM_START)
    {
        FILL(0x00000000);
        player_data_DATA_START = .;
        build/assets/player_data.bin.o(.data);
        player_data_DATA_END = .;
        player_data_DATA_SIZE = ABSOLUTE(player_data_DATA_END - player_data_DATA_START);
    }
    __romPos += SIZEOF(.player_data);
    player_data_ROM_END = __romPos;
    player_data_VRAM_END = .;

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
