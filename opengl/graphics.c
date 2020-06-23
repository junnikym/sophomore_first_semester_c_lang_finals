#include "graphics.h"

void gl_clear_screen ( ) {
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );		// 화면을 검정색으로 만들어 줌
	glClear ( GL_COLOR_BUFFER_BIT );				// 버퍼를 비워줌
}

void gl_draw_sprite_obj ( const BUFFER_OBJECT* obj,
						  mat4 MVP,
						  const VEC2* current_sprite_pos,
						  const vec4* bland_color) {
	GLuint mvp_id;
	GLint texture_location = 0;
	
	/* 쉐이더의 texturePos에 텍스처를 자를 위치 정보를 등록하기 위해
	 * texturePos가 쉐이더의 어느 위치에 있는지 저장하여 해당 정보르 넘겨준다.
	 */
	if ( current_sprite_pos != NULL ) {	// 사용자가 텍스처를 자르고 싶을 경우 실행
		texture_location = glGetUniformLocation ( obj->ID, "texturePos" );
		glUniform2f( texture_location, current_sprite_pos->x, current_sprite_pos->y);
	}

	texture_location = glGetUniformLocation ( obj->ID, "spriteColor" );
	if ( bland_color == NULL ) 
		glUniform4f ( texture_location, 1.0f, 1.0f, 1.0f, 1.0f );
	else
		glUniform4f ( texture_location, 
					  (*bland_color)[0], (*bland_color)[1], (*bland_color)[2], (*bland_color)[3] );
	
	glActiveTexture ( GL_TEXTURE0 );					// 텍스쳐 유닛을 활성화

	glBindTexture ( GL_TEXTURE_2D, obj->texture );	// 해당 텍스처를 활성화된 텍스처 유닛에 바인딩
	
	/* MVP를 통하여 객체가 화면의 어디에 어떤식으로 표현될지 지정을 시켜준다.
	 * MVP는 Model, View, Projection 을 순서대로 곱한 값이다.
	 */
	mvp_id = glGetUniformLocation ( obj->ID, "MVP" );
	 
	glUseProgram ( obj->ID );		// 해당 쉐이더를 활성화 시켜준다.

	glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &MVP[0][0] );		// 쉐이더의 MVP에 mvp인자 값을 넘겨준다.
	glBindVertexArray ( obj->VAO );									// VAO를 쉐이더에 바인딩 해준다.
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );	// 객체를 그려줌.
}

 void gl_rander (  ) {
	 // 추후 추가 예정
 }







