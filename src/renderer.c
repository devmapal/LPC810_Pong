/*
 * renderer.c
 *
 *  Created on: Aug 8, 2013
 *      Author: devmapal
 */

#include "renderer.h"
#include "pong_field.h"
#include "uart.h"
#include <stdio.h>


void init()
{
	move_cursor(1,1);
	int i;
	printf("\033[37;40m");
	for(i = 0; i < 23; ++i)
		printf("                                                                                \r\n");
	printf("                                                                                ");
}

void hide_cursor()
{
	printf("\e[?25l");
}

void show_cursor()
{
	printf("\e[?25h");
}
void clear_screen()
{
    printf("\033[30;47m\033[2J\033[37;40m");
}

void move_cursor(int x, int y)
{
	y /= 2;
	printf("\033[%d;%dH", y, x);
}

void print_top_block()
{
//	printf("%c%c%c", 0xe2, 0x96, 0x80);
	uart0SendChar(0xe2);
	uart0SendChar(0x96);
	uart0SendChar(0x80);
}

void print_bottom_block()
{
//	printf("%c%c%c", 0xe2, 0x96, 0x84);
	uart0SendChar(0xe2);
	uart0SendChar(0x96);
	uart0SendChar(0x84);
}

void renderer_ball(uint8_t x, uint8_t y, uint8_t x_prev, uint8_t y_prev)
{
	move_cursor(x_prev, y_prev);
	printf(" ");
	move_cursor(x, y);
	if(y%2)
		print_bottom_block();
	else
		print_top_block();
//	printf("%d", y);
}
