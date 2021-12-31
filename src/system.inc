[org 0x7c00]

os_write:
	mov ah, 0x0e
	.lp1:
		mov al, [bx]
		cmp al, 0
		je .lp1_end
		
		int 0x10
		inc bx
		jmp .lp1
	.lp1_end:
	ret

os_read: ; read_to_ax_bx_chars
	mov cx, 0 ; chars written
	.lp1:
		; grab input
		mov ah, 0
		int 0x16
		
		cmp al, 0x08
		jne .else1
		;.is_backspace:
			cmp cx, 0
			je .lp1

			dec cx
			mov ah, 0x0e

			mov al, 0x08
			int 0x10

			mov al, 0x20
			int 0x10
			
			mov al, 0x08
			int 0x10

			jmp .lp1
		.else1:
			cmp al, 13
			jne .else2

			;.is_new_line:
				; print newline character
				mov ah, 0x0e
				mov al, 10
				int 0x10

				; get current cursor position (dl = column, dh = row)
				mov ah, 3
				mov bh, 0
				int 0x10
				
				mov dl, 0 ; cursor position column
				mov ah, 0x02 ; set cursor position function
				mov bh, 0x00 ; page number
				int 0x10 ; interrupt call

				jmp .lp1_end
			.else2:
				cmp cx, bx
				je .lp1
				
				inc cx
				mov ah, 0x0e
				int 0x10
				jmp .lp1
	.lp1_end:

	ret