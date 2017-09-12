[bits 32]

mov esp, stack_top

[extern main]
call main
jmp $

section .bss
stack_bottom:
	resb 4069
stack_top:
