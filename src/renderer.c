/*
 * renderer.c
 *
 *  Created on: Aug 8, 2013
 *      Author: devmapal
 */

#include "renderer.h"
#include <stdio.h>

#define X_MIN 1
#define X_MAX 80
#define Y_MIN 1
#define Y_MAX 48

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

int valid_pos(int x, int y)
{
	if(x >= X_MIN && x <= X_MAX)
	{
		if(y >= Y_MIN && y <= Y_MAX)
			return 1;
	}

	return 0;
}

void move_cursor(int x, int y)
{
	if( !valid_pos(x, y) )
		return;

	y /= 2;
	printf("\033[%d;%dH", y, x);
}
