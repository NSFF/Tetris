/*
 * key_input.h
 *
 *  Created on: 11 Dec 2015
 *      Author: robin
 */

#ifndef KEY_INPUT_H_
#define KEY_INPUT_H_

#include "SDL/SDL.h"
#include "blocks.h"
#include "sounds.h"
#include "game_rules.h"
#include "GUI.h"

/* used in main.c and GUI.c */
extern int pause_var;
extern int pause_box_var;
extern int highscore_var;
extern int fps_key_var;

void highscore_key_press();

void check_pause();

void fps_menu();

void pause_menu();

int pause_key_press();

void key_press();

#endif /* KEY_INPUT_H_ */
