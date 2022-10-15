#ifndef sprite_h
#define sprite_h
#include <allegro.h>

class sprite {
private:
	BITMAP* image;
	int width;
	int height;
	int x_pos;
	int y_pos;
	int speed;
	bool alive;
public:
	sprite();
	~sprite();
	bool load(const char* filename);
	void draw(BITMAP* dest);
	int get_width();
	int get_height();
	int get_x_pos();
	int get_y_pos();
	int get_speed();
	bool get_alive();
	void set_x_pos(int new_pos);
	void set_y_pos(int new_pos);
	void set_speed(int new_speed);
	void set_alive(bool state_of_sprite);
	bool is_alive();
	void move_sprite(int x, int y);
	bool collided(sprite* other);
private:
	int inside(int x, int y, int left, int top, int right, int bottom);
};
#endif 
