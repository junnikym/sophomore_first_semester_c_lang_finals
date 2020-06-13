#ifndef OPEN_GL_CALLBACK_FUNCS_H
#define OPEN_GL_CALLBACK_FUNCS_H

#include "../user_control.h"

#include <stdio.h>

#include <GL/glew.h>
#include  <GLFW/glfw3.h>

static GLuint frame_buf_width = 0, frame_buf_height = 0;

// OpenGL에서 에러가 발생 시 다음 콜백함수를 통해 오류가 처리된다.
void err_callback(int err_code, const char* err_description);

// 키보드에 어떠한 이벤트가 실행되면 다음 콜백 함수를 통해 처리가 된다.
void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);	//	~

// 화면의 사이즈가 변경 될 경우 다음 콜백 함수를 통해 처리가 된다.
void gl_frame_buf_size_callback(GLFWwindow* window, int width, int height);


#endif
