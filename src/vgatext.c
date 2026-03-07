#include "vgatext.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* buf;

static inline uint16_t vga_entry(unsigned char uc, uint8_t color){
	return (uint16_t) uc | (uint16_t) color << 8;
}

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg){
	return fg | bg << 4;
}

void terminal_init(void){
	terminal_row = 0; terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
	buf = (uint16_t*) 0xB8000;

	for (size_t y = 0; y < VGA_HEIGHT; y++){
		for (size_t x = 0; x < VGA_WIDTH; x++){

			const size_t index = y * VGA_WIDTH + x;

			buf[index] = vga_entry(' ', terminal_color);
		}
	}
}
