; "Hello World!" in Linux NASM
; adapted from http://asm.sourceforge.net/intro/hello.html by Mark Loiseau
; referenced in http://blog.markloiseau.com/2012/04/hello-world-NASM-Linux
;
; Compile assembly to machine level
; nasm -f elf -o hello.o hello.nasm
; nasm -f elf64 -o hello.o hello.nasm
;
; Link machine to ELF binary
; ld -o hello hello.o
;
; Run
; ./hello

global _start			; global entry point export for ld

section .text
_start:

	; sys_write(stdout, message, length)

	mov eax, 4		; sys_write syscall
	mov ebx, 1		; stdout
	mov ecx, message	; message address
	mov edx, length		; message string length
	int 80h

	; sys_exit(return_code)

	mov eax, 1		; sys_exit syscall
	mov ebx, 0		; return 0 (success)
	int 80h

section .data
	message: db 'Hello, world!',0x0A	; message and newline
	length: equ $-message			; NASM definition pseudo-instruction
