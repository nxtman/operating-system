print_hex:
	pusha
	mov cx, 0
	.start:
		cmp cx, 4
		je .done

		mov ax, dx
		and ax, 0x000f
		add al, 0x30

		cmp al, 0x39
		jle .step2
		add al, 7
	.step2:
		mov bx, [HEXOUT + 5]
		sub bx, cx
		mov [bx], al
		ror dx, 4

		add cx, 1
		jmp .start
	.done:
		mov bx, HEXOUT
		call print

		popa
		ret

HEXOUT: db "0x0000", 0
