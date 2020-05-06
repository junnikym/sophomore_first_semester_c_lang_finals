#include "graphics.h"
#include "stb_image.h"

GLuint* gl_load_shaders(const char* vertex_file_path, const char* fragment_file_path, GLuint* program_id) {
	FILE* fp;
	int file_size = 0;
	char* vertex_shader_code;
	char* fragment_shader_code;

	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	GLint result = GL_FALSE;
	GLchar error_log[512] = "";

	fp = fopen(vertex_file_path, "r");
	if (fp == NULL) {
		printf("fail to open vertex shader file");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);

	vertex_shader_code = (char*)malloc(file_size + 1);
	memset(vertex_shader_code, 0, file_size + 1);

	fseek(fp, 0, SEEK_SET);
	fread(vertex_shader_code, file_size, 1, fp);

	fclose(fp);


	fp = fopen(fragment_file_path, "r");
	if (fp == NULL) {
		printf("fail to open fragment shader file");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);

	fragment_shader_code = (char*)malloc(file_size + 1);
	memset(fragment_shader_code, 0, file_size + 1);

	fseek(fp, 0, SEEK_SET);
	fread(fragment_shader_code, file_size, 1, fp);

	fclose(fp);

	// SHADER COMPILE
	// --- Compile Vertex Shader
	glShaderSource(vertex_shader_id, 1, &vertex_shader_code, NULL);
	glCompileShader(vertex_shader_id);

	// ( check vertex shader )
	glGetShaderiv ( vertex_shader_id, GL_COMPILE_STATUS, &result );
	if (!result) {
		glGetShaderInfoLog(vertex_shader_id, 512, NULL, error_log);
		fprintf(stderr, "fail to compile vertex shader : %s \n", error_log);

		glDeleteShader(vertex_shader_id);
		return NULL;
	}

	// --- Compile Fragment Shader
	glShaderSource(fragment_shader_id, 1, &fragment_shader_code, NULL);
	glCompileShader(fragment_shader_id);

	// ( check Fragment Shader)
	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragment_shader_id, 512, NULL, error_log);
		fprintf(stderr, "fail to compile fragment_shader shader ; %s \n", error_log);

		glDeleteShader(fragment_shader_id);
		return NULL;
	}

	// LINK
	*program_id = glCreateProgram();

	glAttachShader(*program_id, vertex_shader_id);
	glAttachShader(*program_id, fragment_shader_id);
	glLinkProgram(*program_id);

	// ( Check Linked Program)
	glGetProgramiv(*program_id, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(*program_id, 512, NULL, error_log);
		fprintf(stderr, "fail to link shader program ; %s \n", error_log);

		return NULL;
	}

	glDetachShader(*program_id, vertex_shader_id);
	glDetachShader(*program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	free(vertex_shader_code);
	free(fragment_shader_code);

	return program_id;
}

void gl_define_buf_obj(const char* title, BUFFER_OBJECT* p_out, const BUFFER_ATTRIBUTES* data) {

	glGenVertexArrays(1, &p_out->VBO);
	glGenBuffers(1, &p_out->VBO);
	glGenBuffers(1, &p_out->EBO);

	glBindVertexArray(p_out->VAO);

	glBindBuffer ( GL_ARRAY_BUFFER, p_out->VBO );
	glBufferData (
		GL_ARRAY_BUFFER, 
		data->vertices_size, 
		data->vertices_data, 
		GL_STATIC_DRAW
	);

	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, p_out->EBO );
	glBufferData ( 
		GL_ELEMENT_ARRAY_BUFFER, 
		data->indices_size, data->
		indices_data, 
		GL_STATIC_DRAW 
	);

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

// update like this http://www.opengl-tutorial.org/kr/beginners-tutorials/tutorial-5-a-textured-cube
GLuint* gl_load_texture ( const GLuint* program_id, const char* filename, GLuint* p_out) {
	// ! TODO convert C Syntex
	printf("Reading image %s\n", filename );

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int data_pos;
	unsigned int image_size;
	unsigned int width, height;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen( filename,"rb");
	if (!file) {
		printf( "%s could not be opened. \n", filename );

		return NULL;
	}

	// If less than 54 bytes are read, problem
	if ( fread(header, 1, 54, file)!=54 ){ 
		printf("Not a correct BMP file\n");
		return 0;
	}
	// A BMP files always begins with "BM"
	if ( header[0]!='B' || header[1]!='M' ){
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Make sure this is a 24bpp file
	if ( *(int*)&(header[0x1E])!=0  ) { printf("Not a correct BMP file\n");    return 0; }
	if ( *(int*)&(header[0x1C])!=24 ) { printf("Not a correct BMP file\n");    return 0; }

	// Read the information about the image
	data_pos	= *(int*)&(header[0x0A]);
	image_size	= *(int*)&(header[0x22]);
	width		= *(int*)&(header[0x12]);
	height		= *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if ( image_size == 0 )    image_size = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if ( data_pos == 0 )      data_pos = 54; // The BMP header is done that way


	/*
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);

	vertex_shader_code = (char*)malloc(file_size + 1);
	*/

	// Create a buffer
	data = (unsigned char*)malloc(image_size);

	// Read the actual data from the file into the buffer
	fread( data, 1, image_size, file );

	// Everything is in memory now, the file wan be closed
	fclose (file);

	// Create one OpenGL texture
	GLuint texture_id;
	glGenTextures(1, &texture_id );
	
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texture_id );

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	free(data);

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return texture_id;
}

void gl_define_texture ( const GLuint* program_id, const GLuint* texture_buf, int n ) {
	GLint texture_location = glGetUniformLocation ( *program_id, "texture" );

	glUniform1i ( texture_location, n );
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, *texture_buf );
}
/*
 void gl_create_vertex_buf( const char* title, const BUFFER_ATTRIBUTES* attribute, GLuint program_id) {
	 int result = 0;
	 // !TODO : make the fuction that manage vertex buffer array;
	 VERTEX_BUF* last_vertex_buf_ptr = &vertex_buffers;

	 gl_define_buf_obj ("TESTER", last_vertex_buf_ptr, &g_SQUARE_DATA);

	 result = gl_vertex_link(program_id, last_vertex_buf_ptr);
	 if (result != 0) {
		 fprintf(stderr, "fail to create shader program\n");

		 glfwTerminate();
		 exit(EXIT_FAILURE);
	 }

	 glBindVertexArray(last_vertex_buf_ptr->vertex_arr_id);
 }
 */
/*
void gl_init_graphics ( const GLuint* id ) {
	gl_create_texture ( "../../resource/texture/wall.jpg", &id );
}
*/
int gl_create_shader_buf ( BUFFER_OBJECT * p_out, 
						   const char* title, 
						   const BUFFER_ATTRIBUTES* attribute ) {
	int result = 0;

	result = gl_load_shaders (
		"../../opengl/shader/vertex_shader.vs",
		"../../opengl/shader/fragment_shader.fs",
		&(p_out->ID)
	);
	if ( result != 0 ) {
		fprintf ( stderr, "fail to create shader program\n" );

		glfwTerminate ( );
		return -1;
	}

	gl_define_buf_obj ( title, p_out, attribute );
}

void gl_clear_screen ( ) {
	glClearColor ( 0, 0, 0, 1 );
	glClear ( GL_COLOR_BUFFER_BIT );
}

 void gl_draw_obj(const BUFFER_OBJECT* shader ) {
	 GLuint trans_form_location = 0;
	 GLuint texture_id = 0;

	 VEC2 user_pos = g_obj_get_position(0);

	 glActiveTexture ( GL_TEXTURE0 );
	 glBindTexture ( GL_TEXTURE_2D, shader->texture );

	 // for change position
	 trans_form_location = glGetUniformLocation ( shader->ID, "transform" );
	 glUniform4f (
		 trans_form_location,
		 user_pos.x,
		 user_pos.y,
		 0.0f,
		 0.0f
	 );

	 glUseProgram ( shader->ID );
	 glBindVertexArray ( shader->VAO );
	 glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

	 /*
	 trans_form_location = glGetUniformLocation( shader->ID, "transform" );
	 glUniform4f(trans_form_location, 0.0f, 0.0f, 0.0f, 0.0f);
	 //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	 glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	 //glDrawArrays(GL_TRIANGLES, 0, 6);
	 */
 }

 void gl_rander ( /* OBJ Array */ ) {

 }

void gl_shutdown_graphics( BUFFER_OBJECT* x ) {

	// !TODO
	glDeleteBuffers(1, &x->VAO);
	glDeleteBuffers(1, &x->VBO);
	glDeleteVertexArrays(1, &x->EBO);
}