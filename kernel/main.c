#include "../drivers/screen.h"
#include "../drivers/breakpoint.h"

void magic_breakpoint();
void systems_init();
void message_ok (char* message);

void main() {
	systems_init();
}

void systems_init() {
	terminal_init();
	terminal_clearscreen();
	terminal_writestring ("[ OK ] VGA variables have been initialized\n");
	terminal_writestring ("[ OK ] VGA buffer has been cleared\n");
	terminal_writestring ("[ OK ] This one doesn't really mean anything\n");
	terminal_writestring ("hellp\n");
	terminal_writestring ("Boiiiiiiiiiiiiiiiiiiiiii\n");
	terminal_writestring ("neeeeeed help this won't work!!!\n");
	terminal_writestring ("I think I've debunked the idea of this being a memory issue");
}

/* void message_ok (char* message) {
	terminal_writestring ("[ ");
	terminal_writestring ("OK");
	terminal_writestring (" ] ");
	terminal_writestring (message);
	terminal_writestring ("\n");
}
*/
