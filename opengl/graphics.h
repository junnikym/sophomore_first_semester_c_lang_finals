#ifndef OPEN_GL_GRAPHICS_H
#define OPEN_GL_GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include  <GLFW/glfw3.h>

static GLuint triangle_vertex_arr_obj = 0;
static GLuint vertex_buf = 0;
static GLuint color_buf = 0;

int gl_load_shaders(const char* vertex_file_path, const char* fragment_file_path, GLuint* program_id);
int gl_define_vertex_arr_obj(GLuint* program_id);

#endif