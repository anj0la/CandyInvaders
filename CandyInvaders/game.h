#ifndef game
#define game
#include <allegro.h>
#include "sprite.h"

// Screen Constants
#define WIDTH 600
#define HEIGHT 800

// Colours
#define WHITE makecol(255, 255, 255)

// Game Constants
#define PROJECTILE_SPEED 7
#define MONSTER_SPEED 4
#define OFFSET 25
#define FPS 60
#define SPAWN_RATE = 3 * FPS;

// Game Vars
bool game_over;

// Interrupt Handler Vars
volatile int speed_counter = 0;
volatile int timer = 15 * FPS;
volatile int time_since_last_spawn = 0;

//// Sprites
//extern sprite* player;
//extern sprite* monster;
//extern sprite* projectile;
//extern sprite* monster_projectile;
//
//// Double Buffer
//BITMAP* buffer;
//
//// Function Prototypes - Initialization
//void initialize_game();
//
////Function Prototypes - Player
//void move_up();
//void move_down();
//void move_left();
//void move_right();
//void get_player_input();
//void collied_with_monster();
//void handle_player_out_of_bounds();
//
//// Function Prototypes - Monster
//int get_random_monster_x_pos();
//void respawn_monster();
//void move_monster();
//void handle_monster_out_of_bounds();
//
//// Function Prototypes - Projectile
//void move_projectile();
//void fire_projectile();
//void handle_projectile_out_of_bounds();
//void hit_monster();
//
//// Function Prototypes - Monster Projectile
//void move_monster_projectile();
//void hit_player();

//extern bool spawned;
//extern bool game_over;

#endif 
