#include "graphics.h"

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
	
	GLint texture_location = glGetUniformLocation ( shader->ID, "texturePos" );
	//glUniform2f( texture_location, current_sprite_pos->x, current_sprite_pos->y);
	
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, shader->texture );
	
	mvp_id = glGetUniformLocation(shader->ID, "MVP");
	 
	glUseProgram ( shader->ID );

	glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &MVP[0][0] );
	glBindVertexArray ( shader->VAO );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
}

 void gl_rander ( /* OBJ Array */ ) {
	 
 }

void gl_shutdown_graphics( BUFFER_OBJECT* x ) {
	glDeleteBuffers(1, &x->VAO);
	glDeleteBuffers(1, &x->VBO);
	glDeleteVertexArrays(1, &x->EBO);
}
