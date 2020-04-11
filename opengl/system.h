#ifndef OPEN_GL_SYSTEM_H
#define OPEN_GL_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include  <GLFW/glfw3.h>

typedef struct _WINDOW {
    GLFWwindow* window;
    int width, height;
    const char* title;
} WINDOW;

void err_callback(int err_code, const char* err_description);							// ���� ��� �Լ�;
void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);	// Ű �Է� �ݹ��Լ�

WINDOW* gl_init(int width, int height, const char* title);
void gl_run(WINDOW* window);

#endif