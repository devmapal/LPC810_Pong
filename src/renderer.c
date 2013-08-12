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

void move_cursor(uint8_t x, uint8_t y)
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



void render_horizontal_line(uint8_t x, uint8_t y, uint8_t length)
{
	int i;
	for(i = 0; i < length; ++i)
	{
		move_cursor(x+i, y);
		if(y%2)
			print_bottom_block();
		else
			print_top_block();
	}
}

void render_vertical_line(uint8_t x, uint8_t y, uint8_t length)
{
	uint8_t pos = y;
	if(pos%2)
	{
		move_cursor(x, pos);
		print_bottom_block();
		++pos;
	}

	for(; pos < y+length-1; pos+=2)
	{
		move_cursor(x, pos);
		print_full_block();
	}

	if((y+length)%2)
	{
		move_cursor(x, pos);
		print_top_block();
	}
}

void erase_vertical_line(uint8_t x, uint8_t y, uint8_t length)
{
	uint8_t pos = y;
	if(pos%2)
	{
		move_cursor(x, pos);
		printf(" ");
		++pos;
	}

	for(; pos < y+length-1; pos+=2)
	{
		move_cursor(x, pos);
		printf(" ");
	}

	if((y+length)%2)
	{
		move_cursor(x, pos);
		printf(" ");
	}
}

void render_num(uint8_t x, uint8_t y, uint8_t num)
{
	move_cursor(x, y);
	printf("\033[37;40m");
	switch(num)
	{
	case 0:
		render_horizontal_line(x+1, y, 2);
		render_horizontal_line(x+1, y+5, 2);
		render_vertical_line(x, y, 6);
		render_vertical_line(x+3, y, 6);
		break;
	case 1:
		render_vertical_line(x+3, y, 6);
		break;
	case 2:
		render_horizontal_line(x, y, 3);
		render_horizontal_line(x+1, y+2, 2);
		render_horizontal_line(x+1, y+5, 3);
		render_vertical_line(x+3, y, 3);
		render_vertical_line(x, y+2, 4);
		break;
	case 3:
		render_horizontal_line(x, y, 3);
		render_horizontal_line(x, y+2, 3);
		render_horizontal_line(x, y+5, 3);
		render_vertical_line(x+3, y, 6);
		break;
	case 4:
		render_horizontal_line(x+1, y+2, 2);
		render_vertical_line(x, y, 3);
		render_vertical_line(x+3, y, 6);
		break;
	case 5:
		render_horizontal_line(x+1, y, 3);
		render_horizontal_line(x+1, y+2, 2);
		render_horizontal_line(x, y+5, 3);
		render_vertical_line(x, y, 3);
		render_vertical_line(x+3, y+2, 4);
		break;
	case 6:
		render_horizontal_line(x+1, y+2, 2);
		render_horizontal_line(x+1, y+5, 2);
		render_vertical_line(x, y, 6);
		render_vertical_line(x+3, y+2, 4);
		break;
	case 7:
		render_horizontal_line(x, y, 3);
		render_vertical_line(x+3, y, 6);
		break;
	case 8:
		render_horizontal_line(x+1, y, 2);
		render_horizontal_line(x+1, y+2, 2);
		render_horizontal_line(x+1, y+5, 2);
		render_vertical_line(x, y, 6);
		render_vertical_line(x+3, y, 6);
		break;
	case 9:
		render_horizontal_line(x+1, y, 2);
		render_horizontal_line(x+1, y+2, 2);
		render_vertical_line(x, y, 3);
		render_vertical_line(x+3, y, 6);
		break;
	}
}

void render_score(uint8_t x, uint8_t y, uint8_t num)
{
	uint8_t num_high = num/10;
	uint8_t num_low = num%10;
	if( num_high > 0)
		render_num(x, y, num_high);
	render_num(x+7, y, num_low);
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
	erase_vertical_line(x_prev, y_prev, length);
	render_vertical_line(x, y, length);
}

#ifdef __DBG__
void render_debug(char* debugMsg, uint8_t y_offset)
{
	move_cursor(X_MIN, Y_MAX + y_offset);
	printf("%s", debugMsg);
}
#endif /* __DBG__ */

