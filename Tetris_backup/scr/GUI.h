#include "SDL/SDL.h"
#include "SDL/SDL_image.h"//contains IMG_Load() function so we can load PNG and JPG and aren't
						  //restricted to just BMP
#include "blocks.h"
#include "field.h"
#include "key_input.h"
#include "game_rules.h"
#include "ansi_colors.h"

#define BLOCK_HEIGHT 20
#define BLOCK_WIDTH 20

SDL_Surface *window;

/* used in key_input.c */
SDL_Surface *pause_on_img;
SDL_Surface *pause_off_img;
SDL_Surface *high_on_img;
SDL_Surface *high_off_img;
SDL_Surface *quit_on_img;
SDL_Surface *quit_off_img;

SDL_Surface *fps_on_img;
SDL_Surface *fps_off_img;

SDL_Surface *fps_60_on_img;
SDL_Surface *fps_60_off_img;

SDL_Surface *fps_45_on_img;
SDL_Surface *fps_45_off_img;

SDL_Surface *fps_30_on_img;
SDL_Surface *fps_30_off_img;

SDL_Surface *fps_15_on_img;
SDL_Surface *fps_15_off_img;

/* used in highscore.c */
SDL_Surface *high_list_img;

/*
 * Initialiseert onder andere het venster waarin het speelveld getoond zal worden.
 * Deze functie moet gecalled worden aan het begin van het spel, vooraleer je
 * de spelwereld begint te tekenen.
 */
void initialize_gui();

void clear_screen();

SDL_Surface *load_image(char *);

void load_all_images();

void free_all_images();

SDL_Surface *get_form_as_SDL_Surface(enum Form);

void draw_next_piece(enum Form, int, int);

void draw_image(SDL_Surface *, int, int);

/*
 * Tekent het huidige veld in het venster. Deze functie moeten jullie dus zelf implementeren.
 */
void draw_field(void);

