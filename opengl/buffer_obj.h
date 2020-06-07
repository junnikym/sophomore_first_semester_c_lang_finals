#ifndef BUFFER_OBJ_H
#define BUFFER_OBJ_H

#include "../vector2.h"
#include "../types.h"
#include "texture.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <cglm/cglm.h>

// ------------------------------------------------------- //
// ----- Buffer Structure	------------------------------

typedef struct _BUFFER_OBJECT {
	GLuint VBO, VAO, EBO;
	GLuint ID;
	GLuint texture;
	GLsizei n;
	// ! TODO : append sprite_info
} BUFFER_OBJECT;

typedef struct _BUFFER_ATTRIBUTES {
	GLfloat* vertices_data;
	int vertices_size;
	GLuint* indices_data;
	int indices_size;
} BUFFER_ATTRIBUTES;

// ------------------------------------------------------- //
// ----- STD BUFFERS	----------------------------------

// --- Square Const Buffers

const static GLfloat g_SQUARE_VERTICES[] = {
	// positions          // colors           // texture coords
	 1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
	 1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f, // bottom right
	-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, // bottom left
	-1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f  // top left
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

void 	buf_obj_init		 ( BUFFER_OBJECT* lhs );
void 	set_square_vertices	 ( GLfloat p_out[32], VEC2 size, double z, VEC2 texture );

void	gl_define_buf_obj	 ( BUFFER_OBJECT* p_out, const BUFFER_ATTRIBUTES* data, GLsizei n);
void	gl_define_texture	 ( const GLuint* program_id, const GLuint* texture_buf, int n );

void	gl_release_buf_obj	 ( BUFFER_OBJECT* buf_obj );

// ------------------------------------------------------- //

#endif /* BUFFER_OBJ_H */
