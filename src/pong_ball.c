/*
 * pong_ball.c
 *
 *  Created on: Aug 11, 2013
 *      Author: devmapal
 */

#include "pong_ball.h"
#include "pong_field.h"
#include "renderer.h"


PONG_BALL_T ball;


void ball_init(uint8_t x, uint8_t y, uint8_t direction)
{
	ball.x = x;
	ball.y = y;
	ball.direction = direction;
}

void ball_step()
{
	int i;
	for(i = 0; i < 2; ++i)
	{
		if(ball.x == X_MIN)
		{
			if( ball.direction == W )
				ball.direction = E;
			else if( ball.direction == NW )
				ball.direction = NE;
			else if( ball.direction == SW )
				ball.direction = SE;
		}
		else if(ball.x == X_MAX)
		{
			if( ball.direction == E )
				ball.direction = W;
			else if( ball.direction == NE )
				ball.direction = NW;
			else if( ball.direction == SE )
				ball.direction = SW;
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

	uint8_t prev_x = ball.x;
	uint8_t prev_y = ball.y;
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
