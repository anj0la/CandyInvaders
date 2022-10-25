#include "game.h"
#include <allegro.h>
#include <stdio.h> 
#include <stdlib.h>

volatile int Game::speed_counter = 0;

/*
Constructs a new instance of the game class.
*/
Game::Game() {
	//speed_counter = 0;
	timer = 0;
	time_since_last_spawn = 0;
	buffer = create_bitmap(WIDTH, HEIGHT);
	background = NULL;
	player = new Player();
	projectile = new Projectile();
	monster = new Monster();
	monster_projectile = new Projectile();
	sprintf_s(total_score, MAX_SCORE_LEN, "%d", INIT_SCORE);
	sprintf_s(player_health, MAX_HEALTH_LEN, "%d", INIT_HEALTH);
	paused = false;
	LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);
} // constructor

/*
Automatically removes the game object from memory.
*/
Game::~Game() {
	destroy_bitmap(buffer);
	destroy_bitmap(background);
} // destructor

/*
Loads a BMP file into the background bitmap.
@return - true if the file was loaded successfully into the background, false otherwise
*/
bool Game::load_background(const char* filename) {
	background = load_bitmap(filename, NULL);
	if (background != NULL) {
		return true;
	}
	return false; // background is NULL
} // load_background

/*
Loads the BMP file containing the player sprite into the game.
@return - true if the file loaded successfully, false otherwise
*/
bool Game::load_player_sprite(const char* filename) {
	bool loaded = player->get_player_sprite()->load(filename);
	if (loaded) {
		return true;
	}
	return false;
} // load_player_sprite

/*
Loads the BMP file containing the projectile sprite into the game.
@return - true if the file loaded successfully, false otherwise
*/
bool Game::load_projectile_sprite(const char* filename) {
	bool loaded = projectile->get_projectile_sprite()->load(filename);
	if (loaded) {
		return true;
	}
return false;
} // load_projectile_sprite

/*
Loads the BMP file containing the monster sprite into the game.
@return - true if the file loaded successfully, false otherwise
*/
bool Game::load_monster_sprite(const char* filename) {
	bool loaded = monster->get_monster_sprite()->load(filename);
	if (loaded) {
		return true;
	}
	return false;
} // load_monster_sprite

/*
Loads the BMP file containing the monster projectile sprite into the game.
@return - true if the file loaded successfully, false otherwise
*/
bool Game::load_monster_projectile_sprite(const char* filename) {
	bool loaded = monster_projectile->get_projectile_sprite()->load(filename);
	if (loaded) {
		return true;
	}
	return false;
} // load_monster_projectile_sprite

/*
Sets all of the sprites to their default states.
*/
void Game::set_up_sprites() {
	player->get_player_sprite()->set_x_pos(275);
	player->get_player_sprite()->set_y_pos(675);
	player->get_player_sprite()->set_alive(true);
	monster->get_monster_sprite()->set_y_pos(-100);
	monster->get_monster_sprite()->set_x_pos(monster->get_random_monster_x_pos());
	monster->get_monster_sprite()->set_alive(true);
	projectile->get_projectile_sprite()->set_alive(false);
	monster_projectile->get_projectile_sprite()->set_alive(false);
} // set_up_sprites

/*
Starts a new game by setting all game values to their default state and runs the game.
*/
void Game::new_game() {
	set_up_sprites();
	bool game_over = run_game();
	if (!game_over) {
		reset_game();
		new_game();
	}
} // new_game

/*
Resets the game, by setting all game variables back to their initial states.
*/
void Game::reset_game() {
	speed_counter = 0;
	timer = 0;
	time_since_last_spawn = 0;
	player->set_score(0);
	player->set_player_health(100);
	sprintf_s(total_score, MAX_SCORE_LEN, "%d", INIT_SCORE);
	sprintf_s(player_health, MAX_HEALTH_LEN, "%d", INIT_HEALTH);
} // reset_game

/*
Runs the whole game, from the main menu to the end game menu.
@return - true if the player does not want to play the game again, false otherwise
*/
bool Game::run_game() {
	bool advance = main_menu();
	if (!advance) {
		return true; // game is over
	}
	int installed_interrupt = install_int_ex(increment_speed_counter, BPS_TO_TIMER(FPS));
	if (installed_interrupt != 0) {
		allegro_message("Error setting up the interrupt handler.");
		return true;
	}
	bool game_ended = play_game();
	if (game_ended) {
		return true; // game is ever
	}
	bool pressed_esc = end_game_menu();
	if (pressed_esc) {
		return true;
	}
	return false; // the player wants to play the game again
} // run_game

/*
Displays the main menu of the game.
@param background - the static background
@return - true if the enter key was pressed was pressed, false if the escape key was pressed
*/
bool Game::main_menu() {
	clear_bitmap(buffer);
	blit(background, buffer, 0, 0, 0, 0, WIDTH, HEIGHT);
	textout_ex(buffer, font, "Candy Invaders", 1, 11, WHITE, -1);
	textout_ex(buffer, font, "Press ENTER to start the game.", 1, 21, WHITE, -1);
	update_screen();
	while (true) {
		if (key[KEY_ENTER]) {
			key[KEY_ENTER] = 0; // so that the user can press the key again
			break;
		}
		if (key[KEY_ESC]) {
			return false;
		}
	}
	return true; // the enter key was pressed
} // main_menu

/*
Runs the following methods associated with the game logic, such as moving the player, monster, and projectiles,
getting input from the user, and ensuring that all sprites are not out of bounds.
*/
void Game::run_game_logic() {
	monster->respawn_monster();
	monster_projectile->fire_projectile(monster->get_monster_sprite());
	projectile->move_projectile_up();
	monster_projectile->move_projectile_down();
	monster->move_monster();
	monster_projectile->handle_projectile_out_of_bounds();
	projectile->handle_projectile_out_of_bounds();
	monster->handle_monster_out_of_bounds();
	player->handle_player_out_of_bounds();
} // run_game_logic

/*
Checks to see if the player collided with the monster sprite.
@return - true if the player collided with the monster sprite, false otherwise
*/
bool Game::did_player_collide_with_monster() {
	if (player->collied_with_monster(monster->get_monster_sprite())) {
		return true;
	} 
	return false;
} // did_player_collide_with_monster

/*
Checks if the projectile collided with the monster sprite, and if so, increases the score of the player by 100.
*/
void Game::handle_projectile_collsion() {
	if (projectile->direct_hit(monster->get_monster_sprite())) {
		monster->get_monster_sprite()->set_y_pos(-900);
		monster->get_monster_sprite()->set_alive(false);
		projectile->get_projectile_sprite()->set_y_pos(-900);
		projectile->get_projectile_sprite()->set_alive(false);
		int old_score = player->get_score(); // make this a method
		player->set_score(old_score + 100); // make this a method
	}
} // handle_projectile_collsion

/*
Checks if the monster projectile collided with the player sprite, and if so, substracts a set amount from the health of the player.
*/
void Game::handle_monster_projectile_collision() {
	if (monster_projectile->direct_hit(player->get_player_sprite())) {
		monster_projectile->get_projectile_sprite()->set_y_pos(-900);
		monster_projectile->get_projectile_sprite()->set_alive(false);
		int old_health = player->get_player_health();
		player->set_player_health(old_health - 25);
	}
} // handle_monster_projectile_collision

/*
Draws the player to the buffer screen.
*/
void Game::draw_player() {
	player->get_player_sprite()->draw(buffer);
} // draw_player

/*
Draws the player projectile to the buffer screen, if it is currently alive.
*/
void Game::draw_projectile() {
	if (projectile->get_projectile_sprite()->is_alive()) {
		projectile->get_projectile_sprite()->draw(buffer);
	}
} // draw_projectile

/*
Draws the monster to the buffer screen, if it is currently alive.
*/
void Game::draw_monster() {
	if (monster->get_monster_sprite()->is_alive()) {
		monster->get_monster_sprite()->draw(buffer);
	}
} // draw_monster

/*
Draws the monster projectile to the buffer screen, if it is currently alive.
*/
void Game::draw_monster_projectile() {
	if (monster_projectile->get_projectile_sprite()->is_alive()) {
		monster_projectile->get_projectile_sprite()->draw(buffer);
	}
} // draw_monster_projectile

/*
Runs the game.
@return - true if the game was over by pressing the ESC key, false otherwise
*/
bool Game::play_game() {
	bool game_over = false;
	bool pressed_esc = false;
	while (!game_over) {
		while (speed_counter > 0) {
			run_game_logic();
			// Checking if player collided with the monster
			if (did_player_collide_with_monster()) {
					game_over = true;
			} 
			// Checking if monster projectile hit player
			handle_monster_projectile_collision();
			if (is_player_health_zero()) {
				game_over = true;
			}
			// Checking if projectile hit monster
			handle_projectile_collsion();
			player->get_player_input(projectile->get_projectile_sprite());
			speed_counter--;
			timer++;
			time_since_last_spawn--;
		} // inner while

		// Presssed the ESC key?
		if (key[KEY_ESC]) {
			game_over = true;
			pressed_esc = true;
		}
		// Calculating time elasped
		char time_elasped[256];
		sprintf_s(time_elasped, 256, "%d", (timer / FPS) + 1);
		sprintf_s(player_health, MAX_HEALTH_LEN, "%d", player->get_player_health());
		sprintf_s(total_score, MAX_SCORE_LEN, "%d", player->get_score());

		clear_bitmap(buffer);
			
		// Drawing total score and player health to buffer
		textout_ex(buffer, font, time_elasped, 1, 1, WHITE, -1);

		textout_ex(buffer, font, total_score, 1, WIDTH - 20, WHITE, -1);
		textout_ex(buffer, font, player_health, 1, WIDTH - 60, WHITE, -1);

		draw_monster_projectile();
		draw_monster();
		draw_projectile();
		draw_player();

		// Updating game screen
		update_screen();	
	} // game loop
	// checking if we need to pause the game or if we need to quit the game
	/*if (keypressed()) {
		if (key[KEY_LCONTROL] && key[KEY_H] || key[KEY_RCONTROL] && key[KEY_H]) {
			paused = true;
			display_help_module();
		}
		else if (key[KEY_ESC]) {
			return true;
		}
		else {
			paused = false;
			clear_bitmap(buffer);
		}
	}*/
	remove_int(increment_speed_counter); // removing the interrupt handler as we don't need it anymore
	return pressed_esc;
} // play_game

/*
Displays the end game menu.
@param background - the static background
@return - true if the escape key was pressed, false if the enter key was pressed
*/
bool Game::end_game_menu() {
	clear_bitmap(buffer);
	blit(background, buffer, 0, 0, 0, 0, WIDTH, HEIGHT);
	textout_ex(buffer, font, "Candy Invaders", 1, 11, BLACK, -1);
	textout_ex(buffer, font, "Press ENTER to replay the game or ESC to quit the game", 1, 21, BLACK, -1);
	update_screen();
	while (true) {
		if (key[KEY_ENTER]) {
			key[KEY_ENTER] = 0; // so that the user can press the key again
			break;
		}
		if (key[KEY_ESC]) {
			return true;
		}
	}
	return false; // the enter key was pressed
} // end_game_menu

/*
Updates the screen by blitting whatever has been drawn onto the buffer onto the screen.
*/
void Game::update_screen() {
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
	release_screen();
} // update_screen

/*
Displays the help module.
*/
void Game::display_help_module() {
	clear_bitmap(buffer);
	blit(background, buffer, 0, 0, 0, 0, WIDTH, HEIGHT);
	rectfill(buffer, 150, 150, 450, 450, BLACK);
	textout_ex(buffer, font, "HELP MODULE", 155, 155, WHITE, -1);
	textout_ex(buffer, font, "Use the Up, Down, Left and Right arrow keys to move around.", 155, 175, WHITE, -1);
	textout_ex(buffer, font, "Use the Space Bar to shoot candy at the candy monsters.", 155, 195, WHITE, -1);
	update_screen();
} // display_help_module 

/*
Checks if the player's health is 0.
@return - true if the player's health is 0, indicating that the game is over, false otherwise
*/
bool Game::is_player_health_zero() {
	if (player->get_player_health() <= 0) {
		return true;
	}
	return false;
} // is_game_over

/*
The function that gets called every time the interrupt handler is executed.
*/
void Game::increment_speed_counter()
{
	speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter);