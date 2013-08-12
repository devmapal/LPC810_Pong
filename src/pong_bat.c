/*
 * pong_bat.c
 *
 *  Created on: Aug 12, 2013
 *      Author: costa
 */

#include "pong_bat.h"
#include "pong_field.h"
#include "renderer.h"
#include "uart.h"


PONG_BAT_T bat1;
PONG_BAT_T bat2;


int check_batLimits(PONG_BAT_T bat, uint8_t y)
{
	int y_new = bat.y;
	if(((y + bat.length) <= Y_MAX) && (y > Y_MIN))
		y_new = y;

	return y_new;
}



void bat_init(uint8_t x_offset, uint8_t y, uint8_t bat_length)
{
	bat1.x = X_MIN + x_offset;
	bat2.x = X_MAX - x_offset;
	bat1.y = y;
	bat2.y = y;

	bat1.length = bat_length;
	bat2.length = bat_length;

	renderer_pong_bat(bat1.x, bat1.y, bat1.x, bat1.y, bat1.length);
	renderer_pong_bat(bat2.x, bat2.y, bat2.x, bat2.y, bat2.length);
}

void bat_step()
{
	char playerAction;
	playerAction = uart0ReceiveChar();

	if(playerAction)
	{
		uint8_t prevBat1_y = bat1.y;
		uint8_t prevBat2_y = bat2.y;

		switch(playerAction)
		{
		case 'w':
			bat1.y = check_batLimits(bat1, (bat1.y - 2));
			renderer_pong_bat(bat1.x, bat1.y, bat1.x, prevBat1_y, bat1.length);
			break;
		case 's':
			bat1.y = check_batLimits(bat1, (bat1.y + 2));
			renderer_pong_bat(bat1.x, bat1.y, bat1.x, prevBat1_y, bat1.length);
			break;
		case 'o':
			bat2.y = check_batLimits(bat2, (bat2.y - 2));
			renderer_pong_bat(bat2.x, bat2.y, bat2.x, prevBat2_y, bat2.length);
			break;
		case 'l':
			bat2.y = check_batLimits(bat2, (bat2.y + 2));
			renderer_pong_bat(bat2.x, bat2.y, bat2.x, prevBat2_y, bat2.length);
			break;
		}
	}
}
