CC= gcc
CFLAGS= -Wno-unused-result -O3
CLINKING= -lm -lSDL -lSDLmain -lSDL_image -lSDL_mixer -lSDL_ttf -D_SDL_main_h#linken van SDL libraries

OUTPUT= output_files/main.o output_files/field.o output_files/GUI.o output_files/blocks.o output_files/time_functions.o output_files/game_rules.o output_files/key_input.o output_files/sounds.o output_files/text.o output_files/highscore.o output_files/score.o

NO_COLOR=\033[0m#geen kleur, is essentieel of anders blijft uw terminal dezelfde kleur aannemen
GREEN_COLOR=\033[32;01m#groene kleur
YELLOW_COLOR=\033[33;01m#gele kleur
PINK_COLOR=\033[35;01m#roze kleur

DONE_STRING= $(GREEN_COLOR)[DONE]$(NO_COLOR)
RUN_STRING= $(YELLOW_COLOR)./game$(NO_COLOR)
OUTPUT_STRING= $(PINK_COLOR) $@ $(NO_COLOR)#print roze output.o files 

PRINT_DONE = @ printf "$(DONE_STRING)\n"#@ zorgt ervoor dat het commando niet geprint wordt maar wel uitgevoerd
PRINT_RUN = @ printf "Schrijf $(RUN_STRING) om het programma uit te voeren.\n"
PRINT_OUTPUT= @ printf "Bezig met object file$(OUTPUT_STRING)te compileren"

RUN= game#./game

all: $(OUTPUT)#alle object-files worden gelinkt
	@echo Programma maken
	@ $(CC) $(CFLAGS) $(OUTPUT) $(CLINKING) -L./lib -o $(RUN)
	$(PRINT_DONE) 
	$(PRINT_RUN) 

output_files/%.o: scr/%.c scr/%.h#alles wordt in object-files omgezet
	$(PRINT_OUTPUT)
	@ $(CC) $(CFLAGS) $< -o $@ -c
	$(PRINT_DONE)
	
remove:#alle overbodige files verwijderen
	@echo output_files/*.o and $(RUN) is being removed...
	@ rm -f output_files/*.o
	@ rm -f $(RUN)
	$(PRINT_DONE)