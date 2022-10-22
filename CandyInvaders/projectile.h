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
	void move_projectile_up();
	void move_projectile_down();
	void fire_projectile(Sprite* other);
	void handle_projectile_out_of_bounds();
	bool direct_hit(Sprite* other);
};

#endif 
