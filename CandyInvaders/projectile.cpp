#include "projectile.h"

/*
Constructs a new instance of the projectile class.
*/
Projectile::Projectile() {
	projectile = new Sprite();
	projectile->set_speed(7);
} // constructor

/*
Automatically removes the projectile object from memory.
*/
Projectile::~Projectile() {
	// Empty destructor, sprite classes handles the deleting of the bitmap associated with the projectile
} // destructor

/*
Gets the projectile sprite.
@return - the pointer pointing to the projectile sprite
*/
Sprite* Projectile::get_projectile_sprite() {
	return projectile;
} // get_projectile_sprite

/*
Moves the projectile up by the speed specified in the initialize function.
*/
void Projectile::move_projectile() {
	int old_y_pos = projectile->get_y_pos();
	int speed = projectile->get_speed();
	if (!projectile->is_alive()) {
		return;
	}
	projectile->set_y_pos(old_y_pos - speed);
} // move_projectile

/*
Fires the projectile.
*/
void Projectile::fire_projectile(Sprite* player) {
	// fire again
	if (!projectile->is_alive()) {
		projectile->set_x_pos(player->get_x_pos() + OFFSET);
		projectile->set_y_pos(player->get_y_pos());
		projectile->set_alive(true);
	}
} // fire_projectile

/*
Checks if a projectile is out of bounds, that is, its y position is less than height of the game, and makes it not alive if so.
*/
void Projectile::handle_projectile_out_of_bounds() {
	if (projectile->get_y_pos() <= -100) { // top
		projectile->set_alive(false);
	}
} // handle_projectile_out_of_bounds

/*
Checks if the projectile hit the monster.
@param monster - the candy sprite monster
@return true if the projectile collided with the monster, false otherwise
*/
bool Projectile::hit_monster(Sprite* monster) {
	if (projectile->collided(monster)) {
		return true;
	}
	return false;
} // hit_monster
