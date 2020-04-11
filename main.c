#include "opengl/system.h"

int main() {
	WINDOW* g_window = gl_init(800, 600, "Test window");

	gl_run(g_window);
	
	glfwTerminate;

	return 0;
}