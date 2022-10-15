//#include "game.h"
//
//bool initialize_sprites() {
//	sprite* player = new sprite();
//	sprite* monster = new sprite();
//	sprite* projectile = new sprite();
//	bool loaded_player = player->load("graphics\\candy_ship.bmp");
//	bool loaded_monster = player->load("graphics\\candy_monster.bmp");
//	bool loaded_projectile = player->load("graphics\\candy_swirl.bmp");
//	if (!loaded_player || !loaded_monster || !loaded_projectile) {
//		return false; // at least one of the files did not load successfully
//	}
//	return true;
//} // initialize_sprites
//
///*
//Initializes the game, by setting the GFX mode and loading the sprites.
//*/
//void initialize_game() {
//	set_color_depth(24);
//	int ret = set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0);
//	if (ret != 0) {
//		allegro_message("Error setting GFX mode.");
//		return;
//	}
//	BITMAP* buffer = create_bitmap(WIDTH, HEIGHT);
//	clear_bitmap(buffer); // removing unnecessary pixels
//	bool loaded = initialize_sprites();
//	if (!loaded) {
//		allegro_message("Error loading sprites.");
//		return;
//	}
//} // initialize_game


