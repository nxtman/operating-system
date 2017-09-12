void magic_breakpoint() {
	__asm__ ("xchgw %bx, %bx");
}
