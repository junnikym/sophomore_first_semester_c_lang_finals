#ifndef OPEN_GL_GRAPHICS_H
#define OPEN_GL_GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include  <GLFW/glfw3.h>

int gl_load_shaders(const char* vertex_file_path, const char* fragment_file_path, GLuint* program_id);
int gl_define_vertex_arr(GLuint* program_id, GLuint* vertex_arr_id, GLuint* vertex_buf, GLuint* color_buf);

#endif