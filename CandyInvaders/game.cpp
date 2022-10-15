#include "game.h"
#include <allegro.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

/*
The entry point for the game.
*/
int main(void) {
	// Setting up game
	srand(time(NULL));
	int initialized_allegro = allegro_init();
	if (initialized_allegro != 0) {
		allegro_exit();
		return 0;
	}
	bool initialized_game = initialize_game();
	if (!initialized_game) {
		allegro_message("Error setting up the game.");
		allegro_exit();
		return 0;
	}
	// Initializing game vars
	BITMAP* buffer = create_bitmap(WIDTH, HEIGHT);
	bool game_over = false;
	char xpos[256];
	char ypos[256];
	// Game loop
	while (!game_over) {
		while (speed_counter > 0) {
			speed_counter--;
			timer--;
			time_since_last_spawn--;
		}

		// Calculating time left
		char time_left[256];
		sprintf_s(time_left, 256, "%d", timer / FPS);

		// Delete later
		//sprintf_s(xpos, 256, "PAINTER SPIRTE - X: %d", monster->get_x_pos());
		//sprintf_s(ypos, 256, "PAINTER SPRITE - Y: %d", monster->get_y_pos());

		// Game over?
		if (timer <= 0) {
			game_over = true;
		}
		clear_bitmap(buffer);

		// Delete later 
		textout_ex(buffer, font, time_left, 1, 1, WHITE, -1);
		//textout_ex(buffer, font, xpos, 1, 11, WHITE, -1);
		//textout_ex(buffer, font, ypos, 1, 21, WHITE, -1);

		//player->draw(buffer);
		// Updating screen
		acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
		release_screen();
	} // game loop
	allegro_exit();
	return 0;
} // main
END_OF_MAIN()

/*
The function that gets called every time the interrupt handler is executed.
*/
void increment_speed_counter()
{
	speed_counter++;
	//time_since_last_spawn++;
}
END_OF_FUNCTION(increment_speed_counter);

/*
Initializes the game, by setting the GFX mode and loading the sprites.
*/
bool initialize_game() {
	set_color_depth(24);
	int ret = set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0);
	if (ret != 0) {
		allegro_message("Error setting up the GFX mode.");
		return false;
	}
	int installed_keyboard = install_keyboard();
	if (installed_keyboard != 0) {
		allegro_message("Error setting up the keyboard.");
		return false;
	}
	set_keyboard_rate(10000, 0);
	LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);
	int installed_interrupt = install_int_ex(increment_speed_counter, BPS_TO_TIMER(FPS));
	if (installed_interrupt != 0) {
		allegro_message("Error setting up the interrupt handler.");
		return false;
	}
	return true;
} // initialize_game

bool main_menu() {

}
