#include "callback_funcs.h"

void err_callback(int err_code, const char* err_description) {
	fprintf(stderr, "Error : %s\n", err_description);
}

void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)			// esc키 입력 시 종료
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	
	game_control(&key, &action);
}

void gl_frame_buf_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	frame_buf_width = width;
	frame_buf_height = height;
}