#include "player.h"

/*
Constructs a new instance of the player class.
*/
Player::Player() {
	player_spr = new Sprite();
	health = 100;
	score = 0;
} // constructor 

/*
Automatically removes the player object from memory.
*/
Player::~Player() {
	// Empty destructor, sprite classes handles the deleting of the bitmap associated with the player
} // destructor

/*
Loads the BMP file containing the player's sprite.
@return - false if it did not load successfully, true otherwise
*/
bool Player::load_sprite(const char* filename) {
	bool ret = player_spr->load(filename);
	if (!ret) {
		return false; // did not load properly
	}
	return true;
} // load_sprite

/*
Gets the player sprite.
@return - the pointer pointing to the player sprite
*/
Sprite* Player::get_player_sprite() {
	return player_spr;
} // get_player_sprite

/*
Gets the player's health.
@return - the health of the player
*/
int Player::get_player_health() {
	return health;
} // get_player_health

/*
Gets the player's score.
@return - the current score of the player
*/
int Player::get_score() {
	return score;
} // get_score

/*
Sets the health of the player to the new health specified by the parameter.
@param - the new health of the player
*/
void Player::set_player_health(int new_health) {
	health = new_health;
} // set_player_health

/*
Sets the score of the player to the new score specified by the parameter.
@param - the new score of the player
*/
void Player::set_score(int new_score) {
	score = new_score;
} // set_score

/*
Gets keyboard input from the player, and executes an action based on the key that the user has pressed.
*/
void Player::get_player_input(Sprite* player_projectile) {
	if (key[KEY_UP]) {
		move_up();
	}
	if (key[KEY_DOWN]) {
		move_down();
	}
	if (key[KEY_LEFT]) {
		move_left();
	}
	if (key[KEY_RIGHT]) {
		move_right();
	}
	if (key[KEY_SPACE]) {
		fire_player_projectile(player_projectile);
	}
	// short delay after keypress
	//rest(20);
} // get_player_input

/*
Moves the player's sprite up by subtracting the speed of the player's sprite from its current y position.
*/
void Player::move_up() {
		player_spr->set_y_pos(player_spr->get_y_pos() - player_spr->get_speed());
} // move_up

/*
Moves the player's sprite down by adding the speed of the player's sprite from its current y position.
*/
void Player::move_down() {
	player_spr->set_y_pos(player_spr->get_y_pos() + player_spr->get_speed());
} // move_down

/*
Moves the player's sprite left by subtracting the speed of the player's sprite from its current x position.
*/
void Player::move_left() {
	player_spr->set_x_pos(player_spr->get_x_pos() - player_spr->get_speed());
} // move_left

/*
Moves the player's sprite right by subtracting the speed of the player's sprite from its current x position.
*/
void Player::move_right() {
	player_spr->set_x_pos(player_spr->get_x_pos() + player_spr->get_speed());
} // move_right

/*
Fires the projectile.
*/
void Player::fire_player_projectile(Sprite* player_projectile) {
	// fire again
	if (!player_projectile->is_alive()) {
		player_projectile->set_x_pos(player_spr->get_x_pos() + 25);
		player_projectile->set_y_pos(player_spr->get_y_pos());
		player_projectile->set_alive(true);
	}
} // fire_player_projectile

/*
Checks if the player has collided with a candy monster.
@param monster_spr - the monster sprite 
@return true if the player sprite collided with the monster sprite, false otherwise
*/
bool Player::collied_with_monster(Sprite* monster_spr) {
	if (player_spr->collided(monster_spr)) {
		return true;
	}
	return false;
} // collied_with_monster

/*
Handles out of bounds movement if, after the player enters a key, makes the ship greater than the width or height of the game.
*/
void Player::handle_player_out_of_bounds() {
	// checking if position is out of bounds
	if (player_spr->get_x_pos() <= 0) { // left
		player_spr->set_x_pos(0);
	}
	if (player_spr->get_x_pos() >= 525) { // right
		player_spr->set_x_pos(525);
	}
	if (player_spr->get_y_pos() <= 0) { // top
		player_spr->set_y_pos(0);
	}
	if (player_spr->get_y_pos() >= 675) { // down
		player_spr->set_y_pos(675);
	}
} // handle_player_out_of_bounds