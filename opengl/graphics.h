#ifndef OPEN_GL_GRAPHICS_H
#define OPEN_GL_GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include  <GLFW/glfw3.h>

static GLuint triangle_shader_program_id = 0;
static GLuint triangle_vertex_arr_obj = 0;
static GLuint triangle_pos_vertex_buf_obj_id = 0;
static GLuint triangle_color_vertex_buf_obj_id = 0;

int gl_load_shaders(const char* vertex_file_path, const char* fragment_file_path);
int gl_define_vertex_arr_obj();

#endif