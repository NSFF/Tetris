/*
 * highscore.c
 *
 *  Created on: 16 Dec 2015
 *      Author: robin
 */

#include "highscore.h"

static char text_highscore[11][20];//we chose 11 numbers and print only 10,
								   //so we can use 1 number as a buffer when the game ends and sorts the score
static int highscore_values[11];


int cmpfunc (const void * a, const void * b){
	return ( *(int*)b - *(int*)a );
}

void quick_sort_highscore(){
	qsort(highscore_values, sizeof(highscore_values)/sizeof(int), sizeof(int), cmpfunc);
}


void load_highscore(int game_score){
	FILE *text_file;

	char *file_name= "highscore.txt";

	if ((text_file= fopen(file_name,"r+"))== NULL){//testing if the file exists or not
		/* ANSI colors found in ansi_colors.h */
		printf(ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET ": file %s does not exist or could not be opened.\n",file_name);
		exit(1);
	}

	int i;

	/* get all the values out of the text_file */
	for(i=0;i < 11;i++){
		fscanf(text_file, "%d", &highscore_values[i]);
	}

	highscore_values[10]= game_score;//lowest value in existing list is the new value that will be sorted

	quick_sort_highscore();

	fseek(text_file, 0, SEEK_SET);

	/* puts the sorted values back in the file and attach them as a string to text_highscore[] */
	for(i=0; i < 11 ;i++){
		fprintf(text_file,"%i\n",highscore_values[i]);
		sprintf(text_highscore[i],"%d. %d",i+1,highscore_values[i]);
	}

	fclose(text_file);

}
/* draw and recalculate highscore */
void draw_highscore(unsigned int game_score){
	int i;

	load_highscore(game_score);
	draw_image(high_list_img,110,40);

	for(i=0;i<10;i++){
		draw_text("font/Eras_Demi_ITC.ttf",20,text_highscore[i],160,75 +(i* 25));
	}
	SDL_Flip(window);//switch to rendered image stored in the buffer
}
