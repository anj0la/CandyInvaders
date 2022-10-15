#include <allegro.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main(void) {
	srand(time(NULL));
	if (allegro_init() != 0) {
		return 1;
	}
	set_color_depth(24);
	install_keyboard();
	set_keyboard_rate(10000, 0);
	int ret = set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0);
	if (ret != 0) {
		allegro_message("Error setting GFX mode.");
		return 1;
	}
	
	Game* game = new Game();
	game->load_background("graphics\\static_background.bmp");
	game->new_game();

	// while (!key[KEY_ESC]);
	allegro_exit();
	return 0;
}
END_OF_MAIN()