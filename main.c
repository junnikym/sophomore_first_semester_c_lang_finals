#include "opengl/system.h"
#include "types.h"

int main() {
	int result = 0;

	WINDOW g_window;
	result = gl_system_init(&g_window, 800, 600, "Test window");
	if (result != 0)
		return 0;

	gl_system_run(&g_window);
	gl_system_shutdown(&g_window);
	
	return 0;
}