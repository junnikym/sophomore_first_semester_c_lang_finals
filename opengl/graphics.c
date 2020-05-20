#include "graphics.h"

void gl_define_buf_obj(const char* title, BUFFER_OBJECT* p_out, const BUFFER_ATTRIBUTES* data) {
	glGenVertexArrays ( 1, &(p_out->VAO) );
	glGenBuffers ( 1, &(p_out->VBO) );
	glGenBuffers ( 1, &(p_out->EBO) );

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

void gl_clear_screen ( ) {
	glClearColor ( 0.0470f, 0.0117f, 0.0431f, 1.0f );
	glClear ( GL_COLOR_BUFFER_BIT );
}

 void gl_draw_obj(const BUFFER_OBJECT* shader, mat4 MVP ) {
	GLuint trans_form_location = 0;
	GLuint mvp_id;

	/*/
	GLint texture_location = glGetUniformLocation ( shader->ID, "Texture" );

	glUniform1i ( texture_location, 0 );
	/*/

	 
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, shader->texture );
	
	mvp_id = glGetUniformLocation(shader->ID, "MVP");
	 
	glUseProgram ( shader->ID );

	glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &MVP[0][0] );
	glBindVertexArray ( shader->VAO );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
	//glDrawArrays ( GL_TRIANGLES, 0, 6 );
}

void	gl_draw_sprite_obj ( const BUFFER_OBJECT* shader,
							mat4 MVP,
							const VEC2* current_sprite_pos ) {
	GLuint trans_form_location = 0;
	GLuint mvp_id;
	
	printf("animation_coord.x : %f \n", current_sprite_pos[0]);

	GLint texture_location = glGetUniformLocation ( shader->ID, "texturePos" );
	glUniform2f( texture_location, current_sprite_pos->x, current_sprite_pos->y);
	
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, shader->texture );
	
	mvp_id = glGetUniformLocation(shader->ID, "MVP");
	 
	glUseProgram ( shader->ID );

	glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &MVP[0][0] );
	glBindVertexArray ( shader->VAO );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
	//glDrawArrays ( GL_TRIANGLES, 0, 6 );
}

 void gl_rander ( /* OBJ Array */ ) {
	 
 }

void gl_shutdown_graphics( BUFFER_OBJECT* x ) {

	// !TODO
	glDeleteBuffers(1, &x->VAO);
	glDeleteBuffers(1, &x->VBO);
	glDeleteVertexArrays(1, &x->EBO);
}
