#ifndef OPEN_GL_GRAPHICS_H
#define OPEN_GL_GRAPHICS_H

#include "../types.h"
#include "../memory.h"

#include "texture.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#include <malloc.h>
#endif

#include <GL/glew.h>
#include  <GLFW/glfw3.h>
#include <cglm/cglm.h>


// ------------------------------------------------------- //
// ----- Buffer Structure	------------------------------

typedef struct _BUFFER_OBJECT {
	char title[_TITLE_SIZE];
	GLuint VBO, VAO, EBO;
	GLuint ID;
	GLuint texture;			// TODO MAKE -> ARRAY
} BUFFER_OBJECT;

typedef struct _BUFFER_ATTRIBUTES {
	GLfloat* vertices_data;
	int vertices_size;
	GLuint* indices_data;
	int indices_size;
	int attr_arr_size[3];
} BUFFER_ATTRIBUTES;

// ------------------------------------------------------- //
// ----- STD BUFFERS	----------------------------------

// 2D ATTRIBUTE SIZE ARRAY

static const GLfloat g_2D_ATTR_SIZE[3] = { 3, 3, 2 };

// --- Square Const Buffers

const static GLfloat g_SQUARE_VERTICES[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left 
};

const static GLuint g_SQUARE_INDICES[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

static const BUFFER_ATTRIBUTES g_SQUARE_DATA = {
	&g_SQUARE_VERTICES,
	sizeof(g_SQUARE_VERTICES),
	&g_SQUARE_INDICES,
	sizeof(g_SQUARE_INDICES),
	g_2D_ATTR_SIZE
};

// ------------------------------------------------------- //
// ----- OpenGL Graphics functions		------------------

void	gl_define_buf_obj	 ( const char* title, BUFFER_OBJECT* p_out, const BUFFER_ATTRIBUTES* data );
void	gl_define_texture	 ( const GLuint* program_id, const GLuint* texture_buf, int n );
void	gl_disable_attr_arr  ();

void	gl_clear_screen		 ();
void 	gl_draw_obj 		 ( const BUFFER_OBJECT* shader, int attr_size[3], mat4* MVP );
void	gl_rander			 ( /* OBJ Array */ );
void	gl_shutdown_graphics( BUFFER_OBJECT* x );

// ------------------------------------------------------- //

#endif
