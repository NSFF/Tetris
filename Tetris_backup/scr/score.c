/*
 * score.c
 *
 *  Created on: 17 Jan 2016
 *      Author: robin
 */

#include "score.h"


/* determines bonus points when forced falling */
void bonus_points(int falling_block_bonus_points){
	game_score+= falling_block_bonus_points * 5 * (level + 1);
}

/* tests if the level should increase or not */
int level_increase(int score){
	int lvl_list[9]= {250,750,1250,5000,10000,25000,50000,100000,1000000};

	int lvl;
	lvl= level +1;

	if(lvl == 10){
		return 0;
	}
	else if(lvl_list[level]< score){
		level++;
	}
	return 0;
}

/* tests if a full bottom line is there */
int test_full_line(){
	int y,x;
	int full[20]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	for(y=0; y < field_height; y++){
		for(x=0; x < field_width; x++){//if all the blocks on a line aren't ALIVE, that line-value != 0 => not full
			if(field[y][x].form== DEAD){
				full[y]++;
				break;
			}
		}

		if(full[y]==0){
			return y;
		}
	}
	return 0;
}

/* tests and erases a full line if there is one */
int erase_full_line(int n){
	int full_line;
	int i=0;

	while(i==0){

		if(0 < (full_line= test_full_line())){
			int x, y;
			lines++;

			field_start_generation();

			play_sound(clear_sound);
			game_score+= 100 * pow(level+1,n); //found in main.h

				for (y = 0; y < full_line; y++) {
					for (x = 0; x < field_width; x++) {
						next_field[y+1][x].form = field[y][x].form;
						next_field[y+1][x].state = field[y][x].state;
					}
				}
				for(x=0; x < field_width; x++){
					next_field[0][x].form= DEAD;
					next_field[0][x].state= NOT_LANDED;
				}
				field_end_generation();
				n++;
				continue;
			}
		i=1;
	}
	return n;
}
