/*
 * renderer.h
 *
 *  Created on: Aug 8, 2013
 *      Author: devmapal
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <stdint.h>

void init();
void hide_cursor();
void show_cursor();
void clear_screen();
void move_cursor(uint8_t x, uint8_t y);
void renderer_ball(uint8_t x, uint8_t y, uint8_t x_prev, uint8_t y_prev);
void renderer_pong_bat(uint8_t x, uint8_t y, uint8_t x_prev, uint8_t y_prev, uint8_t length);
void render_score(uint8_t x, uint8_t y, uint8_t num);
#ifdef __DBG__
void render_debug(char* debugMsg, uint8_t y_offset);
#endif /* __DBG__ */

#endif /* RENDERER_H_ */
