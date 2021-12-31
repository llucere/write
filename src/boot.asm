[org 0x7c00]
jmp _start

_start:
	mov bx, string001
	call os_write

	mov ax, input001
	mov bx, 5
	call os_read

	;mov ax, [input001]
	;mov ax, 6

	;mov ah, 0x0e
	;mov al, [input001]
	;add al, '0'
	;int 0x10
jmp $

string001: db "Hello, world!", 0
input001: resd 5

%include "system.inc"
times 510 - ($ - $$) db 0
dw 0xAA55