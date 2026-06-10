/* ROM-truth inter-TU zero padding [0x80007E90..0x80007EA0), 4 words. */
/* 2026-06-10 kernel relayout: base has 0x10 of zeros between the osStopThread TU end and the kernel_030 TU. */
glabel _pad_kernel_019_7E90, local
.word 0x00000000
.word 0x00000000
.word 0x00000000
.word 0x00000000
endlabel _pad_kernel_019_7E90
