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
        build/src/kernel/kernel_052.c.o(.text);
        build/src/kernel/kernel_053.c.o(.text);
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
        build/src/kernel/kernel_031b.c.o(.text);
        build/src/kernel/kernel_021.c.o(.text);
        build/src/kernel/kernel_022.c.o(.text);
        build/src/kernel/kernel_054.c.o(.text);
        build/src/kernel/kernel_055.c.o(.text);
        build/src/kernel/kernel_056.c.o(.text);
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

    boarder1_uso_pre_ROM_START = __romPos;
    boarder1_uso_pre_VRAM = ADDR(.boarder1_uso_pre);
    .boarder1_uso_pre : AT(boarder1_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        boarder1_uso_pre_DATA_START = .;
        build/assets/boarder1_uso_pre.bin.o(.data);
        boarder1_uso_pre_DATA_END = .;
        boarder1_uso_pre_DATA_SIZE = ABSOLUTE(boarder1_uso_pre_DATA_END - boarder1_uso_pre_DATA_START);
    }
    __romPos += SIZEOF(.boarder1_uso_pre);
    boarder1_uso_pre_ROM_END = __romPos;
    boarder1_uso_pre_VRAM_END = .;

    boarder1_uso_ROM_START = __romPos;
    .boarder1_uso 0x00000000 : AT(boarder1_uso_ROM_START)
    {
        FILL(0x00000000);
        boarder1_uso_TEXT_START = .;
        build/src/boarder1_uso/boarder1_uso.c.o(.text);
        boarder1_uso_TEXT_END = .;
        boarder1_uso_TEXT_SIZE = ABSOLUTE(boarder1_uso_TEXT_END - boarder1_uso_TEXT_START);
    }
    __romPos += SIZEOF(.boarder1_uso);
    boarder1_uso_ROM_END = __romPos;
    boarder1_uso_VRAM = ADDR(.boarder1_uso);
    boarder1_uso_VRAM_END = .;

    boarder1_uso_post_ROM_START = __romPos;
    boarder1_uso_post_VRAM = ADDR(.boarder1_uso_post);
    .boarder1_uso_post : AT(boarder1_uso_post_ROM_START)
    {
        FILL(0x00000000);
        boarder1_uso_post_DATA_START = .;
        build/assets/boarder1_uso_post.bin.o(.data);
        boarder1_uso_post_DATA_END = .;
        boarder1_uso_post_DATA_SIZE = ABSOLUTE(boarder1_uso_post_DATA_END - boarder1_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.boarder1_uso_post);
    boarder1_uso_post_ROM_END = __romPos;
    boarder1_uso_post_VRAM_END = .;

    boarder2_uso_pre_ROM_START = __romPos;
    boarder2_uso_pre_VRAM = ADDR(.boarder2_uso_pre);
    .boarder2_uso_pre : AT(boarder2_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        boarder2_uso_pre_DATA_START = .;
        build/assets/boarder2_uso_pre.bin.o(.data);
        boarder2_uso_pre_DATA_END = .;
        boarder2_uso_pre_DATA_SIZE = ABSOLUTE(boarder2_uso_pre_DATA_END - boarder2_uso_pre_DATA_START);
    }
    __romPos += SIZEOF(.boarder2_uso_pre);
    boarder2_uso_pre_ROM_END = __romPos;
    boarder2_uso_pre_VRAM_END = .;

    boarder2_uso_ROM_START = __romPos;
    .boarder2_uso 0x00000000 : AT(boarder2_uso_ROM_START)
    {
        FILL(0x00000000);
        boarder2_uso_TEXT_START = .;
        build/src/boarder2_uso/boarder2_uso.c.o(.text);
        boarder2_uso_TEXT_END = .;
        boarder2_uso_TEXT_SIZE = ABSOLUTE(boarder2_uso_TEXT_END - boarder2_uso_TEXT_START);
    }
    __romPos += SIZEOF(.boarder2_uso);
    boarder2_uso_ROM_END = __romPos;
    boarder2_uso_VRAM = ADDR(.boarder2_uso);
    boarder2_uso_VRAM_END = .;

    boarder2_uso_post_ROM_START = __romPos;
    boarder2_uso_post_VRAM = ADDR(.boarder2_uso_post);
    .boarder2_uso_post : AT(boarder2_uso_post_ROM_START)
    {
        FILL(0x00000000);
        boarder2_uso_post_DATA_START = .;
        build/assets/boarder2_uso_post.bin.o(.data);
        boarder2_uso_post_DATA_END = .;
        boarder2_uso_post_DATA_SIZE = ABSOLUTE(boarder2_uso_post_DATA_END - boarder2_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.boarder2_uso_post);
    boarder2_uso_post_ROM_END = __romPos;
    boarder2_uso_post_VRAM_END = .;

    boarder3_uso_pre_ROM_START = __romPos;
    boarder3_uso_pre_VRAM = ADDR(.boarder3_uso_pre);
    .boarder3_uso_pre : AT(boarder3_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        boarder3_uso_pre_DATA_START = .;
        build/assets/boarder3_uso_pre.bin.o(.data);
        boarder3_uso_pre_DATA_END = .;
        boarder3_uso_pre_DATA_SIZE = ABSOLUTE(boarder3_uso_pre_DATA_END - boarder3_uso_pre_DATA_START);
    }
    __romPos += SIZEOF(.boarder3_uso_pre);
    boarder3_uso_pre_ROM_END = __romPos;
    boarder3_uso_pre_VRAM_END = .;

    boarder3_uso_ROM_START = __romPos;
    .boarder3_uso 0x00000000 : AT(boarder3_uso_ROM_START)
    {
        FILL(0x00000000);
        boarder3_uso_TEXT_START = .;
        build/src/boarder3_uso/boarder3_uso.c.o(.text);
        boarder3_uso_TEXT_END = .;
        boarder3_uso_TEXT_SIZE = ABSOLUTE(boarder3_uso_TEXT_END - boarder3_uso_TEXT_START);
    }
    __romPos += SIZEOF(.boarder3_uso);
    boarder3_uso_ROM_END = __romPos;
    boarder3_uso_VRAM = ADDR(.boarder3_uso);
    boarder3_uso_VRAM_END = .;

    boarder3_uso_post_ROM_START = __romPos;
    boarder3_uso_post_VRAM = ADDR(.boarder3_uso_post);
    .boarder3_uso_post : AT(boarder3_uso_post_ROM_START)
    {
        FILL(0x00000000);
        boarder3_uso_post_DATA_START = .;
        build/assets/boarder3_uso_post.bin.o(.data);
        boarder3_uso_post_DATA_END = .;
        boarder3_uso_post_DATA_SIZE = ABSOLUTE(boarder3_uso_post_DATA_END - boarder3_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.boarder3_uso_post);
    boarder3_uso_post_ROM_END = __romPos;
    boarder3_uso_post_VRAM_END = .;

    boarder4_uso_pre_ROM_START = __romPos;
    boarder4_uso_pre_VRAM = ADDR(.boarder4_uso_pre);
    .boarder4_uso_pre : AT(boarder4_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        boarder4_uso_pre_DATA_START = .;
        build/assets/boarder4_uso_pre.bin.o(.data);
        boarder4_uso_pre_DATA_END = .;
        boarder4_uso_pre_DATA_SIZE = ABSOLUTE(boarder4_uso_pre_DATA_END - boarder4_uso_pre_DATA_START);
    }
    __romPos += SIZEOF(.boarder4_uso_pre);
    boarder4_uso_pre_ROM_END = __romPos;
    boarder4_uso_pre_VRAM_END = .;

    boarder4_uso_ROM_START = __romPos;
    .boarder4_uso 0x00000000 : AT(boarder4_uso_ROM_START)
    {
        FILL(0x00000000);
        boarder4_uso_TEXT_START = .;
        build/src/boarder4_uso/boarder4_uso.c.o(.text);
        boarder4_uso_TEXT_END = .;
        boarder4_uso_TEXT_SIZE = ABSOLUTE(boarder4_uso_TEXT_END - boarder4_uso_TEXT_START);
    }
    __romPos += SIZEOF(.boarder4_uso);
    boarder4_uso_ROM_END = __romPos;
    boarder4_uso_VRAM = ADDR(.boarder4_uso);
    boarder4_uso_VRAM_END = .;

    boarder4_uso_post_ROM_START = __romPos;
    boarder4_uso_post_VRAM = ADDR(.boarder4_uso_post);
    .boarder4_uso_post : AT(boarder4_uso_post_ROM_START)
    {
        FILL(0x00000000);
        boarder4_uso_post_DATA_START = .;
        build/assets/boarder4_uso_post.bin.o(.data);
        boarder4_uso_post_DATA_END = .;
        boarder4_uso_post_DATA_SIZE = ABSOLUTE(boarder4_uso_post_DATA_END - boarder4_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.boarder4_uso_post);
    boarder4_uso_post_ROM_END = __romPos;
    boarder4_uso_post_VRAM_END = .;

    boarder5_uso_pre_ROM_START = __romPos;
    boarder5_uso_pre_VRAM = ADDR(.boarder5_uso_pre);
    .boarder5_uso_pre : AT(boarder5_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        boarder5_uso_pre_DATA_START = .;
        build/assets/boarder5_uso_pre.bin.o(.data);
        boarder5_uso_pre_DATA_END = .;
        boarder5_uso_pre_DATA_SIZE = ABSOLUTE(boarder5_uso_pre_DATA_END - boarder5_uso_pre_DATA_START);
    }
    __romPos += SIZEOF(.boarder5_uso_pre);
    boarder5_uso_pre_ROM_END = __romPos;
    boarder5_uso_pre_VRAM_END = .;

    boarder5_uso_ROM_START = __romPos;
    .boarder5_uso 0x00000000 : AT(boarder5_uso_ROM_START)
    {
        FILL(0x00000000);
        boarder5_uso_TEXT_START = .;
        build/src/boarder5_uso/boarder5_uso.c.o(.text);
        boarder5_uso_TEXT_END = .;
        boarder5_uso_TEXT_SIZE = ABSOLUTE(boarder5_uso_TEXT_END - boarder5_uso_TEXT_START);
    }
    __romPos += SIZEOF(.boarder5_uso);
    boarder5_uso_ROM_END = __romPos;
    boarder5_uso_VRAM = ADDR(.boarder5_uso);
    boarder5_uso_VRAM_END = .;

    boarder5_uso_post_ROM_START = __romPos;
    boarder5_uso_post_VRAM = ADDR(.boarder5_uso_post);
    .boarder5_uso_post : AT(boarder5_uso_post_ROM_START)
    {
        FILL(0x00000000);
        boarder5_uso_post_DATA_START = .;
        build/assets/boarder5_uso_post.bin.o(.data);
        boarder5_uso_post_DATA_END = .;
        boarder5_uso_post_DATA_SIZE = ABSOLUTE(boarder5_uso_post_DATA_END - boarder5_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.boarder5_uso_post);
    boarder5_uso_post_ROM_END = __romPos;
    boarder5_uso_post_VRAM_END = .;

    gui_uso_pre_ROM_START = __romPos;
    gui_uso_pre_VRAM = ADDR(.gui_uso_pre);
    .gui_uso_pre : AT(gui_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        gui_uso_pre_DATA_START = .;
        build/assets/gui_uso_pre.bin.o(.data);
        gui_uso_pre_DATA_END = .;
        gui_uso_pre_DATA_SIZE = ABSOLUTE(gui_uso_pre_DATA_END - gui_uso_pre_DATA_START);
    }
    __romPos += SIZEOF(.gui_uso_pre);
    gui_uso_pre_ROM_END = __romPos;
    gui_uso_pre_VRAM_END = .;

    /* gui_uso text: same VRAM=0 pattern as bootup_uso. Asm files are raw
     * .word directives generated by scripts/generate-uso-asm.py — splat's
     * disassembled mnemonics introduce phantom branch labels that don't
     * resolve for USO-relocatable code. */
    gui_uso_ROM_START = __romPos;
    .gui_uso 0x00000000 : AT(gui_uso_ROM_START)
    {
        FILL(0x00000000);
        gui_uso_TEXT_START = .;
        build/src/gui_uso/gui_uso.c.o(.text);
        gui_uso_TEXT_END = .;
        gui_uso_TEXT_SIZE = ABSOLUTE(gui_uso_TEXT_END - gui_uso_TEXT_START);
    }
    __romPos += SIZEOF(.gui_uso);
    gui_uso_ROM_END = __romPos;
    gui_uso_VRAM = ADDR(.gui_uso);
    gui_uso_VRAM_END = .;

    gui_uso_post_ROM_START = __romPos;
    gui_uso_post_VRAM = ADDR(.gui_uso_post);
    .gui_uso_post : AT(gui_uso_post_ROM_START)
    {
        FILL(0x00000000);
        gui_uso_post_DATA_START = .;
        build/assets/gui_uso_post.bin.o(.data);
        gui_uso_post_DATA_END = .;
        gui_uso_post_DATA_SIZE = ABSOLUTE(gui_uso_post_DATA_END - gui_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.gui_uso_post);
    gui_uso_post_ROM_END = __romPos;
    gui_uso_post_VRAM_END = .;

    n64proc_uso_pre_ROM_START = __romPos;
    n64proc_uso_pre_VRAM = ADDR(.n64proc_uso_pre);
    .n64proc_uso_pre : AT(n64proc_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        n64proc_uso_pre_DATA_START = .;
        build/assets/n64proc_uso_pre.bin.o(.data);
        n64proc_uso_pre_DATA_END = .;
        n64proc_uso_pre_DATA_SIZE = ABSOLUTE(n64proc_uso_pre_DATA_END - n64proc_uso_pre_DATA_START);
    }
    __romPos += SIZEOF(.n64proc_uso_pre);
    n64proc_uso_pre_ROM_END = __romPos;
    n64proc_uso_pre_VRAM_END = .;

    /* n64proc_uso text: same VRAM=0 pattern. Asm via scripts/generate-uso-asm.py. */
    n64proc_uso_ROM_START = __romPos;
    .n64proc_uso 0x00000000 : AT(n64proc_uso_ROM_START)
    {
        FILL(0x00000000);
        n64proc_uso_TEXT_START = .;
        build/src/n64proc_uso/n64proc_uso.c.o(.text);
        n64proc_uso_TEXT_END = .;
        n64proc_uso_TEXT_SIZE = ABSOLUTE(n64proc_uso_TEXT_END - n64proc_uso_TEXT_START);
    }
    __romPos += SIZEOF(.n64proc_uso);
    n64proc_uso_ROM_END = __romPos;
    n64proc_uso_VRAM = ADDR(.n64proc_uso);
    n64proc_uso_VRAM_END = .;

    n64proc_uso_post_ROM_START = __romPos;
    n64proc_uso_post_VRAM = ADDR(.n64proc_uso_post);
    .n64proc_uso_post : AT(n64proc_uso_post_ROM_START)
    {
        FILL(0x00000000);
        n64proc_uso_post_DATA_START = .;
        build/assets/n64proc_uso_post.bin.o(.data);
        n64proc_uso_post_DATA_END = .;
        n64proc_uso_post_DATA_SIZE = ABSOLUTE(n64proc_uso_post_DATA_END - n64proc_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.n64proc_uso_post);
    n64proc_uso_post_ROM_END = __romPos;
    n64proc_uso_post_VRAM_END = .;

    titproc_uso_pre_ROM_START = __romPos;
    titproc_uso_pre_VRAM = ADDR(.titproc_uso_pre);
    .titproc_uso_pre : AT(titproc_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        titproc_uso_pre_DATA_START = .;
        build/assets/titproc_uso_pre.bin.o(.data);
        titproc_uso_pre_DATA_END = .;
        titproc_uso_pre_DATA_SIZE = ABSOLUTE(titproc_uso_pre_DATA_END - titproc_uso_pre_DATA_START);
    }
    __romPos += SIZEOF(.titproc_uso_pre);
    titproc_uso_pre_ROM_END = __romPos;
    titproc_uso_pre_VRAM_END = .;

    titproc_uso_ROM_START = __romPos;
    .titproc_uso 0x00000000 : AT(titproc_uso_ROM_START)
    {
        FILL(0x00000000);
        titproc_uso_TEXT_START = .;
        build/src/titproc_uso/titproc_uso.c.o(.text);
        titproc_uso_TEXT_END = .;
        titproc_uso_TEXT_SIZE = ABSOLUTE(titproc_uso_TEXT_END - titproc_uso_TEXT_START);
    }
    __romPos += SIZEOF(.titproc_uso);
    titproc_uso_ROM_END = __romPos;
    titproc_uso_VRAM = ADDR(.titproc_uso);
    titproc_uso_VRAM_END = .;

    titproc_uso_post_ROM_START = __romPos;
    titproc_uso_post_VRAM = ADDR(.titproc_uso_post);
    .titproc_uso_post : AT(titproc_uso_post_ROM_START)
    {
        FILL(0x00000000);
        titproc_uso_post_DATA_START = .;
        build/assets/titproc_uso_post.bin.o(.data);
        titproc_uso_post_DATA_END = .;
        titproc_uso_post_DATA_SIZE = ABSOLUTE(titproc_uso_post_DATA_END - titproc_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.titproc_uso_post);
    titproc_uso_post_ROM_END = __romPos;
    titproc_uso_post_VRAM_END = .;

    eddproc_uso_pre_ROM_START = __romPos;
    eddproc_uso_pre_VRAM = ADDR(.eddproc_uso_pre);
    .eddproc_uso_pre : AT(eddproc_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        eddproc_uso_pre_DATA_START = .;
        build/assets/eddproc_uso_pre.bin.o(.data);
        eddproc_uso_pre_DATA_END = .;
        eddproc_uso_pre_DATA_SIZE = ABSOLUTE(eddproc_uso_pre_DATA_END - eddproc_uso_pre_DATA_START);
    }
    __romPos += SIZEOF(.eddproc_uso_pre);
    eddproc_uso_pre_ROM_END = __romPos;
    eddproc_uso_pre_VRAM_END = .;

    /* eddproc_uso text: same VRAM=0 pattern. Asm via scripts/generate-uso-asm.py. */
    eddproc_uso_ROM_START = __romPos;
    .eddproc_uso 0x00000000 : AT(eddproc_uso_ROM_START)
    {
        FILL(0x00000000);
        eddproc_uso_TEXT_START = .;
        build/src/eddproc_uso/eddproc_uso.c.o(.text);
        eddproc_uso_TEXT_END = .;
        eddproc_uso_TEXT_SIZE = ABSOLUTE(eddproc_uso_TEXT_END - eddproc_uso_TEXT_START);
    }
    __romPos += SIZEOF(.eddproc_uso);
    eddproc_uso_ROM_END = __romPos;
    eddproc_uso_VRAM = ADDR(.eddproc_uso);
    eddproc_uso_VRAM_END = .;

    eddproc_uso_post_ROM_START = __romPos;
    eddproc_uso_post_VRAM = ADDR(.eddproc_uso_post);
    .eddproc_uso_post : AT(eddproc_uso_post_ROM_START)
    {
        FILL(0x00000000);
        eddproc_uso_post_DATA_START = .;
        build/assets/eddproc_uso_post.bin.o(.data);
        eddproc_uso_post_DATA_END = .;
        eddproc_uso_post_DATA_SIZE = ABSOLUTE(eddproc_uso_post_DATA_END - eddproc_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.eddproc_uso_post);
    eddproc_uso_post_ROM_END = __romPos;
    eddproc_uso_post_VRAM_END = .;

    /* mgrproc_uso: 5 slices, see tenshoe.yaml comment. block1 is the text
     * Yay0 block — for now passthrough; later swap with `crunch64`-compressed
     * output of build/src/mgrproc_uso/mgrproc_uso.c.o. */
    mgrproc_uso_pre_ROM_START = __romPos;
    .mgrproc_uso_pre : AT(mgrproc_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        build/assets/mgrproc_uso_pre.bin.o(.data);
    }
    __romPos += SIZEOF(.mgrproc_uso_pre);

    .mgrproc_uso_block0_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/mgrproc_uso_block0_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.mgrproc_uso_block0_yay0);

    .mgrproc_uso_inter : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/mgrproc_uso_inter.bin.o(.data);
    }
    __romPos += SIZEOF(.mgrproc_uso_inter);

    .mgrproc_uso_block1_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/mgrproc_uso_block1_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.mgrproc_uso_block1_yay0);

    .mgrproc_uso_post : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/mgrproc_uso_post.bin.o(.data);
    }
    __romPos += SIZEOF(.mgrproc_uso_post);
    mgrproc_uso_ROM_END = __romPos;
    mgrproc_uso_VRAM_END = .;

    arcproc_uso_pre_ROM_START = __romPos;
    arcproc_uso_pre_VRAM = ADDR(.arcproc_uso_pre);
    .arcproc_uso_pre : AT(arcproc_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        arcproc_uso_pre_DATA_START = .;
        build/assets/arcproc_uso_pre.bin.o(.data);
        arcproc_uso_pre_DATA_END = .;
        arcproc_uso_pre_DATA_SIZE = ABSOLUTE(arcproc_uso_pre_DATA_END - arcproc_uso_pre_DATA_START);
    }
    __romPos += SIZEOF(.arcproc_uso_pre);
    arcproc_uso_pre_ROM_END = __romPos;
    arcproc_uso_pre_VRAM_END = .;

    /* arcproc_uso text: same VRAM=0 pattern. Asm via scripts/generate-uso-asm.py. */
    arcproc_uso_ROM_START = __romPos;
    .arcproc_uso 0x00000000 : AT(arcproc_uso_ROM_START)
    {
        FILL(0x00000000);
        arcproc_uso_TEXT_START = .;
        build/src/arcproc_uso/arcproc_uso.c.o(.text);
        build/src/arcproc_uso/arcproc_uso_o0_50.c.o(.text);
        build/src/arcproc_uso/arcproc_uso_o0_12C.c.o(.text);
        build/src/arcproc_uso/arcproc_uso_tail1.c.o(.text);
        arcproc_uso_TEXT_END = .;
        arcproc_uso_TEXT_SIZE = ABSOLUTE(arcproc_uso_TEXT_END - arcproc_uso_TEXT_START);
    }
    __romPos += SIZEOF(.arcproc_uso);
    arcproc_uso_ROM_END = __romPos;
    arcproc_uso_VRAM = ADDR(.arcproc_uso);
    arcproc_uso_VRAM_END = .;

    arcproc_uso_post_ROM_START = __romPos;
    arcproc_uso_post_VRAM = ADDR(.arcproc_uso_post);
    .arcproc_uso_post : AT(arcproc_uso_post_ROM_START)
    {
        FILL(0x00000000);
        arcproc_uso_post_DATA_START = .;
        build/assets/arcproc_uso_post.bin.o(.data);
        arcproc_uso_post_DATA_END = .;
        arcproc_uso_post_DATA_SIZE = ABSOLUTE(arcproc_uso_post_DATA_END - arcproc_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.arcproc_uso_post);
    arcproc_uso_post_ROM_END = __romPos;
    arcproc_uso_post_VRAM_END = .;

    h2hproc_uso_pre_ROM_START = __romPos;
    h2hproc_uso_pre_VRAM = ADDR(.h2hproc_uso_pre);
    .h2hproc_uso_pre : AT(h2hproc_uso_pre_ROM_START)
    {
        FILL(0x00000000);
        h2hproc_uso_pre_DATA_START = .;
        build/assets/h2hproc_uso_pre.bin.o(.data);
        h2hproc_uso_pre_DATA_END = .;
        h2hproc_uso_pre_DATA_SIZE = ABSOLUTE(h2hproc_uso_pre_DATA_END - h2hproc_uso_pre_DATA_START);
    }
    __romPos += SIZEOF(.h2hproc_uso_pre);
    h2hproc_uso_pre_ROM_END = __romPos;
    h2hproc_uso_pre_VRAM_END = .;

    /* h2hproc_uso text: same VRAM=0 pattern. Asm via scripts/generate-uso-asm.py. */
    h2hproc_uso_ROM_START = __romPos;
    .h2hproc_uso 0x00000000 : AT(h2hproc_uso_ROM_START)
    {
        FILL(0x00000000);
        h2hproc_uso_TEXT_START = .;
        build/src/h2hproc_uso/h2hproc_uso.c.o(.text);
        h2hproc_uso_TEXT_END = .;
        h2hproc_uso_TEXT_SIZE = ABSOLUTE(h2hproc_uso_TEXT_END - h2hproc_uso_TEXT_START);
    }
    __romPos += SIZEOF(.h2hproc_uso);
    h2hproc_uso_ROM_END = __romPos;
    h2hproc_uso_VRAM = ADDR(.h2hproc_uso);
    h2hproc_uso_VRAM_END = .;

    h2hproc_uso_post_ROM_START = __romPos;
    h2hproc_uso_post_VRAM = ADDR(.h2hproc_uso_post);
    .h2hproc_uso_post : AT(h2hproc_uso_post_ROM_START)
    {
        FILL(0x00000000);
        h2hproc_uso_post_DATA_START = .;
        build/assets/h2hproc_uso_post.bin.o(.data);
        h2hproc_uso_post_DATA_END = .;
        h2hproc_uso_post_DATA_SIZE = ABSOLUTE(h2hproc_uso_post_DATA_END - h2hproc_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.h2hproc_uso_post);
    h2hproc_uso_post_ROM_END = __romPos;
    h2hproc_uso_post_VRAM_END = .;

    /* timproc_uso: 9 Yay0 blocks + interspersed bins. Code blocks: 1, 3, 5. */
    timproc_uso_ROM_START = __romPos;
    .timproc_uso_pre : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_pre.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_pre);

    .timproc_uso_block0_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_block0_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_block0_yay0);

    .timproc_uso_inter01 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_inter01.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_inter01);

    .timproc_uso_block1_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_block1_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_block1_yay0);

    .timproc_uso_inter12 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_inter12.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_inter12);

    .timproc_uso_block2_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_block2_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_block2_yay0);

    .timproc_uso_inter23 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_inter23.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_inter23);

    .timproc_uso_block3_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_block3_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_block3_yay0);

    .timproc_uso_inter34 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_inter34.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_inter34);

    .timproc_uso_block4_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_block4_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_block4_yay0);

    .timproc_uso_inter45 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_inter45.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_inter45);

    .timproc_uso_block5_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_block5_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_block5_yay0);

    .timproc_uso_inter56 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_inter56.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_inter56);

    .timproc_uso_block6_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_block6_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_block6_yay0);

    .timproc_uso_inter67 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_inter67.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_inter67);

    .timproc_uso_block7_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_block7_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_block7_yay0);

    .timproc_uso_inter78 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_inter78.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_inter78);

    .timproc_uso_block8_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_block8_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_block8_yay0);

    .timproc_uso_post : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/timproc_uso_post.bin.o(.data);
    }
    __romPos += SIZEOF(.timproc_uso_post);
    timproc_uso_ROM_END = __romPos;
    timproc_uso_VRAM_END = .;

    /* map4_data_uso: 8 Yay0 blocks + 7 inter slices. Code: block 2 only. */
    map4_data_uso_ROM_START = __romPos;
    .map4_data_uso_pre : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_pre.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_pre);

    .map4_data_uso_block0_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_block0_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_block0_yay0);

    .map4_data_uso_inter01 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_inter01.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_inter01);

    .map4_data_uso_block1_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_block1_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_block1_yay0);

    .map4_data_uso_inter12 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_inter12.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_inter12);

    .map4_data_uso_block2_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_block2_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_block2_yay0);

    .map4_data_uso_inter23 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_inter23.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_inter23);

    .map4_data_uso_block3_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_block3_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_block3_yay0);

    .map4_data_uso_inter34 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_inter34.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_inter34);

    .map4_data_uso_block4_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_block4_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_block4_yay0);

    .map4_data_uso_inter45 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_inter45.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_inter45);

    .map4_data_uso_block5_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_block5_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_block5_yay0);

    .map4_data_uso_inter56 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_inter56.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_inter56);

    .map4_data_uso_block6_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_block6_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_block6_yay0);

    .map4_data_uso_inter67 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_inter67.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_inter67);

    .map4_data_uso_block7_yay0 : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_block7_yay0.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_block7_yay0);

    .map4_data_uso_post : AT(__romPos)
    {
        FILL(0x00000000);
        build/assets/map4_data_uso_post.bin.o(.data);
    }
    __romPos += SIZEOF(.map4_data_uso_post);
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

    bootup_uso_pre_head_ROM_START = __romPos;
    bootup_uso_pre_head_VRAM = ADDR(.bootup_uso_pre_head);
    .bootup_uso_pre_head : AT(bootup_uso_pre_head_ROM_START)
    {
        FILL(0x00000000);
        bootup_uso_pre_head_DATA_START = .;
        build/assets/bootup_uso_pre_head.bin.o(.data);
        bootup_uso_pre_head_DATA_END = .;
        bootup_uso_pre_head_DATA_SIZE = ABSOLUTE(bootup_uso_pre_head_DATA_END - bootup_uso_pre_head_DATA_START);
    }
    __romPos += SIZEOF(.bootup_uso_pre_head);
    bootup_uso_pre_head_ROM_END = __romPos;
    bootup_uso_pre_head_VRAM_END = .;

    bootup_uso_ucodes_head_ROM_START = __romPos;
    bootup_uso_ucodes_head_VRAM = ADDR(.bootup_uso_ucodes_head);
    .bootup_uso_ucodes_head : AT(bootup_uso_ucodes_head_ROM_START)
    {
        FILL(0x00000000);
        bootup_uso_ucodes_head_DATA_START = .;
        build/assets/bootup_uso_ucodes_head.bin.o(.data);
        bootup_uso_ucodes_head_DATA_END = .;
        bootup_uso_ucodes_head_DATA_SIZE = ABSOLUTE(bootup_uso_ucodes_head_DATA_END - bootup_uso_ucodes_head_DATA_START);
    }
    __romPos += SIZEOF(.bootup_uso_ucodes_head);
    bootup_uso_ucodes_head_ROM_END = __romPos;
    bootup_uso_ucodes_head_VRAM_END = .;

    bootup_uso_ucodes_F3DEX_NoN_data_ROM_START = __romPos;
    bootup_uso_ucodes_F3DEX_NoN_data_VRAM = ADDR(.bootup_uso_ucodes_F3DEX_NoN_data);
    .bootup_uso_ucodes_F3DEX_NoN_data : AT(bootup_uso_ucodes_F3DEX_NoN_data_ROM_START)
    {
        FILL(0x00000000);
        bootup_uso_ucodes_F3DEX_NoN_data_DATA_START = .;
        build/assets/bootup_uso_ucodes_F3DEX_NoN_data.bin.o(.data);
        bootup_uso_ucodes_F3DEX_NoN_data_DATA_END = .;
        bootup_uso_ucodes_F3DEX_NoN_data_DATA_SIZE = ABSOLUTE(bootup_uso_ucodes_F3DEX_NoN_data_DATA_END - bootup_uso_ucodes_F3DEX_NoN_data_DATA_START);
    }
    __romPos += SIZEOF(.bootup_uso_ucodes_F3DEX_NoN_data);
    bootup_uso_ucodes_F3DEX_NoN_data_ROM_END = __romPos;
    bootup_uso_ucodes_F3DEX_NoN_data_VRAM_END = .;

    bootup_uso_ucodes_F3DEX_data_ROM_START = __romPos;
    bootup_uso_ucodes_F3DEX_data_VRAM = ADDR(.bootup_uso_ucodes_F3DEX_data);
    .bootup_uso_ucodes_F3DEX_data : AT(bootup_uso_ucodes_F3DEX_data_ROM_START)
    {
        FILL(0x00000000);
        bootup_uso_ucodes_F3DEX_data_DATA_START = .;
        build/assets/bootup_uso_ucodes_F3DEX_data.bin.o(.data);
        bootup_uso_ucodes_F3DEX_data_DATA_END = .;
        bootup_uso_ucodes_F3DEX_data_DATA_SIZE = ABSOLUTE(bootup_uso_ucodes_F3DEX_data_DATA_END - bootup_uso_ucodes_F3DEX_data_DATA_START);
    }
    __romPos += SIZEOF(.bootup_uso_ucodes_F3DEX_data);
    bootup_uso_ucodes_F3DEX_data_ROM_END = __romPos;
    bootup_uso_ucodes_F3DEX_data_VRAM_END = .;

    bootup_uso_ucodes_mid_ROM_START = __romPos;
    bootup_uso_ucodes_mid_VRAM = ADDR(.bootup_uso_ucodes_mid);
    .bootup_uso_ucodes_mid : AT(bootup_uso_ucodes_mid_ROM_START)
    {
        FILL(0x00000000);
        bootup_uso_ucodes_mid_DATA_START = .;
        build/assets/bootup_uso_ucodes_mid.bin.o(.data);
        bootup_uso_ucodes_mid_DATA_END = .;
        bootup_uso_ucodes_mid_DATA_SIZE = ABSOLUTE(bootup_uso_ucodes_mid_DATA_END - bootup_uso_ucodes_mid_DATA_START);
    }
    __romPos += SIZEOF(.bootup_uso_ucodes_mid);
    bootup_uso_ucodes_mid_ROM_END = __romPos;
    bootup_uso_ucodes_mid_VRAM_END = .;

    bootup_uso_ucodes_F3DLX_Rej_data_ROM_START = __romPos;
    bootup_uso_ucodes_F3DLX_Rej_data_VRAM = ADDR(.bootup_uso_ucodes_F3DLX_Rej_data);
    .bootup_uso_ucodes_F3DLX_Rej_data : AT(bootup_uso_ucodes_F3DLX_Rej_data_ROM_START)
    {
        FILL(0x00000000);
        bootup_uso_ucodes_F3DLX_Rej_data_DATA_START = .;
        build/assets/bootup_uso_ucodes_F3DLX_Rej_data.bin.o(.data);
        bootup_uso_ucodes_F3DLX_Rej_data_DATA_END = .;
        bootup_uso_ucodes_F3DLX_Rej_data_DATA_SIZE = ABSOLUTE(bootup_uso_ucodes_F3DLX_Rej_data_DATA_END - bootup_uso_ucodes_F3DLX_Rej_data_DATA_START);
    }
    __romPos += SIZEOF(.bootup_uso_ucodes_F3DLX_Rej_data);
    bootup_uso_ucodes_F3DLX_Rej_data_ROM_END = __romPos;
    bootup_uso_ucodes_F3DLX_Rej_data_VRAM_END = .;

    bootup_uso_ucodes_tail_ROM_START = __romPos;
    bootup_uso_ucodes_tail_VRAM = ADDR(.bootup_uso_ucodes_tail);
    .bootup_uso_ucodes_tail : AT(bootup_uso_ucodes_tail_ROM_START)
    {
        FILL(0x00000000);
        bootup_uso_ucodes_tail_DATA_START = .;
        build/assets/bootup_uso_ucodes_tail.bin.o(.data);
        bootup_uso_ucodes_tail_DATA_END = .;
        bootup_uso_ucodes_tail_DATA_SIZE = ABSOLUTE(bootup_uso_ucodes_tail_DATA_END - bootup_uso_ucodes_tail_DATA_START);
    }
    __romPos += SIZEOF(.bootup_uso_ucodes_tail);
    bootup_uso_ucodes_tail_ROM_END = __romPos;
    bootup_uso_ucodes_tail_VRAM_END = .;

    bootup_uso_pre_tail_ROM_START = __romPos;
    bootup_uso_pre_tail_VRAM = ADDR(.bootup_uso_pre_tail);
    .bootup_uso_pre_tail : AT(bootup_uso_pre_tail_ROM_START)
    {
        FILL(0x00000000);
        bootup_uso_pre_tail_DATA_START = .;
        build/assets/bootup_uso_pre_tail.bin.o(.data);
        bootup_uso_pre_tail_DATA_END = .;
        bootup_uso_pre_tail_DATA_SIZE = ABSOLUTE(bootup_uso_pre_tail_DATA_END - bootup_uso_pre_tail_DATA_START);
    }
    __romPos += SIZEOF(.bootup_uso_pre_tail);
    bootup_uso_pre_tail_ROM_END = __romPos;
    bootup_uso_pre_tail_VRAM_END = .;

    /* bootup_uso text: loaded at VRAM 0 (code is unrelocated; LUIs store
     * upper16=0x0000 as placeholders, patched by the USO loader at runtime).
     * Use a NOLOAD VRAM so ld doesn't conflict with kernel at 0x80000000. */
    bootup_uso_ROM_START = __romPos;
    .bootup_uso 0x00000000 : AT(bootup_uso_ROM_START)
    {
        FILL(0x00000000);
        bootup_uso_TEXT_START = .;
        build/src/bootup_uso/bootup_uso.c.o(.text);
        build/src/bootup_uso/bootup_uso_o0_F1F0.c.o(.text);
        build/src/bootup_uso/bootup_uso_o0_F390.c.o(.text);
        build/src/bootup_uso/bootup_uso_F434.c.o(.text);
        build/src/bootup_uso/bootup_uso_o0_F7F4.c.o(.text);
        build/src/bootup_uso/bootup_uso_tail1.c.o(.text);
        build/src/bootup_uso/bootup_uso_o0_1024C.c.o(.text);
        build/src/bootup_uso/bootup_uso_tail2.c.o(.text);
        build/src/bootup_uso/bootup_uso_o0_10310.c.o(.text);
        build/src/bootup_uso/bootup_uso_tail3a.c.o(.text);
        build/src/bootup_uso/bootup_uso_o0_11D40.c.o(.text);
        build/src/bootup_uso/bootup_uso_tail3a_bot.c.o(.text);
        build/src/bootup_uso/bootup_uso_o0_120A8.c.o(.text);
        build/src/bootup_uso/bootup_uso_tail3b_top.c.o(.text);
        build/src/bootup_uso/bootup_uso_o0_123F0.c.o(.text);
        build/src/bootup_uso/bootup_uso_tail3b_bot_t.c.o(.text);
        build/src/bootup_uso/bootup_uso_o0_12B7C.c.o(.text);
        build/src/bootup_uso/bootup_uso_tail3b_bot_b.c.o(.text);
        build/src/bootup_uso/bootup_uso_o0_12DA4.c.o(.text);
        build/src/bootup_uso/bootup_uso_tail4.c.o(.text);
        bootup_uso_TEXT_END = .;
        bootup_uso_TEXT_SIZE = ABSOLUTE(bootup_uso_TEXT_END - bootup_uso_TEXT_START);
    }
    __romPos += SIZEOF(.bootup_uso);
    bootup_uso_ROM_END = __romPos;
    bootup_uso_VRAM = ADDR(.bootup_uso);
    bootup_uso_VRAM_END = .;

    bootup_uso_post_ROM_START = __romPos;
    bootup_uso_post_VRAM = ADDR(.bootup_uso_post);
    .bootup_uso_post : AT(bootup_uso_post_ROM_START)
    {
        FILL(0x00000000);
        bootup_uso_post_DATA_START = .;
        build/assets/bootup_uso_post.bin.o(.data);
        bootup_uso_post_DATA_END = .;
        bootup_uso_post_DATA_SIZE = ABSOLUTE(bootup_uso_post_DATA_END - bootup_uso_post_DATA_START);
    }
    __romPos += SIZEOF(.bootup_uso_post);
    bootup_uso_post_ROM_END = __romPos;
    bootup_uso_post_VRAM_END = .;

    game_libs_pre_ROM_START = __romPos;
    game_libs_pre_VRAM = ADDR(.game_libs_pre);
    .game_libs_pre : AT(game_libs_pre_ROM_START)
    {
        FILL(0x00000000);
        game_libs_pre_DATA_START = .;
        build/assets/game_libs_pre.bin.o(.data);
        game_libs_pre_DATA_END = .;
        game_libs_pre_DATA_SIZE = ABSOLUTE(game_libs_pre_DATA_END - game_libs_pre_DATA_START);
    }
    __romPos += SIZEOF(.game_libs_pre);
    game_libs_pre_ROM_END = __romPos;
    game_libs_pre_VRAM_END = .;

    /* game_libs text: VRAM=0 (relocatable; all LUIs upper16=0, JALs target=0
       in ROM for unresolved refs, pre-resolved intra-segment calls have
       small targets that re-resolve cleanly at VRAM=0). A 56 KB RSP microcode
       blob sits mid-text at VRAM 0xEBF8..0x1CA10 and is spliced back as a
       raw .data bin so objdiff doesn't count it against code progress. */
    game_libs_ROM_START = __romPos;
    .game_libs 0x00000000 : AT(game_libs_ROM_START)
    {
        FILL(0x00000000);
        game_libs_TEXT_START = .;
        build/src/game_libs/game_libs.c.o(.text);
        build/assets/game_libs_text2_pre.bin.o(.data);
        build/assets/game_libs_text2_F3DEX_NoN_imem.bin.o(.data);
        build/assets/game_libs_text2_F3DEX_imem.bin.o(.data);
        build/assets/game_libs_text2_F3DLP_Rej_imem.bin.o(.data);
        build/assets/game_libs_text2_mid.bin.o(.data);
        build/assets/game_libs_text2_F3DLX_Rej_imem.bin.o(.data);
        build/assets/game_libs_text2_tail.bin.o(.data);
        build/src/game_libs/game_libs_post.c.o(.text);
        game_libs_TEXT_END = .;
        game_libs_TEXT_SIZE = ABSOLUTE(game_libs_TEXT_END - game_libs_TEXT_START);
    }
    __romPos += SIZEOF(.game_libs);
    game_libs_ROM_END = __romPos;
    game_libs_VRAM = ADDR(.game_libs);
    game_libs_VRAM_END = .;

    game_libs_post_ROM_START = __romPos;
    game_libs_post_VRAM = ADDR(.game_libs_post);
    .game_libs_post : AT(game_libs_post_ROM_START)
    {
        FILL(0x00000000);
        game_libs_post_DATA_START = .;
        build/assets/game_libs_post.bin.o(.data);
        game_libs_post_DATA_END = .;
        game_libs_post_DATA_SIZE = ABSOLUTE(game_libs_post_DATA_END - game_libs_post_DATA_START);
    }
    __romPos += SIZEOF(.game_libs_post);
    game_libs_post_ROM_END = __romPos;
    game_libs_post_VRAM_END = .;

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
