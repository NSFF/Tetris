/*
 * blocks.c
 *
 *  Created on: 10 Dec 2015
 *      Author: robin
 */

#include "blocks.h"


/*
 * All tetromino's and their rotations described in a 4x4 grid
 * 1= Block 0= No Block
 * example: {{1,1,1,1},{0,...},{...},{...,0}} = 4 blocks horizontally, also known as the I tetromino
 *
 * tetromino's O,I,S,Z,L,J and T are listed here
 */
int *O_DEG_0[4][4]= {(int []){1,1,0,0},(int []){1,1,0,0},(int []){0,0,0,0},(int []){0,0,0,0}};

int *I_DEG_0[4][4]= {(int []){1,0,0,0},(int []){1,0,0,0},(int []){1,0,0,0},(int []){1,0,0,0}};
int *I_DEG_180[4][4]= {(int []){1,1,1,1},(int []){0,0,0,0},(int []){0,0,0,0},(int []){0,0,0,0}};

int *S_DEG_0[4][4]= {(int []){1,0,0,0},(int []){1,1,0,0},(int []){0,1,0,0},(int []){0,0,0,0}};
int *S_DEG_180[4][4]= {(int []){0,1,1,0},(int []){1,1,0,0},(int []){0,0,0,0},(int []){0,0,0,0}};

int *Z_DEG_0[4][4]= {(int []){0,1,0,0},(int []){1,1,0,0},(int []){1,0,0,0},(int []){0,0,0,0}};
int *Z_DEG_180[4][4]= {(int []){1,1,0,0},(int []){0,1,1,0},(int []){0,0,0,0},(int []){0,0,0,0}};

int *L_DEG_0[4][4]= {(int []){1,0,0,0},(int []){1,0,0,0},(int []){1,1,0,0},(int []){0,0,0,0}};
int *L_DEG_90[4][4]= {(int []){0,0,1,0},(int []){1,1,1,0},(int []){0,0,0,0},(int []){0,0,0,0}};
int *L_DEG_180[4][4]= {(int []){1,1,0,0},(int []){0,1,0,0},(int []){0,1,0,0},(int []){0,0,0,0}};
int *L_DEG_270[4][4]= {(int []){1,1,1,0},(int []){1,0,0,0},(int []){0,0,0,0},(int []){0,0,0,0}};

int *J_DEG_0[4][4]= {(int []){0,1,0,0},(int []){0,1,0,0},(int []){1,1,0,0},(int []){0,0,0,0}};
int *J_DEG_90[4][4]= {(int []){1,0,0,0},(int []){1,1,1,0},(int []){0,0,0,0},(int []){0,0,0,0}};
int *J_DEG_180[4][4]= {(int []){1,1,0,0},(int []){1,0,0,0},(int []){1,0,0,0},(int []){0,0,0,0}};
int *J_DEG_270[4][4]= {(int []){1,1,1,0},(int []){0,0,1,0},(int []){0,0,0,0},(int []){0,0,0,0}};

int *T_DEG_0[4][4]= {(int []){0,1,0,0},(int []){1,1,0,0},(int []){0,1,0,0},(int []){0,0,0,0}};
int *T_DEG_90[4][4]= {(int []){1,1,1,0},(int []){0,1,0,0},(int []){0,0,0,0},(int []){0,0,0,0}};
int *T_DEG_180[4][4]= {(int []){1,0,0,0},(int []){1,1,0,0},(int []){1,0,0,0},(int []){0,0,0,0}};
int *T_DEG_270[4][4]= {(int []){0,1,0,0},(int []){1,1,1,0},(int []){0,0,0,0},(int []){0,0,0,0}};

/*
 * all tetromino's and their rotations in 1 big array so we can easily choose which one we want
 * example: *tetromino[O-2][block_rotation][0][0] => will give you O_DEG_0[0][0]
 *
 * mainly used in field.c and game_rules.c
 */
int **tetromino[7][4]= {{*O_DEG_0,*O_DEG_0,*O_DEG_0,*O_DEG_0},
						{*I_DEG_0,*I_DEG_180,*I_DEG_0,*I_DEG_180},
						{*S_DEG_0,*S_DEG_180,*S_DEG_0,*S_DEG_180},
						{*Z_DEG_0,*Z_DEG_180,*Z_DEG_0,*Z_DEG_180},
						{*L_DEG_0,*L_DEG_90,*L_DEG_180,*L_DEG_270},
						{*J_DEG_0,*J_DEG_90,*J_DEG_180,*J_DEG_270},
						{*T_DEG_0,*T_DEG_90,*T_DEG_180,*T_DEG_270}};
