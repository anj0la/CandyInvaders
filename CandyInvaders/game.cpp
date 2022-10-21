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

bool Game::load_background(const char* filename) {
	background = load_bitmap(filename, NULL);
	if (background != NULL) {
		return true;
	}
	return false; // background is NULL
} // load_background

bool Game::load_player_sprite(const char* filename) {
	bool loaded = player->load_sprite(filename);
	if (loaded) {
		return true;
	}
	return false;
} // load_player_sprite

/*
Starts a new game by setting all game values to their default state and runs the game.
*/
void Game::new_game() {
	// Create a new Player here
	// Player* player = new Player();
	// player->
	player->get_player_sprite()->set_x_pos(275);
	player->get_player_sprite()->set_y_pos(675);
	player->get_player_sprite()->set_alive(true);
	// player->set_alive
	bool game_over = run_game();
	if (!game_over) {
		reset_game();
		new_game();
	}
} // new_game

void Game::reset_game() {
	speed_counter = 0;
	timer = 0;
	time_since_last_spawn = 0;
	sprintf_s(total_score, MAX_SCORE_LEN, "%d", INIT_SCORE);
	sprintf_s(player_health, MAX_HEALTH_LEN, "%d", INIT_HEALTH);
}

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
}

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

bool Game::play_game() {
	bool game_over = false;
	bool pressed_esc = false;
	while (!game_over) {
		while (speed_counter > 0) {
			speed_counter--;
			timer++;
			time_since_last_spawn--;
		}

		// Presssed the ESC key?
		if (key[KEY_ESC]) {
			game_over = true;
			pressed_esc = true;
		}
			
		// Calculating time elasped
		char time_elasped[256];
		sprintf_s(time_elasped, 256, "%d", (timer / FPS) + 1);
			
		// Game over?
		if (timer >= 10 * FPS) {
			game_over = true;
		}

		clear_bitmap(buffer);
			
		// Drawing total score and player health to buffer
		textout_ex(buffer, font, time_elasped, 1, 1, WHITE, -1);

		textout_ex(buffer, font, total_score, 1, WIDTH - 20, WHITE, -1);
		textout_ex(buffer, font, player_health, 1, WIDTH - 60, WHITE, -1);

		player->get_player_sprite()->draw(buffer);

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
The function that gets called every time the interrupt handler is executed.
*/
void Game::increment_speed_counter()
{
	speed_counter++;
	//time_since_last_spawn++;
}
END_OF_FUNCTION(increment_speed_counter);

//static void cast_increment_speed_counter() {
//
//}















//// Global variables
//volatile int speed_counter = 0;
//volatile int timer = 1;
//volatile int time_since_last_spawn = 0;
//
///*
//The entry point for the game.
//*/
//int main(void) {
//	// Setting up game
//	srand(time(NULL));
//	int initialized_allegro = allegro_init();
//	if (initialized_allegro != 0) {
//		allegro_exit();
//		return 0;
//	}
//	bool initialized_game = initialize_game();
//	if (!initialized_game) {
//		allegro_message("Error setting up the game.");
//		allegro_exit();
//		return 0;
//	}
//	// Initializing game vars
//	BITMAP* buffer = create_bitmap(WIDTH, HEIGHT);
//	bool game_over = false;
//	char xpos[256];
//	char ypos[256];
//	// Game loop
//	while (!game_over) {
//		while (speed_counter > 0) {
//			speed_counter--;
//			timer++;
//			time_since_last_spawn--;
//		}
//
//		// Calculating time left
//		char time_left[256];
//		sprintf_s(time_left, 256, "%d", timer / FPS);
//
//		// Delete later
//		//sprintf_s(xpos, 256, "PAINTER SPIRTE - X: %d", monster->get_x_pos());
//		//sprintf_s(ypos, 256, "PAINTER SPRITE - Y: %d", monster->get_y_pos());
//
//		// Game over?
//		if (timer >= 10 * FPS) {
//			game_over = true;
//		}
//		clear_bitmap(buffer);
//
//		// Delete later 
//		textout_ex(buffer, font, time_left, 1, 1, WHITE, -1);
//		//textout_ex(buffer, font, xpos, 1, 11, WHITE, -1);
//		//textout_ex(buffer, font, ypos, 1, 21, WHITE, -1);
//
//		//player->draw(buffer);
//		// Updating screen
//		acquire_screen();
//		blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
//		release_screen();
//	} // game loop
//	allegro_exit();
//	return 0;
//} // main
//END_OF_MAIN()
//
///*
//The function that gets called every time the interrupt handler is executed.
//*/
//void increment_speed_counter()
//{
//	speed_counter++;
//	//time_since_last_spawn++;
//}
//END_OF_FUNCTION(increment_speed_counter);
//
///*
//Initializes the game, by setting the GFX mode and loading the sprites.
//*/
//bool initialize_game() {
//	set_color_depth(24);
//	int ret = set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0);
//	if (ret != 0) {
//		allegro_message("Error setting up the GFX mode.");
//		return false;
//	}
//	int installed_keyboard = install_keyboard();
//	if (installed_keyboard != 0) {
//		allegro_message("Error setting up the keyboard.");
//		return false;
//	}
//	set_keyboard_rate(10000, 0);
//	LOCK_VARIABLE(speed_counter);
//	LOCK_FUNCTION(increment_speed_counter);
//	int installed_interrupt = install_int_ex(increment_speed_counter, BPS_TO_TIMER(FPS));
//	if (installed_interrupt != 0) {
//		allegro_message("Error setting up the interrupt handler.");
//		return false;
//	}
//	return true;
//} // initialize_game
//
//bool main_menu() {
//	return false;
//}
