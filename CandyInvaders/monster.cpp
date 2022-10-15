//#include "game.h"
//
///*
//Gets a random position for the candy monster to spawn, between 5 and 595 pixels.
//@return - random x position of the candy monster
//*/
//int get_random_monster_x_pos() {
//	return rand() % 595 + 5;
//} // get_random_monster_x_pos
//
///*
//Checks if a monster is out of bounds, that is, its y position is greater than height of the game.
//*/
//void handle_monster_out_of_bounds() {
//	if (monster->get_y_pos() >= 900) { // down
//		monster->set_y_pos(-100);
//		monster->set_x_pos(get_random_monster_x_pos());
//	}
//} // monster_out_of_bounds
//
///*
//Moves the monster down by the speed specified in the initialize function.
//*/
//void move_monster() {
//	int old_y_pos = monster->get_y_pos();
//	int speed = monster->get_speed();
//	monster->set_y_pos(old_y_pos + speed);
//} // move_monster
//
///*
//Respawns the monster if it is not alive.
//*/
//void respawn_monster() {
//	if (!monster->is_alive()) {
//		monster->set_y_pos(-200);
//		monster->set_x_pos(get_random_monster_x_pos());
//		monster->set_alive(true);
//	}
//} // respawn_monster