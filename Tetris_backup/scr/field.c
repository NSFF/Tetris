/*
 * field.c
 *
 *  Created on: 6 Dec 2015
 *      Author: robin
 */

#include "field.h"

struct Blocks field[20][10];
struct Blocks next_field[20][10];

/* gets the type of block in a certain cell */
enum Form get_form(int x, int y){
	if(field_height<=y || field_width<= x || x<0){
		return ALIVE;
	}
	else if(y< 0){
		return DEAD;
	}
	return field[y][x].form;
}

/* gets the state of a block in a certain cell */
enum State get_state(int x, int y){
	if(field_height<=y || field_width<= x || x<0){
			return LANDED;
	}
	else if(y< 0){
		return NOT_LANDED;
	}
	return field[y][x].state;
}

/* kills a block in current field */
void dead_block(int x, int y){
	if(-1< y || y < field_height || x < field_width || -1 < x){
		field[y][x].form= DEAD;
		field[y][x].state= NOT_LANDED;
	}
}

/* makes a block alive in the next field */
void alive_block(int x, int y, enum Form form){
	if(-1< y || y < field_height || x < field_width || -1 < x){
		next_field[y][x].form= form;
	}
}

/*
 * initializes a tetris field full of DEAD NOT_LANDED blocks
 * this must be called only once in main.c
 */
void initialize_field(){

	int i,j;

	for(i=0; i<field_height;i++){
		for(j=0; j<field_width;j++){

			field[i][j].form= DEAD;
			field[i][j].state= NOT_LANDED;

			next_field[i][j].form= DEAD;
			next_field[i][j].state= NOT_LANDED;
		}
	}
	field_end_generation();
}

/*
 * copies a field of blocks to another field
 */
static void copy_field(struct Blocks from_field[20][10], struct Blocks to_field[20][10]) {
	int x, y;
	for (y = 0; y < field_height; y++) {
		for (x = 0; x < field_width; x++) {
			to_field[y][x].form = from_field[y][x].form;
			to_field[y][x].state = from_field[y][x].state;
		}
	}
}

/*
 * copies field onto next_field
 */
void field_start_generation() {
	copy_field(field, next_field);
}

/*
 * copies next_field onto field
 */
void field_end_generation() {
	copy_field(next_field, field);
}

/* resurrects player_block */
void resurrect_player_block(int x, int y, enum Form form){
	int i,j;
	for(i=0; i<4;i++){
		for(j=0;j<4;j++){
			if((tetromino[form-2][block_rotation % 4][i][j])>0 && -1<(x+j) && (x+j)<field_width && -1<(y+i) && (y+i)<field_height){
				alive_block(x+j, y+i,form);
			}
		}
	}
}

/* resurrects player_block if there is no collision */
void update_player_block(int x,int y, enum Form form){
	if(block_collision==0){
		resurrect_player_block(x,y,form);
		field_end_generation();

		draw_field();

		/* reseting some standard values */
		y_prev_pos= y_player;
		x_prev_pos= x_player;
		block_prev_rot= block_rotation;
	}
}

/* kills a tetromino_block in current field */
void kill_player_block(int x, int y, enum Form form){
	int i,j;
	for(i=0; i<4;i++){
		for(j=0;j<4;j++){
			if((tetromino[form-2][block_prev_rot % 4][i][j])>0 && -1<(x+j) && (x+j)<field_width && -1<(y+i) && (y+i)<field_height){
				dead_block(x+j, y+i);
			}
		}
	}
	field_start_generation();
}
/*
 * should be called after field_start_generation()
 */
void clear_player_block(int x,int y, enum Form form){
	if(lower_collision(x,y,form)== 0){
		kill_player_block(x,y,form);
	}
	else{
		field_end_generation();
	}
}
