#ifndef candyinvaders_h
#define candyinvaders_h

const char* health_bars[4] = {"graphics\\health_bar_100.bmp", 
"graphics\\health_bar_75.bmp", 
"graphics\\health_bar_50.bmp", 
"graphics\\health_bar_25.bmp"};

bool load_game_objects(Game* a_game);

//// Counter for FPS
//static volatile int speed_counter = 0;
//
////Interrupt function
//void increment_speed_counter();

#endif 
