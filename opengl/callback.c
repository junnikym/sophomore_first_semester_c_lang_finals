#include "callback.h"
#include <stdio.h>

void err_callback(int err_code, const char* err_description) {	// 에러 콜백 함수
	fprintf(stderr, "Error : %s\n", err_description);				// 에러를 출력
}

void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)		// esc를 입력시
		glfwSetWindowShouldClose(window, GLFW_TRUE);		// 프로그램을 종료해준다.
	
	if ( is_g_user_obj_setted() )
		game_control(&key, &action);		// 사용자 컨트롤 함수에 키보드 이벤트 값을 전달해주어 케릭터를 조종함.
}

void mouse_cursor_callback(GLFWwindow* window, double pos_x, double pos_y) {
	
}

void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
	// 스크롤을 통해 화면을 줌 인/아웃 조작을 한다.
	gl_add_FOV(-y_offset);
	gl_set_projection();
	gl_update_cam();
}

void gl_frame_buf_size_callback(GLFWwindow* window, int width, int height) {
	// 화면의 크기가 바뀔 때 호출될 콜백함수; 추후 코드 추가 예정
	
	glViewport(0, 0, width, height);

	frame_buf_width = width;
	frame_buf_height = height;
}
