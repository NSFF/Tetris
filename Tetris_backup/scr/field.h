/*
 * field_new.h
 *
 *  Created on: 8 Dec 2015
 *      Author: robin
 */

#ifndef FIELD_H_
#define FIELD_H_

#include <stdio.h>

#include "blocks.h"
#include "game_rules.h"

extern struct Blocks field[20][10];
extern struct Blocks next_field[20][10];

enum Form get_form(int, int);

enum State get_state(int, int);

void dead_block(int, int);

void alive_block(int, int, enum Form);

void resurrect_player_block(int, int, enum Form);

void kill_player_block(int, int, enum Form);

void update_player_block(int, int, enum Form);

void initialize_field();

static void copy_field(struct Blocks [20][10], struct Blocks [20][10]);

void field_start_generation();

void field_end_generation();

#endif /* FIELD_H_ */
