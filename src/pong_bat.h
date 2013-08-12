/*
 * pong_bat.h
 *
 *  Created on: Aug 12, 2013
 *      Author: costa
 */

#ifndef PONG_BAT_H_
#define PONG_BAT_H_

#include <stdint.h>


typedef struct
{
	uint8_t x,y;
	uint8_t length;
} PONG_BAT_T;

extern PONG_BAT_T bat1;
extern PONG_BAT_T bat2;

void bat_init(uint8_t x_offset, uint8_t y, uint8_t bat_length);
void bat_step();


#endif /* PONG_BAT_H_ */
