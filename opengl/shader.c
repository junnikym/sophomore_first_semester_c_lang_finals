#include "shader.h"

GLuint gl_load_shader (const char * vertex_file_path, const char * fragment_file_path){
	FILE* fp = NULL;		// 쉐이더 파일을 읽어올 포인터
	int file_size = 0;		// 쉐이더 파일 크기
	
	GLint result = GL_FALSE;
	GLchar error_log[512] = "";
	
	GLuint program_id = 0;
	
	char* vs_code = NULL;		// Vertex Shader Code
	char* fs_code = NULL;		//	Fragment Shader Code

	// Create the shaders
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);			// 쉐이더를 생성하기 위해
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);		// 초기화를 진행
	
	// - READ Shader Code Files ------
	// ----- Vertex Shader File READ
	fp = fopen(vertex_file_path, "r");		// vertex 쉐이더 파일을 읽기 전용으로 읽어들임
	if (fp == NULL) {			// 파일 읽기 실패 시
		printf("fail to open vertex shader file");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);		// 파일의 끝 위치를 읽도록 이동한다.
	file_size = (int)ftell(fp);	// 현재 위치값을 불러와 파일의 크기를 알 수 있다.

	vs_code = (char*)malloc(file_size + 1);	// 파일의 크기만큼 메모리를 동적 할당.
	memset(vs_code, 0, file_size + 1);	 		// 동적할당 받을 메모리 전체를 0으로 초기화시켜준다.

	fseek(fp, 0, SEEK_SET);					// 파일의 처음 위치를 읽도록 이동
	fread(vs_code, file_size, 1, fp);			// 파일내용을 할당시킨 메모리에 저장한다.

	fclose(fp);	// 파일을 닫아줌.

	// ----- Fragment Shader File READ
	fp = fopen(fragment_file_path, "r");		// vertex 쉐이더와 같은 방식으로 진행
	if (fp == NULL) {
		printf("fail to open fragment shader file");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	file_size = (int)ftell(fp);

	fs_code = (char*)malloc(file_size + 1);
	memset(fs_code, 0, file_size + 1);
  
	fseek(fp, 0, SEEK_SET);
	fread(fs_code, file_size, 1, fp);

	fclose(fp);

	// - COMPILE Shaders -------------
	// ----- Compile Vertex Shader
	glShaderSource(vertex_shader_id, 1, &vs_code , NULL);	// 위에서 가져온 코드를 OpenGL에 넘겨줌
	glCompileShader(vertex_shader_id);						// 쉐이더를 컴파일

	// ( Check Vertex Shader )
	glGetShaderiv ( vertex_shader_id, GL_COMPILE_STATUS, &result );	// 컴파일 결과를 가져옴
	if (!result) {		// 컴파일 실패 시
		glGetShaderInfoLog(vertex_shader_id, 512, NULL, error_log);	// 어떤 구문이 오류인지 알려줌
		fprintf(stderr, "fail to compile vertex shader : %s \n", error_log);

		glDeleteShader(vertex_shader_id);	// 오류가 있는 쉐이더는 지워버림
	}

	// - Compile Fragment Shader
	glShaderSource(fragment_shader_id, 1, &fs_code , NULL);		// vertex 쉐이더와 동일한 방식으로 진행
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




















