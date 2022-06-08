/*
 * sounds.h
 *
 *  Created on: 12 Dec 2015
 *      Author: robin
 */

#ifndef SOUNDS_H_
#define SOUNDS_H_

#include <stdio.h>

#include "SDL/SDL_mixer.h"
#include "ansi_colors.h"

//The sound effects that will be used
extern Mix_Chunk *select_sound;
extern Mix_Chunk *clear_sound;

extern int sound_music_off_var;

void initialize_SDL_mixer();

void load_sounds();

void turn_music_on_off();

void turn_music_off();

void play_sound(Mix_Chunk *);

void free_sounds();


#endif /* SOUNDS_H_ */
