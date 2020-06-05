#include "buffer_obj.h"

// ------------------------------------------------------- //
// ----- OpenGL Graphics functions		------------------

void gl_define_buf_obj( BUFFER_OBJECT* p_out, const BUFFER_ATTRIBUTES* data, GLsizei n ) {
	p_out->n = n;
	
	glGenVertexArrays ( n, &(p_out->VAO) );
	glGenBuffers ( n, &(p_out->VBO) );
	glGenBuffers ( n, &(p_out->EBO) );

	glBindVertexArray ( (p_out->VAO) );

	glBindBuffer ( GL_ARRAY_BUFFER, (p_out->VBO) );
	glBufferData ( GL_ARRAY_BUFFER, data->vertices_size, data->vertices_data, GL_STATIC_DRAW );

	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, (p_out->EBO) );
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER, data->indices_size, data->indices_data, GL_STATIC_DRAW );

	// position attribute
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), (void*)0 );
	glEnableVertexAttribArray ( 0 );
	// color attribute
	glVertexAttribPointer ( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), (void*)(3 * sizeof ( float )) );
	glEnableVertexAttribArray ( 1 );
	// texture coord attribute
	glVertexAttribPointer ( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), (void*)(6 * sizeof ( float )) );
	glEnableVertexAttribArray ( 2 );
	
}

void gl_define_texture ( const GLuint* program_id, const GLuint* texture_buf, int n ) {
	GLint texture_location = glGetUniformLocation ( *program_id, "Texture" );
                  
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture_buf);

	glUniform1i ( texture_location, n );
}

void gl_release_buf_obj	( BUFFER_OBJECT* buf_obj ) {
	glDeleteBuffers(buf_obj->ID, &buf_obj->VAO);
	glDeleteBuffers(buf_obj->ID, &buf_obj->VBO);
	glDeleteVertexArrays(buf_obj->ID, &buf_obj->EBO);
}

// ------------------------------------------------------- //
