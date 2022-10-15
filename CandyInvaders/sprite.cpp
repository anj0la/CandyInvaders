#include "allegro.h"
#include "sprite.h"

/*
Constructs a new instance of the sprite class.
*/
sprite::sprite() {
	image = NULL;
	width = 0;
	height = 0;
	x_pos = 0;
	y_pos = 0;
	speed = 3;
	alive = false; // not alive
} // constructor

/*
Removes the sprite bitmap from memory.
*/
sprite::~sprite() {
	if (image != NULL) {
		destroy_bitmap(image);
	}
} // destructor

/*
Loads the sprite.
@returns - true if the bitmap was successfully loaded, false otherwise
*/
bool sprite::load(const char* filename) {
	image = load_bitmap(filename, NULL);
	if (image != NULL) {
		width = image->w;
		height = image->h;
		return true;
	}
	return false; // image is NULL
} // load

/*
Draws the sprite to the destination bitamp (usally screen or a buffer).
@param dest - the bitmap to load
*/
void sprite::draw(BITMAP* dest) {
	draw_sprite(dest, image, x_pos, y_pos);
} // draw

int sprite::get_width() {
	return width;
} // get_width

int sprite::get_height() {
	return height;
} // get_height

int sprite::get_x_pos() {
	return x_pos;
} // get_x_pos

int sprite::get_y_pos() {
	return y_pos;
} // get_y_pos

int sprite::get_speed() {
	return speed;
} // get_speed

bool sprite::get_alive() {
	return alive;
} // get_alive

void sprite::set_x_pos(int new_pos) {
	x_pos = new_pos;
} // set_y_pos

void sprite::set_y_pos(int new_pos) {
	y_pos = new_pos;
} // set_y_pos

void sprite::set_speed(int new_speed) {
	speed = new_speed;
} // set_speed

void sprite::set_alive(bool state_of_sprite) {
	alive = state_of_sprite;
}

bool sprite::is_alive() {
	if (alive == true) {
		return true;
	}
	else {
		return false;
	}
}

void sprite::move_sprite(int x, int y) {
	x_pos += x;
	y_pos += y;
}

int sprite::inside(int x, int y, int left, int top, int right, int bottom) {
	if (x > left && x < right && y > top && y < bottom) {
		return 1;
	}
	else {
		return 0;
	}
}

bool sprite::collided(sprite* other) {
	int other_width_offset = other->get_x_pos() + other->get_width();
	int other_height_offset = other->get_y_pos() + other->get_height();
	if ((x_pos + width) >= other->get_x_pos() && x_pos < other_width_offset && (y_pos + height) >= other->get_y_pos() && y_pos <= other_height_offset) {
		return true;
	}
	// no collisions occurred
	return false;
}