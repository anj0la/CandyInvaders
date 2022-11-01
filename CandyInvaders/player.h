#ifndef player_h
#define player_h
#include <allegro.h>
#include "sprite.h"

#define PROJECTILE_OFFSET 60
#define VOL 32
#define PAN 32
#define FREQ 1000

class Player {
private:
	Sprite* player_spr;
	int health;
	int score;
public:
	Player();
	~Player();
	bool load_sprite(const char* filename);
	Sprite* get_player_sprite();
	int get_player_health();
	int get_score();
	void set_player_health(int new_health);
	void set_score(int new_score);
	void get_player_input(Sprite* player_projectile, SAMPLE* shooting_sound);
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	void fire_player_projectile(Sprite* player_projectile, SAMPLE* shooting_sound);
	bool collied_with_monster(Sprite* monster_spr);
	void handle_player_out_of_bounds();
};

#endif 
