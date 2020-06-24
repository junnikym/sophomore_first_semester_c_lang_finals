#ifndef OPEN_GL_CALLBACK_FUNCS_H
#define OPEN_GL_CALLBACK_FUNCS_H

#include "../user_control.h"
#include "camera.h"

#include "../vector2.h"

#include <stdio.h>

#include <GL/glew.h>
#include  <GLFW/glfw3.h>

typedef struct _INPUT_COMPONANT_ {
	int key;
	int key_action;
	VEC2 mouse_pos;
	int left_clk;
	int right_clk;
} INPUT_COMPONANT;

extern INPUT_COMPONANT g_input;

static GLuint frame_buf_width = 0, frame_buf_height = 0;

// OpenGL에서 에러가 발생 시 다음 콜백함수를 통해 오류가 처리된다.
void err_callback(int err_code, const char* err_description);

// 키보드에 대한 이벤트가 실행되면 다음 콜백 함수를 통해 처리가 된다.
void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);

// 마우스에 대한 이밴트가 실행되면 다음 콜백 함수를 통해 처리가 된다.
void mouse_cursor_callback(GLFWwindow* window, double pos_x, double pos_y);			// 커서 위치
void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset);	// 스크롤 휠

// 화면의 사이즈가 변경 될 경우 다음 콜백 함수를 통해 처리가 된다.
void gl_frame_buf_size_callback(GLFWwindow* window, int width, int height);


#endif
