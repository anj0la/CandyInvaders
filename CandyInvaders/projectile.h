#ifndef projectile_h
#define projectile_h
#include <allegro.h>
#include "sprite.h"

#define OFFSET 25
#define PROJECTILE_SPEED 7

class Projectile {
private:
	Sprite* projectile;
public:
	Projectile();
	~Projectile();
	Sprite* get_projectile_sprite();
	void move_projectile();
	void fire_projectile(Sprite* player);
	void handle_projectile_out_of_bounds();
	bool hit_monster(Sprite* monster);
};

#endif 
