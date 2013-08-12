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

void print_tennis_net()
{
	uart0SendChar(0xE2);
	uart0SendChar(0x94);
	uart0SendChar(0x8A);
}

void print_full_block()
{
	uart0SendChar(0xE2);
	uart0SendChar(0x96);
	uart0SendChar(0x88);
}

void init()
{
	move_cursor(X_MIN,Y_MIN);
	int x,y;
	printf("\033[37;40m");
	for(y = Y_MIN; y < Y_MAX; y+=2)
	{
		for(x = X_MIN ; x < X_MAX; x++)
		{
			printf(" ");
			if(x == 40)
				print_tennis_net();
		}
		printf("\r\n");
	}
	printf("                                                                                ");
}

void renderer_ball(uint8_t x, uint8_t y, uint8_t x_prev, uint8_t y_prev)
{
	//rebuild the playing field at the last ball point:
	move_cursor(x_prev, y_prev);
	if(x_prev != 41)
		printf(" ");
	else if(x_prev == 41)
		print_tennis_net();

	//build the ball at the current position:
	move_cursor(x, y);
	if(y%2)
		print_bottom_block();
	else
		print_top_block();
//	printf("%d", y);
}

void renderer_pong_bat(uint8_t x, uint8_t y, uint8_t x_prev, uint8_t y_prev, uint8_t length)
{
	int y1;
	for(y1 = 0 ; y1 < length ; y1++)
	{
		//rebuild the playing field at the last pongBlock-pos:
		move_cursor(x_prev, y_prev + y1);
		printf(" ");
	}

	for(y1 = 0 ; y1 < length ; y1++)
	{
		//build the new pongBlock:
		move_cursor(x, y + y1);
		print_full_block();
	}
}
