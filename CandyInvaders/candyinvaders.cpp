#include <allegro.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include "game.h"


int main(void) {
	srand(time(NULL));
	if (allegro_init() != 0) {
		return 1;
	}
	set_color_depth(24);
	install_keyboard();
	set_keyboard_rate(10000, 0);
	int ret = set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0);
	if (ret != 0) {
		allegro_message("Error setting GFX mode.");
		return 1;
	}
	/*LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);
	int installed_interrupt = install_int_ex(increment_speed_counter, BPS_TO_TIMER(FPS));
	if (installed_interrupt != 0) {
		allegro_message("Error setting up the interrupt handler.");
		return false;
	}*/
	Game* game = new Game();
	game->load_background("graphics\\static_background.bmp");
	game->load_player_sprite("graphics\\candy_ship.bmp");
	game->load_projectile_sprite("graphics\\candy_swirl.bmp");
	game->load_monster_sprite("graphics\\candy_monster.bmp");
	game->new_game();
	//while (!(key[KEY_LCONTROL] && key[KEY_H]));
	// while (!key[KEY_ESC]);
	allegro_exit();
	return 0;
}
END_OF_MAIN()

///*
//The function that gets called every time the interrupt handler is executed.
//*/
//void increment_speed_counter() {
//	speed_counter++;
//	//time_since_last_spawn++;
//}
//END_OF_FUNCTION(increment_speed_counter);