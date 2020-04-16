#ifndef OPEN_GL_GRAPHICS_H
#define OPEN_GL_GRAPHICS_H

#include "../types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <GL/glew.h>
#include  <GLFW/glfw3.h>

typedef struct _VERTEX_BUF {
	GLuint vertex_arr_id;
	GLuint vertex_buffer;
	GLuint color_buffer;
	GLuint elem_buffer;
} VERTEX_BUF;

typedef struct _BUF_OBJ_ATT {
	float* vertex_data;
	int vertex_data_size;
	float* color_data;
	int color_data_size;
	int* elem_data;
	int elem_data_size;

	VEC2 position;
} BUF_OBJ_ATT;

// Square Const Buffers

static float g_SQUARE_VERTEX[] = {
	-0.5f,  0.5f, 0.0f, //vertex 1 : Top-left
	 0.5f,  0.5f, 0.0f, //vertex 2 : Top-right
	 0.5f, -0.5f, 0.0f, //vertex 3 : Bottom-right
	-0.5f, -0.5f, 0.0f //vertex 4 : Bottom-left
};

static const GLuint g_SQUARE_ELEM[] = {
	0, 1, 2,
	2, 3, 0
};

// -- for test

const static float g_SQUARE_COLOR[] = {
	1.0f, 0.0f, 0.0f, //vertex 1 : RED (1,0,0)
	0.0f, 1.0f, 0.0f, //vertex 2 : GREEN (0,1,0) 
	0.0f, 0.0f, 1.0f,  //vertex 3 : BLUE (0,0,1)
	1.0f, 1.0f, 1.0f  //vertex 4 : WHITE (1,1,1)
};

//--

static const BUF_OBJ_ATT g_SQUARE_DATA = {
	&g_SQUARE_VERTEX,
	sizeof(g_SQUARE_VERTEX),
	&g_SQUARE_COLOR,
	sizeof(g_SQUARE_COLOR),
	&g_SQUARE_ELEM,
	sizeof(g_SQUARE_ELEM)
};

VERTEX_BUF* gl_define_buffer_obj(VERTEX_BUF* p_out, const BUF_OBJ_ATT* data);
int gl_vertex_link(GLuint* program_id, const VERTEX_BUF* buffers);
void gl_shutdown_graphics();

#endif