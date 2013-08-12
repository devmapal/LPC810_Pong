/*
 * pong_ball.h
 *
 *  Created on: Aug 11, 2013
 *      Author: devmapal
 */

#ifndef PONG_BALL_H_
#define PONG_BALL_H_

#include <stdint.h>

// direction defines
#define W	0
#define NW	1
#define NE	2
#define E	3
#define SE	4
#define SW	5

typedef struct
{
	uint8_t x,y;
	uint8_t direction;
} PONG_BALL_T;

extern PONG_BALL_T ball;

void ball_init(uint8_t x, uint8_t y, uint8_t direction);
void ball_step();

#endif /* PONG_BALL_H_ */
