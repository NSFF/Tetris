/*
 * text.h
 *
 *  Created on: 14 Dec 2015
 *      Author: robin
 */

#ifndef TEXT_H_
#define TEXT_H_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "ansi_colors.h"

TTF_Font *load_font(char *, int);

void draw_text(char *, int, char *, int, int);

void free_text();


#endif /* TEXT_H_ */
