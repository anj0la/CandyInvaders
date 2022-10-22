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
	game->load_player_sprite("graphics\\candy_ship.bmp");
	game->load_projectile_sprite("graphics\\candy_swirl.bmp");
	game->load_monster_sprite("graphics\\candy_monster.bmp");
	game->load_monster_projectile_sprite("graphics\\monster_projectile.bmp");
	game->new_game();
	allegro_exit();
	return 0;
}
END_OF_MAIN()