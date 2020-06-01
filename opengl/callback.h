#ifndef OPEN_GL_CALLBACK_FUNCS_H
#define OPEN_GL_CALLBACK_FUNCS_H

#include "../user_control.h"

#include <stdio.h>

#include <GL/glew.h>
#include  <GLFW/glfw3.h>

typedef struct _MOUSE_INPUT_ {
	VEC2 cur;
	int mouse_input;
	int mouse_act;
} MOUSE_INPUT;

static GLuint frame_buf_width = 0, frame_buf_height = 0;

void err_callback(int err_code, const char* err_description);								//	~
void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);	//	~

void gl_frame_buf_size_callback(GLFWwindow* window, int width, int height);


#endif
