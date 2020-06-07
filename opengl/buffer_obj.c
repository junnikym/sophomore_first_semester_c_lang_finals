#include "buffer_obj.h"

// ------------------------------------------------------- //
// ----- OpenGL Graphics functions		------------------

void buf_obj_init ( BUFFER_OBJECT* lhs ) {
	lhs->VAO = 0;
	lhs->VBO = 0;
	lhs->EBO = 0;
	
	lhs->ID = 0;
	
	lhs->texture = 0;
	
	lhs->n = 0;
}

void set_square_vertices ( GLfloat p_out[32], VEC2 size, double z, VEC2 texture ) {
	
	/*	position index		|	texture coords index
	 *	 0	 1	 2			|	6	 7
	 *	 8	 9	10			|	14	15
	 *	16	17	18			|	22	23
	 *	24	25	26			|	30	31
	 */
	
	// set position
	p_out[ 0] =  size.x;		p_out[ 1] =  size.y;	p_out[ 2] = z;
	p_out[ 8] =  size.x;		p_out[ 9] = -size.y;	p_out[10] = z;
	p_out[16] = -size.x;		p_out[17] = -size.y;	p_out[18] = z;
	p_out[24] = -size.x;		p_out[25] =  size.y;	p_out[26] = z;
	
	// set texture coord
	p_out[ 6] = texture.x;		p_out[ 7] = 0.0f;
	p_out[14] = texture.x;		p_out[15] = texture.y;
	p_out[22] = 0.0f;			p_out[23] = texture.y;
	p_out[30] = 0.0f;			p_out[31] = 0.0f;
}

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
	glDeleteBuffers(buf_obj->n, &buf_obj->VAO);
	glDeleteBuffers(buf_obj->n, &buf_obj->VBO);
	glDeleteVertexArrays(buf_obj->n, &buf_obj->EBO);
}

// ------------------------------------------------------- //
