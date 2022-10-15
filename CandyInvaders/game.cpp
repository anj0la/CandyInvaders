#include "game.h"
#include <allegro.h>
#include <stdio.h> 
#include <stdlib.h>

//bool game_over = false;
//bool spawned = false;

void increment_speed_counter()
{
	speed_counter++;
	//time_since_last_spawn++;
}
END_OF_FUNCTION(increment_speed_counter);


//void update_logic() {
//	
//} // update_logic
//
///*
//Handles out of bounds movement if, after the player enters a key, makes the ship greater than the width or height of the game.
//@param candy_ship - the candy ship sprite controlled by the player
//*/
//void handling_out_of_bounds_movement(sprite* candy_ship) {
//	// checking if position is out of bounds
//	if (candy_ship->get_x_pos() <= 0) { // left
//		candy_ship->set_x_pos(0);
//	}
//	if (candy_ship->get_x_pos() >= 525) { // right
//		candy_ship->set_x_pos(525);
//	}
//	if (candy_ship->get_y_pos() <= 0) { // top
//		candy_ship->set_y_pos(0);
//	}
//	if (candy_ship->get_y_pos() >= 675) { // down
//		candy_ship->set_y_pos(675);
//	}
//} // handling_out_of_bounds_movement


//void move_up(sprite* player) {
//	player->set_y_pos(player->get_y_pos() - player->get_speed());
//} // move_up
//
//void move_down(sprite* player) {
//	player->set_y_pos(player->get_y_pos() + player->get_speed());
//} // move_down
//
//void move_left(sprite* player) {
//	player->set_x_pos(player->get_x_pos() - player->get_speed());
//} // move_left
//
//void move_right(sprite* player) {
//	player->set_x_pos(player->get_x_pos() + player->get_speed());
//} // move_right


//void fire_projectile(sprite* projectile, sprite* player) {
//	// fire again
//	if (!projectile->is_alive()) {
//		projectile->set_x_pos(player->get_x_pos() + OFFSET);
//		projectile->set_y_pos(player->get_y_pos());
//		projectile->set_alive(true);
//	}
//} // fire_player_projectile

//void get_player_input(sprite* player, sprite* projectile) {
//	if (key[KEY_UP]) {
//		move_up(player);
//	}
//	if (key[KEY_DOWN]) {
//		move_down(player);
//	}
//	if (key[KEY_LEFT]) {
//		move_left(player);
//	}
//	if (key[KEY_RIGHT]) {
//		move_right(player);
//	}
//	if (key[KEY_SPACE]) {
//		fire_projectile(projectile, player);
//	}
//	// short delay after keypress
//	//rest(20);
//}


//void move_projectile(sprite* projectile) {
//	int old_y_pos = projectile->get_y_pos();
//	int speed = projectile->get_speed();
//	if (!projectile->is_alive()) {
//		return;
//	} 
//	projectile->set_y_pos(old_y_pos - speed);
//}


//void projectile_out_of_bounds(sprite* projectile) {
//	if (projectile->get_y_pos() <= -100) { // top
//		projectile->set_alive(false);
//	}
//} // projectile_out_of_bounds

///*
//Gets a random position for the candy monster to spawn, between 5 and 795 pixels.
//@return - random x position of the candy monster
//*/
//int get_random_monster_x_pos() {
//	return rand() % 595 + 5;
//} // get_random_monster_x_pos
//
//void monster_out_of_bounds(sprite* monster) {
//	if (monster->get_y_pos() <= -100) { // top
//		monster->set_y_pos(-100);
//		monster->set_x_pos(get_random_monster_x_pos());
//	}
//	else if (monster->get_y_pos() >= 900) { // down
//		monster->set_y_pos(-100);
//		monster->set_x_pos(get_random_monster_x_pos());
//	}
//} // monster_out_of_bounds
//
//void move_monster(sprite* monster) {
//	int old_y_pos = monster->get_y_pos();
//	int speed = monster->get_speed();
//	monster->set_y_pos(old_y_pos + speed);
//} // move_monster
//
//void respawn_monster(sprite* monster) {
//	if (!monster->is_alive()) {
//		monster->set_y_pos(-200);
//		monster->set_x_pos(get_random_monster_x_pos());
//		monster->set_alive(true);
//	}
//}

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


int main(void) {
	srand(time(NULL));
	int initialized_allegro = allegro_init();
	if (initialized_allegro != 0) {
		allegro_exit();
		return 0;
	}
	set_color_depth(24);
	int ret = set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0);
	if (ret != 0) {
		allegro_message("Error setting GFX mode.");
		return 0;
	}
	BITMAP* buffer = create_bitmap(WIDTH, HEIGHT);
	clear_bitmap(buffer); // removing unnecessary pixels
	//set_color_depth(24);
	//set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0);
	int installed_keyboard = install_keyboard();
	if (installed_keyboard != 0) {
		allegro_exit();
		return 0;
	}
	set_keyboard_rate(10000, 0);
	LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);
	int installed_interrupt = install_int_ex(increment_speed_counter, BPS_TO_TIMER(FPS));
	if (installed_interrupt != 0) {
		allegro_exit();
		return 0;
	}
	bool game_over = false;
	/*BITMAP* buffer = create_bitmap(WIDTH, HEIGHT);

	sprite* candy_monster = new sprite();
	sprite* candy_swirl = new sprite();
	sprite* candy_ship = new sprite();

	candy_ship->load("graphics\\candy_ship.bmp");
	candy_ship->set_x_pos(275);
	candy_ship->set_y_pos(675);
	candy_ship->set_type('P');
	candy_ship->set_alive(true);

	candy_swirl->load("graphics\\candy_swirl.bmp");
	candy_swirl->set_speed(PROJECTILE_SPEED);
	
	candy_monster->load("graphics\\candy_monster.bmp");
	candy_monster->set_speed(MONSTER_SPEED);
	candy_monster->set_y_pos(-100);
	candy_monster->set_x_pos(get_random_monster_x_pos());
	candy_monster->set_alive(true);*/


	// candy_swirl->set_type('M');
	
	char xpos[256];
	char ypos[256];

	// Game loop
	while (!game_over) {
		while (speed_counter > 0) {
			//respawn_monster();
			//move_projectile();
			//move_monster();
			//handle_projectile_out_of_bounds();
			//handle_monster_out_of_bounds();
			//hit_monster();
			//hit_player();
			//get_player_input();
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

		/*if (monster->is_alive()) {
			monster->draw(buffer);
		}
		if (projectile->is_alive()) {
			projectile->draw(buffer);
		}*/
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