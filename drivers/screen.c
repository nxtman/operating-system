#include "breakpoint.h"
#include "screen.h"

uint8_t vga_entry_color(uint8_t fg, uint8_t bg) {
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len] != 0)
		len++;
	return len;
}
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_init(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) VIDEO_ADDRESS;
}

void terminal_clearscreen() {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	if (c != '\n') {
		terminal_putentryat (c, terminal_color, terminal_column, terminal_row);
		terminal_column++;
	} else {
		terminal_column = 0;
		terminal_row++;
	}
}

void terminal_write(const char* data) {		
	int i = 0;
	while (data[i] != 0) {		
		terminal_putchar (data[i]);
		i++;
		magic_breakpoint();
	}
}

void terminal_writestring(const char* data) {	
	terminal_write(data);
}
