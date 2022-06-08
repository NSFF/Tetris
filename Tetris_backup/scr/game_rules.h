/*
 * game_restrictions.h
 *
 *  Created on: 7 Dec 2015
 *      Author: robin
 */

#ifndef GAME_RULES_H_
#define GAME_RULES_H_

#include <sys/time.h>
#include <SDL/SDL_mixer.h>
#include <math.h>

#include "blocks.h"
#include "sounds.h"
#include "field.h"
#include "time_functions.h"

/* used in main.c and game_rules.c */
extern unsigned int game_score;
extern unsigned int level;
extern unsigned int lines;
extern unsigned int fps_var;
extern int block_collision;

int rotation_collision();

int ground_kick();

int wall_kick();

int side_collision(int, int, enum Form, int);

int lower_collision(int,int,enum Form);

int colide_and_move();

#endif /* GAME_RULES_H_ */
