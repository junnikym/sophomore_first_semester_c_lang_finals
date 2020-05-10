#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#include <malloc.h>
#endif

#include <GL/glew.h>

#include "shader.h"

GLuint gl_load_shader (const char * vertex_file_path, const char * fragment_file_path){
	FILE* fp = NULL;
	int file_size = 0;
	
	GLint result = GL_FALSE;
	GLchar error_log[512] = "";
	
	GLuint program_id = 0;
	
	char* vs_code = NULL;		// Vertex Shader Code
	char* fs_code = NULL;		//	Fragment Shader Code

	// Create the shaders
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	
	// - READ Shader Code Files ------
	// ----- Vertex Shader File READ
	fp = fopen(vertex_file_path, "r");
	if (fp == NULL) {
		printf("fail to open vertex shader file");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);

	vs_code = (char*)malloc(file_size + 1);
	memset(vs_code, 0, file_size + 1);

	fseek(fp, 0, SEEK_SET);
	fread(vs_code, file_size, 1, fp);

	fclose(fp);

	// ----- Fragment Shader File READ
	fp = fopen(fragment_file_path, "r");
	if (fp == NULL) {
		printf("fail to open fragment shader file");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);

	fs_code = (char*)malloc(file_size + 1);
	memset(fs_code, 0, file_size + 1);

	fseek(fp, 0, SEEK_SET);
	fread(fs_code, file_size, 1, fp);

	fclose(fp);

	// - COMPILE Shaders -------------
	// ----- Compile Vertex Shader
	glShaderSource(vertex_shader_id, 1, &vs_code , NULL);
	glCompileShader(vertex_shader_id);

	// ( Check Vertex Shader )
	glGetShaderiv ( vertex_shader_id, GL_COMPILE_STATUS, &result );
	if (!result) {
		glGetShaderInfoLog(vertex_shader_id, 512, NULL, error_log);
		fprintf(stderr, "fail to compile vertex shader : %s \n", error_log);

		glDeleteShader(vertex_shader_id);
	}

	// - Compile Fragment Shader
	glShaderSource(fragment_shader_id, 1, &fs_code , NULL);
	glCompileShader(fragment_shader_id);

	// ( Check Fragment Shader )
	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragment_shader_id, 512, NULL, error_log);
		fprintf(stderr, "fail to compile fragment_shader shader ; %s \n", error_log);

		glDeleteShader(fragment_shader_id);
	}
	
	// - Link The Program ------------
	program_id = glCreateProgram();
	
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);

	// ( Check the program )
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	if ( !result ) {
		glGetProgramInfoLog(program_id, 512, NULL, error_log);
		fprintf(stderr, "fail to link shader program ; %s \n", error_log);
	}

	
	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);
	
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return program_id;
}


