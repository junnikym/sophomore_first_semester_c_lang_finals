#include "graphics.h"

int gl_load_shaders(const char* vertex_file_path, const char* fragment_file_path) {
	GLuint vertex_shader_id = 0;
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	FILE* fp;
	int file_size = 0;
	char* vertex_shader_code;
	char* fragment_shader_code;

	GLuint vertex_shader = 0;
	GLuint fragment_shader = 0;

	GLint result = 0;
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

	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, error_log);
		fprintf(stderr, "fail to compile vertex shader : %s \n", error_log);

		return -1;
	}

	glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, error_log);
		fprintf(stderr, "fail to compile vertex shader ; %s \n", error_log);

		return -1;
	}

	triangle_shader_program_id = glCreateProgram();

	glAttachShader(triangle_shader_program_id, vertex_shader);
	glAttachShader(triangle_shader_program_id, fragment_shader);

	glLinkProgram(triangle_shader_program_id);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glGetProgramiv(triangle_shader_program_id, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(triangle_shader_program_id, 512, NULL, error_log);
		fprintf(stderr, "fail to link shader program ; %s \n", error_log);

		return -1;
	}

	free(vertex_shader_code);
	free(fragment_shader_code);

	return 0;
}

int gl_define_vertex_arr_obj() {
	GLint position_attribute = 0;
	GLint color_attribute = 0;

	float position[] = {
		 0.0f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	float color[] = {
		 1.0f,  0.0f, 0.0f,
		-0.0f, -1.0f, 0.0f,
		-0.0f,  0.0f, 1.0f,
	};

	// VBO
	glGenBuffers(1, &triangle_pos_vertex_buf_obj_id);
	glBindBuffer(GL_ARRAY_BUFFER, triangle_pos_vertex_buf_obj_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

	glGenBuffers(1, &triangle_color_vertex_buf_obj_id);
	glBindBuffer(GL_ARRAY_BUFFER, triangle_color_vertex_buf_obj_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

	glGenVertexArrays(1, &triangle_vertex_arr_obj);
	glBindVertexArray(triangle_vertex_arr_obj);

	position_attribute = glGetAttribLocation(triangle_shader_program_id, "positionAttribute");
	if (position_attribute == -1) {
		fprintf(stderr, "fail to setting position attribute \n");

		return -1;
	}

	glBindBuffer(GL_ARRAY_BUFFER, triangle_pos_vertex_buf_obj_id);
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	color_attribute = glGetAttribLocation(triangle_shader_program_id, "colorAttribute");
	if (color_attribute == -1) {
		fprintf(stderr, "fail to setting color attribute \n");

		return -1;
	}

	glBindBuffer(GL_ARRAY_BUFFER, triangle_color_vertex_buf_obj_id);
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(color_attribute);

	glBindVertexArray(0);

	return 0;
}
