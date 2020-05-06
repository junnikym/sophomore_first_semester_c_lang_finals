#ifndef OPEN_GL_GRAPHICS_H
#define OPEN_GL_GRAPHICS_H

#include "../types.h"
#include "../memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#include <malloc.h>
#endif

#include <GL/glew.h>
#include  <GLFW/glfw3.h>

typedef struct _BUFFER_OBJECT {
	char title[_TITLE_SIZE];
	GLuint VBO, VAO, EBO;
	GLuint ID;
	GLuint texture;			// TODO MAKE -> ARRAY
} BUFFER_OBJECT;

typedef struct _BUFFER_ATTRIBUTES {
	float* vertices_data;
	int vertices_size;
	GLuint* indices_data;
	int indices_size;
} BUFFER_ATTRIBUTES;

// ------------------------------------------------------- //
// ----- STD BUFFERS		------------------------------

// --- Square Const Buffers

static const float g_SQUARE_VERTICES[] = {
	// positions		// colors			// texture coords
	0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f,	1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};

static const GLuint g_SQUARE_INDICES[] = {
	0, 1, 2,
	2, 3, 0
};

static const BUFFER_ATTRIBUTES g_SQUARE_DATA = {
	&g_SQUARE_VERTICES,
	sizeof(g_SQUARE_VERTICES),
	&g_SQUARE_INDICES,
	sizeof(g_SQUARE_INDICES)
};

// ------------------------------------------------------- //
// ----- OpenGL Graphics functions		------------------

GLuint*	gl_load_shaders		 ( const char* vertex_file_path, const char* fragment_file_path, GLuint* program_id );
void	gl_define_buf_obj	 ( const char* title, BUFFER_OBJECT* p_out, const BUFFER_ATTRIBUTES* data );

GLuint*	gl_load_texture		 ( const GLuint* program_id, const char* filename, GLuint* p_out );
void	gl_define_texture	 ( const GLuint* program_id, const GLuint* texture_buf, int n );

//int		gl_vertex_link		 ( const GLuint program_id, const BUFFER_OBJECT* buffers );
//void	gl_create_vertex_buf ( const char* title, const BUFFER_ATTRIBUTES* attribute, GLuint program_id );

int		gl_create_shader_buf ( BUFFER_OBJECT* p_out, 
							   const char* title, 
							   const BUFFER_ATTRIBUTES* attribute );

//void	gl_init_graphics	 ( const GLuint* id );
void	gl_clear_screen		 ();
void	gl_draw_obj			 ( const BUFFER_OBJECT* shader );
void	gl_rander			 ( /* OBJ Array */ );
void	gl_shutdown_graphics( BUFFER_OBJECT* x );

// ------------------------------------------------------- //

#endif
