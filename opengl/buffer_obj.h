#ifndef BUFFER_OBJ_H
#define BUFFER_OBJ_H

#include "../types.h"
#include "texture.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <cglm/cglm.h>

// ------------------------------------------------------- //
// ----- Buffer Structure	------------------------------

typedef struct _BUFFER_OBJECT {
	char title[_TITLE_SIZE];
	GLuint VBO, VAO, EBO;
	GLuint ID;
	GLuint texture;
	// ! TODO : append sprite_info
} BUFFER_OBJECT;

typedef struct _BUFFER_ATTRIBUTES {
	GLfloat* vertices_data;
	int vertices_size;
	GLuint* indices_data;
	int indices_size;
	int* attr_arr_size;
} BUFFER_ATTRIBUTES;

// ------------------------------------------------------- //
// ----- STD BUFFERS	----------------------------------

// --- Square Const Buffers

const static GLfloat g_SQUARE_VERTICES[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f/16, 0.0f, // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f/16, 1.0f, // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, // bottom left
	-0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f  // top left
};

const static GLuint g_SQUARE_INDICES[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

const static BUFFER_ATTRIBUTES g_SQUARE_DATA = {
	&g_SQUARE_VERTICES,
	sizeof(g_SQUARE_VERTICES),
	&g_SQUARE_INDICES,
	sizeof(g_SQUARE_INDICES)
};

// ------------------------------------------------------- //
// ----- OpenGL Graphics functions		------------------

void	gl_define_buf_obj	 ( const char* title, BUFFER_OBJECT* p_out, const BUFFER_ATTRIBUTES* data );
void	gl_define_texture	 ( const GLuint* program_id, const GLuint* texture_buf, int n );


// ------------------------------------------------------- //

#endif /* BUFFER_OBJ_H */
