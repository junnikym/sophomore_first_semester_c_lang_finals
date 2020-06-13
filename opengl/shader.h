#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#include <malloc.h>
#endif

#include <GL/glew.h>

// 쉐이더 파일을 로드하여 OpenGL에서 사용할 수 있도록 하는 함수
GLuint gl_load_shader ( const char * vertex_file_path,
				   		 	 const char * fragment_file_path );

#endif
