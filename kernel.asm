;;kernel.asm
bits 32         ;nasm 32bit
section .text
    ;multiboot
    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00)
	
global start
extern kmain

start:
    cli ;block interupts
    mov esp, stack_space ;set stack ptr
    call kmain
    hlt

section .bss
resb 8192
stack_space:
