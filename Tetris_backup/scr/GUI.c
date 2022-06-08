#include "GUI.h"

/*
 * Dit is het venster dat getoond zal worden en waarin het speelveld weergegeven wordt.
 * Dit venster wordt aangemaakt bij het initialiseren van de GUI en wordt weer afgebroken
 * wanneer het spel ten einde komt.
 */
SDL_Surface *window;

static char text_score[20];
static char text_line[10];
static char text_level[20];

static SDL_Surface *grid_img;
static SDL_Surface *O_img;
static SDL_Surface *I_img;
static SDL_Surface *J_img;
static SDL_Surface *L_img;
static SDL_Surface *Z_img;
static SDL_Surface *S_img;
static SDL_Surface *T_img;

/*
 * Maakt het hele venster terug blanco.
 */
void clear_screen() {
	SDL_FillRect(window, NULL, 0xFFFFFFFF);
	//SDL_Flip(window);
}

/*
 * loads image of any kind of format (JPG, PNG, BMP) and returns an SDL_surface
 * that will be used in draw_image()
 *
 * this code was heavily inspired by Richard Sweeney
 * resource: http://www.parallelrealities.co.uk/2011/09/basic-game-tutorial-2-displaying-image.html
 */
SDL_Surface *load_image(char *name){

	SDL_Surface *temp = IMG_Load(name);
	SDL_Surface *image;

	if (temp == NULL){//ANSI colours found in ansi_colors.h
		printf(ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET ":failed to load image %s\n", name);
		exit(0);
	}

	/* Convert the image to the screen's native format */
	image = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	if (image == NULL){
		printf(ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET ":failed to convert image %s to native format\n", name);
		exit(0);
	}

	/* Return the processed image */

	return image;
}

void load_all_images(){
	grid_img= load_image("images/grid.jpg");
	high_list_img= load_image("images/highscore_list.jpg");

	pause_on_img= load_image("images/pause_button_on.jpg");
	pause_off_img= load_image("images/pause_button_off.jpg");

	high_on_img= load_image("images/highscore_button_on.jpg");
	high_off_img= load_image("images/highscore_button_off.jpg");

	quit_on_img= load_image("images/quit_button_on.jpg");
	quit_off_img= load_image("images/quit_button_off.jpg");

	fps_on_img= load_image("images/fps_button_on.jpg");
	fps_off_img= load_image("images/fps_button_off.jpg");

	fps_60_on_img= load_image("images/fps_60_button_on.jpg");
	fps_60_off_img= load_image("images/fps_60_button_off.jpg");

	fps_45_on_img= load_image("images/fps_45_button_on.jpg");
	fps_45_off_img= load_image("images/fps_45_button_off.jpg");

	fps_30_on_img= load_image("images/fps_30_button_on.jpg");
	fps_30_off_img= load_image("images/fps_30_button_off.jpg");

	fps_15_on_img= load_image("images/fps_15_button_on.jpg");
	fps_15_off_img= load_image("images/fps_15_button_off.jpg");

	O_img= load_image("images/O.jpg");
	I_img= load_image("images/I.jpg");
	J_img= load_image("images/J.jpg");
	L_img= load_image("images/L.jpg");
	Z_img= load_image("images/Z.jpg");
	S_img= load_image("images/S.jpg");
	T_img= load_image("images/T.jpg");
}

void free_all_images(){
	SDL_FreeSurface(grid_img);
	SDL_FreeSurface(high_list_img);

	SDL_FreeSurface(pause_on_img);
	SDL_FreeSurface(pause_off_img);
	SDL_FreeSurface(high_on_img);
	SDL_FreeSurface(high_off_img);
	SDL_FreeSurface(quit_on_img);
	SDL_FreeSurface(quit_off_img);

	SDL_FreeSurface(fps_on_img);
	SDL_FreeSurface(fps_off_img);
	SDL_FreeSurface(fps_60_on_img);
	SDL_FreeSurface(fps_60_off_img);
	SDL_FreeSurface(fps_45_on_img);
	SDL_FreeSurface(fps_45_off_img);
	SDL_FreeSurface(fps_30_on_img);
	SDL_FreeSurface(fps_30_off_img);
	SDL_FreeSurface(fps_15_on_img);
	SDL_FreeSurface(fps_15_off_img);

	SDL_FreeSurface(O_img);
	SDL_FreeSurface(I_img);
	SDL_FreeSurface(J_img);
	SDL_FreeSurface(L_img);
	SDL_FreeSurface(Z_img);
	SDL_FreeSurface(S_img);
	SDL_FreeSurface(T_img);
}

/*
 * Renders the image texture onto the window
 */
void draw_image(SDL_Surface *image, int x, int y){
	SDL_Rect rect;

	/* Set the blitting rectangle to the size of the src image */

	rect.x= x;
	rect.y= y;
	rect.w= image->w;
	rect.h= image->h;


	/* Blit the entire image onto the screen at coordinates x and y */

	SDL_BlitSurface(image, NULL, window, &rect);
}

/* checks which form a block has and returns an SDL_Surface */
SDL_Surface *get_form_as_SDL_Surface(enum Form form){
	switch(form){
	case O:
		return O_img;
	case I:
		return I_img;
	case S:
		return S_img;
	case Z:
		return Z_img;
	case L:
		return L_img;
	case J:
		return J_img;
	case T:
		return T_img;
	default:
		return 0;
	}
}
void draw_next_piece(enum Form next_piece,int x,int y){
	char string[20];
	int i,j;

	for(i=0; i<4;i++){
		for(j=0;j<4;j++){
			if ((tetromino[next_piece-2][0][i][j])>0){
				draw_image(get_form_as_SDL_Surface(next_piece),x+(j*20),y+(i*20));
			}
		}
	}

}




/* draws the whole field with necessary pictures on position x and y */
void draw_field() {

	draw_image(grid_img,0,0);
	

	sprintf(text_score, "%d", game_score);//score calculated in erase_full_line() in game_restrictions.c
	sprintf(text_line, "%d", lines);//number of scored lines calculated in erase_full_line()
	sprintf(text_level, "Level: %d", level+1);

	draw_text("font/blackWolf.ttf",20,text_score,230,65);
	draw_text("font/blackWolf.ttf",20,text_line,230,160);
	draw_text("font/blackWolf.ttf",20,text_level,10,10);

	draw_next_piece(next_piece,295,250);

	int y;
	char string[10];
	for (y = 2; y < field_height+2; y++) {
		int x;
		for (x = 0; x < field_width; x++) {
			enum Form form = get_form(x, y-2);//y-2 cause we start the for-loop at y= 2

			if(get_form_as_SDL_Surface(form) !=0){//TODO should be rewritten in a smoother way ;)
				//sprintf(string,"images/%c.jpg",get_form_as_character(form));
				draw_image(get_form_as_SDL_Surface(form),x*20,y*20);
			}
		}
	}
	if(pause_var== 1 && highscore_var==0 && fps_key_var==0){
		pause_var= pause_key_press();
	}
	else if(highscore_var== 1){
		highscore_key_press();
		draw_highscore(game_score);
	}
	else if(fps_key_var== 1){
		fps_key_press();
	}
	SDL_Flip(window);//switch to rendered image stored in the buffer
	clear_screen();
}



/*
 * Makes a window with the chosen width and height
 * ! This function should be called before a field is drawn !
 *
 * also initializes text and sound of SDL
 */
void initialize_SDL(char *title) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {//ANSI colours found in ansi_colors.h
		printf(ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET ":Could not initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	int window_width = 20 * BLOCK_WIDTH;
	int window_height = 23 * BLOCK_HEIGHT;
	window = SDL_SetVideoMode(window_width, window_height, 0, SDL_HWPALETTE | SDL_DOUBLEBUF);
	if (window == NULL) {
		printf(ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET ":Couldn't set screen mode to required dimensions: %s\n", SDL_GetError());
		exit(1);
	}
	/* Set the screen title */
	SDL_WM_SetCaption(title, NULL);

	initialize_SDL_mixer();//found in sounds.c

	load_sounds();
	load_all_images();

    if (TTF_Init() < 0){//initialize SDL_ttf
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
        exit(1);
    }
}

void cleanup() {

	printf("\n");

	TTF_Quit();
	free_sounds();//found in sounds.h

	/* Quit SDL_mixer */
	Mix_CloseAudio();

	free_all_images();
	/* Shut down SDL */
	SDL_Quit();
}
/*
 * makes a window with the chosen width and height and cleans the window when it shuts down
 */
void initialize_gui() {
	initialize_SDL("Tetris");
	atexit(cleanup);
}
