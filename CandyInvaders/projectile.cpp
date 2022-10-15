//#include "game.h"
//
///*
//Checks if a projectile is out of bounds, that is, its y position is less than height of the game, and makes it not alive if so.
//*/
//void handle_projectile_out_of_bounds() {
//	if (projectile->get_y_pos() <= -100) { // top
//		projectile->set_alive(false);
//	}
//} // handle_projectile_out_of_bounds
//
///*
//Checks if there was a direct hit, and if so, increases the score of the player;
//*/
//void hit_monster() {
//	if (projectile->collided(monster)) {
//		monster->set_alive(false);
//		projectile->set_alive(false);
//		// increment score 
//		// score = score + 1000;
//	}
//} // hit_monster
//
///*
//Moves the projectile up by the speed specified in the initialize function.
//*/
//void move_projectile() {
//	int old_y_pos = projectile->get_y_pos();
//	int speed = projectile->get_speed();
//	if (!projectile->is_alive()) {
//		return;
//	}
//	projectile->set_y_pos(old_y_pos - speed);
//} // move_projectile
//
///*
//Fires the projectile.
//*/
//void fire_projectile() {
//	// fire again
//	if (!projectile->is_alive()) {
//		projectile->set_x_pos(player->get_x_pos() + OFFSET);
//		projectile->set_y_pos(player->get_y_pos());
//		projectile->set_alive(true);
//	}
//} // fire_player_projectile