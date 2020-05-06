#include "opengl/system.h"
#include "types.h"
#include "memory.h"

int main() {
	int result = 0;
	OBJECT* obj_converter = 0;

	init_memory();

	push_obj_into_g_obj( NULL );
		push_ent_into_g_obj( NULL, 0 );
		g_obj_set_center(0, 0);
			push_force_into_g_obj(NULL, 0, 0);

	set_g_user_obj(0);

	WINDOW g_window;
	result = gl_system_init(&g_window, 800, 600, "Test window");
	if (result != 0)
		return 0;

	gl_system_run(&g_window);
	gl_system_shutdown(&g_window);

	release_memory();

	return 0;
}