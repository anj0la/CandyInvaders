#include "monster.h"

/*
Constructs a new instance of the monster class.
*/
Monster::Monster() {
	monster_spr = new Sprite();
	monster_spr->set_speed(MONSTER_SPEED);
} // constructor

/*
Automatically removes the monster object from memory.
*/
Monster::~Monster() {
	// Empty destructor, sprite classes handles the deleting of the bitmap associated with the player
} // destructor

/*
Gets the monster sprite.
@return - the pointer pointing to the monster sprite
*/
Sprite* Monster::get_monster_sprite() {
	return monster_spr;
} // get_monster_sprite

/*
Moves the monster down by the speed specified in the initialize function.
*/
void Monster::move_monster() {
	int old_y_pos = monster_spr->get_y_pos();
	int speed = monster_spr->get_speed();
	monster_spr->set_y_pos(old_y_pos + speed);
} // move_monster

/*
Respawns the monster if it is not alive.
*/
void Monster::respawn_monster() {
	if (!monster_spr->is_alive()) {
		monster_spr->set_y_pos(-200);
		monster_spr->set_x_pos(get_random_monster_x_pos());
		monster_spr->set_alive(true);
	}
} // respawn_monster

/*
Checks if a monster is out of bounds, that is, its y position is greater than height of the game.
*/
void Monster::handle_monster_out_of_bounds() {
	if (!monster_spr->is_alive()) {
		return; // not alive, exit the method
	}
	if (monster_spr->get_y_pos() >= 900) { // down
		monster_spr->set_y_pos(-100);
		monster_spr->set_x_pos(get_random_monster_x_pos());
	}
} // monster_out_of_bounds

/*
Gets a random position for the candy monster to spawn, between 5 and 595 pixels.
@return - random x position of the candy monster
*/
int Monster::get_random_monster_x_pos() {
	return rand() % 595 + 5;
} // get_random_monster_x_pos




