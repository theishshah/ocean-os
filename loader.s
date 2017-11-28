.extern kernel_main

.global loader

.set MAGIC_NUMBER, 0x1BADB002 ;I guess this just works
.set FLAGS, (1 << 0) | (1 << 1) ;shameless rip of multiboot logic
.set CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

.section .multiboot
    .align 4
    .long MAGIC_NUMBER
    .long FLAGS
    .long CHECKSUM

.section .bss
    .align 16
    stack_bottom:
        .skip 4096 ;should be plenty for now, can expand later if needed
    stack_top:

section .text:
    loader:
        mov $stack_top, %esp

        call kernel_main ;calling main function of kernel.c

        hang: ;in case the kernel returns on accident, hang the cpu
            cli
            hlt
            jmp hang
    