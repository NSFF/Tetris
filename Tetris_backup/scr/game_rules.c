/*
 * game_restrictions.c
 *
 *  Created on: 7 Dec 2015
 *      Author: robin
 */

#include "game_rules.h"

/* checks if a block can rotate without interfering with another block or not */
int rotation_collision(){
	unsigned int i,j;

	for(i=0; i<4;i++){
		for(j=0;j<4;j++){
			if ((tetromino[PLAYER_BLOCK-2][(block_rotation+1) % 4][i][j])>0){
				if((get_form(x_player+j,y_player+i)== DEAD || get_state(x_player+j,y_player+i)== NOT_LANDED)){
					continue;
				}
				else{//if not able to rotate
					return -1;
				}
			}
		}
	}
	return 0;
}

/* checks if a ground_kick is possible and if so, do the ground kick */
int ground_kick(){
	unsigned int block_height;
	unsigned int n= 0;
	unsigned int m= 0;//backup variable to stop while-loop when no collision detected

	//TODO make more efficient
	if(PLAYER_BLOCK==I){
		block_height= 4;
	}
	else{
		block_height= 3;
	}
	while(m< (block_height+1)){
		if(n<block_height){
			unsigned int i,j;

			for(i=0; i<4;i++){
				for(j=0;j<4;j++){
					if ((tetromino[PLAYER_BLOCK-2][(block_rotation+1) % 4][i][j])>0){
						if((get_form(x_player+j,y_player+i)== DEAD || get_state(x_player+j,y_player+i)== NOT_LANDED)){
							continue;
						}
						else{// if collision
							y_player--;
							n++;
							i=j=4;break;//break loop
						}
					}
				}
			}
		}
		else{// if ground_kick not possible
			y_player+= n;
			m=5;n=0;break;//break loop
		}
		m++;
	}
	return n;
}

/* checks if a wall_kick is possible and if so, do the wall kick */
int wall_kick(){
	unsigned int block_height;
	unsigned int n= 0;
	unsigned int m= 0;//backup variable to stop while-loop when no collision detected

	if(PLAYER_BLOCK==I){
		block_height= 4;
	}
	else{
		block_height= 3;
	}
	while(m< block_height && n < block_height){
		unsigned int i,j;

		for(i=0; i<4;i++){
			for(j=0;j<4;j++){
				if ((tetromino[PLAYER_BLOCK-2][(block_rotation+1) % 4][i][j])>0){
					if((get_form(x_player+j,y_player+i)== DEAD || get_state(x_player+j,y_player+i)== NOT_LANDED)){
						continue;
					}
					else{// if collision

						/* stop the loop when outside of the field */
						if(x_player <=0){
							x_player+= n;
							i=j=m=4;break;//break loop
						}

						x_player--;

						/* prevents a bug when landing: the block would not rotate and go 4 spaces to the left side */
						if((++n) >= block_height){
							x_player+= n;
							i=j=m=4;break;//break loop
						}
						i=j=4;break;//break loop
					}
				}
			}
		}
		m++;
	}
	return n;
}

/* checks if there is collision on the side of the player_block,
 *  mostly used in key_input to go to the right and left */
int side_collision(int x, int y, enum Form form, int which_side){//called in key_input.c
	unsigned int i,j;

	for(i=0; i<4;i++){
		for(j=0;j<4;j++){
			if ((tetromino[form-2][block_prev_rot % 4][i][j])>0){//test x-1 and x+1 (= sides of teromino block)
				if((get_form(x+j+which_side,y+i)== DEAD || get_state(x+j+which_side,y+i)== NOT_LANDED)){
					continue;
				}
				else{
					return -1;
				}
			}
		}
	}
	return 0;
}
/* checks a block beneath the player_block to see if there is collision */
int lower_collision(int x,int y, enum Form form){//called in field.c
	int i,j;
	y++;//look at next line of falling

	for(i=0; i<4;i++){
		for(j=0;j<4;j++){
			if ((tetromino[form-2][block_prev_rot % 4][i][j])>0){
				if((y+i)< field_height && (get_form(x+j,y+i)== DEAD || get_state(x+j,y+i)== NOT_LANDED)){
					continue;
				}
				else{// if collision, make player block state landed
					for(i=0; i<4;i++){
						for(j=0;j<4;j++){
							if ((tetromino[form-2][block_prev_rot % 4][i][j])>0 && -1 < y+i-1){
								next_field[y+i-1][x+j].state= LANDED;
							}
						}
					}
					block_collision= 1;
					return -1;
				}
			}
		}
	}
	return 0;
}

/* this function handles: when fallen, you can still move and rotate to alter your end result */
int colide_and_move(){//TODO: I block plat kan nog steeds heen en weer gaan... check key_press()
	int elapsed_time;
	struct timeval stop, start;//start and stop time from <sys/time.h>

	elapsed_time= 0;

	kill_player_block(x_player,y_player,PLAYER_BLOCK);
	field_end_generation();

	while(elapsed_time < 1000){
		gettimeofday(&start, NULL);//gets current time

		block_collision= 1;

		key_press();

		check_pause();//check if the pause button is being held

		field_start_generation();

		if(x_prev_pos-x_player != 0 || block_prev_rot-block_rotation != 0){
			kill_player_block(x_prev_pos,y_prev_pos,PLAYER_BLOCK);
		}

		block_collision= 0;
		update_player_block(x_player,y_player,PLAYER_BLOCK);

		if(lower_collision(x_player,y_player,PLAYER_BLOCK)== 0){//if the block can still fall, we break the loop
			kill_player_block(x_player,y_player,PLAYER_BLOCK);
			return 0;
		}

		sleep(0,fps(fps_var));
		gettimeofday(&stop, NULL);

		elapsed_time+= timedifference_msec(start,stop);
	}

		clear_player_block(x_player,y_player, PLAYER_BLOCK);

		field_end_generation();
		block_collision=1;

		return -1;
}

