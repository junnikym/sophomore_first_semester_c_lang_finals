#include "graphics.h"

int gl_load_shaders(const char* vertex_file_path, const char* fragment_file_path, GLuint* program_id) {
	FILE* fp;
	int file_size = 0;
	char* vertex_shader_code;
	char* fragment_shader_code;

	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

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

	// shader compile
	glShaderSource(vertex_shader_id, 1, &vertex_shader_code, NULL);
	glCompileShader(vertex_shader_id);

	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertex_shader_id, 512, NULL, error_log);
		fprintf(stderr, "fail to compile vertex shader : %s \n", error_log);

		glDeleteShader(vertex_shader_id);
		return -1;
	}

	glShaderSource(fragment_shader_id, 1, &fragment_shader_code, NULL);
	glCompileShader(fragment_shader_id);

	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragment_shader_id, 512, NULL, error_log);
		fprintf(stderr, "fail to compile fragment_shader shader ; %s \n", error_log);

		glDeleteShader(fragment_shader_id);
		return -1;
	}

	// link
	*program_id = glCreateProgram();

	glAttachShader(*program_id, vertex_shader_id);
	glAttachShader(*program_id, fragment_shader_id);

	glLinkProgram(*program_id);


	glGetProgramiv(*program_id, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(*program_id, 512, NULL, error_log);
		fprintf(stderr, "fail to link shader program ; %s \n", error_log);

		return -1;
	}

	glDetachShader(*program_id, vertex_shader_id);
	glDetachShader(*program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	free(vertex_shader_code);
	free(fragment_shader_code);

	return 0;
} // triangle_shader_program_id

VERTEX_BUF* gl_define_buffer_obj(VERTEX_BUF* p_out, const BUF_OBJ_ATT* data) {
	/*
	// for test
	static int i = 0;
	//i += 0.1;
	VEC2 delta = { 0, i };

	float* moved_vertex = (float*)malloc(data->vertex_data_size * sizeof(float));
	move_vertex_vec2(
		moved_vertex,
		data->vertex_data,
		data->vertex_data_size,
		&delta
	);
	*/
	// VBO
	glGenBuffers(1, &p_out->vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, p_out->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, data->vertex_data_size, data->vertex_data, GL_STATIC_DRAW);

	glGenBuffers(1, &p_out->color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, p_out->color_buffer);
	glBufferData(GL_ARRAY_BUFFER, data->color_data_size, data->color_data, GL_STATIC_DRAW);

	// VAO
	glGenVertexArrays(1, &p_out->vertex_arr_id);
	glBindVertexArray(p_out->vertex_arr_id);

	// EBO
	GLuint triangleElementBufferObject;
	glGenBuffers(1, &triangleElementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->elem_data_size, data->elem_data, GL_STATIC_DRAW);

	//free(moved_vertex);

	return p_out;
}


// !TODO : make struct; this function's parameters -> struct members
int gl_vertex_link(GLuint* program_id, const VERTEX_BUF* buffers) {
	GLint position_attribute = 0;
	GLint color_attribute = 0;

	position_attribute = glGetAttribLocation(*program_id, "positionAttribute");
	if (position_attribute == -1) {
		fprintf(stderr, "fail to setting position attribute \n");

		return -1;
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffers->vertex_buffer);
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	color_attribute = glGetAttribLocation(*program_id, "colorAttribute");
	if (color_attribute == -1) {
		fprintf(stderr, "fail to setting color attribute \n");

		return -1;
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffers->color_buffer);
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(color_attribute);

	glBindVertexArray(0);

	return 0;
}