BASENAME  := tenshoe
TARGET    := $(BASENAME)
ROM       := $(TARGET).z64
ELF       := build/$(TARGET).elf
LD_SCRIPT := $(TARGET).ld
BASEROM   := baserom.z64

# Paths
TOOLS       := tools
IDO_DIR     := $(TOOLS)/ido-static-recomp/build/7.1/out
IDO53_DIR   := $(TOOLS)/ido-static-recomp/build/5.3/out
ASM_PROC    := python3 $(TOOLS)/asm-processor/asm_processor.py
ASM_PRELUDE := $(TOOLS)/asm-processor/prelude.inc

# Tools
CROSS    := mips-linux-gnu-
AS       := $(CROSS)as
CC       := $(IDO_DIR)/cc
LD       := $(CROSS)ld
OBJCOPY  := $(CROSS)objcopy

# Flags
ASFLAGS  := -EB -march=vr4300 -mtune=vr4300 -mabi=32 -I include
OPT_FLAGS := -O2
MIPSISET := -mips2 -32
CFLAGS   := -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul
CPPFLAGS := -I include -I src
LDFLAGS  := -T $(LD_SCRIPT) -T undefined_syms_auto.txt -Map build/$(TARGET).map --no-check-sections

# Per-file optimization overrides (O1 libultra functions, O0 empty stubs)
# game_libs statically-linked libultra contpfs functions: original objects were
# built with IDO 5.3 -O1 (7.1 cannot reproduce the stack-residency+filled-slot
# combo; see docs/IDO_CODEGEN.md#feedback-ido-stack-residency-plus-filled-slots-is-o1-not-o0)
build/src/game_libs/game_libs_ido53_71864.c.o build/non_matching/src/game_libs/game_libs_ido53_71864.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_71864.c.o build/non_matching/src/game_libs/game_libs_ido53_71864.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_71864.c.o: TRUNCATE_TEXT := 0x5C
build/src/game_libs/game_libs_ido53_718C0.c.o build/non_matching/src/game_libs/game_libs_ido53_718C0.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_718C0.c.o build/non_matching/src/game_libs/game_libs_ido53_718C0.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_718C0.c.o: TRUNCATE_TEXT := 0xD04
build/src/arcproc_uso/arcproc_uso_o0_50.c.o build/non_matching/src/arcproc_uso/arcproc_uso_o0_50.c.o: OPT_FLAGS := -O0
build/src/arcproc_uso/arcproc_uso.c.o build/non_matching/src/arcproc_uso/arcproc_uso.c.o: OPT_FLAGS := -O0
build/src/arcproc_uso/arcproc_uso.c.o: TRUNCATE_TEXT := 0x50
build/non_matching/src/kernel/kernel_038.c.o: NON_MATCHING_TRUNCATE_TEXT := 0x140
build/non_matching/src/kernel/kernel_017.c.o: NON_MATCHING_TRUNCATE_TEXT := 0x9C
build/src/arcproc_uso/arcproc_uso.c.o: PREFIX_BYTES := arcproc_uso_func_00000000=0x10006F00
build/non_matching/src/arcproc_uso/arcproc_uso.c.o: NON_MATCHING_PREFIX_BYTES := arcproc_uso_func_00000000=0x10006F00
build/src/boarder5_uso/boarder5_uso.c.o: PREFIX_BYTES := boarder5_uso_func_00000000=0x1000736F
build/non_matching/src/boarder5_uso/boarder5_uso.c.o: NON_MATCHING_PREFIX_BYTES := boarder5_uso_func_00000000=0x1000736F
build/src/eddproc_uso/eddproc_uso.c.o: PREFIX_BYTES := eddproc_uso_func_00000000=0x10006F00
build/non_matching/src/eddproc_uso/eddproc_uso.c.o: NON_MATCHING_PREFIX_BYTES := eddproc_uso_func_00000000=0x10006F00
build/src/n64proc_uso/n64proc_uso.c.o: PREFIX_BYTES := n64proc_uso_func_00000000=0x10006F00
build/non_matching/src/n64proc_uso/n64proc_uso.c.o: NON_MATCHING_PREFIX_BYTES := n64proc_uso_func_00000000=0x10006F00
build/src/h2hproc_uso/h2hproc_uso.c.o: PREFIX_BYTES := h2hproc_uso_func_00000000=0x10006F00
build/non_matching/src/h2hproc_uso/h2hproc_uso.c.o: NON_MATCHING_PREFIX_BYTES := h2hproc_uso_func_00000000=0x10006F00
# 2026-06-10 ROM-length convergence: each direct-link USO c segment must emit
# .text at EXACTLY the original segment length (post_bin_start - seg_start).
# IDO/asm-processor leave trailing zero padding after the last function
# (and GAS keeps sh_addralign=16), which used to shift every downstream
# segment and inflate the ROM. TRUNCATE_TEXT clips the all-zero tail to the
# original length (boarder1/3 were already exact because explicit >=2-word
# _pad.s blocks happened to land them on their exact lengths).
build/src/boarder2_uso/boarder2_uso.c.o: TRUNCATE_TEXT := 0x194
build/src/boarder4_uso/boarder4_uso.c.o: TRUNCATE_TEXT := 0x198
build/src/boarder5_uso/boarder5_uso.c.o: TRUNCATE_TEXT := 0x1A0
build/src/n64proc_uso/n64proc_uso.c.o: TRUNCATE_TEXT := 0x430
build/src/titproc_uso/titproc_uso.c.o: TRUNCATE_TEXT := 0x2A30
# eddproc orig text ends on a dead jr-ra word (delay-slot nop lives in the post
# bin); the 1-word _pad.s emits jr-ra + an extra nop — truncate clips that nop.
build/src/eddproc_uso/eddproc_uso.c.o: TRUNCATE_TEXT := 0x480
# gui/h2hproc: single alignment-nop pads between/after matched C fns are
# all-zero SUFFIX_BYTES_FORCE (1-word GLOBAL_ASM pad blocks emit 2 words, +4
# drift each — documented trap). FORCE because the payload is a zero word and
# the fns end `jr ra; nop`, which trips the plain-SUFFIX_BYTES skip path.
build/src/gui_uso/gui_uso_zcopy_0.c.o build/non_matching/src/gui_uso/gui_uso_zcopy_0.c.o: CC_ONLY_FLAGS := -Wo,-zcopy:0
build/src/gui_uso/gui_uso_zcopy_0.c.o: TRUNCATE_TEXT := 0x148
build/src/gui_uso/gui_uso_zcopy_0.c.o: PREFIX_BYTES := gui_func_00000000=0x1000736F
build/non_matching/src/gui_uso/gui_uso_zcopy_0.c.o: NON_MATCHING_PREFIX_BYTES := gui_func_00000000=0x1000736F
build/src/gui_uso/gui_uso.c.o: SUFFIX_BYTES_FORCE := gui_func_0000161C=0x00000000
build/src/gui_uso/gui_uso.c.o: TRUNCATE_TEXT := 0x4738
# Mirror the suffix onto the non_matching object so report.json/objdiff (which
# compare build/non_matching vs expected) score the trailing alignment-nop word.
# splat-symbol-boundary trailing-delay-nop class — see docs/MATCHING_WORKFLOW.md.
build/non_matching/src/gui_uso/gui_uso.c.o: NON_MATCHING_SUFFIX_BYTES_FORCE := gui_func_0000161C=0x00000000
build/src/h2hproc_uso/h2hproc_uso.c.o: SUFFIX_BYTES_FORCE := h2hproc_uso_func_00000274=0x00000000 h2hproc_uso_func_00001AFC=0x00000000
build/src/h2hproc_uso/h2hproc_uso.c.o: TRUNCATE_TEXT := 0x1B30
build/non_matching/src/h2hproc_uso/h2hproc_uso.c.o: NON_MATCHING_SUFFIX_BYTES_FORCE := h2hproc_uso_func_00000274=0x00000000
# 2026-05-27: removed instruction-appending PREFIX_BYTES for game_libs_func_0003ECDC,
# game_libs_func_0005AFB0, kernel func_80007FC8 — all were leading-nop / self-branch
# instruction-faking that violated the 2026-05-23 no-instruction-forcing-matches policy
# (per feedback_no_instruction_forcing_matches_policy). USO-header PREFIX_BYTES for
# n64proc_uso_func_00000000 / h2hproc_uso_func_00000000 above stay (genuine USO segment
# entry header data, not instruction-appending).
build/src/arcproc_uso/arcproc_uso_o0_50.c.o: TRUNCATE_TEXT := 0xDC
build/src/arcproc_uso/arcproc_uso_o0_12C.c.o build/non_matching/src/arcproc_uso/arcproc_uso_o0_12C.c.o: OPT_FLAGS := -O0
build/src/arcproc_uso/arcproc_uso_o0_12C.c.o: TRUNCATE_TEXT := 0x114
build/src/bootup_uso/bootup_uso_o0_F1F0.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_F1F0.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_F390.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_F390.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_F7F4.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_F7F4.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_FBCC.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_FBCC.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_1024C.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_1024C.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_10310.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_10310.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_120A8.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_120A8.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_123F0.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_123F0.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_12B7C.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_12B7C.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_12DA4.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_12DA4.c.o: OPT_FLAGS := -O0
# (o0_12DA4 / tail4 TRUNCATE_TEXT sizes are set further down with the rest of
# the bootup split chain — see the 0x1F0 / 0x184C entries.)
# Trim .text sizes + reduce sh_addralign to 4 so split .o files link at the
# exact non-16-aligned offsets in bootup_uso. See feedback_non_aligned_o_split.md.
build/src/bootup_uso/bootup_uso.c.o: TRUNCATE_TEXT := 0xF1F0
build/src/bootup_uso/bootup_uso_o0_F1F0.c.o: TRUNCATE_TEXT := 0x1A0
build/src/bootup_uso/bootup_uso_o0_F390.c.o: TRUNCATE_TEXT := 0x334
build/src/bootup_uso/bootup_uso_F434.c.o build/non_matching/src/bootup_uso/bootup_uso_F434.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_F434.c.o: TRUNCATE_TEXT := 0xA8
build/src/bootup_uso/bootup_uso_o0_F7F4.c.o: TRUNCATE_TEXT := 0xB0
build/src/bootup_uso/bootup_uso_tail1.c.o: TRUNCATE_TEXT := 0x138
build/src/bootup_uso/bootup_uso_o0_FBCC.c.o: TRUNCATE_TEXT := 0x5C
build/src/bootup_uso/bootup_uso_tail1_bot.c.o: TRUNCATE_TEXT := 0x4C8
build/src/bootup_uso/bootup_uso_tail1_bot.c.o build/non_matching/src/bootup_uso/bootup_uso_tail1_bot.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_1024C.c.o: TRUNCATE_TEXT := 0x58
build/src/bootup_uso/bootup_uso_tail2.c.o: TRUNCATE_TEXT := 0x6C
build/src/bootup_uso/bootup_uso_tail2.c.o build/non_matching/src/bootup_uso/bootup_uso_tail2.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_o0_10310.c.o: TRUNCATE_TEXT := 0x14
# 2026-07-10: tail3a re-truncated 0x14D8 -> 0x848 after carving the 0x10B6C
# -O0 island into bootup_uso_o0_10B6C.c; the 0x10C8C..0x116C7 INCLUDE_ASM
# remainder moved to bootup_uso_tail3a_10C8C.c (-O2 -g3) and the 0x116C8 -O0
# island into bootup_uso_o0_116C8.c.
build/src/bootup_uso/bootup_uso_tail3a.c.o: TRUNCATE_TEXT := 0x28
# 2026-07-10 carve: tail3a (0x10324..0x10B6C) split 4 ways so the two -O0
# islands build at -O0: tail3a {10324,10344} | o0_1034C | tail3a_10540
# {10540 INCLUDE_ASM, 10A9C, 10AA8} | o0_10AB0.
build/src/bootup_uso/bootup_uso_o0_1034C.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_1034C.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_1034C.c.o: TRUNCATE_TEXT := 0x1F4
build/non_matching/src/bootup_uso/bootup_uso_o0_1034C.c.o: NON_MATCHING_TRUNCATE_TEXT := 0x1F4
build/src/bootup_uso/bootup_uso_tail3a_10540.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3a_10540.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_o0_10AB0.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_10AB0.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_10AB0.c.o: TRUNCATE_TEXT := 0xBC
build/non_matching/src/bootup_uso/bootup_uso_o0_10AB0.c.o: NON_MATCHING_TRUNCATE_TEXT := 0xBC
build/src/bootup_uso/bootup_uso_o0_10B6C.c.o: TRUNCATE_TEXT := 0x120
build/src/bootup_uso/bootup_uso_o0_10B6C.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_10B6C.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_tail3a_10C8C.c.o: TRUNCATE_TEXT := 0xA3C
build/src/bootup_uso/bootup_uso_tail3a_10C8C.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3a_10C8C.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_116C8.c.o: TRUNCATE_TEXT := 0x134
build/src/bootup_uso/bootup_uso_o0_116C8.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_116C8.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_117FC.c.o: TRUNCATE_TEXT := 0xE8
build/src/bootup_uso/bootup_uso_o0_117FC.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_117FC.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_tail3a.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3a.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_o0_F954.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_F954.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_F954.c.o: TRUNCATE_TEXT := 0x194
build/src/bootup_uso/bootup_uso_o0_FAE8.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_FAE8.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_FAE8.c.o: TRUNCATE_TEXT := 0xE4
build/src/bootup_uso/bootup_uso_o0_100F0.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_100F0.c.o: OPT_FLAGS := -O0
# 0x15C = exact len of the 0x100F0..0x1024C region (func_000100F0 0x7C +
# func_0001016C 0xE0); clips IDO's trailing pad and drops sh_addralign to 4.
build/src/bootup_uso/bootup_uso_o0_100F0.c.o: TRUNCATE_TEXT := 0x15C
build/src/bootup_uso/bootup_uso_o0_118E4.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_118E4.c.o: OPT_FLAGS := -O0
# 0x150 = exact region len (0x118E4..0x11A34); content already 0x150 — the
# truncate is for the sh_addralign->4 side effect (kills the 16-align link gap
# in front of this .o; 0x118E4 is only 4-aligned).
build/src/bootup_uso/bootup_uso_o0_118E4.c.o: TRUNCATE_TEXT := 0x150
build/src/bootup_uso/bootup_uso_o0_11A34.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_11A34.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_11A34.c.o: TRUNCATE_TEXT := 0x80
build/src/bootup_uso/bootup_uso_o0_11AB4.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_11AB4.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_11AB4.c.o: TRUNCATE_TEXT := 0xA8
build/src/bootup_uso/bootup_uso_tail3a_mid.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3a_mid.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_tail3a_mid.c.o: TRUNCATE_TEXT := 0x114
build/src/bootup_uso/bootup_uso_o0_11C70.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_11C70.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_11C70.c.o: TRUNCATE_TEXT := 0xD0
build/src/bootup_uso/bootup_uso_o0_11D40.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_11D40.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_11D40.c.o: TRUNCATE_TEXT := 0x30
build/non_matching/src/bootup_uso/bootup_uso_o0_11D40.c.o: NON_MATCHING_TRUNCATE_TEXT := 0x30
build/src/bootup_uso/bootup_uso_tail3a_bot.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3a_bot.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_tail3a_bot.c.o: TRUNCATE_TEXT := 0x8
# 2026-07-10 carve: tail3a_bot (0x11D70..0x120A8) split 5 ways so the two
# frameless -O0 leaves land file-terminal (trailing dead-pair TRUNCATE):
# tail3a_bot {11D70} | o0_11D78 | tail3a_bot_11DB4 {11DB4} | o0_11DBC |
# tail3a_bot_11DF8 {11DF8, 11E00/11ED4/11FA8 NM, 1207C..120A0}.
build/src/bootup_uso/bootup_uso_o0_11D78.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_11D78.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_11D78.c.o: TRUNCATE_TEXT := 0x3C
build/non_matching/src/bootup_uso/bootup_uso_o0_11D78.c.o: NON_MATCHING_TRUNCATE_TEXT := 0x3C
build/src/bootup_uso/bootup_uso_tail3a_bot_11DB4.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3a_bot_11DB4.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_tail3a_bot_11DB4.c.o: TRUNCATE_TEXT := 0x8
build/src/bootup_uso/bootup_uso_o0_11DBC.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_11DBC.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_11DBC.c.o: TRUNCATE_TEXT := 0x3C
build/non_matching/src/bootup_uso/bootup_uso_o0_11DBC.c.o: NON_MATCHING_TRUNCATE_TEXT := 0x3C
build/src/bootup_uso/bootup_uso_tail3a_bot_11DF8.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3a_bot_11DF8.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_tail3a_bot_11DF8.c.o: TRUNCATE_TEXT := 0x2B0
build/src/bootup_uso/bootup_uso_o0_120A8.c.o: TRUNCATE_TEXT := 0x21C
build/src/bootup_uso/bootup_uso_tail3b_top.c.o: TRUNCATE_TEXT := 0x12C
build/src/bootup_uso/bootup_uso_tail3b_top.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3b_top.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_123F0.c.o: TRUNCATE_TEXT := 0x27C
build/src/bootup_uso/bootup_uso_tail3b_bot_t.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3b_bot_t.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_tail3b_bot_t.c.o: TRUNCATE_TEXT := 0x1AC
build/src/bootup_uso/bootup_uso_o0_12B7C.c.o: TRUNCATE_TEXT := 0x3E0
build/src/bootup_uso/bootup_uso_tail3b_bot_b.c.o: TRUNCATE_TEXT := 0x18
build/src/bootup_uso/bootup_uso_tail3b_bot_b.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3b_bot_b.c.o: OPT_FLAGS := -O2 -g3
# 0x1F0 = 0x12DA4..0x12E00 + the 8 zero bytes of 16-align padding at
# 0x12DF8..0x12E00 that the original ROM keeps before tail4's first fn
# (was 0x1E8, which cut them and left the segment -0x8 short; IDO already
# emits the zeros, the truncate just stops clipping them).
build/src/bootup_uso/bootup_uso_o0_12DA4.c.o: TRUNCATE_TEXT := 0x1F0
# 0x184C = exact len of the tail4 region (0x12E00..0x1464C); was 0x1850 (+4).
build/src/bootup_uso/bootup_uso_tail4.c.o: TRUNCATE_TEXT := 0x184C
# game_libs split around the 56 KB RSP microcode blob at 0xEBF8..0x1CA10.
# Reduce sh_addralign to 4 so the three objects link back-to-back without
# 16-byte padding between them. Size targets match the natural compiled
# sizes (drift included) so no real code gets truncated; same accumulated
# drift as main's pre-split game_libs.c.o. See feedback_non_aligned_o_split.md.
build/src/game_libs/game_libs.c.o: TRUNCATE_TEXT := 0x8944
# 2026-05-27: removed instruction-appending PREFIX_BYTES for game_libs_func_000040EC
# (per feedback_no_instruction_forcing_matches_policy — same class as the 0003ECDC/
# 0005AFB0/80007FC8 cleanup above).
build/src/game_libs/game_libs_o0_8944.c.o build/non_matching/src/game_libs/game_libs_o0_8944.c.o: OPT_FLAGS := -O0
build/src/game_libs/game_libs_o0_8944.c.o: TRUNCATE_TEXT := 0xFC
build/src/game_libs/game_libs_o0_8A40.c.o build/non_matching/src/game_libs/game_libs_o0_8A40.c.o: OPT_FLAGS := -O0
build/src/game_libs/game_libs_g3_34448.c.o build/non_matching/src/game_libs/game_libs_g3_34448.c.o: OPT_FLAGS := -O2 -g3
build/src/game_libs/game_libs_g3_34448.c.o: TRUNCATE_TEXT := 0x10
build/src/game_libs/game_libs_post0b.c.o: TRUNCATE_TEXT := 0x2eb00
# gl_func_00055B10: byte-correct real-def, IDO trailing jr-delay nop -> symbol 0x30
# vs target 0x2c (nop is baserom alignment). Resize non_matching symbol to 0x2c so
# objdiff scores 11w not 12w. ROM-neutral (non_matching .o only). (Same class as EBC8.)
build/non_matching/src/game_libs/game_libs_post0b.c.o: NON_MATCHING_TEXT_CLIP_KEEP_ALIGN := 0x2b62c gl_func_00055B10=0x2c
build/src/game_libs/game_libs_g3_62F58.c.o build/non_matching/src/game_libs/game_libs_g3_62F58.c.o: OPT_FLAGS := -O2 -g3
build/src/game_libs/game_libs_g3_62F58.c.o: TRUNCATE_TEXT := 0xC
build/src/game_libs/game_libs_post1b.c.o: TRUNCATE_TEXT := 0x8ce0
# (2026-06-10 relayout: the post1b head-shortfall compensation SUFFIX was
# removed -- the missing prologues upstream are restored for real.)
build/src/game_libs/game_libs_ido53_6BC44.c.o build/non_matching/src/game_libs/game_libs_ido53_6BC44.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6BC44.c.o build/non_matching/src/game_libs/game_libs_ido53_6BC44.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6BC44.c.o: TRUNCATE_TEXT := 0x1D0
build/src/game_libs/game_libs_post1b2.c.o: TRUNCATE_TEXT := 0x570
build/src/game_libs/game_libs_ido53_6C384.c.o build/non_matching/src/game_libs/game_libs_ido53_6C384.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6C384.c.o build/non_matching/src/game_libs/game_libs_ido53_6C384.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6C384.c.o: TRUNCATE_TEXT := 0x7C
build/src/game_libs/game_libs_post1b2c.c.o: TRUNCATE_TEXT := 0x3D94
build/src/game_libs/game_libs_ido53_70194.c.o build/non_matching/src/game_libs/game_libs_ido53_70194.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_70194.c.o build/non_matching/src/game_libs/game_libs_ido53_70194.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_70194.c.o: TRUNCATE_TEXT := 0x180
build/src/game_libs/game_libs_post1c.c.o: TRUNCATE_TEXT := 0xC90
build/src/game_libs/game_libs_o0_8A40.c.o: TRUNCATE_TEXT := 0xA4
build/src/game_libs/game_libs_o0_8AE4.c.o build/non_matching/src/game_libs/game_libs_o0_8AE4.c.o: OPT_FLAGS := -O0
build/src/game_libs/game_libs_o0_8AE4.c.o: TRUNCATE_TEXT := 0x158
build/src/game_libs/game_libs_mid.c.o build/non_matching/src/game_libs/game_libs_mid.c.o: OPT_FLAGS := -O0
build/src/game_libs/game_libs_mid.c.o: TRUNCATE_TEXT := 0x860
build/src/game_libs/game_libs_o0_949C.c.o build/non_matching/src/game_libs/game_libs_o0_949C.c.o: OPT_FLAGS := -O0
build/src/game_libs/game_libs_o0_949C.c.o: TRUNCATE_TEXT := 0x100
# Bake resolved jal targets to match expected/.o (which is INCLUDE_ASM-derived
# with pre-baked jals). Without these, the .o has `jal 0` + R_MIPS_26 relocs;
# byte-verify fails even though ROM ends up identical post-link.
build/src/game_libs/game_libs_tail.c.o: TRUNCATE_TEXT := 0x565c
# gl_func_0000EBC8 is a byte-correct real-def (ROM matches, make verify OK) but IDO
# emits a trailing jr-delay nop so its symbol is 0x30 (12w) vs the target's 0x2c (11w
# — baserom attributes that nop to alignment). objdiff per-symbol scored 90.9%=11/12.
# Resize the non_matching symbol to 0x2c so objdiff sees the matching 11w. ROM-neutral
# (non_matching .o only); the nop byte stays in .text. Section size unchanged (0x5530).
build/non_matching/src/game_libs/game_libs_tail.c.o: NON_MATCHING_TEXT_CLIP_KEEP_ALIGN := 0x5544 gl_func_0000EBC8=0x2c
build/src/game_libs/game_libs_post.c.o: TRUNCATE_TEXT := 0x17a38
# 70FA4 = the merged full function (head fragment 70FA0 + the old g3_70FBC
# tail carve); -O1 -g3 is the matching mode. .text ends with 8 bytes of
# natural zero padding = the 0x70FCC/0x70FD0 pad nops before 70FCC=fcos.
# (direct CC, no asm-processor -- asm-processor rejects -O1 -g3; 6AF0C
# precedent. Rules live next to the 6AF0C one near 'all: verify'.)
build/src/game_libs/game_libs_post2.c.o: TRUNCATE_TEXT := 0x890
build/src/game_libs/game_libs_post2b.c.o build/non_matching/src/game_libs/game_libs_post2b.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_post2b.c.o build/non_matching/src/game_libs/game_libs_post2b.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_post2b.c.o: TRUNCATE_TEXT := 0x6C4
build/src/game_libs/game_libs_ido53_72C88.c.o build/non_matching/src/game_libs/game_libs_ido53_72C88.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_72C88.c.o build/non_matching/src/game_libs/game_libs_ido53_72C88.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_72C88.c.o: CC_ONLY_FLAGS := -Olimit 1
build/non_matching/src/game_libs/game_libs_ido53_72C88.c.o: CC_ONLY_FLAGS := -Olimit 1
build/src/game_libs/game_libs_ido53_72C88.c.o: TRUNCATE_TEXT := 0x3AC
build/src/game_libs/game_libs_post2b_c.c.o: TRUNCATE_TEXT := 0x300
build/src/game_libs/game_libs_ido53_73334.c.o build/non_matching/src/game_libs/game_libs_ido53_73334.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_73334.c.o build/non_matching/src/game_libs/game_libs_ido53_73334.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_73334.c.o: SUFFIX_BYTES := gl_func_00073538=0x00000000,0x00000000,0x00000000
build/src/game_libs/game_libs_ido53_73334.c.o: TRUNCATE_TEXT := 0x360
build/src/game_libs/game_libs_post2b_d.c.o: TRUNCATE_TEXT := 0x1210
build/src/game_libs/game_libs_ido53_748A4.c.o build/non_matching/src/game_libs/game_libs_ido53_748A4.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_748A4.c.o build/non_matching/src/game_libs/game_libs_ido53_748A4.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_748A4.c.o: SUFFIX_BYTES := gl_func_00074AC0=0x00000000,0x00000000
build/src/game_libs/game_libs_ido53_748A4.c.o: TRUNCATE_TEXT := 0x360
build/src/game_libs/game_libs_post2b_e.c.o: TRUNCATE_TEXT := 0x150
build/src/game_libs/game_libs_ido53_74D54.c.o build/non_matching/src/game_libs/game_libs_ido53_74D54.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_74D54.c.o build/non_matching/src/game_libs/game_libs_ido53_74D54.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_74D54.c.o: SUFFIX_BYTES := gl_func_00074D54=0x00000000,0x00000000
build/src/game_libs/game_libs_ido53_74D54.c.o: TRUNCATE_TEXT := 0x60
build/src/game_libs/game_libs_ido53_74DB4.c.o build/non_matching/src/game_libs/game_libs_ido53_74DB4.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_74DB4.c.o build/non_matching/src/game_libs/game_libs_ido53_74DB4.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_74DB4.c.o: TRUNCATE_TEXT := 0x128
build/src/game_libs/game_libs_post2b_f.c.o: TRUNCATE_TEXT := 0x388
build/src/game_libs/game_libs_ido_75264.c.o build/non_matching/src/game_libs/game_libs_ido_75264.c.o: OPT_FLAGS := -O1
# 2026-06-10: pad sidecar trimmed 5->2 words (0x48->0x3C). The segment truly ends at
# VRAM 0x752A0 (ROM 0xE5A378 = game_libs_post bin start); the extra 3 zero words were
# the +0xC full-ROM length defect (base's 00000001/00007D58 words there are the bin's
# own first records, not "pre-existing drift").
build/src/game_libs/game_libs_ido_75264.c.o build/non_matching/src/game_libs/game_libs_ido_75264.c.o: TRUNCATE_TEXT := 0x3C

build/src/kernel/kernel_014.c.o build/non_matching/src/kernel/kernel_014.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_001.c.o build/non_matching/src/kernel/kernel_001.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_003.c.o build/non_matching/src/kernel/kernel_003.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_005.c.o build/non_matching/src/kernel/kernel_005.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_005_b.c.o build/non_matching/src/kernel/kernel_005_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_007.c.o build/non_matching/src/kernel/kernel_007.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_009.c.o build/non_matching/src/kernel/kernel_009.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_011.c.o build/non_matching/src/kernel/kernel_011.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_013.c.o build/non_matching/src/kernel/kernel_013.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_015.c.o build/non_matching/src/kernel/kernel_015.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_017.c.o build/non_matching/src/kernel/kernel_017.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_019.c.o build/non_matching/src/kernel/kernel_019.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_021.c.o build/non_matching/src/kernel/kernel_021.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_023.c.o build/non_matching/src/kernel/kernel_023.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_025.c.o build/non_matching/src/kernel/kernel_025.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_027.c.o build/non_matching/src/kernel/kernel_027.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_028.c.o build/non_matching/src/kernel/kernel_028.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_029.c.o build/non_matching/src/kernel/kernel_029.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_030.c.o build/non_matching/src/kernel/kernel_030.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_031.c.o build/non_matching/src/kernel/kernel_031.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_031.c.o: TRUNCATE_TEXT := 0x48  # 0x44 content + ROM pad word at 0x802C (2026-06-10 relayout)
# kernel_031b: file-split holding func_80008030 (compiled at -O2). Per
# feedback_insn_patch_on_reloc_instructions_breaks_byte_verify.md: skip
# patching offsets 0x0/0x4 (R_MIPS_HI16/LO16 for D_A4040010); only patch
# non-reloc offsets 0xC/0x10/0x18/0x20.
build/src/kernel/kernel_031b.c.o build/non_matching/src/kernel/kernel_031b.c.o: OPT_FLAGS := -O2
build/src/kernel/kernel_031b.c.o: TRUNCATE_TEXT := 0x24  # ROM slot [0x8030..0x8054) is flush (2026-06-10 relayout)
build/src/kernel/kernel_032.c.o build/non_matching/src/kernel/kernel_032.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_033.c.o build/non_matching/src/kernel/kernel_033.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_034.c.o build/non_matching/src/kernel/kernel_034.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_035.c.o build/non_matching/src/kernel/kernel_035.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_036.c.o build/non_matching/src/kernel/kernel_036.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_036.c.o: TEXT_CLIP_KEEP_ALIGN := 0x98 func_800073DC=0x1C func_800073DC.NON_MATCHING=0x1C  # 0x98: ROM falls through to func_800073F8 at 0x73F8 (2026-06-10 relayout)
build/non_matching/src/kernel/kernel_036.c.o: NON_MATCHING_TEXT_CLIP_KEEP_ALIGN := 0x98 func_800073DC=0x1C func_800073DC.NON_MATCHING=0x1C
build/src/kernel/kernel_037.c.o build/non_matching/src/kernel/kernel_037.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_038.c.o build/non_matching/src/kernel/kernel_038.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_039.c.o build/non_matching/src/kernel/kernel_039.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_040.c.o build/non_matching/src/kernel/kernel_040.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_040.c.o build/non_matching/src/kernel/kernel_040.c.o: POST_COMPILE = $(OBJCOPY) --remove-section=.mdebug $@
build/src/kernel/kernel_040.c.o build/non_matching/src/kernel/kernel_040.c.o: TRUNCATE_TEXT := 0x194
build/non_matching/src/kernel/kernel_040.c.o: NON_MATCHING_TRUNCATE_TEXT := 0x194
build/src/kernel/kernel_041.c.o build/non_matching/src/kernel/kernel_041.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_042.c.o build/non_matching/src/kernel/kernel_042.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_043.c.o build/non_matching/src/kernel/kernel_043.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_044.c.o build/non_matching/src/kernel/kernel_044.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_045.c.o build/non_matching/src/kernel/kernel_045.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_046.c.o build/non_matching/src/kernel/kernel_046.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_047.c.o build/non_matching/src/kernel/kernel_047.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_048.c.o build/non_matching/src/kernel/kernel_048.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_049.c.o build/non_matching/src/kernel/kernel_049.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_050.c.o build/non_matching/src/kernel/kernel_050.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_053.c.o build/non_matching/src/kernel/kernel_053.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_054.c.o build/non_matching/src/kernel/kernel_054.c.o: OPT_FLAGS := -O1
# kernel_022_o1 (func_800087B4 = MIPS insn classifier): IDO 5.3 -O1 island —
# 5.3 emits the target's AND-into-temp + copy-back that 7.1 -O1 folds in
# place. Single-function unit, flipped wholesale (no donor).
build/src/kernel/kernel_022_o1.c.o build/non_matching/src/kernel/kernel_022_o1.c.o: CC := $(IDO53_DIR)/cc
build/src/kernel/kernel_022_o1.c.o build/non_matching/src/kernel/kernel_022_o1.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_002.c.o build/non_matching/src/kernel/kernel_002.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_018.c.o build/non_matching/src/kernel/kernel_018.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_018_o2.c.o build/non_matching/src/kernel/kernel_018_o2.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_006.c.o build/non_matching/src/kernel/kernel_006.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_000_o1.c.o build/non_matching/src/kernel/kernel_000_o1.c.o: OPT_FLAGS := -O1
# kernel_000_b: only C-compiled fn is func_800044CC (PI-event send_mesg), which
# is -O1-shaped (no branch-likely, stack-spilled mq/es). All other fns in this
# unit are INCLUDE_ASM (raw bytes, opt-independent), so -O1 is safe here.
build/src/kernel/kernel_000_b.c.o build/non_matching/src/kernel/kernel_000_b.c.o: OPT_FLAGS := -O1
# 2026-06-10 kernel ROM-order relayout: split-piece opt flags (inherit parent unit -O1)
build/src/kernel/kernel_042_b.c.o build/non_matching/src/kernel/kernel_042_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_027_b.c.o build/non_matching/src/kernel/kernel_027_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_003_b.c.o build/non_matching/src/kernel/kernel_003_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_004_b.c.o build/non_matching/src/kernel/kernel_004_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_011_b.c.o build/non_matching/src/kernel/kernel_011_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_011_c.c.o build/non_matching/src/kernel/kernel_011_c.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_013_b.c.o build/non_matching/src/kernel/kernel_013_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_018_b.c.o build/non_matching/src/kernel/kernel_018_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_018_c.c.o build/non_matching/src/kernel/kernel_018_c.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_018_d.c.o build/non_matching/src/kernel/kernel_018_d.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_018_e.c.o build/non_matching/src/kernel/kernel_018_e.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_018_f.c.o build/non_matching/src/kernel/kernel_018_f.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_018_g.c.o build/non_matching/src/kernel/kernel_018_g.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_020_b.c.o build/non_matching/src/kernel/kernel_020_b.c.o: OPT_FLAGS := -O1
# kernel_020_c (func_80008264 = rmon set-breakpoint): IDO 5.3 -O1 island —
# 5.3 emits the target's 4 temp+move $a1 arg copies that 7.1 -O1 folds in
# place. Single-function unit, flipped wholesale (no donor).
build/src/kernel/kernel_020_c.c.o build/non_matching/src/kernel/kernel_020_c.c.o: CC := $(IDO53_DIR)/cc
build/src/kernel/kernel_020_c.c.o build/non_matching/src/kernel/kernel_020_c.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_022_b.c.o build/non_matching/src/kernel/kernel_022_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_022_c.c.o build/non_matching/src/kernel/kernel_022_c.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_022_d.c.o build/non_matching/src/kernel/kernel_022_d.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_022_e.c.o build/non_matching/src/kernel/kernel_022_e.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_022_f.c.o build/non_matching/src/kernel/kernel_022_f.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_022_g.c.o build/non_matching/src/kernel/kernel_022_g.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_022_h.c.o build/non_matching/src/kernel/kernel_022_h.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_022_i.c.o build/non_matching/src/kernel/kernel_022_i.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_022_o1_b.c.o build/non_matching/src/kernel/kernel_022_o1_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_035_b.c.o build/non_matching/src/kernel/kernel_035_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_054_b.c.o build/non_matching/src/kernel/kernel_054_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_054_c.c.o build/non_matching/src/kernel/kernel_054_c.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_054_d.c.o build/non_matching/src/kernel/kernel_054_d.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_023_b.c.o build/non_matching/src/kernel/kernel_023_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_025_b.c.o build/non_matching/src/kernel/kernel_025_b.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_039_b.c.o build/non_matching/src/kernel/kernel_039_b.c.o: OPT_FLAGS := -O1
# (TRUNCATE_TEXT entries for relayout pieces are below, computed from ROM-truth spans)
build/src/kernel/kernel_027_b.c.o build/non_matching/src/kernel/kernel_027_b.c.o: TRUNCATE_TEXT := 0x58
build/src/kernel/kernel_000_c.c.o build/non_matching/src/kernel/kernel_000_c.c.o: TRUNCATE_TEXT := 0xE0
build/src/kernel/kernel_000_o1.c.o build/non_matching/src/kernel/kernel_000_o1.c.o: TRUNCATE_TEXT := 0x1D8
build/src/kernel/kernel_038.c.o build/non_matching/src/kernel/kernel_038.c.o: TRUNCATE_TEXT := 0x140
build/src/kernel/kernel_017.c.o build/non_matching/src/kernel/kernel_017.c.o: TRUNCATE_TEXT := 0x9C
build/src/kernel/kernel_018.c.o build/non_matching/src/kernel/kernel_018.c.o: TRUNCATE_TEXT := 0x4
build/src/kernel/kernel_049.c.o build/non_matching/src/kernel/kernel_049.c.o: TRUNCATE_TEXT := 0x34
build/src/kernel/kernel_047.c.o build/non_matching/src/kernel/kernel_047.c.o: TRUNCATE_TEXT := 0x3C
build/src/kernel/kernel_018_b.c.o build/non_matching/src/kernel/kernel_018_b.c.o: TRUNCATE_TEXT := 0x448
build/src/kernel/kernel_032.c.o build/non_matching/src/kernel/kernel_032.c.o: TRUNCATE_TEXT := 0x80
build/src/kernel/kernel_018_c.c.o build/non_matching/src/kernel/kernel_018_c.c.o: TRUNCATE_TEXT := 0xC
build/src/kernel/kernel_033.c.o build/non_matching/src/kernel/kernel_033.c.o: TRUNCATE_TEXT := 0xA8
build/src/kernel/kernel_018_e.c.o build/non_matching/src/kernel/kernel_018_e.c.o: TRUNCATE_TEXT := 0x64
build/src/kernel/kernel_018_o2.c.o build/non_matching/src/kernel/kernel_018_o2.c.o: TRUNCATE_TEXT := 0x108
build/src/kernel/kernel_018_f.c.o build/non_matching/src/kernel/kernel_018_f.c.o: TRUNCATE_TEXT := 0x428
build/src/kernel/kernel_034.c.o build/non_matching/src/kernel/kernel_034.c.o: TRUNCATE_TEXT := 0x10C
build/src/kernel/kernel_018_g.c.o build/non_matching/src/kernel/kernel_018_g.c.o: TRUNCATE_TEXT := 0x338
build/src/kernel/kernel_030.c.o build/non_matching/src/kernel/kernel_030.c.o: TRUNCATE_TEXT := 0x128
build/src/kernel/kernel_020.c.o build/non_matching/src/kernel/kernel_020.c.o: TRUNCATE_TEXT := 0x20
build/src/kernel/kernel_020_b.c.o build/non_matching/src/kernel/kernel_020_b.c.o: TRUNCATE_TEXT := 0x7C
build/src/kernel/kernel_020_c.c.o build/non_matching/src/kernel/kernel_020_c.c.o: TRUNCATE_TEXT := 0x254
build/src/kernel/kernel_021.c.o build/non_matching/src/kernel/kernel_021.c.o: TRUNCATE_TEXT := 0x30
build/src/kernel/kernel_022.c.o build/non_matching/src/kernel/kernel_022.c.o: TRUNCATE_TEXT := 0x360
build/src/kernel/kernel_022_o1.c.o build/non_matching/src/kernel/kernel_022_o1.c.o: TRUNCATE_TEXT := 0x94
build/src/kernel/kernel_041.c.o build/non_matching/src/kernel/kernel_041.c.o: TRUNCATE_TEXT := 0x104
build/src/kernel/kernel_054.c.o build/non_matching/src/kernel/kernel_054.c.o: TRUNCATE_TEXT := 0xBC
build/src/kernel/kernel_022_b.c.o build/non_matching/src/kernel/kernel_022_b.c.o: TRUNCATE_TEXT := 0x30
build/src/kernel/kernel_035.c.o build/non_matching/src/kernel/kernel_035.c.o: TRUNCATE_TEXT := 0x68
build/src/kernel/kernel_022_d.c.o build/non_matching/src/kernel/kernel_022_d.c.o: TRUNCATE_TEXT := 0x118
build/src/kernel/kernel_044.c.o build/non_matching/src/kernel/kernel_044.c.o: TRUNCATE_TEXT := 0x150
build/src/kernel/kernel_022_e.c.o build/non_matching/src/kernel/kernel_022_e.c.o: TRUNCATE_TEXT := 0x2AC
build/src/kernel/kernel_054_b.c.o build/non_matching/src/kernel/kernel_054_b.c.o: TRUNCATE_TEXT := 0x16C
build/src/kernel/kernel_022_f.c.o build/non_matching/src/kernel/kernel_022_f.c.o: TRUNCATE_TEXT := 0x1C4
build/src/kernel/kernel_054_c.c.o build/non_matching/src/kernel/kernel_054_c.c.o: TRUNCATE_TEXT := 0x110
build/src/kernel/kernel_022_g.c.o build/non_matching/src/kernel/kernel_022_g.c.o: TRUNCATE_TEXT := 0x118
build/src/kernel/kernel_054_d.c.o build/non_matching/src/kernel/kernel_054_d.c.o: TRUNCATE_TEXT := 0xC4
build/src/kernel/kernel_029.c.o build/non_matching/src/kernel/kernel_029.c.o: TRUNCATE_TEXT := 0x250  # no trim; lowers sh_addralign so it links at 0x80006D0C
# kernel_056: 64-bit libgcc-style helpers; -mips3 so IDO inlines d-arithmetic.
# Post-compile, rewrite e_flags from mips3 (0x20000000) to mips2+noreorder
# (0x10000001) so the linker will merge it with the rest of the kernel (mips2).
build/src/kernel/kernel_056.c.o build/non_matching/src/kernel/kernel_056.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_056.c.o build/non_matching/src/kernel/kernel_056.c.o: MIPSISET := -mips3 -32
build/src/kernel/kernel_056.c.o build/non_matching/src/kernel/kernel_056.c.o: POST_COMPILE = python3 -c "import sys;f=open(sys.argv[1],'r+b');f.seek(0x24);f.write(bytes.fromhex('10000001'));f.close()" $@

# Prologue-stolen successors: splice the duplicate lui+addiu prefix that
# C-emit naturally produces but expected/.o doesn't include in the symbol.
# Format: <func_name>=<bytes_to_remove>. Multiple entries separated by spaces.
# feedback_prologue_stolen_successor_no_recipe.md for context.
ifndef EXPECTED_BASELINE
endif
ifndef EXPECTED_BASELINE
endif
TIMPROC_B1_5A4_DONOR := build/src/timproc_uso_b1/timproc_uso_b1_o0_5A4.c.o
TIMPROC_B1_65C_DONOR := build/src/timproc_uso_b1/timproc_uso_b1_o0_65C.c.o
# timproc_uso_b1/b3_func_000000B0: -O0 twins (317 insns each, all 28 jal
# delays unfilled) inside the -O2 hosts; spliced via -O0 donors like 5A4/65C.
TIMPROC_B1_B0_DONOR := build/src/timproc_uso_b1/timproc_uso_b1_o0_B0.c.o
build/src/timproc_uso_b1/timproc_uso_b1.c.o build/non_matching/src/timproc_uso_b1/timproc_uso_b1.c.o: REPLACE_FUNC_BODY := timproc_uso_b1_func_000000B0=$(TIMPROC_B1_B0_DONOR) timproc_uso_b1_func_000005A4=$(TIMPROC_B1_5A4_DONOR) timproc_uso_b1_func_0000065C=$(TIMPROC_B1_65C_DONOR)
build/src/timproc_uso_b1/timproc_uso_b1_o0_5A4.c.o build/non_matching/src/timproc_uso_b1/timproc_uso_b1_o0_5A4.c.o: OPT_FLAGS := -O0
build/src/timproc_uso_b1/timproc_uso_b1_o0_65C.c.o build/non_matching/src/timproc_uso_b1/timproc_uso_b1_o0_65C.c.o: OPT_FLAGS := -O0
build/src/timproc_uso_b1/timproc_uso_b1_o0_B0.c.o build/non_matching/src/timproc_uso_b1/timproc_uso_b1_o0_B0.c.o: OPT_FLAGS := -O0
# timproc_uso_b3_func_0000065C: byte-identical sibling of the b1 0x65C donor.
# timproc_uso_b3_func_000005A4: masked-shape twin of the b1 0x5A4 donor (same
# 46-insn -O0 wrapper, differs only in two immediates 0x1->0x2).
TIMPROC_B3_65C_DONOR := build/src/timproc_uso_b3/timproc_uso_b3_o0_65C.c.o
TIMPROC_B3_5A4_DONOR := build/src/timproc_uso_b3/timproc_uso_b3_o0_5A4.c.o
TIMPROC_B3_B0_DONOR := build/src/timproc_uso_b3/timproc_uso_b3_o0_B0.c.o
build/src/timproc_uso_b3/timproc_uso_b3.c.o build/non_matching/src/timproc_uso_b3/timproc_uso_b3.c.o: REPLACE_FUNC_BODY := timproc_uso_b3_func_000000B0=$(TIMPROC_B3_B0_DONOR) timproc_uso_b3_func_000005A4=$(TIMPROC_B3_5A4_DONOR) timproc_uso_b3_func_0000065C=$(TIMPROC_B3_65C_DONOR)
# timproc_uso_b3_func_0000217C: byte-correct real-def whose target symbol has an extra
# trailing alignment nop (target 0x34/13w vs build 0x30/12w). Grow the non_matching
# symbol with one all-zero word so objdiff scores 13w. ROM-neutral (non_matching .o).
build/non_matching/src/timproc_uso_b3/timproc_uso_b3.c.o: NON_MATCHING_SUFFIX_BYTES_FORCE := timproc_uso_b3_func_0000217C=0x00000000
build/src/timproc_uso_b3/timproc_uso_b3_o0_65C.c.o build/non_matching/src/timproc_uso_b3/timproc_uso_b3_o0_65C.c.o: OPT_FLAGS := -O0
build/src/timproc_uso_b3/timproc_uso_b3_o0_5A4.c.o build/non_matching/src/timproc_uso_b3/timproc_uso_b3_o0_5A4.c.o: OPT_FLAGS := -O0
build/src/timproc_uso_b3/timproc_uso_b3_o0_B0.c.o build/non_matching/src/timproc_uso_b3/timproc_uso_b3_o0_B0.c.o: OPT_FLAGS := -O0
# game_libs_func_0006C8AC: byte-identical twin of kernel func_80002BA8 (64-bit
# divmod). Needs -O1 -mips3 (ddivu/ld/sd), which game_libs_post1b2c (default
# -O2 -mips2) can't use TU-wide, so splice the -O1 -mips3 donor's 0x60 body
# (no relocs) in via REPLACE_FUNC_BODY. Size matches target so TRUNCATE_TEXT
# (0x3D94) boundary is unaffected.
GAMELIBS_6C8AC_DONOR := build/src/game_libs/game_libs_o1_6C8AC.c.o
# Masked-twin libultra helpers in post1b2c, byte-exact at IDO 5.3 -O1 (default
# unit is -O2). Ported from matched kernel twins, spliced via REPLACE_FUNC_BODY
# (donor relocs to gl_func_00000000 / D_00000000 placeholders imported).
GAMELIBS_6C9F4_DONOR := build/src/game_libs/game_libs_ido53_6C9F4.c.o
GAMELIBS_6F534_DONOR := build/src/game_libs/game_libs_ido53_6F534.c.o
GAMELIBS_6CCD4_DONOR := build/src/game_libs/game_libs_ido53_6CCD4.c.o
GAMELIBS_6E1A4_DONOR := build/src/game_libs/game_libs_ido53_6E1A4.c.o
GAMELIBS_6FFE4_DONOR := build/src/game_libs/game_libs_ido53_6FFE4.c.o
build/src/game_libs/game_libs_ido53_6E1A4.c.o build/non_matching/src/game_libs/game_libs_ido53_6E1A4.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6E1A4.c.o build/non_matching/src/game_libs/game_libs_ido53_6E1A4.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6FFE4.c.o build/non_matching/src/game_libs/game_libs_ido53_6FFE4.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6FFE4.c.o build/non_matching/src/game_libs/game_libs_ido53_6FFE4.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6C9F4.c.o build/non_matching/src/game_libs/game_libs_ido53_6C9F4.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6C9F4.c.o build/non_matching/src/game_libs/game_libs_ido53_6C9F4.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6F534.c.o build/non_matching/src/game_libs/game_libs_ido53_6F534.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6F534.c.o build/non_matching/src/game_libs/game_libs_ido53_6F534.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6CCD4.c.o build/non_matching/src/game_libs/game_libs_ido53_6CCD4.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6CCD4.c.o build/non_matching/src/game_libs/game_libs_ido53_6CCD4.c.o: OPT_FLAGS := -O1
# 64-bit libgcc helper family (self-contained, 0 relocs), byte-twins of the
# matched kernel_056.c funcs. -O2 -mips3 so IDO inlines d-arithmetic.
GAMELIBS_6C740_DONOR := build/src/game_libs/game_libs_mips3_6C740.c.o
GAMELIBS_6B7A0_DONOR := build/src/game_libs/game_libs_o1_6B7A0.c.o
GAMELIBS_6C11C_DONOR := build/src/game_libs/game_libs_ido53_6C11C.c.o
GAMELIBS_6FAD4_DONOR := build/src/game_libs/game_libs_o1_6FAD4.c.o
GAMELIBS_71708_DONOR := build/src/game_libs/game_libs_ido53_71708.c.o
GAMELIBS_73824_DONOR := build/src/game_libs/game_libs_o1_73824.c.o
GAMELIBS_6BF34_DONOR := build/src/game_libs/game_libs_o1_6BF34.c.o
GAMELIBS_6C1B8_DONOR := build/src/game_libs/game_libs_ido53_6C1B8.c.o
GAMELIBS_6D0F4_DONOR := build/src/game_libs/game_libs_ido53_6D0F4.c.o
# func_80002530 = osInitialize: IDO 5.3 -O1 island inside the 7.1 -O2
# kernel_000 unit (proven exact 284/284 standalone; see donor header).
KERNEL000_2530_DONOR := build/src/kernel/kernel_000_ido53_2530.c.o
# func_80005520 = kernel osCreatePiManager (KMC 2-worker variant): TU-defined
# D_8000A450 shared-$at donor, proven exact 115/115 standalone (see header).
KERNEL006_5520_DONOR := build/src/kernel/kernel_006_o1_5520.c.o
# func_800058C0 = libultra osCartRomInit: TU-defined D_8001B656 2-byte-struct
# shared-$at donor, proven exact 60/60 standalone (see header).
KERNEL008_58C0_DONOR := build/src/kernel/kernel_008_o1_58C0.c.o
# func_80009AB0 = libultra osEPiRawWriteIo (spans former 9AB0+9B60 fragments):
# baked-constant IO_REG donor, proven exact 100/100 standalone (see header).
KERNEL024_9AB0_DONOR := build/src/kernel/kernel_024_o1_9AB0.c.o
# func_80007564 = rmon thread-list handler: IDO 5.3 -O1 island inside the
# 7.1 -O1 kernel_018_f unit (7.1 folds the tail sll with no temp - 1 insn
# short; 5.3 emits the target's sll-temp+move). Proven 77/77 standalone.
KERNEL018F_7564_DONOR := build/src/kernel/kernel_018_f_ido53_7564.c.o
# func_800070A0 = rmon word-streamer: IDO 5.3 -O1 island inside the 7.1 -O1
# kernel_018_d unit (int* post-increment materializes old-p; 7.1 folds -4
# in place - 6-word permuter-immune residual was version-specific).
KERNEL018D_70A0_DONOR := build/src/kernel/kernel_018_d_ido53_70A0.c.o
# func_8000698C = rmon memory-write handler: IDO 5.3 -O1 island inside the
# 7.1 -O1 kernel_018_b unit (deferred prologue `or s0,t6` commit +
# register-var dead-home frame map; 7.1 folds the param load into s0 and
# top-flushes the locals +4). Proven 147/147 standalone.
KERNEL018B_698C_DONOR := build/src/kernel/kernel_018_b_ido53_698C.c.o
GAMELIBS_6DA74_DONOR := build/src/game_libs/game_libs_o1_6DA74.c.o
# -O1 island batch 4 (2026-07-09): libultra pfsisplug.c TU (6D554 =
# osPfsIsPlug at 7.1 -O1; 6D6F4 = __osPfsRequestData + 6D7CC =
# __osPfsGetInitData at IDO 5.3 -O1, $at struct-copy discriminator) plus the
# word-identical custom contramread-family twins 6CDB4/6CF54 (one 5.3 -O1
# donor TU defines both, 6C740 precedent). 6D7CC's donor absorbs the 2-word
# orphan game_libs_func_0006D7C4 (hoisted lui/lbu __osMaxControllers head).
GAMELIBS_6D554_DONOR := build/src/game_libs/game_libs_o1_6D554.c.o
GAMELIBS_6D6F4_DONOR := build/src/game_libs/game_libs_ido53_6D6F4.c.o
GAMELIBS_6D7CC_DONOR := build/src/game_libs/game_libs_ido53_6D7CC.c.o
GAMELIBS_6CDB4_DONOR := build/src/game_libs/game_libs_ido53_6CDB4.c.o
# -O1 island batch 5 (2026-07-09): the flagged controller-pak/SI leads.
# 6CAD4 = __osSiRawStartDma, 6CB84 = __osSpRawStartDma, 6CC64 = osViBlack,
# 6D270 = osMotorInit (libultra verbatim; each donor header has the proof).
# All four are word-exact at BOTH 7.1 -O1 and 5.3 -O1 -> plain -O1 donors
# (default 7.1 cc, no CC override). 6CAD4/6CB84 jr-ra delay nops merged from
# their _pad.s sidecars into the .s (absorption prerequisite).
GAMELIBS_6CAD4_DONOR := build/src/game_libs/game_libs_o1_6CAD4.c.o
GAMELIBS_6CB84_DONOR := build/src/game_libs/game_libs_o1_6CB84.c.o
GAMELIBS_6CC64_DONOR := build/src/game_libs/game_libs_o1_6CC64.c.o
GAMELIBS_6D270_DONOR := build/src/game_libs/game_libs_o1_6D270.c.o
build/src/game_libs/game_libs_o1_6CAD4.c.o build/non_matching/src/game_libs/game_libs_o1_6CAD4.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_6CB84.c.o build/non_matching/src/game_libs/game_libs_o1_6CB84.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_6CC64.c.o build/non_matching/src/game_libs/game_libs_o1_6CC64.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_6D270.c.o build/non_matching/src/game_libs/game_libs_o1_6D270.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_6D554.c.o build/non_matching/src/game_libs/game_libs_o1_6D554.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6D6F4.c.o build/non_matching/src/game_libs/game_libs_ido53_6D6F4.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6D6F4.c.o build/non_matching/src/game_libs/game_libs_ido53_6D6F4.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6D7CC.c.o build/non_matching/src/game_libs/game_libs_ido53_6D7CC.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6D7CC.c.o build/non_matching/src/game_libs/game_libs_ido53_6D7CC.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6CDB4.c.o build/non_matching/src/game_libs/game_libs_ido53_6CDB4.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6CDB4.c.o build/non_matching/src/game_libs/game_libs_ido53_6CDB4.c.o: OPT_FLAGS := -O1
# -O1 island batch 6 (2026-07-10): the AI/VI/EPI libultra block, all IDO
# 5.3 -O1 (each donor header has the proof + the 5.3-vs-7.1 discriminator).
# 70040 = osAiSetFrequency (absorbs orphan 70030), 730CC = osEPiRawReadIo
# (absorbs 730C4), 7369C = osEPiRawWriteIo (absorbs 73694), 70B04 =
# __osViInit (pad.s deleted; delay nop in donor + SUFFIX word), 70C44 =
# __osViSwapContext, 73310 = osViGetCurrentField (leading pad nop ->
# SUFFIX on 732C4).
GAMELIBS_70040_DONOR := build/src/game_libs/game_libs_ido53_70040.c.o
GAMELIBS_730CC_DONOR := build/src/game_libs/game_libs_ido53_730CC.c.o
GAMELIBS_7369C_DONOR := build/src/game_libs/game_libs_ido53_7369C.c.o
GAMELIBS_70B04_DONOR := build/src/game_libs/game_libs_ido53_70B04.c.o
GAMELIBS_70C44_DONOR := build/src/game_libs/game_libs_ido53_70C44.c.o
GAMELIBS_73310_DONOR := build/src/game_libs/game_libs_ido53_73310.c.o
build/src/game_libs/game_libs_ido53_70040.c.o build/non_matching/src/game_libs/game_libs_ido53_70040.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_70040.c.o build/non_matching/src/game_libs/game_libs_ido53_70040.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_730CC.c.o build/non_matching/src/game_libs/game_libs_ido53_730CC.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_730CC.c.o build/non_matching/src/game_libs/game_libs_ido53_730CC.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_7369C.c.o build/non_matching/src/game_libs/game_libs_ido53_7369C.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_7369C.c.o build/non_matching/src/game_libs/game_libs_ido53_7369C.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_70B04.c.o build/non_matching/src/game_libs/game_libs_ido53_70B04.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_70B04.c.o build/non_matching/src/game_libs/game_libs_ido53_70B04.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_70C44.c.o build/non_matching/src/game_libs/game_libs_ido53_70C44.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_70C44.c.o build/non_matching/src/game_libs/game_libs_ido53_70C44.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_73310.c.o build/non_matching/src/game_libs/game_libs_ido53_73310.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_73310.c.o build/non_matching/src/game_libs/game_libs_ido53_73310.c.o: OPT_FLAGS := -O1
# Island stragglers (2026-07-10): 6F088 = osLeoDiskInit, IDO 5.3 -O1
# (absorbs game_libs_func_0006F038 = the hoisted pre-prologue head; true
# entry 0x6F044; 3 pad nops 0x6F038/3C/40 via SUFFIX on gl_func_0006EF64).
GAMELIBS_6F088_DONOR := build/src/game_libs/game_libs_ido53_6F088.c.o
build/src/game_libs/game_libs_ido53_6F088.c.o build/non_matching/src/game_libs/game_libs_ido53_6F088.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6F088.c.o build/non_matching/src/game_libs/game_libs_ido53_6F088.c.o: OPT_FLAGS := -O1
# 6F38C = __osSpDeviceBusy + 6F3BC = __osSiDeviceBusy (hoisted-head
# absorptions of the 6F380/6F3B0 fragments; pads via SUFFIX below).
GAMELIBS_6F38C_DONOR := build/src/game_libs/game_libs_ido53_6F38C.c.o
GAMELIBS_6F3BC_DONOR := build/src/game_libs/game_libs_ido53_6F3BC.c.o
build/src/game_libs/game_libs_ido53_6F38C.c.o build/non_matching/src/game_libs/game_libs_ido53_6F38C.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6F38C.c.o build/non_matching/src/game_libs/game_libs_ido53_6F38C.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6F3BC.c.o build/non_matching/src/game_libs/game_libs_ido53_6F3BC.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6F3BC.c.o build/non_matching/src/game_libs/game_libs_ido53_6F3BC.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_mips3_6C740.c.o build/non_matching/src/game_libs/game_libs_mips3_6C740.c.o: MIPSISET := -mips3 -32
build/src/game_libs/game_libs_post1b2c.c.o build/non_matching/src/game_libs/game_libs_post1b2c.c.o: REPLACE_FUNC_BODY := game_libs_func_0006C8AC=$(GAMELIBS_6C8AC_DONOR) gl_func_0006C90C=$(GAMELIBS_6C8AC_DONOR) gl_func_0006C9F4=$(GAMELIBS_6C9F4_DONOR) gl_func_0006F534=$(GAMELIBS_6F534_DONOR) gl_func_0006CCD4=$(GAMELIBS_6CCD4_DONOR) gl_func_0006E1A4=$(GAMELIBS_6E1A4_DONOR) gl_func_0006FFE4=$(GAMELIBS_6FFE4_DONOR) gl_func_0006FAD4=$(GAMELIBS_6FAD4_DONOR) game_libs_func_0006C740=$(GAMELIBS_6C740_DONOR) game_libs_func_0006C77C=$(GAMELIBS_6C740_DONOR) game_libs_func_0006C7B8=$(GAMELIBS_6C740_DONOR) game_libs_func_0006C7E4=$(GAMELIBS_6C740_DONOR) game_libs_func_0006C820=$(GAMELIBS_6C740_DONOR) game_libs_func_0006C87C=$(GAMELIBS_6C740_DONOR) game_libs_func_0006C9A8=$(GAMELIBS_6C740_DONOR) gl_func_0006D0F4=$(GAMELIBS_6D0F4_DONOR) gl_func_0006DA74=$(GAMELIBS_6DA74_DONOR) gl_func_0006CDB4=$(GAMELIBS_6CDB4_DONOR) gl_func_0006CF54=$(GAMELIBS_6CDB4_DONOR) gl_func_0006D554=$(GAMELIBS_6D554_DONOR) gl_func_0006D6F4=$(GAMELIBS_6D6F4_DONOR) gl_func_0006D7CC=$(GAMELIBS_6D7CC_DONOR) gl_func_0006CAD4=$(GAMELIBS_6CAD4_DONOR) gl_func_0006CB84=$(GAMELIBS_6CB84_DONOR) gl_func_0006CC64=$(GAMELIBS_6CC64_DONOR) gl_func_0006D270=$(GAMELIBS_6D270_DONOR) gl_func_00070040=$(GAMELIBS_70040_DONOR) gl_func_0006F088=$(GAMELIBS_6F088_DONOR) gl_func_0006F38C=$(GAMELIBS_6F38C_DONOR) gl_func_0006F3BC=$(GAMELIBS_6F3BC_DONOR)
# gl_func_0006EF08: -O2 body emits the 0x58 target function (jr-ra + delay nop);
# append the 1-word all-zero alignment pad at 0x6EF60 so gl_func_0006EF64 sits at
# +0x5C. FORCE because the function ends in the natural jr-ra;nop epilogue.
build/src/game_libs/game_libs_post1b2c.c.o: SUFFIX_BYTES_FORCE := gl_func_0006EF08=0x00000000 gl_func_0006CAD4=0x00000000 gl_func_0006CB84=0x00000000 gl_func_0006FFE4=0x00000000 gl_func_0006EF64=0x00000000,0x00000000,0x00000000 game_libs_func_0006F35C=0x00000000 gl_func_0006F38C=0x00000000 gl_func_0006F3BC=0x00000000
build/non_matching/src/game_libs/game_libs_post1b2c.c.o: NON_MATCHING_SUFFIX_BYTES_FORCE := gl_func_0006EF08=0x00000000 gl_func_0006CAD4=0x00000000 gl_func_0006CB84=0x00000000 gl_func_0006FFE4=0x00000000 gl_func_0006EF64=0x00000000,0x00000000,0x00000000 game_libs_func_0006F35C=0x00000000 gl_func_0006F38C=0x00000000 gl_func_0006F3BC=0x00000000
# batch 6: 70B04 alignment word at 0x70C40 (donor delay nop covers 0x70C3C,
# _pad.s sidecar deleted); 732C4 pad nop at 0x73310 (osViGetCurrentField true
# entry = 0x73314 after the 73310 orphan-nop absorption).
build/src/game_libs/game_libs_post1c.c.o: SUFFIX_BYTES_FORCE := gl_func_00070B04=0x00000000 gl_func_00070C44=0x00000000
build/non_matching/src/game_libs/game_libs_post1c.c.o: NON_MATCHING_SUFFIX_BYTES_FORCE := gl_func_00070B04=0x00000000 gl_func_00070C44=0x00000000
build/src/game_libs/game_libs_post2b_c.c.o: SUFFIX_BYTES_FORCE := gl_func_000732C4=0x00000000
build/non_matching/src/game_libs/game_libs_post2b_c.c.o: NON_MATCHING_SUFFIX_BYTES_FORCE := gl_func_000732C4=0x00000000
build/src/game_libs/game_libs_o1_6C8AC.c.o build/non_matching/src/game_libs/game_libs_o1_6C8AC.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_6C8AC.c.o build/non_matching/src/game_libs/game_libs_o1_6C8AC.c.o: MIPSISET := -mips3 -32
# More masked-twin libultra helpers (other parent units), IDO 5.3 -O1.
GAMELIBS_6BA7C_DONOR := build/src/game_libs/game_libs_ido53_6BA7C.c.o
GAMELIBS_70634_DONOR := build/src/game_libs/game_libs_ido53_70634.c.o
GAMELIBS_747F4_DONOR := build/src/game_libs/game_libs_ido53_747F4.c.o
GAMELIBS_732C4_DONOR := build/src/game_libs/game_libs_ido53_732C4.c.o
build/src/game_libs/game_libs_ido53_6BA7C.c.o build/non_matching/src/game_libs/game_libs_ido53_6BA7C.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6BA7C.c.o build/non_matching/src/game_libs/game_libs_ido53_6BA7C.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_70634.c.o build/non_matching/src/game_libs/game_libs_ido53_70634.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_70634.c.o build/non_matching/src/game_libs/game_libs_ido53_70634.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_747F4.c.o build/non_matching/src/game_libs/game_libs_ido53_747F4.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_747F4.c.o build/non_matching/src/game_libs/game_libs_ido53_747F4.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_732C4.c.o build/non_matching/src/game_libs/game_libs_ido53_732C4.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_732C4.c.o build/non_matching/src/game_libs/game_libs_ido53_732C4.c.o: OPT_FLAGS := -O1
GAMELIBS_69E04_DONOR := build/src/game_libs/game_libs_ido53_69E04.c.o
GAMELIBS_74C04_DONOR := build/src/game_libs/game_libs_ido53_74C04.c.o
# gl_func_0006AF0C: 14-insn list-unlink leaf; exact only at IDO 7.1 -O1 -g3
# (post1b is -O2). Reloc-free donor spliced in, like 6BA7C/69E04. Built by an
# explicit direct-CC rule (below "all"): asm-processor rejects "-O1 -g3"
# (only -O2 -g3), and the donor has no GLOBAL_ASM so it would be a no-op.
GAMELIBS_6AF0C_DONOR := build/src/game_libs/game_libs_o1_6AF0C.c.o
# 0x6A09C..0x6BAD4 -O1 island batch (2026-07-08): plain -O1 donors (no -g3, so
# the normal asm-processor rule works — only "-O1 -g3" is rejected). Each is
# byte-exact standalone at -O1; spliced over the -O2 stand-ins in post1b like
# 6AF0C. A304's donor carries real HI16/LO16 relocs vs D_00041710 (=0x41710 in
# undefined_syms_auto.txt) which link to the target's baked lui 4/addiu 0x1710.
GAMELIBS_6A304_DONOR := build/src/game_libs/game_libs_o1_6A304.c.o
GAMELIBS_6AF44_DONOR := build/src/game_libs/game_libs_o1_6AF44.c.o
GAMELIBS_6B880_DONOR := build/src/game_libs/game_libs_o1_6B880.c.o
GAMELIBS_6B974_DONOR := build/src/game_libs/game_libs_o1_6B974.c.o
GAMELIBS_6BAD4_DONOR := build/src/game_libs/game_libs_o1_6BAD4.c.o
build/src/game_libs/game_libs_o1_6A304.c.o build/non_matching/src/game_libs/game_libs_o1_6A304.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_6AF44.c.o build/non_matching/src/game_libs/game_libs_o1_6AF44.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_6B880.c.o build/non_matching/src/game_libs/game_libs_o1_6B880.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_6B974.c.o build/non_matching/src/game_libs/game_libs_o1_6B974.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_6BAD4.c.o build/non_matching/src/game_libs/game_libs_o1_6BAD4.c.o: OPT_FLAGS := -O1
# 0x6B7A0..0x73824 -O1 island batch 2 (2026-07-08): same recipe. 6B7A0's donor
# absorbs the 2-word orphan game_libs_func_0006B798 (stolen lui/lw prologue) —
# its INCLUDE_ASM is removed and the donor's 58 words cover 0x6B798..0x6B880;
# its baked `jal 0x7FEEC` links via gl_ref_0007FEEC (undefined_syms_auto.txt).
build/src/game_libs/game_libs_o1_6B7A0.c.o build/non_matching/src/game_libs/game_libs_o1_6B7A0.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6C11C.c.o build/non_matching/src/game_libs/game_libs_ido53_6C11C.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6C11C.c.o build/non_matching/src/game_libs/game_libs_ido53_6C11C.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_6FAD4.c.o build/non_matching/src/game_libs/game_libs_o1_6FAD4.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_71708.c.o build/non_matching/src/game_libs/game_libs_ido53_71708.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_71708.c.o build/non_matching/src/game_libs/game_libs_ido53_71708.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_73824.c.o build/non_matching/src/game_libs/game_libs_o1_73824.c.o: OPT_FLAGS := -O1
# -O1 island batch 3 (2026-07-09): 6BF34 + 6DA74 match at plain 7.1 -O1;
# 6C1B8 + 6D0F4 need IDO 5.3 -O1 ($at as the swl/swr struct-copy scratch,
# the documented 5.3-vs-7.1 discriminator). 6DA74 = osCreatePiManager
# (libreultra pimgr.c); its TU-defined DevMgr produces the shared-lui $at
# store clusters (see the donor header).
build/src/game_libs/game_libs_o1_6BF34.c.o build/non_matching/src/game_libs/game_libs_o1_6BF34.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_6C1B8.c.o build/non_matching/src/game_libs/game_libs_ido53_6C1B8.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6C1B8.c.o build/non_matching/src/game_libs/game_libs_ido53_6C1B8.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_000_ido53_2530.c.o build/non_matching/src/kernel/kernel_000_ido53_2530.c.o: CC := $(IDO53_DIR)/cc
build/src/kernel/kernel_000_ido53_2530.c.o build/non_matching/src/kernel/kernel_000_ido53_2530.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_000.c.o build/non_matching/src/kernel/kernel_000.c.o: REPLACE_FUNC_BODY := func_80002530=$(KERNEL000_2530_DONOR)
build/src/kernel/kernel_018_f_ido53_7564.c.o build/non_matching/src/kernel/kernel_018_f_ido53_7564.c.o: CC := $(IDO53_DIR)/cc
build/src/kernel/kernel_018_f_ido53_7564.c.o build/non_matching/src/kernel/kernel_018_f_ido53_7564.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_018_f.c.o build/non_matching/src/kernel/kernel_018_f.c.o: REPLACE_FUNC_BODY := func_80007564=$(KERNEL018F_7564_DONOR)
build/src/kernel/kernel_018_d_ido53_70A0.c.o build/non_matching/src/kernel/kernel_018_d_ido53_70A0.c.o: CC := $(IDO53_DIR)/cc
build/src/kernel/kernel_018_d_ido53_70A0.c.o build/non_matching/src/kernel/kernel_018_d_ido53_70A0.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_018_d.c.o build/non_matching/src/kernel/kernel_018_d.c.o: REPLACE_FUNC_BODY := func_800070A0=$(KERNEL018D_70A0_DONOR)
build/src/kernel/kernel_018_b_ido53_698C.c.o build/non_matching/src/kernel/kernel_018_b_ido53_698C.c.o: CC := $(IDO53_DIR)/cc
build/src/kernel/kernel_018_b_ido53_698C.c.o build/non_matching/src/kernel/kernel_018_b_ido53_698C.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_018_b.c.o build/non_matching/src/kernel/kernel_018_b.c.o: REPLACE_FUNC_BODY := func_8000698C=$(KERNEL018B_698C_DONOR)
build/src/kernel/kernel_006_o1_5520.c.o build/non_matching/src/kernel/kernel_006_o1_5520.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_006.c.o build/non_matching/src/kernel/kernel_006.c.o: REPLACE_FUNC_BODY := func_80005520=$(KERNEL006_5520_DONOR)
# kernel_006: the promoted 5520 C body compiles +0x20 over the 0x1CC slot;
# the splice shrinks it back to 0x1CC leaving a 4-byte align-pad tail
# residue (.text 0x504 vs ROM-true 0x500) — trim it.
build/src/kernel/kernel_006.c.o: TRUNCATE_TEXT := 0x500
build/src/kernel/kernel_008_o1_58C0.c.o build/non_matching/src/kernel/kernel_008_o1_58C0.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_008.c.o build/non_matching/src/kernel/kernel_008.c.o: REPLACE_FUNC_BODY := func_800058C0=$(KERNEL008_58C0_DONOR)
build/src/kernel/kernel_024_o1_9AB0.c.o build/non_matching/src/kernel/kernel_024_o1_9AB0.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_024.c.o build/non_matching/src/kernel/kernel_024.c.o: REPLACE_FUNC_BODY := func_80009AB0=$(KERNEL024_9AB0_DONOR)
# kernel_024: the -O2 host body + splice leaves a 4-byte align-pad tail
# residue (.text 0x194 vs ROM-true 0x190) - trim it.
build/src/kernel/kernel_024.c.o build/non_matching/src/kernel/kernel_024.c.o: TRUNCATE_TEXT := 0x190
# kernel_000 tail: C-body path leaves a 4-byte alignment residue after the
# func_800029A0_pad block (.text 0x29B4 vs ROM-true 0x29B0) — trim it.
build/src/kernel/kernel_000.c.o build/non_matching/src/kernel/kernel_000.c.o: TRUNCATE_TEXT := 0x29B0
build/src/game_libs/game_libs_ido53_6D0F4.c.o build/non_matching/src/game_libs/game_libs_ido53_6D0F4.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_6D0F4.c.o build/non_matching/src/game_libs/game_libs_ido53_6D0F4.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_o1_6DA74.c.o build/non_matching/src/game_libs/game_libs_o1_6DA74.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_post1b.c.o build/non_matching/src/game_libs/game_libs_post1b.c.o: REPLACE_FUNC_BODY := gl_func_0006BA7C=$(GAMELIBS_6BA7C_DONOR) gl_func_00069E04=$(GAMELIBS_69E04_DONOR) gl_func_0006AF0C=$(GAMELIBS_6AF0C_DONOR) gl_func_0006A304=$(GAMELIBS_6A304_DONOR) gl_func_0006AF44=$(GAMELIBS_6AF44_DONOR) gl_func_0006B880=$(GAMELIBS_6B880_DONOR) gl_func_0006B974=$(GAMELIBS_6B974_DONOR) gl_func_0006BAD4=$(GAMELIBS_6BAD4_DONOR) gl_func_0006B7A0=$(GAMELIBS_6B7A0_DONOR)
build/src/game_libs/game_libs_post1b2.c.o build/non_matching/src/game_libs/game_libs_post1b2.c.o: REPLACE_FUNC_BODY := gl_func_0006C11C=$(GAMELIBS_6C11C_DONOR) gl_func_0006BF34=$(GAMELIBS_6BF34_DONOR) gl_func_0006C1B8=$(GAMELIBS_6C1B8_DONOR)
GAMELIBS_70FCC_DONOR := build/src/game_libs/game_libs_o2_70FCC.c.o
build/src/game_libs/game_libs_post2.c.o build/non_matching/src/game_libs/game_libs_post2.c.o: REPLACE_FUNC_BODY := gl_func_00071708=$(GAMELIBS_71708_DONOR) game_libs_func_00070FCC=$(GAMELIBS_70FCC_DONOR)
# gl_func_00067370: -O2 body byte-exact; append the 1-word all-zero inter-fn ROM
# pad at 0x67390 (folded into the 0x24 .s symbol). FORCE: ends jr-ra;nop.
build/src/game_libs/game_libs_post1b.c.o: SUFFIX_BYTES_FORCE := gl_func_00067370=0x00000000
build/non_matching/src/game_libs/game_libs_post1b.c.o: NON_MATCHING_SUFFIX_BYTES_FORCE := gl_func_00067370=0x00000000
build/src/game_libs/game_libs_post2b_e.c.o build/non_matching/src/game_libs/game_libs_post2b_e.c.o: REPLACE_FUNC_BODY := gl_func_00074C04=$(GAMELIBS_74C04_DONOR)
build/src/game_libs/game_libs_post1c.c.o build/non_matching/src/game_libs/game_libs_post1c.c.o: REPLACE_FUNC_BODY := gl_func_00070634=$(GAMELIBS_70634_DONOR) gl_func_00070B04=$(GAMELIBS_70B04_DONOR) gl_func_00070C44=$(GAMELIBS_70C44_DONOR)
build/src/game_libs/game_libs_post2b_d.c.o build/non_matching/src/game_libs/game_libs_post2b_d.c.o: REPLACE_FUNC_BODY := gl_func_000747F4=$(GAMELIBS_747F4_DONOR) gl_func_00073824=$(GAMELIBS_73824_DONOR) gl_func_0007369C=$(GAMELIBS_7369C_DONOR)
build/src/game_libs/game_libs_post2b_c.c.o build/non_matching/src/game_libs/game_libs_post2b_c.c.o: REPLACE_FUNC_BODY := gl_func_000732C4=$(GAMELIBS_732C4_DONOR) gl_func_000730CC=$(GAMELIBS_730CC_DONOR) game_libs_func_00073310=$(GAMELIBS_73310_DONOR)
# arcproc_uso_func_00000748: byte-identical sibling of mgrproc_uso_func_000009A8.
# arcproc is non-Yay0 but the donor-splice still applies (relocatable USO: a
# function's bytes are link-offset-independent, so the size change doesn't break
# downstream funcs). Avoids a 3-way file split of tail1 around a mid-file fn.
ARCPROC_748_DONOR := build/src/arcproc_uso/arcproc_uso_o0_748.c.o
ARCPROC_688_DONOR := build/src/arcproc_uso/arcproc_uso_o0_688.c.o
build/src/arcproc_uso/arcproc_uso_tail1.c.o build/non_matching/src/arcproc_uso/arcproc_uso_tail1.c.o: REPLACE_FUNC_BODY := arcproc_uso_func_00000688=$(ARCPROC_688_DONOR) arcproc_uso_func_00000748=$(ARCPROC_748_DONOR)
# 0x2740 = exact len of the tail1 region (0x240..0x2980); clips IDO's
# trailing pad word so arcproc_uso emits at its original segment length.
build/src/arcproc_uso/arcproc_uso_tail1.c.o: TRUNCATE_TEXT := 0x2740
build/src/arcproc_uso/arcproc_uso_o0_748.c.o build/non_matching/src/arcproc_uso/arcproc_uso_o0_748.c.o: OPT_FLAGS := -O0
build/src/arcproc_uso/arcproc_uso_o0_688.c.o build/non_matching/src/arcproc_uso/arcproc_uso_o0_688.c.o: OPT_FLAGS := -O0

# mgrproc_uso (Yay0-compressed): a contiguous -O0 run at the block start
# (func_00000000/4C/B0, 0x0..0xF8) is carved into its own sub-unit (region 0).
# The -O2 main object (region 1) supplies the rest. Both .text sections are
# objcopy'd to raw binary and concatenated in address order before crunch64
# compression (see the block1 yay0 rule). This is the Yay0 file-split infra:
# binary-concat-before-compress, the analogue of the direct multi-.o link used
# by the non-Yay0 USOs (bootup/arcproc).
build/src/mgrproc_uso/mgrproc_uso_o0_0.c.o build/non_matching/src/mgrproc_uso/mgrproc_uso_o0_0.c.o: OPT_FLAGS := -O0
build/src/mgrproc_uso/mgrproc_uso_o0_0.c.o: TRUNCATE_TEXT := 0x140
build/non_matching/src/mgrproc_uso/mgrproc_uso_o0_0.c.o: NON_MATCHING_TRUNCATE_TEXT := 0x140
# region1 = head [0xF8,0x19C); matching build is exactly 0xA4. Built -O2 -g3 so
# the return-0 leaves func_0000015C/_00000188 emit their UNFILLED jr-delay form
# (move v0,zero; jr ra; nop); empty stubs + INCLUDE_ASM funcs are -g3-invariant.
# No NON_MATCHING_TRUNCATE_TEXT (NM bodies diverge; objdiff scores per-function).
build/src/mgrproc_uso/mgrproc_uso_head.c.o build/non_matching/src/mgrproc_uso/mgrproc_uso_head.c.o: OPT_FLAGS := -O2 -g3
build/src/mgrproc_uso/mgrproc_uso_head.c.o: TRUNCATE_TEXT := 0x5C
# region2 = -O0 run [0x19C,0xAE0) (func_0000019C..A14; func_000009A8 matched).
build/src/mgrproc_uso/mgrproc_uso_o0_19C.c.o build/non_matching/src/mgrproc_uso/mgrproc_uso_o0_19C.c.o: OPT_FLAGS := -O0
build/src/mgrproc_uso/mgrproc_uso_o0_19C.c.o: TRUNCATE_TEXT := 0x938

# timproc_uso_b1 / b3 (Yay0-compressed): same opening -O0 run (int-reader 0x4C +
# Quad4-reader 0x64 = 0xB0) carved into a region-0 sub-unit, same concat infra.
build/src/timproc_uso_b1/timproc_uso_b1_o0_0.c.o build/non_matching/src/timproc_uso_b1/timproc_uso_b1_o0_0.c.o: OPT_FLAGS := -O0
build/src/timproc_uso_b1/timproc_uso_b1_o0_0.c.o: TRUNCATE_TEXT := 0xB0
build/non_matching/src/timproc_uso_b1/timproc_uso_b1_o0_0.c.o: NON_MATCHING_TRUNCATE_TEXT := 0xB0
build/src/timproc_uso_b3/timproc_uso_b3_o0_0.c.o build/non_matching/src/timproc_uso_b3/timproc_uso_b3_o0_0.c.o: OPT_FLAGS := -O0
build/src/timproc_uso_b3/timproc_uso_b3_o0_0.c.o: TRUNCATE_TEXT := 0xB0
build/non_matching/src/timproc_uso_b3/timproc_uso_b3_o0_0.c.o: NON_MATCHING_TRUNCATE_TEXT := 0xB0
# timproc_uso_b5: mid-block -O2 -g3 carves for tiny unfilled-jr-delay returns.
# Each is 0xC bytes and spliced into block5 at its original offset (see block5 rule).
build/src/timproc_uso_b5/timproc_uso_b5_g3_87E8.c.o build/non_matching/src/timproc_uso_b5/timproc_uso_b5_g3_87E8.c.o build/src/timproc_uso_b5/timproc_uso_b5_g3_8894.c.o build/non_matching/src/timproc_uso_b5/timproc_uso_b5_g3_8894.c.o build/src/timproc_uso_b5/timproc_uso_b5_g3_8940.c.o build/non_matching/src/timproc_uso_b5/timproc_uso_b5_g3_8940.c.o: OPT_FLAGS := -O2 -g3
build/src/timproc_uso_b5/timproc_uso_b5_g3_87E8.c.o: TRUNCATE_TEXT := 0xC
build/non_matching/src/timproc_uso_b5/timproc_uso_b5_g3_87E8.c.o: NON_MATCHING_TRUNCATE_TEXT := 0xC
build/src/timproc_uso_b5/timproc_uso_b5_g3_8894.c.o: TRUNCATE_TEXT := 0xC
build/non_matching/src/timproc_uso_b5/timproc_uso_b5_g3_8894.c.o: NON_MATCHING_TRUNCATE_TEXT := 0xC
build/src/timproc_uso_b5/timproc_uso_b5_g3_8940.c.o: TRUNCATE_TEXT := 0xC
build/non_matching/src/timproc_uso_b5/timproc_uso_b5_g3_8940.c.o: NON_MATCHING_TRUNCATE_TEXT := 0xC

# Final Yay0 block .text size (fixed per block; the concat is zero-padded up to
# it before compression). NOT a 16-align rule — block sizes vary (e.g. b1 is
# 4-aligned via its donor-splice). These equal the pre-split single-.o .text.
# 0x3420 = exact len of assets/mgrproc_uso_block_1.bin (was 0x3410, stale
# from when the block emitted short; fixed 2026-06-10)
build/assets/mgrproc_uso_block1_yay0.bin: YAY0_TEXT_SIZE := 0x3420
# 0x2EE0 = exact len of assets/timproc_uso_block_1.bin (was 0x2ED4, a stale
# value baked in while the block was emitting -0x10 short; fixed 2026-06-10)
build/assets/timproc_uso_block1_yay0.bin: YAY0_TEXT_SIZE := 0x2EE0
build/assets/timproc_uso_block3_yay0.bin: YAY0_TEXT_SIZE := 0x30E0
build/assets/timproc_uso_block5_yay0.bin: YAY0_TEXT_SIZE := 0xE620

# INSN_PATCH / RELOC_PATCH / PROLOGUE_STEALS were REMOVED 2026-05-23 as
# match-faking (post-cc instruction-byte editing). See
# feedback_no_instruction_forcing_matches_policy. No recipe step applies them.
# Only genuine data/alignment mechanisms remain: all-zero padding SUFFIX_BYTES,
# USO-header PREFIX_BYTES, TRUNCATE_TEXT / TEXT_CLIP_KEEP_ALIGN, and the -O0
# donor splice REPLACE_FUNC_BODY (real -O0 compiler output).
build/src/bootup_uso/bootup_uso.c.o: SUFFIX_BYTES := func_0000F1B4=0x00000000,0x00000000,0x00000000
# func_0000EE8C: byte-exact C body ends `jr ra; nop` at 0xEF1C; the target has a
# single trailing 8-byte-alignment nop so func_0000EF20 sits at 0xEF20. Append it
# as an all-zero (nop) word via SUFFIX_BYTES_FORCE (alignment pad, not an invented
# instruction). FORCE because the natural epilogue trips the plain-SUFFIX skip path.
build/src/bootup_uso/bootup_uso.c.o: SUFFIX_BYTES_FORCE := func_0000EE8C=0x00000000
# Mirror onto the non_matching object so report.json/objdiff score the trailing
# alignment-nop word (splat-symbol-boundary trailing-delay-nop class).
# func_0000F1B4 likewise: matching build has SUFFIX_BYTES (3 all-zero pad words to
# the next-fn boundary at 0xF1F0); mirror it so objdiff sizes the symbol 0x3C not
# 0x30 (was scoring 80%=12/15w on a byte-identical fn). F1B4 is the LAST fn in the
# file so the pad just extends .text (no shift / TRUNCATE needed on non_matching).
build/non_matching/src/bootup_uso/bootup_uso.c.o: NON_MATCHING_SUFFIX_BYTES_FORCE := func_0000EE8C=0x00000000 func_0000F1B4=0x00000000,0x00000000,0x00000000

# Collect source files (kernel/, bootup_uso/, game_libs/, gui_uso/ — exclude o1/ reference)
C_FILES   := $(filter-out src/timproc_uso_b1/timproc_uso_b1_o0_5A4.c src/timproc_uso_b1/timproc_uso_b1_o0_65C.c src/timproc_uso_b1/timproc_uso_b1_o0_B0.c src/timproc_uso_b3/timproc_uso_b3_o0_65C.c src/timproc_uso_b3/timproc_uso_b3_o0_5A4.c src/timproc_uso_b3/timproc_uso_b3_o0_B0.c src/game_libs/game_libs_o1_6C8AC.c src/game_libs/game_libs_o1_6AF0C.c src/game_libs/game_libs_o1_6A304.c src/game_libs/game_libs_o1_6AF44.c src/game_libs/game_libs_o1_6B880.c src/game_libs/game_libs_o1_6B974.c src/game_libs/game_libs_o1_6BAD4.c src/game_libs/game_libs_o1_6B7A0.c src/game_libs/game_libs_ido53_6C11C.c src/game_libs/game_libs_o1_6FAD4.c src/game_libs/game_libs_ido53_71708.c src/game_libs/game_libs_o1_73824.c src/game_libs/game_libs_o1_6BF34.c src/game_libs/game_libs_ido53_6C1B8.c src/game_libs/game_libs_ido53_6D0F4.c src/game_libs/game_libs_o1_6DA74.c src/game_libs/game_libs_o1_6D554.c src/game_libs/game_libs_ido53_6D6F4.c src/game_libs/game_libs_ido53_6D7CC.c src/game_libs/game_libs_ido53_6CDB4.c src/game_libs/game_libs_o1_6CAD4.c src/game_libs/game_libs_o1_6CB84.c src/game_libs/game_libs_o1_6CC64.c src/game_libs/game_libs_o1_6D270.c src/game_libs/game_libs_ido53_70040.c src/game_libs/game_libs_ido53_730CC.c src/game_libs/game_libs_ido53_7369C.c src/game_libs/game_libs_ido53_70B04.c src/game_libs/game_libs_ido53_70C44.c src/game_libs/game_libs_ido53_73310.c src/game_libs/game_libs_ido53_6F088.c src/game_libs/game_libs_ido53_6F38C.c src/game_libs/game_libs_ido53_6F3BC.c src/game_libs/game_libs_o2_70FCC.c src/arcproc_uso/arcproc_uso_o0_748.c src/arcproc_uso/arcproc_uso_o0_688.c src/kernel/kernel_000_ido53_2530.c src/kernel/kernel_018_f_ido53_7564.c src/kernel/kernel_018_d_ido53_70A0.c src/kernel/kernel_018_b_ido53_698C.c src/kernel/kernel_006_o1_5520.c src/kernel/kernel_008_o1_58C0.c src/kernel/kernel_024_o1_9AB0.c,$(shell find src/kernel src/bootup_uso src/game_libs src/gui_uso src/n64proc_uso src/eddproc_uso src/arcproc_uso src/h2hproc_uso src/titproc_uso src/boarder1_uso src/boarder2_uso src/boarder3_uso src/boarder4_uso src/boarder5_uso src/mgrproc_uso src/game_uso src/timproc_uso_b1 src/timproc_uso_b3 src/timproc_uso_b5 src/map4_data_uso_b2 -name '*.c' -type f 2>/dev/null))
ASM_FILES := $(shell find asm -maxdepth 1 -name '*.s' -type f 2>/dev/null)
BIN_FILES := $(shell find assets -name '*.bin' -type f)

# Object files
C_O_FILES   := $(patsubst src/%.c,build/src/%.c.o,$(C_FILES))
ASM_O_FILES := $(patsubst asm/%.s,build/asm/%.s.o,$(ASM_FILES))
BIN_O_FILES := $(patsubst assets/%.bin,build/assets/%.bin.o,$(BIN_FILES))

# Non-matching objects: parallel build tree under build/non_matching/ that
# compiles every .c with -DNON_MATCHING. Used by objdiff to compute fuzzy
# match percentages on NM-wrapped functions (whose default-build path is
# the INCLUDE_ASM stub, byte-exact and so untracked by fuzzy scoring).
# See feedback_non_matching_build_for_fuzzy_scoring.md.
C_O_FILES_NM := $(patsubst src/%.c,build/non_matching/src/%.c.o,$(C_FILES))

# Yay0-recompressed blocks (built from C, not extracted from baserom)
YAY0_O_FILES := build/assets/mgrproc_uso_block1_yay0.bin.o                 build/assets/game_uso_block1_yay0.bin.o                 build/assets/timproc_uso_block1_yay0.bin.o                 build/assets/timproc_uso_block3_yay0.bin.o                 build/assets/timproc_uso_block5_yay0.bin.o                 build/assets/map4_data_uso_block2_yay0.bin.o

O_FILES     := $(BIN_O_FILES) $(YAY0_O_FILES) $(C_O_FILES) $(ASM_O_FILES)

# Default target
all: verify

# gl_func_0006AF0C -O1 -g3 donor: direct CC, no asm-processor (see donor block).
build/src/game_libs/game_libs_o1_6AF0C.c.o: src/game_libs/game_libs_o1_6AF0C.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -O1 -g3 $(MIPSISET) $(CPPFLAGS) -o $@ $<

# game_libs_func_00070FA0 merged unit: -O1 -g3, direct CC (asm-processor
# rejects -O1 -g3). Same rule pair for the non_matching build.
build/src/game_libs/game_libs_o1g3_70FA4.c.o: src/game_libs/game_libs_o1g3_70FA4.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -O1 -g3 $(MIPSISET) $(CPPFLAGS) -o $@ $<
	python3 scripts/truncate-elf-text.py $@ 0x30

build/non_matching/src/game_libs/game_libs_o1g3_70FA4.c.o: src/game_libs/game_libs_o1g3_70FA4.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -O1 -g3 $(MIPSISET) $(CPPFLAGS) -DNON_MATCHING -o $@ $<

# C objects only — used by CI for objdiff reports (no baserom required).
objects: $(C_O_FILES)

# Non-matching C objects only — used by objdiff for fuzzy scoring of
# NM-wrapped functions. See comment on C_O_FILES_NM.
non_matching_objects: $(C_O_FILES_NM)

# Build ROM
$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): $(O_FILES) $(LD_SCRIPT)
	$(LD) $(LDFLAGS) -o $@

# C source -- two-phase asm-processor pattern
ifdef PERMUTER
build/src/%.c.o: src/%.c
	@mkdir -p $(dir $@) build/$(<D)
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) $(CPPFLAGS) -o $@ $<
else
build/src/%.c.o: src/%.c
	@mkdir -p $(dir $@) build/$(<D)
	$(ASM_PROC) $(OPT_FLAGS) $< > build/$<
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(CC_ONLY_FLAGS) $(MIPSISET) $(CPPFLAGS) -o $@ build/$<
	$(ASM_PROC) $(OPT_FLAGS) $< --post-process $@ 		--assembler "$(AS) $(ASFLAGS)" --asm-prelude $(ASM_PRELUDE)
	$(POST_COMPILE)
	@if [ -n "$(REPLACE_FUNC_BODY)" ]; then for spec in $(REPLACE_FUNC_BODY); do 		fn=$$(echo $$spec | cut -d= -f1); 		donor=$$(echo $$spec | cut -d= -f2); 		$(MAKE) $$donor; 		python3 scripts/replace-function-body.py $@ $$fn $$donor; 	done; fi
	@if [ -n "$(PREFIX_BYTES)" ]; then for spec in $(PREFIX_BYTES); do 		fn=$$(echo $$spec | cut -d= -f1); 		words=$$(echo $$spec | cut -d= -f2); 		python3 scripts/inject-prefix-bytes.py $@ $$fn $$words; 	done; fi
	@if [ -n "$(SUFFIX_BYTES)" ]; then for spec in $(SUFFIX_BYTES); do 		fn=$$(echo $$spec | cut -d= -f1); 		words=$$(echo $$spec | cut -d= -f2); 		python3 scripts/inject-suffix-bytes.py $@ $$fn $$words; 	done; fi
	@if [ -n "$(SUFFIX_BYTES_FORCE)" ]; then for spec in $(SUFFIX_BYTES_FORCE); do 		fn=$$(echo $$spec | cut -d= -f1); 		words=$$(echo $$spec | cut -d= -f2); 		python3 scripts/inject-suffix-bytes.py $@ $$fn $$words --allow-natural-epilogue; 	done; fi
	@if [ -n "$(SUFFIX_BYTES_FORCE_UNTIL_SIZE)" ]; then for spec in $(SUFFIX_BYTES_FORCE_UNTIL_SIZE); do 		fn=$$(echo $$spec | cut -d= -f1); 		rest=$$(echo $$spec | cut -d= -f2); 		size=$$(echo $$rest | cut -d: -f1); 		words=$$(echo $$rest | cut -d: -f2); 		python3 scripts/inject-suffix-bytes.py $@ $$fn $$words --allow-natural-epilogue --skip-if-size-ge $$size; 	done; fi
	@if [ -n "$(POST_INSN_SUFFIX_BYTES)" ]; then for spec in $(POST_INSN_SUFFIX_BYTES); do 		fn=$$(echo $$spec | cut -d= -f1); 		words=$$(echo $$spec | cut -d= -f2); 		python3 scripts/inject-suffix-bytes.py $@ $$fn $$words; 	done; fi
	@if [ -n "$(POST_INSN_SUFFIX_BYTES_FORCE)" ]; then for spec in $(POST_INSN_SUFFIX_BYTES_FORCE); do 		fn=$$(echo $$spec | cut -d= -f1); 		words=$$(echo $$spec | cut -d= -f2); 		python3 scripts/inject-suffix-bytes.py $@ $$fn $$words --allow-natural-epilogue; 	done; fi
	@if [ -n "$(TRUNCATE_TEXT)" ]; then python3 scripts/truncate-elf-text.py $@ $(TRUNCATE_TEXT); fi
	@if [ -n "$(TEXT_CLIP_KEEP_ALIGN)" ]; then python3 scripts/clip-elf-text-keep-align.py $@ $(TEXT_CLIP_KEEP_ALIGN); fi
endif

# Non-matching C build: same compile pipeline as the byte-exact rule above
# but with -DNON_MATCHING so #ifdef NON_MATCHING wraps emit C bodies instead
# of INCLUDE_ASM stubs. Skips the instruction-forcing recipes entirely (those
# were removed 2026-05-23 as match-faking).
#
# Only genuine object-split metadata fixups run here, so objdiff can read the
# base object for functions whose .c.o is a partial-file split:
# NON_MATCHING_SUFFIX_BYTES_FORCE (all-zero pad), NON_MATCHING_TRUNCATE_TEXT,
# and NON_MATCHING_TEXT_CLIP_KEEP_ALIGN (boundary/alignment only — no
# instruction bytes invented).
ifndef PERMUTER
build/non_matching/src/%.c.o: src/%.c
	@mkdir -p $(dir $@) build/non_matching/$(<D)
	$(ASM_PROC) $(OPT_FLAGS) $< > build/non_matching/$<
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(CC_ONLY_FLAGS) $(MIPSISET) $(CPPFLAGS) -DNON_MATCHING -o $@ build/non_matching/$<
	$(ASM_PROC) $(OPT_FLAGS) $< --post-process $@ 		--assembler "$(AS) $(ASFLAGS)" --asm-prelude $(ASM_PRELUDE)
	$(POST_COMPILE)
	@if [ -n "$(REPLACE_FUNC_BODY)" ]; then for spec in $(REPLACE_FUNC_BODY); do 		fn=$$(echo $$spec | cut -d= -f1); 		donor=$$(echo $$spec | cut -d= -f2); 		$(MAKE) $$donor; 		python3 scripts/replace-function-body.py $@ $$fn $$donor; 	done; fi
	@if [ -n "$(NON_MATCHING_PREFIX_BYTES)" ]; then for spec in $(NON_MATCHING_PREFIX_BYTES); do 		fn=$$(echo $$spec | cut -d= -f1); 		words=$$(echo $$spec | cut -d= -f2); 		python3 scripts/inject-prefix-bytes.py $@ $$fn $$words; 	done; fi
	@if [ -n "$(NON_MATCHING_SUFFIX_BYTES_FORCE)" ]; then for spec in $(NON_MATCHING_SUFFIX_BYTES_FORCE); do 		fn=$$(echo $$spec | cut -d= -f1); 		words=$$(echo $$spec | cut -d= -f2); 		python3 scripts/inject-suffix-bytes.py $@ $$fn $$words --allow-natural-epilogue; 	done; fi
	@if [ -n "$(NON_MATCHING_TRUNCATE_TEXT)" ]; then python3 scripts/truncate-elf-text.py $@ $(NON_MATCHING_TRUNCATE_TEXT); fi
	@if [ -n "$(NON_MATCHING_TEXT_CLIP_KEEP_ALIGN)" ]; then python3 scripts/clip-elf-text-keep-align.py $@ $(NON_MATCHING_TEXT_CLIP_KEEP_ALIGN); fi
endif

# Standalone assembly
build/asm/%.s.o: asm/%.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

# Binary assets
build/assets/%.bin.o: assets/%.bin
	@mkdir -p $(dir $@)
	$(OBJCOPY) -I binary -O elf32-tradbigmips $< $@

# Yay0-compressed USO blocks: compile C → extract .text → crunch64 compress → wrap as bin
# mgrproc_uso block 1: text 0x3410 bytes uncompressed. Split into 4 regions
# concatenated in address order before Yay0 compression:
#   region0 = mgrproc_uso_o0_0.c.o   (-O0, [0x0,0xF8))  func_00000000/4C/B0
#   region1 = mgrproc_uso_head.c.o   (-O2, [0xF8,0x19C)) func_000000F8 + leaves
#   region2 = mgrproc_uso_o0_19C.c.o (-O0, [0x19C,0xAE0)) func_0000019C..A14
#   region3 = mgrproc_uso.c.o        (-O2, [0xAE0,end))  the rest
# Each region's .text is objcopy'd to raw binary; bake-data-relocs.py then bakes
# HI16/LO16 data relocs (e.g. func_000009A8's D_0000014C %lo) into the bytes —
# objcopy leaves them raw (pre-link) but the USO ships them baked. R_MIPS_26
# jals stay raw (USO load-time relocs). Pad to the exact block size; the 0xC
# gap before region3 (func_00000A14's trailing block-align pad) is the
# intermediate pad-to-0xAE0.
build/assets/mgrproc_uso_block1_yay0.bin: build/src/mgrproc_uso/mgrproc_uso_o0_0.c.o build/src/mgrproc_uso/mgrproc_uso_head.c.o build/src/mgrproc_uso/mgrproc_uso_o0_19C.c.o build/src/mgrproc_uso/mgrproc_uso.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $(word 1,$^) $(@:.bin=.text0.bin)
	python3 scripts/bake-data-relocs.py $(word 1,$^) $(@:.bin=.text0.bin) undefined_syms_auto.txt
	$(OBJCOPY) -O binary --only-section=.text $(word 2,$^) $(@:.bin=.text1.bin)
	python3 scripts/bake-data-relocs.py $(word 2,$^) $(@:.bin=.text1.bin) undefined_syms_auto.txt
	$(OBJCOPY) -O binary --only-section=.text $(word 3,$^) $(@:.bin=.text2.bin)
	python3 scripts/bake-data-relocs.py $(word 3,$^) $(@:.bin=.text2.bin) undefined_syms_auto.txt
	$(OBJCOPY) -O binary --only-section=.text $(word 4,$^) $(@:.bin=.text3.bin)
	python3 scripts/bake-data-relocs.py $(word 4,$^) $(@:.bin=.text3.bin) undefined_syms_auto.txt
	cat $(@:.bin=.text0.bin) $(@:.bin=.text1.bin) $(@:.bin=.text2.bin) > $(@:.bin=.pre.bin)
	python3 -c "import sys; f=sys.argv[1]; n=int(sys.argv[2],0); d=open(f,'rb').read(); assert len(d)<=n,(hex(len(d)),hex(n)); open(f,'ab').write(b'\x00'*(n-len(d)))" $(@:.bin=.pre.bin) 0xAE0
	cat $(@:.bin=.pre.bin) $(@:.bin=.text3.bin) > $(@:.bin=.text.bin)
	python3 -c "import sys; f=sys.argv[1]; n=int(sys.argv[2],0); d=open(f,'rb').read(); assert d[n:]==b'\x00'*len(d[n:]), ('nonzero discarded tail', hex(len(d)), d[n:].hex()); d=d[:n]+b'\x00'*(n-len(d)); open(f,'wb').write(d)" $(@:.bin=.text.bin) $(YAY0_TEXT_SIZE)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

# game_uso block 1: text 0x11B30 bytes uncompressed, 200 functions
# The drop at 0xC0F0: func_0000C0BC's 1-word zero alignment pad (truth offset
# 0xC0EC) sits between two MATCHED C fns, so it must stay a 1-word GLOBAL_ASM
# sidecar -- and asm-processor's minimum C placeholder for a .text block is
# 8 bytes (empty fn = jr ra; nop), leaving one extra ZERO word at 0xC0F0.
# Dropping that asserted-zero word is a pure data/alignment op (no
# instruction bytes are created or modified); remove it if asm-processor
# ever learns to emit 4-byte blocks. See docs/MATCHING_WORKFLOW.md
# (asm-processor 1-word-pad defect).
build/assets/game_uso_block1_yay0.bin: build/src/game_uso/game_uso.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $< $(@:.bin=.text.bin)
	python3 -c "import sys; f=sys.argv[1]; n=0x11B30; d=open(f,'rb').read(); off=0xC0F0; assert d[off:off+4]==b'\x00'*4, ('placeholder leftover not zero', d[off:off+4].hex()); d=d[:off]+d[off+4:]; assert len(d)>=n and d[n:]==b'\x00'*(len(d)-n), ('len/tail', hex(len(d)), d[n:].hex()); open(f,'wb').write(d[:n])" $(@:.bin=.text.bin)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

# timproc_uso code blocks (1: 55 fn, 3: 55 fn, 5: 99 fn). Blocks 1 and 3 each
# open with a contiguous -O0 run (0x0..0xB0) carved into a region-0 sub-unit;
# concatenated with the -O2 main object before compression (Yay0 split infra).
build/assets/timproc_uso_block1_yay0.bin: build/src/timproc_uso_b1/timproc_uso_b1_o0_0.c.o build/src/timproc_uso_b1/timproc_uso_b1.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $(word 1,$^) $(@:.bin=.text0.bin)
	$(OBJCOPY) -O binary --only-section=.text $(word 2,$^) $(@:.bin=.text1.bin)
	cat $(@:.bin=.text0.bin) $(@:.bin=.text1.bin) > $(@:.bin=.text.bin)
	python3 -c "import sys; f=sys.argv[1]; n=int(sys.argv[2],0); d=open(f,'rb').read(); assert d[n:]==b'\x00'*len(d[n:]), ('nonzero discarded tail', hex(len(d)), d[n:].hex()); d=d[:n]+b'\x00'*(n-len(d)); open(f,'wb').write(d)" $(@:.bin=.text.bin) $(YAY0_TEXT_SIZE)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

build/assets/timproc_uso_block3_yay0.bin: build/src/timproc_uso_b3/timproc_uso_b3_o0_0.c.o build/src/timproc_uso_b3/timproc_uso_b3.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $(word 1,$^) $(@:.bin=.text0.bin)
	$(OBJCOPY) -O binary --only-section=.text $(word 2,$^) $(@:.bin=.text1.bin)
	cat $(@:.bin=.text0.bin) $(@:.bin=.text1.bin) > $(@:.bin=.text.bin)
	python3 -c "import sys; f=sys.argv[1]; n=int(sys.argv[2],0); d=open(f,'rb').read(); assert d[n:]==b'\x00'*len(d[n:]), ('nonzero discarded tail', hex(len(d)), d[n:].hex()); d=d[:n]+b'\x00'*(n-len(d)); open(f,'wb').write(d)" $(@:.bin=.text.bin) $(YAY0_TEXT_SIZE)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

# block5: tiny unfilled-jr-delay functions are carved into -O2 -g3 sub-units
# (deleted from the main TU) and spliced back at their original offsets.
build/assets/timproc_uso_block5_yay0.bin: build/src/timproc_uso_b5/timproc_uso_b5.c.o build/src/timproc_uso_b5/timproc_uso_b5_g3_87E8.c.o build/src/timproc_uso_b5/timproc_uso_b5_g3_8894.c.o build/src/timproc_uso_b5/timproc_uso_b5_g3_8940.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $(word 1,$^) $(@:.bin=.main.bin)
	$(OBJCOPY) -O binary --only-section=.text $(word 2,$^) $(@:.bin=.g3_87E8.bin)
	$(OBJCOPY) -O binary --only-section=.text $(word 3,$^) $(@:.bin=.g3_8894.bin)
	$(OBJCOPY) -O binary --only-section=.text $(word 4,$^) $(@:.bin=.g3_8940.bin)
	python3 -c "import sys; m=open(sys.argv[1],'rb').read(); g2=open(sys.argv[2],'rb').read(); g3=open(sys.argv[3],'rb').read(); g4=open(sys.argv[4],'rb').read(); n=int(sys.argv[6],0); assert len(g2)==0xC and len(g3)==0xC and len(g4)==0xC,(hex(len(g2)),hex(len(g3)),hex(len(g4))); p2=0x87E8; p3=0x8894-0xC; p4=0x8940-0x18; out=m[:p2]+g2+m[p2:p3]+g3+m[p3:p4]+g4+m[p4:]; assert len(out)>=n,(hex(len(out)),hex(n)); assert out[n:]==b'\x00'*len(out[n:]),'discarded tail is not zero'; open(sys.argv[5],'wb').write(out[:n])" $(@:.bin=.main.bin) $(@:.bin=.g3_87E8.bin) $(@:.bin=.g3_8894.bin) $(@:.bin=.g3_8940.bin) $(@:.bin=.text.bin) $(YAY0_TEXT_SIZE)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

# map4_data_uso block 2: 0xD0 bytes / 3 functions (the only code block)
build/assets/map4_data_uso_block2_yay0.bin: build/src/map4_data_uso_b2/map4_data_uso_b2.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $< $(@:.bin=.text.bin)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

# Wrap a build/-located .bin into a .o (mirror of the assets/-located rule above)
build/assets/%.bin.o: build/assets/%.bin
	@mkdir -p $(dir $@)
	$(OBJCOPY) -I binary -O elf32-tradbigmips $< $@

# Verify every built Yay0 code block against its ROM-extracted ground truth
# (exact length + only reloc-field word diffs). Catches the asm-processor
# pad/orphan emission damage class -- see docs/MATCHING_WORKFLOW.md.
verify-blocks: build/assets/mgrproc_uso_block1_yay0.bin build/assets/game_uso_block1_yay0.bin \
		build/assets/timproc_uso_block1_yay0.bin build/assets/timproc_uso_block3_yay0.bin \
		build/assets/timproc_uso_block5_yay0.bin build/assets/map4_data_uso_block2_yay0.bin
	python3 scripts/verify-yay0-blocks.py

# Verify ROM matches — HARD-FAILS on any regression (rom-exact reached
# 2026-06-10: tenshoe.z64 is byte-identical to baserom, splat sha1
# 79cd1166c365e5809dec9b62e6d40d6032d5db3a). Do not soften this gate.
verify: $(ROM)
	@md5sum -c checksum.md5 || { echo "ROM MISMATCH — build regressed from byte-exact"; exit 1; }
	@cmp $(ROM) baserom.z64 || { echo "ROM MISMATCH (cmp) — build regressed from byte-exact"; exit 1; }
	@echo "ROM OK (byte-identical to baserom)"

# Snapshot expected objects for objdiff baseline
expected:
	$(RM) -r expected
	mkdir -p expected/src/kernel expected/src/bootup_uso expected/src/game_libs 		expected/src/gui_uso expected/src/n64proc_uso expected/src/eddproc_uso 		expected/src/arcproc_uso expected/src/h2hproc_uso expected/src/titproc_uso 		expected/src/boarder1_uso expected/src/boarder2_uso expected/src/boarder3_uso 		expected/src/boarder4_uso expected/src/boarder5_uso
	cp build/src/kernel/*.o expected/src/kernel/
	cp build/src/bootup_uso/*.o expected/src/bootup_uso/ 2>/dev/null || true
	cp build/src/game_libs/*.o expected/src/game_libs/ 2>/dev/null || true
	for d in gui_uso n64proc_uso eddproc_uso arcproc_uso h2hproc_uso titproc_uso 	         boarder1_uso boarder2_uso boarder3_uso boarder4_uso boarder5_uso 	         mgrproc_uso game_uso timproc_uso_b1 timproc_uso_b3 timproc_uso_b5 	         map4_data_uso_b2; do 	    mkdir -p expected/src/$$d; 	    cp build/src/$$d/*.o expected/src/$$d/ 2>/dev/null || true; 	done

clean:
	rm -rf build $(ROM)

# Extract asset .bin files from baserom.z64 via splat.
# Run once after providing your own legally-obtained ROM.
setup: $(BASEROM)
	python3 -m splat split tenshoe.yaml

.PHONY: all clean verify verify-blocks expected setup objects

# osSendMesg / osStartThread twins, IDO 5.3 -O1 (donor vars defined earlier).
build/src/game_libs/game_libs_ido53_69E04.c.o build/non_matching/src/game_libs/game_libs_ido53_69E04.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_69E04.c.o build/non_matching/src/game_libs/game_libs_ido53_69E04.c.o: OPT_FLAGS := -O1
build/src/game_libs/game_libs_ido53_74C04.c.o build/non_matching/src/game_libs/game_libs_ido53_74C04.c.o: CC := $(IDO53_DIR)/cc
build/src/game_libs/game_libs_ido53_74C04.c.o build/non_matching/src/game_libs/game_libs_ido53_74C04.c.o: OPT_FLAGS := -O1
