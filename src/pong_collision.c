/*
 * pong_collision.c
 *
 *  Created on: Aug 12, 2013
 *      Author: costa
 */

#include "pong_ball.h"
#include "pong_bat.h"


void calculate_collision(PONG_BALL_T ball, PONG_BAT_T bat1, PONG_BAT_T bat2)
{
	//Collision detection for bat1:
	if((ball.x == bat1.x) || (ball.x == (bat1.x +1)))
	{
		uint8_t bat1_y1 = bat1.y;
		uint8_t bat1_y2 = bat1.y + bat1.length * 1/3;
		uint8_t bat1_y3 = bat1.y + bat1.length * 2/3;
		uint8_t bat1_y4 = bat1.y + bat1.length;

		//If ball is generally at bat's position:
		if((ball.y >= bat1_y1) && (ball.y <= bat1_y4))
		{
			//If ball is in section 1:
			if((ball.y >= bat1_y1) && (ball.y <= bat1_y2))
			{
				ball.direction = NE;
			}
			//If ball is in section 2:
			else if((ball.y >= bat1_y2) && (ball.y <= bat1_y3))
			{
				ball.direction = E;
			}
			//If ball is in section 3:
			else if((ball.y >= bat1_y3) && (ball.y <= bat1_y4))
			{
				ball.direction = SE;
			}
		}
	}

	//Collision detection for bat2:
	if((ball.x == bat2.x) || (ball.x == (bat2.x +1)))
	{
		uint8_t bat2_y1 = bat2.y;
		uint8_t bat2_y2 = bat2.y + bat2.length * 1/3;
		uint8_t bat2_y3 = bat2.y + bat2.length * 2/3;
		uint8_t bat2_y4 = bat2.y + bat2.length;

		//If ball is generally at bat's position:
		if((ball.y >= bat2_y1) && (ball.y <= bat2_y4))
		{
			//If ball is in section 1:
			if((ball.y >= bat2_y1) && (ball.y <= bat2_y2))
			{
				ball.direction = NE;
			}
			//If ball is in section 2:
			else if((ball.y >= bat2_y2) && (ball.y <= bat2_y3))
			{
				ball.direction = E;
			}
			//If ball is in section 3:
			else if((ball.y >= bat2_y3) && (ball.y <= bat2_y4))
			{
				ball.direction = SE;
			}
		}
	}
}
