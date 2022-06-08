/*
 * text.c
 *
 *  Created on: 14 Dec 2015
 *      Author: robin
 */

#include "text.h"

static TTF_Font* font;
static SDL_Surface *text_surface;

/*
 *  loads a font into SDL_ttf so we can render it later on a SDL_texture, in draw_text()
 *
 *  load_font() and draw_text() are heavily inspired by Richard Sweeney
 *  source: http://www.parallelrealities.co.uk/2011/09/basic-game-tutorial-7-sdlttf.html
 */
TTF_Font *load_font(char *name, int size){

	/* Use SDL_TTF to load the font at the specified size */
    font = TTF_OpenFont(name, size);

    if (font == NULL){
        printf(ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET ": Failed to open Font %s: %s\n", name, TTF_GetError());
        exit(1);
    }

    return font;
}

/*
 * renders and blits the text onto the screen
 */
void draw_text(char *name, int size, char *text, int x, int y){

	SDL_Color foregroundColor = {255, 255, 255};//white
	SDL_Color backgroundColor = {0, 0, 0};//black

	/* load_font() returns a loaded TTF_Font and will be rendered by TTF_RenderText_Shaded */
	text_surface = TTF_RenderText_Shaded(load_font(name,size), text, foregroundColor, backgroundColor);

	 if (text_surface == NULL){//error-handling
	        printf(ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET ": Couldn't create String %s: %s\n", text, SDL_GetError());
	        exit(1);
	    }

	//SDL_SetColorKey(textSurface,SDL_SRCCOLORKEY,SDL_MapRGB(window->format,0,0,0));//makes a color in the image transparent
	draw_image(text_surface,x,y);//blits the text onto the screen

	/* free's font memory, !! do not delete this line or huge amount of memory leak will be caused !!*/
	free_text();
}
/*
 * closes/free's the font memory
 */
void free_text(){
	/* we free text_surface every frame because the text_surface can change during the game
	 * this can be written more efficiently but the difference would be small
	 * so we neglect it at the moment.
	 */
	SDL_FreeSurface(text_surface);
	TTF_CloseFont(font);
}
