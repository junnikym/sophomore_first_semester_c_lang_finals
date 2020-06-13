#ifndef BUFFER_OBJ_H
#define BUFFER_OBJ_H

#include "../vector2.h"
#include "../types.h"
#include "texture.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <cglm/cglm.h>

// ------------------------------------------------------- //
// ----- Buffer Structure	------------------------------

typedef struct _BUFFER_OBJECT {	// 물체의 정보를 저장한 객체를 모아둔 구조체
	GLuint VBO, VAO, EBO;	// 물체의 정보를 저장할 객체
	GLuint ID;					// 버퍼를 저장할 프로그램 객체
	GLuint texture;			// 텍스쳐를 저장할 객체
	GLsizei n;
	// ! TODO : append sprite_info
} BUFFER_OBJECT;

typedef struct _BUFFER_ATTRIBUTES {	// 물체를 객체화하기 위해 넘겨줄 데이터를 모아둔 구조체
	GLfloat* vertices_data;		// 물체의 꼭짓점
	int vertices_size;			// vertex_data 배열의 사이즈
	GLuint* indices_data;		// 꼭짓점을 연결할 데이터
	int indices_size;			// indices_data 배열의 사이즈
} BUFFER_ATTRIBUTES;

// ------------------------------------------------------- //
// ----- STD BUFFERS	----------------------------------

// --- Square Const Buffers

const static GLfloat g_SQUARE_VERTICES[] = {
	// positions          // colors           // texture coords
	 1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
	 1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f, // bottom right
	-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, // bottom left
	-1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f  // top left
};

const static GLuint g_SQUARE_INDICES[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

const static BUFFER_ATTRIBUTES g_SQUARE_DATA = {
	&g_SQUARE_VERTICES,
	sizeof(g_SQUARE_VERTICES),
	&g_SQUARE_INDICES,
	sizeof(g_SQUARE_INDICES)
};
  
// ------------------------------------------------------- //
// ----- OpenGL Graphics functions		------------------

void 	buf_obj_init		 	 ( BUFFER_OBJECT* lhs );	// 구조체를 초기화하는 함수

// 물체의 크기와 텍스처의 크기 정보를 입력해줄 함수
void 	set_square_vertices	 ( GLfloat p_out[32], VEC2 size, double z, VEC2 texture );

// 물체의 데이터를 모아둔 구조체를 통해 객체를 생성
void	gl_define_buf_obj	 ( BUFFER_OBJECT* p_out, const BUFFER_ATTRIBUTES* data, GLsizei n);

// OpenGL에 텍스쳐 정보를 넘겨주어 객체화 시킴
void	gl_define_texture	 ( const GLuint* program_id, const GLuint* texture_buf, int n );

// OpenGL로부터 생성된 객체를 해제시켜주는 함수
void	gl_release_buf_obj	 ( BUFFER_OBJECT* buf_obj );

// ------------------------------------------------------- //

#endif /* BUFFER_OBJ_H */
  
    
