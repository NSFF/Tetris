/*
 * sounds.c
 *
 *  Created on: 12 Dec 2015
 *      Author: robin
 */

#include "sounds.h"

//The music that will be played
static Mix_Music *music = NULL;
Mix_Chunk *select_sound = NULL;
Mix_Chunk *clear_sound = NULL;
Mix_Chunk *drop_sound= NULL;

/* extern variable defined in sounds.h */
int sound_music_off_var= 0;

/*
 * heavily inspired by the following site:
 * http://lazyfoo.net/SDL_tutorials/lesson11/
 */
void initialize_SDL_mixer(){
	//Initialize SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
		printf(ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET ":Couldn't initialize SDL_mixer: %s\n", SDL_GetError());
		exit(1);
	}
}

void load_sounds(){
	// load music
	 music= Mix_LoadMUS( "sounds/tetris_music.wav" );

	 //load sounds
	 select_sound= Mix_LoadWAV( "sounds/select.wav" );
	 clear_sound= Mix_LoadWAV( "sounds/clear.wav" );
	 drop_sound= Mix_LoadWAV("sounds/drop.wav");

	 //If there was a problem loading the music or sound
	 if( music == NULL || select_sound == NULL || clear_sound== NULL || drop_sound== NULL){
		 printf(ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET ":Couldn't load sound or music: %s\n", SDL_GetError());
		 exit(1);
	 }
}
/* toggle function to turn music on or off */
void turn_music_on_off(){

	//If there is no music playing
	if(Mix_PlayingMusic() == 0 ){
		//Play the music
		if( Mix_PlayMusic(music, -1 ) == -1 ){
			printf(ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET ":Couldn't play music: %s\n", SDL_GetError());
			exit(1);
		}
	}
	//If music is being played
	else{
		//If the music is paused
		if(Mix_PausedMusic() == 1 ){
			//Resume the music
			Mix_ResumeMusic();
		} //If the music is playing
		else{
			//Pause the music
			Mix_PauseMusic();
		}
	}
}

void turn_music_off(){
	Mix_PauseMusic();
}

void play_sound(Mix_Chunk *sound_effect){
	if(sound_music_off_var==0){//if sound is on
		Mix_PlayChannel( -1, sound_effect, 0 );
	}
}

void free_sounds(){;
	Mix_FreeChunk(clear_sound);
	Mix_FreeChunk(select_sound);

	Mix_FreeMusic(music);
}
