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
#define FPS 60
#define SPAWN_RATE = 3 * FPS;

// Interrupt Handler Vars
volatile int speed_counter = 0;
volatile int timer = 15 * FPS;
volatile int time_since_last_spawn = 0;

// Method Declarations
bool initialize_game();
void increment_speed_counter();

#endif 
