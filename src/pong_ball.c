/*
 * pong_ball.c
 *
 *  Created on: Aug 11, 2013
 *      Author: devmapal
 */

#include "pong_ball.h"
#include "pong_field.h"
#include "renderer.h"
#include "player.h"


PONG_BALL_T ball;
uint8_t player1_points;
uint8_t player2_points;


void ball_init(uint8_t x, uint8_t y, uint8_t direction)
{
	ball.x = x;
	ball.y = y;
	ball.direction = direction;
}

void ball_step()
{
	uint8_t i;
	uint8_t prev_x = ball.x;
	uint8_t prev_y = ball.y;
	for(i = 0; i < 2; ++i)
	{
		if(ball.x == X_MIN)
		{
			delete_scores();
			++player2_points;
			prev_x = ball.x;
			ball.x = X_MIN + (X_MAX-X_MIN)/2;
			switch(ball.y%3)
			{
			case 0:
				ball.direction = SW;
				break;
			case 1:
				ball.direction = W;
				break;
			case 2:
				ball.direction = NW;
				break;
			}
		}
		else if(ball.x == X_MAX)
		{
			delete_scores();
			++player1_points;
			prev_x = ball.x;
			ball.x = X_MIN + (X_MAX-X_MIN)/2;
			switch(ball.y%3)
			{
			case 0:
				ball.direction = SE;
				break;
			case 1:
				ball.direction = E;
				break;
			case 2:
				ball.direction = NE;
				break;
			}
		}

		if(ball.y == Y_MIN)
		{
			if( ball.direction == NW )
				ball.direction = SW;
			else if( ball.direction == NE )
				ball.direction = SE;
		}
		else if(ball.y == Y_MAX)
		{
			if( ball.direction == SE )
				ball.direction = NE;
			else if( ball.direction == SW )
				ball.direction = NW;
		}
	}

	switch(ball.direction)
	{
	case W:
		--ball.x;
		renderer_ball(ball.x, ball.y, prev_x, prev_y);
		break;
	case NW:
		--ball.x;
		--ball.y;
		renderer_ball(ball.x, ball.y, prev_x, prev_y);
		break;
	case NE:
		++ball.x;
		--ball.y;
		renderer_ball(ball.x, ball.y, prev_x, prev_y);
		break;
	case E:
		++ball.x;
		renderer_ball(ball.x, ball.y, prev_x, prev_y);
		break;
	case SE:
		++ball.x;
		++ball.y;
		renderer_ball(ball.x, ball.y, prev_x, prev_y);
		break;
	case SW:
		--ball.x;
		++ball.y;
		renderer_ball(ball.x, ball.y, prev_x, prev_y);
		break;
	}
}
