#include <allegro.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "candyinvaders.h"

int main(void) {
	srand(time(NULL));
	if (allegro_init() != 0) {
		return 1;
	}
	set_window_title("Candy Invaders");
	set_color_depth(24);
	install_keyboard();
	set_keyboard_rate(10000, 0);
	int ret = set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0);
	if (ret != 0) {
		allegro_message("Error setting GFX mode.");
		return 1;
	}
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
		allegro_message("Error initializing sound system.");
		return 1;
	}
	Game* game = new Game();
	bool loaded = load_game_objects(game);
	if (!loaded) {
		return 1;
	}
	game->new_game();
	allegro_exit();
	return 0;
} // main
END_OF_MAIN()

/*
Loads the files related to the game into the game object, returning true if everything was loaded successfully, and false otherwise.
@return - true if all files were loaded successfully into the game, false otherwise
*/
bool load_game_objects(Game* a_game) {
	bool ld_background_1 = a_game->load_start_background("graphics\\game_start_background.bmp");
	bool ld_background_2 = a_game->load_game_background("graphics\\game_background.bmp");
	bool ld_background_3 = a_game->load_end_background("graphics\\game_end_background.bmp");
	bool ld_health_bars = a_game->load_health_bars(health_bars);
	bool ld_score_font = a_game->load_score_font("graphics\\score_font.pcx");
	bool ld_player_spr = a_game->load_player_sprite("graphics\\candy_ship.bmp");
	bool ld_prject_spr = a_game->load_projectile_sprite("graphics\\candy_swirl.bmp");
	bool ld_monster_spr = a_game->load_monster_sprite("graphics\\candy_monster.bmp");
	bool ld_monster_prject_spr = a_game->load_monster_projectile_sprite("graphics\\monster_projectile.bmp");
	bool ld_music = a_game->load_background_music("sounds\\cottagecore-17463.wav");
	bool ld_sound1 = a_game->load_shooting_sound("sounds\\pop-94319.wav");
	bool ld_sound2 = a_game->load_goo_sound("sounds\\goo-splat2.wav");
	bool ld_sound3 = a_game->load_monster_fed_sound("sounds\\candy_monster_fed.wav");
	bool ld_sound4 = a_game->load_game_over_sound("sounds\\videogame-death-sound-43894.wav");
	if (!ld_background_1 || !ld_background_2 || !ld_background_3 || !ld_health_bars || !ld_score_font ||
		!ld_player_spr || !ld_prject_spr || !ld_monster_spr || !ld_monster_prject_spr || !ld_music || !ld_sound1
		|| !ld_sound2 || !ld_sound3 || !ld_sound4) {
		return false;
	}
	return true;
} // load_game_objects