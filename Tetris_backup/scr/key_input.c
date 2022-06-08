/*
 * key_input.c
 *
 *  Created on: 11 Dec 2015
 *      Author: robin
 */

#include "key_input.h"

static SDL_Event event;

/* extern variables defined in key_input.h and used in GUI.c */
int pause_var= 0;
int pause_box_var= 10000;//we define a big number so we don't end up getting a negative modulo when we decrement it
						//could also be solved with abs()
int highscore_var= 0;
int fps_key_var= 0;

/* when highscore is displayed, check for key_presses */
void highscore_key_press(){
	if (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			exit(1);
		}
		if(event.type == SDL_KEYDOWN){
			SDLKey key_pressed = event.key.keysym.sym;
			switch(key_pressed){
				case SDLK_ESCAPE:
					play_sound(select_sound);
					highscore_var=0;
					break;
			}
		}
	}
}

/* show fps menu */
void fps_menu(){
	switch(pause_box_var % 4){
				case 0:
					draw_image(fps_60_on_img,160,40);
					draw_image(fps_45_off_img,160,140);
					draw_image(fps_30_off_img,160,240);
					draw_image(fps_15_off_img,160,340);
					break;

				case 1:
					draw_image(fps_60_off_img,160,40);
					draw_image(fps_45_on_img,160,140);
					draw_image(fps_30_off_img,160,240);
					draw_image(fps_15_off_img,160,340);
					break;
				case 2:
					draw_image(fps_60_off_img,160,40);
					draw_image(fps_45_off_img,160,140);
					draw_image(fps_30_on_img,160,240);
					draw_image(fps_15_off_img,160,340);
					break;
				case 3:
					draw_image(fps_60_off_img,160,40);
					draw_image(fps_45_off_img,160,140);
					draw_image(fps_30_off_img,160,240);
					draw_image(fps_15_on_img,160,340);
					break;
				default:
					break;
	}
}

/* show right fps_menu and check for key_input */
void fps_key_press(){
	fps_menu();
	if (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			exit(1);
		}
		if(event.type == SDL_KEYDOWN){
			SDLKey key_pressed = event.key.keysym.sym;
			switch(key_pressed){
				case SDLK_ESCAPE:
					play_sound(select_sound);
					fps_key_var=0;
					break;
				case SDLK_UP:
					play_sound(select_sound);
					pause_box_var--;
					//return 1;
					break;
				case SDLK_DOWN:
					play_sound(select_sound);
					pause_box_var++;
					//return 1;
					break;
				case SDLK_RETURN:
					switch(pause_box_var % 4){
					case 0:
						fps_key_var=0;
						fps_var= 60;
						//return 0;
						break;
					case 1://highscore
						fps_key_var=0;
						fps_var= 45;
						//return 1;
						break;
					case 2://quit
						fps_key_var=0;
						fps_var= 30;
						//exit(1);
						//return 1;
						break;
					case 3://fps
						fps_key_var=0;
						fps_var= 15;
						break;
						//return 1;
					default:
						break;
						//return 0;
					}
					break;
					//return 1;
				default:
					break;
					//return 1;

			}

		}
	}
}
/* check if the game is paused or not */
void check_pause(){
	if(pause_var==1){
		turn_music_off();
		while(pause_var==1){
			draw_field();
			sleep(0,15);
		}
		if(sound_music_off_var==0){//if sound is on
			turn_music_on_off();
		}
	}
}

/* show pause_menu */
void pause_menu(){
	switch(pause_box_var % 4){
				case 0:
					draw_image(pause_on_img,120,40);
					draw_image(high_off_img,80,140);
					draw_image(quit_off_img,145,240);
					draw_image(fps_off_img,160,340);
					break;

				case 1:
					draw_image(pause_off_img,120,40);
					draw_image(high_on_img,80,140);
					draw_image(quit_off_img,145,240);
					draw_image(fps_off_img,160,340);
					break;
				case 2:
					draw_image(pause_off_img,120,40);
					draw_image(high_off_img,80,140);
					draw_image(quit_on_img,145,240);
					draw_image(fps_off_img,160,340);
					break;
				case 3:
					draw_image(pause_off_img,120,40);
					draw_image(high_off_img,80,140);
					draw_image(quit_off_img,145,240);
					draw_image(fps_on_img,160,340);
					break;
				default:
					break;
	}
}

/* show right pause_menu and check for key_input */
int pause_key_press(){
	pause_menu();
	if (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			exit(1);
		}
		if(event.type == SDL_KEYDOWN){
			SDLKey key_pressed = event.key.keysym.sym;
			switch(key_pressed){
			case SDLK_ESCAPE:
				return 0;
			case SDLK_p:
				return 0;
			case SDLK_UP:
				play_sound(select_sound);
				pause_box_var--;
				return 1;
			case SDLK_DOWN:
				play_sound(select_sound);
				pause_box_var++;
				return 1;
			case SDLK_RETURN:
				switch(pause_box_var % 4){
				case 0:
					return 0;
				case 1://highscore
					highscore_var= 1;
					return 1;
				case 2://quit
					exit(1);
					return 1;
				case 3://fps
					fps_key_var= 1;
					return 1;
				default:
					return 0;
				}
				return 1;
			default:
				return 1;

			}
			return 1;
		}
		return 1;
	}
	return 1;
}

/* check for keys being pressed */
void key_press(){
	if (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			exit(1);
		}
		if(event.type == SDL_KEYDOWN){
			SDLKey key_pressed = event.key.keysym.sym;

			switch(key_pressed){
			case SDLK_ESCAPE:
				pause_box_var= 10000;
				pause_var=1;
				break;
			case SDLK_p:
				pause_box_var= 10000;
				pause_var=1;
				break;

			case SDLK_RIGHT:
				if(side_collision(x_player,y_player,PLAYER_BLOCK,1)== 0){//if no collision
					x_prev_pos= x_player;
					x_player++;
				}

				break;

			case SDLK_LEFT:
				if(side_collision(x_player,y_player,PLAYER_BLOCK,-1)== 0){// if no collision
					x_prev_pos= x_player;
					x_player--;
				}
				break;

			case SDLK_DOWN:

				kill_player_block(x_prev_pos,y_player,PLAYER_BLOCK);//erase previous position

				int n= 0;

				while(block_collision== 0){
					if(lower_collision(x_player,y_player,PLAYER_BLOCK)== 0){
						y_player++;
						n++;
					}
				}

				bonus_points(n);

				block_collision=0;

				update_player_block(x_player,y_player,PLAYER_BLOCK);
				field_end_generation();
				field_start_generation();

				block_collision= 1;
				break;


			case SDLK_SPACE:
				block_prev_rot= block_rotation;

				kill_player_block(x_player,y_player,PLAYER_BLOCK);

				if(rotation_collision()!=0){//if rotation not possible

					/* wall_kick */
					if((block_rotation % 4)== 0 || (block_rotation % 4)== 2){//you can only wall_kick if vertical
						if(wall_kick()!= 0){
							if(rotation_collision()==0){//if rotation possible
								block_rotation++;
							}
						}
					}

					/* ground_kick */
					else if((block_rotation % 4)== 1 || (block_rotation % 4)== 3){//you can only be ground_kicked if you are horizontal
						if(ground_kick()!= 0 && rotation_collision()== 0){//if ground kick possible
							block_rotation++;
						}

					}
				}
				else{//if rotation possible
					block_rotation++;
				}
				break;

			case SDLK_m:
				if(sound_music_off_var==0){//if sound is on
					sound_music_off_var=1;//turn off
				}
				else{
					sound_music_off_var= 0;
				}

				turn_music_on_off();
				break;
			}
		}
	}
}

