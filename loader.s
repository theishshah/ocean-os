.extern kernel_main

.global loader

.set MAGIC_NUMBER, 0x1BADB002
.set FLAGS, (1 << 0) | (1 << 1)
.set CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

.section .multiboot
    .align 4
    .long MAGIC_NUMBER
    .long FLAGS
    .long CHECKSUM

.section .bss
    .align 16
    stack_bottom:
        .skip 4096
    stack_top:

section .text:
    loader:
        mov $stack_top, %esp

        call kernel_main

        hang:
            cli
            hlt
            jmp hang
    