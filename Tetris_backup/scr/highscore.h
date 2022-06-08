/*
 * highscore.h
 *
 *  Created on: 16 Dec 2015
 *      Author: robin
 */

#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#include <stdio.h>
#include <stdlib.h>
#include "GUI.h"
#include "ansi_colors.h"

int cmpfunc (const void *, const void *);

void quick_sort_highscore();

void load_highscore(int);

void draw_highscore(unsigned int);

#endif /* HIGHSCORE_H_ */
