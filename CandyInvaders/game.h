#ifndef game_h
#define game_h
#include <allegro.h>
#include "player.h"
#include "projectile.h"

// Screen Constants
#define WIDTH 600
#define HEIGHT 800

// Colours
#define BLACK makecol(0, 0, 0)
#define WHITE makecol(255, 255, 255)

// Game Constants
#define FPS 60
#define SPAWN_RATE = 3 * FPS
#define INIT_SCORE 0
#define INIT_HEALTH 100
#define MAX_SCORE_LEN 12 // max int digits = 10 + 1 to account for the '\0' (null) character and + 1 for the '-' character
#define MAX_HEALTH_LEN 4 // 100 = 3 chars + 1 to account for the '\0' (null) character

// Game class
class Game {
private:
	static volatile int speed_counter;
	volatile int timer; // actually don't need this, leaving it for testing purposes
	volatile int time_since_last_spawn;
	BITMAP* buffer;
	BITMAP* background;
	Player* player;
	Projectile* projectile;
	char total_score[MAX_SCORE_LEN];
	char player_health[MAX_HEALTH_LEN];
	bool paused;
public:
	Game();
	~Game();
	bool load_background(const char* filename);
	bool load_player_sprite(const char* filename);
	bool load_projectile_sprite(const char* filename);
	void new_game();
	void reset_game();
	bool run_game();
	bool main_menu();
	bool play_game();
	bool end_game_menu();
	void display_help_module();
	static void increment_speed_counter();
	//static void cast_increment_speed_counter();
private:
	void update_screen();
};

// Interrupt Handler Vars
//extern volatile int speed_counter;
//extern volatile int timer;
//extern volatile int time_since_last_spawn;

// Method Declarations
//bool initialize_game();
//void increment_speed_counter();
//bool main_menu();

#endif 
