/*
 * score.h
 *
 *  Created on: 17 Jan 2016
 *      Author: robin
 */

#ifndef SCORE_H_
#define SCORE_H_

#include <math.h>

#include "blocks.h"
#include "sounds.h"
#include "field.h"
#include "game_rules.h"

void bonus_points(int);

int level_increase(int);

int test_full_line();

int erase_full_line(int);

#endif /* SCORE_H_ */
