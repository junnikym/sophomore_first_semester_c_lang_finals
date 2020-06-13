#include "buffer_obj.h"

// ------------------------------------------------------- //
// ----- OpenGL Graphics functions		------------------

void buf_obj_init ( BUFFER_OBJECT* lhs ) {
	lhs->VAO = 0; lhs->VBO = 0; lhs->EBO = 0;		// Buffer Object 구조체를 초기화
	lhs->ID = 0;
	lhs->texture = 0;
	lhs->n = 0;
}

void set_square_vertices ( GLfloat p_out[32], VEC2 size, double z, VEC2 texture ) {
	
	/* 버텍스 데이터에서 꼭짓점의 위치를 저장하는 데이터 위치와 텍스쳐 크기를 나타네는 데이터 위치를
	 * 통하여 꼭짓점 위치 데이터를 조작하여 크기를 조작하는 함수
	 */
	
	/*	position index	|	texture coords index
	 *	 0	 1	 2			|	6	 7
	 *	 8	 9	10			|	14	15
	 *	16	17	18			|	22	23
	 *	24	25	26			|	30	31
	 */
	
	// set position
	p_out[ 0] =  size.x;		p_out[ 1] =  size.y;	p_out[ 2] = z;
	p_out[ 8] =  size.x;		p_out[ 9] = -size.y;	p_out[10] = z;
	p_out[16] = -size.x;		p_out[17] = -size.y;	p_out[18] = z;
	p_out[24] = -size.x;		p_out[25] =  size.y;	p_out[26] = z;
	
	// set texture coord
	p_out[ 6] = texture.x;		p_out[ 7] = 0.0f;
	p_out[14] = texture.x;		p_out[15] = texture.y;
	p_out[22] = 0.0f;			p_out[23] = texture.y;
	p_out[30] = 0.0f;			p_out[31] = 0.0f;
}

void gl_define_buf_obj( BUFFER_OBJECT* p_out, const BUFFER_ATTRIBUTES* data, GLsizei n ) {
	p_out->n = n;
	
	glGenVertexArrays ( n, &(p_out->VAO) );		// Vertex Array Object를 생성
	glGenBuffers ( n, &(p_out->VBO) );			// Vertex Buffer Object를 생성
	glGenBuffers ( n, &(p_out->EBO) );			// Element Buffer Object를 생성	-> indices에 해당

	glBindVertexArray ( (p_out->VAO) );			// 생성한 VAO를 OpenGL에 바인드하여 사용함을 알림

	glBindBuffer ( GL_ARRAY_BUFFER, (p_out->VBO) );	// VBO를 바인드하여 사용함을 알림
	// VBO에 버텍스 데이터 사이즈만큼 데이터를 넘겨줌
	glBufferData ( GL_ARRAY_BUFFER,
				  	  data->vertices_size, data->vertices_data, GL_STATIC_DRAW );

	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, (p_out->EBO) );		// EBO를 바인드하여 사용함을 알림
	// VBO에 indices 데이터 사이즈 만큼 데이터를 넘겨줌
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER,
				  	  data->indices_size, data->indices_data, GL_STATIC_DRAW );

	// position attribute
	// 어디서부터 어디까지 어떤 데이터를 표현하였는지 OpenGL에 알려줌
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), (void*)0 );
	glEnableVertexAttribArray ( 0 );		// Position
	// color attribute
	glVertexAttribPointer ( 1, 3, GL_FLOAT, GL_FALSE,
								 8 * sizeof ( float ), (void*)(3 * sizeof ( float )) );
	glEnableVertexAttribArray ( 1 );		// Indices
	// texture coord attribute
	glVertexAttribPointer ( 2, 2, GL_FLOAT, GL_FALSE,
						   		 8 * sizeof ( float ), (void*)(6 * sizeof ( float )) );
	glEnableVertexAttribArray ( 2 );		// Texture
	
}

void gl_define_texture ( const GLuint* program_id, const GLuint* texture_buf, int n ) {
	// 쉐이더의 Texture ( Sampler2D ) 의 위치를 알아옴.
	GLint texture_location = glGetUniformLocation ( *program_id, "Texture" );
                  
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture_buf);	// 알아온 위치에 텍스처 데이터를 등록

	glUniform1i ( texture_location, n );
}

void gl_release_buf_obj	( BUFFER_OBJECT* buf_obj ) {
	glDeleteBuffers(buf_obj->n, &buf_obj->VAO);			// 등록된 객체를 해제 시켜줌
	glDeleteBuffers(buf_obj->n, &buf_obj->VBO);
	glDeleteVertexArrays(buf_obj->n, &buf_obj->EBO);
}

// ------------------------------------------------------- //
       
