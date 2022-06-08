/*
 * blocks.h
 *
 *  Created on: 10 Dec 2015
 *      Author: robin
 */

#ifndef BLOCKS_H_
#define BLOCKS_H_

extern int x_player,x_prev_pos,y_prev_pos, y_player;
extern int field_width, field_height;

extern int block_rotation, block_prev_rot;

extern enum Form PLAYER_BLOCK, next_piece;

/* 4x4 grids of all rotations needed for each tetromino */

extern int *O_DEG_0[4][4]; //0 degrees

extern int *I_DEG_0[4][4];
extern int *I_DEG_180[4][4]; //180 degrees


extern int *S_DEG_0[4][4];
extern int *S_DEG_180[4][4];

extern int *Z_DEG_0[4][4];
extern int *Z_DEG_180[4][4];

extern int *L_DEG_0[4][4];
extern int *L_DEG_90[4][4];
extern int *L_DEG_180[4][4];
extern int *L_DEG_270[4][4];

extern int *J_DEG_0[4][4];
extern int *J_DEG_90[4][4];
extern int *J_DEG_180[4][4];
extern int *J_DEG_270[4][4];

extern int *T_DEG_0[4][4];
extern int *T_DEG_90[4][4];
extern int *T_DEG_180[4][4];
extern int *T_DEG_270[4][4];

extern int **tetromino[7][4];

/*
 * Describes which tetromino equals which number in the allocated field
 * in alocate_field.c
 *
 * DEAD and ALIVE are used when there is no block or when we want a neutral block
 */
enum Form{
	DEAD= 0,
	ALIVE=1,
	O= 2,
	I= 3,
	S= 4,
	Z= 5,
	L= 6,
	J= 7,
	T= 8
};

enum State{
	LANDED,
	NOT_LANDED
};

struct Blocks{
	enum Form form;
	enum State state;
};

#endif /* BLOCKS_H_ */
