#include "graphics.h"

void gl_define_buf_obj(const char* title, BUFFER_OBJECT* p_out, const BUFFER_ATTRIBUTES* data) {
	GLuint VertexArrayID;
	glGenVertexArrays(1, &p_out->VAO);
	glBindVertexArray(p_out->VAO);

	glGenBuffers(1, &p_out->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, p_out->VBO);
	glBufferData(GL_ARRAY_BUFFER, data->vertices_size , data->vertices_data, GL_STATIC_DRAW);

	glGenBuffers(1, &p_out->EBO);
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, p_out->EBO );
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER, data->indices_size, data->indices_data, GL_STATIC_DRAW );
}

void gl_define_texture ( const GLuint* program_id, const GLuint* texture_buf, int n ) {
	GLint texture_location = glGetUniformLocation ( *program_id, "texture" );

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture_buf);

	glUniform1i ( texture_location, n );
}

void gl_clear_screen ( ) {
	glClearColor ( 0, 0, 0, 1 );
	glClear ( GL_COLOR_BUFFER_BIT );
}

void gl_enable_attr_arr (int arr_size[3]) {
	// position attribute
	glVertexAttribPointer ( 0, arr_size[0], GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), (void*)0 );
	glEnableVertexAttribArray ( 0 );
	// color attribute
	glVertexAttribPointer ( 1, arr_size[1], GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), (void*)(3 * sizeof ( float )) );
	glEnableVertexAttribArray ( 1 );
	// texture coord attribute
	glVertexAttribPointer ( 2, arr_size[2], GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), (void*)(6 * sizeof ( float )) );
	glEnableVertexAttribArray ( 2 );
}

void gl_disable_attr_arr () {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

 void gl_draw_obj(const BUFFER_OBJECT* shader, int attr_size[3], mat4* MVP ) {
	GLuint trans_form_location = 0;
	GLuint texture_id = 0;
	GLuint mvp_id;

	VEC2 user_pos = g_obj_get_position(0);

	gl_enable_attr_arr( attr_size );

	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, shader->texture );

	// for change position
	texture_id  = glGetUniformLocation(shader->ID, "myTextureSampler");
	
	mvp_id = glGetUniformLocation(shader->ID, "MVP");
	 
	glUseProgram ( shader->ID );

	glUniformMatrix4fv( mvp_id, 1, GL_FALSE, MVP );
	glBindVertexArray ( shader->VAO );
	 glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

	gl_disable_attr_arr();
}

 void gl_rander ( /* OBJ Array */ ) {
	 
 }

void gl_shutdown_graphics( BUFFER_OBJECT* x ) {

	// !TODO
	glDeleteBuffers(1, &x->VAO);
	glDeleteBuffers(1, &x->VBO);
	glDeleteVertexArrays(1, &x->EBO);
}
