# ocean-os

This is my attempt at writing a kernel and very basic operating systems. Goals include taking keyboard input and having a basic shell.

Tutorials from wiki.osdev.org are my primary source of information.

Instructions to build and run (I still need to write a Makefile):
```
nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kc.o
ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
qemu-system-i386 -kernel kernel
``` 
