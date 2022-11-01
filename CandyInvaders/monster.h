#ifndef monster_h
#define monster_h
#include <allegro.h>
#include "sprite.h"

#define MONSTER_SPEED 3

class Monster {
private:
	Sprite* monster_spr;
public:
	Monster();
	~Monster();
	Sprite* get_monster_sprite();
	void move_monster();
	void respawn_monster();
	void handle_monster_out_of_bounds();
	int get_random_monster_x_pos();
};

#endif 
