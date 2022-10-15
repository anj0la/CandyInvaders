//#include <allegro.h>
//#include <stdio.h> 
//#include <stdlib.h>
//
//int main(void) {
//	if (allegro_init() != 0) {
//		return 1;
//	}
//	set_color_depth(24);
//	install_keyboard();
//	set_keyboard_rate(10000, 0);
//	int ret = set_gfx_mode(GFX_SAFE, 800, 600, 0, 0);
//	if (ret != 0) {
//		allegro_message("Error setting GFX mode.");
//		return 1;
//	}
//	while (!key[KEY_ESC]);
//	allegro_exit();
//	return 0;
//}
//END_OF_MAIN()