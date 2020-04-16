#include "opengl/system.h"
#include "types.h"

int main() {
	
	WINDOW* g_window = gl_system_init(800, 600, "Test window");

	gl_system_run(g_window);
	gl_system_shutdown(g_window);
	
	return 0;
}