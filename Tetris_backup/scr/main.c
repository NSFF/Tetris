/*
 * main.c
 *
 *  Created on: 5 Dec 2015
 *      Author: robin
 */
#include "main.h"

/* extern variables defined in blocks.h and used in main.c , field.c and game_rules.c */
int block_rotation= 0;
int block_prev_rot= 0;
enum Form PLAYER_BLOCK;
enum Form next_piece;
int x_player= 5;
int y_player= -3;
int x_prev_pos= 5;
int y_prev_pos= -3;
int field_width= 10;
int field_height= 20;

/* extern variables defined in game_rules.h */
unsigned int game_score= 0;
unsigned int lines= 0;
unsigned int level= 0;
unsigned int fps_var= 60;
int block_collision= 0;

int main(){

	srand((unsigned)time(NULL));//random seed based on current time
	PLAYER_BLOCK= rand() % 7 +2;
	next_piece= rand() % 7 +2;

	int next_fall_wait_time;
	int list_lvl[10]= {1000, 500, 350, 250, 150, 100, 75, 50, 30, 5};// list of next_fall_wait_times per level

	struct timeval stop, start;//start and stop time from <sys/time.h>
	float elapsed_time, delta_t;

	elapsed_time= 0;
	next_fall_wait_time= list_lvl[level];//1000, 500, 350, 250, 150, 100 ,75 , 50 ,40

	initialize_field();
	initialize_gui();//found in GUI.c
	clear_screen();
	draw_field();//found in GUI.c
				 //visualises the field in a window

	turn_music_on_off();

	printf("\033[2J");//clears terminal screen

	while(1){

		next_fall_wait_time= list_lvl[level];
		//next_fall_wait_time= 350;//testing purpose


		field_start_generation();
		key_press();
		field_end_generation();

		level_increase(game_score);//update score

		check_pause();//check if the pause button is being held

		gettimeofday(&start, NULL);//gets current time
		if(elapsed_time>next_fall_wait_time || block_collision== 1){

			field_start_generation();
			clear_player_block(x_prev_pos,y_player,PLAYER_BLOCK);

			if(block_collision==0){
				update_player_block(x_player,++y_player,PLAYER_BLOCK);
			}

			if(block_collision==1){
				/* checks for full lines, game overs or initialises new player_blocks */
				if_block_collision(); // found in main.c below
			}
			elapsed_time= 0.0f;
			continue;
		}

		field_start_generation();

		if(x_prev_pos-x_player != 0 || block_prev_rot-block_rotation !=0){// if change in x position or rotation
			kill_player_block(x_prev_pos,y_player,PLAYER_BLOCK);
		}

		update_player_block(x_player,y_player,PLAYER_BLOCK);

		sleep(0,fps(fps_var));
		gettimeofday(&stop, NULL);

		delta_t= timedifference_msec(start,stop);
		elapsed_time+= timedifference_msec(start,stop);

		//ANSI_COLOR can be found in ansi_colors.h, it gives color to strings
		printf("fps = " ANSI_COLOR_YELLOW "%0.1f" ANSI_COLOR_RESET "				"
				"Code calculated and in" ANSI_COLOR_YELLOW " %0.4f " ANSI_COLOR_RESET "milliseconds.			"
				"\r", 1000/delta_t, delta_t-fps(fps_var));
		fflush(stdout);//flushes outputbuffer of the output stream
	}

	return 0;
}

/* checks for full lines, game overs or new blocks */
void if_block_collision(){
	if(erase_full_line(1)==1){//if no line erased
		if(colide_and_move()== 0){//if no block is beneath, keep falling
			block_collision=0;
			return;
		}
	}
	if(y_player<=-1){
		printf("\nGAME OVER! \nstats:\n\t"
				"Score= " ANSI_COLOR_YELLOW "%d"ANSI_COLOR_RESET "\n\t"
				"Number of lines= " ANSI_COLOR_YELLOW "%d"ANSI_COLOR_RESET "\n\t"
				"Level reached= "ANSI_COLOR_YELLOW "%d"ANSI_COLOR_RESET "\n",game_score, lines, level+1);
		highscore_var= 1;// found in key_input.h
		draw_field();
		sleep(10,0);
		exit(1);
	}
	block_collision=0;
	y_player=-3;
	x_player= 5;
	block_rotation=0;
	PLAYER_BLOCK= next_piece;
	next_piece= rand() % 7 +2;
}
