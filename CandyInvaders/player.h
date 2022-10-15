#ifndef player_h
#define player_h
#include <allegro.h>
#include "sprite.h"

class player {
private:
	sprite* player_spr;
	int health;
	int score;
public:
	player();
	~player();
	bool load_sprite(const char* filename);
	sprite* get_player_sprite();
	int get_player_health();
	int get_score();
	void set_player_health(int new_health);
	void set_score(int new_score);
	void get_player_input(sprite* player_projectile);
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	void fire_player_projectile(sprite* player_projectile);
	bool collied_with_monster(sprite* monster_spr);
	void handle_player_out_of_bounds();
};


#endif 
