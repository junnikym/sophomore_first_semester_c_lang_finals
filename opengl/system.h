#ifndef OPEN_GL_SYSTEM_H
#define OPEN_GL_SYSTEM_H

#include "callback_funcs.h"
#include "graphics.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include  <GLFW/glfw3.h>

typedef struct _WINDOW {
    GLFWwindow* window;
    int width, height;
    const char* title;
} WINDOW;

WINDOW* gl_system_init(int width, int height, const char* title);
void gl_system_run(WINDOW* window);
void gl_system_shutdown(WINDOW* window);

#endif