#ifndef OPEN_GL_CALLBACK_FUNCS_H
#define OPEN_GL_CALLBACK_FUNCS_H

#include <stdio.h>

#include <GL/glew.h>
#include  <GLFW/glfw3.h>

static GLuint frame_buf_width = 0, frame_buf_height = 0;

void err_callback(int err_code, const char* err_description);							// 에러 출력 함수;
void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);	// 키 입력 콜백함수

void gl_frame_buf_size_callback(GLFWwindow* window, int width, int height);


#endif